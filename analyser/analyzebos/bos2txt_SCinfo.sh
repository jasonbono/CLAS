#!/bin/bash

DataType=MC
#DataType=Data

indir=/w/hallb/clasg12/jbono/SC_DC/SC/bos/$DataType
FILES=$indir/*
outdir=/w/hallb/clasg12/jbono/SC_DC/SC/text/$DataType

COUNT=0
for f in $FILES
do
	bosdump -M10000 -GSC $f | egrep 'Group:|ID:' | while read line
	do
		COUNT=$[$COUNT + 1]
		a=$(echo $line | awk '{print $1}')
		if [ $a == "Group:" ]
			then
			s=$(echo $line | awk '{print $3}')
			b=$(echo $line | awk '{print $4}')
			echo "$s $b" >> $outdir/SCinfo.txt
		elif [ $a == "ID:" ]
		then
			b=$(echo $line | awk '{print $2}')
			echo "$a $b" >> $outdir/SCinfo.txt
		fi
		#echo $b
	done
done
echo $COUNT >> $outdir/EventCount.txt