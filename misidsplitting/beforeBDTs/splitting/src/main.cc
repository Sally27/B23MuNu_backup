#include<iostream>
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
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include"splitmisidsamples.hpp"

using namespace std;
 


int main(int argc, char *argv[]){


	string pathname = "/vols/lhcb/ss4314/misidsplitting/beforeBDTs/";

	string filename1="B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID";
	string filename2="B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID";
//   TTree* t2 = t->CloneTree(0);
        string filename3="B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut";
	string filename4="B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID";
//	string filename4="B23MuNuMCallvar_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu2nShared_qmincut_CombBasic";
//	string filename5="Data2012and2011_corrm_trigger_Jpsi_mu1nShared_mu2nShared_mu2nShared_qmincut_CombBasic";
//	string filename6="B23Pimu_MCtruth_trigger_mu2nShared_qmincut_CombBasic";


	string decaytreename = "DecayTree";
	string ext = ".root";
	string cuttag = argv[1];



	string namecuttree1 = (filename1+cuttag).c_str();
	string namecuttree2 = (filename2+cuttag).c_str();
	string namecuttree3 = (filename3+cuttag).c_str();
	string namecuttree4 = (filename4+cuttag).c_str();
//	string namecuttree5 = (filename5+cuttag).c_str();
//	string namecuttree6 = (filename6+cuttag).c_str();



	string cut2 = argv[2];
//	string cut2 = "Polarity==-1";

	double pionmisid;
	double kaonmisid;
        double protonmisid;
	double misid;
	double mcsig;
	double combi;
	double partreco;


	kaonmisid=cutTree((pathname+filename1+ext).c_str(), decaytreename, (namecuttree1+ext).c_str(), cut2);
	pionmisid=cutTree((pathname+filename2+ext).c_str(), decaytreename, (namecuttree2+ext).c_str(), cut2);
	misid=cutTree((pathname+filename3+ext).c_str(), decaytreename, (namecuttree3+ext).c_str(), cut2);
        protonmisid=cutTree((pathname+filename4+ext).c_str(), decaytreename, (namecuttree4+ext).c_str(), cut2);
//	mcsig=cutTree((pathname+filename4+ext).c_str(), decaytreename, (namecuttree4+ext).c_str(), cut2);
//	combi=cutTree((pathname+filename5+ext).c_str(), decaytreename, (namecuttree5+ext).c_str(), cut2);
//	partreco=cutTree((pathname+filename6+ext).c_str(), decaytreename, (namecuttree6+ext).c_str(), cut2);

//	double numofmcsig = 22;
//	double numofpartreco = 756.4;
	double numofmisid = 5428;
//	double numofcombinatorial = 800;




	ofstream out;
	out.open(("splitpolarityandstripping"+cuttag+".tex").c_str());


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
	out<<"\\begin{table}[h]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
	out<<"\\hline"<<endl;
	out<<"Sample & cut &  Eff of cut &  Num of evts( all range rough)\\\\ "<<endl;
	out<<"kaonmisid  & "<<cuttag<<" & "<< kaonmisid << " & " << " \\\\ "<<endl;
	out<<"pionmisid  & "<<cuttag<<" & "<< pionmisid << " & " << " \\\\ "<<endl;
        out<<"protonmisid  & "<<cuttag<<" & "<< protonmisid << " & "<< " \\\\ " <<endl;
	out<<"misid  & "<<cuttag<<" & "<< misid << " & "<< numofmisid*misid <<" \\\\ " <<endl;
//	out<<"mcsig  & "<<cut2<<" & "<< mcsig << " & "<< numofmcsig*mcsig <<"  \\\\ "<<endl;
//	out<<"combi  & "<<cut2<<" & "<< combi << " & "<< numofcombinatorial*combi <<" \\\\ "<<endl;
//	out<<"partreco  & "<<cut2<<" & "<< partreco << " & " << numofpartreco*partreco  << " \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{Cutofbdt400comb.txt}"<<endl;
	out<<"\\end{table}"<<endl;
	out<<"\\end{document}"<<endl;




	return(0);



}



