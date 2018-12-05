#!bin/bash/

sourc=$PWD
desti=/vols/lhcb/ss4314/addPIDweights/FUMSB_simultaneous_symmetric/

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
