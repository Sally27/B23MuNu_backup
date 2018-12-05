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

        ofstream out;
        out.open("ComparisonSignalMC_SignalModelReweighted_TRUEPANDPT.tex");

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
        ValError jpsik_othereff_passed(double(getKinWeights(files_phsp.back(),"DecayTree")),0);

        ValError sig_othereff_total(double(t_initial_sig->GetEntries()),0);
        ValError jpsik_othereff_total(double(getKinWeights(files_phsp.at(0),"DecayTree")),0);

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

        
        out << "$\\epsilon\\_{"+cuts.at(i-1)+"}$ & "<< double(t_sig_cut_2->GetEntries())/double(t_sig_cut->GetEntries()) << " & " << double(getKinWeights((files_phsp.at(i)).c_str(),"DecayTree"))/double(getKinWeights((files_phsp.at(i-1)).c_str(),"DecayTree"))<<" \\\\ "<<endl;
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
 
//getRatioBinomial(double(t_initial_norm_ORI->GetEntries()),number_bkk_nor)
//getRatioBinomial(double(t_initial_sig_ORI->GetEntries()),number_bkk_sig)
//	double brfr=1e-8;
//	double ppbbX=284e-6;
//	double bBplus= 2*0.4;
//	double datacoll=3e15;
//	double decprodcut =0.185;
//	double effrecostrip= 0.111;

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

//	TFile fillinfo("info_SES.root","UPDATE");
//	TTree fillinfotree("Info_2012","Info_2012");
//
//        double year;
//        double numofevents;
//        double effi_sig;
//        double effi_norm;
//        double sensitivity;
//        double effi_ratio;
//        double effi_numobs;
//        double luminosity;
//        double numofevents_per_lumi;
//        double effi_corr_lumi;
//
//
//        double effi_gen_sig;
//        double effi_gen_norm;
//        double effi_rec_sig;
//        double effi_rec_norm;
//        double effi_off_sig;
//        double effi_off_norm;
//        double effi_combi_sig;
//        double effi_combi_norm;
//        double effi_misid_sig;
//        double effi_misid_norm;
//        double effi_corm_sig;
//        double effi_corm_norm;
//        double effi_pid_sig;
//        double effi_pid_norm;
//
//
//	fillinfotree.Branch("year",&year,"year/D");// "File/C");
//	fillinfotree.Branch("numofevents",&numofevents,"numofevents/D");// "Cut/C");
//	fillinfotree.Branch("effi_sig",&effi_sig,"effi_sig/D");
//	fillinfotree.Branch("effi_norm",&effi_norm, "effi_norm/D");
//	fillinfotree.Branch("sensitivity",&sensitivity, "sensitivity/D");
//        fillinfotree.Branch("effi_ratio",&effi_ratio, "effi_ratio/D");
//        fillinfotree.Branch("effi_numobs",&effi_numobs, "effi_numobs/D");
//        fillinfotree.Branch("luminosity",&luminosity, "luminosity/D");
//        fillinfotree.Branch("numofevents_per_lumi",&numofevents_per_lumi, "numofevents_per_lumi/D");
//        fillinfotree.Branch("effi_corr_lumi",&effi_corr_lumi, "effi_corr_lumi/D");
//        
//        fillinfotree.Branch("effi_gen_sig",&effi_gen_sig, "effi_gen_sig/D");
//        fillinfotree.Branch("effi_gen_norm",&effi_gen_norm, "effi_gen_norm/D");
//
//        fillinfotree.Branch("effi_rec_sig",&effi_rec_sig, "effi_rec_sig/D");
//        fillinfotree.Branch("effi_rec_norm",&effi_rec_norm, "effi_rec_norm/D");
//
//	fillinfotree.Branch("effi_off_sig",&effi_off_sig, "effi_off_sig/D");
//	fillinfotree.Branch("effi_off_norm",&effi_off_norm, "effi_off_norm/D");
//
//        fillinfotree.Branch("effi_combi_sig",&effi_combi_sig, "effi_combi_sig/D");
//        fillinfotree.Branch("effi_combi_norm",&effi_combi_norm, "effi_combi_norm/D");
//
//        fillinfotree.Branch("effi_misid_sig",&effi_misid_sig, "effi_misid_sig/D");
//        fillinfotree.Branch("effi_misid_norm",&effi_misid_norm, "effi_misid_norm/D");
//
//        fillinfotree.Branch("effi_corm_sig",&effi_corm_sig, "effi_corm_sig/D");
//        fillinfotree.Branch("effi_corm_norm",&effi_corm_norm, "effi_corm_norm/D");
//
//        fillinfotree.Branch("effi_pid_sig",&effi_pid_sig, "effi_pid_sig/D");
//        fillinfotree.Branch("effi_pid_norm",&effi_pid_norm, "effi_pid_norm/D");
//        
//
//
//        year=2012.0;
//        luminosity=2968.0;
//        numofevents_per_lumi=double(numberofobsevents.val/luminosity);
//        numofevents=numberofobsevents.val;
//        effi_sig=finalprod_sig.val;
//        effi_norm=finalprod_jpsik.val;
//        sensitivity=newses.val;
//	effi_ratio=double(finalprod_jpsik.val/finalprod_sig.val);
//	effi_numobs=double(finalprod_jpsik.val/(finalprod_sig.val*numberofobsevents.val));
//	effi_corr_lumi=double(numberofobsevents.val/(finalprod_jpsik.val*luminosity));
//        effi_gen_sig=decprodcutsig;
//        effi_gen_norm=decprodcutjpsik;
//        effi_rec_sig=effrecostrsig;
//        effi_rec_norm=effrecostrjpsik;
//        effi_off_sig=effmyrecosig;
//        effi_off_norm=effmyrecostrjpsik;
//        effi_combi_sig=combibdtsig;
//        effi_combi_norm=combibdtjpsik;
//        effi_misid_sig=misidbdtsig;
//        effi_misid_norm=misidbdtjpsik;
//        effi_corm_sig=cormsig;
//        effi_corm_norm=cormjpsik;
//        effi_pid_sig=sigPID;
//        effi_pid_norm=jpsikPID;
//        fillinfotree.Fill();
//	fillinfotree.Write("",TObject::kOverwrite);


 
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



