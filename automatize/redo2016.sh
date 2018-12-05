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


trainingname=FUMSB_simultaneous_add2016 #NEW simultaneous year
tag=FUMSB_NOTsimultaneous_add2016 #NEW NOT simultaneous year
tn2=FUMSB_simultaneous_add2015 #OLD simultaneous year
tn4=FUMSB_NOTsimultaneous_add2015 #OLD NOT simultaneous year
#
#
#
#
#
#

mkdir $trainingname
mkdir $tag

#----------------DO ONLY ONCE if you want to change makefile------------#

#sourc=$tn2
#desti=$trainingname
##
#cp $sourc/* $desti/
#cp -r $sourc/src $desti/
#cp -r $sourc/include $desti/
#mkdir $desti/bin
#mkdir $desti/obj
#mkdir $desti/docs
#mkdir $desti/haddtuple
##
##
#sourc2=$tn4
#desti2=$tag
##
#cp $sourc2/* $desti2/
#cp -r $sourc2/src $desti2/
#cp -r $sourc2/include $desti2/
#mkdir $desti2/bin
#mkdir $desti2/obj
#mkdir $desti2/docs
#mkdir $desti2/haddtuple
##

#-----------------------------------------------------------------------#

#----------------------CUT FIT RANGE sim--------------------------------#
##---------main takes path so change the most recent misidbdt-----------#

#cd $trainingname
#
#KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
#
#make
##
#cd bin
##
#./main /vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsMisidFUMSB_add2016_newPID/bin/
##
##
#latex EfficienciesFitRangeCompare.tex
#latex EfficienciesFitRange.tex
##
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
#----------------------CUT FIT RANGE NOT sim--------------------------------#
##---------main takes path so change the most recent misidbdt-----------#
#cd $tag
#
#KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
#
#make
#
#cd bin
##
#./main /vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsMisidFUMSB_add2016_newPID/bin/
##
##
#latex EfficienciesFitRangeCompare.tex
#latex EfficienciesFitRange.tex
##
#mkdir ~/public_html/cutonFitRange/
#mkdir ~/public_html/cutonFitRange/$tag/
#cp *pdf ~/public_html/cutonFitRange/$tag/
#
#cd ../
#
#hadd haddtuple/JpsiKDataDetached.root bin/B2JpsiKD*.root
#hadd haddtuple/finaldata.root bin/Data2012and2011_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root bin/Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root bin/B23MuNuData_2015_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root
#

###------------------CUT ON FCME-----------------#
##
#cd /vols/lhcb/ss4314/cutonFCME
#
#mkdir $trainingname
#
##sourc3=$tn2
##desti3=$trainingname
##
##cp $sourc3/* $desti3/
##cp -r $sourc3/src $desti3/
##cp -r $sourc3/include $desti3/
##mkdir $desti3/bin
##cp $sourc3/bin/*sh $desti3/bin/
##mkdir $desti3/obj
##mkdir $desti3/docs
##cd $trainingname
#
#KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
#
#cd $trainingname
#
#make
##
#cd bin/
##
#./mainLOW $cutfit$trainingname/bin/
#./mainHIGH $cutfit$trainingname/bin/
##
#latex EfficienciesLCME.tex
#latex EfficienciesHCME.tex
#latex EfficienciesLCMECompare.tex
#latex EfficienciesHCMECompare.tex
##
##
#mkdir ~/public_html/cutonFCME/
#mkdir ~/public_html/cutonFCME/$trainingname/
#cp *pdf   ~/public_html/cutonFCME/$trainingname/

##---------------OPTIMIZE BDT CUTS BY ADDING BRANCHES TO BDT-------##
##------------DO misid splitting before bdt------------##
#
#cd /vols/lhcb/ss4314/misidsplitting/estimateforcombibdt
#
#make
#
#cd bin
#
#
#path3=/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/OSMisIDRestrippingpreparetuple/bin/
#path4=/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/SSMisIDRestrippingpreparetuple/bin/
#filename1=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID;
#filename2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID;
#filename3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut;
#filename4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID;
#filename5=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID;
#filename6=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID;
#filename7=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut;
#filename8=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID;
#
#
#
#VAR2="(Polarity==1)&&(runNumber<105000)"
#VAR1=Strip21r1MagUp
#./main $path3 $VAR1 $VAR2 $filename1 $filename2 $filename3 $filename4
#
#
#VAR4="(Polarity==-1)&&(runNumber<105000)"
#VAR3=Strip21r1MagDown
#./main $path3 $VAR3 $VAR4 $filename1 $filename2 $filename3 $filename4
#
#VAR6="(Polarity==1)&&(runNumber>105000)"
#VAR5=Strip21MagUp
#./main $path3 $VAR5 $VAR6 $filename1 $filename2 $filename3 $filename4
#
#VAR8="(Polarity==-1)&&(runNumber>105000)"
#VAR7=Strip21MagDown
#./main $path3 $VAR7 $VAR8 $filename1 $filename2 $filename3 $filename4
#
#./main $path4 $VAR1 $VAR2 $filename5 $filename6 $filename7 $filename8
#./main $path4 $VAR3 $VAR4 $filename5 $filename6 $filename7 $filename8
#./main $path4 $VAR5 $VAR6 $filename5 $filename6 $filename7 $filename8
#./main $path4 $VAR7 $VAR8 $filename5 $filename6 $filename7 $filename8
#

