trainingname=FUMSB_simultaneous_add2016 #NEW simultaneous year
tag=FUMSB_NOTsimultaneous_add2016 #NEW NOT simultaneous year
tn=_scalesig

##-------------DO MISID SPLITTING for Run1 2015 and 2016-----------#
#
cd /vols/lhcb/ss4314/misidsplitting
#
mkdir $trainingname$tn
mkdir $tag$tn

sourc=$trainingname
desti=$trainingname$tn

sourc2=$tag
desti2=$tag$tn

#
#
cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
cp $sourc/bin/*sh $desti/bin/
#
#
cp $sourc2/* $desti2/
cp -r $sourc2/src $desti2/
cp -r $sourc2/include $desti2/
mkdir $desti2/bin
mkdir $desti2/obj
mkdir $desti2/docs
cp $sourc2/bin/*sh $desti2/bin/
#
cd $trainingname$tn
mkdir Run1
mkdir 2015
mkdir 2016

#
make clean

make

cd bin
rm *tex

path=/vols/lhcb/ss4314/cutonFCME/$trainingname/bin/
filename1=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME;
filename4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename5=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename6=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename7=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME;
filename8=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME;


filename10=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename20=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename30=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME;
filename40=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename50=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename60=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename70=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME;
filename80=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME;

filename100=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename200=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename300=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME;
filename400=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename500=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename600=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_LowFCME;
filename700=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME;
filename800=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_LowFCME;




VAR2="(Polarity==1)&&(runNumber<105000)"
VAR1=Strip21r1MagUp
./main $path $VAR1 $VAR2 $filename1 $filename2 $filename3 $filename4


VAR4="(Polarity==-1)&&(runNumber<105000)"
VAR3=Strip21r1MagDown
./main $path $VAR3 $VAR4 $filename1 $filename2 $filename3 $filename4

VAR6="(Polarity==1)&&(runNumber>105000)"
VAR5=Strip21MagUp
./main $path $VAR5 $VAR6 $filename1 $filename2 $filename3 $filename4

VAR8="(Polarity==-1)&&(runNumber>105000)"
VAR7=Strip21MagDown
./main $path $VAR7 $VAR8 $filename1 $filename2 $filename3 $filename4

./main $path $VAR1 $VAR2 $filename5 $filename6 $filename7 $filename8
./main $path $VAR3 $VAR4 $filename5 $filename6 $filename7 $filename8
./main $path $VAR5 $VAR6 $filename5 $filename6 $filename7 $filename8
./main $path $VAR7 $VAR8 $filename5 $filename6 $filename7 $filename8


cp *tex ../Run1/
rm *tex

VAR22="(Polarity==1)"
VAR11=Strip23_MCTuneV1MagUp

VAR44="(Polarity==-1)"
VAR33=Strip23_MCTuneV1MagDown

./main $path $VAR11 $VAR22 $filename10 $filename20 $filename30 $filename40
./main $path $VAR33 $VAR44 $filename10 $filename20 $filename30 $filename40
#./main $path $VAR5 $VAR6 $filename10 $filename20 $filename30 $filename40
#./main $path $VAR7 $VAR8 $filename10 $filename20 $filename30 $filename40

./main $path $VAR11 $VAR22 $filename50 $filename60 $filename70 $filename80
./main $path $VAR33 $VAR44 $filename50 $filename60 $filename70 $filename80
#./main $path $VAR5 $VAR6 $filename50 $filename60 $filename70 $filename80
#./main $path $VAR7 $VAR8 $filename50 $filename60 $filename70 $filename80


cp *tex ../2015/
rm *tex


VAR222="(Polarity==1)"
VAR111=Strip26MagUp

VAR444="(Polarity==-1)"
VAR333=Strip26MagDown

./main $path $VAR111 $VAR222 $filename100 $filename200 $filename300 $filename400
./main $path $VAR333 $VAR444 $filename100 $filename200 $filename300 $filename400
#./main $path $VAR5 $VAR6 $filename100 $filename200 $filename300 $filename400
#./main $path $VAR7 $VAR8 $filename100 $filename200 $filename300 $filename400

./main $path $VAR111 $VAR222 $filename500 $filename600 $filename700 $filename800
./main $path $VAR333 $VAR444 $filename500 $filename600 $filename700 $filename800
#./main $path $VAR555 $VAR666 $filename500 $filename600 $filename700 $filename800
#./main $path $VAR7 $VAR8 $filename500 $filename600 $filename700 $filename800


cp *tex ../2016/
rm *tex


path=/vols/lhcb/ss4314/cutonFCME/$trainingname/bin/
filename1=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename5=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename6=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename7=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename8=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;


filename10=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename20=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename30=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename40=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename50=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename60=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename70=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename80=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;

filename100=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename200=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename300=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename400=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename500=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename600=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_HighFCME;
filename700=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME;
filename800=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_HighFCME;




VAR2="(Polarity==1)&&(runNumber<105000)"
VAR1=Strip21r1MagUp
./main $path $VAR1 $VAR2 $filename1 $filename2 $filename3 $filename4


VAR4="(Polarity==-1)&&(runNumber<105000)"
VAR3=Strip21r1MagDown
./main $path $VAR3 $VAR4 $filename1 $filename2 $filename3 $filename4

VAR6="(Polarity==1)&&(runNumber>105000)"
VAR5=Strip21MagUp
./main $path $VAR5 $VAR6 $filename1 $filename2 $filename3 $filename4

VAR8="(Polarity==-1)&&(runNumber>105000)"
VAR7=Strip21MagDown
./main $path $VAR7 $VAR8 $filename1 $filename2 $filename3 $filename4

./main $path $VAR1 $VAR2 $filename5 $filename6 $filename7 $filename8
./main $path $VAR3 $VAR4 $filename5 $filename6 $filename7 $filename8
./main $path $VAR5 $VAR6 $filename5 $filename6 $filename7 $filename8
./main $path $VAR7 $VAR8 $filename5 $filename6 $filename7 $filename8


cp *tex ../Run1/
rm *tex

VAR22="(Polarity==1)"
VAR11=Strip23_MCTuneV1MagUp

VAR44="(Polarity==-1)"
VAR33=Strip23_MCTuneV1MagDown

./main $path $VAR11 $VAR22 $filename10 $filename20 $filename30 $filename40
./main $path $VAR33 $VAR44 $filename10 $filename20 $filename30 $filename40
#./main $path $VAR5 $VAR6 $filename10 $filename20 $filename30 $filename40
#./main $path $VAR7 $VAR8 $filename10 $filename20 $filename30 $filename40

./main $path $VAR11 $VAR22 $filename50 $filename60 $filename70 $filename80
./main $path $VAR33 $VAR44 $filename50 $filename60 $filename70 $filename80
#./main $path $VAR5 $VAR6 $filename50 $filename60 $filename70 $filename80
#./main $path $VAR7 $VAR8 $filename50 $filename60 $filename70 $filename80


cp *tex ../2015/
rm *tex


VAR222="(Polarity==1)"
VAR111=Strip26MagUp

VAR444="(Polarity==-1)"
VAR333=Strip26MagDown

./main $path $VAR111 $VAR222 $filename100 $filename200 $filename300 $filename400
./main $path $VAR333 $VAR444 $filename100 $filename200 $filename300 $filename400
#./main $path $VAR5 $VAR6 $filename100 $filename200 $filename300 $filename400
#./main $path $VAR7 $VAR8 $filename100 $filename200 $filename300 $filename400

./main $path $VAR111 $VAR222 $filename500 $filename600 $filename700 $filename800
./main $path $VAR333 $VAR444 $filename500 $filename600 $filename700 $filename800
#./main $path $VAR555 $VAR666 $filename500 $filename600 $filename700 $filename800
#./main $path $VAR7 $VAR8 $filename500 $filename600 $filename700 $filename800


cp *tex ../2016/
rm *tex

#
#
#
cp B23MuNuFake*total*root ../Run1/
cp B23MuNuFakeOS_2015_DV41r2*root ../2015/
cp B23MuNuFakeSS_2015_DV41r2*root ../2015/
cp B23MuNuFakeSS*2016*root ../2016/
cp B23MuNuFakeOS*2016*root ../2016/
#
cd /vols/lhcb/ss4314/misidsplitting/$tag$tn
mkdir Run1
mkdir 2015
mkdir 2016

#
make clean

make
#
cd bin
rm *tex
#
path3=/vols/lhcb/ss4314/cutonFitRange/$tag/bin/
filename1=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM;
filename2=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM;
filename3=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM;
filename4=B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM;
filename5=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM;
filename6=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM;
filename7=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM;
filename8=B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM;
#
filename10=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM;
filename20=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM;
filename30=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM;
filename40=B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM;
filename50=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM;
filename60=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM;
filename70=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM;
filename80=B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM;

filename100=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM;
filename200=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM;
filename300=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM;
filename400=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM;
filename500=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM;
filename600=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM;
filename700=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic_FitCorM;
filename800=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM;


VAR2="(Polarity==1)&&(runNumber<105000)"
VAR1=Strip21r1MagUp
./main $path3 $VAR1 $VAR2 $filename1 $filename2 $filename3 $filename4


VAR4="(Polarity==-1)&&(runNumber<105000)"
VAR3=Strip21r1MagDown
./main $path3 $VAR3 $VAR4 $filename1 $filename2 $filename3 $filename4

VAR6="(Polarity==1)&&(runNumber>105000)"
VAR5=Strip21MagUp
./main $path3 $VAR5 $VAR6 $filename1 $filename2 $filename3 $filename4

VAR8="(Polarity==-1)&&(runNumber>105000)"
VAR7=Strip21MagDown
./main $path3 $VAR7 $VAR8 $filename1 $filename2 $filename3 $filename4

./main $path3 $VAR1 $VAR2 $filename5 $filename6 $filename7 $filename8
./main $path3 $VAR3 $VAR4 $filename5 $filename6 $filename7 $filename8
./main $path3 $VAR5 $VAR6 $filename5 $filename6 $filename7 $filename8
./main $path3 $VAR7 $VAR8 $filename5 $filename6 $filename7 $filename8


cp *tex ../Run1/
rm *tex


VAR22="(Polarity==1)"
VAR11=Strip23_MCTuneV1MagUp

VAR44="(Polarity==-1)"
VAR33=Strip23_MCTuneV1MagDown

./main $path $VAR11 $VAR22 $filename10 $filename20 $filename30 $filename40
./main $path $VAR33 $VAR44 $filename10 $filename20 $filename30 $filename40
#./main $path $VAR5 $VAR6 $filename10 $filename20 $filename30 $filename40
#./main $path $VAR7 $VAR8 $filename10 $filename20 $filename30 $filename40

./main $path $VAR11 $VAR22 $filename50 $filename60 $filename70 $filename80
./main $path $VAR33 $VAR44 $filename50 $filename60 $filename70 $filename80
#./main $path $VAR5 $VAR6 $filename50 $filename60 $filename70 $filename80
#./main $path $VAR7 $VAR8 $filename50 $filename60 $filename70 $filename80


cp *tex ../2015/
rm *tex


VAR222="(Polarity==1)"
VAR111=Strip26MagUp

VAR444="(Polarity==-1)"
VAR333=Strip26MagDown

./main $path $VAR111 $VAR222 $filename100 $filename200 $filename300 $filename400
./main $path $VAR333 $VAR444 $filename100 $filename200 $filename300 $filename400
#./main $path $VAR5 $VAR6 $filename100 $filename200 $filename300 $filename400
#./main $path $VAR7 $VAR8 $filename100 $filename200 $filename300 $filename400

./main $path $VAR111 $VAR222 $filename500 $filename600 $filename700 $filename800
./main $path $VAR333 $VAR444 $filename500 $filename600 $filename700 $filename800
#./main $path $VAR555 $VAR666 $filename500 $filename600 $filename700 $filename800
#./main $path $VAR7 $VAR8 $filename500 $filename600 $filename700 $filename800


cp *tex ../2016/
rm *tex


cp B23MuNuFake*total*root ../Run1/
cp B23MuNuFakeOS_2015_DV41r2*root ../2015/
cp B23MuNuFakeSS_2015_DV41r2*root ../2015/
cp B23MuNuFakeSS*2016*root ../2016/
cp B23MuNuFakeOS*2016*root ../2016/
