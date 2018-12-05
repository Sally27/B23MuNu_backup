#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "PlotMisidVariations.hpp"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "TCanvas.h"
#include "TTree.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooMinuit.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooStats/SPlot.h"
#include "TTreeFormula.h"
#include "RooGaussian.h"
#include "MyCB.hpp"
#include "TLegend.h"
#include "TPaveLabel.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include "TMatrixDSym.h"
#include "TDirectory.h"
#include "RooChi2Var.h"
#include "RooMinimizer.h"
#include "RooMinuit.h"
#include "TMinuitMinimizer.h"
#include "RooExtendPdf.h"
#include "RooMultiVarGaussian.h"
#include "RooProdPdf.h"
#include "TMatrixT.h"

using namespace std;
using namespace RooFit;

int PlotMisidVariations::get_numberofhisto()
{
return(numberofhistograms);
}

int PlotMisidVariations::get_numberoftoys()
{
return(numberoftoys);
}


double PlotMisidVariations::fitmisidone(string type, string dir ,string filename, string weight, string species)
{
	TFile* f = new TFile((dir+"/"+filename+type+".root").c_str());
	TTree* treek = (TTree*)f->Get("DecayTree");

	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
	Bplus_Corrected_Mass.setRange("sideband",4000,6000);
        Bplus_Corrected_Mass.setBins(60);

	RooRealVar crossfeedweight((weight.c_str()),"crossfeedweight", 0.0 ,1.0);
	RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
	RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treek), WeightVar(weight.c_str()));

	RooPlot* frame11 = Bplus_Corrected_Mass.frame(Title(("MisIDShape_"+species).c_str())) ;
	RooPlot* frame12 = Bplus_Corrected_Mass.frame(Title(("MisIDShape_Normalized_"+species).c_str())) ;
	dk.plotOn(frame11);
	dkw.plotOn(frame11,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	dkw.plotOn(frame12,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	double kaonmisid;
	kaonmisid =dkw.sumEntries();
	TPaveLabel *t3 = new TPaveLabel(0.45,0.6,0.9,0.8, Form("Total MisID = %f",kaonmisid),"brNDC");
        t3->SetTextSize(0.2);
	frame12->addObject(t3);



	TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,400) ;
	canv5->Divide(2,1) ;
	canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->GetXaxis()->SetTitle("Corrected Mass") ;  frame11->Draw() ;
	canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->GetXaxis()->SetTitle("Corrected Mass") ; frame12->Draw() ;
	canv5->SaveAs((workdir+"misid_"+filename+"_"+type+"_"+weight+".pdf").c_str());
        //delete t3;
	delete canv5;
        //delete t3;
        f->Close();
        return(kaonmisid);
       

}


void PlotMisidVariations::create_distributionhistograms(string PIDcut)
{

        
	TFile *F1 = new TFile((bindir+"/BinInfo_"+i2s(numberofhistograms)+"_"+PIDcut+".root").c_str(),"RECREATE");

	for (int i(0); i<numberofhistograms; i++)
	{
		TH1D* h_bin = new TH1D(("BinInfo_"+i2s(i)).c_str(),("BinInfo_"+i2s(i)).c_str(), 100, 0, 2);
                h_bin->Write("", TObject::kOverwrite);
                delete h_bin;

	}

       F1->Close();
       delete F1;

}


void PlotMisidVariations::create_bin_histograms(vector< vector<double> > values, string type ,string PIDcut)
{

        
	TFile *F1 = new TFile((bindir+"/BinInfo_"+i2s(numberofhistograms)+"_"+type+"_"+PIDcut+".root").c_str(),"RECREATE");

	for (int i(0); i<numberofhistograms; i++)
	{

		TH1D* h_bin = new TH1D(("BinInfo_"+i2s(i)).c_str(),("BinInfo_"+i2s(i)).c_str(), 100, 0, 2);
		for (int j(0); j<numberoftoys; j++)
		{
                        h_bin->Fill(values[i][j]);
		}

		h_bin->Write("", TObject::kOverwrite);
		delete h_bin;
	}

       F1->Close();
       delete F1;

}



void PlotMisidVariations::print_mean_and_rms(string type, string PIDcut)
{
	TFile* F1 = new TFile((bindir+"/BinInfo_"+i2s(numberofhistograms)+"_"+type+"_"+PIDcut+".root").c_str(),"READ");

        ofstream out;
        out.open((bindir+"BinInfo_"+type+"__"+PIDcut+"Summary.txt").c_str());


        vector<double> bininfo;

        out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        out<<"\\usepackage[pdftex]{graphicx}"<<endl;
        out<<"\\usepackage{url}"<<endl;
        out<<"\\usepackage{mathtools}"<<endl;
        out<<"\\usepackage{amsmath}"<<endl;
        out<<"\\usepackage{graphicx}"<<endl;
        out<<"\\usepackage[table]{xcolor}"<<endl;
        out<<"\\usepackage{amsmath,amssymb}"<<endl;
        out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        out<<"\\usepackage{colortbl}"<<endl;
        out<<"\\begin{document}"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\small"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{| l | l | l | }"<<endl;
        out<<"\\hline"<<endl;
        out<<"Bin Number & Mean & RMS \\\\ "<<endl;

	for (int l(0); l<numberofhistograms; l++){

		TH1D* h_bin= (TH1D*)F1->Get(("BinInfo_"+i2s(l)).c_str());
                cout<<h_bin->GetMean()<<" "<<h_bin->GetStdDev()<<" "<<endl;
                out<<l<<" & "<<h_bin->GetMean()<<" & "<<h_bin->GetStdDev()<<endl;

	}

        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{BinInfo_Summary.txt}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;

	TFile fw((workspacedir+"/RooWS_Error_Mean_MisidVariation_"+i2s(numberofhistograms)+"_"+i2s(numberoftoys)+"_"+type+"_"+PIDcut+".root").c_str(), "RECREATE");
	RooWorkspace workspaceVar("workspaceVar", "workspaceVar");

	for (int l(0); l<numberofhistograms; l++){
		TH1D* h_bin= (TH1D*)F1->Get(("BinInfo_"+i2s(l)).c_str());
		RooRealVar error(("ErrorVar_"+i2s(l)).c_str(),("ErrorVar_"+i2s(l)).c_str(),h_bin->GetStdDev());
		RooRealVar mean(("MeanVar_"+i2s(l)).c_str(),("MeanVar_"+i2s(l)).c_str(),h_bin->GetMean());
		workspaceVar.import(error);
		workspaceVar.import(mean);
	}
	//workspaceFit.writeToFile(workspaceFileName.c_str());
	workspaceVar.Write("", TObject::kOverwrite);
	cout<<"Workspace for error due to misid has been saved:"<<endl;
	workspaceVar.Print();
           
        fw.Close();




	F1->Close();
	delete F1;
}




