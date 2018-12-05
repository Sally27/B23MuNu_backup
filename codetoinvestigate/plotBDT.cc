#include "plotBDT.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TF1.h"
#include "TGraphErrors.h"

#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooAbsReal.h"
#include "RooFormulaVar.h"
#include "getPreselection.h"


valError ExtrapolBkgExpRooFit(TTree* tree,
      double sbMin, //sideband from which the nbr of events will be extrapolated
      double sbMax,
      double srMin, //signal region
      double srMax,
      string varToFit,
      string namePlot)
{
   RooRealVar tot("tot", "tot", 1.*tree->GetEntries(("B_plus_M > "+d2s(sbMin)+" && B_plus_M < "+d2s(sbMax)).c_str()));
   RooRealVar mass("B_plus_M","B_plus_M",srMin,sbMax);
   RooRealVar c("c","c",-0.001,-0.05,0.05);

   RooExponential model("model","model",mass,c);

   RooDataSet data("data","data",tree,RooArgSet(mass));
   mass.setRange("sideband",sbMin,sbMax);
   mass.setRange("signal",srMin,srMax);

   RooFitResult* rfr = model.fitTo(data,RooFit::Minos(1), RooFit::Range("sideband"), RooFit::Save());

   TCanvas cv("cv","cv");
   RooPlot *frame = mass.frame();
   data.plotOn(frame);
   model.plotOn(frame,RooFit::Range("sideband"));
   model.paramOn(frame);
   frame->Draw();
   cv.Print(namePlot.c_str());


   //RooAbsReal* igmass_mod = model.createIntegral(mass,RooFit::NormSet(mass),RooFit::Range("sideband"));
   //RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(1-@0)*@1/(@0)" , RooArgList(*igmass_mod, tot)); 
   
   RooAbsReal* igmass_mod0 = model.createIntegral(mass,RooFit::NormSet(mass),RooFit::Range("sideband"));
   RooAbsReal* igmass_mod1 = model.createIntegral(mass,RooFit::NormSet(mass),RooFit::Range("signal"));
   RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(@1/@0)*@2" , RooArgList(*igmass_mod0, *igmass_mod1, tot)); 
 
   valError ret;
   ret.val = igmass_reg.getValV();
   ret.err = igmass_reg.getPropagatedError(*rfr);
   //cout<<"TOT TOT TOT TOT: "<<igmass_mod->getValV()<<" "<<tot.getValV()<<" "<<(1-igmass_mod->getValV())*tot.getValV()/(igmass_mod->getValV())<<endl;

   return ret;
}

valError ExtrapolBkgExpRooFit(string nametree,
      double sbMin, //sideband from which the nbr of events will be extrapolated
      double sbMax,
      double srMin, //signal region
      double srMax,
      string varToFit,
      string cut,
      string namePlot)
{
   TFile f(nametree.c_str());
   TTree* t = (TTree*)f.Get("DecayTree");
   TFile f2("toerase.root", "RECREATE");
   TTree* tree2 = t->CopyTree(cut.c_str());
   valError ret;
   ret = ExtrapolBkgExpRooFit(tree2, sbMin, sbMax, srMin, srMax, varToFit, namePlot);
   f.Close();
   return ret;
}


double ExtrapolBkgExp(TTree* tree,
      double sbMin, //sideband from which the nbr of events will be extrapolated
      double sbMax,
      double srMin, //signal region
      double srMax,
      string varToFit,
      string cut, 
      string namePlot)
{
   if(cut == "") cut = "1";
   double entriessb(tree->GetEntries( ( cut+" && ("+varToFit+">"+d2s(sbMin)+") && ("+varToFit+"<"+d2s(sbMax)+")").c_str())); 
   TH1F* hsb(0);
   TCanvas csb("csb", "csb", 600, 600);   
   tree->Draw( (varToFit+">>hsb(40,"+d2s(srMin)+","+d2s(sbMax)+")").c_str(), cut.c_str());
   hsb = (TH1F*)csb.GetPrimitive("hsb");

   TF1 fexp("fexp", "[0]*[1]*TMath::Exp(-[1]*x)");
   fexp.SetParameter(0, entriessb);
   fexp.SetParLimits(1, -1e-2, 1e-2);
   fexp.SetRange(sbMin, sbMax);

   hsb->Fit(&fexp, "RU");

   double factor(fexp.Integral(srMin, srMax) / fexp.Integral(sbMin, sbMax));

   if(namePlot.size() > 1) csb.Print(namePlot.c_str());

   return factor*entriessb;
}


