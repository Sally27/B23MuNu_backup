
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
double addstatandsyst(double stat, double syst);
double round_to_digits(double value, int digits);
string d2s(double d);
string i2s(int i);
double calcEffErr(int numofentriesbefore, int numofentriesafter);
double returnEff(string filename, string decaytreename, string variable);
void FillEffInfo(TTree* fillinfotree, string nameofcut, double efficiency, bool update);
void addtcklumi(string filename, string decaytreename, string newfilename, int index);
int getmyentries(string nametree, string decaytreename); 
void addcostheta(string filename, string decaytreename, string newfilename);
double mctruth(string filename, string decaytreename, string newfilename);
double Jpsi(string filename, string decaytreename, string newfilename);
string addKFoldandW(string filename, string decaytreename, string newfilename);
void addqsqinf(string filename, string decaytreename, string newfilename);
double cutTree(string nametree, string decaytreename, string namecuttree, string cuts);
void convertbranchname(string filename, string decaytreename, string newfilename);
double calculateL0effMC(string nametree, string decaytreename, string newfilename);
double mimiqueL0effMC_default(string nametree, string decaytreename, string newfilename);
double mimiqueL0effMC(string nametree, string decaytreename, string newfilename);
