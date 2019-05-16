#!/apps/bin/perl -w

# Date: April 26 2012
# Author: Jason Bono
# Purpose: this will take "my_first_template" and create "my_first_file"


#------------------------initialize variables------------------------------
$mass=1000.0;
$width=1000.0;




$inputd = "/Users/Bono/clas/TESTS/perl/templates";
$inputf = "my_first_template";
$outputd = "/Users/Bono/clas/TESTS/perl/created_files";
$outputf = "my_first_file";



for (@ARGV) 
{
	if(/^-m(.+)/)     { $mass = $1;}
	if(/^-W(.+)/)     { $width = $1;}
	
	print "IN THE @ ARGV THING: mass = $mass  width = $width \n";
}





print "test: mass = $mass \n";
print "test: width = $width \n";



#-----------------------------write the new files from the template-------------------------
open (TEMPLATE, "$inputd/$inputf") || die "Can't open template! \n";
open (NEWFILE, "> $outputd/$outputf") || die "Can't open new file! \n";
while (<TEMPLATE>)
{
	s#template#file#;
	s#HHH#$mass#;
	s#WWW#$width#;
	print NEWFILE;
}
close (TEMPLATE);
close (NEWFILE);
#-------------------------------------------------------------------------------------------