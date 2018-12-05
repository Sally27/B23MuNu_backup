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


int main(int argc, char *argv[]){

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

string sample2016=argv[2];
string sampleRun1=argv[1];

copytree(sampleRun1.c_str(),"DecayTree" , "2016MC.root", variables);

copytree(sample2016.c_str(),"DecayTree" , "Run1MC.root", variables);

return(0);


}



