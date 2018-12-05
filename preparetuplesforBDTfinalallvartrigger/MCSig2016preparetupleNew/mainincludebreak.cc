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
        out.open("EfficienciesNewTrigger.tex");

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


	string pathname = "/vols/lhcb/ss4314/tuplesallvar/B23MuNuMC2015/";
	string filename = "B23MuNuMC2015";
	string decaytreename = "B23MuNu_Tuple/DecayTree";
	string ext = ".root";
	string cuttag = "_MCtruth";
	string filename2 = (filename+cuttag).c_str();


        double decprodcut2 =0.185;
        double effrecostrip2= 0.111;
       
        out << "$\\epsilon_{decprodcut}$ &" << decprodcut2 << " & " << "(3544)10000" << " & "<< (sqrt(double(3544)*(1.0-((double(3544)/double(10000))))))*(1/double(10000))<<" \\\\ "<<endl;
        out << "$\\epsilon_{reco}$ &" << effrecostrip2 << " & "<<"0.10997 & (114190)1038372" << " & "<< (sqrt(double(114190)*(1.0-((double(1038372)/double(1038372))))))*(1/double(1038372)) <<" \\\\ "<<endl;


	double mctrutheff;
	mctrutheff=mctruth((pathname+filename).c_str(), decaytreename, (filename2).c_str());
        out << "$\\epsilon_{MC}$ &" << mctrutheff <<" - & "<< " - & " << " \\\\ "<<endl;


        convertbranchname(filename2, "DecayTree", filename2);
        addqsqinf(filename2, "DecayTree", filename2);        
        addcostheta(filename2, "DecayTree", filename2);  


        double L0eff(0);
        L0eff=calculateL0effMC(filename2, "DecayTree", "miau");
        out << "$\\epsilon_{L0}$ &" << L0eff <<" - & "<< " - & " << " \\\\ "<<endl;
	toteff = L0eff;
//        return(1);

        
        cutTree((filename2+ext).c_str(),"DecayTree",(filename2+"_L0MuonDecision"+ext).c_str(),"Bplus_L0MuonDecision_TOS==1.0");
        
        string file=(filename2+"_L0MuonDecisionTOS").c_str();

        vector<string> varia;
        varia.push_back("trigger");
//        varia.push_back("mu1nShared_mu2nShared_mu3nShared");
        varia.push_back("qmincut");
        

        vector<string> vals;
        vals.push_back("(Bplus_Hlt1TrackMuonDecision_TOS==1.0) && ((Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0))");
