#!/bin/bash


#jason bono
#july 6 2012
#
#            --------------------program will:------------------
#  1) make sure the data is cached (just refrence somthing on tape and the file will automaticly be cached)
#  2) analyze the input/produce output


#the varaibles to pass arguments to
topology=TTT # the 2kppim version (-T)
topology2=ttt # the kpkppim version (topology and topology2 are identical otherwise)
maxfiles=MMM # the number of files specified to analyze (-M) 
anaversion=VVV # the version of the analyzer (-v)
treename=${anaversion}
submit=SSS #weather or not to submit as job. 


# initize the directorys
inputdir=/cache/mss/clas/g12/production/pass1/user_skims/jbono/${topology}
#inputdir=/w/hallb/clasg12/samples/ppippim #just for ppippim (has been made redudant)
ana=/u/home/jbono/analyser/g12/LINKS/${topology}-${anaversion}
outputdir=/w/hallb/clasg12/jbono/analyzed-data/${topology}/${anaversion}


# names
input_prefix=${topology2}-${anaversion}
output_prefix=${topology}-${anaversion}

#make sure the output directory exists
if [[ -d $outputdir ]];
	then
	echo output directory $outputdir exists
	else
	echo output directory $outputdir DNE, making the directory
	mkdir $outputdir
fi
sleep 3


# show how many files are in the input directory
echo "the number of files in $inputdir is"
\ls $inputdir | wc -w
echo "should be 6507 for a full skim (for kaon data)"


# show how many files are already finished
echo "the number of files already analyzed in $inputdir is"
\ls $outputdir | wc -w

#looping over all the files in the input directory
echo "looping over the files in the input directory"
COUNTER=0;
FILES=$inputdir/${topology2}*.bos
for f in $FILES
do	

	#exit program if counter exeeds the specified maximum
	if [ "$COUNTER" == "$maxfiles" ]
	then
		echo "finished processing $COUNTER files as specified"
		exit
	fi

	#chop the file extention off the string $f
	output_suffix="${f#*.}"  # suffix should be in 57293.A3X.bos format
	echo "========================================================================"
	echo "Processing $f" # f should be in /path/kpkppim.54444.B2X.bos format
	echo "counter is $COUNTER"


	###to output root file	
	#dont do the files that have already been created	
	# if [ ! -f ${outputdir}/${output_prefix}_${output_suffix}.root ];
	# then
	#     echo "${output_prefix}_${output_suffix}.root NOT YET CREATED... creating now:"
		# #start analyzing
		# ${ana} -a${treename}.view -X1 -C1 $f
		# ${ana} -L > ${treename}.lab
		# makent ${treename} < ${treename}.lab > ${treename}.C
		# root -q -l ${treename}.C
		# #cleanup time
		# rm ${treename}.C
		# rm ${treename}.view
		# rm ${treename}.lab
		# if [ !$submit ]
		# then
		# 	mv ${treename}.root ${outputdir}/${output_prefix}_${output_suffix}.root	#move this to claswork only of running interactivly
		# elif [ $submit ]
		# then
		# echo "submit = $submit"
		# fi
		# 	#increment the counter
		# 	let "COUNTER += 1"
		# else
		# 	echo "${output_prefix}_${output_suffix}.root has already been created... skiping:"
		# fi
	
		
	#to output bosfile
	#dont do the files that have already been created	
	if [ ! -f ${outputdir}/${output_prefix}_${output_suffix} ];
	then
		echo "${output_prefix}_${output_suffix} NOT YET CREATED... creating now:"
		${ana} -o${output_prefix}_${output_suffix} -X1 -C1 $f
		mv ${output_prefix}_${output_suffix} ${outputdir}/${output_prefix}_${output_suffix}
		#increment the counter
		let "COUNTER += 1"
		else
			echo "${output_prefix}_${output_suffix}.bos has already been created... skiping:"
		fi
		
	done
echo "finished all cached files"
exit

