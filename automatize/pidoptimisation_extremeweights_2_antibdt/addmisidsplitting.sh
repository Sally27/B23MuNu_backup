
#olddir=FUMSB_simultaneous_NewTuples_2016 #NEW simultaneous year
olddir_notsim=FUMSB_simultaneous_NewTCK #NEW NOT simultaneous year

#newdir=FUMSB_simultaneous_NewTCK
newdir_notsim=FUMSB_NOTsimultaneous_NewTCK_AntiBDT

SetupProject Urania v5r0

##-------------DO MISID SPLITTING for Run1 2015 and 2016-----------#
#
cd /vols/lhcb/ss4314/misidsplitting
#
#mkdir $newdir
mkdir $newdir_notsim

sourc=$olddir
desti=$newdir

sourc2=$olddir_notsim
desti2=$newdir_notsim

#
#
#cp $sourc/* $desti/
#cp -r $sourc/src $desti/
#cp -r $sourc/include $desti/
#mkdir $desti/bin
#mkdir $desti/obj
#mkdir $desti/docs
#cp $sourc/bin/*sh $desti/bin/
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
#cd $newdir
#mkdir Run1
#mkdir 2015
#mkdir 2016
#
#rm Run1/*root
#rm 2015/*root
#rm 2016/*root
#
#make clean
#
#make
#
#cd bin
#rm *tex
#
#path=/vols/lhcb/ss4314/cutonFCME/$newdir/bin/
#filename1=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename2=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename3=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename4=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename5=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename6=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename7=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename8=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#
#
#filename10=Data_B23MuNuOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename20=Data_B23MuNuOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename30=Data_B23MuNuOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename40=Data_B23MuNuOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename50=Data_B23MuNuSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename60=Data_B23MuNuSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename70=Data_B23MuNuSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename80=Data_B23MuNuSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#
#filename100=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename200=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename300=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename400=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename500=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename600=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename700=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_CombBasic_AntiBDT_FitCorM_LowFCME;
#filename800=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_LowFCME;
#
#
#
#
#VAR2="(Polarity==1)&&(runNumber<105000)"
#VAR1=Strip21r1MagUp
#./main $path $VAR1 $VAR2 $filename1 $filename2 $filename3 $filename4
#
#
#VAR4="(Polarity==-1)&&(runNumber<105000)"
#VAR3=Strip21r1MagDown
#./main $path $VAR3 $VAR4 $filename1 $filename2 $filename3 $filename4
#
#VAR6="(Polarity==1)&&(runNumber>105000)"
#VAR5=Strip21MagUp
#./main $path $VAR5 $VAR6 $filename1 $filename2 $filename3 $filename4
#
#VAR8="(Polarity==-1)&&(runNumber>105000)"
#VAR7=Strip21MagDown
#./main $path $VAR7 $VAR8 $filename1 $filename2 $filename3 $filename4
#
#./main $path $VAR1 $VAR2 $filename5 $filename6 $filename7 $filename8
#./main $path $VAR3 $VAR4 $filename5 $filename6 $filename7 $filename8
#./main $path $VAR5 $VAR6 $filename5 $filename6 $filename7 $filename8
#./main $path $VAR7 $VAR8 $filename5 $filename6 $filename7 $filename8
#
#
#cp *tex ../Run1/
#rm *tex
#
#VAR22="(Polarity==1)"
#VAR11=Strip23_MCTuneV1MagUp
#
#VAR44="(Polarity==-1)"
#VAR33=Strip23_MCTuneV1MagDown
#
#./main $path $VAR11 $VAR22 $filename10 $filename20 $filename30 $filename40
#./main $path $VAR33 $VAR44 $filename10 $filename20 $filename30 $filename40
##./main $path $VAR5 $VAR6 $filename10 $filename20 $filename30 $filename40
##./main $path $VAR7 $VAR8 $filename10 $filename20 $filename30 $filename40
#
#./main $path $VAR11 $VAR22 $filename50 $filename60 $filename70 $filename80
#./main $path $VAR33 $VAR44 $filename50 $filename60 $filename70 $filename80
##./main $path $VAR5 $VAR6 $filename50 $filename60 $filename70 $filename80
##./main $path $VAR7 $VAR8 $filename50 $filename60 $filename70 $filename80
#
#
#cp *tex ../2015/
#rm *tex
#
#
#VAR222="(Polarity==1)"
#VAR111=Strip26MagUp
#
#VAR444="(Polarity==-1)"
#VAR333=Strip26MagDown
#
#./main $path $VAR111 $VAR222 $filename100 $filename200 $filename300 $filename400
#./main $path $VAR333 $VAR444 $filename100 $filename200 $filename300 $filename400
##./main $path $VAR5 $VAR6 $filename100 $filename200 $filename300 $filename400
##./main $path $VAR7 $VAR8 $filename100 $filename200 $filename300 $filename400
#
#./main $path $VAR111 $VAR222 $filename500 $filename600 $filename700 $filename800
#./main $path $VAR333 $VAR444 $filename500 $filename600 $filename700 $filename800
##./main $path $VAR555 $VAR666 $filename500 $filename600 $filename700 $filename800
##./main $path $VAR7 $VAR8 $filename500 $filename600 $filename700 $filename800
#
#
#cp *tex ../2016/
#rm *tex
#
#
#path=/vols/lhcb/ss4314/cutonFCME/$newdir/bin/
#filename1=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename2=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename3=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename4=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename5=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename6=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename7=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename8=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#
#
#filename10=Data_B23MuNuOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename20=Data_B23MuNuOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename30=Data_B23MuNuOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename40=Data_B23MuNuOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename50=Data_B23MuNuSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename60=Data_B23MuNuSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename70=Data_B23MuNuSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename80=Data_B23MuNuSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#
#filename100=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename200=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename300=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename400=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename500=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename600=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename700=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_CombBasic_AntiBDT_FitCorM_HighFCME;
#filename800=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_HighFCME;
#
#
#
#
#VAR2="(Polarity==1)&&(runNumber<105000)"
#VAR1=Strip21r1MagUp
#./main $path $VAR1 $VAR2 $filename1 $filename2 $filename3 $filename4
#
#
#VAR4="(Polarity==-1)&&(runNumber<105000)"
#VAR3=Strip21r1MagDown
#./main $path $VAR3 $VAR4 $filename1 $filename2 $filename3 $filename4
#
#VAR6="(Polarity==1)&&(runNumber>105000)"
#VAR5=Strip21MagUp
#./main $path $VAR5 $VAR6 $filename1 $filename2 $filename3 $filename4
#
#VAR8="(Polarity==-1)&&(runNumber>105000)"
#VAR7=Strip21MagDown
#./main $path $VAR7 $VAR8 $filename1 $filename2 $filename3 $filename4
#
#./main $path $VAR1 $VAR2 $filename5 $filename6 $filename7 $filename8
#./main $path $VAR3 $VAR4 $filename5 $filename6 $filename7 $filename8
#./main $path $VAR5 $VAR6 $filename5 $filename6 $filename7 $filename8
#./main $path $VAR7 $VAR8 $filename5 $filename6 $filename7 $filename8
#
#
#cp *tex ../Run1/
#rm *tex
#
#VAR22="(Polarity==1)"
#VAR11=Strip23_MCTuneV1MagUp
#
#VAR44="(Polarity==-1)"
#VAR33=Strip23_MCTuneV1MagDown
#
#./main $path $VAR11 $VAR22 $filename10 $filename20 $filename30 $filename40
#./main $path $VAR33 $VAR44 $filename10 $filename20 $filename30 $filename40
##./main $path $VAR5 $VAR6 $filename10 $filename20 $filename30 $filename40
##./main $path $VAR7 $VAR8 $filename10 $filename20 $filename30 $filename40
#
#./main $path $VAR11 $VAR22 $filename50 $filename60 $filename70 $filename80
#./main $path $VAR33 $VAR44 $filename50 $filename60 $filename70 $filename80
##./main $path $VAR5 $VAR6 $filename50 $filename60 $filename70 $filename80
##./main $path $VAR7 $VAR8 $filename50 $filename60 $filename70 $filename80
#
#
#cp *tex ../2015/
#rm *tex
#
#
#VAR222="(Polarity==1)"
#VAR111=Strip26MagUp
#
#VAR444="(Polarity==-1)"
#VAR333=Strip26MagDown
#
#./main $path $VAR111 $VAR222 $filename100 $filename200 $filename300 $filename400
#./main $path $VAR333 $VAR444 $filename100 $filename200 $filename300 $filename400
##./main $path $VAR5 $VAR6 $filename100 $filename200 $filename300 $filename400
##./main $path $VAR7 $VAR8 $filename100 $filename200 $filename300 $filename400
#
#./main $path $VAR111 $VAR222 $filename500 $filename600 $filename700 $filename800
#./main $path $VAR333 $VAR444 $filename500 $filename600 $filename700 $filename800
##./main $path $VAR555 $VAR666 $filename500 $filename600 $filename700 $filename800
##./main $path $VAR7 $VAR8 $filename500 $filename600 $filename700 $filename800
#
#
#cp *tex ../2016/
#rm *tex
#
##
##
##
#cp Data_B23MuNu*root ../Run1/
#cp Bu23MuNuData2016*root ../2016/
#
#
#cd ../Run1/
#for f in *tex
#do
#        latex $f
#done
#
#
#mkdir ~/public_html/misidsplitting/$newdir/
#mkdir ~/public_html/misidsplitting/$newdir/Run1
#
#
#cp *pdf ~/public_html/misidsplitting/$newdir/Run1/
#
#
#cd ../2016/
#for f in *tex
#do
#        latex $f
#done
#
#
#mkdir ~/public_html/misidsplitting/$newdir/2016
#cp *pdf ~/public_html/misidsplitting/$newdir/2016/


