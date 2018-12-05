#!/bin/bash
#lb-run \


VAR1=/vols/lhcbdisk05/ss4314/adapttbcode/results/MisidAFTER400treescombinatorial/

mkdir $VAR1


cp * $VAR1

cp -rf src/ $VAR1

cp -rf include/ $VAR1

cp makefile $VAR1

cp setup.sh $VAR1
