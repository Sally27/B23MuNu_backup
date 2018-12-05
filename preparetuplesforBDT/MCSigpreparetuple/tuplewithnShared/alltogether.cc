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

using namespace std;
 

int mctruth()
{
  Double_t mu3_isMuon;

  TFile* s = new TFile("B23MuNuNewMCNShared.root");
  TTree* t = (TTree*)s->Get("B23MuNu_Tuple/DecayTree");

  Int_t mu1_MC_MOTHER_ID, mu2_MC_MOTHER_ID, mu3_MC_MOTHER_ID, mu1_MC_GD_MOTHER_ID, mu2_MC_GD_MOTHER_ID, mu3_MC_GD_MOTHER_ID;
  Int_t Bplus_BKGCAT;


//  TFile *f1 = new TFile("bkgdcatreconmc.root","RECREATE");
//  TTree *t1 = new TTree("pt1","");
//  TTree *t2 = new TTree("pt2","");

/*  gStyle->SetOptStat(0);*/


  t->SetBranchAddress("Bplus_BKGCAT", &Bplus_BKGCAT);


  t->SetBranchAddress("mu1_MC_MOTHER_ID", &mu1_MC_MOTHER_ID);
  t->SetBranchAddress("mu2_MC_MOTHER_ID", &mu2_MC_MOTHER_ID);
  t->SetBranchAddress("mu3_MC_MOTHER_ID", &mu3_MC_MOTHER_ID);
  t->SetBranchAddress("mu1_MC_GD_MOTHER_ID", &mu1_MC_GD_MOTHER_ID);
  t->SetBranchAddress("mu2_MC_GD_MOTHER_ID", &mu2_MC_GD_MOTHER_ID);
  t->SetBranchAddress("mu3_MC_GD_MOTHER_ID", &mu3_MC_GD_MOTHER_ID);
 




  TFile *filefort2 = new TFile("B23MuNuNewMCsample.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);


   count=0;
   count2=0;

   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      count2++;
      cout<<"This is cout2: "<<count2<<endl;

      if (Bplus_BKGCAT<60)
         {
           count++;

              if (mu1_MC_MOTHER_ID==25)
                {
              count2++;
              t2->Fill();
              }

              if (mu3_MC_MOTHER_ID==25)
                {
              count2++;
              t2->Fill();
               }


              if (mu1_MC_MOTHER_ID==35)
                {
              count2++;
              t2->Fill();
              }

              if (mu3_MC_MOTHER_ID==35)
               {
              count2++;
              t2->Fill();
               }
        }

  }
  cout<<"count1: "<<count<<endl;
  cout<<"count2: "<<count2<<endl;
  
  t2->Print();
  filefort2->Write("",TObject::kOverwrite);
  filefort2->Close();
  s->Close();

  return(count);
  
}
 

