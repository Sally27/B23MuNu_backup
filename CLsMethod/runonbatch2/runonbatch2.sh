#!/bin/sh

echo "Hello World!"

. ~lhcb/grouplogin/lhcb_login.sh

. SetupProject.sh Urania
. SetupProject.sh DaVinci


KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH


cd /vols/lhcb/ss4314/CLsMethod/sallyCLs10minus8/bin

mkdir /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_7sig

cp /vols/lhcb/ss4314/CLsMethod/sallyCLs10minus8/bin/*root /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_7sig/
cp /vols/lhcb/ss4314/CLsMethod/sallyCLs10minus8/bin/main /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_7sig/

cd /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_7sig/

./main 500 7


mkdir /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_14sig2

cp /vols/lhcb/ss4314/CLsMethod/sallyCLs10minus8/bin/*root /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_14sig2/
cp /vols/lhcb/ss4314/CLsMethod/sallyCLs10minus8/bin/main /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_14sig2/

cd /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_14sig2/

./main 100 14


mkdir /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_21sig

cp /vols/lhcb/ss4314/CLsMethod/sallyCLs10minus8/bin/*root /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_21sig/
cp /vols/lhcb/ss4314/CLsMethod/sallyCLs10minus8/bin/main /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_21sig/

cd /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_21sig/

./main 100 21


mkdir /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_28sig

cp /vols/lhcb/ss4314/CLsMethod/sallyCLs10minus8/bin/*root /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_28sig/
cp /vols/lhcb/ss4314/CLsMethod/sallyCLs10minus8/bin/main /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_28sig/

cd /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_28sig/

./main 100 28


mkdir /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_35sig

cp /vols/lhcb/ss4314/CLsMethod/sallyCLs10minus8/bin/*root /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_35sig/
cp /vols/lhcb/ss4314/CLsMethod/sallyCLs10minus8/bin/main /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_35sig/

cd /vols/lhcb/ss4314/CLsMethod/runonbatch/toy_500_35sig/

./main 100 35



#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/bin/myworkspace.root bin/
#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/bin/myworkspace2.root bin/


