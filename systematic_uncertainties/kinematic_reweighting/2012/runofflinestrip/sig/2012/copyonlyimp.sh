#!bin/bash/

sourc=/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012
desti=$PWD

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
