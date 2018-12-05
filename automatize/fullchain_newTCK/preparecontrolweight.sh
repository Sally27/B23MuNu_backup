
simold=FUMSB_simultaneous_add2016_scalesig
notsimold=FUMSB_NOTsimultaneous_add2016_scalesig
sim=FUMSB_simultaneous_NewTCK #NEW simultaneous year
notsim=FUMSB_NOTsimultaneous_NewTCK #NEW NOT simultaneous year



#------------------------add PID weights to MC--------------------#




#sourc=preparecontrolweights_$simold
#sourc2=preparecontrolweights_$notsimold
#desti=preparecontrolweights_$sim
#desti2=preparecontrolweights_$notsim
##---------ADD PID WEIGHTS to control channel-----------#
#
#
cd /vols/lhcb/ss4314/preparecontrolweights/
#
mkdir preparecontrolweights_$sim
mkdir preparecontrolweights_$notsim
#
#
#
#cp $sourc/* $desti/
#cp -r $sourc/src $desti/
#cp -r $sourc/include $desti/
#mkdir $desti/bin
#mkdir $desti/obj
#mkdir $desti/docs
##
##
##
#cp $sourc2/* $desti2/
#cp -r $sourc2/src $desti2/
#cp -r $sourc2/include $desti2/
#mkdir $desti2/bin
#mkdir $desti2/obj
#mkdir $desti2/docs

cd preparecontrolweights_$sim
##
KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH


ERR_PATH=/vols/lhcb/ss4314/error_library/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ERR_PATH

 
SetupProject Urania v5r0

make clean
rm bin/*
make

cd bin



./main Strip21 /vols/lhcb/ss4314/cutonFCME/$sim/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME JpsiKMC2012
./main Strip21 /vols/lhcb/ss4314/cutonFCME/$sim/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME JpsiKMC2012
#./main Strip23_MCTuneV1 /vols/lhcb/ss4314/cutonFCME/$sim/bin/JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME JpsiKMC2015
#./main Strip23_MCTuneV1 /vols/lhcb/ss4314/cutonFCME/$sim/bin/JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME JpsiKMC2015
./main Turbo16 /vols/lhcb/ss4314/cutonFCME/$sim/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME JpsiKMC2016
./main Turbo16 /vols/lhcb/ss4314/cutonFCME/$sim/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME JpsiKMC2016




latex EfficienciesPIDreweightingStrip21LowFCMEJpsiKMC2012.tex
latex EfficienciesPIDreweightingStrip21HighFCMEJpsiKMC2012.tex
#latex EfficienciesPIDreweightingStrip23_MCTuneV1LowFCMEJpsiKMC2015.tex
#latex EfficienciesPIDreweightingStrip23_MCTuneV1HighFCMEJpsiKMC2015.tex
latex EfficienciesPIDreweightingTurbo16LowFCMEJpsiKMC2016.tex
latex EfficienciesPIDreweightingTurbo16HighFCMEJpsiKMC2016.tex


mkdir ~/public_html/preparecontrolweights/
mkdir ~/public_html/preparecontrolweights/preparecontrolweights_$sim

cp *pdf ~/public_html/preparecontrolweights/preparecontrolweights_$sim/

#
#
#

#-----------PrepareControlWeights for tag-----------------------##

cd /vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_$notsim

KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

SetupProject Urania v5r0
rm bin/*
make

cd bin

./main Strip21 /vols/lhcb/ss4314/cutonFitRange/$notsim/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root JpsiKMC2012
#./main Strip23_MCTuneV1 /vols/lhcb/ss4314/cutonFitRange/$notsim/bin/JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root JpsiKMC2015

./main Turbo16 /vols/lhcb/ss4314/cutonFitRange/$notsim/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic_FitCorM.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic_FitCorM.root JpsiKMC2016


mkdir ~/public_html/preparecontrolweights/preparecontrolweights_$notsim/

latex EfficienciesPIDreweightingStrip21JpsiKMC2012.tex
latex EfficienciesPIDreweightingTurbo16JpsiKMC2016.tex

cp *pdf ~/public_html/preparecontrolweights/preparecontrolweights_$notsim/



