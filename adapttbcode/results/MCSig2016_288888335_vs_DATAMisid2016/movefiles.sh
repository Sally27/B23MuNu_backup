#!/bin/bash
#lb-run \


VAR1=/vols/lhcb/ss4314/adapttbcode/results/MCSig2016_288888335_vs_DATAMisid2016/

mkdir $VAR1


cp * $VAR1

cp -rf src/ $VAR1

cp -rf include/ $VAR1

cp makefile $VAR1

cp setup.sh $VAR1


VAR2=/home/hep/ss4314/public_html/BDTtrainings/MCSig2016_288888335_vs_DATAMisid2016/

mkdir $VAR2

cp * $VAR2
