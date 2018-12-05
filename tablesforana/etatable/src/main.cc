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


//        string PIDcut=argv[1];

        ofstream out;
        out.open("EtaBF.tex");

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
        out<<"Process & $\\mathcal{B}$ & Full Contribution"<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"\\hline"<<endl;

        //-------------Dec Prod Cut-------------------//
        ValError etamumugamma(3.1e-4,0.4e-4);
        ValError etaprmumugamma(1.08e-4,0.27e-4);
        ValError d0pietaprpi(9.1e-4,1.4e-4); //done
        ValError d0pietaprpipi(4.5e-4,1.7e-4); //done
        ValError d0etaeta(1.7e-3,0.02e-3); //done
        ValError d0pietaetapr(1.06e-3,0.27e-3); 
        ValError d0phieta(1.4e-4,0.5e-4); //done

        ValError total=(etaprmumugamma*d0pietaprpi)+(etaprmumugamma*d0pietaprpipi)+(etamumugamma*d0etaeta)+(etamumugamma*d0etaeta)+(etamumugamma*d0pietaetapr)+(etaprmumugamma*d0pietaetapr)+(etamumugamma*d0phieta);

        out<<"$\\mathcal{B}(\\eta \\rightarrow \\mu \\mu \\gamma)$ & "<<etamumugamma.roundToError_diffbase(true)<<" & - "<<" \\\\ "<<endl;
        out<<"$\\mathcal{B}(\\eta' \\rightarrow \\mu \\mu \\gamma)$ & "<<etaprmumugamma.roundToError_diffbase(true)<<" & - "<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"$\\mathcal{B}(D^{0} \\rightarrow \\eta' \\pi^{+})$ & "<<d0pietaprpi.roundToError_diffbase(true)<<" & "<<(etaprmumugamma*d0pietaprpi).roundToError_diffbase(true)<<" \\\\ "<<endl;
        out<<"$\\mathcal{B}(D^{0} \\rightarrow \\eta' \\pi^{+} \\pi^{-})$ & "<<d0pietaprpipi.roundToError_diffbase(true)<<" & "<<(etaprmumugamma*d0pietaprpipi).roundToError_diffbase(true)<<" \\\\ "<<endl;
        out<<"$\\mathcal{B}(D^{0} \\rightarrow 2\\eta )$ & "<<d0etaeta.roundToError_diffbase(true)<<" & "<<(etamumugamma*d0etaeta).roundToError_diffbase(true)<<" \\\\ "<<endl; 
        out<<"$\\mathcal{B}(D^{0} \\rightarrow 2\\eta )$ & "<<d0etaeta.roundToError_diffbase(true)<<" & "<<(etamumugamma*d0etaeta).roundToError_diffbase(true)<<" \\\\ "<<endl;
        out<<"$\\mathcal{B}(D^{0} \\rightarrow \\underline{\\eta} \\eta' )$ & "<<d0pietaetapr.roundToError_diffbase(true)<<" & "<<(etamumugamma*d0pietaetapr).roundToError_diffbase(true)<<" \\\\ "<<endl;

        out<<"$\\mathcal{B}(D^{0} \\rightarrow \\eta \\underline{\\eta}' )$ & "<<d0pietaetapr.roundToError_diffbase(true)<<" & "<<(etaprmumugamma*d0pietaetapr).roundToError_diffbase(true)<<" \\\\ "<<endl;
        out<<"$\\mathcal{B}(D^{0} \\rightarrow \\eta \\phi)$ & "<<d0phieta.roundToError_diffbase(true)<<" & "<<(etamumugamma*d0phieta).roundToError_diffbase(true)<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"Total &  - &"<<total.roundToError_diffbase(true)<<" \\\\ "<<endl;
        
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl; 
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Different and total cotribution of $D^{0}\\rightarrow \\eta(') X, \\eta(') \\rightarrow \\mu^{+} \\mu^{-}  \\gamma$ with the highest corrected mass contribution.}"<<endl;
        out<<"\\end{table}"<<endl;


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



