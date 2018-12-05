#!/bin/sh

echo "Cleaning all the directories"

mkdir ImportantTablesAndFigures PIDResult MergedFits workspace Sweights PIDtables

cd bin

KFOLD_PATH=/vols/lhcb/ss4314/customlib/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
rm ../PIDResult/*
rm ../MergedFits/*
rm ../workspace/*
rm ../Sweights/*root
rm ../bin/*root



curdir=fitjpsikst_idPION_includeswaps_automatize_master_sweight_cinMuonAc_NOghostprob_mydefbin_onnlyONEbinINeta_2016_newPIDopt

#./main "K_isMuon==1.0"
#./mainrunbig "K_isMuon==1.0" "K_(Brunel_IsMuon==1.0)_All"
#./mainPIDCalib "K_(Brunel_IsMuon==1.0)_All" "PID_2DK_isMuon__1_0.root" 
#
#tagcut1=K_isMuon_true
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
#
#./main "K_isMuon==1.0 && K_isMuonTight==1.0"
#./mainrunbig "K_isMuon==1.0 && K_isMuonTight==1.0" "K_(Brunel_IsMuon==1.0) && (Brunel_IsMuonTight==1.0)_All"
#./mainPIDCalib "K_(Brunel_IsMuon==1.0) && (Brunel_IsMuonTight==1.0)_All" "PID_2DK_isMuon__1_0_&&_K_isMuonTight__1_0.root" 
#
#tagcut2=K_isMuon_true_and_KisMuonTight_true
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
###
###
###
#rm ../PIDResult/*
#rm ../MergedFits/*
#rm ../workspace/*
#rm ../Sweights/*root
#rm ../bin/*root
#
#
#./main "K_isMuon==1.0 && K_isMuonTight==1.0 && K_MuonNShared<2"
#./mainrunbig "K_isMuon==1.0 && K_isMuonTight==1.0 && K_MuonNShared<2" "K_(Brunel_IsMuon==1.0) && (Brunel_IsMuonTight==1.0) && (Brunel_nShared<2)_All"
#./mainPIDCalib "K_(Brunel_IsMuon==1.0) && (Brunel_IsMuonTight==1.0) && (Brunel_nShared<2)_All" "PID_2DK_isMuon__1_0_&&_K_isMuonTight__1_0_&&_K_MuonNShared<2.root" 
#tagcut3=K_isMuon_true_and_KisMuonTight_true_KnShared_2
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
##
##
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
##
##
#rm ../PIDResult/*
#rm ../MergedFits/*
#rm ../workspace/*
#rm ../Sweights/*root
#rm ../bin/*root
##
##
#./main "K_isMuon==1.0 && K_isMuonTight==1.0 && K_MuonNShared<2 && K_MC15TuneV1_ProbNNmu>0.5"
#./mainrunbig "K_isMuon==1.0 && K_isMuonTight==1.0 && K_MuonNShared<2 && K_MC15TuneV1_ProbNNmu>0.5" "K_(Brunel_IsMuon==1.0) && (Brunel_IsMuonTight==1.0) && (Brunel_nShared<2) && (Brunel_MC15TuneV1_ProbNNmu > 0.5)_All"
#./mainPIDCalib "K_(Brunel_IsMuon==1.0) && (Brunel_IsMuonTight==1.0) && (Brunel_nShared<2) && (Brunel_MC15TuneV1_ProbNNmu > 0.5)_All" "PID_2DK_isMuon__1_0_&&_K_isMuonTight__1_0_&&_K_MuonNShared<2_&&_K_MC15TuneV1_ProbNNmu>0_5.root" 
#tagcut4=K_isMuon_true_and_K_isMuonTight_K_nShared2_K_ProbNNmu_05
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
##
##
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
#./main "K_isMuon==1.0 && K_PIDmu>0"
#./mainrunbig "K_isMuon==1.0 && K_PIDmu>0" "K_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0)_All"
#./mainPIDCalib "K_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0)_All" "PID_2DK_isMuon__1_0_&&_K_PIDmu>0.root"
#tagcut5=K_isMuon_true_and_K_PIDmu_gr0
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

#
#rm ../PIDResult/*
#rm ../MergedFits/*
#rm ../workspace/*
#rm ../Sweights/*root
#rm ../bin/*root
#
#
#./main "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0"
#./mainrunbig "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0" "K_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0)_All"
#./mainPIDCalib "K_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0)_All" "PID_2DK_isMuon__1_0_&&_K_PIDmu>0_&&__K_PIDmu_K_PIDK_>0.root"
#tagcut9=K_isMuon_true_and_K_PIDmu_gr0_and_K_PIDK_gr0
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
#./main "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0"
#./mainrunbig "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0" "K_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_IsMuonTight==1.0)_All"
#./mainPIDCalib "K_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_IsMuonTight==1.0)_All" "PID_2DK_isMuon__1_0_&&_K_PIDmu>0_&&__K_PIDmu_K_PIDK_>0_&&_K_isMuonTight__1_0.root"
#tagcut6=K_isMuon_true_and_K_PIDmu_gr0_and_K_PIDK_gr0_K_isMuTig
#
#mkdir ~/public_html/fitjpsikst
#mkdir ~/public_html/fitjpsikst/$curdir/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut6
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut6
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut6/NOFCME
#cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut6/NOFCME/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut6/PIDtable/
#cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut6/PIDtable/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut6/MergedFits/
#cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut6/MergedFits/
#mkdir ~/public_html/fitjpsikst/$curdir/$tagcut6/ImportantTablesAndFigures/
#cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut6/ImportantTablesAndFigures/
#cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut6/ImportantTablesAndFigures/
#cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcut6/ImportantTablesAndFigures/
#cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut6/ImportantTablesAndFigures/
#cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut6/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut6/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut6/ImportantTablesAndFigures/
#cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut6/ImportantTablesAndFigures/
#
#
#mkdir ../Archive/$tagcut6
#mkdir ../Archive/$tagcut6/workspace
#cp ../workspace/* ../Archive/$tagcut6/workspace/
#mkdir ../Archive/$tagcut6/PIDResult
#cp ../PIDResult/* ../Archive/$tagcut6/PIDResult/
#cp ../PIDtables/* ../Archive/$tagcut6/PIDResult/
#mkdir ../Archive/$tagcut6/MergedFits
#cp ../MergedFits/*pdf ../Archive/$tagcut6/MergedFits/
#mkdir ../Archive/$tagcut6/ImportantTablesAndFigures/
#cp ~/public_html/fitjpsikst/$curdir/$tagcut6/ImportantTablesAndFigures/* ../Archive/$tagcut6/ImportantTablesAndFigures/


for values in 2 25 3 35 # 1 15
do

    rm ../PIDResult/*
    rm ../MergedFits/*
    rm ../workspace/*
    rm ../Sweights/*root
    rm ../bin/*root


    echo $values
    newvar=$values.root


    ./main "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0 && K_MuonNShared<2 && K_MC15TuneV1_ProbNNmu>0.$values"
    ./mainrunbig "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0 && K_MuonNShared<2 && K_MC15TuneV1_ProbNNmu>0.$values" "K_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_IsMuonTight==1.0) && (Brunel_nShared<2)_All"
#./mainPIDCalib "K_(Brunel_IsMuon==1.0) && (Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_IsMuonTight==1.0) && (Brunel_nShared<2)_All" "PID_2DK_isMuon__1_0_&&_K_PIDmu>0_&&__K_PIDmu_K_PIDK_>0_&&_K_isMuonTight__1_0_&&_K_MuonNShared<2.root"
    tagcut7=K_isMuon_true_and_K_PIDmu_gr0_and_K_PIDK_gr0_K_isMuTig_K_MuonNShared_l2_and_K_probnnmu_$values

    mkdir ~/public_html/fitjpsikst
    mkdir ~/public_html/fitjpsikst/$curdir/
    mkdir ~/public_html/fitjpsikst/$curdir/$tagcut7
    mkdir ~/public_html/fitjpsikst/$curdir/$tagcut7
    mkdir ~/public_html/fitjpsikst/$curdir/$tagcut7/NOFCME
    cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/NOFCME/
    mkdir ~/public_html/fitjpsikst/$curdir/$tagcut7/PIDtable/
    cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut7/PIDtable/
    mkdir ~/public_html/fitjpsikst/$curdir/$tagcut7/MergedFits/
    cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/MergedFits/
    mkdir ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
    cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
    cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
    cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
    cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
    cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
    cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
    cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
    cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
    
    
    mkdir ../Archive/$tagcut7
    mkdir ../Archive/$tagcut7/workspace
    cp ../workspace/* ../Archive/$tagcut7/workspace/
    mkdir ../Archive/$tagcut7/PIDResult
    cp ../PIDResult/* ../Archive/$tagcut7/PIDResult/
    cp ../PIDtables/* ../Archive/$tagcut7/PIDResult/
    mkdir ../Archive/$tagcut7/MergedFits
    cp ../MergedFits/*pdf ../Archive/$tagcut7/MergedFits/
    mkdir ../Archive/$tagcut7/ImportantTablesAndFigures/
    cp ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/* ../Archive/$tagcut7/ImportantTablesAndFigures/

done









