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
#include "RooAddPdf.h"
#include "RooSimultaneous.h"
#include "TStyle.h"
#include "MyCB.hpp"
#include "TROOT.h"
#include "TPaveText.h"
#include "TH1.h"
#include "TLatex.h"
#include "TFile.h"
#include "TTree.h"
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "usefulFunctions.hpp"


using namespace RooFit;
using namespace std;

double addinquad(vector<double> err);
double returnEff(string filename, string decaytreename, string variable);
void savePullPlot(RooPlot& graph, string fileName);
void saveFitInfo(ofstream& out, RooPlot* frame, int floatingParams, RooAbsPdf* pdf);

void saveFitInfo_abspdf(ofstream& out, RooPlot* frame, int floatingParams, RooAbsPdf* pdf, RooFitResult* res);
string cleanNameString(string str);
void saveFitInfo_simpdf(ofstream& out, RooPlot* frame, int floatingParams, RooSimultaneous* pdf, RooFitResult* res);
void saveFitInfo_addpdf(ofstream& out, RooPlot* frame, int floatingParams, RooAddPdf* pdf, RooFitResult* res);
void saveFitInfo_abspdf_norf(ofstream& out, RooPlot* frame, int floatingParams, RooAbsPdf* pdf);
void saveFitInfo_cb(ofstream& out, RooPlot* frame, int floatingParams, MyCB pdf, RooFitResult* res);
void saveFitInfoExtended(ofstream& out, RooPlot* frame, int floatingParams, RooAbsPdf* pdf, RooFitResult* res);
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
double addstatandsyst(double stat, double syst);
string roundToError(valError& ve, bool wantLatex = false);
string roundToError(RooRealVar const& var, bool wantLatex = false);
double round_to_digits(double value, int digits);
double returnVar(string filename, string decaytreename, string variable);

#endif
