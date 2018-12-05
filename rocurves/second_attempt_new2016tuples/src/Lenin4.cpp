#include "Lenin4.hpp"
#include "TLegend.h"
#include "TGraph.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"
#include "TF1.h"
#include <algorithm> 
#include <iostream>
#include <fstream>
#include <string>
#include "TTreeFormula.h"
#include "KFolder.hpp"


using namespace std;


bool getOneRocCurvePunzi(string fsigname,
   string fbkgname,
   string bdtvar, 
   string extracut,
   double sigEff[],
   double bkgRej[],
   unsigned int n,
   bool fa,
   int trgSigEvt,
   int trgBkgEvt,
   string nameplot,
   double mincut,
   double maxcut,
   string punzi,
   string weightBranchSig,
   string weightBranchBkg
)

{
   TFile fSig(fsigname.c_str());
   TTree* tSig = (TTree*)fSig.Get("T");
   TFile fBkg(fbkgname.c_str());
   TTree* tBkg = (TTree*)fBkg.Get("T");

   if(tSig == 0 || tBkg == 0)
   {
      cout<<"ERROR in getOneRocCurve: could not get the tree"<<endl;
      fSig.Close();
      fBkg.Close();
      return false;
   }

   if(extracut == "") extracut = "1";

   if( -1 == tSig->GetEntries( (bdtvar + " > 0 && " + extracut).c_str()) || -1 ==  tBkg->GetEntries( (bdtvar + " > 0 && " + extracut).c_str()) )
   {
      cout<<"ERROR in getOneRocCurve: BDT var "<<bdtvar<<" not found, or problem with extracut"<<endl;
      fSig.Close();
      fBkg.Close();
      return false;
   }

//   double mincut(-0.0);
//   double maxcut(1.0);
   double d(maxcut-mincut);

   double nSig(getEntries(tSig, extracut, weightBranchSig));
   double nBkg(getEntries(tBkg, extracut, weightBranchBkg)); 

   double nSigLeft[n];
   double nBkgLeft[n];

   float FOM[n];
   float maxfom(0.0);

   int cutindex(0);
//   int trgSigEvt(97);
//   int trgBkgEvt(22781);

   double scalefacsig(0.0);
   double scalefacbkg(0.0);

//   bool fa=true;
   string scaling;


   if (fa==false)
   {
   scalefacsig=1.0;
   scalefacbkg=1.0;
   scaling = "NotScaled";
//   ontarget = "False"
   }
   else
   {
   scalefacsig = (double(trgSigEvt)/double(nSig));
   scalefacbkg = (double(trgBkgEvt)/double(nBkg));
   scaling = "Scaled";
//   ontarget = "True";
   }

   ofstream myfile;
   myfile.open (("BDTsummary"+scaling+nameplot+punzi+".txt").c_str()); 

 //  float Punzi[n];
 //  float maxPunzi(0.0);


   for(int i(0); i<n; ++i)
   {

      FOM[i]=(scalefacsig*getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )/(scalefacsig*nSig))/(sqrt((scalefacbkg*getEntries( tBkg, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg ))) + float(3/2));
      cout<<"S/sqrt(B)+3/2: "<<FOM[i]<<endl;
 //     myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
	      if (FOM[i]>maxfom)
		{
		maxfom=FOM[i];
                cutindex=i;            
		}
      nSigLeft[i] = getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )*scalefacsig;
      nBkgLeft[i] = getEntries( tBkg, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )*scalefacbkg;
      sigEff[i] = getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )/nSig;
      bkgRej[i] = getEntries( tBkg, extracut+" && "+bdtvar + " < " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )/nBkg;
      cout<<"Index of cut: "<<i<<" Sig Eff: "<<sigEff[i]<<" Bkg Rej: "<<bkgRej[i]<<" Nsigleft: "<<nSigLeft[i]<<" Nbkgleft: "<<nBkgLeft[i]<<" mincut: "<<d2s(mincut+(i/(1.*n))*d)<<endl;
   }

   double plan = maxfom+(0.1*maxfom);

//    for(int i(0); i<n; ++i)
//    {
//    myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
//    }
   
   TH2F *myfom = new TH2F("eff/sqrt(B)+3/2", "eff/sqrt(B)+3/2",100, mincut, maxcut, 100 , 0.0, plan);
   TCanvas e("together", "together", 600, 600);
   myfom->SetTitle(("FOM_with_SIGfile:"+fsigname).c_str());
   myfom->GetXaxis()->SetTitle("BDT output");
   myfom->GetYaxis()->SetTitle("Sigeff/sqrt(B)+3/2");
   myfom->GetYaxis()->SetTitleOffset(1.25);
   
   for(int i(0); i<n; ++i)
    {
    myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
    }

  
   
   myfom->Draw("COL");
   e.Print(("FOM_"+scaling+nameplot+punzi+".pdf").c_str());

   TH2F *myroc = new TH2F("My roc curve", "My roc curve",100, 0.0, 1.0, 100 , 0.0, 1.0);
   TCanvas f("togethe", "togethe", 600, 600);
   myroc->SetTitle(("Roc Curve_with_SIGfile:"+fsigname).c_str());
   myroc->GetXaxis()->SetTitle("Signal efficiency");
   myroc->GetYaxis()->SetTitle("Background rejection");
   myroc->GetYaxis()->SetTitleOffset(1.25);

   for(int i(0); i<n; ++i)
    {
    myroc->Fill(sigEff[i],bkgRej[i]);
    }



   myroc->Draw("COL");
   f.Print(("ROC_"+scaling+nameplot+punzi+".pdf").c_str());






   cout<<"NSig:"<<nSig<<endl;
   cout<<"NBkg:"<<nBkg<<endl;
   cout<<"Max FOM:"<<*std::max_element(FOM,FOM+n)<<endl;
   cout<<"Optimal cut:"<<(mincut+((cutindex-1)/(1.*n))*d)<<endl;
   cout<<"Index of cut:"<<cutindex<<" Sig Eff:"<<sigEff[cutindex]<<" Bkg Rej:"<<bkgRej[cutindex]<<" Nsigleft:"<<nSigLeft[cutindex]<<" Nbkgleft:"<<nBkgLeft[cutindex]<<endl;
   
   myfile<<"-------------------------BDT summary----------------------"<<endl;
   myfile<<""<<endl;
   myfile<<"Signal sample size:"<<nSig<<endl;
   myfile<<"Background sample size:"<<nBkg<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"Target On: "<< fa <<endl;
   myfile<<"Target signal size:"<<trgSigEvt<<endl;
   myfile<<"Target background size:"<<trgBkgEvt<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"Max FOM: eff(S)/sqrt(B)+3/2:"<<*std::max_element(FOM,FOM+n)<<endl;
   myfile<<"Optimal cut:"<<(mincut+((cutindex-1)/(1.*n))*d)<<endl;
   myfile<<"Min cut: "<<mincut<<"MaxCut: "<<maxcut<<endl;
   myfile<<"Index of cut"<<"---Sig Eff---"<<"---Bkg Rej---"<<"---Nsigleft---"<<"---Nbkgleft---"<<endl;
   myfile<<"-------"<<cutindex<<"-----"<<sigEff[cutindex]<<"-----"<<bkgRej[cutindex]<<"-----"<<nSigLeft[cutindex]<<"-----"<<nBkgLeft[cutindex]<<endl;
   myfile.close();
  



   fSig.Close();
   fBkg.Close();
   return true;
}

