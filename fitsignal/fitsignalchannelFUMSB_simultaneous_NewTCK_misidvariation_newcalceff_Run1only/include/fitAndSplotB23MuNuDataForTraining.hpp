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
   :workspaceFileName("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_simultaneous_NewTCK_misidvariation_newcalceff/workspace/FitB23MuNuworkspace.root"),
    plotdir("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_simultaneous_NewTCK_misidvariation_newcalceff/workspace_plots/"), 
    workspacedir("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_simultaneous_NewTCK_misidvariation_newcalceff/workspace_preparation/"),
    workspaceFileNameSim("FitB23MuNuworkspace"),
    fitdir("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_simultaneous_NewTCK_misidvariation_newcalceff/workspace_fit/"),
    clsdir("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_simultaneous_NewTCK_misidvariation_newcalceff/workspace_fitcls/"),
    tupledir("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin"), 
    misiddir("/vols/lhcb/ss4314/addPIDweights/FUMSB_simultaneous_NewTCK/finaltuplesRun1"),
    misidvariationdir("/vols/lhcb/ss4314/average_misidvariations/FUMSB_simultaneous_NewTCK_misidvariation/workspace"),
    tuplename("finaldata"), 
    tuplenamelow("finaldata_LowFCME.root"),
    treename("DecayTree"),
    datadir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_simultaneous_NewTCK/haddtuples"),
    Bplus_Corrected_Mass_min(4000),
    Bplus_Corrected_Mass_max(7000),
    signalfilename("B23MuNuMCAll_"),
    partrecofilename("MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM"),
    kaonfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM"),
    protonfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM"),
    pionfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM"),
    typelow("LowFCME"),
    typehigh("HighFCME"),
    sigdir("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK/haddtuples/"),

    seslowrun1(1.7903e-9),
    seslowrun1_err(5.95034e-11),

    seshighrun1(1.91937e-9),
    seshighrun1_err(6.38219e-11),

    seslow2016(3.28296e-9),
    seslow2016_err(1.03667e-10),

    seshigh2016(4.20876e-9),
    seshigh2016_err(1.3471e-10),

    numberofpartreco_low(46.1084),
    numberofpartreco_error_low(5.16052),

    numberofpartreco_high(46.311),
    numberofpartreco_error_high(5.18287)


    {}
    

//   string PID;
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
   string misidvariationdir;
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
   
   double seslowrun1;
   double seslowrun1_err;

   double seshighrun1;
   double seshighrun1_err;

   double seslow2016;
   double seslow2016_err;

   double seshigh2016;
   double seshigh2016_err;
    

   double numberofpartreco_low;
   double numberofpartreco_error_low;

   double numberofpartreco_high;
   double numberofpartreco_error_high;

   void makeSWeightedTree(string extracut = "", string label = "_sWeighted");
   void prepareWorkspace();
   void fitJpsiKData(bool binnedFit = false);
   void fitJpsiKData2(bool binnedFit = false);
   void fitJpsiKData3(bool binnedFit = false);
   void fitJpsiKData4(bool binnedFit = false);
   void plot();
   void plotpretty();
   void plotprettysim(string type);
   void plotprettysim_chi2(string type);
   void compareplots(string filename);

   vector<double> fitsignalcomponent(string weightname, string typelow);
   vector<double> fitpartrecocomponent(string typelow);
   vector<double> fitmisidcomponent(string type);
   vector<double> fitmisidcomponentall(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type, vector <string> &PID);
   vector<double> fitmisidcomponentall_chi2(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type, vector <string> &PID);


   double fitmisidone(string type, string dir ,string filename, string weight, string species, string PID);  


   void prepareWorkspaceForSimultaneousFit(string type);

   void calculateFOM(string type);
   void calculateFOM_chi2(string type);


   void simultaneouspdf();
   void simultaneouspdfminenew();
   void simultaneouspdfminenewseparate();
   void simfitseparateandsavesig();
   void simfitseparateandsavesig_chi2fit();
};

#endif
