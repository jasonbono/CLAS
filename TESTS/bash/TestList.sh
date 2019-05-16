#!/bin/bash




indir=/Users/Bono/clas/TESTS/bash/inpath
FILES=$indir/*
outdir=/Users/Bono/clas/TESTS/bash/outpath

COUNT=0
for f in $FILES
do
	COUNT=$[$COUNT + 1]
	NAME=`basename $f`
	echo " moving  $NAME"
	echo " to $outdir/$NAME.a1c "
	
done

echo $COUNT