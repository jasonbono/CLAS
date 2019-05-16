#!/bin/bash

#Author: Jason Bono
#Date: October 16 2012
#Notes: This runs the perl script that commands the most recent analyzer to 
#        to analyze the skims.

#Warning: dont specify -Tkpkppim, specify -T2kppim to ensure the full skim is analyzed

echo "running produceana"
#sleep 1
#perl produceana.pl -T2kppim -vv05 -M7000 -d/u/home/jbono/analyser/runana/ra05
#sleep 1
#perl produceana.pl -Tkpkp -vv03 -M7000 -d/u/home/jbono/analyser/runana/ra05


perl produceana.pl -T2kppim -vv07 -M7000 -d/u/home/jbono/analyser/runana/ra09
#sleep 1



# -T topology
# -v analyzer version
# -M max files
# -d directory of this script
# -S submit jobscript as a job