#!bin/bash/

sourc=/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/OSMisIDRestrippingpreparetuple
desti=$PWD

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
