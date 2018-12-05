#!/bin/bash
#. LbLogin.sh -c x86_64-slc6-gcc46-opt
. SetupProject.sh Urania #v2r0p1

cd /vols/lhcb/ss4314/cutonFitRange


cutfit=/vols/lhcb/ss4314/cutonFitRange/

#read -p "SPECIFY NAME FOR SIMULTANEOUS? " -e trainingname
#echo Your SIM is $trainingname
#echo Your SIM is $trainingname > /vols/lhcb/ss4314/automatize/summary.txt
#
#
#mkdir $trainingname
#
#
#read -p "SPECIFY NAME FOR NOTSIMULTA? " -e tag
#echo Your NOTSIM is $tag
#echo Your NOTSIM is $tag >> /vols/lhcb/ss4314/automatize/summary.txt
#
#mkdir $tag
#
#read -p "SPECIFY NAME FOR SIMCOPY? " -e tn2
#echo Your COPYSIM is $tn2
#echo Your COPYSIM is $tn2 >> /vols/lhcb/ss4314/automatize/summary.txt
#
#read -p "SPECIFY NAME FOR NOTSIMCOPY? " -e tn4
#echo Your NOTCOPYSIM is $tn4
#echo Your NOTCOPYSIM is $tn4 >> /vols/lhcb/ss4314/automatize/summary.txt


trainingname=FUMSB_simultaneous_add2015
tag=FUMSB_NOTsimultaneous_add2015
tn2=FUMSB_simultaneous_symmetric_newcontrolchannel
tn4=FUMSB_NOTsimultaneous_newcontrolchannel
#
#
#
#
#
#
sourc=$tn2
desti=$trainingname
#
##cp $sourc/* $desti/
##cp -r $sourc/src $desti/
##cp -r $sourc/include $desti/
##mkdir $desti/bin
##mkdir $desti/obj
##mkdir $desti/docs
#mkdir $desti/haddtuple
#
#
sourc2=$tn4
desti2=$tag
#
##cp $sourc2/* $desti2/
##cp -r $sourc2/src $desti2/
##cp -r $sourc2/include $desti2/
##mkdir $desti2/bin
##mkdir $desti2/obj
##mkdir $desti2/docs
#mkdir $desti2/haddtuple
#
#cd $trainingname
#
#KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
#
#make
#
#cd bin
#
#./main /vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsMisidFUMSB_Add2015/bin/
#
#
#latex EfficienciesFitRangeCompare.tex
#latex EfficienciesFitRange.tex
#
#mkdir ~/public_html/cutonFitRange/
#mkdir ~/public_html/cutonFitRange/$trainingname/
#cp *pdf ~/public_html/cutonFitRange/$trainingname/
#
#cd ../
#
#hadd haddtuple/JpsiKDataDetached.root bin/B2JpsiKD*.root
#hadd haddtuple/finaldata.root bin/Data2012and2011_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root bin/Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root bin/B23MuNuData_2015_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root
#
#
#
#cd ../$tag
#
#cd bin
#
#./main /vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsMisidFUMSB_Add2015/bin/
#
#
#latex EfficienciesFitRangeCompare.tex
#latex EfficienciesFitRange.tex
#
#mkdir ~/public_html/cutonFitRange/
#mkdir ~/public_html/cutonFitRange/$tag/
#cp *pdf ~/public_html/cutonFitRange/$tag/
#
#cd ../
#
#hadd haddtuple/JpsiKDataDetached.root bin/B2JpsiKD*.root
#hadd haddtuple/finaldata.root bin/Data2012and2011_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root bin/Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root bin/B23MuNuData_2015_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root
#

##------------------CUT ON FCME-----------------#
#
#cd /vols/lhcb/ss4314/cutonFCME
#
#mkdir $trainingname
#
#sourc3=$tn2
#desti3=$trainingname
#
#cp $sourc3/* $desti3/
#cp -r $sourc3/src $desti3/
#cp -r $sourc3/include $desti3/
#mkdir $desti3/bin
#cp $sourc3/bin/*sh $desti3/bin/
#mkdir $desti3/obj
#mkdir $desti3/docs
#cd $trainingname
#
#KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
#
#
#make
#
#cd bin
#
#./mainLOW $cutfit$trainingname/bin/
#./mainHIGH $cutfit$trainingname/bin/
#
#latex EfficienciesLCME.tex
#latex EfficienciesHCME.tex
#latex EfficienciesLCMECompare.tex
#latex EfficienciesHCMECompare.tex
#
#
#mkdir ~/public_html/cutonFCME/
#mkdir ~/public_html/cutonFCME/$trainingname/
#cp *pdf   ~/public_html/cutonFCME/$trainingname/