#
cd /vols/lhcb/ss4314/misidsplitting/$newdir_notsim
mkdir Run1
mkdir 2015
mkdir 2016

rm Run1/*root
rm 2015/*root
rm 2016/*root
#
make clean

make
#
cd bin
rm *tex
#
path3=/vols/lhcb/ss4314/cutonFitRange/$newdir_notsim/bin/
filename1=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM;
filename2=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM;
filename3=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_AntiBDT_FitCorM;
filename4=Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM;
filename5=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM;
filename6=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM;
filename7=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_AntiBDT_FitCorM;
filename8=Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM;
#
filename10=Data_B23MuNuOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM;
filename20=Data_B23MuNuOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM;
filename30=Data_B23MuNuOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_AntiBDT_FitCorM;
filename40=Data_B23MuNuOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM;
filename50=Data_B23MuNuSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM;
filename60=Data_B23MuNuSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM;
filename70=Data_B23MuNuSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_AntiBDT_FitCorM;
filename80=Data_B23MuNuSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM;

filename100=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM;
filename200=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM;
filename300=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_CombBasic_AntiBDT_FitCorM;
filename400=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM;
filename500=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM;
filename600=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM;
filename700=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_CombBasic_AntiBDT_FitCorM;
filename800=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM;


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

./main $path3 $VAR11 $VAR22 $filename10 $filename20 $filename30 $filename40
./main $path3 $VAR33 $VAR44 $filename10 $filename20 $filename30 $filename40
#./main $path $VAR5 $VAR6 $filename10 $filename20 $filename30 $filename40
#./main $path $VAR7 $VAR8 $filename10 $filename20 $filename30 $filename40

./main $path3 $VAR11 $VAR22 $filename50 $filename60 $filename70 $filename80
./main $path3 $VAR33 $VAR44 $filename50 $filename60 $filename70 $filename80
#./main $path $VAR5 $VAR6 $filename50 $filename60 $filename70 $filename80
#./main $path $VAR7 $VAR8 $filename50 $filename60 $filename70 $filename80


cp *tex ../2015/
rm *tex


VAR222="(Polarity==1)"
VAR111=Strip26MagUp

VAR444="(Polarity==-1)"
VAR333=Strip26MagDown

./main $path3 $VAR111 $VAR222 $filename100 $filename200 $filename300 $filename400
./main $path3 $VAR333 $VAR444 $filename100 $filename200 $filename300 $filename400
#./main $path $VAR5 $VAR6 $filename100 $filename200 $filename300 $filename400
#./main $path $VAR7 $VAR8 $filename100 $filename200 $filename300 $filename400

./main $path3 $VAR111 $VAR222 $filename500 $filename600 $filename700 $filename800
./main $path3 $VAR333 $VAR444 $filename500 $filename600 $filename700 $filename800
#./main $path $VAR555 $VAR666 $filename500 $filename600 $filename700 $filename800
#./main $path $VAR7 $VAR8 $filename500 $filename600 $filename700 $filename800


cp *tex ../2016/
rm *tex


cp Data_B23MuNu*root ../Run1/
cp Bu23MuNuData2016*root ../2016/

cd ../Run1/
for f in *tex
do
        latex $f
done


mkdir ~/public_html/misidsplitting/$newdir_notsim/
mkdir ~/public_html/misidsplitting/$newdir_notsim/Run1


cp *pdf ~/public_html/misidsplitting/$newdir_notsim/Run1/


cd ../2016/
for f in *tex
do
        latex $f
done


mkdir ~/public_html/misidsplitting/$newdir_notsim/2016
cp *pdf ~/public_html/misidsplitting/$newdir_notsim/2016/
