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

string decaytreename = "DecayTree";
string ext = ".root";
string cuttag = "_PUNZIoptBDT";
string cut2 = "CombinatorialNormalBDTNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection > 0.57";


string pathname4 = "/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/normalBDTCombvsMCqsqcutonMCsignalMARCH2016withJpsi/";
string filename4 = "B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut";


string filename6 = "B2D3pimufinal_MCtruth_Jpsi_cut_mu3nShared_qmin";
string pathname6 = "/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/normalBDTCombvsMCqsqcutonPartRecoMARCH2016withJpsi/";

string pathname2 = "/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/normalBDTCombvsMCqsqcutonPIONmisidMARCH2016withJpsi/";
string filename2 = "B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID";

string pathname1 = "/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/normalBDTCombvsMCqsqcutonKAONmisidMARCH2016withJpsi/";
string filename1 = "B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID";

string pathname5 = "/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/normalBDTCombvsMCqsqcutonCombinatorialMARCH2016withJpsi/";
string filename5 = "B23MuNuSignal2012and2011data_corrm_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmin";


string pathname3 = "/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/normalBDTCombvsMCqsqcutonmisidMARCH2016withJpsi/";
string filename3 = "B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut";

string namecuttree1 = (filename1+cuttag).c_str();
string namecuttree2 = (filename2+cuttag).c_str();
string namecuttree3 = (filename3+cuttag).c_str();
string namecuttree4 = (filename4+cuttag).c_str();
string namecuttree5 = (filename5+cuttag).c_str();
string namecuttree6 = (filename6+cuttag).c_str();



//string cut2 = "CombinatorialNormalBDTfinal400TreesandPNTrees400_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection > 0.324";
string cutinfile = "CombinatorialNormalBDTfinal60Trees $>$ 0.57";

double pionmisid;
double kaonmisid;
double misid;
double mcsig;
double combi;
double partreco;


kaonmisid=cutTree((pathname1+filename1+ext).c_str(), decaytreename, (namecuttree1+ext).c_str(), cut2);
pionmisid=cutTree((pathname2+filename2+ext).c_str(), decaytreename, (namecuttree2+ext).c_str(), cut2);
misid=cutTree((pathname3+filename3+ext).c_str(), decaytreename, (namecuttree3+ext).c_str(), cut2);
mcsig=cutTree((pathname4+filename4+ext).c_str(), decaytreename, (namecuttree4+ext).c_str(), cut2);
combi=cutTree((pathname5+filename5+ext).c_str(), decaytreename, (namecuttree5+ext).c_str(), cut2);
partreco=cutTree((pathname6+filename6+ext).c_str(), decaytreename, (namecuttree6+ext).c_str(), cut2);

double numofmcsig = 96.0405;
double numofpartreco = 301.4;
double numofmisid = 281250;
double numofcombinatorial = 1000000;


ofstream out;
out.open("CombinatorialNormalBDT60Trees_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection.txt");
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
out<<"\\caption{Cutofbdt60Treescomb, benchmarkbdt before bdt num of mc sig estimated before any bdt: 96.0405, num of partreco: 301.5}"<<endl;
out<<"\\end{table}"<<endl;





return(0);



}



