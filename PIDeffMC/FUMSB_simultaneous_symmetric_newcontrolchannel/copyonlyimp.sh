#!bin/bash/

sourc=../FUMSB_simultaneous_symmetric/MCctlJpsiK
desti=$PWD/MCctlJpsiK

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
cp $sourc/bin/*sh $desti/bin/
mkdir $desti/obj
mkdir $desti/docs
