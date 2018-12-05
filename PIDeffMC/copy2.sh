#!bin/bash/

sourc=$PWD/AntiBDT/MCsigB23Mu
desti=$PWD/FUMSB_NOTsimultaneous_newcontrolchannel/MCsigB23Mu

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
cp $sourc/bin/*sh $desti/bin/
mkdir $desti/obj
mkdir $desti/docs
