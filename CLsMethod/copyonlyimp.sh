#!bin/bash/

sourc=$PWD/expected_limit_sim_allsyst
desti=$PWD/expected_limit_sim_Run1only_allsyst

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/

mkdir $desti/bin
cp $sourc/bin/*sh $desti/bin/

mkdir $desti/obj
mkdir $desti/docs

cp -r $sourc/plotExclusionLimit $desti/

