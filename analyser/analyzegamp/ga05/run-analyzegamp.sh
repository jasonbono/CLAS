#!/bin/bash

#$ cd /path/to/files

FILES=/Users/Bono/clas/rootfiles/g12/mc/gamp/v07/copy/MC_*.gamp

echo running over: 
for f in $FILES
do
	
	echo $f
done
echo ---------------------------------------

for f in $FILES
do
	
	ga03 $f
done

 	#cat $files > bigfile
