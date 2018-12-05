#include "usefulFunctions.hpp"
#include "RooFitResult.h"
#include "ComputeChi2.hpp"

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


void savePullPlot_Sally(RooPlot& frame, string nameofhisto, RooRealVar* Bplus_Corrected_Mass, string fileName)
{
	frame.Print("V");
	auto dataHist = (RooHist*)frame.getHist((nameofhisto.c_str()));

	cout<<"NGet "<<dataHist->GetN()<<endl;
	double x(0);
	double y(0);
	for(int i(0); i<dataHist->GetN(); ++i)
	{
		cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;   
		if((dataHist->GetY()[i])==0.0)
		{
			cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;
			dataHist->SetPoint(i,x,1000);
		}
	}
	auto curve1 = (RooCurve*)frame.getObject(1);
	auto hres1 = dataHist->makePullHist(*curve1,true);

	RooPlot* frame10 = Bplus_Corrected_Mass->frame(Title(""));
	frame10->addPlotable(hres1,"P");
	TCanvas c_pullplot("pullplot", "pullplot", 600, 150);
	frame10->GetYaxis()->SetRangeUser(-5,5);
	frame10->GetYaxis()->SetLabelSize(0.1);
	frame10->GetXaxis()->SetNdivisions(0);
	frame10->GetYaxis()->SetNdivisions(503);
	frame10->GetYaxis()->SetLabelSize(0.133);

	TLine line1(4000, -3, 7000, -3);
	line1.SetLineColor(2);
	TLine line2(4000, 3, 7000, 3);
	line2.SetLineColor(2);
	frame10->GetXaxis()->SetTitle("") ;  frame10->SetTitle("") ; frame10->Draw() ; line1.Draw("same"); line2.Draw("same");   


	TFile f(fileName.c_str(), "RECREATE");

	c_pullplot.Write();

	f.Close();
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

   tgae.GetXaxis()->SetTitle("") ;  tgae.SetTitle("");   

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
