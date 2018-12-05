#include "usefulFunctions.h"
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

//
double s2d(string str)
{
   double ret;
   istringstream is(str);
   is >> ret;
   return ret;
}
//
//


using namespace std;
 
string d2s(double d)
{
   string ret;
   ostringstream os;
   os<<d;
   return os.str();
}
//
//string i2s(int i)
//{
//   string ret;
//   ostringstream os;
//   os<<i;
//   return os.str();
//}
//
//vector<string> loadList(ifstream& inf)
//{
//   vector<string> ret;
//   string stock;
//   while(!inf.eof())
//   {
//      getline(inf, stock);
//      if(stock != "" && stock != " " && stock.find("#") == string::npos) ret.push_back(stock);
//   }
//   return ret;
//}
//
////void addVarKFold(KFolder& kf, string spectatorList, string trainingList)
////{
////   ifstream iSpec(spectatorList.c_str());
////   ifstream iTrain(trainingList.c_str());
//
////   if(iSpec.fail())
////   {
////      cerr<<"ERROR in addVarKFold: impossible to read file "<<spectatorList<<endl;
////      return;
////   }
////   if(iTrain.fail())
////   {
////      cerr<<"ERROR in addVarKFold: impossible to read file "<<trainingList<<endl;
////      return;
////   }
//
////   vector<string> vecSpec(loadList(iSpec));
////   vector<string> vecTrain(loadList(iTrain));
//
/////   for(int i(0); i<vecSpec.size(); ++i) kf.addSpectatorVar(vecSpec[i]);
////   for(int i(0); i<vecTrain.size(); ++i) kf.addTrainingVar(vecTrain[i]);
////}
//
double getEntries(string filename, string cut, string weightName)
{
   TFile f(filename.c_str());
   TTree* t = (TTree*)f.Get("DecayTree");
   double ret;
//   cout<<"Rock"<<endl;
   ret = getEntries(t, cut, weightName);
   f.Close();
   return ret;
}
//
double getEntries(TTree* t, string cut, string weightName)
{
//   cout<<"Party"<<endl;
//   cout<<"Cut in Get entries: "<<cut<<endl;
   if(cut == "") cut = "1";
   if(weightName == "") 
   {
   cout<<t->GetEntries(cut.c_str())<<endl;
   return t->GetEntries(cut.c_str());
   }
   t->SetBranchStatus("*", 0);
   setBranchStatusTTF(t, cut);
   double w(0);
   double sumW(0);
   t->SetBranchStatus(weightName.c_str(),1);
   t->SetBranchAddress(weightName.c_str(), &w);
   TTreeFormula ttf("ttf", cut.c_str(), t);

   for(int i(0); i<t->GetEntries(); ++i)
   {
     t->GetEntry(i);
     if(ttf.EvalInstance()) sumW+=w;     
//     cout<<"SumW:"<<sumW;
//     cout<<"W:"<<w;
   }

//   cout<<"SumW:"<<sumW;
//   cout<<"W:"<<w;
   t->SetBranchStatus("*", 1);
//   cout<<"SumW:"<<sumW<<endl;
//   cout<<"W:"<<w<<endl;
   return sumW;
  }
