#include "usefulFunctions.h"
//#include "Lenin.h"
#include <iostream>
#include <string>
//#include "KFolder.hpp"




using namespace std;

int main()
{
      
string str="mamama";

s2d(str);

string fileSig="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/uBDTqsqcutnSharedCombinSamplevsMCSig/B23MuNuSignal2012and2011data_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_corrm.root";

string fileBkg="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/uBDTqsqcutnSharedCombinSamplevsMCSig/B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut.root";

double wSig = 1.0;
double wBkg = 1.0;
string bdtvar = "trialthing";
double mincut = 0.0;
double maxcut = 1.0;
int nstep = 300;
string nameplot = "TH_FOM.pdf";
string cuts="";
string weightBranchSig="";
string weightBranchBkg="";


double FOM;

FOM = optimiseBdt(fileSig, fileBkg, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot, cuts, weightBranchSig, weightBranchBkg);
cout << "Optimal cut at: "<<FOM<<endl;

string extracuts= "";
double minvar=0.0;
double maxvar=1.0;
string cutapplied="Bplus_Corrected_Mass>6000";
string nameplot2 = "CuteffvsVariableSig.pdf";
string nameplot3 = "CuteffvsVariableBkg.pdf";
plotCutEffVsVar(fileSig, cutapplied, bdtvar, minvar, maxvar, nstep, nameplot2, extracuts);
plotCutEffVsVar(fileBkg, cutapplied, bdtvar, minvar, maxvar, nstep, nameplot3, extracuts);

string nameNewBranch="RevBDT";
string formulaNewBranch="-1*trialthing";

addBranchInTree(fileSig, nameNewBranch, formulaNewBranch);
addBranchInTree(fileBkg, nameNewBranch, formulaNewBranch);

string fileBkg2="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/uBDTqsqcutnSharedCombinSamplevsMCSig/B23MuNuSignal2012and2011data_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_corrm.root";

string fileSig2="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/uBDTqsqcutnSharedCombinSamplevsMCSig/B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut.root";

double wSig2 = 1.0;
double wBkg2 = 1.0;
string bdtvar2 = "RevBDT";
double mincut2 = -1.0;
double maxcut2 = 0.0;
int nstep2 = 300;
string nameplotnew = "TH_FOMReversed.pdf";
string cuts2="";
string weightBranchSig2="";
string weightBranchBkg2="";

double revFOM, revFOM2;

revFOM = optimiseBdt(fileSig2, fileBkg2, wSig2, wBkg2, bdtvar2, mincut2, maxcut2, nstep2, nameplotnew, cuts2, weightBranchSig2, weightBranchBkg2);

cout << "Optimal cut at: "<<revFOM<<endl;

string fileBkgnew="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/uBDTqsqcutnSharedCombinSamplevsMCSig/B23MuNuSignal2012and2011data_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_corrm.root";

string fileSignew="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/uBDTqsqcutnSharedCombinSamplevsMCSig/B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut.root";



revFOM2 = optimiseBdtRev(fileSignew, fileBkgnew, wSig2, wBkg2, bdtvar, mincut, maxcut, nstep2, "try.pdf", cuts2, weightBranchSig2, weightBranchBkg2);

cout << "Optimal cut at: "<<revFOM2<<endl;

string var1name="Bplus_Corrected_Mass";
string var2name="RevBDT";
string cut="";
bool draw="true";
int nstepy = 100;


string plotname="CombinatorialBKG";
getCorrelationCoefficient(fileBkgnew, var1name, var2name, cuts2, draw, fileBkgnew, plotname, mincut2, maxcut2, nstepy);


string plotname2="MCsig";
getCorrelationCoefficient(fileSignew, var1name, var2name, cuts2, draw, fileSignew, plotname2, mincut2, maxcut2, nstepy);



return 0;

}
