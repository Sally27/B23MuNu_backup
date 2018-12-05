#!/bin/bash
#lb-run \
VAR1=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/B23MuNuNewMCsample25000.root

VAR2=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/CombinatorialBackground25000.root
 
VAR3=output

VAR4=2

VAR5=Bplus_P;
VAR6=Bplus_PT;
VAR7=mu1_P;
VAR8=mu2_P;
VAR9=mu3_P;
VAR10=mu1_PT;
VAR11=mu2_PT;
VAR12=mu3_PT;
VAR13=mu1_MINIPCHI2;
VAR14=mu2_MINIPCHI2;
VAR15=mu3_MINIPCHI2;
VAR16=Bplus_TAU;
VAR17=Bplus_DIRA_OWNPV;
VAR18=Bplus_ENDVERTEX_CHI2;


weight=W

#declare -a mine=( 'Bplus_P' ,  'mu3_ghost')
#("mu1_MINIP")("mu3_ghost")("mu1_TRACK_CHI2")("mu2_TRACK_CHI2")("mu2_MINIPCHI2")("Bplus_ENDVERTEX_CHI2")


cd /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/guiandstuff/plots/

rm -f *


cd /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/bin

file="./ukfold"
if [ -e $file ]; then
	echo "File exists"
	$file -s $VAR1 -b $VAR2 -o $VAR3 -k $VAR4 -w $weight -v $VAR5 -v $VAR6 -v $VAR7 -v $VAR8 -v $VAR9 -v $VAR10 -v $VAR11 -v $VAR12 -v $VAR13 -v $VAR14 -v $VAR15 -v $VAR16 -v $VAR17 -v $VAR18
 
#for i in "${mine[@]}"
else 
	echo "File does not exits, I will not do anything. Just saying..."

fi

echo $VAR1 $VAR2 $VAR3


