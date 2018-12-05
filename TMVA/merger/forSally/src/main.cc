#include "usefulFunctions.h"
#include "Lenin.h"
#include <iostream>
#include <string>
#include "KFolder.hpp"

using namespace std;

int main()
{
      
   KFolder ke;

   ke.setNFolds(10);
   ke.setOutFile("/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/diffvs/uBDTandKfoldrun-10/tmva/");
   ke.addTrainingOpt("trialthing", "UBDT_Num=100:!H:!V:NTrees=200:nEventsMin=100:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=1.0:PruneMethod=NoPruning:SeparationType=GiniIndex:nCuts=200:uBoostFlag=1");

   string outputFileName="overtraining.eps";
   string outputfilename="roccurves.eps";
   string bdtvar="trialthing";
   string weight="weight";
   string weightBranchSig="weight";
   string weightBranchBkg="weight";
   string fsigname="testsig.root";
   string fbkgname="testbkg.root";
   string extracut="";
   char* strarray[] = {"bdtvar2"};

   vector<string> bdtvars(strarray,strarray+1);
   
   plotOverTraining(ke, outputFileName, bdtvar, weight);


   plotRocCurves(fsigname, fbkgname, bdtvars, outputfilename, extracut, weightBranchSig, weightBranchBkg);


//  getOneRocCurve(fsigname, fbkgname, bdtvar, extracut, sigEff, bkgRej, n, weightBranchSig, weightBranchBkg);
//   getOneRocCurve(fsigname, fbkgname, bdtvar, extracut, sigEff[], bkgRej[], n, weightBranchSig, weightBranchBkg);

   return 0;

}
