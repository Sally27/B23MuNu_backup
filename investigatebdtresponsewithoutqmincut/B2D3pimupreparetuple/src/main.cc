
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


	double toteff;


        string pathname = "/vols/lhcb/ss4314/tuplesallvar/B2D3pimu/";
        string filename = "B23Pimu";
        string decaytreename = "B2D3pimu_Tuple/DecayTree";
        string ext = ".root";
        string cuttag = "_MCtruth";

	string filename2 = (filename+cuttag).c_str();



	double mctrutheff;
	mctrutheff=mctruth((pathname+filename).c_str(), decaytreename, (filename2).c_str());
	out << "$\\epsilon_{MC}$ &" << mctrutheff << " \\\\ "<<endl;


	convertbranchname(filename2, "DecayTree", filename2);
	addqsqinf(filename2, "DecayTree", filename2);        
	addcostheta(filename2, "DecayTree", filename2);  


	vector<string> varia;
	varia.push_back("trigger");
	varia.push_back("mu3nShared");
	varia.push_back("qmincut");


	vector<string> vals;
	vals.push_back("");
	vals.push_back("mu3_nShared == 0.0");
	vals.push_back("minq2 < 960400");



	for(int i(0);i<1;i++)
	{
		double eff;
		eff=cutTree((filename2+ext).c_str(), "DecayTree", (filename2+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
		out<<"$\\epsilon_{"+varia.at(i)+"}$ & "<<eff<<" \\\\ "<<endl;
		filename2=(filename2+"_"+varia.at(i)).c_str();
		toteff=eff;
	} 

	double jpsieff;
	jpsieff=Jpsi((filename2).c_str(), "DecayTree", (filename2+"_Jpsi").c_str());
	out << "$\\epsilon_{Jpsi}$ &" << jpsieff << " \\\\ "<<endl;
	toteff=toteff*jpsieff;
        filename2=(filename2+"_Jpsi").c_str();

	for(int i(1);i<3;i++)
	{
		double eff;
		eff=cutTree((filename2+ext).c_str(), "DecayTree", (filename2+"_"+varia.at(i)+ext).c_str(), (vals.at(i)).c_str());
		out<<"$\\epsilon_{"+varia.at(i)+"}$ & "<<eff<<" \\\\ "<<endl;
		filename2=(filename2+"_"+varia.at(i)).c_str();
		toteff=toteff*eff;
	}

	out<<"$\\epsilon_{totaleff}$ & "<<toteff<<" \\\\ "<<endl;

	addKFoldandW(filename2, "DecayTree", filename2);
        




//        ofstream out;
//        out.open("Efficiencies.tex");
//
//	out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
//	out<<"\\usepackage[pdftex]{graphicx}"<<endl;
//	out<<"\\usepackage{url}"<<endl;
//	out<<"\\usepackage{mathtools}"<<endl;
//	out<<"\\usepackage{amsmath}"<<endl;
//	out<<"\\usepackage{graphicx}"<<endl;
//	out<<"\\usepackage[table]{xcolor}"<<endl;
//	out<<"\\usepackage{amsmath,amssymb}"<<endl;
//	out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
//	out<<"\\usepackage{colortbl}"<<endl;
//	out<<"\\begin{document}"<<endl;
//        
//        out<<"\\begin{table}[ht]"<<endl;
//        out<<"\\begin{center}"<<endl;
//        out<<"\\begin{tabular}{| l | l |}"<<endl;
//        out<<"\\hline"<<endl;
//        out<<"Cut & $\\epsilon$   \\\\ "<<endl;
//        out<<"\\hline"<<endl;
//
//
//
//
//	string pathname = "/vols/lhcb/ss4314/tuplesallvar/B2D3pimu/";
//	string filename = "B23Pimu";
//	string decaytreename = "B2D3pimu_Tuple/DecayTree";
//	string ext = ".root";
//	string cuttag = "_MCtruth";
//	string namecuttree2 = (filename+cuttag).c_str();
//
//	double mctrutheff;
//	mctrutheff=mctruth((pathname+filename).c_str(), decaytreename, (namecuttree2).c_str());  
//        out << "$\\epsilon_{MC}$ &" << mctrutheff << " \\\\ "<<endl;
//
//
//         string filenamespec = namecuttree2;
//         string decaytreenamespec = "DecayTree";
//         string extspec = ".root";
//         string cuttagspec = "_trigger";
//         string namecuttreespec = (filenamespec+"_cut"+cuttagspec).c_str();
//         string cutspec = "";
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
//	string cuttag3 = "_mu3nShared";
//	string namecuttree23 = (filename3+"_cut"+cuttag3).c_str();
//	string cut23 = "mu3_nShared == 0.0";
//
//	double nSharedeff;
//	nSharedeff=cutTree((filename3+ext3).c_str(), decaytreename3, (namecuttree23+ext3).c_str(), cut23);
//out << "$\\epsilon_{nShared}$ &" << nSharedeff << " \\\\ "<<endl;
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
//
//        out<<" \\\\ "<<endl;
//        out<<"\\hline"<<endl;
//        out<<"\\end{tabular}"<<endl;
//        out<<"\\end{center}"<<endl;
//        out<<"\\caption{EFFICIENCIESMCSIG.txt}"<<endl;
//        out<<"\\end{table}"<<endl;       
//        out<<"\\end{document}"<<endl;
//
//        out.close();


	double bBplus= 2*0.4;
	double decprodcut =0.16025;
	double effrecostrip= 0.075031;
	double brfr=1e-7;
	double ppbbX=284e-6;
	//double bBplus= 2*0.4;
	double datacoll=3e15;


	double finalnum;
	finalnum=ppbbX*bBplus*brfr*datacoll*decprodcut*effrecostrip*toteff; 

        out<<"Tot asuming 10$^{-7}$ & "<<finalnum<<" \\\\ "<<endl;
        out<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{EFFICIENCIESMCB2D3pi.txt}"<<endl;
        out<<"\\end{table}"<<endl;       
        out<<"\\end{document}"<<endl;

        out.close();










	return(0);



}



