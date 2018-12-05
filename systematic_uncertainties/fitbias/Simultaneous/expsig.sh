#!/bin/sh

echo "Hello World!"

. ~lhcb/grouplogin/lhcb_login.sh

. SetupProject.sh Urania v5r0
. SetupProject.sh DaVinci


KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH


#
#
mkdir /vols/lhcb/ss4314/systematic_uncertainties/fitbias/Simultaneous/toy_10000_1_0e_8
#
cp /vols/lhcb/ss4314/systematic_uncertainties/fitbias/Simultaneous/bin/*root /vols/lhcb/ss4314/systematic_uncertainties/fitbias/Simultaneous/toy_10000_1_0e_8/
cp /vols/lhcb/ss4314/systematic_uncertainties/fitbias/Simultaneous/bin/runcorrecttoys /vols/lhcb/ss4314/systematic_uncertainties/fitbias/Simultaneous/toy_10000_1_0e_8/

cd /vols/lhcb/ss4314/systematic_uncertainties/fitbias/Simultaneous/toy_10000_1_0e_8/

./runcorrecttoys 10000 1.0e-8



#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/bin/myworkspace.root bin/
#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/bin/myworkspace2.root bin/


