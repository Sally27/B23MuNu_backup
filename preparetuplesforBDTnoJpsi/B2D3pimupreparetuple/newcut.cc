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
 

void mctruth(string filename, string decaytreename, string newfilename)
{
  string ext=".root"; 
  cout<<"MC truth matching"<<endl;

  
  TFile* s = new TFile((filename+ext).c_str());
  TTree* t = (TTree*)s->Get(decaytreename.c_str());

  Double_t mu3_TRUEP_X, mu3_TRUEP_Y, mu3_TRUEP_Z, mu3_TRUEP_E;
  Double_t mu1_TRUEP_X, mu1_TRUEP_Y, mu1_TRUEP_Z, mu1_TRUEP_E;
  Double_t mu2_TRUEP_X, mu2_TRUEP_Y, mu2_TRUEP_Z, mu2_TRUEP_E;
  Double_t Bplus_TRUEP_X, Bplus_TRUEP_Y, Bplus_TRUEP_Z, Bplus_TRUEP_E;
  Int_t mu2_TRUEID, mu1_TRUEID, mu3_TRUEID, Bplus_TRUEID;
  Int_t mu3_MC_MOTHER_ID, mu1_MC_MOTHER_ID, mu2_MC_MOTHER_ID, mu3_MC_GD_MOTHER_ID, mu1_MC_GD_MOTHER_ID, mu2_MC_GD_MOTHER_ID;
  Int_t Bplus_BKGCAT;


  t->SetBranchAddress("Bplus_BKGCAT", &Bplus_BKGCAT);

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

   t->SetBranchAddress("mu2_TRUEID", &mu2_TRUEID);
   t->SetBranchAddress("mu1_TRUEID", &mu1_TRUEID);
   t->SetBranchAddress("mu3_TRUEID", &mu3_TRUEID);
   t->SetBranchAddress("Bplus_TRUEID", &Bplus_TRUEID);

   t->SetBranchAddress("mu3_MC_MOTHER_ID", &mu3_MC_MOTHER_ID);
   t->SetBranchAddress("mu1_MC_MOTHER_ID", &mu1_MC_MOTHER_ID);
   t->SetBranchAddress("mu2_MC_MOTHER_ID", &mu2_MC_MOTHER_ID);
   t->SetBranchAddress("mu3_MC_GD_MOTHER_ID", &mu3_MC_GD_MOTHER_ID);
   t->SetBranchAddress("mu1_MC_GD_MOTHER_ID", &mu1_MC_GD_MOTHER_ID);
 




   TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
   TTree *t2 = t->CloneTree(0);


 
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
  
//         t2->Print();
//         t2->Write("",TObject::kOverwrite);
//	 f->Close();
//	 f1->Close();



  double effofcut;



  effofcut = (double(count)/double(t->GetEntries()));
  cout<<"Efficiency of MC truth:  : "<< effofcut <<endl;

  
//  t2->Print();
  filefort2->Write("",TObject::kOverwrite);
  filefort2->Close();
  s->Close();

  return;
  
}
 

