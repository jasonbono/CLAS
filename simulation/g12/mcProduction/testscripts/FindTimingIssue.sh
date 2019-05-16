



genr8 -B3,5 -M20000 -owork.gamp L0 -U10 < genr8input

#gamp2part stuff (work)
gamp2part -r56855 -owork.part -T -S-0.321,0.378,-0.254,0.407 -z-110,-70 work.gamp
gsim_bat -ffread ffread.g12 -kine 1 -mcin work.part -bosout work.gsim -trig 2000000
gpp -Y -s -S -a2.73 -b1.7 -c1.93 -f1 -R56855 -P0x7f -owork.gsim.gpp work.gsim
a1c -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -owork.gsim.gpp.a1c work.gsim.gpp
#analyze
/u/home/jbono/analyser/g12/LINKS/2kppim-v05 -awork.view -X0 -R10  -C1 work.gsim.gpp.a1c
/u/home/jbono/analyser/g12/LINKS/2kppim-v05 -L > work.lab
makent work < work.lab > work.C
root -q -l -b work.C



#gamp2txt stuff (work2)
gamp2txt -E5.714 -z-110,-70 < work.gamp | txt2part -T -owork2.part
gsim_bat -ffread ffread.g12 -kine 1 -mcin work2.part -bosout work2.gsim -trig 2000000
gpp -Y -s -S -a2.73 -b1.7 -c1.93 -f1 -R56855 -P0x7f -owork2.gsim.gpp work2.gsim
a1c -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -owork2.gsim.gpp.a1c work2.gsim.gpp
#analyze
/u/home/jbono/analyser/g12/LINKS/2kppim-v05 -awork2.view -X0 -R10  -C1 work2.gsim.gpp.a1c
/u/home/jbono/analyser/g12/LINKS/2kppim-v05 -L > work2.lab
makent work2 < work2.lab > work2.C
root -q -l -b work2.C