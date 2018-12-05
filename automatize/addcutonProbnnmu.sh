
trainingname=FUMSB_simultaneous_add2016 #NEW simultaneous year
tag=FUMSB_NOTsimultaneous_add2016 #NEW NOT simultaneous year
tn=_scalesig
#---------------------------------ADD weights trainingname SS 2016-----------------------#

#
#mkdir $tag
#
#sourc=FUMSB_simultaneous_symmetric_newcontrolchannel_nojackweight #for now CHANGE THIS
#
#
sourc=$trainingname
desti=$trainingname$tn


sourc2=$tag
desti2=$tag$tn
###----------------------------------CUT ON PROBNNMU---------------#
##
##
cd /vols/lhcb/ss4314/cutonProbnnmu

mkdir $trainingname$tn
mkdir $tag$tn

#cp $sourc/* $desti/
#cp -r $sourc/src $desti/
#cp -r $sourc/include $desti/
#mkdir $desti/bin
#mkdir $desti/obj
#mkdir $desti/docs
#
#
#
#cp $sourc2/* $desti2/
#cp -r $sourc2/src $desti2/
#cp -r $sourc2/include $desti2/
#mkdir $desti2/bin
#mkdir $desti2/obj
#mkdir $desti2/docs
#

cd $trainingname$tn
###
make clean
make
##
cd bin
##
./main2 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/
##
latex EfficienciesProbnnmu3.tex
##
mkdir ~/public_html/cutonProbnnmu
mkdir ~/public_html/cutonProbnnmu/$trainingname$tn
#
##
cp *pdf ~/public_html/cutonProbnnmu/$trainingname$tn/
#
cd ../
mkdir haddtuples
rm haddtuples/*root
#
#echo "Making Tuples for Signal and Control Fits"
hadd haddtuples/JpsiKdata_Run1_HighFCME.root bin/B2JpsiKDataDetached2012*_HighFCME*.root bin/B2JpsiKDetachedData_2011*_HighFCME*.root
hadd haddtuples/JpsiKdata_Run1_LowFCME.root  bin/B2JpsiKDataDetached2012*_LowFCME*.root bin/B2JpsiKDetachedData_2011*_LowFCME*.root
hadd haddtuples/JpsiKdata_2015_HighFCME.root bin/B2JpsiKDataDetached2015_v42r1*_HighFCME*.root
hadd haddtuples/JpsiKdata_2015_LowFCME.root  bin/B2JpsiKDataDetached2015_v42r1*_LowFCME*.root
hadd haddtuples/JpsiKdata_2016_HighFCME.root bin/B2JpsiK2016*_HighFCME*.root
hadd haddtuples/JpsiKdata_2016_LowFCME.root  bin/B2JpsiK2016*_LowFCME*.root


#
hadd haddtuples/finaldata_HighFCME.root bin/Data2012and2011_corrmFUMSB*_HighFCME*.root bin/Data2012and2011_corrmLSDfull*_HighFCME*.root bin/B23MuNuData2015_DV41r2_corrmLSDfull*HighFCME*.root bin/B23MuNuData2016_corrmFUSMB*HighFCME*.root bin/B23MuNuData2016_corrmLSDfull*HighFCME*.root
hadd haddtuples/finaldata_LowFCME.root  bin/Data2012and2011_corrmFUMSB*_LowFCME*.root bin/Data2012and2011_corrmLSDfull*_LowFCME*.root bin/B23MuNuData2015_DV41r2_corrmLSDfull*LowFCME*.root bin/B23MuNuData2016_corrmFUSMB*LowFCME*.root bin/B23MuNuData2016_corrmLSDfull*LowFCME*.root


hadd haddtuples/finaldata_Run1_HighFCME.root bin/Data2012and2011_corrmFUMSB*_HighFCME*.root bin/Data2012and2011_corrmLSDfull*_HighFCME*.root  
hadd haddtuples/finaldata_Run1_LowFCME.root  bin/Data2012and2011_corrmFUMSB*_LowFCME*.root bin/Data2012and2011_corrmLSDfull*_LowFCME*.root

hadd haddtuples/finaldata_2015_HighFCME.root bin/B23MuNuData2015_DV41r2_corrmLSDfull*HighFCME*.root
hadd haddtuples/finaldata_2015_LowFCME.root  bin/B23MuNuData2015_DV41r2_corrmLSDfull*LowFCME*.root


hadd haddtuples/finaldata_2016_HighFCME.root bin/B23MuNuData2016_corrmFUSMB*HighFCME*.root bin/B23MuNuData2016_corrmLSDfull*HighFCME*.root
hadd haddtuples/finaldata_2016_LowFCME.root  bin/B23MuNuData2016_corrmFUSMB*LowFCME*.root bin/B23MuNuData2016_corrmLSDfull*LowFCME*.root

##
hadd haddtuples/finaldata_Run1and2015_HighFCME.root bin/Data2012and2011_corrmFUMSB*_HighFCME*.root bin/Data2012and2011_corrmLSDfull*_HighFCME*.root bin/B23MuNuData2015_DV41r2_corrmLSDfull*HighFCME*.root
hadd haddtuples/finaldata_Run1and2015_LowFCME.root  bin/Data2012and2011_corrmFUMSB*_LowFCME*.root bin/Data2012and2011_corrmLSDfull*_LowFCME*.root bin/B23MuNuData2015_DV41r2_corrmLSDfull*LowFCME*.root

cd /vols/lhcb/ss4314/cutonProbnnmu
##
cd $tag$tn
##
make clean
make
#
##
cd bin 
##
##
./main2 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/
##
##
latex EfficienciesProbnnmu3.tex
##
mkdir ~/public_html/cutonProbnnmu
mkdir ~/public_html/cutonProbnnmu/$tag$tn
##
##
cp *pdf ~/public_html/cutonProbnnmu/$tag$tn/
#
cd ../
mkdir haddtuples
rm haddtuples/*root
#
hadd haddtuples/JpsiKdata_Run1.root bin/B2JpsiKDataDetached2012* bin/B2JpsiKDetachedData_2011*
hadd haddtuples/JpsiKdata_2015.root bin/B2JpsiKDataDetached2015_v42r1*
hadd haddtuples/JpsiKdata_2016.root bin/B2JpsiK2016*.root
#
echo "Making Tuples for Signal and Control Fits"
#
hadd haddtuples/finaldata.root bin/Data2012and2011_corrmFUMSB*.root bin/Data2012and2011_corrmLSDfull*.root bin/B23MuNuData2015_DV41r2_corrmLSDfull*.root bin/B23MuNuData2016_corrmFUSMB*.root bin/B23MuNuData2016_corrmLSDfull*.root

hadd haddtuples/finaldata_Run1.root bin/Data2012and2011_corrmFUMSB*.root bin/Data2012and2011_corrmLSDfull*.root 

hadd haddtuples/finaldata_2015.root bin/B23MuNuData2015_DV41r2_corrmLSDfull*.root

hadd haddtuples/finaldata_2016.root bin/B23MuNuData2016_corrmFUSMB*.root bin/B23MuNuData2016_corrmLSDfull*.root


hadd haddtuples/finaldata_Run1and2015.root bin/Data2012and2011_corrmFUMSB*.root bin/Data2012and2011_corrmLSDfull*.root bin/B23MuNuData2015_DV41r2_corrmLSDfull*.root

