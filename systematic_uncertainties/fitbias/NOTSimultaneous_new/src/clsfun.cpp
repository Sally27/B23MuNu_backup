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
#include "TLegend.h"

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

      TCanvas* canvasgaus= new TCanvas(" ", " ",800,800);
      gStyle->SetOptFit(1111); //Fitting staff

      gStyle->SetOptStat(0); //Set off stat box
      hsignal_DLL->Fit("Gaussian","RQ");
      hsignal_DLL->SetLineColor(kBlack);
 
      hsignal_DLL->GetXaxis()->SetTitle("N^{orig}_{sig}-N^{fit}_{sig}/#sigma^{fit}");
     
      gPad->SetLeftMargin(0.15) ; hsignal_DLL->GetYaxis()->SetTitleOffset(1.4);
      hsignal_DLL->GetYaxis()->SetTitle("Number of pseudo-experiments");
       
      hsignal_DLL->Draw("E");



      double amp = rufit -> GetParameter(0);
      double mean = rufit -> GetParameter(1);
      double sigma = rufit -> GetParameter(2);

      myfile << "Fitted Histogram with Gaussian! "<< endl;
      myfile << "0th parameter of gaussian: " << amp <<endl;
      myfile << "1st parameter of gaussian / mean: " << mean <<endl;
      myfile << "2nd parameter of gaussian / sigma: " << sigma <<endl;

  //    TLegend *leg = new TLegend(0.2,0.6,0.5,0.8);
  //    leg->AddEntry((TObject*)0,("Mean : "+d2s(mean)).c_str(),"");
  //    leg->AddEntry((TObject*)0,("Sigma : "+d2s(sigma)).c_str(),"");
  //    leg->SetTextSize(0.04);
  //    leg->Draw("same");


      canvasgaus->SaveAs(("SignalBias_"+category+"_numoftoys_"+i2s(nToys)+"_injectsig"+d2s(CLsBF)+".pdf").c_str());
      canvasgaus->SaveAs(("SignalBias_"+category+"_numoftoys_"+i2s(nToys)+"_injectsig"+d2s(CLsBF)+".root").c_str());
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