bool getOneRocCurveSallyDiffTrainingOneMinBkgRej(string pathnamesally, string fsigname,
   string fbkgname,
   string bdtvar, 
   string extracut,
   double sigEff[],
   double bkgRej[],
   unsigned int n,
   bool fa,
   int trgSigEvt,
   int trgBkgEvt,
   string nameplot,
   double mincut,
   double maxcut,
   string weightBranchSig,
   string weightBranchBkg
)

{
   TFile fSig((pathnamesally+"/"+fsigname).c_str());
   TTree* tSig = (TTree*)fSig.Get("DecayTree");
   TFile fBkg((pathnamesally+"/"+fbkgname).c_str());
   TTree* tBkg = (TTree*)fBkg.Get("DecayTree");

   if(tSig == 0 || tBkg == 0)
   {
      cout<<"ERROR in getOneRocCurve: could not get the tree"<<endl;
      fSig.Close();
      fBkg.Close();
      return false;
   }

   if(extracut == "") extracut = "1";

   if( -1 == tSig->GetEntries( (bdtvar + " > 0 && " + extracut).c_str()) || -1 ==  tBkg->GetEntries( (bdtvar + " > 0 && " + extracut).c_str()) )
   {
      cout<<"ERROR in getOneRocCurve: BDT var "<<bdtvar<<" not found, or problem with extracut"<<endl;
      fSig.Close();
      fBkg.Close();
      return false;
   }

//   double mincut(-0.0);
//   double maxcut(1.0);
   double d(maxcut-mincut);

   double nSig(getEntries(tSig, extracut, weightBranchSig));
   double nBkg(getEntries(tBkg, extracut, weightBranchBkg)); 

   double nSigLeft[n];
   double nBkgLeft[n];

   float FOM[n];
   float maxfom(0.0);

   int cutindex(0);
//   int trgSigEvt(97);
//   int trgBkgEvt(22781);

   double scalefacsig(0.0);
   double scalefacbkg(0.0);

//   bool fa=true;
   string scaling;


   if (fa==false)
   {
   scalefacsig=1.0;
   scalefacbkg=1.0;
   scaling = "NotScaled";
//   ontarget = "False"
   }
   else
   {
   scalefacsig = (double(trgSigEvt)/double(nSig));
   scalefacbkg = (double(trgBkgEvt)/double(nBkg));
   scaling = "Scaled";
//   ontarget = "True";
   }

   ofstream myfile;
   myfile.open (("BDTsummaryOneMinusBkg"+scaling+nameplot+".txt").c_str()); 

 //  float Punzi[n];
 //  float maxPunzi(0.0);


   for(int i(0); i<n; ++i)
   {

      FOM[i]=(scalefacsig*getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig ))/sqrt((scalefacbkg*getEntries( tBkg, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )) + (scalefacsig*getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )));
      cout<<"S/sqrt(S+B): "<<FOM[i]<<endl;
 //     myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
	      if (FOM[i]>maxfom)
		{
		maxfom=FOM[i];
                cutindex=i;            
		}
      nSigLeft[i] = getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )*scalefacsig;
      nBkgLeft[i] = getEntries( tBkg, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )*scalefacbkg;
      sigEff[i] = getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )/nSig;
      bkgRej[i] = 1.0-(getEntries( tBkg, extracut+" && "+bdtvar + " < " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )/nBkg);
      cout<<"Index of cut: "<<i<<" Sig Eff: "<<sigEff[i]<<" 1.0 - Bkg Rej: "<<bkgRej[i]<<" Nsigleft: "<<nSigLeft[i]<<" Nbkgleft: "<<nBkgLeft[i]<<" mincut: "<<d2s(mincut+(i/(1.*n))*d)<<endl;
   }

   double plan = maxfom+10.0;

//    for(int i(0); i<n; ++i)
//    {
//    myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
//    }
   
   TH2F *myfom = new TH2F("S/sqrt(S+B)", "myfom",100, mincut, maxcut, 100 , 0.0, plan);
   TCanvas e("together", "together", 600, 600);
   myfom->SetTitle(("FOM_with_SIGfile:"+fsigname).c_str());
   myfom->GetXaxis()->SetTitle("BDT output");
   myfom->GetYaxis()->SetTitle("FOM:S/sqrt(S+B)");
   myfom->GetYaxis()->SetTitleOffset(1.25);
   
   for(int i(0); i<n; ++i)
    {
    myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
    }

  
   
   myfom->Draw("COL");
   e.Print(("FOM_SAlly_OneMinusBkg_"+scaling+nameplot+".pdf").c_str());

   TH2F *myroc = new TH2F("My roc curve", "My roc curve",100, 0.0, 1.0, 100 , 0.0, 1.0);
   TCanvas f("togethe", "togethe", 600, 600);
   myroc->SetTitle(("Roc Curve_with_SIGfile:"+fsigname).c_str());
   myroc->GetXaxis()->SetTitle("Signal efficiency");
   myroc->GetYaxis()->SetTitle("Background rejection");
   myroc->GetYaxis()->SetTitleOffset(1.25);

   for(int i(0); i<n; ++i)
    {
    myroc->Fill(sigEff[i],bkgRej[i]);
    }



   myroc->Draw("COL");
   f.Print(("ROC_Sally_OneMinusBkg_"+scaling+nameplot+".pdf").c_str());






   cout<<"NSig:"<<nSig<<endl;
   cout<<"NBkg:"<<nBkg<<endl;
   cout<<"Max FOM:"<<*std::max_element(FOM,FOM+n)<<endl;
   cout<<"Optimal cut:"<<(mincut+((cutindex-1)/(1.*n))*d)<<endl;
   cout<<"Index of cut:"<<cutindex<<" Sig Eff:"<<sigEff[cutindex]<<" Bkg Rej:"<<bkgRej[cutindex]<<" Nsigleft:"<<nSigLeft[cutindex]<<" Nbkgleft:"<<nBkgLeft[cutindex]<<endl;
   
   myfile<<"-------------------------BDT summary----------------------"<<endl;
   myfile<<""<<endl;
   myfile<<"Signal sample size:"<<nSig<<endl;
   myfile<<"Background sample size:"<<nBkg<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"Target On: "<< fa <<endl;
   myfile<<"Target signal size:"<<trgSigEvt<<endl;
   myfile<<"Target background size:"<<trgBkgEvt<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"Max FOM(S/sqrt(S+B)):"<<*std::max_element(FOM,FOM+n)<<endl;
   myfile<<"Optimal cut:"<<(mincut+((cutindex-1)/(1.*n))*d)<<endl;
   myfile<<"Min cut: "<<mincut<<"MaxCut: "<<maxcut<<endl;
   myfile<<"Index of cut"<<"---Sig Eff---"<<"---Bkg Rej---"<<"---Nsigleft---"<<"---Nbkgleft---"<<endl;
   myfile<<"-------"<<cutindex<<"-----"<<sigEff[cutindex]<<"-----"<<bkgRej[cutindex]<<"-----"<<nSigLeft[cutindex]<<"-----"<<nBkgLeft[cutindex]<<endl;
   myfile.close();
  



   fSig.Close();
   fBkg.Close();
   return true;
}
bool getOneRocCurveSallyDiffTraining(string pathnamesally, string fsigname,
   string fbkgname,
   string bdtvar, 
   string extracut,
   double sigEff[],
   double bkgRej[],
   unsigned int n,
   bool fa,
   int trgSigEvt,
   int trgBkgEvt,
   string nameplot,
   double mincut,
   double maxcut,
   string weightBranchSig,
   string weightBranchBkg
)

