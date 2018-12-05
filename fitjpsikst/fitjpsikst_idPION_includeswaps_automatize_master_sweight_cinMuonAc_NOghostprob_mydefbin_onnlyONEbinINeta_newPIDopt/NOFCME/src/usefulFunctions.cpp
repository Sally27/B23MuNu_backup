#include "usefulFunctions.hpp"
#include "RooFitResult.h"
#include "TTreeFormula.h"
#include "TObjArray.h"
#include "TTree.h"
#include "TH3D.h"
#include "TH2D.h"
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

double normalerror(double val1, double err1, double val2, double err2)
{

double errorratio(0);
errorratio=double(val1/val2)*sqrt(((err1/val1)*(err1/val1))+((err2/val2)*(err2/val2)));
return(errorratio);
}

string cleanForTables(string str)
{
   size_t st(0);

   string toreplace("_.*/#.,[]{}()+-=:&<>");
   for(int i(0); i<toreplace.size(); ++i)
   {
      while(st != string::npos)
      {
         st = str.find(toreplace[i]);
         if(st!=string::npos) str = str.replace(st, 1, "");
      }
      st = 0;
   }

   return str;
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




void copyTreeWithNewVar(TTree*& tNew, TTree* tOld, string cut, string formula, string newVarName)
{
   setBranchStatusTTF(tOld, cut);
   setBranchStatusTTF(tOld, formula);

   TTreeFormula newVarTTF("newVarTTF", formula.c_str(), tOld);
   if(cut == "") cut = "1";
   TTreeFormula cutTTF("cutTTF", cut.c_str(), tOld);
   TTreeFormula varTTF("varTTF", formula.c_str(), tOld);


   tNew = tOld->CloneTree(0);

   double newVarVal(0);
   if(formula != "") tNew->Branch(newVarName.c_str(), &newVarVal, (newVarName+"/D").c_str() );

   cout<<"Filling tree with new var... ";

   for(int i(0); i<tOld->GetEntries(); ++i)
   {
      tOld->GetEntry(i);

      if(cutTTF.EvalInstance() )
      {
         if(formula != "") newVarVal = newVarTTF.EvalInstance();
         tNew->Fill();
      }
   }

   cout<<"done! New tree has: "<<tNew->GetEntries()<<" entries."<<endl;
}


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
        return(effofcut);
}


vector<double> binxjack(){

        vector<double> PArr;




        PArr.push_back(3000.0);
        PArr.push_back(6000.0);
        PArr.push_back(9300.0);
        PArr.push_back(10000.0);
        PArr.push_back(12600.0);
        PArr.push_back(15600.0);
        PArr.push_back(17500.0);
        PArr.push_back(21500.0);
        PArr.push_back(27000.0);
        PArr.push_back(32000.0);
        PArr.push_back(40000.0);
        PArr.push_back(60000.0);
        PArr.push_back(70000.0);
        PArr.push_back(100000.0);


        const int p = 13;





        for(int j(0); j<(p+1); ++j)
        {

                cout<<"  "<<PArr.at(j)<<",";

        }
        cout<<"."<<endl;


        return PArr;
}
vector<double> binx(){

        vector<double> PArr;


        PArr.push_back(3000.0);
        PArr.push_back(9300.0);
        PArr.push_back(15600.0);
        PArr.push_back(19000.0);


        const int p = 18;



        for(int j(4); j<(p+1); ++j)
        {
                PArr.push_back(PArr.at(j-1) + 5400.0);

        }



        cout<<"P binning: ";


        for(int j(0); j<(p+1); ++j)
        {

                cout<<"  "<<PArr.at(j)<<",";

        }
        cout<<"."<<endl;


        return PArr;
}

vector<double> binycourse(){
	vector<double> EtaArr; 
	const int eta=1;
	EtaArr.push_back(1.5); 
        EtaArr.push_back(5.0);	


 
	cout<<"ETA binning: "; 
	
        for(int j(0); j<(eta+1); ++j)
	{
		cout<<"  "<<EtaArr.at(j)<<",";
	}

	cout<<"."<<endl; return EtaArr;
}