##-------------DO MISID SPLITTING-----------#
#
cd /vols/lhcb/ss4314/misidsplitting

mkdir $trainingname
mkdir $tag


#cp $sourc/* $desti/
#cp -r $sourc/src $desti/
#cp -r $sourc/include $desti/
#mkdir $desti/bin
#mkdir $desti/obj
#mkdir $desti/docs
#mkdir $desti/Run1
#mkdir $desti/2015
#cp $sourc/bin/*sh $desti/bin/
#
#
#cp $sourc2/* $desti2/
#cp -r $sourc2/src $desti2/
#cp -r $sourc2/include $desti2/
#mkdir $desti2/bin
#mkdir $desti2/obj
#mkdir $desti2/docs
#mkdir $desti2/Run1
#mkdir $desti2/2015
#cp $sourc2/bin/*sh $desti2/bin/

cd $trainingname

make clean

make

cd bin
rm *tex

path=/vols/lhcb/ss4314/cutonFCME/$trainingname/bin/
filename1=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME;
filename4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename5=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename6=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename7=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME;
filename8=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME;


filename10=B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename20=B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename30=B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME;
filename40=B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename50=B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename60=B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename70=B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME;
filename80=B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME;




VAR2="(Polarity==1)&&(runNumber<105000)"
VAR1=Strip21r1MagUp
./main $path $VAR1 $VAR2 $filename1 $filename2 $filename3 $filename4


VAR4="(Polarity==-1)&&(runNumber<105000)"
VAR3=Strip21r1MagDown
./main $path $VAR3 $VAR4 $filename1 $filename2 $filename3 $filename4

VAR6="(Polarity==1)&&(runNumber>105000)"
VAR5=Strip21MagUp
./main $path $VAR5 $VAR6 $filename1 $filename2 $filename3 $filename4

VAR8="(Polarity==-1)&&(runNumber>105000)"
VAR7=Strip21MagDown
./main $path $VAR7 $VAR8 $filename1 $filename2 $filename3 $filename4

./main $path $VAR1 $VAR2 $filename5 $filename6 $filename7 $filename8
./main $path $VAR3 $VAR4 $filename5 $filename6 $filename7 $filename8
./main $path $VAR5 $VAR6 $filename5 $filename6 $filename7 $filename8
./main $path $VAR7 $VAR8 $filename5 $filename6 $filename7 $filename8


cp *tex ../Run1/
rm *tex


./main $path $VAR1 $VAR2 $filename10 $filename20 $filename30 $filename40
./main $path $VAR3 $VAR4 $filename10 $filename20 $filename30 $filename40
./main $path $VAR5 $VAR6 $filename10 $filename20 $filename30 $filename40
./main $path $VAR7 $VAR8 $filename10 $filename20 $filename30 $filename40

./main $path $VAR1 $VAR2 $filename50 $filename60 $filename70 $filename80
./main $path $VAR3 $VAR4 $filename50 $filename60 $filename70 $filename80
./main $path $VAR5 $VAR6 $filename50 $filename60 $filename70 $filename80
./main $path $VAR7 $VAR8 $filename50 $filename60 $filename70 $filename80


cp *tex ../2015/
rm *tex


path=/vols/lhcb/ss4314/cutonFCME/$trainingname/bin/
filename11=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename22=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename33=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename44=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename55=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename66=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename77=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename88=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
#


filename10=B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename20=B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename30=B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename40=B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename50=B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename60=B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename70=B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename80=B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;


#
VAR2="(Polarity==1)&&(runNumber<105000)"
VAR1=Strip21r1MagUp
./main $path $VAR1 $VAR2 $filename11 $filename22 $filename33 $filename44


VAR4="(Polarity==-1)&&(runNumber<105000)"
VAR3=Strip21r1MagDown
./main $path $VAR3 $VAR4 $filename11 $filename22 $filename33 $filename44

