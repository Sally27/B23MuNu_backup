#include<TROOT.h>

void run_codes()
{
	gROOT->ProcessLine(".L TMVAClassificationApplication.C");
	gROOT->ProcessLine("TMVAClassificationApplication(\"/projects/lhcb/data/thibaud/trees/tmva8_trees/tmva_trees/Bc2Jpsi3pi_Sim08a_2012_MD_tmva.root\", \"BDT\")");
	gROOT->ProcessLine("TMVAClassificationApplication(\"/projects/lhcb/data/thibaud/trees/tmva8_trees/tmva_trees/Bc2Jpsi3pi_Sim08a_2012_MU_tmva.root\", \"BDT\")");
	gROOT->ProcessLine("TMVAClassificationApplication(\"/projects/lhcb/data/thibaud/trees/tmva8_trees/tmva_trees/Bc2Jpsi3pi_Sim08d_2011_MD_tmva.root\", \"BDT\")");
	gROOT->ProcessLine("TMVAClassificationApplication(\"/projects/lhcb/data/thibaud/trees/tmva8_trees/tmva_trees/Bc2Jpsi3pi_Sim08d_2011_MU_tmva.root\", \"BDT\")");
	gROOT->ProcessLine("TMVAClassificationApplication(\"/projects/lhcb/data/thibaud/trees/tmva8_trees/tmva_trees/Bc2Jpsi3pi_Sim08d_2012_MD_tmva.root\", \"BDT\")");
	gROOT->ProcessLine("TMVAClassificationApplication(\"/projects/lhcb/data/thibaud/trees/tmva8_trees/tmva_trees/Bc2Jpsi3pi_Sim08d_2012_MU_tmva.root\", \"BDT\")");
}	