void PlotMisidVariations::plot_bin_histograms(string type,string PIDcut)
{
	TFile* F1 = new TFile((bindir+"/BinInfo_"+i2s(numberofhistograms)+"_"+type+"_"+PIDcut+".root").c_str(),"READ");

	int numberofpdf = int(double(numberofhistograms)/double(9))+1;

        int z(0);
   
	for (int l(0); l<numberofpdf; l++){

		TCanvas *cv = new TCanvas("Distributions", "Distributions");
		cv->Divide(3,3);
                for (int m(0); m<9; m++)
                {
                	cv->cd(m+1);
                        TH1D* h_bin= (TH1D*)F1->Get(("BinInfo_"+i2s(z)).c_str());
                        if (!h_bin){break;}
                        if (h_bin){h_bin->Draw();}
                        z++;                      
                }

               cv->SaveAs((bindir+"/BinInfo_"+i2s(numberofhistograms)+"_"+i2s(l)+"_"+PIDcut+".pdf").c_str());
	}

       F1->Close();
       delete F1;
}





void PlotMisidVariations::fill_distributionhistograms(TH1D* h_bin,double value)
{

                cout<<"Filling with value: "<<value<<endl;
		h_bin->Fill(value);
                h_bin->Write();

}



vector<double> PlotMisidVariations::plotdistributions_perbin(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type, int toynumber, string PIDcut)
{

        TFile* s = new TFile((dir.at(0)+"/"+misidfilenames.at(0)+"_"+type+".root").c_str());
        TTree* treep = (TTree*)s->Get("DecayTree");

        RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
        Bplus_Corrected_Mass.setRange("sideband",4000,6000);
 //       Bplus_Corrected_Mass.setBins(15);
        RooRealVar crossfeedweight(weights.at(0).c_str(),weights.at(0).c_str(), 0.0 ,1.0);

        RooDataSet dp("dp","dp",RooArgSet(Bplus_Corrected_Mass),Import(*treep));
        RooDataSet dpw("dpw","dpw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treep), WeightVar(weights.at(0).c_str()));//, Import(*treew));
        dp.Print();
        dpw.Print();

        cout<<"Size of number of files "<<misidfilenames.size()<<endl;

                for(int i(1); i<misidfilenames.size(); i++)
        {
                cout<<"This is being added to misid"<<endl;

                TFile* f = new TFile((dir.at(i)+"/"+misidfilenames.at(i)+"_"+type+".root").c_str());
                TTree* treek = (TTree*)f->Get("DecayTree");

                RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
                Bplus_Corrected_Mass.setRange("sideband",4000,6000);
                RooRealVar crossfeedweight(weights.at(i).c_str(),weights.at(i).c_str(), 0.0 ,1.0);

                RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
                RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treek), WeightVar(weights.at(i).c_str()));//, Import(*treew));
                dk.Print();
                dkw.Print();

                dpw.append(dkw);
                dpw.Print("v");
                dpw.Print();
                cout<< "Sum of entries for kaon and pion:" <<dpw.sumEntries()<<endl;
                Bool_t klone;
                klone = dpw.isWeighted();
                if (klone==true)
                {
                        cout<<"My dataset is weighted!" << endl;
                }
                const RooArgSet* row5 = dpw.get(5);
                cout<<"This is 5th row weight: "<<endl;
                row5->Print("v");
                f->Close();

        }



	double misid;
	double sumofrangelow;
	double sumofrangehigh;

	double norm_low;
	double norm_high;

	sumofrangelow = dpw.sumEntries("(Bplus_Corrected_Mass < 4500)");
	sumofrangehigh = dpw.sumEntries("(Bplus_Corrected_Mass > 5500)");

	misid = dpw.sumEntries();
	norm_low = sumofrangelow/misid;
	norm_high = sumofrangehigh/misid;


	cout<<"Fractions in low region: "<<norm_low<<endl;
	cout<<"Fraction in high region: "<<norm_high<<endl;


	cout << dpw.weight() << endl;


        int desirednumofbins(15);
        Bplus_Corrected_Mass.setBins(desirednumofbins);

        TH1* myattempt=dpw.createHistogram("MyNewHisto",Bplus_Corrected_Mass);

        RooDataHist binnedData("binnedData","Binned Vesrion of my histo",RooArgSet(Bplus_Corrected_Mass),dpw);
	binnedData.Print("v");

	cout<< "Integral over histogram:" << binnedData.sum(kTRUE)<<endl; 
	cout<< "Sum of weight:" << binnedData.sum(kFALSE)<<endl;
	cout<< "Sum of entries:" << binnedData.sumEntries()<<endl;
	cout<< "Num of bins:" << binnedData.numEntries()<<endl; 

        ofstream out;
        out.open((bindir+"BinInfo_"+type+"_toynumber_"+i2s(toynumber)+"_"+PIDcut+".txt").c_str());


        vector<double> bininfo;

        out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        out<<"\\usepackage[pdftex]{graphicx}"<<endl;
        out<<"\\usepackage{url}"<<endl;
        out<<"\\usepackage{mathtools}"<<endl;
        out<<"\\usepackage{amsmath}"<<endl;
        out<<"\\usepackage{graphicx}"<<endl;
        out<<"\\usepackage[table]{xcolor}"<<endl;
        out<<"\\usepackage{amsmath,amssymb}"<<endl;
        out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        out<<"\\usepackage{colortbl}"<<endl;
        out<<"\\begin{document}"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\small"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{| l | l | l | l | }"<<endl;
        out<<"\\hline"<<endl;
        out<<"Bin Number & Value \\\\ "<<endl;
        out<<"\\hline"<<endl;
        for (int k(1);k<(myattempt->GetNbinsX()+1);k++)
        {
        out<<k<<" & "<<myattempt->GetBinContent(k)<<endl;
        bininfo.push_back(myattempt->GetBinContent(k));
        } 
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{BinInfo.txt}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;


	TPaveLabel *t2 = new TPaveLabel(0.4,0.6,0.9,0.8, Form("TotMisID = %f",misid),"brNDC");


	TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
	canvtot->Divide(2,2) ;
	canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; myattempt->GetYaxis()->SetTitleOffset(1.4) ; myattempt->Draw() ;
        t2->Draw("same");
	canvtot->SaveAs((workdir+"Create_Histo_totalmisid_"+type+"_toynumber_"+i2s(toynumber)+".pdf").c_str());

	delete canvtot;
	s->Close();
        return(bininfo);

}