{
   TFile fSig((pathnamesally+"/"+fsigname).c_str());
   TTree* tSig = (TTree*)fSig.Get("DecayTree");
   TFile fBkg((pathnamesally+"/"+fbkgname).c_str());
   TTree* tBkg = (TTree*)fBkg.Get("DecayTree");

   if(tSig == 0 || tBkg == 0)
   {
      cout<<"ERROR in getOneRocCurve: could not get the tree"<<endl;
      fSig.Close();
      fBkg.Close();
      return false;
   }

   if(extracut == "") extracut = "1";

   if( -1 == tSig->GetEntries( (bdtvar + " > 0 && " + extracut).c_str()) || -1 ==  tBkg->GetEntries( (bdtvar + " > 0 && " + extracut).c_str()) )
   {
      cout<<"ERROR in getOneRocCurve: BDT var "<<bdtvar<<" not found, or problem with extracut"<<endl;
      fSig.Close();
      fBkg.Close();
      return false;
   }

//   double mincut(-0.0);
//   double maxcut(1.0);
   double d(maxcut-mincut);

   double nSig(getEntries(tSig, extracut, weightBranchSig));
   double nBkg(getEntries(tBkg, extracut, weightBranchBkg)); 

   double nSigLeft[n];
   double nBkgLeft[n];

   float FOM[n];
   float maxfom(0.0);

   int cutindex(0);
//   int trgSigEvt(97);
//   int trgBkgEvt(22781);

   double scalefacsig(0.0);
   double scalefacbkg(0.0);

//   bool fa=true;
   string scaling;


   if (fa==false)
   {
   scalefacsig=1.0;
   scalefacbkg=1.0;
   scaling = "NotScaled";
//   ontarget = "False"
   }
   else
   {
   scalefacsig = (double(trgSigEvt)/double(nSig));
   scalefacbkg = (double(trgBkgEvt)/double(nBkg));
   scaling = "Scaled";
//   ontarget = "True";
   }

   ofstream myfile;
   myfile.open (("BDTsummary"+scaling+nameplot+".txt").c_str()); 

 //  float Punzi[n];
 //  float maxPunzi(0.0);


   for(int i(0); i<n; ++i)
   {

      FOM[i]=(scalefacsig*getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig ))/sqrt((scalefacbkg*getEntries( tBkg, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )) + (scalefacsig*getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )));
      cout<<"S/sqrt(S+B): "<<FOM[i]<<endl;
 //     myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
	      if (FOM[i]>maxfom)
		{
		maxfom=FOM[i];
                cutindex=i;            
		}
      nSigLeft[i] = getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )*scalefacsig;
      nBkgLeft[i] = getEntries( tBkg, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )*scalefacbkg;
      sigEff[i] = getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )/nSig;
      bkgRej[i] = getEntries( tBkg, extracut+" && "+bdtvar + " < " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )/nBkg;
      cout<<"Index of cut: "<<i<<" Sig Eff: "<<sigEff[i]<<" Bkg Rej: "<<bkgRej[i]<<" Nsigleft: "<<nSigLeft[i]<<" Nbkgleft: "<<nBkgLeft[i]<<" mincut: "<<d2s(mincut+(i/(1.*n))*d)<<endl;
   }

   double plan = maxfom+10.0;

//    for(int i(0); i<n; ++i)
//    {
//    myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
//    }
   
   TH2F *myfom = new TH2F("S/sqrt(S+B)", "myfom",100, mincut, maxcut, 100 , 0.0, plan);
   TCanvas e("together", "together", 600, 600);
   myfom->SetTitle(("FOM_with_SIGfile:"+fsigname).c_str());
   myfom->GetXaxis()->SetTitle("BDT output");
   myfom->GetYaxis()->SetTitle("FOM:S/sqrt(S+B)");
   myfom->GetYaxis()->SetTitleOffset(1.25);
   
   for(int i(0); i<n; ++i)
    {
    myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
    }

  
   
   myfom->Draw("COL");
   e.Print(("FOM_SAlly"+scaling+nameplot+".pdf").c_str());

   TH2F *myroc = new TH2F("My roc curve", "My roc curve",100, 0.0, 1.0, 100 , 0.0, 1.0);
   TCanvas f("togethe", "togethe", 600, 600);
   myroc->SetTitle(("Roc Curve_with_SIGfile:"+fsigname).c_str());
   myroc->GetXaxis()->SetTitle("Signal efficiency");
   myroc->GetYaxis()->SetTitle("Background rejection");
   myroc->GetYaxis()->SetTitleOffset(1.25);

   for(int i(0); i<n; ++i)
    {
    myroc->Fill(sigEff[i],bkgRej[i]);
    }



   myroc->Draw("COL");
   f.Print(("ROC_Sally"+scaling+nameplot+".pdf").c_str());






   cout<<"NSig:"<<nSig<<endl;
   cout<<"NBkg:"<<nBkg<<endl;
   cout<<"Max FOM:"<<*std::max_element(FOM,FOM+n)<<endl;
   cout<<"Optimal cut:"<<(mincut+((cutindex-1)/(1.*n))*d)<<endl;
   cout<<"Index of cut:"<<cutindex<<" Sig Eff:"<<sigEff[cutindex]<<" Bkg Rej:"<<bkgRej[cutindex]<<" Nsigleft:"<<nSigLeft[cutindex]<<" Nbkgleft:"<<nBkgLeft[cutindex]<<endl;
   
   myfile<<"-------------------------BDT summary----------------------"<<endl;
   myfile<<""<<endl;
   myfile<<"Signal sample size:"<<nSig<<endl;
   myfile<<"Background sample size:"<<nBkg<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"Target On: "<< fa <<endl;
   myfile<<"Target signal size:"<<trgSigEvt<<endl;
   myfile<<"Target background size:"<<trgBkgEvt<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"Max FOM(S/sqrt(S+B)):"<<*std::max_element(FOM,FOM+n)<<endl;
   myfile<<"Optimal cut:"<<(mincut+((cutindex-1)/(1.*n))*d)<<endl;
   myfile<<"Min cut: "<<mincut<<"MaxCut: "<<maxcut<<endl;
   myfile<<"Index of cut"<<"---Sig Eff---"<<"---Bkg Rej---"<<"---Nsigleft---"<<"---Nbkgleft---"<<endl;
   myfile<<"-------"<<cutindex<<"-----"<<sigEff[cutindex]<<"-----"<<bkgRej[cutindex]<<"-----"<<nSigLeft[cutindex]<<"-----"<<nBkgLeft[cutindex]<<endl;
   myfile.close();
  



   fSig.Close();
   fBkg.Close();
   return true;
}





