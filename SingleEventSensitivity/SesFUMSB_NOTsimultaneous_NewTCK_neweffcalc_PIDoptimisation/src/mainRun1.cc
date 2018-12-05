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
        out.open(("SingleEvRun1"+PIDcut+".tex").c_str());

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

	double number_bkk_nor(0);
	double decprodcutjpsik(0.16216);
        double decprodcutjpsik_err(0.00024);
	double effrecostrjpsik(0);
	double effmyrecostrjpsik(0);
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

        double sigPID=readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin/B23MuNuMC2012"+PIDcut+"Strip21_selected.root").c_str(), "DecayTree", "PIDweight");
        double jpsikPID=readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin/JpsiKMC2012"+PIDcut+".root").c_str(), "DecayTree", "mcweight");

  //      double highFCMEsigPID=0.680185;
   //     double highFCMEjpsikPID=0.716373;

   //     double sigPID = 0.663465;
   //     double jpsikPID = 0.71386;       

	TFile f_final_sig("/vols/lhcb/ss4314/cutonFitRange/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root","READ");
	TTree* t_final_sig =(TTree*)f_final_sig.Get(("DecayTree"));

	TFile f_final_norm("/vols/lhcb/ss4314/cutonFitRange/FUMSB_simultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root","READ");
	TTree* t_final_norm =(TTree*)f_final_norm.Get(("DecayTree"));

	TFile f_initial_sig("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/Bu23MuNuMC2012_MCtruth.root","READ");
	TTree* t_initial_sig =(TTree*)f_initial_sig.Get(("DecayTree"));

	TFile f_initial_norm("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root","READ");
	TTree* t_initial_norm =(TTree*)f_initial_norm.Get(("DecayTree"));

 
        double toteffsiglow=decprodcutsig*effrecostrsig*effmyrecosig*combibdtsig*misidbdtsig*cormsig*sigPID;
        double toteffjpsikmclow=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*jpsikPID;
   
        double crosschecksiglow=decprodcutsig*effrecostrsig*(double(double(t_final_sig->GetEntries())/double(t_initial_sig->GetEntries())))*sigPID;
        double crosscheckjpsikmclow=decprodcutjpsik*effrecostrjpsik*(double(double(t_final_norm->GetEntries())/double(t_initial_norm->GetEntries())))*jpsikPID;

	double crosschecksiglowerr=calcEffErr(int(number_bkk_sig),t_final_sig->GetEntries());//still need to add on error from dec prodcut
	double crosscheckjpsikmclowerr=calcEffErr(int(number_bkk_nor),t_final_norm->GetEntries());//still need to add on error from dec prodcut

        //-------------Dec Prod Cut-------------------//

        ValError sig_decprod(decprodcutsig,decprodcutsig_err);
        ValError jpsik_decprod(decprodcutjpsik,decprodcutjpsik_err);
           

        //-------------All other selection------------//

        ValError sig_othereff_passed(double(t_final_sig->GetEntries()),sqrt(double(t_final_sig->GetEntries())));
        ValError jpsik_othereff_passed(double(t_final_norm->GetEntries()),sqrt(double(t_final_norm->GetEntries())));

        ValError sig_othereff_total(number_bkk_sig,sqrt(number_bkk_sig));
        ValError jpsik_othereff_total(number_bkk_nor,sqrt(number_bkk_nor));

        ValError sig_othereff=getRatioBinomial(sig_othereff_passed,sig_othereff_total);
        ValError jpsik_othereff=getRatioBinomial(jpsik_othereff_passed,jpsik_othereff_total);

        //------------PID estuff no error so far-------//
        ValError sig_pid(readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin/B23MuNuMC2012"+PIDcut+"Strip21_selected.root").c_str(), "DecayTree", "PIDweight"),0.005);
        ValError jpsik_pid(readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin/JpsiKMC2012"+PIDcut+".root").c_str(), "DecayTree", "mcweight"),0.0011);


        //-------------Errors alltogether

        ValError finalprod_sig=sig_decprod*sig_othereff*sig_pid;
        ValError finalprod_jpsik=jpsik_decprod*jpsik_othereff*jpsik_pid;
 
        out << "Efficiency & "<< " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$  & " << " $B^{+} \\rightarrow J\\psi\\ K^{+}$ \\\\" <<endl;   
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{decprodcut}$ &" << decprodcutsig << " & " << decprodcutjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{reco}$ &" << effrecostrsig << " & " << effrecostrjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{myreco}$ &" << effmyrecosig << " & " << effmyrecostrjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{combibdt}$ &" << combibdtsig << " & " << combibdtjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{misidbdt}$ &" << misidbdtsig << " & " << misidbdtjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{corm}$ &" << cormsig << " & " << cormjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{PID}$ &" << sigPID << " & " << jpsikPID <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{totalNOFCME}$ &" << toteffsiglow << " & " << toteffjpsikmclow <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{crosscheckNOFCME}$ &" << crosschecksiglow << " $\\pm$ "<< crosschecksiglowerr << " & " << crosscheckjpsikmclow <<" $\\pm$ "<< crosscheckjpsikmclowerr<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"$\\epsilon_{neweffapp_nodecprodcut_nopid}$ &"<<sig_othereff <<" & "<<jpsik_othereff<<" \\\\ "<<endl;
        out<<"$\\epsilon_{neweffapp_decprodcut}$ &"<<sig_decprod <<" & "<<jpsik_decprod<<" \\\\ "<<endl;
        out<<"$\\epsilon_{neweffapp_decprocut_nopid}$ &"<<sig_decprod*sig_othereff <<" & "<<jpsik_decprod*jpsik_othereff<<" \\\\ "<<endl;
        out<<"$\\epsilon_{neweffapp_pid}$ &"<<sig_pid <<" & "<<jpsik_pid<<" \\\\ "<<endl;
        out<<"$\\epsilon_{neweffapp}$ &"<<finalprod_sig <<" & "<<finalprod_jpsik<<" \\\\ "<<endl;
   

	double brfr=1e-8;
	double ppbbX=284e-6;
	double bBplus= 2*0.4;
	double datacoll=3e15;
	double decprodcut =0.185;
	double effrecostrip= 0.111;

        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Single event sensitivity}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"Calculation of the Single Event Sensitivity"<<endl;
        out<<"\\begin{equation}"<<endl;
        out<<"\\mathcal{B}(B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu) = \\frac{\\mathcal{B}(B^{+} \\rightarrow J\\psi\\ K^{+}) \\times \\epsilon_{B^{+} \\rightarrow J\\psi\\ K^{+}}}{N_{(B^{+} \\rightarrow J\\psi\\ K^{+})} \\times \\epsilon_{B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu}} \\times N_{B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu} "<<endl;
        out<<"\\end{equation}"<<endl;
      
        double numberofevents_low = returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/NOFCME/FitResults/FitControl_Run1_"+PIDcut+".root").c_str(), "FitControl_Run1", "NumNormObs");

        cout<<"the numofobs ev is "<< numberofevents_low <<endl;
        cout<<"the error is" << double(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/NOFCME/FitResults/FitControl_Run1_"+PIDcut+".root").c_str(), "FitControl_Run1", "NumNormObs_Err"))<<endl;

        ValError b2jpsik(1.026e-3,0.031e-3);
        ValError jpsik2mumu(5.961e-2,0.033e-2);

        ValError b2jpsikjpsik2mumu=b2jpsik*jpsik2mumu;

        ValError numberofobsevents(double(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/NOFCME/FitResults/FitControl_Run1_"+PIDcut+".root").c_str(), "FitControl_Run1", "NumNormObs")),double(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/NOFCME/FitResults/FitControl_Run1_"+PIDcut+".root").c_str(), "FitControl_Run1", "NumNormObs_Err")));
 
        ValError newses=((finalprod_jpsik*b2jpsikjpsik2mumu)/(finalprod_sig*numberofobsevents));

        double brfr1=1.028e-3*5.88e-2;
        double expsensitivity_low = (brfr1*crosscheckjpsikmclow)/(numberofevents_low*crosschecksiglow);
        //double expsensitivity_low_error = sqrt((pow(crosschecksiglowerr/crosschecksiglow),2)+(pow(crosscheckjpsikmclowerr/crosscheckjpsikmclow),2))*expsensitivity_low;      
        double expsensitivity_low_error = (sqrt((double(crosschecksiglowerr/crosschecksiglow)*double(crosschecksiglowerr/crosschecksiglow))+((double(crosscheckjpsikmclowerr/crosscheckjpsikmclow))*(double(crosscheckjpsikmclowerr/crosscheckjpsikmclow)))))*expsensitivity_low; 

        out<<"Assuming $B^{+} \\rightarrow J/\\psi \\ K^{+})$ = "<<b2jpsik<<" (PDG 2016)  is "<<endl;
        //out<<"\\newline"<<endl;
        out<<"and $J/\\psi \\rightarrow \\mu^{-} \\mu^{+}$ = "<<jpsik2mumu<<endl;
        out<<"\\newline"<<endl;
        out<<"Observed in: "<<numberofobsevents<<" $J/\\psi \\ K^{+}$  events."<<endl;
        out<<"\\newline"<<endl;
        out<<"OLD STUFF"<<endl;
        out<<"Efficiency ratio, i.e efftotjpsik/efftot3mu is "<< double(crosscheckjpsikmclow/crosschecksiglow)<<endl;
        out<<"\\newline"<<endl;
        out<<"Efficiency ratio with numofevents obs, i.e efftotjpsik/efftot3mu is "<< double(crosscheckjpsikmclow/(crosschecksiglow*numberofevents_low))<<endl;
        out<<"\\newline"<<endl;        
        out<<"Expected Single Event Sensitivity NOFCME: "<< expsensitivity_low <<endl;
        out<<"\\newline"<<endl;
        out<<"Error is $\\pm$ "<<expsensitivity_low_error;
        out<<"\\newline"<<endl;
        out<<"NEW STUFF"<<endl;
        out<<"\\newline"<<endl;
        out<<"Efficiency ratio, i.e efftotjpsik/efftot3mu is "<< finalprod_jpsik/finalprod_sig;
        out<<"\\newline"<<endl;
        out<<"Efficiency ratio with numofevents obs, i.e efftotjpsik/efftot3mu is "<< (finalprod_jpsik/(finalprod_sig*numberofobsevents))<<endl;
        out<<"\\newline"<<endl;        
        out<<"Expected Single Event Sensitivity NOFCME: "<<dbl2str(newses.val,17)<<"$\\pm$"<<dbl2str(newses.err,17) <<endl;
  //      out<<"Error is $\\pm$ "<<expsensitivity_low_error;
        out<<"\\newline"<<endl;
        out<<"FOR ANANOTE"<<endl;
        out<<"\\begin{equation}"<<endl;
        out<<"R^{21}_{NOFCME}(\\epsilon)=\\frac{"<<finalprod_sig.val<<"\\pm"<<finalprod_sig.err<<"}{"<<finalprod_jpsik.val<<"\\pm"<<finalprod_jpsik.err<<"}="<<(finalprod_sig/finalprod_jpsik).val <<"\\pm"<< (finalprod_sig/finalprod_jpsik).err<<endl;

        out<<"\\end{equation}"<<endl;
        out<<"\\begin{equation}"<<endl;
        out<<"\\alpha^{Run1}_{NOFCME}=\\frac{\\mathcal{B}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+})}{N^{Run1}_{NOFCME}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+}) \\times R^{21}_{NOFCME}(\\epsilon)}="<<newses.val<<"\\pm"<<newses.err <<endl;

        out<<"\\end{equation}"<<endl;





	TFile fillinfo(("../info/info_SES_2012_"+PIDcut+".root").c_str(),"UPDATE");
	TTree fillinfotree("Info_2012","Info_2012");

        double year;
        double numofevents;
        double numofevents_err;
        double effi_sig;
        double effi_norm;
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


	fillinfotree.Branch("year",&year,"year/D");// "File/C");
	fillinfotree.Branch("numofevents",&numofevents,"numofevents/D");// "Cut/C");
	fillinfotree.Branch("numofevents_err",&numofevents_err,"numofevents_err/D");// "Cut/C");
	fillinfotree.Branch("effi_sig",&effi_sig,"effi_sig/D");
	fillinfotree.Branch("effi_norm",&effi_norm, "effi_norm/D");
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
        


        year=2012.0;
        luminosity=2968.0;
        numofevents_per_lumi=double(numberofobsevents.val/luminosity);
        numofevents=numberofobsevents.val;
        numofevents_err=numberofobsevents.err;
        effi_sig=finalprod_sig.val;
        effi_norm=finalprod_jpsik.val;
        sensitivity=newses.val;
        sensitivity_err=newses.err;
	effi_ratio=double(finalprod_jpsik.val/finalprod_sig.val);
	effi_numobs=double(finalprod_jpsik.val/(finalprod_sig.val*numberofobsevents.val));
	effi_corr_lumi=double(numberofobsevents.val/(finalprod_jpsik.val*luminosity));
        effi_gen_sig=decprodcutsig;
        effi_gen_norm=decprodcutjpsik;
        effi_rec_sig=effrecostrsig;
        effi_rec_norm=effrecostrjpsik;
        effi_off_sig=effmyrecosig;
        effi_off_norm=effmyrecostrjpsik;
        effi_combi_sig=combibdtsig;
        effi_combi_norm=combibdtjpsik;
        effi_misid_sig=misidbdtsig;
        effi_misid_norm=misidbdtjpsik;
        effi_corm_sig=cormsig;
        effi_corm_norm=cormjpsik;
        effi_pid_sig=sigPID;
        effi_pid_norm=jpsikPID;
        fillinfotree.Fill();
	fillinfotree.Write("",TObject::kOverwrite);

        out<<"\\newpage"<<endl;
        out<<"$\\epsilon_{reco}$"<<endl;
        out<<"for \\textbf{B23MuNu}: "<<endl;
        out<<"\\newline"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\textbf{muon filter}: " << " (MIPCHI2DV(PRIMARY) $>$ 9.0 ) and (TRCHI2DOF $<$ 3.0) and (TRGHP $<$ 0.35)"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\textbf{mother filter}: " <<  "(BPVDIRA $>$ 0.999) and (PT $>$ 2000) and (BPVVDCHI2 $>$ 50) and (M $>$ 0) and (M $<$ 7500) and (BPVCORRM $>$ 2500) and (BPVCORRM $<$ 10000) and (VFASPF(VCHI2/VDOF)$<$4)" << endl;
        out<<"\\newline"<<endl;
        out<<"\\newline"<<endl;
        out<<"$\\epsilon_{reco}$"<<endl;
        out<<"for \\textbf{B2JpsiK}: "<<endl;
        out<<"\\newline"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\textbf{muon filter}: (StdAllLooseMuons so isMuon==true): " << " (MIPCHI2DV(PRIMARY) $>$ 9.0 ) and (TRGHP $<$ 0.5)"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\textbf{K filter}: (StdAllNoPIDsKaons): " << "(VFASPF(VCHI2/VDOF) $<$ 12 and (BPVDIRA) $>$ -0.9 and (MIPCHI2DV(PRIMARY) $>$ 6.0 and (HASRICH)"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\textbf{Jpsi filter} "<<" (VFASPF(VCHI2/VDOF) $<$ 12 and (BPVDIRA) $>$ -0.9 and  BPVVDCHI2 $>$ 9.0 and (MAXTREE(ISBASIC,MIPCHI2DV(PRIMARY)) $>$ 9.0 "<<endl;
        out<<"\\newline"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\textbf{mother filter}: " <<  "(abs(SUMQ) $<$ 3) and (BPVIPCHI2() $<$ 16) and (BPVDIRA $>$ 0.9999) and (BPVVDCHI2 $>$ 121) and (M $>$ 4700) and (M $<$ 7100) and (VFASPF(VCHI2/VDOF)$<$8) and (MAXTREE(ISBASIC,MIPCHI2DV(PRIMARY)) $>$ 9 " << endl;


 
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



