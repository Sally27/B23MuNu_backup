#!/bin/bash
#lb-run \

export TMVALOC=/afs/cern.ch/work/s/slstefko/optimizedubdt/uboost/TMVA-v4.1.2/
export LD_LIBRARY_PATH=$TMVALOC/lib/:$LD_LIBRARY_PATH
echo "$TMVALOC"
DEND_PATH=/afs/cern.ch/work/s/slstefko/kfoldoldandubdt/dendrology-master/TMVA/dendrology-master/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH




VAR2=/afs/cern.ch/work/s/slstefko/kfoldoldandubdt/kfoldold/datasets/newdatasets_combinatorial/B23MuNuSignal2012and2011data_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_corrm.root

VAR1=/afs/cern.ch/work/s/slstefko/kfoldoldandubdt/kfoldold/datasets/newdatasets_combinatorial/B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut.root
 
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

#declare -a mine=( 'Bplus_P' ,  'mu3_ghost')
#("mu1_MINIP")("mu3_ghost")("mu1_TRACK_CHI2")("mu2_TRACK_CHI2")("mu2_MINIPCHI2")("Bplus_ENDVERTEX_CHI2")


cd /afs/cern.ch/work/s/slstefko/kfoldoldandubdt/kfoldold/guiandstuff/plots/

rm -f *


cd /afs/cern.ch/work/s/slstefko/kfoldoldandubdt/kfoldold/bin

file="./ukfold"
if [ -e $file ]; then
	echo "File exists"
	$file -s $VAR1 -b $VAR2 -o $VAR3 -k $VAR4 -w $weight -v $VAR5 -v $VAR6 -v $VAR10 -v $VAR11 -v $VAR12 -v $VAR13 -v $VAR14 -v $VAR15 -v $VAR16 -v $VAR17 -v $VAR18 -v $VAR19 -v $VAR20 -v $VAR21
#for i in "${mine[@]}"
else 
	echo "File does not exits, I will not do anything. Just saying..."

fi

echo $VAR1 $VAR2 $VAR3


