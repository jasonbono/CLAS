#this is old code, it got updated to producesim.pl

# #! /bin/bash
# 
# #Author: Jason Bono
# #Date:	  Oct 16 2012
# #Notes:   The runs a software package that generates mc events and output root files
# #
# #
# 
# 
# 
# 
# 
# 
# 
# 
# #############################################i8####################################i8#############################################################
# #i9 produced from s23. 
# 
# 
# eLow=2.8;
# eHigh=5.5;
# eStep=0.1;
# elow[0]=eLow;
# for i in `seq 0 26`;
# do
# 	#eLow+=$eStep;
# 	let "var += 0.1";
# done
# 
# 
# m[0]=17093;
# m[1]=24659;
# m[2]=24809;
# m[3]=29378;
# m[4]=30760;
# m[5]=49909;
# m[6]=45265;
# m[7]=36824;
# m[8]=100000;
# m[9]=88353;
# m[10]=71960;
# m[11]=91412;
# m[12]=56217;
# m[13]=60499;
# m[14]=40306;
# m[15]=36559;
# m[16]=34225;
# m[17]=54333;
# m[18]=39319;
# m[19]=32273;
# m[20]=44774;
# m[21]=31551;
# m[22]=28605;
# m[23]=27640;
# m[24]=20787;
# m[25]=28192;
# m[26]=14595;
# 
# 
# Mass[0]=1.92539;
# Mass[1]=2.00066;
# Mass[2]=2.05297;
# Mass[3]=2.11446;
# Mass[4]=2.14517;
# MassB[5]=2.06933; #the lower mass hyperon in double production (only one bin)
# MassC[5]=2.06933; #the higher mass hyperon in double production
# 
# 
# 
# 
# 
# 
# for i in `seq 0 26`;
# do
#         #echo ${m[i]}
# 		#echo ${elow[i]}
# done
# 
# 
# 
# 

# perl producesim.pl -s0.002 -e2.8 -E2.9 -M24299 -m1.915 -W0.105 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e2.9 -E3.0 -M38027  -m1.915 -W0.105 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e3.0 -E3.1 -M38396 -m1.915 -W0.105 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# 
# perl producesim.pl -s0.002 -e3.1 -E3.2 -M43828 -m1.97 -W0.161 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e3.2 -E3.3 -M46450 -m1.97 -W0.161 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e3.3 -E3.4 -M72212 -m1.97 -W0.161 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e3.4 -E3.5 -M69669 -m1.97 -W0.161 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# 
# perl producesim.pl -s0.002 -e3.5 -E3.6 -M59224 -m2.02 -W0.210 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e3.6 -E3.7 -M102337 -m2.02 -W0.210 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e3.7 -E3.8 -M96550 -m2.02 -W0.210 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# 
# perl producesim.pl -s0.002 -e3.8 -E3.9 -M87237 -m2.06 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e3.9 -E4.0 -M98174 -m2.06 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e4.0 -E4.1 -M78571 -m2.06 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e4.1 -E4.2 -M81733 -m2.06 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# 
# perl producesim.pl -s0.002 -e4.2 -E4.3 -M66713 -m2.10 -W0.318 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e4.3 -E4.4 -M63971 -m2.10 -W0.318 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e4.4 -E4.5 -M60417 -m2.10 -W0.318 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# 
# perl producesim.pl -s0.002 -e4.5 -E4.6 -M78639 -m2.14 -W0.344 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e4.6 -E4.7 -M66876 -m2.14 -W0.344 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e4.7 -E4.8 -M58646 -m2.14 -W0.344 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e4.8 -E4.9 -M73799 -m2.14 -W0.344 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# 
# ###the double bins below:
# perl producesim.pl -s0.002 -e4.9 -E5.0 -M32722 -m2.05 -W0.210 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.0 -E5.1 -M30000 -m2.05 -W0.210 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.1 -E5.2 -M29933 -m2.05 -W0.210 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# #do this energy bin twice and half the M. this is done to generate two hyperon resonances to match the data
# perl producesim.pl -s0.002 -e4.9 -E5.0 -M32722 -m2.25 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.0 -E5.1 -M30000 -m2.25 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.1 -E5.2 -M29933 -m2.25 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# 
# perl producesim.pl -s0.002 -e5.2 -E5.3 -M22534 -m2.1 -W0.318 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.3 -E5.4 -M50000  -m2.1 -W0.318 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.4 -E5.5 -M16338 -m2.1 -W0.318 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# #do this energy bin twice and half the M. this is done to generate two hyperon resonances to match the data
# perl producesim.pl -s0.002 -e5.2 -E5.3 -M22534 -m2.32 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.3 -E5.4 -M50000  -m2.32 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.4 -E5.5 -M16338 -m2.32 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

























#############################################i8####################################i8#############################################################
#i8 produced from s22. 


#perl producesim.pl -s0.002 -e2.8 -E2.9 -M24299 -m1.915 -W0.105 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e2.9 -E3.0 -M38027  -m1.915 -W0.105 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.0 -E3.1 -M38396 -m1.915 -W0.105 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.002 -e3.1 -E3.2 -M43828 -m1.97 -W0.161 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.2 -E3.3 -M46450 -m1.97 -W0.161 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.3 -E3.4 -M72212 -m1.97 -W0.161 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.4 -E3.5 -M69669 -m1.97 -W0.161 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.002 -e3.5 -E3.6 -M59224 -m2.02 -W0.210 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.6 -E3.7 -M102337 -m2.02 -W0.210 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.7 -E3.8 -M96550 -m2.02 -W0.210 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.002 -e3.8 -E3.9 -M87237 -m2.06 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e3.9 -E4.0 -M98174 -m2.06 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.0 -E4.1 -M78571 -m2.06 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.002 -e4.1 -E4.2 -M81733 -m2.06 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

# perl producesim.pl -s0.002 -e4.2 -E4.3 -M66713 -m2.10 -W0.318 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e4.3 -E4.4 -M63971 -m2.10 -W0.318 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e4.4 -E4.5 -M60417 -m2.10 -W0.318 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

# perl producesim.pl -s0.002 -e4.5 -E4.6 -M78639 -m2.14 -W0.344 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e4.6 -E4.7 -M66876 -m2.14 -W0.344 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e4.7 -E4.8 -M58646 -m2.14 -W0.344 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e4.8 -E4.9 -M73799 -m2.14 -W0.344 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# 
# ###the double bins below:
# perl producesim.pl -s0.002 -e4.9 -E5.0 -M32722 -m2.05 -W0.210 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.0 -E5.1 -M30000 -m2.05 -W0.210 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.1 -E5.2 -M29933 -m2.05 -W0.210 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# #do this energy bin twice and half the M. this is done to generate two hyperon resonances to match the data
# perl producesim.pl -s0.002 -e4.9 -E5.0 -M32722 -m2.25 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.0 -E5.1 -M30000 -m2.25 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.1 -E5.2 -M29933 -m2.25 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# 
# perl producesim.pl -s0.002 -e5.2 -E5.3 -M22534 -m2.1 -W0.318 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.3 -E5.4 -M50000  -m2.1 -W0.318 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.4 -E5.5 -M16338 -m2.1 -W0.318 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# #do this energy bin twice and half the M. this is done to generate two hyperon resonances to match the data
# perl producesim.pl -s0.002 -e5.2 -E5.3 -M22534 -m2.32 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.3 -E5.4 -M50000  -m2.32 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
# perl producesim.pl -s0.002 -e5.4 -E5.5 -M16338 -m2.32 -W0.258 -KNORM -vi8t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS




#############################################i7####################################i7#############################################################
#i7t1 TEST TO SEE EFFECT FROM MOVING FROM LEPTONIC FFREAD TO THE NORMAL G12 FFREAD CARD (WITH RUN 10) produced from s22.
#only other difference from this to i7t0 is the step size is three times bigger


