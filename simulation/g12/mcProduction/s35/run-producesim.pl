#Author: Jason Bono
#Date:	  Nov 12 2012
#Notes:  adopted from run-producesim.sh.

#!/apps/bin/perl -w
use diagnostics;
use warnings;

#create 27 energy bins
$eLow=2.8;
$eStep=0.1; #dont change this
@elow = ();
@ehigh = ();
for  ($i = 0; $i <= 26; $i++  )
{
	$templow = $eLow + $eStep * $i;
	$temphigh = $eLow + $eStep * ($i+1);
	push(@elow,$templow);
	push(@ehigh,$temphigh);
	#print "elow = $elow[$i],  ehigh = $ehigh[$i] \n";
}


#from i10t3
@m = ();
push(@m,17745);
push(@m,21075);
push(@m,22232);
push(@m,26894);
push(@m,29619);
push(@m,45570);
push(@m,44129);
push(@m,37878);
push(@m,100000);
push(@m,67051);
push(@m,54405);
push(@m,79362);
push(@m,44541);
push(@m,46288);
push(@m,39553);
push(@m,37259);
push(@m,34078);
push(@m,47887);
push(@m,41663);
push(@m,32999);
push(@m,41430);
push(@m,38878);
push(@m,32349);
push(@m,34753);
push(@m,25375);
push(@m,35707);
push(@m,17538);
for  ($i = 0; $i <= 26; $i++  )
{
	print "$m[$i] \n";
}

$s=0.001; #for real run
#$s=0.01;#for test
#$s=0.01; #for Cx Cz

$a="2kppim-v15";
$b="kpkp-v03";
$g="ga05";
$v="i10t4";
$K="NORM";
$thisdir="/u/home/jbono/simulation/s35";
$outdir="/w/hallb/clasg12/jbono/sim/DATA";
$anadir="/u/home/jbono/analyser/g12/LINKS";
#call producesim.pl
for  ($i = 0; $i <= 26; $i++  )
{
	system ("perl producesim.pl -e$elow[$i] -E$ehigh[$i] -M$m[$i] -s$s -K$K -v$v -a$a -b$b -g$g -w$thisdir -o$outdir -A$anadir");
}



#======================================================NOTES========================================================
# possible options: m W B b s t M v w I (d h)  K a 
#   m=mass W=width  -------------------------------------------------------------> give [HHH,WWW]
#   E=beammax  e=beammim  s=beam-increment  -------------------------------------> give [XXX,BBB,SSS] 
#   M=events --------------------------------------------------------------------> gives [NNN]
#   v=jobversion w=work-dir-path R=scripts-subdir I=genr8template-filename ------> give [VVV, DDD,?,?] 
#	o = bosdir which is where the generated events go
#	K = kind.  examples are ALL,NORM,GPPTST (meaning they output diffrent files)
#	b = second analyzer

# note that TTT is the tslope

# s#BBB#$emean#;  #  BBB <- $emean <- incremented from min and max (which are iniaized in this code) 
# s#HHH#$mass#;   #  HHH <- $mass <- initized in this code
# s#WWW#$width#;  #  WWW <- $width <- initized in this code 
# s#TTT#$tslope#; #  TTT <- $tslope <- initized to 2.0, eventualy will be taken from array which is initized in each iteration

# s#XXX#$ebin#;  # substitute XXX by the ebin  (from -B,-b,-s)
# s#SSS#$step#;  # substitute SSS by the step size (-s)
# s#DDD#$dir#;  # substitute DDD by the directory (-w)
# s#NNN#$M#;    # M -> NNN -> amount of events accepted by genr8 (-M)

