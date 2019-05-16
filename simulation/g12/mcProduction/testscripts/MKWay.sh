#generation
genr8 -B3,5 -M100000 -owork.gamp L0 -U10 < genr8input 

#cut out from MK's script
gamp2part -r10 -owork.part -T -S-0.321,0.378,-0.254,0.407 -z-110,-70 work.gamp
gsim_bat -ffread ffread.g12 -kine 1 -mcin work.part -bosout work.gsim
gpp -a2.73 -b1.7 -c1.93 -f1 -Y -s -R10 -P0x7f -owork.gsim.gpp work.gsim
a1c -R10 -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -owork.gsim.gpp.a1c work.gsim.gpp


/u/home/jbono/analyser/g12/LINKS/2kppim-v05 -awork.view -X0 -R10  -C1 work.gsim.gpp.a1c
/u/home/jbono/analyser/g12/LINKS/2kppim-v05 -L > work.lab
makent work < work.lab > work.C
root -q -l -b work.C
