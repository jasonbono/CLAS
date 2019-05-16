#!/apps/bin/perl -w
use diagnostics;
use warnings;


# Author: Jason Bono
# Date: Jan 7 2013
# Purpose: to take the g12 simulation files and hadd them into a singe file and make a symbolic link in LINKS
#note this is only religable anymore for the computer=farm and the finalize=yes part. 

# Usage:         perl myhadd-sim.pl

#          This is an Interactive script
#           Answer the questions asked
#             Questions regarding (Topology, iteration,)
 



print "is this on the farm or local? type 'farm' or 'local' \n";
chomp ($Computer = <>);
if ($Computer eq "local"){
	#set the links directory
	$Links = "/Users/Bono/clas/rootfiles/LINKS/sim";


	print "what topology? example: 2kppim,gamp,2kppim-gsim \n";
	chomp ($topology = <>);
	print "using $topology topology \n";
	print "what iteration number is assocated with theese files example: i1,i2,i3 etc \n";
	chomp ($iteration = <>);
	print "using iteration $iteration \n";


	# Specifys the in and out directorys
	$inputdir = "/Users/Bono/clas/rootfiles/g12/mc/";
	$outputdir = "/Users/Bono/clas/rootfiles/g12/mc/hadded/${iteration}";
	print "inputdir is: $inputdir \n";
	print "outputdir is: $outputdir \n";




	#------------hadd------------	
	print "hadding \n";
	my @files = glob("${inputdir}/${iteration}t*/${topology}/MC*.root");
	system("hadd -f ${outputdir}/MC_${iteration}_${topology}.root @files");
	print " \n ";

	#--------make link-------
	print "do you want to make the symbolic link in $Links type: yes or no \n";
	chomp ($choice = <>);
	if ($choice eq "yes"){
		print "creating a symbolic link: \n";
		print ("ln -s ${outputdir}/MC_${iteration}_${topology}.root ${Links}/MC_${iteration}_${topology}.root \n");
		system("ln -s ${outputdir}/MC_${iteration}_${topology}.root ${Links}/MC_${iteration}_${topology}.root");
	}
	else{
		print "not creating symbolic link";
	}
	
}
###########################################farm###################################################################

 elsif ($Computer eq "farm"){
	print "do hadd for a range of try values? type 'yes' or 'no' \n ";
	print "if 'yes' than this will hadd the files into 1 file by iteration number \n ";
	print "if 'no': this will hadd the orginized files into 1 file by iteration & try number  \n ";
	print " the 'no' option hadds for a single try number \n";
	chomp ($final = <>);
	if ($final eq "no"){
	
	
		print "what topology? example: 2kppim,gamp,2kppim-gsim \n";
		chomp ($topology = <>);
		print "using $topology topology \n";
		print "what iteration number is assocated with theese files example: i1t0,i2t4,i3t8 etc \n";
		chomp ($iteration = <>);
		print "using iteration $iteration \n";


		# Specifys the in and out directorys
		$inputdir = "/w/hallb/clasg12/jbono/sim/DATA";
		$outputdir = "/w/hallb/clasg12/jbono/sim/DATA/hadded";
		print "inputdir is: $inputdir \n";
		print "outputdir is: $outputdir \n";


		#------------hadd------------	
		for ($i = 0; $i <= 9; $i++) { #the $i is in the file name that specifies energy like 3.${i}55 GeV 
			print "hadding \n";
			my @files = glob("${inputdir}/${iteration}/${topology}/MC*.${i}*.root");
			system("hadd -f ${outputdir}/MC_${iteration}_${topology}.root @files");
			print " \n ";
		}
	
	}
	
	elsif ($final eq "yes"){
		
		print "what topology? example: 2kppim,gamp,2kppim-gsim \n";
		chomp ($topology = <>);
		print "using $topology topology \n";
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
		
		#------------hadd------------	
		for ($i = 0; $i <= 9; $i++) {
			for ($try = $trylow; $try <= $tryhigh; $try++){  #the $i is in the file name that specifies energy like 3.${i}55 GeV 
				print "hadding all MC*.${i}*${iteration}t${try}*.root files \n";
				my @files = glob("${inputdir}/${iteration}t${try}/${topology}/MC*_*.${i}*_*${iteration}t${try}*.root");
				system("hadd -f ${outputdir}/MC_${iteration}t${try}_${topology}_${i}.root @files");
				
				#system("hadd -f ${outputdir}/MC_${iteration}t${try}_${topology}.root @files");
				#system("hadd -f ${outputdir}/MC_${iteration}t${trylow}_t${tryhigh}_${topology}.root @files");
				print " \n ";
			}
		}
		system ("hadd -f ${outputdir}/MC_${iteration}t${trylow}_t${tryhigh}_${topology}.root  ${outputdir}/MC_${iteration}t*_${topology}_*.root");
		system ("rm ${outputdir}/MC_${iteration}t*_${topology}_*.root");
		
		
	
	}
}
#############################################neither farm or local#########################################################
else {
	print "Computer $Computer not recognized. Exiting \n";
}

