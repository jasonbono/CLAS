#!/apps/bin/perl -w
use diagnostics;
use warnings;


# Author: Jason Bono
# Date: Feb 26 2014
 

		print "what analyzer? example: v10,v11 \n";
		chomp ($ana = <>);
		print "analyzer version is $ana \n";

		
		# Specifys the in and out directorys
		$inputdir = "/w/hallb/clasg12/jbono/analyzed-data/2kppim/$ana/rootfiles";
		$outputdir = "$inputdir/hadded";
		print "inputdir is: $inputdir \n";
		print "outputdir is: $outputdir \n";
		
			
		#the new way of doing it
		$filecount = 0;
		#------------hadd------------	
		for ($i = 0; $i <= 9; $i++) #the $i is in the file name that specifies the last digit ($i) in the run number (2kppim-v09_5652$i.A0X.bos.root) 
		{
			print "gathering all 2kppim-${ana}*$i.*.root files \n";
			my @files = glob("${inputdir}/2kppim-${ana}*$i.*.root");
			system("hadd -f ${outputdir}/temp-${i}.root @files");
			$filecount += scalar @files;
			print " \n";
		}
		
		
		
		
		system ("hadd -f ${outputdir}/2kppim-$ana.root  ${outputdir}/temp-*.root");
		system ("rm ${outputdir}/temp-*.root");
		
		
		print "The total number of files hadded were \n";
		print $filecount;
		print "\n";
		print "MAKE SURE THIS IS CORRECT!"	