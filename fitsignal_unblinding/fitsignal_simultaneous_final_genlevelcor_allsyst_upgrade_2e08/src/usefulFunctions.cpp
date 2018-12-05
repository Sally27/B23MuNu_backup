#include "usefulFunctions.hpp"
#include "RooFitResult.h"
#include "ComputeChi2.hpp"
#include "TFile.h"
#include "TTree.h"
#include<iostream>
#include<sstream>
#include<string>
#include "MyCB.hpp"
#include "RooAddPdf.h"
#include "RooSimultaneous.h"
#include<vector>
#include<fstream>

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


double addinquad(vector<double> err)
{
	double res(0);
	double result(0);
	for (int p(0); p<err.size(); p++)
	{
		res+=((err.at(p))*(err.at(p)));
		// res=1.0;
		// res =sqrt((err.at(p))*((err.at(p))+(((err.at(p+1)*((err.at(p+1)));
	}
	result=sqrt(res);
	return(result);

}

void saveFitInfo_abspdf(ofstream& out, RooPlot* frame, int floatingParams, RooAbsPdf* pdf, RooFitResult* res)
{

	string separation("====================================");
	if(frame)
	{
		double chi2;
		int ndof;
		ndof=frame->GetNbinsX();
		//cout<<"NUMBER OF BINS: po "<<ndof<<endl;
		chi2=frame->chiSquare();
		//      out<<separation<<endl;
		//   chi2=frame->chiSquare();
		//ComputeChi2 computeChi2;
		//computeChi2.getChi2(frame, floatingParams, chi2, ndof);
		out<<"Chi2 = "<<d2s(chi2)<<" / "<<i2s(ndof-floatingParams)<<endl;
		out<<"Prob = "<<d2s(TMath::Prob(double(chi2), double(ndof-floatingParams)))<<endl;
		out<<"Standard way chi2: "<<d2s(frame->chiSquare())<<endl;
		out<<"Standard way chi2 with float params: "<<d2s(frame->chiSquare(floatingParams))<<endl;
	}

	if(pdf)
	{
		out<<separation<<endl;
		RooArgSet* vars = pdf->getVariables();
		vars->writeToStream(out, false);
	}

         if(res)
        {
                out<<separation<<endl;
        out<<" ------------------Fit Results------------"<<endl;
        out<<" Status: "<<res->status()<<endl;
        out<<" edm: "<<res->edm()<<endl;
        out<<" minll: "<<res->minNll()<<endl;
        out<<" Floating parameters  "<<res->floatParsInit()<<endl;
        out<<" Constant parameters  "<<res->constPars()<<endl;
        out<<" Floating parameters at the end:  "<<res->floatParsFinal()<<endl;
        out<<" CovQuality:  "<<res->covQual()<<endl;
        out<<" status:  "<<res->status()<<endl;
        ostringstream os;
        res->printArgs(os);
        ostringstream os2;
        res->printMultiline(os2, 1, kTRUE);
                out<<separation<<endl;
        out<<" Show only non-verbose:  "<<os.str()<<endl;
                out<<separation<<endl;
        out<<" Show verbose:  "<<os2.str()<<endl;

        const TMatrixDSym& cor = res->correlationMatrix();
        const TMatrixDSym& cov = res->covarianceMatrix();

        Int_t nrows= cor.GetNrows();
        Int_t ncols= cor.GetNcols();

                out<<separation<<endl;
        out<<" Correlation Matrix: "<<endl;
        for (int i(0); i<nrows; i++)
        {
                for (int j(0); j<ncols; j++)
                {
                        out<<"    "<<cor[i][j];
                        if(j==ncols-1){

                                out<<endl;}
                }
        }

        out<<" Covariance Matrix: "<<endl;
        for (int i(0); i<nrows; i++)
        {
                for (int j(0); j<ncols; j++)
                {
                        out<<"    "<<cov[i][j];
                        if(j==ncols-1){

                                out<<endl;}
                }
        }
        std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
        std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

	cor.Print("v"); //call function
	cov.Print();
	std::cout.rdbuf(coutbuf); //reset to standard output again
	}



}
void saveFitInfo_simpdf(ofstream& out, RooPlot* frame, int floatingParams, RooSimultaneous* pdf, RooFitResult* res)
{

	string separation("====================================");
	if(frame)
	{
		double chi2;
		int ndof;
		ndof=frame->GetNbinsX();
		//cout<<"NUMBER OF BINS: po "<<ndof<<endl;
		chi2=frame->chiSquare();
		//      out<<separation<<endl;
		//   chi2=frame->chiSquare();
		//ComputeChi2 computeChi2;
		//computeChi2.getChi2(frame, floatingParams, chi2, ndof);
		out<<"Chi2 = "<<d2s(chi2)<<" / "<<i2s(ndof-floatingParams)<<endl;
		out<<"Prob = "<<d2s(TMath::Prob(double(chi2), double(ndof-floatingParams)))<<endl;
		out<<"Standard way chi2: "<<d2s(frame->chiSquare())<<endl;
		out<<"Standard way chi2 with float params: "<<d2s(frame->chiSquare(floatingParams))<<endl;
	}

	if(pdf)
	{
		out<<separation<<endl;
		RooArgSet* vars = pdf->getVariables();
		vars->writeToStream(out, false);
	}

         if(res)
        {
                out<<separation<<endl;
        out<<" ------------------Fit Results------------"<<endl;
        out<<" Status: "<<res->status()<<endl;
        out<<" edm: "<<res->edm()<<endl;
        out<<" minll: "<<res->minNll()<<endl;
        out<<" Floating parameters  "<<res->floatParsInit()<<endl;
        out<<" Constant parameters  "<<res->constPars()<<endl;
        out<<" Floating parameters at the end:  "<<res->floatParsFinal()<<endl;
        out<<" CovQuality:  "<<res->covQual()<<endl;
        out<<" status:  "<<res->status()<<endl;
        ostringstream os;
        res->printArgs(os);
        ostringstream os2;
        res->printMultiline(os2, 1, kTRUE);
                out<<separation<<endl;
        out<<" Show only non-verbose:  "<<os.str()<<endl;
                out<<separation<<endl;
        out<<" Show verbose:  "<<os2.str()<<endl;

        const TMatrixDSym& cor = res->correlationMatrix();
        const TMatrixDSym& cov = res->covarianceMatrix();

        Int_t nrows= cor.GetNrows();
        Int_t ncols= cor.GetNcols();

                out<<separation<<endl;
        out<<" Correlation Matrix: "<<endl;
        for (int i(0); i<nrows; i++)
        {
                for (int j(0); j<ncols; j++)
                {
                        out<<"    "<<cor[i][j];
                        if(j==ncols-1){

                                out<<endl;}
                }
        }

        out<<" Covariance Matrix: "<<endl;
        for (int i(0); i<nrows; i++)
        {
                for (int j(0); j<ncols; j++)
                {
                        out<<"    "<<cov[i][j];
                        if(j==ncols-1){

                                out<<endl;}
                }
        }
        std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
        std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

	cor.Print("v"); //call function
	cov.Print();
	std::cout.rdbuf(coutbuf); //reset to standard output again
	}



}
void saveFitInfo_addpdf(ofstream& out, RooPlot* frame, int floatingParams, RooAddPdf* pdf, RooFitResult* res)
{

	string separation("====================================");
	if(frame)
	{
		double chi2;
		int ndof;
		ndof=frame->GetNbinsX();
		//cout<<"NUMBER OF BINS: po "<<ndof<<endl;
		chi2=frame->chiSquare();
		//      out<<separation<<endl;
		//   chi2=frame->chiSquare();
		//ComputeChi2 computeChi2;
		//computeChi2.getChi2(frame, floatingParams, chi2, ndof);
		out<<"Chi2 = "<<d2s(chi2)<<" / "<<i2s(ndof-floatingParams)<<endl;
		out<<"Prob = "<<d2s(TMath::Prob(double(chi2), double(ndof-floatingParams)))<<endl;
		out<<"Standard way chi2: "<<d2s(frame->chiSquare())<<endl;
		out<<"Standard way chi2 with float params: "<<d2s(frame->chiSquare(floatingParams))<<endl;
	}

	if(pdf)
	{
		out<<separation<<endl;
		RooArgSet* vars = pdf->getVariables();
		vars->writeToStream(out, false);
	}

         if(res)
        {
                out<<separation<<endl;
        out<<" ------------------Fit Results------------"<<endl;
        out<<" Status: "<<res->status()<<endl;
        out<<" edm: "<<res->edm()<<endl;
        out<<" minll: "<<res->minNll()<<endl;
        out<<" Floating parameters  "<<res->floatParsInit()<<endl;
        out<<" Constant parameters  "<<res->constPars()<<endl;
        out<<" Floating parameters at the end:  "<<res->floatParsFinal()<<endl;
        out<<" CovQuality:  "<<res->covQual()<<endl;
        out<<" status:  "<<res->status()<<endl;
        ostringstream os;
        res->printArgs(os);
        ostringstream os2;
        res->printMultiline(os2, 1, kTRUE);
                out<<separation<<endl;
        out<<" Show only non-verbose:  "<<os.str()<<endl;
                out<<separation<<endl;
        out<<" Show verbose:  "<<os2.str()<<endl;

        const TMatrixDSym& cor = res->correlationMatrix();
        const TMatrixDSym& cov = res->covarianceMatrix();

        Int_t nrows= cor.GetNrows();
        Int_t ncols= cor.GetNcols();

                out<<separation<<endl;
        out<<" Correlation Matrix: "<<endl;
        for (int i(0); i<nrows; i++)
        {
                for (int j(0); j<ncols; j++)
                {
                        out<<"    "<<cor[i][j];
                        if(j==ncols-1){

                                out<<endl;}
                }
        }

        out<<" Covariance Matrix: "<<endl;
        for (int i(0); i<nrows; i++)
        {
                for (int j(0); j<ncols; j++)
                {
                        out<<"    "<<cov[i][j];
                        if(j==ncols-1){

                                out<<endl;}
                }
        }
        std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
        std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

	cor.Print("v"); //call function
	cov.Print();
	std::cout.rdbuf(coutbuf); //reset to standard output again
	}



}

  


