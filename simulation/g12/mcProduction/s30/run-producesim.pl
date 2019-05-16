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
#for i9t6
@m = ();
push(@m,18279);
push(@m,25470);
push(@m,25623);
push(@m,31366);
push(@m,32963);
push(@m,47491);
push(@m,44033);
push(@m,38372);
push(@m,99999);
push(@m,73989);
push(@m,57603);
push(@m,83345);
push(@m,45710);
push(@m,46387);
push(@m,38110);
push(@m,50100);
push(@m,46368);
push(@m,49641);
push(@m,36674);
push(@m,31639);
push(@m,38994);
push(@m,35656);
push(@m,31696);
push(@m,30685);
push(@m,24357);
push(@m,33032);
push(@m,16840);
for  ($i = 0; $i <= 26; $i++  )
{
	print "$m[$i] \n";
}

#$s=0.002; #for real run
$s=0.05;#for test

$a="2kppim-v06";
$b="kpkp-v03";
$g="ga04";
$v="i10t0";
$K="NORM";
$thisdir="/u/home/jbono/simulation/s30";
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

