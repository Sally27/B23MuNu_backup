#!/bin/bash

tag=FUMSB_NOTsimultaneous_add2016 #NEW NOT simultaneous year
tn=_scalesig


#------------------------add PID weights to MC--------------------#




##
KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

./main Strip21 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/JpsiKMCDetachedLine_2012_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root JpsiKMCDetachedLine_2012_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root JpsiKMC2012
./main Strip23_MCTuneV1 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root JpsiKMC2015

./main Strip26 /vols/lhcb/ss4314/cutonFitRange/$tag/bin/B2JpsiKMC2016Detached_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root B2JpsiKMC2016Detached_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root JpsiKMC2016

#
#
for i in *.tex; do pdflatex $i; done
#latex EfficienciesPIDreweightingStrip21B23MuNuMC2012.tex
#latex EfficienciesPIDreweightingStrip23_MCTuneV1B23MuNuMC2015.tex
#latex EfficienciesPIDreweightingStrip26B23MuNuMC2016.tex
#
mkdir ~/public_html/preparecontrolweights/preparecontrolweights_forMCcutvsPIDreweight
cp *pdf ~/public_html/preparecontrolweights/preparecontrolweights_forMCcutvsPIDreweight/

#mkdir ../haddtuples
#rm ../haddtuples/*
#
#hadd ../haddtuples/B23MuNuMCAll.root B23MuNuMC2012NNmumore03Strip21.root B23MuNuMC2015NNmumore03Strip23_MCTuneV1.root B23MuNuMC2016NNmumore03Strip26.root
#hadd ../haddtuples/B23MuNuMCAll_onlyRun1and2015.root B23MuNuMC2012NNmumore03Strip21.root B23MuNuMC2015NNmumore03Strip23_MCTuneV1.root
#hadd ../haddtuples/B23MuNuMCAll_onlyRun1.root B23MuNuMC2012NNmumore03Strip21.root
