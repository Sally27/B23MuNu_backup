#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <cmath>
#include "TH1F.h"
#include "TCanvas.h"
#include "TBranch.h"
#include "RooConstVar.h"
#include "RooEffProd.h"
#include "RooBreitWigner.h"
#include "RooNumIntConfig.h"
#include "TF2.h"
#include "TEllipse.h"
#include "TLine.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooAbsPdf.h"
#include "RooCategory.h"
#include "RooArgSet.h"
#include "RooFitResult.h"
#include "clsfun.hpp"
#include "RooPlot.h"
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TMath.h"
#include "TStyle.h"
#include "RooAbsReal.h"
#include "RooMinuit.h"

using namespace std;
using namespace RooFit;

double s2d(string str)
{
        double ret;
        istringstream is(str);
        is >> ret;
        return ret;
}

string d2s(double d)
{
        string ret;
        ostringstream os;
        os<<d;
        return os.str();
}

string f2s(float d)
{
        string ret;
        ostringstream os;
        os<<d;
        return os.str();
}


string i2s(int i)
{
        string ret;
        ostringstream os;
        os<<i;
        return os.str();
}


double calculatemedian(TH1F * hbackground_DLL){



      Int_t nbins2 = hbackground_DLL->GetXaxis()->GetNbins();
      Double_t *x2 = new Double_t[nbins2];
      Double_t *y2 = new Double_t[nbins2];
      for (Int_t i=0;i<nbins2;i++) {
      x2[i] = hbackground_DLL->GetXaxis()->GetBinCenter(i+1);
      y2[i] = hbackground_DLL->GetBinContent(i+1);
      }
      Double_t median = TMath::Median(nbins2,x2,y2);

return(median);
}


double fitgaussianandplot(TH1F * hsignal_DLL, string category, std::ofstream& myfile, int nToys, double CLsBF){

      TF1* rufit = new TF1("Gaussian","gaus",-30.0,30.0);

      TCanvas* canvasgaus= new TCanvas("fitsig", "Fitsig",800,800);
      gStyle->SetOptFit(1111);
      hsignal_DLL->Fit("Gaussian","RQ");
      hsignal_DLL->SetLineColor(kBlue);
      hsignal_DLL->Draw();
      double amp = rufit -> GetParameter(0);
      double mean = rufit -> GetParameter(1);
      double sigma = rufit -> GetParameter(2);

      myfile << "Fitting Signal_DLL with Gaussian! "<< endl;
      myfile << "0th parameter of gaussian: " << amp <<endl;
      myfile << "1st parameter of gaussian / mean: " << mean <<endl;
      myfile << "2nd parameter of gaussian / sigma: " << sigma <<endl;

      canvasgaus->SaveAs(("gaus_"+category+"_numoftoys"+i2s(nToys)+"_injectsig"+d2s(CLsBF)+".pdf").c_str());
      return(sigma);

}


double calculateCLs(TH1F * hsignal_DLL, TH1F * hbackground_DLL, double value, std::ofstream& myfile, double CLsBF){
      double CLb = hbackground_DLL->Integral(hbackground_DLL->FindBin(-30),hbackground_DLL->FindBin(value))/hbackground_DLL->GetSumOfWeights();
      double CLs_b = hsignal_DLL->Integral(hsignal_DLL->FindBin(-30),hsignal_DLL->FindBin(value))/hsignal_DLL->GetSumOfWeights();
      double CLs = CLs_b/CLb;

      std::cout << "Value at which to calculate Cls: "<<value<<endl;
      std::cout << "CLs + b: " << CLs_b << " CLb:" << CLb << std::endl;
      std::cout << "CLs = " << CLs << " at BF of " << CLsBF << std::endl;

      myfile << "Value at which to calculate Cls: "<<value<<endl;
      myfile << "CLs + b: " << CLs_b << " CLb:" << CLb << endl;
      myfile << "CLs = " << CLs << " at BF of " << CLsBF <<endl;
      return(CLs);

}


