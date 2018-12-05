cd  /vols/lhcb/ss4314/mergedataforBDTtraining/
mkdir /vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_newTCK
mkdir /vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_newTCK
mkdir /vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_newTCK/combi
mkdir /vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_newTCK/misid
mkdir /vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_newTCK/combi
mkdir /vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_newTCK/misid


#starting=/vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_new2016tuples/combi/
#ending=/vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_newTCK/combi/
#
##-------------Copy functions to do this-----------#
#
#
#
##sourc=$starting
##desti=$ending
##
##
##cp $sourc/* $desti/
##cp -r $sourc/src $desti/
##cp -r $sourc/include $desti/
##mkdir $desti/bin
##mkdir $desti/obj
##mkdir $desti/docs
##cp $sourc/bin/*sh $desti/bin/
#
#
#
#cd /vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_newTCK/combi/
#
#
#rm *root
#
#make
#
#SetupProject Urania v5r0
#
#KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
#
#cp /vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/2016/FullUpperMassSideBand/bin/Bu23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut.root .
#cp /vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/Run1/FullUpperMassSideBand/bin/Data_B23MuNu_Run1_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root .
#
#cd bin
#
#./main /vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_newTCK/combi/Data_B23MuNu_Run1_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root /vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_newTCK/combi/Bu23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut.root
#
#hadd combinatorialrun1and2016_newTCK.root *root



#cd /vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_newTCK/combi/
#
#starting=/vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_new2016tuples/combi
#ending=/vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_newTCK/combi
#
##-------------Copy functions to do this-----------#
#
#
#
#sourc=$starting
#desti=$ending
#
#
#cp $sourc/* $desti/
#cp -r $sourc/src $desti/
#cp -r $sourc/include $desti/
#mkdir $desti/bin
#mkdir $desti/obj
#mkdir $desti/docs
#cp $sourc/bin/*sh $desti/bin/
#
#cd /vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_newTCK/combi/
##
##
#rm *root
##
#make clean
#make
##
#SetupProject Urania v5r0
##
#KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
##
#cp /vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root .
#cp /vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut.root .
##
#cd bin
##
#./main /vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_newTCK/combi/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root /vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_newTCK/combi/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut.root
##
#hadd MCrun1and2016_newTCK.root *root

#cd /vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_newTCK/misid/

#starting=/vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_newTCK/combi
#ending=/vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_newTCK/misid
##-------------Copy functions to do this-----------#
#
#
#
#sourc=$starting
#desti=$ending
#
#
#cp $sourc/* $desti/
#cp -r $sourc/src $desti/
#cp -r $sourc/include $desti/
#mkdir $desti/bin
#mkdir $desti/obj
#mkdir $desti/docs
#cp $sourc/bin/*sh $desti/bin/
#
#
#
#cd /vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_newTCK/misid/
#
#
#rm *root
#SetupProject Urania v5r0
#make clean
#make
#
#
#KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
#
#cp /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_CombBasic.root .
#cp /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic.root .
#
#cd bin
#
#./main /vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_newTCK/misid/Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic.root /vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_newTCK/misid/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_CombBasic.root
#
#hadd misidrun1and2016_newTCK.root *root




cd /vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_newTCK/misid/

starting=/vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_newTCK/combi
ending=/vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_newTCK/misid
#-------------Copy functions to do this-----------#



sourc=$starting
desti=$ending


cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
cp $sourc/bin/*sh $desti/bin/

cd /vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_newTCK/misid/
#
#
rm *root
#
make clean
make
#
SetupProject Urania v5r0
#
KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
#
cp /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic.root .
cp /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root .
#
cd bin
#
./main /vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_newTCK/misid/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/mergedataforBDTtraining/mc/run1and2016_newTCK/misid/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root
#
hadd MCMisidrun1and2016_newTCK.root *root






