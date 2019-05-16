#s24



# - - - - - - generation, polarization, gsim, gpp, a1c - - - - - - 
genr8 -BLLL,UUU -MNNN -owork.gamp L0 -U10 <  genr8input_XXX.VVV
#PLR work.gamp #this will output two more files: PosPolwork.gamp & NegPolwork.gamp

#run gamp files through gamp2part or gamp2txt|txt2part
mygamp2part -r10 -owork.part -T -S-0.321,0.378,-0.254,0.407 -z-110,-70 work.gamp
#mygamp2part -r10 -oPosPolwork.part -T -S-0.321,0.378,-0.254,0.407 -z-110,-70 PosPolwork.gamp
#mygamp2part -r10 -oNegPolwork.part -T -S-0.321,0.378,-0.254,0.407 -z-110,-70 NegPolwork.gamp

#run part files through gsim
gsim_bat -ffread ffread.g12 -kine 1 -mcin work.part -bosout work.gsim -trig 2000000
#gsim_bat -ffread ffread.g12 -kine 1 -mcin PosPolwork.part -bosout PosPolwork.gsim -trig 2000000
#gsim_bat -ffread ffread.g12 -kine 1 -mcin NegPolwork.part -bosout NegPolwork.gsim -trig 2000000

#for the unpolirized file run through a1c directly from gsim (skipping gpp)
#a1c -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -owork.gsim.a1c work.gsim

#run gsim files through gpp
gpp -Y -s -S -a2.73 -b1.7 -c1.93 -f1 -R10 -P0x7f -owork.gsim.gpp work.gsim
#gpp -Y -s -S -a2.73 -b1.7 -c1.93 -f1 -R10 -P0x7f -oPosPolwork.gsim.gpp PosPolwork.gsim
#gpp -Y -s -S -a2.73 -b1.7 -c1.93 -f1 -R10 -P0x7f -oNegPolwork.gsim.gpp NegPolwork.gsim

#run gsim.gpp files through a1c
a1c -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -owork.gsim.gpp.a1c work.gsim.gpp
#a1c -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -oPosPolwork.gsim.gpp.a1c PosPolwork.gsim.gpp
#a1c -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -oNegPolwork.gsim.gpp.a1c NegPolwork.gsim.gpp

#remove (part, gsim, gsim.gpp, hbook) files (leaving the  - 3 gamp files, 1 gsim.a1c file, 3 gsim.gpp.a1c files)
rm work.part work.gsim work.gsim.gpp gpp.hbook
#rm PosPolwork.part PosPolwork.gsim PosPolwork.gsim.gpp
#rm NegPolwork.part NegPolwork.gsim NegPolwork.gsim.gpp


# - - - - analyze the unpolarized gsim.a1c file - - - - 
#ANA -agsim2kppim.view -X0 -R56855  -C1 work.gsim.a1c
#ANA -L > gsim2kppim.lab
#makent gsim2kppim < gsim2kppim.lab > gsim2kppim.C
#root -q -l -b gsim2kppim.C
#remove created execess (view, lab, C) files (leaving root file)
#rm gsim2kppim.view gsim2kppim.lab gsim2kppim.C
#change the name of the root file
#mv gsim2kppim.root ANA.gsim.root

#remove the gsim.a1c file
#rm work.gsim.a1c



# - - - - analyze 3 gsim.gpp.a1c files - - - - - - 
ANA -agpp2kppim.view -X0 -R10  -C1 work.gsim.gpp.a1c
ANA -L > gpp2kppim.lab
makentfile gpp2kppim < gpp2kppim.lab > gpp2kppim.C
root -q -l -b gpp2kppim.C
#remove (a1c,view,lab,C) files (leaving root file)
rm gpp2kppim.view gpp2kppim.lab gpp2kppim.C
#change the name of the root file
mv gpp2kppim.root ANA.gsim.gpp.root

#analyze for the positivly polarized set
# ANA -agpp2kppim.view -X0 -R10  -C1 PosPolwork.gsim.gpp.a1c
# ANA -L > gpp2kppim.lab
# makentfile gpp2kppim < gpp2kppim.lab > gpp2kppim.C
# root -q -l -b gpp2kppim.C
# #remove (a1c,view,lab,C) files (leaving root file)
# rm gpp2kppim.view gpp2kppim.lab gpp2kppim.C
# #change the name of the root file
# mv gpp2kppim.root PosPolANA.gsim.gpp.root

#analyze for the negitivly polarized set
# ANA -agpp2kppim.view -X0 -R10  -C1 NegPolwork.gsim.gpp.a1c
# ANA -L > gpp2kppim.lab
# makentfile gpp2kppim < gpp2kppim.lab > gpp2kppim.C
# root -q -l -b gpp2kppim.C
# #remove (a1c,view,lab,C) files (leaving root file)
# rm gpp2kppim.view gpp2kppim.lab gpp2kppim.C
# #change the name of the root file
# mv gpp2kppim.root NegPolANA.gsim.gpp.root

#remove a1c files
rm work.gsim.gpp.a1c
#rm PosPolwork.gsim.gpp.a1c
#rm NegPolwork.gsim.gpp.a1c


#  - - - - some final gamp stuff - - - - - - - - - - 

# analyze the 3 gamp files
GGG work.gamp
#GGG PosPolwork.gamp
#GGG NegPolwork.gamp
 
#reduce all three gamp.root file and remove the full ones. 
RED work.gamp.root #output is reduced100_work.gamp.root
#RED PosPolwork.gamp.root 
#RED NegPolwork.gamp.root
rm work.gamp.root
#rm PosPolwork.gamp.root
#rm NegPolwork.gamp.root

#remove the gamp files
rm work.gamp
#rm PosPolwork.gamp
#rm NegPolwork.gamp

#remove the extra hbook file
#rm gpp.hbook
