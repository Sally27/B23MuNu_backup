
trainingname=FUMSB_simultaneous_add2016 #NEW simultaneous year
tag=FUMSB_NOTsimultaneous_add2016 #NEW NOT simultaneous year
tn=_scalesig


#------------------------add PID weights to MC--------------------#


cd /vols/lhcb/ss4314/preparesignalweights/

mkdir preparesignalweights_$trainingname$tn
mkdir preparesignalweights_$tag$tn

#sourc=preparesignalweights_$trainingname
#sourc2=preparesignalweights_$tag
#desti=preparesignalweights_$trainingname$tn
#desti2=preparesignalweights_$tag$tn
#
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


cd preparesignalweights_$trainingname$tn
##
KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
#
rm bin/*

make
#
cd bin
#
./main Strip21 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME B23MuNuMC2012
./main Strip21 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME B23MuNuMC2012
#
./main Strip23_MCTuneV1 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME B23MuNuMC2015
./main Strip23_MCTuneV1 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME B23MuNuMC2015

./main Strip26 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME B23MuNuMC2016
./main Strip26 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME B23MuNuMC2016



#
#
latex EfficienciesPIDreweightingStrip21LowFCMEB23MuNuMC2012.tex
latex EfficienciesPIDreweightingStrip21HighFCMEB23MuNuMC2012.tex
latex EfficienciesPIDreweightingStrip23_MCTuneV1LowFCMEB23MuNuMC2015.tex
latex EfficienciesPIDreweightingStrip23_MCTuneV1HighFCMEB23MuNuMC2015.tex
latex EfficienciesPIDreweightingStrip26LowFCMEB23MuNuMC2016.tex
latex EfficienciesPIDreweightingStrip26HighFCMEB23MuNuMC2016.tex

#
#
mkdir ~/public_html/preparesignalweights/
mkdir ~/public_html/preparesignalweights/preparesignalweights_$trainingname$tn
#
cp *pdf ~/public_html/preparesignalweights/preparesignalweights_$trainingname$tn/
mkdir ../haddtuples
rm ../haddtuples/*

hadd ../haddtuples/B23MuNuMCAll_LowFCME.root B23MuNuMC2012NNmumore03Strip21LowFCME.root B23MuNuMC2015NNmumore03Strip23_MCTuneV1LowFCME.root B23MuNuMC2016NNmumore03Strip26LowFCME.root
hadd ../haddtuples/B23MuNuMCAll_HighFCME.root B23MuNuMC2012NNmumore03Strip21HighFCME.root B23MuNuMC2015NNmumore03Strip23_MCTuneV1HighFCME.root B23MuNuMC2016NNmumore03Strip26HighFCME.root
hadd ../haddtuples/B23MuNuMCAll_onlyRun1and2015_LowFCME.root B23MuNuMC2012NNmumore03Strip21LowFCME.root B23MuNuMC2015NNmumore03Strip23_MCTuneV1LowFCME.root
hadd ../haddtuples/B23MuNuMCAll_onlyRun1and2015_HighFCME.root B23MuNuMC2012NNmumore03Strip21HighFCME.root B23MuNuMC2015NNmumore03Strip23_MCTuneV1HighFCME.root
hadd ../haddtuples/B23MuNuMCAll_onlyRun1_LowFCME.root B23MuNuMC2012NNmumore03Strip21LowFCME.root
hadd ../haddtuples/B23MuNuMCAll_onlyRun1_HighFCME.root B23MuNuMC2012NNmumore03Strip21HighFCME.root
#

#
##-------------------DO the tag art-----------------------------------#
#
#cd /vols/lhcb/ss4314/preparesignalweights/preparesignalweights_$tag$tn
##
#rm bin/*
#make
##
#cd bin
##
#./main Strip21 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2012
##
#./main Strip23_MCTuneV1 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2015
#
#./main Strip26 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2016
##
#mkdir ~/public_html/preparesignalweights/preparesignalweights_$tag/
##
#latex EfficienciesPIDreweightingStrip21B23MuNuMC2012.tex
#latex EfficienciesPIDreweightingStrip23_MCTuneV1B23MuNuMC2015.tex
#latex EfficienciesPIDreweightingStrip26B23MuNuMC2016.tex
##
#mkdir ~/public_html/preparesignalweights/preparesignalweights_$tag$tn
#cp *pdf ~/public_html/preparesignalweights/preparesignalweights_$tag$tn/
#
#mkdir ../haddtuples
#rm ../haddtuples/*
#
#hadd ../haddtuples/B23MuNuMCAll.root B23MuNuMC2012NNmumore03Strip21.root B23MuNuMC2015NNmumore03Strip23_MCTuneV1.root B23MuNuMC2016NNmumore03Strip26.root
#
#hadd ../haddtuples/B23MuNuMCAll_onlyRun1and2015.root B23MuNuMC2012NNmumore03Strip21.root B23MuNuMC2015NNmumore03Strip23_MCTuneV1.root
#hadd ../haddtuples/B23MuNuMCAll_onlyRun1.root B23MuNuMC2012NNmumore03Strip21.root
