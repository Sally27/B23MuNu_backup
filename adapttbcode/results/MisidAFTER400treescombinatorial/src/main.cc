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


//-----------Define Background and Signal Samples---------//

string fileBkg="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/MisIDvsMCSigafter400TreesCombinatorialApril2016/B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_400andPPUNZIoptBDT.root";

string fileSig="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/MisIDvsMCSigafter400TreesCombinatorialApril2016/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_400andPPUNZIoptBDT.root";

//------------Define the bdt var, range and number of steps to obtain FOM and PUNZI fom---//
double wSig = 1.0;
double wBkg = 1.0;
string bdtvar = "MisIDvsMCSigafter400TreesCombinatorialNTrees400_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection";
double mincut = -1.0;
double maxcut = 1.0;
int nstep = 300;
string nameplot = "FOM.pdf";
string cuts="";
string weightBranchSig="";
string weightBranchBkg="";


double FOM;
double FOMPUNZI;

//----------Find the Figure of Merit Normal/Punzi----------------------//

FOM = optimiseBdt(fileSig, fileBkg, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot, cuts, weightBranchSig, weightBranchBkg);
cout << "Optimal cut at: "<<FOM<<endl;

FOMPUNZI = optimiseBdtPunzi(fileSig, fileBkg, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot);// cuts, punzi, weightBranchSig, weightBranchBkg);
cout << "Optimal Punzi cut at: "<<FOMPUNZI<<endl;


//-----------Plot cut applied as a function of Variable-------------//
string extracuts= "";
string cutapplied="Bplus_Corrected_Mass>6000";
string nameplot2 = "CuteffvsVariableSig";
string nameplot3 = "CuteffvsVariableBkg";
plotCutEffVsVar(fileSig, cutapplied, bdtvar, mincut, maxcut, nstep, nameplot2, extracuts);
plotCutEffVsVar(fileBkg, cutapplied, bdtvar, mincut, maxcut, nstep, nameplot3, extracuts);


string weightBranchSig2="";
string weightBranchBkg2="";

//------------Plot the Profile X Plot-------------------------------//


string var1name="Bplus_Corrected_Mass";
string var2name="MisIDvsMCSigafter400TreesCombinatorialNTrees400_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection";
bool draw="true";
string plotname="MisidafterCombinatorialBKG";
getCorrelationCoefficient(fileBkg, var1name, var2name, cuts, draw, fileBkg, plotname, mincut, maxcut, nstep);

string plotname2="MCsig";
getCorrelationCoefficient(fileSig, var1name, var2name, cuts, draw, fileSig, plotname2, mincut, maxcut, nstep);


//------------------Plot Corrected mass as fn signal efficiency and background efficiency---------//////


double minmine=0.0;
double maxmine=10000.0;
double numofbdtsteps=100;
plotSigEffvsCorrMass(fileSig, var2name, var1name, minmine, maxmine, mincut, maxcut, numofbdtsteps, "SigMCSampleeff.pdf", extracuts);
plotSigEffvsCorrMass(fileBkg, var2name, var1name, minmine, maxmine, mincut, maxcut, numofbdtsteps, "BkgMisIDSampleeff.pdf", extracuts);



//-----------------Plots Overtraining , Roc cuves----------------------////

KFolder ke;
ke.setNFolds(7); 
ke.setOutFile("/vols/lhcbdisk05/ss4314/BDTtrainings/MisIDvsMCSigafter400TreesCombinatorial/tmva/");
string pathname="/vols/lhcbdisk05/ss4314/BDTtrainings/MisIDvsMCSigafter400TreesCombinatorial/tmva/";
string bdtvarintuples="MisIDvsMCSigafter400TreesCombinatorial";
string outputFileName="overtraining.pdf";
string outputfilename="roccurves.pdf";
bool fa=false;
string weight="";
string fsigname="testsig.root";
string fbkgname="testbkg.root";
string extracut="";
char* strarray[] = {"bdtvar2"};
string namemything1 = "Regular";
vector<string> bdtvars(strarray,strarray+1);

plotOverTraining(ke, outputFileName, bdtvarintuples, bdtvar, weight, pathname, mincut, maxcut, fsigname, fbkgname);
plotRocCurves(fsigname, fbkgname, bdtvars, outputfilename, extracuts, fa, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);
plotRocCurvesPunzi(fsigname, fbkgname, bdtvars, outputfilename, extracuts, fa, namemything1, mincut, maxcut);//, punzi, weightBranchSig, weightBranchBkg);

bool tr=true;
plotRocCurves(fsigname, fbkgname, bdtvars, outputfilename, extracuts, tr, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);
plotRocCurvesPunzi(fsigname, fbkgname, bdtvars, outputfilename, extracuts, tr, namemything1, mincut, maxcut);

//--------------------On MIS ID--------------------------------//

//string str="mamama";
//string nametree="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/400treesandPnormalBDTCombvsMCMARCH2016withJpsi/B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut.root";
//string decaytreename="DecayTree";
//string namecuttree="B23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_BDTPunziOPT.root";
//string mycut="Bplus_Corrected_Mass > 6000";
//string mycuts="CombinatorialNormalBDTfinal400TreesandPNTrees400_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection > 0.578";
//cutTree(nametree, decaytreename, namecuttree, mycuts);


}