##------------DO misid splitting after combi bdt------------##
#
#cd /vols/lhcb/ss4314/misidsplitting/estimateformisidbdt
#
#make
#
#cd bin
#
#
#path3=/vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsCombiFUMSB_add2016_newPID/bin/
#path4=/vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsCombiFUMSB_add2016_newPID/bin/
#filename1=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic
#filename2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic
#filename3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic
#filename4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic
#filename5=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic
#filename6=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic
#filename7=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic
#filename8=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic
#
#
#
#VAR2="(Polarity==1)&&(runNumber<105000)"
#VAR1=Strip21r1MagUp
#./main $path3 $VAR1 $VAR2 $filename1 $filename2 $filename3 $filename4
#
#
#VAR4="(Polarity==-1)&&(runNumber<105000)"
#VAR3=Strip21r1MagDown
#./main $path3 $VAR3 $VAR4 $filename1 $filename2 $filename3 $filename4
#
#VAR6="(Polarity==1)&&(runNumber>105000)"
#VAR5=Strip21MagUp
#./main $path3 $VAR5 $VAR6 $filename1 $filename2 $filename3 $filename4
#
#VAR8="(Polarity==-1)&&(runNumber>105000)"
#VAR7=Strip21MagDown
#./main $path3 $VAR7 $VAR8 $filename1 $filename2 $filename3 $filename4
#
#./main $path4 $VAR1 $VAR2 $filename5 $filename6 $filename7 $filename8
#./main $path4 $VAR3 $VAR4 $filename5 $filename6 $filename7 $filename8
#./main $path4 $VAR5 $VAR6 $filename5 $filename6 $filename7 $filename8
#./main $path4 $VAR7 $VAR8 $filename5 $filename6 $filename7 $filename8



##----------------------ADD PID WEIGJTS before bdt--------##
#
#cd /vols/lhcb/ss4314/addPIDweights/
#cd estimateforcombibdt
#
#make
#
#rm finaltuplesRun1/*
#
#cd bin/
#
#cp /vols/lhcb/ss4314/misidsplitting/estimateforcombibdt/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/estimateforcombibdt/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/estimateforcombibdt/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_Strip* .
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_Strip21MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_Strip21MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_Strip21MagDown.root MagDown Strip21
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_Strip21MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_Strip21MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_Strip21MagUp.root MagUp Strip21
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_Strip21r1MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_Strip21r1MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_Strip21r1MagDown.root MagDown Strip21r1
##
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_Strip21r1MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_Strip21r1MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuplesRun1/modifiedandcut
#end=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root
#beg2=modifiedandcut
#end2=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_
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
#beg3=../finaltuplesRun1/modifiedandcut
#end3=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root
#beg4=modifiedandcut
#end4=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuplesRun1/modifiedandcut
#end5=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM.root
#beg6=modifiedandcut
#end6=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done
###
##
#cd /vols/lhcb/ss4314/addPIDweights/
#cd estimateforcombibdt
#
#cd os
#
#rm finaltuplesRun1/*
#rm bin/*
#
#make
#
#cd bin
#
#
#
#cp /vols/lhcb/ss4314/misidsplitting/estimateforcombibdt/bin/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/estimateforcombibdt/bin/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/estimateforcombibdt/bin/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_Strip* .
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_Strip21MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_Strip21MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_Strip21MagDown.root MagDown Strip21
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_Strip21MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_Strip21MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_Strip21MagUp.root MagUp Strip21
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_Strip21r1MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_Strip21r1MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_Strip21r1MagDown.root MagDown Strip21r1
##
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_Strip21r1MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_Strip21r1MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuplesRun1/modifiedandcut
#end=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root
#beg2=modifiedandcut
#end2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_
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
#beg3=../finaltuplesRun1/modifiedandcut
#end3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root
#beg4=modifiedandcut
#end4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuplesRun1/modifiedandcut
#end5=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_CombBasic_MisidBasic_FitCorM.root
#beg6=modifiedandcut
#end6=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done