double ExtrapolBkgExp(string nametree,
      double sbMin, //sideband from which the nbr of events will be extrapolated
      double sbMax,
      double srMin, //signal region
      double srMax,
      string varToFit,
      string cut, 
      string namePlot)
{
   TFile f(nametree.c_str());
   TTree* t = (TTree*)f.Get("DecayTree");
   double ret(0);
   ret = ExtrapolBkgExp(t, sbMin, sbMax, srMin, srMax, varToFit, cut, namePlot);
   f.Close();
   return ret;
}


double optimiseBdtWithExpoBkg(string fileSig,
      string fileBkg,
      double wSig,
      double wBkg,
      string bdtvar,
      double mincut,
      double maxcut,
      int nstep,
      string nameplot,
      string cuts, 
      double sbMin, //sideband from which the nbr of events will be extrapolated
      double sbMax,
      double srMin, //signal region
      double srMax,
      string varToFit
      )
{
   TFile fSig(fileSig.c_str());
   TTree* tSig = (TTree*)fSig.Get("DecayTree");
   TFile fBkg(fileBkg.c_str());
   TTree* tBkg = (TTree*)fBkg.Get("DecayTree");

   string str;
   if(cuts =="") cuts = "1"; 
   str = cuts+" && "+bdtvar+" > ";

   double step( (maxcut-mincut)/(1.*(nstep-1)));
   TH1F reth("reth", "reth", nstep, mincut-0.5*step, maxcut+0.5*step);

   double currentcut;
   double S;
   double B;

   for(int i(0); i<nstep; ++i)
   {
      currentcut = mincut+i*step;
      S = wSig*getEntries( tSig, str+d2s(currentcut));
      B = wBkg*ExtrapolBkgExp(tBkg, sbMin, sbMax, srMin, srMax, varToFit, str+d2s(currentcut), "");
      if(S+B == 0) reth.SetBinContent(reth.GetXaxis()->FindBin(currentcut), 0); 
      else reth.SetBinContent(reth.GetXaxis()->FindBin(currentcut), S/sqrt(S+B)); 
   }

   reth.SetXTitle(bdtvar.c_str());

   TCanvas canv("canv", "canv", 600,600);
   reth.Draw();
   if(nameplot.size()>1) canv.Print(nameplot.c_str());


   return reth.GetXaxis()->GetBinCenter(reth.GetMaximumBin());
}


