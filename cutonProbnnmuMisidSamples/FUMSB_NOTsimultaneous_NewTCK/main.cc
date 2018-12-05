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
#include "splitmisidsamples.hpp"

using namespace std;
 


int main(int argc, char *argv[]){


        string pathname = argv[1];



//int main(){





//	string pathname = "/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_symmetric_newcontrolchannel/haddtuples/";

	string filename1="JpsiKdata_LowFCME";
        string filename2="JpsiKdata_HighFCME";
	string filename3="finaldata_HighFCME";
        string filename4="finaldata_LowFCME";

	string decaytreename = "DecayTree";
	string ext = ".root";
	string cuttag = "_Probnnmu3";


	string namecuttree1 = (filename1+cuttag).c_str();
	string namecuttree2 = (filename2+cuttag).c_str();
	string namecuttree3 = (filename3+cuttag).c_str();
	string namecuttree4 = (filename4+cuttag).c_str();
//	string namecuttree5 = (filename5+cuttag).c_str();
//	string namecuttree6 = (filename6+cuttag).c_str();
//        string namecuttree7 = (filename7+cuttag).c_str();
//        string namecuttree8 = (filename8+cuttag).c_str();
//        string namecuttree9 = (filename9+cuttag).c_str();
//        string namecuttree10 = (filename10+cuttag).c_str();
//        string namecuttree11 = (filename11+cuttag).c_str();
//        string namecuttree12 = (filename12+cuttag).c_str();
//        string namecuttree13 = (filename13+cuttag).c_str();
//        string namecuttree14 = (filename14+cuttag).c_str();
//        string namecuttree15 = (filename15+cuttag).c_str();
//        string namecuttree16 = (filename16+cuttag).c_str();




        string cut1 = "mu1_ProbNNmu>0.3 && mu2_ProbNNmu>0.3";
	string cut2 = "mu1_ProbNNmu>0.3 && mu2_ProbNNmu>0.3 && mu3_ProbNNmu>0.3";
	string cutinfile = "ProbNNmu$>$0.3";

	double pionmisid;
	double kaonmisid;
	double misid;
	double mcsig;
	double combi;
	double partreco;
        double protonmisid;
        double osmis;
        double pionosmis;
        double kaonosmis;
        double protonosmis;
        double jpsikdata;
        double jpsikmc2011;
        double jpsikmc2012; 
        double mcsigPHSP;
        double lowermasssdata;
        double lowermasssdatafull;
        double jpsikdatalow;
        double jpsikdatahigh;
        double datalow;
        double datahigh;



	jpsikdatalow=cutTree((pathname+filename1+ext).c_str(), decaytreename, (namecuttree1+ext).c_str(), cut1);
	jpsikdatahigh=cutTree((pathname+filename2+ext).c_str(), decaytreename, (namecuttree2+ext).c_str(), cut1);
        datalow=cutTree((pathname+filename3+ext).c_str(), decaytreename, (namecuttree3+ext).c_str(), cut2); 
	datahigh=cutTree((pathname+filename4+ext).c_str(), decaytreename, (namecuttree4+ext).c_str(), cut2);

	double numofmcsig = 72;
	double numofpartreco = 756.4;
	double numofmisid = 80000;
	double numofcombinatorial = 13242;




	ofstream out;
	out.open("Probnncut.tex");


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
	out<<"dataLowFCME  & "<<cutinfile<<" & "<< datalow << " & " <<" \\\\ "<<endl;
        out<<"dataHighFCME & "<<cutinfile<<" &  "<< datahigh << " \\\\ "<<endl;
        out<<"jpsikdatalow & "<<cutinfile<<" &  "<< jpsikdatalow << " \\\\ "<<endl;
        out<<"jpsikdatahigh & "<<cutinfile<<" &  "<< jpsikdatahigh << " \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{Cutofbdt400Misid.txt}"<<endl;
	out<<"\\end{table}"<<endl;
	out<<"\\end{document}"<<endl;

        ofstream out2;
        out2.open("numofeventsleftintuples.tex");
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
        out2<<"\\begin{tabular}{| l | l | l |}"<<endl;
        out2<<"\\hline"<<endl;
        out2<<"Sample & cut &  Num of evts left in tuple\\\\ "<<endl;
        out2<<"dataLowFCME  & "<<cutinfile<<" & "<< getmyentries((namecuttree3+ext).c_str(),"DecayTree")<<" \\\\ "<<endl;
        out2<<"dataHighFCME & "<<cutinfile<<" &  "<< getmyentries((namecuttree4+ext).c_str(),"DecayTree")<< " \\\\ "<<endl;
        out2<<"jpsikdatalow & "<<cutinfile<<" &  "<< getmyentries((namecuttree1+ext).c_str(),"DecayTree")<< " \\\\ "<<endl;
        out2<<"jpsikdatahigh & "<<cutinfile<<" &  "<< getmyentries((namecuttree2+ext).c_str(),"DecayTree")<< " \\\\ "<<endl;
        out2<<"\\hline"<<endl;
        out2<<"\\end{tabular}"<<endl;
        out2<<"\\end{center}"<<endl;
        out2<<"\\caption{Entries.txt}"<<endl;
        out2<<"\\end{table}"<<endl;
        out2<<"\\end{document}"<<endl;



	return(0);



}