VAR6="(Polarity==1)&&(runNumber>105000)"
VAR5=Strip21MagUp
./main $path $VAR5 $VAR6 $filename11 $filename22 $filename33 $filename44

VAR8="(Polarity==-1)&&(runNumber>105000)"
VAR7=Strip21MagDown
./main $path $VAR7 $VAR8 $filename11 $filename22 $filename33 $filename44

./main $path $VAR1 $VAR2 $filename55 $filename66 $filename77 $filename88
./main $path $VAR3 $VAR4 $filename55 $filename66 $filename77 $filename88
./main $path $VAR5 $VAR6 $filename55 $filename66 $filename77 $filename88
./main $path $VAR7 $VAR8 $filename55 $filename66 $filename77 $filename88


cp *tex ../Run1/
rm *tex


./main $path $VAR1 $VAR2 $filename10 $filename20 $filename30 $filename40
./main $path $VAR3 $VAR4 $filename10 $filename20 $filename30 $filename40
./main $path $VAR5 $VAR6 $filename10 $filename20 $filename30 $filename40
./main $path $VAR7 $VAR8 $filename10 $filename20 $filename30 $filename40

./main $path $VAR1 $VAR2 $filename50 $filename60 $filename70 $filename80
./main $path $VAR3 $VAR4 $filename50 $filename60 $filename70 $filename80
./main $path $VAR5 $VAR6 $filename50 $filename60 $filename70 $filename80
./main $path $VAR7 $VAR8 $filename50 $filename60 $filename70 $filename80



cp *tex ../2015/
rm *tex

cp B23MuNuFake*root ../Run1/
cp B23MuNuOS*root ../2015/
cp B23MuNuSS*root ../2015/


cd /vols/lhcb/ss4314/misidsplitting/$tag
#
make clean

make
#
cd bin
rm *tex
#
path3=/vols/lhcb/ss4314/cutonFitRange/$tag/bin/
filename1=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM;
filename2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM;
filename3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM;
filename4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM;
filename5=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM;
filename6=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM;
filename7=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM;
filename8=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM;
#
filename10=B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM;
filename20=B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM;
filename30=B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM;
filename40=B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM;
filename50=B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM;
filename60=B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM;
filename70=B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM;
filename80=B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM;


VAR2="(Polarity==1)&&(runNumber<105000)"
VAR1=Strip21r1MagUp
./main $path3 $VAR1 $VAR2 $filename1 $filename2 $filename3 $filename4


VAR4="(Polarity==-1)&&(runNumber<105000)"
VAR3=Strip21r1MagDown
./main $path3 $VAR3 $VAR4 $filename1 $filename2 $filename3 $filename4

VAR6="(Polarity==1)&&(runNumber>105000)"
VAR5=Strip21MagUp
./main $path3 $VAR5 $VAR6 $filename1 $filename2 $filename3 $filename4

VAR8="(Polarity==-1)&&(runNumber>105000)"
VAR7=Strip21MagDown
./main $path3 $VAR7 $VAR8 $filename1 $filename2 $filename3 $filename4

./main $path3 $VAR1 $VAR2 $filename5 $filename6 $filename7 $filename8
./main $path3 $VAR3 $VAR4 $filename5 $filename6 $filename7 $filename8
./main $path3 $VAR5 $VAR6 $filename5 $filename6 $filename7 $filename8
./main $path3 $VAR7 $VAR8 $filename5 $filename6 $filename7 $filename8


cp *tex ../Run1/
rm *tex

./main $path3 $VAR1 $VAR2 $filename10 $filename20 $filename30 $filename40
./main $path3 $VAR3 $VAR4 $filename10 $filename20 $filename30 $filename40
./main $path3 $VAR5 $VAR6 $filename10 $filename20 $filename30 $filename40
./main $path3 $VAR7 $VAR8 $filename10 $filename20 $filename30 $filename40

./main $path3 $VAR1 $VAR2 $filename50 $filename60 $filename70 $filename80
./main $path3 $VAR3 $VAR4 $filename50 $filename60 $filename70 $filename80
./main $path3 $VAR5 $VAR6 $filename50 $filename60 $filename70 $filename80
./main $path3 $VAR7 $VAR8 $filename50 $filename60 $filename70 $filename80


cp *tex ../2015/
rm *tex

cp B23MuNuFake*root ../Run1/
cp B23MuNuOS*root ../2015/
cp B23MuNuSS*root ../2015/


