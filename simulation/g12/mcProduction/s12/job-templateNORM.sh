PROJECT:  g12
TRACK:  simulation
JOBNAME:  g12_simulation_XXX.VVV
COMMAND:  generatescript_XXX.VVV
OTHER_FILES: DDD/generatescript_XXX.VVV
INPUT_FILES: 
DDD/genr8input_XXX.VVV
DDD/ffread.g12
ADD/ANA
ADD/BNB

OUTPUT_DATA: ANA.gsim.root
OUTPUT_TEMPLATE: OOO/MC_ANA_XXX.VVV.gsim.a1c.root

OUTPUT_DATA: BNB.gsim.root
OUTPUT_TEMPLATE: OOO/MC_BNB_XXX.VVV.gsim.a1c.root

OUTPUT_DATA: ANA.gsim.gpp.root
OUTPUT_TEMPLATE: OOO/MC_ANA_XXX.VVV.gsim.gpp.a1c.root

OUTPUT_DATA: BNB.gsim.gpp.root
OUTPUT_TEMPLATE: OOO/MC_BNB_XXX.VVV.gsim.gpp.a1c.root

OUTPUT_DATA: work.gamp.root
OUTPUT_TEMPLATE: OOO/MC_ga03_XXX.VVV.gamp.root

SINGLE_JOB: true
DISK_SPACE: 1 GB
TIME: 400
MEMORY: 500 MB
CPU: 3