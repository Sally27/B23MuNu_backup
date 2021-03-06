#include "lumi.hpp"
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

using namespace std;

int main(){
TCanvas* C = new TCanvas("myname","myname",600,600);
double mylumi;
//TFile *file = new TFile("/vols/lhcb/ss4314/tuplesallvar/JpsiKdataDetachedLine/2011/B2JpsiKDetachedData_2011.root");
//mylumi=lumi(file).getLumi1();
//cout<<"My luminosity is : "<<mylumi<<endl;

vector<string> tuples;

tuples.push_back("/vols/lhcb/ss4314/final_tuples/data/B2jpsik_data/Run1/Data_B2JpsiK_2011.root");
tuples.push_back("/vols/lhcb/ss4314/final_tuples/data/B2jpsik_data/Run1/Data_B2JpsiK_2012.root");
tuples.push_back("/vols/lhcb/ss4314/final_tuples/data/misid_data_ss/Run1/Data_B23MuNu_MisidSS_Run1.root");
tuples.push_back("/vols/lhcb/ss4314/final_tuples/data/misid_data_os/Run1/Data_B23MuNu_MisidOS_Run1.root");
tuples.push_back("/vols/lhcb/ss4314/tuplesallvar/ThreeSameSignMuonsData/B23SameSignMuonTotal.root");
tuples.push_back("/vols/lhcb/ss4314/final_tuples/data/sig_data/Run1/Data_B23MuNu_Run1.root");
tuples.push_back("/vols/lhcb/ss4314/final_tuples/data/sig_data/Run1/Data_B23MuNu_2011.root");
tuples.push_back("/vols/lhcb/ss4314/final_tuples/data/sig_data/Run1/Data_B23MuNu_2012.root");
tuples.push_back("/vols/lhcb/ss4314/tuplesallvar/JpsiKdata/BuKMuMuMerged.root");
tuples.push_back("/vols/lhcb/ss4314/final_tuples/data/B2jpsikst_data/2011/B2JpsiKst_Data_2011.root");
tuples.push_back("/vols/lhcb/ss4314/tuplesallvar/JpsiKst_fromB2XMuMu_Data/2012/BuKstMuMu2012.root");
tuples.push_back("/vols/lhcb/ss4314/tuplesallvar/JpsiKdataDetachedLine/2015/B2JpsiKDataDetached2015.root");
tuples.push_back("/vols/lhcb/ss4314/tuplesallvar/Data2015/B23MuNuData2015_DV41r2.root");
tuples.push_back("/vols/lhcb/ss4314/tuplesallvar/OSMisidRestripping2015/B23MuNuFakeOS_2015_DV41r2.root");
tuples.push_back("/vols/lhcb/ss4314/tuplesallvar/SSMisidRestripping2015/B23MuNuFakeSS_2015_DV41r2.root");
tuples.push_back("/vols/lhcb/ss4314/tuplesallvar/JpsiKdataDetachedLine/2015/B2JpsiKDataDetached2015_v42r1.root");
tuples.push_back("/vols/lhcb/ss4314/tuplesallvar/Data2015/B23MuNuData_2015.root");
tuples.push_back("/vols/lhcb/ss4314/tuplesallvar/OSMisidRestripping2015/B23MuNuOSMisid2015.root");
tuples.push_back("/vols/lhcb/ss4314/tuplesallvar/SSMisidRestripping2015/B23MuNuSSMisid2015.root");
tuples.push_back("/vols/lhcb/ss4314/final_tuples/data/sig_data/2016/Bu23MuNuData2016.root");
tuples.push_back("/vols/lhcb/ss4314/final_tuples/data/misid_data_os/2016/Bu23MuNuData2016_OSmisid.root");
tuples.push_back("/vols/lhcb/ss4314/final_tuples/data/misid_data_ss/2016/Bu23MuNuData2016_SSmisid.root");
tuples.push_back("/vols/lhcb/ss4314/final_tuples/data/B2jpsik_data/2016/Bu23JpsiKData2016.root");
tuples.push_back("/vols/lhcb/ss4314/final_tuples/data/B2jpsikst_data/2016/B2JpsiKst_Data_2016.root");



vector<string> tuples2;
tuples2.push_back("B2JpsiKDetachedData_2011.root");
tuples2.push_back("B2JpsiKDetachedData_2012.root");
tuples2.push_back("B23MuNuFakeSStotal.root");
tuples2.push_back("B23MuNuFakeOStotal.root");
tuples2.push_back("B23SameSignMuon_2012.root");
tuples2.push_back("B23MuNuData_Run1.root");
tuples2.push_back("B23MuNuData_2011.root");
tuples2.push_back("B23MuNuData_2012.root");
tuples2.push_back("B2JpsiK_fromB2XMuMu_Run1.root");
tuples2.push_back("B2JpsiKst_2011.root");
tuples2.push_back("B2JpsiKst_2012.root");
tuples2.push_back("B2JpsiKDetachedData_2015.root");
tuples2.push_back("B23MuNu2015_DV41r2.root");
tuples2.push_back("B23MuNuFakeOS_2015_DV41r2.root");
tuples2.push_back("B23MuNuFakeSS_2015_DV41r2.root");
tuples2.push_back("B2JpsiKDataDetached2015_v42r1.root");
tuples2.push_back("B23MuNuData_2015.root");
tuples2.push_back("B23MuNuOSMisid_2015.root");
tuples2.push_back("B23MuNuSSMisid_2015.root");
tuples2.push_back("B23MuNuData_2016.root");
tuples2.push_back("B23MuNuFakeOS_2016.root");
tuples2.push_back("B23MuNuFakeSS_2016.root");
tuples2.push_back("B2JpsiKDetachedData_2016.root");
tuples2.push_back("B2JpsiKst_2016.root");

TFile *file = new TFile(tuples.at(0).c_str());
mylumi=lumi(file).getLumi1();
cout<<"My luminosity is : "<<mylumi<<endl;

ofstream out;
out.open(("luminew.tex"));
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
out<<"\\begin{tabular}{| l | l |}"<<endl;
out<<"\\hline"<<endl;
out<<"Sample & lumi \\\\ "<<endl;


for(int i(0); i<tuples.size(); i++)
{
double mylumi(0);
TFile *file = new TFile(tuples.at(i).c_str());
mylumi=lumi(file).getLumi1();
out<<tuples2.at(i)<<" & "<<d2s(mylumi)<<" \\\\ " <<endl;
}



out<<"\\hline"<<endl;
out<<"\\end{tabular}"<<endl;
out<<"\\end{center}"<<endl;
out<<"\\caption{lumiprocessed}"<<endl;
out<<"\\end{table}"<<endl;
out<<"\\end{document}"<<endl;

//cout<<"My luminosity is : "<<mylumi<<endl;
lumi(file).print(0.5,0.5);
C->SaveAs("lumicheck.pdf");
delete C;
file->Close();
return(0);
}