##----------------------ADD PID WEIGJTS after combi bdt--------##
#
#cd /vols/lhcb/ss4314/addPIDweights/
#cd estimateformisidbdt
#
#make
#
#rm finaltuplesRun1/*
#
#cd bin/
#
#cp /vols/lhcb/ss4314/misidsplitting/estimateformisidbdt/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/estimateformisidbdt/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/estimateformisidbdt/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_Strip* .
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_Strip21MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_Strip21MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_Strip21MagDown.root MagDown Strip21
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_Strip21MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_Strip21MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_Strip21MagUp.root MagUp Strip21
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_Strip21r1MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_Strip21r1MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_Strip21r1MagDown.root MagDown Strip21r1
##
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_Strip21r1MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_Strip21r1MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuplesRun1/modifiedandcut
#end=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_CombBasic_MisidBasic_FitCorM.root
#beg2=modifiedandcut
#end2=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_
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
#beg3=../finaltuplesRun1/modifiedandcut
#end3=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_CombBasic_MisidBasic_FitCorM.root
#beg4=modifiedandcut
#end4=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuplesRun1/modifiedandcut
#end5=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_CombBasic_MisidBasic_FitCorM.root
#beg6=modifiedandcut
#end6=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done
###
##
#cd /vols/lhcb/ss4314/addPIDweights/
#cd estimateformisidbdt
#
#cd os
#
#rm finaltuplesRun1/*
#rm bin/*
#
#make
#
#cd bin
#
#
#
#cp /vols/lhcb/ss4314/misidsplitting/estimateformisidbdt/bin/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/estimateformisidbdt/bin/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/estimateformisidbdt/bin/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_Strip* .
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_Strip21MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_Strip21MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_Strip21MagDown.root MagDown Strip21
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_Strip21MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_Strip21MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_Strip21MagUp.root MagUp Strip21
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_Strip21r1MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_Strip21r1MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_Strip21r1MagDown.root MagDown Strip21r1
##
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_Strip21r1MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_Strip21r1MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuplesRun1/modifiedandcut
#end=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_CombBasic_MisidBasic_FitCorM.root
#beg2=modifiedandcut
#end2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_
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
#beg3=../finaltuplesRun1/modifiedandcut
#end3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_CombBasic_MisidBasic_FitCorM.root
#beg4=modifiedandcut
#end4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuplesRun1/modifiedandcut
#end5=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_CombBasic_MisidBasic_FitCorM.root
#beg6=modifiedandcut
#end6=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035


