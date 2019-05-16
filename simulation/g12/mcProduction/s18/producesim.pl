#!/apps/bin/perl -w
use diagnostics;
use warnings;

#initiize some of the variables
$mass=1.94;  #default mass of the hyperon
$width=0.22;  #default width of the hyperon
$lowerBeam=2.8; #default beam range (low)
$upperBeam=5.5; #default beam range (high)
$step=0.10;  #default step size
$M=10000;    #default number of events to generate      
$proceed=1;
$sys=1;
$jobversion=v0000000;
$dir = "/w/hallb/clasg12/jbono/sim/full";  #default bas directory
$newdir = "CREATED";
$inputfile = "genr8input-template";      #default genr8 template
$bosdir = "initalized_value";           #nonsence default path for files
$polarizer = "PolarizeGampFile";       #the name of the 'analyzer' that polarizes flat gamp files: this probably won't change.
$reducer = "ReduceRootFile";			#the name of the root file reducer: this probably won't change.

if(!@ARGV)
{
	&printusage("junk");
}
for (@ARGV) 
{
	if(/^-m(.+)/)	{ $mass = $1;}
	if(/^-W(.+)/)	{ $width = $1;} 
	if(/^-e(.+)/)	{ $lowerBeam = $1;} 
	if(/^-E(.+)/)	{ $upperBeam = $1;}
	if(/^-s(.+)/)	{ $step = $1;} 
	if(/^-M(.+)/)	{ $M = $1;}
	if(/^-v(.+)/)	{ $jobversion = $1;}
	if(/^-w(.+)/)	{ $dir = $1;}
	if(/^-I(.+)/)   { $inputfile = $1;}
	if(/^-o(.+)/)	{ $bosdir = $1;}
	if(/^-a(.+)/)	{ $ana = $1;}
	if(/^-b(.+)/)	{ $bna = $1;}
	if(/^-g(.+)/)	{ $gampana = $1;}
	if(/^-A(.+)/)	{ $anadir = $1;}
	if(/^-K(.+)/)   { $kind = $1;}	
	if(/^-d/)    	{ $sys = 0;}
	if(/^-h/)     	{ $proceed=0; &printusage("particles?");}	
}



print "Analyzer versions $ana and $bna \n";

#setup for incrementing
$L=$lowerBeam;
$i=0;
$U=0.0;

while( (${U} < ${upperBeam}) && (${proceed}) )
{
	#increment
	$U=$lowerBeam + ($i + 1)*${step};
	$L=$lowerBeam + ($i)*${step};
 	$ebin="$L".'_'."$U";
 	$emean=($L+$U)/2.0;
	$i = $i +1;
	
	#fill the tslope with the approprite values
	if($emean >= 2.8 && $emean <= 3.4){$tslope=2.80942;} #this first step is a double step
	elsif($emean >= 3.4 && $emean <= 3.75){$tslope=2.44894;}
	elsif($emean >= 3.75 && $emean <= 4.1){$tslope=2.50891;}
	elsif($emean >= 4.1 && $emean <= 4.45){$tslope=2.45089;}
	elsif($emean >= 4.45 && $emean <= 4.8){$tslope=2.5028;}
	elsif($emean >= 4.8 && $emean <= 5.15){$tslope=2.85991;}
	elsif($emean >= 5.15 && $emean <= 5.5){$tslope=2.48431;}		
	else { print "beam $emean ouside of proper range: Exiting $!\n"; exit;}
	
	#display
	print " i = $i  ::  step = $step  ::  L = $L  ::  emean = $emean  ::  U = $U  :: tslope = $tslope   $! \n";
	
	# create the new directory if it does not exist
	if(!-e "$dir/$newdir") {
    	system("mkdir $dir/$newdir");
 	}

	#-------------------------------------------open and change GENERATE template ----------------------------------------------------------------

 	open(GENERATETEMPLATE, "$dir/generate-template$kind.sh")|| die "Can't open generate template $!\n"; 
 	open(GENERATESCRIPT, ">$dir/$newdir/generatescript_${ebin}.${jobversion}") || die "Can't open farmscript_${ebin} $!\n";
 
 	while (<GENERATETEMPLATE>) 
	{
   		s#XXX#$ebin#;  # substitute XXX by the ebin  ( comes from from -B,-b,-s)
   		s#SSS#$step#;  # substitute SSS by the step size (-s)
   		s#DDD#${dir}/${newdir}#;  # substitute DDD by the directory (-w)
   		s#NNN#$M#;    # M -> NNN -> amount of events accepted by genr8 (-M)
		s#VVV#$jobversion#;
		s#PLR#$polarizer#g;
		s#RED#$reducer#g;
		s#ANA#$ana#g; #g means global!
		s#BNB#$bna#g; #g means global!
		s#GGG#$gampana#g; #g means global!
		s#LLL#$L#;  # lower lim of ebin
		s#UUU#$U#;  # uper lim of ebin
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
 	open (JOBTEMPLATE, "$dir/job-template$kind.sh") || die "Can't open farmjob_template $!\n";
 	open (JOBSCRIPT, "> $dir/$newdir/jobscript_${ebin}.${jobversion}") || die "Can't open farmjob.${ebin}$!`\n";

 	while (<JOBTEMPLATE>) 
	{
   		s#XXX#$ebin#;
   		s#DDD#${dir}/${newdir}#;
   		s#VVV#$jobversion#;
		s#OOO#$bosdir#;
		s#ADD#$anadir#;
		s#RED#$reducer#g;
		s#PLR#$polarizer#g;
		s#ANA#$ana#g; 
		s#BNB#$bna#g;
		s#GGG#$gampana#g;
   		print JOBSCRIPT;
 	}
 	close (JOBTEMPLATE);
 	close (JOBSCRIPT);


	#~~~~~~~~~~~~~~~~~~~~~~~~only for running at jlab~~~~~~~~~~~~~~~~~~~~~~~~
	if($sys) 	
	{
		system ("cp  ffread.g12  $dir/$newdir/ffread.g12 ");
		system ("jsub $dir/$newdir/jobscript_${ebin}.${jobversion}");
	}   
	
}







#============================================================================================================================
#=========================================================USAGE==============================================================
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
	-K				for choosing what kind of MC data to output (ALL,NORM,GPP)
    -h          	usage
	\n"   
}

