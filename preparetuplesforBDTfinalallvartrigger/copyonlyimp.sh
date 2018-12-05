#!bin/bash/

sourc=$PWD/JpsiKst_fromB2XMuMu_MC/2012
desti=$PWD/JpsiKst_fromB2XMuMu_MC_PiKswaps/2012

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
