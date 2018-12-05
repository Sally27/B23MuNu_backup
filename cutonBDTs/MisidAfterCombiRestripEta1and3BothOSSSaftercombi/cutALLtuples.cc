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

using namespace std;
 

double cutTree(string nametree, string decaytreename, string namecuttree, string cuts)
{
   TFile f(nametree.c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());

   TFile f2(namecuttree.c_str(), "RECREATE");
   TTree* t2 = t->CloneTree(0);

   TTreeFormula ttf("ttf", cuts.c_str(), t);

   cout<<"Cutting tree "<<nametree<<endl;
   cout<<"Cut applied: "<<cuts<<endl;

   for(int i(0); i<t->GetEntries(); ++i)
   {
      if(i % (t->GetEntries()/10) == 0) cout<<100*i/(t->GetEntries())<<" \% processed"<<endl;
      t->GetEntry(i);
      if(ttf.EvalInstance()) t2->Fill();
   }

   double effofcut;
   effofcut = double(t2->GetEntries())/double(t->GetEntries());
   cout<<"Efficiency of cut"<< cuts << " wrt " << nametree << " is: " << effofcut << endl;

   t2->Write("",TObject::kOverwrite);
   f2.Close();
   f.Close();
   return(effofcut);

}

int getmyentries(string nametree, string decaytreename)
{
   TFile f(nametree.c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());

   int o(0);
   o=t->GetEntries();

   f.Close();
   return(o);

}





