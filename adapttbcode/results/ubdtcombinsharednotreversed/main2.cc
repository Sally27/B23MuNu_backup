#include "usefulFunctions.h"
#include "Lenin4.h"
#include <iostream>
#include <string>
#include "KFolder.hpp"

using namespace std;

int main()
{

//   string nametree = "/vols/lhcbdisk05/ss4314/BDTtrainings/uBDTqsqcutnSharedMisIDSmallDataSamplevsMCSig/tmva/TMVA_fold_0.root";
//   string decaytreename = "TestTree";
//   string namecuttree = "testsig.root";
//   string cuts = "classID == 0";      
//   cutTree(nametree, decaytreename, namecuttree, cuts);

//   string nametree2 = "/vols/lhcbdisk05/ss4314/BDTtrainings/uBDTqsqcutnSharedMisIDSmallDataSamplevsMCSig/tmva/TMVA_fold_0.root";
//   string decaytreename2 = "TestTree";
//  string namecuttree2 = "testbkg.root";
//   string cuts2 = "classID == 1";
//   cutTree(nametree2, decaytreename2, namecuttree2, cuts2);



   //break;



   KFolder ke;

   ke.setNFolds(10);
   ke.setOutFile("/vols/lhcbdisk05/ss4314/BDTtrainings/uBDTqsqcutnSharedCombinSamplevsMCSig/tmva/");
   ke.addTrainingOpt("trialthing", "UBDT_Num=100:!H:!V:NTrees=200:nEventsMin=100:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=1.0:PruneMethod=NoPruning:SeparationType=GiniIndex:nCuts=200:uBoostFlag=1");

   string pathname="/vols/lhcbdisk05/ss4314/BDTtrainings/uBDTqsqcutnSharedCombinSamplevsMCSig/tmva/";
   string outputFileName="overtrainingRev.eps";
   string outputfilename="roccurvesRev.eps";
   string bdtvar="RevBDT";
   string weight="";
   string weightBranchSig="";
   string weightBranchBkg="";
   string fsigname="testsigRev.root";
   string fbkgname="testbkgRev.root";
   string extracut="";
   char* strarray[] = {"bdtvar2"};
   double minvar = -1.0;
   double maxvar = 0.0;

   vector<string> bdtvars(strarray,strarray+1);
   
   plotOverTraining(ke, outputFileName, bdtvar, weight, pathname, minvar, maxvar, fsigname, fbkgname);


   plotRocCurves(fsigname, fbkgname, bdtvars, outputfilename, extracut, weightBranchSig, weightBranchBkg);


//  getOneRocCurve(fsigname, fbkgname, bdtvar, extracut, sigEff, bkgRej, n, weightBranchSig, weightBranchBkg);
//   getOneRocCurve(fsigname, fbkgname, bdtvar, extracut, sigEff[], bkgRej[], n, weightBranchSig, weightBranchBkg);

   return 0;

}
