
simold=FUMSB_simultaneous_add2016_scalesig
notsimold=FUMSB_NOTsimultaneous_add2016_scalesig
sim=FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights #NEW simultaneous year
notsim=FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_AntiBDT #NEW NOT simultaneous year




#------------------------add PID weights to MC--------------------#




sourc=preparejpsipiweights_$simold
sourc2=preparejpsipiweights_$notsimold
desti=preparejpsipiweights_$sim
desti2=preparejpsipiweights_$notsim
#---------ADD PID WEIGHTS to jpsipi channel-----------#


cd /vols/lhcb/ss4314/preparejpsipiweights/
#
#mkdir preparejpsipiweights_$sim
#mkdir preparejpsipiweights_$notsim
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

#cd preparejpsipiweights_$sim
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
#./main Strip21 /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiPiMCafterall/bin/MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_HighFCME_PTkaon_Blifetime.root MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_HighFCME_PTkaon_Blifetime.root HighFCME JpsiPiMC2012
#
#./main Strip21 /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiPiMCafterall/bin/MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_LowFCME_PTkaon_Blifetime.root MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_LowFCME_PTkaon_Blifetime.root LowFCME JpsiPiMC2012
##./main Strip21 /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiPiMCafterall/bin/JpsiKMCDetachedLine_2012_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_PTkaon_Blifetime_LowFCME.root JpsiKMCDetachedLine_2012_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_PTkaon_Blifetime_LowFCME.root LowFCME JpsiPiMC2012
##./main Strip23_MCTuneV1 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_PTkaon_Blifetime_HighFCME.root JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_PTkaon_Blifetime_HighFCME.root HighFCME JpsiKMC2015
##./main Strip23_MCTuneV1 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_PTkaon_Blifetime_LowFCME.root JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_PTkaon_Blifetime_LowFCME.root LowFCME JpsiKMC2015
##./main Strip26 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/B2JpsiKMC2016Detached_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_PTkaon_Blifetime_HighFCME.root B2JpsiKMC2016Detached_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_PTkaon_Blifetime_HighFCME.root HighFCME JpsiKMC2016
##./main Strip26 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/B2JpsiKMC2016Detached_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_PTkaon_Blifetime_LowFCME.root B2JpsiKMC2016Detached_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_PTkaon_Blifetime_LowFCME.root LowFCME JpsiKMC2016
#
#
#
#
#latex EfficienciesPIDreweightingStrip21LowFCMEJpsiPiMC2012.tex
#latex EfficienciesPIDreweightingStrip21HighFCMEJpsiPiMC2012.tex
##latex EfficienciesPIDreweightingStrip23_MCTuneV1LowFCMEJpsiKMC2015.tex
##latex EfficienciesPIDreweightingStrip23_MCTuneV1HighFCMEJpsiKMC2015.tex
##latex EfficienciesPIDreweightingStrip26LowFCMEJpsiKMC2016.tex
##latex EfficienciesPIDreweightingStrip26HighFCMEJpsiKMC2016.tex
#
#
#mkdir ~/public_html/preparejpsipiweights/
#mkdir ~/public_html/preparejpsipiweights/preparejpsipiweights_$sim
#
#cp *pdf ~/public_html/preparejpsipiweights/preparejpsipiweights_$sim/
###
##
##
##
##
#-----------PrepareControlWeights for tag-----------------------##

cd /vols/lhcb/ss4314/preparejpsipiweights/preparejpsipiweights_$notsim

KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

make

cd bin

./main Strip21 /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiPiMCafterall/bin/MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_PTkaon_Blifetime.root MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic_AntiBDT_FitCorM_PTkaon_Blifetime.root JpsiPiMC2012

mkdir ~/public_html/preparejpsipiweights/preparejpsipiweights_$notsim/

latex EfficienciesPIDreweightingStrip21JpsiPiMC2012.tex
#latex EfficienciesPIDreweightingStrip23_MCTuneV1JpsiKMC2015.tex
#latex EfficienciesPIDreweightingStrip26JpsiKMC2016.tex

cp *pdf ~/public_html/preparejpsipiweights/preparejpsipiweights_$notsim/
#
#
#
