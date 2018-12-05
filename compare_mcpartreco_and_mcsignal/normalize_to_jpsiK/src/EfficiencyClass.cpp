#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "EfficiencyClass.hpp"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "TCanvas.h"
#include "TTree.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooMinuit.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooStats/SPlot.h"
#include "TTreeFormula.h"
#include "RooGaussian.h"
#include "TLegend.h"
#include "TPaveLabel.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include "TMatrixDSym.h"
#include "TDirectory.h"
#include "RooChi2Var.h"
#include "RooMinimizer.h"
#include "RooMinuit.h"
#include "TMinuitMinimizer.h"
#include "RooExtendPdf.h"
#include "RooMultiVarGaussian.h"
#include "RooProdPdf.h"
#include "TMatrixT.h"
#include "ValError.hpp"
#include "usefulFunctions.hpp"
#include "EfficiencyClass.hpp"

using namespace std;
using namespace RooFit;


ValError EfficiencyClass::return_num_obs(string type, string year)
{

        if (type=="low" && year=="2012")
        {
        ValError obs_lowfcme(number_obs_LowFCME,number_obs_LowFCME_err);
        ValError product=obs_lowfcme;
        cout<<"Is "<<product<<endl;
        return(product);
        }


        if (type=="high" && year=="2012" )
        {
        ValError obs_highfcme(number_obs_HighFCME,number_obs_HighFCME_err);
        ValError product=obs_highfcme;
        cout<<"Is "<<product<<endl;
        return(product);
        }
                 
        if (type=="no" && year=="2012")
        {
        ValError obs_nofcme(number_obs_NOFCME,number_obs_NOFCME_err);
        ValError product=obs_nofcme;
        cout<<"Is "<<product<<endl;
        return(product);
        }
        if (type=="low" && year=="2016")
        {
        ValError obs_lowfcme(number_obs_LowFCME_2016,number_obs_LowFCME_err_2016);
        ValError product=obs_lowfcme;
        cout<<"Is "<<product<<endl;
        return(product);
        }


        if (type=="high" && year=="2016" )
        {
        ValError obs_highfcme(number_obs_HighFCME_2016,number_obs_HighFCME_err_2016);
        ValError product=obs_highfcme;
        cout<<"Is "<<product<<endl;
        return(product);
        }
                 
        if (type=="no" && year=="2016")
        {
        ValError obs_nofcme(number_obs_NOFCME_2016,number_obs_NOFCME_err_2016);
        ValError product=obs_nofcme;
        cout<<"Is "<<product<<endl;
        return(product);
        }
}

ValError EfficiencyClass::calculateProduct_BR_eff_number_obs(string type, string year ,ValError eff_pr, ValError eff_jpsik)
{
        cout<<"Final number of particles for part reco in "<<type<<endl;


        if (type=="low"&& year=="2012")
        {
        ValError obs_lowfcme(number_obs_LowFCME,number_obs_LowFCME_err);
        ValError product=((obs_lowfcme*eff_pr)/(eff_jpsik));
        cout<<"Is "<<product<<endl;
        return(product);
        }


        if (type=="high"&& year=="2012")
        {
        ValError obs_highfcme(number_obs_HighFCME,number_obs_HighFCME_err);
        ValError product=((obs_highfcme*eff_pr)/(eff_jpsik));
        cout<<"Is "<<product<<endl;
        return(product);
        }
                 
        if (type=="no" && year=="2012")
        {
        ValError obs_nofcme(number_obs_NOFCME,number_obs_NOFCME_err);
        ValError product=((obs_nofcme*eff_pr)/(eff_jpsik));
        cout<<"Is "<<product<<endl;
        return(product);
        }

        if (type=="low" && year=="2016")
        {
        ValError obs_lowfcme(number_obs_LowFCME_2016,number_obs_LowFCME_err_2016);
        ValError product=((obs_lowfcme*eff_pr)/(eff_jpsik));
        cout<<"Is "<<product<<endl;
        return(product);
        }


        if (type=="high" && year=="2016")
        {
        ValError obs_highfcme(number_obs_HighFCME_2016,number_obs_HighFCME_err_2016);
        ValError product=((obs_highfcme*eff_pr)/(eff_jpsik));
        cout<<"Is "<<product<<endl;
        return(product);
        }
                 
        if (type=="no" && year=="2016")
        {
        ValError obs_nofcme(number_obs_NOFCME_2016,number_obs_NOFCME_err_2016);
        ValError product=((obs_nofcme*eff_pr)/(eff_jpsik));
        cout<<"Is "<<product<<endl;
        return(product);
        }
}

