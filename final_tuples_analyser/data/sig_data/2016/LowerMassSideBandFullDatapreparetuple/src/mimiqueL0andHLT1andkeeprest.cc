
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
        out.open("EfficienciesRecalibrate_mimiqueL0andHLT1andkeeprest.tex");

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
        out<<"Cut & $\\epsilon$   \\\\ "<<endl;
        out<<"\\hline"<<endl;


      
        double toteff(1.0);

        string pathname = "/vols/lhcb/ss4314/final_tuples/data/sig_data/2016/";
        string filename = "Bu23MuNuData2016";
        string decaytreename = "B_Tuple/DecayTree";
        string ext = ".root";
	string cuttag = "_mimiqueL0andHLT1";
	string filename2 = (filename+cuttag).c_str();
        string filenameclean=filename;

        cutTree((pathname+filename+ext).c_str(), decaytreename, (filename2+ext).c_str(), "");


       convertbranchname(filename2, "DecayTree", filename2);
       addqsqinf(filename2, "DecayTree", filename2);        
       addcostheta(filename2, "DecayTree", filename2);  


//        printvalue((filename2+ext).c_str(), "DecayTree", "HLT1TCK");
//        getTCKprop(filename2, "DecayTree",(filename2+"_recount").c_str());
//        emulatetrigger(filename2+"_corrmFUSMB", "DecayTree", (filename2+"_corrmFUSMB_emulated").c_str());
//        mimiqueL0effMC(filename2, "DecayTree", "myattempt");
//        mimiqueHLT1effMC("myattempt", "DecayTree", "myattemptHLT1");
//        return(1);

        vector<string> varia;
        varia.push_back("corrmLSDfull");
        varia.push_back("trigger");
        varia.push_back("mu1isMuonTight_mu2isMuonTight_mu3isMuonTight");
        varia.push_back("mu1MuonNShared_mu2MuonNShared_mu3MuonNShared");
        varia.push_back("qmincut");


        vector<string> vals;
        vals.push_back(" Bplus_Corrected_Mass < 4500");
        vals.push_back("((Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0))");
        vals.push_back("mu1_isMuonTight == 1.0 && mu2_isMuonTight == 1.0 && mu3_isMuonTight == 1.0");
        vals.push_back("mu1_MuonNShared < 2 && mu2_MuonNShared < 2 && mu3_MuonNShared < 2");

