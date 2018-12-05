#!/bin/bash
#. LbLogin.sh -c x86_64-slc6-gcc46-opt
. SetupProject.sh Urania v4r0 #v2r0p1

#export TMVALOC=/vols/lhcb/ss4314/TMVA/kfoldandubdt/optimizedubdt/uboost/TMVA-v4.1.2
#export LD_LIBRARY_PATH=$TMVALOC/lib/:$LD_LIBRARY_PATH
#echo "$TMVALOC"
DEND_PATH=/vols/lhcb/ss4314/TMVA/dendrology-master/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH

make clean

echo "Do you wish to change input variables or options for BDT?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) cd src/; echo "Do your changes and run this script again selecting no";  return;;
        No ) make; break;;
    esac
done



VAR1=/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B23MuNuMCallvar_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_CombBasic.root
VAR2=/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic.root
 

VAR4=10


weight=W

read -p "SPECIFY NAME OF THE TRAINING? " -e trainingname
echo Your trainingname is $trainingname
echo Your trainingname is $trainingname > /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt

read -p "SPECIFY TAG you want to use to apply BDT/ could be also TRAINING NAME? " -e tag
echo Your TAG is $tag
echo Your TAG is $tag >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt

read -p "SPECIFY THE NAME OF THE BDT BRANCH in TRAINING? " -e bdt
echo Your BDTBranch is $bdt
echo Your BDTBranch is $bdt >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt



dktree=DecayTree


echo "Changing directory to BDTtrainings to get the training"

cd /vols/lhcb/ss4314/BDTtrainings/$trainingname

echo "Copying weights to bin directory"

cp -rf weights/ /vols/lhcb/ss4314/BDTrunonsamples/bin/

echo "Copying_CombBasic_CombBasic.root files bin directory"

cp -rf tmva/ /vols/lhcb/ss4314/BDTrunonsamples/bin/


echo "Running on usual files"


echo "Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root" >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt



for runfile in /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuData2016_corrmLSDfull_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_KaonPID_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_287905280_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_287905283_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_287905284_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_287905285_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288495113_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288626185_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288691721_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288757257_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288822793_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288822798_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888329_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888334_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888337_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888338_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_287905280_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_287905283_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_287905284_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_287905285_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288495113_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288626185_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288691721_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288757257_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288822793_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288822798_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888329_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888334_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888337_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888338_Hlt1TrackMuonDecision_trigger_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root

do

	echo "This is runfile"

	echo $runfile


	echo "Copying the runfile into dataset directory"

	cp $runfile /vols/lhcb/ss4314/BDTrunonsamples/datasets/

done

for myfile in Bu23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut_CombBasic.root Bu23MuNuData2016_corrmLSDfull_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut_CombBasic.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_CombBasic.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_CombBasic.root Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_KaonPID_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_trigger_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_287905280_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_287905283_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_287905284_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_287905285_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288495113_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288626185_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288691721_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288757257_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288822793_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288822798_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888329_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888334_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888337_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888338_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_287905280_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_287905283_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_287905284_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_287905285_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288495113_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288626185_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288691721_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288757257_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288822793_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288822798_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888329_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888334_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888337_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888338_Hlt1TrackMuonDecision_trigger_CombBasic.root B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic.root


do

	newrunfileloc=/vols/lhcb/ss4314/BDTrunonsamples/datasets/$myfile

	cd /vols/lhcb/ss4314/BDTrunonsamples/bin/


	file="./kfoldbacknomu1mu3"
        echo "the option is $file" >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt
	if [ -e $file ]; then
		echo "File exists"
		$file -s $VAR1 -b $VAR2 -k $VAR4 --sig-tree $dktree --bkg-tree $dktree  -w $weight  --bdt $bdt  -r $newrunfileloc


	else 
		echo "File does not exits, I will not do anything. Just saying..."

	fi

	echo "Coppying trained and applied BDT"

	mkdir /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag

	cp $newrunfileloc /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag
       
done


echo "put all training into /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag"
echo "put all training into /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag" >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt
cp  /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt  /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag
 
echo "FINISHED"