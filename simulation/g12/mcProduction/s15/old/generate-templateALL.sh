#outputs all files:

#work.gamp
#work.part
#work.gsim
#work.gpp
#gpp.hbook
#work.a1c
#ANA.view
#ANA.lab
#ANA.C
#ANA.root
#work.gamp.root

# - - - - - - - - - - - - -generate the a1c files - - - - - - - 
genr8 -BLLL,UUU -MNNN -owork.gamp L0 -U10 <  genr8input_XXX.VVV
gamp2part -r56855 -owork.part -T -S-0.321,0.378,-0.254,0.407 -z-110,-70 work.gamp
gsim_bat -ffread ffread.g12 -kine 1 -mcin work.part -bosout work.gsim -trig 2000000
gpp -Y -s -R56855 -P0x7f -owork.gpp work.gsim
a1c -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -owork.a1c work.gpp
#leaving (gamp,part,gsim,gpp,hbook,a1c) files

#- - - - - - - - - - - - analyze the a1c file - - - - - - - - - 
ANA -aANA.view -X0 -R10  -C1 work.a1c
ANA -L > ANA.lab
makent ANA < ANA.lab > ANA.C
root -q -l -b ANA.C
#leaving (view,lab,C,root file)

# - - - - - - - -  - - - -analyze the gamp - - - - - - - - - - - -
/u/home/jbono/analyser/gampana/ga03/build/bin/ga03 work.gamp
#leaving (root) file
