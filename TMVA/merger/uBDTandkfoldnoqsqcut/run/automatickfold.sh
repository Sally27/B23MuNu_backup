#!/bin/bash
#lb-run \
VAR1=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/26may/my5000signal.root

VAR2=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/26may/my5000background.root
 
VAR3=output

VAR4=2


cd /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/27may/plots/

rm -f *


cd /vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/bin

file="./kfold"
if [ -e $file ]; then
	echo "File exists"
	$file -s $VAR1 -b $VAR2 -o $VAR3 -k $VAR4
else 
	echo "File does not exits, I will not do anything. Just saying..."

fi

echo $VAR1 $VAR2 $VAR3


