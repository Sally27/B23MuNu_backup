#!bin/bash/

#cd /vols/lhcb/ss4314/addPIDweights/
#mkdir estimateforcombibdt_newTCK_2016
#
#
#sourc=$PWD/estimateforcombibdt_2016_newtuples/
#desti=$PWD/estimateforcombibdt_newTCK_2016
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
#sourc2=$PWD/estimateforcombibdt_2016_newtuples/os
#desti2=$PWD/estimateforcombibdt_newTCK_2016/os
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

#----------------------ADD PID WEIGJTS before bdt--------##

cd /vols/lhcb/ss4314/addPIDweights/
#mkdir estimateforcombibdt_newTCK_2016
cd estimateforcombibdt_finalPID_2016

mkdir finaltuples2016

make

rm finaltuples2016/*

cd bin/

cp /vols/lhcb/ss4314/misidsplitting/estimateforcombibdt_newTCK_2016/bin/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/estimateforcombibdt_newTCK_2016/bin/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/estimateforcombibdt_newTCK_2016/bin/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_Strip* .

./main Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_Strip26MagDown.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_Strip26MagDown.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_Strip26MagDown.root MagDown Strip26

./main Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_Strip26MagUp.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_Strip26MagUp.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_Strip26MagUp.root MagUp Strip26

#
this=Basiccut
var3=Strip26MagDown
var4=Strip26MagUp
beg=../finaltuples2016/modifiedandcut
end=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root
beg2=modifiedandcut
end2=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_


for tags in nShared22

do

	hadd $beg$tags$end $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 

done

beg3=../finaltuples2016/modifiedandcut
end3=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root
beg4=modifiedandcut
end4=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_

for tags in nShared22

do

        hadd $beg3$tags$end3 $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root

done

beg5=../finaltuples2016/modifiedandcut
end5=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM.root
beg6=modifiedandcut
end6=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_

for tags in nShared22

do

        hadd $beg5$tags$end5 $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root

done

mkdir ~/public_html/addPIDweights
mkdir ~/public_html/addPIDweights/estimateforcombibdt_finalPID_2016
mkdir ~/public_html/addPIDweights/estimateforcombibdt_finalPID_2016/ss

rm ~/public_html/addPIDweights/estimateforcombibdt_finalPID_2016/ss/*pdf


cp *pdf ~/public_html/addPIDweights/estimateforcombibdt_finalPID_2016/ss/
cp *txt ~/public_html/addPIDweights/estimateforcombibdt_finalPID_2016/ss/
##
#
cd /vols/lhcb/ss4314/addPIDweights/
cd estimateforcombibdt_finalPID_2016

cd os

mkdir finaltuples2016
rm finaltuples2016/*
rm bin/*

make

cd bin



cp /vols/lhcb/ss4314/misidsplitting/estimateforcombibdt_newTCK_2016/bin/Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/estimateforcombibdt_newTCK_2016/bin/Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/estimateforcombibdt_newTCK_2016/bin/Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_Strip* .

./mainforos Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_Strip26MagDown.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_Strip26MagDown.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_Strip26MagDown.root MagDown Strip26

./mainforos Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_Strip26MagUp.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_Strip26MagUp.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_Strip26MagUp.root MagUp Strip26

#
this=Basiccut
var3=Strip26MagDown
var4=Strip26MagUp
beg=../finaltuples2016/modifiedandcut
end=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root
beg2=modifiedandcut
end2=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_


for tags in nShared22

do

	hadd $beg$tags$end $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 

done

beg3=../finaltuples2016/modifiedandcut
end3=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root
beg4=modifiedandcut
end4=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_

for tags in nShared22

do

        hadd $beg3$tags$end3 $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root

done

beg5=../finaltuples2016/modifiedandcut
end5=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_CombBasic_MisidBasic_FitCorM.root
beg6=modifiedandcut
end6=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_

for tags in nShared22

do

        hadd $beg5$tags$end5 $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root

done

mkdir ~/public_html/addPIDweights/estimateforcombibdt_finalPID_2016/os

rm ~/public_html/addPIDweights/estimateforcombibdt_finalPID_2016/os/*pdf


cp *pdf ~/public_html/addPIDweights/estimateforcombibdt_finalPID_2016/os/
cp *txt ~/public_html/addPIDweights/estimateforcombibdt_finalPID_2016/os/
