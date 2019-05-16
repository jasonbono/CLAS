#!/bin/csh

gfortran -m32 -c *.F;

make -f Makefile;
