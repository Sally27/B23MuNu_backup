for cut2 in BasicCut probmu1 probmu15 probmu2 probmu25 probmu3 probmu35
do
    robot=$cut2.root
##hadd haddtuples/JpsiKdata_2015.root bin/B2JpsiKDataDetached2015_v42r1*
    hadd -f haddtuples_correct/Signaldata_2016_$robot bin/Bu23MuNuData2016_corrmFUSMB*$robot bin/Bu23MuNuData2016_lmsbregion*$robot

done




