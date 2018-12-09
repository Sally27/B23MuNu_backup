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
#include "RooSimultaneous.h"
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
void define_pdf_from_scratch();
double fitTwiceOld2_2(RooDataSet* data,int nToys, double CLsBF, TTree* treename, bool update);
string cleanNameString(string str);
double calculatemedian(TH1F * hbackground_DLL);
double fitgaussianandplot(TH1F * hsignal_DLL, string category, std::ofstream& myfile, int nToys, double CLsBF);
double calculateCLs_usingGaussian(TH1F * hsignal_DLL, TH1F * hbackground_DLL, double value, std::ofstream& myfile, double CLsBF);
double calculateCLs(TH1F * hsignal_DLL, TH1F * hbackground_DLL, double value, std::ofstream& myfile, double CLsBF);
std::vector<RooDataSet*> generateData_2(double BFval,int nToys);
std::vector<RooDataSet*> generateData(RooRealVar* BF,double BFval,RooAbsPdf* model_LL,RooAbsPdf* model_DD,RooRealVar* mass,RooCategory cat, int nToys); 
double fitTwice(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* mass, TTree* treename, bool update);
double fitTwiceOld(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* mass, TTree* treename, bool update);
double fitTwicePat(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF);

void calculateFOM_chi2(RooRealVar* BF,RooAbsPdf* model,int nToys, double CLsBF, int toyfit, string type);

double fitTwiceOld2_con_new(RooDataSet* data,int nToy, int nToys ,double CLsBF, TTree* treename, bool update);
double fitTwiceOld2_con_new_onerange(RooDataSet* data,int nToys, double CLsBF, TTree* treename, bool update);


double fitTwiceOld2_con(RooAbsPdf* m_mean, RooAbsPdf* m_num, RooAbsPdf* m_sigma,RooAbsPdf* m_mean_high, RooAbsPdf* m_num_high, RooAbsPdf* m_sigma_high,RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* Bplus_Corrected_Mass, TTree* treename, bool update, RooCategory* cat);
double fitTwiceOld2(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* Bplus_Corrected_Mass, TTree* treename, bool update, RooCategory* category);
