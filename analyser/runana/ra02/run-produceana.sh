#!/bin/bash


echo "running produceana"
sleep 1
perl produceana.pl -Tkpkppim -vv01 -M2 -d/u/home/jbono/analyser/runana/ra02
#perl produceana.pl -Tkpkppim -vv34k -M100 -d/u/home/jbono/SendGet/runana

# -T topology
# -v analyzer version
# -M max files
# -d directory of this script
# -S submit jobscript as a job