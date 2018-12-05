
simold=FUMSB_simultaneous_add2016_scalesig
notsimold=FUMSB_NOTsimultaneous_add2016_scalesig
sim=FUMSB_simultaneous_NewTCK_PIDoptimisation #NEW simultaneous year
notsim=FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation #NEW NOT simultaneous year
#---------------------------------ADD weights trainingname SS 2016-----------------------#

#
#mkdir $notsim
#
#sourc=FUMSB_simultaneous_symmetric_newcontrolchannel_nojackweight #for now CHANGE THIS
#
#
sourc=$sim
desti=$sim


sourc2=$notsim
desti2=$notsim



cd /vols/lhcb/ss4314/cutonProbnnmuMisidSamples

#mkdir $sim
mkdir $notsim

#sourc=$simold
#sourc2=$notsimold
#desti=$sim
#desti2=$notsim
#
#cp $sourc/* $desti/
#cp -r $sourc/src $desti/
#cp -r $sourc/include $desti/
#mkdir $desti/bin
#mkdir $desti/obj
#mkdir $desti/docs
#
#
#
#cp $sourc2/* $desti2/
#cp -r $sourc2/src $desti2/
#cp -r $sourc2/include $desti2/
#mkdir $desti2/bin
#mkdir $desti2/obj
#mkdir $desti2/docs


#
#
###----------------------------------CUT ON PROBNNMU---------------#
##
##
#cd /vols/lhcb/ss4314/cutonProbnnmuMisidSamples
#
#mkdir $sim
#
#cd $sim
####
#make clean
#make
###
#cd bin
#
#cp /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/LFCME/* /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/
#cp /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/HFCME/* /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/
#cp /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/LFCME/* /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/
#cp /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/HFCME/* /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/
#
#
#cp /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/LFCME/* /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/
#cp /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/HFCME/* /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/
#cp /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/LFCME/* /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/
#cp /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/HFCME/* /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/
#
###
##./main2 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Kaon High
##./main2 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Kaon Low
##./main2 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Pion High
##./main2 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Pion Low
##./main2 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Proton High
##./main2 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Proton Low
#
#
#./main2016 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/ Bu23MuNuData2016_SSmisid Kaon High
#./main2016 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/ Bu23MuNuData2016_SSmisid Kaon Low
#./main2016 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/ Bu23MuNuData2016_SSmisid Pion High
#./main2016 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/ Bu23MuNuData2016_SSmisid Pion Low
#./main2016 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/ Bu23MuNuData2016_SSmisid Proton High
#./main2016 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/ Bu23MuNuData2016_SSmisid Proton Low
#
#
#./mainRun1 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Kaon High
#./mainRun1 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Kaon Low
#./mainRun1 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Pion High
#./mainRun1 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Pion Low
#./mainRun1 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Proton High
#./mainRun1 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Proton Low
#
#
##./mainos /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Kaon High
##./mainos /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Kaon Low
##./mainos /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Pion High
##./mainos /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Pion Low
##./mainos /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Proton High
##./mainos /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Proton Low
#
#
#./mainos2016 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Kaon High
#./mainos2016 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Kaon Low
#./mainos2016 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Pion High
#./mainos2016 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Pion Low
#./mainos2016 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Proton High
#./mainos2016 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Proton Low
#
#
#./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Kaon High
#./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Kaon Low
#./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Pion High
#./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Pion Low
#./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Proton High
#./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Proton Low
#latex EfficienciesProbnnmu3.tex
##
#mkdir ~/public_html/cutonProbnnmuMisidSamples
#mkdir ~/public_html/cutonProbnnmuMisidSamples/$sim
#
##
#cp *tex ~/public_html/cutonProbnnmuMisidSamples/$sim/
#
#
#
cd /vols/lhcb/ss4314/cutonProbnnmuMisidSamples

#cp /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuples2016/LFCME/* /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuples2016/
#cp /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuples2016/HFCME/* /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuples2016/

mkdir $notsim

cd $notsim
###
make clean
make
##
cd bin
##
#./main2 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Kaon
#./main2 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Pion
#./main2 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Proton


./main2016 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuples2016/ Bu23MuNuData2016_SSmisid Kaon 
./main2016 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuples2016/ Bu23MuNuData2016_SSmisid Pion 
./main2016 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuples2016/ Bu23MuNuData2016_SSmisid Proton 


./mainRun1 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Kaon 
./mainRun1 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Pion 
./mainRun1 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Proton

 
#./mainos /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Kaon 
#./mainos /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Pion 
#./mainos /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Proton 


./mainos2016 /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Kaon 
./mainos2016 /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Pion 
./mainos2016 /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Proton 


./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Kaon 
./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Pion 
./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Proton

 
mkdir ~/public_html/cutonProbnnmuMisidSamples
mkdir ~/public_html/cutonProbnnmuMisidSamples/$notsim
#
##
cp *tex ~/public_html/cutonProbnnmuMisidSamples/$notsim/

