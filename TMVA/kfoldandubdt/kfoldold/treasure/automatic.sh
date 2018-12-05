#!/bin/bash
#lb-run \
VAR1=/vols/lhcbdisk05/ss4314/TMVA/kfoldold/test/my1000signal.root

VAR2=/vols/lhcbdisk05/ss4314/TMVA/kfoldold/test/my1000background.root
 
VAR3=output


cd /vols/lhcbdisk05/ss4314/TMVA/kfoldold/bin

file="./kfold"
if [ -e $file ]; then
	echo "File exists"
	$file -s $VAR1 -b $VAR2 -o $VAR3
else 
	echo "File does not exits"

fi

echo $VAR1 $VAR2 $VAR3


