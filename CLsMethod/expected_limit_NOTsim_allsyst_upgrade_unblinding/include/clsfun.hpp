#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <cmath>
#include "TH1F.h"
#include "TCanvas.h"
#include "TBranch.h"
#include "RooConstVar.h"
#include "RooEffProd.h"
#include "RooBreitWigner.h"
#include "RooNumIntConfig.h"
#include "TF2.h"
#include "TEllipse.h"
#include "TLine.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooAbsPdf.h"
#include "RooCategory.h"
#include "RooArgSet.h"
#include "RooFitResult.h"
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TMath.h"

using namespace std;
string d2s(double d);
string f2s(float d);
string i2s(int i);
double s2d(string str);

string cleanNameString(string str);
double calculatemedian(TH1F * hbackground_DLL);
double fitgaussianandplot(TH1F * hsignal_DLL, string category, std::ofstream& myfile, int nToys, double CLsBF);
double calculateCLs(TH1F * hsignal_DLL, TH1F * hbackground_DLL, double value, std::ofstream& myfile, double CLsBF);
std::vector<RooDataSet*> generateData(RooRealVar* BF,double BFval,RooAbsPdf* model_LL,RooRealVar* mass,int nToys);
std::vector<RooDataSet*> generateData_con(RooRealVar* BF,double BFval,RooAbsPdf* model_LL,RooRealVar* mass, int nToys, RooArgSet con); 
double fitTwice(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* mass, TTree* treename, bool update);
double fitTwiceOld(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* mass, TTree* treename, bool update, int toyfit, RooArgSet constraints);
