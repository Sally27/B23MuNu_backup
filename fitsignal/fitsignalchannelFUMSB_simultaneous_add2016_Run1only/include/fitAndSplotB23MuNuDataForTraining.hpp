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
   :workspaceFileName("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_simultaneous_add2016_Run1only/workspace/FitB23MuNuworkspace.root"),
    plotdir("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_simultaneous_add2016_Run1only/workspace_plots/"), 
    workspacedir("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_simultaneous_add2016_Run1only/workspace_preparation/"),
    workspaceFileNameSim("FitB23MuNuworkspace"),
    fitdir("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_simultaneous_add2016_Run1only/workspace_fit/"),
    clsdir("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_simultaneous_add2016_Run1only/workspace_fitcls/"),
    tupledir("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_add2016/bin"), 
    misiddir("/vols/lhcb/ss4314/addPIDweights/FUMSB_simultaneous_add2016/finaltuplesRun1"),
    tuplename("finaldata_Run1"), 
    tuplenamelow("finaldata_LowFCME.root"),
    treename("DecayTree"),
    datadir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_simultaneous_add2016/haddtuples"),
    Bplus_Corrected_Mass_min(4000),
    Bplus_Corrected_Mass_max(7000),
    signalfilename("B23MuNuMC2012NNmumore03Strip21"),
    partrecofilename("B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM"),
    kaonfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM"),
    protonfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM"),
    pionfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM"),
    typelow("LowFCME"),
    typehigh("HighFCME"),
    sigdir("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_add2016/bin/")
    {}
    

   string workspaceFileName;
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
   


   void makeSWeightedTree(string extracut = "", string label = "_sWeighted");
   void prepareWorkspace();
   void fitJpsiKData(bool binnedFit = false);
   void fitJpsiKData2(bool binnedFit = false);
   void fitJpsiKData3(bool binnedFit = false);
   void fitJpsiKData4(bool binnedFit = false);
   void plot();
   void plotpretty();
   void plotprettysim(string type);
   void compareplots(string filename);

   vector<double> fitsignalcomponent(string weightname, string typelow);
   vector<double> fitpartrecocomponent(string typelow);
   vector<double> fitmisidcomponent(string type);
   vector<double> fitmisidcomponentall(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type);

   double fitmisidone(string type, string dir ,string filename, string weight, string species);  


   void prepareWorkspaceForSimultaneousFit(string type);

   void calculateFOM(string type);

   void simultaneouspdf();
   void simultaneouspdfminenew();
   void simultaneouspdfminenewseparate();
   void simfitseparateandsavesig();

};

#endif