vector<double> biny(){
	vector<double> EtaArr; 
	const int eta=4;
	EtaArr.push_back(1.5); 
	


        for(int j(1); j<(eta+1); ++j) 
	{ 
		EtaArr.push_back(EtaArr[j-1] + 0.875); 
	}
 
	cout<<"ETA binning: "; 
	
        for(int j(0); j<(eta+1); ++j)
	{
		cout<<"  "<<EtaArr.at(j)<<",";
	}

	cout<<"."<<endl; return EtaArr;
}

vector<double> binz(){ 

	vector<double> nTracksArr; 
	const int ntracks=4;
	nTracksArr.push_back(0.0);
	nTracksArr.push_back(50.0);
	nTracksArr.push_back(200.0);
	nTracksArr.push_back(300.0);
	nTracksArr.push_back(500.0);
	cout<<"ntracks binning: "; 
	for(int j(0); j<(ntracks+1); ++j) 
	{ 

		cout<<"  "<<nTracksArr.at(j)<<",";
	} 
	cout<<"."<<endl; return nTracksArr;
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


string cleanAbsolutelyNameString(string str)
{
   size_t st(0);

   string toreplace("_.");
   for(int i(0); i<toreplace.size(); ++i)
   {
      while(st != string::npos)
      {
         st = str.find(toreplace[i]);
         if(st!=string::npos) str = str.replace(st, 1, " ");
      }
      st = 0;
   }

   return str;
}


void plotMergedFitsPrettyLogy(vector<double> binningx, vector<double> binningy, string pidcut, string state, string path)
{

	int numberofbins = (binningx.size()-1)*(binningy.size()-1);
	const int numberofpdfs = numberofbins/9;
	cout<<" Number of pdf will be "<<numberofpdfs<<endl;
	int counterm(0);
	int counterk(0);

	for(int s(0); s<numberofpdfs ;s++)
	{
		TCanvas* canvshifttotal = new TCanvas("PID","PID",800,800) ;
		canvshifttotal->Divide(3,3);
		int z(0);
		for(int k(0); k<(binningx.size()-1) ;k++){
			for(int m(0); m<(binningy.size()-1) ;m++){
				if(z==0){
					k=counterk;
					m=counterm;
				}
//				string pidcut = "K_PIDK<0";
				string kinbinstring = "K_P_"+d2s(binningx.at(k))+"_K_P_"+d2s(binningx.at(k+1))+"_K_ETA_"+d2s(binningy.at(m))+"_K_ETA_"+d2s(binningy.at(m+1));
				cout<<"Here P bin "<< k<<" ETA bin "<<m<<endl;
				cout<<"This is the string "<<kinbinstring<<endl;
				TFile f((path+"/plotJpsiKstFitLogyPretty"+cleanNameString(kinbinstring)+"_"+cleanNameString(pidcut)+".root").c_str(),"READ");
				TCanvas* canvTot = (TCanvas*)f.Get("canvTot");
				canvshifttotal->cd(z+1) ; gPad->SetLeftMargin(0.15) ; canvTot->DrawClonePad();// canvTot->GetYaxis()->SetTitleOffset(1.4) ; canvTot->GetXaxis()->SetTitle("Corrected Mass") ;  canvTot->Draw() ;
				z++;
				cout<<" z  is"<<z<<endl;
				if(z==9)
				{

					counterm=m;
					cout<<"I am breaking from m"<<endl;
					cout<<"Value of m "<< counterm<<endl;
					break; 
				}
			}
			if(z==9)
			{
				counterk=k;
				cout<<"I am breaking from K"<<endl;
				cout<<"Value of k "<< counterk<<endl;
				break;
			}
		}
		canvshifttotal->SaveAs(("../MergedFits/ResultofFits_Pretty_Log_"+state+"_ALL"+i2s(s)+".pdf").c_str());
		delete canvshifttotal;
	}


}
void plotMergedFitsPretty(vector<double> binningx, vector<double> binningy, string pidcut, string state, string path)
{

	int numberofbins = (binningx.size()-1)*(binningy.size()-1);
	const int numberofpdfs = numberofbins/9;
	cout<<" Number of pdf will be "<<numberofpdfs<<endl;
	int counterm(0);
	int counterk(0);

	for(int s(0); s<numberofpdfs ;s++)
	{
		TCanvas* canvshifttotal = new TCanvas("PID","PID",800,800) ;
		canvshifttotal->Divide(3,3);
		int z(0);
		for(int k(0); k<(binningx.size()-1) ;k++){
			for(int m(0); m<(binningy.size()-1) ;m++){
				if(z==0){
					k=counterk;
					m=counterm;
				}
//				string pidcut = "K_PIDK<0";
				string kinbinstring = "K_P_"+d2s(binningx.at(k))+"_K_P_"+d2s(binningx.at(k+1))+"_K_ETA_"+d2s(binningy.at(m))+"_K_ETA_"+d2s(binningy.at(m+1));
				cout<<"Here P bin "<< k<<" ETA bin "<<m<<endl;
				cout<<"This is the string "<<kinbinstring<<endl;
				TFile f((path+"/plotJpsiKstFitPretty"+cleanNameString(kinbinstring)+"_"+cleanNameString(pidcut)+".root").c_str(),"READ");
				TCanvas* canvTot = (TCanvas*)f.Get("canvTot");
				canvshifttotal->cd(z+1) ; gPad->SetLeftMargin(0.15) ; canvTot->DrawClonePad();// canvTot->GetYaxis()->SetTitleOffset(1.4) ; canvTot->GetXaxis()->SetTitle("Corrected Mass") ;  canvTot->Draw() ;
				z++;
				cout<<" z  is"<<z<<endl;
				if(z==9)
				{

					counterm=m;
					cout<<"I am breaking from m"<<endl;
					cout<<"Value of m "<< counterm<<endl;
					break; 
				}
			}
			if(z==9)
			{
				counterk=k;
				cout<<"I am breaking from K"<<endl;
				cout<<"Value of k "<< counterk<<endl;
				break;
			}
		}
		canvshifttotal->SaveAs(("../MergedFits/ResultofFits_Pretty_"+state+"_ALL"+i2s(s)+".pdf").c_str());
		delete canvshifttotal;
	}


}
void plotMergedFits(vector<double> binningx, vector<double> binningy, string pidcut, string state, string path)
{

	int numberofbins = (binningx.size()-1)*(binningy.size()-1);
	const int numberofpdfs = numberofbins/9;
	cout<<" Number of pdf will be "<<numberofpdfs<<endl;
	int counterm(0);
	int counterk(0);

	for(int s(0); s<numberofpdfs ;s++)
	{
		TCanvas* canvshifttotal = new TCanvas("PID","PID",800,800) ;
		canvshifttotal->Divide(3,3);
		int z(0);
		for(int k(0); k<(binningx.size()-1) ;k++){
			for(int m(0); m<(binningy.size()-1) ;m++){
				if(z==0){
					k=counterk;
					m=counterm;
				}
//				string pidcut = "K_PIDK<0";
				string kinbinstring = "K_P_"+d2s(binningx.at(k))+"_K_P_"+d2s(binningx.at(k+1))+"_K_ETA_"+d2s(binningy.at(m))+"_K_ETA_"+d2s(binningy.at(m+1));
				cout<<"Here P bin "<< k<<" ETA bin "<<m<<endl;
				cout<<"This is the string "<<kinbinstring<<endl;
				TFile f((path+"/plotJpsiKst_"+cleanNameString(kinbinstring)+"_"+cleanNameString(pidcut)+".root").c_str(),"READ");
				TCanvas* canvTot = (TCanvas*)f.Get("canv");
				canvshifttotal->cd(z+1) ; gPad->SetLeftMargin(0.15) ; canvTot->DrawClonePad();// canvTot->GetYaxis()->SetTitleOffset(1.4) ; canvTot->GetXaxis()->SetTitle("Corrected Mass") ;  canvTot->Draw() ;
				z++;
				cout<<" z  is"<<z<<endl;
				if(z==9)
				{

					counterm=m;
					cout<<"I am breaking from m"<<endl;
					cout<<"Value of m "<< counterm<<endl;
					break; 
				}
			}
			if(z==9)
			{
				counterk=k;
				cout<<"I am breaking from K"<<endl;
				cout<<"Value of k "<< counterk<<endl;
				break;
			}
		}
		canvshifttotal->SaveAs(("../MergedFits/ResultofFits"+state+"_ALL"+i2s(s)+".pdf").c_str());
		delete canvshifttotal;
	}


}

//void prepare2Dhist(string piddir, string name, vector<double> xbin, vector<double> ybin)
//{
//        double* PArr=&xbin[0];
//        double* EtaArr=&ybin[0];
//   
//        const Int_t XBINS = (xbin.size()-1);
//        const Int_t YBINS = (ybin.size()-1);          
//
//        cout<<"Number of Xbins: "<<XBINS<<endl;      
//        cout<<"Number of Ybins: "<<YBINS<<endl;
//
//      	TCanvas *canv=new TCanvas("plotmy3d","plotmy3d",600,600);
//
//	TH2* h2 = new TH2D("PIDHist_sally", "PIDHist_sally", XBINS, PArr, YBINS, EtaArr);
//
//	float myfav;
//	int z(0);
//	vector<float> kindistribution;
//
//	for (int i=0; i<XBINS+0; i++) {
//		for (int j=0; j<YBINS+0; j++) {
//				myfav=3.8/2*double(j);
//				kindistribution.push_back(myfav);
//				h2->SetBinContent(i,j,myfav);
//				z++;
//		}
//	}
//
//	float check;
//	for (int i=0; i<XBINS+0; i++) {
//		for (int j=0; j<YBINS+0; j++) {
//				check = h2->GetBinContent(i,j);
//		}
//	}
//
//        TFile *F1 = new TFile((piddir+"PID_2D.root").c_str(),"UPDATE");
//        h2->Write("", TObject::kOverwrite);
//        F1->Close();
//        delete F1;
//        delete h2;
//        delete canv;
//
//
//return;
//}
//void prepare3Dhist(string piddir, string name, vector<double> xbin, vector<double> ybin, vector<double> zbin)
//{
//        double* PArr=&xbin[0];
//        double* EtaArr=&ybin[0];
//        double* nTracksArr=&zbin[0];
//   
//        const Int_t XBINS = (xbin.size()-1);
//        const Int_t YBINS = (ybin.size()-1);          
//        const Int_t ZBINS = (zbin.size()-1);        
//
//        cout<<"Number of Xbins: "<<XBINS<<endl;      
//        cout<<"Number of Ybins: "<<YBINS<<endl;
//        cout<<"Number of Zbins: "<<ZBINS<<endl;
//
//      	TCanvas *canv=new TCanvas("plotmy3d","plotmy3d",600,600);
//
//	TH3* h3 = new TH3D("PIDHist_sally", "PIDHist_sally", XBINS, PArr, YBINS, EtaArr, ZBINS, nTracksArr);
//
//	float myfav;
//	int z(0);
//	vector<float> kindistribution;
//
//	for (int i=0; i<XBINS+0; i++) {
//		for (int j=0; j<YBINS+0; j++) {
//			for (int k=0; k<ZBINS+0; k++) {
//				myfav=3.8/2*double(j);
//				kindistribution.push_back(myfav);
//				h3->SetBinContent(i,j,k, myfav);
//				z++;
//			}
//		}
//	}
//
//	float check;
//	for (int i=0; i<XBINS+0; i++) {
//		for (int j=0; j<YBINS+0; j++) {
//			for (int k=0; k<ZBINS+0; k++) {
//				check = h3->GetBinContent(i,j,k);
//			}
//		}
//	}
//
//        TFile *F1 = new TFile((piddir+"PID_3D.root").c_str(),"UPDATE");
//        h3->Write("", TObject::kOverwrite);
//        F1->Close();
//        delete F1;
//        delete h3;
//        delete canv;
//
//
//return;
//}


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
//      ComputeChi2 computeChi2;
//      computeChi2.getChi2(frame, floatingParams, chi2, ndof);
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

