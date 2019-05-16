#running everything

#======================================================FOR FARM RUNNING/TESTING========================================================
#for normal output of only name.a1c.root and name.gamp.root
#perl producesim.pl -KNORM  -vi2t1 -M5000 -av37k -m1.96 -W0.01 -b2.8 -B3.8 -s0.10 -w/u/home/jbono/simulation/sim_v11 -o/w/hallb/clasg12/jbono/sim/DATA -A/u/home/jbono/SendGet/g12ana/v37k/build/bin
#perl producesim.pl -KNORM  -vi2t1 -M5000 -av37k -m1.96 -W0.01 -b3.8 -B4.8 -s0.10 -w/u/home/jbono/simulation/sim_v11 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/SendGet/g12ana/v37k/build/bin
#perl producesim.pl -KNORM  -vi2t1 -M5000 -av37k -m1.96 -W0.01 -b4.8 -B5.6 -s0.10 -w/u/home/jbono/simulation/sim_v11 -o/w/hallb/clasg12/jbono/sim/DATA -A/u/home/jbono/SendGet/g12ana/v37k/build/bin


#for gpp test
perl producesim.pl -KGPP -vgpptest2 -M1000  -av37k -m1.96 -W0.01 -b2.8 -B3.0 -s0.20 -w/u/home/jbono/simulation/sim_v11 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/SendGet/g12ana/v37k/build/bin

#for all test
perl producesim.pl -KALL -valltest2 -M1000  -av37k -m1.96 -W0.01 -b2.8 -B3.0 -s0.20 -w/u/home/jbono/simulation/sim_v11 -o/w/hallb/clasg12/jbono/sim/DATA -A/u/home/jbono/SendGet/g12ana/v37k/build/bin

#for norm test
perl producesim.pl -KNORM -vnormtest2 -M1000  -av37k -m1.96 -W0.01 -b2.8 -B3.0 -s0.20 -w/u/home/jbono/simulation/sim_v11 -o/w/hallb/clasg12/jbono/sim/DATA -A/u/home/jbono/SendGet/g12ana/v37k/build/bin


#======================================================FOR LOCAL TESTING ========================================================
#perl producesim.pl -KALL -valltest -M1000  -av37k -m1.96 -W0.01 -b2.8 -B3.0 -s0.20 -w/Users/Bono/clas/simulation/g12/mcProduction/sim_v11 -o/w/hallb/clasg12/jbono/sim/DATA -A/u/home/jbono/SendGet/g12ana/v37k/build/bin
#perl producesim.pl -KNORM -vnormtest -M1000  -av37k -m1.96 -W0.01 -b2.8 -B3.0 -s0.20 -w/Users/Bono/clas/simulation/g12/mcProduction/sim_v11 -o/w/hallb/clasg12/jbono/sim/DATA -A/u/home/jbono/SendGet/g12ana/v37k/build/bin
#perl producesim.pl -KGPP -vgpptest -M1000  -av37k -m1.96 -W0.01 -b2.8 -B3.0 -s0.20 -w/Users/Bono/clas/simulation/g12/mcProduction/sim_v11 -o/w/hallb/clasg12/jbono/sim/DATA -A/u/home/jbono/SendGet/g12ana/v37k/build/bin





















#======================================================NOTES========================================================
# possible options: m W B b s t M v w I (d h)  K a 
#   m=mass W=width  -------------------------------------------------------------> give [HHH,WWW]
#   B=beammax  b=beammim  s=beam-increment  -------------------------------------> give [XXX,BBB,SSS] 
#   M=events --------------------------------------------------------------------> gives [NNN]
#   v=jobversion w=work-dir-path R=scripts-subdir I=genr8template-filename ------> give [VVV, DDD,?,?] 
#	o = bosdir which is where the generated events go
#	K = kind.  examples are ALL,NORM,GPPTST (meaning they output diffrent files)


# note that TTT is the tslope

# s#BBB#$emean#;  #  BBB <- $emean <- incremented from min and max (which are iniaized in this code) 
# s#HHH#$mass#;   #  HHH <- $mass <- initized in this code
# s#WWW#$width#;  #  WWW <- $width <- initized in this code 
# s#TTT#$tslope#; #  TTT <- $tslope <- initized to 2.0, eventualy will be taken from array which is initized in each iteration

# s#XXX#$ebin#;  # substitute XXX by the ebin  (from -B,-b,-s)
# s#SSS#$step#;  # substitute SSS by the step size (-s)
# s#DDD#$dir#;  # substitute DDD by the directory (-w)
# s#NNN#$M#;    # M -> NNN -> amount of events accepted by genr8 (-M)




