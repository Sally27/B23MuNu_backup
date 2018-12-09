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

using namespace std;


int main(){

        ofstream out;
        out.open("EfficiencyComparison.tex");

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
        
//        out<<"Calculation of the Single Event Sensitivity"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{ l | l | l }"<<endl; 
        out<<"\\hline"<<endl;
        out<<"$\\varepsilon$ & $B^+ \\rightarrow \\mu^+ \\mu^- \\mu^+$  & $B^+ \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-}$ \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"\\hline"<<endl;

        vector<int> years;

	years.push_back(2011);
	years.push_back(2012);
	years.push_back(2016);

	double number_bkk_sig(0);
	double decprodcutsig(0);
        
	double effrecostrsig(0);
	double effmyrecosig(0);
	double combibdtsig(0);	
	double misidbdtsig(0);
	double cormsig(0);		
	double effstripsig(0);

	number_bkk_sig=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_SIG.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "numbkk");
	decprodcutsig=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_SIG.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "decprodcut");
	effstripsig=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_SIG.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "strip");
	effrecostrsig=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_SIG.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "mctruth");
	effmyrecosig=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_SIG.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "toteff");

	double	efftriggersig=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_SIG.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "trigger");
	double	effqminsig=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_SIG.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "qmincut");
	double	effjpsisig=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_SIG.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "jpsi");



	//	combibdtsig=returnEff(("../tuples/Efficiencies_SigMC_"+i2s(years.at(1))+"_Combi.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "combibdt");	
	//	misidbdtsig=returnEff(("../tuples/Efficiencies_SigMC_"+i2s(years.at(1))+"_Misid.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "misidbdt");
	//	cormsig=returnEff(("../tuples/Efficiencies_SigMC_"+i2s(years.at(1))+"_Fitrange.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "fitrange");

	double number_bkk_nor(0);
	double decprodcutjpsik(0);
	double effrecostrjpsik(0);
	double effmyrecostrjpsik(0);
	double combibdtjpsik(0);
	double misidbdtjpsik(0);
	double cormjpsik(0);
	double effstripjpsik(0);
        
        combibdtsig=0.472538;
        misidbdtsig=0.435813;
        
        combibdtjpsik=0.245146;
        misidbdtjpsik=0.635529;



	number_bkk_nor=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "numbkk");
	decprodcutjpsik=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "decprodcut");
	effstripjpsik=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "strip");
	effrecostrjpsik=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "mctruth");
	effmyrecostrjpsik=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "toteff");

	double efftriggerjpsik=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "trigger");
	double effqminjpsik=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "qmincut");
	double effjpsijpsik=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "jpsi");
//	combibdtjpsik=returnEff(("../tuples/Efficiencies_NormMC_"+i2s(years.at(1))+"_Combi.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "combibdt");
//	misidbdtjpsik=returnEff(("../tuples/Efficiencies_NormMC_"+i2s(years.at(1))+"_Misid.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "misidbdt");
//	cormjpsik=returnEff(("../tuples/Efficiencies_NormMC_"+i2s(years.at(1))+"_Fitrange.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "fitrange");


 
        double toteff;
        double sigPID=0.648;
        double jpsikPID=0.7160;


