#ifndef USEFULFUNCTIONS
#define USEFULFUNCTIONS

#include<RooPlot.h>
#include<RooHist.h>
#include<TLine.h>
#include<TAxis.h>
#include<RooRealVar.h>
#include<TCanvas.h>
#include<TGraphAsymmErrors.h>
#include<string>
#include "TFile.h"
#include<sstream>
//#include "ComputeChi2.hpp"
#include "RooMinuit.h"
#include "TMath.h"
#include "RooAbsPdf.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TPaveText.h"
#include "TH1.h"
#include "TLatex.h"
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
#include<iostream>



using namespace RooFit;
using namespace std;


void savePullPlot(RooPlot& graph, string fileName);
void saveFitInfo(ofstream& out, RooPlot* frame, int floatingParams, RooAbsPdf* pdf);

void lhcbStyle(double fontsize);
void make2DPullPlot(TH1* data, TH1* model, TH1* pull);
double s2d(string str);
string d2s(double d);
string d2s(double nbr, int nfixed );
string i2s(int i);

struct valError{
   double err;
   double val;
};
string roundToError(valError& ve, bool wantLatex = false);
string roundToError(RooRealVar const& var, bool wantLatex = false);
void FillEffInfo(TTree* fillinfotree, string nameofcut, double efficiency, bool update);

#endif