std::vector<RooDataSet*> generateData(RooRealVar* BF,double BFval,RooAbsPdf* model_LL,RooAbsPdf* model_DD,RooRealVar* mass,RooCategory cat, int nToys) 
{
        std::vector<RooDataSet*> datasets;
        for (int i = 0; i < nToys; ++i)
        {
                BF->setConstant(false);
                BF->setVal(BFval);

                RooDataSet* dataset_LL = model_LL->generate(RooArgSet(*mass),RooFit::Extended(true));
                RooDataSet* dataset_DD = model_DD->generate(RooArgSet(*mass),RooFit::Extended(true));
                RooDataSet* dataset = new RooDataSet("data","combined data",*mass,RooFit::Index(cat),RooFit::Import("LowFCME",*dataset_LL),RooFit::Import("HighFCME",*dataset_DD));
                datasets.push_back(dataset);

        }
        return datasets;
  
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

double fitTwicePat(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF)
{
    BF->setConstant(false);
    BF->setVal(CLsBF);
    BF->removeError();
    BF->setConstant(true);
    RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true));
    double BFresult = BF->getVal();
    BF->setConstant(false);
    BF->setVal(0.0);
    BF->setConstant(true);
    RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true));
    double testStat = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());
    if ((dataresult_fixed->covQual() !=3) || (dataresult_fixed->covQual() != 3))
    {
        if ((dataresult_fixed->edm() > 0.02) || (dataresult_free->edm() > 0.02))
        {
                testStat = -50;
        }
    }
    std::cout << BFresult << " " << testStat << std::endl;
    delete dataresult_free;
    delete dataresult_fixed;
    return testStat;
}


double fitTwiceOld2(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* Bplus_Corrected_Mass, TTree* treename, bool update, RooCategory* cat)
{       
    BF->setConstant(false);
    BF->setVal(CLsBF);
    BF->removeError();
    BF->setConstant(true);

//    RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true),RooFit::NumCPU(2));//RooFit::Save(true),RooFit::PrintLevel(-1));
//    RooMinuit m(*nll);

//    int migradStatus(-1000);
//    int hesseStatus(-1000);
    
//    migradStatus = m.migrad();
//    hesseStatus = m.hesse();

//    RooFitResult* dataresult_free = m.save();
//    dataresult_free->Print("v");

//    RooCategory cat("sample","sample");
//    cat.defineType("LowFCME") ;
//    cat.defineType("HighFCME") ;


    RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true));


    if (nToys==10)
    {


    TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
    firstfit->Divide(2) ;
    RooPlot* frame1 = Bplus_Corrected_Mass->frame(Title("firstfitLowFCME"),Bins(60)) ;
    data->plotOn(frame1,Cut("sample==sample::LowFCME")) ;
    cout<<"PLOT FINISH in fit old"<<endl;
    model->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
    cout<<"PLOT FINISH in fit old 2"<<endl;
    RooPlot* frame2 = Bplus_Corrected_Mass->frame(Title("firstfitHighFCME"),Bins(60)) ;
    data->plotOn(frame2,Cut("sample==sample::HighFCME")) ;
    model->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
    firstfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
    firstfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
    firstfit->SaveAs(("fitTwiceOld2_dataresult_free_fitnumber_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
    }


    cout<<"Fitting dataresult_free"<<endl;    

    double la=dataresult_free->minNll();
    double BFresult2 = BF->getVal();
    double statusa= dataresult_free->status();

 //   TFile rfres("roofitresult.root","update");
//    TTree *treename2=(TTree*)rfres.Get("bkgll");
    
    if(!update) treename->Branch("dataresult_free_minNll",&la, "dataresult_free_minNll/D");
    if(update) treename->SetBranchAddress("dataresult_free_minNll", &la);
    if(!update) treename->Branch("BF_free_minNll",&BFresult2, "BF_free_minNll/D");
    if(update) treename->SetBranchAddress("BF_free_minNll", &BFresult2);
//    if(!update) treename->Branch("migradStatus_free",&migradStatus, "smigradStatus_free/I");
//    if(update) treename->SetBranchAddress("migradStatus_free", &migradStatus);
    if(!update) treename->Branch("status_free",&statusa, "status_free/D");
    if(update) treename->SetBranchAddress("status_free", &statusa);



     cout<<" EDM value: "<<dataresult_free->edm();

//    treename->Fill();
//    treename->Write();

 //   rfrestree.Branch("CLsOneSigma",&dataresult_free->minNll(), "CLsOneSigma/D");
    

    BF->setConstant(false);
    BF->setVal(0.0);
    BF->setConstant(true);

    cout<<"Fitting dataresult_fixed"<<endl;

    RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true));

    if (nToys==10)
    {
    TCanvas* secondfit= new TCanvas("secondfit", "secondfit",800,800);
    secondfit->Divide(2);
    RooPlot* frame3 = Bplus_Corrected_Mass->frame(Title("secondfitlowFCME"),Bins(60)) ;
    data->plotOn(frame3,Cut("sample==sample::LowFCME"));
    model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
    cout<<"PLOT FINISH 3"<<endl;
    RooPlot* frame4 = Bplus_Corrected_Mass->frame(Title("secondfitHighFCME"),Bins(60)) ;
    data->plotOn(frame4,Cut("sample==sample::HighFCME")) ;
    model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
    secondfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
    secondfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
    secondfit->SaveAs(("fitTwiceOld2_dataresult_fixed_fitnumber_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
    }

    double BFresult = BF->getVal();
    double lb=dataresult_fixed->minNll();
    double statusb=dataresult_fixed->status();

    if(!update) treename->Branch("dataresult_fixed_minNll",&lb, "dataresult_fixed_minNll/D");
    if(update) treename->SetBranchAddress("dataresult_fixed_minNll", &lb);
    if(!update) treename->Branch("BF_fixed_minNll",&BFresult, "BF_fixed_minNll/D");
    if(update) treename->SetBranchAddress("BF_fixed_minNll", &BFresult); 
    if(!update) treename->Branch("status_fixed",&statusb, "status_fixed/D");
    if(update) treename->SetBranchAddress("status_fixed", &statusb);



    double testStat = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());


    if(!update) treename->Branch("TestStat",&testStat, "TestStat/D");
    if(update) treename->SetBranchAddress("TestStat", &testStat);    



    if ((dataresult_fixed->covQual() !=3) || (dataresult_fixed->covQual() != 3))
    {
        if ((dataresult_fixed->edm() > 0.02) || (dataresult_free->edm() > 0.02))
        {
                testStat = -50;
        }
    }
    std::cout <<"I give you result: "<< BFresult << " " << testStat << std::endl;

    treename->Fill();
    delete dataresult_free;
    delete dataresult_fixed;
    return testStat;
}

