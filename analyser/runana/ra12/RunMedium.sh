#!/bin/bash
#jason bono
#Feb 26 2014

#Choose thisana, thatana, indir and outdir. everything else should be automatic
#this must be run from the work disk because it handles big files

#choose the analyzer
top=ppippim 
thisana=v04 #the analyzer that will be run
thatana=v09 #the analyzer used to produce the bosfiles (only relavant for inputdir=$work option)
ana=/u/home/jbono/analyser/g12/LINKS/$top-${thisana}
tree=${thisana}

#choose the input 
workmany=/w/hallb/clasg12/jbono/analyzed-data/$top/${thatana}
worksingle=/w/hallb/clasg12/jbono/analyzed-data/$top/${thatana}/concated
tape=/cache/mss/clas/g12/production/pass1/user_skims/jbono/$top
#indir=$workmany
indir=$tape
#indir=$worksingle

#choose the output
out_prefix=$top-${thisana}
outpath=/w/hallb/clasg12/jbono/analyzed-data/$top/${thisana}
rootout=${outpath}/rootfiles
bosout=${outpath}/bos
outdir=$rootout
#outdir=$bosout

if [[ -d $outpath ]];
	then
	echo out directory $outpath exists
	else
	echo out directory $outpath DNE, making the directory
	mkdir $outpath
fi
if [[ -d $outdir ]];
	then
	echo out directory $outdir exists
	else
	echo out directory $outdir DNE, making the directory
	mkdir $outdir
fi

echo "looping over the files in the input directory"
COUNTER=0;
FILES=$indir/*.bos
for f in $FILES
do

	#chop the file extention off the string $f. suffix should be in 57293.A3X.bos format
	if [ "$indir" == "$tape" ]
	then
		out_suffix="${f#*.}"
	else
		out_suffix="${f#*_}"
	fi
		
	#for bos output
	if [ "$outdir" == "$bosout" ]
	then
		if [ ! -f ${outdir}/${out_prefix}_${out_suffix} ];
			then
			echo "${out_prefix}_${out_suffix} NOT YET CREATED... creating now:"
			${ana} -o${out_prefix}_${out_suffix} -X1 -C1 $f
			mv ${out_prefix}_${out_suffix} ${outdir}/${out_prefix}_${out_suffix}
		else
			echo "${out_prefix}_${out_suffix}.bos has already been created... skiping:"
		fi
	fi
	
	#for root output
	if [ "$outdir" == "$rootout" ]	
	then
		if [ ! -f ${outdir}/${out_prefix}_${out_suffix}.root ];
			then
	    	echo "${out_prefix}_${out_suffix}.root NOT YET CREATED... creating now:"
			#start analyzing
			${ana} -a${tree}.view -X1 -C1 $f
			${ana} -L > ${tree}.lab
			makentfile ${tree} ${tree}.lab > ${tree}.C
			root -q -l ${tree}.C
			#cleanup time
			rm ${tree}.C ${tree}.view ${tree}.lab
			mv ${tree}.root ${outdir}/${out_prefix}_${out_suffix}.root
		else
			echo "${out_prefix}_${out_suffix}.root has already been created... skiping:"
		fi
	fi
	
done
echo "finished all files"
# #------------start analyzing-------------
# ${ana} -a${tree}.view -X1 -C1 ${input}
# ${ana} -L > ${tree}.lab
# makentfile ${tree} ${tree}.lab > ${tree}.C
# root -q -l ${tree}.C
# #----------------------------------------
# rm ${tree}.C ${tree}.lab ${tree}.view
# mv ${tree}.root ${out}