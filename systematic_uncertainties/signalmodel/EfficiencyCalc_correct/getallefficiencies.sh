#!/bin/bash

#-----------Selection Efficiencies----------------#

cp /vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/Efficiencies_2012.root efficiencytuples_sig/Efficiencies_SigMC_2012.root
#cp /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSig2015preparetupleNew/bin/Efficiencies.pdf EfficienciesB23muMC2015.pdf
cp /vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2016/bin/Efficiencies_2016_*root efficiencytuples_sig/
#
#
#



cp /vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/Efficiencies_2012.root efficiencytuples_norm/Efficiencies_NormMC_2012.root


cp /vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/Efficiencies_2016_Norm* efficiencytuples_norm/
#cp /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKMCDetachedLine/2011/bin/Efficiencies.pdf EfficienciesJpsiKmc2011.pdf
#cp /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKMCDetachedLine/2012/bin/Efficiencies.pdf EfficienciesJpsiKmc2012.pdf
##cp /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKMCDetachedLine/2015/bin/Efficiencies.pdf EfficienciesJpsiKmc2015.pdf
#cp /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKMCDetachedLine/2016/bin/Efficiencies.pdf EfficienciesJpsiKmc2016.pdf
#
##-----------BDT Efficiencies----------------#


cp /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/efficiencytuples_sig/* efficiencytuples_sig/
cp /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/efficiencytuples_norm/* efficiencytuples_norm/

cp /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/efficiencytuples_sig/* efficiencytuples_sig/
cp /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/efficiencytuples_norm/* efficiencytuples_norm/

#cp /vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsMisidFUMSB_add2016_newPID/bin/EfficienciesMisidBDT.pdf EfficienciesMISID.pdf
#cp /vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsCombiFUMSB_add2016_newPID/bin/EfficienciesCombiBDTCompare.pdf EfficienciesCombiBDTCompare.pdf
#cp /vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsMisidFUMSB_add2016_newPID/bin/EfficienciesMisidBDTCompare.pdf EfficienciesMisidBDTCompare.pdf
#
#
#
##-----------Fit and Binning Eff-------------#


cp /vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/efficiencytuples_sig/* efficiencytuples_sig/
cp /vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/efficiencytuples_norm/* efficiencytuples_norm/

#cp /vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesFitRange.pdf EfficienciesFitRange.pdf
#cp /vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesFitRangeCompare.pdf EfficienciesFitRangeCompare.pdf
#
#
##-----------Binning Eff-------------#
##cp /vols/lhcb/ss4314/cutonFCME/FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesLCME.pdf EfficienciesLCFME.pdf
##cp /vols/lhcb/ss4314/cutonFCME/FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesHCME.pdf EfficienciesHCFME.pdf
##cp /vols/lhcb/ss4314/cutonFCME/FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesLCMECompare.pdf EfficienciesLCMECompare.pdf
##cp /vols/lhcb/ss4314/cutonFCME/FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesHCMECompare.pdf EfficienciesHCMECompare.pdf
#
#
##----------FIT TO DATA------------#
#
##cp /vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK/LowFCME/workspace/plotJpsiKFit.pdf JpsikdatalowFCME.pdf
##cp /vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK/HighFCME/workspace/plotJpsiKFit.pdf JpsikdatahighFCME.pdf
#
#
#
#cp /vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK/NOFCME/workspace/HypathiaplotJpsiKRun1.pdf JpsikdataHypathiaRun1.pdf
##cp /vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK/NOFCME/workspace/HypathiaplotJpsiK2015.pdf JpsikdataHypathia2015.pdf
#cp /vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK/NOFCME/workspace/HypathiaplotJpsiK2016.pdf JpsikdataHypathia2016.pdf
##---------PID efficiency----------#
#
#cp /vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesPIDreweightingStrip21B23MuNuMC2012.pdf EfficienciesPIDreweightingStrip21B23MuNuMC2012.pdf
##cp /vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesPIDreweightingStrip21HighFCMEB23MuNuMC2012.pdf EfficienciesPIDreweightingStrip21HighFCMEB23MuNuMC2012.pdf
##cp /vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesPIDreweightingStrip23_MCTuneV1B23MuNuMC2015.pdf EfficienciesPIDreweightingStrip23_MCTuneV1B23MuNuMC2015.pdf
##cp /vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesPIDreweightingStrip21HighFCMEB23MuNuMC2015.pdf EfficienciesPIDreweightingStrip21HighFCMEB23MuNuMC2015.pdf
#cp /vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesPIDreweightingStrip26B23MuNuMC2016.pdf EfficienciesPIDreweightingStrip26B23MuNuMC2016.pdf
#
#
#cp /vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesPIDreweightingStrip21JpsiKMC2012.pdf EfficienciesPIDreweightingStrip21JpsiKMC2012.pdf
##cp /vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesPIDreweightingStrip21HighFCMEJpsiKMC2012.pdf EfficienciesPIDreweightingStrip21HighFCMEJpsiKMC2012.pdf
##cp /vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesPIDreweightingStrip23_MCTuneV1JpsiKMC2015.tex EfficienciesPIDreweightingStrip23_MCTuneV1JpsiKMC2015.tex
##cp /vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesPIDreweightingStrip21HighFCMEJpsiKMC2015.pdf EfficienciesPIDreweightingStrip21HighFCMEJpsiKMC2015.pdf
#cp /vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesPIDreweightingStrip26JpsiKMC2016.pdf EfficienciesPIDreweightingStrip26JpsiKMC2016.pdf
#
##---------CrossCheck-------------#
#cp /vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesFitRange.pdf crosschecksig.pdf
##cp /vols/lhcb/ss4314/cutonFCME/FUMSB_NOTsimultaneous_NewTCK/bin/EfficienciesHCME.pdf crosschecksigHighFCME.pdf
#