//	TFile f_final_sig("/vols/lhcb/ss4314/cutonFitRange/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root","READ");
//	TTree* t_final_sig =(TTree*)f_final_sig.Get(("DecayTree"));
//
//	TFile f_final_norm("/vols/lhcb/ss4314/cutonFitRange/FUMSB_simultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root","READ");
//	TTree* t_final_norm =(TTree*)f_final_norm.Get(("DecayTree"));
//
//	TFile f_initial_sig("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/Bu23MuNuMC2012_MCtruth.root","READ");
//	TTree* t_initial_sig =(TTree*)f_initial_sig.Get(("DecayTree"));
//
//	TFile f_initial_norm("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root","READ");
//	TTree* t_initial_norm =(TTree*)f_initial_norm.Get(("DecayTree"));
//
// 
//        double toteffsiglow=decprodcutsig*effrecostrsig*effmyrecosig*combibdtsig*misidbdtsig*cormsig*sigPID;
//        double toteffjpsikmclow=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*jpsikPID;
//   
//        double crosschecksiglow=decprodcutsig*effrecostrsig*(double(double(t_final_sig->GetEntries())/double(t_initial_sig->GetEntries())))*sigPID;
//        double crosscheckjpsikmclow=decprodcutjpsik*effrecostrjpsik*(double(double(t_final_norm->GetEntries())/double(t_initial_norm->GetEntries())))*jpsikPID;
//
//	double crosschecksiglowerr=calcEffErr(int(number_bkk_sig),t_final_sig->GetEntries());//still need to add on error from dec prodcut
//	double crosscheckjpsikmclowerr=calcEffErr(int(number_bkk_nor),t_final_norm->GetEntries());//still need to add on error from dec prodcut


 
//        out << "Efficiency & "<< " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$  & " << " $B^{+} \\rightarrow J\\psi\\ K^{+}$ \\\\" <<endl;   
//        out<<"\\hline"<<endl;
        out << "$\\varepsilon_{gen}$ &" << round_to_digits(decprodcutsig,3) << " & " << round_to_digits(decprodcutjpsik,3) <<" \\\\ "<<endl;
        out << "Events in Bookeeping &" << round_to_digits(number_bkk_sig,7) << " & " << round_to_digits(number_bkk_nor,7) <<" \\\\ "<<endl;
        out << "$\\varepsilon_{strip}$ &" << round_to_digits(effstripsig,3) << " & " << round_to_digits(effstripjpsik,3) <<" \\\\ "<<endl;
        out << "$\\varepsilon_{mctruth}$ &" << round_to_digits(effrecostrsig,3) << " & " << round_to_digits(effrecostrjpsik,3) <<" \\\\ "<<endl; 
        out << "$\\varepsilon_{trigger}$ &" << round_to_digits(efftriggersig,3) << " & " << round_to_digits(efftriggerjpsik,3) <<" \\\\ "<<endl;
        out << "$\\varepsilon_{J/\\psi}$ &" << round_to_digits(effjpsisig,3) << " & " << round_to_digits(effjpsijpsik,3) <<" \\\\ "<<endl;
        out << "$\\varepsilon_{qmin}$ &" << round_to_digits(effqminsig,3) << " & " << round_to_digits(effqminjpsik,3) <<" \\\\ "<<endl;
//        out << "$\\varepsilon_{myreco}$ &" << round_to_digits(effmyrecosig,3) << " & " << round_to_digits(effmyrecostrjpsik,3) <<" \\\\ "<<endl;

        out << "$\\varepsilon_{combibdt}$ &" << round_to_digits(combibdtsig,3) << " & " << round_to_digits(combibdtjpsik,3) <<" \\\\ "<<endl;
        out << "$\\varepsilon_{misidbdt}$ &" << round_to_digits(misidbdtsig,3) << " & " << round_to_digits(misidbdtjpsik,3) <<" \\\\ "<<endl;
//        out << "$\\epsilon_{corm}$ &" << cormsig << " & " << cormjpsik <<" \\\\ "<<endl;
//        out << "$\\epsilon_{PID}$ &" << sigPID << " & " << jpsikPID <<" \\\\ "<<endl;
//        out<<"\\hline"<<endl;
//        out << "$\\epsilon_{totalNOFCME}$ &" << toteffsiglow << " & " << toteffjpsikmclow <<" \\\\ "<<endl;
//        out<<"\\hline"<<endl;
//        out << "$\\epsilon_{crosscheckNOFCME}$ &" << crosschecksiglow << " $\\pm$ "<< crosschecksiglowerr << " & " << crosscheckjpsikmclow <<" $\\pm$ "<< crosscheckjpsikmclowerr<<" \\\\ "<<endl;
        

//	double brfr=1e-8;
//	double ppbbX=284e-6;
//	double bBplus= 2*0.4;
//	double datacoll=3e15;
//	double decprodcut =0.185;
//	double effrecostrip= 0.111;
//
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{MC efficiency comparison between Signal and Part Reco samples up to multivariate selection. There was no trigger applied on the part reco sample as it would be mismodelled as most of trigger lines selected look for muon, hence taking conservative approach of not requiring trigger will over-estimate the partreco efficiency for this category.}"<<endl;
        out<<"\\end{table}"<<endl;

double sigfirst=decprodcutsig*effstripsig*effrecostrsig*efftriggersig*effqminsig*effjpsisig;
double partrecofisrt=decprodcutjpsik*effstripjpsik*effrecostrjpsik*efftriggerjpsik*effqminjpsik*effjpsijpsik;
double firstratio=double(double(sigfirst)*double(1.0e-8))/double(double(partrecofisrt)*double(4.10e-7));
double sigsec=decprodcutsig*effstripsig*effrecostrsig*efftriggersig*effqminsig*effjpsisig*combibdtsig*misidbdtsig;
double partrecosec=decprodcutjpsik*effstripjpsik*effrecostrjpsik*efftriggerjpsik*effqminjpsik*effjpsijpsik*combibdtjpsik*misidbdtjpsik;
double secratio=double(double(sigsec)*double(1.0e-8))/double(double(partrecosec)*double(4.10e-7));

