


may 16 2012:  changed the script_template, took out the -s command and changed the order of < with -L and -U 


may 4 2012:  v01:
got v00 working: ie it produces files from the templates. havent tested it on the farm yet.



changes: 
the script_template to my version. but kept same name
need to change the $dir in createmcjob to v01 (will have to do this for each sub directory)
changed the beam energy high and low so there is less iterations and therefor less created files

commented out the following form createmcjob
#if(/^-x(.+)/)     { $ppgenmode = $1;}
#if (/^-R(.+)/)     { $subdir = $1;}


altered the genr8input_template to match what i had done in /try5 in claswork


april 26 2012
sim_v00

this is my first modivication of leis perl script.  it should create new files from the templates in the new directory newdir

eventualy this is what i will use to make my simulation.

to do:
change the script_template to my version.
initize tslope to array elements in iteration rather than constant value
