#!/apps/python/bin/python

from sys import argv, stdout, exit
from os import path, makedirs, remove, environ
from shutil import move
from subprocess import Popen
from time import time, sleep
from random import shuffle
from tempfile import NamedTemporaryFile
from argparse import ArgumentParser, RawDescriptionHelpFormatter

### exectution shell for all subprocesses ##############################
shell = '/bin/tcsh'
########################################################################

def mkdir_p(path):
    'provides function similar to unix command: mkdir -p'
    try:
        makedirs(path)
    except OSError:
        pass

def run(cmd, execdir=None, envmap=None, outfile=None, outfile_timeout=300, minsize=1e4, timeout=None):
    '''
        this executes a command, [cmd], in the default shell in the directory [execdir] with the environment specified by [envmap]. If [outfile] is given, then it is expected to be greater than [minsize] bytes after [outfile_timeout] seconds. If not, then the process is killed and a the functions returns False. Once the command finishes, the function returns True. There is an overall [timeout], in hours, after which the job is killed regardless of output file size.
    '''

    if shell == '/bin/tcsh':
        cmd = 'source ~/.tcshrc && '+cmd

    # execute command in background shell
    proc = Popen(cmd, cwd=execdir, env=envmap, shell=True, executable=shell)

    # setup final checkpoint time if needed
    if not timeout is None:
        fin_time = time() + (60*60*timeout)

    if not outfile is None:

        # setup checkpoint time
        outfile_fin_time = time() + outfile_timeout

        # clock ticks every 5 seconds
        while (proc.poll() is None) and (time() < outfile_fin_time):
            sleep(5)

        # either process has exited or the time check is reached
        if time() > outfile_fin_time:

            # the file must exist and the size must be greater than minsize
            if (not path.exists(outfile)) or (path.getsize(outfile) < minsize):

                # job failed (no output)!
                print '    after ' + outfile_timeout + ' seconds, ' + \
                      'output (' + outfile + ') is only ' + \
                      path.getsize(outfile) + ' bytes.\n' + \
                      '    job timeout!\n'
                proc.kill()
                return False

    # observe overall timeout if specified
    if not timeout is None:

        # clock ticks every 5 seconds
        while (proc.poll() is None) and (time() < fin_time):
            sleep(5)

        # either process has exited or the final time check is reached
        if (proc.poll() is None) and (time() > fin_time):

            # job failed (timeout)!
            print '    job timeout! (>'+timeout+' hours)\n'
            proc.kill()
            return False

    proc.wait()

    # successful completion of process
    return True

def write_submit_file(subfile, cmdargs=None, infiles=None, outfiles=None, propmap=None, subcount=0):
    '''
        Creates the submit file to passed to the jsub executble on the JLab CUE machines. The command to run is always this python script file. Arguments can be specified in the list propmap['args']. [infiles] and [outfiles] are both lists of 2-tuples for example: [(src1, dest1), (src2, dest2), ...]. MSS stub files are automatically prepended with "mss:" to ensure Auger handles them properly.

        propmap is type dict() with these keys:
            experiment (g12, ...)
            track      (reconstruction, analysis, simulation, debug)
            timelimit  (hours)
            memspace   (MB)
            diskspace  (GB)
    '''
    wfcmd = argv[0]+' -c'+str(subcount)

    default_propmap = {
        'track'          : 'analysis',
        'timelimit'      : 24,
        'timelimit_unit' : 'hours',
        'memspace'       : 1024,
        'memspace_unit'  : 'MB',
        'diskspace'      : 10,
        'diskspace_unit' : 'GB',
        }

    for d in default_propmap:
        if not d in propmap:
            propmap[d] = default_propmap[d]

    if not 'experiment' in propmap:
        print '    Workflow Error: you must specify an experiment.'
        exit -1

    if propmap['track'] is 'debug':
        propmap['timelimit'] = 30
        propmap['timelimit_unit'] = 'minutes'

    subfile.write(
        '<Request>\n'
        '<Project name="'+propmap['experiment']+'"/>\n'
        '<Track name="'+propmap['track']+'"/>\n'
        '<Name name="'+path.basename(argv[0]).replace('.py','')+'-'+str(subcount).rjust(3,'0')+'"/>\n'
        '<TimeLimit time="'+str(propmap['timelimit'])+'" unit="'+propmap['timelimit_unit']+'"/>\n'
        '<Memory space="'+str(propmap['memspace'])+'" unit="'+propmap['memspace_unit']+'"/>\n'
        '<DiskSpace space="'+str(propmap['diskspace'])+'" unit="'+propmap['diskspace_unit']+'"/>\n'
        '<Command><![CDATA[\n')

    # the command to run is always this python script.
    # arguments can be specified in the list [args].
    subfile.write('    '+wfcmd)
    if not cmdargs is None:
        for a in cmdargs:
            subfile.write(' '+a)
    subfile.write(
        '\n]]></Command>\n'
        '<Job>\n')

    # input and output files. These automatically handle mss stub files.
    if not infiles is None:
        for infile, infilelocal in infiles:
            subfile.write('    <Input src="')
            if infile[:5] == '/mss/':
                subfile.write('mss:')
            subfile.write(infile+'" dest="'+infilelocal+'"/>\n')

    if not outfiles is None:
        for outfilelocal, outfile in outfiles:
            subfile.write('    <Output src="'+outfilelocal+'" dest="')
            if outfile[:5] == '/mss/':
                subfile.write('mss:')
            subfile.write(outfile+'"/>\n')

    subfile.write(
        '</Job>\n'
        '</Request>\n')

    subfile.flush()

    f = open(subfile.name, 'r')
    print '    submit file created:\n', f.read()
    f.close()

