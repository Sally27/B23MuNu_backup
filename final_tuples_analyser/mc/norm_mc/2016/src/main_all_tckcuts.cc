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


                //all tck related var definition//

		Int_t tcks[] = {287905280,287905283,287905284,287905285,288495113,288626185,288691721,288757257,288822793,288822798,288888329,288888334,288888335,288888337,288888338,288888339};
		vector<Int_t> mytcks(tcks, tcks+sizeof(tcks)/ sizeof(Int_t) );

		double L0thresh[] = {14,22,26,30,26,26,26,26,26,30,26,30,36,30,32,27};
		vector<double> values(L0thresh, L0thresh+sizeof(L0thresh)/ sizeof(double) );

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


                //all external definitions that need to be input//
                double decprodcut(0.1738);                
                int num_evt_bkk(13231591);
                

              
		double mctrutheff;
		mctrutheff=mctruth((pathname+filename).c_str(), decaytreename, (filename2).c_str());

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

		//out<<"\\hline"<<endl;

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
		vals.push_back("((Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0))");
		//        vals.push_back("mu1_isMuonTight == 1.0 && mu2_isMuonTight == 1.0");
		//        vals.push_back("mu1_MuonNShared < 2 && mu2_MuonNShared < 2");


		//        vals.push_back("mu1_n < 2 && mu2_nShared < 2");
		//	vals.push_back("mu1_nShared < 2 && mu2_nShared < 2");
		//	vals.push_back("minq2 < 960400");
		//       vals.push_back("(mu3_PIDK > 0) && (mu3_PIDp - mu3_PIDK < 5)");
                double misidstrippingfulleff(0);

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
//			out<<vals.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
			filename2=(filename2+"_"+varia.at(i)).c_str();
//			toteff=toteff*eff;
                        misidstrippingfulleff=eff;
		}