//
////void plotOneVariable(vector<string> const& filenames, string varname, string outputdirname, int nbin, string cut)
//void plotOneVariable(vector<string> const& filenames,
//      string varname,
//      string outputname,
//      int nbin,
//      string cut,
//      vector<string> weightExpressions,
//      string outputlegname,
//      vector<string> legEntries)
//{
//   unsigned int n(filenames.size());
//   if(n==0) return;
//
//   vector<TFile*> vecf(n);
//   vector<TTree*> vect(n);
//
//   for(unsigned int i(0); i<n; ++i)
//   {
//      vecf[i] = new TFile(filenames[i].c_str());
//      vect[i] = (TTree*)vecf[i]->Get("B2KstarTauMu_Tuple/DecayTree");
//   }
//
//   TH1F* htemp;
//   TAxis* axis;
//
//   TCanvas tc("tc", "tc", 600, 600);
//
//   double max(0);
//   double min(0);
//
//   if(!separateString(varname, min, max))
//   {
//      double maxima[n];
//      double minima[n];
//      for(unsigned int i(0); i<n; ++i)
//      {
//         tc.cd();
//         if(-1 != vect[i] -> Draw(varname.c_str(), cut.c_str()))
//         {
//            htemp = (TH1F*)gPad->GetPrimitive("htemp");
//            if(htemp == 0)
//            {
//               cout<<"Warning: in plotonevariable: could not get a histogram (tree "<<i<<" )"<<endl;
//             //  for(unsigned int i(0); i<n; ++i)
//             //  {
//             //     vecf[i]->Close();
//             //     delete vecf[i];
//             //  }
//             //  return;
//               maxima[i] = -1e10;
//               minima[i] = 1e10;
//            }
//            else
//            {
//               maxima[i] = htemp->GetXaxis()->GetXmax();
//               minima[i] = htemp->GetXaxis()->GetXmin();
//            }
//         }
//         else
//         {
//            cout<<"Warning: in plotonevariable: "<<varname<<" not found, plot aborted"<<endl;
//            for(unsigned int i(0); i<n; ++i)
//            {
//               vecf[i]->Close();
//               delete vecf[i];
//            }
//            return;
//         }
//      }
//
//      max = *max_element(maxima, maxima+n);
//      min = *min_element(minima, minima+n); 
//   }
//
//   string canvname(cleanNameString(varname));
//   if(canvname.size() > 50) canvname = canvname.substr(0,50);
//
//   if(cut == "") cut = "1";
//   THStack ths("thstack", varname.c_str());
//
//   vector<TH1F*> htemps(n);
//
//
//   for(int i(0); i< weightExpressions.size(); ++i)
//   {
//      if(weightExpressions[i] == "") weightExpressions[i] = "1";
//   }
//
//   if(weightExpressions.size() != n)
//   {
//      cout<<"Warning: in PlotOnevariable: weightexpression does not have the same size as nbr of trees: all weights set to 1"<<endl;
//      weightExpressions = vector<string>(n, "1");
//   }
//
//   for(unsigned int i(0); i<n; ++i)
//   {
//      tc.cd();
//      if( -1 != vect[i]->Draw((varname + ">>htemp_" +i2s(i)+  "("+d2s(nbin)+","+d2s(min)+","+d2s(max)+")").c_str(),
//               ( weightExpressions[i]+" * ((("+varname+") > "+d2s(min)+" && ("+varname+") < "+d2s(max)+") && ("+cut+"))" ).c_str()) )
//      {
//         htemps[i] = (TH1F*)tc.GetPrimitive(("htemp_"+i2s(i)).c_str());
//         if(htemps[i] == 0)
//         {
//            cout<<"Warning: in plotonevariable: could not get a histogram"<<endl;
//       //     for(unsigned int i(0); i<n; ++i)
//       //     {
//       //        vecf[i]->Close();
//       //        delete vecf[i];
//       //     }
//       //     return;
//         }
//         if(htemps[i] && htemps[i]->Integral() !=0)
//         {
//            htemps[i]->SetLineColor(i+1);
//            htemps[i]->SetLineWidth(2);
//            htemps[i]->Scale(1./htemps[i]->Integral(), "width");
//            ths.Add(htemps[i]);
//         }
//      }
//      else
//      {
//         cout<<"WARNING: in plotonevariable, "<<varname<<" could not be plotted"<<endl;
//      }
//   }
//
//   TCanvas canv(canvname.c_str(), canvname.c_str(), 600, 600);
//   if(ths.GetNhists() > 0)
//   {
//      ths.Draw("nostackhist");
//      ths.GetXaxis()->SetTitle((varname + ", "+cut).c_str());
//      if(outputname.find(".pdf") != string::npos) canv.Print(outputname.c_str());
//      else
//      {
//         outputname = outputname + canvname + ".pdf";
//         canv.Print(outputname.c_str());
//      }
//   }
//   if(ths.GetNhists() <= 0) cout<<"In plotOneVariable, nothing to print for "<<varname<<endl;
//
//   if(legEntries.size() == n && outputlegname.size() > 0)
//   {
//      TLegend leg(0.1, 0.1, 0.9, 0.9);
//      for(int i(0); i < n; ++i)
//      {
//         if(htemps[i] && htemps[i]->Integral() > 0) leg.AddEntry(htemps[i], legEntries[i].c_str(), "l");
//      }
//      leg.SetLineColor(0);
//      leg.SetFillColor(0);
//      TCanvas canvleg("legend", "legend", 600,600);
//      leg.Draw();
//
//      if(outputlegname.find(".pdf") != string::npos) canvleg.Print(outputlegname.c_str());
//      else
//      {
//         outputlegname = outputlegname  + "A_legend.pdf";
//         canvleg.Print(outputlegname.c_str());
//      }
//   }
//
//   for(unsigned int i(0); i<n; ++i)
//   {
//      vecf[i]->Close();
//      delete vecf[i];
//   }
//
//}
//
//
////void plotOneVariable(vector<string> const& filenames,
////      string varname,
////      string outputname,
////      string outputlegname,
////      int nbin,
////      string cut,
////      vector<string> weightExpressions,
////      vector<string> legEntries)
////{
////   unsigned int n(filenames.size());
////   if(n==0) return;
////
////   if(weightExpressions.size() != n) return;
////
////   vector<TFile*> vecf(n);
////   vector<TTree*> vect(n);
////
////   for(unsigned int i(0); i<n; ++i)
////   {
////      vecf[i] = new TFile(filenames[i].c_str());
////      vect[i] = (TTree*)vecf[i]->Get("B2KstarTauMu_Tuple/DecayTree");
////   }
////
////   TH1F* htemp;
////   TAxis* axis;
////
////   TCanvas tc("tc", "tc", 600, 600);
////
////   double max(0);
////   double min(0);
////
////   if(!separateString(varname, min, max))
////   {
////      double maxima[n];
////      double minima[n];
////      for(unsigned int i(0); i<n; ++i)
////      {
////         tc.cd();
////         if(-1 != vect[i] -> Draw(varname.c_str(), cut.c_str()))
////         {
////            htemp = (TH1F*)gPad->GetPrimitive("htemp");
////            if(htemp == 0)
////            {
////               cout<<"Warning: in plotonevariable: could not get a histogram (tree "<<i<<" )"<<endl;
////               for(unsigned int i(0); i<n; ++i)
////               {
////                  vecf[i]->Close();
////                  delete vecf[i];
////               }
////               return;
////            }
////            maxima[i] = htemp->GetXaxis()->GetXmax();
////            minima[i] = htemp->GetXaxis()->GetXmin();
////         }
////         else
////         {
////            cout<<"Warning: in plotonevariable: "<<varname<<" not found, plot aborted"<<endl;
////            for(unsigned int i(0); i<n; ++i)
////            {
////               vecf[i]->Close();
////               delete vecf[i];
////            }
////            return;
////         }
////      }
////
////      max = *max_element(maxima, maxima+n);
////      min = *min_element(minima, minima+n); 
////   }
////
////   string canvname(cleanNameString(varname));
////   if(canvname.size() > 50) canvname = canvname.substr(0,50);
///
////   if(cut == "") cut = "1";
////   THStack ths("thstack", varname.c_str());
////
////   vector<TH1F*> histos(n);
////
////   for(unsigned int i(0); i<n; ++i)
////   {
////      tc.cd();
////
////      vect[i]->SetBranchStatus("*", 0);
////      if(cut == "") cut = "1";
////      else setBranchStatusTTF(vect[i], cut);
////
////      if(weightExpressions[i] == "") weightExpressions[i] = "1";
////      else setBranchStatusTTF(vect[i], weightExpressions[i]);
////
////      setBranchStatusTTF(vect[i], varname);
////      TTreeFormula ttfVar("ttfVar", varname.c_str(), vect[i]);
////      TTreeFormula ttfCut("ttfCut", cut.c_str(), vect[i]);
////      TTreeFormula ttfWeight("ttfWeight", (weightExpressions[i]).c_str(), vect[i]);
////
////      histos[i] = new TH1F(("histo"+i2s(i)).c_str(), ("histo"+i2s(i)).c_str(), nbin, min, max);
////      histos[i] -> Sumw2();
////   
////      for(int j(0); j<vect[i]->GetEntries(); ++j)
////      {
////         vect[i]->GetEntry(j);
////         if(ttfCut.EvalInstance()) histos[i]->Fill(ttfVar.EvalInstance(), ttfWeight.EvalInstance());
////      }
////
////      if(histos[i] && histos[i]->Integral() > 0)
////      {
////         histos[i]->SetLineColor(i+1);
////         histos[i]->SetLineWidth(2);
////         histos[i]->Scale(1./histos[i]->Integral(), "width");
////         ths.Add(histos[i]);
////      }
////      else
////      {
////         cout<<"WARNING: in plotonevariable, "<<varname<<" could not be plotted"<<endl;
////      }
////   }
////
////   if(legEntries.size() == n)
////   {
////      TLegend leg(0.1, 0.1, 0.9, 0.9);
////      for(int i(0); i < n; ++i)
////      {
////         if(histos[i]->Integral() > 0) leg.AddEntry(histos[i], legEntries[i].c_str(), "l");
////      }
////      leg.SetLineColor(0);
////      leg.SetFillColor(0);
////      TCanvas canvleg("legend", "legend", 600,600);
////      leg.Draw();
////      outputlegname = outputlegname + ".pdf";
////      canvleg.Print(outputlegname.c_str());
////   }
////
////   TCanvas canv(canvname.c_str(), canvname.c_str(), 600, 600);
////   if(ths.GetNhists() > 0)
////   {
////      ths.Draw("nostack");
////      ths.GetXaxis()->SetTitle((varname + ", "+cut).c_str());
////      if(outputname.find(".pdf") != string::npos) canv.Print(outputname.c_str());
////      else
////      {
////         outputname = outputname + canvname + ".pdf";
////         cout<<"CANVNAME: "<<canvname<<endl;
////         canv.Print(outputname.c_str());
////      }
////   }
////   if(ths.GetNhists() <= 0) cout<<"In plotOnVariable, nothing to print for "<<varname<<endl;
////
////   for(unsigned int i(0); i<n; ++i)
////   {
////      delete histos[i];
////      vecf[i]->Close();
////      delete vecf[i];
////   }
////
////}
//
bool separateString(string& str1, double& min, double& max)
{
   size_t frst;
   frst = str1.find(";");
   if(frst == string::npos) return false;
   size_t scnd;
   scnd = str1.find(";", frst+1);
   if(scnd == string::npos) return false;

   string str2, str3;

   str2 = str1.substr(frst+1, scnd-frst-1);
   str3 = str1.substr(scnd+1);
   str1 = str1.substr(0, frst);

   min = s2d(str2);
   max = s2d(str3);
   return true;
}
//
double getCorrelationCoefficient(TTree*& t, string var1name, string var2name, string cuts, bool draw, string dirname)
 {
//   TH2F th2f("th2f", "th2f", 50,-1e5,1e5,50,-1e5,1e5);
   TH2F th2f("th2f", "th2f", 100,2400,10000,100,0,1.0);
   TH2D eff("eff", "eff", 100,2400,10000,100,0,1.0);


   cout<<"I am in"<<endl;
   string filename="uBDTqsqcutnSharedMisIDSmallDataSamplevsMCSig_FakeSSMuonSample";

   double var1min(-3);
   double var1max(-3); 
   double var2min(-3);
   double var2max(-3);

   bool isSeparable1;
   bool isSeparable2;

   t->SetBranchStatus("*",0);
   if(cuts != "") setBranchStatusTTF(t, cuts);
   if(cuts == "") cuts = "1"; 

//   cout<<"I am in again"<<endl;


   isSeparable1 = separateString(var1name, var1min, var1max);
   isSeparable2 = separateString(var2name, var2min, var2max);

   if(!isSeparable1 && !isSeparable2) th2f.SetCanExtend(TH1::kAllAxes);
   if(!isSeparable1 && isSeparable2)
   {
      if(draw) th2f.SetBins(50,-1e5,1e5, 50, var2min, var2max);
      if(draw) th2f.SetCanExtend(TH1::kXaxis);
      cuts += (" && " + var2name + " > " + d2s(var2min) + " && " + var2name + " < " + d2s(var2max));
   }
   if(isSeparable1 && !isSeparable2)
   {
      if(draw) th2f.SetBins(50, var1min, var1max, 50,-1e5,1e5);
      if(draw) th2f.SetCanExtend(TH1::kYaxis);
      cuts += (" && " + var1name + " > " + d2s(var1min) + " && " + var1name + " < " + d2s(var1max));
   }
   if(isSeparable1 && isSeparable2)
   {
      if(draw) th2f.SetBins(50, var1min, var1max,50, var2min, var2max);
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
   
//   cout<<"I am in again"<<endl;


   TFile fSig(dirname.c_str());
   TTree* tSig = (TTree*)fSig.Get("DecayTree");


  double nSig(getEntries(dirname.c_str(), "", ""));
  cout<<nSig<<"NSIG"<<endl;
  double mincut(-0.0);
  double maxcut(1.0);
  double d(maxcut-mincut); 
  const int n = int(nSig);
  double sigEff[n]; 
  string extracut="1"; 
  string weightBranchSig="";
//  i<t->GetEntries()

 
  for (int i=0; i<t->GetEntries(); i++){
          t->GetEntry(i);
          var1 = var1ttf->EvalInstance();
//          cout<<"Entry:"<<i<<endl;
//          cout<<"Var1:"<< var1<<endl;
//          cout<<"nSig:"<<nSig<<endl;
//          cout<<"Cut Value:"<<double(getEntries( dirname.c_str() , extracut + " && " + var2name.c_str() + " < " + d2s(mincut+(i/(1.*n))*d), weightBranchSig ));
//          cout<<"check mincut: "<<(mincut+(i/(1.*n))*d)<<endl;
          sigEff[i] = double(getEntries( dirname.c_str() ,  extracut + " && " + var2name.c_str() + " < " + d2s(mincut+(i/(1.*n))*d), weightBranchSig ))/double(nSig); 
          cout<<"SigEff:"<<sigEff[i]<<endl;
          if(draw) eff.Fill(var1, sigEff[i]);
 	}

      if(draw)
   {
      TCanvas canv4("canv4", "canv4", 600, 600);
      eff.GetXaxis()->SetTitle(var1name.c_str());
      eff.GetYaxis()->SetTitle("Sig Efficiency");
      eff.SetTitle(( var1name+"_vs_"+"SigEfficiency").c_str());
      eff.Draw("colz");
//      TProfile *profile = eff.ProfileX();
//      profile->Draw("same");
      canv4.Print((filename+cleanNameString("SigEff_vs_"+var1name)+".pdf").c_str());
   }

      if(draw)
   {
      TCanvas canv6("canv6", "canv6", 800, 600);
      TProfile *profile = eff.ProfileX();  
      profile->GetXaxis()->SetTitle(var1name.c_str());
      profile->GetYaxis()->SetTitle("Sig Efficiency");
      profile->SetTitle(( "ProfileX_"+var1name+"_vs_"+"SigEfficiency").c_str());
      profile->Draw();     
      canv6.Print((filename+cleanNameString("ProfileX_SigEff_vs_"+var1name)+".pdf").c_str());
   }

  

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
   cout<<"THIS is correlation:"<<correl<<endl;
//   return correl;

    if(draw)
   {
      TCanvas canv3("canv3", "canv3", 800, 600);
      TProfile *prof = th2f.ProfileX();
      prof->GetYaxis()->SetTitleOffset(1.4);
      prof->GetXaxis()->SetTitle(var1name.c_str());
      prof->GetYaxis()->SetTitle(var2name.c_str());
      prof->SetTitle(( "ProfileX_"+var1name+"_vs_"+var2name).c_str());
  //    TProfile *prof = th2f.ProfileX();  
      prof->Draw();
      canv3.Print( (filename+cleanNameString("ProfileX_"+var1name+"_vs_"+var2name)+".pdf").c_str());
   }

  return correl;
 }

double getCorrelationCoefficient(string filename, string var1name, string var2name, string cuts, bool draw, string dirname)
{
   cout<<"Starting"<<endl;
   TFile f(filename.c_str());
   TTree* t = (TTree*)f.Get("DecayTree");
   cout<<"lala"<<endl;
   cout<<filename<<t<<var1name<<var2name<<cuts<<draw<<dirname<<endl; 
   getCorrelationCoefficient(t, var1name, var2name, cuts, draw, dirname);
   cout<<"Past Get Corr Factor"<<endl;
   f.Close();
}


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
}




