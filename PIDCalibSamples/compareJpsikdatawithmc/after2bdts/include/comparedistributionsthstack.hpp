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
using namespace std;

string d2s(double d);


void plotvariable(string k, double low, double high);
void plotvariablebeforeq2(string k, double low, double high, string xaxis);
void plotvariableafterq2(string k, double low, double high, string xaxis);
void plotvariablePID(string pidcalibvar, string tuplevar, double low, double high, string xaxis);

void plotvariablePIDbinPandETA(string pidcalibvar, string tuplevar, double low, double high, string xaxis, double lowPbin, double highPbin, double lowETAbin, double highETAbin);
void plotvariablePIDbinPandETAsweight(string pidcalibvar, string tuplevar, double low, double high, string xaxis, double lowPbin, double highPbin, double lowETAbin, double highETAbin);
void plotvariablePIDbinPandETAsweightexperimental(string pidcalibvar, string tuplevar, double low, double high, string xaxis, double lowPbin, double highPbin, double lowETAbin, double highETAbin);

void plotvariablePIDsweight(string pidcalibvar, string tuplevar, double low, double high, string xaxis);




  

