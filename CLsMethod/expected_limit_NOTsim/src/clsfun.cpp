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
#include "RooWorkspace.h"

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

std::vector<RooDataSet*> generateData_con(RooRealVar* BF,double BFval,RooAbsPdf* model_LL,RooRealVar* mass, int nToys, RooArgSet con) 
{
	std::vector<RooDataSet*> datasets;
	for (int i = 0; i < nToys; ++i)
	{
		BF->setConstant(false);
		BF->setVal(BFval);

		RooDataSet* dataset_LL = model_LL->generate(RooArgSet(*mass),RooFit::Extended(true), ExternalConstraints(con));
//		RooDataSet* dataset_DD = model_DD->generate(RooArgSet(*mass),RooFit::Extended(true));
         	RooDataSet* dataset = new RooDataSet("data","combined data",*mass,RooFit::Import(*dataset_LL));
		datasets.push_back(dataset);

	}
	return datasets;
}

std::vector<RooDataSet*> generateData(RooRealVar* BF,double BFval,RooAbsPdf* model_LL,RooRealVar* mass, int nToys) 
{
	std::vector<RooDataSet*> datasets;
	for (int i = 0; i < nToys; ++i)
	{
		BF->setConstant(false);
		BF->setVal(BFval);

		RooDataSet* dataset_LL = model_LL->generate(RooArgSet(*mass),RooFit::Extended(true));
//		RooDataSet* dataset_DD = model_DD->generate(RooArgSet(*mass),RooFit::Extended(true));
         	RooDataSet* dataset = new RooDataSet("data","combined data",*mass,RooFit::Import(*dataset_LL));
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


void calculateFOM_chi2(RooRealVar* BF,RooAbsPdf* model,int nToys, double CLsBF, int toyfit)
{
        cout<<"Calculate the figure of merit from the fit: "<<endl;
        TFile fw(("Fitresults_forCLs_BF"+cleanNameString(d2s(BF->getVal()))+"_"+i2s(toyfit)+"_"+i2s(nToys)+".root").c_str());

        RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
        if(!workspaceFit)
        {
                cerr<<"ERROR: no workspace found in file "<<endl;
                return;
        }

        RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
        //RooDataSet* data = (RooDataSet*)workspaceFit->data(("data"));
        //RooAbsPdf* model_total = workspaceFit->pdf(("normsigpdf"));
	RooAbsPdf* model_exp = workspaceFit->pdf(("newexpoun"));
	RooAbsPdf* model_sig = workspaceFit->pdf(("blah"));
	RooAbsPdf* model_pr = workspaceFit->pdf(("newpartreco"));
	RooAbsPdf* model_misid = workspaceFit->pdf(("misidModel"));
	RooRealVar* number_exp = workspaceFit->var(("nexp"));
	RooAbsReal* number_sig = workspaceFit->function(("nsigform"));
	RooAbsReal* number_pr = workspaceFit->function(("npartreco"));
	RooRealVar* number_misid = workspaceFit->var(("misid_scaled"));





	//RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
	Bplus_Corrected_Mass->setRange("new",4000,7000);
	Bplus_Corrected_Mass->setRange("high",5501,7000);
	Bplus_Corrected_Mass->setRange("low",4000,4499);
	Bplus_Corrected_Mass->setRange("fit",4500,5500);


	if( !model_exp || !model_sig || !model_pr || !model_misid || !number_exp )//|| !number_sig || !number_pr || !number_misid)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
		//              cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<endl;
		return;
	}

	//      Bplus_Corrected_Mass.setBins(60);
      
        RooAbsReal* combinatorial = model_exp->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
        RooAbsReal* combinatorialfit = model_exp->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* combinatorialfit2 = model_exp->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
        RooFormulaVar combinatorialres("combinatorialres", "combinatorialres", "(@1/@0)*@2" , RooArgList(*combinatorial, *combinatorialfit, *number_exp ));
        RooFormulaVar combinatorialres2("combinatorialres2", "combinatorialres2", "(@1/@0)*@2" , RooArgList(*combinatorial, *combinatorialfit2, *number_exp ));
        cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< combinatorial->getVal()<<endl;
        cout<<"Integral in the combinatorial wrt figreg: " << combinatorialfit->getVal()<<endl;
        cout<<"Integral: outcome :"<<combinatorialres.getVal()<<endl;

        RooAbsReal* mymisid = model_misid->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
        RooAbsReal* mymisidfit = model_misid->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* mymisidfit2 = model_misid->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
        RooFormulaVar mymisidres("mymisidres", "mymisidres", "(@1/@0)*@2" , RooArgList(*mymisid, *mymisidfit, *number_misid ));
        RooFormulaVar mymisidres2("mymisidres2", "mymisidres2", "(@1/@0)*@2" , RooArgList(*mymisid, *mymisidfit2, *number_misid ));
        cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mymisid->getVal()<<endl;
        cout<<"Integral in the misid wrt figreg: " << mymisidfit->getVal()<<endl;
        cout<<"Integral: outcome :"<<mymisidres.getVal()<<endl;

        RooAbsReal* mysig = model_sig->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
        RooAbsReal* mysigfit = model_sig->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* mysigfit2 = model_sig->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
        RooFormulaVar mysigres("mysigres", "mysigres", "(@1/@0)*@2" , RooArgList(*mysig, *mysigfit, *number_sig));
        RooFormulaVar mysigres2("mysigres2", "mysigres2", "(@1/@0)*@2" , RooArgList(*mysig, *mysigfit2, *number_sig));
        cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mysig->getVal()<<endl;
        cout<<"Integral in the signal wrt figreg: " << mysigfit->getVal()<<endl;
        cout<<"Integral: outcome :"<<mysigres.getVal()<<endl;

        RooAbsReal* mypr = model_pr->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
        RooAbsReal* myprfit = model_pr->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* myprfit2 = model_pr->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
        RooFormulaVar myprres("myprres", "myprres", "(@1/@0)*@2" , RooArgList(*mypr, *myprfit, *number_pr));
        RooFormulaVar myprres2("myprres2", "myprres2", "(@1/@0)*@2" , RooArgList(*mypr, *myprfit2, *number_pr));
        cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mypr->getVal()<<endl;
        cout<<"Integral in the partreco wrt figreg: " << myprfit->getVal()<<endl;
        cout<<"Integral: outcome :"<<myprres.getVal()<<endl;

       double punzimetric(0);
        punzimetric=double(mysigres.getVal())/(sqrt(double(combinatorialres.getVal())+double(mymisidres.getVal())+double(myprres.getVal()))+double(3.0/2.0));

        cout<<"My punzi calc: "<< sqrt(double(combinatorialres.getVal())+double(mymisidres.getVal())+double(myprres.getVal())) << " " <<combinatorialres.getVal() << " " << mymisidres.getVal()<< " " << (myprres.getVal())<<endl;
        cout<<"My punzi metric: "<< punzimetric << "Num of sig"<< mysigres.getVal() << endl;

        string tags=(cleanNameString(d2s(BF->getVal()))).c_str();

        ofstream out;
        out.open((("FOM_chi2_"+cleanNameString(d2s(BF->getVal()))+"_"+i2s(toyfit)+"_"+i2s(nToys)+".txt")).c_str());
        out<<"\\begin{table}[h]"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
        out<<"\\hline"<<endl;
        out<<"Sample &   cut & 3fb$^{-1}$ \\\\ "<<endl;
        out<<"misid  & "<<tags<<" & "<< number_misid->getVal() <<" \\\\ " <<endl;
        out<<"mcsig  & "<<tags<<" & "<< number_sig->getVal() <<"  \\\\ "<<endl;
        out<<"combi  & "<<tags<<" & "<< number_exp->getVal() <<" \\\\ "<<endl;
        out<<"partreco  & "<<"no cut"<<" & " << number_pr->getVal() << " \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"Sample 4.5-5.0 &  cut & 3fb$^{-1}$ \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"misid  & "<<tags<<" & "<< mymisidres.getVal() <<" \\\\ " <<endl;
        out<<"mcsig  & "<<tags<<" & "<< mysigres.getVal() <<"  \\\\ "<<endl;
        out<<"combi  & "<<tags<<" & "<< combinatorialres.getVal() <<" \\\\ "<<endl;
        out<<"partreco  & "<<"no cut"<< " & " << myprres.getVal() << " \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"Sample OUT &  cut & 3fb$^{-1}$ \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"misid  & "<<tags<<" & "<< mymisidres2.getVal() <<" \\\\ " <<endl;
        out<<"mcsig  & "<<tags<<" & "<< mysigres2.getVal() <<"  \\\\ "<<endl;
        out<<"combi  & "<<tags<<" & "<< combinatorialres2.getVal() <<" \\\\ "<<endl;
        out<<"partreco  & "<<"no cut"<< " & " << myprres2.getVal() << " \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"punzi metric & " <<" S/sqrt(B)+3/2 & "<< punzimetric << " & "<< " \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{STATISTICS.txt}"<<endl;
        out<<"\\end{table}"<<endl;


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
    Bplus_Corrected_Mass->setRange("full3",4000,7000);

    model->getParameters(*Bplus_Corrected_Mass)->Print("s") ; 
    RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),ExternalConstraints(constraints),RooFit::Save(true));

    if (toyfit==5 || toyfit==6)
    {


    TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
    RooPlot* frame1 = Bplus_Corrected_Mass->frame(Title("NOFCME")) ;
    data->plotOn(frame1) ;
    model->plotOn(frame1,RooFit::Range("full3"), RooFit::NormRange("full3"));
    model->plotOn(frame1,Components("newexpoun"),LineStyle(kDashed),LineColor(kRed),RooFit::Range("full3"), RooFit::NormRange("full3"));
    model->plotOn(frame1,Components("misidModel"),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("full3"), RooFit::NormRange("full3"));
    model->plotOn(frame1,Components("newpartreco"),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("full3"), RooFit::NormRange("full3"));
    model->plotOn(frame1,Components("blah"),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("full3"), RooFit::NormRange("full3"));

    TFile file2(("Fitresults_forCLs_BF"+cleanNameString(d2s(BF->getVal()))+"_"+i2s(toyfit)+"_"+i2s(nToys)+".root").c_str(), "RECREATE");
    RooWorkspace workspaceFit2("workspaceFit", "workspaceFit");
    workspaceFit2.import(*Bplus_Corrected_Mass);
    workspaceFit2.import(*model);
    workspaceFit2.Write("", TObject::kOverwrite);
    cout<<"Workspace for fit has been saved:"<<endl;
    workspaceFit2.Print();
    file2.Close();

    calculateFOM_chi2(BF, model, nToys, CLsBF, toyfit);

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
    cout<<"These are the parameters"<<endl;
    model->getParameters(*Bplus_Corrected_Mass)->Print("s") ;

    RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Extended(true),ExternalConstraints(constraints),RooFit::Save(true));

    if (toyfit==5 || toyfit==6)
    {
    //plotting 5 and 6 th toy

    TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
    RooPlot* frame1 = Bplus_Corrected_Mass->frame(Title("NOFCME")) ;
    data->plotOn(frame1) ;
    model->plotOn(frame1,RooFit::Range("full3"), RooFit::NormRange("full3"));
    model->plotOn(frame1,Components("newexpoun"),LineStyle(kDashed),LineColor(kRed),RooFit::Range("full3"), RooFit::NormRange("full3"));
    model->plotOn(frame1,Components("misidModel"),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("full3"), RooFit::NormRange("full3"));
    model->plotOn(frame1,Components("newpartreco"),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("full3"), RooFit::NormRange("full3"));
    model->plotOn(frame1,Components("blah"),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("full3"), RooFit::NormRange("full3"));

    TFile file2(("Fitresults_forCLs_BF"+cleanNameString(d2s(BF->getVal()))+"_"+i2s(toyfit)+"_"+i2s(nToys)+".root").c_str(), "RECREATE");
    RooWorkspace workspaceFit2("workspaceFit", "workspaceFit");
    workspaceFit2.import(*Bplus_Corrected_Mass);
    workspaceFit2.import(*model);
    workspaceFit2.Write("", TObject::kOverwrite);
    cout<<"Workspace for fit has been saved:"<<endl;
    workspaceFit2.Print();
    file2.Close();

    calculateFOM_chi2(BF, model, nToys, CLsBF, toyfit);


    gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
    firstfit->SaveAs(("fitTwiceOld2_dataresult_fixed_fitnumber_"+i2s(toyfit)+"_from_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(BF->getVal()))+".pdf").c_str());
    delete firstfit;
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
