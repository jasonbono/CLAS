#!/bin/bash


echo "running produceana"
sleep 1
perl produceana.pl -Tkpkppim -vv34k -M100 -d/Users/Bono/clas/analyser/runana
#perl produceana.pl -Tkpkppim -vv34k -M100 -d/u/home/jbono/SendGet/runana

# -T topology
# -v version
# -M max files
# -d directory of this script
# -S submit jobscript as a job