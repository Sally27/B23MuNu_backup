trainingname=estimateforcombibdt_newTCK_2016 #NEW simultaneous year
new=estimateformisidbdt_newTCK_2016 #NEW NOT simultaneous year

SetupProject Urania v5r0

##-------------DO MISID SPLITTING for 2016 tuples-----------#
#
cd /vols/lhcb/ss4314/misidsplitting
#
mkdir $new

sourc=$trainingname
desti=$new

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/
mkdir $desti/bin
mkdir $desti/obj
mkdir $desti/docs
cp $sourc/bin/*sh $desti/bin/



cd bin
rm *tex
cd /vols/lhcb/ss4314/misidsplitting/$new

make clean
make

cd bin

path3=/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/
path4=/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/
filename100=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic;
filename200=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic;
filename300=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_CombBasic;
filename400=Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic;
filename500=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic;
filename600=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic;
filename700=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_CombBasic;
filename800=Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic;


VAR222="(Polarity==1)"
VAR111=Strip26MagUp

VAR444="(Polarity==-1)"
VAR333=Strip26MagDown

./main $path3 $VAR111 $VAR222 $filename100 $filename200 $filename300 $filename400
./main $path3 $VAR333 $VAR444 $filename100 $filename200 $filename300 $filename400
#./main $path $VAR5 $VAR6 $filename100 $filename200 $filename300 $filename400
#./main $path $VAR7 $VAR8 $filename100 $filename200 $filename300 $filename400

./main $path4 $VAR111 $VAR222 $filename500 $filename600 $filename700 $filename800
./main $path4 $VAR333 $VAR444 $filename500 $filename600 $filename700 $filename800
#./main $path $VAR555 $VAR666 $filename500 $filename600 $filename700 $filename800
#./main $path $VAR7 $VAR8 $filename500 $filename600 $filename700 $filename800

for f in *tex
do
        latex $f
done

mkdir ~/public_html/misidsplitting/$new
cp *pdf ~/public_html/misidsplitting/$new/

#cp *tex ../2016/
#rm *tex
