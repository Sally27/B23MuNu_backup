#!bin/bash/

cd /vols/lhcb/ss4314/addPIDweights/
mkdir FUMSB_NOTsimultaneous_NewTCK_misidvariation

SetupProject Urania v5r0

#sourc=$PWD/estimateformisidbdt_newTCK_Run1
#desti=$PWD/FUMSB_NOTsimultaneous_NewTCK_misidvariation
#
#cp $sourc/* $desti/
#cp -r $sourc/src $desti/
#cp -r $sourc/include $desti/
#
#mkdir $desti/bin
#cp $sourc/bin/*sh $desti/bin/
#
#mkdir $desti/obj
#mkdir $desti/docs
#
#
#sourc2=$PWD/estimateformisidbdt_newTCK_Run1/os
#desti2=$PWD/FUMSB_NOTsimultaneous_NewTCK_misidvariation/os
#
#cp $sourc2/* $desti2/
#cp -r $sourc2/src $desti2/
#cp -r $sourc2/include $desti2/
#
#mkdir $desti2/bin
#cp $sourc2/bin/*sh $desti2/bin/
#
#mkdir $desti2/obj
#mkdir $desti2/docs

#-----------------SS RUN1 tag---------------#

cd /vols/lhcb/ss4313/addPIDweights/
mkdir FUMSB_NOTsimultaneous_NewTCK_misidvariation
cd FUMSB_NOTsimultaneous_NewTCK_misidvariation

#mkdir finaltuples2016
#
#make
#
#rm finaltuples2016/*
#
#cd bin/
#
#
##
#for ntoy in {0..100..1}
#
#
#    do
#
#    echo $ntoy
#
#    rm *pdf
#    rm *txt
#    
#    
#    cp /vols/lhcb/ss4314/misidsplitting/FUMSB_NOTsimultaneous_NewTCK/2016/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip* .
#    cp /vols/lhcb/ss4314/misidsplitting/FUMSB_NOTsimultaneous_NewTCK/2016/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#    cp /vols/lhcb/ss4314/misidsplitting/FUMSB_NOTsimultaneous_NewTCK/2016/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#    #
#    ./main Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip26MagDown.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip26MagDown.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip26MagDown.root MagDown Strip26 $ntoy 100
#    
#    ./main Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip26MagUp.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip26MagUp.root Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip26MagUp.root MagUp Strip26 $ntoy 100
#    
#    
#    genius=modified_andcut_${ntoy}_
#    
#    this=Basiccut
#    var3=Strip26MagDown
#    var4=Strip26MagUp
#    beg=../finaltuples2016/$genius
#    end=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root
#    beg2=$genius
#    end2=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_
#    
#    
#    for wohoo in nShared22 
#    
#    do
#    
#        hadd $beg$wohoo$end $beg2$wohoo$var3$end2$var3.root $beg2$wohoo$var4$end2$var4.root 
#    
#    done
#    
#    beg3=../finaltuples2016/$genius
#    end3=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root
#    beg4=$genius
#    end4=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_
#    
#    for wohoo in nShared22
#    
#    do
#    
#        hadd $beg3$wohoo$end3 $beg4$wohoo$var3$end4$var3.root $beg4$wohoo$var4$end4$var4.root
#    
#    done
#    
#    beg5=../finaltuples2016/$genius
#    end5=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM.root
#    beg6=$genius
#    end6=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_
#    
#    for wohoo in nShared22
#    
#    do
#    
#        hadd $beg5$wohoo$end5 $beg6$wohoo$var3$end6$var3.root $beg6$wohoo$var4$end6$var4.root
#    
#    done
#    
#    
#    
#    
#    mkdir ~/public_html/addPIDweights
#    mkdir ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation
#    mkdir ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/ss/
#    mkdir ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/ss/2016/
#    mkdir ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/ss/2016/$ntoy
#    
#    rm ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/ss/2016/$ntoy/*
#    
#    
#    cp *pdf ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/ss/2016/$ntoy
#    cp *txt ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/ss/2016/$ntoy
#
#done



##-----------------OS RUN1 tag---------------#
cd /vols/lhcb/ss4314/addPIDweights/
cd FUMSB_NOTsimultaneous_NewTCK_misidvariation
cd os

mkdir finaltuples2016

make

rm finaltuples2016/*

cd bin/

for ntoy in {0..100..1}

do

    echo $ntoy

    rm *pdf
    rm *txt
    
    cp /vols/lhcb/ss4314/misidsplitting/FUMSB_NOTsimultaneous_NewTCK/2016/Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip* .
    cp /vols/lhcb/ss4314/misidsplitting/FUMSB_NOTsimultaneous_NewTCK/2016/Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip* .
    cp /vols/lhcb/ss4314/misidsplitting/FUMSB_NOTsimultaneous_NewTCK/2016/Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip* .
    
    
    
    ./mainforos Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip26MagDown.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip26MagDown.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip26MagDown.root MagDown Strip26 $ntoy 100
    
    ./mainforos Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip26MagUp.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip26MagUp.root Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip26MagUp.root MagUp Strip26 $ntoy 100
    
    genius=modified_andcut_${ntoy}_
    
    this=Basiccut
    var3=Strip26MagDown
    var4=Strip26MagUp
    beg=../finaltuples2016/$genius
    end=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root
    beg2=$genius
    end2=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_
    
    
    for wohoo in nShared22
    
    do
    
    	hadd $beg$wohoo$end $beg2$wohoo$var3$end2$var3.root $beg2$wohoo$var4$end2$var4.root 
    
    done
    
    beg3=../finaltuples2016/$genius
    end3=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root
    beg4=$genius
    end4=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_
    
    for wohoo in nShared22
    
    do
    
            hadd $beg3$wohoo$end3 $beg4$wohoo$var3$end4$var3.root $beg4$wohoo$var4$end4$var4.root
    
    done
    
    beg5=../finaltuples2016/$genius
    end5=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM.root
    beg6=$genius
    end6=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_
    
    for wohoo in nShared22 
    
    do
    
            hadd $beg5$wohoo$end5 $beg6$wohoo$var3$end6$var3.root $beg6$wohoo$var4$end6$var4.root
    
    done
    
    mkdir ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/os
    mkdir ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/os/2016
    mkdir ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/os/2016/$ntoy    

    rm ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/os/2016/$ntoy/*
    
    
    cp *pdf ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/os/2016/$ntoy/
    cp *txt ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/os/2016/$ntoy/

done