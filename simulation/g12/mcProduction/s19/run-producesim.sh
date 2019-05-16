
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


## i0t0 from s19: diagnostics for wiggle in ~(lambda + pim) spectrum.
perl producesim.pl -s1.0 -e4.0 -E5.0 -M100000 -m2.06 -W0.25 -KNORM -vi0t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s19 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS


#############################################i5####################################i5#############################################################
#i6 produced from s18.


#perl producesim.pl -s0.001 -e2.8 -E2.9 -M5061 -m1.96 -W0.17 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e2.9 -E3.0 -M7095 -m1.96 -W0.17 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.0 -E3.1 -M7292 -m1.96 -W0.17 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.1 -E3.2 -M9303 -m1.96 -W0.17 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.2 -E3.3 -M10265 -m1.96 -W0.17 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.3 -E3.4 -M16823 -m1.96 -W0.17 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.4 -E3.5 -M17999 -m1.96 -W0.17 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.5 -E3.6 -M18141 -m1.96 -W0.17 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.6 -E3.7 -M35162 -m1.96 -W0.17 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.7 -E3.8 -M34559 -m1.96 -W0.17 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.001 -e3.8 -E3.9 -M27382 -m2.06 -W0.25 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.9 -E4.0 -M41570 -m2.06 -W0.25 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.0 -E4.1 -M29712 -m2.06 -W0.25 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.1 -E4.2 -M42172 -m2.06 -W0.25 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.2 -E4.3 -M41390 -m2.06 -W0.25 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.3 -E4.4 -M46244 -m2.06 -W0.25 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.4 -E4.5 -M50675 -m2.06 -W0.25 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.001 -e4.5 -E4.6 -M77476  -m2.12 -W0.37 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.6 -E4.7 -M67193  -m2.12 -W0.37 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.7 -E4.8 -M58893  -m2.12 -W0.37 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.8 -E4.9 -M115066  -m2.12 -W0.37 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.9 -E5.0 -M125235  -m2.12 -W0.37 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e5.0 -E5.1 -M118819  -m2.12 -W0.37 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e5.1 -E5.2 -M123066  -m2.12 -W0.37 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e5.2 -E5.3 -M90901  -m2.12 -W0.37 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e5.3 -E5.4 -M200000  -m2.12 -W0.37 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e5.4 -E5.5 -M62317  -m2.12 -W0.37 -KNORM -vi6t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS











#############################################i5####################################i5#############################################################
#i5 produced from s18, this was where the kpkp was taken out and the polarized simulation was added.


##oops, for got 3.5-3.6 GeV
#perl producesim.pl -s0.002 -e3.5 -E3.6 -M40382 -m1.96 -W0.17 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.5 -E3.6 -M40382 -m1.96 -W0.17 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.002 -e2.8 -E2.9 -M10702 -m1.96 -W0.17 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e2.9 -E3.0 -M15763 -m1.96 -W0.17 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.0 -E3.1 -M17085 -m1.96 -W0.17 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.1 -E3.2 -M21319 -m1.96 -W0.17 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.2 -E3.3 -M23576 -m1.96 -W0.17 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.3 -E3.4 -M41942 -m1.96 -W0.17 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.4 -E3.5 -M43269 -m1.96 -W0.17 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.6 -E3.7 -M66052 -m1.96 -W0.17 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.7 -E3.8 -M63885 -m1.96 -W0.17 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.002 -e3.8 -E3.9 -M66113 -m2.06 -W0.25 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.9 -E4.0 -M84629 -m2.06 -W0.25 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.0 -E4.1 -M70870 -m2.06 -W0.25 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.1 -E4.2 -M85853 -m2.06 -W0.25 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.2 -E4.3 -M89291 -m2.06 -W0.25 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.3 -E4.4 -M94430 -m2.06 -W0.25 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.4 -E4.5 -M101597 -m2.06 -W0.25 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.002 -e4.5 -E4.6 -M119857  -m2.12 -W0.37 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.6 -E4.7 -M112835  -m2.12 -W0.37 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.7 -E4.8 -M104206  -m2.12 -W0.37 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.8 -E4.9 -M139388  -m2.12 -W0.37 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.9 -E5.0 -M151768  -m2.12 -W0.37 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e5.0 -E5.1 -M143597  -m2.12 -W0.37 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e5.1 -E5.2 -M150928  -m2.12 -W0.37 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e5.2 -E5.3 -M133035  -m2.12 -W0.37 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e5.3 -E5.4 -M200000  -m2.12 -W0.37 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e5.4 -E5.5 -M109422  -m2.12 -W0.37 -KNORM -vi5t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS






#perl producesim.pl -s0.002 -e2.8 -E2.9 -M10702 -m1.96 -W0.17 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e2.9 -E3.0 -M15763 -m1.96 -W0.17 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.0 -E3.1 -M17085 -m1.96 -W0.17 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.1 -E3.2 -M21319 -m1.96 -W0.17 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.2 -E3.3 -M23576 -m1.96 -W0.17 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.3 -E3.4 -M41942 -m1.96 -W0.17 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.4 -E3.5 -M43269 -m1.96 -W0.17 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.6 -E3.7 -M66052 -m1.96 -W0.17 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.7 -E3.8 -M63885 -m1.96 -W0.17 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.002 -e3.8 -E3.9 -M66113 -m2.06 -W0.25 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.9 -E4.0 -M84629 -m2.06 -W0.25 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.0 -E4.1 -M70870 -m2.06 -W0.25 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.1 -E4.2 -M85853 -m2.06 -W0.25 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.2 -E4.3 -M89291 -m2.06 -W0.25 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.3 -E4.4 -M94430 -m2.06 -W0.25 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.4 -E4.5 -M101597 -m2.06 -W0.25 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.002 -e4.5 -E4.6 -M119857  -m2.12 -W0.37 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.6 -E4.7 -M112835  -m2.12 -W0.37 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.7 -E4.8 -M104206  -m2.12 -W0.37 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.8 -E4.9 -M139388  -m2.12 -W0.37 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.9 -E5.0 -M151768  -m2.12 -W0.37 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e5.0 -E5.1 -M143597  -m2.12 -W0.37 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e5.1 -E5.2 -M150928  -m2.12 -W0.37 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e5.2 -E5.3 -M133035  -m2.12 -W0.37 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e5.3 -E5.4 -M200000  -m2.12 -W0.37 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e5.4 -E5.5 -M109422  -m2.12 -W0.37 -KNORM -vi5t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS


