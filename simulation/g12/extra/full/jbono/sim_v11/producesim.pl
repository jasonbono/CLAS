#!/apps/bin/perl -w
use diagnostics;
use warnings;

#initiize some of the variables
$mass=1.94;
$width=0.22;
$upperBeam=2.0 ;
$lowerBeam=1.5;
$step=0.10;
#$tslope=3;
$M=100;
$proceed=1;
$sys=1;
$jobversion=v0000000;

#specify the directorys
$dir = "/w/hallb/clasg12/jbono/sim/full";
$newdir = "CREATED";
$inputfile = "genr8input-template";
$bosdir = "initalized_value";

if(!@ARGV)
{
	&printusage("junk");
}

for (@ARGV) 
{
	if(/^-m(.+)/)	{ $mass = $1;}
	if(/^-W(.+)/)	{ $width = $1;} 
	if(/^-B(.+)/)	{ $upperBeam = $1;}
	if(/^-b(.+)/)	{ $lowerBeam = $1;} 
	if(/^-s(.+)/)	{ $step = $1;} 
#	if(/^-t(.+)/)	{ $tslope = $1; print "tslope = $tslope\n";} 
	if(/^-M(.+)/)	{ $M = $1;}
	if(/^-v(.+)/)	{ $jobversion = $1;}
	if(/^-w(.+)/)	{ $dir = $1;}
	if(/^-I(.+)/)   { $inputfile = $1;}
	if(/^-o(.+)/)	{ $bosdir = $1;}
	if(/^-a(.+)/)	{ $ana = $1;}
	if(/^-A(.+)/)	{ $anadir = $1;}	
	if(/^-d/)    	{ $sys = 0;}
	if(/^-h/)     	{ $proceed=0; &printusage("particles?");}  
}

print "the analyzer being used is $ana";
$L=$lowerBeam;
$i=0;
#from leis old code @ts=(5.4, 3.9, 2.3, 1.8, 1.7, 1.6, 1.6, 1.5, 1.6, 1.9);
#from leis old code @ts=(3.08, 2.3, 2.15,2.35,2.34,1.68,1.45,1.90,2.3,2.3,2.45);
@ts=(5.4, 3.9, 2.3, 1.8, 1.7, 1.6, 1.6, 1.5, 1.6, 1.9);
print "L = $L : upperBeam = $upperBeam : proceed = $proceed\n";
while( (${L} <= ${upperBeam}) && (${proceed}) )  #iterating in L
{
	$U=$L+$step;  #L is the lower beam limit for the one iteration, U  is one "step" up (0.1)
	$tslope=$ts[$i];
	#$tslope=2.0;
	$i++;


	## create the new directory if it does not exist
	if(!-e "$dir/$newdir") 
	{
    	system("mkdir $dir/$newdir");
 	}

 	#increment
 	$ebin="$L".'_'."$U";
 	$emean=($L+$U)/2;


#-------------------------------------------open and change GENERATE template ----------------------------------------------------------------


 	open(GENERATETEMPLATE, "$dir/generate-template.sh")|| die "Can't open generate template $!\n"; 
 	open(GENERATESCRIPT, ">$dir/$newdir/generatescript_${ebin}.${jobversion}") || die "Can't open farmscript_${ebin} $!\n";
 
 	while (<GENERATETEMPLATE>) 
	{
   		s#XXX#$ebin#;  # substitute XXX by the ebin  (from -B,-b,-s)
   		s#SSS#$step#;  # substitute SSS by the step size (-s)
   		s#DDD#${dir}/${newdir}#;  # substitute DDD by the directory (-w)
   		s#NNN#$M#;    # M -> NNN -> amount of events accepted by genr8 (-M)
		s#VVV#$jobversion#;
		s#ANA#$ana#g;
   		print GENERATESCRIPT;   # write out modified line
 	}
 	#end of creating the scirpt for $ebindir;
 	close (GENERATETEMPLATE);
	close (GENERATESCRIPT);
 	system ("chmod u+x $dir/$newdir/generatescript_${ebin}.${jobversion}"); 


#----------------------------------------------open and change GENR8INPUT template--------------------------------------------------------


 	#open the GENR8 INPUT FILE (as initialized at the top or by -I).  also make the new input file in the newdir
 	open(GENR8INPUTTEMPLATE, "$dir/$inputfile")|| die " Can't open genr8input-template!! $!\n"; 
 	open(GENR8INPUTSCRIPT, ">$dir/$newdir/genr8input_${ebin}.${jobversion}") || die "Can't open genr8input_$ebin.${jobversion}$!\n";

 	while (<GENR8INPUTTEMPLATE>)
 	{
   		s#BBB#$emean#;  #  BBB <- $emean <- incremented from min and max (which are iniaized in this code) 
   		s#HHH#$mass#;   #  HHH <- $mass <- initized in this code
   		s#WWW#$width#;  #  WWW <- $width <- initized in this code 
   		s#TTT#$tslope#; #  TTT <- $tslope <- initized to 2.0, eventualy will be taken from array which is initized in each iteration
   		print GENR8INPUTSCRIPT;    #   write out modified line
 	}
 
 	close (GENR8INPUTTEMPLATE);
	close (GENR8INPUTSCRIPT);


#-----------------------------------------open and change JOB template-----------------------------------------------


 	#create a farm job for that jobscipt
 	open (JOBTEMPLATE, "$dir/job-template.sh") || die "Can't open farmjob_template $!\n";
 	open (JOBSCRIPT, "> $dir/$newdir/jobscript_${ebin}.${jobversion}") || die "Can't open farmjob.${ebin}$!`\n";

 	while (<JOBTEMPLATE>) 
	{
   		s#XXX#$ebin#;
   		s#DDD#${dir}/${newdir}#;
   		s#VVV#$jobversion#;
		s#OOO#$bosdir#;
		s#ADD#$anadir#;
		s#ANA#$ana#;
   		print JOBSCRIPT;
 	}
 	close (JOBTEMPLATE);
 	close (JOBSCRIPT);


#--------------------------------------NOW MOVE THE ADDITIONAL NEEDED FILES TO THE "CREATED" DIRECTORY-------------------
 
	if($sys) 	
	{
		system ("cp  ffread.g12  $dir/$newdir/ffread.g12 ");
		#system ("cp  ffread.g12  $dir/$newdir/ffread.g12 ");
	}   #when run localy the jsub command will cause an error
 
#-----------------------------------DO JSUB, INCREMENT L, AND TERMINATE THE LOOP-----------------------------------------


	if($sys) {system ("jsub $dir/$newdir/jobscript_${ebin}.${jobversion}");}	#when run localy the jsub command will report error
	$L=$U;
}


#============================================================================================================================


sub printusage() 
{
	print "  Creating mc jobs for $_[0] from ppgen to filter: 
	[-options]:       
	-m#         	hyperon mass (GeV)
   	-W#         	width of hyperon (GeV) 
	-B#         	upper limit of photon energy (GeV)
   	-b#         	lower limit of photon energy (GeV) 
  	-s#         	photon energy bin size (GeV)
    -t#         	tslope(default 3)
   	-M#         	maximum # of events per mass bin
   	-v<string>      jobversion ( to distinguish ifarmjobs)
	-w<string>	    full path of work dir
	-R<string>	    sub dir containing the script templates
	-I<string>	    genr8 input file template (filename)
#   -o<string>	    full path of sylo destination for output
    -d	    		for debugging purpose, no submitting of jobs
    -h          	usage
	\n"   
}

