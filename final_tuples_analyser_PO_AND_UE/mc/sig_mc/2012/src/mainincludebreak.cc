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
#include "analib.hpp"
#include "EfficiencyClass.hpp"
#include "ValError.hpp"
#include<iostream>

using namespace std;


int main(){

	ofstream out;
	out.open("Efficiencies_2012.tex");

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
	out<<"\\begin{tabular}{| l | l | l |}"<<endl;
	out<<"\\hline"<<endl;
	out<<"Cut & $\\epsilon$  \\\\ "<<endl;
	out<<"\\hline"<<endl;


	double toteff(1.0);


	//creating efficiency storage//


	TFile *fillinfo = new TFile("Efficiencies_2012.root","RECREATE");
	TTree *fillinfotree = new TTree("MC_Sig_2012","MC_Sig_2012");

	//defining paths//

	EfficiencyClass neweff;

	string filename;
	string pathname;
	string decaytreename;

	filename=neweff.return_string("file");
	pathname=neweff.return_string("path");
	decaytreename=neweff.return_string("decaytree");



	//number of bkk
	FillEffInfo(fillinfotree, "numbkk",double(neweff.return_numbkk("")),false);
        out << "$N_{bkk}$ &" << double(neweff.return_numbkk("")) <<" \\\\ "<<endl;
        //number of generated
	FillEffInfo(fillinfotree, "numgen",double(neweff.return_numgen("")),true);
        out << "$N_{gen}$ &" << double(neweff.return_numgen("")) <<" \\\\ "<<endl;

        //numbers at generator level
        out<<"\\hline"<<endl;
	out << "N$^{generated}$ &" <<neweff.return_numgen("") <<"  \\\\ "<<endl;
	out << "N$^{generated,minq^{2}}$ &" << getmyentries(neweff.return_string("genqmin").c_str(),"MCDecayTree")<<" \\\\"<<endl;
	out << "N$^{in\\_acc,minq^{2}}$ &" << getmyentries(neweff.return_string("genqmininacc").c_str(),"MCDecayTree") <<" \\\\"<<endl;
	out << "N$^{in\\_acc}$ &" << neweff.return_numbkk("") << " \\\\ "<<endl;


	//mctrutheff//
	string ext = ".root";
	string cuttag = "_MCtruth";
	string filename2 = (filename+cuttag).c_str();
	double mctrutheff;
	mctrutheff=mctruth((pathname+filename).c_str(), decaytreename, (filename2).c_str());
	out << "$\\epsilon_{MC}$ &" << mctrutheff <<" \\\\ "<<endl;

        //correct all the names
	convertbranchname(filename2, "DecayTree", filename2);
	addqsqinf(filename2, "DecayTree", filename2);
	addcostheta(filename2, "DecayTree", filename2);

        //qmincut//
        double qmincut;
        qmincut=cutTree((filename2+ext).c_str(), "DecayTree", (filename2+ext).c_str(), "minq2 < 960400");
	out << "$\\epsilon_{qmin}$ &" << mctrutheff <<" \\\\ "<<endl;


        //calculate the epsilon_gen \times epsilon reco
	double nbkk_1(neweff.return_numbkk(""));
	double numgen_1(neweff.return_numgen(""));

	ValError ninaccqmin((double(getmyentries(neweff.return_string("genqmininacc").c_str(),"MCDecayTree"))),sqrt((double(getmyentries(neweff.return_string("genqmininacc").c_str(),"MCDecayTree")))));
	ValError nglqmin((double(getmyentries(neweff.return_string("genqmin").c_str(),"MCDecayTree"))),sqrt((double(getmyentries(neweff.return_string("genqmin").c_str(),"MCDecayTree")))));
	ValError nrecqmin(double(getmyentries((filename2+ext).c_str(),"DecayTree")),sqrt(double(getmyentries((filename2+ext).c_str(),"DecayTree"))));
	ValError ninacc(nbkk_1,sqrt(nbkk_1));
	ValError numgen(numgen_1,sqrt(numgen_1));
	ValError try1_err = (getRatioBinomial(ninaccqmin,nglqmin))*(getRatioBinomial(nrecqmin,(ninacc*getRatioBinomial(nglqmin,numgen))));
	out << "N$^{REC, minq^{2}}$ & "<<double(getmyentries((filename2+ext).c_str(),"DecayTree"))<<"\\\\"<<endl;
        out << "${\\epsilon^{GEN,minq^{2}}}$  & "<<(getRatioBinomial(ninaccqmin,nglqmin)/2).val<<"\\\\"<<endl;
        out << "${\\epsilon^{RECO,minq^{2}}}$  & "<<(getRatioBinomial(nrecqmin,(ninacc*getRatioBinomial(nglqmin,numgen)))).val<<"\\\\"<<endl;
	out << "${\\epsilon^{GEN,minq^{2}}}\\times {\\epsilon^{REC,minq^{2}}}$  &" << try1_err << " \\\\ "<<endl;

        FillEffInfo(fillinfotree, "effgentimeseffreco",double(try1_err.val),true);
        FillEffInfo(fillinfotree, "effgen",double((getRatioBinomial(ninaccqmin,nglqmin)/2.0).val),true);
        FillEffInfo(fillinfotree, "effgen_err",double((getRatioBinomial(ninaccqmin,nglqmin)/2.0).err),true);
        FillEffInfo(fillinfotree, "effreco",double((getRatioBinomial(nrecqmin,(ninacc*getRatioBinomial(nglqmin,numgen)))).val),true);
        FillEffInfo(fillinfotree, "effreco_err",double((getRatioBinomial(nrecqmin,(ninacc*getRatioBinomial(nglqmin,numgen)))).err),true);

        toteff=try1_err.val;

	double L0eff(0);
	L0eff=cutTree((filename2+ext).c_str(),"DecayTree",(filename2+"_L0MuonDecisionTOS"+ext).c_str(),"Bplus_L0MuonDecision_TOS==1.0");
	toteff = toteff*L0eff;
	FillEffInfo(fillinfotree, "L0",L0eff,true);


	string filenameclean=(filename2+"_L0MuonDecisionTOS").c_str();
	string file=(filename2+"_L0MuonDecisionTOS").c_str();
	out << "$\\epsilon_{L0}$ &" << L0eff << " \\\\ "<<endl;


	vector<string> varia;
	varia.push_back("trigger");


	vector<string> vals;
	vals.push_back("(Bplus_Hlt1TrackMuonDecision_TOS==1.0) && ((Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0))");



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
		out<<"$\\epsilon_{"+varia.at(i)+"}$  & "<<eff<<" \\\\ "<<endl;
		filenameclean=(filenameclean+"_"+varia.at(i)).c_str();
		toteff=toteff*eff;

		FillEffInfo(fillinfotree, varia.at(i), eff,true);
	} 

	double jpsieff;
	jpsieff=Jpsi((filenameclean).c_str(), "DecayTree", (filenameclean+"_Jpsi").c_str());
	double error;
	int numofentriesbefore;
	int numofentriesafter;
	numofentriesbefore= getmyentries((filenameclean+ext).c_str(),"DecayTree");
	numofentriesafter= getmyentries((filenameclean+"_Jpsi"+ext).c_str(),"DecayTree");
	error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
	out << "$\\epsilon_{Jpsi}$ &" << jpsieff<< " \\\\ "<<endl;
	toteff=toteff*jpsieff;


	FillEffInfo(fillinfotree, "jpsi", jpsieff,true);
	filenameclean=(filenameclean+"_Jpsi").c_str();

