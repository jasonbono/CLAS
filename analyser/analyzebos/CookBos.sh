#!/bin/bash

#Author: Jason Bono
#Purpose: To cook the g12 data keeping all bank info


indir=/w/hallb/clasg12/jbono/RawData
FILES=$indir/*
outdir=/w/hallb/clasg12/jbono/RawData/Cooked

COUNT=0
for f in $FILES
do
	COUNT=$[$COUNT + 1]
	NAME=`basename $f`
	a1c  -T4 -sa -ct1930 -cm0 -cp0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -o$outdir/$NAME.a1c $indir/$NAME
done
echo "cooked $COUNT files"



#flags taken out of a1c: -R10 -X0