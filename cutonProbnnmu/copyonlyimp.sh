#!bin/bash/

sourc=$PWD/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights
desti=$PWD/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_AntiBDT

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
cp -r $sourc/haddtuples $desti/
mkdir $desti/bin
cp $sourc/bin/*sh $desti/bin/

mkdir $desti/obj
mkdir $desti/docs
