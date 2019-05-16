#!/apps/bin/perl -w
use diagnostics;
use warnings;


# Author: Jason Bono
# Date: Jan 7 2013 (updated May 26 2013)
 

# Usage:         perl myhadd-sim.pl

#          This is an Interactive script
#           Answer the questions asked
#             Questions regarding (Topology, iteration,)
 
###########################################farm###################################################################



		
		print "what type? example: 2kppim  2kppim-gsim  gamproot-100  NegPol-2kppim  NegPol-gamproot  PosPol-2kppim  PosPol-gamproot (not including gampascii)\n";
		chomp ($type = <>);
		print "using $type type \n";
		print "what iteration number is assocated with theese files example: i1,i2,i3 etc \n";
		chomp ($iteration = <>);
		print "using iteration $iteration \n";
		print "what is the lowest try number in the range? eg '0'  \n";
		chomp ($trylow = <>);
		print "what is the highest try number in the range eg '9' \n";
		chomp ($tryhigh = <>);
		
		# Specifys the in and out directorys
		$inputdir = "/w/hallb/clasg12/jbono/sim/DATA";
		$outputdir = "/w/hallb/clasg12/jbono/sim/DATA/hadded";
		print "inputdir is: $inputdir \n";
		print "outputdir is: $outputdir \n";
		
		#$filecount = 0;
		#------------hadd------------	
		#for ($i = 2; $i <= 5; $i++) {
		#	for ($try = $trylow; $try <= $tryhigh; $try++){  #the $i is in the file name that specifies energy like {i}.55 GeV 
		#		print "gathering all MC*-*-*_${i}*${iteration}t${try}*.root files \n";
		#		my @files = glob("${inputdir}/${iteration}t${try}/${type}/MC*-*-*_${i}*${iteration}t${try}*.root");
		#		system("hadd -f ${outputdir}/MC-${iteration}t${try}-${type}-${i}.root @files");
		#		$filecount += scalar @files;
		#		print " \n";
		#	}
		#}
		
		
		
		
		#the new way of doing it
		$filecount = 0;
		#------------hadd------------	
		for ($i = 2; $i <= 5; $i++) #the $i is in the file name that specifies energy like {i}.55 GeV 
		{
			for ($try = $trylow; $try <= $tryhigh; $try++)
			{
				for ($j = 0; $j <= 9; $j++) #the $j is in the file name that specifies energy like 3.{j}43 
				{
					print "gathering all MC*-*-*_${i}.${j}*${iteration}t${try}*.root files \n";
					my @files = glob("${inputdir}/${iteration}t${try}/${type}/MC*-*-*_${i}.${j}*${iteration}t${try}*.root");
					system("hadd -f ${outputdir}/MC-${iteration}t${try}-${type}-${i}.${j}.root @files");
					$filecount += scalar @files;
					print " \n";
				}
				#get those pesky ones with energys like 5 instead of 5.234
				print "gathering extras: all MC*-*-*_${i}.${iteration}t${try}*.root files \n";
				my @files = glob("${inputdir}/${iteration}t${try}/${type}/MC*-*-*_${i}.${iteration}t${try}*.root");
				system("hadd -f ${outputdir}/MC-${iteration}t${try}-${type}-${i}.root @files");
				$filecount += scalar @files;
				print " \n";
			}
		}
		
		
		



		
		system ("hadd -f ${outputdir}/MC-${iteration}t${trylow}-t${tryhigh}-${type}.root  ${outputdir}/MC-${iteration}t*-${type}-*.root");
		system ("rm ${outputdir}/MC-${iteration}t*-${type}-*.root");
		
		
		print "The total number of files hadded were \n";
		print $filecount;
		print "\n";
		print "MAKE SURE THIS IS CORRECT!"	




