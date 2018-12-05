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
        out.open("EtaBF_fromB.tex");

	out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
	out<<"\\usepackage[pdftex]{grarhocx}"<<endl;
	out<<"\\usepackage{url}"<<endl;
	out<<"\\usepackage{mathtools}"<<endl;
	out<<"\\usepackage{amsmath}"<<endl;
	out<<"\\usepackage{grarhocx}"<<endl;
	out<<"\\usepackage[table]{xcolor}"<<endl;
	out<<"\\usepackage{amsmath,amssymb}"<<endl;
	out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
	out<<"\\usepackage{colortbl}"<<endl;
	out<<"\\begin{document}"<<endl;
        
        out<<"Calculation of the Single Event Sensitivity"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{| l | l |}"<<endl;
        out<<"Process & $\\mathcal{B}$ "<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"\\hline"<<endl;

        //-------------Dec Prod Cut-------------------//
        ValError etamumugamma(3.1e-4,0.4e-4);
        ValError etaprmumugamma(1.08e-4,0.27e-4);
    //    ValError d0pietaprpi(9.1e-4,1.4e-4); //done
    //    ValError d0pietaprpipi(4.5e-4,1.7e-4); //done
    //    ValError d0etaeta(1.7e-3,0.02e-3); //done
   //     ValError d0pietaetapr(1.06e-3,0.27e-3); 
   //     ValError d0rhoeta(1.4e-4,0.5e-4); //done


        ValError b0omegaeta(9.4e-7,4.0e-7);
        ValError b0rhoeta(5e-7,0);
        ValError b0omegaetapr(1.0e-6,0.5e-6);
        ValError b0rhoetapr(5e-7,0);

        ValError rhomumu(4.55e-5,0.28e-5);
        ValError omegamumu(9.0e-5,3.1e-5);

        ValError total=(etaprmumugamma*b0rhoetapr*rhomumu)+(etamumugamma*b0rhoeta*rhomumu)+(etaprmumugamma*b0omegaetapr*omegamumu)+(etamumugamma*b0omegaeta*omegamumu);
       

        out<<"$\\mathcal{B}(B^{0} \\rightarrow \\omega \\eta')$ & "<<b0omegaetapr.roundToError_diffbase(true)<<" \\\\ "<<endl;
        out<<"$\\mathcal{B}(B^{0} \\rightarrow \\rho \\eta')$ &  $<$"<<b0rhoetapr.roundToError_diffbase(true)<<"  \\\\ "<<endl;
        out<<"$\\mathcal{B}(B^{0} \\rightarrow  \\omega  \\eta )$ & "<<b0omegaeta.roundToError_diffbase(true)<<" \\\\ "<<endl; 
        out<<"$\\mathcal{B}(B^{0} \\rightarrow \\rho \\eta )$ & $<$ "<<b0rhoeta.roundToError_diffbase(true)<<"  \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"$\\mathcal{B}(\\eta \\rightarrow \\mu \\mu \\gamma)$ & "<<etamumugamma.roundToError_diffbase(true)<<" \\\\ "<<endl;
        out<<"$\\mathcal{B}(\\eta' \\rightarrow \\mu \\mu \\gamma)$ & "<<etaprmumugamma.roundToError_diffbase(true)<<"  \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"$\\mathcal{B}(\\rho \\rightarrow \\mu \\mu)$ & "<<rhomumu.roundToError_diffbase(true)<<"  \\\\ "<<endl;
        out<<"$\\mathcal{B}(\\omega \\rightarrow \\mu \\mu)$ & "<<omegamumu.roundToError_diffbase(true)<<"  \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"$\\mathcal{B}(B^{0} \\rightarrow (\\omega \\rightarrow \\mu \\mu) (\\eta \\rightarrow \\mu \\mu \\gamma))$ &"<<(etamumugamma*b0rhoeta*rhomumu).roundToError_diffbase(true)<<" \\\\ "<<endl;
        out<<"$\\mathcal{B}(B^{0} \\rightarrow (\\omega \\rightarrow \\mu \\mu) (\\eta'\\rightarrow \\mu \\mu \\gamma))$ &"<<(etaprmumugamma*b0rhoetapr*rhomumu).roundToError_diffbase(true)<<" \\\\ "<<endl;
        out<<"$\\mathcal{B}(B^{0} \\rightarrow (\\rho \\rightarrow \\mu \\mu) (\\eta \\rightarrow \\mu \\mu \\gamma))$ & $<$"<<(etamumugamma*b0omegaeta*omegamumu).roundToError_diffbase(true)<<" \\\\ "<<endl;
        out<<"$\\mathcal{B}(B^{0} \\rightarrow (\\rho \\rightarrow \\mu \\mu) (\\eta'\\rightarrow \\mu \\mu \\gamma))$ & $<$"<<(etaprmumugamma*b0omegaetapr*omegamumu).roundToError_diffbase(true)<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"Total  & $ <$ " <<total.roundToError_diffbase(true)<<" \\\\ "<<endl;
        
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl; 
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Different and total cotribution to $B^{0} \\rightarrow \\eta(') \\rho(\\omega)$.}"<<endl;
        out<<"\\label{tab:ed}"<<endl;
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



