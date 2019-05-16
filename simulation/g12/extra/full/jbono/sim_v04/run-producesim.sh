#this is for local testing
perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -vv01 -w/Users/Bono/clas/simulation/g12/full/jbono/sim_v04  -Igenr8input-template

#this is for testing on the farm
perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -vv01 -w/u/home/jbono/simulation/sim_v04 -Igenr8input-template

#this is for full farm use
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v0cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v1cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v2cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v3cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v4cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v5cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v6cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v7cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v8cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v9cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v10cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v11cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v12cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v13cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v14cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v15cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input-template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v16cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input_template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v17cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input_template
#perl producesim.pl -m1.96 -W0.22 -B5.00 -b2.74 -s0.1  -M1000 -v18cascade -w/w/hallb/clasg12/jbono/sim/full  -Igenr8input_template

# possible options: m W B b s t M v w I (d h) 





#   m=mass W=width  -------------------------------------------------------------> give [HHH,WWW]
#   B=beammax  b=beammim  s=beam-increment  -------------------------------------> give [XXX,BBB,SSS] 
#   M=events --------------------------------------------------------------------> gives [NNN]
#   v=jobversion w=work-dir-path R=scripts-subdir I=genr8template-filename ------> give [VVV, DDD,?,?] 


# note that TTT is the tslope

# s#BBB#$emean#;  #  BBB <- $emean <- incremented from min and max (which are iniaized in this code) 
# s#HHH#$mass#;   #  HHH <- $mass <- initized in this code
# s#WWW#$width#;  #  WWW <- $width <- initized in this code 
# s#TTT#$tslope#; #  TTT <- $tslope <- initized to 2.0, eventualy will be taken from array which is initized in each iteration

# s#XXX#$ebin#;  # substitute XXX by the ebin  (from -B,-b,-s)
# s#SSS#$step#;  # substitute SSS by the step size (-s)
# s#DDD#$dir#;  # substitute DDD by the directory (-w)
# s#NNN#$M#;    # M -> NNN -> amount of events accepted by genr8 (-M)