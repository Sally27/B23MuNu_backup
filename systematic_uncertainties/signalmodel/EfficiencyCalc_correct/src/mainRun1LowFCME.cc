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
        out.open("ComparisonSignalMC_PHSPmodelefficienciesbelow1Gev_LowFCME.tex");

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
	double effrecostrsig(0);
	double effmyrecosig(0);
	double combibdtsig(0);	
	double misidbdtsig(0);
	double cormsig(0);		

	number_bkk_sig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "numbkk");
//	decprodcutsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "decprodcut");
	effrecostrsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "reco");
	effmyrecosig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "toteff");
	combibdtsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Combi.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "combibdt");	
	misidbdtsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Misid.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "misidbdt");
	cormsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Fitrange.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "fitrange");

	double number_bkk_nor(258229.0+352963.0+255641.0+373627.0);
	double decprodcutjpsik(0.16822);
        double decprodcutjpsik_err(0.00021);
	double effrecostrjpsik(0);
	double effmyrecostrjpsik(0);
	double combibdtjpsik(0);
	double misidbdtjpsik(0);
	double cormjpsik(0);

//	number_bkk_nor=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "numbkk");
//	decprodcutjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "decprodcut");
//	effrecostrjpsik=(returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "reco"))*(returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "misidstrippingfull"));
//	effmyrecostrjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "trigger");
//	combibdtjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+"_Combi.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "combibdt");
//	misidbdtjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+"_Misid.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "misidbdt");
//	cormjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+"_Fitrange.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "fitrange");


 
        double toteff;


	TFile f_initial_sig_ORI("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012_signalmodelqminfirst/bin/Bu23MuNuMC2012_MCtruthORI.root","READ");
	TTree* t_initial_sig_ORI =(TTree*)f_initial_sig_ORI.Get(("DecayTree"));


	TFile f_initial_sig("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012_signalmodelqminfirst/bin/Bu23MuNuMC2012_MCtruth.root","READ");
	TTree* t_initial_sig =(TTree*)f_initial_sig.Get(("DecayTree"));

	TFile f_final_sig("/vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic_FitCorM_LowFCME.root","READ");
	TTree* t_final_sig =(TTree*)f_final_sig.Get(("DecayTree"));

	TFile f_initial_norm_ORI("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc_PHSP/2012/bin/B23MuNuMCPHSP_MCtruthORI.root","READ");
	TTree* t_initial_norm_ORI =(TTree*)f_initial_norm_ORI.Get(("DecayTree"));


	TFile f_initial_norm("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc_PHSP/2012/bin/B23MuNuMCPHSP_MCtruth.root","READ");
	TTree* t_initial_norm =(TTree*)f_initial_norm.Get(("DecayTree"));

	TFile f_final_norm("/vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/B23MuNuMCPHSP_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic_FitCorM_LowFCME.root","READ");
	TTree* t_final_norm =(TTree*)f_final_norm.Get(("DecayTree"));



 
//        double toteffsiglow=decprodcutsig*effrecostrsig*effmyrecosig*combibdtsig*misidbdtsig*cormsig*sigPID;
//        double toteffjpsikmclow=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*jpsikPID;
   
//        double crosschecksiglow=decprodcutsig*effrecostrsig*(double(double(t_final_sig->GetEntries())/double(t_initial_sig->GetEntries())))*sigPID;
  //      double crosscheckjpsikmclow=decprodcutjpsik*effrecostrjpsik*(double(double(t_final_norm->GetEntries())/double(t_initial_norm->GetEntries())))*jpsikPID;

//	double crosschecksiglowerr=calcEffErr(int(number_bkk_sig),t_final_sig->GetEntries());//still need to add on error from dec prodcut
//	double crosscheckjpsikmclowerr=calcEffErr(int(number_bkk_nor),t_final_norm->GetEntries());//still need to add on error from dec prodcut

        //-------------Dec Prod Cut-------------------//

        ValError sig_decprod(decprodcutsig,decprodcutsig_err);
        ValError jpsik_decprod(decprodcutjpsik,decprodcutjpsik_err);
           

        //-------------All other selection------------//

        ValError sig_othereff_passed(double(t_final_sig->GetEntries()),sqrt(double(t_final_sig->GetEntries())));
        ValError jpsik_othereff_passed(double(t_final_norm->GetEntries()),sqrt(double(t_final_norm->GetEntries())));

        ValError sig_othereff_total(double(t_initial_sig->GetEntries()),sqrt(double(t_initial_sig->GetEntries())));
        ValError jpsik_othereff_total(double(t_initial_norm->GetEntries()),sqrt(double(t_initial_norm->GetEntries())));

        ValError sig_othereff=getRatioBinomial(sig_othereff_passed,sig_othereff_total);
        ValError jpsik_othereff=getRatioBinomial(jpsik_othereff_passed,jpsik_othereff_total);

        //------------PID estuff no error so far-------//

