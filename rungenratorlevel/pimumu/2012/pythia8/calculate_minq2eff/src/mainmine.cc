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
#include<iostream>

using namespace std;


int main(){

        ofstream out;
        out.open("EfficienciesQ2mine2.tex");

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
        
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
        out<<"\\hline"<<endl;
        out<<"Cut & $\\epsilon$ & N & error   \\\\ "<<endl;
        out<<"\\hline"<<endl;

      
        double toteff;


	string pathname = "/vols/lhcb/ss4314/rungenratorlevel/pimumu/2012/pythia8/";
	string filename = "B2MuMuPi_2012_PYTHIA8";
	string decaytreename = "MCDecayTreeTuple/MCDecayTree";
	string ext = ".root";
	string cuttag = "";
	string filename2 = (filename+cuttag).c_str();


        cutTree((pathname+filename+ext).c_str(), decaytreename, (filename2+ext).c_str(),"");

//        convertbranchname(filename2, "DecayTree", filename2);
        addqsqinf(filename2, "MCDecayTree", filename2);        
//        addcostheta(filename2, "DecayTree", filename2);  

        string filenameclean=filename2;

        vector<string> varia;
        varia.push_back("qmincut");
        varia.push_back("inacc");

        vector<string> vals;
        vals.push_back("minq2 < 960400");
      vals.push_back("(muplus_eta>1.596 && muplus_eta<5.298) && (muminus_eta>1.596 && muminus_eta<5.298) && (piplus_eta>1.596 && piplus_eta<5.298)"); 


        for(int i(0);i<2;i++)
        {
        double eff;
        double error;
        int numofentriesbefore;
        int numofentriesafter;


        eff=cutTree((filename2+ext).c_str(), "MCDecayTree", (filename2+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
        numofentriesbefore= getmyentries((filename2+ext).c_str(),"MCDecayTree");
        numofentriesafter= getmyentries((filename2+"_"+varia.at(i)+ext).c_str(),"MCDecayTree");
        error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
        out<<"$\\epsilon_{"+varia.at(i)+"}$  & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
        filename2=(filename2+"_"+varia.at(i)).c_str();
        toteff=eff;
        } 

        out<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{EFFICIENCIESMCSIG.txt}"<<endl;
        out<<"\\end{table}"<<endl;       


        double nbkk(1114130.0);
        double nrecoq(116892.0);
        double numgen(25000.0);

        double effici(0);
        effici = (double(getmyentries((filename2+ext).c_str(),"MCDecayTree"))/double(getmyentries((filenameclean+"_"+varia.at(0)+ext).c_str(),"MCDecayTree")))*(nrecoq/(nbkk*(double(getmyentries((filenameclean+"_"+varia.at(0)+ext).c_str(),"MCDecayTree"))/numgen)));

        cout<<"Efficiency is " <<effici<<endl;
        out<<"Efficiency is " <<effici<<endl;
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



