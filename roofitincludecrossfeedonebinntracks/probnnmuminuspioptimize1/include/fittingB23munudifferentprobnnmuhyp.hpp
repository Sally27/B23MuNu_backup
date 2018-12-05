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

TH1* getcorrmspec();
TH1* getcorrmspeccomb();
TTree* gettreecomb();
TTree* gettreemcsig();
TTree* gettreemisidkaon();
TTree* gettreemisidpion();
TTree* gettreemisidpionnormalized();
TTree* gettreemisidkaonnormalized();
TTree* gettreepartreco();

string d2s(double d);
double cutTree(string nametree, string decaytreename, string namecuttree, string cuts);
TTree* gettreecomb(string cuts, string tags);
TTree* gettreemisidkaon(string tags);
TTree* gettreemisidpion(string tags);
TTree* gettreemisidkaonsoft(string tags);
TTree* gettreemisidpionsoft(string tags);
TTree* gettreemisidkaonhard(string tags);
TTree* gettreemisidpionhard(string tags);

//Fitting functions//
vector<double> paramfitsignal();
vector<double> paramfitcombi(string cut, string tag);
vector<double> fitmisid(string soft, string hard);
vector<double> biny();
vector<double> binmuonx();
double calaveffofasamplesoft(string softfile, string softweight);
double calaveffofasamplehard(string hardfile, string hardweight);
void  addmultiplicationofbranches();

