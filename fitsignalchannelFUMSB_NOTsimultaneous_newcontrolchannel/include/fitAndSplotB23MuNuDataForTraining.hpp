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
   :workspaceFileName("/vols/lhcb/ss4314/fitsignalchannelFUMSB_NOTsimultaneous_newcontrolchannel/workspace/FitB23MuNuworkspace.root"),
    plotdir("/vols/lhcb/ss4314/fitsignalchannelFUMSB_NOTsimultaneous_newcontrolchannel/workspace_plots/"), 
    workspacedir("/vols/lhcb/ss4314/fitsignalchannelFUMSB_NOTsimultaneous_newcontrolchannel/workspace_preparation/"),
    workspaceFileNameSim("FitB23MuNuworkspace"),
    fitdir("/vols/lhcb/ss4314/fitsignalchannelFUMSB_NOTsimultaneous_newcontrolchannel/workspace_fit/"),
    clsdir("/vols/lhcb/ss4314/fitsignalchannelFUMSB_NOTsimultaneous_newcontrolchannel/workspace_fitcls/"),
    tupledir("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_newcontrolchannel/bin"), 
    misiddir("/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_newcontrolchannel/finaltuples"),
    tuplename("finaldata"), 
    tuplenamelow("finaldata_LowFCME.root"),
    treename("DecayTree"),
    datadir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_NOTsimultaneous_newcontrolchannel/"),
    Bplus_Corrected_Mass_min(4000),
    Bplus_Corrected_Mass_max(7000),
    signalfilename("B23MuNuMCNNmumore03Strip21MagUp"),
    partrecofilename("B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM"),
    kaonfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM"),
    protonfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM"),
    pionfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM"),
    typelow("LowFCME"),
    typehigh("HighFCME"),
    sigdir("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_NOTsimultaneous_newcontrolchannel/bin/")
//    nofitdata("Data2012and2011_SigReg_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM")
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
   string nofitdata;

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
   void plotprettysimrookeys(string type);

   vector<double> fitsignalcomponent(string weightname, string typelow);
   vector<double> fitpartrecocomponent(string typelow);
   vector<double> fitmisidcomponent(string type);
   vector<double> fitmisidcomponentrookeys(string type); 
 
   void prepareWorkspaceForSimultaneousFit(string type);

   void prepareWorkspaceNoFitData(string type);
   void fitplot();
   void fitplotrookeys();
   void calculateFOM(string type);

   void simfitseparateandsavesig();

};

#endif
