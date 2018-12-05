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
#include "TString.h"
#include<string>
#include<vector>
#include "THStack.h"
#include "TLine.h"
#include "TPaveText.h"
#include <string>
#include <iostream>
#include <sstream>
#include "TMath.h"
#include <math.h>
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TObjArray.h"
#include "TTreeFormula.h"
#include "TH2I.h"
#include "THStack.h"
#include "TObjArray.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TText.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TPaveText.h"
#include "TTree.h"
#include "TTreeFormula.h"
#include "TFile.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <string>
#include "TH2F.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TGraph.h"
#include<vector>
#include<algorithm>
#include "TH3D.h"
#include "TH3F.h"
#include "TPad.h"

using namespace std;

string d2s(double d)
{
string ret;
ostringstream os;
os<<d;
return os.str();
}


class DataSample {
 public:
  DataSample(std::string filename, std::string treename) : _filename(filename), _treename(treename), f(NULL), t(NULL) 
  { this->open(); }
  ~DataSample() { this->close(); }
  TString _filename;
  TString _treename;  
  TFile *f;
  TTree *t;
  void open();
  void close();
};

void DataSample::open()
{
  f = new TFile(_filename);
  t = (TTree*)f->Get(_treename);
}

void DataSample::close()
{
  if (f)
    if (f->IsOpen())
	f->Close();
  delete f;
}


bool setBranchStatusTTF(TTree* t, string cuts)
{
  TObjArray* array = t->GetListOfBranches();
  int n(array->GetEntries());
  string name;
  bool ret(false);
  for(int i(0); i<n; ++i)
  {
     name = ((*array)[i])->GetName();
     if(cuts.find(name) != string::npos)
     {
        t->SetBranchStatus(name.c_str(), 1);
        ret = true;
     }
  }
  return ret;
}

int plotposition3D(string filename, string cuts, string var1name, string var2name, string var3name){
   
   TH3D th3f("th3f", "th3f", 50,-200,200,50,-200,200,50,200,200);

   TFile f(filename.c_str());
   TTree* t = (TTree*)f.Get("DecayTree");

   t->SetBranchStatus("*",0);
   if(cuts != "") setBranchStatusTTF(t, cuts);
   if(cuts == "") cuts = "1";



   if(!setBranchStatusTTF(t, var1name))
   {
      cout<<"WARNING: IN getCorrelationCoefficient, variable "<<var1name<<" not found, return 0"<<endl;
      return 0;
   }
   if(!setBranchStatusTTF(t, var2name))
   {
      cout<<"WARNING: IN getCorrelationCoefficient, variable "<<var2name<<" not found, return 0"<<endl;
      return 0;
  }

   if(!setBranchStatusTTF(t, var3name))
   {
      cout<<"WARNING: IN getCorrelationCoefficient, variable "<<var3name<<" not found, return 0"<<endl;
      return 0;
   }

   double var1(0);
   double var2(0);
   double var3(0);

   TTreeFormula* ttf = new TTreeFormula("ttf", cuts.c_str(), t);
   TTreeFormula* var1ttf = new TTreeFormula("var1ttf", var1name.c_str(), t);
   TTreeFormula* var2ttf = new TTreeFormula("var2ttf", var2name.c_str(), t);
   TTreeFormula* var3ttf = new TTreeFormula("var3ttf", var3name.c_str(), t);


   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);

      cout<<var1name.c_str()<<endl;

       if(ttf->EvalInstance())
      {
         cout<<"I am here"<<endl;
         var1 = var1ttf->EvalInstance();
         var2 = var2ttf->EvalInstance();
         var3 = var3ttf->EvalInstance(); 
        cout<<var1<<endl;
         cout<<var2<<endl;
         th3f.Fill(var1, var2, var3);
      }
   }

        gStyle->SetCanvasPreferGL(kTRUE);


      TCanvas *canv= new TCanvas("canv2", "canv2", 100, 10, 850, 400);
      TPad *boxPad  = new TPad("box", "box", 0.02, 0.02, 0.48, 0.82);
      TPad *box1Pad = new TPad("box1", "box1", 0.52, 0.02, 0.98, 0.82);
      boxPad->Draw();
      box1Pad->Draw();



      th3f.GetXaxis()->SetTitle(var1name.c_str());
      th3f.GetYaxis()->SetTitle(var2name.c_str());
      th3f.GetZaxis()->SetTitle(var3name.c_str());
      th3f.SetFillColor(2);

      th3f.SetTitle("Position");
      th3f.Draw("glbox");
      //canv.Print( (filename+cleanNameString(var1name+"_vs_"+var2name)+".pdf").c_str());
      canv->Print(( "3D"+var1name+"_vs_"+var2name+"_vs_"+var3name+".pdf").c_str());

   t->SetBranchStatus("*",1);
   delete ttf;
   delete var1ttf;
   delete var2ttf;
   delete var3ttf;
   f.Close();
 return 0;

}


int main()
{

//gROOT->ProcessLine(".x lhcbSally.C");

using namespace std;


plotposition3D("B23SameSignMuonTotal_investigateALLCORMandtigterMMreleasetriggerREQ.root","Bplus_Corrected_Mass > 0","mu1_MuMuMu_PV_X" ,"mu1_MuMuMu_PV_Y" ,"mu1_MuMuMu_PV_Z");

plotposition3D("B23SameSignMuonTotal_investigateALLCORMandtigterMMreleasetriggerREQ.root","Bplus_Corrected_Mass > 0","mu1_MuMuMu_SV_X" ,"mu1_MuMuMu_SV_Y" ,"mu1_MuMuMu_SV_Z");
return(1);
}
