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

using namespace std;

string d2s(double d);
void cutTree(string nametree, string decaytreename, string namecuttree, string cuts);
