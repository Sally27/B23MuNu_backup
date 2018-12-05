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
        out<<"\\begin{tabular}{| l | l | l |}"<<endl;
        out<<"\\hline"<<endl;
        out<<"\\hline"<<endl;

 
        double toteff;
        double decprodcutsig =0.185;
        double effrecostrsig= 0.111;
        double decprodcutjpsik =0.16743;
        double effrecostrjpsik= 0.233207*0.739694;
        double effmyrecosig =0.516623;
        double effmyrecostrjpsik= 0.019507;
        double combibdtsig = 0.304679;
        double combibdtjpsik = 0.368919; 
        double misidbdtsig = 0.410646;
        double misidbdtjpsik = 0.349817;
        
        double toteffsig=decprodcutsig*effrecostrsig*effmyrecosig*combibdtsig*misidbdtsig;
        double toteffjpsikmc=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*combibdtjpsik*misidbdtjpsik;

    
        out << "Efficiency & "<< " B23Mu MC & " << "Jpsi 2012 MC \\\\" <<endl;   
        out << "$\\epsilon_{decprodcut}$ &" << decprodcutsig << " & " << decprodcutjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{reco}$ &" << effrecostrsig << " & " << effrecostrjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{myreco}$ &" << effmyrecosig << " & " << effmyrecostrjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{combibdt}$ &" << combibdtsig << " & " << combibdtjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{misidbdt}$ &" << misidbdtsig << " & " << misidbdtjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{ALL}$ &" << toteffsig << " & " << toteffjpsikmc <<" \\\\ "<<endl;
        


	double brfr=1e-8;
	double ppbbX=284e-6;
	double bBplus= 2*0.4;
	double datacoll=3e15;
	double decprodcut =0.185;
	double effrecostrip= 0.111;

        out<<"\\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Single event sensitivity}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"Calculation of the Single Event Sensitivity"<<endl;
        out<<"\\begin{equation}"<<endl;
        out<<"\\mathcal{B}(B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu) = \\frac{\\mathcal{B}(B^{+} \\rightarrow J\\psi K^{+}) \\times \\epsilon_{B^{+} \\rightarrow J\\psi K^{+}}}{N_{(B^{+} \\rightarrow J\\psi K^{+})} \\times \\epsilon_{B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu}} \\times N_{B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu} "<<endl;
        out<<"\\end{equation}"<<endl;
      
        double numberofevents = 1241.0;
        double brfr1=1.028e-3*5.88e-2;
        double expsensitivity = (brfr1*toteffjpsikmc)/(numberofevents*toteffsig);

        out<<"Assuming $B^{+} \\rightarrow J\\psi K^{+}) = 1.028e-3 (PDG 2014) $ is "<<endl;
        out<<"\\newline"<<endl;
        out<<"And $J\\psi \\rightarrow \\mu^{-} \\mu^{+}$= 5.88e-2 "<<endl;
        out<<"\\newline"<<endl;
        out<<"Expected Single Event Sensitivity:"<< expsensitivity <<endl;

 
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



