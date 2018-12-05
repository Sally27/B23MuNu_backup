:
trainingname=FUMSB_simultaneous_add2016 #NEW simultaneous year
tag=FUMSB_NOTsimultaneous_add2016 #NEW NOT simultaneous year
tn=_scalesig
#---------------------------------ADD weights trainingname SS 2016-----------------------#

cd /vols/lhcb/ss4314/addPIDweights/
#
mkdir $trainingname$tn
#mkdir $tag
#
#sourc=FUMSB_simultaneous_symmetric_newcontrolchannel_nojackweight #for now CHANGE THIS
#
#
sourc=$trainingname
desti=$trainingname$tn

sourc2=$tag
desti2=$tag$tn

#cp $sourc/* $desti/
#cp -r $sourc/src $desti/
#cp -r $sourc/include $desti/
#mkdir $desti/bin
#mkdir $desti/obj
#mkdir $desti/docs
#mkdir $desti/finaltuples2016
#mkdir $desti/finaltuples2015
#cp $sourc/bin/*sh $desti/bin/
##
##
#cp $sourc2/* $desti2/
#cp -r $sourc2/src $desti2/
#cp -r $sourc2/include $desti2/
#mkdir $desti2/bin
#mkdir $desti2/obj
#mkdir $desti2/docs
#mkdir $desti2/finaltuples2016
#mkdir $desti2/finaltuples2015
#cp $sourc2/bin/*sh $desti2/bin/
#
cd $trainingname$tn
mkdir finaltuples2016
#
rm finaltuples2016/*

rm bin/*
#
make
#
cd bin



cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/2016/B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/2016/B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/2016/B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .

./main B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip26MagDown.root B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip26MagDown.root B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip26MagDown.root MagDown Strip26

./main B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip26MagUp.root B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip26MagUp.root B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip26MagUp.root MagUp Strip26

#
#
this=Basiccut
var3=Strip26MagDown
var4=Strip26MagUp
beg=../finaltuples2016/modifiedandcut
end=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
beg2=modifiedandcut
end2=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_


for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

	hadd $beg$tags$end $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 

done

beg3=../finaltuples2016/modifiedandcut
end3=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
beg4=modifiedandcut
end4=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

        hadd $beg3$tags$end3 $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root

done

beg5=../finaltuples2016/modifiedandcut
end5=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
beg6=modifiedandcut
end6=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

        hadd $beg5$tags$end5 $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root

done



cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/2016/B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/2016/B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/2016/B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .

./main B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagDown.root B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagDown.root B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagDown.root MagDown Strip26

./main B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagUp.root B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagUp.root B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagUp.root MagUp Strip26

this=Basiccut
var3=Strip26MagDown
var4=Strip26MagUp
beg=../finaltuples2016/modifiedandcut
end=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg2=modifiedandcut
end2=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_


for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

	hadd $beg$tags$end $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 

done

beg3=../finaltuples2016/modifiedandcut
end3=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg4=modifiedandcut
end4=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

        hadd $beg3$tags$end3 $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root

done

beg5=../finaltuples2016/modifiedandcut
end5=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg6=modifiedandcut
end6=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

        hadd $beg5$tags$end5 $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root

done
