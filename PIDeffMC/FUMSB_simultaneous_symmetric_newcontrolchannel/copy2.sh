#!bin/bash/

sourc=../FUMSB_simultaneous_symmetric/MCsigB23Mu
desti=$PWD/MCsigB23Mu/

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
cp $sourc/bin/*sh $desti/bin/
mkdir $desti/obj
mkdir $desti/docs
