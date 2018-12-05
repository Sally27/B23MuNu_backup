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
TTree* gettreemcsig(string file, string weight);
TTree* gettreemisidkaon();
TTree* gettreemisidpion();
TTree* gettreemisidpionnormalized();
TTree* gettreemisidkaonnormalized();
TTree* gettreepartreco();

string d2s(double d);
double cutTree(string nametree, string decaytreename, string namecuttree, string cuts);
TTree* gettreecomb(string filename, string cuts, string tagsoft, string taghard);
TTree* gettreecomb(string filename, string cuts, string tag);
TTree* gettreemisidkaon(string filename, string tags);
TTree* gettreemisidpion(string filename, string tags);
TTree* gettreemisidkaonsoft(string tags);
TTree* gettreemisidpionsoft(string tags);
TTree* gettreemisidkaonhard(string tags);
TTree* gettreemisidpionhard(string tags);

//Fitting functions//
vector<double> paramfitsignal(string file, string weight);
vector<double> paramfitcombi(string cut, string tagsoft, string taghard);
vector<double> paramfitcombi(string cut, string tag);
vector<double> fitmisid(string soft, string hard);
vector<double> fitmisidcut(string kaonname, string pionname, string cut);
vector<double> fitpartreco(string filename);

vector<double> biny();
vector<double> binmuonx();
double calaveffofasamplesoft(string softfile, string softweight);
double calaveffofasamplehard(string hardfile, string hardweight);
void  addmultiplicationofbranches();
void addmultiplicationofbranches(string filename, string first, string second, string third, string nameofbranch, string newfilename);
double calaveffofasamplemu1(string filename, string weightfile, string wfilecuts, string weightfilesup, string wfilecutssup, string muon, string eta, string name, string newfilename);
void addratioofbranches(string filename, string first, string second, string name, string newfilename);
void printvalue(string nametree, string decaytreename, string variable);
//FINAL use of reading trees//
TTree* gettreepartreco(string filename);

vector<double> fitmisidcuts3samples(string kaonsamplename, string pionsamplename, string protonsample ,string cut);
vector<double> fitmisidcuts3samples2(string kaonsamplename, string pionsamplename, string protonsample ,string cut);

int getmyentries(string nametree, string decaytreename);