int Jpsi()
{
  Double_t mu2_isMuon, mu1_isMuon, mu3_isMuon, Bplus_isMuon, mu2_inMuon, mu1_inMuon, mu3_inMuon, mu3_MINIPCHI2, mu3_PIDmu, mu3_PIDK, mu3_ghost, mu3_TRACK_CHI2, mu3_PIDp;

  Double_t mu3_PX, mu3_PY, mu3_PZ, mu3_PE;
  Double_t mu1_PX, mu1_PY, mu1_PZ, mu1_PE;
  Double_t mu2_PX, mu2_PY, mu2_PZ, mu2_PE;

  TFile* s = new TFile("B23MuNuNewMCsample.root");
  TTree* t = (TTree*)s->Get("DecayTree");
//  t->SetBranchAddress("mu1_isMuon", &mu1_isMuon);
//  t->SetBranchAddress("mu2_isMuon", &mu2_isMuon); 
//  t->SetBranchAddress("mu3_isMuon", &mu3_isMuon);
  
//  t->SetBranchAddress("mu1_inMuon", &mu1_inMuon);
//  t->SetBranchAddress("mu2_inMuon", &mu2_inMuon);
//  t->SetBranchAddress("mu3_inMuon", &mu3_inMuon);

//  t->SetBranchAddress("mu1_inMuon", &mu1_inMuon);
//  t->SetBranchAddress("mu2_inMuon", &mu2_inMuon);
  t->SetBranchAddress("mu3_MINIPCHI2", &mu3_MINIPCHI2);
  t->SetBranchAddress("mu3_PIDmu", &mu3_PIDmu);
  t->SetBranchAddress("mu3_PIDK", &mu3_PIDK);
  t->SetBranchAddress("mu3_PIDp", &mu3_PIDp);
  t->SetBranchAddress("mu3_ghost", &mu3_ghost);
  t->SetBranchAddress("mu3_TRACK_CHI2", &mu3_TRACK_CHI2);
 
//  t->SetBranchAddress("mu1_isMuon", &mu1_isMuon);
//  t->SetBranchAddress("mu2_isMuon", &mu2_isMuon);
//  t->SetBranchAddress("mu3_isMuon", &mu3_isMuon);


//veto J/psi
   t->SetBranchAddress("mu3_PX", &mu3_PX);
   t->SetBranchAddress("mu3_PY", &mu3_PY);
   t->SetBranchAddress("mu3_PZ", &mu3_PZ);
   t->SetBranchAddress("mu3_PE", &mu3_PE);

   t->SetBranchAddress("mu1_PX", &mu1_PX);
   t->SetBranchAddress("mu1_PY", &mu1_PY);
   t->SetBranchAddress("mu1_PZ", &mu1_PZ);
   t->SetBranchAddress("mu1_PE", &mu1_PE);

   t->SetBranchAddress("mu2_PX", &mu2_PX);
   t->SetBranchAddress("mu2_PY", &mu2_PY);
   t->SetBranchAddress("mu2_PZ", &mu2_PZ);
   t->SetBranchAddress("mu2_PE", &mu2_PE);


  TFile *filefort2 = new TFile("B23MuNuNewMCsamplevetoJpsi.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2;
  TLorentzVector mu1, mu2, mu3;
  Double_t mu1mu2, mu2mu3, mu1mu3;
  Double_t jpsimin, jpsimax, psi2smin, psi2smax;
  jpsimin = 2946.0;
  jpsimax = 3167.0;
  psi2smin = 3586.0;
  psi2smax = 3766.0;

  TFile *f1 = new TFile("JpsimakerSignal.root","RECREATE");
  TTree *t1 = new TTree("InvMass","");



   Int_t count,count2;
   Double_t mu1mu2, mu2mu3, mu1mu3, onlymu1, onlymu2, onlymu3;

   TBranch *bpt1 = t1->Branch("mu1mu2Massfinal",&mu1mu2,"mu1mu2/D");
   TBranch *bpt2 = t1->Branch("mu2mu3Massfinal",&mu2mu3,"mu2mu3/D");
   TBranch *bpt3 = t1->Branch("mu1mu3Massfinal",&mu1mu3,"mu1mu3/D");
   TBranch *bpt4 = t1->Branch("mu1only",&onlymu1,"onlymu1/D");
   TBranch *bpt5 = t1->Branch("mu2only",&onlymu2,"onlymu2/D");
   TBranch *bpt6 = t1->Branch("mu3only",&onlymu3,"onlymu3/D");
   count=0;
   count2=0;



  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;


//veto J/psi and psi (2s)
      mu3[3] = mu3_PE;
      mu3[0] = mu3_PX;
      mu3[1] = mu3_PY;
      mu3[2] = mu3_PZ;

      mu2[3] =  mu2_PE;
      mu2[0] =  mu2_PX;
      mu2[1] =  mu2_PY;
      mu2[2] =  mu2_PZ;

      mu1[3] =  mu1_PE;
      mu1[0] =  mu1_PX;
      mu1[1] =  mu1_PY;
      mu1[2] =  mu1_PZ;

      mu1mu2 = (mu1 + mu2).M();
      mu2mu3 = (mu2 + mu3).M();
      mu1mu3 = (mu1 + mu3).M();


       t1->Fill();
//      if ((mu1mu2>3050) && (mu1mu2<3150))
//      {
//      t2->Fill();
//      count2++;
//      cout<<"YouMayPass,";
//      cout<<count2<<",";
//      cout<<"invmassof mu1 and mu2 :"<<mu1mu2<<endl;
//      }    
//      cout<<"Inv mass 1 and 2:"<< mu1mu2<<endl;

      cout<<count<<endl;
      if (((mu1mu2<jpsimin) || ((mu1mu2>jpsimax) && (mu1mu2<psi2smin)) || (mu1mu2>psi2smax)) && ((mu2mu3<jpsimin) || ((mu2mu3>jpsimax) && (mu2mu3<psi2smin)) || (mu2mu3>psi2smax)))
     {       
      	t2->Fill();
        count2++;
        cout<<"YouMayPass,";
        cout<<count2<<",";
        cout<<Bplus_isMuon<<","<<mu1_isMuon<<","<<mu2_isMuon<<","<<mu3_isMuon<<endl;
        cout<<"Infiltrators:"<<mu3_isMuon<<endl;
        cout<<"Inv mass 1 and 2:"<< mu1mu2<<endl;
        if (mu1mu2>psi2smax)
        {
        cout<<" Heavy dimuon inv mass 1 and 2:"<< mu1mu2<<endl;
        }

     }

   }

  t1->Print();
  t2->Print();
  f1->Write();
  filefort2->Write("",TObject::kOverwrite);
  //t2->SetScanField(0);
  //t2->Scan("Bplus_isMuon:mu1_isMuon:mu2_isMuon:mu3_isMuon"); 
  filefort2->Close();
  f1->Close();
  s->Close();

  return(count2);
  
}


