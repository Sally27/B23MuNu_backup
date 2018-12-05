
#--------------------------ADD weights for OS-------------------#

trainingname=FUMSB_simultaneous_add2016 #NEW simultaneous year
tag=FUMSB_NOTsimultaneous_add2016 #NEW NOT simultaneous year
tn=_scalesig
cd /vols/lhcb/ss4314/addPIDweights/

#

mkdir $trainingname$tn/os


#cp $sourc/os/* $desti/os/
#cp -r $sourc/os/src $desti/os/
#cp -r $sourc/os/include $desti/os/
#mkdir $desti/os/bin
#mkdir $desti/os/obj
#mkdir $desti/os/docs
#mkdir $desti/os/finaltuplesRun1
#mkdir $desti/os/finaltuples2015
#cp $sourc/os/bin/*sh $desti/os/bin/
##
##
#cp $sourc2/os/* $desti2/os/
#cp -r $sourc2/os/src $desti2/os/
#cp -r $sourc2/os/include $desti2/os/
#mkdir $desti2/os/bin
#mkdir $desti2/os/obj
#mkdir $desti2/os/docs
#mkdir $desti2/os/finaltuplesRun1
#mkdir $desti2/os/finaltuples2015
#cp $sourc2/os/bin/*sh $desti2/os/bin/

cd $trainingname$tn

#
cd os
#
rm finaltuplesRun1/*
rm bin/*
#
make
#
cd bin



cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .

./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagDown.root MagDown Strip21

./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21MagUp.root MagUp Strip21

./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagDown.root MagDown Strip21r1
#
./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip21r1MagUp.root MagUp Strip21r1
#
this=Basiccut
var1=Strip21r1MagDown
var2=Strip21r1MagUp
var3=Strip21MagDown
var4=Strip21MagUp
beg=../finaltuplesRun1/modifiedandcut
end=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
beg2=modifiedandcut
end2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_


for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

	hadd $beg$tags$end $beg2$tags$var1$end2$var1.root $beg2$tags$var2$end2$var2.root $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 

done

beg3=../finaltuplesRun1/modifiedandcut
end3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
beg4=modifiedandcut
end4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root

done

beg5=../finaltuplesRun1/modifiedandcut
end5=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
beg6=modifiedandcut
end6=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

        hadd $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root

done



cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/Run1/B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .

./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagDown.root MagDown Strip21

./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21MagUp.root MagUp Strip21

./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagDown.root MagDown Strip21r1
#
./mainforos B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip21r1MagUp.root MagUp Strip21r1
#
this=Basiccut
var1=Strip21r1MagDown
var2=Strip21r1MagUp
var3=Strip21MagDown
var4=Strip21MagUp
beg=../finaltuplesRun1/modifiedandcut
end=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg2=modifiedandcut
end2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_


for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

	hadd $beg$tags$end $beg2$tags$var1$end2$var1.root $beg2$tags$var2$end2$var2.root $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 

done

beg3=../finaltuplesRun1/modifiedandcut
end3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg4=modifiedandcut
end4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

        hadd $beg3$tags$end3 $beg4$tags$var1$end4$var1.root $beg4$tags$var2$end4$var2.root $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root

done

beg5=../finaltuplesRun1/modifiedandcut
end5=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg6=modifiedandcut
end6=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

        hadd $beg5$tags$end5 $beg6$tags$var1$end6$var1.root $beg6$tags$var2$end6$var2.root $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root

done

