#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include<algorithm>


using namespace std;

int mctruth()
{
  Double_t mu3_TRUEP_X, mu3_TRUEP_Y, mu3_TRUEP_Z, mu3_TRUEP_E;
  Double_t mu1_TRUEP_X, mu1_TRUEP_Y, mu1_TRUEP_Z, mu1_TRUEP_E;
  Double_t mu2_TRUEP_X, mu2_TRUEP_Y, mu2_TRUEP_Z, mu2_TRUEP_E;
  Double_t Bplus_TRUEP_X, Bplus_TRUEP_Y, Bplus_TRUEP_Z, Bplus_TRUEP_E;
  Int_t mu2_TRUEID, mu1_TRUEID, mu3_TRUEID, Bplus_TRUEID;
  Int_t mu3_MC_MOTHER_ID, mu1_MC_MOTHER_ID, mu2_MC_MOTHER_ID, mu3_MC_GD_MOTHER_ID, mu1_MC_GD_MOTHER_ID, mu2_MC_GD_MOTHER_ID;
  Int_t Bplus_BKGCAT;
 

  TFile* f = new TFile("B2D3pimufinal.root");
  TTree* t = (TTree*)f->Get("B2D3pimu_Tuple/DecayTree");

  TFile *f1 = new TFile("B2D3piD0inclusiverightMC.root","RECREATE");
  TTree *t2 = t->CloneTree(0);
//  TTree *t1 = new TTree("InvMass","");
/*  gStyle->SetOptStat(0);*/	

   t->SetBranchAddress("mu3_TRUEP_X", &mu3_TRUEP_X);
   t->SetBranchAddress("mu3_TRUEP_Y", &mu3_TRUEP_Y);
   t->SetBranchAddress("mu3_TRUEP_Z", &mu3_TRUEP_Z);
   t->SetBranchAddress("mu3_TRUEP_E", &mu3_TRUEP_E);

   t->SetBranchAddress("mu1_TRUEP_X", &mu1_TRUEP_X);
   t->SetBranchAddress("mu1_TRUEP_Y", &mu1_TRUEP_Y);
   t->SetBranchAddress("mu1_TRUEP_Z", &mu1_TRUEP_Z);
   t->SetBranchAddress("mu1_TRUEP_E", &mu1_TRUEP_E);

   t->SetBranchAddress("mu2_TRUEP_X", &mu2_TRUEP_X);
   t->SetBranchAddress("mu2_TRUEP_Y", &mu2_TRUEP_Y);
   t->SetBranchAddress("mu2_TRUEP_Z", &mu2_TRUEP_Z);
   t->SetBranchAddress("mu2_TRUEP_E", &mu2_TRUEP_E);
   
   t->SetBranchAddress("Bplus_TRUEP_X", &Bplus_TRUEP_X);
   t->SetBranchAddress("Bplus_TRUEP_Y", &Bplus_TRUEP_Y);
   t->SetBranchAddress("Bplus_TRUEP_Z", &Bplus_TRUEP_Z);
   t->SetBranchAddress("Bplus_TRUEP_E", &Bplus_TRUEP_E);
   

//   t->SetBranchAddress("Bplus_BKGCAT", &Bplus_BKGCAT);
   
   t->SetBranchAddress("mu2_TRUEID", &mu2_TRUEID);
   t->SetBranchAddress("mu1_TRUEID", &mu1_TRUEID);
   t->SetBranchAddress("mu3_TRUEID", &mu3_TRUEID);
   t->SetBranchAddress("Bplus_TRUEID", &Bplus_TRUEID);

   t->SetBranchAddress("mu3_MC_MOTHER_ID", &mu3_MC_MOTHER_ID);
   t->SetBranchAddress("mu1_MC_MOTHER_ID", &mu1_MC_MOTHER_ID);
   t->SetBranchAddress("mu2_MC_MOTHER_ID", &mu2_MC_MOTHER_ID);
   t->SetBranchAddress("mu3_MC_GD_MOTHER_ID", &mu3_MC_GD_MOTHER_ID);
   t->SetBranchAddress("mu1_MC_GD_MOTHER_ID", &mu1_MC_GD_MOTHER_ID);
   t->SetBranchAddress("mu2_MC_GD_MOTHER_ID", &mu2_MC_GD_MOTHER_ID);



   Double_t invmassmu2nu, invmassmu3mu1, invmassmu3mu2, invmassmu1mu2, newinvmassmu3andmu1;
   Int_t count,count2;
   TLorentzVector nu, mu2nu, mu3mu1, mu3mu2, mu1mu2, newmu3mu1;
   TBranch *bpt1 = t2->Branch("invmassmu3mu1",&invmassmu3mu1,"invmassmu3mu1/D");
   TBranch *bpt2 = t2->Branch("invmassmu1mu2",&invmassmu1mu2,"invmassmu1mu2/D");
   TBranch *bpt3 = t2->Branch("invmassmu3mu2",&invmassmu3mu2,"invmassmu3mu2/D");
   TBranch *bpt4 = t2->Branch("invmassmu2nu",&invmassmu2nu,"invmassmu2nu/D");

   count=0;
   count2=0;
   
   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      count2++;
      cout<<"This is cout2: "<<count2<<endl;

              if (((mu3_MC_MOTHER_ID==521) && (mu1_MC_MOTHER_ID==-421) && (mu2_MC_MOTHER_ID==-421) )||((mu3_MC_MOTHER_ID==-521) && (mu1_MC_MOTHER_ID==421) && (mu2_MC_MOTHER_ID==421)))

		{


            cout<<"mu_id: "<<mu3_TRUEID<<" "<<" mu1_id: "<<mu1_TRUEID<<" "<<" mu2_id: "<<mu2_TRUEID<<" "<<" Bplus: "<<Bplus_TRUEID<<" "<<" mu_motherid: "<<" "<<mu3_MC_MOTHER_ID<<" "<<" mu1_motherid: "<<mu1_MC_MOTHER_ID<<" "<<" mu2_motherid: "<<mu2_MC_MOTHER_ID<<" "<<" mu_gdmtid: "<<mu3_MC_GD_MOTHER_ID<<" "<<" mu1_gdmtid: "<<" "<<mu1_MC_GD_MOTHER_ID<<" mu2_gdmtid: "<<" "<<mu2_MC_GD_MOTHER_ID<<endl;


 
	      nu[0] = Bplus_TRUEP_X - (mu2_TRUEP_X+mu1_TRUEP_X+mu3_TRUEP_X);
	      nu[1] = Bplus_TRUEP_Y - (mu2_TRUEP_Y+mu1_TRUEP_Y+mu3_TRUEP_Y);
	      nu[2] = Bplus_TRUEP_Z - (mu2_TRUEP_Z+mu1_TRUEP_Z+mu3_TRUEP_Z);
	      nu[3] = Bplus_TRUEP_E - (mu2_TRUEP_E+mu1_TRUEP_E+mu3_TRUEP_E);
	      

              mu2nu[0] = nu[0];// + mu_TRUEP_X;
      	      mu2nu[1] = nu[1];// + mu_TRUEP_Y;
              mu2nu[2] = nu[2];// + mu_TRUEP_Z;
              mu2nu[3] = nu[3];// + mu_TRUEP_E;


              invmassmu2nu= (nu.Mag());
	      

   
      	      mu3mu1[0] = mu1_TRUEP_X+mu3_TRUEP_X;
              mu3mu1[1] = mu1_TRUEP_Y+mu3_TRUEP_Y;
              mu3mu1[2] = mu1_TRUEP_Z+mu3_TRUEP_Z;
              mu3mu1[3] = mu1_TRUEP_E+mu3_TRUEP_E;
              invmassmu3mu1 =  (mu3mu1.Mag());

              mu3mu2[0] = mu2_TRUEP_X+mu3_TRUEP_X;
              mu3mu2[1] = mu2_TRUEP_Y+mu3_TRUEP_Y;
              mu3mu2[2] = mu2_TRUEP_Z+mu3_TRUEP_Z;
              mu3mu2[3] = mu2_TRUEP_E+mu3_TRUEP_E;
              invmassmu3mu2 =  (mu3mu2.Mag());

              mu1mu2[0] = mu2_TRUEP_X+mu1_TRUEP_X;
              mu1mu2[1] = mu2_TRUEP_Y+mu1_TRUEP_Y;
              mu1mu2[2] = mu2_TRUEP_Z+mu1_TRUEP_Z;
              mu1mu2[3] = mu2_TRUEP_E+mu1_TRUEP_E;
              invmassmu1mu2 =  (mu1mu2.Mag());
              
                count++;
                cout<<"this is count"<<count<<endl;
                cout<<invmassmu2nu<<endl;
              	
		
                t2->Fill();
              	
              }
   }
  
         t2->Print();
         t2->Write("",TObject::kOverwrite);
	 f->Close();
	 f1->Close();

