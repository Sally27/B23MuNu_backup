#!bin/bash/


SetupProject Urania v5r0

folder=estimateforcombibdt_newTCK_2016

cd /vols/lhcb/ss4314/beforecombibdt/

mkdir /vols/lhcb/ss4314/beforecombibdt/$folder

cd $folder 

mkdir 2016

cd 2016

rm *root

cp /vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/2016/LowerMassSideBandFullDatapreparetuple/bin/Bu23MuNuData2016_corrmLSDfull_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut.root .
cp /vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/2016/FullUpperMassSideBand/bin/Bu23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut.root .


hadd finaldata2016.root *root

KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH


make

cd bin

./main /vols/lhcb/ss4314/beforecombibdt/$folder/2016/finaldata2016.root


#need to change all of these to fit
