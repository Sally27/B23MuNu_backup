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
#include "TPaveText.h"
#include <string>
#include <iostream>
#include <sstream>
#include "TMath.h"
#include <math.h>
#include "DataSample.hpp"

using namespace std;

void plotvariable_one(string k, double low, double high, string xaxis, string filenamereco, string year, double scalecalc);
void plotvariable_partrecostudy_checkcorr(string k, double low, double high, string xaxis, string filenamereco,string filenamereco2 ,string year, double scalecalc);
void plotvariablebeforeq2(string k, double low, double high, string xaxis,string filemcsig, string filepartreco, string filemisid, string filecombi, string year);
void plotvariable_partrecostudy(string k, double low, double high, string xaxis, string filenamesig, string filenamereco, string year, double scale);
void plotvariablebeforeq2_line(string k, double low, double high, string xaxis,string filemcsig, string filepartreco, string filemisid, string filecombi);
void plotvariablefourdisnoscale(string scale,string nameforplot, string file1, string file2, string file3, string file4,string tag1, string tag2, string tag3, string tag4, string k, string k_2016, double low, double high, string xaxis, string variable,string legend, string legendTitle);
