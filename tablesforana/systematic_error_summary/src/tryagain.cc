
#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH2D.h"
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
#include "TLegend.h"
#include "TProfile.h"
#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TString.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "TH3F.h"
#include <numeric>
#include "TGraph.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <cstring>
#include "TLegend.h"
#include "TStyle.h"
#include "TTreeFormula.h"
#include "TMultiGraph.h"
#include "TString.h"

#include "usefulFunctions.hpp"
#include "lhcbSally.hpp"

using namespace std;

int main(int argc, char *argv[])
{


        string systematic_trigger("/vols/lhcb/ss4314/systematic_uncertainties/triggerTISTOS/makeatable/Systematic_Trigger/Systematic_Trigger.root");
        string systematic_sigmodel("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/EfficiencyCalc/Systematic_SigModel/Systematic_SigModel.root");

        string systematic_kinrew("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/KinRew_Systematic/KinRew_Systematic.root");

        string stat_2012("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_NOTsimultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_probnnmu035.root");

        string stat_2016("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_NOTsimultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_probmu35.root");

	vector<double> suminquad_2012;
        vector<double> suminquad_2016;
        vector<double> suminquad_overall;

  //      suminquad_2012=;

        ofstream out;
	out.open("Summary_Systematics.tex");

	out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
	out<<"\\usepackage[pdftex]{graphicx}"<<endl;
	out<<"\\usepackage{url}"<<endl;
	out<<"\\usepackage{mathtools}"<<endl;
	out<<"\\usepackage{amsmath}"<<endl;
	out<<"\\usepackage{graphicx}"<<endl;
	out<<"\\usepackage[table]{xcolor}"<<endl;
	out<<"\\usepackage{amsmath,amssymb}"<<endl;
	out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
	out<<"\\usepackage{colortbl}"<<endl;
	out<<"\\begin{document}"<<endl;


	out<<"\\begin{table}[H]"<<endl;
	out<<"\\centering"<<endl;
	out<<"\\small"<<endl;
	out<<"\\begin{tabular}{ l | c  c | c  }"<<endl;
	out<<"\\hline"<<endl;
	out<<"Systematic source & Run 1/\\% &  2016/\\% & Error Overall \\\\ \\hline"<<endl;
	out<<"\\hline"<<endl;
	out<<"$\\mathcal{B}(J/\\psi \\rightarrow \\mu^{+} \\mu^{-})$ & "<<100*round_to_digits((0.033e-2/5.961e-2),2)<<" & "<<100*round_to_digits((0.033e-2/5.961e-2),2)<<" & "<<100*round_to_digits((0.033e-2/5.961e-2),2)<<"\\\\"<<endl;


        suminquad_2012.push_back((0.033e-2/5.961e-2)*100.0);
        suminquad_2016.push_back((0.033e-2/5.961e-2)*100.0);
        suminquad_overall.push_back((0.033e-2/5.961e-2)*100.0);
	
	out<<"$\\mathcal{B}(B^{+} \\rightarrow  J/\\psi K^{+})$ & "<<100*round_to_digits((0.031e-3/1.026e-3),2)<<" & "<<100*round_to_digits((0.031e-3/1.026e-3),2)<<" & "<<100*round_to_digits((0.031e-3/1.026e-3),2)<<"\\\\"<<endl;


        suminquad_2012.push_back((0.031e-3/1.026e-3)*100.0);
        suminquad_2016.push_back((0.031e-3/1.026e-3)*100.0);
        suminquad_overall.push_back((0.031e-3/1.026e-3)*100.0);

        out<<"\\hline"<<endl;
	out<<"Signal Model & "<<abs(round_to_digits(returnVar(systematic_sigmodel.c_str(),"SigModel_Run1","systematic"),2))<<" & "<< abs(round_to_digits(returnVar(systematic_sigmodel.c_str(),"SigModel_Run1","systematic"),2))<<" & "<<abs(round_to_digits(returnVar(systematic_sigmodel.c_str(),"SigModel_Run1","systematic"),2))<<"\\\\"<<endl;

        suminquad_2012.push_back(returnVar(systematic_sigmodel.c_str(),"SigModel_Run1","systematic"));
        suminquad_2016.push_back(returnVar(systematic_sigmodel.c_str(),"SigModel_Run1","systematic"));
        suminquad_overall.push_back(returnVar(systematic_sigmodel.c_str(),"SigModel_Run1","systematic"));


	out<<"Trigger & "<<abs(round_to_digits(returnVar(systematic_trigger.c_str(),"Trigger_Run1","systematic"),2))<<" & "<< abs(round_to_digits(returnVar(systematic_trigger.c_str(),"Trigger_2016","systematic"),2))<<"& "<<round_to_digits(addstatandsyst(returnVar(systematic_trigger.c_str(),"Trigger_Run1","systematic"),returnVar(systematic_trigger.c_str(),"Trigger_2016","systematic")),2)<<"\\\\"<<endl;


        suminquad_2012.push_back(returnVar(systematic_trigger.c_str(),"Trigger_Run1","systematic"));
        suminquad_2016.push_back(returnVar(systematic_trigger.c_str(),"Trigger_2016","systematic"));
	suminquad_overall.push_back(addstatandsyst(returnVar(systematic_trigger.c_str(),"Trigger_Run1","systematic"),returnVar(systematic_trigger.c_str(),"Trigger_2016","systematic")));

	out<<"Kinematic Reweighting & "<<abs(round_to_digits(returnVar(systematic_kinrew.c_str(),"KinRew_Run1_DataMCWeight2D_alt2_new","systematic"),2))<<" & "<< abs(round_to_digits(returnVar(systematic_kinrew.c_str(),"KinRew_2016_DataMCWeight2D_alt2_new","systematic"),2))<<" &"<< round_to_digits(addstatandsyst(returnVar(systematic_kinrew.c_str(),"KinRew_Run1_DataMCWeight2D_alt2_new","systematic"),returnVar(systematic_kinrew.c_str(),"KinRew_2016_DataMCWeight2D_alt2_new","systematic")),2)<<"\\\\"<<endl;


        suminquad_2012.push_back(returnVar(systematic_kinrew.c_str(),"KinRew_Run1_DataMCWeight2D_alt2_new","systematic"));
        suminquad_2016.push_back(returnVar(systematic_kinrew.c_str(),"KinRew_2016_DataMCWeight2D_alt2_new","systematic"));
        suminquad_overall.push_back(addstatandsyst(returnVar(systematic_kinrew.c_str(),"KinRew_Run1_DataMCWeight2D_alt2_new","systematic"),returnVar(systematic_kinrew.c_str(),"KinRew_2016_DataMCWeight2D_alt2_new","systematic")));

	out<<"Simulation statistics & "<<100*round_to_digits((0.000020/0.001581),2)<<" & "<<100*round_to_digits((0.000008/0.001182),2)<<" & "<<round_to_digits((addstatandsyst((0.000020/0.001581)*100.0,(0.000008/0.001182)*100.0)),2)<<" \\\\" <<endl;

        
        suminquad_2012.push_back((0.000020/0.001581)*100.0);
        suminquad_2016.push_back((0.000008/0.001182)*100.0);
	suminquad_overall.push_back(addstatandsyst((0.000020/0.001581)*100.0,(0.000008/0.001182)*100.0));
        
	out<<"Fit bias & 1.0 & 1.0 & 1.0 "<<" \\\\"<<endl;


        suminquad_2012.push_back(1.0);
        suminquad_2016.push_back(1.0);
        suminquad_overall.push_back(1.0);

	out<<" \\hline"<<endl;
	out<<" \\hline"<<endl;

        out<<" Total & "<<round_to_digits(addinquad(suminquad_2012),2)<<" & "<<round_to_digits(addinquad(suminquad_2016),2)<<" & "<<round_to_digits(addinquad(suminquad_overall),2)<<" \\\\"<<endl;
	out<<" \\hline"<<endl;
        out<<"Statistical source & Run 1/\\% & 2016/\\% & Error Overall \\\\ \\hline"<<endl;
	out<<" \\hline"<<endl;
        out<<"Error on $B^{+} \\rightarrow J/\\psi K^{+}$ yield & "<<abs(round_to_digits((returnVar(stat_2012.c_str(),"Info_2012","numofevents_err"))/((returnVar(stat_2012.c_str(),"Info_2012","numofevents"))),2))*100<<" & "<< abs(round_to_digits((returnVar(stat_2016.c_str(),"Info_2016","numofevents_err"))/((returnVar(stat_2016.c_str(),"Info_2016","numofevents"))),2))*100<<" & "<< round_to_digits(addstatandsyst(((returnVar(stat_2012.c_str(),"Info_2012","numofevents_err"))/((returnVar(stat_2012.c_str(),"Info_2012","numofevents"))))*100,((returnVar(stat_2016.c_str(),"Info_2016","numofevents_err"))/((returnVar(stat_2016.c_str(),"Info_2016","numofevents"))))*100),2)<<"\\\\"<<endl;

	out<<" \\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\caption{Summary of systematic uncertainties.}"<<endl;
	out<<"\\label{tab:systematicsummary}"<<endl;
	out<<"\\end{table}"<<endl;


//        variablestoplot.push_back("numofevents");
//        variablestoplot.push_back("numofevents_err");



//	out<<"\\begin{table}[H]"<<endl;
//	out<<"\\begin{center}"<<endl;
//	out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
//	out<<"\\hline"<<endl;
//	out<<"	Sample & Stripping & Split  &Yields \\\\"<<endl;
//	out<<"\\hline"<<endl;
//	out<<"	$N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 21+21r1 & NOFCME & "<<holder.at(8)<<"$\\pm$"<<holder.at(10)<<"  \\\\"<<endl;
//	out<<"	$N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 26 & NOFCME &"<<holder.at(9)<<"$\\pm$"<<holder.at(11)<<"  \\\\"<<endl;
//	out<<"\\hline"<<endl;
//	out<<"	$N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 21+21r1 & lowFCME & "<<holder.at(0)<<"$\\pm$"<<holder.at(4)<<"  \\\\"<<endl;
//	out<<" $N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 26 & lowFCME & "<<holder.at(1)<<"$\\pm$"<<holder.at(5)<<"  \\\\"<<endl;
//	out<<"\\hline"<<endl;
//	out<<"	$N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 21+21r1 & highFCME &"<<holder.at(2)<<"$\\pm$"<<holder.at(6)<<"  \\\\"<<endl;
//	out<<" $N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 26 & highFCME & "<<holder.at(3)<<"$\\pm$"<<holder.at(7)<<"  \\\\"<<endl;
//	out<<"\\hline"<<endl;
//	out<<"\\end{tabular}"<<endl;
//	out<<"\\end{center}"<<endl;
//	out<<"\\caption{Signal Yield $B^{+} \\rightarrow J/\\psi K^{+}$}"<<endl;
//	out<<"\\label{tab:normchannelyields}"<<endl;
//	out<<"\\end{table}"<<endl;


	out<<"\\end{document}"<<endl;

}
