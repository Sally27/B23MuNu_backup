#ifndef FITANDSPLOTJPSIKDATAFORTRAINING 
#define FITANDSPLOTJPSIKDATAFORTRAINING 

#include "usefulFunctions.hpp"
//#include "RooCBShape.h"
//#include "doubleCrystalBall.hpp"
#include<string>

using namespace RooFit;
//using namespace RooStats;
using namespace std;

class FitAndSplotB23MuNuDataForTraining
{ 
   public:

   FitAndSplotB23MuNuDataForTraining()
   :workspaceFileName("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous/workspace/FitB23MuNuworkspace.root"),
    plotdir("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous/workspace_plots/"), 
    workspacedir("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous/workspace_preparation/"),
    workspaceFileNameSim("FitB23MuNuworkspace"),
    fitdir("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous/workspace_fit/"),
    clsdir("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous/workspace_fitcls/"),
    tupledir("/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/fitallafterMCnSharedRemovedFullUMSBIncludeLMSB_improvefit/bin/rootfiles"), 
    tuplename("finaldata"), 
    tuplenamelow("finaldata_LowFCME.root"),
    treename("DecayTree"),
    Bplus_Corrected_Mass_min(4000),
    Bplus_Corrected_Mass_max(10000),
    signalfilename("B23MuNuMC_NNmumore03Strip21MagUp"),
    partrecofilename("B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic"),
    kaonfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic"),
    protonfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic"),
    pionfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic"),
    typelow("LowFCME"),
    typehigh("HighFCME")
    {}
    

   string workspaceFileName;
   string plotdir;
   string fitdir;
   string workspacedir;
   string clsdir;
   string workspaceFileNameSim;
   string tuplename;
   

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


   vector<double> fitsignalcomponent(string weightname, string typelow);
   vector<double> fitpartrecocomponent(string typelow);
   vector<double> fitmisidcomponent(string type);
  
   void prepareWorkspaceForSimultaneousFit(string type);

   void calculateFOM(string type);

   void simultaneouspdf();
   void simultaneouspdfminenew();
   void simultaneouspdfminenewseparate();
   void simfitseparateandsavesig();

};

#endif
