#include <iostream>
#include <cmath>
#include <string>
#include "TTree.h"
#include "math.h"
#include <sstream>
#include "TLatex.h"
#include "TCanvas.h"
#include <string>
#include<iostream>
#include<fstream>
#include<vector>
#include "functions.hpp"
#include<map>
#include "TFile.h"
#include "TBranch.h"

using namespace std;

int main(int argc, char *argv[]){
	//TCanvas* C = new TCanvas("myname","myname",600,600);
	//double mylumi;

	vector<string> tuples;

        tuples.push_back("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_forMCcutvsPIDreweight/bin/B23MuNuMC2012nSharedStrip21");
        tuples.push_back("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_forMCcutvsPIDreweight/bin/B23MuNuMC2012nSharedDllmuStrip21");
        tuples.push_back("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_forMCcutvsPIDreweight/bin/B23MuNuMC2012nSharedDllmuDllKStrip21");
        tuples.push_back("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_forMCcutvsPIDreweight/bin/B23MuNuMC2012nSharedDllmuDllKProbnnStrip21");


        tuples.push_back("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_forMCcutvsPIDreweight/bin/B23MuNuMC2015nSharedStrip23_MCTuneV1");
        tuples.push_back("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_forMCcutvsPIDreweight/bin/B23MuNuMC2015nSharedDllmuStrip23_MCTuneV1");
        tuples.push_back("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_forMCcutvsPIDreweight/bin/B23MuNuMC2015nSharedDllmuDllKStrip23_MCTuneV1");
        tuples.push_back("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_forMCcutvsPIDreweight/bin/B23MuNuMC2015nSharedDllmuDllKProbnnStrip23_MCTuneV1");



        tuples.push_back("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_forMCcutvsPIDreweight/bin/B23MuNuMC2016nSharedStrip26");
        tuples.push_back("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_forMCcutvsPIDreweight/bin/B23MuNuMC2016nSharedDllmuStrip26");
        tuples.push_back("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_forMCcutvsPIDreweight/bin/B23MuNuMC2016nSharedDllmuDllKStrip26");
        tuples.push_back("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_forMCcutvsPIDreweight/bin/B23MuNuMC2016nSharedDllmuDllKProbnnStrip26");

	vector<string> tags;

	tags.push_back("mcsigrun1nShared");
	tags.push_back("mcsigrun1nSharedDllmu");
	tags.push_back("mcsigrun1nSharedDllmuDllK");
        tags.push_back("mcsigrun1nSharedDllmuDllKProbnn");

	tags.push_back("mcsig2015nShared");
	tags.push_back("mcsig2015nSharedDllmu");
	tags.push_back("mcsig2015nSharedDllmuDllK");
        tags.push_back("mcsig2015nSharedDllmuDllKProbnn");
	

	tags.push_back("mcsig2016nShared");
	tags.push_back("mcsig2016nSharedDllmu");
	tags.push_back("mcsig2016nSharedDllmuDllK");
        tags.push_back("mcsig2016nSharedDllmuDllKProbnn");



        vector<string> cuts;

	cuts.push_back("(mu1_isMuon==1.0) && (mu2_isMuon==1.0) && (mu3_isMuon==1.0) && mu1_nShared==0 && mu2_nShared==0 && mu3_nShared==0");
        cuts.push_back("(mu1_isMuon==1.0) && (mu2_isMuon==1.0) && (mu3_isMuon==1.0) && mu1_nShared==0 && mu2_nShared==0 && mu3_nShared==0 && (mu1_PIDmu > 0.0) && (mu2_PIDmu > 0.0) && (mu3_PIDmu > 0.0)");
        cuts.push_back("(mu1_isMuon==1.0) && (mu2_isMuon==1.0) && (mu3_isMuon==1.0) && mu1_nShared==0 && mu2_nShared==0 && mu3_nShared==0 && (mu1_PIDmu > 0.0) && (mu2_PIDmu > 0.0) && (mu3_PIDmu > 0.0) && ((mu1_PIDmu - mu1_PIDK) > 0.0) && ((mu2_PIDmu - mu2_PIDK)> 0.0) && ((mu3_PIDmu-mu3_PIDK) > 0.0) ");
	cuts.push_back("(mu1_isMuon==1.0) && (mu2_isMuon==1.0) && (mu3_isMuon==1.0) && (mu1_PIDmu > 0.0) && (mu2_PIDmu > 0.0) && (mu3_PIDmu > 0.0) && ((mu1_PIDmu - mu1_PIDK) > 0.0) && ((mu2_PIDmu - mu2_PIDK)> 0.0) && ((mu3_PIDmu-mu3_PIDK) > 0.0) && mu1_nShared==0 && mu2_nShared==0 && mu3_nShared==0 && (mu2_ProbNNmu > 0.3) && (mu1_ProbNNmu > 0.3) && (mu3_ProbNNmu > 0.3)");


        vector<string> tagcut;
        tagcut.push_back("nShared");
        tagcut.push_back("nSharedDllmu");
        tagcut.push_back("nSharedDllmuDllK");
        tagcut.push_back("nSharedDllmuDllKProbnn");


        string decaytreename = "DecayTree";
        string ext = ".root";


	vector<vector<double> > efficiencies((tuples.size()/3), vector<double>(cuts.size()));
	double efficiency(0);
        

	for(int j(0); j<tuples.size(); j++){
		for(int i(0); i<cuts.size(); i++)
		{
			efficiency=cutTree((tuples.at(j)+ext).c_str(), decaytreename, (tags.at(j)+tagcut.at(i)+ext).c_str(), cuts.at(i));
			efficiencies[j/3][i]=efficiency;
			cout<<"I am here"<<endl;
                        
		}
                cout<<"This is j ="<<j<<endl;
                j=j+3;
                cout<<"This is new j ="<<j<<endl;
                
	}

	vector<double> pidweight(0);
	for(int j(0); j<tuples.size(); j++){

		double pidweighthold(0);
		pidweighthold=calculatePIDfromWeights(tuples.at(j), "DecayTree", "PIDweight");
		pidweight.push_back(pidweighthold);
	}

	ofstream out2;
	out2.open("EfficienciesIDPIDfromMCandPIDreweightBasic.tex");


	out2<<"\\documentclass[a4paper,11pt]{article}"<<endl;
	out2<<"\\usepackage[pdftex]{graphicx}"<<endl;
	out2<<"\\usepackage{url}"<<endl;
	out2<<"\\usepackage{mathtools}"<<endl;
	out2<<"\\usepackage{amsmath}"<<endl;
	out2<<"\\usepackage{graphicx}"<<endl;
	out2<<"\\usepackage[table]{xcolor}"<<endl;
	out2<<"\\usepackage{amsmath,amssymb}"<<endl;
	out2<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
	out2<<"\\usepackage{colortbl}"<<endl;
	out2<<"\\begin{document}"<<endl;
	out2<<"\\begin{table}[h]"<<endl;
	out2<<"\\begin{center}"<<endl;
	out2<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
	out2<<"\\hline"<<endl;
	out2<<"Sample & Cut &  EfficiencyMCcut & EfficiencyPIDReweight \\\\ "<<endl;

	for(int j(0); j<tuples.size(); j++){
		for(int i(0); i<cuts.size(); i++)
		{
			cout<<"OK"<<endl;
                        cout<<" i: "<<i<<" j: "<<j<<" pidweight "<< pidweight[i+j]<<endl;
			out2<<(tags.at(j)+ext).c_str()<<" & "<<tagcut.at(i)<<" & "<<d2s(efficiencies[j/3][i])<<" & "<< pidweight[i+j]<<" \\\\ " <<endl;
		}
                j=j+3;
	}        


	out2<<"\\hline"<<endl;
	out2<<"\\end{tabular}"<<endl;
	out2<<"\\end{center}"<<endl;
	out2<<"\\caption{CompareMCcutvsPIDrewe.txt}"<<endl;
	out2<<"\\end{table}"<<endl;
	out2<<"\\end{document}"<<endl;


	ofstream out3;
	out3.open("Basicforpython.tex");


      TFile fillinfo("info_basic.root","RECREATE");
      TTree fillinfotree("Info","Info");

      string file_tofill, cut_tofill;
      double MCEff, PIDreEff, Diff;
      

      fillinfotree.Branch("File",&file_tofill);// "File/C");
      fillinfotree.Branch("Cut",&cut_tofill);// "Cut/C");
      fillinfotree.Branch("MCEff",&MCEff,"MCEff/D");
      fillinfotree.Branch("PIDreEff",&PIDreEff, "PIDreEff/D");
      fillinfotree.Branch("Diff",&Diff, "Diff/D");



        out3<<"[ "<<endl;
	for(int j(0); j<tuples.size(); j++){
		for(int i(0); i<cuts.size(); i++)
		{
			cout<<"OK"<<endl;
                        cout<<" i: "<<i<<" j: "<<j<<" pidweight "<< pidweight[i+j]<<endl;
			out3<<"[ "<<(tags.at(j)+ext).c_str()<<" , "<<tagcut.at(i)<<" , "<<d2s(efficiencies[j/3][i])<<" , "<< pidweight[i+j]<<" ], " <<endl;
                        file_tofill=(tags.at(j)+ext).c_str();
                        cut_tofill=(tagcut.at(i)).c_str();
                        MCEff=efficiencies[j/3][i];
                        PIDreEff=pidweight[i+j];
                        Diff=MCEff-PIDreEff;
                        fillinfotree.Fill();
		}
                j=j+3;
	}        

        out3<<" ] " <<endl;

      fillinfotree.Write();


 
	ofstream out;
	out.open("EfficienciesIDPIDfromMCafterAllSelectionNOFCMEBasic.tex");


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
	out<<"Sample & Cut &  Efficiency & NumLeft\\\\ "<<endl;

	for(int j(0); j<tuples.size(); j++){
		for(int i(0); i<cuts.size(); i++)
		{
                cout<<"OK"<<endl;
                out<<(tags.at(j)+ext).c_str()<<" & "<<tagcut.at(i)<<" & "<<d2s(efficiencies[j/3][i])<<" & "<< getmyentries((tags.at(j)+tagcut.at(i)+ext).c_str(),"DecayTree")<<" \\\\ " <<endl;
		}
                j=j+3;

	}        


	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{GetMCcuteff}"<<endl;
	out<<"\\end{table}"<<endl;
	out<<"\\end{document}"<<endl;



        
//        ofstream comp;
//        comp.open("EfficienciesHCMECompare.tex");
//
//
//        comp<<"\\documentclass[a4paper,11pt]{article}"<<endl;
//        comp<<"\\usepackage[pdftex]{graphicx}"<<endl;
//        comp<<"\\usepackage{url}"<<endl;
//        comp<<"\\usepackage{mathtools}"<<endl;
//        comp<<"\\usepackage{amsmath}"<<endl;
//        comp<<"\\usepackage{graphicx}"<<endl;
//        comp<<"\\usepackage[table]{xcolor}"<<endl;
//        comp<<"\\usepackage{amsmath,amssymb}"<<endl;
//        comp<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
//        comp<<"\\usepackage{colortbl}"<<endl;
//        comp<<"\\begin{document}"<<endl;
//        comp<<"\\begin{table}[h]"<<endl;
//        comp<<"\\begin{center}"<<endl;
//        comp<<"\\begin{tabular}{| l | l | l | l | l |}"<<endl;
//        comp<<"\\hline"<<endl;
//        comp<<"Sample & Cut & 2011 & 2012 & 2015\\\\ "<<endl;
//        comp<<"\\hline"<<endl;
//        comp<<"Signal MC  & "<< cutinfile <<" & N/A & " <<collection.find("SigMC2012")->second<<" & "<<collection.find("MC2015Sig")->second<<" \\\\ " <<endl;
//        comp<<"JpsiK MC Detached & "<< cutinfile <<" & "<<collection.find("JpsiKMCDetached2011")->second<<" & "<<collection.find("JpsiKMCDetached2012")->second<<" & "<<collection.find("JpsiKMCDetached2015")->second<<" \\\\ " <<endl;;
//        comp<<"JpsiK Data Detached & "<< cutinfile <<" & "<<collection.find("JpsiKDataDetached2011")->second<<" & "<<collection.find("JpsiKDataDetached2012")->second<<" & "<<collection.find("JpsiKDataDetached2015")->second<<" \\\\ " <<endl;;
//        comp<<"SS Misid Total & "<< cutinfile <<" & "<<collection.find("SSmisidTotal")->second<<" & "<<collection.find("SSmisidTotal")->second<<" & "<<collection.find("SSMisid2015Total")->second<<" \\\\ " <<endl;;
//        comp<<"SS Misid Kaon & "<< cutinfile <<" & "<<collection.find("SSmisidKaon")->second<<" & "<<collection.find("SSmisidKaon")->second<<" & "<<collection.find("SSMisid2015Kaon")->second<<" \\\\ " <<endl;;
//        comp<<"SS Misid Pion & "<< cutinfile <<" & "<<collection.find("SSmisidPion")->second<<" & "<<collection.find("SSmisidPion")->second<<" & "<<collection.find("SSMisid2015Pion")->second<<" \\\\ " <<endl;;
//        comp<<"SS Misid Proton & "<< cutinfile <<" & "<<collection.find("SSmisidProton")->second<<" & "<<collection.find("SSmisidProton")->second<<" & "<<collection.find("SSMisid2015Proton")->second<<" \\\\ " <<endl;; 
//        comp<<"OS Misid Total & "<< cutinfile <<" & "<<collection.find("OSmisidTotal")->second<<" & "<<collection.find("OSmisidTotal")->second<<" & "<<collection.find("OSMisid2015Total")->second<<" \\\\ " <<endl;;
//        comp<<"OS Misid Kaon & "<< cutinfile <<" & "<<collection.find("OSmisidKaon")->second<<" & "<<collection.find("OSmisidKaon")->second<<" & "<<collection.find("OSMisid2015Kaon")->second<<" \\\\ " <<endl;;
//        comp<<"OS Misid Pion & "<< cutinfile <<" & "<<collection.find("OSmisidPion")->second<<" & "<<collection.find("OSmisidPion")->second<<" & "<<collection.find("OSMisid2015Pion")->second<<" \\\\ " <<endl;;
//        comp<<"OS Misid Proton & "<< cutinfile <<" & "<<collection.find("OSmisidProton")->second<<" & "<<collection.find("OSmisidProton")->second<<" & "<<collection.find("OSMisid2015Proton")->second<<" \\\\ " <<endl;;
//        comp<<"Data UMSB & "<< cutinfile <<" & "<<collection.find("DataUMSB")->second<<" & "<<collection.find("DataUMSB")->second<<" & "<<collection.find("Data2015UMSB")->second<<" \\\\ " <<endl;;
//        comp<<"Data LMSB & "<< cutinfile <<" & "<<collection.find("DataLMSB")->second<<" & "<<collection.find("DataLMSB")->second<<" & "<<collection.find("Data2015LMSB")->second<<" \\\\ " <<endl;;
//        comp<<"\\hline"<<endl;
////        for(int i(0); i<tuples.size(); i++)
////        {
////                comp<<tags.at(i)<<" & "<<cutinfile<<" & "<<d2s(efficiencies.at(i))<<" & "<< getmyentries(newtuples.at(i),"DecayTree") <<" \\\\ " <<endl;
////        }
//
//
//        comp<<"\\hline"<<endl;
//        comp<<"\\end{tabular}"<<endl;
//        comp<<"\\end{center}"<<endl;
//        comp<<"\\caption{LCME.txt}"<<endl;
//        comp<<"\\end{table}"<<endl;
//        comp<<"\\end{document}"<<endl;




	return(0);
}