//
//void getCorrelationMatrix(vector<string> vars, string namefile, string nameoutput, string cuts, bool draw2d)
//{
//   TFile f(namefile.c_str());
//   TTree* t = (TTree*)f.Get("B2KstarTauMu_Tuple/DecayTree");
//   unsigned int n(vars.size());
//   TH2I megamatrix("megamatrix", "Mega Matrix", n,0,n,n,0,n);
//   megamatrix.SetStats(0);
//
//   double dummy1, dummy2;
//   string stringdummy;
//
//   for(int i(0); i<n; ++i)
//   {
//      stringdummy = vars[i];
//      separateString(stringdummy, dummy1, dummy2);
//      megamatrix.GetXaxis()->SetBinLabel(i+1, stringdummy.c_str()); 
//      megamatrix.GetYaxis()->SetBinLabel(i+1, stringdummy.c_str()); 
//   }
//
//   megamatrix.GetXaxis()->SetLabelSize(0.015);
//   megamatrix.GetYaxis()->SetLabelSize(0.015);
//   megamatrix.GetXaxis()->LabelsOption("v");
//
//   double coef(0);
//   int count(0);
//   int tot(0.5*n*(n+1));
//
//   cout<<"computation of big matrix"<<endl;
//   for(int i(0); i<n;++i)
//   {
//      for(int j(i); j<n; ++j)
//      {
//         if(count % (tot/10) == 0) cout<<100*count/tot<<" \% processed"<<endl;
//         coef = getCorrelationCoefficient(t, vars[i], vars[j], cuts, draw2d, nameoutput);
//         megamatrix.SetBinContent(i+1, j+1, 100*coef);
//         megamatrix.SetBinContent(j+1, i+1, 100*coef);
//         ++count;
//      }
//   }
//
//   TCanvas canv("canv", "canv", 1200, 1200);
//   canv.SetBottomMargin(0.2);
//   canv.SetLeftMargin(0.2);
//   megamatrix.SetMarkerSize(0.7);
//   megamatrix.Draw("textcolz");
//
//   canv.Print( nameoutput.c_str());
//   f.Close();
//}
//
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

