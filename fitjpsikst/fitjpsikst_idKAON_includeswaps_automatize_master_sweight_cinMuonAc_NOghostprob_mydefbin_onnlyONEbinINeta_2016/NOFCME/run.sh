#!/bin/sh


cd bin

echo "Cleaning all the directories"

KFOLD_PATH=/vols/lhcb/ss4314/customlib/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
rm ../PIDResult/*
rm ../MergedFits/*
rm ../workspace/*
rm ../Sweights/*root
rm ../bin/*root

curdir=fitjpsikst_idKAON_includeswaps_automatize_master_sweight_cinMuonAc_NOghostprob_mydefbin_onnlyONEbinINeta_2016

#./main "Pi_isMuon==1.0"
#./mainrunbig "Pi_isMuon==1.0" "Pi_(Brunel_IsMuon==1.0)_All"
#./mainPIDCalib "Pi_(Brunel_IsMuon==1.0)_All" "PID_2DPi_isMuon__1_0.root" 
#
#tagcut1=Pi_isMuon_true
#
#mkdir ~/public_html/fitjpsikst
#mkdir ~/public_html/fitjpsikst/$curdir/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut1
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut1
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut1/NOFCME
#cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/NOFCME/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut1/PIDtable/
#cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut1/PIDtable/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut1/MergedFits/
#cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/MergedFits/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
#cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
#cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
#cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
#cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
#cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
#
#rm -r Archive 
#
#mkdir ../Archive
#mkdir ../Archive/$tagcut1
#mkdir ../Archive/$tagcut1/workspace
#cp ../workspace/* ../Archive/$tagcut1/workspace/
#mkdir ../Archive/$tagcut1/PIDResult
#cp ../PIDResult/* ../Archive/$tagcut1/PIDResult/
#cp ../PIDtables/* ../Archive/$tagcut1/PIDResult/
#mkdir ../Archive/$tagcut1/MergedFits
#cp ../MergedFits/*pdf ../Archive/$tagcut1/MergedFits/
#mkdir ../Archive/$tagcut1/ImportantTablesAndFigures/
#cp ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/* ../Archive/$tagcut1/ImportantTablesAndFigures/
#
#
#rm ../PIDResult/*
#rm ../MergedFits/*
#rm ../workspace/*
#rm ../Sweights/*root
#rm ../bin/*root
#
#./main "Pi_isMuon==1.0 && Pi_isMuonTight==1.0"
#./mainrunbig "Pi_isMuon==1.0 && Pi_isMuonTight==1.0" "Pi_(Brunel_IsMuon==1.0) && (Brunel_IsMuonTight==1.0)_All"
#./mainPIDCalib "Pi_(Brunel_IsMuon==1.0) && (Brunel_IsMuonTight==1.0)_All" "PID_2DPi_isMuon__1_0_&&_Pi_isMuonTight__1_0.root"
#
#tagcut2=Pi_isMuon_true_and_Pi_isMuonTight
#
#mkdir ~/public_html/fitjpsikst
#mkdir ~/public_html/fitjpsikst/$curdir/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut2
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut2
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut2/NOFCME
#cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/NOFCME/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut2/PIDtable/
#cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut2/PIDtable/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut2/MergedFits/
#cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/MergedFits/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
#cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
#cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
#cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
#cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
#cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
#
#
#mkdir ../Archive/$tagcut2
#mkdir ../Archive/$tagcut2/workspace
#cp ../workspace/* ../Archive/$tagcut2/workspace/
#mkdir ../Archive/$tagcut2/PIDResult
#cp ../PIDResult/* ../Archive/$tagcut2/PIDResult/
#cp ../PIDtables/* ../Archive/$tagcut2/PIDResult/
#mkdir ../Archive/$tagcut2/MergedFits
#cp ../MergedFits/*pdf ../Archive/$tagcut2/MergedFits/
#mkdir ../Archive/$tagcut2/ImportantTablesAndFigures/
#cp ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/* ../Archive/$tagcut2/ImportantTablesAndFigures/
##
##
##
#rm ../PIDResult/*
#rm ../MergedFits/*
#rm ../workspace/*
#rm ../Sweights/*root
#rm ../bin/*root
#
#
#
#./main "Pi_isMuon==1.0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2"
#./mainrunbig "Pi_isMuon==1.0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2" "Pi_(Brunel_IsMuon==1.0) && (Brunel_IsMuonTight==1.0) && (Brunel_nShared<2)_All"
#./mainPIDCalib "Pi_(Brunel_IsMuon==1.0) && (Brunel_IsMuonTight==1.0) && (Brunel_nShared<2)_All" "PID_2DPi_isMuon__1_0_&&_Pi_isMuonTight__1_0_&&_Pi_MuonNShared<2.root" 
#
#tagcut3=Pi_isMuon_true_and_Pi_isMuonTight_Pi_nShared2
#
#mkdir ~/public_html/fitjpsikst
#mkdir ~/public_html/fitjpsikst/$curdir/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut3
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut3
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut3/NOFCME
#cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/NOFCME/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut3/PIDtable/
#cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut3/PIDtable/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut3/MergedFits/
#cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/MergedFits/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
#cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
#cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
#cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
#cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
#cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
#
#
#mkdir ../Archive/$tagcut3
#mkdir ../Archive/$tagcut3/workspace
#cp ../workspace/* ../Archive/$tagcut3/workspace/
#mkdir ../Archive/$tagcut3/PIDResult
#cp ../PIDResult/* ../Archive/$tagcut3/PIDResult/
#cp ../PIDtables/* ../Archive/$tagcut3/PIDResult/
#mkdir ../Archive/$tagcut3/MergedFits
#cp ../MergedFits/*pdf ../Archive/$tagcut3/MergedFits/
#mkdir ../Archive/$tagcut3/ImportantTablesAndFigures/
#cp ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/* ../Archive/$tagcut3/ImportantTablesAndFigures/
#
#
#rm ../PIDResult/*
#rm ../MergedFits/*
#rm ../workspace/*
#rm ../Sweights/*root
#rm ../bin/*root
#
#
#./main "Pi_isMuon==1.0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2 && Pi_MC15TuneV1_ProbNNmu>0.5"
#./mainrunbig "Pi_isMuon==1.0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2 && Pi_MC15TuneV1_ProbNNmu>0.5" "Pi_(Brunel_IsMuon==1.0) && (Brunel_IsMuonTight==1.0) && (Brunel_nShared<2) && (Brunel_MC15TuneV1_ProbNNmu > 0.5)_All"
#./mainPIDCalib "Pi_(Brunel_IsMuon==1.0) && (Brunel_IsMuonTight==1.0) && (Brunel_nShared<2) && (Brunel_MC15TuneV1_ProbNNmu > 0.5)_All" "PID_2DPi_isMuon__1_0_&&_Pi_isMuonTight__1_0_&&_Pi_MuonNShared<2_&&_Pi_MC15TuneV1_ProbNNmu>0_5.root" 
#tagcut4=Pi_isMuon_true_and_Pi_isMuonTight_Pi_nShared2_Pi_ProbNNmu_05
#
#mkdir ~/public_html/fitjpsikst
#mkdir ~/public_html/fitjpsikst/$curdir/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut4
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut4
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut4/NOFCME
#cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/NOFCME/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut4/PIDtable/
#cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut4/PIDtable/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut4/MergedFits/
#cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/MergedFits/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
#cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
#cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
#cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
#cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
#cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
#
#
#mkdir ../Archive/$tagcut4
#mkdir ../Archive/$tagcut4/workspace
#cp ../workspace/* ../Archive/$tagcut4/workspace/
#mkdir ../Archive/$tagcut4/PIDResult
#cp ../PIDResult/* ../Archive/$tagcut4/PIDResult/
#cp ../PIDtables/* ../Archive/$tagcut4/PIDResult/
#mkdir ../Archive/$tagcut4/MergedFits
#cp ../MergedFits/*pdf ../Archive/$tagcut4/MergedFits/
#mkdir ../Archive/$tagcut4/ImportantTablesAndFigures/
#cp ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/* ../Archive/$tagcut4/ImportantTablesAndFigures/
#
#
#

#rm ../PIDResult/*
#rm ../MergedFits/*
#rm ../workspace/*
#rm ../Sweights/*root
#rm ../bin/*root
#
#
#./main "Pi_isMuon==1.0 && Pi_PIDmu>0"
#./mainrunbig "Pi_isMuon==1.0 && Pi_PIDmu>0" "Pi_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0)_All"
#./mainPIDCalib "Pi_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0)_All" "PID_2DPi_isMuon__1_0_&&_Pi_PIDmu>0.root"
#tagcut9=Pi_isMuon_true_and_Pi_PIDmu_gr0
#
#mkdir ~/public_html/fitjpsikst
#mkdir ~/public_html/fitjpsikst/$curdir/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut9
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut9
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut9/NOFCME
#cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut9/NOFCME/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut9/PIDtable/
#cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut9/PIDtable/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut9/MergedFits/
#cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut9/MergedFits/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut9/ImportantTablesAndFigures/
#cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut9/ImportantTablesAndFigures/
#cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut9/ImportantTablesAndFigures/
#cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcut9/ImportantTablesAndFigures/
#cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut9/ImportantTablesAndFigures/
#cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut9/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut9/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut9/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut9/ImportantTablesAndFigures/
#
#
#mkdir ../Archive/$tagcut9
#mkdir ../Archive/$tagcut9/workspace
#cp ../workspace/* ../Archive/$tagcut9/workspace/
#mkdir ../Archive/$tagcut9/PIDResult
#cp ../PIDResult/* ../Archive/$tagcut9/PIDResult/
#cp ../PIDtables/* ../Archive/$tagcut9/PIDResult/
#mkdir ../Archive/$tagcut9/MergedFits
#cp ../MergedFits/*pdf ../Archive/$tagcut9/MergedFits/
#mkdir ../Archive/$tagcut9/ImportantTablesAndFigures/
#cp ~/public_html/fitjpsikst/$curdir/$tagcut9/ImportantTablesAndFigures/* ../Archive/$tagcut9/ImportantTablesAndFigures/


#rm ../PIDResult/*
#rm ../MergedFits/*
#rm ../workspace/*
#rm ../Sweights/*root
#rm ../bin/*root
#
#
#./main "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0"
#./mainrunbig "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0" "Pi_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0)_All"
#./mainPIDCalib "Pi_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0)_All" "PID_2DPi_isMuon__1_0_&&_Pi_PIDmu>0_&&_Pi_PIDmu_Pi_PIDK>0.root"
#tagcut5=Pi_isMuon_true_and_Pi_PIDmu_gr0_and_Pi_PIDPi_gr0
#
#mkdir ~/public_html/fitjpsikst
#mkdir ~/public_html/fitjpsikst/$curdir/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut5
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut5
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut5/NOFCME
#cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/NOFCME/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut5/PIDtable/
#cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut5/PIDtable/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut5/MergedFits/
#cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/MergedFits/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
#cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
#cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
#cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
#cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
#cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
#
#
#mkdir ../Archive/$tagcut5
#mkdir ../Archive/$tagcut5/workspace
#cp ../workspace/* ../Archive/$tagcut5/workspace/
#mkdir ../Archive/$tagcut5/PIDResult
#cp ../PIDResult/* ../Archive/$tagcut5/PIDResult/
#cp ../PIDtables/* ../Archive/$tagcut5/PIDResult/
#mkdir ../Archive/$tagcut5/MergedFits
#cp ../MergedFits/*pdf ../Archive/$tagcut5/MergedFits/
#mkdir ../Archive/$tagcut5/ImportantTablesAndFigures/
#cp ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/* ../Archive/$tagcut5/ImportantTablesAndFigures/

rm ../PIDResult/*
rm ../MergedFits/*
rm ../workspace/*
rm ../Sweights/*root
rm ../bin/*root


./main "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_isMuonTight==1.0"
./mainrunbig "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_isMuonTight==1.0" "Pi_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_IsMuonTight==1.0)_All"
./mainPIDCalib "Pi_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_IsMuonTight==1.0)_All" "PID_2DPi_isMuon__1_0_&&_Pi_PIDmu>0_&&_Pi_PIDmu_Pi_PIDK>0_&&_Pi_isMuonTight__1_0.root"
tagcutTight=Pi_isMuon_true_and_Pi_PIDmu_gr0_and_Pi_PIDPi_gr0_isMuonTight

mkdir ~/public_html/fitjpsikst
mkdir ~/public_html/fitjpsikst/$curdir/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcutTight
mkdir ~/public_html/fitjpsikst/$curdir/$tagcutTight
mkdir ~/public_html/fitjpsikst/$curdir/$tagcutTight/NOFCME
cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcutTight/NOFCME/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcutTight/PIDtable/
cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcutTight/PIDtable/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcutTight/MergedFits/
cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcutTight/MergedFits/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcutTight/ImportantTablesAndFigures/
cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcutTight/ImportantTablesAndFigures/
cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcutTight/ImportantTablesAndFigures/
cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcutTight/ImportantTablesAndFigures/
cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcutTight/ImportantTablesAndFigures/
cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcutTight/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcutTight/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcutTight/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcutTight/ImportantTablesAndFigures/


mkdir ../Archive/$tagcutTight
mkdir ../Archive/$tagcutTight/workspace
cp ../workspace/* ../Archive/$tagcutTight/workspace/
mkdir ../Archive/$tagcutTight/PIDResult
cp ../PIDResult/* ../Archive/$tagcutTight/PIDResult/
cp ../PIDtables/* ../Archive/$tagcutTight/PIDResult/
mkdir ../Archive/$tagcutTight/MergedFits
cp ../MergedFits/*pdf ../Archive/$tagcutTight/MergedFits/
mkdir ../Archive/$tagcutTight/ImportantTablesAndFigures/
cp ~/public_html/fitjpsikst/$curdir/$tagcutTight/ImportantTablesAndFigures/* ../Archive/$tagcutTight/ImportantTablesAndFigures/



rm ../PIDResult/*
rm ../MergedFits/*
rm ../workspace/*
rm ../Sweights/*root
rm ../bin/*root


./main "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2"
./mainrunbig "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2" "Pi_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_IsMuonTight==1.0) && (Brunel_nShared<2)_All"
./mainPIDCalib "Pi_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_IsMuonTight==1.0) && (Brunel_nShared<2)_All" "PID_2DPi_isMuon__1_0_&&_Pi_PIDmu>0_&&_Pi_PIDmu_Pi_PIDK>0_&&_Pi_isMuonTight__1_0_&&_Pi_MuonNShared<2.root"
tagcutnshared=Pi_isMuon_true_and_Pi_PIDmu_gr0_and_Pi_PIDPi_gr0_isMuonTight_nShared2

mkdir ~/public_html/fitjpsikst
mkdir ~/public_html/fitjpsikst/$curdir/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcutnshared
mkdir ~/public_html/fitjpsikst/$curdir/$tagcutnshared
mkdir ~/public_html/fitjpsikst/$curdir/$tagcutnshared/NOFCME
cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcutnshared/NOFCME/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcutnshared/PIDtable/
cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcutnshared/PIDtable/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcutnshared/MergedFits/
cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcutnshared/MergedFits/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcutnshared/ImportantTablesAndFigures/
cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcutnshared/ImportantTablesAndFigures/
cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcutnshared/ImportantTablesAndFigures/
cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcutnshared/ImportantTablesAndFigures/
cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcutnshared/ImportantTablesAndFigures/
cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcutnshared/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcutnshared/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcutnshared/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcutnshared/ImportantTablesAndFigures/


mkdir ../Archive/$tagcutnshared
mkdir ../Archive/$tagcutnshared/workspace
cp ../workspace/* ../Archive/$tagcutnshared/workspace/
mkdir ../Archive/$tagcutnshared/PIDResult
cp ../PIDResult/* ../Archive/$tagcutnshared/PIDResult/
cp ../PIDtables/* ../Archive/$tagcutnshared/PIDResult/
mkdir ../Archive/$tagcutnshared/MergedFits
cp ../MergedFits/*pdf ../Archive/$tagcutnshared/MergedFits/
mkdir ../Archive/$tagcutnshared/ImportantTablesAndFigures/
cp ~/public_html/fitjpsikst/$curdir/$tagcutnshared/ImportantTablesAndFigures/* ../Archive/$tagcutnshared/ImportantTablesAndFigures/



