s23: 
seting up the new simulation to run on the new centos 6.2.
additional changes include:
1) detached vertex in mygamp2part
2) using makentfile instead of makent (the new build of makent didnt output to root file)
3) upgraded analyzer from 2kppim-v05 t0 2kppim-v06 which had the kinfit taken out and was compiled on centos 6.2
4) new tslope
5) new beam energy
6) new Y* mass and width
7) increased statistics
8) run 56855 (run 10 no longer works for centos 6.2)
9) TAKE OUT POSPOL AND NEGPOL??
10) TAKE OUT PROCESSING OF GSIM FILES

s22: 
UPDATE: fixed the BEAM00 5.XXX parameter in the ffread card. the type was BEAM 0 0 5.XXX. 
this verion was used to generate i8 which should correct:

1)addressing the change in acceptance shown in i7 (from the BEAM error being fixed) by changing the beam normalization
2) addresing the large change in tslope shown in i7 (same reason)
3) addressing the double hyperons in the two higer energy bins.

 my ffread card but with RUNG 10 rather than the experimental run number as in previous verisons (i7t1 and presumably i8)


s21: mk's ffread card (i7t0)

august 27: now the execution of run-producesim.sh produces events from genr8 which go through all the processing untill a1c files are made.  from here the analyzer is run over the a1c files giving output of everything from .gamp to .root files.  THE ANALYZER USED MUST BE SOURCED IN THE .TCSHRC FILE!!  

 


jun 13. tried to change it to match what im doing in "try8" on the farm.


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


OTHER_FILES:    
 DDD/bin/genr8
 DDD/bin/ffread.card









#=================================================EXTRA=======================================
#   DDD - replaced by directory path (dir) (-w)
#   XXX - replaced by file name  (ebin)
#   YYY - replaced by path/filename
#   ZZZ - replaced by path/tag_file
#   VVV - replaced by version (jobversion)



#here is some extra crap that came with
 #DDD/bin/gamp2part
 #DDD/bin/gsim_bat
 #DDD/bin/gpp
 #DDD/bin/a1c

 #DDD/bin/recsis.tcl
 #DDD/bin/user_ana-g11-pass1


# INPUT_DATA      genr8input
# TOWORK

# OUTPUT_DATA     work.bosview
# OUTPUT_TEMPLATE DDD/bosview/egXXX.vVVV.bosview
# OUTPUT_DATA     work.gampview
# OUTPUT_TEMPLATE DDD/gampview/egXXX.vVVV.gampview

