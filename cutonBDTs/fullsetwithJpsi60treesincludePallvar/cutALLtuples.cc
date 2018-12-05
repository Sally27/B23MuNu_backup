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






int main(){


string pathname = "/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/60TreesCombiAppliedonAllVar/";

string filename1="SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID";
string filename2="SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID";
string filename3="SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut";
string filename4="B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut";
string filename5="Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut";
string filename6="B23Pimu_MCtruth_Jpsi_cut_mu3nShared_qmincut";


string decaytreename = "DecayTree";
string ext = ".root";
string cuttag = "_60TreesComAllVar";


string namecuttree1 = (filename1+cuttag).c_str();
string namecuttree2 = (filename2+cuttag).c_str();
string namecuttree3 = (filename3+cuttag).c_str();
string namecuttree4 = (filename4+cuttag).c_str();
string namecuttree5 = (filename5+cuttag).c_str();
string namecuttree6 = (filename6+cuttag).c_str();



string cut2 = "Combinatorial60TreesPfinaltuplesNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection > 0.56";
string cutinfile = "Combinatorial60TreesPfinaltuples $>$ 0.56";

double pionmisid;
double kaonmisid;
double misid;
double mcsig;
double combi;
double partreco;


kaonmisid=cutTree((pathname+filename1+ext).c_str(), decaytreename, (namecuttree1+ext).c_str(), cut2);
pionmisid=cutTree((pathname+filename2+ext).c_str(), decaytreename, (namecuttree2+ext).c_str(), cut2);
misid=cutTree((pathname+filename3+ext).c_str(), decaytreename, (namecuttree3+ext).c_str(), cut2);
mcsig=cutTree((pathname+filename4+ext).c_str(), decaytreename, (namecuttree4+ext).c_str(), cut2);
combi=cutTree((pathname+filename5+ext).c_str(), decaytreename, (namecuttree5+ext).c_str(), cut2);
partreco=cutTree((pathname+filename6+ext).c_str(), decaytreename, (namecuttree6+ext).c_str(), cut2);

double numofmcsig = 96.0405;
double numofpartreco = 756.4;
double numofmisid = 281250;
double numofcombinatorial = 1000000;




ofstream out;
out.open("Combinatorial60TreesPfinaltuplesNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection056.txt");
out<<"\\begin{table}[h]"<<endl;
out<<"\\begin{center}"<<endl;
out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
out<<"\\hline"<<endl;
out<<"Sample & cut &  Eff of cut &  Num of evts(rough)\\\\ "<<endl;
out<<"kaonmisid  & "<<cutinfile<<" & "<< kaonmisid << " & " << " \\\\ "<<endl;
out<<"pionmisid  & "<<cutinfile<<" & "<< pionmisid << " & " << " \\\\ "<<endl;
out<<"misid  & "<<cutinfile<<" & "<< misid << " & "<< numofmisid*misid <<" \\\\ " <<endl;
out<<"mcsig  & "<<cutinfile<<" & "<< mcsig << " & "<< numofmcsig*mcsig <<"  \\\\ "<<endl;
out<<"combi  & "<<cutinfile<<" & "<< combi << " & "<< numofcombinatorial*combi <<" \\\\ "<<endl;
out<<"partreco  & "<<cutinfile<<" & "<< partreco << " & " << numofpartreco*partreco  << " \\\\ "<<endl;
out<<"\\hline"<<endl;
out<<"\\end{tabular}"<<endl;
out<<"\\end{center}"<<endl;
out<<"\\caption{Cutofbdt400comb.txt}"<<endl;
out<<"\\end{table}"<<endl;





return(0);



}



