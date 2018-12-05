#!/bin/sh

echo "Hello World!"

. ~lhcb/grouplogin/lhcb_login.sh

. SetupProject.sh Urania v5r0
. SetupProject.sh DaVinci


KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH


cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin

mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_1_0e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_1_0e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_1_0e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_1_0e_8sig/

./main 1000 1.0e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_2_0e_8

cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_2_0e_8/
cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_2_0e_8/

cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_2_0e_8/

./main 1000 2.0e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_3_0e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_3_0e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_3_0e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_3_0e_8sig/

./main 1000 3.0e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_4_0e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_4_0e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_4_0e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_4_0e_8sig/

./main 1000 4.0e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_5_0e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_5_0e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_5_0e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_5_0e_8sig/

./main 1000 5.0e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_1_5e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_1_5e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_1_5e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_1_5e_8sig/

./main 1000 1.5e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_2_5e_8

cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_2_5e_8/
cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_2_5e_8/

cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_2_5e_8/

./main 1000 2.5e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_3_5e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_3_5e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_3_5e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_3_5e_8sig/

./main 1000 3.5e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_4_5e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_4_5e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_4_5e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_4_5e_8sig/

./main 1000 4.5e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_5_5e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_5_5e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_5_5e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_add2016_scalesig/toy_1000_5_5e_8sig/

./main 1000 5.5e-8

#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/bin/myworkspace.root bin/
#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/bin/myworkspace2.root bin/