double addstatandsyst(double stat, double syst)
{
        double res(0);
        res =sqrt((stat*stat)+(syst*syst));
        return(res);

}

double round_to_digits(double value, int digits)
{
    if (value == 0.0) // otherwise it will return 'nan' due to the log10() of zero
        return 0.0;

    double factor = pow(10.0, digits - ceil(log10(fabs(value))));
    return round(value * factor) / factor;
}



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

string d2s(double nbr, int nfixed )
{
   stringstream ss;
   //if(nfixed>=1) ss<<fixed<<setprecision(nfixed)<<nbr;
   //else ss<<nbr;
   ss<<nbr;
   return ss.str();
}


string i2s(int i)
{
   string ret;
   ostringstream os;
   os<<i;
   return os.str();
}


string roundToError(RooRealVar const& var, bool wantLatex)
{
   valError ve;
   ve.val=var.getVal();
   ve.err= var.getError();
   return roundToError(ve, wantLatex);
}

string roundToError(valError& ve, bool wantLatex)
{
   int power(floor(TMath::Log10(ve.err)));
   double todivide(TMath::Power(10, power-2));
   int err3dig(TMath::Nint(ve.err/todivide));
   int nfixed;
   if(err3dig<=354 || err3dig>=950)
   {
      todivide = TMath::Power(10, power-1);
      nfixed = 1-power;
   }
   if(err3dig>=355 && err3dig<=949)
   {
      todivide = TMath::Power(10, power);
      nfixed = 0-power;
   }
   ve.err = todivide*TMath::Nint(ve.err/todivide);
   ve.val = todivide*TMath::Nint(ve.val/todivide);
   string ret(d2s(ve.val, nfixed)+"+-"+d2s(ve.err, nfixed));
   if(wantLatex) ret= "$"+d2s(ve.val, nfixed)+"\\pm"+d2s(ve.err, nfixed)+"$";
   return ret;
}