//		out<<"\\hline"<<endl;


		for(int l(0); l<values.size();l++){ 


			TFile *fillinfo = new TFile(("Efficiencies_2016_Norm_"+i2s(mytcks.at(l))+".root").c_str(),"RECREATE");
			TTree *fillinfotree = new TTree("MC_Norm_2016","MC_Norm_2016");


			FillEffInfo(fillinfotree, "decprodcut",decprodcut,false);
			FillEffInfo(fillinfotree, "numbkk",double(num_evt_bkk),true);




			double toteff(1.0);
                        toteff=toteff*misidstrippingfulleff;
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
			out<<"Cut & $\\epsilon$ & N &  \\\\ "<<endl;
			out<<"\\hline"<<endl;

			out<<"dec prod cut & "<<decprodcut<<"from simulation & TBD \\\\ "<<endl;
			out << "$\\epsilon_{MC}$ &" << mctrutheff <<" - & "<< " - & " << " \\\\ "<<endl;
			out << "$\\epsilon_{reco}$ &" << double(getmyentries((filename+cuttag+ext).c_str(),"DecayTree"))/double(num_evt_bkk) << " & "<<"("<<getmyentries((filename+cuttag+ext).c_str(),"DecayTree")<<")"<<i2s(num_evt_bkk) << " & "<< (sqrt(double(getmyentries((filename+cuttag+ext).c_str(),"DecayTree"))*(1.0-((double(getmyentries((filename+cuttag+ext).c_str(),"DecayTree"))/double(num_evt_bkk))))))*(1/double(num_evt_bkk)) <<" \\\\ "<<endl;
			out<<"\\hline"<<endl;

                        
        		FillEffInfo(fillinfotree, "reco",double(double(getmyentries((filename+cuttag+ext).c_str(),"DecayTree"))/double(num_evt_bkk)),true);

			out<<" misidstrippingfull & "<<misidstrippingfulleff<<" & "<<getmyentries((filename2+ext).c_str(),"DecayTree") <<"  & " << " \\\\ "<<endl;

			
        		FillEffInfo(fillinfotree, "misidstrippingfull",misidstrippingfulleff,true);

			double L0eff(0);
			L0eff=cutTree((filename2+ext).c_str(),"DecayTree",(filename2+"_L0MuonDecisionTOS_"+i2s(mytcks.at(l))+ext).c_str(),("L0Data_Muon1_Pt>"+d2s(values.at(l))+" && L0Data_Spd_Mult < 450").c_str());

        		FillEffInfo(fillinfotree, "L0",L0eff,true);
			string filenameclean_L0=(filename2+"_L0MuonDecisionTOS_"+i2s(mytcks.at(l))).c_str();
			string file_L0=(filename2+"_L0MuonDecisionTOS_"+i2s(mytcks.at(l))).c_str();
			out << "$\\epsilon_{L0}$ "<< l <<" &" << L0eff <<"&"<< getmyentries((filenameclean_L0+ext).c_str(),"DecayTree") << "  & " << " \\\\ "<<endl;


			toteff=toteff*L0eff;

			double HLT1eff(0);
			string hlt1string="((mu1_PT>"+d2s(myvaluesPT.at(l))+" && mu1_P>"+d2s(myvaluesP.at(l))+" && mu1_ghost<"+d2s(myvaluesGHOSTPROB.at(l))+" && mu1_TRACK_CHI2<"+d2s(myvaluesTRACKCHI2.at(l))+" && mu1_MINIPCHI2>"+d2s(myvaluesMINIPCHI2.at(l))+")||(mu2_PT>"+d2s(myvaluesPT.at(l))+" && mu2_P>"+d2s(myvaluesP.at(l))+" && mu2_ghost<"+d2s(myvaluesGHOSTPROB.at(l))+" && mu2_TRACK_CHI2<"+d2s(myvaluesTRACKCHI2.at(l))+" && mu2_MINIPCHI2>"+d2s(myvaluesMINIPCHI2.at(l))+"))";
			HLT1eff=cutTree((filenameclean_L0+ext).c_str(),"DecayTree",(filenameclean_L0+"_Hlt1TrackMuonDecision"+ext).c_str(),(hlt1string).c_str());

        		FillEffInfo(fillinfotree, "HLT1",HLT1eff,true);
			string filenameclean=(filenameclean_L0+"_Hlt1TrackMuonDecision").c_str();
			string file=(filenameclean_L0+"_Hlt1TrackMuonDecision").c_str();
			out << "$\\epsilon_{HLT1}$ "<< l <<" &" << HLT1eff <<"&"<< getmyentries((filenameclean+ext).c_str(),"DecayTree") << "  & " << " \\\\ "<<endl;

			toteff=toteff*HLT1eff;

			for(int i(15);i<16;i++)
			{
				double error;
				int numofentriesbefore;
				int numofentriesafter;
				double eff;
				eff=cutTree((file+ext).c_str(), "DecayTree", (file+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
				numofentriesbefore= getmyentries((file+ext).c_str(),"DecayTree");
				numofentriesafter= getmyentries((file+"_"+varia.at(i)+ext).c_str(),"DecayTree");
				error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
				out<<vals.at(i)+" & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
				file=(file+"_"+varia.at(i)).c_str();
				toteff=toteff*eff;
				
        			FillEffInfo(fillinfotree, varia.at(i), eff,true);
			}
			out<<"\\hline"<<endl;

			out<<"TOT left in tuple &" << getmyentries((file+ext).c_str(), "DecayTree")<<" \\\\ "<<endl;
			out<<"\\hline"<<endl;
			out<<"$\\epsilon_{totaleff}$ & "<<toteff<<" \\\\ "<<endl;
			out<<"\\hline"<<endl;

			addKFoldandW(file, "DecayTree", file);
                        addtcklumi(file, "DecayTree", file, l);


			vals.push_back("Bplus_Hlt2TopoMu2BodyDecision_TOS==1.0");
			vals.push_back("Bplus_Hlt2TopoMu3BodyDecision_TOS==1.0");
			vals.push_back("Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0");
			vals.push_back("Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0");

			varia.push_back("Hlt2TopoMu2BodyDecision");
			varia.push_back("Hlt2TopoMu3BodyDecision");
			varia.push_back("Hlt2DiMuonDetachedDecision");
			varia.push_back("Hlt2DiMuonDetachedHeavyDecision");


			string filename4=(filenameclean_L0).c_str();        

			for(int i(16);i<20;i++)
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

        			FillEffInfo(fillinfotree, varia.at(i), eff,true);
			}


			FillEffInfo(fillinfotree, "toteff", toteff,true);

			fillinfo->cd();
			fillinfotree->Write("",TObject::kOverwrite);

			delete fillinfotree;
			delete fillinfo;
			out<<"\\end{tabular}"<<endl;
			out<<"\\end{center}"<<endl;
			out<<"\\caption{SPECIALEFFICIENCIES.txt}"<<endl;
			out<<"\\end{table}"<<endl;
			out<<"\\end{document}"<<endl;
		}

	}








}



