#!/bin/sh

echo "Hello World!"

. ~lhcb/grouplogin/lhcb_login.sh

. SetupProject.sh Urania v5r0
. SetupProject.sh DaVinci


KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH


cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin

#mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_0_5e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_0_5e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_0_5e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_0_5e_8sig/
#
#./main 1000 0.5e-8
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_0_75e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_0_75e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_0_75e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_0_75e_8sig/
#
#./main 1000 0.75e-8
#
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_0e_8
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_0e_8/
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_0e_8/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_0e_8/
#
#./main 1000 1.0e-8
#
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_25e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_25e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_25e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_25e_8sig/
#
#./main 1000 1.25e-8
#
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_5e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_5e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_5e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_5e_8sig/
#
#./main 1000 1.5e-8
#
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_75e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_75e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_75e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_1_75e_8sig/
#
#./main 1000 1.75e-8
#
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_0e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_0e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_0e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_0e_8sig/
#
#./main 1000 2.0e-8
#
#
mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_25e_8

cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_25e_8/
cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_25e_8/

cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_25e_8/

./main 1000 2.25e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_5e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_5e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_5e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_5e_8sig/

./main 1000 2.5e-8


#mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_75e_8
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_75e_8/
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_75e_8/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_2_75e_8/
#
#./main 1000 2.75e-8
#
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_3_0e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_3_0e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_3_0e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_simultaneous_NewTCK_newcode/toy_1000_3_0e_8sig/
#
#./main 1000 3.0e-8

#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/bin/myworkspace.root bin/
#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/bin/myworkspace2.root bin/


