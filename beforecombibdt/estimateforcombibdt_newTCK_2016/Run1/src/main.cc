#include "lumi.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include "TTree.h"
#include "math.h"
#include <sstream>
#include "TLatex.h"
#include "TCanvas.h"
#include <string>
#include<iostream>
#include<fstream>
#include<vector>
#include "functions.hpp"


using namespace std;

int main(){

cutTree("/vols/lhcb/ss4314/beforecombibdt/Run1/fulldatarun1.root", "DecayTree", "fulldatarun1.root", "Bplus_Corrected_Mass > 4000 && Bplus_Corrected_Mass < 7000");
return(0);

}
