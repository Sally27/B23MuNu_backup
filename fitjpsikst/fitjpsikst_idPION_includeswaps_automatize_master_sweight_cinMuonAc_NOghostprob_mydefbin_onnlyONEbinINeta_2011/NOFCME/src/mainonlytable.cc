#include "fitAndSplotJpsiKDataForTraining.hpp"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "TCanvas.h"
#include "TTree.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooMinuit.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooStats/SPlot.h"
#include "TTreeFormula.h"
#include<fstream>
#include<iostream>
#include<string>

using namespace std;

int main(){
cout<<"I am bad!"<<endl;
//RUN with hypathia


//-----------CREATE BINNING SCHEME--------//

vector<double> binningx = binx();
vector<double> binningy = biny();
vector<double> binningz = binz();




string pidcutafter = "K_isMuon==1.0";

FitAndSplotJpsiKDataForTraining resultrun;
resultrun.readFilled2DHist(pidcutafter.c_str());
resultrun.divideFilled2DHist("",binningx,binningy,pidcutafter.c_str());
resultrun.readEfficiency2DHist(pidcutafter.c_str());


}