bool getOneRocCurveSally(string pathnamesally, string fsigname,
   string fbkgname,
   string bdtvar, 
   string extracut,
   double sigEff[],
   double bkgRej[],
   unsigned int n,
   bool fa,
   int trgSigEvt,
   int trgBkgEvt,
   string nameplot,
   double mincut,
   double maxcut,
   string weightBranchSig,
   string weightBranchBkg
)

{
   TFile fSig((pathnamesally+"/"+fsigname).c_str());
   TTree* tSig = (TTree*)fSig.Get("DecayTree");
   TFile fBkg((pathnamesally+"/"+fbkgname).c_str());
   TTree* tBkg = (TTree*)fBkg.Get("DecayTree");

   if(tSig == 0 || tBkg == 0)
   {
      cout<<"ERROR in getOneRocCurve: could not get the tree"<<endl;
      fSig.Close();
      fBkg.Close();
      return false;
   }

   if(extracut == "") extracut = "1";

   if( -1 == tSig->GetEntries( (bdtvar + " > 0 && " + extracut).c_str()) || -1 ==  tBkg->GetEntries( (bdtvar + " > 0 && " + extracut).c_str()) )
   {
      cout<<"ERROR in getOneRocCurve: BDT var "<<bdtvar<<" not found, or problem with extracut"<<endl;
      fSig.Close();
      fBkg.Close();
      return false;
   }

//   double mincut(-0.0);
//   double maxcut(1.0);
   double d(maxcut-mincut);

   double nSig(getEntries(tSig, extracut, weightBranchSig));
   double nBkg(getEntries(tBkg, extracut, weightBranchBkg)); 

   double nSigLeft[n];
   double nBkgLeft[n];

   float FOM[n];
   float maxfom(0.0);

   int cutindex(0);
//   int trgSigEvt(97);
//   int trgBkgEvt(22781);

   double scalefacsig(0.0);
   double scalefacbkg(0.0);

//   bool fa=true;
   string scaling;


   if (fa==false)
   {
   scalefacsig=1.0;
   scalefacbkg=1.0;
   scaling = "NotScaled";
//   ontarget = "False"
   }
   else
   {
   scalefacsig = (double(trgSigEvt)/double(nSig));
   scalefacbkg = (double(trgBkgEvt)/double(nBkg));
   scaling = "Scaled";
//   ontarget = "True";
   }

   ofstream myfile;
   myfile.open (("BDTsummary"+scaling+nameplot+".txt").c_str()); 

 //  float Punzi[n];
 //  float maxPunzi(0.0);


   for(int i(0); i<n; ++i)
   {

      FOM[i]=(scalefacsig*getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig ))/sqrt((scalefacbkg*getEntries( tBkg, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )) + (scalefacsig*getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )));
      cout<<"S/sqrt(S+B): "<<FOM[i]<<endl;
 //     myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
	      if (FOM[i]>maxfom)
		{
		maxfom=FOM[i];
                cutindex=i;            
		}
      nSigLeft[i] = getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )*scalefacsig;
      nBkgLeft[i] = getEntries( tBkg, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )*scalefacbkg;
      sigEff[i] = getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )/nSig;
      bkgRej[i] = getEntries( tBkg, extracut+" && "+bdtvar + " < " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )/nBkg;
      cout<<"Index of cut: "<<i<<" Sig Eff: "<<sigEff[i]<<" Bkg Rej: "<<bkgRej[i]<<" Nsigleft: "<<nSigLeft[i]<<" Nbkgleft: "<<nBkgLeft[i]<<" mincut: "<<d2s(mincut+(i/(1.*n))*d)<<endl;
   }

   double plan = maxfom+10.0;

//    for(int i(0); i<n; ++i)
//    {
//    myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
//    }
   
   TH2F *myfom = new TH2F("S/sqrt(S+B)", "myfom",100, mincut, maxcut, 100 , 0.0, plan);
   TCanvas e("together", "together", 600, 600);
   myfom->SetTitle(("FOM_with_SIGfile:"+fsigname).c_str());
   myfom->GetXaxis()->SetTitle("BDT output");
   myfom->GetYaxis()->SetTitle("FOM:S/sqrt(S+B)");
   myfom->GetYaxis()->SetTitleOffset(1.25);
   
   for(int i(0); i<n; ++i)
    {
    myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
    }

  
   
   myfom->Draw("COL");
   e.Print(("FOM_SAlly"+scaling+nameplot+".pdf").c_str());

   TH2F *myroc = new TH2F("My roc curve", "My roc curve",100, 0.0, 1.0, 100 , 0.0, 1.0);
   TCanvas f("togethe", "togethe", 600, 600);
   myroc->SetTitle(("Roc Curve_with_SIGfile:"+fsigname).c_str());
   myroc->GetXaxis()->SetTitle("Signal efficiency");
   myroc->GetYaxis()->SetTitle("Background rejection");
   myroc->GetYaxis()->SetTitleOffset(1.25);

   for(int i(0); i<n; ++i)
    {
    myroc->Fill(sigEff[i],bkgRej[i]);
    }



   myroc->Draw("COL");
   f.Print(("ROC_Sally"+scaling+nameplot+".pdf").c_str());






   cout<<"NSig:"<<nSig<<endl;
   cout<<"NBkg:"<<nBkg<<endl;
   cout<<"Max FOM:"<<*std::max_element(FOM,FOM+n)<<endl;
   cout<<"Optimal cut:"<<(mincut+((cutindex-1)/(1.*n))*d)<<endl;
   cout<<"Index of cut:"<<cutindex<<" Sig Eff:"<<sigEff[cutindex]<<" Bkg Rej:"<<bkgRej[cutindex]<<" Nsigleft:"<<nSigLeft[cutindex]<<" Nbkgleft:"<<nBkgLeft[cutindex]<<endl;
   
   myfile<<"-------------------------BDT summary----------------------"<<endl;
   myfile<<""<<endl;
   myfile<<"Signal sample size:"<<nSig<<endl;
   myfile<<"Background sample size:"<<nBkg<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"Target On: "<< fa <<endl;
   myfile<<"Target signal size:"<<trgSigEvt<<endl;
   myfile<<"Target background size:"<<trgBkgEvt<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"Max FOM(S/sqrt(S+B)):"<<*std::max_element(FOM,FOM+n)<<endl;
   myfile<<"Optimal cut:"<<(mincut+((cutindex-1)/(1.*n))*d)<<endl;
   myfile<<"Min cut: "<<mincut<<"MaxCut: "<<maxcut<<endl;
   myfile<<"Index of cut"<<"---Sig Eff---"<<"---Bkg Rej---"<<"---Nsigleft---"<<"---Nbkgleft---"<<endl;
   myfile<<"-------"<<cutindex<<"-----"<<sigEff[cutindex]<<"-----"<<bkgRej[cutindex]<<"-----"<<nSigLeft[cutindex]<<"-----"<<nBkgLeft[cutindex]<<endl;
   myfile.close();
  



   fSig.Close();
   fBkg.Close();
   return true;
}

