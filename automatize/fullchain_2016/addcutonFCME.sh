#!/bin/bash
#. LbLogin.sh -c x86_64-slc6-gcc46-opt
. SetupProject.sh Urania v5r0 #v2r0p1

cd /vols/lhcb/ss4314/cutonFitRange


cutfit=/vols/lhcb/ss4314/cutonFitRange/

##------------------CUT ON FCME-----------------#
#
cd /vols/lhcb/ss4314/cutonFCME

newdir=FUMSB_simultaneous_NewTuples_2016
olddir=FUMSB_simultaneous_add2016
mkdir $newdir

sourc3=/vols/lhcb/ss4314/cutonFCME/$olddir
desti3=/vols/lhcb/ss4314/cutonFCME/$newdir


echo "Do you wish to copy all source files from old directory?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) cp $sourc3/* $desti3/; cp -r $sourc3/src $desti3/; cp -r $sourc3/include $desti3/; mkdir $desti3/bin; cp $sourc3/bin/*sh $desti3/bin/; mkdir $desti3/obj; mkdir $desti3/docs; echo "Do your changes and run this script again selecting no";  return;;
        No )  break;;
    esac
done

cd $newdir

echo "Do you wish to change any of the input tuples?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) cd src/; echo "Do your changes and run this script again selecting no";  return;;
        No ) make; break;;
    esac
done


cd $newdir
KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH


make
#
cd bin/
#
./mainLOW $cutfit$newdir/bin/
./mainHIGH $cutfit$newdir/bin/
#
latex EfficienciesLCME.tex
latex EfficienciesHCME.tex
latex EfficienciesLCMECompare.tex
latex EfficienciesHCMECompare.tex
#
#
mkdir ~/public_html/cutonFCME/
mkdir ~/public_html/cutonFCME/$newdir/
cp *pdf   ~/public_html/cutonFCME/$newdir/
