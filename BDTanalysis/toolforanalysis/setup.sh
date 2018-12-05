#!/bin/bash


export ROOTSYS=/cvmfs/lhcb.cern.ch/lib/lcg/app/releases/ROOT/5.34.09/x86_64-slc6-gcc46-opt/root
source $ROOTSYS/bin/thisroot.sh

DEND_PATH=/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH


KFOLD_PATH=/vols/lhcbdisk05/ss4314/TMVA/kfoldold/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

make clean
make
