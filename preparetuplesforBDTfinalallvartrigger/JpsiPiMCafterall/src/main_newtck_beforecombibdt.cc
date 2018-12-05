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

	//string pathname = "/vols/lhcb/ss4314/tuplesallvar/B23MuNuMC/";
	//string filename = "B23MuNuMCallvar";
	//string decaytreename = "B23MuNu_Tuple/DecayTree";
	//string ext = ".root";
	//string cuttag = "_MCtruth";
	//string namecuttree2 = (filename+cuttag).c_str();

	//	double mctrutheff;
	//	mctrutheff=mctruth((pathname+filename).c_str(), decaytreename, (namecuttree2).c_str());

	ofstream out;
	out.open("Efficiencies_combibdt.tex");

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
	out<<"dec prod cut & 0.16743(md from simstat) & 3554(10000) & TBD \\\\ "<<endl;
	out<<"or strip and reco & 0.31575 & 2539870(8043820) & TBD  \\\\ "<<endl;
        
        int p(0);
          
        if (p==0)
        {
	string pathname = "/vols/lhcb/ss4314/preparejpsipiweights/preparejpsipiweights_FUMSB_NOTsimultaneous_before_combibdt/bin/";
	string filename = "JpsiPiMC2012BasicCut";
	string decaytreename = "DecayTree";
	string ext = ".root";
	string cuttag = "";
	string filename2 = (filename+cuttag).c_str();
        string filenameclean = filename;

	cutTree((pathname+filename+ext).c_str(), decaytreename, (filename+ext).c_str(), "");
	addqsqinf(filename2, "DecayTree", filename2);
	addcostheta(filename2, "DecayTree", filename2);
 

	vector<string> varia;
	varia.push_back("PTkaon");
	varia.push_back("Blifetime");
        varia.push_back("firstpid");
        varia.push_back("secondpid");

	vector<string> vals;
	vals.push_back("mu3_PT > 500");
        vals.push_back("Bplus_TAU > 0.0002");
        vals.push_back("mu3_PIDK > 0");
        vals.push_back("mu3_PIDp - mu3_PIDK > 5");
        

 //       vector<double> errors;
        vector<int> numofevents;
        numofevents.push_back(1865621);

	        for(int i(0);i<2;i++)
	        {
               double error;
	       double eff;
               int numofentriesbefore;
               int numofentriesafter;         
	       eff=cutTree((filename+ext).c_str(), "DecayTree", (filename+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
               numofentriesbefore= getmyentries((filename+ext).c_str(),"DecayTree");
               numofentriesafter= getmyentries((filename+"_"+varia.at(i)+ext).c_str(),"DecayTree");
               error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
               out<<vals.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
	       filename=(filename+"_"+varia.at(i)).c_str();
	        } 

	
        addkaonhypoinf(filename, "DecayTree", filename);
        convertbranchname(filename, "DecayTree", filename, "Bplus_MM", "Bplus_MM_Old");
        removebranchname(filename, "DecayTree","Bplus_MM",filename);
        convertbranchname(filename, "DecayTree", filename, "Bplus_MM_New", "Bplus_MM");

        out<<"\\hline"<<endl;


	out<<"TOT left in tuple &" << getmyentries((filename2+ext).c_str(), "DecayTree")<<" \\\\ "<<endl;

	out<<"\\hline"<<endl;


	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{SPECIALEFFICIENCIES.txt}"<<endl;
	out<<"\\end{table}"<<endl;

	out<<"\\end{document}"<<endl;

        }

	//        return(0);
	//
	//
	////        return(1);
	//
	//        string filenamespec = namecuttree1;
	//        string decaytreenamespec = "DecayTree";
	//        string extspec = ".root";
	//        string cuttagspec = "_trigger";
	//        string namecuttreespec = (filenamespec+"_cut"+cuttagspec).c_str();
	//        string cutspec = "(Bplus_L0MuonDecision_TOS==1.0) && (Bplus_Hlt1TrackMuonDecision_TOS==1.0) && ((Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0))";
	//
	//        double triggereff;
	//        triggereff=cutTree((filenamespec+extspec).c_str(), decaytreenamespec, (namecuttreespec+extspec).c_str(), cutspec);
	//        out << "$\\epsilon_{trig}$ &" << triggereff << " \\\\ "<<endl;
	//
	//        string filename = namecuttreespec;
	//        string decaytreename = "DecayTree";
	//        string ext = ".root";
	//        string cuttag = "_mu3isNotMuon_mu3inMuonAcc";
	//        string namecuttree2 = (filename+cuttag).c_str();
	//        string cut2 = "mu3_isMuon == 0.0 && mu3_inMuon == 1.0";
	//        double notmuoneff;
	//        notmuoneff=cutTree((filename+ext).c_str(), decaytreename, (namecuttree2+ext).c_str(), cut2);
	//        cout<<"Not muoneff eff: "<<notmuoneff<<endl;
	//        out << "Not muoneff &" << notmuoneff << " \\\\ "<<endl;
	//
	////	string filename2 = namecuttree2;
	////	string decaytreename2 = "DecayTree";
	////	string ext2 = ".root";
	////	string cuttag2 = "_Jpsi";
	////	string namecuttree22 = (filename2+cuttag2).c_str();
	////	double jpsieff;
	////	jpsieff=Jpsi((filename2).c_str(), decaytreename2, (namecuttree22).c_str());
	////        cout<<"Jpsi veto: "<<jpsieff<<endl;
	////        out <<"Jpsi veto &" << jpsieff << " \\\\ "<<endl;
	//
	//	//string pathname = "";
	//	string filename3 = namecuttree2;
	//	string decaytreename3 = "DecayTree";
	//	string ext3 = ".root";
	//	string cuttag3 = "_mu1nShared_mu2nShared";
	//	string namecuttree23 = (filename3+"_cut"+cuttag3).c_str();
	//	string cut23 = "mu1_nShared == 0.0 && mu2_nShared == 0.0";
	//
	//	double nSharedeff;
	//	nSharedeff=cutTree((filename3+ext3).c_str(), decaytreename3, (namecuttree23+ext3).c_str(), cut23);
	//      
	//        cout<<"NShared eff: "<<nSharedeff<<endl;
	//        out <<"Nshared eff &" << nSharedeff << " \\\\ "<<endl;
	//
	//       
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
	//
	//	addqsqinf(filename5.c_str(), decaytreename5, (namecuttree25).c_str());
	//
	//	string filename6 = namecuttree25;
	//	string decaytreename6 = "DecayTree";
	//	string ext6 = ".root";
	//	string cuttag6 = "_qmincut";
	//	string namecuttree26 = (filename6+cuttag6).c_str();
	//	string cut26 = "minq2 < 960400";
	//
	//	double qmineff;
	//	qmineff=cutTree((filename6+ext).c_str(), decaytreename6, (namecuttree26+ext).c_str(), cut26);
	//        out <<"qmineff eff & " << qmineff << " \\\\ "<<endl;
	//
	//
	//        string filename4 = namecuttree26;
	//        string decaytreename4 = "DecayTree";
	//        string ext4 = ".root";
	//        string cuttag4 = "";
	//        string namecuttree24 = (filename4+cuttag4).c_str();
	//
	//        addKFoldandW(filename4.c_str(), decaytreename4, (namecuttree24).c_str());
	//
	//        string filename8 = namecuttree24;
	//        string decaytreename8 = "DecayTree";
	//        string ext8 = ".root";
	//        string cuttag8 = "_KaonPID";
	//        string namecuttree28 = (filename8+cuttag8).c_str();
	//        string cut28 = "(mu3_PIDK > 0) && (mu3_PIDp - mu3_PIDK < 5)";
	//
	//        double idenkaon;
	//        idenkaon=cutTree((filename8+ext8).c_str(), decaytreename8, (namecuttree28+ext8).c_str(), cut28);
	//        out <<"idenkaon & " << idenkaon << " \\\\ "<<endl;
	//
	//
	//
	//        out<<"\\hline"<<endl;
	//        out<<"\\end{tabular}"<<endl;
	//        out<<"\\end{center}"<<endl;
	//        out<<"\\caption{SPECIALEFFICIENCIES.txt}"<<endl;
	//        out<<"\\end{table}"<<endl;
	//
	//        out<<"\\end{document}"<<endl;
	//
	//        out.close();
	//
	////        return(1);
	//
	//
	//
	//
	//
	////        string filename7 = namecuttree26;
	////        string decaytreename7 = "DecayTree";
	////        string ext7 = ".root";
	////        string cuttag7 = "_PionPID";
	////        string namecuttree27 = (filename7+cuttag7).c_str();
	////        string cut27 = "(mu3_PIDK < 0) && (mu3_PIDp < 5)";
	////
	////        double idenpion;
	////        idenpion=cutTree((filename7+ext7).c_str(), decaytreename7, (namecuttree27+ext7).c_str(), cut27);
	////
	////	string filename8 = namecuttree26;
	////	string decaytreename8 = "DecayTree";
	////	string ext8 = ".root";
	////	string cuttag8 = "_KaonPID";
	////	string namecuttree28 = (filename8+cuttag8).c_str();
	////	string cut28 = "(mu3_PIDK > 0) && (mu3_PIDp - mu3_PIDK < 5)";
	////
	////	double idenkaon;
	////	idenkaon=cutTree((filename8+ext8).c_str(), decaytreename8, (namecuttree28+ext8).c_str(), cut28);
	////
	////
	////        string filename48 = namecuttree27;
	////        string decaytreename48 = "DecayTree";
	////        string ext48 = ".root";
	////        string cuttag48 = "";
	////        string namecuttree248 = (filename48+cuttag48).c_str();
	////
	////        addKFoldandW(filename48.c_str(), decaytreename48, (namecuttree248).c_str());
	////
	////        string filename46 = namecuttree28;
	////        string decaytreename46 = "DecayTree";
	////        string ext46 = ".root";
	////        string cuttag46 = "";
	////        string namecuttree246 = (filename46+cuttag46).c_str();
	////
	////        addKFoldandW(filename46.c_str(), decaytreename46, (namecuttree246).c_str());
	//
	//
	//
	//
	//
	//	return(0);



}



