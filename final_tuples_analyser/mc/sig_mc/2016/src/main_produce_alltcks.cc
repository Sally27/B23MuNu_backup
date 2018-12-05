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

//        double toteff(0);


	string pathname = "/vols/lhcb/ss4314/final_tuples/mc/sig_mc/2016/";
	string filename = "Bu23MuNuMC2016";
        string decaytreename = "B23MuNu_Tuple/DecayTree";
        string ext = ".root";
        string cuttag = "_MCtruth";
        string filename2 = (filename+cuttag).c_str();

        double mctrutheff;
        mctrutheff=mctruth((pathname+filename).c_str(), decaytreename, (filename2).c_str());

        convertbranchname(filename2, "DecayTree", filename2);
        addqsqinf(filename2, "DecayTree", filename2);
        addcostheta(filename2, "DecayTree", filename2);

        //----------------------External variables----------------------------//
        double decprodcut2 =0.19139;
        int num_evt_bkk=1107715;

        //----------------------ALL tck related businnes-----------------------//

        Int_t tcks[] = {287905280,287905283,287905284,287905285,288495113,288626185,288691721,288757257,288822793,288822798,288888329,288888334,288888335,288888337,288888338,288888339};

        vector<Int_t> mytcks(tcks, tcks+sizeof(tcks)/ sizeof(Int_t) );

        double L0thresh[] = {14,22,26,30,26,26,26,26,26,30,26,30,36,30,32,27};
	vector<double> values(L0thresh, L0thresh+sizeof(L0thresh)/ sizeof(double) );

        string filenameclean="la";
        string file="la";

	double valuesP[] = {6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0};

	vector<double> myvaluesP(valuesP, valuesP+sizeof(valuesP)/ sizeof(double) );

	double valuesPT[] = {910.0,910.0,910.0,910.0,910.0,910.0,1100.0,1100.0,1100.0,1100.0,1100.0,1100.0,1100.0,1100.0,1100.0,1100.0};

	vector<double> myvaluesPT(valuesPT, valuesPT+sizeof(valuesPT)/ sizeof(double) );

	double valuesMINIPCHI2[] = {10.0,10.0,10.0,10.0,10.0,10.0,35.0,35.0,35.0,35.0,35.0,35.0,35.0,35.0,35.0,35.0};

	vector<double> myvaluesMINIPCHI2(valuesMINIPCHI2, valuesMINIPCHI2+sizeof(valuesMINIPCHI2)/ sizeof(double) );

	double valuesTRACKCHI2[] = {3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0};

	vector<double> myvaluesTRACKCHI2(valuesTRACKCHI2, valuesTRACKCHI2+sizeof(valuesTRACKCHI2)/ sizeof(double) );

	double valuesGHOSTPROB[] ={999999.9,999999.9,999999.9,999999.9,999999.9,9999.0,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2};

	vector<double> myvaluesGHOSTPROB(valuesGHOSTPROB, valuesGHOSTPROB+sizeof(valuesGHOSTPROB)/ sizeof(double) );



        //-------------------Looping over all possible TCKs------------------//

	for(int l(0); l<values.size();l++){ //values.size()

        	TFile *fillinfo = new TFile(("Efficiencies_2016_"+i2s(mytcks.at(l))+".root").c_str(),"RECREATE");
        	TTree *fillinfotree = new TTree("MC_Sig_2016","MC_Sig_2016");
              
        	
		FillEffInfo(fillinfotree, "decprodcut",decprodcut2,false);
                FillEffInfo(fillinfotree, "numbkk",double(num_evt_bkk),true);

                double toteff(1.0);
		ofstream out;
		out.open(("alltcks/EfficienciesRecalibrate_ApplyL0_"+i2s(l)+"_"+i2s(mytcks.at(l))+".tex").c_str());

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


		out << "$\\epsilon_{decprodcut}$ &" << decprodcut2 << " & " << " " << " & "<< " "<<" \\\\ "<<endl;
                out << "$\\epsilon_{MC}$ &" << mctrutheff <<" - & "<< " - & " << " \\\\ "<<endl;
                out << "$\\epsilon_{reco}$ &" << double(getmyentries((filename2+ext).c_str(),"DecayTree"))/double(num_evt_bkk) << " & "<<"("<<getmyentries((filename2+ext).c_str(),"DecayTree")<<")"<<i2s(num_evt_bkk)<< " & "<< (sqrt(double(getmyentries((filename2+ext).c_str(),"DecayTree"))*(1.0-((double(getmyentries((filename2+ext).c_str(),"DecayTree"))/double(num_evt_bkk))))))*(1/double(num_evt_bkk)) <<" \\\\ "<<endl;
                out<<"\\hline"<<endl;

        	FillEffInfo(fillinfotree, "reco",double( double(getmyentries((filename2+ext).c_str(),"DecayTree"))/double(num_evt_bkk)),true);

		double L0eff(0);
		L0eff=cutTree((filename2+ext).c_str(),"DecayTree",(filename2+"_L0MuonDecisionTOS_"+i2s(mytcks.at(l))+ext).c_str(),("L0Data_Muon1_Pt>"+d2s(values.at(l))+" && L0Data_Spd_Mult < 450").c_str());

        	FillEffInfo(fillinfotree, "L0",L0eff,true);

		string filenameclean_L0=(filename2+"_L0MuonDecisionTOS_"+i2s(mytcks.at(l))).c_str();
		string file_L0=(filename2+"_L0MuonDecisionTOS_"+i2s(mytcks.at(l))).c_str();
		out << "$\\epsilon_{L0}$ "<< l <<" &" << L0eff <<"&"<< getmyentries((filenameclean_L0+ext).c_str(),"DecayTree") << "  & " << " \\\\ "<<endl;
                toteff=toteff*L0eff;      

                double HLT1eff(0);
                string hlt1string="((mu1_PT>"+d2s(myvaluesPT.at(l))+" && mu1_P>"+d2s(myvaluesP.at(l))+" && mu1_ghost<"+d2s(myvaluesGHOSTPROB.at(l))+" && mu1_TRACK_CHI2<"+d2s(myvaluesTRACKCHI2.at(l))+" && mu1_MINIPCHI2>"+d2s(myvaluesMINIPCHI2.at(l))+")||(mu2_PT>"+d2s(myvaluesPT.at(l))+" && mu2_P>"+d2s(myvaluesP.at(l))+" && mu2_ghost<"+d2s(myvaluesGHOSTPROB.at(l))+" && mu2_TRACK_CHI2<"+d2s(myvaluesTRACKCHI2.at(l))+" && mu2_MINIPCHI2>"+d2s(myvaluesMINIPCHI2.at(l))+")||(mu3_PT>"+d2s(myvaluesPT.at(l))+" && mu3_P>"+d2s(myvaluesP.at(l))+" && mu3_ghost<"+d2s(myvaluesGHOSTPROB.at(l))+" && mu3_TRACK_CHI2<"+d2s(myvaluesTRACKCHI2.at(l))+" && mu3_MINIPCHI2>"+d2s(myvaluesMINIPCHI2.at(l))+"))";

                HLT1eff=cutTree((filenameclean_L0+ext).c_str(),"DecayTree",(filenameclean_L0+"_Hlt1TrackMuonDecision"+ext).c_str(),(hlt1string).c_str());
		                
        	FillEffInfo(fillinfotree, "HLT1",HLT1eff,true);

                string filenameclean=(filenameclean_L0+"_Hlt1TrackMuonDecision").c_str();
                string file=(filenameclean_L0+"_Hlt1TrackMuonDecision").c_str();
		out << "$\\epsilon_{HLT1}$ "<< l <<" &" << HLT1eff <<"&"<< getmyentries((filenameclean+ext).c_str(),"DecayTree") << "  & " << " \\\\ "<<endl;
                toteff=toteff*HLT1eff;


		vector<string> varia;
		varia.push_back("trigger");
		varia.push_back("qmincut");



		vector<string> vals;
		vals.push_back("((Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0))");
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
                        
        		FillEffInfo(fillinfotree, varia.at(i), eff,true);
		} 

		double jpsieff;
		jpsieff=Jpsi((filenameclean).c_str(), "DecayTree", (filenameclean+"_Jpsi").c_str());
		
        	FillEffInfo(fillinfotree, "jpsi", jpsieff,true);
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
                         
        		FillEffInfo(fillinfotree, varia.at(i), eff,true);
		}
		out<<"\\hline"<<endl;
		out<<"$\\epsilon_{totaleff}$ & "<<toteff<<" \\\\ "<<endl;
		out<<"\\hline"<<endl;


		addKFoldandW(filenameclean, "DecayTree", filenameclean);
                addtcklumi(filenameclean, "DecayTree", filenameclean, l);

