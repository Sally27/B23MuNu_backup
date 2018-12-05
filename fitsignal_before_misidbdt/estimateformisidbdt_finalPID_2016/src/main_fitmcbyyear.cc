#include "fitAndSplotB23MuNuDataForTraining.hpp"
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


using namespace std;

int main(int argc,char* argv[]){


string PIDcut_Run1=argv[1];
string PIDcut_Run2=argv[2];
string year="2012";


if (year=="2012")
{

	cout<<"I am bad!"<<endl;
	FitAndSplotB23MuNuDataForTraining run;
	run.fitsignalcomponent_byyear("PIDweight","", "", "",("2012"+PIDcut_Run1+"Strip21").c_str());
	run.fitsignalcomponent_byyear("PIDweight","", "", "",("2016"+PIDcut_Run2+"Turbo16").c_str());


}

return(0);
}
