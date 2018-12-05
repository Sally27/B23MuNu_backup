#ifndef PLOTMISIDVARIATIONS 
#define PLOTMISIDVARIATIONS 

#include "usefulFunctions.hpp"
//#include "RooCBShape.h"
//#include "doubleCrystalBall.hpp"
#include<string>
#include<vector>

using namespace RooFit;
//using namespace RooStats;
using namespace std;

class PlotMisidVariations
{ 
   public:

   PlotMisidVariations()
   :plotdir("/vols/lhcb/ss4314/average_misidvariations/FUMSB_simultaneous_NewTCK_misidvariation/plots/"), 
    fitdir("/vols/lhcb/ss4314/average_misidvariations/FUMSB_simultaneous_NewTCK_misidvariation/fit/"),
    bindir("/vols/lhcb/ss4314/average_misidvariations/FUMSB_simultaneous_NewTCK_misidvariation/bin_info/"),
    workdir("/vols/lhcb/ss4314/average_misidvariations/FUMSB_simultaneous_NewTCK_misidvariation/preparation/"),
    fitresdir("/vols/lhcb/ss4314/average_misidvariations/FUMSB_simultaneous_NewTCK_misidvariation/fit_results"),
    comparedir("/vols/lhcb/ss4314/average_misidvariations/FUMSB_simultaneous_NewTCK_misidvariation/compare_fits"),
    datadir("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_misidvariation/bin"),
    treename("DecayTree"),
    numberofhistograms(10),
    numberoftoys(100), 
    Bplus_Corrected_Mass_min(4000),
    Bplus_Corrected_Mass_max(7000),
    workspacedir("/vols/lhcb/ss4314/average_misidvariations/FUMSB_simultaneous_NewTCK_misidvariation/workspace")
    
    {}
    

   string plotdir;
   string fitdir;
   string workdir;
   string bindir;
   string fitresdir;
   string comparedir;   
   string datadir;

   string treename;
   int numberofhistograms;
   int numberoftoys;
   double Bplus_Corrected_Mass_max;
   double Bplus_Corrected_Mass_min;
   string workspacedir;

   int get_numberofhisto();
   int get_numberoftoys();
   void create_distributionhistograms();
   void fill_distributionhistograms(TH1D* h_bin,double value);
   void print_mean_and_rms(string type);
   void plot_bin_histograms(string type);
   void create_bin_histograms(vector< vector<double> > values,string type);
   vector<double> plotdistributions_perbin(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type, int toynumber,vector <string> &PID);
   void plotmisidcomponents_pertoy(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type, int ntoy,vector <string> &PID);
   vector<double> fitmisidcomponentall_compare(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type);
   vector<double> fitmisidcomponentall_chi2(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type);
   double fitmisidone(string type, string dir ,string filename, string weight, string species);
   
};

#endif
