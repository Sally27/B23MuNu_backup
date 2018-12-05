trainingname=FUMSB_simultaneous_add2016 #NEW simultaneous year
tag=FUMSB_NOTsimultaneous_add2016 #NEW NOT simultaneous year
tn=_scalesig


#------------------------add PID weights to MC--------------------#


cd /vols/lhcb/ss4314/preparesignalweights/

mkdir preparesignalweights_$trainingname$tn
mkdir preparesignalweights_$tag$tn


KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

cd /vols/lhcb/ss4314/preparesignalweights/preparesignalweights_$tag$tn
#
make
#
cd bin
#
./main Strip21 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2012
#
./main Strip21 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2015

./main Strip21 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2016
#
mkdir ~/public_html/preparesignalweights/preparesignalweights_$tag$tn/
#
latex EfficienciesPIDreweightingStrip21B23MuNuMC2012.tex
latex EfficienciesPIDreweightingStrip21B23MuNuMC2015.tex
latex EfficienciesPIDreweightingStrip21B23MuNuMC2016.tex
#
mkdir ~/public_html/preparesignalweights/preparesignalweights_$tag$tn
cp *pdf ~/public_html/preparesignalweights/preparesignalweights_$tag$tn/

