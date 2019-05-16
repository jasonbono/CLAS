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


#keep the gamp files for reference and give them ascii extentions
OUTPUT_DATA: work.gamp
OUTPUT_TEMPLATE: OOO/MC-ga03-XXX.VVV.gamp.ascii



#one file of analyzed reconstructed events without using gpp
OUTPUT_DATA: ANA.gsim.root
OUTPUT_TEMPLATE: OOO/MC-ANA-XXX.VVV.gsim.a1c.root




#three files of reconstruced files
OUTPUT_DATA: ANA.gsim.gpp.root
OUTPUT_TEMPLATE: OOO/MC-ANA-XXX.VVV.gsim.gpp.a1c.root

OUTPUT_DATA: PosPolANA.gsim.gpp.root
OUTPUT_TEMPLATE: OOO/MC-PosPol-ANA-XXX.VVV.gsim.gpp.a1c.root

OUTPUT_DATA: NegPolANA.gsim.gpp.root
OUTPUT_TEMPLATE: OOO/MC-NegPol-ANA-XXX.VVV.gsim.gpp.a1c.root


#keep the a1c file
OUTPUT_DATA: work.gsim.gpp.a1c
OUTPUT_TEMPLATE: OOO/MC-XXX.VVV.gsim.gpp.a1c

#the generated events after going through the gamp analyzer
OUTPUT_DATA: reduced100_work.gamp.root
OUTPUT_TEMPLATE: OOO/MC-100-ga03-XXX.VVV.gamp.root

OUTPUT_DATA: PosPolwork.gamp.root
OUTPUT_TEMPLATE: OOO/MC-PosPol-ga03-XXX.VVV.gamp.root

OUTPUT_DATA: NegPolwork.gamp.root
OUTPUT_TEMPLATE: OOO/MC-NegPol-ga03-XXX.VVV.gamp.root




SINGLE_JOB: true
DISK_SPACE: 10 GB
TIME: 1140
MEMORY: 1 GB

#set wall time lim to 4000 mins which is close to the maximum of 4200 (three days)

######THINGS LEFT BEHIND FROM s17############  (careful with the underscores)
#OUTPUT_DATA: BNB.gsim.gpp.root
#OUTPUT_TEMPLATE: OOO/MC_BNB_XXX.VVV.gsim.gpp.a1c.root


#OUTPUT_DATA: BNB.gsim.root
#OUTPUT_TEMPLATE: OOO/MC_BNB_XXX.VVV.gsim.a1c.root