void PlotMisidVariations::plotmisidcomponents_pertoy(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type, int toynumber, vector <string> &PID)
{

        TFile* s = new TFile((dir.at(0)+"/"+misidfilenames.at(0)+"_"+type+".root").c_str());
 //       TFile* s = new TFile((dir.at(0)+"/"+misidfilenames.at(0)+type+".root").c_str());
        TTree* treep = (TTree*)s->Get("DecayTree");

        RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
        Bplus_Corrected_Mass.setRange("sideband",4000,6000);
        Bplus_Corrected_Mass.setBins(15);
        RooRealVar crossfeedweight(weights.at(0).c_str(),weights.at(0).c_str(), 0.0 ,1.0);

        RooDataSet dp("dp","dp",RooArgSet(Bplus_Corrected_Mass),Import(*treep));
        RooDataSet dpw("dpw","dpw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treep), WeightVar(weights.at(0).c_str()));//, Import(*treew));
        dp.Print();
        dpw.Print();

        ofstream out;
        out.open((workdir+"misid_comp_summary_"+type+"_toynumber_"+i2s(toynumber)+".txt").c_str());
        vector<double> efficiencies2;


        out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        out<<"\\usepackage[pdftex]{graphicx}"<<endl;
        out<<"\\usepackage{url}"<<endl;
        out<<"\\usepackage{mathtools}"<<endl;
        out<<"\\usepackage{amsmath}"<<endl;
        out<<"\\usepackage{graphicx}"<<endl;
        out<<"\\usepackage[table]{xcolor}"<<endl;
        out<<"\\usepackage{amsmath,amssymb}"<<endl;
        out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        out<<"\\usepackage{colortbl}"<<endl;
        out<<"\\begin{document}"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\small"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{| l | l | l | l | }"<<endl;
        out<<"\\hline"<<endl;
        out<<"Filename & type & weight & Number  \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<(misidfilenames.at(0)).c_str()<<" & "<<(type).c_str()<<" & "<<(weights.at(0)).c_str()<<" & "<< dpw.sumEntries() <<" \\\\ "<<endl;


 //       fitmisidone(type, dir.at(0) , misidfilenames.at(0), weights.at(0), species.at(0));
        cout<<"Size of number of files "<<misidfilenames.size()<<endl;

                for(int i(1); i<misidfilenames.size(); i++)
        {
                cout<<"This is being added to misid"<<endl;
   //             fitmisidone(type, dir.at(i) , misidfilenames.at(i), weights.at(i), species.at(i));

   //             TFile* f = new TFile((dir.at(i)+"/"+misidfilenames.at(i)+type+".root").c_str());
                TFile* f = new TFile((dir.at(i)+"/"+misidfilenames.at(i)+"_"+type+".root").c_str());
                TTree* treek = (TTree*)f->Get("DecayTree");

                RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
                Bplus_Corrected_Mass.setRange("sideband",4000,6000);
                RooRealVar crossfeedweight(weights.at(i).c_str(),weights.at(i).c_str(), 0.0 ,1.0);

                RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
                RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treek), WeightVar(weights.at(i).c_str()));//, Import(*treew));
                dk.Print();
                dkw.Print();
//                Bplus_Corrected_Mass.setBins(60);

                dpw.append(dkw);
                dpw.Print("v");
                dpw.Print();
                cout<< "Sum of entries for kaon and pion:" <<dpw.sumEntries()<<endl;
                Bool_t klone;
                klone = dpw.isWeighted();
                if (klone==true)
                {
                        cout<<"My dataset is weighted!" << endl;
                }
                const RooArgSet* row5 = dpw.get(5);
                cout<<"This is 5th row weight: "<<endl;
                row5->Print("v");
                out<<(misidfilenames.at(i)).c_str()<<" & "<<(type).c_str()<<" & "<<(weights.at(i)).c_str()<<" & "<< dpw.sumEntries() <<" \\\\ "<<endl;
                f->Close();

        }

        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Numbersofmisidcomponents.txt}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;

        out.close();


	double misid;

	double sumofrangelow;
	double sumofrangehigh;

	double norm_low;
	double norm_high;

	sumofrangelow = dpw.sumEntries("(Bplus_Corrected_Mass < 4500)");
	sumofrangehigh = dpw.sumEntries("(Bplus_Corrected_Mass > 5500)");

	misid = dpw.sumEntries();
	norm_low = sumofrangelow/misid;
	norm_high = sumofrangehigh/misid;


	cout<<"Fractions in low region: "<<norm_low<<endl;
	cout<<"Fraction in high region: "<<norm_high<<endl;

	double fullmisid;
	fullmisid=100.0*misid;
	RooRealVar nmisid(("nmisid"+type).c_str(),"number of misid events",fullmisid);
	RooRealVar frac_low(("frac_low"+type).c_str(),"number of misid events",norm_low);
	RooRealVar frac_high(("frac_high"+type).c_str(),"number of misid events",norm_high);

	cout << dpw.weight() << endl;
	RooPlot* misidtotal = Bplus_Corrected_Mass.frame(Title("MISIDTOTAL")) ;
	RooPlot* misidtotal2 = Bplus_Corrected_Mass.frame(Title("MISIDtotal2")) ;

	dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
	dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));

	TPaveLabel *t2 = new TPaveLabel(0.4,0.6,0.9,0.8, Form("TotMisID = %f",misid),"brNDC");
	misidtotal->addObject(t2);


	TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
	canvtot->Divide(2,2) ;
	canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
	canvtot->SaveAs((workdir+"totalmisid_NOTMAIN_all_"+type+"_toynumber_"+i2s(toynumber)+".pdf").c_str());

	delete canvtot;
//	delete t2;
//	f->Close();
	s->Close();
        return;

}



