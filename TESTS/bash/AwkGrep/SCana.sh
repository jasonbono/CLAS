#!/bin/bash

cat bosdumpSC.txt | egrep 'Group:|ID:' | while read line
do
	a=$(echo $line | awk '{print $1}')
	if [ $a == "Group:" ]
	then
		#echo "\n" >> text.txt
		s=$(echo $line | awk '{print $3}')
		b=$(echo $line | awk '{print $4}')
		echo "$s $b" >> text.txt
		#echo "\n"  >> text.txt
		#b="yes"
	elif [ $a == "ID:" ]
	then
		b=$(echo $line | awk '{print $2}')
		echo "$a $b" >> text.txt
	fi
	echo $b
done