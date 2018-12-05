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
        out.open("SingleEv.tex");

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

        double effrecostrsig= 0.111;
        double effrecostrjpsik= 0.233207*0.820968;

        double effmyrecosig =0.63634;
        double effmyrecostrjpsik= 0.796514;


        double combibdtsig = 0.446179;
        double combibdtjpsik = 0.483201; 

        double misidbdtsig = 0.418599;
        double misidbdtjpsik = 0.476374;

        double cormsig=0.923807;
        double cormjpsik=0.99959;

        double lowFCMEsig=0.50474; 
        double lowFCMEjpsik=0.618093;

        double highFCMEsig=0.49526;
        double highFCMEjpsik=0.381907;

        double lowFCMEsigPID=0.651957;
        double lowFCMEjpsikPID=0.705099;

        double highFCMEsigPID=0.677322;
        double highFCMEjpsikPID=0.728184;

   //     double sigPID = 0.663465;
   //     double jpsikPID = 0.71386;       


 
        double toteffsiglow=decprodcutsig*effrecostrsig*effmyrecosig*combibdtsig*misidbdtsig*cormsig*lowFCMEsig*lowFCMEsigPID;
        double toteffjpsikmclow=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*lowFCMEjpsik*lowFCMEjpsikPID;
        double toteffsighigh=decprodcutsig*effrecostrsig*effmyrecosig*combibdtsig*misidbdtsig*cormsig*highFCMEsig*highFCMEsigPID;
        double toteffjpsikmchigh=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*highFCMEjpsik*highFCMEjpsikPID;
   
        double crosschecksiglow=decprodcutsig*effrecostrsig*(double(6389.0/124051.0))*lowFCMEsigPID;
        double crosscheckjpsikmclow=decprodcutjpsik*effrecostrjpsik*(double(173498.0/1531615.0))*lowFCMEjpsikPID;
        double crosschecksighigh=decprodcutsig*effrecostrsig*(double(6269.0/124051.0))*highFCMEsigPID;
        double crosscheckjpsikmchigh=decprodcutjpsik*effrecostrjpsik*(double(107201.0/1531615.0))*highFCMEjpsikPID;   

        double crosschecksiglowerr=(sqrt(double(6389.0)*(1.0-((double(6389.0)/double(1114130))))))*(1/double(1114130));
        double crosscheckjpsikmclowerr=(sqrt(double(173498.0)*(1.0-((double(173498.0)/double(8043820))))))*(1/double(8043820));
        double crosschecksighigherr=(sqrt(double(6269.0)*(1.0-((double(6269.0)/double(1114130))))))*(1/double(1114130));
        double crosscheckjpsikmchigherr=(sqrt(double(107201.0)*(1.0-((double(107201.0)/double(8043820))))))*(1/double(8043820));


 
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
      
        double numberofevents_low = 111143.0;
        double numberofevents_high = 58030.0;
        double brfr1=1.028e-3*5.88e-2;
        double expsensitivity_low = (brfr1*crosscheckjpsikmclow)/(numberofevents_low*crosschecksiglow);
        double expsensitivity_high = (brfr1*crosscheckjpsikmchigh)/(numberofevents_high*crosschecksighigh);
       
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



