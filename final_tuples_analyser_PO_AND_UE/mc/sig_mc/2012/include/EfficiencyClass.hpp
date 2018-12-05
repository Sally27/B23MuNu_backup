#ifndef EFFICIENCYCLASS 
#define EFFICIENCYCLASS 

#include "ValError.hpp"
#include "analib.hpp"
//#include "doubleCrystalBall.hpp"
#include<string>
#include<vector>

//using namespace RooFit;
//using namespace RooStats;
using namespace std;


//class ValError;

class EfficiencyClass
{ 
   public:

   EfficiencyClass()
   :gen_eff(0.1606,0.0004),
    numbkk(1114130),
    numgen(25000),

    pathname("/vols/lhcb/ss4314/final_tuples/mc/sig_mc/2012/"),
    filename("Bu23MuNuMC2012"), 
    decaytreename("B23MuNu_Tuple/DecayTree"),
    extension(".root"),
    qmin_genlevel("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut.root"),
    qmin_inacc_genlevel("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut_inacc.root")
    {}
    

    ValError gen_eff;
    double numbkk;  
    double numgen;

    string filename;
    string pathname;
    string decaytreename;
    string extension;
    string qmin_genlevel;
    string qmin_inacc_genlevel;
//    ValError EfficiencyClass::calculateProduct_BR_eff(string type, string species, ValError gen_eff, ValError sel_eff)
    ValError return_gen_eff(string species);
    double return_numbkk(string species);
    double return_numgen(string species);
    string return_string(string species);
};

#endif
