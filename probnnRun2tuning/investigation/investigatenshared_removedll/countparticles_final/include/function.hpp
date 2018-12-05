#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TString.h"
#include <string>
#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TH3F.h"
#include <numeric>
#include "TGraph.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <string>
#include "TLegend.h"
#include "TStyle.h"
#include "TTreeFormula.h"


using namespace std;


double s2d(string str);
string bool_cast(const bool b); 
string d2s(double d);
string f2s(float d);
string i2s(int i);
void plotvariable2Dnostack_only2_10bins(string scale,string nameforplot, string file1, string file2, string tag1, string tag2, string k, string k2,double low, double high, string xaxis, string variable);
vector<double> binx();
vector<double> biny();
vector<float> newbinmydata(string filename, string decaytree, string species, string year);
void plotvariable2Dstack(string scale,string nameforplot, string file1, string file2, string file3, string tag1, string tag2, string tag3, string k, string k2,double low, double high, string xaxis, string variable);
void plotvariable2Dnostack(string scale,string nameforplot, string file1, string file2, string file3, string tag1, string tag2, string tag3, string k, string k2,double low, double high, string xaxis, string variable);
void plotvariable2Dnostack_only2(string scale,string nameforplot, string file1, string file2, string tag1, string tag2, string k, string k2,double low, double high, string xaxis, string variable);
void counttheparticles(string filename, string decaytreename, string species, string year);
void plotvariable(string scale,string nameforplot, string file1, string file2, string file3, string tag1, string tag2, string tag3, string k, double low, double high, string xaxis, string variable);