double optimiseBdt(string fileSig,
      string fileBkg,
      double wSig,
      double wBkg,
      string bdtvar,
      double mincut,
      double maxcut,
      int nstep,
      string nameplot,
      string cuts, 
      string weightBranchSig, 
      string weightBranchBkg
      )
{
   TFile fSig(fileSig.c_str());
   TTree* tSig = (TTree*)fSig.Get("DecayTree");
   TFile fBkg(fileBkg.c_str());
   TTree* tBkg = (TTree*)fBkg.Get("DecayTree");

   string str;
   if(cuts =="") str = bdtvar+" > "; 
   if(cuts !="") str = cuts+" && "+bdtvar+" > ";

   double step( (maxcut-mincut)/(1.*(nstep-1)));
   TH1F reth("reth", "reth", nstep, mincut-0.5*step, maxcut+0.5*step);

   double currentcut;
   double S;
   double B;

   for(int i(0); i<nstep; ++i)
   {
      currentcut = mincut+i*step;
      S = wSig*getEntries( tSig, str+d2s(currentcut), weightBranchSig);
      B = wBkg*getEntries( tBkg, str+d2s(currentcut), weightBranchBkg);
      if(S+B == 0) reth.SetBinContent(reth.GetXaxis()->FindBin(currentcut), 0); 
      else reth.SetBinContent(reth.GetXaxis()->FindBin(currentcut), S/sqrt(S+B)); 
   }

   reth.SetXTitle(bdtvar.c_str());
   TCanvas canv("canv", "canv", 600,600);
   reth.Draw();
   if(nameplot.size()>1) canv.Print(nameplot.c_str()); 

   return reth.GetXaxis()->GetBinCenter(reth.GetMaximumBin());
}

bool getOneRocCurve(string fsigname,
      string fbkgname, 
      string bdtvar, 
      string extracut,
      double sigEff[],
      double bkgRej[],
      unsigned int n,
      string weightBranchSig,
      string weightBranchBkg)
{
   TFile fSig(fsigname.c_str());
   TTree* tSig = (TTree*)fSig.Get("DecayTree");
   TFile fBkg(fbkgname.c_str());
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

   double mincut(-0.5);
   double maxcut(0.5);
   double d(maxcut-mincut);
   double nSig(getEntries(tSig, extracut, weightBranchSig));

   double nBkg(getEntries(tBkg, extracut, weightBranchBkg));

   for(int i(0); i<n; ++i)
   {
      sigEff[i] = getEntries( tSig, extracut+" && "+bdtvar + " > " + d2s(mincut+(i/(1.*n))*d), weightBranchSig )/nSig;
      bkgRej[i] = getEntries( tBkg, extracut+" && "+bdtvar + " < " + d2s(mincut+(i/(1.*n))*d), weightBranchBkg )/nBkg;
   }

   fSig.Close();
   fBkg.Close();
   return true;
}

void plotRocCurves(string fsigname,
      string fbkgname,
      vector<string> bdtvars,
      string outputfilename,
      string extracut,
      string weightBranchSig,
      string weightBranchBkg
      )
{
   unsigned int n(100);
   double minCut(-0.5);
   double maxCut(0.5);
   double sigEff[n];
   double bkgRej[n];

   vector<TGraph*> vec;

   TCanvas cROC("cROC", "cROC", 600, 600);
   TH1F* frame;
   frame = cROC.DrawFrame(0,0,1,1);
   frame->GetXaxis()->SetTitle("Signal Efficiency");
   frame->GetXaxis()->SetNdivisions(510, false);
   frame->GetYaxis()->SetTitle("Background Rejection");
    
   TLegend leg(0.1,0.1,0.4,0.4);
   int j(0);

   for(int i(0); i < bdtvars.size(); ++i)
   {
      if(getOneRocCurve(fsigname, fbkgname, bdtvars[i], extracut, sigEff, bkgRej, n))
      {
         vec.push_back(new TGraph(n, sigEff, bkgRej));

         cout<<"In ROC curve: "<<sigEff[50]<<" "<<bkgRej[50]<<endl;

         j = vec.size()-1;         

         vec[j] -> SetLineColor(j+1);
         vec[j] -> SetLineWidth(2);
         cROC.cd();
         vec[j] -> Draw("L");
         leg.AddEntry(vec[j] , (bdtvars[i]).c_str(), "l");
      }
   }

   cROC.cd();
   cROC.SetGrid();
   leg.Draw();
   leg.SetFillColor(0);
   cROC.Print(outputfilename.c_str());

   for(int i(0); i<vec.size(); ++i) delete vec[i];
}