void addKFoldandW() {

double s = 1.0;


if (s == 1.0){

TFile* f = new TFile("B23MuNuNewMCsamplevetoJpsi.root","update");
UInt_t KFold;
Float_t W;
W=1.0;
TRandom number;
TTree *t3 = (TTree*)f->Get("DecayTree");
//TBranch *newBranch = t3->Branch("KFold_0",&KFold_0,"KFold_0/F");
TBranch *newBranch1 = t3->Branch("W",&W,"W/F");
TBranch *newBranch0 = t3->Branch("KFold",&KFold,"KFold/I");
//read the number of entries in the t3
Int_t nentries = (Int_t)t3->GetEntries();
for (Int_t i = 0; i < nentries; i++){
        t3->GetEntry(i);
        KFold= number.Integer(10);
        newBranch0->Fill();
        newBranch1->Fill();
        }
t3->Write("",TObject::kOverwrite); // save only the new version of the tree
}

//if (b == 1.0)
//{
//TFile* f2 = new TFile("my1000background.root","update");
//Int_t KFold;
//TTree *t4 = (TTree*)f2->Get("DecayTree");
//TBranch *newBranch3 = t4->Branch("KFold_0",&KFold_0,"KFold_0/F");
//TBranch *newBranch4 = t4->Branch("KFold_1",&KFold_1,"KFold_1/F");
//TBranch *newBranch0 = t4->Branch("KFold",&KFold,"KFold/I");
//read the number of entries in the t3
//Int_t nentries2 = (Int_t)t4->GetEntries();
//for (Int_t i = 0; i < 1000; i++){
//        KFold= gRandom->Binomial(1,0.5);
//        newBranch0->Fill();

//}
//t4->Write("",TObject::kOverwrite); // save only the new version of the tree
//}

f->Close();

}


