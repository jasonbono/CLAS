#!/bin/bash

#Author: Jason Bono
#Date: October 16 2012
#Notes: This runs the perl script that commands the most recent analyzer to 
#        to analyze the skims.

#Warning: dont specify -Tkpkppim, specify -T2kppim to ensure the full skim is analyzed

echo "running produceana"
sleep 1
perl produceana.pl -T2kppim -vv01 -M7000 -d/u/home/jbono/analyser/runana/ra03
sleep 1
perl produceana.pl -Tkpkp -vv01 -M7000 -d/u/home/jbono/analyser/runana/ra03

# -T topology
# -v analyzer version
# -M max files
# -d directory of this script
# -S submit jobscript as a job