//        vals.push_back("mu1_nShared == 0.0 && mu2_nShared == 0.0 && mu3_nShared == 0.0");
        vals.push_back("minq2 < 960400");
       


        for(int i(0);i<1;i++)
        {
        double eff;
        double error;
        int numofentriesbefore;
        int numofentriesafter;
88

        eff=cutTree((file+ext).c_str(), "DecayTree", (file+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
        numofentriesbefore= getmyentries((file+ext).c_str(),"DecayTree");
        numofentriesafter= getmyentries((file+"_"+varia.at(i)+ext).c_str(),"DecayTree");
        error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
        out<<"$\\epsilon_{"+varia.at(i)+"}$  & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
        file=(file+"_"+varia.at(i)).c_str();
        toteff=toteff*eff;
        } 

        double jpsieff;
        jpsieff=Jpsi((file).c_str(), "DecayTree", (file+"_Jpsi").c_str());
        double error;
        int numofentriesbefore;
        int numofentriesafter;
        numofentriesbefore= getmyentries((file+ext).c_str(),"DecayTree");
        numofentriesafter= getmyentries((file+"_Jpsi"+ext).c_str(),"DecayTree");
        error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
        out << "$\\epsilon_{Jpsi}$ &" << jpsieff<<" & "<<numofentriesafter<<" & "<<error << " \\\\ "<<endl;
        toteff=toteff*jpsieff;
        file=(file+"_Jpsi").c_str();

        for(int i(1);i<2;i++)
        {
        double eff;
        double error;
        int numofentriesbefore;
        int numofentriesafter;
        eff=cutTree((file+ext).c_str(), "DecayTree", (file+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
        numofentriesbefore= getmyentries((file+ext).c_str(),"DecayTree");
        numofentriesafter= getmyentries((file+"_"+varia.at(i)+ext).c_str(),"DecayTree");
        error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
        out<<"$\\epsilon_{"+varia.at(i)+"}$ & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
        file=(file+"_"+varia.at(i)).c_str();
        toteff=toteff*eff;
        }

        out<<"$\\epsilon_{totaleff}$ & "<<toteff<<" \\\\ "<<endl;

        addKFoldandW(file, "DecayTree", file);


//	vals.push_back("Bplus_L0MuonDecision_TOS==1.0");
	vals.push_back("Bplus_Hlt1TrackMuonDecision_TOS==1.0");
	vals.push_back("(Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0)");

//	varia.push_back("L0MuonDecisionTOS");
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

        
	vals.push_back("Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0");
        vals.push_back("Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0");
        vals.push_back("Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0");
        vals.push_back("Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0");

	varia.push_back("Hlt2TopoMu2BodyBBDTDecision");
        varia.push_back("Hlt2TopoMu3BodyBBDTDecision");
        varia.push_back("Hlt2DiMuonDetachedDecision");
        varia.push_back("Hlt2DiMuonDetachedHeavyDecision");
        

	string filename4=(file+"_L0MuonDecisionTOS_Hlt1TrackMuonDecisionTOS").c_str();        

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
	//	filename3=(filename3+"_"+varia.at(i)).c_str();
	}

        out<<"\\hline"<<endl;
//         string filenamespec = namecuttree2;
//         string decaytreenamespec = "DecayTree";
//         string extspec = ".root";
//         string cuttagspec = "_trigger";
//         string namecuttreespec = (filenamespec+"_cut"+cuttagspec).c_str();
//         string cutspec = "(Bplus_L0MuonDecision_TOS==1.0) && (Bplus_Hlt1TrackMuonDecision_TOS==1.0) && ((Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0))";
//
//       double triggereff;
//       triggereff=cutTree((filenamespec+extspec).c_str(), decaytreenamespec, (namecuttreespec+extspec).c_str(), cutspec);
//       out << "$\\epsilon_{trig}$ &" << triggereff << " \\\\ "<<endl;
//
//
//
//
//
//	string filename2 = namecuttreespec;
//	string decaytreename2 = "DecayTree";
//	string ext2 = ".root";
//	string cuttag2 = "_Jpsi";
//	string namecuttree22 = (filename2+cuttag2).c_str();
//	double jpsieff;
//	jpsieff=Jpsi((filename2).c_str(), decaytreename2, (namecuttree22).c_str());
//        out << "$\\epsilon_{Jpsi}$ &" << jpsieff << " \\\\ "<<endl;
//
//	string filename3 = namecuttree22;
//	string decaytreename3 = "DecayTree";
//	string ext3 = ".root";
//	string cuttag3 = "_mu1nShared_mu2nShared_mu3nShared";
//	string namecuttree23 = (filename3+"_cut"+cuttag3).c_str();
//	string cut23 = "mu1_nShared == 0.0 && mu2_nShared == 0.0 && mu3_nShared == 0.0";
//        
//
//	double nSharedeff;
//	nSharedeff=cutTree((filename3+ext3).c_str(), decaytreename3, (namecuttree23+ext3).c_str(), cut23);
//        out << "$\\epsilon_{nShared}$ &" << nSharedeff << " \\\\ "<<endl;
//
//        string filenamecon = namecuttree23;
//        string decaytreenamecon = "DecayTree";
//        string extcon = ".root";
//        string cuttagcon = "";
//        string namecuttreecon = (filenamecon+cuttagcon).c_str();
//        convertbranchname(filenamecon.c_str(), decaytreenamecon, (namecuttreecon).c_str());
//
//	string filename5 = namecuttreecon;
//	string decaytreename5 = "DecayTree";
//	string ext5 = ".root";
//	string cuttag5 = "";
//	string namecuttree25 = (filename5+cuttag5).c_str();
//	addqsqinf(filename5.c_str(), decaytreename5, (namecuttree25).c_str());
//
//	string filename6 = namecuttree25;
//	string decaytreename6 = "DecayTree";
//	string ext6 = ".root";
//	string cuttag6 = "_qmincut";
//	string namecuttree26 = (filename6+cuttag6).c_str();
//	string cut26 = "minq2 < 960400";
//
//
//
//	double qmineff;
//	qmineff=cutTree((filename6+ext).c_str(), decaytreename6, (namecuttree26+ext).c_str(), cut26);
//        out << "$\\epsilon_{qmin}$ &" << qmineff << " \\\\ "<<endl;
//
//
//        string filename4 = namecuttree26;
//        string decaytreename4 = "DecayTree";
//        string ext4 = ".root";
//        string cuttag4 = "";
//        string namecuttree24 = (filename4+cuttag4).c_str();
//
//        addKFoldandW(filename4.c_str(), decaytreename4, (namecuttree24).c_str());

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



