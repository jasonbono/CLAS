#!/bin/bash

#author: jason bono	
#date: Feb 20 2014

idir=/w/hallb/clasg12/jbono/analyzed-data/2kppim/v07
odir=/w/hallb/clasg12/jbono/analyzed-data/2kppim/v07/concated
echo "looping over the files in the input directory"
COUNTER=0;
FILES=$idir/*.bos
for f in $FILES
do
	touch ${odir}/2kppim-v07.bos
	#file_suffix="${f#*.}" 
	echo "catting $f"
	echo "counter is $COUNTER"
	cat $f >> ${odir}/2kppim-v07.bos
	let "COUNTER += 1"		
done

echo "finished all cached files"
exit