void plotOverTraining(
      uKFolder kf,
      string outputFileName,
      string BDTName,
      string weightBranch,
      bool wantUserScale,
      double scaleSig,
      double scaleBkg
      )
{
   int nFolds(kf.getNFolds());
   double wTrain(1./(1.*(nFolds-1)));
   TH1F hsigtest("hsigtest", "hsigtest", 40, -1, 1);
   TH1F hbkgtest("hbkgtest", "hbkgtest", 40, -1, 1); 
   TH1F hsigtrain("hsigtrain", "hsigtrain", 40, -1, 1);
   TH1F hbkgtrain("hbkgtrain", "hbkgtrain", 40, -1, 1); 

   hsigtest.Sumw2();
   hbkgtest.Sumw2();
   hsigtrain.Sumw2();
   hbkgtrain.Sumw2();

   unsigned int foundTrain(0);
   unsigned int foundTest(1);

   for(int i(0); i<nFolds; ++i)
   {
      TFile f( (kf.getOutFileName() + "TMVA_fold_" + i2s(i) + ".root").c_str());
      TTree* ttest = (TTree*)f.Get("TestTree");
      TTree* ttrain = (TTree*)f.Get("TrainTree");
      if(ttest == 0 || ttrain == 0)
      {
         cout<<"ERROR in plotOverTraining: tree not found"<<endl;
         f.Close();
         return;
      }
      int classIDTest, classIDTrain;
      float BDTTest, BDTTrain;
      ttest->SetBranchStatus("*",0);
      ttest->SetBranchStatus("classID", 1);
      ttest->SetBranchStatus( (BDTName+"_fold_"+i2s(i)).c_str(), 1, &foundTrain);
      ttrain->SetBranchStatus("*",0);
      ttrain->SetBranchStatus("classID", 1);
      ttrain->SetBranchStatus((BDTName+"_fold_"+i2s(i)).c_str(), 1, &foundTest);

      if(foundTrain == 0 || foundTest == 0)
      {
         cout<<"ERROR in plotOverTraining: "<<BDTName<<" not found"<<endl;
         f.Close();
         return; 
      }

      ttest->SetBranchAddress((BDTName+"_fold_"+i2s(i)).c_str(), &BDTTest);
      ttrain->SetBranchAddress((BDTName+"_fold_"+i2s(i)).c_str(), &BDTTrain);
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

      for(int i(0); i<ttest->GetEntries(); ++i)
      {
         ttest->GetEntry(i);
         w = ttfWeightTest.EvalInstance();
         if(classIDTest == 0) hsigtest.Fill(BDTTest, w);
         if(classIDTest == 1) hbkgtest.Fill(BDTTest, w);
      }

      for(int i(0); i<ttrain->GetEntries(); ++i)
      {
         ttrain->GetEntry(i);
         w = ttfWeightTrain.EvalInstance();
         if(classIDTrain == 0) hsigtrain.Fill(BDTTrain, w);
         if(classIDTrain == 1) hbkgtrain.Fill(BDTTrain, w);
      }
      f.Close();
   }


   if(!wantUserScale)
   {
      hsigtest.Scale(1./hsigtest.Integral());
      hsigtrain.Scale(1./hsigtrain.Integral());
      hbkgtest.Scale(1./hbkgtest.Integral());
      hbkgtrain.Scale(1./hbkgtrain.Integral());
   }
   if(wantUserScale)
   {
      hsigtest.Scale(scaleSig);
      hbkgtest.Scale(scaleBkg);
      hsigtrain.Scale(scaleSig/(1.*(nFolds-1)));
      hbkgtrain.Scale(scaleBkg/(1.*(nFolds-1)));
   }

   hsigtest.SetMarkerColor(2);
   hsigtest.SetMarkerStyle(10);
   hsigtest.SetLineColor(2);
   hsigtest.SetLineWidth(2);

   hbkgtest.SetMarkerColor(4);
   hbkgtest.SetMarkerStyle(10);
   hbkgtest.SetLineWidth(2);

   hsigtrain.SetLineColor(2);
   hsigtrain.SetLineWidth(2);
   hsigtrain.SetFillColor(2);
   hsigtrain.SetFillStyle(3365);

   hbkgtrain.SetLineWidth(2);
   hbkgtrain.SetFillColor(4);
   hbkgtrain.SetFillStyle(3365);

   TCanvas c("cOverTraining", "cOverTraining", 600, 600);  

   hsigtrain.GetXaxis()->SetTitle("BDT output");
   hsigtrain.GetYaxis()->SetTitle("# Events (normalised)");
   hsigtrain.GetYaxis()->SetTitleOffset(1.25);


   hbkgtrain.Draw("hist");
   hsigtrain.Draw("histsame");
   hbkgtest.Draw("E1Psame");
   hsigtest.Draw("E1Psame");

   c.Print(outputFileName.c_str());
}


