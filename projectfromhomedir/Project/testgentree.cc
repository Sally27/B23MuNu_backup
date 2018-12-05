#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"

using namespace std;

//B prim vtx, B sec vtx, visible mmmtm, visible energy 
double getCorMass(TVector3 BPV, TVector3 BSV,TVector3 visP, double visE); 
//B prim vertex, B sec vertex, momentum of the visible pcles coming from B vertex, position of the muon, 
//momentum of the muon
TLorentzVector getTauP(TVector3 BPV, TVector3 BSV, TVector3 XP, TVector3 muPos, TVector3 muP);
TVector3 getTauLoF(TVector3 BPV, TVector3 BSV, TVector3 XP, TVector3 muPos, TVector3 muP);
TSlavk getPmu1()

void Bmomentum()
{
  double BPx, BPy, BPz;
  TFile* f = new TFile("B23munuSimon.root");
  TTree* t = (TTree*)f->Get("DecayTree");

   t->SetBranchAddress("KPx", &KPx);
   t->SetBranchAddress("KPy", &KPy);
   t->SetBranchAddress("KPz", &KPz);
   t->SetBranchAddress("KPE", &KPE);



}

void Bmass()
{
   /*
   double Ksm(0.89594);
   double Ksw(0.0487);
   double Bm(5.27958);
   double Km(0.493677);
   double pim(0.13957018);
   double taum(1.77682);
   double mum(0.1056583715);
   double num(0.);
   */
   double tauSVx, tauSVy, tauSVz;
   double BPx, BPy, BPz, BPE;
   double tauPx, tauPy, tauPz, tauPE;
   double KsPx, KsPy, KsPz, KsPE;
   double KPx, KPy, KPz, KPE;
   double piPx, piPy, piPz, piPE;
   double mu1Px, mu1Py, mu1Pz, mu1PE;
   double mu2Px, mu2Py, mu2Pz, mu2PE;
   double nu1Px, nu1Py, nu1Pz, nu1PE;
   double nu2Px, nu2Py, nu2Pz, nu2PE;
   double mu2posx, mu2posy, mu2posz;

   double  mB;
   TFile* f = new TFile("B2Ktaumu_gen.root");
   TTree* t = (TTree*)f->Get("DecayTree");

   t->SetBranchAddress("KPx", &KPx);
   t->SetBranchAddress("KPy", &KPy);
   t->SetBranchAddress("KPz", &KPz);
   t->SetBranchAddress("KPE", &KPE);

   t->SetBranchAddress("piPx", &piPx);
   t->SetBranchAddress("piPy", &piPy);
   t->SetBranchAddress("piPz", &piPz);
   t->SetBranchAddress("piPE", &piPE);

   t->SetBranchAddress("mu1Px", &mu1Px);
   t->SetBranchAddress("mu1Py", &mu1Py);
   t->SetBranchAddress("mu1Pz", &mu1Pz);
   t->SetBranchAddress("mu1PE", &mu1PE);
  
   t->SetBranchAddress("mu2Px", &mu2Px);
   t->SetBranchAddress("mu2Py", &mu2Py);
   t->SetBranchAddress("mu2Pz", &mu2Pz);
   t->SetBranchAddress("mu2PE", &mu2PE);

   t->SetBranchAddress("nu1Px", &nu1Px);
   t->SetBranchAddress("nu1Py", &nu1Py);
   t->SetBranchAddress("nu1Pz", &nu1Pz);
   t->SetBranchAddress("nu1PE", &nu1PE);

   t->SetBranchAddress("nu2Px", &nu2Px);
   t->SetBranchAddress("nu2Py", &nu2Py);
   t->SetBranchAddress("nu2Pz", &nu2Pz);
   t->SetBranchAddress("nu2PE", &nu2PE);

   double totPx, totPy, totPz, totPE;

   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      totPx = KPx + piPx + mu1Px + mu2Px + nu1Px + nu2Px; 
      totPy = KPy + piPy + mu1Py + mu2Py + nu1Py + nu2Py; 
      totPz = KPz + piPz + mu1Pz + mu2Pz + nu1Pz + nu2Pz; 
      totPE = KPE + piPE + mu1PE + mu2PE + nu1PE + nu2PE; 
      mB = sqrt(totPE*totPE - totPx*totPx - totPy*totPy - totPz*totPz);
      cout<<mB<<endl;
   }

}

