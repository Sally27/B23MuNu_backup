
trainingname=FUMSB_simultaneous_add2016 #NEW simultaneous year
tag=FUMSB_NOTsimultaneous_add2016 #NEW NOT simultaneous year
tn=_scalesig
#---------------------------------ADD weights trainingname SS 2016-----------------------#

#
#mkdir $tag
#
#sourc=FUMSB_simultaneous_symmetric_newcontrolchannel_nojackweight #for now CHANGE THIS
#
#
###----------------------------------CUT ON PROBNNMU---------------#
##
##
cd /vols/lhcb/ss4314/cutonProbnnmuMisidSamples

mkdir $trainingname$tn

cd $trainingname$tn
###
make clean
make
##
cd bin
##
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Kaon High
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Kaon Low
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Pion High
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Pion Low
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Proton High
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Proton Low


./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuples2016/ B23MuNuFakeSS_2016 Kaon High
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuples2016/ B23MuNuFakeSS_2016 Kaon Low
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuples2016/ B23MuNuFakeSS_2016 Pion High
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuples2016/ B23MuNuFakeSS_2016 Pion Low
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuples2016/ B23MuNuFakeSS_2016 Proton High
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuples2016/ B23MuNuFakeSS_2016 Proton Low


./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuplesRun1/ B23MuNuFakeSStotal Kaon High
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuplesRun1/ B23MuNuFakeSStotal Kaon Low
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuplesRun1/ B23MuNuFakeSStotal Pion High
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuplesRun1/ B23MuNuFakeSStotal Pion Low
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuplesRun1/ B23MuNuFakeSStotal Proton High
./main2 /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/finaltuplesRun1/ B23MuNuFakeSStotal Proton Low


./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Kaon High
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Kaon Low
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Pion High
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Pion Low
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Proton High
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Proton Low


./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuples2016/ B23MuNuFakeOS_2016 Kaon High
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuples2016/ B23MuNuFakeOS_2016 Kaon Low
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuples2016/ B23MuNuFakeOS_2016 Pion High
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuples2016/ B23MuNuFakeOS_2016 Pion Low
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuples2016/ B23MuNuFakeOS_2016 Proton High
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuples2016/ B23MuNuFakeOS_2016 Proton Low


./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuplesRun1/ B23MuNuFakeOStotal Kaon High
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuplesRun1/ B23MuNuFakeOStotal Kaon Low
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuplesRun1/ B23MuNuFakeOStotal Pion High
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuplesRun1/ B23MuNuFakeOStotal Pion Low
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuplesRun1/ B23MuNuFakeOStotal Proton High
./mainos /vols/lhcb/ss4314/addPIDweights/$trainingname$tn/os/finaltuplesRun1/ B23MuNuFakeOStotal Proton Low
latex EfficienciesProbnnmu3.tex
#
mkdir ~/public_html/cutonProbnnmuMisidSamples
mkdir ~/public_html/cutonProbnnmuMisidSamples/$trainingname$tn

#
cp *tex ~/public_html/cutonProbnnmuMisidSamples/$trainingname$tn/



#cd /vols/lhcb/ss4314/cutonProbnnmuMisidSamples
#
#mkdir $tag$tn
#
#cd $tag$tn
####
#make clean
#make
###
#cd bin
###
#./main2 /vols/lhcb/ss4314/addPIDweights/$tag$tn/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Kaon
#./main2 /vols/lhcb/ss4314/addPIDweights/$tag$tn/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Pion
#./main2 /vols/lhcb/ss4314/addPIDweights/$tag$tn/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Proton
#
#
#./main2 /vols/lhcb/ss4314/addPIDweights/$tag$tn/finaltuples2016/ B23MuNuFakeSS_2016 Kaon 
#./main2 /vols/lhcb/ss4314/addPIDweights/$tag$tn/finaltuples2016/ B23MuNuFakeSS_2016 Pion 
#./main2 /vols/lhcb/ss4314/addPIDweights/$tag$tn/finaltuples2016/ B23MuNuFakeSS_2016 Proton 
#
#
#./main2 /vols/lhcb/ss4314/addPIDweights/$tag$tn/finaltuplesRun1/ B23MuNuFakeSStotal Kaon 
#./main2 /vols/lhcb/ss4314/addPIDweights/$tag$tn/finaltuplesRun1/ B23MuNuFakeSStotal Pion 
#./main2 /vols/lhcb/ss4314/addPIDweights/$tag$tn/finaltuplesRun1/ B23MuNuFakeSStotal Proton
#
# 
#./mainos /vols/lhcb/ss4314/addPIDweights/$tag$tn/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Kaon 
#./mainos /vols/lhcb/ss4314/addPIDweights/$tag$tn/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Pion 
#./mainos /vols/lhcb/ss4314/addPIDweights/$tag$tn/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Proton 
#
#
#./mainos /vols/lhcb/ss4314/addPIDweights/$tag$tn/os/finaltuples2016/ B23MuNuFakeOS_2016 Kaon 
#./mainos /vols/lhcb/ss4314/addPIDweights/$tag$tn/os/finaltuples2016/ B23MuNuFakeOS_2016 Pion 
#./mainos /vols/lhcb/ss4314/addPIDweights/$tag$tn/os/finaltuples2016/ B23MuNuFakeOS_2016 Proton 
#
#
#./mainos /vols/lhcb/ss4314/addPIDweights/$tag$tn/os/finaltuplesRun1/ B23MuNuFakeOStotal Kaon 
#./mainos /vols/lhcb/ss4314/addPIDweights/$tag$tn/os/finaltuplesRun1/ B23MuNuFakeOStotal Pion 
#./mainos /vols/lhcb/ss4314/addPIDweights/$tag$tn/os/finaltuplesRun1/ B23MuNuFakeOStotal Proton
#
# 
#mkdir ~/public_html/cutonProbnnmuMisidSamples
#mkdir ~/public_html/cutonProbnnmuMisidSamples/$tag$tn
##
###
#cp *tex ~/public_html/cutonProbnnmuMisidSamples/$tag$tn/
#
