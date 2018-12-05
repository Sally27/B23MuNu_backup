#!/bin/bash

path=/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_symmetric_newcontrolchannel/bin/
filename1=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename5=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename6=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename7=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename8=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;



VAR2="(Polarity==1)&&(runNumber<105000)"
VAR1=Strip21r1MagUp
./main $path $VAR1 $VAR2 $filename1 $filename2 $filename3 $filename4


VAR4="(Polarity==-1)&&(runNumber<105000)"
VAR3=Strip21r1MagDown
./main $path $VAR3 $VAR4 $filename1 $filename2 $filename3 $filename4

VAR6="(Polarity==1)&&(runNumber>105000)"
VAR5=Strip21MagUp
./main $path $VAR5 $VAR6 $filename1 $filename2 $filename3 $filename4

VAR8="(Polarity==-1)&&(runNumber>105000)"
VAR7=Strip21MagDown
./main $path $VAR7 $VAR8 $filename1 $filename2 $filename3 $filename4

./main $path $VAR1 $VAR2 $filename5 $filename6 $filename7 $filename8
./main $path $VAR3 $VAR4 $filename5 $filename6 $filename7 $filename8
./main $path $VAR5 $VAR6 $filename5 $filename6 $filename7 $filename8
./main $path $VAR7 $VAR8 $filename5 $filename6 $filename7 $filename8