double returnVar(string filename, string decaytreename, string variable)
{
        
        TFile f_pid(filename.c_str(),"READ");
        TTree* t =(TTree*)f_pid.Get(decaytreename.c_str());
        double eff;
        t->SetBranchAddress(variable.c_str(), &eff);
        double var_of_interest(0);

	for(int s(0);s<t->GetEntries();s++){
		t->GetEntry(s);
		cout<<variable<<" exists"<<endl;
		var_of_interest=eff;


	}

        return(var_of_interest);

}

double returnEff(string filename, string decaytreename, string variable)
{
        
        TFile f_pid(filename.c_str(),"READ");
        TTree* t =(TTree*)f_pid.Get(decaytreename.c_str());
        string *branchname=0;
        double eff;
        t->SetBranchAddress("cut_fill", &branchname);
        t->SetBranchAddress("effi_fill", &eff);
        
        double var_of_interest(0);
        for(int s(0);s<t->GetEntries();s++){
                t->GetEntry(s);
                
                if(*branchname==variable){
                        cout<<variable<<" exists"<<endl;
                        var_of_interest=eff;
                }

        
        }

return(var_of_interest);

}


void savePullPlot(RooPlot& graph, string fileName)
{
   RooHist* hist = graph.pullHist(0,0,true);
   TGraphAsymmErrors tgae(hist->GetN());
   tgae.SetTitle("");
   double x(0);
   double y(0);
   for(int i(0); i<hist->GetN(); ++i)
   {
      hist->GetPoint(i,x,y);
      tgae.SetPoint(i,x,y);
      tgae.SetPointError(i, hist->GetErrorXlow(i), hist->GetErrorXhigh(i),
            hist->GetErrorYlow(i), hist->GetErrorYhigh(i));
   }

   TCanvas c_pullplot("pullplot", "pullplot", 600, 150);
   tgae.SetMarkerStyle(20);
   tgae.SetMarkerSize(1);
   tgae.SetMarkerColor(1);

   tgae.GetXaxis()->SetLimits(graph.GetXaxis()->GetXmin(), graph.GetXaxis()->GetXmax());
   tgae.GetYaxis()->SetRangeUser(-5,5);
   tgae.GetYaxis()->SetLabelSize(0.1);
   tgae.GetXaxis()->SetNdivisions(0);
   tgae.GetYaxis()->SetNdivisions(503);
   tgae.GetYaxis()->SetLabelSize(0.133);

   TLine line1(graph.GetXaxis()->GetXmin(), -3, graph.GetXaxis()->GetXmax(), -3);
   line1.SetLineColor(2);
   TLine line2(graph.GetXaxis()->GetXmin(), 3, graph.GetXaxis()->GetXmax(), 3);
   line2.SetLineColor(2);

   tgae.Draw("AP");
   line1.Draw();
   line2.Draw();

   TFile f(fileName.c_str(), "RECREATE");

   c_pullplot.Write();

   f.Close();
}

