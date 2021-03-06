#!/apps/bin/perl -w
use diagnostics;
use warnings;

#initiize some of the variables
$mass=1.94;  #default mass of the hyperon
$width=0.22;  #default width of the hyperon
$lowerBeam=2.8; #default beam range (low)
$upperBeam=5.5; #default beam range (high)
$step=0.010;  #default step size
$M=10000;    #default number of events to generate      
$proceed=1;
$sys=1;
$jobversion=v0000000;
$dir = "/w/hallb/clasg12/jbono/sim/full";  #default bas directory
$newdir = "CREATED";
$inputfile = "genr8input-template";      #default genr8 template
$bosdir = "initalized_value";           #nonsence default path for files
$polarizer = "PolarizeGampFile2";       #the name of the 'analyzer' that polarizes flat gamp files: this probably won't change.
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

# # create the new directory if it does not exist
# if(!-e "$dir/$newdir") {
#     	system("mkdir $dir/$newdir");
#  	}



#Set up bins for hyperon mass and width.
# Get the parameters from FundamentalSpectra.C (based on 6 sub ebins)
@ELOW = (); 
#create 6 sub bins
push(@ELOW,2.800);
push(@ELOW,3.250);
push(@ELOW,3.700);
push(@ELOW,4.150);
push(@ELOW,4.600);
push(@ELOW,5.050);
for  ($i = 0; $i <= 5; $i++ )
{
#	print "i=$i:  $ELOW[$i] \n";
}
@Mass = ();
@MassB = ();
@MassC = ();
@Width = ();
@WidthB = ();#light double hyperon in 6th bin
@WidthC = ();#heavy double hyperon in 6th bin

#2.3 is to give fwhm from the fitted gaus widths, the subracted numbers were done by eye since,
#for some reason the fatter width increases the value of the mean for some bins. breight-wiggner must be an,
#asymetric function or somthing
push(@Mass,1.925);
push(@Width,0.053*2.3); 
push(@Mass,2.001);
push(@Width,0.081*2.3);
push(@Mass,2.053);
push(@Width,0.110*2.3);
push(@Mass,2.114);
push(@Width,0.141*2.3);
push(@Mass,2.145 - 0.04); #had to fix by eye
push(@Width,0.166*2.3);
push(@MassB,2.069 - 0.04); #had to fix by eye
push(@WidthB,0.111*2.3);
push(@MassC,2.335);
push(@WidthC,0.115*2.3);


#setup for incrementing
$L=$lowerBeam;
$i=0;
$U=0.0;

#begin the loop over all 27 energy bins
while( (${U} < ${upperBeam}) && (${proceed}) )
{
	#set current beam bins
	$U=$lowerBeam + ($i + 1)*${step};
	$L=$lowerBeam + ($i)*${step};
 	$ebin="$L".'_'."$U";
 	$emean=($L+$U)/2.0;

	#set the tslope	
	#Got tslope parameters from nf01 (based on 8 sub ebins)
	if($emean >= 2.8 && $emean <= 3.1375){$tslope=1.78153;}
	elsif($emean >= 3.1375 && $emean <= 3.475){$tslope=1.43802;}
	elsif($emean >= 3.475 && $emean <= 3.8125){$tslope=1.29218;}
	elsif($emean >= 3.8125 && $emean <= 4.15){$tslope=1.16666;}
	elsif($emean >= 4.15 && $emean <= 4.4875){$tslope=1.23255;}
	elsif($emean >= 4.4875 && $emean <= 4.825){$tslope=1.48449;}
	elsif($emean >= 4.825 && $emean <= 5.1625){$tslope=1.45055;}
	elsif($emean >= 5.1625 && $emean <= 5.5){$tslope=1.41051;}		
	else { print "beam $emean ouside of proper range: Exiting $!\n"; exit;}
	

	#set the hyperon mass and width
	if ($emean >= $ELOW[0] &&  $emean < $ELOW[1])
	{
		$mass = $Mass[0];
		$width = $Width[0];
		# push(@mass,$Mass[0]);
		# push(@width,$Width[0]);
	}
	if ($emean >= $ELOW[1] &&  $emean < $ELOW[2])
	{
		$mass = $Mass[1];
		$width = $Width[1];
		# push(@mass,$Mass[1]);
		# push(@width,$Width[1]);
	}
	if ($emean >= $ELOW[2] &&  $emean < $ELOW[3])
	{
		$mass = $Mass[2];
		$width = $Width[2];
		# push(@mass,$Mass[2]);
		# push(@width,$Width[2]);
	}
	if ($emean >= $ELOW[3] &&  $emean < $ELOW[4])
	{
		$mass = $Mass[3];
		$width = $Width[3];
		# push(@mass,$Mass[3]);
		# push(@width,$Width[3]);
	}
	if ($emean >= $ELOW[4] &&  $emean < $ELOW[5])
	{
		$mass = $Mass[4];
		$width = $Width[4];
		# push(@mass,$Mass[4]);
		# push(@width,$Width[4]);
	}
	if ($emean >= $ELOW[5])
	{
		if (0 == $i % 2) #assign even ebins to light hyperon and odd ebins to heavy hyperon 
		{
			#print "The number $i is even\n";
			$mass = $MassB[0];
			$width = $WidthB[0];
			# push(@mass,$MassB[0]);
			# push(@width,$WidthB[0]);
		} 
		else 
		{
		    #print "The number $i is odd\n";
			$mass = $MassC[0];
			$width = $WidthC[0];
			# push(@mass,$MassC[0]);
			# push(@width,$WidthC[0]);
		}	
	
	}	
	#display parameters
	print " i = $i  ::  step = $step  ::  L = $L  ::  emean = $emean  ::  U = $U  :: tslope = $tslope :: mass =  $mass ::  width = $width   $! \n";
	

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

	#increment the beam bin
	$i = $i +1;
	
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

