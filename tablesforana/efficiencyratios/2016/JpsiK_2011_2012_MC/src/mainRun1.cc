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


        string PIDcut=argv[1];

        ofstream out;
        out.open(("SingleEvRun1"+PIDcut+"_FULL_ERRORS_JPSIK2011and2012.tex").c_str());

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
        
        out<<"Calculation of the $J/\\psi$ K differences between 2011 and 2012 MC"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{ l | l | l | l }"<<endl;
        out<<"\\hline"<<endl;
        out<<"\\hline"<<endl;

        vector<int> years;
        years.push_back(2011);
        years.push_back(2012);
        years.push_back(2016);

	double number_bkk_sig(4074487);
	double decprodcutsig(0.15921);
	double decprodcutsig_err(0.00015);
	double effrecostrsig(0);
	double effmyrecosig(0);
	double combibdtsig(0);	
	double misidbdtsig(0);
	double cormsig(0);		
        double vetojpsisig(0);

//	number_bkk_sig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "numbkk");
//	decprodcutsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "decprodcut");
	effrecostrsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "effreco");
	effmyrecosig=(returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "L0"))*(returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "trigger"));
        vetojpsisig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "jpsi");
	combibdtsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Combi.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "combibdt");	
	misidbdtsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Misid.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "misidbdt");
	cormsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Fitrange.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "fitrange");

	double number_bkk_nor(0);
	double decprodcutjpsik(0.16216);
        double decprodcutjpsik_err(0.00024);
	double effrecostrjpsik(0);
	double effmyrecostrjpsik(0);
        double vetojpsijpsik(1.0);
	double combibdtjpsik(0);
	double misidbdtjpsik(0);
	double cormjpsik(0);

	number_bkk_nor=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "numbkk");
//	decprodcutjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "decprodcut");
	effrecostrjpsik=(returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "reco"))*(returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "misidstrippingfull"));
	effmyrecostrjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "trigger");
	combibdtjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+"_Combi.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "combibdt");
	misidbdtjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+"_Misid.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "misidbdt");
	cormjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+"_Fitrange.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "fitrange");


 
        double toteff;
//        double decprodcutsig =0.185;
//        double decprodcutjpsik =0.16743;

//        double effrecostrsig= 0.111;
//        double effrecostrjpsik= 0.3165*0.5373404;

//        double effmyrecosig =0.63634;
//        double effmyrecostrjpsik= 0.776819;


//        double combibdtsig = 0.446179;
//        double combibdtjpsik = 0.489546; 

//        double misidbdtsig = 0.43133;
  //      double misidbdtjpsik = 0.49489;

//        double cormsig=0.923507;
//        double cormjpsik=0.996;

//        double lowFCMEsig=0.579403; 
//        double lowFCMEjpsik=0.68763;

