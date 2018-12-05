#include "usefulFunctions.h"
#include "Lenin.h"
#include <iostream>
#include <string>
#include "KFolder.hpp"

using namespace std;

int main()
{
      
   KFolder ke;

   ke.setNFolds(1);
   ke.setOutFile("/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/diffvs/uBDTandKfoldrun-10/tmva/");
   ke.addTrainingOpt("trialthing", "UBDT_Num=100:!H:!V:NTrees=200:nEventsMin=100:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=1.0:PruneMethod=NoPruning:SeparationType=GiniIndex:nCuts=200:uBoostFlag=1");

   string outputFileName="output.pdf";
   string outputfilename="roccurves.pdf";
   string bdtvar="trialthing";
   string weight="weight";
   string weightBranchSig="weight";
   string weightBranchBkg="weight";
   string fsigname="testsig.root";
   string fbkgname="testbkg.root";
   string extracut="";
   char* strarray[] = {"bdtvar2"};//,"Bplus_P", "Bplus_PT", "mu1_PT", "mu2_PT", "mu3_PT", "mu1_MINIPCHI2", "mu2_MINIPCHI2", "mu3_MINIPCHI2", "Bplus_TAU", "Bplus_DIRA_OWNPV", "Bplus_ENDVERTEX_CHI2", "Bplus_FD_CHI2"};
   vector<string> bdtvars(strarray,strarray+1);


//   unsigned int n=1;
//   double bkgRej=6.0;
//   double sigEff=9.3;

//   void plotOverTraining;
//   string bdtvar="trialthing";
   
   plotOverTraining(ke, outputFileName, bdtvar, weight);

//bool getOneRocCurve(string fsigname,
//   string fbkgname,
//   string bdtvar,
//   string extracut,
//   double sigEff[],
//   double bkgRej[],
//   unsigned int n,
//   string weightBranchSig,
//   string weightBranchBkg)
//void plotRocCurves(string fsigname,
//      string fbkgname,
//      vector<string> bdtvars,
//      string outputfilename,
//      string extracut,
//      string weightBranchSig,
//      string weightBranchBkg
//      )


   plotRocCurves(fsigname, fbkgname, bdtvars, outputfilename, extracut, weightBranchSig, weightBranchBkg);


//  getOneRocCurve(fsigname, fbkgname, bdtvar, extracut, sigEff, bkgRej, n, weightBranchSig, weightBranchBkg);
//   getOneRocCurve(fsigname, fbkgname, bdtvar, extracut, sigEff[], bkgRej[], n, weightBranchSig, weightBranchBkg);

   return 0;

}
