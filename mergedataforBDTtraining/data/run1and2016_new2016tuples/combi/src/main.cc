#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TH1F.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"
#include<algorithm>
#include "TTreeFormula.h"
#include "alltogetherMC.hpp"
#include<iostream>

using namespace std;


int main(){

vector<string> variables;
variables.push_back("Bplus_P");
variables.push_back("Bplus_PT");
variables.push_back("mu1_PT");
variables.push_back("mu2_PT");
variables.push_back("mu3_PT");
variables.push_back("mu1_P");
variables.push_back("mu2_P");
variables.push_back("mu3_P");
variables.push_back("Bplus_TAU");
variables.push_back("Bplus_DIRA_OWNPV");
variables.push_back("mu1_MINIPCHI2");
variables.push_back("mu2_MINIPCHI2");
variables.push_back("mu3_MINIPCHI2");
variables.push_back("Bplus_pmu_ISOLATION_BDT1_weights");
variables.push_back("Bplus_ENDVERTEX_CHI2");
variables.push_back("Bplus_FD_CHI2");
variables.push_back("KFold");
variables.push_back("W");

copytree("/vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_new2016tuples/combi/Bu23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut.root","DecayTree" , "Combi2016Data.root", variables);

copytree("/vols/lhcb/ss4314/mergedataforBDTtraining/data/run1and2016_new2016tuples/combi/Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root","DecayTree" , "CombiRun1Data.root", variables);

return(0);


}



