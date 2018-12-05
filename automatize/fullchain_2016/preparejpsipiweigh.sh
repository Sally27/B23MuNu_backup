
trainingname=FUMSB_simultaneous_add2016 #NEW simultaneous year
tag=FUMSB_NOTsimultaneous_add2016 #NEW NOT simultaneous year
tn=_scalesig


#------------------------add PID weights to MC--------------------#




sourc=preparejpsipiweights_$trainingname
sourc2=preparejpsipiweights_$tag
desti=preparejpsipiweights_$trainingname$tn
desti2=preparejpsipiweights_$tag$tn
#---------ADD PID WEIGHTS to jpsipi channel-----------#


cd /vols/lhcb/ss4314/preparejpsipiweights/

mkdir preparejpsipiweights_$trainingname$tn
mkdir preparejpsipiweights_$tag$tn



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

#cd preparejpsipiweights_$trainingname$tn
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
#./main Strip23_MCTuneV1 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME JpsiKMC2015
#./main Strip23_MCTuneV1 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME JpsiKMC2015
#./main Strip26 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/B2JpsiKMC2016Detached_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root B2JpsiKMC2016Detached_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME JpsiKMC2016
#./main Strip26 /vols/lhcb/ss4314/cutonFCME/$trainingname/bin/B2JpsiKMC2016Detached_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root B2JpsiKMC2016Detached_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME JpsiKMC2016
#
#
#
#
#latex EfficienciesPIDreweightingStrip21LowFCMEJpsiKMC2012.tex
#latex EfficienciesPIDreweightingStrip21HighFCMEJpsiKMC2012.tex
#latex EfficienciesPIDreweightingStrip23_MCTuneV1LowFCMEJpsiKMC2015.tex
#latex EfficienciesPIDreweightingStrip23_MCTuneV1HighFCMEJpsiKMC2015.tex
#latex EfficienciesPIDreweightingStrip26LowFCMEJpsiKMC2016.tex
#latex EfficienciesPIDreweightingStrip26HighFCMEJpsiKMC2016.tex
#
#
#mkdir ~/public_html/preparejpsipiweights/
#mkdir ~/public_html/preparejpsipiweights/preparejpsipiweights_$trainingname$tn
#
#cp *pdf ~/public_html/preparejpsipiweights/preparejpsipiweights_$trainingname$tn/
##
#
#
#
#
#-----------PrepareControlWeights for tag-----------------------##

cd /vols/lhcb/ss4314/preparejpsipiweights/preparejpsipiweights_$tag$tn

KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

make

cd bin

./main Strip21 /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiPiMCafterall/bin/BuPiMuMuMC_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_PTkaon_Blifetime.root BuPiMuMuMC_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_PTkaon_Blifetime.root JpsiPiMC2012

mkdir ~/public_html/preparejpsipiweights/preparejpsipiweights_$tag$tn/

latex EfficienciesPIDreweightingStrip21JpsiPiMC2012.tex
#latex EfficienciesPIDreweightingStrip23_MCTuneV1JpsiKMC2015.tex
#latex EfficienciesPIDreweightingStrip26JpsiKMC2016.tex

cp *pdf ~/public_html/preparejpsipiweights/preparejpsipiweights_$tag$tn/