void reconstruct_Bmass()
{

   double KPx, KPy, KPz, KPE;
   double piPx, piPy, piPz, piPE;
   double mu1Px, mu1Py, mu1Pz, mu1PE;
   double mu2Px, mu2Py, mu2Pz, mu2PE;
   double mu2posx, mu2posy, mu2posz;
   double BPVx, BPVy, BPVz;
   double BSVx, BSVy, BSVz;
   double psiPx, psiPy, psiPz, psiPE;
   double nu1Px, nu1Py, nu1Pz;
   double nu2Px, nu2Py, nu2Pz;

   double  mB;
//   TFile* f = new TFile("B2Ktaumu_gen.root");
   TFile* f = new TFile("/home/hep/th1011/gangadir/workspace/th1011/LocalXML/31/output/TupleBc2PsiDs.root");
   TTree* t = (TTree*)f->Get("BcTuple/DecayTree");
//   cout<<"TREE: "<<t<<endl;

   //****************
   /*
   double tauPx;
   t->SetBranchAddress("tauPx", &tauPx);
   double tauPy;
   t->SetBranchAddress("tauPy", &tauPy);
   double tauPz;
   t->SetBranchAddress("tauPz", &tauPz);

   double tauSVx;
   t->SetBranchAddress("tauSVx", &tauSVx);
   double tauSVy;
   t->SetBranchAddress("tauSVy", &tauSVy);
   double tauSVz;
   t->SetBranchAddress("tauSVz", &tauSVz);
   */
   //***************


   t->SetBranchAddress("Kp_PX", &nu1Px);
   t->SetBranchAddress("Kp_PY", &nu1Py);
   t->SetBranchAddress("Kp_PZ", &nu1Pz);

   t->SetBranchAddress("Km_PX", &nu2Px);
   t->SetBranchAddress("Km_PY", &nu2Py);
   t->SetBranchAddress("Km_PZ", &nu2Pz);

   t->SetBranchAddress("psi_PX", &psiPx);
   t->SetBranchAddress("psi_PY", &psiPy);
   t->SetBranchAddress("psi_PZ", &psiPz);
   t->SetBranchAddress("psi_PE", &psiPE);

   t->SetBranchAddress("pi_PX", &mu2Px);
   t->SetBranchAddress("pi_PY", &mu2Py);
   t->SetBranchAddress("pi_PZ", &mu2Pz);
   t->SetBranchAddress("pi_PE", &mu2PE);

   t->SetBranchAddress("Bc_OWNPV_X", &BPVx); 
   t->SetBranchAddress("Bc_OWNPV_Y", &BPVy); 
   t->SetBranchAddress("Bc_OWNPV_Z", &BPVz); 

   t->SetBranchAddress("psi_ENDVERTEX_X", &BSVx); 
   t->SetBranchAddress("psi_ENDVERTEX_Y", &BSVy); 
   t->SetBranchAddress("psi_ENDVERTEX_Z", &BSVz); 

   t->SetBranchAddress("pi_REFPX", &mu2posx);
   t->SetBranchAddress("pi_REFPY", &mu2posy);
   t->SetBranchAddress("pi_REFPZ", &mu2posz);

   double m;
   t->SetBranchAddress("Bc_M", &m);

   TVector3 tauLoF;
   TVector3 BPV, BSV, XP, muPos, muP, visP;
   TLorentzVector tau4P;
   TVector3 tauP;
   TLorentzVector X4P;
   TVector3 tautrueP;
   double mcor, mthib;
   double visE;

//   TH1F* hcor = new TH1F("hcor", "hcor", 100, 4000, 5500);
//   TH1F* hthib = new TH1F("hthib", "hthib", 100, 4000, 5500);

   double mdown(3000);
   double mup(10000);
   TH1F* hcor = new TH1F("hcor", "hcor", 150, mdown, mup);
   TH1F* hthib = new TH1F("hthib", "hthib", 150, mdown, mup);
   TH1F* hm = new TH1F("hm", "hm", 150, mdown, mup);
   TH1F* htauLoF = new TH1F("tauLoF", "tauLoF", 100, 0, 100);
   TH1F* hBLoF = new TH1F("BLoF", "BLoF", 100, 0, 100);
   TH1F* htauCosA = new TH1F("tauCosA", "tauCosA", 100, -0.1,0.5); 
   
   TH1F* htauPmisaligned = new TH1F("tauPmisaligned", "tauPmisaligned", 100, -0.1, 3.15);
   TH1F* htauPmisnormalised = new TH1F("tauPmisnormalised", "tauPmisnormalised", 100, 0,1);
   double tauCosA;

   hthib->SetLineColor(2);
   hm->SetLineColor(8);

   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);      
