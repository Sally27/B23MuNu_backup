#!/bin/sh

echo "Hello World!"

. ~lhcb/grouplogin/lhcb_login.sh

. SetupProject.sh Urania
. SetupProject.sh DaVinci


KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH


cd /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/bin

#mkdir /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_1_0e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_1_0e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/bin/main /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_1_0e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_1_0e_8sig/
#
#./main 300 1.0e-8
#
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_2_0e_8
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_2_0e_8/
#cp /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/bin/main /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_2_0e_8/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_2_0e_8/
#
#./main 300 2.0e-8
#
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_3_0e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_3_0e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/bin/main /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_3_0e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_3_0e_8sig/
#
#./main 300 3.0e-8
#
#
mkdir /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_6_0e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_6_0e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/bin/main /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_6_0e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_6_0e_8sig/

./main 300 6.0e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_7_0e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_7_0e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/bin/main /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_7_0e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedsignificanceafterjack/toy_300_7_0e_8sig/

./main 300 7.0e-8



#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/bin/myworkspace.root bin/
#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/bin/myworkspace2.root bin/


