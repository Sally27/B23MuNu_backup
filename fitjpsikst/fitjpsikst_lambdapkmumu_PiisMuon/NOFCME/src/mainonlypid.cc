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



////-----------------Just fit all of JpsiKst-----------//
//FitAndSplotJpsiKDataForTraining run;  
//run.prepareWorkspaceSigMC();  //prepare workspace for mc
//run.sigfitnoweight("","");   //fit mc
//run.prepareWorkspaceData();  //prepare workspace for data
//run.fitJpsiKstData(false, "",""); //fit the data
//run.plotprettyjpsikst(""); //plot nicely
////
////
////
////
//
////-----------------Just fit all of JpsiKst for PID purposes-----------//
//
//////-------------Create PID table--------------------////
ofstream out;
out.open("../PIDResult/TableBefore.txt");
out<<"\\begin{table}[h]"<<endl;
out<<"\\begin{center}"<<endl;
out<<"\\begin{tabular}{| l | l | l | l | l |}"<<endl;
out<<"\\hline"<<endl;
out<<"P low & P high & ETA low  & ETA high & nSig  \\\\ "<<endl;


ofstream out2;
out2.open("../PIDResult/TableAfter.txt");
out2<<"\\begin{table}[h]"<<endl;
out2<<"\\begin{center}"<<endl;
out2<<"\\begin{tabular}{| l | l | l | l | l |}"<<endl;
out2<<"\\hline"<<endl;
out2<<"P low & P high & ETA low  & ETA high & nSig \\\\ "<<endl;
//
//
//FitAndSplotJpsiKDataForTraining resultPID;
//resultPID.prepare2Dhist("",binningx,binningy);
//
//////----------For a given binning scheme fit jspsikst no PID------------------------//
//for(int i(0); i<18 ;i++) //number of bins wanted to be iterated above in momentum
//{
//        for(int j(0); j<4 ;j++){ //number of bins wanted to be iterated above in eta
//
//        string pbin = "Pi_P>"+d2s(binningx.at(i))+" && Pi_P<"+d2s(binningx.at(i+1));
//        string etabin = "Pi_ETA>"+d2s(binningy.at(j))+" && Pi_ETA<"+d2s(binningy.at(j+1));
//        string pidcut = "Pi_PIDK<0";
//        string pidcutafter = "Pi_PIDK<-2";
//        string kinbinstring = "Pi_P_"+d2s(binningx.at(i))+"_Pi_P_"+d2s(binningx.at(i+1))+"_Pi_ETA_"+d2s(binningy.at(j))+"_Pi_ETA_"+d2s(binningy.at(j+1));
//
//	FitAndSplotJpsiKDataForTraining runPID;
//	runPID.prepareWorkspaceSigMC(pbin.c_str(), etabin.c_str(),pidcut.c_str()); //prepare ws for mc
//	runPID.sigfitnoweight("",""); //fit mc ws
//	runPID.prepareWorkspaceData(pbin.c_str(), etabin.c_str(),pidcut.c_str()); //prepare ws for data
////	runPID.fitJpsiKstData(false, "",("Pi_P_"+d2s(binningx.at(i))+"_Pi_P_"+d2s(binningx.at(i+1))+"_Pi_ETA_"+d2s(binningy.at(j))+"_Pi_ETA_"+d2s(binningy.at(j+1))).c_str()); //fitdata ws
//        runPID.fitJpsiKstDataAndMakePIDbefore(false, "",kinbinstring.c_str(), i, j, pidcut.c_str(),out); //fitdata ws and fill pidtable
//        runPID.plotprettyjpsikst("",kinbinstring.c_str(),pidcut.c_str()); //plot nicely the fit
//
//
//	FitAndSplotJpsiKDataForTraining runPIDafter;
//          	
//	runPIDafter.prepareWorkspaceSigMC(pbin.c_str(), etabin.c_str(),pidcutafter.c_str()); //prepare ws for mc
//	runPIDafter.sigfitnoweight("",""); //fit mc ws
//	runPIDafter.prepareWorkspaceData(pbin.c_str(), etabin.c_str(),pidcutafter.c_str()); //prepare ws for data
////	runPID.fitJpsiKstData(false, "",("Pi_P_"+d2s(binningx.at(i))+"_Pi_P_"+d2s(binningx.at(i+1))+"_Pi_ETA_"+d2s(binningy.at(j))+"_Pi_ETA_"+d2s(binningy.at(j+1))).c_str()); //fitdata ws
//        runPIDafter.fitJpsiKstDataAndMakePIDafter(false, "",kinbinstring.c_str(), i, j, pidcutafter.c_str(),out2); //fitdata ws and fill pidtable
//        runPID.plotprettyjpsikst("",kinbinstring.c_str(),pidcutafter.c_str());
//        }
//}
//
//

FitAndSplotJpsiKDataForTraining resultrun;
//resultPID.readFilled2DHist();
//resultPID.divideFilled2DHist("",binningx,binningy);
resultrun.readEfficiency2DHist();


//plotMergedFits(binningx, binningy,"Pi_PIDK<0","Before","/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_nolambdapkmumu/NOFCME/workspace");
//plotMergedFits(binningx, binningy,"Pi_PIDK<-2","After","/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_nolambdapkmumu/NOFCME/workspace");

out<<"\\hline"<<endl;
out<<"\\end{tabular}"<<endl;
out<<"\\end{center}"<<endl;
out<<"\\caption{STATISTICS.txt}"<<endl;
out<<"\\end{table}"<<endl;


out2<<"\\hline"<<endl;
out2<<"\\end{tabular}"<<endl;
out2<<"\\end{center}"<<endl;
out2<<"\\caption{STATISTICS.txt}"<<endl;
out2<<"\\end{table}"<<endl;







//runPID.plotprettyjpsikst("");
//run.sigfitnoweight("","");
//run.prepareWorkspaceData();
//run.prepareWorkspaceData("Pi_P>50000", "Pi_ETA>2.6","Pi_PIDK<0");
//run.fitJpsiKstData(false, "");
//run.plotprettyjpsikst("");

//FitAndSplotJpsiKDataForTraining run2;
//run2.sigfithypathia("mcweight","","JpsiKMC2015NNmumore03","2015");
//run2.prepareWorkspace("JpsiKdata_2015.root");
//run2.fitJpsiKDataHypathia3(false,"","2015");
//run2.plotprettyhypathia3("2015");


//FitAndSplotJpsiKDataForTraining run3;
//run3.sigfithypathia("mcweight","","JpsiKMC2016NNmumore03","2016");
//run3.prepareWorkspace("JpsiKdata_2016.root");
//run3.fitJpsiKDataHypathia3(false,"","2016");
//run3.plotprettyhypathia3("2016");


//RUN with 2 double sided crystalball//
//FitAndSplotJpsiKDataForTraining run;
//run.prepareWorkspace();
//run.fitJpsiKData4(false);
//run.plot();
//run.plotpretty();
}
