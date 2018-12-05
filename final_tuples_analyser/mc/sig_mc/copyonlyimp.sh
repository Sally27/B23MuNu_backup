#!bin/bash/

sourc=$PWD/2012_signalmodelqminfirst
desti=/vols/lhcb/ss4314/final_tuples_analyser_PO_AND_UE/mc/sig_mc/2012

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