void saveFitInfo(ofstream& out, RooPlot* frame, int floatingParams, RooAbsPdf* pdf)
{
   
	string separation("====================================");
	if(frame)
	{
		double chi2;
		int ndof;
		out<<separation<<endl;
		ComputeChi2 computeChi2;
		computeChi2.getChi2(frame, floatingParams, chi2, ndof);
		out<<"Chi2 = "<<chi2<<" / "<<ndof-floatingParams<<endl;
		out<<"Prob = "<<TMath::Prob(chi2, ndof-floatingParams)<<endl;

	}

	if(pdf)
	{
		out<<separation<<endl;
		RooArgSet* vars = pdf->getVariables();
		vars->writeToStream(out, false);
	}
}

void saveFitInfo_cb(ofstream& out, RooPlot* frame, int floatingParams, MyCB pdf, RooFitResult* res)
{

        string separation("====================================");
        if(frame)
        {
                double chi2;
                int ndof;
                out<<separation<<endl;
                ComputeChi2 computeChi2;
                computeChi2.getChi2(frame, floatingParams, chi2, ndof);
                out<<"Chi2 = "<<chi2<<" / "<<ndof-floatingParams<<endl;
                out<<"Prob = "<<TMath::Prob(chi2, ndof-floatingParams)<<endl;

        }
               out<<separation<<endl;
                RooArgSet* vars = pdf.getVariables();
                vars->writeToStream(out, false);
               if(res)
                {
                        out<<" ------------------Fit Results------------"<<endl;
                        out<<" Status: "<<res->status()<<endl;
                        out<<" edm: "<<res->edm()<<endl;
                        out<<" minll: "<<res->minNll()<<endl;
                        out<<" Floating parameters  "<<res->floatParsInit()<<endl;
                        out<<" Constant parameters  "<<res->constPars()<<endl;
                        out<<" Floating parameters at the end:  "<<res->floatParsFinal()<<endl;
                        out<<" CovQuality:  "<<res->covQual()<<endl;
                        out<<" status:  "<<res->status()<<endl;
                        ostringstream os;
                        res->printArgs(os);
                        ostringstream os2;
                        res->printMultiline(os2, 1, kTRUE);
                        out<<" Show only non-verbose:  "<<os.str()<<endl;
                        out<<" Show verbose:  "<<os2.str()<<endl;

                        const TMatrixDSym& cor = res->correlationMatrix();
                        const TMatrixDSym& cov = res->covarianceMatrix();

                        Int_t nrows= cor.GetNrows();
                        Int_t ncols= cor.GetNcols();

                        out<<" Correlation Matrix: "<<endl;
                        for (int i(0); i<nrows; i++)
                        {
                                for (int j(0); j<ncols; j++)
                                {
                                        out<<"    "<<cor[i][j];
                                        if(j==ncols-1){

                                                out<<endl;}
                                }
                        }
                       out<<" Covariance Matrix: "<<endl;
		       for (int i(0); i<nrows; i++)
		       {
			       for (int j(0); j<ncols; j++)
			       {
				       out<<"    "<<cov[i][j];
				       if(j==ncols-1){

					       out<<endl;}
			       }
		       }
		       std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
		       std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

		       //        cout<<"LOLILOL"<<endl;
		       cor.Print("v"); //call function
		       cov.Print();
		       //       res->Print("v");
		       //       cout<<"LOLILOL2"<<endl;
		       //      std::cin.rdbuf(cinbuf);   //reset to standard input again
		       std::cout.rdbuf(coutbuf); //reset to standard output again
		       //: out<<" Correlation Matrix:  "<<os3.str()<<endl;
		}
}