bool getOneRocCurve(string fsigname,
   string fbkgname,
   string bdtvar, 
   string extracut,
   double sigEff[],
   double bkgRej[],
   unsigned int n,
   bool fa,
   int trgSigEvt,
   int trgBkgEvt,
   string nameplot,
   double mincut,
   double maxcut,
   string weightBranchSig,
   string weightBranchBkg
)

{
   TFile fSig(fsigname.c_str());
   TTree* tSig = (TTree*)fSig.Get("T");
   TFile fBkg(fbkgname.c_str());
   TTree* tBkg = (TTree*)fBkg.Get("T");

   if(tSig == 0 || tBkg == 0)
   {
      cout<<"ERROR in getOneRocCurve: could not get the tree"<<endl;
      fSig.Close();
      fBkg.Close();
      return false;
   }

   if(extracut == "") extracut = "1";

   if( -1 == tSig->GetEntries( (bdtvar + " > 0 && " + extracut).c_str()) || -1 ==  tBkg->GetEntries( (bdtvar + " > 0 && " + extracut).c_str()) )
   {
      cout<<"ERROR in getOneRocCurve: BDT var "<<bdtvar<<" not found, or problem with extracut"<<endl;
      fSig.Close();
      fBkg.Close();
      return false;
   }

//   double mincut(-0.0);
//   double maxcut(1.0);
   double d(maxcut-mincut);

   double nSig(getEntries(tSig, extracut, weightBranchSig));
   double nBkg(getEntries(tBkg, extracut, weightBranchBkg)); 

   double nSigLeft[n];
   double nBkgLeft[n];

   float FOM[n];
   float maxfom(0.0);

   int cutindex(0);
//   int trgSigEvt(97);
//   int trgBkgEvt(22781);

   double scalefacsig(0.0);
   double scalefacbkg(0.0);

//   bool fa=true;
   string scaling;


   if (fa==false)
   {
   scalefacsig=1.0;
   scalefacbkg=1.0;
   scaling = "NotScaled";
//   ontarget = "False"
   }
   else
   {
   scalefacsig = (double(trgSigEvt)/double(nSig));
   scalefacbkg = (double(trgBkgEvt)/double(nBkg));
   scaling = "Scaled";
//   ontarget = "True";
   }

   ofstream myfile;
   myfile.open (("BDTsummary"+scaling+nameplot+".txt").c_str()); 

 //  float Punzi[n];
 //  float maxPunzi(0.0);


   for(int i(0); i<n; ++i)
   {

      FOM[i]=(scalefacsig*getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig ))/sqrt((scalefacbkg*getEntries( tBkg, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )) + (scalefacsig*getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )));
      cout<<"S/sqrt(S+B): "<<FOM[i]<<endl;
 //     myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
	      if (FOM[i]>maxfom)
		{
		maxfom=FOM[i];
                cutindex=i;            
		}
      nSigLeft[i] = getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )*scalefacsig;
      nBkgLeft[i] = getEntries( tBkg, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )*scalefacbkg;
      sigEff[i] = getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )/nSig;
      bkgRej[i] = getEntries( tBkg, extracut+" && "+bdtvar + " < " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )/nBkg;
      cout<<"Index of cut: "<<i<<" Sig Eff: "<<sigEff[i]<<" Bkg Rej: "<<bkgRej[i]<<" Nsigleft: "<<nSigLeft[i]<<" Nbkgleft: "<<nBkgLeft[i]<<" mincut: "<<d2s(mincut+(i/(1.*n))*d)<<endl;
   }

   double plan = maxfom+10.0;

//    for(int i(0); i<n; ++i)
//    {
//    myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
//    }
   
   TH2F *myfom = new TH2F("S/sqrt(S+B)", "myfom",100, mincut, maxcut, 100 , 0.0, plan);
   TCanvas e("together", "together", 600, 600);
   myfom->SetTitle(("FOM_with_SIGfile:"+fsigname).c_str());
   myfom->GetXaxis()->SetTitle("BDT output");
   myfom->GetYaxis()->SetTitle("FOM:S/sqrt(S+B)");
   myfom->GetYaxis()->SetTitleOffset(1.25);
   
   for(int i(0); i<n; ++i)
    {
    myfom->Fill((mincut+(i/(1.*n))*d),FOM[i]);
    }

  
   
   myfom->Draw("COL");
   e.Print(("FOM_"+scaling+nameplot+".pdf").c_str());

   TH2F *myroc = new TH2F("My roc curve", "My roc curve",100, 0.0, 1.0, 100 , 0.0, 1.0);
   TCanvas f("togethe", "togethe", 600, 600);
   myroc->SetTitle(("Roc Curve_with_SIGfile:"+fsigname).c_str());
   myroc->GetXaxis()->SetTitle("Signal efficiency");
   myroc->GetYaxis()->SetTitle("Background rejection");
   myroc->GetYaxis()->SetTitleOffset(1.25);

   for(int i(0); i<n; ++i)
    {
    myroc->Fill(sigEff[i],bkgRej[i]);
    }



   myroc->Draw("COL");
   f.Print(("ROC_"+scaling+nameplot+".pdf").c_str());






   cout<<"NSig:"<<nSig<<endl;
   cout<<"NBkg:"<<nBkg<<endl;
   cout<<"Max FOM:"<<*std::max_element(FOM,FOM+n)<<endl;
   cout<<"Optimal cut:"<<(mincut+((cutindex-1)/(1.*n))*d)<<endl;
   cout<<"Index of cut:"<<cutindex<<" Sig Eff:"<<sigEff[cutindex]<<" Bkg Rej:"<<bkgRej[cutindex]<<" Nsigleft:"<<nSigLeft[cutindex]<<" Nbkgleft:"<<nBkgLeft[cutindex]<<endl;
   
   myfile<<"-------------------------BDT summary----------------------"<<endl;
   myfile<<""<<endl;
   myfile<<"Signal sample size:"<<nSig<<endl;
   myfile<<"Background sample size:"<<nBkg<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"Target On: "<< fa <<endl;
   myfile<<"Target signal size:"<<trgSigEvt<<endl;
   myfile<<"Target background size:"<<trgBkgEvt<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"-----------------------------------------------------------"<<endl;
   myfile<<"Max FOM(S/sqrt(S+B)):"<<*std::max_element(FOM,FOM+n)<<endl;
   myfile<<"Optimal cut:"<<(mincut+((cutindex-1)/(1.*n))*d)<<endl;
   myfile<<"Min cut: "<<mincut<<"MaxCut: "<<maxcut<<endl;
   myfile<<"Index of cut"<<"---Sig Eff---"<<"---Bkg Rej---"<<"---Nsigleft---"<<"---Nbkgleft---"<<endl;
   myfile<<"-------"<<cutindex<<"-----"<<sigEff[cutindex]<<"-----"<<bkgRej[cutindex]<<"-----"<<nSigLeft[cutindex]<<"-----"<<nBkgLeft[cutindex]<<endl;
   myfile.close();
  



   fSig.Close();
   fBkg.Close();
   return true;
}


