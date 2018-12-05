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
//#include "alltogetherMC.hpp"
#include<iostream>

using namespace std;


int main(){

        ofstream out;
        out.open("SingleEv2015.tex");

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

 
        double toteff;

        double decprodcutsig =0.185;
        double decprodcutjpsik =0.16743;

        double effrecostrsig= 0.10997;
        double effrecostrjpsik= 0.291137*0.573916;

        double effmyrecosig=0.496757;
        double effmyrecostrjpsik= 0.616901;


        double combibdtsig = 0.431;
        double combibdtjpsik = 0.482323;

        double misidbdtsig = 0.454419;
        double misidbdtjpsik = 0.501379;

        double cormsig=0.9289;
        double cormjpsik=0.99768;

        double lowFCMEsig=0.423718; 
        double lowFCMEjpsik=0.553374;

        double highFCMEsig=0.57628;
        double highFCMEjpsik=0.446626;

        double lowFCMEsigPID=0.403;
        double lowFCMEjpsikPID=0.522287;

        double highFCMEsigPID=0.39794238;
        double highFCMEjpsikPID=0.520014;

   //     double sigPID = 0.663465;
   //     double jpsikPID = 0.71386;       


 
        double toteffsiglow=decprodcutsig*effrecostrsig*effmyrecosig*combibdtsig*misidbdtsig*cormsig*lowFCMEsig*lowFCMEsigPID;
        double toteffjpsikmclow=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*lowFCMEjpsik*lowFCMEjpsikPID;
        double toteffsighigh=decprodcutsig*effrecostrsig*effmyrecosig*combibdtsig*misidbdtsig*cormsig*highFCMEsig*highFCMEsigPID;
        double toteffjpsikmchigh=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*highFCMEjpsik*highFCMEjpsikPID;
   
        double crosschecksiglow=decprodcutsig*effrecostrsig*(double(3991.0/104212.0))*lowFCMEsigPID;
        double crosscheckjpsikmclow=decprodcutjpsik*effrecostrjpsik*(double(57827.0/702105.0))*lowFCMEjpsikPID;
        double crosschecksighigh=decprodcutsig*effrecostrsig*(double(5248.0/104212.0))*highFCMEsigPID;
        double crosscheckjpsikmchigh=decprodcutjpsik*effrecostrjpsik*(double(46672.0/702105.0))*highFCMEjpsikPID;   

        double crosschecksiglowerr=(sqrt(double(3991.0)*(1.0-((double(3991.0)/double(1114130))))))*(1/double(1114130));
        double crosscheckjpsikmclowerr=(sqrt(double(57827.0)*(1.0-((double(57827.0)/double(8043820))))))*(1/double(8043820));
        double crosschecksighigherr=(sqrt(double(5248.0)*(1.0-((double(5248.0)/double(1114130))))))*(1/double(1114130));
        double crosscheckjpsikmchigherr=(sqrt(double(46672.0)*(1.0-((double(46672.0)/double(8043820))))))*(1/double(8043820));


 
        out << "Efficiency & "<< " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$  & " << " $B^{+} \\rightarrow J\\psi\\ K^{+}$ \\\\" <<endl;   
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{decprodcut}$ &" << decprodcutsig << " & " << decprodcutjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{reco}$ &" << effrecostrsig << " & " << effrecostrjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{myreco}$ &" << effmyrecosig << " & " << effmyrecostrjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{combibdt}$ &" << combibdtsig << " & " << combibdtjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{misidbdt}$ &" << misidbdtsig << " & " << misidbdtjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{corm}$ &" << cormsig << " & " << cormjpsik <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{lowFCME}$ &" << lowFCMEsig << " & " << lowFCMEjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{highFCME}$ &" << highFCMEsig << " & " << highFCMEjpsik <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{PIDlowFCME}$ &" << lowFCMEsigPID << " & " << lowFCMEjpsikPID <<" \\\\ "<<endl;
        out << "$\\epsilon_{PIDhighFCME}$ &" << highFCMEsigPID << " & " << highFCMEjpsikPID <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{totallowFCME}$ &" << toteffsiglow << " & " << toteffjpsikmclow <<" \\\\ "<<endl;
        out << "$\\epsilon_{totalhighFCME}$ &" << toteffsighigh << " & " << toteffjpsikmchigh <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{crosschecklowFCME}$ &" << crosschecksiglow << " $\\pm$ "<< crosschecksiglowerr << " & " << crosscheckjpsikmclow <<" $\\pm$ "<< crosscheckjpsikmclowerr<<" \\\\ "<<endl;
        out << "$\\epsilon_{crosscheckhighFCME}$ &" << crosschecksighigh << " $\\pm$ "<< crosschecksighigherr << "& " << crosscheckjpsikmchigh <<" $\\pm$ "<<crosscheckjpsikmchigherr<<" \\\\ "<<endl;
        

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
      
//DCB        double numberofevents_low = 102214.0;
//DCB        double numberofevents_high = 55147.0;
        double numberofevents_low = 9091.0; //Hypa
        double numberofevents_high = 6220.0; //Hypa
        double brfr1=1.028e-3*5.88e-2;
        double expsensitivity_low = (brfr1*crosscheckjpsikmclow)/(numberofevents_low*crosschecksiglow);
        double expsensitivity_high = (brfr1*crosscheckjpsikmchigh)/(numberofevents_high*crosschecksighigh);
      
        double expsensitivity_low_error = (sqrt((double(crosschecksiglowerr/crosschecksiglow)*double(crosschecksiglowerr/crosschecksiglow))+((double(crosscheckjpsikmclowerr/crosscheckjpsikmclow))*(double(crosscheckjpsikmclowerr/crosscheckjpsikmclow)))))*expsensitivity_low;
        double expsensitivity_high_error = (sqrt((double(crosschecksighigherr/crosschecksighigh)*double(crosschecksighigherr/crosschecksighigh))+((double(crosscheckjpsikmchigherr/crosscheckjpsikmchigh))*(double(crosscheckjpsikmchigherr/crosscheckjpsikmchigh)))))*expsensitivity_high;      

	TFile fillinfo("info_SES.root","UPDATE");
	TTree fillinfotree("Info_2015_lowFCME","Info_2015_lowFCME");

        double year;
        double numofevents;
        double effi_sig;
        double effi_norm;
        double sensitivity;
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
        double effi_FCME_sig;
        double effi_FCME_norm;
        double effi_pid_sig;
        double effi_pid_norm;

	fillinfotree.Branch("year",&year,"year/D");// "File/C");
	fillinfotree.Branch("numofevents",&numofevents,"numofevents/D");// "Cut/C");
	fillinfotree.Branch("effi_sig",&effi_sig,"effi_sig/D");
	fillinfotree.Branch("effi_norm",&effi_norm, "effi_norm/D");
	fillinfotree.Branch("sensitivity",&sensitivity, "sensitivity/D");
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

        fillinfotree.Branch("effi_FCME_sig",&effi_FCME_sig, "effi_FCME_sig/D");
        fillinfotree.Branch("effi_FCME_norm",&effi_FCME_norm, "effi_FCME_norm/D");

        fillinfotree.Branch("effi_pid_sig",&effi_pid_sig, "effi_pid_sig/D");
        fillinfotree.Branch("effi_pid_norm",&effi_pid_norm, "effi_pid_norm/D");


        year=2015.0;
        luminosity=282.0;
        numofevents_per_lumi=double(numberofevents_low/luminosity);
        numofevents=numberofevents_low;
        effi_sig=crosschecksiglow;
        effi_norm=crosscheckjpsikmclow;
        sensitivity=expsensitivity_low;
        effi_ratio=double(crosscheckjpsikmclow/crosschecksiglow);
        effi_numobs=double(crosscheckjpsikmclow/(crosschecksiglow*numberofevents_low));
        effi_corr_lumi=double(numberofevents_low/(crosscheckjpsikmclow*luminosity));
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
        effi_FCME_sig=lowFCMEsig;
        effi_FCME_norm=lowFCMEjpsik;
        effi_pid_sig=lowFCMEsigPID;
        effi_pid_norm=lowFCMEjpsikPID;
        fillinfotree.Fill();
	fillinfotree.Write("",TObject::kOverwrite);



	TTree fillinfotree2("Info_2015_highFCME","Info_2015_highFCME");

        double year;
        double numofevents;
        double effi_sig;
        double effi_norm;
        double sensitivity;
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
        double effi_FCME_sig;
        double effi_FCME_norm;
        double effi_pid_sig;
        double effi_pid_norm;

	fillinfotree2.Branch("year",&year,"year/D");// "File/C");
	fillinfotree2.Branch("numofevents",&numofevents,"numofevents/D");// "Cut/C");
	fillinfotree2.Branch("effi_sig",&effi_sig,"effi_sig/D");
	fillinfotree2.Branch("effi_norm",&effi_norm, "effi_norm/D");
	fillinfotree2.Branch("sensitivity",&sensitivity, "sensitivity/D");
        fillinfotree2.Branch("effi_ratio",&effi_ratio, "effi_ratio/D");
        fillinfotree2.Branch("effi_numobs",&effi_numobs, "effi_numobs/D");
        fillinfotree2.Branch("luminosity",&luminosity, "luminosity/D");
        fillinfotree2.Branch("numofevents_per_lumi",&numofevents_per_lumi, "numofevents_per_lumi/D");
        fillinfotree2.Branch("effi_corr_lumi",&effi_corr_lumi, "effi_corr_lumi/D");
        
        fillinfotree2.Branch("effi_gen_sig",&effi_gen_sig, "effi_gen_sig/D");
        fillinfotree2.Branch("effi_gen_norm",&effi_gen_norm, "effi_gen_norm/D");

        fillinfotree2.Branch("effi_rec_sig",&effi_rec_sig, "effi_rec_sig/D");
        fillinfotree2.Branch("effi_rec_norm",&effi_rec_norm, "effi_rec_norm/D");

	fillinfotree2.Branch("effi_off_sig",&effi_off_sig, "effi_off_sig/D");
	fillinfotree2.Branch("effi_off_norm",&effi_off_norm, "effi_off_norm/D");

        fillinfotree2.Branch("effi_combi_sig",&effi_combi_sig, "effi_combi_sig/D");
        fillinfotree2.Branch("effi_combi_norm",&effi_combi_norm, "effi_combi_norm/D");

        fillinfotree2.Branch("effi_misid_sig",&effi_misid_sig, "effi_misid_sig/D");
        fillinfotree2.Branch("effi_misid_norm",&effi_misid_norm, "effi_misid_norm/D");

        fillinfotree2.Branch("effi_corm_sig",&effi_corm_sig, "effi_corm_sig/D");
        fillinfotree2.Branch("effi_corm_norm",&effi_corm_norm, "effi_corm_norm/D");

        fillinfotree2.Branch("effi_FCME_sig",&effi_FCME_sig, "effi_FCME_sig/D");
        fillinfotree2.Branch("effi_FCME_norm",&effi_FCME_norm, "effi_FCME_norm/D");

        
        fillinfotree2.Branch("effi_pid_sig",&effi_pid_sig, "effi_pid_sig/D");
        fillinfotree2.Branch("effi_pid_norm",&effi_pid_norm, "effi_pid_norm/D");


        year=2015.0;
        luminosity=282.0;
        numofevents_per_lumi=double(numberofevents_high/luminosity);
        numofevents=numberofevents_high;
        effi_sig=crosschecksighigh;
        effi_norm=crosscheckjpsikmchigh;
        sensitivity=expsensitivity_high;
        effi_ratio=double(crosscheckjpsikmchigh/crosschecksighigh);
        effi_numobs=double(crosscheckjpsikmchigh/(crosschecksighigh*numberofevents_high));
        effi_corr_lumi=double(numberofevents_high/(crosscheckjpsikmchigh*luminosity));
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
        effi_FCME_sig=highFCMEsig;
        effi_FCME_norm=highFCMEjpsik;
        effi_pid_sig=highFCMEsigPID;
        effi_pid_norm=highFCMEjpsikPID;
        fillinfotree2.Fill();
	fillinfotree2.Write("",TObject::kOverwrite);
 
        out<<"Assuming $B^{+} \\rightarrow J/\\psi \\ K^{+})$ = 1.028e-3 (PDG 2014)  is "<<endl;
        //out<<"\\newline"<<endl;
        out<<"and $J/\\psi \\rightarrow \\mu^{-} \\mu^{+}$ = 5.88e-2 "<<endl;
        out<<"\\newline"<<endl;
        out<<"Observed in LowCME: "<<numberofevents_low<<" $J/\\psi \\ K^{+}$  events."<<endl;
        out<<"\\newline"<<endl;
        out<<"Observed in HighCME: "<<numberofevents_high<<" $J/\\psi \\ K^{+}$  events."<<endl;
        out<<"\\newline"<<endl;
        out<<"Expected Single Event Sensitivity LowCME: "<< expsensitivity_low <<endl;
        out<<"\\newline"<<endl;
        out<<"Expected Single Event Sensitivity HighCME: "<< expsensitivity_high <<endl;
        out<<"\\newline"<<endl;
        out<<"Low Error is $\\pm$ "<<expsensitivity_low_error;
        out<<"\\newline"<<endl;
        out<<"High Error is $\\pm$ "<<expsensitivity_high_error;

 

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



