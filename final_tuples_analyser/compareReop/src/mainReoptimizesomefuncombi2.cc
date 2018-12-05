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
#include "myFirstClass.hpp"

using namespace std;

int main(int argc, char *argv[]){
	//TCanvas* C = new TCanvas("myname","myname",600,600);
	//double mylumi;

	vector<string> tuples1;
	vector<string> tuples2;
	vector<string> tuples3;
	vector<string> tuples4;


        tuples1.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2016/bin/Bu23MuNuMC2016_MCtruth_trigger_Jpsi");
        tuples1.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/2016/LowerMassSideBandFullDatapreparetuple/bin/Bu23MuNuData2016_corrmLSDfull_trigger_Jpsi");
        tuples1.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/2016/FullUpperMassSideBand/bin/Bu23MuNuData2016_corrmFUSMB_trigger_Jpsi");

        tuples4.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_misidstrippingfull_trigger");
        tuples4.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/B2jpsik_data/2016/bin/Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger");

        tuples3.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/misid_data_os/2016/bin/Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger");

        tuples2.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/misid_data_ss/2016/bin/Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi");


	vector<string> tags1;
        vector<string> tags2;
        vector<string> tags3;
        vector<string> tags4;

	tags1.push_back("mcsig2016");
	tags4.push_back("mcnorm2016");
	tags4.push_back("datanorm2016");
        tags3.push_back("dataOS2016");

	tags2.push_back("dataSS2016");
	tags1.push_back("dataLMSB2016");
	tags1.push_back("dataCOMBI2016");
	


        vector<string> cuts1;

        cuts1.push_back("mu1_isMuonTight == 1.0 && mu2_isMuonTight == 1.0 && mu3_isMuonTight == 1.0");
        cuts1.push_back("mu1_MuonNShared < 2 && mu2_MuonNShared < 2 && mu3_MuonNShared==0 ");
        cuts1.push_back("minq2 < 960400");

       
        vector<string> cuts2;
 
        cuts2.push_back("mu1_isMuonTight == 1.0 && mu2_isMuonTight == 1.0");
        cuts2.push_back("mu1_MuonNShared < 2 && mu2_MuonNShared < 2");
        cuts2.push_back("minq2 < 960400");



        vector<string> cuts3;

        cuts3.push_back("mu1_isMuonTight == 1.0 && mu3_isMuonTight == 1.0");
        cuts3.push_back("mu1_MuonNShared < 2 && mu3_MuonNShared==0");
        cuts3.push_back("minq2 < 960400");

        vector<string> cuts4;
        
        
        cuts4.push_back("mu1_isMuonTight == 1.0 && mu2_isMuonTight == 1.0");
        cuts4.push_back("mu1_MuonNShared < 2 && mu2_MuonNShared < 2");
        cuts4.push_back("");

        vector<string> tagcut;
        tagcut.push_back("opt_3_isMuonTight");
        tagcut.push_back("opt_3_nSharedCombi2");
        tagcut.push_back("opt_3_minq2");



        string decaytreename = "DecayTree";
        string ext = ".root";


	ofstream out2;
	out2.open("Efficiencies_2016_FunCombi2.tex");


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
	out2<<"\\begin{tabular}{| l | l | l | }"<<endl;
	out2<<"\\hline"<<endl;
	out2<<"Sample & Cut & Efficiency \\\\ "<<endl;

        vector<myFirstClass> maps;

	for(int j(0); j<tuples1.size(); j++){
        string filename1=(tuples1.at(j)+ext).c_str();
		for(int i(0); i<cuts1.size(); i++)
		{
			double efficiency(0);
			cout<<"OK"<<endl;
			efficiency=cutTree(filename1.c_str(), decaytreename, (tags1.at(j)+tagcut.at(i)+ext).c_str(), cuts1.at(i));
                        filename1=(tags1.at(j)+tagcut.at(i)+ext).c_str();
			out2<<(tags1.at(j)+ext).c_str()<<" & "<<tagcut.at(i)<<" & "<< efficiency <<" \\\\ " <<endl;
                        myFirstClass really;
                        really.filename=(tags1.at(j)+ext).c_str();
                        really.decaytreename=decaytreename;
                        really.cut=tagcut.at(i);
                        really.efficiency=efficiency; 
                        maps.push_back(really);
		}

	}        


	for(int j(0); j<tuples2.size(); j++){
        string filename2=(tuples2.at(j)+ext).c_str();
		for(int i(0); i<cuts2.size(); i++)
		{
			double efficiency(0);
			cout<<"OK"<<endl;
			efficiency=cutTree(filename2.c_str(), decaytreename, (tags2.at(j)+tagcut.at(i)+ext).c_str(), cuts2.at(i));
                        filename2=(tags2.at(j)+tagcut.at(i)+ext).c_str();

                        myFirstClass really;
                        really.filename=(tags2.at(j)+ext).c_str();
                        really.decaytreename=decaytreename;
                        really.cut=tagcut.at(i);
                        really.efficiency=efficiency; 
                        maps.push_back(really);

			out2<<(tags2.at(j)+ext).c_str()<<" & "<<tagcut.at(i)<<" & "<< efficiency <<" \\\\ " <<endl;
		}

	}        

	for(int j(0); j<tuples3.size(); j++){
        string filename3=(tuples3.at(j)+ext).c_str();
		for(int i(0); i<cuts3.size(); i++)
		{
			double efficiency(0);
			cout<<"OK"<<endl;
			efficiency=cutTree(filename3.c_str(), decaytreename, (tags3.at(j)+tagcut.at(i)+ext).c_str(), cuts3.at(i));
                        filename3=(tags3.at(j)+tagcut.at(i)+ext).c_str();
			out2<<(tags3.at(j)+ext).c_str()<<" & "<<tagcut.at(i)<<" & "<< efficiency <<" \\\\ " <<endl;

                        myFirstClass really;
                        really.filename=(tags3.at(j)+ext).c_str();
                        really.decaytreename=decaytreename;
                        really.cut=tagcut.at(i);
                        really.efficiency=efficiency; 
                        maps.push_back(really);
		}

	}        

	for(int j(0); j<tuples4.size(); j++){
        string filename4=(tuples4.at(j)+ext).c_str();
		for(int i(0); i<cuts4.size(); i++)
		{ 
                        
			double efficiency(0);
			cout<<"OK"<<endl;
			efficiency=cutTree(filename4.c_str(), decaytreename, (tags4.at(j)+tagcut.at(i)+ext).c_str(), cuts4.at(i));
                        filename4=(tags4.at(j)+tagcut.at(i)+ext).c_str();
			out2<<(tags4.at(j)+ext).c_str()<<" & "<<tagcut.at(i)<<" & "<< efficiency <<" \\\\ " <<endl;

                        myFirstClass really;
                        really.filename=(tags4.at(j)+ext).c_str();
                        really.decaytreename=decaytreename;
                        really.cut=tagcut.at(i);
                        really.efficiency=efficiency; 
                        maps.push_back(really);
		}

	}        

	out2<<"\\hline"<<endl;
	out2<<"\\end{tabular}"<<endl;
	out2<<"\\end{center}"<<endl;
	out2<<"\\caption{maybedoastruct.txt}"<<endl;
	out2<<"\\end{table}"<<endl;
	out2<<"\\end{document}"<<endl;

	ofstream out3;
	out3.open("EfficienciesPlay_2016_FunCombi2.tex");


	out3<<"\\documentclass[a4paper,11pt]{article}"<<endl;
	out3<<"\\usepackage[pdftex]{graphicx}"<<endl;
	out3<<"\\usepackage{url}"<<endl;
	out3<<"\\usepackage{mathtools}"<<endl;
	out3<<"\\usepackage{amsmath}"<<endl;
	out3<<"\\usepackage{graphicx}"<<endl;
	out3<<"\\usepackage[table]{xcolor}"<<endl;
	out3<<"\\usepackage{amsmath,amssymb}"<<endl;
	out3<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
	out3<<"\\usepackage{colortbl}"<<endl;

	out3<<"\\usepackage{pdflscape}"<<endl;
	out3<<"\\begin{document}"<<endl;
	out3<<"\\begin{landscape}"<<endl;
	out3<<"\\begin{table}[h]"<<endl;
	out3<<"\\begin{center}"<<endl;
//	out3<<"\\begin{tabular}{| l | l | l | }"<<endl;
        out3<<"\\begin{tabular}{";
        for(int z(0); z<maps.size(); z++){out3<<"| l ";}
        out3<<" | } "<<endl;
	out3<<"\\hline"<<endl;


        out3<<"Cut & ";
	for(int z(0); z<maps.size(); z++){
		if ((maps.at(z)).cut=="opt_3_isMuonTight"){
			out3<<"Sample & ";

		} 

	}
        out3<<"\\\\"<<endl;
        out3<<"- & ";

	for(int z(0); z<maps.size(); z++){
		if ((maps.at(z)).cut=="opt_3_isMuonTight"){
			out3<<(maps.at(z)).filename<<" & ";

		} 

	}
        out3<<"\\\\"<<endl;
        out3<<"isMuonTight & ";
        
	for(int z(0); z<maps.size(); z++){
		if ((maps.at(z)).cut=="opt_3_isMuonTight"){
			out3<<(maps.at(z)).efficiency<<" & ";

		} 

	}
        out3<<"\\\\"<<endl;

        out3<<"nSharedCombi & ";
        
	for(int z(0); z<maps.size(); z++){
		if ((maps.at(z)).cut=="opt_3_nSharedCombi2"){
			out3<<(maps.at(z)).efficiency<<" & ";

		} 

	}
        out3<<"\\\\"<<endl;
        out3<<"minq2 & ";

        
	for(int z(0); z<maps.size(); z++){
		if ((maps.at(z)).cut=="opt_3_minq2"){
			out3<<(maps.at(z)).efficiency<<" & ";

		} 

	}
        out3<<"\\\\"<<endl;

        out3<<"\\hline"<<endl;
        out3<<" - & ";         
       
	for(int s(0); s<maps.size(); s++){
		double overalleff(1.0);
		for(int z(0); z<maps.size(); z++){
			if ((maps.at(z)).filename==(maps.at(s)).filename){
				overalleff=overalleff*((maps.at(z)).efficiency);
			}
                if (z==(maps.size()-1) && ((s+1)%(int(cuts1.size()))==1)){
                        out3<<overalleff<<" & ";}
		}
	}

        out3<<"\\\\"<<endl;



	out3<<"\\hline"<<endl;
	out3<<"\\end{tabular}"<<endl;
	out3<<"\\end{center}"<<endl;
	out3<<"\\caption{";
		for(int i(0); i<cuts1.size();i++){
			out3<<" "<<cuts1.at(i);}
        out3<<"}"<<endl;
	out3<<"\\end{table}"<<endl;
        out3<<"\\end{landscape}"<<endl;
	out3<<"\\end{document}"<<endl;


        
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
