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

#cd /vols/lhcb/ss4313/addPIDweights/
#mkdir FUMSB_NOTsimultaneous_NewTCK_misidvariation
#cd FUMSB_NOTsimultaneous_NewTCK_misidvariation
#
#mkdir finaltuplesRun1
#
#make
#
#rm finaltuplesRun1/*
#
#cd bin/
#
#
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
#    cp /vols/lhcb/ss4314/misidsplitting/FUMSB_NOTsimultaneous_NewTCK/bin/Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip* .
#    cp /vols/lhcb/ss4314/misidsplitting/FUMSB_NOTsimultaneous_NewTCK/bin/Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#    cp /vols/lhcb/ss4314/misidsplitting/FUMSB_NOTsimultaneous_NewTCK/bin/Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip* .
#    #
#    ./main Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root MagDown Strip21 $ntoy 100
#
#    ./main Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root MagUp Strip21 $ntoy 100
#    
#    ./main Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root MagDown Strip21r1 $ntoy 100
#    #
#    ./main Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root MagUp Strip21r1 $ntoy 100
#    #
#
#    genius=modified_andcut_${ntoy}_ 
#
#    this=Basiccut
#    var1=Strip21r1MagDown
#    var2=Strip21r1MagUp
#    var3=Strip21MagDown
#    var4=Strip21MagUp
#    beg=../finaltuplesRun1/$genius
#    end=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root
#    beg2=$genius
#    end2=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_
#    
#    
#    for wohoo in nSharednew probnnmunew 
#    
#    do
#    
#    	hadd $beg$wohoo$end $beg2$wohoo$var1$end2$var1.root $beg2$wohoo$var2$end2$var2.root $beg2$wohoo$var3$end2$var3.root $beg2$wohoo$var4$end2$var4.root 
#    
#    done
#    
#    beg3=../finaltuplesRun1/$genius
#    end3=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root
#    beg4=$genius
#    end4=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_
#    
#    for wohoo in nSharednew probnnmunew
#    
#    do
#    
#            hadd $beg3$wohoo$end3 $beg4$wohoo$var1$end4$var1.root $beg4$wohoo$var2$end4$var2.root $beg4$wohoo$var3$end4$var3.root $beg4$wohoo$var4$end4$var4.root
#    
#    done
#    
#    beg5=../finaltuplesRun1/$genius
#    end5=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM.root
#    beg6=$genius
#    end6=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_
#    
#    for wohoo in nSharednew probnnmunew
#    
#    do
#    
#            hadd $beg5$wohoo$end5 $beg6$wohoo$var1$end6$var1.root $beg6$wohoo$var2$end6$var2.root $beg6$wohoo$var3$end6$var3.root $beg6$wohoo$var4$end6$var4.root
#    
#    done
#    
#    
#    mkdir ~/public_html/addPIDweights
#    mkdir ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation
#    mkdir ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/ss/
#    mkdir ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/ss/Run1
#    mkdir ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/ss/Run1/$ntoy
#    
#    rm ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/ss/Run1/$ntoy/*pdf
#    
#    
#    cp *pdf ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/ss/Run1/$ntoy
#    cp *txt ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/ss/Run1/$ntoy
#
#done


#-----------------OS RUN1 tag---------------#
cd /vols/lhcb/ss4314/addPIDweights/
cd FUMSB_NOTsimultaneous_NewTCK_misidvariation
cd os

mkdir finaltuplesRun1

make

rm finaltuplesRun1/*

cd bin/

for ntoy in {0..100..1}


    do

    rm *pdf
    rm *txt


    echo $ntoy


    cp /vols/lhcb/ss4314/misidsplitting/FUMSB_NOTsimultaneous_NewTCK/bin/Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip* .
    cp /vols/lhcb/ss4314/misidsplitting/FUMSB_NOTsimultaneous_NewTCK/bin/Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip* .
    cp /vols/lhcb/ss4314/misidsplitting/FUMSB_NOTsimultaneous_NewTCK/bin/Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip* .
    
    
    
    ./mainforos Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagDown.root MagDown Strip21 $ntoy 100  
    
    ./mainforos Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21MagUp.root MagUp Strip21 $ntoy 100
    
    ./mainforos Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagDown.root MagDown Strip21r1 $ntoy 100
    
    ./mainforos Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_Strip21r1MagUp.root MagUp Strip21r1 $ntoy 100

    genius=modified_andcut_${ntoy}_    
    
    this=Basiccut
    var1=Strip21r1MagDown
    var2=Strip21r1MagUp
    var3=Strip21MagDown
    var4=Strip21MagUp
    beg=../finaltuplesRun1/$genius
    end=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root
    beg2=$genius
    end2=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_
    
    
    for wohoo in nSharednew probnnmunew
    
    do
    
    	hadd $beg$wohoo$end $beg2$wohoo$var1$end2$var1.root $beg2$wohoo$var2$end2$var2.root $beg2$wohoo$var3$end2$var3.root $beg2$wohoo$var4$end2$var4.root 
    
    done
    
    beg3=../finaltuplesRun1/$genius
    end3=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root
    beg4=$genius
    end4=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_
    
    for wohoo in nSharednew probnnmunew
    
    do
    
            hadd $beg3$wohoo$end3 $beg4$wohoo$var1$end4$var1.root $beg4$wohoo$var2$end4$var2.root $beg4$wohoo$var3$end4$var3.root $beg4$wohoo$var4$end4$var4.root
    
    done
    
    beg5=../finaltuplesRun1/$genius
    end5=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM.root
    beg6=$genius
    end6=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_
    
    for wohoo in nSharednew probnnmunew 
    
    do
    
            hadd $beg5$wohoo$end5 $beg6$wohoo$var1$end6$var1.root $beg6$wohoo$var2$end6$var2.root $beg6$wohoo$var3$end6$var3.root $beg6$wohoo$var4$end6$var4.root
    
    done
    
    mkdir ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/os
    mkdir ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/os/Run1
    mkdir ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/os/Run1/$ntoy
    
    rm ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/os/Run1/$ntoy/*pdf
    
    
    cp *pdf ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/os/Run1/$ntoy
    cp *txt ~/public_html/addPIDweights/FUMSB_NOTsimultaneous_NewTCK_misidvariation/os/Run1/$ntoy

done

