
simold=FUMSB_simultaneous_NewTCK
notsimold=FUMSB_NOTsimultaneous_NewTCK
sim=FUMSB_simultaneous_NewTCK_misidvariation #NEW simultaneous year
notsim=FUMSB_NOTsimultaneous_NewTCK_misidvariation #NEW NOT simultaneous year
#---------------------------------ADD weights trainingname SS 2016-----------------------#

#
#mkdir $notsim
#
#sourc=FUMSB_simultaneous_symmetric_newcontrolchannel_nojackweight #for now CHANGE THIS
#
#
#sourc=$sim
#desti=$sim
#
#
#sourc2=$notsim
#desti2=$notsim
#
#
#
#cd /vols/lhcb/ss4314/cutonProbnnmuMisidSamples
#
#mkdir $sim
#mkdir $notsim
#
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
###
#
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
#
#for ntoy in {0..100..1}
#
#do
#
#    echo $ntoy
#
#
#    
#    ##
#    #./main2 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Kaon High
#    #./main2 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Kaon Low
#    #./main2 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Pion High
#    #./main2 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Pion Low
#    #./main2 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Proton High
#    #./main2 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Proton Low
#    
#    
#    ./main2016 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/ Bu23MuNuData2016_SSmisid Kaon High $ntoy
#    ./main2016 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/ Bu23MuNuData2016_SSmisid Kaon Low $ntoy
#    ./main2016 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/ Bu23MuNuData2016_SSmisid Pion High $ntoy
#    ./main2016 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/ Bu23MuNuData2016_SSmisid Pion Low $ntoy
#    ./main2016 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/ Bu23MuNuData2016_SSmisid Proton High $ntoy
#    ./main2016 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuples2016/ Bu23MuNuData2016_SSmisid Proton Low $ntoy
#    
#    
#    ./mainRun1 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Kaon High $ntoy
#    ./mainRun1 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Kaon Low $ntoy
#    ./mainRun1 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Pion High $ntoy
#    ./mainRun1 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Pion Low $ntoy
#    ./mainRun1 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Proton High $ntoy
#    ./mainRun1 /vols/lhcb/ss4314/addPIDweights/$sim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Proton Low $ntoy
#    
#    
#    #./mainos /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Kaon High
#    #./mainos /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Kaon Low
#    #./mainos /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Pion High
#    #./mainos /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Pion Low
#    #./mainos /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Proton High
#    #./mainos /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Proton Low
#    
#    
#    ./mainos2016 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Kaon High $ntoy
#    ./mainos2016 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Kaon Low $ntoy
#    ./mainos2016 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Pion High $ntoy
#    ./mainos2016 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Pion Low $ntoy
#    ./mainos2016 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Proton High $ntoy
#    ./mainos2016 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Proton Low $ntoy
#    
#    
#    ./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Kaon High $ntoy
#    ./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Kaon Low $ntoy
#    ./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Pion High $ntoy
#    ./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Pion Low $ntoy
#    ./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Proton High $ntoy
#    ./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$sim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Proton Low $ntoy
#   
#    #
#    mkdir ~/public_html/cutonProbnnmuMisidSamples
#    mkdir ~/public_html/cutonProbnnmuMisidSamples/$sim
#    
#    #
#    cp *tex ~/public_html/cutonProbnnmuMisidSamples/$sim/
#
#done
#
#
#
cd /vols/lhcb/ss4314/cutonProbnnmuMisidSamples


mkdir $notsim

cd $notsim
####

SetupProject Urania v5r0

#make clean


make
##
cd bin
##
##./main2 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Kaon
##./main2 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Pion
##./main2 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuples2015/ B23MuNuFakeSS_2015_DV41r2 Proton

#rm *pdf
#rm *txt
for ntoy in {0..100..1}

do

    echo $ntoy


#    ./main2016 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuples2016/ Bu23MuNuData2016_SSmisid Kaon $ntoy 
#    ./main2016 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuples2016/ Bu23MuNuData2016_SSmisid Pion $ntoy
#    ./main2016 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuples2016/ Bu23MuNuData2016_SSmisid Proton $ntoy
#    
#    
#    ./mainRun1 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Kaon $ntoy 
#    ./mainRun1 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Pion $ntoy
#    ./mainRun1 /vols/lhcb/ss4314/addPIDweights/$notsim/finaltuplesRun1/ Data_B23MuNu_MisidSS_Run1 Proton $ntoy
    
     
    ##./mainos /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Kaon 
    ##./mainos /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Pion 
    ##./mainos /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuples2015/ B23MuNuFakeOS_2015_DV41r2 Proton 
    
    
#    ./mainos2016 /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Kaon $ntoy
#    ./mainos2016 /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Pion $ntoy
#    ./mainos2016 /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuples2016/ Bu23MuNuData2016_OSmisid Proton $ntoy
    
    
    ./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Kaon $ntoy
    ./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Pion $ntoy
    ./mainosRun1 /vols/lhcb/ss4314/addPIDweights/$notsim/os/finaltuplesRun1/ Data_B23MuNu_MisidOS_Run1 Proton $ntoy
    
     
    mkdir ~/public_html/cutonProbnnmuMisidSamples
    mkdir ~/public_html/cutonProbnnmuMisidSamples/$notsim
    #
    ##
    cp *tex ~/public_html/cutonProbnnmuMisidSamples/$notsim/


done
#