#---------------------------------ADD weights-----------------------#
#
#cd /vols/lhcb/ss4314/addPIDweights/
#
#mkdir $trainingname
#mkdir $tag
#
#sourc=FUMSB_simultaneous_symmetric_newcontrolchannel_nojackweight #for now CHANGE THIS
#
#
#cp $sourc/* $desti/
#cp -r $sourc/src $desti/
#cp -r $sourc/include $desti/
#mkdir $desti/bin
#mkdir $desti/obj
#mkdir $desti/docs
#mkdir $desti/finaltuples
#cp $sourc/bin/*sh $desti/bin/
#
#
#cp $sourc2/* $desti2/
#cp -r $sourc2/src $desti2/
#cp -r $sourc2/include $desti2/
#mkdir $desti2/bin
#mkdir $desti2/obj
#mkdir $desti2/docs
#mkdir $desti2/finaltuples
#cp $sourc2/bin/*sh $desti2/bin/
#
#cd $trainingname
#
#make
#
#cd bin
#
#
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root MagDown Strip21
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root MagUp Strip21
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root MagDown Strip21r1
##
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuples/modifiedandcut
#end=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg2=modifiedandcut
#end2=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_
#
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#	hadd $beg$tags$end $beg2$tags$var1$end2$var1.root $beg2$tags$var2$end2$var2.root $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 
#
#done
#
#beg3=../finaltuples/modifiedandcut
#end3=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg4=modifiedandcut
#end4=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuples/modifiedandcut
#end5=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg6=modifiedandcut
#end6=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done
#
#
#
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root MagDown Strip21
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root MagUp Strip21
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root MagDown Strip21r1
##
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuples/modifiedandcut
#end=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg2=modifiedandcut
#end2=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_
#
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#	hadd $beg$tags$end $beg2$tags$var1$end2$var1.root $beg2$tags$var2$end2$var2.root $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 
#
#done
#
#beg3=../finaltuples/modifiedandcut
#end3=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg4=modifiedandcut
#end4=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuples/modifiedandcut
#end5=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg6=modifiedandcut
#end6=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done