double fitTwiceOld(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* Bplus_Corrected_Mass, TTree* treename, bool update)
{       
    BF->setConstant(false);
    BF->setVal(CLsBF);
    BF->removeError();
    BF->setConstant(true);

//    RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true),RooFit::NumCPU(2));//RooFit::Save(true),RooFit::PrintLevel(-1));
//    RooMinuit m(*nll);

//    int migradStatus(-1000);
//    int hesseStatus(-1000);
    
//    migradStatus = m.migrad();
//    hesseStatus = m.hesse();

//    RooFitResult* dataresult_free = m.save();
//    dataresult_free->Print("v");

    RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true),RooFit::PrintLevel(-1));

    cout<<"Fitting dataresult_free"<<endl;    

    double la=dataresult_free->minNll();
    double BFresult2 = BF->getVal();
    double statusa= dataresult_free->status();

 //   TFile rfres("roofitresult.root","update");
//    TTree *treename2=(TTree*)rfres.Get("bkgll");
    
    if(!update) treename->Branch("dataresult_free_minNll",&la, "dataresult_free_minNll/D");
    if(update) treename->SetBranchAddress("dataresult_free_minNll", &la);
    if(!update) treename->Branch("BF_free_minNll",&BFresult2, "BF_free_minNll/D");
    if(update) treename->SetBranchAddress("BF_free_minNll", &BFresult2);
//    if(!update) treename->Branch("migradStatus_free",&migradStatus, "smigradStatus_free/I");
//    if(update) treename->SetBranchAddress("migradStatus_free", &migradStatus);
    if(!update) treename->Branch("status_free",&statusa, "status_free/D");
    if(update) treename->SetBranchAddress("status_free", &statusa);



     cout<<" EDM value: "<<dataresult_free->edm();

