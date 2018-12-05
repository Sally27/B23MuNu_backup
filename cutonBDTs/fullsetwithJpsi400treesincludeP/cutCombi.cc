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
 

void cutTree(string nametree, string decaytreename, string namecuttree, string cuts)
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
}






int main(){


string pathname = "/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/400treesandPnormalBDTCombvsMCMARCH2016withJpsi/";

string filename1="B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID";
string filename2="B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID";
string filename3="B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut";
string filename4="B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut";
string filename5="B23MuNuSignal2012and2011data_corrm_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmin";
string filename6="B2D3pimufinal_MCtruth_Jpsi_cut_mu3nShared_qmin";


string decaytreename = "DecayTree";
string ext = ".root";
string cuttag = "_400andPPUNZIoptBDT";


string namecuttree1 = (filename1+cuttag).c_str();
string namecuttree2 = (filename2+cuttag).c_str();
string namecuttree3 = (filename3+cuttag).c_str();
string namecuttree4 = (filename4+cuttag).c_str();
string namecuttree5 = (filename5+cuttag).c_str();
string namecuttree6 = (filename6+cuttag).c_str();



string cut2 = "CombinatorialNormalBDTfinal400TreesandPNTrees400_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection > 0.324";

cutTree((pathname+filename1+ext).c_str(), decaytreename, (namecuttree1+ext).c_str(), cut2);
cutTree((pathname+filename2+ext).c_str(), decaytreename, (namecuttree2+ext).c_str(), cut2);
cutTree((pathname+filename3+ext).c_str(), decaytreename, (namecuttree3+ext).c_str(), cut2);
cutTree((pathname+filename4+ext).c_str(), decaytreename, (namecuttree4+ext).c_str(), cut2);
cutTree((pathname+filename5+ext).c_str(), decaytreename, (namecuttree5+ext).c_str(), cut2);
cutTree((pathname+filename6+ext).c_str(), decaytreename, (namecuttree6+ext).c_str(), cut2);


return(0);



}



