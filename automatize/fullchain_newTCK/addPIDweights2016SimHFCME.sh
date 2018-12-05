#!bin/bash/

cd /vols/lhcb/ss4314/addPIDweights/
mkdir FUMSB_simultaneous_NewTCK


#sourc=$PWD/estimateformisidbdt_newTCK_Run1
#desti=$PWD/FUMSB_simultaneous_NewTCK
#
#cp $sourc/* $desti/
#cp -r $sourc/src $desti/
#cp -r $sourc/include $desti/
#
#mkdir $desti/bin
#cp $sourc/bin/*sh $desti/bin/
#
#mkdir $desti/obj
#mkdir $desti/docs
#
#
#sourc2=$PWD/estimateformisidbdt_newTCK_Run1/os
#desti2=$PWD/FUMSB_simultaneous_NewTCK/os
#
#cp $sourc2/* $desti2/
#cp -r $sourc2/src $desti2/
#cp -r $sourc2/include $desti2/
#
#mkdir $desti2/bin
#cp $sourc2/bin/*sh $desti2/bin/
#
#mkdir $desti2/obj
#mkdir $desti2/docs

#-----------------SS RUN1 tag---------------#

cd /vols/lhcb/ss4314/addPIDweights/
mkdir FUMSB_simultaneous_NewTCK
cd FUMSB_simultaneous_NewTCK

mkdir finaltuples2016
mkdir finaltuples2016/HFCME

make

rm finaltuples2016/*
rm finaltuples2016/HFCME/*


cd bin/
rm *pdf
rm *txt



cp /vols/lhcb/ss4314/misidsplitting/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
#
./main Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagDown.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagDown.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagDown.root MagDown Strip26

./main Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagUp.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagUp.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagUp.root MagUp Strip26

#
this=Basiccut
var3=Strip26MagDown
var4=Strip26MagUp
beg=../finaltuples2016/HFCME/modifiedandcut
end=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg2=modifiedandcut
end2=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_


for wohoo in nShared22 

do

	hadd $beg$wohoo$end $beg2$wohoo$var3$end2$var3.root $beg2$wohoo$var4$end2$var4.root 

done

beg3=../finaltuples2016/HFCME/modifiedandcut
end3=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg4=modifiedandcut
end4=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_

for wohoo in nShared22

do

        hadd $beg3$wohoo$end3 $beg4$wohoo$var3$end4$var3.root $beg4$wohoo$var4$end4$var4.root

done

beg5=../finaltuples2016/HFCME/modifiedandcut
end5=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg6=modifiedandcut
end6=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_

for wohoo in nShared22

do

        hadd $beg5$wohoo$end5 $beg6$wohoo$var3$end6$var3.root $beg6$wohoo$var4$end6$var4.root

done


mkdir ~/public_html/addPIDweights
mkdir ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK
mkdir ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/ss
mkdir ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/ss/HFCME
mkdir ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/ss/HFCME/2016

rm ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/ss/*pdf
rm ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/ss/*txT
rm ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/ss/HFCME/2016/*pdf
rm ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/ss/HFCME/2016/*txt

cp *pdf ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/ss/HFCME/2016
cp *txt ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/ss/HFCME/2016




#-----------------OS RUN1 tag---------------#
cd /vols/lhcb/ss4314/addPIDweights/
mkdir FUMSB_simultaneous_NewTCK
cd FUMSB_simultaneous_NewTCK

cd os

mkdir finaltuples2016
mkdir finaltuples2016/HFCME

make

rm finaltuples2016/*
rm finaltuples2016/HFCME/*

cd bin/
rm *pdf
rm *txt

cp /vols/lhcb/ss4314/misidsplitting/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .



./mainforos Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagDown.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagDown.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagDown.root MagDown Strip26

./mainforos Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagUp.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagUp.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagUp.root MagUp Strip26



this=Basiccut
var3=Strip26MagDown
var4=Strip26MagUp
beg=../finaltuples2016/HFCME/modifiedandcut
end=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg2=modifiedandcut
end2=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_


for wohoo in nShared22

do

	hadd $beg$wohoo$end $beg2$wohoo$var3$end2$var3.root $beg2$wohoo$var4$end2$var4.root 

done

beg3=../finaltuples2016/HFCME/modifiedandcut
end3=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg4=modifiedandcut
end4=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_

for wohoo in nShared22

do

        hadd $beg3$wohoo$end3 $beg4$wohoo$var3$end4$var3.root $beg4$wohoo$var4$end4$var4.root

done

beg5=../finaltuples2016/HFCME/modifiedandcut
end5=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg6=modifiedandcut
end6=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_

for wohoo in nShared22 

do

        hadd $beg5$wohoo$end5 $beg6$wohoo$var3$end6$var3.root $beg6$wohoo$var4$end6$var4.root

done


mkdir ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/os
mkdir ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/os/HFCME/
mkdir ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/os/HFCME/2016

rm ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/os/*pdf
rm ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/os/HFCME/2016/*pdf

cp *pdf ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/os/HFCME/2016/
cp *txt ~/public_html/addPIDweights/FUMSB_simultaneous_NewTCK/os/HFCME/2016/
