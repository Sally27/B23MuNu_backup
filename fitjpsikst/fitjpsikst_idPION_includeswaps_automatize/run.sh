#!/bin/sh

echo "Cleaning all the directories"

KFOLD_PATH=/vols/lhcb/ss4314/customlib/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH
rm ../PIDResult/*
rm ../PIDtables/*
rm ../MergedFits/*
rm ../workspace/*
rm ../Sweights/*root
rm ../bin/*root

curdir=fitjpsikst_idPION_includeswaps_automatize

./main "K_isMuon==1.0"
./mainrunbig "K_isMuon==1.0"
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
rm ../PIDtables/*
rm ../MergedFits/*
rm ../workspace/*
rm ../Sweights/*root
rm ../bin/*root


./main "K_isMuon==1.0 && K_nShared==0"
./mainrunbig "K_isMuon==1.0 && K_nShared==0"
./mainPIDCalib "K_(IsMuon==1.0)_All" "PID_2DK_isMuon__1_0.root" 

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
