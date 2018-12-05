#include "usefulFunctions.h"
#include "TH2I.h"
#include "THStack.h"
#include "TObjArray.h"
#include "TLegend.h"





double getCorrelationCoefficient(TTree*& t, string var1name, string var2name, string cuts, bool draw, string filename)
{
   TH2F th2f("th2f", "th2f", 50,-1e5,1e5,50,-1e5,1e5);

   double var1min(-3);
   double var1max(-3);
   double var2min(-3);
   double var2max(-3);

   bool isSeparable1;
   bool isSeparable2;

   t->SetBranchStatus("*",0);
   if(cuts != "") setBranchStatusTTF(t, cuts);
   if(cuts == "") cuts = "1";

   isSeparable1 = separateString(var1name, var1min, var1max);
   isSeparable2 = separateString(var2name, var2min, var2max);

   if(!isSeparable1 && !isSeparable2) th2f.SetCanExtend(TH1::kAllAxes);
   if(!isSeparable1 && isSeparable2)

   {
      if(draw) th2f.SetBins(50, -1e5, 1e5, 50, var2min, var2max);
      if(draw) th2f.SetCanExtend(TH1::kXaxis);
      cuts += (" && " + var2name + " > " + d2s(var2min) + " && " + var2name + " < " + d2s(var2max));
   }
   if(isSeparable1 && !isSeparable2)
   {
      if(draw) th2f.SetBins(50, var1min, var1max, 50, -1e5, 1e5);
      if(draw) th2f.SetCanExtend(TH1::kYaxis);
      cuts += (" && " + var1name + " > " + d2s(var1min) + " && " + var1name + " < " + d2s(var1max));
   }
   if(isSeparable1 && isSeparable2)
   {
      if(draw) th2f.SetBins(50, var1min, var1max, 50, var2min, var2max);
            cuts += (" && " + var2name + " > " + d2s(var2min) + " && " + var2name + " < " + d2s(var2max));
      cuts += (" && " + var1name + " > " + d2s(var1min) + " && " + var1name + " < " + d2s(var1max));
   }


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
         cuts += (" && " + var2name + " > " + d2s(var2min) + " && " + var2name + " < " + d2s(var2max));
      cuts += (" && " + var1name + " > " + d2s(var1min) + " && " + var1name + " < " + d2s(var1max));
   }

   double sumx(0);
   double sumy(0);
   double sumxy(0);
   double sumxx(0);
   double sumyy(0);
   double var1(0);
   double var2(0);
   double tot(0);

   TTreeFormula* ttf = new TTreeFormula("ttf", cuts.c_str(), t);
   TTreeFormula* var1ttf = new TTreeFormula("var1ttf", var1name.c_str(), t);
   TTreeFormula* var2ttf = new TTreeFormula("var2ttf", var2name.c_str(), t);

   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      if(ttf->EvalInstance())
      {
         var1 = var1ttf->EvalInstance();
         var2 = var2ttf->EvalInstance();
         sumx += var1;
         sumy += var2;
         sumxy += var1*var2;
         sumxx += var1*var1;
         sumyy += var2*var2;
         tot += 1;
         if(draw) th2f.Fill(var1, var2);
      }
   }

   if(draw)
   {
      TCanvas canv("canv2", "canv2", 600, 600);
      th2f.GetXaxis()->SetTitle(var1name.c_str());
      th2f.GetYaxis()->SetTitle(var2name.c_str());
      th2f.SetTitle(( var1name+"_vs_"+var2name).c_str());
      th2f.Draw("colz");
      canv.Print( (filename+cleanNameString(var1name+"_vs_"+var2name)+".pdf").c_str());
   }

   double correl = (sumxy - sumx*sumy/tot )/ sqrt( (sumxx -sumx*sumx/tot )*(sumyy - sumy*sumy/tot ) );

   t->SetBranchStatus("*",1);
   delete ttf;
   delete var1ttf;
   delete var2ttf;
   if(correl != correl)
   {
      cout<<"WARNING: for variables "<<var1name<<" and "<<var2name<<", correlation coef is nan. Return 1.02"<<endl;
      correl = 1.02;
   }
   return correl;
}
 

