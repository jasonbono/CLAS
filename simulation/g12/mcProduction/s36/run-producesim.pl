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


#from results of i10t4, for i10t5
@m = ();
push(@m,17118);
push(@m,24345);
push(@m,23883);
push(@m,31653);
push(@m,39513);
push(@m,49823);
push(@m,48175);
push(@m,34593);
push(@m,100000);
push(@m,55171);
push(@m,53417);
push(@m,72743);
push(@m,45824);
push(@m,47965);
push(@m,37000);
push(@m,34242);
push(@m,30914);
push(@m,40918);
push(@m,37921);
push(@m,29890);
push(@m,37160);
push(@m,34061);
push(@m,33448);
push(@m,29217);
push(@m,20518);
push(@m,28378);
push(@m,14684);
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
$v="i10t5";
$K="NORM";
$thisdir="/u/home/jbono/simulation/s36";
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

