#!/bin/bash
#lb-run \


cd diffvs

#SET Today=%Date:~10,4%_%Date:~7,2%_%Data:~4,2%

#echo %Today%

name=uBDTandKfoldrun

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

VAR0="B23MuNuNewMCsamplevetoJpsi.root"
VAR1="CombinatorialBackgroundvetoJpsi.root"

cp /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/$VAR0 .

cp /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/$VAR1 .

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


