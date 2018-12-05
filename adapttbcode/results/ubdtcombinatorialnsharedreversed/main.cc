#include "usefulFunctions.h"
//#include "Lenin.h"
#include <iostream>
#include <string>
#include "KFolder.hpp"
//#include "usefulFunctions.h"
#include "Lenin4.h"
//#include <iostream>
//#include <string>
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

addBranchInTreeD(fileSig, nameNewBranch, formulaNewBranch);
addBranchInTreeD(fileBkg, nameNewBranch, formulaNewBranch);

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

//string filename="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/uBDTqsqcutnSharedMisIDSmallDataSamplevsMCSig/B23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut.root";
string var1name="Bplus_Corrected_Mass";
string var2name="RevBDT";
string cut="";
bool draw="true";
//string dirname="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/uBDTqsqcutnSharedMisIDSmallDataSamplevsMCSig/B23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut.root";
//string plotname="goodname";
int nsteps=300;
string plotname="CombinatorialBKG";
getCorrelationCoefficient(fileBkgnew, var1name, var2name, cuts2, draw, fileBkgnew, plotname, mincut2, maxcut2, nsteps);

string plotname2="MCsig";
getCorrelationCoefficient(fileSignew, var1name, var2name, cuts2, draw, fileSignew, plotname2, mincut2, maxcut2, nsteps);

double minmine=0.0;
double maxmine=10000.0;
double numofbdtsteps=100;
plotSigEffvsCorrMass(fileSignew, var2name, var1name, minmine, maxmine, mincut2, maxcut2, numofbdtsteps, "SigSampleeff.pdf", extracuts);

plotSigEffvsCorrMass(fileBkgnew, var2name, var1name, minmine, maxmine, mincut2, maxcut2, numofbdtsteps, "BkgSampleeff.pdf", extracuts);


KFolder ke;
ke.setNFolds(10); 
ke.setOutFile("/vols/lhcbdisk05/ss4314/BDTtrainings/uBDTqsqcutnSharedCombinSamplevsMCSig/tmva/");
//ke.addTrainingOpt("trialthing", "UBDT_Num=100:!H:!V:NTrees=200:nEventsMin=100:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=1.0:PruneMethod=NoPruning:SeparationType=GiniIndex:nCuts=200:uBoostFlag=1");
    
string pathname="/vols/lhcbdisk05/ss4314/BDTtrainings/uBDTqsqcutnSharedCombinSamplevsMCSig/tmva/";
string outputFileName="overtraining.eps";
string outputfilename="roccurves.eps";
//string bdtvar="trialthing";
string weight="";
string fsigname="testsig.root";
string fbkgname="testbkg.root";
string extracut="";
char* strarray[] = {"bdtvar2"};

vector<string> bdtvars(strarray,strarray+1);
plotOverTraining(ke, outputFileName, bdtvar, weight, pathname, minvar, maxvar, fsigname, fbkgname);
plotRocCurves(fsigname, fbkgname, bdtvars, outputfilename, extracuts, weightBranchSig, weightBranchBkg);


for(int i(0); i<10; i++){
string nameNewBranch=("RevBDT_fold_"+i2s(i)).c_str();
string formulaNewBranch=(("-1*trialthing_fold_"+i2s(i)).c_str());
cout<< "I am here"<<endl;
addBranchInTreeTestTree(("/vols/lhcbdisk05/ss4314/BDTtrainings/uBDTqsqcutnSharedCombinSamplevsMCSig/tmva/TMVA_fold_"+i2s(i)+".root").c_str(), nameNewBranch, formulaNewBranch);
addBranchInTreeTrainTree(("/vols/lhcbdisk05/ss4314/BDTtrainings/uBDTqsqcutnSharedCombinSamplevsMCSig/tmva/TMVA_fold_"+i2s(i)+".root").c_str(), nameNewBranch, formulaNewBranch);
}

KFolder kt;
kt.setNFolds(10);
kt.setOutFile("/vols/lhcbdisk05/ss4314/BDTtrainings/uBDTqsqcutnSharedCombinSamplevsMCSig/tmva/");
//kt.addTrainingOpt("trialthing", "UBDT_Num=100:!H:!V:NTrees=200:nEventsMin=100:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=1.0:PruneMethod=NoPruning:SeparationType=GiniIndex:nCuts=200:uBoostFlag=1");

string pathnameRev="/vols/lhcbdisk05/ss4314/BDTtrainings/uBDTqsqcutnSharedCombinSamplevsMCSig/tmva/";
string outputFileNameRev="overtrainingRev.eps";
string outputfilenameRev="roccurvesRev.eps";
string bdtvarRev="RevBDT";
//string weight="";
string fsignameRev="testsigRev.root";
string fbkgnameRev="testbkgRev.root";
//string extracut="";
char* strarray2[] = {"bdtvar2"};
//
vector<string> bdtvarsRev(strarray2,strarray2+1);
plotOverTraining(kt, outputFileNameRev, bdtvar, weight, pathnameRev, mincut2 , maxcut2, fsignameRev, fbkgnameRev);
plotRocCurves(fbkgnameRev, fsignameRev, bdtvars, outputfilenameRev, extracuts, weightBranchSig, weightBranchBkg);











//getCorrelationCoefficient(fileBkgnew, var1name, var2name, cuts2, draw, fileBkgnew, plotname);
//  getOneRocCurve(fsigname, fbkgname, bdtvar, extracut, sigEff, bkgRej, n, weightBranchSig, weightBranchBkg);
//   getOneRocCurve(fsigname, fbkgname, bdtvar, extracut, sigEff[], bkgRej[], n, weightBranchSig, weightBranchBkg);   return 0;
}
