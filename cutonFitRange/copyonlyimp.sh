#!bin/bash/

#sourc=$PWD/FUMSB_simultaneous_NewTCK
sourc=$PWD/FUMSB_NOTsimultaneous_NewTCK_AntiBDT
desti=$PWD/FUMSB_NOTsimultaneous_beforecombibdt

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