void addqsqinf()
{


  TFile* s = new TFile("B23MuNuNewMCsamplevetoJpsi.root");
  TTree* t = (TTree*)s->Get("DecayTree");


  Double_t mu3_PX, mu3_PY, mu3_PZ, mu3_PE;
  Double_t mu1_PX, mu1_PY, mu1_PZ, mu1_PE;
  Double_t mu2_PX, mu2_PY, mu2_PZ, mu2_PE;
 
//
//
//              //veto J/psi
    t->SetBranchAddress("mu3_PX", &mu3_PX);
    t->SetBranchAddress("mu3_PY", &mu3_PY);
    t->SetBranchAddress("mu3_PZ", &mu3_PZ);
    t->SetBranchAddress("mu3_PE", &mu3_PE);
    t->SetBranchAddress("mu1_PX", &mu1_PX);
    t->SetBranchAddress("mu1_PY", &mu1_PY);
    t->SetBranchAddress("mu1_PZ", &mu1_PZ);
    t->SetBranchAddress("mu1_PE", &mu1_PE);

    t->SetBranchAddress("mu2_PX", &mu2_PX);
    t->SetBranchAddress("mu2_PY", &mu2_PY);
    t->SetBranchAddress("mu2_PZ", &mu2_PZ);
    t->SetBranchAddress("mu2_PE", &mu2_PE);

 
  TFile *filefort2 = new TFile("B23MuNuNewMCsamplevetoJpsiandqsqmin.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  TLorentzVector mu1, mu2, mu3;
  Double_t mu1mu2, mu2mu3, mu1mu3, minq2, maxq2;
  TBranch *bpt1 = t2->Branch("qsqmu1andmu2",&mu1mu2,"mu1mu2/D");
  TBranch *bpt2 = t2->Branch("qsqmu2andmu3",&mu2mu3,"mu2mu3/D");
  TBranch *bpt3 = t2->Branch("qsqmu1andmu3",&mu1mu3,"mu1mu3/D"); 
  TBranch *bpt4 = t2->Branch("minq2",&minq2,"minq2/D");
  TBranch *bpt5 = t2->Branch("maxq2",&maxq2,"maxq2/D");


  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<count<<endl;
      mu3[3] = mu3_PE;
      mu3[0] = mu3_PX;
      mu3[1] = mu3_PY;
      mu3[2] = mu3_PZ;

      mu2[3] =  mu2_PE;
      mu2[0] =  mu2_PX;
      mu2[1] =  mu2_PY;
      mu2[2] =  mu2_PZ;

      mu1[3] =  mu1_PE;
      mu1[0] =  mu1_PX;
      mu1[1] =  mu1_PY;
      mu1[2] =  mu1_PZ;

      mu1mu2 = (mu1 + mu2).M2();
      mu2mu3 = (mu2 + mu3).M2();
      mu1mu3 = (mu1 + mu3).M2();      


      maxq2 = std::max(mu1mu2,mu2mu3);
      minq2 = std::min(mu1mu2,mu2mu3);           

 
      	t2->Fill();
        count2++;
        cout<<count2<<endl;
        cout<<"mu1mu2"<< mu1mu2 << "mu2mu3"<< mu2mu3 << "max" << maxq2 << "min" << minq2 <<endl;     
   }

  t2->Print();
  //filefort2->Write(); 
  //
  filefort2->Write("",TObject::kOverwrite);
  filefort2->Close();
  s->Close();

  return;
  
}

 

int cutminqsq()
{
  Double_t minq2;

  TFile* s = new TFile("B23MuNuNewMCsamplevetoJpsiandqsqmin.root");
  TTree* t = (TTree*)s->Get("DecayTree");
  t->SetBranchAddress("minq2", &minq2);
 
  TFile *filefort2 = new TFile("B23MuNuNewMCsamplecutqmin2.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<count<<endl;
      if (minq2<960400)
      {       
      	t2->Fill();
        count2++;
        cout<<count2<<endl;
      }
   }

  t2->Print();
  //filefort2->Write(); 
  //
  filefort2->Write("",TObject::kOverwrite);
  return(count2);
  filefort2->Close();
  s->Close();
}

int applyBDTnoqsqcut()
{

  Double_t trialthing;

  TFile* s = new TFile("B23MuNuNewMCsamplevetoJpsiBDT.root");
  TTree* t = (TTree*)s->Get("DecayTree");
  t->SetBranchAddress("trialthing", &trialthing);

  TFile *filefort2 = new TFile("B23MuNuNewMCsamplevetoJpsiBDTcut.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2;

  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      cout<<count<<endl;
      if (trialthing>0.69)
      {
          t2->Fill();
          count2++;
          cout<<count2<<endl;
      }
  }

        t2->Print();
       filefort2->Write("",TObject::kOverwrite);
       return(count2);
      filefor2->Close();
      s->Close();
}








