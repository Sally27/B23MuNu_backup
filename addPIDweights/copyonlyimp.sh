#!bin/bash/

sourc=$PWD/estimateformisidbdt_finalPID_2016
desti=$PWD/estimateforcombibdt_finalPID_2016

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/

mkdir $desti/bin
cp $sourc/bin/*sh $desti/bin/

mkdir $desti/obj
mkdir $desti/docs

mkdir $desti/os

sourc2=$PWD/estimateformisidbdt_finalPID_2016/os
desti2=$PWD/estimateforcombibdt_finalPID_2016/os
mkdir $desti2/src

cp $sourc2/* $desti2/
cp -r $sourc2/src $desti2/
cp -r $sourc2/include $desti2/

mkdir $desti2/bin
cp $sourc2/bin/*sh $desti2/bin/

mkdir $desti2/obj
mkdir $desti2/docs