vector<double> PlotMisidVariations::fitmisidcomponentall_chi2(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type)
{

	cout<<"Start misid fit all components"<<endl;


        TFile* s = new TFile((dir.at(0)+"/"+misidfilenames.at(0)+type+".root").c_str());
        TTree* treep = (TTree*)s->Get("DecayTree");

        RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
        Bplus_Corrected_Mass.setRange("sideband",4000,6000);
//        Bplus_Corrected_Mass.setBins(60);
        RooRealVar crossfeedweight(weights.at(0).c_str(),weights.at(0).c_str(), 0.0 ,1.0);

        RooDataSet dp("dp","dp",RooArgSet(Bplus_Corrected_Mass),Import(*treep));
        RooDataSet dpw("dpw","dpw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treep), WeightVar(weights.at(0).c_str()));//, Import(*treew));
        dp.Print();
        dpw.Print();

        ofstream out;
        out.open((workdir+"misid_comp_number"+type+".txt").c_str());
        vector<double> efficiencies2;


        out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        out<<"\\usepackage[pdftex]{graphicx}"<<endl;
        out<<"\\usepackage{url}"<<endl;
        out<<"\\usepackage{mathtools}"<<endl;
        out<<"\\usepackage{amsmath}"<<endl;
        out<<"\\usepackage{graphicx}"<<endl;
        out<<"\\usepackage[table]{xcolor}"<<endl;
        out<<"\\usepackage{amsmath,amssymb}"<<endl;
        out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        out<<"\\usepackage{colortbl}"<<endl;
        out<<"\\begin{document}"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\small"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{| l | l | l | l | }"<<endl;
        out<<"\\hline"<<endl;
        out<<"Filename & type & weight & Number  \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<(misidfilenames.at(0)).c_str()<<" & "<<(type).c_str()<<" & "<<(weights.at(0)).c_str()<<" & "<< dpw.sumEntries() <<" \\\\ "<<endl;


        fitmisidone(type, dir.at(0) , misidfilenames.at(0), weights.at(0), species.at(0));
        cout<<"Size of number of files "<<misidfilenames.size()<<endl;

                for(int i(1); i<misidfilenames.size(); i++)
        {
                cout<<"This is being added to misid"<<endl;
                fitmisidone(type, dir.at(i) , misidfilenames.at(i), weights.at(i), species.at(i));

                TFile* f = new TFile((dir.at(i)+"/"+misidfilenames.at(i)+type+".root").c_str());
                TTree* treek = (TTree*)f->Get("DecayTree");

                RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
                Bplus_Corrected_Mass.setRange("sideband",4000,6000);
                RooRealVar crossfeedweight(weights.at(i).c_str(),weights.at(i).c_str(), 0.0 ,1.0);

                RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
                RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treek), WeightVar(weights.at(i).c_str()));//, Import(*treew));
                dk.Print();
                dkw.Print();
//                Bplus_Corrected_Mass.setBins(60);

                dpw.append(dkw);
                dpw.Print("v");
                dpw.Print();
                cout<< "Sum of entries for kaon and pion:" <<dpw.sumEntries()<<endl;
                Bool_t klone;
                klone = dpw.isWeighted();
                if (klone==true)
                {
                        cout<<"My dataset is weighted!" << endl;
                }
                const RooArgSet* row5 = dpw.get(5);
                cout<<"This is 5th row weight: "<<endl;
                row5->Print("v");
                out<<(misidfilenames.at(i)).c_str()<<" & "<<(type).c_str()<<" & "<<(weights.at(i)).c_str()<<" & "<< dpw.sumEntries() <<" \\\\ "<<endl;
                f->Close();

        }

        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Numbersofmisidcomponents.txt}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;

        out.close();


	double misid;

	double sumofrangelow;
	double sumofrangehigh;

	double norm_low;
	double norm_high;

	sumofrangelow = dpw.sumEntries("(Bplus_Corrected_Mass < 4500)");
	sumofrangehigh = dpw.sumEntries("(Bplus_Corrected_Mass > 5500)");

	misid = dpw.sumEntries();
	norm_low = sumofrangelow/misid;
	norm_high = sumofrangehigh/misid;


	cout<<"Fractions in low region: "<<norm_low<<endl;
	cout<<"Fraction in high region: "<<norm_high<<endl;

	double fullmisid;
	fullmisid=100.0*misid;
	RooRealVar nmisid(("nmisid"+type).c_str(),"number of misid events",fullmisid);
	RooRealVar frac_low(("frac_low"+type).c_str(),"number of misid events",norm_low);
	RooRealVar frac_high(("frac_high"+type).c_str(),"number of misid events",norm_high);

	cout << dpw.weight() << endl;
	RooPlot* misidtotal = Bplus_Corrected_Mass.frame(Title("MISIDTOTAL")) ;
	RooPlot* misidtotal2 = Bplus_Corrected_Mass.frame(Title("MISIDtotal2")) ;

	dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
	dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));

	TPaveLabel *t2 = new TPaveLabel(0.4,0.6,0.9,0.8, Form("TotMisID = %f",misid),"brNDC");
	misidtotal->addObject(t2);


	TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
	canvtot->Divide(2,2) ;
	canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
	canvtot->SaveAs((workdir+"totalmisid_NOTMAIN_all_"+type+".pdf").c_str());

	delete canvtot;
//	delete t2;
//	f->Close();
	s->Close();

//---- Setup all thing for 3 different fits--------//

	vector<double> params;

        RooRealVar sig4(("sig4"),"frac of events in sig4",2.83,2.0,40.0);
        RooRealVar cbmeanr4(("cbmeanr4"),"cbmeanr", 4195.4, 3000.0, 4400.0);
        RooRealVar cbsigmar4(("cbsigmar4"),"cbsigmar",511.,400.,600.0);//,0.1,50) ;
        RooRealVar nr4(("nr4"),"",1.24);//, 0.8, 5.0);
        RooRealVar alphar4(("alphar4"),"",0.6);//, 0.1, 1.0);
	RooCBShape twocbs3(("twocbs3"), "c3", Bplus_Corrected_Mass, cbmeanr4, cbsigmar4, alphar4, nr4); 
        RooExtendPdf two_ext4("two_ext4","two_ext4",twocbs3,sig4);


//-------------------------------------------Bin corrected mass into 15 bins-----------------------------------------------------------------------//

        int desirednumofbins(15);
        Bplus_Corrected_Mass.setBins(desirednumofbins);
        RooDataHist binnedData("binnedData","Binned Vesrion of my histo",RooArgSet(Bplus_Corrected_Mass),dpw);
//	RooDataHist* binnedData = dpw.binnedClone("Binned Version") ; 
                

        //Bplus_Corrected_Mass.setBins(30);
	binnedData.Print("v");

	cout<< "Integral over histogram:" << binnedData.sum(kTRUE)<<endl; 
	cout<< "Sum of weight:" << binnedData.sum(kFALSE)<<endl;
	cout<< "Sum of entries:" << binnedData.sumEntries()<<endl;
	cout<< "Num of bins:" << binnedData.numEntries()<<endl; 


