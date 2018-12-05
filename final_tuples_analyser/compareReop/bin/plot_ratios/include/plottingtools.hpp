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

using namespace std;

string d2s(double d);
void plotvariable(string k, double low, double high);
void plotvariablebeforeq2(string k, double low, double high, string xaxis);
void plotvariableafterq2(string k, double low, double high, string xaxis);
void plotvariablethreedis(string file1, string file2, string file3, string tag1, string tag2, string tag3,string k, double low, double high, string xaxis);
void plotvariablesixdisnoscale(string scale,string nameforplot, string file1, string file2, string file3, string file4, string file5, string file6, string tag1, string tag2, string tag3, string tag4, string tag5, string tag6, string k, double low, double high, string xaxis);
void plotvariableratio(string scale,string nameforplot, string file1, string file2, string tag1, string tag2, string k, double low, double high, string xaxis);
void plotvariablesixdisnoscaleratio(string scale,string nameforplot, string file1, string file2, string file3, string file4, string file5, string file6, string tag1, string tag2, string tag3, string tag4, string tag5, string tag6, string k, double low, double high, string xaxis);
void plotvariablesixdis(string nameforplot, string file1, string file2, string file3, string file4, string file5, string file6, string tag1, string tag2, string tag3, string tag4, string tag5, string tag6, string k, double low, double high, string xaxis);
void plotvariableratioVECTOR(string scale,string nameforplot, string file1, vector<string> file2, string sample1, vector<string> tag2, string k, double low, double high, string xaxis);

void plotvariableratioVECTORolderr(string scale,string nameforplot, string file1, vector<string> file2, string sample1, vector<string> tag2, string k, double low, double high, string xaxis);
