
#--------------------------ADD weights for OS 2016 trainingname-------------------#

trainingname=FUMSB_simultaneous_add2016 #NEW simultaneous year
tag=FUMSB_NOTsimultaneous_add2016 #NEW NOT simultaneous year
tn=_scalesig
cd /vols/lhcb/ss4314/addPIDweights/
#
mkdir $trainingname$tn
mkdir $tag

mkdir $trainingname$tn/os
mkdir $tag/os


sourc=$trainingname
desti=$trainingname$tn

sourc2=$tag
desti2=$tag$tn



#cp $sourc/os/* $desti/os/
#cp -r $sourc/os/src $desti/os/
#cp -r $sourc/os/include $desti/os/
#mkdir $desti/os/bin
#mkdir $desti/os/obj
#mkdir $desti/os/docs
#mkdir $desti/os/finaltuples2016
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
#mkdir $desti2/os/finaltuples2016
#mkdir $desti2/os/finaltuples2015
#cp $sourc2/os/bin/*sh $desti2/os/bin/
#
cd $trainingname$tn

#
cd os
mkdir finaltuples2016
##
rm finaltuples2016/*
rm bin/*
#
make
#
cd bin



cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/2016/B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/2016/B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/2016/B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip* .

./mainforos B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip26MagDown.root B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip26MagDown.root B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip26MagDown.root MagDown Strip26

./mainforos B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip26MagUp.root B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip26MagUp.root B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_Strip26MagUp.root MagUp Strip26

this=Basiccut
var3=Strip26MagDown
var4=Strip26MagUp
beg=../finaltuples2016/modifiedandcut
end=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
beg2=modifiedandcut
end2=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME_


for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

	hadd $beg$tags$end $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 

done

beg3=../finaltuples2016/modifiedandcut
end3=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
beg4=modifiedandcut
end4=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

        hadd $beg3$tags$end3 $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root

done

beg5=../finaltuples2016/modifiedandcut
end5=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME.root
beg6=modifiedandcut
end6=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME_

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

        hadd $beg5$tags$end5 $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root

done



cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/2016/B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/2016/B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .
cp /vols/lhcb/ss4314/misidsplitting/$trainingname$tn/2016/B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip* .

./mainforos B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagDown.root B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagDown.root B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagDown.root MagDown Strip26

./mainforos B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagUp.root B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagUp.root B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_Strip26MagUp.root MagUp Strip26

#
this=Basiccut
var3=Strip26MagDown
var4=Strip26MagUp
beg=../finaltuples2016/modifiedandcut
end=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg2=modifiedandcut
end2=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME_


for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

	hadd $beg$tags$end $beg2$tags$var3$end2$var3.root $beg2$tags$var4$end2$var4.root 

done

beg3=../finaltuples2016/modifiedandcut
end3=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg4=modifiedandcut
end4=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

        hadd $beg3$tags$end3 $beg4$tags$var3$end4$var3.root $beg4$tags$var4$end4$var4.root

done

beg5=../finaltuples2016/modifiedandcut
end5=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME.root
beg6=modifiedandcut
end6=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME_

for tags in "$this" Dllmumore05 Dllmumore1 Dllmumore15 Dllmumore2 Dllmuminkmore05 Dllmuminkmore1 Dllmuminkmore15 Dllmuminkmore2 NNmuminuspimorem06 NNmuminuspimorem05 NNmuminuspimorem04 NNmumore02 NNmumore025 NNmumore03 NNmumore035

do

        hadd $beg5$tags$end5 $beg6$tags$var3$end6$var3.root $beg6$tags$var4$end6$var4.root

done




