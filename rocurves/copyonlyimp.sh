#!bin/bash/

#sourc=$PWD/second_attempt_new2016tuples
sourc=$PWD/third_attemp_newTCKapproach

desti=$PWD/fourth_attempt

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/

mkdir $desti/bin
cp $sourc/bin/*sh $desti/bin/

mkdir $desti/obj
mkdir $desti/docs
