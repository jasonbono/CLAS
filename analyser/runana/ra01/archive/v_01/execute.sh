#!/bin/bash


echo "producing analyze-script.sh and job-script.sh by running the python scripts produce.pl \n"
sleep 1
echo "command:perl produce.pl -Tkpkppim -vv01 -M100 \n"
perl produce.pl -Tkpkppim -vv01 -M100
echo "wait..."
sleep 1
echo "submitting the job-script to the farm"
jsub ./CREATED/2kppim-v01/job-script_kpkppim-v01.sh