out<<" Assuming branching fractions $\\mathcal{B}(B^+ \\rightarrow \\mu^+ \\mu^- \\mu^+ ) = 1\\times10^{-8}$ and $\\mathcal{B}(B^+ \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-} ) = 4.10\\times10^{-7}$  \\newline Before BDTs: \\newline $ \\frac{\\mathcal{B}(B^+ \\rightarrow \\mu^+ \\mu^- \\mu^+ ) = 1\\times10^{-8} \\times \\varepsilon_{reco = gen + strip + truthm + jpsi + trigger + qmin}="<<sigfirst<<"}{\\mathcal{B}(B^+ \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-} ) = 4.10\\times10^{-7} \\times \\varepsilon_{reco = }= "<<partrecofisrt<< "} = \\frac{ "<<sigfirst*1.0e-8<<" }{ "<<partrecofisrt*4.10e-7<<"} = "<<firstratio<<" $ "<<endl;

out<<" After BDTs: \\newline $ \\frac{\\mathcal{B}(B^+ \\rightarrow \\mu^+ \\mu^- \\mu^+ ) = 1\\times10^{-8} \\times \\varepsilon_{reco} = " <<sigfirst<<" \\times \\varepsilon_{bdts}= "<<combibdtsig*misidbdtsig<<" }{ \\mathcal{B}(B^+ \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-} ) = 4.10\\times10^{-7} \\times \\varepsilon_{reco} = " <<partrecofisrt<< " \\times \\varepsilon_{bdts}= " << combibdtjpsik*misidbdtjpsik <<"} = \\frac{ "<<sigsec*1.0e-8<<" }{ "<<partrecosec*4.10e-7<<" }  = "<< secratio<<" $"<<endl;


       ValError decprod(0.1606,0.0004);
       ValError decprod_sig(0.1856,0.0011);
   
       double syst(0.40e-6);
       double stat(0.12e-6);
       
 
       ValError assumedbr1(4.17e-6,addstatandsyst(0.12e-6, 0.40e-6));//lhcb rho and omega region
       ValError assumedbr2(9.8e-2,0.7e-2);//pdg dlnu anything
       ValError assumedbr=assumedbr1*assumedbr2;

       ValError bquark2011(288.0e-6,addstatandsyst(4.0e-6,48.0e-6));//newest lhcb paper
       ValError bquark2012(298.0e-6,addstatandsyst(3.0e-6,36.0e-6));//newest lhcb paper
       ValError bquark2016(600.6e-6,addstatandsyst(5.85e-6,55.77e-6));//newest lhcb paper
     
       ValError l2011lumi(0.985e15,0.00017e15);//not precisel
       ValError l2012lumi(1.9858e15,0.00017e15);//not precise
       ValError l2016lumi(1.612e15,0.00017e15);//not precise


       ValError bquark=(bquark2011*l2011lumi)+(bquark2012*l2012lumi)+(bquark2016*l2016lumi);

       ValError fragfrac(34.4e-2,2.1e-2); //review 


       //total stuff//

       int numofontriesnofcme=getmyentries("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root", "DecayTree");
       ValError passed(double(numofontriesnofcme),double(sqrt(numofontriesnofcme)));

       ValError total(double(number_bkk_nor),double(sqrt(number_bkk_nor)));

       ValError seleff=getRatioBinomial(passed, total);

       ValError tot2011=2.0*(assumedbr*fragfrac*l2011lumi*bquark2011*decprod*seleff);
       ValError tot2012=2.0*(assumedbr*fragfrac*l2012lumi*bquark2012*decprod*seleff);
       ValError tot2016=2.0*(assumedbr*fragfrac*l2016lumi*bquark2016*decprod*seleff);


       //low fcme//

       int numofontriesnofcme_low=getmyentries("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root", "DecayTree");
       ValError passed_low(double(numofontriesnofcme_low),double(sqrt(numofontriesnofcme_low)));

       ValError seleff_low=getRatioBinomial(passed_low, total);

       ValError tot2011_low=2.0*(assumedbr*fragfrac*l2011lumi*bquark2011*decprod*seleff_low);
       ValError tot2012_low=2.0*(assumedbr*fragfrac*l2012lumi*bquark2012*decprod*seleff_low);
       ValError tot2016_low=2.0*(assumedbr*fragfrac*l2016lumi*bquark2016*decprod*seleff_low);
       //high fcme//

       int numofontriesnofcme_high=getmyentries("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root", "DecayTree");
       ValError passed_high(double(numofontriesnofcme_high),double(sqrt(numofontriesnofcme_high)));

       ValError seleff_high=getRatioBinomial(passed_high, total);


       ValError tot2011_high=2.0*(assumedbr*fragfrac*l2011lumi*bquark2011*decprod*seleff_high);
       ValError tot2012_high=2.0*(assumedbr*fragfrac*l2012lumi*bquark2012*decprod*seleff_high);
       ValError tot2016_high=2.0*(assumedbr*fragfrac*l2016lumi*bquark2016*decprod*seleff_high);

       //for error//

       int numofontriesnofcme_uptobdts=getmyentries("/vols/lhcb/ss4314/final_tuples_analyser/mc/partreco_mc/2012/bin/MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut.root", "DecayTree");
       ValError passed_uptobdts(double(numofontriesnofcme_uptobdts),double(sqrt(numofontriesnofcme_uptobdts)));
   
       int numofontriesnofcme_uptobdts_n=getmyentries("/vols/lhcb/ss4314/final_tuples_analyser/mc/partreco_mc/2012/bin/MC_PartReco_MCtruth_trigger_Jpsi_qmincut.root", "DecayTree");
       ValError passed_uptobdts_n(double(numofontriesnofcme_uptobdts_n),double(sqrt(numofontriesnofcme_uptobdts_n)));

       int numofontriesnofcme_correction_1=getmyentries("/vols/lhcb/ss4314/final_tuples_analyser/mc/partreco_mc/2012/bin/MC_PartReco_MCtruth_trigger_Jpsi.root", "DecayTree");
       ValError passed_correction_1(double(numofontriesnofcme_correction_1),double(sqrt(numofontriesnofcme_correction_1)));
       int numofontriesnofcme_correction_2=getmyentries("/vols/lhcb/ss4314/final_tuples_analyser/mc/partreco_mc/2012/bin/MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared.root", "DecayTree");
       ValError passed_correction_2(double(numofontriesnofcme_correction_2),double(sqrt(numofontriesnofcme_correction_2)));
       ValError correction=getRatioBinomial(passed_correction_2,passed_correction_1);

       int numofontriesnofcme_afterbdts=getmyentries("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic.root", "DecayTree");
       ValError passed_afterbdts(double(numofontriesnofcme_afterbdts),double(sqrt(numofontriesnofcme_afterbdts)));

       ValError seleff_uptobdts=getRatioBinomial(passed_uptobdts, total);
       ValError seleff_afterbdts=getRatioBinomial(passed_afterbdts, total);
       ValError seleff_bdts=getRatioBinomial(passed_afterbdts, passed_uptobdts_n);

       vector<int> numberofentriess;
     
       vector<string> filenames;
  
       vector<ValError> effs;

       vector<string> names;

       filenames.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/partreco_mc/2012/bin/MC_PartReco_MCtruth.root");
       filenames.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/partreco_mc/2012/bin/MC_PartReco_MCtruth_trigger.root");
       filenames.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/partreco_mc/2012/bin/MC_PartReco_MCtruth_trigger_Jpsi.root");
       filenames.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/partreco_mc/2012/bin/MC_PartReco_MCtruth_trigger_Jpsi_qmincut.root");
       filenames.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic.root");
   //    filenames.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic.root");
       filenames.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic.root");

       vector<string> filenames_sig;

       vector<ValError> effs_sig;

       vector<string> names_sig;

       int numsig(1114130);
    
       filenames_sig.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/forpartreco/Bu23MuNuMC2012_MCtruth.root");
       filenames_sig.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/forpartreco/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger.root");
       filenames_sig.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/forpartreco/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi.root");
       filenames_sig.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/forpartreco/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root");
       filenames_sig.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic.root");
     filenames_sig.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic.root"); 

       names.push_back("trig");
       names.push_back("jpsi");
       names.push_back("qmincut");
       names.push_back("combi");
       names.push_back("misid");

       ValError sig_total(double(numsig),double(sqrt(numsig)));
       ValError sig_passed(double(numsig),double(sqrt(numsig)));

      // ValError seleff=getRatioBinomial(passed, total);

       int sig_uptobdts=getmyentries(filenames_sig.at(3), "DecayTree");
       ValError sig_passed_uptobdts(double(sig_uptobdts),double(sqrt(sig_uptobdts)));
   

       int sig_afterbdts=getmyentries(filenames_sig.at(5), "DecayTree");
       ValError sig_passed_afterbdts(double(sig_afterbdts),double(sqrt(sig_afterbdts)));

       ValError seleff_uptobdts_sig=getRatioBinomial(sig_passed_uptobdts, sig_total);
       ValError seleff_afterbdts_sig=getRatioBinomial(sig_passed_afterbdts, sig_total);
       ValError seleff_bdts_sig=getRatioBinomial(sig_passed_afterbdts, sig_passed_uptobdts);

       for (int i(1); i<6; i++)
       {
       int before=getmyentries(filenames.at(i-1), "DecayTree");
       int after=getmyentries(filenames.at(i), "DecayTree");
       ValError before_err(double(before),double(sqrt(before)));
       ValError after_err(double(after),double(sqrt(after)));
       ValError neweff=getRatioBinomial(after_err,before_err);
       effs.push_back(neweff);
       }

       double fitreff(0.261523);
       double lowfcme(0.498904);
       double highfcme(0.501096);

       double alto=fitreff*combibdtjpsik*misidbdtjpsik*effqminjpsik*effjpsijpsik*efftriggerjpsik*effrecostrjpsik*effstripjpsik;

       out<<"\\newpage"<<endl;

        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{l | l | l | l}"<<endl; 
        out<<"\\hline"<<endl;
        out<<"Properties & 2011 & 2012 & 2016 "<<" \\\\ "<<endl;
        
        out<<"\\hline"<<endl;
        out<<"\\hline"<<endl;

        out << "$\\varepsilon_{gen}$ &"<<"-  & " << decprod.val<<"$\\pm$" <<decprod.err<<" & - " <<" \\\\ "<<endl;
        out << " Assumed $\\mathcal{B}(B^+ \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-})$ &"<< assumedbr.val<<"$\\pm$"<<assumedbr.err<<"& "<<assumedbr.val<<"$\\pm$"<<assumedbr.err<<" &"<< assumedbr.val<<"$\\pm$"<<assumedbr.err<<" \\\\ "<<endl;
        out << "$\\sigma(p\\bar{p})$ & "<<bquark2011.val<<"$\\pm$" <<bquark2011.err<<" & "<<bquark2012.val<<"$\\pm$" <<bquark2012.err<<" & "<<bquark2016.val<<"$\\pm$" <<bquark2016.err<<" \\\\ "<<endl;
        out << "$2*f(b\\rightarrow B^{+})$ "<<"& 2$\\times$"<<fragfrac.val<<"$\\pm$"<<fragfrac.err<<"& 2$\\times$"<<fragfrac.val<<"$\\pm$"<<fragfrac.err<<"& 2$\\times$"<<fragfrac.val<<"$\\pm$"<<fragfrac.err<<" \\\\ "<<endl;
        out << "$\\mathcal{L}$ &"<<l2011lumi.val<<"$\\pm$"<<l2011lumi.err <<" b$^{-1}$ &"<<l2012lumi.val<<"$\\pm$"<<l2012lumi.err <<" b$^{-1}$ &  "<<l2016lumi.val<<"$\\pm$"<<l2016lumi.err <<" b$^{-1}$ \\\\ "<<endl;
        out << "$\\varepsilon_{gen}$ &"<<"-  & " << decprod.val<<"$\\pm$" <<decprod.err<<" & - " <<" \\\\ "<<endl;
        out << "Events in Bookeeping & " << number_bkk_nor <<" & "<<" \\\\ "<<endl;
        out << "$\\varepsilon_{strip}$ & & " << round_to_digits(effstripjpsik,3) <<" & "<<" \\\\ "<<endl;
        out << "$\\varepsilon_{mctruth}$ & & " << round_to_digits(effrecostrjpsik,3)<<" & " <<" \\\\ "<<endl; 
        out << "$\\varepsilon_{trigger}$ & & " << round_to_digits(efftriggerjpsik,3)<< " & " <<" \\\\ "<<endl;
        out << "$\\varepsilon_{J/\\psi}$ & & " << round_to_digits(effjpsijpsik,3) <<" & "<<" \\\\ "<<endl;
        out << "$\\varepsilon_{qmin}$ & & " << round_to_digits(effqminjpsik,3)<<" & "<<" \\\\ "<<endl;
