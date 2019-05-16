PROJECT:        g12
TRACK:          analysis
JOBNAME:		anajob_TTT_VVV
COMMAND         sh DDD/analyzescript_TTT_VVV.sh

INPUT_FILES: 
/mss/clas/g12/production/pass1/user_skims/jbono/TTT/*.bos
/u/home/jbono/analyser/g12/LINKS/TTT-VVV

OUTPUT_DATA: VVV.root
OUTPUT_TEMPLATE: /w/hallb/clasg12/jbono/analyzed-data/TTT/VVV/TTT-VVV*.root

SINGLE_JOB: true
DISK_SPACE: 10 GB
TIME: 800
MEMORY: 1 GB