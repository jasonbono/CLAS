#!/apps/bin/perl -w

#author: jason bono	
#date: july 10 2012
#

#initiaize some variables
$dir = 'unknownDir';
$maxfiles = 7000;
$topology = 'unknownTop';
$version = 'unknownVersion';

#print "$topology \n";

#exit the program if no arguments are passed in
if(!@ARGV)
{
  &printusage("junk"); # dont know what the "junk" argument means
  exit
}

$submit = 0;

# assign the input arguments to variables
for (@ARGV) 
{

	if(/^-T(.+)/)	{ $topology = $1;}
	if(/^-v(.+)/)	{ $version = $1;}
	if(/^-M(.+)/)	{ $maxfiles = $1;} 
	if (/^-d(.+)/)		{$dir = $1;}	
	if(/^-h/)		{&printusage("particles?");}
	if(/^-S(.+)/)	{ $submit = 1;} 
	# if(/^-t(.+)/)    { $tslope = $1; print "tslope = $tslope\n";} 
	# if (/^-d/)     { $sys = 0;}
}


print "creating scripts for the $topology topology \n";

# define topology2 because of naming discrepancy between kpkppim and 2kppim
if($topology eq 'kpkppim') {$topology = '2kppim';} #made it fool proof
if($topology eq '2kppim') {$topology2 = 'kpkppim';}
else{$topology2 = $topology;}

# create the new directory if it does not exist
#$dir = "/Users/Bono/clas/analyser/runana";
$newdir = "CREATED/${topology}-${version}";
$fulldir = "${dir}/${newdir}";
if(!-e "$dir/CREATED") {system("mkdir $dir/CREATED");}
if(!-e "$dir/$newdir") {system("mkdir $dir/$newdir");}

# - - - - - - - - - - - - - - - - - - - - - - open templates and new scripts - - - - - - - - - - - - - - - - - -

#open the analyze template and make the new scripts in the newdir
open(ANATEMPLATE, "$dir/analyzetemplate.sh")|| die "Can't open analyzetemplate.sh $!\n"; 
open(ANASCRIPT, ">$dir/$newdir/analyzescript_${topology}_${version}.sh") || die "Can't open analyzescript_${topology}-${version}.sh $!\n";

open(JOBTEMPLATE, "$dir/jobtemplate.sh")|| die "Can't open job-template.sh $!\n"; 
open(JOBSCRIPT, ">$dir/$newdir/jobscript_${topology}_${version}.sh") || die "Can't open job-script_${topology}-${version}.sh $!\n";

#make the scripts from the templates
while (<ANATEMPLATE>) 
{
	s#TTT#$topology#;
	s#ttt#$topology2#;
	s#MMM#$maxfiles#;    
	s#VVV#$version#;  
	s#DDD#$fulldir#;
	print ANASCRIPT;
}

while (<JOBTEMPLATE>) 
{
	s#TTT#$topology#;
	s#ttt#$topology2#;
	s#MMM#$maxfiles#;    
	s#VVV#$version#;  
	s#DDD#$fulldir#;
	print JOBSCRIPT;	
}

#close all of the files
close (ANASCRIPT);
close (ANATEMPLATE);
close (JOBSCRIPT);
close (JOBTEMPLATE);

system ("chmod u+x $dir/$newdir/jobscript_${topology}_${version}.sh");
system ("chmod u+x $dir/$newdir/analyzescript_${topology}_${version}.sh");


# - - - - - - - - - - - - - - - - - - - - - - - -jsub - - - - - - - - - - - - - - - - - - - - - - - 

if($submit)
{
	 system ("jsub $dir/$newdir/jobscript_${topology}_${version}.sh");
}
# - - - - - - - - - - - - - - - - - - - - - - - -print usage - - - - - - - - - - - - - - - - - - - - - - - 
sub printusage()
{
    print "    Creating mc jobs for $_[0] from ppgen to filter: 
 	[-options]:       
	-T<string>         	topology used (2kppim, kpkp, kppippim)
    -v<string>			analyzer version (ie v0)
    -M#         		number of bos files to skim (integer) 
	-h         			usage
	\n "   

}







