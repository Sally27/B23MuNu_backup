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
#include<map>

using namespace std;

int main(int argc, char *argv[]){


        string tuple="../mergedData/FullData.root";

        string cut2 = "(mu1_MuMuMu_MCORRFULLERR/Bplus_Corrected_Mass)<0.0225";
        string cut3 = "(mu1_MuMuMu_MCORRFULLERR/Bplus_Corrected_Mass)>0.0225";
        string cutinfile = "LowFCME";

        cutTree(tuple, "DecayTree", "../mergedData/FullData_LowFCME.root", cut2);
        cutTree(tuple, "DecayTree", "../mergedData/FullData_HighFCME.root", cut3);
}
