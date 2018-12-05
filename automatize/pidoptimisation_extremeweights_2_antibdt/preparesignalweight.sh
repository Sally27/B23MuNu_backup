
#simold=FUMSB_simultaneous_add2016_scalesig
#notsimold=FUMSB_NOTsimultaneous_add2016_scalesig
sim=FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights #NEW simultaneous year
notsim=FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights #NEW NOT simultaneous year
notsimPID=FUMSB_NOTsimultaneous_NewTCK #NEW NOT simultaneous year


#------------------------add PID weights to MC--------------------#


cd /vols/lhcb/ss4314/preparesignalweights/

#mkdir preparesignalweights_$sim
#mkdir preparesignalweights_$notsim
#
#sourc=preparesignalweights_$simold
#sourc2=preparesignalweights_$notsimold
#desti=preparesignalweights_$sim
#desti2=preparesignalweights_$notsim
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


#cd preparesignalweights_$sim
####
KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
#
ERR_PATH=/vols/lhcb/ss4314/error_library/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ERR_PATH
#
##
#rm bin/*
#SetupProject Urania v5r0
#make
##
#cd bin
##
#./main Strip21 /vols/lhcb/ss4314/cutonFCME/$sim/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME B23MuNuMC2012
#./main Strip21 /vols/lhcb/ss4314/cutonFCME/$sim/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME B23MuNuMC2012
##
##./main Strip23_MCTuneV1 /vols/lhcb/ss4314/cutonFCME/$sim/bin/B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME B23MuNuMC2015
##./main Strip23_MCTuneV1 /vols/lhcb/ss4314/cutonFCME/$sim/bin/B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME B23MuNuMC2015
#
#./main Turbo16 /vols/lhcb/ss4314/cutonFCME/$sim/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME B23MuNuMC2016
#./main Turbo16 /vols/lhcb/ss4314/cutonFCME/$sim/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME B23MuNuMC2016
#
#
#
##
##
#latex EfficienciesPIDreweightingStrip21LowFCMEB23MuNuMC2012.tex
#latex EfficienciesPIDreweightingStrip21HighFCMEB23MuNuMC2012.tex
##latex EfficienciesPIDreweightingStrip23_MCTuneV1LowFCMEB23MuNuMC2015.tex
##latex EfficienciesPIDreweightingStrip23_MCTuneV1HighFCMEB23MuNuMC2015.tex
#latex EfficienciesPIDreweightingTurbo16LowFCMEB23MuNuMC2016.tex
#latex EfficienciesPIDreweightingTurbo16HighFCMEB23MuNuMC2016.tex
#
##
##
#mkdir ~/public_html/preparesignalweights/
#mkdir ~/public_html/preparesignalweights/preparesignalweights_$sim
##
#cp *pdf ~/public_html/preparesignalweights/preparesignalweights_$sim/
#mkdir ../haddtuples
#rm ../haddtuples/*
#
#hadd ../haddtuples/B23MuNuMCAll_LowFCME.root B23MuNuMC2012NNmumore03Strip21LowFCME_selected.root B23MuNuMC2016BasiccutTurbo16LowFCME_selected.root
#hadd ../haddtuples/B23MuNuMCAll_HighFCME.root B23MuNuMC2012NNmumore03Strip21HighFCME_selected.root B23MuNuMC2016BasiccutTurbo16HighFCME_selected.root
##hadd ../haddtuples/B23MuNuMCAll_onlyRun1and2015_LowFCME.root B23MuNuMC2012NNmumore03Strip21LowFCME.root B23MuNuMC2015NNmumore03Strip23_MCTuneV1LowFCME.root
##hadd ../haddtuples/B23MuNuMCAll_onlyRun1and2015_HighFCME.root B23MuNuMC2012NNmumore03Strip21HighFCME.root B23MuNuMC2015NNmumore03Strip23_MCTuneV1HighFCME.root
#hadd ../haddtuples/B23MuNuMCAll_onlyRun1_LowFCME.root B23MuNuMC2012NNmumore03Strip21LowFCME_selected.root
#hadd ../haddtuples/B23MuNuMCAll_onlyRun1_HighFCME.root B23MuNuMC2012NNmumore03Strip21HighFCME_selected.root
##


#-------------------DO the tag art-----------------------------------#

cd /vols/lhcb/ss4314/preparesignalweights/preparesignalweights_$notsim
#
rm bin/*
make
#
cd bin
#
./main Strip21 /vols/lhcb/ss4314/cutonFitRange/$notsimPID/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2012
#
#./main Strip23_MCTuneV1 /vols/lhcb/ss4314/cutonFitRange/$notsim/bin/B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2015

./main Turbo16 /vols/lhcb/ss4314/cutonFitRange/$notsimPID/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2016
#
mkdir ~/public_html/preparesignalweights/preparesignalweights_$notsim/
#
latex EfficienciesPIDreweightingStrip21B23MuNuMC2012.tex
#latex EfficienciesPIDreweightingStrip23_MCTuneV1B23MuNuMC2015.tex
latex EfficienciesPIDreweightingTurbo16B23MuNuMC2016.tex
#
mkdir ~/public_html/preparesignalweights/preparesignalweights_$notsim
cp *pdf ~/public_html/preparesignalweights/preparesignalweights_$notsim/

mkdir ../haddtuples
rm ../haddtuples/*

#hadd ../haddtuples/B23MuNuMCAll.root B23MuNuMC2012NNmumore03Strip21_selected.root B23MuNuMC2016BasiccutTurbo16_selected.root

#hadd ../haddtuples/B23MuNuMCAll_onlyRun1and2015.root B23MuNuMC2012NNmumore03Strip21.root B23MuNuMC2015NNmumore03Strip23_MCTuneV1.root
#hadd ../haddtuples/B23MuNuMCAll_onlyRun1.root B23MuNuMC2012NNmumore03Strip21_selected.root
