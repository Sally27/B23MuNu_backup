#!bin/bash/

sourc=$PWD/FUMSB_simultaneous_NewTCK
desti=$PWD/FUMSB_simultaneous_NewTCK_AntiBDT

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
cp $sourc/bin/*sh $desti/bin/
mkdir $desti/obj
mkdir $desti/docs
