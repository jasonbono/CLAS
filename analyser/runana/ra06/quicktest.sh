#!/bin/bash






ana=2kppimv01
out=kpkppim
dir=/u/home/jbono/analyser/g12/2kppim/v01


#start analyzing
${ana} -a${out}.view -X1 -C1 kpkppim.56455.A1X.bos
${ana} -L > ${out}.lab
makent ${out} ${out}.lab > ${out}.C
root -q -l ${out}.C



# rm ${ana}.C ${ana}.lab ${ana}.view 
view 