//-----------------------------------------Chi2 fit----------------------------------------------------------------//

        cout<<"Number of bins for chi2 fit "<<binnedData.numEntries()<<endl;
	RooChi2Var chi2("chi2","chi2",two_ext4,binnedData,RooFit::Range("sideband"),SumW2Error(kTRUE),Extended());
        
        RooMinimizer m(chi2);
        m.migrad();
        m.hesse();
        RooFitResult* chi2_binned_fit=m.save();
        RooPlot* chi2_binned=Bplus_Corrected_Mass.frame(Title("Chi2  binned data fit")) ;
        binnedData.plotOn(chi2_binned);//,DataError(RooAbsData::SumW2));
        two_ext4.paramOn(chi2_binned);
        two_ext4.plotOn(chi2_binned, LineColor(kRed),LineStyle(kDashed));
        ofstream out_chi2((plotdir+type+"FitResults_Bin_CHI2.txt").c_str());
        saveFitInfoExtended(out_chi2, chi2_binned, 2, &two_ext4,chi2_binned_fit);
        out_chi2<<"-----------Special fit specific---------------"<<endl;
        out_chi2<<"chi2.getval():"<<d2s(chi2.getVal())<<endl;
        out_chi2.close();
        cout<<"Finishing chi2 fit "<<endl;
        const TMatrixDSym& cov_chi = chi2_binned_fit->covarianceMatrix();
        chi2_binned_fit->Print("v") ;
	cout<<" edm: "<<chi2_binned_fit->edm()<<endl;
        cout<<" -log(L) at minimum: "<< chi2_binned_fit->minNll()<<endl;


//--------------------------------------Product of params function and error matrix-------------------------------------------//

         //---------------------get values for mean from the chi2 fit------------------------------------------------------//
         RooRealVar mu_sig4(("mu_sig4"),"frac of events in sig4",sig4.getVal()*100.0);//,(sig4.getVal()-sig4.getError())*100.0,((sig4.getVal()+sig4.getError())*100.0));
         RooRealVar mu_cbmeanr4(("mu_cbmeanr4"),"cbmeanr",cbmeanr4.getVal());//,cbmeanr4.getVal()-cbmeanr4.getError(),cbmeanr4.getVal()+cbmeanr4.getError());
         RooRealVar mu_cbsigmar4(("mu_cbsigmar4"),"cbsigmar",cbsigmar4.getVal());//,cbsigmar4.getVal()-cbsigmar4.getError(),cbsigmar4.getVal()+cbsigmar4.getError());//,0.1,50) ;

         //---------------------get the floating pars from fit--------------------------------------------------------//
         
         RooArgSet pars_before = chi2_binned_fit->floatParsFinal();
         cout<<"Look at floats "<<endl;
         pars_before.Print();

         //---------------------set scale for misid constant for final fit------------------//
         //cout<<" value before: "<<sig4.getValV()<<endl;
         //double newsig4val = double(sig4.getValV()*double(100.0));
         //double newseterr = double(sig4.getError()*double(100.0));
         //sig4.setVal(newsig4val);
         //sig4.setError(newseterr);
         //cout<<" value scaled: "<<sig4.getValV()<<endl;


         //---------------------get the floating pars from fit--------------------------------------------------------//
         
         RooArgSet pars = chi2_binned_fit->floatParsFinal();
         cout<<"Look at floats after "<<endl;
         pars.Print();

         //---------------------scale----------------//
 	 RooRealVar scale_for_misid("scale_for_misid","scale_for_misid",100.0);
         cout<<"What is the error: "<<sig4.getError()<<endl;
         RooRealVar misid_scaled("misid_scaled","misid_scaled",(sig4.getVal()*100.0),(double(sig4.getVal()-sig4.getError())*100.0),(double(sig4.getVal()+sig4.getError())*100.0));
         misid_scaled.setError(double(sig4.getError())*100.0);
         misid_scaled.Print(); 

         //---------------------function that shall be passed------------------------------//
         RooExtendPdf two_ext5("two_ext5","two_ext5",twocbs3,misid_scaled);
         RooMultiVarGaussian mvg("mvg", "mvg",RooArgSet(misid_scaled,cbmeanr4,cbsigmar4),RooArgSet(mu_sig4,mu_cbmeanr4,mu_cbsigmar4),cov_chi);

         //RooMultiVarGaussian misidModel("misidModel", "misidModel",pars,RooArgSet(mu_sig4,mu_cbmeanr4,mu_cbsigmar4),cov_chi);
         RooProdPdf misidModel("misidModel", "model from binned chi2 fit", RooArgSet(two_ext5, mvg));


//-----------------------------------Dokonci-------------//


	Bplus_Corrected_Mass.setRange("low",4000,4500);
	Bplus_Corrected_Mass.setRange("high",5500,7000);
	Bplus_Corrected_Mass.setRange("full",4000,7000);
	RooAbsReal* integral_low = two_ext4.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("low"));

	double int_low = integral_low->getVal(); 

	RooAbsReal* integral_high = two_ext4.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("high"));

	double int_high = integral_high->getVal();

	RooAbsReal* integral_full = two_ext4.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("full"));

	double int_full = integral_full->getVal();

	cout<<"Integral in low: " << int_low <<endl;
	cout<<"Integral in high: " << int_high<<endl;
	cout<<"Integral in full: " << int_full<<endl;

	RooPlot* ibou = Bplus_Corrected_Mass.frame(Title("Binned histogram")) ;
	binnedData.plotOn(ibou,DataError(RooAbsData::SumW2)); 
	RooPlot* ibou2 = Bplus_Corrected_Mass.frame(Title("Binned histogram")) ;
	binnedData.plotOn(ibou2,DataError(RooAbsData::SumW2));
	two_ext4.plotOn(ibou2) ;
	two_ext4.paramOn(ibou2);
   


	RooHist* hresidcom = ibou2->residHist();
	RooHist* hpullcom = ibou2->pullHist();
	RooPlot* framecom1 = Bplus_Corrected_Mass.frame(Title("Residual Distribution"));
	framecom1->addPlotable(hresidcom,"P");
	RooPlot* framecom2 = Bplus_Corrected_Mass.frame(Title("Pull Distribution")) ;
	framecom2->addPlotable(hpullcom,"P");


	TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
	canvibou->Divide(2,2) ;
	canvibou->cd(1); gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->GetXaxis()->SetTitle("Corrected Mass") ;  ibou->Draw() ;
	canvibou->cd(2); gPad->SetLeftMargin(0.15) ; ibou2->GetYaxis()->SetTitleOffset(1.4) ; ibou2->GetXaxis()->SetTitle("Corrected Mass") ;  ibou2->Draw() ;
	canvibou->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom1->GetYaxis()->SetTitleOffset(1.4) ; framecom1->GetXaxis()->SetTitle("Corrected Mass") ; framecom1->Draw() ;
	canvibou->cd(4) ; gPad->SetLeftMargin(0.15) ; framecom2->GetYaxis()->SetTitleOffset(1.4) ; framecom2->GetXaxis()->SetTitle("Corrected Mass") ; framecom2->Draw() ;
	canvibou->SaveAs((workdir+"totalmisidfit_NOTMAIN_all_"+type+".pdf").c_str());         

	delete canvibou; 


	TCanvas* canvnew = new TCanvas("misidplot","mBplus_Corrected_Massnew",800,800) ;
	gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->GetXaxis()->SetTitle("Corrected Mass") ;  ibou->Draw();
	TFile *fm = new TFile((workdir+"plotmisid_all_"+type+".root").c_str(),"RECREATE");
	canvnew->Write();
	fm->Close();
	delete fm;
	delete canvnew;

