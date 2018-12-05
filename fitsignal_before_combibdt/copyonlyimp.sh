#!bin/bash/
sourc=$PWD/estimateforcombibdt_finalPID_Run1
desti=$PWD/estimateforcombibdt_finalPID_2016


cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/

mkdir $desti/bin
cp $sourc/bin/*sh $desti/bin/

mkdir $desti/obj
mkdir $desti/docs
