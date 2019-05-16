#!bin/bash


#Name: OrganizeSim.sh
#Author: Jason Bono
#Date: October 22 2012
#Purpose: To take the ouput of my generated montecarlo (s13 etc) and orginize

#Usage: go to directory where the files to be cleaned are, then specify the i9t9 group as argument

dir=$1


#the script for generation with s18
if [ -d "./${dir}" ]
then
    echo "Directory ./${dir} already exits. Moving files to subdirectorys"
else
    echo "Directory ./${dir} DNE and will be created along with all needed sub-directorys"
mkdir ./${dir}
mkdir ./${dir}/2kppim ./${dir}/PosPol-2kppim ./${dir}/NegPol-2kppim  ./${dir}/2kppim-gsim ./${dir}/gamproot-100 ./${dir}/PosPol-gamproot ./${dir}/NegPol-gamproot ./${dir}/gampascii
fi

mv MC-2kppim*${dir}.gsim.gpp.a1c.root ./${dir}/2kppim/. 
mv MC-PosPol-2kppim*${dir}.gsim.gpp.a1c.root ./${dir}/PosPol-2kppim/.
mv MC-NegPol-2kppim*${dir}.gsim.gpp.a1c.root ./${dir}/NegPol-2kppim/.

mv MC-2kppim*${dir}.gsim.a1c.root ./${dir}/2kppim-gsim/.

mv MC-100-*${dir}*.gamp.root ./${dir}/gamproot-100/.
mv MC-PosPol-*${dir}*.gamp.root ./${dir}/PosPol-gamproot/.
mv MC-NegPol-*${dir}*.gamp.root ./${dir}/NegPol-gamproot/.
mv MC-*${dir}*.gamp.ascii ./${dir}/gampascii/.



##now to print how many files are in each directory
echo " ./${dir}/2kppim/ has this many files: "
ls ./${dir}/2kppim/* | wc

echo " ./${dir}/PosPol-2kppim/ has this many files: "
ls ./${dir}/PosPol-2kppim/* | wc

echo " ./${dir}/NegPol-2kppim/ has this many files: "
ls ./${dir}/NegPol-2kppim/* | wc

echo " ./${dir}/2kppim-gsim/ has this many files: "
ls ./${dir}/2kppim-gsim/* | wc

echo " ./${dir}/gamproot-100/ has this many files: "
ls ./${dir}/gamproot-100/* | wc

echo " ./${dir}/PosPol-gamproot/ has this many files: "
ls ./${dir}/PosPol-gamproot/* | wc

echo " ./${dir}/NegPol-gamproot/ has this many files: "
ls ./${dir}/NegPol-gamproot/* | wc

echo " ./${dir}/gampascii/ has this many files: "
ls ./${dir}/gampascii/* | wc




###below is for generation of simulation with versions s17 or lower#######
#mkdir ./${dir}
#mkdir ./${dir}/kpkp ./${dir}/kpkp-gsim ./${dir}/2kppim ./${dir}/2kppim-gsim ./${dir}/gamp
#mv *kpkp*${dir}.gsim.gpp.a1c.root ./${dir}/kpkp/.
#mv *kpkp*${dir}.gsim.a1c.root ./${dir}/kpkp-gsim/.
#mv *2kppim*${dir}.gsim.gpp.a1c.root ./${dir}/2kppim/.
#mv *2kppim*${dir}.gsim.a1c.root ./${dir}/2kppim-gsim/.
#mv *${dir}*.gamp.root ./${dir}/gamp/.