struct weightBDT{
   double weight;
   double BDT;
};

bool compare(weightBDT wB1, weightBDT wB2) { return (wB1.BDT>wB2.BDT);}

double getBDTCutWithGivenSigYield(string fileSig,
      double wSig,
      string bdtvar,
      string weightBranchSig,
      double sigYield,
      string cuts,
      int maxEntries
      )
{
   TFile fSig(fileSig.c_str());
   TTree* tSig = (TTree*)fSig.Get("DecayTree");

   if(maxEntries == -1) maxEntries = tSig->GetEntries();

   tSig->SetBranchStatus("*", 0);

   double BDT;
   double  weight(1.);

   tSig->SetBranchStatus(bdtvar.c_str(), 1);
   tSig->SetBranchAddress(bdtvar.c_str(), &BDT);
   if(weightBranchSig.size()>1)
   {
      tSig->SetBranchStatus(weightBranchSig.c_str(), 1);
      tSig->SetBranchAddress(weightBranchSig.c_str(), &weight);
   }


   if(cuts == "") cuts = "1";
   if(cuts != "1") setBranchStatusTTF(tSig, cuts);
   TTreeFormula ttfcuts("ttfcuts", cuts.c_str(), tSig);

   vector<weightBDT> vec;
   weightBDT dummy;

   for(int i(0); i<maxEntries; ++i)
   {
      tSig->GetEntry(i);
      if(ttfcuts.EvalInstance())
      {
         dummy.weight = weight;
         dummy.BDT = BDT;
         vec.push_back(dummy); 
      }
   }

   sort(vec.begin(), vec.end(), compare);

   int i(0);
   double sumW(0);
   double oldBDTcut(-1000);
   double newBDTcut(-1000);

   while( (sumW < sigYield) && (i < vec.size()))
   {
      oldBDTcut = newBDTcut;
      sumW += wSig*(vec.at(i).weight);
      newBDTcut = vec.at(i).BDT;
      ++i;
   }

   return 0.5*(newBDTcut + oldBDTcut);
}


void plotCutEffVsVar(string fileTree,
      string cut,
      string var,
      double minVar,
      double maxVar,
      int nstep,
      string nameplot,
      string extracuts)
{
   TFile f(fileTree.c_str());
   TTree* t = (TTree*)f.Get("DecayTree");
   
   if(extracuts == "") extracuts = "1";

   TCanvas canv("canv", "canv", 600,600);
   TH1F* hb(0);//histo before cut
   t->Draw( (var+">>hb("+i2s(nstep)+","+d2s(minVar)+","+d2s(maxVar)+")").c_str(), extracuts.c_str()  );
   hb = (TH1F*)canv.GetPrimitive("hb");

   TH1F* ha(0);//histo after cut
   t->Draw( (var+">>ha("+i2s(nstep)+","+d2s(minVar)+","+d2s(maxVar)+")").c_str(), ("("+cut+") && ("+extracuts+")").c_str()  );
   ha = (TH1F*)canv.GetPrimitive("ha");

   ha->Sumw2(); hb->Sumw2();
   ha->Divide(hb);
   
   ha->Draw();   
   canv.Print(nameplot.c_str());
}

