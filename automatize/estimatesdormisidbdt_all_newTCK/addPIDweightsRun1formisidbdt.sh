#!bin/bash/

cd /vols/lhcb/ss4314/addPIDweights/
mkdir estimateformisidbdt_newTCK_Run1


sourc=$PWD/estimateforcombibdt_newTCK_Run1
desti=$PWD/estimateformisidbdt_newTCK_Run1

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/

mkdir $desti/bin
cp $sourc/bin/*sh $desti/bin/

mkdir $desti/obj
mkdir $desti/docs


sourc2=$PWD/estimateforcombibdt_newTCK_Run1/os
desti2=$PWD/estimateformisidbdt_newTCK_Run1/os

cp $sourc2/* $desti2/
cp -r $sourc2/src $desti2/
cp -r $sourc2/include $desti2/

mkdir $desti2/bin
cp $sourc2/bin/*sh $desti2/bin/

mkdir $desti2/obj
mkdir $desti2/docs

#-----------------SS RUN1 tag---------------#

cd /vols/lhcb/ss4314/addPIDweights/
mkdir estimateformisidbdt_newTCK_Run1
cd estimateformisidbdt_newTCK_Run1

mkdir finaltuplesRun1

make

rm finaltuplesRun1/*

cd bin/




cp /vols/lhcb/ss4314/misidsplitting/estimateformisidbdt_newTCK_Run1/bin/Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/estimateformisidbdt_newTCK_Run1/bin/Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/estimateformisidbdt_newTCK_Run1/bin/Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_Strip* .
#
./main Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_Strip21MagDown.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_Strip21MagDown.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_Strip21MagDown.root MagDown Strip21

./main Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_Strip21MagUp.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_Strip21MagUp.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_Strip21MagUp.root MagUp Strip21

./main Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_Strip21r1MagDown.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_Strip21r1MagDown.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_Strip21r1MagDown.root MagDown Strip21r1
#
./main Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_Strip21r1MagUp.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_Strip21r1MagUp.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_Strip21r1MagUp.root MagUp Strip21r1
#
this=Basiccut
var1=Strip21r1MagDown
var2=Strip21r1MagUp
var3=Strip21MagDown
var4=Strip21MagUp
beg=../finaltuplesRun1/modifiedandcut
end=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID.root
beg2=modifiedandcut
end2=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_


for wohoo in nSharednew 

do

	hadd $beg$wohoo$end $beg2$wohoo$var1$end2$var1.root $beg2$wohoo$var2$end2$var2.root $beg2$wohoo$var3$end2$var3.root $beg2$wohoo$var4$end2$var4.root 

done

beg3=../finaltuplesRun1/modifiedandcut
end3=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID.root
beg4=modifiedandcut
end4=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_

for wohoo in nSharednew

do

        hadd $beg3$wohoo$end3 $beg4$wohoo$var1$end4$var1.root $beg4$wohoo$var2$end4$var2.root $beg4$wohoo$var3$end4$var3.root $beg4$wohoo$var4$end4$var4.root

done

beg5=../finaltuplesRun1/modifiedandcut
end5=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID.root
beg6=modifiedandcut
end6=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_

for wohoo in nSharednew

do

        hadd $beg5$wohoo$end5 $beg6$wohoo$var1$end6$var1.root $beg6$wohoo$var2$end6$var2.root $beg6$wohoo$var3$end6$var3.root $beg6$wohoo$var4$end6$var4.root

done


mkdir ~/public_html/addPIDweights
mkdir ~/public_html/addPIDweights/estimateformisidbdt_newTCK_Run1
mkdir ~/public_html/addPIDweights/estimateformisidbdt_newTCK_Run1/ss

rm ~/public_html/addPIDweights/estimateformisidbdt_newTCK_Run1/ss/*pdf


cp *pdf ~/public_html/addPIDweights/estimateformisidbdt_newTCK_Run1/ss/
cp *txt ~/public_html/addPIDweights/estimateformisidbdt_newTCK_Run1/ss/




#-----------------OS RUN1 tag---------------#
cd /vols/lhcb/ss4314/addPIDweights/
mkdir estimateformisidbdt_newTCK_Run1
cd estimateformisidbdt_newTCK_Run1

cd os

mkdir finaltuplesRun1

make

rm finaltuplesRun1/*

cd bin/

cp /vols/lhcb/ss4314/misidsplitting/estimateformisidbdt_newTCK_Run1/bin/Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/estimateformisidbdt_newTCK_Run1/bin/Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/estimateformisidbdt_newTCK_Run1/bin/Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_Strip* .



./mainforos Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_Strip21MagDown.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_Strip21MagDown.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_Strip21MagDown.root MagDown Strip21

./mainforos Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_Strip21MagUp.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_Strip21MagUp.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_Strip21MagUp.root MagUp Strip21

./mainforos Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_Strip21r1MagDown.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_Strip21r1MagDown.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_Strip21r1MagDown.root MagDown Strip21r1

./mainforos Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_Strip21r1MagUp.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_Strip21r1MagUp.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_Strip21r1MagUp.root MagUp Strip21r1


this=Basiccut
var1=Strip21r1MagDown
var2=Strip21r1MagUp
var3=Strip21MagDown
var4=Strip21MagUp
beg=../finaltuplesRun1/modifiedandcut
end=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID.root
beg2=modifiedandcut
end2=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_


for wohoo in nSharednew

do

	hadd $beg$wohoo$end $beg2$wohoo$var1$end2$var1.root $beg2$wohoo$var2$end2$var2.root $beg2$wohoo$var3$end2$var3.root $beg2$wohoo$var4$end2$var4.root 

done

beg3=../finaltuplesRun1/modifiedandcut
end3=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID.root
beg4=modifiedandcut
end4=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_

for wohoo in nSharednew

do

        hadd $beg3$wohoo$end3 $beg4$wohoo$var1$end4$var1.root $beg4$wohoo$var2$end4$var2.root $beg4$wohoo$var3$end4$var3.root $beg4$wohoo$var4$end4$var4.root

done

beg5=../finaltuplesRun1/modifiedandcut
end5=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID.root
beg6=modifiedandcut
end6=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_

for wohoo in nSharednew 

do

        hadd $beg5$wohoo$end5 $beg6$wohoo$var1$end6$var1.root $beg6$wohoo$var2$end6$var2.root $beg6$wohoo$var3$end6$var3.root $beg6$wohoo$var4$end6$var4.root

done


mkdir ~/public_html/addPIDweights/estimateformisidbdt_newTCK_Run1/os

rm ~/public_html/addPIDweights/estimateformisidbdt_newTCK_Run1/os/*pdf


cp *pdf ~/public_html/addPIDweights/estimateformisidbdt_newTCK_Run1/os/
cp *txt ~/public_html/addPIDweights/estimateformisidbdt_newTCK_Run1/os/
