#!/bin/bash

#jason bono
#Aug 9 2012
#to use type:
#nohup jcache_smart.sh topology (kpkp,2kppim,kppippim, or the old kpkppim)

FILES=/w/mss/clas/g12/production/pass1/user_skims/jbono/$1/*
for f in $FILES
do
	echo "--------------  $f   --------------"
	jcache $f
done
