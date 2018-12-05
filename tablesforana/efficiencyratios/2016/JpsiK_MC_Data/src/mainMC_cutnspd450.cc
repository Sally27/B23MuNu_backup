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


int main(int argc,char* argv[]){

        Int_t tcks[] = {287905280,287905283,287905284,287905285,288495113,288626185,288691721,288757257,288822793,288822798,288888329,288888334,288888335,288888337,288888338,288888339};

        vector<Int_t> mytcks(tcks, tcks+sizeof(tcks)/ sizeof(Int_t) );

        string PIDcut=argv[1];
        string PIDcut2016=argv[2];
        int z(12);

        ofstream out;
        out.open(("Information_"+PIDcut+"_FULL_ERRORS_JPSIK2012and2016MC_nSPD_nice.tex").c_str());

	out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
	out<<"\\usepackage[pdftex]{graphicx}"<<endl;
	out<<"\\usepackage{url}"<<endl;
	out<<"\\usepackage{mathtools}"<<endl;
	out<<"\\usepackage{amsmath}"<<endl;
	out<<"\\usepackage{graphicx}"<<endl;
	out<<"\\usepackage[table]{xcolor}"<<endl;
	out<<"\\usepackage{amsmath,amssymb}"<<endl;
	out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
	out<<"\\usepackage{lscape}"<<endl;
        out<<"\\usepackage{colortbl}"<<endl;
	out<<"\\begin{document}"<<endl;
        
        out<<"Calculation of the $J/\\psi$ K differences between 2011 and 2012 and 2016 MC"<<endl;
        out<<"\\begin{landscape}"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\small"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{ l | l | l | l | l | l }"<<endl;
        out<<"\\hline"<<endl;
        out<<"\\hline"<<endl;

        vector<int> years;
        years.push_back(2011);
        years.push_back(2012);
        years.push_back(2016);

	double number_bkk_sig(4074487);
	double number_bkk_nor(0);
        double number_bkk_nor2016(0);
        number_bkk_nor=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "numbkk");
        number_bkk_nor2016=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "numbkk");


	double decprodcutsig(0.15921);
	double decprodcutsig_err(0.00015);

	double decprodcutjpsik(0.16216);
        double decprodcutjpsik_err(0.00024);


	double decprodcutjpsik2016(0.1739);
        double decprodcutjpsik2016_err(0.0004);
 

	TFile f_initial_sig("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2011/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull.root","READ");
	TTree* t_initial_sig =(TTree*)f_initial_sig.Get(("DecayTree"));

	TFile f_final_sig("/vols/lhcb/ss4314/cutonFitRange/FUMSB_simultaneous_NewTCK/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root","READ");
	TTree* t_final_sig =(TTree*)f_final_sig.Get(("DecayTree"));

	TFile f_initial_norm("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root","READ");
	TTree* t_initial_norm =(TTree*)f_initial_norm.Get(("DecayTree"));

	TFile f_final_norm("/vols/lhcb/ss4314/cutonFitRange/FUMSB_simultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root","READ");
	TTree* t_final_norm =(TTree*)f_final_norm.Get(("DecayTree"));
 
	TFile f_initial_norm2016("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull.root","READ");
	TTree* t_initial_norm2016 =(TTree*)f_initial_norm2016.Get(("DecayTree"));

	TFile f_final_norm2016(("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(12))+"_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic_FitCorM.root").c_str(),"READ");
	TTree* t_final_norm2016 =(TTree*)f_final_norm2016.Get(("DecayTree"));

        //-------------Dec Prod Cut-------------------//

        ValError sig_decprod(decprodcutsig,decprodcutsig_err);
        ValError jpsik_decprod(decprodcutjpsik,decprodcutjpsik_err);
        ValError jpsik2016_decprod(decprodcutjpsik2016,decprodcutjpsik2016_err);
        
        

        //-------------All other selection------------//

        ValError sig_othereff_passed(double(t_final_sig->GetEntries()),sqrt(double(t_final_sig->GetEntries())));
        ValError jpsik_othereff_passed(double(t_final_norm->GetEntries()),sqrt(double(t_final_norm->GetEntries())));
        ValError jpsik2016_othereff_passed(double(t_final_norm2016->GetEntries()),sqrt(double(t_final_norm2016->GetEntries())));

        ValError sig_othereff_total(number_bkk_sig,sqrt(number_bkk_sig));
        ValError jpsik_othereff_total(number_bkk_nor,sqrt(number_bkk_nor));
        ValError jpsik2016_othereff_total(number_bkk_nor2016,sqrt(number_bkk_nor2016));

        ValError sig_othereff=getRatioBinomial(sig_othereff_passed,sig_othereff_total);
        ValError jpsik_othereff=getRatioBinomial(jpsik_othereff_passed,jpsik_othereff_total);
        ValError jpsik2016_othereff=getRatioBinomial(jpsik2016_othereff_passed,jpsik2016_othereff_total);

         //Reco for jpsiK 2011//
         ValError sig_initial(double(t_initial_sig->GetEntries()),sqrt(double(t_initial_sig->GetEntries())));
         ValError sig_reco=getRatioBinomial(sig_initial,sig_othereff_total);
         //Reco for jpsiK 2012//
         ValError jpsik_initial(double(t_initial_norm->GetEntries()),sqrt(double(t_initial_norm->GetEntries())));
         ValError jpsik_reco=getRatioBinomial(jpsik_initial,jpsik_othereff_total);
         //Reco for jpsiK 2016//
         ValError jpsik2016_initial(double(t_initial_norm2016->GetEntries()),sqrt(double(t_initial_norm2016->GetEntries())));
         ValError jpsik2016_reco=getRatioBinomial(jpsik2016_initial,jpsik2016_othereff_total);


        //------------PID estuff no error so far-------//
        ValError sig_pid(readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2011"+PIDcut+".root").c_str(), "DecayTree", "mcweight"),0.0010);
        ValError jpsik_pid(readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2012"+PIDcut+".root").c_str(), "DecayTree", "mcweight"),0.0011);
        ValError jpsik2016_pid(readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2016"+PIDcut2016+".root").c_str(), "DecayTree", "mcweight"),0.0010);


        //-------------Errors alltogether

        ValError finalprod_sig=sig_decprod*sig_othereff*sig_pid;//*sig_pid;
        ValError finalprod_jpsik=jpsik_decprod*jpsik_othereff*jpsik_pid;//*jpsik_pid;
        ValError finalprod_jpsik2016=jpsik2016_decprod*jpsik2016_othereff*jpsik2016_pid;//*jpsik2016_pid;
 
        out << "Efficiency & "<< " $B^{+} \\rightarrow J/\\psi\\ K^{+}$  2011 & " << " $B^{+} \\rightarrow J/\\psi\\ K^{+}$ 2012 & "<<" $B^{+} \\rightarrow J/\\psi\\ K^{+}$ 2016 & "<<" Ratio (2012/2011)" <<" & Ratio (2016/2012) "<<" \\\\" <<endl;   
        out<<"\\hline"<<endl;
   

//        vector<string> files_2011;
        vector<string> files_mine;
        vector<string> files_norm;
        vector<string> files_norm2016;
        vector<string> cuts;

        cutTree("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root", "DecayTree", "MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_nSPD450.root", "nSPDHits<450");
 
        cutTree("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root", "DecayTree", "MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_nSPD450.root", "nSPDHits<450");

        files_mine.push_back("/vols/lhcb/ss4314/final_tuples/mc/norm_mc/2011/MC_B2JpsiK_2011.root");
        files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2011/bin/MC_B2JpsiK_2011MCTruth.root");
        files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2011/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull.root");
        files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2011/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger.root");
        files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2011/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger.root");
        files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger_CombBasic.root");
        files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger_CombBasic_MisidBasic.root");
        files_mine.push_back("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root");

        files_mine.push_back("MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_nSPD450.root");



        files_norm.push_back("/vols/lhcb/ss4314/final_tuples/mc/norm_mc/2012/MC_B2JpsiK_2012.root");
        files_norm.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth_.root");
        files_norm.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root");
        files_norm.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger.root");
        files_norm.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger.root");
        files_norm.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic.root");
        files_norm.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic.root");
        files_norm.push_back("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root");

        files_norm.push_back("MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_nSPD450.root");

 //      Int_t tcks[] = {287905280,287905283,287905284,287905285,288495113,288626185,288691721,288757257,288822793,288822798,288888329,288888334,288888335,288888337,288888338,288888339};

   //     vector<Int_t> mytcks(tcks, tcks+sizeof(tcks)/ sizeof(Int_t) );

	files_norm2016.push_back("/vols/lhcb/ss4314/final_tuples/mc/norm_mc/2016/B2JpsiKMC2016.root");
	files_norm2016.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth.root");
	files_norm2016.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull.root");
	files_norm2016.push_back(("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger.root").c_str());
	files_norm2016.push_back(("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger.root").c_str());
	files_norm2016.push_back(("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_CombBasic.root").c_str());
	files_norm2016.push_back(("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic.root").c_str());
	files_norm2016.push_back(("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic_FitCorM.root").c_str());

	files_norm2016.push_back(("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic_FitCorM.root").c_str());

     //   ValError jpsik_rec

        cuts.push_back("mctruth");
        cuts.push_back("misidstripping");
        cuts.push_back("TRG");
        cuts.push_back("OFF");
        cuts.push_back("CombiBDT");
        cuts.push_back("MisidBDT");
        cuts.push_back("FR");
        cuts.push_back("nSPD");
        cuts.push_back("all");

        vector<string> decaytreename;
        decaytreename.push_back("B2JpsiK_Tuple/DecayTree");
        decaytreename.push_back("DecayTree");
        decaytreename.push_back("DecayTree");
        decaytreename.push_back("DecayTree");
        decaytreename.push_back("DecayTree");
        decaytreename.push_back("DecayTree");
        decaytreename.push_back("DecayTree");
        decaytreename.push_back("DecayTree");
        decaytreename.push_back("DecayTree");


         //Stripping only for jpsiK 2011//

	TFile f_sig_cut_strip((files_mine.at(0)).c_str(),"READ");
	TTree* t_sig_cut_strip =(TTree*)f_sig_cut_strip.Get((decaytreename.at(0)).c_str());

	TFile f_norm_cut_strip((files_norm.at(0)).c_str(),"READ");
	TTree* t_norm_cut_strip =(TTree*)f_norm_cut_strip.Get((decaytreename.at(0).c_str()));

	TFile f_norm2016_cut_strip((files_norm2016.at(0)).c_str(),"READ");
	TTree* t_norm2016_cut_strip =(TTree*)f_norm2016_cut_strip.Get((decaytreename.at(0).c_str()));

         //Stripping only for jpsiK 2011//
         ValError sig_initial_strip(double(t_sig_cut_strip->GetEntries()),sqrt(double(t_sig_cut_strip->GetEntries())));
         ValError sig_reco_strip=getRatioBinomial(sig_initial_strip,sig_othereff_total);
         //Stripping only for jpsiK 2012//
         ValError jpsik_initial_strip(double(t_norm_cut_strip->GetEntries()),sqrt(double(t_norm_cut_strip->GetEntries())));
         ValError jpsik_reco_strip=getRatioBinomial(jpsik_initial_strip,jpsik_othereff_total);
         //Stripping only for jpsiK 2016//
         ValError jpsik2016_initial_strip(double(t_norm2016_cut_strip->GetEntries()),sqrt(double(t_norm2016_cut_strip->GetEntries())));
         ValError jpsik2016_reco_strip=getRatioBinomial(jpsik2016_initial_strip,jpsik2016_othereff_total);


        out<<"\\hline"<<endl;
        out << "Number in bkk & "<<number_bkk_sig<< " & " << number_bkk_nor<<" & " << number_bkk_nor2016<<" & "<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\varepsilon_{GEN}$ & "<<printnice(sig_decprod)<< " & " << printnice(jpsik_decprod)<<" & "<< printnice(jpsik2016_decprod)<<" & "<<printnice(jpsik_decprod/sig_decprod)<<" & "<<printnice(jpsik2016_decprod/jpsik_decprod)<<" \\\\ "<<endl;
       out << "$\\varepsilon_{REC}$ & "<<printnice(sig_reco)<< " & " << printnice(jpsik_reco)<<" & "<<printnice(jpsik2016_reco)<<" &"<< printnice(jpsik_reco/sig_reco)<<"& "<<printnice(jpsik2016_reco/jpsik_reco)<<" \\\\ "<<endl;
        out << "$\\varepsilon_{striponly}$ & "<<printnice(sig_reco_strip)<< " & " << printnice(jpsik_reco_strip)<<" & "<<printnice(jpsik2016_reco_strip)<<" & "<< printnice(jpsik_reco_strip/sig_reco_strip)<<" & "<< printnice(jpsik2016_reco_strip/jpsik_reco_strip)<<" \\\\ "<<endl;
  
	vector<ValError> signal_efficiencies;
        vector<ValError> jpsik_efficiencies;
        vector<ValError> jpsik2016_efficiencies;

	for( int i(1); i<9; i++)
	{
		TFile f_sig_cut((files_mine.at(i-1)).c_str(),"READ");
		TTree* t_sig_cut =(TTree*)f_sig_cut.Get((decaytreename.at(i-1)).c_str());

		TFile f_norm_cut((files_norm.at(i-1)).c_str(),"READ");
		TTree* t_norm_cut =(TTree*)f_norm_cut.Get((decaytreename.at(i-1).c_str()));

		TFile f_norm2016_cut((files_norm2016.at(i-1)).c_str(),"READ");
		TTree* t_norm2016_cut =(TTree*)f_norm2016_cut.Get((decaytreename.at(i-1).c_str()));

		TFile f_sig_cut_2((files_mine.at(i)).c_str(),"READ");
		TTree* t_sig_cut_2 =(TTree*)f_sig_cut_2.Get(((decaytreename.at(i)).c_str()));

		TFile f_norm_cut_2((files_norm.at(i)).c_str(),"READ");
		TTree* t_norm_cut_2 =(TTree*)f_norm_cut_2.Get(((decaytreename.at(i)).c_str()));

		TFile f_norm2016_cut_2((files_norm2016.at(i)).c_str(),"READ");
		TTree* t_norm2016_cut_2 =(TTree*)f_norm2016_cut_2.Get(((decaytreename.at(i)).c_str()));



                ValError sig_passes(double(t_sig_cut_2->GetEntries()),sqrt(double(t_sig_cut_2->GetEntries())));
                ValError jpsik_passes(double(t_norm_cut_2->GetEntries()),sqrt(double(t_norm_cut_2->GetEntries())));
                ValError jpsik2016_passes(double(t_norm2016_cut_2->GetEntries()),sqrt(double(t_norm2016_cut_2->GetEntries())));

                ValError sig_tots(double(t_sig_cut->GetEntries()),sqrt(double(t_sig_cut->GetEntries())));
                ValError jpsik_tots(double(t_norm_cut->GetEntries()),sqrt(double(t_norm_cut->GetEntries())));
                ValError jpsik2016_tots(double(t_norm2016_cut->GetEntries()),sqrt(double(t_norm2016_cut->GetEntries())));

                ValError sig_effs=getRatioBinomial(sig_passes,sig_tots);
                ValError jpsik_effs=getRatioBinomial(jpsik_passes,jpsik_tots);
                ValError jpsik2016_effs=getRatioBinomial(jpsik2016_passes,jpsik2016_tots);


		out << "$\\varepsilon_{"+cuts.at(i-1)+"}$ & "<<printnice(sig_effs)<< " & " << printnice(jpsik_effs)<< " & "<<printnice(jpsik2016_effs)<<" & "<< printnice(jpsik_effs/sig_effs)<<" & "<<printnice(jpsik2016_effs/jpsik_effs)<<" \\\\ "<<endl;

                signal_efficiencies.push_back(sig_effs);
                jpsik_efficiencies.push_back(jpsik_effs);
                jpsik2016_efficiencies.push_back(jpsik2016_effs);

		f_sig_cut.Close();
		f_norm_cut.Close();
		f_sig_cut_2.Close();
		f_norm_cut_2.Close();
		f_norm2016_cut.Close();
		f_norm2016_cut_2.Close();

	}


        out << "$\\varepsilon_{PID}$ & "<<printnice(sig_pid)<< " & " << printnice(jpsik_pid)<< " & "<<printnice(jpsik2016_pid)<<" & "<< printnice(jpsik_pid/sig_pid)<<" & "<<printnice(jpsik2016_pid/jpsik_pid)<<" \\\\ "<<endl;
        out<<"$\\varepsilon_{total}$ &"<<printnice(finalprod_sig)<<" & "<<printnice(finalprod_jpsik)<< " & "<<printnice(finalprod_jpsik2016)<< " & "<< printnice(finalprod_jpsik/finalprod_sig)<<" & "<<printnice(finalprod_jpsik2016/finalprod_jpsik)<<" \\\\ "<<endl;

        out<<"\\hline"<<endl;
        out<<" Ratios & -  &$\\epsilon^{2012}_{tot}/\\epsilon^{2011}_{tot}$= "<<printnice(finalprod_jpsik/finalprod_sig)<<" & "<<"$\\epsilon^{2016}_{tot}/\\epsilon^{2012}_{tot}$="<<printnice(finalprod_jpsik2016/finalprod_jpsik)<<" \\\\ "<<endl;

        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Efficiency differences. /vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/JpsiK\\_MC\\_Data}"<<endl;
        out<<"\\end{table}"<<endl;

        out<<"\\end{landscape}"<<endl;




	TFile fillinfo(("../info/info_SES_new_"+PIDcut+"_FULL_ERROR.root").c_str(),"UPDATE");
	TTree fillinfotree("Info_2011","Info_2011");

        double year;
        double numofevents;
        double numofevents_err;

        double effi_sig;
        double effi_norm;

        double effi_err_sig;
        double effi_err_norm;
      
        double sensitivity;
        double sensitivity_err;
        double effi_ratio;
        double effi_numobs;
        double luminosity;
        double numofevents_per_lumi;
        double effi_corr_lumi;


        double effi_gen_sig;
        double effi_gen_norm;

        double effi_rec_sig;
        double effi_rec_norm;

        double effi_trg_sig;
        double effi_trg_norm;

        double effi_off_sig;
        double effi_off_norm;

        double effi_combi_sig;
        double effi_combi_norm;

        double effi_misid_sig;
        double effi_misid_norm;

        double effi_corm_sig;
        double effi_corm_norm;

        double effi_pid_sig;
        double effi_pid_norm;

        double effi_err_gen_sig;
        double effi_err_gen_norm;

        double effi_err_rec_sig;
        double effi_err_rec_norm;

        double effi_err_trg_sig;
        double effi_err_trg_norm;

        double effi_err_off_sig;
        double effi_err_off_norm;

        double effi_err_combi_sig;
        double effi_err_combi_norm;

        double effi_err_misid_sig;
        double effi_err_misid_norm;

        double effi_err_corm_sig;
        double effi_err_corm_norm;

        double effi_err_pid_sig;
        double effi_err_pid_norm;

	fillinfotree.Branch("year",&year,"year/D");// "File/C");
	fillinfotree.Branch("numofevents",&numofevents,"numofevents/D");// "Cut/C");
	fillinfotree.Branch("numofevents_err",&numofevents_err,"numofevents_err/D");// "Cut/C");

	fillinfotree.Branch("effi_sig",&effi_sig,"effi_sig/D");
	fillinfotree.Branch("effi_norm",&effi_norm, "effi_norm/D");

	fillinfotree.Branch("effi_err_sig",&effi_err_sig,"effi_err_sig/D");
	fillinfotree.Branch("effi_err_norm",&effi_err_norm, "effi_err_norm/D");

	fillinfotree.Branch("sensitivity",&sensitivity, "sensitivity/D");
	fillinfotree.Branch("sensitivity_err",&sensitivity_err, "sensitivity_err/D");
        fillinfotree.Branch("effi_ratio",&effi_ratio, "effi_ratio/D");
        fillinfotree.Branch("effi_numobs",&effi_numobs, "effi_numobs/D");
        fillinfotree.Branch("luminosity",&luminosity, "luminosity/D");
        fillinfotree.Branch("numofevents_per_lumi",&numofevents_per_lumi, "numofevents_per_lumi/D");
        fillinfotree.Branch("effi_corr_lumi",&effi_corr_lumi, "effi_corr_lumi/D");
        
        fillinfotree.Branch("effi_gen_sig",&effi_gen_sig, "effi_gen_sig/D");
        fillinfotree.Branch("effi_gen_norm",&effi_gen_norm, "effi_gen_norm/D");

        fillinfotree.Branch("effi_rec_sig",&effi_rec_sig, "effi_rec_sig/D");
        fillinfotree.Branch("effi_rec_norm",&effi_rec_norm, "effi_rec_norm/D");

	fillinfotree.Branch("effi_trg_sig",&effi_trg_sig, "effi_trg_sig/D");
	fillinfotree.Branch("effi_trg_norm",&effi_trg_norm, "effi_trg_norm/D");

	fillinfotree.Branch("effi_off_sig",&effi_off_sig, "effi_off_sig/D");
	fillinfotree.Branch("effi_off_norm",&effi_off_norm, "effi_off_norm/D");

        fillinfotree.Branch("effi_combi_sig",&effi_combi_sig, "effi_combi_sig/D");
        fillinfotree.Branch("effi_combi_norm",&effi_combi_norm, "effi_combi_norm/D");

        fillinfotree.Branch("effi_misid_sig",&effi_misid_sig, "effi_misid_sig/D");
        fillinfotree.Branch("effi_misid_norm",&effi_misid_norm, "effi_misid_norm/D");

        fillinfotree.Branch("effi_corm_sig",&effi_corm_sig, "effi_corm_sig/D");
        fillinfotree.Branch("effi_corm_norm",&effi_corm_norm, "effi_corm_norm/D");

        fillinfotree.Branch("effi_pid_sig",&effi_pid_sig, "effi_pid_sig/D");
        fillinfotree.Branch("effi_pid_norm",&effi_pid_norm, "effi_pid_norm/D");
        
        fillinfotree.Branch("effi_err_gen_sig",&effi_err_gen_sig, "effi_err_gen_sig/D");
        fillinfotree.Branch("effi_err_gen_norm",&effi_err_gen_norm, "effi_err_gen_norm/D");

        fillinfotree.Branch("effi_err_rec_sig",&effi_err_rec_sig, "effi_err_rec_sig/D");
        fillinfotree.Branch("effi_err_rec_norm",&effi_err_rec_norm, "effi_err_rec_norm/D");

	fillinfotree.Branch("effi_err_trg_sig",&effi_err_trg_sig, "effi_err_trg_sig/D");
	fillinfotree.Branch("effi_err_trg_norm",&effi_err_trg_norm, "effi_err_trg_norm/D");

	fillinfotree.Branch("effi_err_off_sig",&effi_err_off_sig, "effi_err_off_sig/D");
	fillinfotree.Branch("effi_err_off_norm",&effi_err_off_norm, "effi_err_off_norm/D");

        fillinfotree.Branch("effi_err_combi_sig",&effi_err_combi_sig, "effi_err_combi_sig/D");
        fillinfotree.Branch("effi_err_combi_norm",&effi_err_combi_norm, "effi_err_combi_norm/D");

        fillinfotree.Branch("effi_err_misid_sig",&effi_err_misid_sig, "effi_err_misid_sig/D");
        fillinfotree.Branch("effi_err_misid_norm",&effi_err_misid_norm, "effi_err_misid_norm/D");

        fillinfotree.Branch("effi_err_corm_sig",&effi_err_corm_sig, "effi_err_corm_sig/D");
        fillinfotree.Branch("effi_err_corm_norm",&effi_err_corm_norm, "effi_err_corm_norm/D");

        fillinfotree.Branch("effi_err_pid_sig",&effi_err_pid_sig, "effi_err_pid_sig/D");
        fillinfotree.Branch("effi_err_pid_norm",&effi_err_pid_norm, "effi_err_pid_norm/D");


        year=2012.0;
        luminosity=2968.0;


        effi_sig=finalprod_sig.val;
        effi_norm=finalprod_jpsik.val;

        effi_err_sig=finalprod_sig.err;
        effi_err_norm=finalprod_jpsik.err;


	effi_ratio=double(finalprod_jpsik.val/finalprod_sig.val);

        effi_gen_sig=sig_decprod.val;
        effi_gen_norm=jpsik_decprod.val;
        effi_rec_sig=sig_reco.val;
        effi_rec_norm=jpsik_reco.val;;
        effi_trg_sig=(signal_efficiencies.at(0)).val;
        effi_trg_norm=(jpsik_efficiencies.at(0)).val;
        effi_off_sig=(signal_efficiencies.at(1)).val;
        effi_off_norm=(jpsik_efficiencies.at(1)).val;
        effi_combi_sig=(signal_efficiencies.at(2)).val;
        effi_combi_norm=(jpsik_efficiencies.at(2)).val;
        effi_misid_sig=(signal_efficiencies.at(3)).val;
        effi_misid_norm=(jpsik_efficiencies.at(3)).val;
        effi_corm_sig=(signal_efficiencies.at(4)).val;
        effi_corm_norm=(jpsik_efficiencies.at(4)).val;
        effi_pid_sig=sig_pid.val;
        effi_pid_norm=jpsik_pid.val;


        effi_err_gen_sig=sig_decprod.err;
        effi_err_gen_norm=jpsik_decprod.err;
        effi_err_rec_sig=sig_reco.err;
        effi_err_rec_norm=jpsik_reco.err;;
        effi_err_trg_sig=(signal_efficiencies.at(0)).err;
        effi_err_trg_norm=(jpsik_efficiencies.at(0)).err;
        effi_err_off_sig=(signal_efficiencies.at(1)).err;
        effi_err_off_norm=(jpsik_efficiencies.at(1)).err;
        effi_err_combi_sig=(signal_efficiencies.at(2)).err;
        effi_err_combi_norm=(jpsik_efficiencies.at(2)).err;
        effi_err_misid_sig=(signal_efficiencies.at(3)).err;
        effi_err_misid_norm=(jpsik_efficiencies.at(3)).err;
        effi_err_corm_sig=(signal_efficiencies.at(4)).err;
        effi_err_corm_norm=(jpsik_efficiencies.at(4)).err;
        effi_err_pid_sig=sig_pid.err;
        effi_err_pid_norm=jpsik_pid.err;


        fillinfotree.Fill();
	fillinfotree.Write("",TObject::kOverwrite);



 
        out<<"\\end{document}"<<endl;



        out.close();



	return(0);



}



