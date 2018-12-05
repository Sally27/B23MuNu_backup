#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TH1F.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"
#include<algorithm>
#include "TTreeFormula.h"
#include "usefulFunctions.hpp"
#include "ValError.hpp"
#include "mySecondClass.hpp"
#include "EfficiencyClass.hpp"
#include<iostream>

using namespace std;
//using namespace RooFit;


int main(){

	ofstream out;
	out.open("FittedJpsiK_Yields_Selection_OnlyTCK35_nspd450.tex");

	out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
	out<<"\\usepackage[pdftex]{graphicx}"<<endl;
	out<<"\\usepackage{url}"<<endl;
	out<<"\\usepackage{mathtools}"<<endl;
	out<<"\\usepackage{multirow}"<<endl;
        out<<"\\usepackage{amsmath}"<<endl;
	out<<"\\usepackage{graphicx}"<<endl;
	out<<"\\usepackage[table]{xcolor}"<<endl;
	out<<"\\usepackage{amsmath,amssymb}"<<endl;
	out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
	out<<"\\usepackage{colortbl}"<<endl;
	out<<"\\usepackage{lscape}"<<endl;
	out<<"\\begin{document}"<<endl;
	out<<"\\begin{landscape}"<<endl;

	//        out<<"Calculation of the Single Event Sensitivity"<<endl;
	out<<"\\begin{table}[ht]"<<endl;
	out<<"\\small"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{ l | l | l | l | l | l}"<<endl; 
	out<<"\\hline"<<endl;
	out<<"Properties & 2011 nspd & 2012 nspd & 2016 tck35 & 2012/2011 & 2016/2012  \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"\\hline"<<endl;

	vector<int> years;

        years.push_back(2011);
        years.push_back(2012);
        years.push_back(2016);

	vector<string> cuts;

	cuts.push_back("nocut");
	cuts.push_back("misidstripping");
	cuts.push_back("PIDinmuonacc");
	cuts.push_back("trigger");
	cuts.push_back("PIDnshared");
	cuts.push_back("combibdt");
	cuts.push_back("misidbdt");
	cuts.push_back("fitrange");
	cuts.push_back("nSPD");

        double number_obs_NOFCME_2011, number_obs_NOFCME_err_2011, number_obs_NOFCME_2012, number_obs_NOFCME_err_2012,  number_obs_NOFCME_2016, number_obs_NOFCME_err_2016;	
        double number_obs_NOFCME_old_2011, number_obs_NOFCME_old_err_2011, number_obs_NOFCME_old_2012, number_obs_NOFCME_old_err_2012,  number_obs_NOFCME_old_2016, number_obs_NOFCME_old_err_2016;	


        for (int i(0); i<cuts.size(); i++)
        {

        if (i!=cuts.size()-1)
        {
	number_obs_NOFCME_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
	number_obs_NOFCME_err_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));


	number_obs_NOFCME_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
	number_obs_NOFCME_err_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));

	number_obs_NOFCME_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i)+".root").c_str(), "FitControl_2016", "NumNormObs")));
	number_obs_NOFCME_err_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i)+".root").c_str(), "FitControl_2016", "NumNormObs_Err")));
        }

        else
        {
	number_obs_NOFCME_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011_SPD450/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
	number_obs_NOFCME_err_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011_SPD450/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));


	number_obs_NOFCME_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012_SPD450/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
	number_obs_NOFCME_err_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012_SPD450/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));

	number_obs_NOFCME_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i-1)+".root").c_str(), "FitControl_2016", "NumNormObs")));
	number_obs_NOFCME_err_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i-1)+".root").c_str(), "FitControl_2016", "NumNormObs_Err")));
        }



        ValError info2011(number_obs_NOFCME_2011,number_obs_NOFCME_err_2011);
        ValError info2012(number_obs_NOFCME_2012,number_obs_NOFCME_err_2012);
        ValError info2016(number_obs_NOFCME_2016,number_obs_NOFCME_err_2016);
  

        out << "N tuple"<<cuts.at(i)<<" & "<< (info2011).roundToError_diffbase(true)<<" & "<<(info2012).roundToError_diffbase(true)<<" & "<<(info2016).roundToError_diffbase(true)<< " & "<<printnice(info2012/info2011)<<" & " <<printnice(info2016/info2012)<<" \\\\ "<<endl;
	}


     //   fillinfo.cd();
     //   fillinfotree.Fill();
     //   fillinfotree.Write("",TObject::kOverwrite);

        out<<"\\hline"<<endl;
        for (int i(1); i<cuts.size(); i++)
        {

	number_obs_NOFCME_old_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
	number_obs_NOFCME_old_err_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));


	number_obs_NOFCME_old_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
	number_obs_NOFCME_old_err_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));


	number_obs_NOFCME_old_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i-1)+".root").c_str(), "FitControl_2016", "NumNormObs")));
	number_obs_NOFCME_old_err_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i-1)+".root").c_str(), "FitControl_2016", "NumNormObs_Err")));

        if (i!=cuts.size()-1)
        {
	number_obs_NOFCME_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
	number_obs_NOFCME_err_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));


	number_obs_NOFCME_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
	number_obs_NOFCME_err_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));

	number_obs_NOFCME_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i)+".root").c_str(), "FitControl_2016", "NumNormObs")));
	number_obs_NOFCME_err_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i)+".root").c_str(), "FitControl_2016", "NumNormObs_Err")));

        }

        else
        {
	number_obs_NOFCME_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011_SPD450/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
	number_obs_NOFCME_err_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011_SPD450/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));

	number_obs_NOFCME_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012_SPD450/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
	number_obs_NOFCME_err_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012_SPD450/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));

	number_obs_NOFCME_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i-1)+".root").c_str(), "FitControl_2016", "NumNormObs")));
	number_obs_NOFCME_err_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i-1)+".root").c_str(), "FitControl_2016", "NumNormObs_Err")));
        }

