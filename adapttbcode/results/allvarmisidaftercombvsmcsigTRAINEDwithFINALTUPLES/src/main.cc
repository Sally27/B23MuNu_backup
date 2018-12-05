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

string fileBkg="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/allvarcombvsmcsigMISIDafterCOMB/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_60TreesComb.root";

string fileSig="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/allvarcombvsmcsigMISIDafterCOMB/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb.root";

//------------Define the bdt var, range and number of steps to obtain FOM and PUNZI fom---//
double wSig = 1.0;
double wBkg = 1.0;
string bdtvar = "allvarcombvsmcsigMISIDafterCOMBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection";
double mincut = -1.0;
double maxcut = 1.0;
int nstep = 300;
string nameplot = "FOM.pdf";
string cuts="";
string weightBranchSig="";
string weightBranchBkg="";


double FOM;
double FOMSCALED;
double FOMPUNZI;
double FOMPUNZISCALED;
double maxsigeff;

double nsigexp = 30;
double nbkgexp = 7757;
//----------Find the Figure of Merit Normal/Punzi----------------------//

FOM = optimiseBdt(fileSig, fileBkg, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot, cuts, weightBranchSig, weightBranchBkg);
cout << "Optimal cut at: "<<FOM<<endl;

FOMSCALED = optimiseBdtScaled(fileSig, fileBkg, wSig, wBkg, bdtvar, mincut, maxcut, nstep,  nsigexp, nbkgexp, nameplot);
      

FOMPUNZI = optimiseBdtPunzi(fileSig, fileBkg, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot);// cuts, punzi, weightBranchSig, weightBranchBkg);
cout << "Optimal Punzi cut at: "<<FOMPUNZI<<endl;

FOMPUNZISCALED = optimiseBdtPunziScaled(fileSig, fileBkg, nsigexp, nbkgexp, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot);

maxsigeff=plotSigEffBdtPunziScaled(fileSig, fileBkg, nsigexp, nbkgexp, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot);
      
//return(1);
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
string var2name="allvarcombvsmcsigMISIDafterCOMBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection";
bool draw="true";
string plotname="CombBDT";
getCorrelationCoefficient(fileBkg, var1name, var2name, cuts, draw, fileBkg, plotname, mincut, maxcut, nstep);

string plotname2="MCsig";
getCorrelationCoefficient(fileSig, var1name, var2name, cuts, draw, fileSig, plotname2, mincut, maxcut, nstep);


//------------------Plot Corrected mass as fn signal efficiency and background efficiency---------//////


double minmine=0.0;
double maxmine=10000.0;
double numofbdtsteps=100;
plotSigEffvsCorrMass(fileSig, var2name, var1name, minmine, maxmine, mincut, maxcut, numofbdtsteps, "SigMCSampleeff.pdf", extracuts);
plotSigEffvsCorrMass(fileBkg, var2name, var1name, minmine, maxmine, mincut, maxcut, numofbdtsteps, "BkgCombSampleeff.pdf", extracuts);



//-----------------Plots Overtraining , Roc cuves----------------------////

KFolder ke;
ke.setNFolds(10); 
ke.setOutFile("/vols/lhcbdisk05/ss4314/BDTtrainings/allvarcombvsmcsigMISIDafterCOMB/tmva/");
string pathname="/vols/lhcbdisk05/ss4314/BDTtrainings/allvarcombvsmcsigMISIDafterCOMB/tmva/";
string bdtvarintuples="allvarcombvsmcsigMISIDafterCOMB";
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
plotRocCurves(fsigname, fbkgname, bdtvars, outputfilename, extracuts, fa, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);
plotRocCurvesPunzi(fsigname, fbkgname, bdtvars, outputfilename, extracuts, fa, nsigexp, nbkgexp, namemything1, mincut, maxcut);//, punzi, weightBranchSig, weightBranchBkg);

bool tr=true;
plotRocCurves(fsigname, fbkgname, bdtvars, outputfilename, extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);
plotRocCurvesPunzi(fsigname, fbkgname, bdtvars, outputfilename, extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut);

//--------------------On MIS ID--------------------------------//

//string str="mamama";
//string nametree="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/60Treesfinaltuplesafter60treescombinatorial30percsig/B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut.root";
//string decaytreename="DecayTree";
//string namecuttree="B23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_BDTPunziOPT.root";
//string mycut="Bplus_Corrected_Mass > 6000";
//string mycuts="CombinatorialNormalBDTfinal400TreesandPNTrees400_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection > 0.578";
//cutTree(nametree, decaytreename, namecuttree, mycuts);


}
