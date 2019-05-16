PROJECT:  g12
TRACK:  simulation
OS: centos62 #new
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


#rec and gen
OUTPUT_DATA: ANA.gsim.gpp.root
OUTPUT_TEMPLATE: OOO/MC-ANA-XXX.VVV.gsim.gpp.a1c.root
OUTPUT_DATA: work.gamp.root
OUTPUT_TEMPLATE: OOO/MC-ga03-XXX.VVV.gamp.root

# PosPolY rec and gen
OUTPUT_DATA: PosPolYANA.gsim.gpp.root
OUTPUT_TEMPLATE: OOO/MC-PosPolY-ANA-XXX.VVV.gsim.gpp.a1c.root
OUTPUT_DATA: PosPolYwork.gamp.root
OUTPUT_TEMPLATE: OOO/MC-PosPolY-ga03-XXX.VVV.gamp.root

# NegPolY rec and gen
OUTPUT_DATA: NegPolYANA.gsim.gpp.root
OUTPUT_TEMPLATE: OOO/MC-NegPolY-ANA-XXX.VVV.gsim.gpp.a1c.root
OUTPUT_DATA: NegPolYwork.gamp.root
OUTPUT_TEMPLATE: OOO/MC-NegPolY-ga03-XXX.VVV.gamp.root



#one file of analyzed reconstructed events without using gpp
#OUTPUT_DATA: ANA.gsim.root
#OUTPUT_TEMPLATE: OOO/MC-ANA-XXX.VVV.gsim.a1c.root



# OUTPUT_DATA: PosPolANA.gsim.gpp.root
# OUTPUT_TEMPLATE: OOO/MC-PosPol-ANA-XXX.VVV.gsim.gpp.a1c.root
# 
# OUTPUT_DATA: NegPolANA.gsim.gpp.root
# OUTPUT_TEMPLATE: OOO/MC-NegPol-ANA-XXX.VVV.gsim.gpp.a1c.root

#keep the uppolarized a1c file
#OUTPUT_DATA: work.gsim.gpp.a1c
#OUTPUT_TEMPLATE: OOO/MC-XXX.VVV.gsim.gpp.a1c
#keep the uppolarized part file
#OUTPUT_DATA: work.part
#OUTPUT_TEMPLATE: OOO/MC-XXX.VVV.part




# OUTPUT_DATA: reduced_PosPolwork.gamp.root
# OUTPUT_TEMPLATE: OOO/MC-PosPol-10-ga03-XXX.VVV.gamp.root
# 
# OUTPUT_DATA: reduced_NegPolwork.gamp.root
# OUTPUT_TEMPLATE: OOO/MC-NegPol-10-ga03-XXX.VVV.gamp.root



### keep the X, Z, and XZ polarized files.###
# OUTPUT_DATA: PosPolXANA.gsim.gpp.root
# OUTPUT_TEMPLATE: OOO/MC-PosPolX-ANA-XXX.VVV.gsim.gpp.a1c.root
# OUTPUT_DATA: NegPolXANA.gsim.gpp.root
# OUTPUT_TEMPLATE: OOO/MC-NegPolX-ANA-XXX.VVV.gsim.gpp.a1c.root
# 
# OUTPUT_DATA: PosPolZANA.gsim.gpp.root
# OUTPUT_TEMPLATE: OOO/MC-PosPolZ-ANA-XXX.VVV.gsim.gpp.a1c.root
# OUTPUT_DATA: NegPolZANA.gsim.gpp.root
# OUTPUT_TEMPLATE: OOO/MC-NegPolZ-ANA-XXX.VVV.gsim.gpp.a1c.root
# 
# OUTPUT_DATA: PosPolXZANA.gsim.gpp.root
# OUTPUT_TEMPLATE: OOO/MC-PosPolXZ-ANA-XXX.VVV.gsim.gpp.a1c.root
# OUTPUT_DATA: NegPolXZANA.gsim.gpp.root
# OUTPUT_TEMPLATE: OOO/MC-NegPolXZ-ANA-XXX.VVV.gsim.gpp.a1c.root










SINGLE_JOB: true
DISK_SPACE: 5 GB
TIME: 1435
MEMORY: 1 GB

#walltime Default = 1440 (one day) walltime Max = 4200 (three days)

######THINGS LEFT BEHIND FROM s17############  (careful with the underscores)
#OUTPUT_DATA: BNB.gsim.gpp.root
#OUTPUT_TEMPLATE: OOO/MC_BNB_XXX.VVV.gsim.gpp.a1c.root


#OUTPUT_DATA: BNB.gsim.root
#OUTPUT_TEMPLATE: OOO/MC_BNB_XXX.VVV.gsim.a1c.root