#!bin/bash/

sourc=/vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsMisidFUMSB_newcontrolchannel
desti=

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
