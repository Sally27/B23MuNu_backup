starting=estimateforcombibdt_newTCK_Run1 #NEW simultaneous year
ending=estimateformisidbdt_newTCK_Run1 #NEW NOT simultaneous year

##-------------DO MISID SPLITTING for Run1 before combi bdt-----------#
#
cd /vols/lhcb/ss4314/misidsplitting
#
#mkdir $trainingname$tn

mkdir $ending

sourc=$starting
desti=$ending


cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
cp $sourc/bin/*sh $desti/bin/
#
#
cd $ending
mkdir Run1

#
make clean

make

cd bin
rm *tex

path3=/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/
path4=/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/


filename1=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic;
filename2=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic;
filename3=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic;
filename4=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic;
filename5=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic;
filename6=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic;
filename7=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic;
filename8=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic;




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

./main $path4 $VAR1 $VAR2 $filename5 $filename6 $filename7 $filename8
./main $path4 $VAR3 $VAR4 $filename5 $filename6 $filename7 $filename8
./main $path4 $VAR5 $VAR6 $filename5 $filename6 $filename7 $filename8
./main $path4 $VAR7 $VAR8 $filename5 $filename6 $filename7 $filename8


cp *tex ../Run1/

for f in *tex
do
        latex $f
done

mkdir ~/public_html/misidsplitting/$ending
cp *pdf ~/public_html/misidsplitting/$ending/
