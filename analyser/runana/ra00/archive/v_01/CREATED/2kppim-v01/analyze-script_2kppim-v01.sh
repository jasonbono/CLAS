#!/bin/bash

#jason bono
#july 6
#
#            --------------------program will:------------------
#  1) make sure the data is cached (just refrence somthing on tape and the file will automaticly be cached)
#  2) analyze the input/produce output
#  3) hadd the ouput (add this once everything is opened)
#


#the varaibles to pass arguments to
topology=2kppim # the 2kppim version (-T)
topology2=kpkppim # the kpkppim version (topology and topology2 are identical otherwise)
maxfiles=100 # the number of files specified to analyze (-M) 
version=v01 # the version of the analyzer (-v)

# initize the directorys
inputdir=/w/cache/mss/clas/g12/production/pass1/user_skims/jbono/${topology}
ana=/u/home/jbono/analyser/g12/LINKS/${topology}-${version}
outputdir=/w/hallb/clasg12/jbono/analyzed-data/${topology}/${version}

# names
input_prefix=${topology2}-${version}
output_prefix=${topology}-${version}


#make sure the output directory exists
if [[ -d $outputdir ]];
	then
	echo output directory $outputdir exists
	else
	echo output directory $outputdir DNE, making the directory
	mkdir $ouputdir
fi
sleep 3


# show how many files are in the input directory
echo "the number of files in $inputdir is"
\ls | wc -w
echo "and there should be 6507 for a full skim"



#looping over all the files in the input directory
echo "looping over the files in the input directory"
COUNTER=1;
FILES=$inputdir/*
for f in $FILES
	
	do	
		#exit program if counter exeeds the specified maximum
		if [ "$COUNTER" -g "$maxfiles" ]
			echo "finished processing $COUNTER files as specified"
			exit
		fi

		#chop the file extention off the string $f
		ouput_suffix="${f#*.}"  # suffix should be in 57293.A3X.bos format
		echo "Processing $f" # f should be in /path/kpkppim.54444.B2X.bos format
		echo "counter is $COUNTER"
		
		#start analyzing
		${ana}/ -a${output_prefix}.view -X1 -C1 $f
	    ${ana} -L > ${output_prefix}.lab
	    makent ${ana} < ${output_prefix}.lab > ${output_prefix}.C
	    root -q -l ${output_prefix}.C
	    
		#cleanup time
		rm ${output_prefix}.C
	   	rm ${output_prefix}.view
		rm ${output_prefix}.lab
	    mv ${output_prefix}.root ${outputdir}/${output_prefix}_${output_suffix}.root
	  	
		#increment the counter
		let "COUNT += 1"

	done


# may want to add a hadd section here once its clear that the analyzer is up and working
