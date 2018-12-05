
cd /vols/lhcb/ss4314/misidsplitting/estimateforcombibdt_2016

make

cd bin


path3=/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/OSMisIDRestrippingpreparetuple2016/bin/
path4=/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/SSMisIDRestrippingpreparetuple2016/bin/
filename100=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID;
filename200=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID;
filename300=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut;
filename400=B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID;
filename500=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID;
filename600=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID;
filename700=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut;
filename800=B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID;


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


#cp *tex ../2016/
#rm *tex
