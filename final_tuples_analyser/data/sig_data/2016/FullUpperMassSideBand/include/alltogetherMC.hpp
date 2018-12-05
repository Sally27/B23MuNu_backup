
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
//#include "alltogetherMC.hpp"

using namespace std;

int getmyentries(string nametree, string decaytreename); 
void addcostheta(string filename, string decaytreename, string newfilename);
double mctruth(string filename, string decaytreename, string newfilename);
double Jpsi(string filename, string decaytreename, string newfilename);
string addKFoldandW(string filename, string decaytreename, string newfilename);
void addqsqinf(string filename, string decaytreename, string newfilename);
double cutTree(string nametree, string decaytreename, string namecuttree, string cuts);
void convertbranchname(string filename, string decaytreename, string newfilename);
void converttobplus(string filename, string decaytreename, string newfilename);
void printvalue(string nametree, string decaytreename, string variable);
void emulatetrigger(string nametree, string decaytreename, string newfilename);
void getTCKprop(string nametree, string decaytreename, string newfilename);
double mimiqueL0effMC(string nametree, string decaytreename, string newfilename);

double mimiqueHLT1effMC(string nametree, string decaytreename, string newfilename);
