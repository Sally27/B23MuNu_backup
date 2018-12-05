#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TString.h"
#include <string>
#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TH3F.h"
#include <numeric>
#include "TGraph.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <string>
#include "TLegend.h"
#include "TStyle.h"
#include "TTreeFormula.h"
#include "addingcrossfeedbranch.hpp"

using namespace std;


int main(){

//vector<float>
efficiency("/vols/lhcbdisk05/ss4314/tightPIDinvestigation/nontrackcalculation/probnnmuminuspi/muon/PerfHists_Mu_Strip20_MagDown_P_ETA.root" , "Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.8)_All", 18, 4);

TFile s("append.root");
   
string misidcuts="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.8)_All";

//--MIS ID EFFICIENCIES FROM TH2F--//
TH2F *miskaon =(TH2F*)s.Get(misidcuts.c_str());



//--Checking the bin boundaries--//
TAxis* xAxis = miskaon->GetXaxis();
TAxis* yAxis = miskaon->GetYaxis();

for(int j(0); j<(18+1); ++j)
{
cout<< "Binx: "<<j<<" : "<<endl;
cout<< "lower edge: "<<xAxis->GetBinLowEdge(j)<<endl;
cout<< "high edge: "<<xAxis->GetBinUpEdge(j)<<endl;
}

for(int j(0); j<(4+1); ++j)
{
cout<< "Biny: "<<j<<" : "<<endl;
cout<< "lower edge: "<<yAxis->GetBinLowEdge(j)<<endl;
cout<< "high edge: "<<yAxis->GetBinUpEdge(j)<<endl;
}


return(0);

}

