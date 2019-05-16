PROJECT:  g12
TRACK:  simulation
JOBNAME:  g12_simulation_XXX.VVV
COMMAND:  generatescript_XXX.VVV
OTHER_FILES: DDD/generatescript_XXX.VVV
INPUT_FILES: 
DDD/genr8input_XXX.VVV
DDD/ffread.g12
ADD/RED
ADD/PLR
ADD/ANA
ADD/BNB
ADD/GGG


#keep the gamp 
OUTPUT_DATA: work.gamp
OUTPUT_TEMPLATE: OOO/MC-XXX.VVV.gamp

#keep the part
OUTPUT_DATA: work.part
OUTPUT_TEMPLATE: OOO/MC-XXX.VVV.part

#keep the gsim
OUTPUT_DATA: work.gsim
OUTPUT_TEMPLATE: OOO/MC-XXX.VVV.gsim

#keep the gpp
OUTPUT_DATA: work.gsim.gpp
OUTPUT_TEMPLATE: OOO/MC-XXX.VVV.gsim.gpp

#keep the a1c
OUTPUT_DATA: work.gsim.gpp.a1c
OUTPUT_TEMPLATE: OOO/MC-XXX.VVV.gsim.gpp.a1c

#keep the view
OUTPUT_DATA: gpp2kppim.view
OUTPUT_TEMPLATE: OOO/MC-ANA-XXX.VVV.view

#keep the lable
OUTPUT_DATA: gpp2kppim.lab
OUTPUT_TEMPLATE: OOO/MC-ANA-XXX.VVV.lab

#keep the C
OUTPUT_DATA: gpp2kppim.C
OUTPUT_TEMPLATE: OOO/MC-ANA-XXX.VVV.C

#keep the root
OUTPUT_DATA: gpp2kppim.root
OUTPUT_TEMPLATE: OOO/MC-ANA-XXX.VVV.root


SINGLE_JOB: true
DISK_SPACE: 3 GB
TIME: 300
MEMORY: 1 GB

#set wall time lim to 4000 mins which is close to the maximum of 4200 (three days)

######THINGS LEFT BEHIND FROM s17############  (careful with the underscores)
#OUTPUT_DATA: BNB.gsim.gpp.root
#OUTPUT_TEMPLATE: OOO/MC_BNB_XXX.VVV.gsim.gpp.a1c.root


#OUTPUT_DATA: BNB.gsim.root
#OUTPUT_TEMPLATE: OOO/MC_BNB_XXX.VVV.gsim.a1c.root

# developed in s20, this ALL version has the purpose of keeping every file in the chain of generation for checking and debuging 