return(count);
}


int Jpsi()
{
  Double_t mu2_isMuon, mu1_isMuon, mu3_isMuon, Bplus_isMuon, mu2_inMuon, mu1_inMuon, mu3_inMuon, mu3_MINIPCHI2, mu3_PIDmu, mu3_PIDK, mu3_ghost, mu3_TRACK_CHI2, mu3_PIDp;

  Double_t mu3_PX, mu3_PY, mu3_PZ, mu3_PE;
  Double_t mu1_PX, mu1_PY, mu1_PZ, mu1_PE;
  Double_t mu2_PX, mu2_PY, mu2_PZ, mu2_PE;

  TFile* s = new TFile("B2D3piD0inclusiverightMC.root");
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


  TFile *filefort2 = new TFile("B2D3piD0inclusiverightMCvetoJpsi.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2;
  TLorentzVector mu1, mu2, mu3;
  Double_t mu1mu2, mu2mu3, mu1mu3;
  Double_t jpsimin, jpsimax, psi2smin, psi2smax;
  jpsimin = 2946.0;
  jpsimax = 3167.0;
  psi2smin = 3586.0;
  psi2smax = 3766.0;

  TFile *f1 = new TFile("JpsimakerBackground.root","RECREATE");
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

  filefort2->Close();
  //t2->SetScanField(0);
  //t2->Scan("Bplus_isMuon:mu1_isMuon:mu2_isMuon:mu3_isMuon"); 
  return(count2);
  
}



void addKFoldandW() {

double b = 1.0;


if (b == 1.0){

TFile* f = new TFile("B2D3piD0inclusiverightMCvetoJpsi.root","update");
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


  TFile* s = new TFile("B2D3piD0inclusiverightMCvetoJpsi.root");
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

 
  TFile *filefort2 = new TFile("B2D3piD0inclusiverightMCvetoJpsiandqsqmin.root", "RECREATE");
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

  TFile* s = new TFile("B2D3piD0inclusiverightMCvetoJpsiandqsqmin.root");
  TTree* t = (TTree*)s->Get("DecayTree");
  t->SetBranchAddress("minq2", &minq2);
 
  TFile *filefort2 = new TFile("B2D3piD0inclusiverightMCcutqmin.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<count<<endl;
      if (minq2<1000000)
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
  
}

int applyBDTnoqsqcut()
{

  Double_t trialthing;

  TFile* s = new TFile("B2D3piD0inclusiverightMCrightIsolationvetoJpsi.root");
  TTree* t = (TTree*)s->Get("DecayTree");
  t->SetBranchAddress("trialthing", &trialthing);

  TFile *filefort2 = new TFile("B2D3piD0inclusiverightMCrightIsolationvetoJpsiBDTcut.root", "RECREATE");
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


  TFile* s = new TFile("B2D3piD0inclusiverightMCrightIsolationcutqmin.root");
  TTree* t = (TTree*)s->Get("DecayTree");
  t->SetBranchAddress("trialthing", &trialthing);

  TFile *filefort2 = new TFile("D0inclusiverightMCrightIsolationcutqsqBDTcut.root", "RECREATE");
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
//TFile* s = new TFile("B23MuNuNewMC.root");
//TTree* t = (TTree*)s->Get("B23MuNu_Tuple/DecayTree");

TFile* f = new TFile("B2D3pimufinal.root");
TTree* t = (TTree*)f->Get("B2D3pimu_Tuple/DecayTree");



rawsample=t->GetEntries();

int numofevtfromstripping = 2054607;
int a, b, c, d;
bool qsqcut=false;
bool bdtcut=true;

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
double effgen=0.16025;
double br=0.0000001;
double bdteff=double(d)/double(c);

cout<<"Overall NormFac: effgen:"<<effgen<<"*effcomb:"<<effcomb<<"*br:"<<br<<" overall normalisation fac: "<<float(effgen*effcomb*br) <<endl;
cout<<"Overall NormFac with BDT: effgen:"<<effgen<<"*effcomb:"<<effcomb<<"*br:"<<br<<"*bdtcut:"<<bdteff<<" overall normalisation fac: "<<float(effgen*effcomb*br*bdteff)<<endl;

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
double effgen=0.16025;
double br=0.0000001;
double bdteff=double(d)/double(b);


cout<<"Overall NormFac: effgen:"<<effgen<<"*effcomb:"<<effcomb<<"*br:"<<br<<" overall normalisation fac: "<<float(effgen*effcomb*br) <<endl;
cout<<"Overall NormFac with BDT: effgen:"<<effgen<<"*effcomb:"<<effcomb<<"*br:"<<br<<"*bdtcut:"<<d<<" overall normalisation fac: "<<float(effgen*effcomb*br*bdteff) <<endl;


     
}

}


}
