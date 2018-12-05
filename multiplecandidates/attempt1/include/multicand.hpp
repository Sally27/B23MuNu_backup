#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TCut.h"
//#include "sel.h"
#include "TCanvas.h"
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class multicand {
const char* name;
TTree* tree;
TString diffParticle;
public:
multicand();
multicand(const char*,TTree*,TString = "");
~multicand();
void addDiffParticle(TString);
void weight(TTree*);
TTree* reweight();
TTree* random(ofstream &out,string nameoffile);
TTree* random_long(std::vector<TString>);
TTree* randomFast(std::vector<bool*>);
};

