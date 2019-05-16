#s16
#this outputs the two gsim.a1c.root, two gsim.gpp.a1c.root files & and one gamp.root:
# ana1-gsim, ana2-gsim, ana1-gpp, ana2-gpp, gamp

# - - - - - - - - - - - - -generate the a1c files - - - - - - - 
genr8 -BLLL,UUU -MNNN -owork.gamp L0 -U10 <  genr8input_XXX.VVV
gamp2part -r56855 -owork.part -T -S-0.321,0.378,-0.254,0.407 -z-110,-70 work.gamp
gsim_bat -ffread ffread.g12 -kine 1 -mcin work.part -bosout work.gsim -trig 2000000
#from gsim get a1c
a1c -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -owork.gsim.a1c work.gsim
#run through gpp and get a1c file
gpp -Y -s -R56855 -P0x7f -owork.gsim.gpp work.gsim
a1c -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -owork.gsim.gpp.a1c work.gsim.gpp


#remove (part, gsim, gsim.gpp, hbook) files (leaving the  -gamp, gsim.a1c & gsim.gpp.a1c- files)
rm work.part work.gsim work.gsim.gpp gpp.hbook


#- - - - - - - - - - - - analyze the gsim.a1c file - - - - - - - - - 

#the first analyzer
ANA -agsim2kppim.view -X0 -R10  -C1 work.gsim.a1c
ANA -L > gsim2kppim.lab
makent gsim2kppim < gsim2kppim.lab > gsim2kppim.C
root -q -l -b gsim2kppim.C
#remove created execess (view, lab, C) files (leaving root file)
rm gsim2kppim.view gsim2kppim.lab gsim2kppim.C
#change the name of the root file
mv gsim2kppim.root ANA.gsim.root


#the second analyzer
BNB -agsimkpkp.view -X0 -R10  -C1 work.gsim.a1c
BNB -L > gsimkpkp.lab
makent gsimkpkp < gsimkpkp.lab > gsimkpkp.C
root -q -l -b gsimkpkp.C
#remove created execess (view, lab, C) files (leaving root file)
rm gsimkpkp.view gsimkpkp.lab gsimkpkp.C
#change the name of the root file
mv gsimkpkp.root BNB.gsim.root


#remove the gsim.a1c file
rm work.gsim.a1c

#- - - - - - - - - - - - analyze the gsim.gpp.a1c file - - - - - - - - - 

#the first analyzer
ANA -agpp2kppim.view -X0 -R10  -C1 work.gsim.gpp.a1c
ANA -L > gpp2kppim.lab
makent gpp2kppim < gpp2kppim.lab > gpp2kppim.C
root -q -l -b gpp2kppim.C
#remove (a1c,view,lab,C) files (leaving root file)
rm gpp2kppim.view gpp2kppim.lab gpp2kppim.C
#change the name of the root file
mv gpp2kppim.root ANA.gsim.gpp.root


#the second analyzer
BNB -agppkpkp.view -X0 -R10  -C1 work.gsim.gpp.a1c
BNB -L > gppkpkp.lab
makent gppkpkp < gppkpkp.lab > gppkpkp.C
root -q -l -b gppkpkp.C
#remove (a1c,view,lab,C) files (leaving root file)
rm gppkpkp.view gppkpkp.lab gppkpkp.C
#change the name of the root file
mv gppkpkp.root BNB.gsim.gpp.root


#remove the gsim.gpp.a1c file
rm work.gsim.gpp.a1c

# - - - - - - - - - - - - - - - - -analyze the gamp -  - - -- - - - - - - - - - -
GGG work.gamp
#remove the (gamp) file (leaving root file) 
rm work.gamp