std::vector<RooDataSet*> generateData(RooRealVar* BF,double BFval,RooAbsPdf* model_LL,RooRealVar* mass, int nToys) 
{
	std::vector<RooDataSet*> datasets;
	for (int i = 0; i < nToys; ++i)
	{
		BF->setConstant(false);
		BF->setVal(BFval);

		RooDataSet* dataset_LL = model_LL->generate(RooArgSet(*mass),RooFit::Extended(true));
         	RooDataSet* dataset = new RooDataSet("data","combined data",*mass,RooFit::Import(*dataset_LL));
                cout<<"Number of entries generated: "<<dataset->sumEntries()<<endl;
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


double fitGeneratedSample(RooRealVar* BF,RooAbsReal* number_sig,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* Bplus_Corrected_Mass, TTree* treename, bool update, int toyfit, RooArgSet constraints, double original_number_sig)
{

//    BF->setConstant(false);
//    BF->setVal(CLsBF);
//    BF->removeError();
//    BF->setConstant(true);
        double original_br = BF->getVal();

    BF->setConstant(false);
    BF->setRange(-1.0,1.0);

    model->getParameters(*Bplus_Corrected_Mass)->Print("s") ; 
    RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),ExternalConstraints(constraints),RooFit::Save(true), RooFit::Minos(true), RooFit::PrintLevel(-1));

    if (toyfit==5 || toyfit==6)
    {


    TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
    RooPlot* frame1 = Bplus_Corrected_Mass->frame(Title("NOFCME")) ;
    data->plotOn(frame1) ;
    model->plotOn(frame1);
    gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
    firstfit->SaveAs(("fitTwiceOld2_dataresult_free_fitnumber_"+i2s(toyfit)+"_from_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(BF->getVal()))+".pdf").c_str());
    delete firstfit;
    }
    cout<<"Fitting dataresult_free"<<endl;    

    double la=dataresult_free->minNll();
    double BFresult2 = BF->getVal();
    double statusa= dataresult_free->status();
    double numberofsignaloriginal=original_number_sig;
    // New stuff //
    double numberofsignalfitted(0);
    double errorsifnalfitted(0);
    numberofsignalfitted=number_sig->getVal();
    errorsifnalfitted=number_sig->getPropagatedError(*dataresult_free);
    cout<<"fitted "<<numberofsignalfitted<<" with error "<< errorsifnalfitted<<" values"<<endl; 
     double error_br = BF->getPropagatedError(*dataresult_free);
    double biasstudy=((numberofsignaloriginal-numberofsignalfitted)/errorsifnalfitted);

    //        double la=dataresult_free->minNll();
    //        double BFresult2 = BF->getVal();
    //        double error_br = BF->getPropagatedError(*dataresult_free);
    //        double statusa= dataresult_free->status();
    //
    //        double numberofsignaloriginal=original_number_sig;
    //        double numberofsignalfitted(0);
    //        double errorsifnalfitted(0);
    //        numberofsignalfitted=(number_sig_low->getVal())+(number_sig_high->getVal());
    //        errorsifnalfitted=sqrt(((number_sig_low->getPropagatedError(*dataresult_free))*(number_sig_low->getPropagatedError(*dataresult_free)))+(number_sig_high->getPropagatedError(*dataresult_free))*(number_sig_high->getPropagatedError(*dataresult_free)));
    //        cout<<"fitted "<<numberofsignalfitted<<" with error "<< errorsifnalfitted<<" values"<<endl;
    //
    //        double biasstudy=((numberofsignaloriginal-numberofsignalfitted)/errorsifnalfitted);

    double bias_br = ((original_br - BFresult2)/error_br);



    //        double numberofsignalfitted_low = number_sig_low->getVal();//+(number_sig_high->getVal());
    //        double numberofsignalfitted_high = number_sig_high->getVal();

    //        double errorsifnalfitted_low = (number_sig_low->getPropagatedError(*dataresult_free));
    //        double errorsifnalfitted_high = (number_sig_high->getPropagatedError(*dataresult_free));

    //        double biasstudy_low = ((original_number_sig_low-numberofsignalfitted_low)/errorsifnalfitted_low);
    //        double biasstudy_high = ((original_number_sig_high-numberofsignalfitted_high)/errorsifnalfitted_high);


    double BF_err_asslow = BF->getAsymErrorLo();
    double BF_err_asshigh = BF->getAsymErrorHi();

    double BF_err_ass(-1000.0);
    if (BFresult2>original_br){BF_err_ass=(-1.0)*BF_err_asslow; cout<<"Low Error"<< BF_err_ass<<endl;}
    if (BFresult2<original_br){BF_err_ass=BF_err_asshigh; cout<<"High Error"<< BF_err_ass<<endl;}

    double BF_bias_ass= ((original_br - BFresult2)/BF_err_ass);








    if(!update) treename->Branch("dataresult_free_minNll",&la, "dataresult_free_minNll/D");
    if(update) treename->SetBranchAddress("dataresult_free_minNll", &la);
    if(!update) treename->Branch("BF_free_minNll",&BFresult2, "BF_free_minNll/D");
    if(update) treename->SetBranchAddress("BF_free_minNll", &BFresult2);
    if(!update) treename->Branch("status_free",&statusa, "status_free/D");
    if(update) treename->SetBranchAddress("status_free", &statusa);
    if(!update) treename->Branch("numberofsignalfitted",&numberofsignalfitted, "numberofsignalfitted/D");
    if(update) treename->SetBranchAddress("numberofsignalfitted", &numberofsignalfitted);
    if(!update) treename->Branch("numberofsignaloriginal",&numberofsignaloriginal, "numberofsignaloriginal/D");
    if(update) treename->SetBranchAddress("numberofsignaloriginal", &numberofsignaloriginal);
    if(!update) treename->Branch("errorsifnalfitted",&errorsifnalfitted, "errorsifnalfitted/D");
    if(update) treename->SetBranchAddress("errorsifnalfitted", &errorsifnalfitted);
    if(!update) treename->Branch("biasstudy",&biasstudy, "biasstudy/D");
    if(update) treename->SetBranchAddress("biasstudy", &biasstudy);


    if(!update) treename->Branch("BF_fit",&BFresult2, "BF_fit/D");
    if(update) treename->SetBranchAddress("BF_fit", &BFresult2);

    if(!update) treename->Branch("BF_ori",&original_br, "BF_ori/D");
    if(update) treename->SetBranchAddress("BF_ori", &original_br);

    if(!update) treename->Branch("BF_err",&error_br, "BF_err/D");
    if(update) treename->SetBranchAddress("BF_err", &error_br);

    if(!update) treename->Branch("BF_err_ass",&BF_err_ass, "BF_err_ass/D");
    if(update) treename->SetBranchAddress("BF_err_ass", &BF_err_ass);

    if(!update) treename->Branch("BF_bias_ass",&BF_bias_ass, "BF_bias_ass/D");
    if(update) treename->SetBranchAddress("BF_bias_ass", &BF_bias_ass);

    if(!update) treename->Branch("BF_bias",&bias_br, "BF_bias/D");
    if(update) treename->SetBranchAddress("BF_bias", &bias_br);


    treename->Fill();
    delete dataresult_free;

    return(biasstudy);
    
}



double fitTwiceOld(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* Bplus_Corrected_Mass, TTree* treename, bool update, int toyfit, RooArgSet constraints)
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

   // Bplus_Corrected_Mass->setRange("new",4000,7000);


    model->getParameters(*Bplus_Corrected_Mass)->Print("s") ; 
    RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),ExternalConstraints(constraints),RooFit::Save(true));

    if (toyfit==5 || toyfit==6)
    {


    TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
    RooPlot* frame1 = Bplus_Corrected_Mass->frame(Title("NOFCME")) ;
    data->plotOn(frame1) ;
    model->plotOn(frame1);
    gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
    firstfit->SaveAs(("fitTwiceOld2_dataresult_free_fitnumber_"+i2s(toyfit)+"_from_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(BF->getVal()))+".pdf").c_str());
    delete firstfit;
    }
    cout<<"Fitting dataresult_free"<<endl;    

    double la=dataresult_free->minNll();
    double BFresult2 = BF->getVal();
    double statusa= dataresult_free->status();

    
    if(!update) treename->Branch("dataresult_free_minNll",&la, "dataresult_free_minNll/D");
    if(update) treename->SetBranchAddress("dataresult_free_minNll", &la);
    if(!update) treename->Branch("BF_free_minNll",&BFresult2, "BF_free_minNll/D");
    if(update) treename->SetBranchAddress("BF_free_minNll", &BFresult2);
    if(!update) treename->Branch("status_free",&statusa, "status_free/D");
    if(update) treename->SetBranchAddress("status_free", &statusa);



     cout<<" EDM value: "<<dataresult_free->edm();

 //   rfrestree.Branch("CLsOneSigma",&dataresult_free->minNll(), "CLsOneSigma/D");
    

    BF->setConstant(false);
    BF->setVal(0.0);
    BF->setConstant(true);

    cout<<"Fitting dataresult_fixed"<<endl;

    RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Extended(true),ExternalConstraints(constraints),RooFit::Save(true));

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