//      cout<<"i "<<i<<endl;
      BPV[0] = BPVx;
      BPV[1] = BPVy;
      BPV[2] = BPVz;
      BSV[0] = BSVx;
      BSV[1] = BSVy;
      BSV[2] = BSVz;

      tautrueP[0] = nu1Px + nu2Px + mu2Px;
      tautrueP[1] = nu1Py + nu2Py + mu2Py;
      tautrueP[2] = nu1Pz + nu2Pz + mu2Pz;
      
      XP[0] = psiPx;
      XP[1] = psiPy;
      XP[2] = psiPz;
      X4P[0] = XP[0];
      X4P[1] = XP[1];
      X4P[2] = XP[2];
//      X4P[3] = mu1PE+piPE+KPE;
      X4P[3] = psiPE;      

      visP[0] = psiPx + mu2Px;
      visP[1] = psiPy + mu2Py;
      visP[2] = psiPz + mu2Pz;
      visE = psiPE + mu2PE;

      muPos[0] = mu2posx;
      muPos[1] = mu2posy;
      muPos[2] = mu2posz;

      muP[0] = mu2Px;
      muP[1] = mu2Py;
      muP[2] = mu2Pz;
      
//      cout<<tauSVx<<" "<<tauSVy<<" "<<tauSVz<<endl;
      tauLoF = getTauLoF(BPV, BSV, XP, muPos, muP);      
      tau4P = getTauP(BPV, BSV, XP, muPos, muP);
      tauP=tau4P.Vect();
      mcor = getCorMass(BPV, BSV, visP, visE);
      tauCosA = acos((muP*tauLoF) / (muP.Mag() * tauLoF.Mag()));
//      tauCosA = (tauLoF*(tautrueP)) / ((tautrueP).Mag() * tauLoF.Mag());
   
//      cout<<tauP[0]<<" "<<tauPx<<" "<<tauP[0]-tauPx<<endl;
 //     cout<<tauP[1]<<" "<<tauPy<<" "<<tauP[1]-tauPy<<endl;
//      cout<<tauP[2]<<" "<<tauPz<<" "<<tauP[2]-tauPz<<endl;
//      cout<< (tauP+X4P).M()<<endl;
      mthib = (tau4P+X4P).M();
      
