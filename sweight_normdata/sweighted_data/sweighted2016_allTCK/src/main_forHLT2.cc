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
	out.open("Efficiencies_forHLT2_Special.tex");

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
	out<<"Cut & $\\epsilon$ & N &  \\\\ "<<endl;
	out<<"\\hline"<<endl;
        double decprodcut2(0.16734);
	out<<"dec prod cut & "<<decprodcut2<<"(md from simstat) & 3554(10000) & TBD \\\\ "<<endl;
//	out<<"or strip and reco & 0.33522 & 1365886(8043820) & TBD  \\\\ "<<endl;
        
        int p(0);
          
        if (p==0)
        {

 
        double toteff(1.0);      
 
	TFile *fillinfo = new TFile("Efficiencies_Data_Sweighted_2016_trigger_TISTOS_HLT2.root","RECREATE");
	TTree *fillinfotree = new TTree("Data_Norm_2016","Data_Norm_2016");


	FillEffInfo(fillinfotree, "decprodcut",decprodcut2,false);

        string ext=".root";
        string filenameclean="Data_WS_sweights_2016_ALLTCK";




	vector<string> varia;


	vector<string> vals;
        vector<int> numofevents;

        vals.push_back("Bplus_L0MuonDecision_TIS==1.0 && Bplus_Hlt1TrackMuonDecision_TIS==1.0 & (Bplus_Hlt2TopoMu2BodyDecision_TIS==1.0) || (Bplus_Hlt2TopoMu3BodyDecision_TIS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TIS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TIS==1.0 )");

	vals.push_back("Bplus_L0MuonDecision_TIS==1.0 && Bplus_Hlt1TrackMuonDecision_TIS==1.0 &(Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0 && Bplus_Hlt2TopoMu2BodyDecision_TIS==1.0) || (Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0 && Bplus_Hlt2TopoMu3BodyDecision_TIS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0 && Bplus_Hlt2DiMuonDetachedDecision_TIS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0 && Bplus_Hlt2DiMuonDetachedHeavyDecision_TIS==1.0 )");
        
        varia.push_back("L0MuonandHlt1TISHlt2TOS");
        varia.push_back("L0MuonandHlt1TISHlt2TISTOS");

	string filename3=filenameclean;
        string filename4=filenameclean;

	for(int i(0);i<1;i++)
	{
               double error;
               int numofentriesbefore;
               int numofentriesafter;
		double eff;
                double numbertistos;
		eff=cutTree((filename3+ext).c_str(), "DecayTree", (filename3+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
                numofentriesbefore= getmyentries((filename3+ext).c_str(),"DecayTree");
                numofentriesafter= double(getmyentries((filename3+"_"+varia.at(i)+ext).c_str(),"DecayTree"));
                numbertistos=double(getSweightValue((filename3+"_"+varia.at(i)).c_str(),"DecayTree"));
                error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
                out<<vals.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
		filename3=(filename3+"_"+varia.at(i)).c_str();

                
        	FillEffInfo(fillinfotree, (varia.at(i)+"numberTISonly").c_str(), numbertistos,true);
        	FillEffInfo(fillinfotree, varia.at(i), eff,true);
	}
	out<<"\\hline"<<endl;

	for(int i(1);i<2;i++)
	{
               double error;
               int numofentriesbefore;
               int numofentriesafter;
		double eff;
                double numbertistos;
		eff=cutTree((filename4+ext).c_str(), "DecayTree", (filename4+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
                numofentriesbefore= getmyentries((filename4+ext).c_str(),"DecayTree");
                numofentriesafter= double(getmyentries((filename4+"_"+varia.at(i)+ext).c_str(),"DecayTree"));
                numbertistos=double(getSweightValue((filename4+"_"+varia.at(i)).c_str(),"DecayTree"));
                error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
                out<<vals.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
		filename4=(filename4+"_"+varia.at(i)).c_str();

                
        	FillEffInfo(fillinfotree, (varia.at(i)+"numberTISandTOSonly").c_str(), numbertistos,true);
        	FillEffInfo(fillinfotree, varia.at(i), eff,true);
	}
        

	fillinfo->cd();
	fillinfotree->Write("",TObject::kOverwrite);

	delete fillinfotree;
	delete fillinfo;
        }




}