#perl producesim.pl -KNORM -vi5t0 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m1.96 -W0.17 -e2.7 -E3.6 -s0.05 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi5t0 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.06 -W0.25 -e3.6 -E4.5 -s0.02 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi5t0 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.12 -W0.37 -e4.5 -E5.5 -s0.005 -w/u/home/jbono/simulation/s18 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS







#############################################i4####################################i4#############################################################

#the first three below are to fill holes in the preexisting beam spectrum
#perl producesim.pl -KNORM -vi4t6 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m1.96 -W0.17 -e2.95 -E3.1 -s0.001 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi4t6 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.06 -W0.25 -e3.95 -E4.05 -s0.001 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi4t6 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.12 -W0.37 -e4.95 -E5.05 -s0.001 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#the three below are are the normal inputs and  proportions (times two)perl producesim.pl -KNORM -vi4t5 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m1.96 -W0.17 -e2.7 -E3.6 -s0.0301 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi4t5 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.06 -W0.25 -e3.6 -E4.5 -s0.0101 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKSperl producesim.pl -KNORM -vi4t5 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.12 -W0.37 -e4.5 -E5.5 -s0.0051 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi4t4 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m1.96 -W0.17 -e2.7 -E3.6 -s0.05 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi4t4 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.06 -W0.25 -e3.6 -E4.5 -s0.02 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS#perl producesim.pl -KNORM -vi4t4 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.12 -W0.37 -e4.5 -E5.5 -s0.01 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -KNORM -vi4t3 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m1.96 -W0.17 -e2.7 -E3.6 -s0.05 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi4t3 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.06 -W0.25 -e3.6 -E4.5 -s0.02 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS#perl producesim.pl -KNORM -vi4t3 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.12 -W0.37 -e4.5 -E5.5 -s0.01 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -KNORM -vi4t2 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m1.96 -W0.17 -e2.7 -E3.6 -s0.05 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi4t2 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.06 -W0.25 -e3.6 -E4.5 -s0.02 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS#perl producesim.pl -KNORM -vi4t2 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.12 -W0.37 -e4.5 -E5.5 -s0.01 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS


#perl producesim.pl -KNORM -vi4t1 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m1.96 -W0.17 -e2.7 -E3.6 -s0.1 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi4t1 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.06 -W0.25 -e3.6 -E4.5 -s0.05 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi4t1 -M200000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.12 -W0.37 -e4.5 -E5.5 -s0.02 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS#perl producesim.pl -KNORM -vi4t0 -M5000 -a2kppim-v05 -bkpkp-v03 -gga04 -m1.96 -W0.17 -e2.7 -E3.6 -s0.5 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -KNORM -vi4t0 -M50000 -a2kppim-v05 -bkpkp-v03 -gga04 -m1.96 -W0.17 -e2.7 -E3.6 -s0.1 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS#perl producesim.pl -KNORM -vi4t0 -M50000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.06 -W0.25 -e3.6 -E4.5 -s0.05 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi4t0 -M50000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.12 -W0.37 -e4.5 -E5.5 -s0.02 -w/u/home/jbono/simulation/s17 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS




#############################################i3####################################i3#############################################################
#perl producesim.pl -KNORM -vi3t1 -M5000 -a2kppim-v05 -bkpkp-v03 -gga04 -m1.96 -W0.17 -e2.7 -E3.6 -s0.05 -w/u/home/jbono/simulation/s16 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi3t1 -M5000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.06 -W0.25 -e3.6 -E4.5 -s0.02 -w/u/home/jbono/simulation/s16 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi3t1 -M5000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.12 -W0.37 -e4.5 -E5.5 -s0.005 -w/u/home/jbono/simulation/s16 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -KNORM -vi3t0 -M5000 -a2kppim-v05 -bkpkp-v03 -gga04 -m1.96 -W0.17 -e2.7 -E3.6 -s0.05 -w/u/home/jbono/simulation/s16 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi3t0 -M5000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.06 -W0.25 -e3.6 -E4.5 -s0.02 -w/u/home/jbono/simulation/s16 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -KNORM -vi3t0 -M5000 -a2kppim-v05 -bkpkp-v03 -gga04 -m2.12 -W0.37 -e4.5 -E5.5 -s0.005 -w/u/home/jbono/simulation/s16 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -d -KNORM -vi1t7 -M100000 -a2kppim-v05 -bkpkp-v03 -gga04 -m1.96 -W0.01 -e2.7 -E5.5 -s0.1 -w/Users/Bono/clas/simulation/g12/mcProduction/s16 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS




#############################################i2####################################i2#############################################################
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
#perl producesim.pl -d -KNORM -vi1t7 -M100000 -a2kppim-v01 -bkpkp-v01 -gga03 -m1.96 -W0.01 -e3.3 -E3.4 -s0.01 -w/Users/Bono/clas/simulation/g12/mcProduction/s15 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS






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