//-------------Will Propagate function that is prod(F)*contraintsfromchi2(fit)-------------------//

	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	string namews8="misid";
	TFile wrkspc8((workdir+"myworkspace_"+namews8+".root").c_str(),"RECREATE");
	w8->import(Bplus_Corrected_Mass);
	w8->import(binnedData);
	w8->import(misidModel);
//	w8->import(nmisid);
	w8->import(frac_low);       
	w8->import(frac_high);

	cout<<"Misid workspace"<<endl;
	w8->Print();
	w8->Write();
        cout<<"New stuff"<<endl;
	wrkspc8.Write();


        cout<<"New stuff ou yeah"<<endl;
        delete w8;

        params.push_back(0);
	return(params);
}

vector<double> PlotMisidVariations::fitmisidcomponentall_compare(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type)
{

	cout<<"Start misid fit all components"<<endl;


        TFile* s = new TFile((dir.at(0)+"/"+misidfilenames.at(0)+type+".root").c_str());
        TTree* treep = (TTree*)s->Get("DecayTree");

        RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
        Bplus_Corrected_Mass.setRange("sideband",4000,6000);
//        Bplus_Corrected_Mass.setBins(60);
        RooRealVar crossfeedweight(weights.at(0).c_str(),weights.at(0).c_str(), 0.0 ,1.0);

        RooDataSet dp("dp","dp",RooArgSet(Bplus_Corrected_Mass),Import(*treep));
        RooDataSet dpw("dpw","dpw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treep), WeightVar(weights.at(0).c_str()));//, Import(*treew));
        dp.Print();
        dpw.Print();

        ofstream out;
        out.open((workdir+"misid_comp_number"+type+".txt").c_str());
        vector<double> efficiencies2;


        out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        out<<"\\usepackage[pdftex]{graphicx}"<<endl;
        out<<"\\usepackage{url}"<<endl;
        out<<"\\usepackage{mathtools}"<<endl;
        out<<"\\usepackage{amsmath}"<<endl;
        out<<"\\usepackage{graphicx}"<<endl;
        out<<"\\usepackage[table]{xcolor}"<<endl;
        out<<"\\usepackage{amsmath,amssymb}"<<endl;
        out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        out<<"\\usepackage{colortbl}"<<endl;
        out<<"\\begin{document}"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\small"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{| l | l | l | l | }"<<endl;
        out<<"\\hline"<<endl;
        out<<"Filename & type & weight & Number  \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<(misidfilenames.at(0)).c_str()<<" & "<<(type).c_str()<<" & "<<(weights.at(0)).c_str()<<" & "<< dpw.sumEntries() <<" \\\\ "<<endl;


        fitmisidone(type, dir.at(0) , misidfilenames.at(0), weights.at(0), species.at(0));
        cout<<"Size of number of files "<<misidfilenames.size()<<endl;

                for(int i(1); i<misidfilenames.size(); i++)
        {
                cout<<"This is being added to misid"<<endl;
                fitmisidone(type, dir.at(i) , misidfilenames.at(i), weights.at(i), species.at(i));

                TFile* f = new TFile((dir.at(i)+"/"+misidfilenames.at(i)+type+".root").c_str());
                TTree* treek = (TTree*)f->Get("DecayTree");

                RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
                Bplus_Corrected_Mass.setRange("sideband",4000,6000);
                RooRealVar crossfeedweight(weights.at(i).c_str(),weights.at(i).c_str(), 0.0 ,1.0);

                RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
                RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treek), WeightVar(weights.at(i).c_str()));//, Import(*treew));
                dk.Print();
                dkw.Print();
//                Bplus_Corrected_Mass.setBins(60);

                dpw.append(dkw);
                dpw.Print("v");
                dpw.Print();
                cout<< "Sum of entries for kaon and pion:" <<dpw.sumEntries()<<endl;
                Bool_t klone;
                klone = dpw.isWeighted();
                if (klone==true)
                {
                        cout<<"My dataset is weighted!" << endl;
                }
                const RooArgSet* row5 = dpw.get(5);
                cout<<"This is 5th row weight: "<<endl;
                row5->Print("v");
                out<<(misidfilenames.at(i)).c_str()<<" & "<<(type).c_str()<<" & "<<(weights.at(i)).c_str()<<" & "<< dpw.sumEntries() <<" \\\\ "<<endl;
                f->Close();

        }

        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Numbersofmisidcomponents.txt}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;

        out.close();


	double misid;

	double sumofrangelow;
	double sumofrangehigh;

	double norm_low;
	double norm_high;

	sumofrangelow = dpw.sumEntries("(Bplus_Corrected_Mass < 4500)");
	sumofrangehigh = dpw.sumEntries("(Bplus_Corrected_Mass > 5500)");

	misid = dpw.sumEntries();
	norm_low = sumofrangelow/misid;
	norm_high = sumofrangehigh/misid;


	cout<<"Fractions in low region: "<<norm_low<<endl;
	cout<<"Fraction in high region: "<<norm_high<<endl;

	double fullmisid;
	fullmisid=100.0*misid;
	RooRealVar nmisid(("nmisid"+type).c_str(),"number of misid events",fullmisid);
	RooRealVar frac_low(("frac_low"+type).c_str(),"number of misid events",norm_low);
	RooRealVar frac_high(("frac_high"+type).c_str(),"number of misid events",norm_high);

	cout << dpw.weight() << endl;
	RooPlot* misidtotal = Bplus_Corrected_Mass.frame(Title("MISIDTOTAL")) ;
	RooPlot* misidtotal2 = Bplus_Corrected_Mass.frame(Title("MISIDtotal2")) ;

	dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
	dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));

	TPaveLabel *t2 = new TPaveLabel(0.4,0.6,0.9,0.8, Form("TotMisID = %f",misid),"brNDC");
	misidtotal->addObject(t2);


	TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
	canvtot->Divide(2,2) ;
	canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
	canvtot->SaveAs((workdir+"totalmisid_NOTMAIN_all_"+type+".pdf").c_str());

	delete canvtot;
