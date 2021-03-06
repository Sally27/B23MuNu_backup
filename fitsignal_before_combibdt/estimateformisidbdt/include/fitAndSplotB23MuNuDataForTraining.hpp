#ifndef FITANDSPLOTJPSIKDATAFORTRAINING 
#define FITANDSPLOTJPSIKDATAFORTRAINING 

#include "usefulFunctions.hpp"
//#include "RooCBShape.h"
//#include "doubleCrystalBall.hpp"
#include<string>
#include<vector>

using namespace RooFit;
//using namespace RooStats;
using namespace std;

class FitAndSplotB23MuNuDataForTraining
{ 
   public:

   FitAndSplotB23MuNuDataForTraining()
   :workspaceFileName("/vols/lhcb/ss4314/adapttbcode/estimateformisidbdt/workspace/FitB23MuNuworkspace.root"),
    plotdir("/vols/lhcb/ss4314/adapttbcode/estimateformisidbdt/workspace_plots/"), 
    workspacedir("/vols/lhcb/ss4314/adapttbcode/estimateformisidbdt/workspace_preparation/"),
    workspaceFileNameSim("FitB23MuNuworkspace"),
    fitdir("/vols/lhcb/ss4314/adapttbcode/estimateformisidbdt/workspace_fit/"),
    clsdir("/vols/lhcb/ss4314/adapttbcode/estimateformisidbdt/workspace_fitcls/"),
    tupledir("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_add2015/bin"), 
    misiddir("/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2015/finaltuplesRun1"),
    tuplename("fulldatarun1"), 
    tuplenamelow("finaldata_LowFCME.root"),
    treename("DecayTree"),
    datadir("/vols/lhcb/ss4314/beforemisidbdt/Run1/bin"),
    Bplus_Corrected_Mass_min(4000),
    Bplus_Corrected_Mass_max(10000),
    signalfilename("B23MuNuMC2012NNmumore03Strip21"),
    partrecodir("/vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsCombiFUMSB_add2016_newPID/bin"),
    partrecofilename("B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic"),
    kaonfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM"),
    protonfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM"),
    pionfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM"),
    typelow("LowFCME"),
    typehigh("HighFCME"),
    sigdir("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_NOTsimultaneous_add2015/bin/")
    {}
    

   string workspaceFileName;
   string partrecodir;
   string plotdir;
   string fitdir;
   string workspacedir;
   string datadir;
   string clsdir;
   string workspaceFileNameSim;
   string tuplename;
   string sigdir;
   string misiddir;
   string tupledir;
   string tuplenamelow;
   string tuplenamehigh;
   string treename;
   

   string signalfilename;
   string partrecofilename;
   string kaonfilename;
   string protonfilename;
   string pionfilename;

   string typelow;
   string typehigh;

   double Bplus_Corrected_Mass_max;
   double Bplus_Corrected_Mass_min;
   
//original functions template//

   void fitJpsiKData4(bool binnedFit);
   void makeSWeightedTree(string extracut = "", string label = "_sWeighted");
   void plot();

//Sally's addition//

   void plotprettysim(string type);


   vector<double> fitsignalcomponent(string weightname, string typelow);
   vector<double> fitpartrecocomponent(string typelow);
   vector<double> fitmisidcomponent(string type);

   vector<double> fitmisidcomponentall(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type);

   double fitmisidone(string type, string dir ,string filename, string weight, string species);
  
   void prepareWorkspaceForSimultaneousFit(string type);

   void calculateFOM(string type);

   void simfitseparateandsavesig();

};

#endif
