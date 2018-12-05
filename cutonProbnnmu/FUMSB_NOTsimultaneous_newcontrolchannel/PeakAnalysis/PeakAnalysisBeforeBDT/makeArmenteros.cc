// #include "fitAndSplotKmumuDataForTraining.hpp"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TTree.h"
#include "TIterator.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooMinuit.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooStats/SPlot.h"
#include "TTreeFormula.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TSystem.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "RooExponential.h"
#include "RooFormulaVar.h"
#include "TVector3.h"
#include "TH2D.h"
#include "TTreeFormula.h"

double m_pion = 139.57;
double m_d0 = 1864.86;
double m_dst = 2010.26;
double mMu = 105.6583715;

void makeArmenteros(std::string FileName, std::string TreeName, std::string cuts, std::string plotdir) 
{


  TFile fin(FileName.c_str());
  TTree *tin = (TTree*) fin.Get(TreeName.c_str());
  tin->SetBranchStatus("*",0);
  tin->SetBranchStatus("mu1_PX",1);
  tin->SetBranchStatus("mu1_PY",1);
  tin->SetBranchStatus("mu1_PZ",1);
  tin->SetBranchStatus("mu2_PX",1);
  tin->SetBranchStatus("mu2_PY",1);
  tin->SetBranchStatus("mu2_PZ",1);
//  tin->SetBranchStatus("mu2_PIDe",1);
  tin->SetBranchStatus("mu1_ID",1);
  tin->SetBranchStatus("Bplus_Corrected_Mass",1); 
// tin->SetBranchStatus("Kpi_M",1); 
  

  TVector3 e_plus_P, K_Kst_P, Kpi_P; 
  int e_plus_ID;
  

  tin->SetBranchAddress("mu1_PX",&e_plus_P[0]);  
  tin->SetBranchAddress("mu1_PY",&e_plus_P[1]);
  tin->SetBranchAddress("mu1_PZ",&e_plus_P[2]);
  tin->SetBranchAddress("mu1_ID",&e_plus_ID);
  

  tin->SetBranchAddress("mu2_PX",&K_Kst_P[0]);
  tin->SetBranchAddress("mu2_PY",&K_Kst_P[1]);
  tin->SetBranchAddress("mu2_PZ",&K_Kst_P[2]);
  

  TTreeFormula ttf( "ttf", cuts.c_str(), tin);

  double pt, pl_plus, pl_minus, alpha;

  TH2D* AKpi = new TH2D("Amumu","Amumu",10,-1,1,20,0,1500);

  std::cout<<"processing "<<TreeName<<"..."<<std::endl;  
  int k=0;
  int pc =0;
  int total = tin->GetEntries();
  

  for(int i(0); i<total; ++i)
  {
    
    tin->GetEntry(i);
    if( !ttf.EvalInstance()) continue;    

    Kpi_P = K_Kst_P + e_plus_P;
    pt = K_Kst_P.Perp(Kpi_P);

    if (e_plus_ID>0)
    { 
      pl_plus = (e_plus_P - pt*(Kpi_P.Orthogonal().Unit())).Mag();
      pl_minus = (K_Kst_P - pt*(Kpi_P.Orthogonal().Unit())).Mag();
    }
    else
    {
      pl_minus = (e_plus_P - pt*(Kpi_P.Orthogonal().Unit())).Mag();
      pl_plus = (K_Kst_P - pt*(Kpi_P.Orthogonal().Unit())).Mag();
    }
    
    alpha = (pl_plus-pl_minus)/(pl_plus+pl_minus);
    
    AKpi->Fill(alpha,pt);

    pc = ((100*i)/total); 
    if(pc == k+10)
    {
      k = pc; 
      std::cout << pc << "\% complete\r" << std::flush;
    }
  }
  


  TCanvas* cv = new TCanvas();

  AKpi->Draw("colz");

  cv->SaveAs((plotdir+"armenteros_mu_mu.pdf").c_str());
  cv->SaveAs("armenteros_mu_mu.root");
  

  delete cv;
  delete AKpi;

}


int main() 
{
  std::string lepton = "mu";
  
  std::string filename = "/vols/lhcb/ss4314/cutonProbnnmu/AntiBDT/PeakAnalysis/finaldata_FitCorM_Probnnmu3.root";
  std::string treename = "DecayTree";
  std::string plotdir = "/vols/lhcb/ss4314/cutonProbnnmu/AntiBDT/PeakAnalysis/";

  std::string trigger = "Bplus_Corrected_Mass>4250 && Bplus_Corrected_Mass<4450";

  makeArmenteros(filename, treename, trigger,
	       plotdir);


//  lepton = "e";
  
//  filename = "/vols/lhcb/palvare1/RK_analysis/DstD0Klnu/Dst2Dpi_D2K"+lepton+"_Strip21_2012_DeltaM.root";
//  treename = "D2KE_Tuple/DecayTree";
//  plotdir = "/home/hep/palvare1/public_html/DstD0K"+lepton+"nu_Data/";

//  makeArmenteros(filename, treename, trigger,
//	       plotdir);


  return 1;
}
 