##read -p "SPECIFY THE NAME OF THE BDT BRANCH in TRAINING? " -e bdt
##echo Your BDTBranch is $bdt
##echo Your BDTBranch is $bdt >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt
#
#
#
#dktree=DecayTree
#
#
#echo "Changing directory to BDTtrainings to get the training"
#
#cd /vols/lhcb/ss4314/BDTtrainings/$trainingname
#
#echo "Copying weights to bin directory"
#
#cp -rf weights/ /vols/lhcb/ss4314/BDTrunonsamples/bin/
#
#echo "Copying root files bin directory"
#
#cp -rf tmva/ /vols/lhcb/ss4314/BDTrunonsamples/bin/
#
#
#echo "Running on usual files"
#
#
#echo "Your files run on are:Data2012and2011_corrm_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID.root B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut.root B23MuNuMCallvar_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root  B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut.root BuKMuMuMerged_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_qmincut_KaonPID.root BuKMuMuMCtotal_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_qmincut_KaonPID.root BuKMuMuMC2011total_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_qmincut_KaonPID.root B23MuNuMCPHSP_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root Data2012and2011_corrmLSD_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root"  >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt
#
#for runfile in  /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/Combinatorialpreparetuple/bin/Data2012and2011_corrm_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/SSMisIDRestrippingpreparetuple/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/B2D3pimupreparetuple/bin/B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/SSMisIDRestrippingpreparetuple/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/SSMisIDRestrippingpreparetuple/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/OSMisIDRestrippingpreparetuple/bin/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/OSMisIDRestrippingpreparetuple/bin/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/OSMisIDRestrippingpreparetuple/bin/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/OSMisIDRestrippingpreparetuple/bin/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/SSMisIDRestrippingpreparetuple/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSigPHSPpreparetuple/bin/B23MuNuMCPHSP_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/LowerMassSideBandDatapreparetuple/bin/Data2012and2011_corrmLSD_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/LowerMassSideBandFullDatapreparetuple/bin/Data2012and2011_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSigpreparetupleNew/bin/B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKmc2011strip20r1New/bin/BuKMuMuMC2011total_misidstrippingfull_trigger.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKmcNew/bin/BuKMuMuMCtotal_misidstrippingfull_trigger.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKdataNew/bin/BuKMuMuMerged_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetupleNew/bin/B23SameSignMuonTotal_trigger_mu1nShared_mu2nShared_mu3nShared.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/FullUpperMassSideBand/bin/Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/DataSignalMassBand/bin/Data2012and2011_SigReg_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKMCDetachedLine/2011/bin/JpsiKMCDetachedLine_2011_misidstrippingfull_trigger.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKMCDetachedLine/2012/bin/JpsiKMCDetachedLine_2012_misidstrippingfull_trigger.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKDataDetachedLine/2011/bin/B2JpsiKDetachedData_2011_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKDataDetachedLine/2012/bin/B2JpsiKDataDetached2012_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSig2015preparetupleNew/bin/B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/B23MuData2015preparetuple/FullUpperMassSideBand/bin/B23MuNuData_2015_corrmFUSMB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/B23MuData2015preparetuple/LowerMassSideBandFullDatapreparetuple/bin/B23MuNuData_2015_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/SSMisIDRestrippingpreparetuple2015/bin/B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/SSMisIDRestrippingpreparetuple2015/bin/B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/SSMisIDRestrippingpreparetuple2015/bin/B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/SSMisIDRestrippingpreparetuple2015/bin/B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/OSMisIDRestrippingpreparetuple2015/bin/B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/OSMisIDRestrippingpreparetuple2015/bin/B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/OSMisIDRestrippingpreparetuple2015/bin/B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/OSMisIDRestrippingpreparetuple2015/bin/B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKMCDetachedLine/2015/bin/JpsiKMCDetached_2015_misidstrippingfull_trigger.root /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKDataDetachedLine/2015/bin/B2JpsiKDataDetached2015_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID.root
#
#
#do
#
#	echo "This is runfile"
#
#	echo $runfile
#
#
#	echo "Copying the runfile into dataset directory"
#
#	cp $runfile /vols/lhcb/ss4314/BDTrunonsamples/datasets/
#
#done
#
#for myfile in Data2012and2011_corrm_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID.root B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut.root B23MuNuMCallvar_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root  B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut.root BuKMuMuMerged_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_qmincut_KaonPID.root BuKMuMuMCtotal_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_qmincut_KaonPID.root BuKMuMuMC2011total_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_qmincut_KaonPID.root B23MuNuMCPHSP_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root Data2012and2011_corrmLSD_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root Data2012and2011_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut.root BuKMuMuMC2011total_misidstrippingfull_trigger.root BuKMuMuMCtotal_misidstrippingfull_trigger.root BuKMuMuMerged_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID.root B23SameSignMuonTotal_trigger_mu1nShared_mu2nShared_mu3nShared.root Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root Data2012and2011_SigReg_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root JpsiKMCDetachedLine_2011_misidstrippingfull_trigger.root JpsiKMCDetachedLine_2012_misidstrippingfull_trigger.root B2JpsiKDetachedData_2011_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID.root B2JpsiKDataDetached2012_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID.root B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root B23MuNuData_2015_corrmFUSMB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root B23MuNuData_2015_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID.root B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID.root B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID.root B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut.root B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID.root B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID.root B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID.root B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut.root JpsiKMCDetached_2015_misidstrippingfull_trigger.root B2JpsiKDataDetached2015_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID.root 
#
#do
#
#	newrunfileloc=/vols/lhcb/ss4314/BDTrunonsamples/datasets/$myfile
#
#	cd /vols/lhcb/ss4314/BDTrunonsamples/bin/
#
#
#	file="./kfoldbacknomu1mu3"
#        echo "the option is $file" >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt
#	if [ -e $file ]; then
#		echo "File exists"
#		$file -s $VAR1 -b $VAR2 -k $VAR4 --sig-tree $dktree --bkg-tree $dktree  -w $weight  --bdt $bdt  -r $newrunfileloc
#
#
#	else 
#		echo "File does not exits, I will not do anything. Just saying..."
#
#	fi
#
#	echo "Coppying trained and applied BDT"
#
#	mkdir /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag
#
#	cp $newrunfileloc /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag
#       
#done
#
#
#echo "put all training into /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag"
#echo "put all training into /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag" >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt
#cp  /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt  /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag
# 
#echo "FINISHED"