#
#do
#
#        hadd $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done
#
##-------------DO MISID SPLITTING for Run1 2015 and 2016-----------#
#
cd /vols/lhcb/ss4314/misidsplitting
#
mkdir $trainingname
mkdir $tag
#
#
cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
cp $sourc/bin/*sh $desti/bin/
#
#
cp $sourc2/* $desti2/
cp -r $sourc2/src $desti2/
cp -r $sourc2/include $desti2/
mkdir $desti2/bin
mkdir $desti2/obj
mkdir $desti2/docs
cp $sourc2/bin/*sh $desti2/bin/
#
cd $trainingname
mkdir Run1
mkdir 2015
mkdir 2016

#
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


filename10=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename20=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename30=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME;
filename40=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename50=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename60=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename70=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME;
filename80=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME;

filename100=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename200=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename300=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME;
filename400=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename500=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename600=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename700=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME;
filename800=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME;




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


./main $path $VAR1 $VAR2 $filename100 $filename200 $filename300 $filename400
./main $path $VAR3 $VAR4 $filename100 $filename200 $filename300 $filename400
./main $path $VAR5 $VAR6 $filename100 $filename200 $filename300 $filename400
./main $path $VAR7 $VAR8 $filename100 $filename200 $filename300 $filename400

./main $path $VAR1 $VAR2 $filename500 $filename600 $filename700 $filename800
./main $path $VAR3 $VAR4 $filename500 $filename600 $filename700 $filename800
./main $path $VAR5 $VAR6 $filename500 $filename600 $filename700 $filename800
./main $path $VAR7 $VAR8 $filename500 $filename600 $filename700 $filename800


cp *tex ../2016/
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


filename10=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename20=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename30=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename40=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename50=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename60=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename70=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename80=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;

filename100=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename200=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename300=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename400=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename500=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename600=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename700=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename800=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;




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

./main $path $VAR1 $VAR2 $filename100 $filename200 $filename300 $filename400
./main $path $VAR3 $VAR4 $filename100 $filename200 $filename300 $filename400
./main $path $VAR5 $VAR6 $filename100 $filename200 $filename300 $filename400
./main $path $VAR7 $VAR8 $filename100 $filename200 $filename300 $filename400

./main $path $VAR1 $VAR2 $filename500 $filename600 $filename700 $filename800
./main $path $VAR3 $VAR4 $filename500 $filename600 $filename700 $filename800
./main $path $VAR5 $VAR6 $filename500 $filename600 $filename700 $filename800
./main $path $VAR7 $VAR8 $filename500 $filename600 $filename700 $filename800


cp *tex ../2016/
rm *tex



cp B23MuNuFake*total*root ../Run1/
cp B23MuNuFakeOS_2015_DV41r2*root ../2015/
cp B23MuNuFakeSS_2015_DV41r2*root ../2015/
cp B23MuNuFakeSS*2016*root ../2016/
cp B23MuNuFakeOS*2016*root ../2016/

cd /vols/lhcb/ss4314/misidsplitting/$tag
mkdir Run1
mkdir 2015
mkdir 2016

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
filename10=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM;
filename20=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM;
filename30=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM;
filename40=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM;
filename50=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM;
filename60=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM;
filename70=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM;
filename80=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM;

filename100=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM;
filename200=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM;
filename300=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM;
filename400=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM;
filename500=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM;
filename600=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM;
filename700=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM;
filename800=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM;


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


./main $path3 $VAR1 $VAR2 $filename100 $filename200 $filename300 $filename400
./main $path3 $VAR3 $VAR4 $filename100 $filename200 $filename300 $filename400
./main $path3 $VAR5 $VAR6 $filename100 $filename200 $filename300 $filename400
./main $path3 $VAR7 $VAR8 $filename100 $filename200 $filename300 $filename400

./main $path3 $VAR1 $VAR2 $filename500 $filename600 $filename700 $filename800
./main $path3 $VAR3 $VAR4 $filename500 $filename600 $filename700 $filename800
./main $path3 $VAR5 $VAR6 $filename500 $filename600 $filename700 $filename800
./main $path3 $VAR7 $VAR8 $filename500 $filename600 $filename700 $filename800


cp *tex ../2016/
rm *tex




cp B23MuNuFake*total*root ../Run1/
cp B23MuNuFakeOS_2015_DV41r2*root ../2015/
cp B23MuNuFakeSS_2015_DV41r2*root ../2015/
cp B23MuNuFakeSS*2016*root ../2016/
cp B23MuNuFakeOS*2016*root ../2016/


#

#---------------------------------ADD weights-----------------------#

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
#mkdir $desti/finaltuplesRun1
#mkdir $desti/finaltuples2015
#cp $sourc/bin/*sh $desti/bin/
#
#
#cp $sourc2/* $desti2/
#cp -r $sourc2/src $desti2/
#cp -r $sourc2/include $desti2/
#mkdir $desti2/bin
#mkdir $desti2/obj
#mkdir $desti2/docs
#mkdir $desti2/finaltuplesRun1
#mkdir $desti2/finaltuples2015
#cp $sourc2/bin/*sh $desti2/bin/
#
#cd $trainingname
#
#
#rm bin/*
#
#make
#
#cd bin



#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/Run1/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/Run1/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/Run1/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
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
#beg=../finaltuplesRun1/modifiedandcut
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
#beg3=../finaltuplesRun1/modifiedandcut
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
#beg5=../finaltuplesRun1/modifiedandcut
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
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/Run1/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/Run1/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/Run1/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
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
#beg=../finaltuplesRun1/modifiedandcut
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
#beg3=../finaltuplesRun1/modifiedandcut
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
#beg5=../finaltuplesRun1/modifiedandcut
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

#--------------------------ADD weights for OS-------------------#

#cd /vols/lhcb/ss4314/addPIDweights/
#
#mkdir $trainingname
#mkdir $tag

#sourc=FUMSB_simultaneous_symmetric_newcontrolchannel_nojackweight #for now CHANGE THIS


#cp $sourc/* $desti/
#cp -r $sourc/src $desti/
#cp -r $sourc/include $desti/
#mkdir $desti/bin
#mkdir $desti/obj
#mkdir $desti/docs
#mkdir $desti/finaltuplesRun1
#mkdir $desti/finaltuples2015
#cp $sourc/bin/*sh $desti/bin/
#
#
#cp $sourc2/* $desti2/
#cp -r $sourc2/src $desti2/
#cp -r $sourc2/include $desti2/
#mkdir $desti2/bin
#mkdir $desti2/obj
#mkdir $desti2/docs
#mkdir $desti2/finaltuplesRun1
#mkdir $desti2/finaltuples2015
#cp $sourc2/bin/*sh $desti2/bin/

#cd $trainingname
#
#cd os
#
#rm finaltuplesRun1/*
#rm bin/*
#
#make
#
#cd bin
#
#
#
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root MagDown Strip21
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root MagUp Strip21
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root MagDown Strip21r1
##
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuplesRun1/modifiedandcut
#end=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg2=modifiedandcut
#end2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_
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
#beg3=../finaltuplesRun1/modifiedandcut
#end3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg4=modifiedandcut
#end4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuplesRun1/modifiedandcut
#end5=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg6=modifiedandcut
#end6=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_
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
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root MagDown Strip21
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root MagUp Strip21
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root MagDown Strip21r1
##
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuplesRun1/modifiedandcut
#end=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg2=modifiedandcut
#end2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_
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
#beg3=../finaltuplesRun1/modifiedandcut
#end3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg4=modifiedandcut
#end4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuplesRun1/modifiedandcut
#end5=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg6=modifiedandcut
#end6=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done


#cd $tag
#
#cd os
#
#rm finaltuplesRun1/*
#rm bin/*
#
#make
#
#cd bin
#
#
#
#cp /vols/lhcb/ss4314/misidsplitting/$tag/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$tag/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$tag/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root MagDown Strip21
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root MagUp Strip21
#
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root MagDown Strip21r1
##
#./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuplesRun1/modifiedandcut
#end=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root
#beg2=modifiedandcut
#end2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_
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
#beg3=../finaltuplesRun1/modifiedandcut
#end3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root
#beg4=modifiedandcut
#end4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuplesRun1/modifiedandcut
#end5=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM.root
#beg6=modifiedandcut
#end6=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done

##--------------------------Remove all and add 2015------------------#


#cd /vols/lhcb/ss4314/addPIDweights/
#
#mkdir $trainingname
#mkdir $tag


#
#rm *
#
#cd ../
#
#make 
#
#cd bin/
#
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root MagDown Strip21
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root MagUp Strip21
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root MagDown Strip21r1
##
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuples2015/modifiedandcut
#end=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg2=modifiedandcut
#end2=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_
#
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#	hadd -f $beg$tags$end $beg2$tags$var1$end2$var1.root $beg2$tags$var2$end2$var2.root $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 
#
#done
#
#beg3=../finaltuples2015/modifiedandcut
#end3=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg4=modifiedandcut
#end4=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd -f $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuples2015/modifiedandcut
#end5=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg6=modifiedandcut
#end6=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd -f $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done
#
#
#
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root MagDown Strip21
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root MagUp Strip21
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root MagDown Strip21r1
##
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuples2015/modifiedandcut
#end=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg2=modifiedandcut
#end2=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_
#
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#	hadd -f $beg$tags$end $beg2$tags$var1$end2$var1.root $beg2$tags$var2$end2$var2.root $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 
#
#done
#
#beg3=../finaltuples2015/modifiedandcut
#end3=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg4=modifiedandcut
#end4=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd -f $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuples2015/modifiedandcut
#end5=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg6=modifiedandcut
#end6=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd -f $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done


#cd /vols/lhcb/ss4314/addPIDweights/
#cd $tag
#
#make
#
#rm finaltuplesRun1/*
#
#cd bin/
#
#cp /vols/lhcb/ss4314/misidsplitting/$tag/Run1/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$tag/Run1/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$tag/Run1/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root MagDown Strip21
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root MagUp Strip21
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root MagDown Strip21r1
##
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuplesRun1/modifiedandcut
#end=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root
#beg2=modifiedandcut
#end2=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_
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
#beg3=../finaltuplesRun1/modifiedandcut
#end3=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root
#beg4=modifiedandcut
#end4=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuplesRun1/modifiedandcut
#end5=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM.root
#beg6=modifiedandcut
#end6=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done
##
#

##---------------------------------------2015 SS working vs------------------------#
#cd /vols/lhcb/ss4314/addPIDweights/
#cd $tag
#
##cd ../
#
#make 
#
#rm finaltuples2015/*
#
#cd bin/
#
#cp /vols/lhcb/ss4314/misidsplitting/$tag/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$tag/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$tag/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root MagDown Strip21
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root MagUp Strip21
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root MagDown Strip21r1
##
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuples2015/modifiedandcut
#end=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root
#beg2=modifiedandcut
#end2=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_
#
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#	hadd  $beg$tags$end $beg2$tags$var1$end2$var1.root $beg2$tags$var2$end2$var2.root $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 
#
#done
#
#beg3=../finaltuples2015/modifiedandcut
#end3=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root
#beg4=modifiedandcut
#end4=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd  $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuples2015/modifiedandcut
#end5=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM.root
#beg6=modifiedandcut
#end6=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd  $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done
#
#
#--------------------------OS 2015 working vs------------------------------------------------#
#
#cd /vols/lhcb/ss4314/addPIDweights/
#cd $tag
#
#cd os
#
#rm finaltuples2015/*
#rm bin/*
#
#make
#
#cd bin
#
#cp /vols/lhcb/ss4314/misidsplitting/$tag/2015/B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$tag/2015/B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$tag/2015/B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#
#./mainforos B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root MagDown Strip21
#
#./mainforos B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root MagUp Strip21
#
#./mainforos B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root MagDown Strip21r1
##
#./mainforos B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuples2015/modifiedandcut
#end=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root
#beg2=modifiedandcut
#end2=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_
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
#beg3=../finaltuples2015/modifiedandcut
#end3=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root
#beg4=modifiedandcut
#end4=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuples2015/modifiedandcut
#end5=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM.root
#beg6=modifiedandcut
#end6=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done


###--------------------------Remove all and add 2015 working version simultaneous------------------#
#
#cd /vols/lhcb/ss4314/addPIDweights/
#cd $trainingname
#
#rm finaltuples2015/*
##
##cd ../
##
#make 
##
#cd bin/
#
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root MagDown Strip21
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root MagUp Strip21
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root MagDown Strip21r1
##
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuples2015/modifiedandcut
#end=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg2=modifiedandcut
#end2=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_
#
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#	hadd -f $beg$tags$end $beg2$tags$var1$end2$var1.root $beg2$tags$var2$end2$var2.root $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 
#
#done
#
#beg3=../finaltuples2015/modifiedandcut
#end3=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg4=modifiedandcut
#end4=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd -f $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuples2015/modifiedandcut
#end5=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg6=modifiedandcut
#end6=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd -f $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done
#
#
#
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root MagDown Strip21
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root MagUp Strip21
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root MagDown Strip21r1
##
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuples2015/modifiedandcut
#end=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg2=modifiedandcut
#end2=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_
#
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#	hadd -f $beg$tags$end $beg2$tags$var1$end2$var1.root $beg2$tags$var2$end2$var2.root $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 
#
#done
#
#beg3=../finaltuples2015/modifiedandcut
#end3=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg4=modifiedandcut
#end4=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd -f $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuples2015/modifiedandcut
#end5=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg6=modifiedandcut
#end6=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd -f $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done

##----------------------------Add OS 2015 sim----------------------------------------------## 
#
#cd /vols/lhcb/ss4314/addPIDweights/
#cd $trainingname
#
#cd os
#rm finaltuples2015/*
##
##cd ../
##
#make 
##
#cd bin/
#
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
#
#./mainforos B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root MagDown Strip21
#
#./mainforos B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root MagUp Strip21
#
#./mainforos B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root MagDown Strip21r1
##
#./mainforos B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuples2015/modifiedandcut
#end=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg2=modifiedandcut
#end2=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_
#
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#	hadd -f $beg$tags$end $beg2$tags$var1$end2$var1.root $beg2$tags$var2$end2$var2.root $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 
#
#done
#
#beg3=../finaltuples2015/modifiedandcut
#end3=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg4=modifiedandcut
#end4=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd -f $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuples2015/modifiedandcut
#end5=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
#beg6=modifiedandcut
#end6=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd -f $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done
#
#
#
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$trainingname/2015/B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#
#./mainforos B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root MagDown Strip21
#
#./mainforos B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root MagUp Strip21
#
#./mainforos B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root MagDown Strip21r1
##
#./mainforos B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuples2015/modifiedandcut
#end=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg2=modifiedandcut
#end2=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_
#
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#	hadd -f $beg$tags$end $beg2$tags$var1$end2$var1.root $beg2$tags$var2$end2$var2.root $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 
#
#done
#
#beg3=../finaltuples2015/modifiedandcut
#end3=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg4=modifiedandcut
#end4=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd -f $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuples2015/modifiedandcut
#end5=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
#beg6=modifiedandcut
#end6=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd -f $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done
#
#cd /vols/lhcb/ss4314/addPIDweights/
#cd $tag
#
#make
#
#rm finaltuplesRun1/*
#
#cd bin/
#
#cp /vols/lhcb/ss4314/misidsplitting/$tag/Run1/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$tag/Run1/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$tag/Run1/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root MagDown Strip21
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root MagUp Strip21
#
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root MagDown Strip21r1
##
#./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuplesRun1/modifiedandcut
#end=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root
#beg2=modifiedandcut
#end2=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_
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
#beg3=../finaltuplesRun1/modifiedandcut
#end3=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root
#beg4=modifiedandcut
#end4=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuplesRun1/modifiedandcut
#end5=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM.root
#beg6=modifiedandcut
#end6=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done
##
#
#cd /vols/lhcb/ss4314/addPIDweights/
#cd $tag
#
##cd ../
#
#make 
#
#rm finaltuples2015/*
#
#cd bin/
#
#cp /vols/lhcb/ss4314/misidsplitting/$tag/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$tag/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#cp /vols/lhcb/ss4314/misidsplitting/$tag/2015/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root MagDown Strip21
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root MagUp Strip21
#
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root MagDown Strip21r1
##
#./main B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root MagUp Strip21r1
##
#this=Basiccut
#var1=Strip21r1MagDown
#var2=Strip21r1MagUp
#var3=Strip21MagDown
#var4=Strip21MagUp
#beg=../finaltuples2015/modifiedandcut
#end=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root
#beg2=modifiedandcut
#end2=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_
#
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#	hadd  $beg$tags$end $beg2$tags$var1$end2$var1.root $beg2$tags$var2$end2$var2.root $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 
#
#done
#
#beg3=../finaltuples2015/modifiedandcut
#end3=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root
#beg4=modifiedandcut
#end4=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd  $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root
#
#done
#
#beg5=../finaltuples2015/modifiedandcut
#end5=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM.root
#beg6=modifiedandcut
#end6=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_
#
#for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035
#
#do
#
#        hadd  $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root
#
#done

##----------------------------------CUT ON PROBNNMU---------------#
#
#cd /vols/lhcb/ss4314/cutonProbnnmu
#
##mkdir $trainingname
##mkdir $tag
#
#
##cp $sourc/* $desti/
##cp -r $sourc/src $desti/
##cp -r $sourc/include $desti/
##mkdir $desti/bin
##mkdir $desti/obj
##mkdir $desti/docs
##
##
##cp $sourc2/* $desti2/
##cp -r $sourc2/src $desti2/
##cp -r $sourc2/include $desti2/
##mkdir $desti2/bin
##mkdir $desti2/obj
##mkdir $desti2/docs
#
#cd $trainingname
#
#
##hadd haddtuples/JpsiKdata_HighFCME.root bin/B2JpsiKD*_HighFCME.root
##hadd haddtuples/JpsiKdata_LowFCME.root bin/B2JpsiKD*_LowFCME.root
##hadd haddtuples/finaldata_HighFCME.root bin/Data2012and2011_corrmFUMSB*_HighFCME.root bin/Data2012and2011_corrmLSDfull*_HighFCME.root bin/B23MuNuData_2015_corrmLSDfull*HighFCME.root 
##hadd haddtuples/finaldata_LowFCME.root  bin/Data2012and2011_corrmFUMSB*_LowFCME.root bin/Data2012and2011_corrmLSDfull*_LowFCME.root bin/B23MuNuData_2015_corrmLSDfull*LowFCME.root
##
#cd /vols/lhcb/ss4314/cutonProbnnmu
##
#mkdir $trainingname
#mkdir $tag
##
##
###cp $sourc/* $desti/
###cp -r $sourc/src $desti/
###cp -r $sourc/include $desti/
###mkdir $desti/bin
###mkdir $desti/obj
###mkdir $desti/docs
###
###
###cp $sourc2/* $desti2/
###cp -r $sourc2/src $desti2/
###cp -r $sourc2/include $desti2/
###mkdir $desti2/bin
###mkdir $desti2/obj
###mkdir $desti2/docs
##
#cd $trainingname
##
#make clean
#make
##
#cd bin
##
#./main2 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/
##
#latex EfficienciesProbnnmu3.tex
##
#mkdir ~/public_html/cutonProbnnmu
#mkdir ~/public_html/cutonProbnnmu/$trainingname
##
##
#cp *pdf ~/public_html/cutonProbnnmu/$trainingname/
#
#cd ../
#mkdir haddtuples
#rm haddtuples/*root
#
#echo "Making Tuples for Signal and Control Fits"
#hadd haddtuples/JpsiKdata_Run1_HighFCME.root bin/B2JpsiKDataDetached2012*_HighFCME*.root bin/B2JpsiKDetachedData_2011*_HighFCME*.root
#hadd haddtuples/JpsiKdata_Run1_LowFCME.root  bin/B2JpsiKDataDetached2012*_LowFCME*.root bin/B2JpsiKDetachedData_2011*_LowFCME*.root
#hadd haddtuples/JpsiKdata_2015_HighFCME.root bin/B2JpsiKDataDetached2015*_HighFCME*.root
#hadd haddtuples/JpsiKdata_2015_LowFCME.root  bin/B2JpsiKDataDetached2015*_LowFCME*.root
#
#hadd haddtuples/finaldata_HighFCME.root bin/Data2012and2011_corrmFUMSB*_HighFCME*.root bin/Data2012and2011_corrmLSDfull*_HighFCME*.root bin/B23MuNuData_2015_corrmLSDfull*HighFCME*.root 
#hadd haddtuples/finaldata_LowFCME.root  bin/Data2012and2011_corrmFUMSB*_LowFCME*.root bin/Data2012and2011_corrmLSDfull*_LowFCME*.root bin/B23MuNuData_2015_corrmLSDfull*LowFCME*.root


#hadd haddtuples/finaldata_Run1_HighFCME.root bin/Data2012and2011_corrmFUMSB*_HighFCME*.root bin/Data2012and2011_corrmLSDfull*_HighFCME*.root  
#hadd haddtuples/finaldata_Run1_LowFCME.root  bin/Data2012and2011_corrmFUMSB*_LowFCME*.root bin/Data2012and2011_corrmLSDfull*_LowFCME*.root

##
##
#cd /vols/lhcb/ss4314/cutonProbnnmu
##
#cd $tag
##
#make clean
#make
#
##
#cd bin 
##
##
#./main2 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/
##
##
#latex EfficienciesProbnnmu3.tex
##
#mkdir ~/public_html/cutonProbnnmu
#mkdir ~/public_html/cutonProbnnmu/$tag
##
##
#cp *pdf ~/public_html/cutonProbnnmu/$tag/
#
#cd ../
#mkdir haddtuples
#rm haddtuples/*root
#
#hadd haddtuples/JpsiKdata_Run1.root bin/B2JpsiKDataDetached2012* bin/B2JpsiKDetachedData_2011*
#hadd haddtuples/JpsiKdata_2015.root bin/B2JpsiKDataDetached2015*
#
#echo "Making Tuples for Signal and Control Fits"
#
#hadd haddtuples/finaldata.root bin/Data2012and2011_corrmFUMSB*.root bin/Data2012and2011_corrmLSDfull*.root bin/B23MuNuData_2015_corrmLSDfull*.root

#hadd haddtuples/finaldata_Run1.root bin/Data2012and2011_corrmFUMSB*.root bin/Data2012and2011_corrmLSDfull*.root 
#
#
##------------------------add PID weights to MC--------------------#
#
#
#cd /vols/lhcb/ss4314/preparesignalweights/
#
#mkdir preparesignalweights_$trainingname
#mkdir preparesignalweights_$tag
#
#sourc=preparesignalweights_simultaneous_symmetric_newcontrolchannel
#sourc2=preparesignalweights_NOTsimultaneous_newcontrolchannel
#desti=preparesignalweights_$trainingname
#desti2=preparesignalweights_$tag
#
#
##cp $sourc/* $desti/
##cp -r $sourc/src $desti/
##cp -r $sourc/include $desti/
##mkdir $desti/bin
##mkdir $desti/obj
##mkdir $desti/docs
#
#
#
##cp $sourc2/* $desti2/
##cp -r $sourc2/src $desti2/
##cp -r $sourc2/include $desti2/
##mkdir $desti2/bin
##mkdir $desti2/obj
##mkdir $desti2/docs
#
#
#Cd preparesignalweights_$trainingname
#
#KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
#Export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
#
#Make
#
#Cd bin
#
#./main Strip21 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME B23MuNuMC2012
#./main Strip21 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME B23MuNuMC2012
#
#./main Strip21 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME B23MuNuMC2015
#./main Strip21 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME B23MuNuMC2015
#
#
#Latex EfficienciesPIDreweightingStrip21LowFCMEB23MuNuMC2012.tex
#Latex EfficienciesPIDreweightingStrip21HighFCMEB23MuNuMC2012.tex
#Latex EfficienciesPIDreweightingStrip21LowFCMEB23MuNuMC2015.tex
#Latex EfficienciesPIDreweightingStrip21HighFCMEB23MuNuMC2015.tex
#
#
#Mkdir ~/public_html/preparesignalweights/
#Mkdir ~/public_html/preparesignalweights/preparesignalweights_$trainingname
#
#Cp *pdf ~/public_html/preparesignalweights/preparesignalweights_$trainingname/
#
#Cd /vols/lhcb/ss4314/preparesignalweights/preparesignalweights_$tag
#
#Make
#
#Cd bin
#
#./main Strip21 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2012
#
#./main Strip21 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2015
#
#Mkdir ~/public_html/preparesignalweights/preparesignalweights_$tag/
#
#Latex EfficienciesPIDreweightingStrip21B23MuNuMC2012.tex
#Latex EfficienciesPIDreweightingStrip21B23MuNuMC2015.tex
#
#Cp *pdf ~/public_html/preparesignalweights/preparesignalweights_$tag/


##---------ADD PID WEIGHTS to control channel-----------#
#
#
#cd /vols/lhcb/ss4314/preparecontrolweights/
#
#mkdir preparecontrolweights_$trainingname
#mkdir preparecontrolweights_$tag
#
#sourc=preparecontrolweights_simultaneous_symmetric_newcontrolchannel
#sourc2=preparecontrolweights_NOTsimultaneous_newcontrolchannel
#desti=preparecontrolweights_$trainingname
#desti2=preparecontrolweights_$tag
#
#
##cp $sourc/* $desti/
##cp -r $sourc/src $desti/
##cp -r $sourc/include $desti/
##mkdir $desti/bin
##mkdir $desti/obj
##mkdir $desti/docs
##
##
##
##cp $sourc2/* $desti2/
##cp -r $sourc2/src $desti2/
##cp -r $sourc2/include $desti2/
##mkdir $desti2/bin
##mkdir $desti2/obj
##mkdir $desti2/docs
#
#cd preparecontrolweights_$trainingname
##
#KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
# 
#make
#
#cd bin
#
#
#
#./main Strip21 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/JpsiKMCDetachedLine_2012_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root JpsiKMCDetachedLine_2012_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME JpsiKMC2012
#./main Strip21 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/JpsiKMCDetachedLine_2012_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root JpsiKMCDetachedLine_2012_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME JpsiKMC2012
#./main Strip21 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME JpsiKMC2015
#./main Strip21 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME JpsiKMC2015
#
#
#
#latex EfficienciesPIDreweightingStrip21LowFCMEJpsiKMC2012.tex
#latex EfficienciesPIDreweightingStrip21HighFCMEJpsiKMC2012.tex
#latex EfficienciesPIDreweightingStrip21LowFCMEJpsiKMC2015.tex
#latex EfficienciesPIDreweightingStrip21HighFCMEJpsiKMC2015.tex
#
#
#mkdir ~/public_html/preparecontrolweights/
#mkdir ~/public_html/preparecontrolweights/preparecontrolweights_$trainingname
#
#cp *pdf ~/public_html/preparecontrolweights/preparecontrolweights_$trainingname/
#
#
#
#
#
#
#
#cd /vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_$tag
#
#make
#
#cd bin
#
#./main Strip21 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/JpsiKMCDetachedLine_2012_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root JpsiKMCDetachedLine_2012_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root JpsiKMC2012
#
#mkdir ~/public_html/preparecontrolweights/preparecontrolweights_$tag/
#
#latex EfficienciesPIDreweightingStrip21JpsiKMC2012.tex
#
#cp *pdf ~/public_html/preparecontrolweights/preparecontrolweights_$tag/
#
#
#./main Strip21 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root  JpsiKMC2015
#
#
#mkdir ~/public_html/preparecontrolweights/preparecontrolweights_$tag/
#
#latex EfficienciesPIDreweightingStrip21JpsiKMC2015.tex
#
#cp *pdf ~/public_html/preparecontrolweights/preparecontrolweights_$tag/

