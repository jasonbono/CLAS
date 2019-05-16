#!/bin/bash


energy=$1
version=$2
stage=a1c
ana=v37k
anadir=/u/home/jbono/SendGet/g12ana/v37k/build/bin
input=/w/hallb/clasg12/jbono/sim/DATA
output=/w/hallb/clasg12/jbono/sim/ANALYZED/test3



if [ "$PWD" == "$output" ]
 then
  loc=dir
  echo "from $output"
  else
  echo "go to the output directory ${output} "
  echo "you are in $PWD"
  exit
fi

echo "=====make symbolic link for analyzer in current directory====="
ln -s ${anadir}/${ana} ${output}/.

echo "======create the view file from the bos file========"
${ana} -a${ana}.view -X0 -R10  -C1 ${input}/work_${energy}.${version}.${stage}
echo "======create the lable file from the view file========"
${ana} -L > ${ana}.lab
echo "========making the C file======================"
makent ${ana} < ${ana}.lab > ${ana}.C
echo "==========making the root file================="
root -q -l ${ana}.C


echo "removing the C, view and lable files"
rm ${ana}.C ${ana}.view ${ana}.lab

echo "removing the symbolic link" 
#the file extention is here to ensure the build of the analyzer is not deleeted 
rm ${output}/${ana}


mv ${ana}.root ${energy}_${version}.root