ValError EfficiencyClass::calculateProduct_BR(string species)
{

        cout<<"Calc total br for "<<species<<" "<<endl;

        if (species=="pr")
        {
        ValError pr_1(branching_frac_PR_1,branching_frac_PR_1_err);
        ValError pr_2(branching_frac_PR_2,branching_frac_PR_2_err);
        ValError product=(pr_1*pr_2);
        cout<<"Is "<<product<<endl;
        return(product);
        }


        if (species=="norm")
        {
        ValError norm_1(branching_frac_NORM_1,branching_frac_NORM_1_err);
        ValError norm_2(branching_frac_NORM_2,branching_frac_NORM_2_err);
        ValError product=(norm_1*norm_2);
        cout<<"Is "<<product<<endl;
        return(product);
        }


}



ValError EfficiencyClass::calculateProduct_eff(string type, string species, ValError gen_eff, ValError sel_eff)
{

        cout<<"Calculate tot eff  for "<<type<<" and "<<species<<" "<<endl;

        if (species=="pr")
        {
//        ValError pr_1(branching_frac_PR_1,branching_frac_PR_1_err);
//        ValError pr_2(branching_frac_PR_2,branching_frac_PR_2_err);
        ValError product=(gen_eff*sel_eff);
        cout<<"Is "<<product<<endl;
        return(product);
        }


        if (species=="norm")
        {
//        ValError norm_1(branching_frac_NORM_1,branching_frac_NORM_1_err);
//        ValError norm_2(branching_frac_NORM_2,branching_frac_NORM_2_err);
        ValError product=(gen_eff*sel_eff);
        cout<<"Is "<<product<<endl;
        return(product);
        }


}


ValError EfficiencyClass::calculateProduct_BR_eff(string type, string species, ValError gen_eff, ValError sel_eff)
{

        cout<<"Calc eff times br for "<<type<<" and "<<species<<" "<<endl;

        if (species=="pr")
        {
        ValError pr_1(branching_frac_PR_1,branching_frac_PR_1_err);
        ValError pr_2(branching_frac_PR_2,branching_frac_PR_2_err);
        ValError product=(pr_1*pr_2*gen_eff*sel_eff);
        cout<<"Is "<<product<<endl;
        return(product);
        }


        if (species=="norm")
        {
        ValError norm_1(branching_frac_NORM_1,branching_frac_NORM_1_err);
        ValError norm_2(branching_frac_NORM_2,branching_frac_NORM_2_err);
        ValError product=(norm_1*norm_2*gen_eff*sel_eff);
        cout<<"Is "<<product<<endl;
        return(product);
        }


}

ValError EfficiencyClass::calculate_total_seleff(double number_total,string file, string type)
{

        int numofontriesnofcme=getmyentries(file.c_str(), "DecayTree");
        ValError passed(double(numofontriesnofcme),sqrt(double(numofontriesnofcme)));
        ValError total(double(number_total),sqrt(double(number_total)));
        ValError seleff=getRatioBinomial(passed, total);

        cout<<"Total selection eff is "<<seleff<<" for "<<type<<endl;
        return(seleff);

}


ValError EfficiencyClass::return_gen_eff(string species)
{

  // ValError GEN_EFF(0.,0.);

   if (species=="pr")
   {
   ValError GEN_EFF(gen_eff_PR,gen_eff_PR_err);
   cout<<"Generator level for "<<species<<" is "<<GEN_EFF<<endl;
   return(GEN_EFF);
   }
   if (species=="norm")
   {
   ValError GEN_EFF(gen_eff_NORM,gen_eff_NORM_err);
   cout<<"Generator level for "<<species<<" is "<<GEN_EFF<<endl;
   return(GEN_EFF);
   }



}


ValError EfficiencyClass::return_brbdmunu()
{

  // ValError GEN_EFF(0.,0.);

   ValError brbdmunu(branching_frac_PR_1,branching_frac_PR_1_err);
   cout<<"br b to dmunux for  is "<<brbdmunu<<endl;
   return(brbdmunu);

}

ValError EfficiencyClass::return_brdkpimumu()
{

  // ValError GEN_EFF(0.,0.);

   ValError brdkpimumu(branching_frac_PR_2,branching_frac_PR_2_err);
   cout<<"br dkpimumu for  is "<<brdkpimumu<<endl;
   return(brdkpimumu);

}



string EfficiencyClass::return_file(string species, string type)
{

    string file;
    if (species=="pr" && type=="low")
    {
    file=pr_low; 
    }

    if (species=="pr" && type=="high")
    {
    file=pr_high;
    }


    if (species=="pr" && type=="no")
    {
    file=pr_no;
    }

    if (species=="norm" && type=="low")
    {
    file=norm_low; 
    }

    if (species=="norm" && type=="high")
    {
    file=norm_high;
    }

    if (species=="norm" && type=="no")
    {
    file=norm_no;
    }


    cout<<"Returning "<<file<<" for "<< species<<" and "<<type<<endl;
return file;
}

