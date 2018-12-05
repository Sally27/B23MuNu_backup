#!/bin/bash

#rm *.root *.pdf

VAR1=Strip21
VAR2=MagUp
KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

SetupProject Urania v5r0
make


cd bin

./main Strip21 /vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic_FitCorM.root Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic_FitCorM.root B23MuNuMC2012

./main Strip21 /vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/B23MuNuMCPHSP_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic_FitCorM.root B23MuNuMCPHSP_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic_FitCorM.root B23MuNuMCPHSP2012


latex EfficienciesPIDreweightingStrip21B23MuNuMC2012.tex
latex EfficienciesPIDreweightingStrip21B23MuNuMCPHSP2012.tex
#./main Strip21 MagDown

#./main Strip21r1 MagUp

#./main Strip21r1 MagDown