//	number_obs_NOFCME_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i)+".root").c_str(), "FitControl_2016", "NumNormObs")));
//	number_obs_NOFCME_err_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i)+".root").c_str(), "FitControl_2016", "NumNormObs_Err")));

        ValError info2011_old(number_obs_NOFCME_old_2011,number_obs_NOFCME_old_err_2011);
        ValError info2012_old(number_obs_NOFCME_old_2012,number_obs_NOFCME_old_err_2012);
        ValError info2016_old(number_obs_NOFCME_old_2016,number_obs_NOFCME_old_err_2016);


        ValError info2011(number_obs_NOFCME_2011,number_obs_NOFCME_err_2011);
        ValError info2012(number_obs_NOFCME_2012,number_obs_NOFCME_err_2012);
        ValError info2016(number_obs_NOFCME_2016,number_obs_NOFCME_err_2016);
  

     //   cout<<"ALL OK"<<i<< " : "<< info2011/info2011_old<<" : "<< info2012/info2012_old<< " : "<< info2016/info2016_old <<endl;
      //  out << "$\\varepsilon_{"<<cuts.at(i)<<"}$ & "<< (info2011/info2011_old).roundToError_diffbase(true)<<" & "<<(info2012/info2012_old).roundToError_diffbase(true)<<" & "<<(info2016/info2016_old).roundToError_diffbase(false)<<" & & "<<" \\\\ "<<endl;
	}

        cout<<"of first loop "<<endl;

        vector<ValError> eff2011;
        vector<ValError> eff2012;
        vector<ValError> eff2016;


        vector<ValError> eff2011_sel;
        vector<ValError> eff2012_sel;
        vector<ValError> eff2016_sel;

        vector<ValError> eff2011_sel2;
        vector<ValError> eff2012_sel2;
        vector<ValError> eff2016_sel2;

        vector<ValError> eff2011_sel3;
        vector<ValError> eff2012_sel3;
        vector<ValError> eff2016_sel3;
        vector<ValError> eff2011_sel4;
        vector<ValError> eff2012_sel4;
        vector<ValError> eff2016_sel4;

	out<<"\\hline"<<endl;
	for (int i(1); i<cuts.size(); i++)
	{

		number_obs_NOFCME_old_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
		number_obs_NOFCME_old_err_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));


		number_obs_NOFCME_old_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
		number_obs_NOFCME_old_err_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));


		number_obs_NOFCME_old_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i-1)+".root").c_str(), "FitControl_2016", "NumNormObs")));
		number_obs_NOFCME_old_err_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i-1)+".root").c_str(), "FitControl_2016", "NumNormObs_Err")));

		if (i!=cuts.size()-1)
		{
			number_obs_NOFCME_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
			number_obs_NOFCME_err_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));


			number_obs_NOFCME_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
			number_obs_NOFCME_err_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));

		number_obs_NOFCME_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i)+".root").c_str(), "FitControl_2016", "NumNormObs")));
		number_obs_NOFCME_err_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i)+".root").c_str(), "FitControl_2016", "NumNormObs_Err")));
		}

		else
		{
			number_obs_NOFCME_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011_SPD450/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
			number_obs_NOFCME_err_2011=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2011_SPD450/selection_7/FitResults/FitControl_Run1_2011"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));

			number_obs_NOFCME_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012_SPD450/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs")));
			number_obs_NOFCME_err_2012=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2012_SPD450/selection_7/FitResults/FitControl_Run1_2012"+cuts.at(i-1)+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));

		number_obs_NOFCME_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i-1)+".root").c_str(), "FitControl_2016", "NumNormObs")));
		number_obs_NOFCME_err_2016=(double(returnEff(("/home/hep/ss4314/public_html/fitcontrol_selection/2016_35TCK/selection_7/FitResults/FitControl_2016_2016"+cuts.at(i-1)+".root").c_str(), "FitControl_2016", "NumNormObs_Err")));
		}



		ValError info2011_old(number_obs_NOFCME_old_2011,number_obs_NOFCME_old_err_2011);
		ValError info2012_old(number_obs_NOFCME_old_2012,number_obs_NOFCME_old_err_2012);
		ValError info2016_old(number_obs_NOFCME_old_2016,number_obs_NOFCME_old_err_2016);


		ValError info2011(number_obs_NOFCME_2011,number_obs_NOFCME_err_2011);
		ValError info2012(number_obs_NOFCME_2012,number_obs_NOFCME_err_2012);
		ValError info2016(number_obs_NOFCME_2016,number_obs_NOFCME_err_2016);

		string for2011=(dbl2str((info2011/info2011_old).val,4)+" $\\pm$ "+dbl2str((info2011/info2011_old).err,4)); 
		string for2012=(dbl2str((info2012/info2012_old).val,4)+" $\\pm$ "+dbl2str((info2012/info2012_old).err,4)); 
		string for2016=(dbl2str((info2016/info2016_old).val,4)+" $\\pm$ "+dbl2str((info2016/info2016_old).err,4)); 


		eff2011.push_back(info2011/info2011_old);
		eff2012.push_back(info2012/info2012_old);
		eff2016.push_back(info2016/info2016_old);

		if ((cuts.at(i)=="PIDinmuonacc") ||  (cuts.at(i)=="PIDnshared"))
		{
			cout<<"cuts "<< cuts.at(i)<<endl;
		}
		else
		{
			eff2011_sel.push_back(info2011/info2011_old);
			eff2012_sel.push_back(info2012/info2012_old);
			eff2016_sel.push_back(info2016/info2016_old);
		} 
                            
		if ((cuts.at(i)=="PIDinmuonacc") ||  (cuts.at(i)=="PIDnshared") || (cuts.at(i)=="trigger"))
		{
			cout<<"cuts "<< cuts.at(i)<<endl;
		}
		else
		{
			eff2011_sel2.push_back(info2011/info2011_old);
			eff2012_sel2.push_back(info2012/info2012_old);
			eff2016_sel2.push_back(info2016/info2016_old);
		} 

		if ( (cuts.at(i)=="trigger") || (cuts.at(i)=="nSPD"))
		{
			cout<<"cuts "<< cuts.at(i)<<endl;
		}
		else
		{
			eff2011_sel4.push_back(info2011/info2011_old);
			eff2012_sel4.push_back(info2012/info2012_old);
			eff2016_sel4.push_back(info2016/info2016_old);
		} 
		if ((cuts.at(i)=="PIDinmuonacc") ||  (cuts.at(i)=="PIDnshared") || (cuts.at(i)=="trigger") || (cuts.at(i)=="nSPD"))
		{
			cout<<"cuts "<< cuts.at(i)<<endl;
		}
		else
		{
			eff2011_sel3.push_back(info2011/info2011_old);
			eff2012_sel3.push_back(info2012/info2012_old);
			eff2016_sel3.push_back(info2016/info2016_old);
		} 
		out << "$\\varepsilon_{"<<cuts.at(i)<<"}$ & "<< for2011.c_str() <<" & "<< for2012.c_str() <<" & "<<for2016.c_str()<<" & "<<printnice((info2012/info2012_old)/(info2011/info2011_old))<<" & "<< printnice((info2016/info2016_old)/(info2012/info2012_old))<<" \\\\ "<<endl;
	}

	vector<double> weights;
	for (int i(1); i<cuts.size(); i++)
	{
		weights.push_back(1.0);
	}

        ValError finalprod_2011=getFullProduct(eff2011);
        ValError finalprod_2012=getFullProduct(eff2012);
        ValError finalprod_2016=getFullProduct(eff2016);

        ValError finalprod_2011_sel=getFullProduct(eff2011_sel);
        ValError finalprod_2012_sel=getFullProduct(eff2012_sel);
        ValError finalprod_2016_sel=getFullProduct(eff2016_sel);
       
        ValError finalprod_2011_sel2=getFullProduct(eff2011_sel2);
        ValError finalprod_2012_sel2=getFullProduct(eff2012_sel2);
        ValError finalprod_2016_sel2=getFullProduct(eff2016_sel2);


        ValError finalprod_2011_sel3=getFullProduct(eff2011_sel3);
        ValError finalprod_2012_sel3=getFullProduct(eff2012_sel3);
        ValError finalprod_2016_sel3=getFullProduct(eff2016_sel3);

        ValError finalprod_2011_sel4=getFullProduct(eff2011_sel4);
        ValError finalprod_2012_sel4=getFullProduct(eff2012_sel4);
        ValError finalprod_2016_sel4=getFullProduct(eff2016_sel4);
 
       out<<"\\hline"<<endl;
        out << "$\\varepsilon_{total}$ & "<< printnice(finalprod_2011) <<" & "<< printnice(finalprod_2012) <<" & "<<printnice(finalprod_2016)<<" & &"<<" \\\\ "<<endl;
        out << "$\\varepsilon_{total_nopid}$ & "<< printnice(finalprod_2011_sel) <<" & "<< printnice(finalprod_2012_sel) <<" & "<<printnice(finalprod_2016_sel)<<" & &"<<" \\\\ "<<endl;
        out << "$\\varepsilon_{total_nopid_trg}$ & "<< printnice(finalprod_2011_sel2) <<" & "<< printnice(finalprod_2012_sel2) <<" & "<<printnice(finalprod_2016_sel2)<<" & &"<<" \\\\ "<<endl;
        out << "$\\varepsilon_{total_nopid_trg_nspd}$ & "<< printnice(finalprod_2011_sel3) <<" & "<< printnice(finalprod_2012_sel3) <<" & "<<printnice(finalprod_2016_sel3)<<" & &"<<" \\\\ "<<endl;
        out << "$\\varepsilon_{total_notrg_nspd}$ & "<< printnice(finalprod_2011_sel4) <<" & "<< printnice(finalprod_2012_sel4) <<" & "<<printnice(finalprod_2016_sel4)<<" & &"<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"Ratios & - & $\\epsilon^{2012}_{tot}/\\epsilon^{2011}_{tot}$=" <<printnice(finalprod_2012/finalprod_2011)<<"&$\\epsilon^{2016}_{tot}/\\epsilon^{2012}_{tot}$= "<<printnice(finalprod_2016/finalprod_2012)<<" & & "<<" \\\\ "<<endl;
        out<<"Ratios no pid & - & $\\epsilon^{2012}_{tot}/\\epsilon^{2011}_{tot}$=" <<printnice(finalprod_2012_sel/finalprod_2011_sel)<<"&$\\epsilon^{2016}_{tot}/\\epsilon^{2012}_{tot}$= "<<printnice(finalprod_2016_sel/finalprod_2012_sel)<<" & & "<<" \\\\ "<<endl;

        out<<"Ratios no pid and trg & - & $\\epsilon^{2012}_{tot}/\\epsilon^{2011}_{tot}$=" <<printnice(finalprod_2012_sel2/finalprod_2011_sel2)<<"&$\\epsilon^{2016}_{tot}/\\epsilon^{2012}_{tot}$= "<<printnice(finalprod_2016_sel2/finalprod_2012_sel2)<<" & & "<<" \\\\ "<<endl;
        out<<"Ratios no pid and trg nspd& - & $\\epsilon^{2012}_{tot}/\\epsilon^{2011}_{tot}$=" <<printnice(finalprod_2012_sel3/finalprod_2011_sel3)<<"&$\\epsilon^{2016}_{tot}/\\epsilon^{2012}_{tot}$= "<<printnice(finalprod_2016_sel3/finalprod_2012_sel3)<<" & & "<<" \\\\ "<<endl;
        out<<"Ratios no trg nspd& - & $\\varepsilon^{2012}_{tot}/\\varepsilon^{2011}_{tot}$=" <<printnice(finalprod_2012_sel4/finalprod_2011_sel4)<<"&$\\epsilon^{2016}_{tot}/\\epsilon^{2012}_{tot}$= "<<printnice(finalprod_2016_sel4/finalprod_2012_sel4)<<" & & "<<" \\\\ "<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{ $B^+ \\rightarrow (J/\\psi \\rightarrow \\mu^+ \\mu^{-}) K^{+}$ yields and efficiencies of selection in 2011,2012,2016 samples (before and after method).}"<<endl;
        out<<"\\label{tab:yields}"<<endl;
        out<<"\\end{table}"<<endl;
//        EfficiencyClass highpr;
//        EfficiencyClass nopr;

      


	out<<"\\end{landscape}"<<endl;


	out<<"\\newpage"<<endl;
	out<<"\\end{document}"<<endl;



	out.close();


        



	//	cout<<mctrutheff*jpsieff*nSharedeff*qmineff<<endl;
	//	double brfr=1e-8;
	//	double ppbbX=284e-6;
	//	double bBplus= 2*0.4;
	//	double datacoll=3e15;
	//	double decprodcut =0.185;
	//	double effrecostrip= 0.111;
	//
	//	double finaleff;
	//	finaleff=ppbbX*bBplus*brfr*datacoll*decprodcut*effrecostrip*jpsieff*nSharedeff*qmineff*triggereff; 
	//	cout<<"Final Num Of Events: "<<finaleff<<endl;




	return(0);



}



