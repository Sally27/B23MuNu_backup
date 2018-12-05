#!/bin/bash
#lb-run \


cd diffvs

#SET Today=%Date:~10,4%_%Date:~7,2%_%Data:~4,2%

#echo %Today%

name=60treesCombinatorialSamplevsMCSigNormalBDT

if [ -d "$name" ] ; then
	i=0
        echo "PUF1"
	while [ -d "$name-$i" ] ; do
		let i++
		echo "PUF2"
	done
	name="$name-$i"
fi
mkdir $name

cd $name
#mkdir $(date +%F--%T)
#VAR1=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/B23MuNuNewMCsamplecutqmin2.root

#VAR2=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/CombinatorialBackgroundcutqmin.root
#VAR1=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/newsamples_qsqandnsharedcut/B23MuNuSignal2012and2011data_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_corrm.root

#VAR2=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/newsamples_qsqandnsharedcut/B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut.root
#VAR2=/vols/lhcbdisk05/ss4314/cutonBDTs/fullsetwithJpsi400treesincludeP/B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_400andPPUNZIoptBDT.root


#VAR1=/vols/lhcbdisk05/ss4314/cutonBDTs/fullsetwithJpsi400treesincludeP/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_400andPPUNZIoptBDT.root

VAR2=/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinal/Combinatorialpreparetuple/B23MuNuSignal2012and2011data_corrm_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmin.root

VAR1=/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinal/MCSigpreparetuple/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root


#VAR2=/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinal/SSmuonStrSmallDatapreparetuple/B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut.root

#VAR1=/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinal/MCSigpreparetuple/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root



#VAR1=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/newsamples_qsqandnsharedcutbutnotcutonnshared/B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut.root

#VAR2=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/newsamples_qsqandnsharedcutbutnotcutonnshared/B23MuNuNewMCNShared_MCtruth_Jpsi_qmincut.root



#VAR0="B23MuNuNewMCsamplecutqmin2.root"
#VAR1="CombinatorialBackgroundcutqmin.root"

cp $VAR1 .

cp $VAR2 .

#cp
 
#VAR3=output

#VAR4=2

#VAR5=Bplus_P;
#VAR6=mu1_P;
#VAR7=mu3_PT;
#VAR8=mu1_MINIP;
#VAR9=mu2_ghost;
#VAR10=mu1_TRACK_CHI2;

#declare -a mine=( 'Bplus_P' ,  'mu3_ghost')
#("mu1_MINIP")("mu3_ghost")("mu1_TRACK_CHI2")("mu2_TRACK_CHI2")("mu2_MINIPCHI2")("Bplus_ENDVERTEX_CHI2")


cp -rf /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/guiandstuff/plots .
cp -rf /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/bin/tmva .
cp -rf /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/src .
cp -rf /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/bin/weights .
cp /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/Makefile .
cp -rf /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/run/ .

cp -rf /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/diffvs/$name /vols/lhcbdisk05/ss4314/BDTtrainings/

#rm -f *


#cd /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/bin

#file="./ukfold"
#if [ -e $file ]; then
#	echo "File exists"
#	$file -s $VAR1 -b $VAR2 -o $VAR3 -k $VAR4 -v $VAR5 -v $VAR6 -v $VAR7 -v $VAR8 -v $VAR9 -v $VAR10
 
#for i in "${mine[@]}"
#else 
#	echo "File does not exits, I will not do anything. Just saying..."

#fi

#echo $VAR1 $VAR2 $VAR3