//	for(int i(1);i<2;i++)
//	{
//		double eff;
//		double error;
//		int numofentriesbefore;
//		int numofentriesafter;
//		eff=cutTree((filenameclean+ext).c_str(), "DecayTree", (filenameclean+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
//		numofentriesbefore= getmyentries((filenameclean+ext).c_str(),"DecayTree");
//		numofentriesafter= getmyentries((filenameclean+"_"+varia.at(i)+ext).c_str(),"DecayTree");
//		error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
//		out<<"$\\epsilon_{"+varia.at(i)+"}$ & "<<eff<<" & "<<numofentriesafter<<" & "<<error<<" \\\\ "<<endl;
//		filenameclean=(filenameclean+"_"+varia.at(i)).c_str();
//		toteff=toteff*eff;
//
//		FillEffInfo(fillinfotree, varia.at(i), eff,true);
//	}

	addKFoldandW(filenameclean, "DecayTree", filenameclean);


	vals.push_back("Bplus_Hlt1TrackMuonDecision_TOS==1.0");
	vals.push_back("(Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0)");

	varia.push_back("Hlt1TrackMuonDecisionTOS");
	varia.push_back("Hlt2orofDecisions");

	string filename3=(file).c_str();

	for(int i(1);i<3;i++)
	{
		double error;
		int numofentriesbefore;
		int numofentriesafter;
		double eff;
		eff=cutTree((filename3+ext).c_str(), "DecayTree", (filename3+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
		numofentriesbefore= getmyentries((filename3+ext).c_str(),"DecayTree");
		numofentriesafter= getmyentries((filename3+"_"+varia.at(i)+ext).c_str(),"DecayTree");
		error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
		out<<vals.at(i)+" & "<<eff<<" \\\\ "<<endl;
		filename3=(filename3+"_"+varia.at(i)).c_str();
		FillEffInfo(fillinfotree, varia.at(i), eff,true);
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
		out<<vals.at(i)+" & "<<eff<<" \\\\ "<<endl;


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
	out<<"Total Efficiency & "<<toteff<<" \\\\ "<<endl;
	fillinfo->cd();
	fillinfotree->Write("",TObject::kOverwrite);
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



