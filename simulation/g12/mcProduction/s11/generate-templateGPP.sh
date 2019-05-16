#this outputs the root files made from 3 diffrent stages in simulation:
#work.gsim.a1c.root
#work.gpp.a1c.root
#work.gamp.root

# - - - - - - - - - - - - -generate the gpp.a1c file from scratch-  - - - - - - - - - - - - - 
genr8 -BLLL,UUU -MNNN -owork.gamp L0 -U10 <  genr8input_XXX.VVV
gamp2part -r56855 -owork.part -T -S-0.321,0.378,-0.254,0.407 -z-110,-70 work.gamp
gsim_bat -ffread ffread.g12 -kine 1 -mcin work.part -bosout work.gsim -trig 2000000
gpp -Y -s -R56855 -P0x7f -owork.gpp work.gsim
a1c -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -owork.a1c work.gpp
#change name to specify the file went through gpp
mv work.a1c work.gpp.a1c

# - - - - - - - - - - - - - - -run the gsim file through a1c- - - - - - - - - - - - - - - - - 
a1c -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -owork.a1c work.gsim
#change name to specify file when through gsim (and did NOT go through gpp)
mv work.a1c work.gsim.a1c

#- - - - - - - - - -  - - - - - - analyze the gsim.a1c file - - -  - - - - - - - - - - - - - - - -
#analyze the gsim file
ANA -aANA.view -X0 -R10  -C1 work.gsim.a1c
ANA -L > ANA.lab
makent ANA < ANA.lab > ANA.C
root -q -l -b ANA.C
#change the name of the gsim root file
mv ANA.root work.gsim.a1c.root
#clean up the extra files for the next run of the analyzer
rm ANA.view ANA.lab ANA.C

# - - - - - - - - - - - - - - - - -analyze the gpp.a1c file - - - - - - - - - - - - - - - - - - 
ANA -aANA.view -X0 -R10  -C1 work.gpp.a1c
ANA -L > ANA.lab
makent ANA < ANA.lab > ANA.C
root -q -l -b ANA.C
#change the name of the gpp root file
mv ANA.root work.gpp.a1c.root
#clean up 
rm ANA.view ANA.lab ANA.C

# - - - - - - - -  - - - -analyze the gamp file - - - - - - - - - - - -
/u/home/jbono/analyser/gampana/ga00/build/bin/analyzegamp work.gamp
# this should output work.gamp.root

# - - - - - - - - - - - - - remove things - - - - - - - - - - - - 
#remove (gamp,part,gsim,gpp,hbook) files
rm work.gamp work.part work.gsim work.gpp gpp.hbook
#remove the gpp.a1c and gsim.a1c files
rm work.gsim.a1c work.gpp.a1c


