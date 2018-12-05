#!/bin/bash
#. LbLogin.sh -c x86_64-slc6-gcc46-opt
. SetupProject.sh Urania v5r0 #v2r0p1

cd /vols/lhcb/ss4314/cutonFitRange


cutfit=/vols/lhcb/ss4314/cutonFitRange/

newdir_notsim=FUMSB_NOTsimultaneous_NewTCK
newdir=FUMSB_simultaneous_NewTCK


#olddir_notsim=FUMSB_NOTsimultaneous_NewTuples_2016
#olddir=FUMSB_simultaneous_NewTuples_2016

mkdir $newdir_notsim
mkdir $newdir


sourc3=/vols/lhcb/ss4314/cutonFitRange/$olddir
desti3=/vols/lhcb/ss4314/cutonFitRange/$newdir

sourc4=/vols/lhcb/ss4314/cutonFitRange/$olddir_notsim
desti4=/vols/lhcb/ss4314/cutonFitRange/$newdir_notsim


#-----------------------------------------------------------------------#

#----------------------CUT FIT RANGE sim--------------------------------#
##---------main takes path so change the most recent misidbdt-----------#

cd $newdir

KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

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

make
#
cd bin
#
# 2 pathnames for BDT on run1 and bdt on Run2
./main /vols/lhcb/ss4314/cutonBDTs/MCsig_vs_MisidFUMSB_new2016tuples/bin/ /vols/lhcb/ss4314/cutonBDTs/MCsig_vs_MisidFUMSB_new2016tuples/bin/
#
#
latex EfficienciesFitRangeCompare.tex
latex EfficienciesFitRange.tex
#
mkdir ~/public_html/cutonFitRange/
mkdir ~/public_html/cutonFitRange/$newdir/
cp *pdf ~/public_html/cutonFitRange/$newdir/

cd ../

hadd haddtuple/JpsiKDataDetached.root bin/B2JpsiKD*.root
hadd haddtuple/finaldata.root bin/Data2012and2011_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root bin/Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root bin/B23MuNuData2015_DV41r2_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root



#----------------------CUT FIT RANGE NOT sim--------------------------------#
##---------main takes path so change the most recent misidbdt-----------#
cd $newdir_notsim

KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

echo "Do you wish to copy all source files from old directory?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) cp $sourc4/* $desti4/; cp -r $sourc4/src $desti4/; cp -r $sourc4/include $desti4/; mkdir $desti4/bin; cp $sourc4/bin/*sh $desti4/bin/; mkdir $desti4/obj; mkdir $desti4/docs; echo "Do your changes and run this script again selecting no";  return;;
        No )  break;;
    esac
done


echo "Do you wish to change any of the input tuples?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) cd src/; echo "Do your changes and run this script again selecting no";  return;;
        No ) make; break;;
    esac
done
make

cd bin
#
./main /vols/lhcb/ss4314/cutonBDTs/MCsig_vs_MisidFUMSB_new2016tuples/bin/ /vols/lhcb/ss4314/cutonBDTs/MCsig_vs_MisidFUMSB_new2016tuples/bin/
#
#
latex EfficienciesFitRangeCompare.tex
latex EfficienciesFitRange.tex
#
mkdir ~/public_html/cutonFitRange/
mkdir ~/public_html/cutonFitRange/$newdir_notsim/
cp *pdf ~/public_html/cutonFitRange/$newdir_notsim/

cd ../

hadd haddtuple/JpsiKDataDetached.root bin/B2JpsiKD*.root
hadd haddtuple/finaldata.root bin/Data2012and2011_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root bin/Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root bin/B23MuNuData2015_DV41r2_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root
#

