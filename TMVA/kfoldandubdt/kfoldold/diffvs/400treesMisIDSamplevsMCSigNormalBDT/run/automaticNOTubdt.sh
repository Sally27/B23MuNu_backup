#!/bin/bash
#lb-run \


#. ~lhcb/grouplogin/lhcb_login.sh

#LbLogin -c x86_64-slc6-gcc46-opt
#SetupProject Urania

#export TMVALOC=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/optimizedubdt/uboost/TMVA-v4.1.2
#export LD_LIBRARY_PATH=$TMVALOC/lib/:$LD_LIBRARY_PATH
#echo "$TMVALOC"
DEND_PATH=/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH



VAR2=/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinal/SSmuonStrSmallDatapreparetuple/B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut.root

VAR1=/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinal/MCSigpreparetuple/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root

cp $VAR2 /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/
cp $VAR1 /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/


sig=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root
bkg=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut.root

 
VAR3=MisIDNormalBDTfinal400TreesandP

VAR4=10

#VAR5=Bplus_P;
#VAR6=Bplus_PT;
#VAR10=mu1_PT;
#VAR11=mu2_PT;
#VAR12=mu3_PT;
#VAR13=mu1_MINIPCHI2;
#VAR14=mu2_MINIPCHI2;
#VAR15=mu3_MINIPCHI2;
#VAR16=Bplus_TAU;
#VAR17=Bplus_DIRA_OWNPV;
#VAR18=Bplus_ENDVERTEX_CHI2;
#VAR19=Bplus_FD_CHI2;
#VAR20=Bplus_pmu_ISOLATION_BDT1_weights;
#VAR21=mu1_Xmu_SV_CHI2;


weight=W

#declare -a mine=( 'Bplus_P' ,  'mu3_ghost')
#("mu1_MINIP")("mu3_ghost")("mu1_TRACK_CHI2")("mu2_TRACK_CHI2")("mu2_MINIPCHI2")("Bplus_ENDVERTEX_CHI2")


cd /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/guiandstuff/plots/

rm -f *

#rm -f /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/bin/tmva/* 
#rm -f /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/bin/weights/* .



cd /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/bin

file="./kfold"
if [ -e $file ]; then
	echo "File exists"
	$file -s $sig -b $bkg -o $VAR3 -k $VAR4 -w $weight "all" 
#for i in "${mine[@]}"
else 
	echo "File does not exits, I will not do anything. Just saying..."

fi

echo $VAR1 $VAR2 $VAR3


