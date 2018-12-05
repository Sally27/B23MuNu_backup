#!/bin/bash
#lb-run \


cd analysisofubdt


#SET Today=%Date:~10,4%_%Date:~7,2%_%Data:~4,2%

#echo %Today%

name=uBDTqsqnocutfold0to9

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

cp ../../*.pdf .
cp ../../*.eps .
cp ../../*.root .
cp ../../*.txt .
cp -rf ../../src .


#VAR0="B23MuNuNewMCsamplevetoJpsi.root"
#VAR1="CombinatorialBackgroundvetoJpsi.root"

#cp -rf /afs/cern.ch/work/s/slstefko/kfoldoldandubdt/kfoldold/datasets/$VAR0 .

#cp -rf /afs/cern.ch/work/s/slstefko/kfoldoldandubdt/kfoldold/datasets/$VAR1 .
