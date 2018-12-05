#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH3F.h"
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

vector<double> binx();
vector<double> biny();
vector<double> binz();

vector<double> binxmuon();
void addweighttotreeJACK(string filename, string decaytree, string species, string name, string newfilename);
vector<double> jackpion();
vector<double> jackkaon();
vector<double> jackproton();
vector<float> jackefficiency(string filename, string cuts, int p, int eta, string species);
void addproductbranches(string filename, string decaytree, string branch1, string branch2, string varname);

double s2d(string str);
string bool_cast(const bool b);
string d2s(double d);
string f2s(float d);
string i2s(int i);
void plotPIDvariation(string filename, string cuts, int p, int eta, string  polarity, string stripping, int toy);
void createPIDvariation(string filename, string cuts, int p, int eta, string  polarity, string stripping, int toy);
//vector<float> numofparticles(string filename, string decaytree);
//vector<float> tkindis(string filename, string decaytree, string misidPIDcalib, string misidcuts, string idPIDcalib, string idcuts);

vector<float> crossmisid(string filename, string cuts, int p, int eta, string polarity, string stripping);
float avcrossmisid(string filename, string cuts, int p, int eta);
vector<float> efficiency(string filename, string cuts, int p, int eta, string polarity, string stripping);
double averageefficiency(string filename, string cuts, int p, int eta);
vector<float> misefficiency(string filename, string cuts, int p, int eta);
//vector<float> binmydata(string filename, string decaytree, string species);
void cutTree(string nametree, string decaytreename, string namecuttree, string cuts);
void addmultiplicationofbranches(string filename, string decaytree, string branch1, string branch2, string varname);

string cleanNameString(string str);
void plotheatmapPID(string filename, string decaytree, string weightfile, string wfilecuts, string name, string polarity, string stripping);

void addweight(string filename, string decaytree, string variable, string weight, string varname);
//void addrealweight(string filename, string decaytree, string variable, string weight, string varname, string species);
void addratiofbranches(string filename, string decaytree, string branch1, string branch2, string varname);
void addnormalbranchweight(string filename, string decaytree, string branch1, string varname);
void addweighttotree(string filename, string decaytree, string weightfile, string wfilecuts, string name, string newfilename);
void addweighttotreespecial(string filename, string decaytree, vector<float> weights, string name);

float totmisidproton(string filename, string species, string misidPIDcalib, string misidcuts, string idPIDcalib, string idcuts, string tags, string stripping, string polarity);
//void addweighttotree(string filename, string decaytree, string weightfiledown, string weightfileup, string wfilecuts, string name, string newfilename);

vector<float> binmydatacorrm(string filename, string decaytree, string species, Double_t lowcorrm, Double_t highcorrm);
vector<float> newmyfavkin(vector<float> numberofparticles , vector<float> ideff, string species);
vector<float> myfavkin(vector<float> numberofparticles , vector<float> ideff, string species);


vector<float> newkindistrpion(vector<float> pionbinmydata , vector<float> myktopimisid, vector<float> truekinematicaldistributionkaon, vector<float> pionideff, vector<float> misidpiontomuon, int number, string species, string misidcuts, string polarity, string stripping);
vector<float> newkindistrkaon(vector<float> kaonbinmydata , vector<float> mypitokmisid, vector<float> truekinematicaldistributionpion, vector<float> kaonideff, vector<float> misidkaontomuon, int number, string species, string misidcuts, string polarity, string stripping);
float numofkaonafteriteration(vector<float> kaonbinmydata , vector<float> mypitokmisid, vector<float> truekinematicaldistributionpion, vector<float> kaonideff, vector<float> misidkaontomuon);
float numofparafteriteration(int number,vector<float> pionbinmydata , vector<float> myktopimisid, vector<float> truekinematicaldistributionkaon, vector<float> pionideff, vector<float> misidpiontomuon, vector<float> kaonbinmydata , vector<float> mypitokmisid, vector<float> truekinematicaldistributionpion, vector<float> kaonideff, vector<float> misidkaontomuon);
float totmisidnobinofcorrm(string filename, string filename2, string species, string species2 ,string misidPIDcalib, string misidcuts, string misidPIDcalib2, string misidcuts2, string tags);
float totmisidnobinofcorrmimp(string filename, string filename2, string species, string species2 ,string misidPIDcalib, string misidcuts, string misidPIDcalib2, string misidcuts2, string idPIDcalib, string idcuts, string idPIDcalib2, string idcuts2, string ktopimisidfilename, string ktopimisidcuts, string pitokmisidfilename, string pitokmisidcuts, string tags, string stripping, string polarity);
//float totmisidinbinofcorrm(Double_t lowboundary, Double_t highboundary) ;
double calaveffofasamplemu3(string filename, string decaytree, string weightfile, string wfilecuts, string name, string newfilename);
double calaveffofasamplemu2(string filename, string decaytree, string weightfile, string wfilecuts, string name, string newfilename);
double calaveffofasamplemu1(string filename, string decaytree, string weightfile, string wfilecuts, string name, string newfilename);
