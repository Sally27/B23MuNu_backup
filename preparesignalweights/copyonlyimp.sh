#!bin/bash/

##sourc=$PWD/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights
sourc=$PWD/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_correct_gen_level
desti=/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/preparesignalweights_correct/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_correct_gen_level

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
cp $sourc/bin/*sh $desti/bin/
mkdir $desti/obj
mkdir $desti/docs
