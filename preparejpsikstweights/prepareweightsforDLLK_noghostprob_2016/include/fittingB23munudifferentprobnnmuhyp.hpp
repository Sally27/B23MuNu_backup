#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TH1.h"
#include "TRandom.h"
#include "RooCBShape.h"
#include "Riostream.h"  
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 
#include "RooPlot.h"
#include "RooHist.h"
#include "RooKeysPdf.h"
#include "RooNDKeysPdf.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooFitResult.h"
#include "RooGenericPdf.h"
#include "RooMCStudy.h"
#include "RooChi2MCSModule.h"
#include "TPaveLabel.h"
#include "TLegend.h"
#include "TLatex.h"
#include <vector>
#include <string>
#include "TTreeFormula.h"
#include "TString.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include "MyCB.hpp"


using namespace std;
using namespace RooFit ;


string d2s(double d);
double cutTree(string nametree, string decaytreename, string namecuttree, string cuts);
vector<double> biny();
vector<double> binmuonx();
void  addmultiplicationofbranches();
void addmultiplicationofbranches(string filename, string first, string second, string third, string nameofbranch, string newfilename);
double calaveffofasamplemu1(string filename, string weightfile, string wfilecuts, string weightfilesup, string wfilecutssup, string muon, string eta, string name, string newfilename);
void addratioofbranches(string filename, string first, string second, string name, string newfilename);
void printvalue(string nametree, string decaytreename, string variable);
vector<double> binx();
int getmyentries(string nametree, string decaytreename);
double calaveffofasamplekaon(string filename, string weightfile, string wfilecuts, string weightfileup, string wfilecutsup ,string muon, string eta, string name, string newfilename);