def submit(subfilename):
    '''
        submits a job to the JLab farm.
    '''
    # submit the job to the queue
    cmd = 'jsub -xml '+subfilename
    run(cmd)

def is_done_locally(job):
    for outfile, _ in job.output_files:
        if not path.exists(outfile):
            return False
    return True

def is_done(job):
    for _, outfile in job.output_files:
        if not path.exists(outfile):
            return False
    return True

def clear_local_output_files(job):
    mkdir_p('failed')
    for outfile, _ in job.output_files:
        if path.exists(outfile):
            print 'mv', outfile, 'failed/'
            move(outfile, 'failed/'+outfile)

def clear_output_files(job):
    for _, outfile in job.output_files:
        if path.exists(outfile):
            print 'rm', outfile
            remove(outfile)





class Job:
    '''
        A set of jobs to run. The __init__() method takes enough arguments to define:
            1. all jobs this script is responsible for
            2. the specific job this instance is going to execute

        These methods are used in the main loop and must be included:
            run(timeout)
                timeout in hours.
                returns True or False based on successful completion
            next_job()
                returns the next job that will be submitted to the farm.
                This can be randomized or sequential.

        self.input_files is a list of 2-tuples:
            [(remote_input_file_1, local_input_file_1),
             (remote_input_file_2, local_input_file_2),
             ... ]

        self.output_files is similar self.input_files:
            [(local_output_file_1, remote_output_file_1),
             (local_output_file_2, remote_output_file_2),
             ... ]

        self.propmap is of type dict() and must include the 'experiment'
        key, but which may also include these (defaults shown):
            'track'          : 'analysis',
            'timelimit'      : 24,
            'timelimit_unit' : 'hours',
            'memspace'       : 1024,
            'memspace_unit'  : 'MB',
            'diskspace'      : 10,
            'diskspace_unit' : 'GB',
    '''

    def __init__(self, run, maxindex, index='A00'):
        self.run_number = run
        self.maxindex = maxindex
        self.index = index

        # input and output directories
        mssdir = '/mss/clas/g12/production/pass1/bos'
        skimdirs = '1-1ckaon1ctrk 2-2pos1neg_not_1ckaon1ctrk 3-2ctrk_not_2pos1neg_1ckaon1ctrk 4-not_2ctrk_2pos1neg_1ckaon1ctrk 5-other'.split()
        outdir = '/mss/clas/g12/production/pass1/user_skims/jbono/kpppim'

        # setup output directories (if they don't exist already)
        #mkdir_p(workdir)

        # input file list
        self.input_files = []
        for ind in self.index_list(index, maxindex):
            self.input_files += [ (
                path.join(mssdir, skimdirs[0], run+'.'+ind),
                '.'.join(['input',run,ind,'bos']) ) ]

        # output file list
        self.output_files = [(
            'out.bos',
            path.join(outdir, '.'.join(['kpppim',run,index[:-1]+'X','bos']))
            )]

        # job properties
        self.propmap = {
            'experiment' : 'g12',
            'track' : 'analysis',
            'timelimit' : 4,
            'timelimit_unit' : 'hours',
            'diskspace' : 15,
        }

    def index_list(self, ind, maxind):
        if ind[:2] == maxind[:2]:
            return [ind[:2]+str(i) for i in xrange(int(maxind[-1])+1)]
        return [ind[:2]+str(i) for i in xrange(10)]

    def index_list_10s(self, maxind):
        if maxind[0] is 'B':
            indlist = ['A' + str(n).rjust(2,'0') for n in xrange(0, 100, 10)]
            indlist += ['B' + str(n).rjust(2,'0') for n in xrange(0, int(maxind[1:])+1, 10)]
        else:
            indlist = ['A' + str(n).rjust(2,'0') for n in xrange(0, int(maxind[1:])+1, 10)]
        return indlist

    def next_job(self):
        '''
            return a Job instance or False if all jobs are complete.
        '''
        indexlist = self.index_list_10s(self.maxindex)

        # randomize next job
        shuffle(indexlist)
        print 'next job. possible indexes:', indexlist

        for i in indexlist:
            nextjob = Job(self.run_number, self.maxindex, i)
            if not (is_done(nextjob) or is_done_locally(nextjob)):
                return nextjob
        return False

    def check_output(self):
        for local_file, remote_file in self.output_files:
            if path.getsize(local_file) < 1e6:
                return False
        return True



    def run(self, timelimit=4.):
        '''
            timeout in hours
        '''
        # must finish this at least five minutes before Auger will kill this job
        fin_time = time() + ((60*60*timelimit) - 5*60)

        cmd = 'kpppim-skim -oout.bos input.*.bos'
        if not run(cmd, outfile='out.bos', timeout=(fin_time - time())):
            return False

        if not self.check_output():
            return False

        return is_done_locally(self)




