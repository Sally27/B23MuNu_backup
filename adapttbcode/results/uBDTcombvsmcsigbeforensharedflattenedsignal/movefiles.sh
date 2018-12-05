#!/bin/bash
#lb-run \


VAR1=/vols/lhcbdisk05/ss4314/adapttbcode/results/uBDTcombvsmcsigbeforensharedflattenedsignal/

mkdir $VAR1

$VAR2=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/CombinatorialBackground25000.root



cp * $VAR1

cp -rf src/ $VAR1

cp -rf include/ $VAR1

cp makefile $VAR1

cp setup.sh $VAR1
