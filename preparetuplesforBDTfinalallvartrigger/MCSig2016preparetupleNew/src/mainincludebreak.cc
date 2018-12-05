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
        out.open("EfficienciesBreakNT.tex");

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

      
        double toteff(0);



        string pathname = "/vols/lhcb/ss4314/tuplesallvar/B23MuNuMCL0/";
        string filename = "B23MuMC2012L0data";
        string decaytreename = "B23MuNu_Tuple/DecayTree";
        string ext = ".root";
        string cuttag = "_MCtruth";
        string filename2 = (filename+cuttag).c_str();


        double decprodcut2 =0.185;
        double effrecostrip2= 0.135;

        out << "$\\epsilon_{decprodcut}$ &" << decprodcut2 << " & " << "(3544)10000" << " & "<< (sqrt(double(3544)*(1.0-((double(3544)/double(10000))))))*(1/double(10000))<<" \\\\ "<<endl;
        out << "$\\epsilon_{reco}$ &" << effrecostrip2 << " & "<<"(149879)1107715" << " & "<< (sqrt(double(149879)*(1.0-((double(149879)/double(1107715))))))*(1/double(1107715)) <<" \\\\ "<<endl;


        double mctrutheff;
        mctrutheff=mctruth((pathname+filename).c_str(), decaytreename, (filename2).c_str());
        out << "$\\epsilon_{MC}$ &" << mctrutheff <<" - & "<< " - & " << " \\\\ "<<endl;


        convertbranchname(filename2, "DecayTree", filename2);
        addqsqinf(filename2, "DecayTree", filename2);
        addcostheta(filename2, "DecayTree", filename2);

        double L0eff(0);
        L0eff=calculateL0effMC(filename2, "DecayTree", "miau");
	toteff = L0eff;

        
        cutTree((filename2+ext).c_str(),"DecayTree",(filename2+"_L0MuonDecisionTOS"+ext).c_str(),"Bplus_L0MuonDecision_TOS==1.0");
        
        string filenameclean=(filename2+"_L0MuonDecisionTOS").c_str();
        string file=(filename2+"_L0MuonDecisionTOS").c_str();
        out << "$\\epsilon_{L0}$ &" << L0eff <<"&"<< getmyentries((filenameclean+ext).c_str(),"DecayTree") << "  & " << " \\\\ "<<endl;


        vector<string> varia;
        varia.push_back("trigger");
        varia.push_back("qmincut");
        

        vector<string> vals;
        vals.push_back("(Bplus_Hlt1TrackMuonDecision_TOS==1.0) && ((Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0))");
        vals.push_back("minq2 < 960400");
       


        for(int i(0);i<1;i++)
        {
        double eff;
        double error;
        int numofentriesbefore;
        int numofentriesafter;


        eff=cutTree((filenameclean+ext).c_str(), "DecayTree", (filenameclean+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
        numofentriesbefore= getmyentries((filenameclean+ext).c_str(),"DecayTree");
        numofentriesafter= getmyentries((filenameclean+"_"+varia.at(i)+ext).c_str(),"DecayTree");
        error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
        out<<"$\\epsilon_{"+varia.at(i)+"}$  & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
        filenameclean=(filenameclean+"_"+varia.at(i)).c_str();
        toteff=toteff*eff;
        } 

        double jpsieff;
        jpsieff=Jpsi((filenameclean).c_str(), "DecayTree", (filenameclean+"_Jpsi").c_str());
        double error;
        int numofentriesbefore;
        int numofentriesafter;
        numofentriesbefore= getmyentries((filenameclean+ext).c_str(),"DecayTree");
        numofentriesafter= getmyentries((filenameclean+"_Jpsi"+ext).c_str(),"DecayTree");
        error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
        out << "$\\epsilon_{Jpsi}$ &" << jpsieff<<" & "<<numofentriesafter<<" & "<<error << " \\\\ "<<endl;
        toteff=toteff*jpsieff;
        filenameclean=(filenameclean+"_Jpsi").c_str();

        for(int i(1);i<2;i++)
        {
        double eff;
        double error;
        int numofentriesbefore;
        int numofentriesafter;
        eff=cutTree((filenameclean+ext).c_str(), "DecayTree", (filenameclean+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
        numofentriesbefore= getmyentries((filenameclean+ext).c_str(),"DecayTree");
        numofentriesafter= getmyentries((filenameclean+"_"+varia.at(i)+ext).c_str(),"DecayTree");
        error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
        out<<"$\\epsilon_{"+varia.at(i)+"}$ & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
        filenameclean=(filenameclean+"_"+varia.at(i)).c_str();
        toteff=toteff*eff;
        }
        out<<"\\hline"<<endl;
        out<<"$\\epsilon_{totaleff}$ & "<<toteff<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;


        addKFoldandW(filenameclean, "DecayTree", filenameclean);


	vals.push_back("Bplus_Hlt1TrackMuonDecision_TOS==1.0");
	vals.push_back("(Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0)");

	varia.push_back("Hlt1TrackMuonDecisionTOS");
	varia.push_back("Hlt2orofDecisions");

	string filename3=(file).c_str();

	for(int i(2);i<4;i++)
	{
               double error;
               int numofentriesbefore;
               int numofentriesafter;
		double eff;
		eff=cutTree((filename3+ext).c_str(), "DecayTree", (filename3+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
                numofentriesbefore= getmyentries((filename3+ext).c_str(),"DecayTree");
                numofentriesafter= getmyentries((filename3+"_"+varia.at(i)+ext).c_str(),"DecayTree");
                error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
                out<<vals.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
		filename3=(filename3+"_"+varia.at(i)).c_str();
	}
	out<<"\\hline"<<endl;

        
	vals.push_back("Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS==1.0");
        vals.push_back("Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS==1.0");
        vals.push_back("Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0");
        vals.push_back("Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0");

	varia.push_back("Hlt2TopoMu2BodyBBDTDecision");
        varia.push_back("Hlt2TopoMu3BodyBBDTDecision");
        varia.push_back("Hlt2DiMuonDetachedDecision");
        varia.push_back("Hlt2DiMuonDetachedHeavyDecision");
        

	string filename4=(file+"_Hlt1TrackMuonDecisionTOS").c_str();        

        for(int i(4);i<8;i++)
	{
               double error;
               int numofentriesbefore;
               int numofentriesafter;	
         	double eff;
		eff=cutTree((filename4+ext).c_str(), "DecayTree", (filename4+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
                numofentriesbefore= getmyentries((filename4+ext).c_str(),"DecayTree");
                numofentriesafter= getmyentries((filename4+"_"+varia.at(i)+ext).c_str(),"DecayTree");
                error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
                out<<vals.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
	}

        out<<"\\hline"<<endl;

	double brfr=1e-8;
	double ppbbX=284e-6;
	double bBplus= 2*0.4;
	double datacoll=3e15;
	double decprodcut =0.185;
	double effrecostrip= 0.111;

	double finalnum;
	finalnum=ppbbX*bBplus*brfr*datacoll*decprodcut*effrecostrip*toteff; 

        out<<"TotSig asuming 10$^-8$ & "<<finalnum<<" \\\\ "<<endl;
        out<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{EFFICIENCIESMCSIG.txt}"<<endl;
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



