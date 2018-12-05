#include "Lenin.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TH2F.h"

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
         leg.AddEntry(vec[j] , (bdtvars[i]).c_str(), "L");
      }
   }

   cROC.cd();
   leg.Draw();
   cROC.Print(outputfilename.c_str());

   for(int i(0); i<vec.size(); ++i) delete vec[i];
}

void plotOverTraining(
      KFolder kf,
      string outputFileName,
      string BDTName,
      string weightBranch
      )
{
   int nFolds(kf.getNFolds());
   double wTrain(1./(1.*(nFolds-1)));
   TH1F hsigtest("hsigtest", "hsigtest", 40, -0.0, 1.0);
   TH1F hbkgtest("hbkgtest", "hbkgtest", 40, -0.0, 1.0); 
   TH1F hsigtrain("hsigtrain", "hsigtrain", 40, -0.0, 1.0);
   TH1F hbkgtrain("hbkgtrain", "hbkgtrain", 40, -0.0, 1.0); 

   TH2F curve("curve", "curve", 40, -0.0, 1.0, 40, -0.0, 1000);


   hsigtest.Sumw2();
   hbkgtest.Sumw2();
   hsigtrain.Sumw2();
   hbkgtrain.Sumw2();

   unsigned int foundTrain(0);
   unsigned int foundTest(1);

   for(int i(0); i<nFolds; ++i)
   {
//      TFile f( (kf.getOutFileName() + "TMVA_fold_" + i2s(i) + ".root").c_str());
      TFile f(("/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/diffvs/uBDTandKfoldrun-10/tmva/TMVA_fold_" + i2s(i) + ".root").c_str());

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
   
      cout<<"test entries: "<<ttest->GetEntries()<<endl;
      cout<<"train entries: "<<ttrain->GetEntries()<<endl;


      for(int i(0); i<ttest->GetEntries(); ++i)
      {
         ttest->GetEntry(i);
         w = ttfWeightTest.EvalInstance();
         if(classIDTest == 0)
         {
	 hsigtest.Fill(BDTTest, w);
         curve.Fill(BDTTest,1.0,w);
	 }
         if(classIDTest == 1)
	 {
	 hbkgtest.Fill(BDTTest, w);
         curve.Fill(BDTTest,1.0, w);
	 }
      }

      for(int i(0); i<ttrain->GetEntries(); ++i)
      {
         ttrain->GetEntry(i);
         w = ttfWeightTrain.EvalInstance();
         cout<<"This is w:"<<w<<endl;
         cout<<"This is BDTTrain:"<<BDTTrain<<endl;
         if(classIDTrain == 0) hsigtrain.Fill(BDTTrain, w);
         if(classIDTrain == 1) hbkgtrain.Fill(BDTTrain, w);
      }
      f.Close();
   }
 
 cout<<"Integral background train"<<(hbkgtrain.Integral())<<endl;
 cout<<"Integral signal train"<<(hsigtrain.Integral())<<endl;
 cout<<"Integral test bkg"<<(hbkgtest.Integral())<<endl;
 cout<<"Integral test sig"<<(hsigtest.Integral())<<endl; 


   hsigtest.Scale(1./hsigtest.Integral());
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

   hsigtest.SetLineColor(2);
   hsigtest.SetLineWidth(2);
   hsigtest.SetFillColor(2);
   hsigtest.SetFillStyle(3365);

   hbkgtest.SetLineWidth(2);
   hbkgtest.SetFillColor(4);
   hbkgtest.SetFillStyle(3365);

   TCanvas c("cOverTraining", "cOverTraining", 600, 600);  

   hsigtrain.GetXaxis()->SetTitle("BDT output");
   hsigtrain.GetYaxis()->SetTitle("# Events (normalised)");
   hsigtrain.GetYaxis()->SetTitleOffset(1.25);

   hbkgtest.Draw("hist");
   hsigtest.Draw("histsame");
  
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

   d.Print("curve.pdf");





}
