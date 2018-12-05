#!bin/bash/

sourc=$PWD/sig_data/2016/FullUpperMassSideBand
desti=$PWD/sig_data_fullregion/2016

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