void saveFitInfoExtended(ofstream& out, RooPlot* frame, int floatingParams, RooAbsPdf* pdf, RooFitResult* res)
{
   
	string separation("====================================");
	if(frame)
	{
		double chi2;
		int ndof;
                ndof=frame->GetNbinsX();
             //cout<<"NUMBER OF BINS: po "<<ndof<<endl;
                chi2=frame->chiSquare();
	//	out<<separation<<endl;
             //   chi2=frame->chiSquare();
		//ComputeChi2 computeChi2;
		//computeChi2.getChi2(frame, floatingParams, chi2, ndof);
		out<<"Chi2 = "<<d2s(chi2)<<" / "<<i2s(ndof-floatingParams)<<endl;
		out<<"Prob = "<<d2s(TMath::Prob(double(chi2), double(ndof-floatingParams)))<<endl;
                out<<"Standard way chi2: "<<d2s(frame->chiSquare())<<endl;         
                out<<"Standard way chi2 with float params: "<<d2s(frame->chiSquare(floatingParams))<<endl;
	}

	if(pdf)
	{
		out<<separation<<endl;
		RooArgSet* vars = pdf->getVariables();
		vars->writeToStream(out, false);
	}

        if(res)
        {
        out<<" ------------------Fit Results------------"<<endl;
        out<<" Status: "<<res->status()<<endl;
        out<<" edm: "<<res->edm()<<endl;
        out<<" minll: "<<res->minNll()<<endl;
        out<<" Floating parameters  "<<res->floatParsInit()<<endl;
        out<<" Constant parameters  "<<res->constPars()<<endl;
        out<<" Floating parameters at the end:  "<<res->floatParsFinal()<<endl;
        out<<" CovQuality:  "<<res->covQual()<<endl;
        out<<" status:  "<<res->status()<<endl;
        ostringstream os;
        res->printArgs(os);
        ostringstream os2;
        res->printMultiline(os2, 1, kTRUE);
        out<<" Show only non-verbose:  "<<os.str()<<endl;
        out<<" Show verbose:  "<<os2.str()<<endl;
      
        const TMatrixDSym& cor = res->correlationMatrix(); 
        const TMatrixDSym& cov = res->covarianceMatrix(); 

        Int_t nrows= cor.GetNrows();
        Int_t ncols= cor.GetNcols();
       
        out<<" Correlation Matrix: "<<endl;
	for (int i(0); i<nrows; i++)
	{
		for (int j(0); j<ncols; j++)
		{
			out<<"    "<<cor[i][j];
			if(j==ncols-1){

				out<<endl;}
		}
	}
        
        out<<" Covariance Matrix: "<<endl;
	for (int i(0); i<nrows; i++)
	{
		for (int j(0); j<ncols; j++)
		{
			out<<"    "<<cov[i][j];
			if(j==ncols-1){

				out<<endl;}
		}
	}
	std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

//        cout<<"LOLILOL"<<endl;
	cor.Print("v"); //call function
        cov.Print();
 //       res->Print("v");
 //       cout<<"LOLILOL2"<<endl;
//	std::cin.rdbuf(cinbuf);   //reset to standard input again
	std::cout.rdbuf(coutbuf); //reset to standard output again 
       //: out<<" Correlation Matrix:  "<<os3.str()<<endl;
        }

}