//        out << "$\\varepsilon_{myreco}$ &" << round_to_digits(effmyrecosig,3) << " & " << round_to_digits(effmyrecostrjpsik,3) <<" \\\\ "<<endl;
        for (int i(0); i<5;i++)
        {
        out << "$\\varepsilon_{"+names.at(i)+"}$ & & " <<(effs.at(i)).val<<" $\\pm$ "<<(effs.at(i)).err<<" & "<<" \\\\ "<<endl;
        }

        out<<"\\hline"<<endl;
        out << "$\\varepsilon_{correction}$ & & " <<(correction).val<<" $\\pm$ "<<(correction).err<<" & "<<" \\\\ "<<endl;
        out << "$\\varepsilon_{uptobdts}$ & & " <<(seleff_uptobdts*decprod).val<<" $\\pm$ "<<(seleff_uptobdts*decprod).err<<" & "<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\varepsilon_{combibdt}$ & & " << round_to_digits(combibdtjpsik,3)<<" &" <<" \\\\ "<<endl;
        out << "$\\varepsilon_{misidbdt}$ & & " << round_to_digits(misidbdtjpsik,3)<<" & " <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\varepsilon_{bdts}$ & & " <<(seleff_bdts).val<<" $\\pm$ "<<(seleff_bdts).err<<" & "<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\varepsilon_{afterbdts}$ & & " <<(seleff_afterbdts*decprod).val<<" $\\pm$ "<<(seleff_afterbdts*decprod).err<<" & "<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out <<  "$\\varepsilon_{fitrange}$ & & "<< fitreff<<" & " <<" \\\\ "<<endl;
        out <<  "$\\varepsilon_{lowfcme}$ & & "<< lowfcme<<" & " <<" \\\\ "<<endl;
        out <<  "$\\varepsilon_{highfcme}$ & & "<< highfcme<<" & " <<" \\\\ "<<endl;

        out << "$\\varepsilon_{multitotalseleff}$ & & " << alto<<" & " <<" \\\\ "<<endl;
        out << "$\\varepsilon_{totalseleff}$ & & " << seleff.val<<"$\\pm$"<<seleff.err<<" & " <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "N &"<< tot2011.val<<"$\\pm$"<<tot2011.err<<" & "<<tot2012.val<<"$\\pm$"<<tot2012.err<<" & "<<tot2016.val<<"$\\pm$"<<tot2016.err <<" \\\\ "<<endl;    
        out<<"\\hline"<<endl;

        out<<"\\hline"<<endl;
        out << "$\\varepsilon_{uptobdts_sig}$ & & " <<(seleff_uptobdts_sig*decprod_sig).val<<" $\\pm$ "<<(seleff_uptobdts_sig*decprod_sig).err<<" & "<<" \\\\ "<<endl;
        out << "$\\varepsilon_{sig_bdts}$ & & " <<(seleff_bdts_sig).val<<" $\\pm$ "<<(seleff_bdts_sig).err<<" & "<<" \\\\ "<<endl;
        out << "$\\varepsilon_{afterbdts}$ & & " <<(seleff_afterbdts_sig*decprod_sig).val<<" $\\pm$ "<<(seleff_afterbdts_sig*decprod_sig).err<<" & "<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Calculation of Part Reco, assuming 2012 efficiencies but extrapolating to 2011,2012,2016}"<<endl;
        out<<"\\end{table}"<<endl;


        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{l | l | l | l}"<<endl; 
        out<<"\\hline"<<endl;
        out<<"Properties & 2011 & 2012 & 2016 "<<" \\\\ "<<endl;
        
        out<<"\\hline"<<endl;
        out<<"\\hline"<<endl;
        out << "$\\mathcal{L}$ &"<<(1e-15)*(l2011lumi.val)<<"$\\pm$"<<(1e-15)*(l2011lumi.err) <<" fb$^{-1}$ &"<<(1e-15)*(l2012lumi.val)<<"$\\pm$"<<(1e-15)*(l2012lumi.err) <<" fb$^{-1}$ &  "<<(1e-15)*(l2016lumi.val)<<"$\\pm$"<<(1e-15)*(l2016lumi.err) <<" fb$^{-1}$ \\\\ "<<endl;
        out << "$\\sigma(pp \\rightarrow b\\bar{b})$ & "<<(1e6)*(bquark2011.val)<<"$\\pm$" <<(1e6)*(bquark2011.err)<<"$\\mu$b$^{-1}$ & "<<(1e6)*(bquark2012.val)<<"$\\pm$" <<(1e6)*(bquark2012.err)<<"$\\mu$b$^{-1}$ & "<<(1e6)*(bquark2016.val)<<"$\\pm$" <<(1e6)*(bquark2016.err)<<"$\\mu$b$^{-1}$ \\\\ "<<endl;
        out << "$2.0\\times f(b\\rightarrow B^{+})$ "<<"& 2$\\times$"<<fragfrac.val<<"$\\pm$"<<fragfrac.err<<"& 2$\\times$"<<fragfrac.val<<"$\\pm$"<<fragfrac.err<<"& 2$\\times$"<<fragfrac.val<<"$\\pm$"<<fragfrac.err<<" \\\\ "<<endl;
        out << "$\\mathcal{B}(B^+ \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-})$ &"<< assumedbr.val<<"$\\pm$"<<assumedbr.err<<"& "<<assumedbr.val<<"$\\pm$"<<assumedbr.err<<" &"<< assumedbr.val<<"$\\pm$"<<assumedbr.err<<" \\\\ "<<endl;
        out << "$\\varepsilon_{gen}$ &"<<"-  & " << decprod.val<<"$\\pm$" <<decprod.err<<" & - " <<" \\\\ "<<endl;
        out << "$\\varepsilon_{totalsel}$ & & " << seleff.val<<"$\\pm$"<<seleff.err<<" & " <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "N &"<< tot2011.val<<"$\\pm$"<<tot2011.err<<" & "<<tot2012.val<<"$\\pm$"<<tot2012.err<<" & "<<tot2016.val<<"$\\pm$"<<tot2016.err <<" \\\\ "<<endl;    
        out << "N low &"<< tot2011_low.val<<"$\\pm$"<<tot2011_low.err<<" & "<<tot2012_low.val<<"$\\pm$"<<tot2012_low.err<<" & "<<tot2016_low.val<<"$\\pm$"<<tot2016_low.err <<" \\\\ "<<endl;    
        out << "N high &"<< tot2011_high.val<<"$\\pm$"<<tot2011_high.err<<" & "<<tot2012_high.val<<"$\\pm$"<<tot2012_high.err<<" & "<<tot2016_high.val<<"$\\pm$"<<tot2016_high.err <<" \\\\ "<<endl;    
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Calculation of number of events that comes from partially reconstructed backgrounds, assuming 2012 efficiencies but extrapolating to 2011,2012,2016 samples. $\\mathcal{B}(B^+ \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-})$ is obtained by multiplying  $\\mathcal{B}(D^{0} \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-}) $ ="<<assumedbr1.val<<"$\\pm$"<<assumedbr1.err<<    " and $\\mathcal{B}(B^{+} \\rightarrow D l^{+} \\nu $ anything) = "<<assumedbr2.val<<"$\\pm$"<<assumedbr2.err<<". }"<<endl;
        out<<"\\label{tab:prsum}"<<endl;
        out<<"\\end{table}"<<endl;

        out<<"FOR ANA"<<endl;
        out<<"\\begin{equation}"<<endl;
        out<<"N^{year}= \\mathcal{L} \\times \\sigma(pp \\rightarrow b\\bar{b}) \\times 2.0 \\times f(b\\rightarrow B^{+}) \\times \\mathcal{B}(B^+ \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-}) \\times \\varepsilon_{gen} \\times \\varepsilon_{totalsel}"<<endl;
        out<<"\\end{equation}"<<endl;
        out<<" yielding N = "<< (tot2011+tot2012+tot2016).val<< " $\\pm$ " <<(tot2011+tot2012+tot2016).err << " for NOFCME " <<(tot2011_low+tot2012_low+tot2016_low).val<< " $\\pm$ " <<(tot2011_low+tot2012_low+tot2016_low).err<<" for lowFCME and "<<(tot2011_high+tot2012_high+tot2016_high).val<< " $\\pm$ " <<(tot2011_high+tot2012_high+tot2016_high).err<< " for highFCME" <<endl;





