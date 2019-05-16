#!/bin/bash

export PREFIX=/group/clas/builds/64bit/NIGHTLY/2011-08-03-r2525/

export ALIGNBITS=64
export PYTHONPATH=$PREFIX
export PATH=$PREFIX/scripts:$PATH

export CERNLIB=/site/cernlib/x86_64_rhel5/2005/lib

export ROOTSYS=/site/root/5.26/Linux_CentOS5.3-x86_64-gcc4.1.2/
export ROOTINC=$ROOTSYS/include
export ROOTLIB=$ROOTSYS/lib
export ROOTBIN=$ROOTSYS/bin

export CLAS6INC=$PREFIX/build/include
export CLAS6LIB=$PREFIX/build/lib
export CLAS6BIN=$PREFIX/build/bin

export MYSQLINC=/usr/include/mysql
export MYSQLLIB=/usr/lib64/mysql

export TCLLIB=/usr/lib64

export PATH=$ROOTBIN:$CLAS6BIN:$PATH

### test if LD_LIBRARY_PATH is set or not
echo $LD_LIBRARY_PATH >& /dev/null
if [[ $? -eq 1 ]]; then
    ### its not, so we set it first.
    LD_LIBRARY_PATH="."
fi

LD_LIBRARY_PATH=$ROOTLIB:$LD_LIBRARY_PATH
LD_LIBRARY_PATH=$CLAS6LIB:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH

export CLAS_PARMS=/group/clas/parms


