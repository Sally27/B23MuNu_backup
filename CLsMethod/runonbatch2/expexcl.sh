#!/bin/sh

echo "Hello World!"

. ~lhcb/grouplogin/lhcb_login.sh

. SetupProject.sh Urania
. SetupProject.sh DaVinci


KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH


cd /vols/lhcb/ss4314/CLsMethod/expectedexclusion/bin

mkdir /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_7sig

cp /vols/lhcb/ss4314/CLsMethod/expectedexclusion/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_7sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedexclusion/bin/main /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_7sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_7sig/

./main 50 7


mkdir /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_14sig2

cp /vols/lhcb/ss4314/CLsMethod/expectedexclusion/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_14sig2/
cp /vols/lhcb/ss4314/CLsMethod/expectedexclusion/bin/main /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_14sig2/

cd /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_14sig2/

./main 50 14


mkdir /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_21sig

cp /vols/lhcb/ss4314/CLsMethod/expectedexclusion/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_21sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedexclusion/bin/main /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_21sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_21sig/

./main 50 21


mkdir /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_28sig

cp /vols/lhcb/ss4314/CLsMethod/expectedexclusion/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_28sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedexclusion/bin/main /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_28sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_28sig/

./main 50 28


mkdir /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_35sig

cp /vols/lhcb/ss4314/CLsMethod/expectedexclusion/bin/*root /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_35sig/
cp /vols/lhcb/ss4314/CLsMethod/expectedexclusion/bin/main /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_35sig/

cd /vols/lhcb/ss4314/CLsMethod/expectedexclusion/toy_50_35sig/

./main 50 35



#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/bin/myworkspace.root bin/
#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/bin/myworkspace2.root bin/


