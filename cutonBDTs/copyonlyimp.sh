#!bin/bash/

sourc=$PWD/MCSig2016_288888335_vs_DATAMisid2016
desti=$PWD/MCSig2016_288888335_vs_DATAMisid2016_AntiBDT

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs

echo 'This was the dir you copied from:' > $desti/copysummary.txt
echo $sourc >> $desti/copysummary.txt
echo $desti >> $desti/copysummary.txt
 