//    treename->Fill();
//    treename->Write();

 //   rfrestree.Branch("CLsOneSigma",&dataresult_free->minNll(), "CLsOneSigma/D");
    

    BF->setConstant(false);
    BF->setVal(0.0);
    BF->setConstant(true);

    cout<<"Fitting dataresult_fixed"<<endl;

    RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true));

    double BFresult = BF->getVal();
    double lb=dataresult_fixed->minNll();
    double statusb=dataresult_fixed->status();

    if(!update) treename->Branch("dataresult_fixed_minNll",&lb, "dataresult_fixed_minNll/D");
    if(update) treename->SetBranchAddress("dataresult_fixed_minNll", &lb);
    if(!update) treename->Branch("BF_fixed_minNll",&BFresult, "BF_fixed_minNll/D");
    if(update) treename->SetBranchAddress("BF_fixed_minNll", &BFresult); 
    if(!update) treename->Branch("status_fixed",&statusb, "status_fixed/D");
    if(update) treename->SetBranchAddress("status_fixed", &statusb);



    double testStat = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());


    if(!update) treename->Branch("TestStat",&testStat, "TestStat/D");
    if(update) treename->SetBranchAddress("TestStat", &testStat);    



    if ((dataresult_fixed->covQual() !=3) || (dataresult_fixed->covQual() != 3))
    {
        if ((dataresult_fixed->edm() > 0.02) || (dataresult_free->edm() > 0.02))
        {
                testStat = -50;
        }
    }
    std::cout <<"I give you result: "<< BFresult << " " << testStat << std::endl;

    treename->Fill();
    delete dataresult_free;
    delete dataresult_fixed;
    return testStat;
}

double fitTwice(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* Bplus_Corrected_Mass, TTree* treename, bool update)
{       
    BF->setConstant(false);
    BF->setVal(CLsBF);
    BF->removeError();
    BF->setConstant(true);

    RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true));//RooFit::Save(true),RooFit::PrintLevel(-1));
    RooMinuit m(*nll);

    int migradStatus(-1000);
    int hesseStatus(-1000);
    
    migradStatus = m.migrad();
    hesseStatus = m.hesse();

    RooFitResult* dataresult_free = m.save();
    dataresult_free->Print("v");

//    RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),RooFit::NumCPU(2),RooFit::Save(true),RooFit::PrintLevel(-1));

    cout<<"Fitting dataresult_free"<<endl;    

    double la=dataresult_free->minNll();
    double BFresult2 = BF->getVal();
    double statusa= dataresult_free->status();

 //   TFile rfres("roofitresult.root","update");
//    TTree *treename2=(TTree*)rfres.Get("bkgll");
    
    if(!update) treename->Branch("dataresult_free_minNll",&la, "dataresult_free_minNll/D");
    if(update) treename->SetBranchAddress("dataresult_free_minNll", &la);
    if(!update) treename->Branch("BF_free_minNll",&BFresult2, "BF_free_minNll/D");
    if(update) treename->SetBranchAddress("BF_free_minNll", &BFresult2);
    if(!update) treename->Branch("migradStatus_free",&migradStatus, "smigradStatus_free/I");
    if(update) treename->SetBranchAddress("migradStatus_free", &migradStatus);
    if(!update) treename->Branch("hesseStatus_free",&hesseStatus, "shesseStatus_free/I");
    if(update) treename->SetBranchAddress("hesseStatus_free", &hesseStatus);



     cout<<" EDM value: "<<dataresult_free->edm();

//    treename->Fill();
//    treename->Write();

 //   rfrestree.Branch("CLsOneSigma",&dataresult_free->minNll(), "CLsOneSigma/D");
    

    BF->setConstant(false);
    BF->setVal(0.0);
    BF->setConstant(true);

    cout<<"Fitting dataresult_fixed"<<endl;

    RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true));

    double BFresult = BF->getVal();
    double lb=dataresult_fixed->minNll();
    double statusb=dataresult_fixed->status();

    if(!update) treename->Branch("dataresult_fixed_minNll",&lb, "dataresult_fixed_minNll/D");
    if(update) treename->SetBranchAddress("dataresult_fixed_minNll", &lb);
    if(!update) treename->Branch("BF_fixed_minNll",&BFresult, "BF_fixed_minNll/D");
    if(update) treename->SetBranchAddress("BF_fixed_minNll", &BFresult); 
    if(!update) treename->Branch("status_fixed",&statusb, "status_fixed/D");
    if(update) treename->SetBranchAddress("status_fixed", &statusb);



    double testStat = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());


    if(!update) treename->Branch("TestStat",&testStat, "TestStat/D");
    if(update) treename->SetBranchAddress("TestStat", &testStat);    



    if ((dataresult_fixed->covQual() !=3) || (dataresult_fixed->covQual() != 3))
    {
        if ((dataresult_fixed->edm() > 0.02) || (dataresult_free->edm() > 0.02))
        {
                testStat = -50;
        }
    }
    std::cout <<"I give you result: "<< BFresult << " " << testStat << std::endl;

    treename->Fill();
    delete dataresult_free;
    delete dataresult_fixed;
    return testStat;
}