string Jpsi(string filename, string decaytreename, string newfilename)
{
  Double_t mu2_isMuon, mu1_isMuon, mu3_isMuon, Bplus_isMuon, mu2_inMuon, mu1_inMuon, mu3_inMuon, mu3_MINIPCHI2, mu3_PIDmu, mu3_PIDK, mu3_ghost, mu3_TRACK_CHI2, mu3_PIDp;

  string ext=".root";
  cout<<"Vetoing Jpsi"<<endl;


  Double_t mu3_PX, mu3_PY, mu3_PZ, mu3_PE;
  Double_t mu1_PX, mu1_PY, mu1_PZ, mu1_PE;
  Double_t mu2_PX, mu2_PY, mu2_PZ, mu2_PE;

  TFile* s = new TFile((filename+ext).c_str());
  TTree* t = (TTree*)s->Get(decaytreename.c_str());
//  t->SetBranchAddress("mu1_isMuon", &mu1_isMuon);
//  t->SetBranchAddress("mu2_isMuon", &mu2_isMuon); 
//  t->SetBranchAddress("mu3_isMuon", &mu3_isMuon);
  
//  t->SetBranchAddress("mu1_inMuon", &mu1_inMuon);
//  t->SetBranchAddress("mu2_inMuon", &mu2_inMuon);
//  t->SetBranchAddress("mu3_inMuon", &mu3_inMuon);

//  t->SetBranchAddress("mu1_inMuon", &mu1_inMuon);
//  t->SetBranchAddress("mu2_inMuon", &mu2_inMuon);
//  t->SetBranchAddress("mu3_MINIPCHI2", &mu3_MINIPCHI2);
//  t->SetBranchAddress("mu3_PIDmu", &mu3_PIDmu);
//  t->SetBranchAddress("mu3_PIDK", &mu3_PIDK);
//  t->SetBranchAddress("mu3_PIDp", &mu3_PIDp);
//  t->SetBranchAddress("mu3_ghost", &mu3_ghost);
//  t->SetBranchAddress("mu3_TRACK_CHI2", &mu3_TRACK_CHI2);
 
//  t->SetBranchAddress("mu1_isMuon", &mu1_isMuon);
//  t->SetBranchAddress("mu2_isMuon", &mu2_isMuon);
//  t->SetBranchAddress("mu3_isMuon", &mu3_isMuon);


// veto J/psi
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


  TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
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

//      cout<<count<<endl;
      if (((mu1mu2<jpsimin) || ((mu1mu2>jpsimax) && (mu1mu2<psi2smin)) || (mu1mu2>psi2smax)) && ((mu2mu3<jpsimin) || ((mu2mu3>jpsimax) && (mu2mu3<psi2smin)) || (mu2mu3>psi2smax)))

//IN CASE YOU WANT TO APPLY both mu1mu2 and mu2mu3combination
// && ((mu2mu3<jpsimin) || ((mu2mu3>jpsimax) && (mu2mu3<psi2smin)) || (mu2mu3>psi2smax)))

     {       
      	t2->Fill();
        count2++;
 //       cout<<"YouMayPass,";
 //       cout<<count2<<",";
//        cout<<Bplus_isMuon<<","<<mu1_isMuon<<","<<mu2_isMuon<<","<<mu3_isMuon<<endl;
//        cout<<"Infiltrators:"<<mu3_isMuon<<endl;
//        cout<<"Inv mass 1 and 2:"<< mu1mu2<<endl;
//        if (mu1mu2>psi2smax)
//        {
 //       cout<<" Heavy dimuon inv mass 1 and 2:"<< mu1mu2<<endl;
//        }

     }

   }

  double effofcut;

  effofcut = (double(count2)/double(t->GetEntries()));
  cout<<"Efficiency of Jpsiveto:  : "<< effofcut <<endl;

  string newfilenamereturn = (newfilename).c_str();
//  t1->Print();
//  t2->Print();
  f1->Write();
  filefort2->Write("",TObject::kOverwrite);
  filefort2->Close();
  f1->Close();
  s->Close();

  return(newfilenamereturn);
  
}


string addKFoldandW(string filename, string decaytreename, string newfilename) {


cout<<"Adding Kfold and W"<<endl;
double s = 1.0;


if (s == 1.0){

string ext=".root";

//cout<<"lala"<<endl;
//cout<<newfilename<<endl;

TFile* f = new TFile((newfilename+ext).c_str(),"update");
TTree* t3 = (TTree*)f->Get(decaytreename.c_str());

//cout<<"lala2"<<endl;


UInt_t KFold;
Float_t W;
W=1.0;
TRandom number;
TBranch *newBranch1 = t3->Branch("W",&W,"W/F");
TBranch *newBranch0 = t3->Branch("KFold",&KFold,"KFold/I");


Int_t nentries = (Int_t)t3->GetEntries();
for (Int_t i = 0; i < nentries; i++){
        t3->GetEntry(i);
        KFold= number.Integer(10);
        newBranch0->Fill();
        newBranch1->Fill();
        }
t3->Write("",TObject::kOverwrite); // save only the new version of the tree
}


f->Close();

}


void addqsqinf(string filename, string decaytreename, string newfilename)
{

  cout<<"Adding qsqinfo"<<endl;  

  string ext=".root";

  TFile* s = new TFile((filename+ext).c_str());
  TTree* t = (TTree*)s->Get(decaytreename.c_str());



//  TFile* s = new TFile("B23MuNuNewMCsamplevetoJpsi.root");
//  TTree* t = (TTree*)s->Get("DecayTree");


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

 
  TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
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
//        cout<<count2<<endl;
//        cout<<"mu1mu2"<< mu1mu2 << "mu2mu3"<< mu2mu3 << "max" << maxq2 << "min" << minq2 <<endl;     
   }

//  t2->Print();
  //filefort2->Write(); 
  //
  filefort2->Write("",TObject::kOverwrite);
  filefort2->Close();
  s->Close();

  return;
  
}

 


