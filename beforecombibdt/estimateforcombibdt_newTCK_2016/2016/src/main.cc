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

int main(int argc, char *argv[]){

string sample=argv[1];
cutTree(sample.c_str(), "DecayTree", "fulldata2016.root", "Bplus_Corrected_Mass > 4000 && Bplus_Corrected_Mass < 7000");
return(0);

}
