
#s13 Update: 
#1)	 	changed the genr8input template... the final two particles (pim2 proton) in the decay
		#chain were specified to come from the lambda decay (rather than wrongfuly the proton decaying
		#into itself)  

#2)		added flexibility for the gamp analyzer: 

#3) 	renamed the 

#Author: Jason Bono
#Date:	  Oct 16 2012
#Notes:   The runs a software package that generates mc events and output root files
#
#

#for the fix of i2t0
#perl producesim.pl -KNORM -vi2t0 -M5000 -a2kppim-v02 -bkpkp-v02 -gga04 -m1.96 -W0.01 -e3.34 -E3.35 -s0.005 -w/u/home/jbono/simulation/s15 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi2t0 -M5000 -a2kppim-v02 -bkpkp-v02 -gga04 -m1.96 -W0.01 -e3.38 -E3.39 -s0.005 -w/u/home/jbono/simulation/s15 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi2t0 -M5000 -a2kppim-v02 -bkpkp-v02 -gga04 -m1.96 -W0.01 -e3.57 -E3.58 -s0.005 -w/u/home/jbono/simulation/s15 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi2t0 -M5000 -a2kppim-v02 -bkpkp-v02 -gga04 -m1.96 -W0.01 -e3.75 -E3.76 -s0.005 -w/u/home/jbono/simulation/s15 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi2t0 -M5000 -a2kppim-v02 -bkpkp-v02 -gga04 -m1.96 -W0.01 -e4.03 -E4.04 -s0.005 -w/u/home/jbono/simulation/s15 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi2t0 -M5000 -a2kppim-v02 -bkpkp-v02 -gga04 -m1.96 -W0.01 -e4.18 -E4.19 -s0.005 -w/u/home/jbono/simulation/s15 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi2t0 -M5000 -a2kppim-v02 -bkpkp-v02 -gga04 -m1.96 -W0.01 -e5.32 -E5.33 -s0.005 -w/u/home/jbono/simulation/s15 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#the start of the first iteration (should generate 10.5 million events)
#perl producesim.pl -KNORM -vi2t0 -M50000 -a2kppim-v02 -bkpkp-v02 -gga04 -m1.96 -W0.01 -e3.3 -E5.4 -s0.01 -w/u/home/jbono/simulation/s14 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#doing it again
#perl producesim.pl -KNORM -vi1t7 -M100000 -a2kppim-v01 -bkpkp-v01 -gga03 -m1.96 -W0.01 -e3.3 -E3.5 -s0.10 -w/u/home/jbono/simulation/s13 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -KNORM -vi1t7 -M100000 -a2kppim-v01 -bkpkp-v01 -gga03 -m1.96 -W0.01 -e4.3 -E5.8 -s0.10 -w/u/home/jbono/simulation/s13 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi1t7 -M100000 -a2kppim-v01 -bkpkp-v01 -gga03 -m1.96 -W0.01 -e4.8 -E5.3 -s0.10 -w/u/home/jbono/simulation/s13 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -KNORM -vi1t8 -M100000 -a2kppim-v01 -bkpkp-v01 -gga03 -m1.96 -W0.01 -e4.9 -E5.1 -s0.10 -w/u/home/jbono/simulation/s13 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# to try and get good data
#perl producesim.pl -KNORM -vi1t5 -M100000 -a2kppim-v01 -bkpkp-v01 -gga03 -m1.96 -W0.01 -e3.6 -E4.2 -s0.10 -w/u/home/jbono/simulation/s13 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi1t5 -M100000 -a2kppim-v01 -bkpkp-v01 -gga03 -m1.96 -W0.01 -e5.2 -E5.4 -s0.10 -w/u/home/jbono/simulation/s13 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -KNORM -vi1t6 -M100000 -a2kppim-v01 -bkpkp-v01 -gga03 -m1.96 -W0.01 -e3.6 -E4.2 -s0.10 -w/u/home/jbono/simulation/s13 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi1t6 -M100000 -a2kppim-v01 -bkpkp-v01 -gga03 -m1.96 -W0.01 -e5.2 -E5.4 -s0.10 -w/u/home/jbono/simulation/s13 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS



#for normal running
#perl producesim.pl -KNORM -vi1t5 -M100000 -a2kppim-v01 -bkpkp-v01 -gga03 -m1.96 -W0.01 -e3.2 -E4.0 -s0.20 -w/u/home/jbono/simulation/s13 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi1t5 -M100000 -a2kppim-v01 -bkpkp-v01 -gga03 -m1.96 -W0.01 -e4.0 -E4.8 -s0.20 -w/u/home/jbono/simulation/s13 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi1t5 -M100000 -a2kppim-v01 -bkpkp-v01 -gga03 -m1.96 -W0.01 -e4.8 -E5.6 -s0.20 -w/u/home/jbono/simulation/s13 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS


#for test
#perl producesim.pl -KNORM -vs12test3 -M1000 -a2kppim-v01 -bkpkp-v01 -m1.96 -W0.01 -e3.2 -E3.3 -s0.20 -w/u/home/jbono/simulation/s12 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vs12test3 -M1000 -a2kppim-v01 -bkpkp-v01 -m1.96 -W0.01 -e3.34 -E3.35 -s0.01 -w/u/home/jbono/simulation/s12 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS




#local test
perl producesim.pl -d -KNORM -vi1t7 -M100000 -a2kppim-v01 -bkpkp-v01 -gga03 -m1.96 -W0.01 -e3.3 -E3.4 -s0.01 -w/Users/Bono/clas/simulation/g12/mcProduction/s15 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS






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




