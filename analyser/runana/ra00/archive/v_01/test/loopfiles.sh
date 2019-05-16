#!/bin/bash

#thiss teaches me how to loop through files and create
#substrings from character strings

inputdir=/Users/Bono/clas/analyser/runana/test

FILES=$inputdir/*
COUNT=0
for f in $FILES
	do	

		#echo "$COUNT"
		#echo "Processing $f file"
		let "COUNT += 1"
		x="${f#*.}"
		 #y=${x%.*}
		
		echo "f is $f"
		echo "x is $x"
		echo "y is $y"
		echo
		
		
		
		
		
		
		
		
	done
	
echo "DONE"