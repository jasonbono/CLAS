#Author: Jason Bono
#Date:	  Nov 12 2012
#Notes:  adopted from run-producesim.sh.


#!/apps/bin/perl -w
use diagnostics;
use warnings;


#create 27 energy bins
$eLow=2.8;
$eStep=0.1;
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

#beam matching
#for test
@m = ();
push(@m,2374);
push(@m,3715);
push(@m,3751);
push(@m,4282);
push(@m,4538);
push(@m,7056);
push(@m,6807);
push(@m,5787);
push(@m,10000);
push(@m,9434);
push(@m,8524);
push(@m,9593);
push(@m,7677);
push(@m,7986);
push(@m,6519);
push(@m,6251);
push(@m,5903);
push(@m,7684);
push(@m,6534);
push(@m,5730);
push(@m,7211);
push(@m,6395);
push(@m,5862);
push(@m,5849);
push(@m,4403);
push(@m,9771);
push(@m,3193);

#for full run
# @m = ();
# push(@m,23744);
# push(@m,37158);
# push(@m,37519);
# push(@m,42827);
# push(@m,45389);
# push(@m,70563);
# push(@m,68078);
# push(@m,57872);
# push(@m,100000);
# push(@m,94345);
# push(@m,85244);
# push(@m,95932);
# push(@m,76777);
# push(@m,79866);
# push(@m,65190);
# push(@m,62510);
# push(@m,59037);
# push(@m,76843);
# push(@m,65349);
# push(@m,57306);
# push(@m,72113);
# push(@m,63951);
# push(@m,58625);
# push(@m,58499);
# push(@m,44039);
# push(@m,97716);
# push(@m,31931);
# for  ($i = 0; $i <= 26; $i++  )
# {
# 	print "$m[$i] \n";
# }




#declare other options

#for real run
#$s=0.002;
#for test
$s=0.05;

$a="2kppim-v06";
$b="kpkp-v03";
$g="ga04";
$v="i9t1";
$K="NORM";
$thisdir="/u/home/jbono/simulation/s24";
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


#################the way to specify the hyperon mass from this script#################
######## its better to do this from producesim.pl instead for finer binning############
# 
# #the hyperon mass and widths
# @ELOW = (); #create 6 sub bins
# #create 6 sub bins
# push(@ELOW,2.800);
# push(@ELOW,3.250);
# push(@ELOW,3.700);
# push(@ELOW,4.150);
# push(@ELOW,4.600);
# push(@ELOW,5.050);
# for  ($i = 0; $i <= 5; $i++ )
# {
# 	#print "i=$i:  $ELOW[$i] \n";
# }
# @Mass = ();
# @MassB = ();
# @MassC = ();
# @Width = ();
# @WidthB = ();
# @WidthC = ();
# push(@Mass,1.925);
# push(@Width,0.053);
# push(@Mass,2.001);
# push(@Width,0.081);
# push(@Mass,2.053);
# push(@Width,0.110);
# push(@Mass,2.114);
# push(@Width,0.141);
# push(@Mass,2.145);
# push(@Width,0.166);
# push(@MassB,2.069);
# push(@WidthB,0.111);
# push(@MassC,2.335);
# push(@WidthC,0.115);
# 
# @mass = ();
# @width = ();
#  for  ($i = 0; $i <= 26; $i++  )
#  {
# 	if ($elow[$i] >= $ELOW[0] &&  $elow[$i] < $ELOW[1])
# 	{
# 		push(@mass,$Mass[0]);
# 		push(@width,$Width[0]);
# 	}
# 	if ($elow[$i] >= $ELOW[1] &&  $elow[$i] < $ELOW[2])
# 	{
# 		push(@mass,$Mass[1]);
# 		push(@width,$Width[1]);
# 	}
# 	if ($elow[$i] >= $ELOW[2] &&  $elow[$i] < $ELOW[3])
# 	{
# 		push(@mass,$Mass[2]);
# 		push(@width,$Width[2]);
# 	}
# 	if ($elow[$i] >= $ELOW[3] &&  $elow[$i] < $ELOW[4])
# 	{
# 		push(@mass,$Mass[3]);
# 		push(@width,$Width[3]);
# 	}
# 	if ($elow[$i] >= $ELOW[4] &&  $elow[$i] < $ELOW[5])
# 	{
# 		push(@mass,$Mass[4]);
# 		push(@width,$Width[4]);
# 	}
# 	if ($elow[$i] >= $ELOW[5])
# 	{
# 		if (0 == $i % 2) #assign even ebins to light hyperon and odd ebins to heavy hyperon 
# 		{
# 			#print "The number $i is even\n";
# 			push(@mass,$MassB[0]);
# 			push(@width,$WidthB[0]);
# 		} 
# 		else 
# 		{
# 		    #print "The number $i is odd\n";
# 			push(@mass,$MassC[0]);
# 			push(@width,$WidthC[0]);
# 		}	
# 		
# 	}
# }
# for  ($i = 0; $i <= 26; $i++  )
# {
# 	print "mass =  $mass[$i],  width = $width[$i]  \n";
# }
