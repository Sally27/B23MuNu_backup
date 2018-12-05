
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
        out.open("Efficiencies.tex");

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
        out<<"\\begin{tabular}{| l | l |}"<<endl;
        out<<"\\hline"<<endl;
        out<<"Cut & $\\epsilon$   \\\\ "<<endl;
        out<<"\\hline"<<endl;


      
        double toteff(1.0);

        string pathname = "/vols/lhcb/ss4314/tuplesallvar/ThreeSameSignMuonsData/";
        string filename = "B23SameSignMuonTotal";
        string decaytreename = "B_Tuple/DecayTree";
        string ext = ".root";
	string cuttag = "";
	string filename2 = (filename+cuttag).c_str();
        string filenameclean = filename;




        cutTree((pathname+filename+ext).c_str(), decaytreename, (filename+ext).c_str(), "");


        string decaytreename2 = "DecayTree";
           

        convertbranchname(filename2, "DecayTree", filename2);
        addqsqinf(filename2, "DecayTree", filename2);        
        addcostheta(filename2, "DecayTree", filename2);  


//        cout<<(filename2+ext).c_str()<<endl;
//        cout<<decaytreename<<endl;
//        cutTree((filename2+ext).c_str(), decaytreename2, (filename2+"_investigateALLCORMandtigterMMreleasetriggerREQ"+ext).c_str(), "Bplus_MM>325");
//return(1);
//        cutTree((filename2+ext).c_str(), decaytreename2, (filename2+"_investigateALLCORMandtigterMMreleasetriggerREQ"+ext).c_str(), "Bplus_MM<325");
//
//        cutTree((filename2+ext).c_str(), decaytreename2, (filename2+"_investigateALLCORMandOP500"+ext).c_str(), "Bplus_MM>500");
//        cutTree((filename2+ext).c_str(), decaytreename2, (filename2+"_investigateALLCORMand500"+ext).c_str(), "Bplus_MM<500");


        

//        return(1);


        vector<string> varia;
//        varia.push_back("corrm");
        varia.push_back("trigger");
        varia.push_back("mu1nShared_mu2nShared_mu3nShared");
//        varia.push_back("qmincut");
        

        vector<string> vals;
//        vals.push_back("Bplus_Corrected_Mass > 6000");
        vals.push_back("(Bplus_L0MuonDecision_TOS==1.0) && (Bplus_Hlt1TrackMuonDecision_TOS==1.0)");// && ((Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0))");
        vals.push_back("mu1_nShared == 0.0 && mu2_nShared == 0.0 && mu3_nShared == 0.0");
//        vals.push_back("minq2 < 960400");
       


	for(int i(0);i<2;i++)
	{
		double eff;
		eff=cutTree((filename2+ext).c_str(), "DecayTree", (filename2+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
		out<<"$\\epsilon_{"+varia.at(i)+"}$ & "<<eff<<" \\\\ "<<endl;
		filename2=(filename2+"_"+varia.at(i)).c_str();
		toteff=toteff*eff;
	} 


        vals.push_back("Bplus_L0MuonDecision_TOS==1.0");
        vals.push_back("Bplus_Hlt1TrackMuonDecision_TOS==1.0");
        vals.push_back("(Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0)");

        varia.push_back("L0MuonDecisionTOS");
        varia.push_back("Hlt1TrackMuonDecisionTOS");
        varia.push_back("Hlt2orofDecisions");

        string filename3=(filenameclean).c_str();

        for(int i(2);i<5;i++)
        
        {
                double eff;
                eff=cutTree((filename3+ext).c_str(), "DecayTree", (filename3+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
                out<<"$\\epsilon_{"+varia.at(i)+"}$ & "<<eff<<" \\\\ "<<endl;
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


        string filename4=(filenameclean+"_L0MuonDecisionTOS_Hlt1TrackMuonDecisionTOS").c_str();

        for(int i(5);i<9;i++)
        {
                double eff;
                eff=cutTree((filename4+ext).c_str(), "DecayTree", (filename4+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
                out<<"$\\epsilon_{"+varia.at(i)+"}$ & "<<eff<<" \\\\ "<<endl;

        }        
//  







	out<<"$\\epsilon_{totaleff}$ & "<<toteff<<" \\\\ "<<endl;

	addKFoldandW(filename2, "DecayTree", filename2);
     
        out<<"Number of candidates left:  &"<< getmyentries((filename2+ext).c_str(), "DecayTree")<<endl;


        out<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{EFFICIENCIESCOMBI.txt}"<<endl;
        out<<"\\end{table}"<<endl;       
        out<<"\\end{document}"<<endl;

        out.close();



	return(0);



}



