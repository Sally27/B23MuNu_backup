
simold=FUMSB_simultaneous_add2016_scalesig
notsimold=FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation
sim=FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights #NEW simultaneous year
notsimPID=FUMSB_NOTsimultaneous_NewTCK_AntiBDT #NEW NOT simultaneous year
notsim=FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_AntiBDT #NEW NOT simultaneous year
#---------------------------------ADD weights trainingname SS 2016-----------------------#

#
#mkdir $notsim
#
#sourc=FUMSB_simultaneous_symmetric_newcontrolchannel_nojackweight #for now CHANGE THIS
#
#
sourc=$sim
desti=$sim


sourc2=$notsim
desti2=$notsim
###----------------------------------CUT ON PROBNNMU---------------#
##
##
cd /vols/lhcb/ss4314/cutonProbnnmu

#mkdir $sim
mkdir $notsim
#
#sourc=$simold
#sourc2=$notsimold
#desti=$sim
#desti2=$notsim
#
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
#
#cd $sim
#
#
#make clean
#make
#
#cd bin
#
#
#./main2 /vols/lhcb/ss4314/cutonFCME/$sim/bin/
#
#
#latex EfficienciesProbnnmu3.tex
#
#
#mkdir ~/public_html/cutonProbnnmu
#mkdir ~/public_html/cutonProbnnmu/$sim
#
#
#cp *pdf ~/public_html/cutonProbnnmu/$sim/
#cd ../
#mkdir haddtuples
#rm haddtuples/*root
##
##echo "Making Tuples for Signal and Control Fits"
#hadd haddtuples/JpsiKdata_Run1_HighFCME.root bin/Data_B2JpsiK_2012*_HighFCME*.root bin/Data_B2JpsiK_2011*_HighFCME*.root
#hadd haddtuples/JpsiKdata_Run1_LowFCME.root  bin/Data_B2JpsiK_2012*_LowFCME*.root bin/Data_B2JpsiK_2011*_LowFCME*.root
##hadd haddtuples/JpsiKdata_2015_HighFCME.root bin/B2JpsiKDataDetached2015_v42r1*_HighFCME*.root
##hadd haddtuples/JpsiKdata_2015_LowFCME.root  bin/B2JpsiKDataDetached2015_v42r1*_LowFCME*.root
#hadd haddtuples/JpsiKdata_2016_HighFCME.root bin/Bu23JpsiKData2016*_HighFCME*.root
#hadd haddtuples/JpsiKdata_2016_LowFCME.root  bin/Bu23JpsiKData2016*_LowFCME*.root
#
#
##
#hadd haddtuples/finaldata_HighFCME.root bin/Data_B23MuNu_Run1_corrmFUMSB*_HighFCME*.root bin/Data_B23MuNu_Run1_corrmLSDfull*_HighFCME*.root bin/Bu23MuNuData2016_corrmFUSMB*HighFCME*.root bin/Bu23MuNuData2016_corrmLSDfull*HighFCME*.root
#hadd haddtuples/finaldata_LowFCME.root  bin/Data_B23MuNu_Run1_corrmFUMSB*_LowFCME*.root bin/Data_B23MuNu_Run1_corrmLSDfull*_LowFCME*.root bin/Bu23MuNuData2016_corrmFUSMB*LowFCME*.root bin/Bu23MuNuData2016_corrmLSDfull*LowFCME*.root
#
#
#hadd haddtuples/finaldata_Run1_HighFCME.root bin/Data_B23MuNu_Run1_corrmFUMSB*_HighFCME*.root bin/Data_B23MuNu_Run1_corrmLSDfull*_HighFCME*.root  
#hadd haddtuples/finaldata_Run1_LowFCME.root  bin/Data_B23MuNu_Run1_corrmFUMSB*_LowFCME*.root bin/Data_B23MuNu_Run1_corrmLSDfull*_LowFCME*.root
#
##hadd haddtuples/finaldata_2015_HighFCME.root bin/B23MuNuData2015_DV41r2_corrmLSDfull*HighFCME*.root
##hadd haddtuples/finaldata_2015_LowFCME.root  bin/B23MuNuData2015_DV41r2_corrmLSDfull*LowFCME*.root
#
#
#hadd haddtuples/finaldata_2016_HighFCME.root bin/Bu23MuNuData2016_corrmFUSMB*HighFCME*.root bin/Bu23MuNuData2016_corrmLSDfull*HighFCME*.root
#hadd haddtuples/finaldata_2016_LowFCME.root  bin/Bu23MuNuData2016_corrmFUSMB*LowFCME*.root bin/Bu23MuNuData2016_corrmLSDfull*LowFCME*.root

