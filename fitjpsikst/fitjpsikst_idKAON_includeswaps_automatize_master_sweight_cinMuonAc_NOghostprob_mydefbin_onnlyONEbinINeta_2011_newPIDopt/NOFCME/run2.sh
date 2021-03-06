#!/bin/sh



echo "Cleaning all the directories"

KFOLD_PATH=/vols/lhcb/ss4314/customlib/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

curdir=fitjpsikst_idKAON_includeswaps_automatize_master_sweight_cinMuonAc_NOghostprob_mydefbin_onnlyONEbinINeta_2011_newPIDopt

mkdir PIDResult MergedFits workspace Sweights PIDtables

cd bin

for values in 4 5 6
do

    rm ../PIDResult/*
    rm ../MergedFits/*
    rm ../workspace/*
    rm ../Sweights/*root
    rm ../bin/*root


    echo $values
    newvar=$values.root


    ./main "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && (Pi_ProbNNmu-Pi_ProbNNpi)>-0.$values"
    ./mainrunbig "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && (Pi_ProbNNmu-Pi_ProbNNpi)>-0.$values" "Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((MC12TuneV2_ProbNNmu - MC12TuneV2_ProbNNpi) > -0.$values)_All"
    ./mainPIDCalib "Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((MC12TuneV2_ProbNNmu - MC12TuneV2_ProbNNpi) > -0.$values)_All" "PID_2DPi_isMuon__1_0_&&_Pi_PIDmu>0_&&_Pi_PIDmu_Pi_PIDK>0_&&_Pi_nShared__0_&&__Pi_ProbNNmu_Pi_ProbNNpi_>_0_$newvar"
    tagcut7=Pi_isMuon_true_and_Pi_PIDmu_gr0_and_Pi_PIDPi_gr0_Pi_nShared0_Pronnmu_minus_Probnnpi_gr_0_$values
    
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

