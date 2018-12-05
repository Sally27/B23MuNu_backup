#!/bin/bash
#. LbLogin.sh -c x86_64-slc6-gcc46-opt
. SetupProject.sh Urania v5r0 #v2r0p1

#export TMVALOC=/vols/lhcb/ss4314/TMVA/kfoldandubdt/optimizedubdt/uboost/TMVA-v4.1.2
#export LD_LIBRARY_PATH=$TMVALOC/lib/:$LD_LIBRARY_PATH
#echo "$TMVALOC"
DEND_PATH=/vols/lhcb/ss4314/TMVA/dendrology-master/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH

make clean

echo "Do you wish to change input variables or options for BDT?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) cd src/; echo "Do your changes and run this script again selecting no";  return;;
        No ) make; break;;
    esac
done


DEND_PATH=/vols/lhcb/ss4314/TMVA/dendrology-master/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH




echo "Summary of Options" > /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/summary.txt 



read -p "Please input path for signal tuple? " -e inputsig
echo Your sigpath is $inputsig
echo Your sigpath is $inputsig >> /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/summary.txt

read -p "Please input signal tuple name? " -e namesig
echo Your signame is $namesig
echo Your signame is $namesig >> /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/summary.txt

read -p "Please input path for bkg tuple? " -e inputbkg
echo Your bkgpath is $inputbkg
echo Your bkgpath is $inputbkg >> /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/summary.txt

read -p "Please input signal bkg name? " -e namebkg
echo Your bkgname is $namebkg
echo Your bkgname is $namebkg  >> /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/summary.txt



VAR2=$inputbkg/$namebkg

VAR1=$inputsig/$namesig

echo "Your sig is $VAR1 and bkg $VAR2"

echo "Your sig is $VAR1 and bkg $VAR2" >> /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/summary.txt



cp $VAR1 /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/
cp $VAR2 /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/


sig=/vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/$namesig
bkg=/vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/$namebkg

read -p "SPECIFY NAME FOR THIS TRAINING? " -e trainingname
echo Your trainingname is $trainingname

echo Your trainingname is $trainingname >> /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/summary.txt



 
VAR3=$trainingname

VAR4=10



weight=W



cd /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/guiandstuff/plots/

rm -f *

rm -f /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/bin/tmva/* 
rm -f /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/bin/weights/* .


cd /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/bin

file="./kfold"
if [ -e $file ]; then
	echo "File exists"
	$file -s $sig -b $bkg -o $VAR3 -k $VAR4 -w $weight "all" >> /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/summary.txt 
#for i in "${mine[@]}"
else 
	echo "File does not exits, I will not do anything. Just saying..."

fi

echo "finished training and copying all xml and root files"

cd /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/

cd diffvs



name=$trainingname

if [ -d "$name" ] ; then
        i=0
        echo "PUF1"
        while [ -d "$name-$i" ] ; do
                let i++
                echo "Already with this name, creating numbered version"
        done
        name="$name-$i"
fi
mkdir $name

cd $name

echo "Created training in diffvs/$trainingname" >> /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/summary.txt 



cp $VAR1 .
cp $VAR2 .
cp -r /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/guiandstuff/plots .
cp -r /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/bin/tmva .
cp -r /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/src .
cp -r /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/bin/weights .
cp /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/Makefile .
cp -r /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/run/ .
cp -r /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/summary.txt .
cp -rf /vols/lhcb/ss4314/TMVA/kfoldandubdt/kfoldold/diffvs/$trainingname /vols/lhcb/ss4314/BDTtrainings/
echo "finished copying files have a look at training"
#make
