PROJECT         g12
TRACK:			simulation
COMMAND         DDD/farmscript/farmscript_XXX.vVVV
JOBNAME         g12_simulation_egXXX.vVVV
INPUT_FILES     DDD/genr8input/genr8input_XXX.vVVV

OTHER_FILES:    
 DDD/bin/genr8
 DDD/bin/ffread.card









#=================================================EXTRA=======================================
#   DDD - replaced by directory path (dir) (-w)
#   XXX - replaced by file name  (ebin)
#   YYY - replaced by path/filename
#   ZZZ - replaced by path/tag_file
#   VVV - replaced by version (jobversion)



#here is some extra crap that came with
 #DDD/bin/gamp2part
 #DDD/bin/gsim_bat
 #DDD/bin/gpp
 #DDD/bin/a1c

 #DDD/bin/recsis.tcl
 #DDD/bin/user_ana-g11-pass1


# INPUT_DATA      genr8input
# TOWORK

# OUTPUT_DATA     work.bosview
# OUTPUT_TEMPLATE DDD/bosview/egXXX.vVVV.bosview
# OUTPUT_DATA     work.gampview
# OUTPUT_TEMPLATE DDD/gampview/egXXX.vVVV.gampview