//        double sigPID=0.64815;
//        double jpsikPID=0.644225;

        ValError sig_pid(readPIDvar("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/preparesignalweights_correct/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_correct_gen_level/bin/B23MuNuMC2012probnnmu035Strip21_selected_LowFCME.root", "DecayTree", "PIDweight"),0.007);
        ValError jpsik_pid(readPIDvar("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/preparesignalweights_correct/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_correct_gen_level/bin/B23MuNuMCPHSP2012probnnmu035Strip21_selected_LowFCME.root","DecayTree", "PIDweight"),0.011);

        //--------decorprodcut-----------//
        ValError truedecsig(decprodcutsig,decprodcutsig_err);
        ValError truedecjpsik(decprodcutjpsik,decprodcutjpsik_err);


        //---strings of files to investigate ---//
        vector<string> files_mine;
        vector<string> files_phsp;
        vector<string> cuts;   

       files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012_signalmodelqminfirst/bin/Bu23MuNuMC2012_MCtruth.root");
       files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012_signalmodelqminfirst/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger.root");
       files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012_signalmodelqminfirst/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi.root");
       files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic.root");
       files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic.root");
       files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic_FitCorM.root");
       files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic_FitCorM_LowFCME.root");
   

       files_phsp.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc_PHSP/2012/bin/B23MuNuMCPHSP_MCtruth.root");
       files_phsp.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc_PHSP/2012/bin/B23MuNuMCPHSP_MCtruth_L0MuonDecisionTOS_trigger.root");
       files_phsp.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc_PHSP/2012/bin/B23MuNuMCPHSP_MCtruth_L0MuonDecisionTOS_trigger_Jpsi.root");
       files_phsp.push_back("/vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/B23MuNuMCPHSP_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic.root");
       files_phsp.push_back("/vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/B23MuNuMCPHSP_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic.root");
       files_phsp.push_back("/vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/B23MuNuMCPHSP_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic_FitCorM.root");
       files_phsp.push_back("/vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/B23MuNuMCPHSP_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic_FitCorM_LowFCME.root");

       cuts.push_back("trigger");
       cuts.push_back("Jpsi");
       cuts.push_back("combibdt");
       cuts.push_back("misidbdt");
       cuts.push_back("fitrange");
       cuts.push_back("LowFCME");
       cuts.push_back("all");

       

        //-------------Errors alltogether

        ValError finalprod_sig=sig_decprod*sig_othereff*sig_pid;
        ValError finalprod_jpsik=jpsik_decprod*jpsik_othereff*jpsik_pid;
 
        out << " & "<< " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ (Nominal)  & " << " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ (Alternative) "<<" \\\\" <<endl;   
        out<<"\\hline"<<endl;
//        out << "$\\epsilon_{decprodcut}$ &" << decprodcutsig << " & " << decprodcutjpsik <<" \\\\ "<<endl;

        out << "N$^{generated}$ &" << " 25000 " << " & " << " 25000 " <<" \\\\ "<<endl;
        out << "N$^{generated,minq^{2}}$ &" << getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut.root","MCDecayTree") << " & " << getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/phspmodel_qmincut.root","MCDecayTree")<<" \\\\ "<<endl;
        out << "N$^{in\\_acc,minq^{2}}$ &" << getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut_inacc.root","MCDecayTree") << " & " << getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/phspmodel_qmincut_inacc.root","MCDecayTree")<<" \\\\ "<<endl;
        out << "N$^{in\\_acc}$ &" << number_bkk_sig << " & " << number_bkk_nor <<" \\\\ "<<endl;
        out << "N$^{REC, minq^{2}}$ &" << t_initial_sig->GetEntries() << " & " << t_initial_norm->GetEntries() <<" \\\\ "<<endl;




        double eff_firstpart(0);
        double eff_secondpart(0);
        double nbkk_1(1114130.0);
//        double nrecoq_1(116892.0);
        double numgen_1(25000.0);

        double nbkk_2(258229.0+352963.0+255641.0+373627.0);
