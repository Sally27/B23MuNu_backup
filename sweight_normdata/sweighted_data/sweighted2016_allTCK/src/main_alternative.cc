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
	out.open("Efficiencies_Allternative.tex");

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
 
	TFile *fillinfo = new TFile("Efficiencies_Data_Sweighted_2012_trigger_TISTOS_Alt.root","RECREATE");
	TTree *fillinfotree = new TTree("Data_Norm_2012","Data_Norm_2012");


	FillEffInfo(fillinfotree, "decprodcut",decprodcut2,false);

        string ext=".root";
        string filenameclean="Data_WS_sweights_2012";




	vector<string> varia;


	vector<string> vals;
        vector<int> numofevents;


	vals.push_back("Bplus_L0MuonDecision_TOS==1.0 && Bplus_L0MuonDecision_TIS==1.0");
	vals.push_back("Bplus_Hlt1TrackMuonDecision_TOS==1.0 && Bplus_Hlt1TrackMuonDecision_TIS==1.0");
	vals.push_back("(Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS==1.0 && Bplus_Hlt2TopoMu2BodyBBDTDecision_TIS==1.0) || (Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS==1.0 && Bplus_Hlt2TopoMu3BodyBBDTDecision_TIS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0 && Bplus_Hlt2DiMuonDetachedDecision_TIS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0 && Bplus_Hlt2DiMuonDetachedHeavyDecision_TIS==1.0 )");

	varia.push_back("L0MuonDecisionTISTOS");
	varia.push_back("Hlt1TrackMuonDecisionTISTOS");
	varia.push_back("Hlt2orofDecisionsTISTOS");

	string filename3=filenameclean;

	for(int i(0);i<3;i++)
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
//		filename3=(filename3+"_"+varia.at(i)).c_str();

                
        	FillEffInfo(fillinfotree, (varia.at(i)+"numberTISTOS").c_str(), numbertistos,true);
        	FillEffInfo(fillinfotree, varia.at(i), eff,true);
	}
	out<<"\\hline"<<endl;

        
	vals.push_back("Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS==1.0 && Bplus_Hlt2TopoMu2BodyBBDTDecision_TIS==1.0");
        vals.push_back("Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS==1.0 && Bplus_Hlt2TopoMu3BodyBBDTDecision_TIS==1.0");
        vals.push_back("Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0 && Bplus_Hlt2DiMuonDetachedDecision_TIS==1.0");
        vals.push_back("Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0 && Bplus_Hlt2DiMuonDetachedHeavyDecision_TIS==1.0");

	varia.push_back("Hlt2TopoMu2BodyBBDTDecisionTISTOS");
        varia.push_back("Hlt2TopoMu3BodyBBDTDecisionTISTOS");
        varia.push_back("Hlt2DiMuonDetachedDecisionTISTOS");
        varia.push_back("Hlt2DiMuonDetachedHeavyDecisionTISTOS");
        

//	string filename4=(filenameclean+"_L0MuonDecisionTISTOS_Hlt1TrackMuonDecisionTISTOS").c_str();        
//
//        for(int i(3);i<7;i++)
//	{
//               double error;
//               int numofentriesbefore;
//               int numofentriesafter;	
//         	double eff;
//                double numbertistos;
//		eff=cutTree((filename4+ext).c_str(), "DecayTree", (filename4+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
//                numofentriesbefore= getmyentries((filename4+ext).c_str(),"DecayTree");
//                numofentriesafter= getmyentries((filename4+"_"+varia.at(i)+ext).c_str(),"DecayTree");
//                numbertistos=double(getSweightValue((filename4+"_"+varia.at(i)).c_str(),"DecayTree"));
//                error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
//                out<<vals.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
//
//		FillEffInfo(fillinfotree, (varia.at(i)+"numberTISTOS").c_str(), numbertistos,true);
//        	FillEffInfo(fillinfotree, varia.at(i), eff,true);
//	//	filename3=(filename3+"_"+varia.at(i)).c_str();
//	}

	vals.push_back("Bplus_L0MuonDecision_TIS==1.0");
	vals.push_back("Bplus_Hlt1TrackMuonDecision_TIS==1.0");
	vals.push_back("(Bplus_Hlt2TopoMu2BodyBBDTDecision_TIS==1.0) || (Bplus_Hlt2TopoMu3BodyBBDTDecision_TIS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TIS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TIS==1.0 )");

	varia.push_back("L0MuonDecisionTIS");
	varia.push_back("Hlt1TrackMuonDecisionTIS");
	varia.push_back("Hlt2orofDecisionsTIS");

	string filename7=filenameclean;

	for(int i(7);i<10;i++)
	{
               double error;
               int numofentriesbefore;
               int numofentriesafter;
		double eff;
                double numbertistos;
		eff=cutTree((filename7+ext).c_str(), "DecayTree", (filename7+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
                numofentriesbefore= getmyentries((filename7+ext).c_str(),"DecayTree");
                numofentriesafter= double(getmyentries((filename7+"_"+varia.at(i)+ext).c_str(),"DecayTree"));
                numbertistos=double(getSweightValue((filename7+"_"+varia.at(i)).c_str(),"DecayTree"));
                error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
                out<<vals.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
//		filename7=(filename7+"_"+varia.at(i)).c_str();

                
        	FillEffInfo(fillinfotree, (varia.at(i)+"numberTIS").c_str(), numbertistos,true);
        	FillEffInfo(fillinfotree, varia.at(i), eff,true);
	}
	out<<"\\hline"<<endl;

        
	vals.push_back("Bplus_Hlt2TopoMu2BodyBBDTDecision_TIS==1.0");
        vals.push_back("Bplus_Hlt2TopoMu3BodyBBDTDecision_TIS==1.0");
        vals.push_back("Bplus_Hlt2DiMuonDetachedDecision_TIS==1.0");
        vals.push_back("Bplus_Hlt2DiMuonDetachedHeavyDecision_TIS==1.0");

	varia.push_back("Hlt2TopoMu2BodyBBDTDecisionTIS");
        varia.push_back("Hlt2TopoMu3BodyBBDTDecisionTIS");
        varia.push_back("Hlt2DiMuonDetachedDecisionTIS");
        varia.push_back("Hlt2DiMuonDetachedHeavyDecisionTIS");
        

//	string filename8=(filenameclean+"_L0MuonDecisionTIS_Hlt1TrackMuonDecisionTIS").c_str();        
//
//        for(int i(10);i<14;i++)
//	{
//               double error;
//               int numofentriesbefore;
//               int numofentriesafter;	
//         	double eff;
//                double numbertistos;
//		eff=cutTree((filename8+ext).c_str(), "DecayTree", (filename8+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
//                numofentriesbefore= getmyentries((filename8+ext).c_str(),"DecayTree");
//                numofentriesafter= getmyentries((filename8+"_"+varia.at(i)+ext).c_str(),"DecayTree");
//                numbertistos=double(getSweightValue((filename8+"_"+varia.at(i)).c_str(),"DecayTree"));
//                error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
//                out<<vals.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
//
//		FillEffInfo(fillinfotree, (varia.at(i)+"numberTIS").c_str(), numbertistos,true);
//        	FillEffInfo(fillinfotree, varia.at(i), eff,true);
//	//	filename3=(filename3+"_"+varia.at(i)).c_str();
//	}

	fillinfo->cd();
	fillinfotree->Write("",TObject::kOverwrite);

	delete fillinfotree;
	delete fillinfo;
        }




}