//        vals.push_back("mu1_MuonNShared == 0.0 && mu2_MuonNShared == 0.0 && mu3_MuonNShared == 0.0");
        vals.push_back("minq2 < 960400");



	for(int i(0);i<1;i++)
	{
                double error;
                int numofentriesbefore;
                int numofentriesafter;
                double eff;
                eff=cutTree((filename2+ext).c_str(), "DecayTree", (filename2+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
                numofentriesbefore= getmyentries((filename2+ext).c_str(),"DecayTree");
                numofentriesafter= getmyentries((filename2+"_"+varia.at(i)+ext).c_str(),"DecayTree");
                error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
                out<<"$\\epsilon_{"+varia.at(i)+"}$ & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
		filename2=(filename2+"_"+varia.at(i)).c_str();
		toteff=toteff*eff;
	} 

        double L0eff(0);
	L0eff=mimiqueL0effMC(filename2, "DecayTree", (filename2+"_L0MuonDecisionDEC").c_str());
        filename2=(filename2+"_L0MuonDecisionDEC").c_str();
        out << "$\\epsilon_{L0}$ &" << L0eff <<"&"<< getmyentries((filename2+ext).c_str(),"DecayTree") << "  & " << " \\\\ "<<endl;

        double hlt1eff(0);
       	hlt1eff=mimiqueHLT1effMC(filename2, "DecayTree", (filename2+"_Hlt1TrackMuonDecisionTUP").c_str());
        filename2=(filename2+"_Hlt1TrackMuonDecisionTUP").c_str();
        out << "$\\epsilon_{HLT1}$ &" << hlt1eff <<"&"<< getmyentries((filename2+ext).c_str(),"DecayTree") << "  & " << " \\\\ "<<endl;


	for(int i(1);i<2;i++)
	{
                double error;
                int numofentriesbefore;
                int numofentriesafter;
                double eff;
                eff=cutTree((filename2+ext).c_str(), "DecayTree", (filename2+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
                numofentriesbefore= getmyentries((filename2+ext).c_str(),"DecayTree");
                numofentriesafter= getmyentries((filename2+"_"+varia.at(i)+ext).c_str(),"DecayTree");
                error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
                out<<"$\\epsilon_{"+varia.at(i)+"}$ & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
		filename2=(filename2+"_"+varia.at(i)).c_str();
		toteff=toteff*eff;
	} 


	double jpsieff;
	jpsieff=Jpsi((filename2).c_str(), "DecayTree", (filename2+"_Jpsi").c_str());
        filename2=(filename2+"_Jpsi").c_str();   
	out << "$\\epsilon_{Jpsi}$ &" << jpsieff << " & "<<getmyentries((filename2+ext).c_str(),"DecayTree")<<" & \\\\ "<<endl;
	toteff=toteff*jpsieff;


	for(int i(2);i<5;i++)
	{
                 double error;
                 int numofentriesbefore;
                 int numofentriesafter;
                 double eff;
	

                eff=cutTree((filename2+ext).c_str(), "DecayTree", (filename2+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
                numofentriesbefore= getmyentries((filename2+ext).c_str(),"DecayTree");
                numofentriesafter= getmyentries((filename2+"_"+varia.at(i)+ext).c_str(),"DecayTree");
                error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
                out<<"$\\epsilon_{"+varia.at(i)+"}$ & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
                filename2=(filename2+"_"+varia.at(i)).c_str();
                toteff=toteff*eff;
	}

	out<<"$\\epsilon_{totaleff}$ & "<<toteff<<" \\\\ "<<endl;

	addKFoldandW(filename2, "DecayTree", filename2);
     
        out<<"Number of candidates left:  & "<< getmyentries((filename2+ext).c_str(), "DecayTree")<<" & & \\\\"<<endl;

//        vals.push_back("Bplus_L0MuonDecision_TOS==1.0");
//        vals.push_back("Bplus_Hlt1TrackMuonDecision_TOS==1.0");
//        vals.push_back("(Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0)");
//
//        varia.push_back("L0MuonDecisionTOS");
//        varia.push_back("Hlt1TrackMuonDecisionTOS");
//        varia.push_back("Hlt2orofDecisions");
//
//        string filename3=(filenameclean+"_corrmFUSMB").c_str();
//
//        for(int i(4);i<4;i++)
//        {
//               double error;
//               int numofentriesbefore;
//               int numofentriesafter;
//                double eff;
//                eff=cutTree((filename3+ext).c_str(), "DecayTree", (filename3+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
//                numofentriesbefore= getmyentries((filename3+ext).c_str(),"DecayTree");
//                numofentriesafter= getmyentries((filename3+"_"+varia.at(i)+ext).c_str(),"DecayTree");
//                error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
//                out<<varia.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
//                filename3=(filename3+"_"+varia.at(i)).c_str();
//        }
        out<<"\\hline"<<endl;


        vals.push_back("Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0");
        vals.push_back("Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0");
        vals.push_back("Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0");
        vals.push_back("Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0");

        varia.push_back("Hlt2TopoMu2BodyDecision");
        varia.push_back("Hlt2TopoMu3BodyDecision");
        varia.push_back("Hlt2DiMuonDetachedDecision");
        varia.push_back("Hlt2DiMuonDetachedHeavyDecision");


        string filename4=(filenameclean+"_mimiqueL0andHLT1_corrmFUSMB_L0MuonDecisionDEC_Hlt1TrackMuonDecisionTUP").c_str();

        for(int i(5);i<9;i++)
        {
               double error;
               int numofentriesbefore;
               int numofentriesafter;
                double eff;
                eff=cutTree((filename4+ext).c_str(), "DecayTree", (filename4+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
                numofentriesbefore= getmyentries((filename4+ext).c_str(),"DecayTree");
                numofentriesafter= getmyentries((filename4+"_"+varia.at(i)+ext).c_str(),"DecayTree");
                error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
                out<<varia.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
        //      filename3=(filename3+"_"+varia.at(i)).c_str();
        }
        //
        //                      }
        //
//	string pathname = "/vols/lhcb/ss4314/tuplesallvar/Data2015/";
//	string filename = "Data2015";
//	string decaytreename = "B_Tuple/DecayTree";
//	string ext = ".root";
//	string cuttag = "_corrm";
//	string namecuttree2 = (filename+cuttag).c_str();
//	string cut2 = "Bplus_Corrected_Mass > 6000";
//
//	double cutmcorr;
//        cutmcorr=cutTree((pathname+filename+ext).c_str(), decaytreename, (namecuttree2+ext).c_str(), cut2);
//
//
////        string filenamespec = namecuttree2;
////        string decaytreenamespec = "DecayTree";
////        string extspec = ".root";
////        string cuttagspec = "_trigger";
////        string namecuttreespec = (filenamespec+"_cut"+cuttagspec).c_str();
////        string cutspec = "(Bplus_L0MuonDecision_TOS==1.0) && (Bplus_Hlt1TrackMuonDecision_TOS==1.0)";// && (Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0 || Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0) && (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) && (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0)";
//
////        double triggereff;
////        triggereff=cutTree((filenamespec+extspec).c_str(), decaytreenamespec, (namecuttreespec+extspec).c_str(), cutspec);
//
// //       return(1);
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
//	string filename2 = namecuttreespec;
//	string decaytreename2 = "DecayTree";
//	string ext2 = ".root";
//	string cuttag2 = "_Jpsi";
//	string namecuttree22 = (filename2+cuttag2).c_str();
//	double jpsieff;
//	jpsieff=Jpsi((filename2).c_str(), decaytreename2, (namecuttree22).c_str());
//
//        out << "$\\epsilon_{Jpsi}$ &" << jpsieff << " \\\\ "<<endl;
//
//	//string pathname = "";
//	string filename3 = namecuttree22;
//	string decaytreename3 = "DecayTree";
//	string ext3 = ".root";
//	string cuttag3 = "_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared";
//	string namecuttree23 = (filename3+"_cut"+cuttag3).c_str();
//	string cut23 = "mu1_MuonNShared == 0.0 && mu2_MuonNShared == 0.0 && mu3_MuonNShared == 0.0";
//
//	double MuonNSharedeff;
//	MuonNSharedeff=cutTree((filename3+ext3).c_str(), decaytreename3, (namecuttree23+ext3).c_str(), cut23);
//
//        out << "$\\epsilon_{MuonNShared}$ &" << MuonNSharedeff << " \\\\ "<<endl;
//       
//        
//       
//
//        string filenamecon = namecuttree23;
//        string decaytreenamecon = "DecayTree";
//        string extcon = ".root";
//        string cuttagcon = "";
//        string namecuttreecon = (filenamecon+cuttagcon).c_str();
//        convertbranchname(filenamecon.c_str(), decaytreenamecon, (namecuttreecon).c_str());
//        converttobplus(filenamecon.c_str(), decaytreenamecon, (namecuttreecon).c_str());
//
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
//
//
//	double qmineff;
//	qmineff=cutTree((filename6+ext).c_str(), decaytreename6, (namecuttree26+ext).c_str(), cut26);
//
//        out << "$\\epsilon_{qmin}$ &" << qmineff << " \\\\ "<<endl;
//
//        string filename4 = namecuttree26;
//        string decaytreename4 = "DecayTree";
//        string ext4 = ".root";
//        string cuttag4 = "";
//        string namecuttree24 = (filename4+cuttag4).c_str();
//
//        addKFoldandW(filename4.c_str(), decaytreename4, (namecuttree24).c_str());

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



