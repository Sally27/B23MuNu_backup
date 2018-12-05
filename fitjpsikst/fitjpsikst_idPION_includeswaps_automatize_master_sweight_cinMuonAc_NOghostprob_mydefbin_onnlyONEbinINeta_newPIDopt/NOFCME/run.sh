#!/bin/sh

echo "Cleaning all the directories"

KFOLD_PATH=/vols/lhcb/ss4314/customlib/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

curdir=fitjpsikst_idPION_includeswaps_automatize_master_sweight_cinMuonAc_NOghostprob_mydefbin_onnlyONEbinINeta_newPIDopt

cd bin

for values in 6 5 4
do 
    
    rm ../PIDResult/*
    rm ../MergedFits/*
    rm ../workspace/*
    rm ../Sweights/*root
    rm ../bin/*root


    echo $values
    newvar=$values.root

    ./main "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && (K_ProbNNmu - K_ProbNNpi)>-0.$values"
    ./mainrunbig "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && (K_ProbNNmu - K_ProbNNpi)>-0.$values" "K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.$values)_All"
    ./mainPIDCalib "K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.$values)_All" "PID_2DK_isMuon__1_0_&&_K_PIDmu>0_&&__K_PIDmu_K_PIDK_>0_&&_K_nShared__0_&&__K_ProbNNmu___K_ProbNNpi_>_0_$newvar"
    tagcut7=K_isMuon_true_and_K_PIDmu_gr0_and_K_PIDK_gr0_K_nShared_0_K_PIDmugr0_Pronnmu_minus_Probnnpi_$values
    
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


#for values in 2 25 3 35
#do 
#    echo $values
#    newvar=$values.root
#
#    ./main "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.$values"
#    ./mainrunbig "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.$values" "K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.$values)_All"
#    ./mainPIDCalib "K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.$values)_All" "PID_2DK_isMuon__1_0_&&_K_PIDmu>0_&&__K_PIDmu_K_PIDK_>0_&&_K_nShared__0_&&_K_ProbNNmu>0_$newvar"
#    tagcut7=K_isMuon_true_and_K_PIDmu_gr0_and_K_PIDK_gr0_K_nShared_0_K_PIDmugr0_$values
#    
#    mkdir ~/public_html/fitjpsikst
#    mkdir ~/public_html/fitjpsikst/$curdir/
#    mkdir ~/public_html/fitjpsikst/$curdir/$tagcut7
#    mkdir ~/public_html/fitjpsikst/$curdir/$tagcut7
#    mkdir ~/public_html/fitjpsikst/$curdir/$tagcut7/NOFCME
#    cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/NOFCME/
#    mkdir ~/public_html/fitjpsikst/$curdir/$tagcut7/PIDtable/
#    cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut7/PIDtable/
#    mkdir ~/public_html/fitjpsikst/$curdir/$tagcut7/MergedFits/
#    cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/MergedFits/
#    mkdir ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
#    cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
#    cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
#    cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
#    cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
#    cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
#    cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
#    cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
#    cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/
#    
#    
#    mkdir ../Archive/$tagcut7
#    mkdir ../Archive/$tagcut7/workspace
#    cp ../workspace/* ../Archive/$tagcut7/workspace/
#    mkdir ../Archive/$tagcut7/PIDResult
#    cp ../PIDResult/* ../Archive/$tagcut7/PIDResult/
#    cp ../PIDtables/* ../Archive/$tagcut7/PIDResult/
#    mkdir ../Archive/$tagcut7/MergedFits
#    cp ../MergedFits/*pdf ../Archive/$tagcut7/MergedFits/
#    mkdir ../Archive/$tagcut7/ImportantTablesAndFigures/
#    cp ~/public_html/fitjpsikst/$curdir/$tagcut7/ImportantTablesAndFigures/* ../Archive/$tagcut7/ImportantTablesAndFigures/
#
#
#
#done


