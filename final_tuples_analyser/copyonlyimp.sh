#!bin/bash/

sourc=$PWD/compareReop/
desti=$PWD/compareReop_finaltuples/

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