vector<string> cuttuple(string pathname, string filename, string decaytreename, string ext, string cutvar, double cutval)
{
  Double_t cutvarholder;
  Double_t effofcut;
  vector<string> list;

  TFile* s = new TFile((pathname+filename+ext).c_str());
  TTree* t = (TTree*)s->Get(decaytreename.c_str());

  cout<<"I am here boys"<<endl;



  t->SetBranchAddress(cutvar.c_str(), &cutvarholder);

  TFile *filefort2 = new TFile((filename+"_cut_"+cutvar+ext).c_str(), "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2;

  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      if (cutvarholder<cutval)
      {       
        t2->Fill();
        count2++;
      }
   }

  effofcut = (double(count2)/double(t->GetEntries()));
  list.push_back((filename+"_cut_"+cutvar).c_str());
  cout<<"Efficiency of cut: "<< cutvar << " < " << cutval << " : "<< effofcut <<endl;

  filefort2->Write("",TObject::kOverwrite);
  return(list);
  filefort2->Close();
  s->Close();
}


vector<string> cuttuplehere(string filename, string decaytreename, string ext, string cutvar, double cutval)
{
  Double_t cutvarholder;
  Double_t effofcut;
  vector<string> list;

  TFile* s = new TFile((filename+ext).c_str());
  TTree* t = (TTree*)s->Get(decaytreename.c_str());

  cout<<"I am here boys"<<endl;



  t->SetBranchAddress(cutvar.c_str(), &cutvarholder);

  TFile *filefort2 = new TFile((filename+"_cut_"+cutvar+ext).c_str(), "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2;

  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      cout<<cutvarholder<<endl;
      cout<<cutval<<endl;
      if (cutvarholder != cutval)
      {       
        t2->Fill();
        count2++;
      }
   }

  effofcut = (double(count2)/double(t->GetEntries()));
  list.push_back((filename+"_cut_"+cutvar).c_str());
  cout<<"Efficiency of cut: "<< cutvar << " == " << cutval << " : "<< effofcut <<endl;

  filefort2->Write("",TObject::kOverwrite);
  return(list);
  filefort2->Close();
  s->Close();
}


vector<string> cuttupleheretry(string filename, string decaytreename, string ext, string cutvar, string cut)
{
  Double_t cutvarholder;
  Double_t effofcut;
  vector<string> list;

  TFile* s = new TFile((filename+ext).c_str());
  TTree* t = (TTree*)s->Get(decaytreename.c_str());

  cout<<"I am here boys"<<endl;



  t->SetBranchAddress(cutvar.c_str(), &cutvarholder);

  TFile *filefort2 = new TFile((filename+"_cut_"+cutvar+ext).c_str(), "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2;

  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
//      cout<<cutvarholder<<endl;
//      cout<<cutval<<endl;
      if (cut)
      {
        t2->Fill();
        count2++;
      }
   }

  effofcut = (double(count2)/double(t->GetEntries()));
  list.push_back((filename+"_cut_"+cutvar).c_str());
  cout<<"Efficiency of cut: "<< cutvar << " == " << cutval << " : "<< effofcut <<endl;

  filefort2->Write("",TObject::kOverwrite);
  return(list);
  filefort2->Close();
  s->Close();
}







 applyBDTnoqsqcut()
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






void main(){

string pathname = "/vols/lhcbdisk05/ss4314/tuples/B2D3pimu/";
string filename = "B2D3pimufinal";
string decaytreename = "B2D3pimu_Tuple/DecayTree";
string ext = ".root";
string cuttag = "_MCtruth";
string namecuttree2 = (filename+cuttag).c_str();


mctruth((pathname+filename).c_str(), decaytreename, (namecuttree2).c_str());



string filename = namecuttree2;
string decaytreename = "DecayTree";
string ext = ".root";
string cuttag = "_mu3nShared";
string namecuttree2 = (filename+"_cut"+cuttag).c_str();
string cut2 = "mu3_nShared == 0.0";

cutTree((filename+ext).c_str(), decaytreename, (namecuttree2+ext).c_str(), cut2);


//string filename = namecuttree2;
//string decaytreename = "DecayTree";
//string ext = ".root";
//string cuttag = "_Jpsi";
//string namecuttree2 = (filename+cuttag).c_str();


//Jpsi((filename).c_str(), decaytreename, (namecuttree2).c_str());


string filename = namecuttree2;
string decaytreename = "DecayTree";
string ext = ".root";
string cuttag = "";
string namecuttree2 = (filename+cuttag).c_str();

addKFoldandW(filename.c_str(), decaytreename, (namecuttree2).c_str());

string filename = namecuttree2;
string decaytreename = "DecayTree";
string ext = ".root";
string cuttag = "";
string namecuttree2 = (filename+cuttag).c_str();

addqsqinf(filename.c_str(), decaytreename, (namecuttree2).c_str());

string filename = namecuttree2;
string decaytreename = "DecayTree";
string ext = ".root";
string cuttag = "_qmincut";
string namecuttree2 = (filename+cuttag).c_str();
cut2 = "minq2 < 960400";

cutTree((filename+ext).c_str(), decaytreename, (namecuttree2+ext).c_str(), cut2);




return;



}