int main(){


	string pathname = "/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MisidAfterCombiRestripEta1and3BothOSSSaftercombi/";

	string filename1="B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic";
        string filename10="B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic";
	string filename2="B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic";
	string filename3="B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic";
	string filename4="B23MuNuMCallvar_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic";
	string filename5="Data2012and2011_corrm_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic";
	string filename6="B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic";
        string filename7="B23MuNuFakebothtotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic";
        string filename8="B23MuNuFakebothtotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic";
        string filename9="B23MuNuFakebothtotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic";
        string filename11="B23MuNuFakebothtotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic";
        string filename12="BuKMuMuMerged_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic";        
                           
        string filename13="BuKMuMuMCtotal_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic";
        string filename14="BuKMuMuMC2011total_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic";

	string decaytreename = "DecayTree";
	string ext = ".root";
	string cuttag = "_MisidBasic";


	string namecuttree1 = (filename1+cuttag).c_str();
	string namecuttree2 = (filename2+cuttag).c_str();
	string namecuttree3 = (filename3+cuttag).c_str();
	string namecuttree4 = (filename4+cuttag).c_str();
	string namecuttree5 = (filename5+cuttag).c_str();
	string namecuttree6 = (filename6+cuttag).c_str();
        string namecuttree7 = (filename7+cuttag).c_str();
        string namecuttree8 = (filename8+cuttag).c_str();
        string namecuttree9 = (filename9+cuttag).c_str();
        string namecuttree10 = (filename10+cuttag).c_str();
        string namecuttree11 = (filename11+cuttag).c_str();
        string namecuttree12 = (filename12+cuttag).c_str();
        string namecuttree13 = (filename13+cuttag).c_str();
        string namecuttree14 = (filename14+cuttag).c_str();






	string cut2 = "MisidAfterCombiRestripEta1and3BothOSSSaftercombiNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection > 0.186";
	string cutinfile = "MisidAfterCombiRestripEta1and3BothOSSSaftercombi $>$ 0.186";

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




//	kaonmisid=cutTree((pathname+filename1+ext).c_str(), decaytreename, (namecuttree1+ext).c_str(), cut2);
//	pionmisid=cutTree((pathname+filename2+ext).c_str(), decaytreename, (namecuttree2+ext).c_str(), cut2);
//        protonmisid=cutTree((pathname+filename10+ext).c_str(), decaytreename, (namecuttree10+ext).c_str(), cut2); 
//	misid=cutTree((pathname+filename3+ext).c_str(), decaytreename, (namecuttree3+ext).c_str(), cut2);
	mcsig=cutTree((pathname+filename4+ext).c_str(), decaytreename, (namecuttree4+ext).c_str(), cut2);
	combi=cutTree((pathname+filename5+ext).c_str(), decaytreename, (namecuttree5+ext).c_str(), cut2);
	partreco=cutTree((pathname+filename6+ext).c_str(), decaytreename, (namecuttree6+ext).c_str(), cut2);
        kaonosmis=cutTree((pathname+filename7+ext).c_str(), decaytreename, (namecuttree7+ext).c_str(), cut2);
        protonosmis=cutTree((pathname+filename8+ext).c_str(), decaytreename, (namecuttree8+ext).c_str(), cut2);
        pionosmis=cutTree((pathname+filename9+ext).c_str(), decaytreename, (namecuttree9+ext).c_str(), cut2);
        osmis=cutTree((pathname+filename11+ext).c_str(), decaytreename, (namecuttree11+ext).c_str(), cut2);
        jpsikdata=cutTree((pathname+filename12+ext).c_str(), decaytreename, (namecuttree12+ext).c_str(), cut2);
        jpsikmc2012=cutTree((pathname+filename13+ext).c_str(), decaytreename, (namecuttree13+ext).c_str(), cut2);
        jpsikmc2011=cutTree((pathname+filename14+ext).c_str(), decaytreename, (namecuttree14+ext).c_str(), cut2);



	double numofmcsig = 72;
	double numofpartreco = 756.4;
	double numofmisid = 80000;
	double numofcombinatorial = 13242;




	ofstream out;
	out.open("Misid60TreesPfinaltuplesNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection0186.tex");


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
//	out<<"kaonmisid  & "<<cutinfile<<" & "<< kaonmisid << " & " << " \\\\ "<<endl;
//	out<<"pionmisid  & "<<cutinfile<<" & "<< pionmisid << " & " << " \\\\ "<<endl;
//       out<<"protonmisid  & "<<cutinfile<<" & "<< protonmisid << " & " << " \\\\ "<<endl;
//	out<<"misid  & "<<cutinfile<<" & "<< misid << " & "<< numofmisid*misid <<" \\\\ " <<endl;
	out<<"mcsig  & "<<cutinfile<<" & "<< mcsig << " & "<< numofmcsig*mcsig <<"  \\\\ "<<endl;
	out<<"combi  & "<<cutinfile<<" & "<< combi << " & "<< numofcombinatorial*combi <<" \\\\ "<<endl;
	out<<"partreco  & "<<cutinfile<<" & "<< partreco << " & " << numofpartreco*partreco  << " \\\\ "<<endl;
        out<<"tot misid & "<<cutinfile<<" &  "<< osmis << " \\\\ "<<endl;
        out<<"tot pion & "<<cutinfile<<" &  "<< pionosmis << " \\\\ "<<endl;
        out<<"tot kaon & "<<cutinfile<<" &  "<< kaonosmis << " \\\\ "<<endl;
        out<<"tot proton & "<<cutinfile<<" &  "<< protonosmis << " \\\\ "<<endl;
        out<<"jpsikdata & "<<cutinfile<<" &  "<< jpsikdata << " \\\\ "<<endl; 
        out<<"jpsikmc2011 & "<<cutinfile<<" &  "<< jpsikmc2011 << " \\\\ "<<endl;
        out<<"jpsikmc2012 & "<<cutinfile<<" &  "<< jpsikmc2012 << " \\\\ "<<endl;


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
 //       out2<<"kaonmisid  & "<<cutinfile<<" & "<< getmyentries((namecuttree1+ext).c_str(),"DecayTree") << " \\\\ "<<endl;
   //     out2<<"pionmisid  & "<<cutinfile<<" & "<< getmyentries((namecuttree2+ext).c_str(),"DecayTree") << " \\\\ "<<endl;
     //   out2<<"misid  & "<<cutinfile<<" & "<< getmyentries((namecuttree3+ext).c_str(),"DecayTree") << " \\\\ " <<endl;
        out2<<"mcsig  & "<<cutinfile<<" & "<< getmyentries((namecuttree4+ext).c_str(),"DecayTree") << " \\\\ "<<endl;
        out2<<"combi  & "<<cutinfile<<" & "<< getmyentries((namecuttree5+ext).c_str(),"DecayTree") <<" \\\\ "<<endl;
        out2<<"partreco  & "<<cutinfile<<" & "<< getmyentries((namecuttree6+ext).c_str(),"DecayTree")<< " \\\\ "<<endl;
  //      out2<<"protonmisid  & "<<cutinfile<<" & "<<getmyentries((namecuttree10+ext).c_str(),"DecayTree")<< " \\\\ "<<endl;
        out2<<" kaon  & "<<cutinfile<<" & "<< getmyentries((namecuttree7+ext).c_str(),"DecayTree") <<" \\\\ "<<endl;
        out2<<" proton  & "<<cutinfile<<" & "<< getmyentries((namecuttree8+ext).c_str(),"DecayTree")<< " \\\\ "<<endl;
        out2<<" pion  & "<<cutinfile<<" & "<<getmyentries((namecuttree9+ext).c_str(),"DecayTree")<< " \\\\ "<<endl;
        out2<<" tot  & "<<cutinfile<<" & "<< getmyentries((namecuttree11+ext).c_str(),"DecayTree") <<" \\\\ "<<endl;
        out2<<"jpsikdata  & "<<cutinfile<<" & "<< getmyentries((namecuttree12+ext).c_str(),"DecayTree")<< " \\\\ "<<endl;
        out2<<"jpsimc2012  & "<<cutinfile<<" & "<<getmyentries((namecuttree13+ext).c_str(),"DecayTree")<< " \\\\ "<<endl;
        out2<<"jpsimc2011  & "<<cutinfile<<" & "<<getmyentries((namecuttree14+ext).c_str(),"DecayTree")<< " \\\\ "<<endl;


        out2<<"\\hline"<<endl;
        out2<<"\\end{tabular}"<<endl;
        out2<<"\\end{center}"<<endl;
        out2<<"\\caption{Entries.txt}"<<endl;
        out2<<"\\end{table}"<<endl;
        out2<<"\\end{document}"<<endl;



	return(0);



}