#perl producesim.pl -s0.003 -e2.8 -E2.9 -M2530 -m1.915 -W0.105 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e2.9 -E3.0 -M3547  -m1.915 -W0.105 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e3.0 -E3.1 -M7292 -m1.915 -W0.105 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.003 -e3.1 -E3.2 -M4651 -m1.97 -W0.161 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e3.2 -E3.3 -M5132 -m1.97 -W0.161 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e3.3 -E3.4 -M8411 -m1.97 -W0.161 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e3.4 -E3.5 -M8999 -m1.97 -W0.161 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.003 -e3.5 -E3.6 -M9070 -m2.02 -W0.210 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e3.6 -E3.7 -M17581 -m2.02 -W0.210 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e3.7 -E3.8 -M17279 -m2.02 -W0.210 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.003 -e3.8 -E3.9 -M13691 -m2.06 -W0.258 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e3.9 -E4.0 -M21785 -m2.06 -W0.258 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e4.0 -E4.1 -M14856 -m2.06 -W0.258 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e4.1 -E4.2 -M21086 -m2.06 -W0.258 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.003 -e4.2 -E4.3 -M20695 -m2.10 -W0.318 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e4.3 -E4.4 -M23122 -m2.10 -W0.318 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e4.4 -E4.5 -M25337 -m2.10 -W0.318 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.003 -e4.5 -E4.6 -M38738 -m2.14 -W0.344 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e4.6 -E4.7 -M33596 -m2.14 -W0.344 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e4.7 -E4.8 -M29446 -m2.14 -W0.344 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e4.8 -E4.9 -M57533 -m2.14 -W0.344 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.003 -e4.9 -E5.0 -M62617 -m2.16 -W0.413 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e5.0 -E5.1 -M59409 -m2.16 -W0.413 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e5.1 -E5.2 -M61533 -m2.16 -W0.413 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.003 -e5.2 -E5.3 -M45450 -m2.22 -W0.449 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e5.3 -E5.4 -M100000  -m2.22 -W0.449 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.003 -e5.4 -E5.5 -M31158 -m2.22 -W0.449 -KNORM -vi7t1 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s22 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS








######################################i0 testing ##############################
#perl producesim.pl -s2.0 -e3.0 -E5.0 -M100000 -m2.06 -W0.25 -KTEST -vi0t4 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s2.0 -e3.0 -E5.0 -M100000 -m2.06 -W0.25 -KTEST2 -vi0t5 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS



#############################################i7####################################i7#############################################################
#i7 produced from s21.


#perl producesim.pl -s0.001 -e2.8 -E2.9 -M2530 -m1.915 -W0.105 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e2.9 -E3.0 -M3547  -m1.915 -W0.105 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.0 -E3.1 -M7292 -m1.915 -W0.105 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.001 -e3.1 -E3.2 -M4651 -m1.97 -W0.161 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.2 -E3.3 -M5132 -m1.97 -W0.161 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.3 -E3.4 -M8411 -m1.97 -W0.161 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.4 -E3.5 -M8999 -m1.97 -W0.161 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.001 -e3.5 -E3.6 -M9070 -m2.02 -W0.210 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.6 -E3.7 -M17581 -m2.02 -W0.210 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.7 -E3.8 -M17279 -m2.02 -W0.210 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.001 -e3.8 -E3.9 -M13691 -m2.06 -W0.258 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e3.9 -E4.0 -M21785 -m2.06 -W0.258 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.0 -E4.1 -M14856 -m2.06 -W0.258 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.1 -E4.2 -M21086 -m2.06 -W0.258 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.001 -e4.2 -E4.3 -M20695 -m2.10 -W0.318 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.3 -E4.4 -M23122 -m2.10 -W0.318 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.4 -E4.5 -M25337 -m2.10 -W0.318 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04  -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.001 -e4.5 -E4.6 -M38738 -m2.14 -W0.344 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.6 -E4.7 -M33596 -m2.14 -W0.344 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.7 -E4.8 -M29446 -m2.14 -W0.344 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e4.8 -E4.9 -M57533 -m2.14 -W0.344 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.001 -e4.9 -E5.0 -M62617 -m2.16 -W0.413 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e5.0 -E5.1 -M59409 -m2.16 -W0.413 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e5.1 -E5.2 -M61533 -m2.16 -W0.413 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS

#perl producesim.pl -s0.001 -e5.2 -E5.3 -M45450 -m2.22 -W0.449 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e5.3 -E5.4 -M100000  -m2.22 -W0.449 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS
#perl producesim.pl -s0.001 -e5.4 -E5.5 -M31158 -m2.22 -W0.449 -KNORM -vi7t0 -a2kppim-v05 -bkpkp-v03 -gga04 -w/u/home/jbono/simulation/s21 -o/w/hallb/clasg12/jbono/sim/DATA  -A/u/home/jbono/analyser/g12/LINKS


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