#!/bin/bash
#lb-run \


VAR1=/vols/lhcb/ss4314/adapttbcode/results/MCSig2016_288888335_vs_DATACMisid2016_finalmisidtemplate/

mkdir $VAR1


cp bin/* $VAR1

cp -rf src/ $VAR1

cp -rf include/ $VAR1

cp makefile $VAR1

cp setup.sh $VAR1


VAR2=/home/hep/ss4314/public_html/BDTtrainings/MCSig2016_288888335_vs_DATACMisid2016_finalmisidtemplate/

mkdir $VAR2

cp bin/* $VAR2
