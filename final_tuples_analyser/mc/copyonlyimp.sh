#!bin/bash/

sourc=$PWD/sig_mc/2012
desti=/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