//        double highFCMEsig=0.420597;
//        double highFCMEjpsik=0.303809;

        double sigPID=readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/bin/B23MuNuMC2012"+PIDcut+"Strip21_selected.root").c_str(), "DecayTree", "PIDweight");
        double jpsikPID=readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2012"+PIDcut+".root").c_str(), "DecayTree", "mcweight");

  //      double highFCMEsigPID=0.680185;
   //     double highFCMEjpsikPID=0.716373;

   //     double sigPID = 0.663465;
   //     double jpsikPID = 0.71386;       

	TFile f_final_sig("/vols/lhcb/ss4314/cutonFitRange/FUMSB_simultaneous_NewTCK/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root","READ");
	TTree* t_final_sig =(TTree*)f_final_sig.Get(("DecayTree"));

	TFile f_final_norm("/vols/lhcb/ss4314/cutonFitRange/FUMSB_simultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root","READ");
	TTree* t_final_norm =(TTree*)f_final_norm.Get(("DecayTree"));

	TFile f_initial_sig("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2011/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull.root","READ");
	TTree* t_initial_sig =(TTree*)f_initial_sig.Get(("DecayTree"));

	TFile f_initial_norm("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root","READ");
	TTree* t_initial_norm =(TTree*)f_initial_norm.Get(("DecayTree"));

 
        double toteffsiglow=decprodcutsig*effrecostrsig*effmyrecosig*vetojpsisig*combibdtsig*misidbdtsig*cormsig*sigPID;
        double toteffjpsikmclow=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*vetojpsijpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*jpsikPID;
   
        double crosschecksiglow=decprodcutsig*effrecostrsig*(double(double(t_final_sig->GetEntries())/double(t_initial_sig->GetEntries())))*sigPID;
        double crosscheckjpsikmclow=decprodcutjpsik*effrecostrjpsik*(double(double(t_final_norm->GetEntries())/double(t_initial_norm->GetEntries())))*jpsikPID;

	double crosschecksiglowerr=calcEffErr(int(number_bkk_sig),t_final_sig->GetEntries());//still need to add on error from dec prodcut
	double crosscheckjpsikmclowerr=calcEffErr(int(number_bkk_nor),t_final_norm->GetEntries());//still need to add on error from dec prodcut

        //-------------Dec Prod Cut-------------------//

        ValError sig_decprod(decprodcutsig,decprodcutsig_err);
        ValError jpsik_decprod(decprodcutjpsik,decprodcutjpsik_err);
        
         //------------Reco Selec for signal ---------//
    //    ValError sig_reco(returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "effreco"),returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "effreco_err")); 

        

        //-------------All other selection------------//

        ValError sig_othereff_passed(double(t_final_sig->GetEntries()),sqrt(double(t_final_sig->GetEntries())));
        ValError jpsik_othereff_passed(double(t_final_norm->GetEntries()),sqrt(double(t_final_norm->GetEntries())));

        ValError sig_othereff_total(number_bkk_sig,sqrt(number_bkk_sig));
        ValError jpsik_othereff_total(number_bkk_nor,sqrt(number_bkk_nor));

        ValError sig_othereff=getRatioBinomial(sig_othereff_passed,sig_othereff_total);
        ValError jpsik_othereff=getRatioBinomial(jpsik_othereff_passed,jpsik_othereff_total);

         //Reco for jpsiK 2011//
         ValError sig_initial(double(t_initial_sig->GetEntries()),sqrt(double(t_initial_sig->GetEntries())));
         ValError sig_reco=getRatioBinomial(sig_initial,sig_othereff_total);
         //Reco for jpsiK 2012//
         ValError jpsik_initial(double(t_initial_norm->GetEntries()),sqrt(double(t_initial_norm->GetEntries())));
         ValError jpsik_reco=getRatioBinomial(jpsik_initial,jpsik_othereff_total);


        //------------PID estuff no error so far-------//
        ValError sig_pid(readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2011"+PIDcut+".root").c_str(), "DecayTree", "mcweight"),0.0010);
        ValError jpsik_pid(readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2012"+PIDcut+".root").c_str(), "DecayTree", "mcweight"),0.0011);


        //-------------Errors alltogether

        ValError finalprod_sig=sig_decprod*sig_othereff*sig_pid;//*sig_pid;
        ValError finalprod_jpsik=jpsik_decprod*jpsik_othereff*jpsik_pid;//*jpsik_pid;
 
        out << "Efficiency & "<< " $B^{+} \\rightarrow J/\\psi\\ K^{+}$  2011 & " << " $B^{+} \\rightarrow J/\\psi\\ K^{+}$ 2012 & Ratio (2012/2011) \\\\" <<endl;   
        out<<"\\hline"<<endl;
  //      out << "$\\epsilon_{decprodcut}$ &" << decprodcutsig << " & " << decprodcutjpsik <<" \\\\ "<<endl;
  //      out << "$\\epsilon_{reco}$ &" << effrecostrsig << " & " << effrecostrjpsik <<" \\\\ "<<endl;
  //      out << "$\\epsilon_{trigger}$ &" << effmyrecosig << " & " << effmyrecostrjpsik <<" \\\\ "<<endl;
  //      out << "$\\epsilon_{cc}$ &" << vetojpsisig << " & " << vetojpsijpsik <<" \\\\ "<<endl;
  //      out << "$\\epsilon_{combibdt}$ &" << combibdtsig << " & " << combibdtjpsik <<" \\\\ "<<endl;
  //      out << "$\\epsilon_{misidbdt}$ &" << misidbdtsig << " & " << misidbdtjpsik <<" \\\\ "<<endl;
  //      out << "$\\epsilon_{corm}$ &" << cormsig << " & " << cormjpsik <<" \\\\ "<<endl;
  //      out << "$\\epsilon_{PID}$ &" << sigPID << " & " << jpsikPID <<" \\\\ "<<endl;
  //      out<<"\\hline"<<endl;
  //      out << "$\\epsilon_{totalNOFCME}$ &" << toteffsiglow << " & " << toteffjpsikmclow <<" \\\\ "<<endl;
  //      out<<"\\hline"<<endl;
  //      out << "$\\epsilon_{crosscheckNOFCME}$ &" << crosschecksiglow << " $\\pm$ "<< crosschecksiglowerr << " & " << crosscheckjpsikmclow <<" $\\pm$ "<< crosscheckjpsikmclowerr<<" \\\\ "<<endl;
  //      out<<"\\hline"<<endl;
  //      out<<"$\\epsilon_{neweffapp_nodecprodcut_nopid}$ &"<<sig_othereff <<" & "<<jpsik_othereff<<" \\\\ "<<endl;
  //      out<<"$\\epsilon_{neweffapp_decprodcut}$ &"<<sig_decprod <<" & "<<jpsik_decprod<<" \\\\ "<<endl;
  //      out<<"$\\epsilon_{neweffapp_decprocut_nopid}$ &"<<sig_decprod*sig_othereff <<" & "<<jpsik_decprod*jpsik_othereff<<" \\\\ "<<endl;
  //      out<<"$\\epsilon_{neweffapp_pid}$ &"<<sig_pid <<" & "<<jpsik_pid<<" \\\\ "<<endl;
  //      out<<"$\\epsilon_{neweffapp}$ &"<<finalprod_sig <<" & "<<finalprod_jpsik<<" \\\\ "<<endl;
   

        vector<string> files_mine;
        vector<string> files_norm;
        vector<string> cuts;

        files_mine.push_back("/vols/lhcb/ss4314/final_tuples/mc/norm_mc/2011/MC_B2JpsiK_2011.root");
        files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2011/bin/MC_B2JpsiK_2011MCTruth.root");
        files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2011/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull.root");
        files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2011/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger.root");
        files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2011/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger.root");
        files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger_CombBasic.root");
        files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger_CombBasic_MisidBasic.root");
        files_mine.push_back("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root");




        files_norm.push_back("/vols/lhcb/ss4314/final_tuples/mc/norm_mc/2012/MC_B2JpsiK_2012.root");
        files_norm.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth_.root");
        files_norm.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root");
        files_norm.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger.root");
        files_norm.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger.root");
        files_norm.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic.root");
        files_norm.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic.root");
        files_norm.push_back("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root");

     //   ValError jpsik_for_rec(double(t_initial_norm->GetEntries(),)
     //   ValError jpsik_rec

        cuts.push_back("mctruth");
        cuts.push_back("misidstripping");
        cuts.push_back("trigger");
        cuts.push_back("offline");
        cuts.push_back("combibdt");
        cuts.push_back("misidbdt");
        cuts.push_back("fitrange");
        cuts.push_back("all");

        vector<string> decaytreename;
        decaytreename.push_back("B2JpsiK_Tuple/DecayTree");
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

         ValError sig_initial_strip(double(t_sig_cut_strip->GetEntries()),sqrt(double(t_sig_cut_strip->GetEntries())));
         ValError sig_reco_strip=getRatioBinomial(sig_initial_strip,sig_othereff_total);
         //Stripping only for jpsiK 2012//
         ValError jpsik_initial_strip(double(t_norm_cut_strip->GetEntries()),sqrt(double(t_norm_cut_strip->GetEntries())));
         ValError jpsik_reco_strip=getRatioBinomial(jpsik_initial_strip,jpsik_othereff_total);


        out<<"\\hline"<<endl;
        out << "Number in bkk & "<<number_bkk_sig<< " & " << number_bkk_nor<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\epsilon\\_{GEN}$ & "<<sig_decprod.val<<"$\\pm$"<<sig_decprod.err<< " & " << jpsik_decprod.val<<"$\\pm$"<<jpsik_decprod.err<<" & "<< (jpsik_decprod/sig_decprod).val<< "$\\pm$"<< (jpsik_decprod/sig_decprod).err<<" \\\\ "<<endl;
        out << "$\\epsilon\\_{REC}$ & "<<sig_reco.val<<"$\\pm$"<<sig_reco.err<< " & " << jpsik_reco.val<<"$\\pm$"<<jpsik_reco.err<<" & "<< (jpsik_reco/sig_reco).val<< "$\\pm$"<< (jpsik_reco/sig_reco).err<<" \\\\ "<<endl;
        out << "$\\epsilon\\_{striponly}$ & "<<sig_reco_strip.val<<"$\\pm$"<<sig_reco_strip.err<< " & " << jpsik_reco_strip.val<<"$\\pm$"<<jpsik_reco_strip.err<<" & "<< (jpsik_reco_strip/sig_reco_strip).val<< "$\\pm$"<< (jpsik_reco_strip/sig_reco_strip).err<<" \\\\ "<<endl;
  
	vector<ValError> signal_efficiencies;
        vector<ValError> jpsik_efficiencies;

	for( int i(1); i<7; i++)
	{
		TFile f_sig_cut((files_mine.at(i-1)).c_str(),"READ");
		TTree* t_sig_cut =(TTree*)f_sig_cut.Get((decaytreename.at(i-1)).c_str());
		TFile f_norm_cut((files_norm.at(i-1)).c_str(),"READ");
		TTree* t_norm_cut =(TTree*)f_norm_cut.Get((decaytreename.at(i-1).c_str()));

		TFile f_sig_cut_2((files_mine.at(i)).c_str(),"READ");
		TTree* t_sig_cut_2 =(TTree*)f_sig_cut_2.Get(((decaytreename.at(i)).c_str()));
		TFile f_norm_cut_2((files_norm.at(i)).c_str(),"READ");
		TTree* t_norm_cut_2 =(TTree*)f_norm_cut_2.Get(((decaytreename.at(i)).c_str()));

                ValError sig_passes(double(t_sig_cut_2->GetEntries()),sqrt(double(t_sig_cut_2->GetEntries())));
                ValError jpsik_passes(double(t_norm_cut_2->GetEntries()),sqrt(double(t_norm_cut_2->GetEntries())));

                ValError sig_tots(double(t_sig_cut->GetEntries()),sqrt(double(t_sig_cut->GetEntries())));
                ValError jpsik_tots(double(t_norm_cut->GetEntries()),sqrt(double(t_norm_cut->GetEntries())));

                ValError sig_effs=getRatioBinomial(sig_passes,sig_tots);
                ValError jpsik_effs=getRatioBinomial(jpsik_passes,jpsik_tots);


		out << "$\\epsilon\\_{"+cuts.at(i-1)+"}$ & "<<sig_effs.val<<"$\\pm$"<<sig_effs.err<< " & " << jpsik_effs.val<<"$\\pm$"<<jpsik_effs.err<< " & "<< (jpsik_effs/sig_effs).val<< "$\\pm$"<< (jpsik_effs/sig_effs).err<<" \\\\ "<<endl;

                signal_efficiencies.push_back(sig_effs);
                jpsik_efficiencies.push_back(jpsik_effs);

		f_sig_cut.Close();
		f_norm_cut.Close();
		f_sig_cut_2.Close();
		f_norm_cut_2.Close();
	}


        out << "$\\epsilon\\_{PID}$ & "<<sig_pid.val<<"$\\pm$"<<sig_pid.err<< " & " << jpsik_pid.val<<" $\\pm$ "<<jpsik_pid.err<< " & "<< (jpsik_pid/sig_pid).val<< "$\\pm$"<< (jpsik_pid/sig_pid).err<<" \\\\ "<<endl;
        out<<"$\\epsilon_{tot}$ &"<<finalprod_sig.val<<"$\\pm$"<<finalprod_sig.err<<" & "<<finalprod_jpsik.val<<"$\\pm$"<<finalprod_jpsik.err<< " & "<< (finalprod_jpsik/finalprod_sig).val<< "$\\pm$"<< (finalprod_jpsik/finalprod_sig).err<<" \\\\ "<<endl;

        out<<"\\hline"<<endl;
        out<<"$\\epsilon^{2012}_{tot}/\\epsilon^{2011}_{tot}$ & "<<(finalprod_jpsik/finalprod_sig).val<<"$\\pm$"<<(finalprod_jpsik/finalprod_sig).err<<" & "<<" \\\\ "<<endl;

        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Efficiency differences}"<<endl;
        out<<"\\end{table}"<<endl;





	TFile fillinfo(("../info/info_SES_2011_"+PIDcut+"_FULL_ERROR.root").c_str(),"UPDATE");
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
//        numofevents_per_lumi=double(numberofobsevents.val/luminosity);
//        numofevents=numberofobsevents.val;
//        numofevents_err=numberofobsevents.err;


        effi_sig=finalprod_sig.val;
        effi_norm=finalprod_jpsik.val;

        effi_err_sig=finalprod_sig.err;
        effi_err_norm=finalprod_jpsik.err;


//        sensitivity=newses.val;
//        sensitivity_err=newses.err;
	effi_ratio=double(finalprod_jpsik.val/finalprod_sig.val);
//	effi_numobs=double(finalprod_jpsik.val/(finalprod_sig.val*numberofobsevents.val));
//	effi_corr_lumi=double(numberofobsevents.val/(finalprod_jpsik.val*luminosity));

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



