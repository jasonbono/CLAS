#jb updated sep 20 2012

#for -vi1t0 meaning iteration 2, try 1 (starting from 1,1)
perl producesim.pl -m1.96 -W0.01 -B3.8 -b2.8 -s0.10 -M1000000 -vi2t1 -w/u/home/jbono/simulation/sim_v11 -o/w/hallb/clasg12/jbono/sim/DATA -av37k -A/u/home/jbono/SendGet/g12ana/v37k/build/bin
perl producesim.pl -m1.96 -W0.01 -B4.8 -b3.8 -s0.10 -M1000000 -vi2t1 -w/u/home/jbono/simulation/sim_v11 -o/w/hallb/clasg12/jbono/sim/DATA -av37k -A/u/home/jbono/SendGet/g12ana/v37k/build/bin
perl producesim.pl -m1.96 -W0.01 -B5.6 -b4.8 -s0.10 -M1000000 -vi2t1 -w/u/home/jbono/simulation/sim_v11 -o/w/hallb/clasg12/jbono/sim/DATA -av37k -A/u/home/jbono/SendGet/g12ana/v37k/build/bin


#from sim_v10
#perl producesim.pl -m1.96 -W0.22 -B3.8 -b2.8 -s0.10 -M1000000 -vv05 -w/u/home/jbono/simulation/sim_v10 -o/w/hallb/clasg12/jbono/sim/DATA -av37k -A/u/home/jbono/SendGet/g12ana/v37k/build/bin
#perl producesim.pl -m1.96 -W0.22 -B4.8 -b3.8 -s0.10 -M1000000 -vv05 -w/u/home/jbono/simulation/sim_v10 -o/w/hallb/clasg12/jbono/sim/DATA -av37k -A/u/home/jbono/SendGet/g12ana/v37k/build/bin
#perl producesim.pl -m1.96 -W0.22 -B5.6 -b4.8 -s0.10 -M1000000 -vv05 -w/u/home/jbono/simulation/sim_v10 -o/w/hallb/clasg12/jbono/sim/DATA -av37k -A/u/home/jbono/SendGet/g12ana/v37k/build/bin




# possible options: m W B b s t M v w I (d h) 

#   m=mass W=width  -------------------------------------------------------------> give [HHH,WWW]
#   B=beammax  b=beammim  s=beam-increment  -------------------------------------> give [XXX,BBB,SSS] 
#   M=events --------------------------------------------------------------------> gives [NNN]
#   v=jobversion w=work-dir-path R=scripts-subdir I=genr8template-filename ------> give [VVV, DDD,?,?] 
#	o = bosdir which is where the generated events go

# note that TTT is the tslope

# s#BBB#$emean#;  #  BBB <- $emean <- incremented from min and max (which are iniaized in this code) 
# s#HHH#$mass#;   #  HHH <- $mass <- initized in this code
# s#WWW#$width#;  #  WWW <- $width <- initized in this code 
# s#TTT#$tslope#; #  TTT <- $tslope <- initized to 2.0, eventualy will be taken from array which is initized in each iteration

# s#XXX#$ebin#;  # substitute XXX by the ebin  (from -B,-b,-s)
# s#SSS#$step#;  # substitute SSS by the step size (-s)
# s#DDD#$dir#;  # substitute DDD by the directory (-w)
# s#NNN#$M#;    # M -> NNN -> amount of events accepted by genr8 (-M)