//        double nrecoq_2(44086.0);
        double numgen_2(25000.0);

        ValError ninaccqmin((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut_inacc.root","MCDecayTree"))),sqrt((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut_inacc.root","MCDecayTree")))));
        ValError nglqmin((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut.root","MCDecayTree"))),sqrt((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut.root","MCDecayTree")))));
        ValError nrecqmin(t_initial_sig->GetEntries(),sqrt(t_initial_sig->GetEntries()));
        ValError ninacc(nbkk_1,sqrt(nbkk_1));
        ValError numgen(numgen_1,sqrt(numgen_1));


        ValError try1 = ((ninaccqmin)/(nglqmin))*(nrecqmin/(ninacc*(nglqmin/numgen)));
        ValError try1_err = (getRatioBinomial(ninaccqmin,nglqmin))*(getRatioBinomial(nrecqmin,(ninacc*getRatioBinomial(nglqmin,numgen))));
        


        ValError ninaccqmin_s((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/phspmodel_qmincut_inacc.root","MCDecayTree"))),sqrt((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/phspmodel_qmincut_inacc.root","MCDecayTree")))));
        ValError nglqmin_s((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/phspmodel_qmincut.root","MCDecayTree"))),sqrt((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/phspmodel_qmincut.root","MCDecayTree")))));
        ValError nrecqmin_s(t_initial_norm->GetEntries(),sqrt(t_initial_norm->GetEntries()));
        ValError ninacc_s(nbkk_2,sqrt(nbkk_2));
        ValError numgen_s(numgen_2,sqrt(numgen_2));


        ValError try2 = ((ninaccqmin_s)/(nglqmin_s))*(nrecqmin_s/(ninacc_s*(nglqmin_s/numgen_s)));
        ValError try2_err = (getRatioBinomial(ninaccqmin_s,nglqmin_s))*(getRatioBinomial(nrecqmin_s,(ninacc_s*getRatioBinomial(nglqmin_s,numgen_s))));

        eff_firstpart = (double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut_inacc.root","MCDecayTree")))/double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut.root","MCDecayTree"))*(t_initial_sig->GetEntries()/(nbkk_1*(double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut.root","MCDecayTree")/numgen_1))));

        eff_secondpart = (double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/phspmodel_qmincut_inacc.root","MCDecayTree")))/double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/phspmodel_qmincut.root","MCDecayTree"))*(t_initial_norm->GetEntries()/(nbkk_2*(double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/phspmodel_qmincut.root","MCDecayTree")/numgen_2))));



       
        out<<"\\hline"<<endl;
        out << "${\\epsilon^{GEN,minq^{2}}}\\times {\\epsilon^{REC,minq^{2}}}$ &" << eff_firstpart << " & " << eff_secondpart <<" \\\\ "<<endl;
        out << "${\\epsilon^{GEN,minq^{2}}}\\times {\\epsilon^{REC,minq^{2}}}$ val &" << try1 << " & " << try2 <<" \\\\ "<<endl;
        out << "${\\epsilon^{GEN,minq^{2}}}\\times {\\epsilon^{REC,minq^{2}}}$ val err &" << return_nice_string(((try1_err)/2.0))<< " & " << return_nice_string(((try2_err)/2.0)) <<" \\\\ "<<endl;
 //       out<<"\\hline"<<endl;
 //       out << "$\\epsilon_{reco+strip+mctruth}$ & "<<t_initial_sig_ORI->GetEntries()/number_bkk_sig <<" & "<< t_initial_norm_ORI->GetEntries()/number_bkk_nor<<" \\\\ "<<endl;
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

        

        out << "$\\epsilon\\_{"+cuts.at(i-1)+"}$ & "<< double(t_sig_cut_2->GetEntries())/double(t_sig_cut->GetEntries()) << " & " << double(t_norm_cut_2->GetEntries())/double(t_norm_cut->GetEntries())<<" \\\\ "<<endl;
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

        ValError sigy(double(t_initial_sig_ORI->GetEntries()),sqrt(double(t_initial_sig_ORI->GetEntries())));
        ValError sigz(number_bkk_sig,sqrt(number_bkk_sig));
        ValError normy(double(t_initial_norm_ORI->GetEntries()),sqrt(double(t_initial_norm_ORI->GetEntries())));
        ValError normz(number_bkk_nor,sqrt(number_bkk_nor));

        ValError sig_reco=getRatioBinomial(sigy,sigz);
        ValError jpsik_reco=getRatioBinomial(normy,normz);


        //out<<"${\\epsilon^{OFF,minq^{2}}}\\times {\\epsilon^{CombiBDT,minq^{2}}}\\times {\\epsilon^{MisidBDT,minq^{2}}}\\times{\\epsilon^{fitrange,minq^{2}}}$ & "<<  sig_othereff.val <<" $\\pm$"<<sig_othereff.err<< " & "<< jpsik_othereff.val <<" $\\pm$"<<jpsik_othereff.err <<" \\\\ "<<endl;
        out<<"${\\epsilon^{other,minq^{2}}}$ & "<<  sig_othereff.val <<" $\\pm$"<<sig_othereff.err<< " & "<< jpsik_othereff.val <<" $\\pm$"<<jpsik_othereff.err <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "N$^{final}$ &" <<t_final_sig->GetEntries()  << " & " << t_final_norm->GetEntries() <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\epsilon^{PID,minq^{2}}$ &" << sig_pid << " & " << jpsik_pid <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
 //       out<<"$\\epsilon\\_{decprodcut}$ &"<<sig_decprod <<" & "<<jpsik_decprod<<" \\\\ "<<endl;
//        out<<"$\\epsilon\\_{reco+strip+mctruth}$ & "<<t_initial_sig_ORI->GetEntries()/number_bkk_sig <<" & "<< t_initial_norm_ORI->GetEntries()/number_bkk_nor<<" \\\\ "<<endl;
//        out<<"$\\epsilon\\_{alloffcuts}$ &"<<sig_othereff <<" & "<<jpsik_othereff<<" \\\\ "<<endl;
//        out<<"$\\epsilon\\_{pid}$ &"<<sig_pid <<" & "<<jpsik_pid<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<" &"<<" $\\epsilon_{nom}$ = "<<(try1_err/2.0)*(sig_othereff)*(sig_pid) <<" & "<<" $\\epsilon_{alt}$ ="<<(try2_err/2.0)*(jpsik_othereff)*(sig_pid)<<" \\\\ "<<endl;
  
        ValError all_sig=(try1_err/2.0)*(sig_othereff)*(sig_pid);
        ValError all_norm=(try2_err/2.0)*(jpsik_othereff)*(jpsik_pid);
 
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
        out<<"\\caption{Comparison of efficiencies of nominal and alternative signal model samples using 2012 datasets with minq$<$980 MeV/c$^{2}$ leads to systematic uncertainty "<< (100.0*(all_sig-all_norm)/(all_sig)).val <<" \\%."<<"}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"This is comparison"<<endl;

              
     //  out<<"Efficiency ratio decprodcut, i.e effmine/effphsp is "<< truedecsig/truedecjpsik<<endl;
     //   out<<"\\newline"<<endl;
     //   out<<"Efficiency ratio reco+mc+truth, i.e effmine/effphsp is "<< sig_reco/jpsik_reco<<endl;
     //   out<<"\\newline"<<endl;
        out<<"Efficiency ratio offlineeff, i.e effmine/effphsp is "<< sig_othereff/jpsik_othereff<<endl;
        out<<"\\newline"<<endl;
        out<<"Efficiency ratio pid, i.e effmine/effphsp is "<< sig_pid/jpsik_pid<<endl;
        out<<"\\newline"<<endl;
        out<<"Efficiency ratio Total, i.e effmine/effphsp is "<< all_sig/all_norm<<endl;
        out<<"\\newline"<<endl;
        out<<"Sytematics from using different model after minq$^2$ cut is "<<(100.0*((((sig_othereff)*(sig_pid))-((jpsik_othereff)*(jpsik_pid)))/((sig_othereff)*(sig_pid)))).val<<" \\%"<<endl;
//        out<<"\\newline"<<endl;
//        out<<"Sytematics from using different model after minq$^2$ cut + genlevelcut is "<<100.0*((((sig_othereff)*(sig_pid)*(truedecsig))-((truedecjpsik)*(jpsik_othereff)*(jpsik_pid)))/((truedecsig)*(sig_othereff)*(sig_pid)))<<" \\%"<<endl;
        out<<"\\newline"<<endl;
        out<<"Sytematics from using different model after minq$^2$ cut + genlevelcut + reco is "<<(100.0*(all_sig-all_norm)/(all_sig)).val<<" \\%"<<endl;

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