string cleanNameString(string str)
{
   size_t st(0);

   string toreplace(" */#.,[]{}()+-=:");
   for(int i(0); i<toreplace.size(); ++i)
   {
      while(st != string::npos)
      {
         st = str.find(toreplace[i]);
         if(st!=string::npos) str = str.replace(st, 1, "_");
      }
      st = 0;
   }

   return str;
}
//
//double gamma(double* x, double* param)
//{
//   return param[0]*TMath::GammaDist(x[0], param[1], param[2], param[3]);
//}
//
//double gammaDataNorm(double SPDHits)
//{
//   double tab[4];
//   tab[0] = 33.76956;
//   tab[1] = 4.70346;
//   tab[2] = -3.45522e-8;
//   tab[3] = 123.049;
//   return gamma(&SPDHits, tab);
//}
//
//double gammaMCNorm(double SPDHits)
//{
//   double tab[4];
//   tab[0] = 20.15166;
//   tab[1] = 4.15994;
//   tab[2] = -6.73319;
//   tab[3] = 62.8926;
//   return gamma(&SPDHits, tab);
//}
//
//// all users - please change the name of this file to lhcbStyle.C
//// // Commits to lhcbdocs svn of .C files are not allowed
//void lhcbStyle(double fontsize)
//{
//   // define names for colours
//   Int_t black  = 1;
//   Int_t red    = 2;
//   Int_t green  = 3;
//   Int_t blue   = 4;
//   Int_t yellow = 5; 
//   Int_t magenta= 6;
//   Int_t cyan   = 7;
//   Int_t purple = 9;
//
//
//   ////////////////////////////////////////////////////////////////////
//   // PURPOSE:
//   //
//   // This macro defines a standard style for (black-and-white) 
//   // "publication quality" LHCb ROOT plots. 
//   //
//   // USAGE:
//   //
//   // Include the lines
//   //   gROOT->ProcessLine(".L lhcbstyle.C");
//   //   lhcbStyle();
//   // at the beginning of your root macro.
//   //
//   // Example usage is given in myPlot.C
//   //
//   // COMMENTS:
//   //
//   // Font:
//   // 
//   // The font is chosen to be 132, this is Times New Roman (like the text of
//   //  your document) with precision 2.
//   //
//   // "Landscape histograms":
//   //
//   // The style here is designed for more or less square plots.
//   // For longer histograms, or canvas with many pads, adjustements are needed. 
//   // For instance, for a canvas with 1x5 histograms:
//   //  TCanvas* c1 = new TCanvas("c1", "L0 muons", 600, 800);
//   //  c1->Divide(1,5);
//   //  Adaptions like the following will be needed:
//   //  gStyle->SetTickLength(0.05,"x");
//   //  gStyle->SetTickLength(0.01,"y");
//   //  gStyle->SetLabelSize(0.15,"x");
//   //  gStyle->SetLabelSize(0.1,"y");
//   //  gStyle->SetStatW(0.15);
//   //  gStyle->SetStatH(0.5);
//   //
//   // Authors: Thomas Schietinger, Andrew Powell, Chris Parkes, Niels Tuning
//   // Maintained by Editorial board member (currently Niels)
//   ///////////////////////////////////////////////////////////////////
//
//   // Use times new roman, precision 2 
//   Int_t lhcbFont        = 132;  // Old LHCb style: 62;
//   // Line thickness
//   Double_t lhcbWidth    = 2.00; // Old LHCb style: 3.00;
//   // Text size
//   Double_t lhcbTSize    = fontsize;//0.06; 
//
//   // use plain black on white colors
//   gROOT->SetStyle("Plain"); 
//   TStyle *lhcbStyle= new TStyle("lhcbStyle","LHCb plots style");
//
//   //lhcbStyle->SetErrorX(0); //  don't suppress the error bar along X
//
//   lhcbStyle->SetFillColor(1);
//   lhcbStyle->SetFillStyle(1001);   // solid
//   lhcbStyle->SetFrameFillColor(0);
//   lhcbStyle->SetFrameBorderMode(0);
//   lhcbStyle->SetPadBorderMode(0);
//   lhcbStyle->SetPadColor(0);
//   lhcbStyle->SetCanvasBorderMode(0);
//   lhcbStyle->SetCanvasColor(0);
//   lhcbStyle->SetStatColor(0);
//   lhcbStyle->SetLegendBorderSize(0);
//   lhcbStyle->SetLegendFont(132);
//
//   // If you want the usual gradient palette (blue -> red)
//   lhcbStyle->SetPalette(1);
//   // If you want colors that correspond to gray scale in black and white:
////   int colors[8] = {0,5,7,3,6,2,4,1};
////   lhcbStyle->SetPalette(8,colors);
//
//   // set the paper & margin sizes
//   lhcbStyle->SetPaperSize(20,26);
//   lhcbStyle->SetPadTopMargin(0.05);
//   lhcbStyle->SetPadRightMargin(0.05); // increase for colz plots
//   lhcbStyle->SetPadBottomMargin(0.16);
//   lhcbStyle->SetPadLeftMargin(0.14);
//
//   // use large fonts
//   lhcbStyle->SetTextFont(lhcbFont);
//   lhcbStyle->SetTextSize(lhcbTSize);
//   lhcbStyle->SetLabelFont(lhcbFont,"x");
//   lhcbStyle->SetLabelFont(lhcbFont,"y");
//   lhcbStyle->SetLabelFont(lhcbFont,"z");
//   lhcbStyle->SetLabelSize(lhcbTSize,"x");
//   lhcbStyle->SetLabelSize(lhcbTSize,"y");
//   lhcbStyle->SetLabelSize(lhcbTSize,"z");
//   lhcbStyle->SetTitleFont(lhcbFont);
//   lhcbStyle->SetTitleFont(lhcbFont,"x");
//   lhcbStyle->SetTitleFont(lhcbFont,"y");
//   lhcbStyle->SetTitleFont(lhcbFont,"z");
//   lhcbStyle->SetTitleSize(1.2*lhcbTSize,"x");
//   lhcbStyle->SetTitleSize(1.2*lhcbTSize,"y");
//   lhcbStyle->SetTitleSize(1.2*lhcbTSize,"z");
//
//   // use medium bold lines and thick markers
//   lhcbStyle->SetLineWidth(lhcbWidth);
//   lhcbStyle->SetFrameLineWidth(lhcbWidth);
//   lhcbStyle->SetHistLineWidth(lhcbWidth);
//   lhcbStyle->SetFuncWidth(lhcbWidth);
//   lhcbStyle->SetGridWidth(lhcbWidth);
//   lhcbStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
//   lhcbStyle->SetMarkerStyle(20);
//   lhcbStyle->SetMarkerSize(1.0);
//
//   // label offsets
//   lhcbStyle->SetLabelOffset(0.010,"X");
//   lhcbStyle->SetLabelOffset(0.010,"Y");
//
//   // by default, do not display histogram decorations:
//   lhcbStyle->SetOptStat(0);  
//   //lhcbStyle->SetOptStat("emr");  // show only nent -e , mean - m , rms -r
//   // full opts at http://root.cern.ch/root/html/TStyle.html#TStyle:SetOptStat
//   lhcbStyle->SetStatFormat("6.3g"); // specified as c printf options
//   lhcbStyle->SetOptTitle(0);
//   lhcbStyle->SetOptFit(0);
//   //lhcbStyle->SetOptFit(1011); // order is probability, Chi2, errors, parameters
//   //titles
//   lhcbStyle->SetTitleOffset(0.95,"X");
//   lhcbStyle->SetTitleOffset(0.95,"Y");
//   lhcbStyle->SetTitleOffset(1.2,"Z");
//   lhcbStyle->SetTitleFillColor(0);
//   lhcbStyle->SetTitleStyle(0);
//   lhcbStyle->SetTitleBorderSize(0);
//   lhcbStyle->SetTitleFont(lhcbFont,"title");
//   lhcbStyle->SetTitleX(0.0);
//   lhcbStyle->SetTitleY(1.0); 
//   lhcbStyle->SetTitleW(1.0);
//   lhcbStyle->SetTitleH(0.05);
//
//   // look of the statistics box:
//   lhcbStyle->SetStatBorderSize(0);
//   lhcbStyle->SetStatFont(lhcbFont);
//   lhcbStyle->SetStatFontSize(0.05);
//   lhcbStyle->SetStatX(0.9);
//   lhcbStyle->SetStatY(0.9);
//   lhcbStyle->SetStatW(0.25);
//   lhcbStyle->SetStatH(0.15);
//
//   // put tick marks on top and RHS of plots
//   lhcbStyle->SetPadTickX(1);
//   lhcbStyle->SetPadTickY(1);
//
//   // histogram divisions: only 5 in x to avoid label overlaps
//   lhcbStyle->SetNdivisions(505,"x");
//   lhcbStyle->SetNdivisions(510,"y");
//
//   gROOT->SetStyle("lhcbStyle");
//   gROOT->ForceStyle();
//
//   // add LHCb label
//   TPaveText* lhcbName = new TPaveText(gStyle->GetPadLeftMargin() + 0.05,
//         0.87 - gStyle->GetPadTopMargin(),
//         gStyle->GetPadLeftMargin() + 0.20,
//         0.95 - gStyle->GetPadTopMargin(),
//         "BRNDC");
//   lhcbName->AddText("LHCb");
//   lhcbName->SetFillColor(0);
//   lhcbName->SetTextAlign(12);
//   lhcbName->SetBorderSize(0);
//
//   TText *lhcbLabel = new TText();
//   lhcbLabel->SetTextFont(lhcbFont);
//   lhcbLabel->SetTextColor(1);
//   lhcbLabel->SetTextSize(lhcbTSize);
//   lhcbLabel->SetTextAlign(12);
//
//   TLatex *lhcbLatex = new TLatex();
//   lhcbLatex->SetTextFont(lhcbFont);
//   lhcbLatex->SetTextColor(1);
//   lhcbLatex->SetTextSize(lhcbTSize);
//   lhcbLatex->SetTextAlign(12);
//
//   cout << "-------------------------" << endl;  
//   cout << "Set LHCb Style - Feb 2012" << endl;
//   cout << "-------------------------" << endl;  
//
//}
//