//	delete t2;
//	f->Close();
	s->Close();

//---- Setup all thing for 3 different fits--------//

	vector<double> params;
        RooRealVar sig2(("sig2"),"frac of events in sig2",2.83,2.0,40.0);
        RooRealVar cbmeanr2(("cbmeanr2"),"cbmeanr", 4195.4, 100.0, 4400.0);
        RooRealVar cbsigmar2(("cbsigmar2"),"cbsigmar",511.,400.,600.0);//,0.1,50) ;
        RooRealVar nr2(("nr2"),"",1.24);//, 0.01, 5.0);
        RooRealVar alphar2(("alphar2"),"",0.6);//, 0.1, 1.0);
        RooCBShape twocbs(("twocbs"), "crystal ball", Bplus_Corrected_Mass, cbmeanr2, cbsigmar2, alphar2, nr2);
        RooExtendPdf two_ext("two_ext","two_ext",twocbs,sig2);

        RooRealVar sig3(("sig3"),"frac of events in sig3",2.83,2.0,40.0);
        RooRealVar cbmeanr3(("cbmeanr3"),"cbmeanr", 4195.4,100.0, 4400.0);
        RooRealVar cbsigmar3(("cbsigmar3"),"cbsigmar",511.,400.,600.0);//,0.1,50) ;
        RooRealVar nr3(("nr3"),"",1.24);//, 0.01, 5.0);
        RooRealVar alphar3(("alphar3"),"",0.6);//, 0.1, 1.0);
	RooCBShape twocbs2(("twocbs2"), "c2", Bplus_Corrected_Mass, cbmeanr3, cbsigmar3, alphar3, nr3);
        RooExtendPdf two_ext3("two_ext3","two_ext3",twocbs2,sig3);

        RooRealVar sig4(("sig4"),"frac of events in sig4",2.83,2.0,40.0);
        RooRealVar cbmeanr4(("cbmeanr4"),"cbmeanr", 4195.4, 3000.0, 4400.0);
        RooRealVar cbsigmar4(("cbsigmar4"),"cbsigmar",511.,400.,600.0);//,0.1,50) ;
        RooRealVar nr4(("nr4"),"",1.24);//, 0.8, 5.0);
        RooRealVar alphar4(("alphar4"),"",0.6);//, 0.1, 1.0);
	RooCBShape twocbs3(("twocbs3"), "c3", Bplus_Corrected_Mass, cbmeanr4, cbsigmar4, alphar4, nr4); 
        RooExtendPdf two_ext4("two_ext4","two_ext4",twocbs3,sig4);

//--------------------------------------------Weighted ML likelihood fit to unbinned data------------------------------//
       int desirednumofbins(15);
       RooPlot* all=Bplus_Corrected_Mass.frame(Title("Compare Fits"),Bins(desirednumofbins)) ;
       dpw.plotOn(all,DataError(RooAbsData::SumW2));


        RooFitResult* not_binned = two_ext.fitTo(dpw,RooFit::Range("sideband"),SumW2Error(kTRUE),Extended(),Save());//,SumW2Error(kTRUE),Save());//Extended(kTRUE);
        not_binned->Print("v") ;
        RooPlot* wei_unbinned=Bplus_Corrected_Mass.frame(Title("Weighted ML likelihood unbinned data fit")) ;
        dpw.plotOn(wei_unbinned,DataError(RooAbsData::SumW2));
        two_ext.paramOn(wei_unbinned);
        two_ext.plotOn(wei_unbinned);
        two_ext.plotOn(all);
        ofstream out_un((comparedir+"/"+type+"FitResults_Unb_ML.txt").c_str());
        saveFitInfoExtended(out_un, wei_unbinned, 2, &two_ext,not_binned);
        out_un.close();        

        not_binned->Print("v") ;
	cout<<" edm: "<<not_binned->edm()<<endl;
        cout<<" -log(L) at minimum: "<< not_binned->minNll()<<endl;
        cout<<"Finishing Weighted ML likelihood unbinned data fit "<<endl;




//------------------------------------------------BIN HISTOGRAM---------------------------------------------------------------//

        
        Bplus_Corrected_Mass.setBins(desirednumofbins);
        RooDataHist binnedData("binnedData","Binned Vesrion of my histo",RooArgSet(Bplus_Corrected_Mass),dpw);
//	RooDataHist* binnedData = dpw.binnedClone("Binned Version") ; 
                

        //Bplus_Corrected_Mass.setBins(30);
	binnedData.Print("v");

	cout<< "Integral over histogram:" << binnedData.sum(kTRUE)<<endl; 
	cout<< "Sum of weight:" << binnedData.sum(kFALSE)<<endl;
	cout<< "Sum of entries:" << binnedData.sumEntries()<<endl;
	cout<< "Num of bins:" << binnedData.numEntries()<<endl;  

	RooPlot* ibou = Bplus_Corrected_Mass.frame(Title("Binned histogram")) ;
	binnedData.plotOn(ibou,DataError(RooAbsData::SumW2)); 


//--------------------------------------Weighted ML likelihood binned data fit------------------------------------------//



        RooFitResult* r = two_ext3.fitTo(binnedData,RooFit::Range("sideband"),SumW2Error(kTRUE),Extended(),Save());
        RooPlot* wei_binned=Bplus_Corrected_Mass.frame(Title("Weighted ML likelihood binned data fit")) ;
        binnedData.plotOn(wei_binned,DataError(RooAbsData::SumW2));
        two_ext3.paramOn(wei_binned);
        two_ext3.plotOn(wei_binned,LineColor(kGreen),LineStyle(kDashed));
        two_ext3.plotOn(all,LineColor(kGreen),LineStyle(kDashed));

        ofstream out_b((comparedir+"/"+type+"FitResults_Bin_ML.txt").c_str());
        saveFitInfoExtended(out_b, wei_binned, 2, &two_ext3,r);
        out_b.close();

        r->Print("v") ;
	cout<<" edm: "<<r->edm()<<endl;
        cout<<" -log(L) at minimum: "<< r->minNll()<<endl;

        const TMatrixDSym& cor = r->correlationMatrix();
        cout<<" correlation matrix "<<endl;
        cor.Print();
        const TMatrixDSym& cov = r->covarianceMatrix();
        cout<<" covariance matrix "<<endl;
        cov.Print();


        cout<<"Finishing Weighted ML likelihood binned data fit "<<endl;

