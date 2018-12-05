#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"
#include<string>
#include<vector>
#include "THStack.h"
#include "TLine.h"
#include <sstream>
#include <iostream>
#include<algorithm>
#include "TLegend.h"
#include "TROOT.h"
#include "TStyle.h"
#include "comparedistributionsthstack.hpp"
using namespace std;

class DataSample {
 public:
  DataSample(std::string filename, std::string treename) : _filename(filename), _treename(treename), f(NULL), t(NULL)
  { this->open(); }
  ~DataSample() { this->close(); }
  TString _filename;
  TString _treename;
  TFile *f;
  TTree *t;
  void open();
  void close();
};

void DataSample::open()
{
  f = new TFile(_filename);
  t = (TTree*)f->Get(_treename);
}

void DataSample::close()
{
  if (f)
    if (f->IsOpen())
        f->Close();
  delete f;
}


int main()
{

gROOT->ProcessLine(".x lhcbSally.C");

  string k = "Bplus_PT";
  double low(0.0);
  double high(20000.0);
//  double yaxismax(20000.0);
//plotvariablebeforeq2("minq2", 0, 10000000, "minq^{2} [MeV^{2}/c^{4}]");
//plotvariablebeforeq2("maxq2", 0, 35000000, "maxq^{2} [MeV^{2}/c^{4}]");
//plotvariablePID("nTracks", "nTracks", 0, 500, "nTracks");
//plotvariablePID("Pi_Eta", "mu3_ETA", 0, 5, "ETA");
//plotvariablePID("Pi_PT", "mu3_PT", 0, 50000, "PT");
//plotvariablePID("Pi_V2ProbNNghost", "mu3_ProbNNghost", 0, 0.3, "ProbNNghost");

vector<double> momentum;
vector<double> eta;

momentum.push_back(3000);
momentum.push_back(9300); 
momentum.push_back(15600);
momentum.push_back(19000);
momentum.push_back(24400);
momentum.push_back(29800);
momentum.push_back(35200);
momentum.push_back(40600); 
momentum.push_back(46000);
momentum.push_back(51400);
momentum.push_back(56800);
momentum.push_back(62200);
momentum.push_back(67600);
momentum.push_back(73000);
momentum.push_back(78400);
momentum.push_back(83800);
momentum.push_back(89200);
momentum.push_back(94600);
momentum.push_back(100000);

eta.push_back(1.5);
eta.push_back(2.375);
eta.push_back(3.25);
eta.push_back(4.125);
eta.push_back(5);

//plotvariablePID("Pi_V2ProbNNghost", "mu3_ProbNNghost", 0, 0.9, "ProbNNghost");
//plotvariablePID("Pi_P", "mu3_P", 0, 150000, "P");
plotvariablePIDbinPandETA("Pi_P", "mu3_P", 2000, 20000, "P", 3000, 18000, 0, 5);

for(int(i=0); i<momentum.size()-1; i++)
{
	for(int(j=0); j<eta.size()-1; j++){	
//		plotvariablePIDbinPandETA("Pi_V2ProbNNghost", "mu3_ProbNNghost", 0, 0.9,"ProbNNghost", momentum.at(i), momentum.at(i+1), eta.at(j), eta.at(j+1));
        plotvariablePIDbinPandETAsweight("Pi_V2ProbNNghost", "mu3_ProbNNghost", 0, 0.9,"ProbNNghost", momentum.at(i), momentum.at(i+1), eta.at(j), eta.at(j+1));
	}
}

//plotvariablePIDsweight("nTracks", "nTracks", 0, 500, "nTracks");
//plotvariablePIDsweight("Pi_Eta", "mu3_ETA", 0, 5, "ETA");
//plotvariablePIDsweight("Pi_PT", "mu3_PT", 0, 50000, "PT");
//plotvariablePIDsweight("Pi_V2ProbNNghost", "mu3_ProbNNghost", 0, 0.9, "ProbNNghost");

//plotvariablePIDsweight("Pi_P", "mu3_P", 0, 150000, "P");



//plotvariableafterq2("Bplus_pmu_ISOLATION_BDT1_weights", -2.5, 5.0, "Isolation Variable");


//plotvariable("minq2", 0.0, 10000000.0);
//plotvariable("maxq2", 0.0, 35000000.0);

//plotvariableafterq2("Bplus_P", 0, 1000000, "B^{+} momentum");


return(0);
}



  

