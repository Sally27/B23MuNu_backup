#!/bin/bash

rm  ../finaltuples/*.root

cp /vols/lhcb/ss4314/misidsplitting/beforeBDTs/splitting/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPIDStrip* .
cp /vols/lhcb/ss4314/misidsplitting/beforeBDTs/splitting/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPIDStrip* .

./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPIDStrip21MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPIDStrip21MagDown.root MagDown Strip21

./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPIDStrip21MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPIDStrip21MagUp.root MagUp Strip21

./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPIDStrip21r1MagDown.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPIDStrip21r1MagDown.root MagDown Strip21r1

./main B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPIDStrip21r1MagUp.root B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPIDStrip21r1MagUp.root MagUp Strip21r1

this=Basic*cut
var1=Strip21r1MagDown
var2=Strip21r1MagUp
var3=Strip21MagDown
var4=Strip21MagUp
beg=../finaltuples/modifiedandcut
end=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID.root
beg2=modifiedandcut
end2=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

	hadd $beg$tags$end $beg2$tags$var1$end2$var1.root $beg2$tags$var2$end2$var2.root $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 

done


begk=../finaltuples/modifiedandcut
endk=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID.root
beg2k=modifiedandcut
end2k=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

        hadd $begk$tags$endk $beg2k$tags$var1$end2k$var1.root $beg2k$tags$var2$end2k$var2.root $beg2k$tags$var3$end2k$var3.root $beg2k$tags$var4$end2k$var4.root

done



#./main SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_60TreesComb_60TreesMisID.root SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_60TreesComb_60TreesMisID.root MagUp Strip21

#./main SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_60TreesComb_60TreesMisID.root SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_60TreesComb_60TreesMisID.root MagDown Strip21r1

#./main SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_60TreesComb_60TreesMisID.root SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_60TreesComb_60TreesMisID.root MagUp Strip21r1
