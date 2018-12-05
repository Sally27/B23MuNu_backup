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
   :workspaceFileName("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_NOTsimultaneous_NewTCK_misidvariation_newcalceff_PIDoptimisation_extremeweights_2/workspace/FitB23MuNuworkspace.root"),
    plotdir("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_NOTsimultaneous_NewTCK_misidvariation_newcalceff_PIDoptimisation_extremeweights_2/workspace_plots/"), 
    fitdir("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_NOTsimultaneous_NewTCK_misidvariation_newcalceff_PIDoptimisation_extremeweights_2/workspace_fit/"),
    clsdir("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_NOTsimultaneous_NewTCK_misidvariation_newcalceff_PIDoptimisation_extremeweights_2/workspace_fitcls/"),
    workspacedir("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_NOTsimultaneous_NewTCK_misidvariation_newcalceff_PIDoptimisation_extremeweights_2/workspace_preparation/"),
    fitresdir("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_NOTsimultaneous_NewTCK_misidvariation_newcalceff_PIDoptimisation_extremeweights_2/fit_results"),
    comparedir("/vols/lhcb/ss4314/fitsignal/fitsignalchannelFUMSB_NOTsimultaneous_NewTCK_misidvariation_newcalceff_PIDoptimisation_extremeweights_2/compare_fits"),

    partrecodir("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin"), 
    sigdir("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/bin/"),
    datadir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/haddtuples"),
    misidvariationdir("/vols/lhcb/ss4314/average_misidvariations/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/workspace"),

    partrecofilename("MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM"),
    signalfilename("B23MuNuMC"),
    tuplename("Signaldata"), 
    workspaceDataFile("FitB23MuNuworkspace"),
    treename("DecayTree"),

    Bplus_Corrected_Mass_min(4000),
    Bplus_Corrected_Mass_max(7000),
    
    sesinfo("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc_PIDoptimisation_extremeweights/info"),
//    ses2016(1.8332e-9),
//    sesrun1err("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc_PIDoptimisation_extremeweights_2/info"),
//    ses2016err(5.5727e-11),

    numberofpartreco((92.4194/2.0)),
    numberofpartreco_error((10.2703/2.0))
    {}
    

   string workspaceFileName;
   string plotdir;
   string fitdir;
   string clsdir;
   string workspacedir;
   string fitresdir;
   string comparedir;   

   string partrecodir;
   string sigdir;
   string datadir;
   string misidvariationdir;

   string partrecofilename;
   string signalfilename;
   string tuplename;

   string workspaceDataFile;
   string treename;


   double Bplus_Corrected_Mass_max;
   double Bplus_Corrected_Mass_min;

 
   string sesinfo;
//   double sesrun1;
//   double ses2016;
//   double sesrun1err;
//   double ses2016err;

   double numberofpartreco;
   double numberofpartreco_error;

//original functions template//

   void fitJpsiKData4(bool binnedFit);
//   void makeSWeightedTree(string extracut = "", string label = "_sWeighted");
   void plot();

//Sally's addition//

   void plotprettysim(string type);
   void plotprettysim_chi2(string type, string PIDcut);

   vector<double> fitsignalcomponent(string weightname, string type, string year, string PIDcut);
   vector<double> fitpartrecocomponent(string typelow);
//   vector<double> fitmisidcomponent(string type);

   vector<double> fitmisidcomponentall_compare(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type);
   vector<double> fitmisidcomponentall_chi2(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type, string PIDcut);

   double fitmisidone(string type, string dir ,string filename, string weight, string species);
  
   void prepareWorkspaceForSimultaneousFit(string type, string year,string PIDcut);

   void calculateFOM(string type);
   void calculateFOM_chi2(string type, string PIDcut);

 //  void simfitseparateandsavesig();
   void simfitseparateandsavesig_chi2fit(string year, string PIDcut);
};

#endif