##
#hadd haddtuples/finaldata_Run1and2015_HighFCME.root bin/Data_B23MuNu_Run1_corrmFUMSB*_HighFCME*.root bin/Data_B23MuNu_Run1_corrmLSDfull*_HighFCME*.root bin/B23MuNuData2015_DV41r2_corrmLSDfull*HighFCME*.root
#hadd haddtuples/finaldata_Run1and2015_LowFCME.root  bin/Data_B23MuNu_Run1_corrmFUMSB*_LowFCME*.root bin/Data_B23MuNu_Run1_corrmLSDfull*_LowFCME*.root bin/B23MuNuData2015_DV41r2_corrmLSDfull*LowFCME*.root
#
cd /vols/lhcb/ss4314/cutonProbnnmu
##
cd $notsim
##
make clean
make

#
cd bin 
#
#
./main2 /vols/lhcb/ss4314/cutonFitRange/$notsimPID/bin/
##
##
latex EfficienciesAll.tex
##
mkdir ~/public_html/cutonProbnnmu
mkdir ~/public_html/cutonProbnnmu/$notsim
##
##
cp *pdf ~/public_html/cutonProbnnmu/$notsim/
#
cd ../


mkdir haddtuples
rm haddtuples/*root

for cut in BasicCut probnnmunew probnnmu02 probnnmu025 probnnmu03 probnnmu035 probnnmupi04 probnnmupi05 probnnmupi06
do
    newvar=$cut.root

    hadd -f haddtuples/JpsiKdata_Run1_$newvar bin/Data_B2JpsiK_2012*$newvar bin/Data_B2JpsiK_2011*$newvar
    hadd -f haddtuples/Signaldata_Run1_$newvar bin/Data_B23MuNu_Run1_corrmFUMSB*$newvar bin/Data_B23MuNu_Run1_corrmLSDfull*$newvar 

done

for cut2 in BasicCut probmu1 probmu15 probmu2 probmu25 probmu3 probmu35
do
    robot=$cut2.root
##hadd haddtuples/JpsiKdata_2015.root bin/B2JpsiKDataDetached2015_v42r1*
    hadd -f haddtuples/JpsiKdata_2016_$robot bin/Bu23JpsiKData2016*$robot
    hadd -f haddtuples/Signaldata_2016_$robot bin/Bu23MuNuData2016_corrmFUSMB*$robot bin/Bu23MuNuData2016_corrmLSDfull*$robot

done
##
#echo "Making Tuples for Signal and Control Fits"
##
#hadd haddtuples/finaldata.root bin/Data_B23MuNu_Run1_corrmFUMSB*.root bin/Data_B23MuNu_Run1_corrmLSDfull*.root  bin/Bu23MuNuData2016_corrmFUSMB*.root bin/Bu23MuNuData2016_corrmLSDfull*.root
#
#hadd haddtuples/finaldata_Run1.root bin/Data_B23MuNu_Run1_corrmFUMSB*.root bin/Data_B23MuNu_Run1_corrmLSDfull*.root 
#
##hadd haddtuples/finaldata_2015.root bin/B23MuNuData2015_DV41r2_corrmLSDfull*.root
#
#hadd haddtuples/finaldata_2016.root bin/Bu23MuNuData2016_corrmFUSMB*.root bin/Bu23MuNuData2016_corrmLSDfull*.root
#
#
##hadd haddtuples/finaldata_Run1and2015.root bin/Data_B23MuNu_Run1_corrmFUMSB*.root bin/Data_B23MuNu_Run1_corrmLSDfull*.root bin/B23MuNuData2015_DV41r2_corrmLSDfull*.root