if __name__ == '__main__':

    parser = ArgumentParser(description="Johann's JLab Workflow Script.\nFiltering BOS files.",
        epilog='Typical usage might be something like:\n    g12runs -tpass1 -m | xargs -n2 '+path.basename(argv[0])+' -j',
        formatter_class=RawDescriptionHelpFormatter)

    # options to maintain submission count and initial injection into the queue
    parser.add_argument('-c', '--subcount', action='store', dest='subcount', type=int, default=0,
        help='number of times this script has been resubmitted to the farm.')
    parser.add_argument('-j', '--inject', action='store_true', default=False,
        help='submit immediately without running a command first. Used for injecting this workflow into the queue.')

    ### these options define the Job parameters
    parser.add_argument('run', action='store',
        help='Run number associated with this workflow instance.')
    parser.add_argument('maxindex', action='store',
        help='Maximum index number for this run.')
    parser.add_argument('-i', '--index', action='store', default='A00',
        help='Index number associated with this workflow instance.')

    args = parser.parse_args()

    print '    submit count:', args.subcount
    print '    inject into queue?', args.inject

    print '    run:', args.run
    print '    maximum index:', args.maxindex
    print '    this index:', args.index

    job = Job(args.run, args.maxindex, args.index)

    if not args.inject:
        if not is_done(job):
            print '    running command now...'
            if not job.run():
                print '    job failed!'
                clear_local_output_files(job)

    print '    getting next job...'
    nextjob = job.next_job()

    if nextjob:
        cmdargs = [args.run, args.maxindex, '-i'+nextjob.index]

        subfile = NamedTemporaryFile()

        write_submit_file(subfile,
            cmdargs=cmdargs,
            infiles=nextjob.input_files,
            outfiles=nextjob.output_files,
            propmap=nextjob.propmap,
            subcount=args.subcount+1)

        print '    submitting...'
        submit(subfile.name)

        subfile.close()
        exit(0)

    print '    All jobs appear to be done!'
    exit(0)



