#!/bin/bash

#jason bono
#Feb 25 2014
#this must be run from the work disk because it handles big files



ana=/u/home/jbono/analyser/g12/LINKS/2kppim-v09
tree=v09
input=/w/hallb/clasg12/jbono/analyzed-data/2kppim/v09/concated/2kppim-v09.bos #this is the bos skim with my skim cuts from 2kppim-v07
output=/w/hallb/clasg12/jbono/analyzed-data/2kppim/v09/rootfiles/2kppim-v09.root


#------------start analyzing-------------
${ana} -a${tree}.view -X1 -C1 ${input}
${ana} -L > ${tree}.lab
makentfile ${tree} ${tree}.lab > ${tree}.C
root -q -l ${tree}.C
#----------------------------------------

rm ${tree}.C ${tree}.lab ${tree}.view
mv ${tree}.root ${output}