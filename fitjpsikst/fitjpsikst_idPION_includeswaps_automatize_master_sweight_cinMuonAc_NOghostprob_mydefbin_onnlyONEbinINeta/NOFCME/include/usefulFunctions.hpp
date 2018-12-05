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
#include "TTree.h"

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
void copyTreeWithNewVar(TTree*& tNew, TTree* tOld, string cut, string formula, string newVarName);
bool setBranchStatusTTF(TTree* t, string cuts);
struct valError{
   double err;
   double val;
};
string cleanForTables(string str);
string cleanAbsolutelyNameString(string str);
string roundToError(valError& ve, bool wantLatex = false);
string roundToError(RooRealVar const& var, bool wantLatex = false);
vector<double> binx();
vector<double> binxjack();
vector<double> biny();
vector<double> binz();
vector<double> binycourse();
string cleanNameString(string str);
void plotMergedFits(vector<double> binningx, vector<double> binningy, string pidcut, string state, string path);
void plotMergedFitsPretty(vector<double> binningx, vector<double> binningy, string pidcut, string state, string path);
void plotMergedFitsPrettyLogy(vector<double> binningx, vector<double> binningy, string pidcut, string state, string path);
//void prepare3Dhist(string piddir, string name, vector<double> xbin, vector<double> ybin, vector<double> zbin);
//void prepare2Dhist(string piddir, string name, vector<double> xbin, vector<double> ybin);
double cutTree(string nametree, string decaytreename, string namecuttree, string cuts);
double normalerror(double val1, double err1, double val2, double err2);
#endif
