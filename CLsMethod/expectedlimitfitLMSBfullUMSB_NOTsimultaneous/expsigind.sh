#!/bin/sh

echo "Hello World!"

. ~lhcb/grouplogin/lhcb_login.sh

. SetupProject.sh Urania
. SetupProject.sh DaVinci


KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH


#cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/bin
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_1_0e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_1_0e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_1_0e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_1_0e_8sig/
#
#./main 1000 1.0e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_2_0e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_2_0e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_2_0e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_2_0e_8sig/

./main 1000 2.0e-8


#mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_3_0e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_3_0e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_3_0e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_3_0e_8sig/
#
#./main 1000 3.0e-8
#
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_4_0e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_4_0e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_4_0e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_4_0e_8sig/
#
#./main 1000 4.0e-8
#
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_5_0e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_5_0e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/bin/main /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_5_0e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedlimitfitLMSBfullUMSB_NOTsimultaneous/toy_1000_5_0e_8sig/
#
#./main 1000 5.0e-8



#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/bin/myworkspace.root bin/
#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/bin/myworkspace2.root bin/