int applyBDTqsqcut()
{

  Double_t trialthing;


  TFile* s = new TFile("B23MuNuNewMCsamplecutqmin2BDT.root");
  TTree* t = (TTree*)s->Get("DecayTree");
  t->SetBranchAddress("trialthing", &trialthing);

  TFile *filefort2 = new TFile("B23MuNuNewMCsamplecutqmin2BDTcut.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2;

  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      cout<<count<<endl;
      if (trialthing>0.83667)
      {
          t2->Fill();
          count2++;
          cout<<count2<<endl;
      }
  }

        t2->Print();
       filefort2->Write("",TObject::kOverwrite);
       return(count2);
      filefor2->Close();
      s->Close();
}






void main(){
int rawsample;
TFile* s = new TFile("B23MuNuNewMCNShared.root");
TTree* t = (TTree*)s->Get("B23MuNu_Tuple/DecayTree");

rawsample=t->GetEntries();

int numofevtfromstripping = 1114130;
int a, b, c, d;
bool qsqcut=true;
bool bdtcut=false;


if (qsqcut==true){
a = mctruth();
b = Jpsi();
addKFoldandW();
addqsqinf();
c = cutminqsq();

if (bdtcut==true){
        d = applyBDTqsqcut();
        cout<<"This is D"<<d<<endl;
        }




cout<<"q sq cut applied!"<<endl;
cout<<"Final Results: "<<" "<<numofevtfromstripping<<" "<<rawsample<<" "<<a <<" "<<b<<" "<<c<<" "<<d<<endl;
cout<<"eff of stripping:"<<double(rawsample)/double(numofevtfromstripping)<<endl;
cout<<"eff of mctruth:"<<double(a)/double(rawsample)<<endl;
cout<<"eff of jpsi:"<<double(b)/double(a)<<endl;
cout<<"eff of qsqcut:"<<double(c)/double(b)<<endl;
cout<<"eff of stripping mctruth jpsi qsqcut:"<<double(c)/double(numofevtfromstripping)<<endl;
cout<<"eff of bdt:"<<double(d)/double(c)<<endl;
double effcomb=double(c)/double(numofevtfromstripping);
float effgen=0.1920;
float br=0.00000001;
double bdteff=double(d)/double(c);

cout<<"Overall NormFac: effgen:"<<effgen<<"*effcomb:"<<effcomb<<"*br:"<<br<<" overall normalisation fac: "<<float(effgen*effcomb*br) <<endl;
cout<<"Overall NormFac with BDT: effgen:"<<effgen<<"*effcomb:"<<effcomb<<"*br:"<<br<<"*bdtcut:"<<bdteff<<" overall normalisation fac: "<<float(effgen*effcomb*br*bdteff)<<endl;

s->Close();

}





else{
if (qsqcut==false){
a = mctruth();
b = Jpsi();
addKFoldandW();
addqsqinf();

if (bdtcut==true){
        d = applyBDTnoqsqcut();
        cout<<"This is D"<<d<<endl;
        }


cout<<"q sq cut NOT applied!"<<endl;
cout<<"Final Results: "<<rawsample<<" "<<a <<" "<<b<<" "<<c<<endl;
cout<<"eff of stripping:"<<double(rawsample)/double(numofevtfromstripping)<<endl;
cout<<"eff of mctruth:"<<double(a)/double(rawsample)<<endl;
cout<<"eff of jpsi:"<<double(b)/double(a)<<endl;
cout<<"eff of stripping mctruth jpsi"<<double(b)/double(numofevtfromstripping)<<endl;
cout<<"eff of bdt:"<<double(d)/double(b)<<endl;
double effcomb=double(b)/double(numofevtfromstripping);
double effgen=0.1920;
double br=0.00000001;
double bdteff=double(d)/double(b);


cout<<"Overall NormFac: effgen:"<<effgen<<"*effcomb:"<<effcomb<<"*br:"<<br<<" overall normalisation fac: "<<float(effgen*effcomb*br) <<endl;
cout<<"Overall NormFac with BDT: effgen:"<<effgen<<"*effcomb:"<<effcomb<<"*br:"<<br<<"*bdtcut:"<<bdteff<<" overall normalisation fac: "<<float(effgen*effcomb*br*bdteff) <<endl;



}

}


return;



}



