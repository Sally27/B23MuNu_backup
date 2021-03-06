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
#include "TROOT.h"
#include "TTreeFormula.h"
#include "TTree.h"
#include<iostream>
#include "TH1F.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"
#include<algorithm>
#include "TTreeFormula.h"

using namespace std;

double calculatePIDfromWeights(string filename, string decaytreename, string weightvar);
double calculatePIDfromWeights2muons(string filename, string decaytreename, string muon1, string muon2);
void convertbranchname(string filename, string decaytreename, string newfilename);
string d2s(double d);
double cutTree(string nametree, string decaytreename, string namecuttree, string cuts);
int getmyentries(string nametree, string decaytreename);