void make2DPullPlot(TH1* data, TH1* model, TH1* pull)
{
   int nX(data->GetXaxis()->GetNbins());
   int nY(data->GetYaxis()->GetNbins());

   double currentData;
   double currentModel;
   double currentError;

   for(int iX(1); iX<=nX; ++iX)
   {
      for(int iY(1); iY<=nY; ++iY)
      {
         currentData = data->GetBinContent(iX, iY);
         currentModel = model->GetBinContent(iX, iY);
         currentError = data->GetBinError(iX, iY);
         //currentError = sqrt(data->GetBinContent(iX, iY));
         if(currentError == 0) currentError=1.;
         pull->SetBinContent(iX, iY, (currentData-currentModel) / currentError);
         if( abs( (currentData-currentModel) / currentError )>2.5)
	 {
            cout<<"BIG PULL: data: "<<currentData<<", model: "<<currentModel<<", error: "<<currentError<<endl;
         }
      }
   }
}

void lhcbStyle(double fontsize)
{
   // define names for colours
   Int_t black  = 1;
   Int_t red    = 2;
   Int_t green  = 3;
   Int_t blue   = 4;
   Int_t yellow = 5;
   Int_t magenta= 6;
   Int_t cyan   = 7;
   Int_t purple = 9;


   ////////////////////////////////////////////////////////////////////
   // PURPOSE:
   //
   // This macro defines a standard style for (black-and-white) 
   // "publication quality" LHCb ROOT plots. 
   //
   // USAGE:
   //
   // Include the lines
   //   gROOT->ProcessLine(".L lhcbstyle.C");
   //   lhcbStyle();
   // at the beginning of your root macro.
   //
   // Example usage is given in myPlot.C
   //
   // COMMENTS:
   //
   // Font:
   // 
   // The font is chosen to be 132, this is Times New Roman (like the text of
   //  your document) with precision 2.
   //
   // "Landscape histograms":
   //
   // The style here is designed for more or less square plots.
   // For longer histograms, or canvas with many pads, adjustements are needed. 
   // For instance, for a canvas with 1x5 histograms:
   //  TCanvas* c1 = new TCanvas("c1", "L0 muons", 600, 800);
   //  c1->Divide(1,5);
   //  Adaptions like the following will be needed:
   //  gStyle->SetTickLength(0.05,"x");
   //  gStyle->SetTickLength(0.01,"y");
   //  gStyle->SetLabelSize(0.15,"x");
   //  gStyle->SetLabelSize(0.1,"y");
   //  gStyle->SetStatW(0.15);
   //  gStyle->SetStatH(0.5);
   //
   // Authors: Thomas Schietinger, Andrew Powell, Chris Parkes, Niels Tuning
   // Maintained by Editorial board member (currently Niels)
   ///////////////////////////////////////////////////////////////////


   // Use times new roman, precision 2 
   Int_t lhcbFont        = 132;  // Old LHCb style: 62;
   // Line thickness
   Double_t lhcbWidth    = 2.00; // Old LHCb style: 3.00;
   // Text size
   Double_t lhcbTSize    = fontsize;//0.06; 

   // use plain black on white colors
   gROOT->SetStyle("Plain");
   TStyle *lhcbStyle= new TStyle("lhcbStyle","LHCb plots style");

   //lhcbStyle->SetErrorX(0); //  don't suppress the error bar along X

   lhcbStyle->SetFillColor(1);
   lhcbStyle->SetFillStyle(1001);   // solid
   lhcbStyle->SetFrameFillColor(0);
   lhcbStyle->SetFrameBorderMode(0);
   lhcbStyle->SetPadBorderMode(0);
   lhcbStyle->SetPadColor(0);
   lhcbStyle->SetCanvasBorderMode(0);
   lhcbStyle->SetCanvasColor(0);
   lhcbStyle->SetStatColor(0);
   lhcbStyle->SetLegendBorderSize(0);
   lhcbStyle->SetLegendFont(132);

   // If you want the usual gradient palette (blue -> red)
   lhcbStyle->SetPalette(1);
   // If you want colors that correspond to gray scale in black and white:
   //   int colors[8] = {0,5,7,3,6,2,4,1};
   //   lhcbStyle->SetPalette(8,colors);

   // set the paper & margin sizes
   lhcbStyle->SetPaperSize(20,26);
   lhcbStyle->SetPadTopMargin(0.05);
   lhcbStyle->SetPadRightMargin(0.05); // increase for colz plots
   lhcbStyle->SetPadBottomMargin(0.16);
   lhcbStyle->SetPadLeftMargin(0.14);

   // use large fonts
   lhcbStyle->SetTextFont(lhcbFont);
   lhcbStyle->SetTextSize(lhcbTSize);
   lhcbStyle->SetLabelFont(lhcbFont,"x");
   lhcbStyle->SetLabelFont(lhcbFont,"y");
   lhcbStyle->SetLabelFont(lhcbFont,"z");
   lhcbStyle->SetLabelSize(lhcbTSize,"x");
   lhcbStyle->SetLabelSize(lhcbTSize,"y");
   lhcbStyle->SetLabelSize(lhcbTSize,"z");
   lhcbStyle->SetTitleFont(lhcbFont);
   lhcbStyle->SetTitleFont(lhcbFont,"x");
   lhcbStyle->SetTitleFont(lhcbFont,"y");
   lhcbStyle->SetTitleFont(lhcbFont,"z");
   lhcbStyle->SetTitleSize(1.2*lhcbTSize,"x");

   lhcbStyle->SetTitleSize(1.2*lhcbTSize,"y");
   lhcbStyle->SetTitleSize(1.2*lhcbTSize,"z");

   // use medium bold lines and thick markers
   lhcbStyle->SetLineWidth(lhcbWidth);
   lhcbStyle->SetFrameLineWidth(lhcbWidth);
   lhcbStyle->SetHistLineWidth(lhcbWidth);
   lhcbStyle->SetFuncWidth(lhcbWidth);
   lhcbStyle->SetGridWidth(lhcbWidth);
   lhcbStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
   lhcbStyle->SetMarkerStyle(20);
   lhcbStyle->SetMarkerSize(1.0);

   // label offsets
   lhcbStyle->SetLabelOffset(0.010,"X");
   lhcbStyle->SetLabelOffset(0.010,"Y");

   // by default, do not display histogram decorations:
   lhcbStyle->SetOptStat(0);
   //lhcbStyle->SetOptStat("emr");  // show only nent -e , mean - m , rms -r
   // full opts at http://root.cern.ch/root/html/TStyle.html#TStyle:SetOptStat
   lhcbStyle->SetStatFormat("6.3g"); // specified as c printf options
   lhcbStyle->SetOptTitle(0);
   lhcbStyle->SetOptFit(0);
   //lhcbStyle->SetOptFit(1011); // order is probability, Chi2, errors, parameters
   //titles
   lhcbStyle->SetTitleOffset(0.95,"X");
   lhcbStyle->SetTitleOffset(0.95,"Y");
   lhcbStyle->SetTitleOffset(1.2,"Z");
   lhcbStyle->SetTitleFillColor(0);
   lhcbStyle->SetTitleStyle(0);
   lhcbStyle->SetTitleBorderSize(0);
   lhcbStyle->SetTitleFont(lhcbFont,"title");
   lhcbStyle->SetTitleX(0.0);
   lhcbStyle->SetTitleY(1.0);
   lhcbStyle->SetTitleW(1.0);
   lhcbStyle->SetTitleH(0.05);

   // look of the statistics box:
   lhcbStyle->SetStatBorderSize(0);
   lhcbStyle->SetStatFont(lhcbFont);
   lhcbStyle->SetStatFontSize(0.05);
   lhcbStyle->SetStatX(0.9);
   lhcbStyle->SetStatY(0.9);
   lhcbStyle->SetStatW(0.25);
   lhcbStyle->SetStatH(0.15);

   // put tick marks on top and RHS of plots
   //   lhcbStyle->SetPadTickX(1);
   //   lhcbStyle->SetPadTickY(1);

   // histogram divisions: only 5 in x to avoid label overlaps
   lhcbStyle->SetNdivisions(505,"x");
   lhcbStyle->SetNdivisions(510,"y");


   gROOT->SetStyle("lhcbStyle");
   gROOT->ForceStyle();

   // add LHCb label
   TPaveText* lhcbName = new TPaveText(gStyle->GetPadLeftMargin() + 0.05,
         0.87 - gStyle->GetPadTopMargin(),
         gStyle->GetPadLeftMargin() + 0.20,
         0.95 - gStyle->GetPadTopMargin(),
         "BRNDC");
   lhcbName->AddText("LHCb");
   lhcbName->SetFillColor(0);
   lhcbName->SetTextAlign(12);
   lhcbName->SetBorderSize(0);

   TText *lhcbLabel = new TText();
   lhcbLabel->SetTextFont(lhcbFont);
   lhcbLabel->SetTextColor(1);
   lhcbLabel->SetTextSize(lhcbTSize);
   lhcbLabel->SetTextAlign(12);

   TLatex *lhcbLatex = new TLatex();
   lhcbLatex->SetTextFont(lhcbFont);
   lhcbLatex->SetTextColor(1);
   lhcbLatex->SetTextSize(lhcbTSize);
   lhcbLatex->SetTextAlign(12);

   cout << "-------------------------" << endl;
   cout << "Set LHCb Style - Feb 2012" << endl;
   cout << "-------------------------" << endl;

}