//$
///


//        out<<"\\end{table}"<<endl;
//        out<<"Calculation of the Single Event Sensitivity"<<endl;
//        out<<"\\begin{equation}"<<endl;
//        out<<"\\mathcal{B}(B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu) = \\frac{\\mathcal{B}(B^{+} \\rightarrow J\\psi\\ K^{+}) \\times \\epsilon_{B^{+} \\rightarrow J\\psi\\ K^{+}}}{N_{(B^{+} \\rightarrow J\\psi\\ K^{+})} \\times \\epsilon_{B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu}} \\times N_{B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu} "<<endl;
//        out<<"\\end{equation}"<<endl;
//      
//        double numberofevents_low = 177178;
//        double brfr1=1.028e-3*5.88e-2;
//        double expsensitivity_low = (brfr1*crosscheckjpsikmclow)/(numberofevents_low*crosschecksiglow);
//        //double expsensitivity_low_error = sqrt((pow(crosschecksiglowerr/crosschecksiglow),2)+(pow(crosscheckjpsikmclowerr/crosscheckjpsikmclow),2))*expsensitivity_low;      
//        double expsensitivity_low_error = (sqrt((double(crosschecksiglowerr/crosschecksiglow)*double(crosschecksiglowerr/crosschecksiglow))+((double(crosscheckjpsikmclowerr/crosscheckjpsikmclow))*(double(crosscheckjpsikmclowerr/crosscheckjpsikmclow)))))*expsensitivity_low; 
//
//        out<<"Assuming $B^{+} \\rightarrow J/\\psi \\ K^{+})$ = 1.028e-3 (PDG 2014)  is "<<endl;
//        //out<<"\\newline"<<endl;
//        out<<"and $J/\\psi \\rightarrow \\mu^{-} \\mu^{+}$ = 5.88e-2 "<<endl;
//        out<<"\\newline"<<endl;
//        out<<"Observed in: "<<numberofevents_low<<" $J/\\psi \\ K^{+}$  events."<<endl;
//        out<<"\\newline"<<endl;
//        out<<"Efficiency ratio, i.e efftotjpsik/efftot3mu is "<< double(crosscheckjpsikmclow/crosschecksiglow)<<endl;
//        out<<"\\newline"<<endl;
//        out<<"Efficiency ratio with numofevents obs, i.e efftotjpsik/efftot3mu is "<< double(crosscheckjpsikmclow/(crosschecksiglow*numberofevents_low))<<endl;
//        out<<"\\newline"<<endl;        
//        out<<"Expected Single Event Sensitivity NOFCME: "<< expsensitivity_low <<endl;
//        out<<"Error is $\\pm$ "<<expsensitivity_low_error;
//
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
//        numofevents_per_lumi=double(numberofevents_low/luminosity);
//        numofevents=numberofevents_low;
//        effi_sig=crosschecksiglow;
//        effi_norm=crosscheckjpsikmclow;
//        sensitivity=expsensitivity_low;
//        effi_ratio=double(crosscheckjpsikmclow/crosschecksiglow);
//        effi_numobs=double(crosscheckjpsikmclow/(crosschecksiglow*numberofevents_low));
//        effi_corr_lumi=double(numberofevents_low/(crosscheckjpsikmclow*luminosity));
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
//
//        out<<"\\newpage"<<endl;
//        out<<"$\\epsilon_{reco}$"<<endl;
//        out<<"for \\textbf{B23MuNu}: "<<endl;
//        out<<"\\newline"<<endl;
//        out<<"\\newline"<<endl;
//        out<<"\\textbf{muon filter}: " << " (MIPCHI2DV(PRIMARY) $>$ 9.0 ) and (TRCHI2DOF $<$ 3.0) and (TRGHP $<$ 0.35)"<<endl;
//        out<<"\\newline"<<endl;
//        out<<"\\newline"<<endl;
//        out<<"\\textbf{mother filter}: " <<  "(BPVDIRA $>$ 0.999) and (PT $>$ 2000) and (BPVVDCHI2 $>$ 50) and (M $>$ 0) and (M $<$ 7500) and (BPVCORRM $>$ 2500) and (BPVCORRM $<$ 10000) and (VFASPF(VCHI2/VDOF)$<$4)" << endl;
//        out<<"\\newline"<<endl;
//        out<<"\\newline"<<endl;
//        out<<"$\\epsilon_{reco}$"<<endl;
//        out<<"for \\textbf{B2JpsiK}: "<<endl;
//        out<<"\\newline"<<endl;
//        out<<"\\newline"<<endl;
//        out<<"\\textbf{muon filter}: (StdAllLooseMuons so isMuon==true): " << " (MIPCHI2DV(PRIMARY) $>$ 9.0 ) and (TRGHP $<$ 0.5)"<<endl;
//        out<<"\\newline"<<endl;
//        out<<"\\newline"<<endl;
//        out<<"\\textbf{K filter}: (StdAllNoPIDsKaons): " << "(VFASPF(VCHI2/VDOF) $<$ 12 and (BPVDIRA) $>$ -0.9 and (MIPCHI2DV(PRIMARY) $>$ 6.0 and (HASRICH)"<<endl;
//        out<<"\\newline"<<endl;
//        out<<"\\newline"<<endl;
//        out<<"\\textbf{Jpsi filter} "<<" (VFASPF(VCHI2/VDOF) $<$ 12 and (BPVDIRA) $>$ -0.9 and  BPVVDCHI2 $>$ 9.0 and (MAXTREE(ISBASIC,MIPCHI2DV(PRIMARY)) $>$ 9.0 "<<endl;
//        out<<"\\newline"<<endl;
//        out<<"\\newline"<<endl;
//        out<<"\\textbf{mother filter}: " <<  "(abs(SUMQ) $<$ 3) and (BPVIPCHI2() $<$ 16) and (BPVDIRA $>$ 0.9999) and (BPVVDCHI2 $>$ 121) and (M $>$ 4700) and (M $<$ 7100) and (VFASPF(VCHI2/VDOF)$<$8) and (MAXTREE(ISBASIC,MIPCHI2DV(PRIMARY)) $>$ 9 " << endl;
//
//
 
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



