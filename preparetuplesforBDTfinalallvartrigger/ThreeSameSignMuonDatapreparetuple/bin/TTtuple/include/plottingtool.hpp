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
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TObjArray.h"
#include "TTreeFormula.h"
#include "TH2I.h"
#include "THStack.h"
#include "TObjArray.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TText.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TPaveText.h"
#include "TTree.h"
#include "TTreeFormula.h"
#include "TFile.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <string>
#include "TH2F.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TGraph.h"
#include<vector>
#include<algorithm>
#include "TH3D.h"
#include "TH3F.h"
#include "TPad.h"

using namespace std;
double s2d(string str);
string d2s(double d);
void plotonevariable(string filename, string k, double low, double high, int nbins);
bool setBranchStatusTTF(TTree* t, string cuts);
int plotposition3D(string filename, string cuts, string var1name, string var2name, string var3name);
bool separateString(string& str1, double& min, double& max);
string cleanNameString(string str);
int plotposition2(string filename, string cuts, string var1name, string var2name);
int plotposition2morecanv(string filename, string cuts, string var1name, string var2name, string variablec2);
void printValue(string filename,string variable);
int plotposition(string filename, string cuts, string var1name, string var2name);
void plotonevariable3folders(string filename, string filename2, string filename3,string k, double low, double high, int nbins, string nameplot);
void plotvariable(string k, double low, double high);
void plotstackmytrigger(int nbins,string scale,string nameforplot, string file1, string file2, string file3, string file4,string tag1, string tag2, string tag3, string tag4, string k, double low, double high, string xaxis, string variable);
void plotstackimprovedexclude2(int nbins,string scale,string nameforplot, string file1, string file2, string file3, string file4,string tag1, string tag2, string tag3, string tag4, string k, double low, double high, string xaxis, string variable);
void plotstackimprovedexclude(int nbins, string scale,string nameforplot, string file1, string file2, string file3, string file4,string tag1, string tag2, string tag3, string tag4, string k, double low, double high, string xaxis, string variable);
void plotstackimproved(int nbins, string scale,string nameforplot, string file1, string file2, string file3, string file4,string tag1, string tag2, string tag3, string tag4, string k, double low, double high, string xaxis, string variable);
void plotstack(string scale,string nameforplot, string file1, string file2, string file3, string file4,string tag1, string tag2, string tag3, string tag4, string k, double low, double high, string xaxis, string variable);
void addmissingpt(string filename, string newfilename);

  

