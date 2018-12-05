#!/bin/bash

. SetupProject.sh Urania


echo $PWD
read -p "Please input soft or hard! " -e tag
homepath=$PWD

echo "Summary of Options" > $homepath/$tag+summary.txt

read -p "Please input path for pion tuple to analyze! " -e inputsig
echo Your  pion path is $inputsig
echo Your pion path is $inputsig >> $homepath/$tag+summary.txt

read -p "Please input pion tuple name? " -e namesig
echo Your  pion name is $namesig
echo Your  pion name is $namesig >> $homepath/$tag+summary.txt

read -p "Please input path for kaon tuple " -e inputbkg
echo Your kaon tuple is $inputbkg
echo Your bkgpath is $inputbkg >> $homepath/$tag+summary.txt

read -p "Please input kaon tuple name? " -e namebkg
echo Your kaon is $namebkg
echo Your kaon is $namebkg  >> $homepath/$tag+summary.txt



VAR2=$inputbkg/$namebkg

VAR1=$inputsig/$namesig

echo "Your sig is $VAR1 and bkg $VAR2"

echo "Your sig is $VAR1 and bkg $VAR2" >> $homepath/$tag+summary.txt

make

cp $VAR1 $homepath/bin/
cp $VAR2 $homepath/bin/

cd bin/



echo "You can run main now"

./main $namesig $namebkg > main.txt

mkdir ../$tag/
cp * ../$tag/