vector<double> optimise2D(string bkgfilename, string sigfilename,string BDTVarName, string extraCut, double BDTCutMin, double BDTCutMax, double PIDCutMin, double PIDCutMax, int nSteps, double weightBkg, double weightSig, string outputName)
{
   TFile fbkg(bkgfilename.c_str());
   TTree* tbkg = (TTree*)fbkg.Get("DecayTree");

   TFile fsig(sigfilename.c_str());
   TTree* tsig = (TTree*)fsig.Get("DecayTree");


   double PIDCutNow;
   double BDTCutNow;
   double PIDStep( (PIDCutMax-PIDCutMin)/(1.*nSteps) );
   double BDTStep( (BDTCutMax-BDTCutMin)/(1.*nSteps) );

   TH2F h("h", "h", nSteps, BDTCutMin-0.5*BDTStep, BDTCutMax+0.5*BDTStep, nSteps, PIDCutMin-0.5*PIDStep, PIDCutMax+0.5*PIDStep);

   double sig(0);
   double bkg(0);
   double S;

   double maxS(-1.);
   double optimalBDTCut(0);
   double optimalPIDCut(0);

   for(int iPID(0); iPID<nSteps; ++iPID)
   {
      PIDCutNow = PIDCutMin+iPID*PIDStep;
      for(int iBDT(0); iBDT<nSteps; ++iBDT)
      {
         BDTCutNow = BDTCutMin + iBDT*BDTStep;
         sig = weightSig*getEntries(tsig, (extraCut + " && " + BDTVarName+" > "+d2s(BDTCutNow) + " && "+ "e_plus_PIDe > "+d2s(PIDCutNow) + " && "+"e_minus_PIDe > "+d2s(PIDCutNow)).c_str());
         bkg = weightBkg*getEntries(tbkg, (extraCut + " && " + BDTVarName+" > "+d2s(BDTCutNow) + " && "+ "e_plus_PIDe > "+d2s(PIDCutNow) + " && "+"e_minus_PIDe > "+d2s(PIDCutNow)).c_str());

         S = sig/sqrt(sig+bkg);

         h.SetBinContent(iBDT+1, iPID+1, S);

         if(S>maxS)
         {
            optimalBDTCut = BDTCutNow;
            optimalPIDCut = PIDCutNow;
         } 
      }
   }

   h.GetXaxis()->SetTitle("BDT cut");
   h.GetYaxis()->SetTitle("PIDe cut");

   if(outputName.size() > 1)
   {
      TCanvas canv("canv", "canv", 800, 600);
      canv.SetRightMargin(0.2);
      h.Draw("colz");
      canv.Print(outputName.c_str());
   }

   vector<double> ret;

   ret.push_back(optimalBDTCut);
   ret.push_back(optimalPIDCut);
   ret.push_back(maxS);
   return ret;
}

