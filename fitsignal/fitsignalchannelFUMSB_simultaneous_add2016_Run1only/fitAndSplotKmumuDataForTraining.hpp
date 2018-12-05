#ifndef FITANDSPLOTKMUMUDATAFORTRAINING 
#define FITANDSPLOTKMUMUDATAFORTRAINING 

#include "usefulFunctions.hpp"
//#include "RooCBShape.h"
//#include "doubleCrystalBall.hpp"
#include<string>

using namespace RooFit;
//using namespace RooStats;
using namespace std;

class FitAndSplotKmumuDataForTraining
{ 
   public:

   FitAndSplotKmumuDataForTraining()
   :workspaceFileName("/home/hep/th1011/Documents/Kee/fits/workspaces/FitAndSplotKmumuDataForTrainingWorkspace.root"), plotdir("/home/hep/th1011/public_html/Kee_fits/fitKmumuDataForTraining/"),
      tupledir("/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/"), tuplename("B2XMuMu_Line_Strip21_sel.root"), treename("DecayTree"), B_plus_M_max(5700), B_plus_M_min(5180)
   {}


   string workspaceFileName;
   string plotdir;
   string tupledir;
   string tuplename;
   string treename;

   double B_plus_M_max;
   double B_plus_M_min;
   


   void makeSWeightedTree(string extracut = "", string label = "_sWeighted");
   void prepareWorkspace();
   void fitKmumuData(bool binnedFit = false);
   void plot();


};

#endif
