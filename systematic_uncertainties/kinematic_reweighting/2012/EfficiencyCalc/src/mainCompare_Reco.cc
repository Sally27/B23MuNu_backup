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
#include "alltogetherMC.hpp"
#include "ValError.hpp"
#include<iostream>
#include<iomanip>

using namespace std;


int main(){


	vector<string> nameofweight;

	nameofweight.push_back("DataMCWeight2D");
	nameofweight.push_back("DataMCWeight2D_new");
	nameofweight.push_back("DataMCWeight2D_alt1");
	nameofweight.push_back("DataMCWeight2D_alt1_new");
	nameofweight.push_back("DataMCWeight2D_alt2");
	nameofweight.push_back("DataMCWeight2D_alt2_new");


	for (int z(0); z<nameofweight.size() ;z++)
	{

        string todo=nameofweight.at(z);




		int normalisation(1);
		int signal(1);
		ValError normalisation_nominal(0,0);
		ValError normalisation_reweight(0,0);
		ValError signal_nominal(0,0);
		ValError signal_reweight(0,0);





		if (normalisation==1)
		{
			ofstream out;
			out.open(("ComparisonNormMC_NormModelReweighted_"+todo+".tex").c_str());

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

			out<<"\\begin{table}[ht]"<<endl;
			out<<"\\begin{center}"<<endl;
			out<<"\\begin{tabular}{ l | l | l }"<<endl;
			out<<"\\hline"<<endl;
			out<<"\\hline"<<endl;

                        vector<int> years;
			years.push_back(2011);
			years.push_back(2012);
			years.push_back(2016);

			double number_bkk_sig(8043820.0);
			double decprodcutsig(0.16216);
			double decprodcutsig_err(0.00024);

			//	number_bkk_sig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "numbkk");
			//	decprodcutsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "decprodcut");

			double number_bkk_nor(number_bkk_sig);
			double decprodcutjpsik(0.16216);
			double decprodcutjpsik_err(0.00024);



			double toteff;

			double sigPID=0.7160;
			double jpsikPID=0.7160;



			TFile f_initial_sig("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root","READ");
			TTree* t_initial_sig =(TTree*)f_initial_sig.Get(("DecayTree"));

			TFile f_final_sig("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root","READ");
			TTree* t_final_sig =(TTree*)f_final_sig.Get(("DecayTree"));

			TFile f_initial_norm("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/runofflinestrip/norm/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_2D_misidstrippingfull.root","READ");
			TTree* t_initial_norm =(TTree*)f_initial_norm.Get(("DecayTree"));

			TFile f_final_norm("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/applybdtandothercuts/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_2D_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root","READ");
			TTree* t_final_norm =(TTree*)f_final_norm.Get(("DecayTree"));


			//---strings of files to investigate ---//
			vector<string> files_mine;
			vector<string> files_phsp;
			vector<string> cuts;   

			files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root");
			files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger.root");
			files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic.root");
			files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic.root");
			files_mine.push_back("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root");

			files_phsp.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/runofflinestrip/norm/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_2D_misidstrippingfull.root");
			files_phsp.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/runofflinestrip/norm/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_2D_misidstrippingfull_trigger.root");
			files_phsp.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/applybdtandothercuts/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_2D_misidstrippingfull_trigger_CombBasic.root");
			files_phsp.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/applybdtandothercuts/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_2D_misidstrippingfull_trigger_CombBasic_MisidBasic.root");
			files_phsp.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/applybdtandothercuts/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_2D_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root");

			cuts.push_back("trigger");
			cuts.push_back("combibdt");
			cuts.push_back("misidbdt");
			cuts.push_back("fitrange");
			cuts.push_back("all");



			//-------------Dec Prod Cut-------------------//

			ValError sig_decprod(decprodcutsig,decprodcutsig_err);
			ValError jpsik_decprod(decprodcutjpsik,decprodcutjpsik_err);


			//-------------Reco Efficiencies--------------//
			ValError sigy(double(t_initial_sig->GetEntries()),0);
			ValError sigz(number_bkk_sig,0);
			ValError normy(double(t_initial_norm->GetEntries()),0);
			ValError normz(number_bkk_nor,0);

			ValError sig_reco=getRatioBinomial(sigy,sigz);
			ValError jpsik_reco=getRatioBinomial(normy,normz);


			//-------------All other selection------------//

			ValError sig_othereff_passed(double(t_final_sig->GetEntries()),0);
			ValError jpsik_othereff_passed(double(getKinWeights_nameweight(files_phsp.back(),"DecayTree",todo)),0);

			ValError sig_othereff_total(double(t_initial_sig->GetEntries()),0);
			ValError jpsik_othereff_total(double(getKinWeights_nameweight(files_phsp.at(0),"DecayTree",todo)),0);

			ValError sig_othereff=getRatioBinomial(sig_othereff_passed,sig_othereff_total);
			ValError jpsik_othereff=getRatioBinomial(jpsik_othereff_passed,jpsik_othereff_total);

			//------------PID estuff no error so far-------//
			ValError sig_pid(sigPID,0);
			ValError jpsik_pid(jpsikPID,0);

			//--------decorprodcut-----------//
			ValError truedecsig(decprodcutsig,decprodcutsig_err);
			ValError truedecjpsik(decprodcutjpsik,decprodcutjpsik_err);



			//-------------Errors alltogether

			ValError finalprod_sig=sig_decprod*sig_othereff*sig_pid;
			ValError finalprod_jpsik=jpsik_decprod*jpsik_othereff*jpsik_pid;

			out << "Efficiency & "<< " $B^{+} \\rightarrow J\\psi\\ K^{+}$ (Nominal)  & " << " $B^{+} \\rightarrow J\\psi\\ K^{+}$ (Reweighted Jpsik weights) "<<" \\\\" <<endl;   
			out<<"\\hline"<<endl;
			out << "$\\epsilon_{decprodcut}$ &" << decprodcutsig << " & " << decprodcutjpsik <<" \\\\ "<<endl;
			out << "num bkk &" << number_bkk_sig << " & " << number_bkk_nor <<" \\\\ "<<endl;
			out << "num reco and mc truth &" << t_initial_sig->GetEntries() << " & " << t_initial_norm->GetEntries() <<" \\\\ "<<endl;
			out<<"\\hline"<<endl;
			out << "$\\epsilon_{reco+strip+mctruth}$ & "<<t_initial_sig->GetEntries()/number_bkk_sig <<" & "<< t_initial_norm->GetEntries()/number_bkk_nor<<" \\\\ "<<endl;
			out<<"\\hline"<<endl;
			out << "num  final &" <<t_final_sig->GetEntries()  << " & " << t_final_norm->GetEntries() <<" \\\\ "<<endl;
			out<<"\\hline"<<endl;
			for( int i(1); i<5; i++)
			{
				TFile f_sig_cut((files_mine.at(i-1)).c_str(),"READ");
				TTree* t_sig_cut =(TTree*)f_sig_cut.Get(("DecayTree"));
				TFile f_norm_cut((files_phsp.at(i-1)).c_str(),"READ");
				TTree* t_norm_cut =(TTree*)f_norm_cut.Get(("DecayTree"));

				TFile f_sig_cut_2((files_mine.at(i)).c_str(),"READ");
				TTree* t_sig_cut_2 =(TTree*)f_sig_cut_2.Get(("DecayTree"));
				TFile f_norm_cut_2((files_phsp.at(i)).c_str(),"READ");
				TTree* t_norm_cut_2 =(TTree*)f_norm_cut_2.Get(("DecayTree"));


				out << "$\\epsilon\\_{"+cuts.at(i-1)+"}$ & "<< double(t_sig_cut_2->GetEntries())/double(t_sig_cut->GetEntries()) << " & " << double(getKinWeights_nameweight((files_phsp.at(i)).c_str(),"DecayTree",todo))/double(getKinWeights_nameweight((files_phsp.at(i-1)).c_str(),"DecayTree",todo))<<" \\\\ "<<endl;
				f_sig_cut.Close();
				f_norm_cut.Close();
				f_sig_cut_2.Close();
				f_norm_cut_2.Close();
			}
			//        out << "$\\epsilon_{myreco}$ &" << effmyrecosig << " & " << effmyrecostrjpsik <<" \\\\ "<<endl;
			//        out << "$\\epsilon_{combibdt}$ &" << combibdtsig << " & " << combibdtjpsik <<" \\\\ "<<endl;
			//        out << "$\\epsilon_{misidbdt}$ &" << misidbdtsig << " & " << misidbdtjpsik <<" \\\\ "<<endl;
			//        out << "$\\epsilon_{corm}$ &" << cormsig << " & " << cormjpsik <<" \\\\ "<<endl;

			out<<"\\hline"<<endl;



			out<<"$\\epsilon\\_{alloffcuts}$ & "<<  sig_othereff.val <<" $\\pm$"<<sig_othereff.err<< " & "<< jpsik_othereff.val <<" $\\pm$"<<jpsik_othereff.err <<" \\\\ "<<endl;
			out<<"\\hline"<<endl;
			out << "$\\epsilon_{PID}$ &" << sigPID << " & " << jpsikPID <<" \\\\ "<<endl;
			out<<"\\hline"<<endl;
			out<<"$\\epsilon\\_{decprodcut}$ &"<<sig_decprod <<" & "<<jpsik_decprod<<" \\\\ "<<endl;
			out<<"$\\epsilon\\_{reco+strip+mctruth}$ & "<<t_initial_sig->GetEntries()/number_bkk_sig <<" & "<< t_initial_norm->GetEntries()/number_bkk_nor<<" \\\\ "<<endl;
			out<<"$\\epsilon\\_{offlinesel}$ &"<<sig_othereff <<" & "<<jpsik_othereff<<" \\\\ "<<endl;
			out<<"$\\epsilon\\_{pid}$ &"<<sig_pid <<" & "<<jpsik_pid<<" \\\\ "<<endl;
			out<<"\\hline"<<endl;
			out<<"$\\epsilon\\_{all}$ &"<<(truedecsig)*(sig_reco)*(sig_othereff)*(sig_pid) <<" & "<<(truedecjpsik)*(jpsik_reco)*(jpsik_othereff)*(jpsik_pid)<<" \\\\ "<<endl;

			ValError all_sig=(truedecsig)*(sig_reco)*(sig_othereff)*(sig_pid);
			ValError all_norm=(truedecjpsik)*(jpsik_reco)*(jpsik_othereff)*(jpsik_pid);


			out<<"\\hline"<<endl;
			out<<"\\end{tabular}"<<endl;
			out<<"\\end{center}"<<endl;
			out<<"\\caption{Comparison between my nominal Norm MC efficiencies and reweighted Norm MC efficiencies. Reweigting in B P , PT , IPchi2 and pointing has been used from normalisation sweighted data. In these efficiencies in nominal efficiencies of cuts are evaluated in reweighted MC sum of kinematic weights before and after are used. In reweighted MC efficiencies that change are after MC truth matching and misiidstripping (after reco) so all the efficiencies before that are unaccounted. Effect of reweighting is also not applied for PID calibration yet.}"<<endl;
			out<<"\\end{table}"<<endl;
			out<<"This is comparison"<<endl;


			out<<"Efficiency ratio decprodcut, i.e effmine/effrew is "<< truedecsig/truedecjpsik<<endl;
			out<<"\\newline"<<endl;
			out<<"Efficiency ratio reco+mc+truth, i.e effmine/effrew is "<< sig_reco/jpsik_reco<<endl;
			out<<"\\newline"<<endl;
			out<<"Efficiency ratio offlineeff, i.e effmine/effrew is "<< sig_othereff/jpsik_othereff<<endl;
			out<<"\\newline"<<endl;
			out<<"Efficiency ratio pid, i.e effmine/effrew is "<< sig_pid/jpsik_pid<<endl;
			out<<"\\newline"<<endl;
			out<<"Efficiency ratio Total, i.e effmine/effrew is "<< all_sig/all_norm<<endl;
			out<<"\\newline"<<endl;
			out<<"\\newline"<<endl;
			out<<"Sytematics from using reweighted model is "<<100.0*(all_sig-all_norm)/(all_sig)<<" \\%"<<endl;

			normalisation_nominal=all_sig;
			normalisation_reweight=all_norm;




			out<<"\\end{document}"<<endl;



			out.close();
		}


		if (signal==1)
		{  

			ofstream out;
			out.open(("ComparisonSignalMC_SignalModelReweighted_"+todo+".tex").c_str());

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

			out<<"Calculation of the Single Event Sensitivity"<<endl;
			out<<"\\begin{table}[ht]"<<endl;
			out<<"\\begin{center}"<<endl;
			out<<"\\begin{tabular}{ l | l | l }"<<endl;
			out<<"\\hline"<<endl;
			out<<"\\hline"<<endl;

			vector<int> years;
			years.push_back(2011);
			years.push_back(2012);
			years.push_back(2016);

			double number_bkk_sig(0);
			double decprodcutsig(0.18643);
			double decprodcutsig_err(0.00029);

			number_bkk_sig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "numbkk");
			//	decprodcutsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "decprodcut");

			double number_bkk_nor(number_bkk_sig);
			double decprodcutjpsik(0.18643);
			double decprodcutjpsik_err(0.00029);



			double toteff;

			double sigPID=0.64815;
			double jpsikPID=0.64815;



			TFile f_initial_sig("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/Bu23MuNuMC2012_MCtruth.root","READ");
			TTree* t_initial_sig =(TTree*)f_initial_sig.Get(("DecayTree"));

			TFile f_final_sig("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root","READ");
			TTree* t_final_sig =(TTree*)f_final_sig.Get(("DecayTree"));

			TFile f_initial_norm("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/runofflinestrip/sig/2012/bin/Bu23MuNuMC2012_MCtruth_2D.root","READ");
			TTree* t_initial_norm =(TTree*)f_initial_norm.Get(("DecayTree"));

			TFile f_final_norm("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/applybdtandothercuts/2012/bin/Bu23MuNuMC2012_MCtruth_2D_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root","READ");
			TTree* t_final_norm =(TTree*)f_final_norm.Get(("DecayTree"));


			//---strings of files to investigate ---//
			vector<string> files_mine;
			vector<string> files_phsp;
			vector<string> cuts;   

			files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/Bu23MuNuMC2012_MCtruth.root");
			files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger.root");
			files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi.root");
			files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root");
			files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic.root");
			files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic.root");
			files_mine.push_back("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root");


			files_phsp.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/runofflinestrip/sig/2012/bin/Bu23MuNuMC2012_MCtruth_2D.root");
			files_phsp.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/runofflinestrip/sig/2012/bin/Bu23MuNuMC2012_MCtruth_2D_L0MuonDecisionTOS_trigger.root");
			files_phsp.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/runofflinestrip/sig/2012/bin/Bu23MuNuMC2012_MCtruth_2D_L0MuonDecisionTOS_trigger_Jpsi.root");
			files_phsp.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/runofflinestrip/sig/2012/bin/Bu23MuNuMC2012_MCtruth_2D_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root");
			files_phsp.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/applybdtandothercuts/2012/bin/Bu23MuNuMC2012_MCtruth_2D_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic.root");
			files_phsp.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/applybdtandothercuts/2012/bin/Bu23MuNuMC2012_MCtruth_2D_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic.root");
			files_phsp.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/applybdtandothercuts/2012/bin/Bu23MuNuMC2012_MCtruth_2D_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root");

			cuts.push_back("trigger");
			cuts.push_back("Jpsi");
			cuts.push_back("qmincut");
			cuts.push_back("combibdt");
			cuts.push_back("misidbdt");
			cuts.push_back("fitrange");
			cuts.push_back("all");



			//-------------Dec Prod Cut-------------------//

			ValError sig_decprod(decprodcutsig,decprodcutsig_err);
			ValError jpsik_decprod(decprodcutjpsik,decprodcutjpsik_err);


			//-------------Reco Efficiencies--------------//
			ValError sigy(double(t_initial_sig->GetEntries()),0);
			ValError sigz(number_bkk_sig,0);
			ValError normy(double(t_initial_norm->GetEntries()),0);
			ValError normz(number_bkk_nor,0);

			ValError sig_reco=getRatioBinomial(sigy,sigz);
			ValError jpsik_reco=getRatioBinomial(normy,normz);


			//-------------All other selection------------//

			ValError sig_othereff_passed(double(t_final_sig->GetEntries()),0);
			ValError jpsik_othereff_passed(double(getKinWeights_nameweight(files_phsp.back(),"DecayTree",todo)),0);

			ValError sig_othereff_total(double(t_initial_sig->GetEntries()),0);
			ValError jpsik_othereff_total(double(getKinWeights_nameweight(files_phsp.at(0),"DecayTree",todo)),0);

			ValError sig_othereff=getRatioBinomial(sig_othereff_passed,sig_othereff_total);
			ValError jpsik_othereff=getRatioBinomial(jpsik_othereff_passed,jpsik_othereff_total);

			//------------PID estuff no error so far-------//
			ValError sig_pid(sigPID,0);
			ValError jpsik_pid(jpsikPID,0);

			//--------decorprodcut-----------//
			ValError truedecsig(decprodcutsig,decprodcutsig_err);
			ValError truedecjpsik(decprodcutjpsik,decprodcutjpsik_err);



			//-------------Errors alltogether

			ValError finalprod_sig=sig_decprod*sig_othereff*sig_pid;
			ValError finalprod_jpsik=jpsik_decprod*jpsik_othereff*jpsik_pid;

			out << "Efficiency & "<< " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ (Nominal)  & " << " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ (Reweighted Jpsik weights) "<<" \\\\" <<endl;   
			out<<"\\hline"<<endl;
			out << "$\\epsilon_{decprodcut}$ &" << decprodcutsig << " & " << decprodcutjpsik <<" \\\\ "<<endl;
			out << "num bkk &" << number_bkk_sig << " & " << number_bkk_nor <<" \\\\ "<<endl;
			out << "num reco and mc truth &" << t_initial_sig->GetEntries() << " & " << t_initial_norm->GetEntries() <<" \\\\ "<<endl;
			out<<"\\hline"<<endl;
			out << "$\\epsilon_{reco+strip+mctruth}$ & "<<t_initial_sig->GetEntries()/number_bkk_sig <<" & "<< t_initial_norm->GetEntries()/number_bkk_nor<<" \\\\ "<<endl;
			out<<"\\hline"<<endl;
			out << "num  final &" <<t_final_sig->GetEntries()  << " & " << t_final_norm->GetEntries() <<" \\\\ "<<endl;
			out<<"\\hline"<<endl;
			for( int i(1); i<7; i++)
			{
				TFile f_sig_cut((files_mine.at(i-1)).c_str(),"READ");
				TTree* t_sig_cut =(TTree*)f_sig_cut.Get(("DecayTree"));
				TFile f_norm_cut((files_phsp.at(i-1)).c_str(),"READ");
				TTree* t_norm_cut =(TTree*)f_norm_cut.Get(("DecayTree"));

				TFile f_sig_cut_2((files_mine.at(i)).c_str(),"READ");
				TTree* t_sig_cut_2 =(TTree*)f_sig_cut_2.Get(("DecayTree"));
				TFile f_norm_cut_2((files_phsp.at(i)).c_str(),"READ");
				TTree* t_norm_cut_2 =(TTree*)f_norm_cut_2.Get(("DecayTree"));


				out << "$\\epsilon\\_{"+cuts.at(i-1)+"}$ & "<< double(t_sig_cut_2->GetEntries())/double(t_sig_cut->GetEntries()) << " & " << double(getKinWeights_nameweight((files_phsp.at(i)).c_str(),"DecayTree",todo))/double(getKinWeights_nameweight((files_phsp.at(i-1)).c_str(),"DecayTree",todo))<<" \\\\ "<<endl;
				f_sig_cut.Close();
				f_norm_cut.Close();
				f_sig_cut_2.Close();
				f_norm_cut_2.Close();
			}

			out<<"\\hline"<<endl;



			out<<"$\\epsilon\\_{alloffcuts}$ & "<<  sig_othereff.val <<" $\\pm$"<<sig_othereff.err<< " & "<< jpsik_othereff.val <<" $\\pm$"<<jpsik_othereff.err <<" \\\\ "<<endl;
			out<<"\\hline"<<endl;
			out << "$\\epsilon_{PID}$ &" << sigPID << " & " << jpsikPID <<" \\\\ "<<endl;
			out<<"\\hline"<<endl;
			out<<"$\\epsilon\\_{decprodcut}$ &"<<sig_decprod <<" & "<<jpsik_decprod<<" \\\\ "<<endl;
			out<<"$\\epsilon\\_{reco+strip+mctruth}$ & "<<t_initial_sig->GetEntries()/number_bkk_sig <<" & "<< t_initial_norm->GetEntries()/number_bkk_nor<<" \\\\ "<<endl;
			out<<"$\\epsilon\\_{offlinesel}$ &"<<sig_othereff <<" & "<<jpsik_othereff<<" \\\\ "<<endl;
			out<<"$\\epsilon\\_{pid}$ &"<<sig_pid <<" & "<<jpsik_pid<<" \\\\ "<<endl;
			out<<"\\hline"<<endl;
			out<<"$\\epsilon\\_{all}$ &"<<(truedecsig)*(sig_reco)*(sig_othereff)*(sig_pid) <<" & "<<(truedecjpsik)*(jpsik_reco)*(jpsik_othereff)*(jpsik_pid)<<" \\\\ "<<endl;

			ValError all_sig=(truedecsig)*(sig_reco)*(sig_othereff)*(sig_pid);
			ValError all_norm=(truedecjpsik)*(jpsik_reco)*(jpsik_othereff)*(jpsik_pid);


			out<<"\\hline"<<endl;
			out<<"\\end{tabular}"<<endl;
			out<<"\\end{center}"<<endl;
			out<<"\\caption{Comparison between my nominal MC efficiencies and reweghted MC efficiencies. Reweigting in B P , PT , IPchi2 and pointing has been used from normalisation Channel. In these efficiencies in nominal efficiencies of cuts are evaluated in reweighted MC sum of kinematic weights before and after are used. In reweighted MC efficiencies that change are after MC truth matching so all the efficiencies before that are unaccounted. Effect of reweighting is also not applied for PID calibration yet.}"<<endl;
			out<<"\\end{table}"<<endl;
			out<<"This is comparison"<<endl;


			out<<"Efficiency ratio decprodcut, i.e effmine/effrew is "<< truedecsig/truedecjpsik<<endl;
			out<<"\\newline"<<endl;
			out<<"Efficiency ratio reco+mc+truth, i.e effmine/effrew is "<< sig_reco/jpsik_reco<<endl;
			out<<"\\newline"<<endl;
			out<<"Efficiency ratio offlineeff, i.e effmine/effrew is "<< sig_othereff/jpsik_othereff<<endl;
			out<<"\\newline"<<endl;
			out<<"Efficiency ratio pid, i.e effmine/effrew is "<< sig_pid/jpsik_pid<<endl;
			out<<"\\newline"<<endl;
			out<<"Efficiency ratio Total, i.e effmine/effrew is "<< all_sig/all_norm<<endl;
			out<<"\\newline"<<endl;
			out<<"\\newline"<<endl;
			out<<"Sytematics from using reweighted model is "<<100.0*(all_sig-all_norm)/(all_sig)<<" \\%"<<endl;

			signal_nominal=all_sig;
			signal_reweight=all_norm;
			out<<"\\end{document}"<<endl;



			out.close();
		}


		ofstream out2;
		out2.open(("ImpactOnEffRatio"+todo+".tex").c_str());

		out2<<"\\documentclass[a4paper,11pt]{article}"<<endl;
		out2<<"\\usepackage[pdftex]{graphicx}"<<endl;
		out2<<"\\usepackage{url}"<<endl;
		out2<<"\\usepackage{mathtools}"<<endl;
		out2<<"\\usepackage{amsmath}"<<endl;
		out2<<"\\usepackage{graphicx}"<<endl;
		out2<<"\\usepackage[table]{xcolor}"<<endl;
		out2<<"\\usepackage{amsmath,amssymb}"<<endl;
		out2<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
		out2<<"\\usepackage{colortbl}"<<endl;
		out2<<"\\begin{document}"<<endl;
		out2<<"Efficiency ratio sig\\_nominal/norm\\_nominal is "<< signal_nominal/normalisation_nominal<<endl;
		out2<<"\\newline"<<endl;
		out2<<"Efficiency ratio sig\\_reweighted/norm\\_reweighted is "<< signal_reweight/normalisation_reweight<<endl;
		out2<<"\\newline"<<endl;
		out2<<"Hence systematic is "<< 100.0*((signal_nominal/normalisation_nominal)-(signal_reweight/normalisation_reweight))/(signal_nominal/normalisation_nominal)<<endl;
		out2<<"\\end{document}"<<endl;



		out2.close();

	}

		return(0);
}



