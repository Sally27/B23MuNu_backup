#!/bin/bash
#lb-run \
#export TMVALOC=/afs/cern.ch/work/s/slstefko/optimizedubdt/uboost/TMVA-v4.1.2/
#export LD_LIBRARY_PATH=$TMVALOC/lib/:$LD_LIBRARY_PATH
#echo "$TMVALOC"
#DEND_PATH=/afs/cern.ch/work/s/slstefko/kfoldoldandubdt/dendrology-master/TMVA/dendrology-master/lib
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH

### THE ONLY THING YOU NEED TO CHANGE is the runfile and newrunfileloc VARIABLES ###
### START to use sensible names for yout bdts otherwise there will be mess ###

#. ~lhcb/grouplogin/lhcb_login.sh

#LbLogin -c x86_64-slc6-gcc46-opt
#SetupProject Urania v2r0p1

#export TMVALOC=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/optimizedubdt/uboost/TMVA-v4.1.2
#export LD_LIBRARY_PATH=$TMVALOC/lib/:$LD_LIBRARY_PATH
#echo "$TMVALOC"
DEND_PATH=/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH

VAR1=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/newsamples_qsqandnsharedcut/B23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut.root

VAR2=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/newsamples_qsqandnsharedcut/B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut.root

 
VAR3=output

VAR4=10

VAR5=Bplus_P;
VAR6=Bplus_PT;
VAR10=mu1_PT;
VAR11=mu2_PT;
VAR12=mu3_PT;
VAR13=mu1_MINIPCHI2;
VAR14=mu2_MINIPCHI2;
VAR15=mu3_MINIPCHI2;
VAR16=Bplus_TAU;
VAR17=Bplus_DIRA_OWNPV;
VAR18=Bplus_ENDVERTEX_CHI2;
VAR19=Bplus_FD_CHI2;
VAR20=Bplus_pmu_ISOLATION_BDT1_weights;
VAR21=mu1_Xmu_SV_CHI2;

weight=W

#dirname=/vols/lhcbdisk05/ss4314/BDTtrainings/
trainingname=qsqcutnSharedCombinatorialSamplevsMCSigNormalBDT
#runfilename=B23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut.root
tag=normalBDTCombvsMCqsqcutonPIONmisid
runfile=/vols/lhcbdisk05/ss4314/BDTrunonsamples/datasets/B23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_PionPID.root
myfile=B23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_PionPID.root

bdt=CombinatorialNormalBDTNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection
dktree=DecayTree


echo "This is runfile"

echo $runfile

echo "Changing directory to BDTtrainings to get the training"

cd /vols/lhcbdisk05/ss4314/BDTtrainings/$trainingname

echo "Copying weights to bin directory"

cp -rf weights/ /vols/lhcbdisk05/ss4314/BDTrunonsamples/bin/

echo "Copying root files bin directory"

cp -rf tmva/ /vols/lhcbdisk05/ss4314/BDTrunonsamples/bin/

echo "Copying the runfile into dataset directory"

#cp $runfile /vols/lhcbdisk05/ss4314/BDTrunonsamples/datasets/

newrunfileloc=/vols/lhcbdisk05/ss4314/BDTrunonsamples/datasets/$myfile

cd /vols/lhcbdisk05/ss4314/BDTrunonsamples/bin/


file="./kfold"
if [ -e $file ]; then
	echo "File exists"
	$file -s $VAR1 -b $VAR2 -k $VAR4 --sig-tree $dktree --bkg-tree $dktree  -w $weight  --bdt $bdt  -r $newrunfileloc


else 
	echo "File does not exits, I will not do anything. Just saying..."

fi

echo "Coppying trained and applied BDT"

mkdir /vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag

cp $newrunfileloc /vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag
