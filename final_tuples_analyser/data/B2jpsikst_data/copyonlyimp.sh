#!bin/bash/

sourc=$PWD/2016
desti=$PWD/2011

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