//      cout<<" hoho:  "<<(tautrueP*tauP) / (tautrueP.Mag()*tauP.Mag())<<endl;
      htauPmisnormalised ->Fill((tauP.Mag()-tautrueP.Mag())/(tauP.Mag()+tautrueP.Mag()));


      if( tauLoF.Mag() > 1.5 && (BSV-BPV).Mag() > 1.5 &&  tauCosA > 0.01 && tauCosA < 1.5 )
      {
          hthib->Fill(mthib);
          hcor->Fill(mcor);
           hm->Fill(m);

         htauPmisaligned ->Fill(acos( (tautrueP*tauP) / (tautrueP.Mag()*tauP.Mag())) );
      }

      htauLoF->Fill(tauLoF.Mag());
       hBLoF->Fill((BSV-BPV).Mag());
      if(tauLoF.Mag() > 3)
      {
          htauCosA->Fill(tauCosA);
      }

   }

   TCanvas* cm = new TCanvas("cm", "cm", 600, 600);

   hcor->Draw();
   hthib->Draw("same");
   hm->Draw("same");

   TCanvas* ctauLof = new TCanvas("ctauLoF", "taulof", 600, 600);
   htauLoF->Draw();

   TCanvas* cBLof = new TCanvas("cBLoF", "Blof", 600, 600);
   hBLoF->Draw();

   TCanvas* cTauCosA = new TCanvas("cTauCosA", "cTauCosA", 600, 600);
   htauCosA->Draw();

   TCanvas* c3 = new TCanvas("c3", "c3", 600, 600);
   htauPmisaligned->Draw();

   TCanvas* c4 = new TCanvas("c4", "c4", 600, 600);
   htauPmisnormalised->Draw();
}


double getCorMass(TVector3 BPV, TVector3 BSV,TVector3 visP, double visE)
{
   TVector3 tmp; //just here to stock temporary stuff
   TVector3 LB; //NORMALISED vector, line of flight of B  
   LB = BSV-BPV;
   LB = LB.Unit();

   TVector3 missPT;
   missPT =  (LB*visP)*LB - visP;

   return sqrt(visE*visE - visP.Mag2() + missPT.Mag2())+ missPT.Mag(); 
}

TVector3 getTauLoF(TVector3 BPV, TVector3 BSV, TVector3 XP, TVector3 muPos, TVector3 muP)
{
   TVector3 tmp; //just here to stock temporary stuff
   TVector3 LB; //NORMALISED vector, line of flight of B  
   LB = BSV-BPV;
   LB = LB.Unit();

   TVector3 tauPT;
   tauPT =  (LB*XP)*LB - XP;


   double a,b,c,d; //4 coords of plan equation containing tauPT and LB
   tmp = LB.Cross(tauPT.Unit());
   tmp = tmp.Unit();
   a = tmp[0];
   b = tmp[1];
   c = tmp[2];
   d = -a*BSV[0]-b*BSV[1]-c*BSV[2];


   //now will comput intersection of that plan and the muon LoF
   
   double lambda; //lambda of the LoF equation
   lambda = (-a*muPos[0]-b*muPos[1]-c*muPos[2]-d) / (a*muP[0]+b*muP[1]+c*muP[2]);
   TVector3 IP; //tau decay vertex
   IP = muPos +( lambda * muP);

   return IP - BSV; //tmp is parallel to the tau LoF
}

TLorentzVector getTauP(TVector3 BPV, TVector3 BSV, TVector3 XP, TVector3 muPos, TVector3 muP)
{
   
   TVector3 LB; //NORMALISED vector, line of flight of B  
   LB = BSV-BPV;
   LB = LB.Unit();

   TVector3 tauPT;
   tauPT =  (LB*XP)*LB - XP;
//   double taum(1776.82);
   double taum(1968.30);

   //now can get tau 3mmtm
   TVector3 tmp(getTauLoF(BPV, BSV, XP,  muPos, muP));

//   cout<<(tauPT*(tmp)) / (tauPT.Mag() * (tmp).Mag())<<" ";

   tmp = tmp.Unit();
   double norm(tauPT.Mag2() / (tmp*tauPT));
   tmp = norm*tmp; //now tmp is set to the tau 3 mmtm

   double Etau(sqrt( taum*taum+tmp.Mag2() ));

   TLorentzVector ret(tmp, Etau);
   return ret;
}
