#!bin/bash/


SetupProject Urania v5r0

folder=estimateforcombibdt_newTCK_Run1

cd /vols/lhcb/ss4314/beforecombibdt/

mkdir /vols/lhcb/ss4314/beforecombibdt/$folder

cd $folder 

mkdir Run1

cd Run1

rm *root

cp /vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/Run1/LowerMassSideBandFullDatapreparetuple/bin/Data_B23MuNu_Run1_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root .
cp /vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/Run1/FullUpperMassSideBand/bin/Data_B23MuNu_Run1_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root .


hadd finaldataRun1.root *root

KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH


make

cd bin

./main /vols/lhcb/ss4314/beforecombibdt/$folder/Run1/finaldataRun1.root


#need to change all of these to fit
