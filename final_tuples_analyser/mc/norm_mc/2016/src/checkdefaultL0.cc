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
	out.open("EfficienciesRecalibrate_ApplyL0.tex");

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
	out<<"dec prod cut & 0.1738(from simstat)  & TBD \\\\ "<<endl;

	int p(0);

	if (p==0)
	{


		string pathname = "/vols/lhcb/ss4314/final_tuples/mc/norm_mc/2016/";
		string filename = "B2JpsiKMC2016";
		string decaytreename = "B2JpsiK_Tuple/DecayTree";
		string ext = ".root";
		string cuttag = "_MCtruth";
		string filename2 = (filename+cuttag).c_str();
		string filenameclean=filename2; 
		string filenameforcomplex=filename2;


                mimiqueL0effMC_default(filename2, "DecayTree", "myattempt_default");
                return(1);

		double mctrutheff;
		mctrutheff=mctruth((pathname+filename).c_str(), decaytreename, (filename2).c_str());
		out << "$\\epsilon_{MC}$ &" << mctrutheff <<" - & "<< " - & " << " \\\\ "<<endl;
		out << "$\\epsilon_{reco}$ &" << double(getmyentries((filename2+ext).c_str(),"DecayTree"))/double(13231591) << " & "<<"("<<getmyentries((filename2+ext).c_str(),"DecayTree")<<")13231591" << " & "<< (sqrt(double(getmyentries((filename2+ext).c_str(),"DecayTree"))*(1.0-((double(getmyentries((filename2+ext).c_str(),"DecayTree"))/double(13231591))))))*(1/double(13231591)) <<" \\\\ "<<endl;
		out<<"\\hline"<<endl;

		convertbranchname(filename2, "DecayTree", filename2);
		addqsqinf(filename2, "DecayTree", filename2);
		addcostheta(filename2, "DecayTree", filename2);


		vector<string> varia;
		varia.push_back("DIRA");
		varia.push_back("PT");
		varia.push_back("ENDVERTEX_CHI2");
		varia.push_back("1ghost");
		varia.push_back("2ghost");
		varia.push_back("3ghost");
		varia.push_back("1TRACKCHI2");
		varia.push_back("2TRACKCHI2");
		varia.push_back("3TRACKCHI2");
		varia.push_back("mu1mipCHI2");
		varia.push_back("mu2mipCHI2");
		varia.push_back("mu3mipCHI2");
		//	varia.push_back("mu1PIDmu");
		//	varia.push_back("mu2PIDmu");
		//	varia.push_back("mu1PIDmmu1PIDK");
		//	varia.push_back("mu1PIDmmu2PIDK");
		varia.push_back("M");
		varia.push_back("Corrected_Mass");


		vector<string> vals;
		vals.push_back("Bplus_DIRA_OWNPV > 0.999");
		vals.push_back("Bplus_PT > 2000");
		vals.push_back("Bplus_ENDVERTEX_CHI2 < 4");
		vals.push_back("mu1_ghost < 0.35");
		vals.push_back("mu2_ghost < 0.35");
		vals.push_back("mu3_ghost < 0.35");
		vals.push_back("mu1_TRACK_CHI2 < 3.0");
		vals.push_back("mu2_TRACK_CHI2 < 3.0");
		vals.push_back("mu3_TRACK_CHI2 < 3.0");
		vals.push_back("mu1_MINIPCHI2 > 9.0");
		vals.push_back("mu2_MINIPCHI2 > 9.0");
		vals.push_back("mu3_MINIPCHI2 > 9.0");
		//	vals.push_back("mu1_PIDmu > 0");
		//	vals.push_back("mu2_PIDmu > 0");
		//	vals.push_back("(mu1_PIDmu - mu1_PIDK) > 0");
		//	vals.push_back("(mu2_PIDmu - mu2_PIDK) > 0");
		vals.push_back("Bplus_M > 0 && Bplus_M < 7500");
		vals.push_back("Bplus_Corrected_Mass > 2500 && Bplus_Corrected_Mass < 10000");


		vector<int> numofevents;

		for(int i(0);i<14;i++)
		{
			//			double error;
			//			double eff;
			//			int numofentriesbefore;
			//			int numofentriesafter;         
			//			eff=cutTree((filenameforcomplex+ext).c_str(), "DecayTree", (filenameforcomplex+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
			//			numofentriesbefore= getmyentries((filenameforcomplex+ext).c_str(),"DecayTree");
			//			numofentriesafter= getmyentries((filenameforcomplex+"_"+varia.at(i)+ext).c_str(),"DecayTree");
			//			error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
			//			out<<vals.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
			//			filenameforcomplex=(filenameforcomplex+"_"+varia.at(i)).c_str();
		} 

		out<<"\\hline"<<endl;

		varia.push_back("misidstrippingfull");
		//	varia.push_back("mu3isNotMuon_mu3inMuonAcc");
		varia.push_back("trigger");
		//	varia.push_back("mu1nShared_mu2nShared");
		//	varia.push_back("qmincut");
		//        varia.push_back("KaonPID");
		//        varia.push_back("mu1isMuonTight_mu2isMuonTight");
		//        varia.push_back("mu1MuonNShared_mu2MuonNShared");



		vals.push_back("Bplus_DIRA_OWNPV > 0.999 && Bplus_PT > 2000 && Bplus_ENDVERTEX_CHI2 < 4 && mu1_ghost < 0.35 && mu2_ghost < 0.35 && mu3_ghost < 0.35 && mu1_TRACK_CHI2 < 3.0 && mu2_TRACK_CHI2 < 3.0 && mu3_TRACK_CHI2 < 3.0 && mu1_MINIPCHI2 > 9.0 && mu2_MINIPCHI2 > 9.0  && mu3_MINIPCHI2 > 9.0 && Bplus_M > 0 && Bplus_M < 7500 && Bplus_Corrected_Mass > 2500 && Bplus_Corrected_Mass < 10000");
		//	vals.push_back("mu3_isMuon == 0.0 && mu3_inMuon == 1.0");
		vals.push_back("(Bplus_Hlt1TrackMuonDecision_TOS==1.0) && ((Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0))");
		//        vals.push_back("mu1_isMuonTight == 1.0 && mu2_isMuonTight == 1.0");
		//        vals.push_back("mu1_MuonNShared < 2 && mu2_MuonNShared < 2");


		//        vals.push_back("mu1_n < 2 && mu2_nShared < 2");
		//	vals.push_back("mu1_nShared < 2 && mu2_nShared < 2");
		//	vals.push_back("minq2 < 960400");
		//       vals.push_back("(mu3_PIDK > 0) && (mu3_PIDp - mu3_PIDK < 5)");
		double toteff(1.0);

		for(int i(14);i<15;i++)
		{
			double error;
			int numofentriesbefore;
			int numofentriesafter;
			double eff;
			eff=cutTree((filename2+ext).c_str(), "DecayTree", (filename2+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
			numofentriesbefore= getmyentries((filename2+ext).c_str(),"DecayTree");
			numofentriesafter= getmyentries((filename2+"_"+varia.at(i)+ext).c_str(),"DecayTree");
			error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
			out<<vals.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
			filename2=(filename2+"_"+varia.at(i)).c_str();
			toteff=toteff*eff;
		}
		out<<"\\hline"<<endl;


		double L0eff(0);
		L0eff=calculateL0effMC(filename2, "DecayTree", "miau");
		toteff = toteff*L0eff;


		cutTree((filename2+ext).c_str(),"DecayTree",(filename2+"_L0MuonDecisionTOS"+ext).c_str(),"Bplus_L0MuonDecision_TOS==1.0");

		string filename_trigger=(filename2+"_L0MuonDecisionTOS").c_str();
		string file=(filename2+"_L0MuonDecisionTOS").c_str();
		out << "$\\epsilon_{L0}$ &" << L0eff <<"&"<< getmyentries((filename_trigger+ext).c_str(),"DecayTree") << "  & " << " \\\\ "<<endl;

		for(int i(15);i<16;i++)
		{
			double error;
			int numofentriesbefore;
			int numofentriesafter;
			double eff;
			eff=cutTree((filename_trigger+ext).c_str(), "DecayTree", (filename_trigger+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
			numofentriesbefore= getmyentries((filename_trigger+ext).c_str(),"DecayTree");
			numofentriesafter= getmyentries((filename_trigger+"_"+varia.at(i)+ext).c_str(),"DecayTree");
			error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
			out<<vals.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
			filename_trigger=(filename_trigger+"_"+varia.at(i)).c_str();
			toteff=toteff*eff;
		}
		out<<"\\hline"<<endl;

		out<<"TOT left in tuple &" << getmyentries((filename_trigger+ext).c_str(), "DecayTree")<<" \\\\ "<<endl;
		out<<"\\hline"<<endl;
		out<<"$\\epsilon_{totaleff}$ & "<<toteff<<" \\\\ "<<endl;
		out<<"\\hline"<<endl;

		addKFoldandW(filename_trigger, "DecayTree", filename_trigger);

		vals.push_back("Bplus_Hlt1TrackMuonDecision_TOS==1.0");
		vals.push_back("(Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0)");

		varia.push_back("Hlt1TrackMuonDecisionTOS");
		varia.push_back("Hlt2orofDecisions");

		string filename3=(file).c_str();

		for(int i(16);i<18;i++)
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

		varia.push_back("Hlt2TopoMu2BodyDecision");
		varia.push_back("Hlt2TopoMu3BodyDecision");
		varia.push_back("Hlt2DiMuonDetachedDecision");
		varia.push_back("Hlt2DiMuonDetachedHeavyDecision");


		string filename4=(file+"_Hlt1TrackMuonDecisionTOS").c_str();        

		for(int i(19);i<23;i++)
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

	}


	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{SPECIALEFFICIENCIES.txt}"<<endl;
	out<<"\\end{table}"<<endl;

	out<<"\\end{document}"<<endl;






}