void plotRocCurvesPunzi(string fsigname,
      string fbkgname,
      vector<string> bdtvars,
      string outputfilename,
      string extracut,
      bool fa,
      int trgSigEvt,
      int trgBkgEvt,
      string nameplot,
      double mincut,
      double maxcut,
      string punzi,
      string weightBranchSig,
      string weightBranchBkg
      )
{
   unsigned int n(300);
//  bool fa=false;
//   double maxCut(1.0);
   double sigEff[n];
   double bkgRej[n];
  
   string scale=bool_cast(fa);
  
   vector<TGraph*> vec;

   TCanvas cROC("cROC", "cROC", 600, 600);
   TH1F* frame;
   frame = cROC.DrawFrame(0,0,1,1);
   frame->SetTitle("ROC Curve");
   frame->GetXaxis()->SetTitle("Signal Efficiency");
   frame->GetYaxis()->SetTitle("Background Rejection");
    
//   TLegend leg(0.1,0.1,0.4,0.4);
   int j(0);

   for(int i(0); i < bdtvars.size(); ++i)
   {
      if(getOneRocCurvePunzi(fsigname, fbkgname, bdtvars[i], extracut, sigEff, bkgRej, n, fa, trgSigEvt, trgBkgEvt, nameplot, mincut, maxcut, punzi, weightBranchSig, weightBranchBkg))

      {
         vec.push_back(new TGraph(n, sigEff, bkgRej));

         cout<<"In ROC curve: "<<sigEff[50]<<" "<<bkgRej[50]<<endl;

         j = vec.size()-1;         

         vec[j] -> SetLineColor(j+1);
         vec[j] -> SetLineWidth(2);
         cROC.cd();
         vec[j] -> Draw("L");
//         leg.AddEntry(vec[j] , (bdtvars[i]).c_str(), "L");
      }
   }

   cROC.cd();
//   leg.Draw();
   cROC.Print((scale+punzi+"_"+outputfilename).c_str());

   for(int i(0); i<vec.size(); ++i) delete vec[i];
}





void plotRocCurves(string fsigname,
      string fbkgname,
      vector<string> bdtvars,
      string outputfilename,
      string extracut,
      bool fa,
      int trgSigEvt,
      int trgBkgEvt,
      string nameplot,
      double mincut,
      double maxcut,
      string weightBranchSig,
      string weightBranchBkg
      )
{
   unsigned int n(300);
//  bool fa=false;
//   double maxCut(1.0);
   double sigEff[n];
   double bkgRej[n];
  
   string scale=bool_cast(fa);
  
   vector<TGraph*> vec;

   TCanvas cROC("cROC", "cROC", 600, 600);
   TH1F* frame;
   frame = cROC.DrawFrame(0,0,1,1);
   frame->GetXaxis()->SetTitle("Signal Efficiency");
   frame->GetYaxis()->SetTitle("Background Rejection");
    
   TLegend leg(0.1,0.1,0.4,0.4);
   int j(0);

   for(int i(0); i < bdtvars.size(); ++i)
   {
      if(getOneRocCurve(fsigname, fbkgname, bdtvars[i], extracut, sigEff, bkgRej, n, fa, trgSigEvt, trgBkgEvt ,nameplot, mincut, maxcut, weightBranchSig, weightBranchBkg))

      {
         vec.push_back(new TGraph(n, sigEff, bkgRej));

         cout<<"In ROC curve: "<<sigEff[50]<<" "<<bkgRej[50]<<endl;

         j = vec.size()-1;         

         vec[j] -> SetLineColor(j+1);
         vec[j] -> SetLineWidth(2);
         cROC.cd();
         vec[j] -> Draw("L");
         leg.AddEntry(vec[j] , (bdtvars[i]).c_str(), "L");
      }
   }

   cROC.cd();
   leg.Draw();
   cROC.Print((scale+"_"+outputfilename).c_str());

   for(int i(0); i<vec.size(); ++i) delete vec[i];
}


void plotRocCurvesSally(string pathnamesally,string fsigname,
      string fbkgname,
      vector<string> bdtvars,
      string outputfilename,
      string extracut,
      bool fa,
      int trgSigEvt,
      int trgBkgEvt,
      string nameplot,
      double mincut,
      double maxcut,
      string weightBranchSig,
      string weightBranchBkg
      )
{
   unsigned int n(300);
//  bool fa=false;
//   double maxCut(1.0);
   double sigEff[n];
   double bkgRej[n];
  
   string scale=bool_cast(fa);
  
   vector<TGraph*> vec;

   TCanvas cROC("cROC", "cROC", 600, 600);
   TH1F* frame;
   frame = cROC.DrawFrame(0,0,1,1);
   frame->GetXaxis()->SetTitle("Signal Efficiency");
   frame->GetYaxis()->SetTitle("Background Rejection");
    
   TLegend leg(0.1,0.1,0.4,0.4);
   int j(0);

   for(int i(0); i < bdtvars.size(); ++i)
   {
      if(getOneRocCurveSally(pathnamesally, fsigname, fbkgname, bdtvars[i], extracut, sigEff, bkgRej, n, fa, trgSigEvt, trgBkgEvt ,nameplot, mincut, maxcut, weightBranchSig, weightBranchBkg))

      {
         vec.push_back(new TGraph(n, sigEff, bkgRej));

         cout<<"In ROC curve: "<<sigEff[50]<<" "<<bkgRej[50]<<endl;

         j = vec.size()-1;         

         vec[j] -> SetLineColor(j+1);
         vec[j] -> SetLineWidth(2);
         cROC.cd();
         vec[j] -> Draw("L");
         leg.AddEntry(vec[j] , (bdtvars[i]).c_str(), "L");
      }
   }

   cROC.cd();
   leg.Draw();
   cROC.Print((scale+"_"+outputfilename).c_str());

   for(int i(0); i<vec.size(); ++i) delete vec[i];
}

void plotRocCurvesSallyCompareDiffTraining(vector<string> pathnamesally,vector<string> condition,vector<string> fsigname,
      vector<string> fbkgname,
      vector<string> bdtvar,
      string outputfilename,
      string extracut,
      bool fa,
      int trgSigEvt,
      int trgBkgEvt,
      string nameplot,
      double mincut,
      double maxcut,
      string weightBranchSig,
      string weightBranchBkg
      )
{
   unsigned int n(300);
//  bool fa=false;
//   double maxCut(1.0);
   double sigEff[n];
   double bkgRej[n];
  
   string scale=bool_cast(fa);
  
   vector<TGraph*> vec;

   TCanvas cROC("cROC", "cROC", 600, 600);
   TH1F* frame;
   frame = cROC.DrawFrame(0,0,1,1);
   frame->GetXaxis()->SetTitle("Signal Efficiency");
   frame->GetYaxis()->SetTitle("Background Rejection");
    
   TLegend leg(0.1,0.1,0.4,0.4);
   int j(0);

   for(int i(0); i < fsigname.size(); ++i)
   {
      if(getOneRocCurveSallyDiffTraining(pathnamesally[i], fsigname[i], fbkgname[i], bdtvar[i], extracut, sigEff, bkgRej, n, fa, trgSigEvt, trgBkgEvt ,nameplot, mincut, maxcut, weightBranchSig, weightBranchBkg))

      {
         vec.push_back(new TGraph(n, sigEff, bkgRej));

         cout<<"In ROC curve: "<<sigEff[50]<<" "<<bkgRej[50]<<endl;

         j = vec.size()-1;         

         vec[j] -> SetLineColor(j+1);
         vec[j] -> SetLineWidth(2);
         cROC.cd();
         vec[j] -> Draw("L");
         leg.AddEntry(vec[j] , (condition[i]).c_str(), "L");
      }
   }

   cROC.cd();
   leg.Draw();
   cROC.Print((scale+outputfilename+"_COMPAREroccurvesDIFFERENTtrainings.pdf").c_str());

   for(int i(0); i<vec.size(); ++i) delete vec[i];
}

