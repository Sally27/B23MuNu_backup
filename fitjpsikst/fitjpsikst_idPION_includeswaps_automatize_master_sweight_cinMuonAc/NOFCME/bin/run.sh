#!/bin/sh

echo "Cleaning all the directories"

KFOLD_PATH=/vols/lhcb/ss4314/customlib/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
rm ../PIDResult/*
rm ../MergedFits/*
rm ../workspace/*
rm ../Sweights/*root
rm ../bin/*root

curdir=fitjpsikst_idPION_includeswaps_automatize_master_sweight_cinMuonAc

./main "K_isMuon==1.0"
./mainrunbig "K_isMuon==1.0" "K_(IsMuon==1.0)_All"
./mainPIDCalib "K_(IsMuon==1.0)_All" "PID_2DK_isMuon__1_0.root" 

tagcut1=K_isMuon_true

mkdir ~/public_html/fitjpsikst
mkdir ~/public_html/fitjpsikst/$curdir/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut1
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut1
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut1/NOFCME
cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/NOFCME/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut1/PIDtable/
cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut1/PIDtable/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut1/MergedFits/
cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/MergedFits/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/

rm -r Archive 

mkdir ../Archive
mkdir ../Archive/$tagcut1
mkdir ../Archive/$tagcut1/workspace
cp ../workspace/* ../Archive/$tagcut1/workspace/
mkdir ../Archive/$tagcut1/PIDResult
cp ../PIDResult/* ../Archive/$tagcut1/PIDResult/
cp ../PIDtables/* ../Archive/$tagcut1/PIDResult/
mkdir ../Archive/$tagcut1/MergedFits
cp ../MergedFits/*pdf ../Archive/$tagcut1/MergedFits/
mkdir ../Archive/$tagcut1/ImportantTablesAndFigures/
cp ~/public_html/fitjpsikst/$curdir/$tagcut1/ImportantTablesAndFigures/* ../Archive/$tagcut1/ImportantTablesAndFigures/


rm ../PIDResult/*
rm ../MergedFits/*
rm ../workspace/*
rm ../Sweights/*root
rm ../bin/*root


./main "K_isMuon==1.0 && K_nShared==0"
./mainrunbig "K_isMuon==1.0 && K_nShared==0" "K_(IsMuon==1.0) && (nShared==0)_All"
./mainPIDCalib "K_(IsMuon==1.0) && (nShared==0)_All" "PID_2DK_isMuon__1_0_&&_K_nShared__0.root" 

tagcut2=K_isMuon_true_and_KnShared_0

mkdir ~/public_html/fitjpsikst
mkdir ~/public_html/fitjpsikst/$curdir/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut2
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut2
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut2/NOFCME
cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/NOFCME/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut2/PIDtable/
cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut2/PIDtable/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut2/MergedFits/
cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/MergedFits/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/


mkdir ../Archive/$tagcut2
mkdir ../Archive/$tagcut2/workspace
cp ../workspace/* ../Archive/$tagcut2/workspace/
mkdir ../Archive/$tagcut2/PIDResult
cp ../PIDResult/* ../Archive/$tagcut2/PIDResult/
cp ../PIDtables/* ../Archive/$tagcut2/PIDResult/
mkdir ../Archive/$tagcut2/MergedFits
cp ../MergedFits/*pdf ../Archive/$tagcut2/MergedFits/
mkdir ../Archive/$tagcut2/ImportantTablesAndFigures/
cp ~/public_html/fitjpsikst/$curdir/$tagcut2/ImportantTablesAndFigures/* ../Archive/$tagcut2/ImportantTablesAndFigures/
#
#
#
rm ../PIDResult/*
rm ../MergedFits/*
rm ../workspace/*
rm ../Sweights/*root
rm ../bin/*root


./main "K_isMuon==1.0 && K_nShared==0 && K_ProbNNmu>0.5"
./mainrunbig "K_isMuon==1.0 && K_nShared==0 && K_ProbNNmu>0.5" "K_(IsMuon==1.0) && (nShared==0) && (V2ProbNNmu > 0.5)_All"
./mainPIDCalib "K_(IsMuon==1.0) && (nShared==0) && (V2ProbNNmu > 0.5)_All" "PID_2DK_isMuon__1_0_&&_K_nShared__0_&&_K_ProbNNmu>0_5.root" 
tagcut3=K_isMuon_true_and_KnShared_0_and_K_Probnnmu_0_5

mkdir ~/public_html/fitjpsikst
mkdir ~/public_html/fitjpsikst/$curdir/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut3
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut3
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut3/NOFCME
cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/NOFCME/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut3/PIDtable/
cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut3/PIDtable/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut3/MergedFits/
cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/MergedFits/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/
#
#
mkdir ../Archive/$tagcut3
mkdir ../Archive/$tagcut3/workspace
cp ../workspace/* ../Archive/$tagcut3/workspace/
mkdir ../Archive/$tagcut3/PIDResult
cp ../PIDResult/* ../Archive/$tagcut3/PIDResult/
cp ../PIDtables/* ../Archive/$tagcut3/PIDResult/
mkdir ../Archive/$tagcut3/MergedFits
cp ../MergedFits/*pdf ../Archive/$tagcut3/MergedFits/
mkdir ../Archive/$tagcut3/ImportantTablesAndFigures/
cp ~/public_html/fitjpsikst/$curdir/$tagcut3/ImportantTablesAndFigures/* ../Archive/$tagcut3/ImportantTablesAndFigures/


rm ../PIDResult/*
rm ../MergedFits/*
rm ../workspace/*
rm ../Sweights/*root
rm ../bin/*root


./main "K_isMuon==1.0 && K_PIDmu>0"
./mainrunbig "K_isMuon==1.0 && K_PIDmu>0" "K_(IsMuon==1.0) && (DLLmu > 0.0)_All"
./mainPIDCalib "K_(IsMuon==1.0) && (DLLmu > 0.0)_All" "PID_2DK_isMuon__1_0_&&_K_PIDmu>0.root" 
tagcut4=K_isMuon_true_and_K_PIDmu_gr0

mkdir ~/public_html/fitjpsikst
mkdir ~/public_html/fitjpsikst/$curdir/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut4
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut4
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut4/NOFCME
cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/NOFCME/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut4/PIDtable/
cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut4/PIDtable/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut4/MergedFits/
cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/MergedFits/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/
#
#
mkdir ../Archive/$tagcut4
mkdir ../Archive/$tagcut4/workspace
cp ../workspace/* ../Archive/$tagcut4/workspace/
mkdir ../Archive/$tagcut4/PIDResult
cp ../PIDResult/* ../Archive/$tagcut4/PIDResult/
cp ../PIDtables/* ../Archive/$tagcut4/PIDResult/
mkdir ../Archive/$tagcut4/MergedFits
cp ../MergedFits/*pdf ../Archive/$tagcut4/MergedFits/
mkdir ../Archive/$tagcut4/ImportantTablesAndFigures/
cp ~/public_html/fitjpsikst/$curdir/$tagcut4/ImportantTablesAndFigures/* ../Archive/$tagcut4/ImportantTablesAndFigures/



rm ../PIDResult/*
rm ../MergedFits/*
rm ../workspace/*
rm ../Sweights/*root
rm ../bin/*root


./main "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 "
./mainrunbig "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0" "K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All"
./mainPIDCalib "K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All" "PID_2DK_isMuon__1_0_&&_K_PIDmu>0_&&__K_PIDmu_K_PIDK_>0_.root"
tagcut5=K_isMuon_true_and_K_PIDmu_gr0_and_K_PIDK_gr0

mkdir ~/public_html/fitjpsikst
mkdir ~/public_html/fitjpsikst/$curdir/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut5
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut5
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut5/NOFCME
cp ../workspace/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/NOFCME/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut5/PIDtable/
cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut5/PIDtable/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut5/MergedFits/
cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/MergedFits/
mkdir ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
cp ../MergedFits/*pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
cp ../PIDResult/*txt ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
cp ../workspace/mclambdafit_rookeys.pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
cp ../workspace/mcsigfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
cp ../workspace/mcswapsfit_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKstFitLogyPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKstFitPretty.pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/
cp ../workspace/plotJpsiKst_.pdf ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/


mkdir ../Archive/$tagcut5
mkdir ../Archive/$tagcut5/workspace
cp ../workspace/* ../Archive/$tagcut5/workspace/
mkdir ../Archive/$tagcut5/PIDResult
cp ../PIDResult/* ../Archive/$tagcut5/PIDResult/
cp ../PIDtables/* ../Archive/$tagcut5/PIDResult/
mkdir ../Archive/$tagcut5/MergedFits
cp ../MergedFits/*pdf ../Archive/$tagcut5/MergedFits/
mkdir ../Archive/$tagcut5/ImportantTablesAndFigures/
cp ~/public_html/fitjpsikst/$curdir/$tagcut5/ImportantTablesAndFigures/* ../Archive/$tagcut5/ImportantTablesAndFigures/
