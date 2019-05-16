#!/bin/bash

#jason bono 

#june 18 2012: changed the code to include the runs
#56556.A70
#56869.A10
#56635.A10
#56593.A20
#56405.A20
#56860.B20


#june 17 2012

#this was created to skim by had the files that are giving workflow a hard time.
#after this work flow should work smoothly unless there are more bos files which are sufficently small to crash it
#the following bos files have very few events and are causing my skim to crash.
#56405 A20
#56593 A20
#56869 A10
#56635 A10


# specify the files to write
badfile[0]=56556.A7
badfile[1]=56869.A1
badfile[2]=56635.A1
badfile[3]=56593.A2
badfile[4]=56405.A2
badfile[5]=56860.B2 #this file is naughty-> its because it wasnt cached
max=5
for ((i=0; i <= 5; i++))
do
	
	#cache
	echo ======================CACHEING ${badfile[i]}0 FROM THE TAPE============================== 
	jcache /mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/${badfile[i]}0
	#skim
	echo =================SKIMMING ${badfile[i]}0 and outputting ${badfile[i]}0.bos===============
	kpkppim-skim -okpkppim.${badfile[i]}0.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/${badfile[i]}0
	kpkp-skim -okpkp.${badfile[i]}0.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/${badfile[i]}0
	kppippim-skim -okppippim.${badfile[i]}0.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/${badfile[i]}0
	#jput
	echo ==================JPUTING ${badfile[i]}0.bos AS ${badfile[i]}X.bos =====================
	jput kpkppim.${badfile[i]}0.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/2kppim/kpkppim.${badfile[i]}X.bos
	jput kpkp.${badfile[i]}0.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/kpkp/kpkp.${badfile[i]}X.bos
	jput kppippim.${badfile[i]}0.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/kppippim/kppippim.${badfile[i]}X.bos
	#rm 
	echo ======================REMOVING ${badfile[i]}0.bos FROM CURRENT DIRECTORY===============
	rm kpkppim.${badfile[i]}0.bos
	rm kpkp.${badfile[i]}0.bos
	rm kppippim.${badfile[i]}0.bos
done



#-------------------------------------skim by hand--------------------------------------
#kpkppim (2kppim)

#kpkppim-skim -okpkppim.56405.A2X.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/56405.A20
#kpkppim-skim -okpkppim.56593.A2X.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/56593.A20
#kpkppim-skim -okpkppim.56635.A1X.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/56635.A10
#kpkppim-skim -okpkppim.56869.A1X.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/56869.A10


#kpkp
#kpkp-skim -okpkp.56405.A2X.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/56405.A20
#kpkp-skim -okpkp.56593.A2X.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/56593.A20
#kpkp-skim -okpkp.56635.A1X.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/56635.A10
#kpkp-skim -okpkp.56869.A1X.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/56869.A10
#kppippim
#kppippim-skim -okppippim.56405.A2X.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/56405.A20
#kppippim-skim -okppippim.56593.A2X.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/56593.A20
#kppippim-skim -okppippim.56635.A1X.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/56635.A10
#kppippim-skim -okppippim.56869.A1X.bos /cache/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk/56869.A10


#-------------------------------jput bos skims-----------------------------------------------------------
#kpkppim
#jput kpkppim.56405.A2X.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/2kppim/kpkppim.56405.A2X.bos
#jput kpkppim.56593.A2X.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/2kppim/kpkppim.56593.A2X.bos
#jput kpkppim.56635.A1X.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/2kppim/kpkppim.56635.A1X.bos
#jput kpkppim.56869.A1X.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/2kppim/kpkppim.56869.A1X.bos
#kpkp
#jput kpkp.56405.A2X.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/kpkp/kpkp.56405.A2X.bos
#jput kpkp.56593.A2X.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/kpkp/kpkp.56593.A2X.bos
#jput kpkp.56635.A1X.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/kpkp/kpkp.56635.A1X.bos
#jput kpkp.56869.A1X.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/kpkp/kpkp.56869.A1X.bos
#kppippim
#jput kppippim.56405.A2X.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/kppippim/kppippim.56405.A2X.bos
#jput kppippim.56593.A2X.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/kppippim/kppippim.56593.A2X.bos
#jput kppippim.56635.A1X.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/kppippim/kppippim.56635.A1X.bos
#jput kppippim.56869.A1X.bos /w/mss/clas/g12/production/pass1/user_skims/jbono/kppippim/kppippim.56869.A1X.bos

#------------------------------------------remove skims from current directory---------------------------
#kpkppim
#rm kpkppim.56405.A2X.bos
#rm kpkppim.56593.A2X.bos
#rm kpkppim.56635.A1X.bos
#rm kpkppim.56869.A1X.bos
#kpkp
#rm kpkp.56405.A2X.bos
#rm kpkp.56593.A2X.bos
#rm kpkp.56635.A1X.bos
#rm kpkp.56869.A1X.bos
#kppippim
#rm kppippim.56405.A2X.bos
#rm kppippim.56593.A2X.bos
#rm kppippim.56635.A1X.bos
#rm kppippim.56869.A1X.bos

#---------------------------------------------uncomment to run workflow again------------------------
#g12runs -tpass1 -m | xargs -n2 workflow-bosskim-kpkppim.py -j
#g12runs -tpass1 -m | xargs -n2 workflow-bosskim-kpkp.py -j
#g12runs -tpass1 -m | xargs -n2 workflow-bosskim-kppippim.py -j