void plotRocCurvesSallyCompareDiffTrainingOneMinusBkgRej(vector<string> pathnamesally,vector<string> condition,vector<string> fsigname,
      vector<string> fbkgname,
      vector<string> bdtvar,
      string outputfilename,
      string extracut,
      bool fa,
      int trgSigEvt,
      int trgBkgEvt,
      string nameplot,
      double mincut,
      double maxcut,
      string weightBranchSig,
      string weightBranchBkg
      )
{
   unsigned int n(300);
//  bool fa=false;
//   double maxCut(1.0);
   double sigEff[n];
   double bkgRej[n];
  
   string scale=bool_cast(fa);
  
   vector<TGraph*> vec;

   TCanvas cROC("cROC", "cROC", 600, 600);
   
   TH1F* frame;
   frame = cROC.DrawFrame(0,0,1,0.015);
   frame->GetXaxis()->SetTitle("Signal Efficiency");
   frame->GetYaxis()->SetTitle("1-Background Rejection");
     
 
   TLegend leg(0.1,0.6,0.4,0.9);
   int j(0);

   for(int i(0); i < fsigname.size(); ++i)
   {
      if(getOneRocCurveSallyDiffTrainingOneMinBkgRej(pathnamesally[i], fsigname[i], fbkgname[i], bdtvar[i], extracut, sigEff, bkgRej, n, fa, trgSigEvt, trgBkgEvt ,nameplot, mincut, maxcut, weightBranchSig, weightBranchBkg))
        
      {
         vec.push_back(new TGraph(n, sigEff, bkgRej));

         cout<<"In ROC curve: "<<sigEff[50]<<" "<<bkgRej[50]<<endl;

         j = vec.size()-1;         

         vec[j] -> SetLineColor(j+1);
         vec[j] -> SetLineWidth(2);
         cROC.cd();
         vec[j] -> Draw("L");
         leg.AddEntry(vec[j] , (condition[i]).c_str(), "L");
      }
   }

   cROC.cd();
//   cROC.SetLogy();
//   cROC.Update();
   leg.Draw();
   cROC.Print((scale+outputfilename+"_COMPAREroccurvesDIFFERENTtrainings_ONEminusBKGRej.pdf").c_str());

   for(int i(0); i<vec.size(); ++i) delete vec[i];
}



void plotRocCurvesSallyCompare(string pathnamesally,vector<string> condition,vector<string> fsigname,
      vector<string> fbkgname,
      string bdtvar,
      string outputfilename,
      string extracut,
      bool fa,
      int trgSigEvt,
      int trgBkgEvt,
      string nameplot,
      double mincut,
      double maxcut,
      string weightBranchSig,
      string weightBranchBkg
      )
{
   unsigned int n(300);
//  bool fa=false;
//   double maxCut(1.0);
   double sigEff[n];
   double bkgRej[n];
  
   string scale=bool_cast(fa);
  
   vector<TGraph*> vec;

   TCanvas cROC("cROC", "cROC", 600, 600);
   TH1F* frame;
   frame = cROC.DrawFrame(0,0,1,1);
   frame->GetXaxis()->SetTitle("Signal Efficiency");
   frame->GetYaxis()->SetTitle("Background Rejection");
    
   TLegend leg(0.1,0.1,0.4,0.4);
   int j(0);

   for(int i(0); i < fsigname.size(); ++i)
   {
      if(getOneRocCurveSally(pathnamesally, fsigname[i], fbkgname[i], bdtvar, extracut, sigEff, bkgRej, n, fa, trgSigEvt, trgBkgEvt ,nameplot, mincut, maxcut, weightBranchSig, weightBranchBkg))

      {
         vec.push_back(new TGraph(n, sigEff, bkgRej));

         cout<<"In ROC curve: "<<sigEff[50]<<" "<<bkgRej[50]<<endl;

         j = vec.size()-1;         

         vec[j] -> SetLineColor(j+1);
         vec[j] -> SetLineWidth(2);
         cROC.cd();
         vec[j] -> Draw("L");
         leg.AddEntry(vec[j] , (condition[i]).c_str(), "L");
      }
   }

   cROC.cd();
   leg.Draw();
   cROC.Print((scale+outputfilename+"_COMPAREroccurves.pdf").c_str());

   for(int i(0); i<vec.size(); ++i) delete vec[i];
}
//void cutTree(string nametree, string decaytreename, string namecuttree, string cuts)
//{
//   TFile f(nametree.c_str());
//   TTree* t = (TTree*)f.Get(decaytreename.c_str());
//
//   TFile f2(namecuttree.c_str(), "RECREATE");
//   TTree* t2 = t->CloneTree(0);
//
//   TTreeFormula ttf("ttf", cuts.c_str(), t);
//
//   cout<<"Cutting tree "<<nametree<<endl;
//   cout<<"Cut applied: "<<cuts<<endl;
//
//   for(int i(0); i<t->GetEntries(); ++i)
//   {
//      if(i % (t->GetEntries()/10) == 0) cout<<100*i/(t->GetEntries())<<" \% processed"<<endl;
//      t->GetEntry(i);
//      if(ttf.EvalInstance()) t2->Fill();
//   }
//
//   double effofcut;
//   effofcut = double(t2->GetEntries())/double(t->GetEntries());
//   cout<<"Efficiency of cut"<< cuts << " wrt " << nametree << " is: " << effofcut << endl;
//
//   t2->Write("",TObject::kOverwrite);
//   f2.Close();
//   f.Close();
//}