vector<double> optimise2DHOPBDT(string bkgfilename, string sigfilename,string BDTVarName, string extraCut, double BDTCutMin, double BDTCutMax, double HOPCutMin, double HOPCutMax, int nSteps, double weightBkg, double weightSig, string outputName)
{
   TFile fbkg(bkgfilename.c_str());
   TTree* tbkg = (TTree*)fbkg.Get("DecayTree");

   TFile fsig(sigfilename.c_str());
   TTree* tsig = (TTree*)fsig.Get("DecayTree");


   double HOPCutNow;
   double BDTCutNow;
   double HOPStep( (HOPCutMax-HOPCutMin)/(1.*nSteps) );
   double BDTStep( (BDTCutMax-BDTCutMin)/(1.*nSteps) );

   TH2F h("h", "h", nSteps, BDTCutMin-0.5*BDTStep, BDTCutMax+0.5*BDTStep, nSteps, HOPCutMin-0.5*HOPStep, HOPCutMax+0.5*HOPStep);

   double sig(0);
   double bkg(0);
   double S;

   double maxS(-1.);
   double optimalBDTCut(0);
   double optimalHOPCut(0);

   for(int iHOP(0); iHOP<nSteps; ++iHOP)
   {
      HOPCutNow = HOPCutMin+iHOP*HOPStep;
      for(int iBDT(0); iBDT<nSteps; ++iBDT)
      {
         BDTCutNow = BDTCutMin + iBDT*BDTStep;
         sig = weightSig*getEntries(tsig, (extraCut + " && " + BDTVarName+" > "+d2s(BDTCutNow) + " && "+ getMarieHeleneCut(HOPCutNow)).c_str());
         bkg = weightBkg*getEntries(tbkg, (extraCut + " && " + BDTVarName+" > "+d2s(BDTCutNow) + " && "+ getMarieHeleneCut(HOPCutNow)).c_str());
         cout<<getMarieHeleneCut(HOPCutNow)<<endl;

         S = sig/sqrt(sig+bkg);

         h.SetBinContent(iBDT+1, iHOP+1, S);

         cout<<HOPCutNow<<" "<<BDTCutNow<<" "<<sig<<" "<<bkg<<endl;

         if(S>maxS)
         {
            maxS=S;
            optimalBDTCut = BDTCutNow;
            optimalHOPCut = HOPCutNow;
         } 
      }
   }

   h.GetXaxis()->SetTitle("BDT cut");
   h.GetYaxis()->SetTitle("HOP shift");

   if(outputName.size() > 1)
   {
      TCanvas canv("canv", "canv", 800, 600);
      canv.SetRightMargin(0.2);
      h.Draw("colz");
      canv.Print(outputName.c_str());
   }

   vector<double> ret;

   ret.push_back(optimalBDTCut);
   ret.push_back(optimalHOPCut);
   ret.push_back(maxS);
   return ret;
}


//   double BDTCut;

void ExpVsBDTCut(double fitRegionMin, double fitRegionMax, string BDTName, double BDTCutMin, double BDTCutMax, string nameTree, string namePlot, string extracut)
{
   TF1 fExp("fExp", "TMath::Exp([0]+[1]*x)", fitRegionMin, fitRegionMax);

   int nbins(30); 

   double BDTCuts[nbins];
   double ExpoConstErrs[nbins];
   double ExpoConsts[nbins];

   double BDTStep( (BDTCutMax-BDTCutMin)/(1.*nbins) );
   double BDTCut;
   string BDTCutString;

   TFile f(nameTree.c_str());
   TTree* t = (TTree*)f.Get("DecayTree");

   TCanvas cFit("cExpBDT", "cExpBDT", 600, 600);
   TH1F* h;

   if(extracut == "") extracut = "1";

   for(int i(0); i<nbins; ++i)
   {
      BDTCut = BDTCutMin+i*BDTStep;
      BDTCutString = "("+BDTName+" > "+d2s(BDTCut)+")";
      cFit.cd();
      t->Draw( ("B_plus_M>>h(20,"+d2s(fitRegionMin)+", "+d2s(fitRegionMax)+")").c_str(), (extracut+" && "+BDTCutString).c_str());
      h = (TH1F*)cFit.GetPrimitive("h");

      h->Fit(&fExp, "U");

      BDTCuts[i] = BDTCut;
      ExpoConsts[i] = fExp.GetParameter(1);
      ExpoConstErrs[i] = fExp.GetParError(1);
   }


   TCanvas cExpBDT("cExpBDT", "cExpBDT", 600, 600);
   TGraphErrors graphExpConstVsBDTCut(nbins, BDTCuts, ExpoConsts, 0, ExpoConstErrs);
   graphExpConstVsBDTCut.Draw("ALP");

   cExpBDT.Print( namePlot.c_str());
}
