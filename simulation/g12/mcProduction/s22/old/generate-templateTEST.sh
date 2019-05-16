


# - - - - - - generation, polarization, gsim, gpp, a1c - - - - - - 
genr8 -BLLL,UUU -MNNN -owork.gamp L0 -U10 <  genr8input_XXX.VVV

#run through gamp2part and tamp2txt|txt2part
gamp2txt -E5.714 -z-110,-70 < work.gamp | txt2part -T -owork.part
rm work.gamp

#run through gsim
gsim_bat -ffread ffread.g12 -kine 1 -mcin work.part -bosout work.gsim -trig 2000000
rm work.part


#run through gpp
gpp -Y -s -a2.73 -b1.7 -c1.93 -f1 -R10 -P0x7f -owork.gsim.gpp work.gsim
rm work.gsim


#run through a1c
a1c -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -owork.gsim.gpp.a1c work.gsim.gpp
rm work.gsim.gpp

# - - - - analyze 3 gsim.gpp.a1c files - - - - - - 

ANA -agpp2kppim.view -X0 -R10  -C1 work.gsim.gpp.a1c
ANA -L > gpp2kppim.lab
makent gpp2kppim < gpp2kppim.lab > gpp2kppim.C
root -q -l -b gpp2kppim.C


rm work.gsim.gpp.a1c
rm gpp2kppim.view gpp2kppim.lab gpp2kppim.C