void plotOverTraining(
      KFolder kf,
      string outputFileName,
      string BDTName,
      string BDTBranch,
      string weightBranch,
      string pathname,
      double minbdtvar,
      double maxbdtvar,
      string namesigfile,
      string namebkgfile
      )
{
   int nFolds(kf.getNFolds());
   double wTrain(1./(1.*(nFolds-1)));
   TH1F *hsigtest = new TH1F("hsigtest", "hsigtest", 40, minbdtvar, maxbdtvar);
   TH1F hbkgtest("hbkgtest", "hbkgtest", 40, minbdtvar, maxbdtvar); 
   TH1F hsigtrain("hsigtrain", "hsigtrain", 40, minbdtvar, maxbdtvar);
   TH1F hbkgtrain("hbkgtrain", "hbkgtrain", 40, minbdtvar, maxbdtvar); 

   TFile *F = new TFile((namesigfile).c_str(),"RECREATE");
   TTree *T = new TTree("T","test");

   TFile *L = new TFile((namebkgfile).c_str(),"RECREATE");
   TTree *M = new TTree("T","test");
  

   float BDTTest, BDTTrain;
//   float la=2.0;
   TBranch *tbr1 = T->Branch("sig", &BDTTest, "BDTTest/F");
   TBranch *tbr2 = M->Branch("bkg", &BDTTest, "BDTTest/F");
   TBranch *tbr3 = T->Branch("bdtvar2", &BDTTest, "BDTTest/F");
   TBranch *tbr4 = M->Branch("bdtvar2", &BDTTest, "BDTTest/F");



   TH2F curve("curve", "curve", 40, -0.0, 1.0, 40, -0.0, 1000);

   hsigtest->Sumw2();
   hbkgtest.Sumw2();
   hsigtrain.Sumw2();
   hbkgtrain.Sumw2();

   unsigned int foundTrain(0);
   unsigned int foundTest(1);

   for(int i(0); i<nFolds; ++i)
   {
//      TFile f( (kf.getOutFileName() + "TMVA_fold_" + i2s(i) + ".root").c_str());
//   TFile *F = new TFile("test.root","RECREATE");
//   TTree *T = new TTree("T","test");

//   float la=2.0;
//   TBranch *tbr1 = T->Branch("sig","TH1F",&hsigtest);
//   TBranch *tbr2 = T->Branch("bkg","TH1F",&hbkgtest);
//   T->Fill();
//   T->Print();
//   T->Write();
//   F->Close();
     cout<<"CORSSSSSSS CHEEECCCCCKKKKK"<<endl;
     cout<<(pathname+BDTName+"TMVA_fold_" + i2s(i) + ".root").c_str()<<endl;
     

      TFile f((pathname+BDTName+"TMVA_fold_" + i2s(i) + ".root").c_str());

      TTree* ttest = (TTree*)f.Get("TestTree");
      TTree* ttrain = (TTree*)f.Get("TrainTree");
      if(ttest == 0 || ttrain == 0)
      {
         cout<<"ERROR in plotOverTraining: tree not found"<<endl;
         f.Close();
         return;
      }
      int classIDTest, classIDTrain;
//      float BDTTest, BDTTrain;
//
     
      ttest->SetBranchStatus("*",0);
      ttest->SetBranchStatus("classID", 1);
      ttest->SetBranchStatus( (BDTBranch+"_fold_"+i2s(i)).c_str(), 1, &foundTrain);
      ttrain->SetBranchStatus("*",0);
      ttrain->SetBranchStatus("classID", 1);
      ttrain->SetBranchStatus((BDTBranch+"_fold_"+i2s(i)).c_str(), 1, &foundTest);

      if(foundTrain == 0 || foundTest == 0)
      {
         cout<<"ERROR in plotOverTraining: "<<BDTBranch<<" not found"<<endl;
         f.Close();
         return; 
      }

      ttest->SetBranchAddress((BDTBranch+"_fold_"+i2s(i)).c_str(), &BDTTest);
      ttrain->SetBranchAddress((BDTBranch+"_fold_"+i2s(i)).c_str(), &BDTTrain);
      ttest->SetBranchAddress("classID", &classIDTest);
      ttrain->SetBranchAddress("classID", &classIDTrain);

      if(weightBranch == "") weightBranch = "1";
      if(weightBranch != "1")
      {
          setBranchStatusTTF(ttest, weightBranch); 
          setBranchStatusTTF(ttrain, weightBranch); 
      }
      TTreeFormula ttfWeightTest("ttfWeightTest", weightBranch.c_str(), ttest);
      TTreeFormula ttfWeightTrain("ttfWeightTrain", weightBranch.c_str(), ttrain);

      double w(0);
   
      cout<<"test entries: "<<ttest->GetEntries()<<endl;
      cout<<"train entries: "<<ttrain->GetEntries()<<endl;
      


      for(int i(0); i<ttest->GetEntries(); ++i)
      {
       //  RevBDT_fold_0  
         cout<<BDTTest<<"BDTTest"<<endl;
         ttest->GetEntry(i);
         w = ttfWeightTest.EvalInstance();
         if(classIDTest == 0)
         {
	 hsigtest->Fill(BDTTest, w);
         curve.Fill(BDTTest,1.0,w);
         cout<<BDTTest<<"BDTTest"<<endl;
         T->Fill();
	 }
         if(classIDTest == 1)
	 {
	 hbkgtest.Fill(BDTTest, w);
         curve.Fill(BDTTest,1.0, w);
         M->Fill();
         
	 }
      }
      

      for(int i(0); i<ttrain->GetEntries(); ++i)
      {
         ttrain->GetEntry(i);
         w = ttfWeightTrain.EvalInstance();
//         cout<<"This is w:"<<w<<endl;
//         cout<<"This is BDTTrain:"<<BDTTrain<<endl;
         if(classIDTrain == 0) hsigtrain.Fill(BDTTrain, w);
         if(classIDTrain == 1) hbkgtrain.Fill(BDTTrain, w);
      }
   
}

   T->Print();
   M->Print();
   
   F->Write();
   F->Close();
   L->Write();
   L->Close();

   //gStyle->SetOptStat(0);

   cout<<"Integral background train"<<(hbkgtrain.Integral())<<endl;
   cout<<"Integral signal train"<<(hsigtrain.Integral())<<endl;
   cout<<"Integral test bkg"<<(hbkgtest.Integral())<<endl;
   cout<<"Integral test sig"<<(hsigtest->Integral())<<endl; 


   hsigtest->Scale(1./hsigtest->Integral());
   hsigtrain.Scale(1./hsigtrain.Integral());
   hbkgtest.Scale(1./hbkgtest.Integral());
   hbkgtrain.Scale(1./hbkgtrain.Integral());

   hsigtrain.SetMarkerColor(2);
   hsigtrain.SetMarkerStyle(10);
   hsigtrain.SetLineColor(2);
   hsigtrain.SetLineWidth(2);

   hbkgtrain.SetMarkerColor(4);
   hbkgtrain.SetMarkerStyle(10);
   hbkgtrain.SetLineWidth(2);

   hsigtest->SetLineColor(2);
   hsigtest->SetLineWidth(2);
   hsigtest->SetFillColor(2);
   hsigtest->SetFillStyle(3365);

   hbkgtest.SetLineWidth(2);
   hbkgtest.SetFillColor(4);
   hbkgtest.SetFillStyle(3365);

   TCanvas c("cOverTraining", "cOverTraining", 600, 600);  

   hbkgtest.SetTitle("Overtraining");
   hbkgtest.GetXaxis()->SetTitle("BDT output");
   hbkgtest.GetYaxis()->SetTitle("# Events (normalised)");
   hbkgtest.GetYaxis()->SetTitleOffset(1.25);

   c.SetLogy();
   
   hbkgtest.Draw("hist");
   hsigtest->Draw("histsame");
  
   hsigtrain.Draw("E1Psame");
   hbkgtrain.Draw("E1Psame");

   c.Print(outputFileName.c_str());

   TCanvas d("together", "together", 600, 600);

   curve.GetXaxis()->SetTitle("BDT output");
   curve.GetYaxis()->SetTitle("# Events (normalised)");
   curve.GetYaxis()->SetTitleOffset(1.25);

   curve.Draw("hist");
//   hsigtest.Draw("histsame");

//   hsigtrain.Draw("E1Psame");
//   hbkgtrain.Draw("E1Psame");

//   d.Print("curve.eps");  

}