//-------------------------------------------Chi2 fits-----------------------------------------------------------------------//


        cout<<"Number of bins for chi2 fit "<<binnedData.numEntries()<<endl;
	RooChi2Var chi2("chi2","chi2",two_ext4,binnedData,RooFit::Range("sideband"),SumW2Error(kTRUE),Extended());
        
        RooMinimizer m(chi2);
        m.migrad();
        m.hesse();
        RooFitResult* chi2_binned_fit=m.save();
        RooPlot* chi2_binned=Bplus_Corrected_Mass.frame(Title("Chi2  binned data fit")) ;
        binnedData.plotOn(chi2_binned);//,DataError(RooAbsData::SumW2));
        two_ext4.paramOn(chi2_binned);
        two_ext4.plotOn(chi2_binned, LineColor(kRed),LineStyle(kDashed));
        two_ext4.plotOn(all, LineColor(kRed),LineStyle(3));
        ofstream out_chi2((comparedir+"/"+type+"FitResults_Bin_CHI2.txt").c_str());
        saveFitInfoExtended(out_chi2, chi2_binned, 2, &two_ext4,chi2_binned_fit);
        out_chi2<<"-----------Special fit specific---------------"<<endl;
        out_chi2<<"chi2.getval():"<<d2s(chi2.getVal())<<endl;
        out_chi2.close();
        cout<<"Finishing chi2 fit "<<endl;
        const TMatrixDSym& cov_chi = chi2_binned_fit->covarianceMatrix();
        chi2_binned_fit->Print("v") ;
	cout<<" edm: "<<chi2_binned_fit->edm()<<endl;
        cout<<" -log(L) at minimum: "<< chi2_binned_fit->minNll()<<endl;


//--------------------------------------Product of params function and error matrix-------------------------------------------//

         //---------------------get values for mean from the chi2 fit------------------------------------------------------//
         RooRealVar mu_sig4(("mu_sig4"),"frac of events in sig4",sig4.getVal()*100.0);//,(sig4.getVal()-sig4.getError())*100.0,((sig4.getVal()+sig4.getError())*100.0));
         RooRealVar mu_cbmeanr4(("mu_cbmeanr4"),"cbmeanr",cbmeanr4.getVal());//,cbmeanr4.getVal()-cbmeanr4.getError(),cbmeanr4.getVal()+cbmeanr4.getError());
         RooRealVar mu_cbsigmar4(("mu_cbsigmar4"),"cbsigmar",cbsigmar4.getVal());//,cbsigmar4.getVal()-cbsigmar4.getError(),cbsigmar4.getVal()+cbsigmar4.getError());//,0.1,50) ;

         //---------------------get the floating pars from fit--------------------------------------------------------//
         
         RooArgSet pars_before = chi2_binned_fit->floatParsFinal();
         cout<<"Look at floats "<<endl;
         pars_before.Print();

         //---------------------set scale for misid constant for final fit------------------//
         //cout<<" value before: "<<sig4.getValV()<<endl;
         //double newsig4val = double(sig4.getValV()*double(100.0));
         //double newseterr = double(sig4.getError()*double(100.0));
         //sig4.setVal(newsig4val);
         //sig4.setError(newseterr);
         //cout<<" value scaled: "<<sig4.getValV()<<endl;


         //---------------------get the floating pars from fit--------------------------------------------------------//
         
         RooArgSet pars = chi2_binned_fit->floatParsFinal();
         cout<<"Look at floats after "<<endl;
         pars.Print();

         //---------------------scale----------------//
 	 RooRealVar scale_for_misid("scale_for_misid","scale_for_misid",100.0);
         cout<<"What is the error: "<<sig4.getError()<<endl;
         RooRealVar misid_scaled("misid_scaled","misid_scaled",(sig4.getVal()*100.0),(double(sig4.getVal()-sig4.getError())*100.0),(double(sig4.getVal()+sig4.getError())*100.0));
         misid_scaled.setError(double(sig4.getError())*100.0);
         misid_scaled.Print(); 

         //---------------------function that shall be passed------------------------------//
         RooExtendPdf two_ext5("two_ext5","two_ext5",twocbs3,misid_scaled);
         RooMultiVarGaussian mvg("mvg", "mvg",RooArgSet(misid_scaled,cbmeanr4,cbsigmar4),RooArgSet(mu_sig4,mu_cbmeanr4,mu_cbsigmar4),cov_chi);

         //RooMultiVarGaussian misidModel("misidModel", "misidModel",pars,RooArgSet(mu_sig4,mu_cbmeanr4,mu_cbsigmar4),cov_chi);
         RooProdPdf misidModel("misidModel", "model from binned chi2 fit", RooArgSet(two_ext5, mvg));




//--------------------------------------Compare All fits ---------------------------------------------------------------------//





        TCanvas* comp = new TCanvas("compare","compare",800,800) ;
        comp->Divide(2,2) ;
        comp->cd(1); gPad->SetLeftMargin(0.15) ; wei_unbinned->GetYaxis()->SetTitleOffset(1.4) ; wei_unbinned->GetXaxis()->SetTitle("Corrected Mass") ;  wei_unbinned->Draw() ;
        comp->cd(2); gPad->SetLeftMargin(0.15) ; wei_binned->GetYaxis()->SetTitleOffset(1.4) ; wei_binned->GetXaxis()->SetTitle("Corrected Mass") ;  wei_binned->Draw() ;
        comp->cd(3) ; gPad->SetLeftMargin(0.15) ; chi2_binned->GetYaxis()->SetTitleOffset(1.4) ; chi2_binned->GetXaxis()->SetTitle("Corrected Mass") ; chi2_binned->Draw() ;
        comp->cd(4) ; gPad->SetLeftMargin(0.15) ; all->GetYaxis()->SetTitleOffset(1.4) ; all->GetXaxis()->SetTitle("Corrected Mass") ; all->Draw() ;
        comp->SaveAs((comparedir+"/CompareFit_weigted_dataset"+type+".pdf").c_str());


        twocbs.plotOn(ibou) ;

	cout<<"HAVE LOOK AT CONVERGENCE"<<endl;
	params.push_back(cbmeanr2.getVal());
	params.push_back(cbsigmar2.getVal());
	params.push_back(nr2.getVal());
	params.push_back(alphar2.getVal());

        delete comp;
//        delete w8;

	return(params);
}



