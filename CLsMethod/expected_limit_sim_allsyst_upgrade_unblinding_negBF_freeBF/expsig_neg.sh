#!/bin/sh

echo "Hello World!"

#cat /etc/redhat-release


#. ~lhcb/grouplogin/lhcb_login.sh

#lb-run Urania/v7r0 bash

#. LbLogin.sh -c x86_64-slc6-gcc49-opt
. lhcb_login_new.sh
. LbLogin.sh -c x86_64-slc6-gcc49-opt
. SetupProject.sh Urania v5r0
. SetupProject.sh DaVinci v41r2



KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH


cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin


#mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_0_0e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_0_0e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_0_0e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_0_0e_8sig/
#
#./main 1000 0.0e-8
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_0_5e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_0_5e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_0_5e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_0_5e_8sig/
#
#./main 1000 -0.5e-8
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_0_75e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_0_75e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_0_75e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_0_75e_8sig/
#
#./main 1000 -0.75e-8
#

mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_0e_8

cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_0e_8/
cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_0e_8/

cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_0e_8/

./main 1000 -1.0e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_25e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_25e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_25e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_25e_8sig/

./main 1000 -1.25e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_5e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_5e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_5e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_5e_8sig/

./main 1000 -1.5e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_75e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_75e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_75e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_1_75e_8sig/

./main 1000 -1.75e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_0e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_0e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_0e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_0e_8sig/

./main 1000 -2.0e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_25e_8

cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_25e_8/
cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_25e_8/

cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_25e_8/

./main 1000 -2.25e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_5e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_5e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_5e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_5e_8sig/

./main 1000 -2.5e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_75e_8

cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_75e_8/
cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_75e_8/

cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_2_75e_8/

./main 1000 -2.75e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_0e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_0e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_0e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_0e_8sig/

./main 1000 -3.0e-8

mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_25e_8

cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_25e_8/
cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_25e_8/

cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_25e_8/

./main 1000 -3.25e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_5e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_5e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_5e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_5e_8sig/

./main 1000 -3.5e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_75e_8

cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_75e_8/
cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_75e_8/

cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_3_75e_8/

./main 1000 -3.75e-8


mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_0e_8sig

cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_0e_8sig/
cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_0e_8sig/

cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_0e_8sig/

./main 1000 -4.0e-8



#mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_25e_8
#
#cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_25e_8/
#cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_25e_8/
#
#cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_25e_8/
#
#./main 1000 4.25e-8
#
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_5e_8sig
#
#cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_5e_8sig/
#cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_5e_8sig/
#
#cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_5e_8sig/
#
#./main 1000 4.5e-8
#
#
#mkdir /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_75e_8
#
#cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/*root /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_75e_8/
#cp /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/bin/main /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_75e_8/
#
#cd /vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_negBF_freeBF/toy_1000_minus_4_75e_8/
#
#./main 1000 4.75e-8
#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/bin/myworkspace.root bin/
#cp /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/jackprobnnmu3/bin/myworkspace2.root bin/


