#!/bin/bash

rm *txt *pdf *tex *root
rm ../finaltuples/*root


cp /vols/lhcb/ss4314/misidsplitting/MisidAfterCombiRestripEta1and3tighterproton/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasicStrip* .
cp /vols/lhcb/ss4314/misidsplitting/MisidAfterCombiRestripEta1and3tighterproton/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasicStrip* .

./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasicStrip21MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasicStrip21MagDown.root MagDown Strip21

./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasicStrip21MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasicStrip21MagUp.root MagUp Strip21

./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasicStrip21r1MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasicStrip21r1MagDown.root MagDown Strip21r1
#
./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasicStrip21r1MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasicStrip21r1MagUp.root MagUp Strip21r1
#
this=Basic*cut
var1=Strip21r1MagDown
var2=Strip21r1MagUp
var3=Strip21MagDown
var4=Strip21MagUp
beg=../finaltuples/modifiedandcut
end=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root
beg2=modifiedandcut
end2=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic


for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

	hadd $beg$tags$end $beg2$tags$var1$end2$var1.root $beg2$tags$var2$end2$var2.root $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 

done

beg3=../finaltuples/modifiedandcut
end3=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic.root
beg4=modifiedandcut
end4=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root

done
