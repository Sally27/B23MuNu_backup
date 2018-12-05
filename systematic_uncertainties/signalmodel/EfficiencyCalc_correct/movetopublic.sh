#!/bin/bash

mkdir /home/hep/ss4314/public_html/getsyst/
mkdir /home/hep/ss4314/public_html/getsyst/SignalModel_correct
mkdir /home/hep/ss4314/public_html/getsyst/SignalModel_correct/PHSP


cp bin/*.pdf /home/hep/ss4314/public_html/getsyst/SignalModel_correct/PHSP

cp bin/*.tex /home/hep/ss4314/public_html/getsyst/SignalModel_correct/PHSP
echo $PWD >> pathtocode.txt

cp pathtocode.txt /home/hep/ss4314/public_html/getsyst/SignalModel_correct/

varprepath=getsyst/SignalModel_correct

mkdir /home/hep/ss4314/public_html/$varprepath/code_calculation

cp -r include /home/hep/ss4314/public_html/$varprepath/code_calculation/
cp -r src /home/hep/ss4314/public_html/$varprepath/code_calculation/

cp Makefile /home/hep/ss4314/public_html/$varprepath/code_calculation/
cp *sh /home/hep/ss4314/public_html/$varprepath/code_calculation/


