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
   :workspaceFileName("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous_symmetric_newcontrolchannel/workspace/FitB23MuNuworkspace.root"),
    plotdir("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous_symmetric_newcontrolchannel/workspace_plots/"), 
    workspacedir("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous_symmetric_newcontrolchannel/workspace_preparation/"),
    workspaceFileNameSim("FitB23MuNuworkspace"),
    fitdir("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous_symmetric_newcontrolchannel/workspace_fit/"),
    clsdir("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous_symmetric_newcontrolchannel/workspace_fitcls/"),
    tupledir("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_symmetric_newcontrolchannel/bin"), 
    misiddir("/vols/lhcb/ss4314/addPIDweights/FUMSB_simultaneous_symmetric_newcontrolchannel_nojackweight/finaltuples"),
    tuplename("finaldata"), 
    tuplenamelow("finaldata_LowFCME.root"),
    treename("DecayTree"),
    datadir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_simultaneous_symmetric_newcontrolchannel"),
    Bplus_Corrected_Mass_min(4000),
    Bplus_Corrected_Mass_max(7000),
    signalfilename("B23MuNuMCNNmumore03Strip21MagUp"),
    partrecofilename("B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM"),
    kaonfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM"),
    protonfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM"),
    pionfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM"),
    typelow("LowFCME"),
    typehigh("HighFCME"),
    sigdir("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_simultaneous_symmetric_newcontrolchannel/bin/")
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
  
   void prepareWorkspaceForSimultaneousFit(string type);

   void calculateFOM(string type);

   void simultaneouspdf();
   void simultaneouspdfminenew();
   void simultaneouspdfminenewseparate();
   void simfitseparateandsavesig();

};

#endif
