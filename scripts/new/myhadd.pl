#!/apps/bin/perl -w
use diagnostics;
use warnings;


# Author: Jason Bono
# Date: October 18 2012
# Purpose: to take the g12 bos.root files and hadd them into only 10 seperate files with the option to reduce this to a single file and make a symbolic link in LINKS

# Usage:         perl myhadd.pl

#          This is an Interactive script
#           Answer the questions asked
#             Questions regarding (Topology, Version, Remove bad files, Second hadd, Cleanup)
 


#initalize the removal switch to off
$remove = 0;

#set the links directory
$Links = "/Users/Bono/clas/rootfiles/LINKS";

#for (@ARGV) 
#{
#	if(/^-t(.+)/)	{ $topology = $1;}
#	if(/^-v(.+)/)	{ $version = $1;}
#	if(/^-r/)    	{ $remove = 1;}  #only use for removal!
#}

print "what topology? example: 2kppim \n";
chomp ($topology = <>);
print "using $topology topology \n";
print "what analyzer version was used to create the root files? example: v01 \n";
chomp ($version = <>);
print "using version $version \n";
print "shall we remove those pesky files that came from bad bos files? type: 1 for yes,  0 for no \n" ;
chomp ($remove = <>);

# Specifys the directorys
$inputdir = "/Users/Bono/clas/rootfiles/g12/${topology}/${version}";
$outputdir = "/Users/Bono/clas/rootfiles/g12/${topology}";
print "inputdir is: $inputdir \n";
print "outputdir is: $outputdir \n";


#remove the files that were nameed badly
if(${remove}){
	
	my @badfiles = glob("${inputdir}/${topology}-${version}*X.root"); 
	print "removing the bad files that look like ${topology}-${version}*X.root \n";
	system("sleep 2");
	print " going to do: rm @badfiles in a few seconds";
	system("sleep 2");
	system("rm @badfiles");
	
}
else{
	print "remove = $remove and this means false \n";
}


#-------------------------------first hadd-------------------------------
for ($i = 0; $i <= 9; $i++) {
	print "hadding ${topology}-${version}*A${i}X.bos.root \n";
	my @files = glob("${inputdir}/${topology}-${version}*A${i}X.bos.root");
	system("hadd -f ${outputdir}/${topology}-${version}-${i}.root @files");
	print " \n ";
}

#---------------------------------------second hadd--------------------------------------------------------
print "do you want to do a second hadd? type: yes or no \n";
chomp ($choice = <>);
if ($choice eq "yes"){
	print " ok yes, doing the second hadd since the answer was $choice \n";	
	my @files2 = glob("${outputdir}/${topology}-${version}-*.root");
	system("hadd -f ${outputdir}/hadded/${topology}-${version}.root @files2");
	
	#--------make link-------
	print "do you want to make the symbolic link in $Links type: yes or no \n";
	chomp ($choice = <>);
	if ($choice eq "yes"){
		print "creating a symbolic link: \n";
		print ("ln -s ${outputdir}/hadded/${topology}-${version}.root ${Links}/${topology}-${version}.root \n");
		system("ln -s ${outputdir}/hadded/${topology}-${version}.root ${Links}/${topology}-${version}.root");
    }
	else{
		print "not creating symbolic link";
	}
	
	#--------clean up---------
	print "do you want to clean up the 10 extra files? type: yes or no \n";
	chomp ($choice2 = <>);
	if ($choice2 eq "yes"){
		print " ok yes, cleaning up since the answer was $choice2 \n";	
		system("rm ${outputdir}/${topology}-${version}-*.root");
	} elsif ($choice2 eq "no"){
		print "ok no, the answer was $choice2 \n";
	} else {
		print "your being unclear with your answer of $choice2 \n ";
	}
	
	
} elsif ($choice eq "no"){
	print "ok no, the answer was $choice \n";
} else {
	print "your being unclear with your answer of $choice \n ";
}