//		vals.push_back("Bplus_Hlt1TrackMuonDecision_TOS==1.0");
		vals.push_back("(Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0)");

//		varia.push_back("Hlt1TrackMuonDecisionTOS");
		varia.push_back("Hlt2orofDecisions");

		string filename3=(file).c_str();

		for(int i(2);i<3;i++)
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
                        
        		FillEffInfo(fillinfotree, varia.at(i), eff,true);
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


		string filename4=file;        

		for(int i(3);i<7;i++)
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
			
        		FillEffInfo(fillinfotree, varia.at(i), eff,true);
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
		
        	FillEffInfo(fillinfotree, "toteff", toteff,true);

		fillinfo->cd();
		fillinfotree->Write("",TObject::kOverwrite);

        	delete fillinfotree;
		delete fillinfo;
		out<<"TotSig asuming 10$^-8$ & "<<finalnum<<" \\\\ "<<endl;
		out<<" \\\\ "<<endl;
		out<<"\\hline"<<endl;
		out<<"\\end{tabular}"<<endl;
		out<<"\\end{center}"<<endl;
		out<<"\\caption{EFFICIENCIESMCSIG.txt}"<<endl;
		out<<"\\end{table}"<<endl;       
		out<<"\\end{document}"<<endl;

		out.close();


	}
	return(0);



}



