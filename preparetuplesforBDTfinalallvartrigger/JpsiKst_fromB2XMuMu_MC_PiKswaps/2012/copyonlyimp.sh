#!bin/bash/

sourc=$PWD
desti=/vols/lhcb/ss4314/final_tuples_analyser/mc/jpsikst_PiKswaps_mc/2016

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
