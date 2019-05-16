# developed in s20, this ALL version has the purpose of keeping every file in the chain of generation for checking and debuging 



# - - - - - - generation, polarization, gsim, gpp, a1c - - - - - - 
genr8 -BLLL,UUU -MNNN -owork.gamp L0 -U10 <  genr8input_XXX.VVV

#run through gamp2part or tamp2txt|txt2part
#the old way
#gamp2part -r56855 -owork.part -T -S-0.321,0.378,-0.254,0.407 -z-110,-70 work.gamp
#the new way
gamp2part -r10 -owork.part -T -S-0.321,0.378,-0.254,0.407 -z-110,-70 work.gamp

gsim_bat -ffread ffread.g12 -kine 1 -mcin work.part -bosout work.gsim -trig 2000000

#runthrough gpp and a1c
#the old way
#gpp -Y -s -S -a2.73 -b1.7 -c1.93 -f1 -R56855 -P0x7f -owork.gsim.gpp work.gsim
#the new way
gpp -Y -s -a2.73 -b1.7 -c1.93 -f1 -R10 -P0x7f -owork.gsim.gpp work.gsim
a1c -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -owork.gsim.gpp.a1c work.gsim.gpp


# - - - - analyze 3 gsim.gpp.a1c files - - - - - - 

ANA -agpp2kppim.view -X0 -R10  -C1 work.gsim.gpp.a1c
ANA -L > gpp2kppim.lab
makent gpp2kppim < gpp2kppim.lab > gpp2kppim.C
root -q -l -b gpp2kppim.C
#mv gpp2kppim.root ANA.gsim.gpp.root