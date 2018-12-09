#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "fitAndSplotB23MuNuDataForTraining.hpp"
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
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TColor.h"
#include "TROOT.h"
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
#include "RooBinning.h"
#include "TMatrixT.h"

using namespace std;
using namespace RooFit;

double FitAndSplotB23MuNuDataForTraining::fitmisidone_newdir(string type, string dir ,string filename, string weight, string species)
{
        TFile* f = new TFile((dir+"/"+filename+type+".root").c_str());
        TTree* treek = (TTree*)f->Get("DecayTree");

        RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
        Bplus_Corrected_Mass.setRange("sideband",4000,7000);
        Bplus_Corrected_Mass.setBins(30);

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


        string newdir("../misid_shapes_nocross_andcross/");

        TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",1500,600) ;
        canv5->Divide(2,1) ;
        canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.1) ; frame11->GetXaxis()->SetTitle("Corrected Mass") ;  frame11->Draw() ;
        canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.1) ; frame12->GetXaxis()->SetTitle("Corrected Mass") ; frame12->Draw() ;
        canv5->SaveAs((newdir+"misid_"+filename+"_"+type+"_"+weight+".pdf").c_str());
        //delete t3;
	delete canv5;
	//delete t3;
	f->Close();
	return(kaonmisid);


}
        

double FitAndSplotB23MuNuDataForTraining::fitmisidone_newdir_compare2weights(string type, string dir ,string filename, string weight, string weight2 ,string species)
{
        TFile* f = new TFile((dir+"/"+filename+type+".root").c_str());
        TTree* treek = (TTree*)f->Get("DecayTree");

        RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
        Bplus_Corrected_Mass.setRange("sideband",4000,7000);
        Bplus_Corrected_Mass.setBins(30);

        RooRealVar crossfeedweight((weight.c_str()),"crossfeedweight", 0.0 ,1.0);
        RooRealVar crossfeedweight2((weight2.c_str()),"crossfeedweight", 0.0 ,1.0);

        RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
        RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treek), WeightVar(weight.c_str()));
        RooDataSet dkw2("dkw2","dkw2", RooArgSet(Bplus_Corrected_Mass,crossfeedweight2), Import(*treek), WeightVar(weight2.c_str()));

        RooPlot* frame11 = Bplus_Corrected_Mass.frame(Title(("MisIDShape_"+species).c_str())) ;
        RooPlot* frame12 = Bplus_Corrected_Mass.frame(Title(("MisIDShape_Normalized_"+species).c_str())) ;
        dk.plotOn(frame11);
        dkw.plotOn(frame11,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
        dkw2.plotOn(frame11,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kBlue));
        dkw.plotOn(frame12,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed),RooFit::Name("weight1"));
        dkw2.plotOn(frame12,DataError(RooAbsData::SumW2),MarkerColor(kBlue),LineColor(kBlue),RooFit::Name("weight2"));
        double kaonmisid,kaonmisid2;
        kaonmisid =dkw.sumEntries();
        kaonmisid2 =dkw2.sumEntries();
       
        frame11->SetMinimum(0.01); 
        frame11->GetYaxis()->SetTitle("Entries / (100 MeV/c^{2})");
        frame12->GetYaxis()->SetTitle("Entries / (100 MeV/c^{2})");



//      TPaveLabel *t3 = new TPaveLabel(0.45,0.6,0.9,0.8, Form("Total MisID = %f",kaonmisid),"brNDC");
//        t3->SetTextSize(0.2);
//      frame12->addObject(t3);


	string newdir("../misid_shapes_nocross_andcross/");

	TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",1500,600) ;
	canv5->Divide(2,1) ;
	canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; gPad->SetLogy(); frame11->GetYaxis()->SetTitleOffset(1.05) ; frame11->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]") ;  frame11->Draw() ;
	canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.05) ; frame12->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]") ; frame12->Draw() ;

	TLegend *leg = new TLegend(0.45,0.45,0.9,0.7);
//	leg->SetTextSize(0.05);
        leg->SetTextSize(0.062);
	leg->AddEntry(frame12->findObject("weight1"),("No Crossfeed: "+d2s(round_to_digits(kaonmisid,4))).c_str(),"l");
	leg->AddEntry(frame12->findObject("weight2"),("Crossfeed: "+d2s(round_to_digits(kaonmisid2,4))).c_str(),"l");
	//      leg->AddEntry(frame->findObject("partreco"),"PartReco","l");
	leg->Draw("same");

	canv5->SaveAs((newdir+"compare_misid_"+filename+"_"+type+"_NEW.pdf").c_str());
	//delete t3;
	delete canv5;
	//delete t3;
	f->Close();
	return(kaonmisid);
}






void FitAndSplotB23MuNuDataForTraining::prepareWorkspaceNoFitData(string type, string PIDcut)
{
        TFile f( (nofitdatadir+"/"+nofitdatafile+"_"+PIDcut+".root").c_str());
        TTree* t = (TTree*)f.Get(treename.c_str());

        if(!t)
        {
                cerr<<"ERROR: in function prepareWorkspace, no tree "<<nofitdatadir<<" found in "<<nofitdatafile<<"/"<<tuplename<<endl;
                return;
        }

        t->SetBranchStatus("*", 0);
        t->SetBranchStatus("Bplus_Corrected_Mass", 1);

        RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass", "Bplus_Corrected_Mass",Bplus_Corrected_Mass_min,Bplus_Corrected_Mass_max);
        RooArgSet vars(Bplus_Corrected_Mass);


        cout<<"BLABLA: "<<"Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)<<endl;

        RooDataSet data(("data"), ("data"), vars, Import(*t), Cut( ("Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)).c_str() ) );

        RooWorkspace workspaceData("workspaceNoFitData", "workspaceNoFitData");

        workspaceData.import(Bplus_Corrected_Mass);
        workspaceData.import(data);


        TFile fws((workspacedir+"NoFitData.root").c_str(), "RECREATE");
        workspaceData.Write("",TObject::kOverwrite );

        cout<<"Workspace containing data ready:"<<endl;
        cout<<"In "<<(workspacedir+"NoFitData.root").c_str()<<endl;
        workspaceData.Print();


        f.Close();
        fws.Close();
}



double FitAndSplotB23MuNuDataForTraining::fitmisidone(string type, string dir ,string filename, string weight, string species)
{
	TFile* f = new TFile((dir+"/"+filename+type+".root").c_str());
	TTree* treek = (TTree*)f->Get("DecayTree");

	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
	Bplus_Corrected_Mass.setRange("sideband",4000,7000);
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
 //      TPaveText *pave = new TPaveText(-3.78,500,-1.2,750);
//   pave->SetFillColor(42);
//        t1->SetTextSize(0.05);
//        TText *t1=pave->AddText("You can move");
//        t1->SetTextSize(0.05);
//        t1->SetTextColor(4);
//      frame12->addObject(pave);
//   t1->SetTextColor(4);
//   t1->SetTextSize(0.05);
//   pave->AddText("Title and Stats pads");
//   pave->AddText("X and Y axis");
//   pave->AddText("You can modify bin contents");
//   pave->Draw();



	TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,400) ;
	canv5->Divide(2,1) ;
	canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.1) ; frame11->GetXaxis()->SetTitle("Corrected Mass") ;  frame11->Draw() ;
	canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.1) ; frame12->GetXaxis()->SetTitle("Corrected Mass") ; frame12->Draw() ;
	canv5->SaveAs((workspacedir+"misid_"+filename+"_"+type+"_"+weight+".pdf").c_str());
        //delete t3;
	delete canv5;
        //delete t3;
        f->Close();
        return(kaonmisid);
       

}


vector<double> FitAndSplotB23MuNuDataForTraining::fitmisidcomponentall_chi2(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type, string PIDcut_Run1, string PIDcut_Run2)
{

	cout<<"Start misid fit all components"<<endl;
        cout<<"This is the name considered for "<<misidfilenames.at(0)<<endl;


        TFile* s = new TFile((dir.at(0)+"/"+misidfilenames.at(0)+type+".root").c_str());
        TTree* treep = (TTree*)s->Get("DecayTree");

        RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
        Bplus_Corrected_Mass.setRange("sideband",4000,7000);
//        Bplus_Corrected_Mass.setBins(60);
        RooRealVar crossfeedweight(weights.at(0).c_str(),weights.at(0).c_str(), 0.0 ,1.0);

        RooDataSet dp("dp","dp",RooArgSet(Bplus_Corrected_Mass),Import(*treep));
        RooDataSet dpw("dpw","dpw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treep), WeightVar(weights.at(0).c_str()));//, Import(*treew));
        dp.Print();
        dpw.Print();




        ofstream out2;
        out2.open((workspacedir+"misid_comp_number_forana_"+type+".txt").c_str());


        out2<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        out2<<"\\usepackage[pdftex]{graphicx}"<<endl;
        out2<<"\\usepackage{url}"<<endl;
        out2<<"\\usepackage{mathtools}"<<endl;
        out2<<"\\usepackage{amsmath}"<<endl;
        out2<<"\\usepackage{graphicx}"<<endl;
        out2<<"\\usepackage[table]{xcolor}"<<endl;
        out2<<"\\usepackage{amsmath,amssymb}"<<endl;
        out2<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        out2<<"\\usepackage{colortbl}"<<endl;
        out2<<"\\begin{document}"<<endl;
        out2<<"\\begin{table}[ht]"<<endl;
        out2<<"\\small"<<endl;
        out2<<"\\begin{center}"<<endl;
        out2<<"\\begin{tabular}{| l | l | l | l | l | }"<<endl;
        out2<<"\\hline"<<endl;
        out2<<"Sample & Region & PID & weight & Cummulative Number of Misid events / 100  \\\\ "<<endl;
        out2<<"\\hline"<<endl;
        out2<<(misidfilenames.at(0)).c_str()<<" & "<<(species.at(0)).c_str()<<" & "<<(type).c_str()<<" & "<<(weights.at(0)).c_str()<<" & "<< dpw.sumEntries() <<" \\\\ "<<endl;







        ofstream out;
        out.open((workspacedir+"misid_comp_number"+type+".txt").c_str());
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
                Bplus_Corrected_Mass.setRange("sideband",4000,7000);
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
                out2<<(misidfilenames.at(i)).c_str()<<" & "<<(species.at(i)).c_str()<<" & "<<(type).c_str()<<" & "<<(weights.at(i)).c_str()<<" & "<< dpw.sumEntries() <<" \\\\ "<<endl;
                f->Close();

        }

        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Numbersofmisidcomponents.txt}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;

        out.close();

        out2<<"\\hline"<<endl;
        out2<<"\\end{tabular}"<<endl;
        out2<<"\\end{center}"<<endl;
        out2<<"\\caption{Numbersofmisidcomponents.txt}"<<endl;
        out2<<"\\end{table}"<<endl;
        out2<<"\\end{document}"<<endl;

        out2.close();

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
	RooPlot* misidtotal = Bplus_Corrected_Mass.frame(Title("MISIDTOTAL"),Bins(60)) ;
	RooPlot* misidtotal2 = Bplus_Corrected_Mass.frame(Title("MISIDtotal2"),Bins(60)) ;

	dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
	dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));

	TPaveLabel *t2 = new TPaveLabel(0.4,0.6,0.9,0.8, Form("TotMisID = %f",misid),"brNDC");
	misidtotal->addObject(t2);


	TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
	canvtot->Divide(2,2) ;
	canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.1) ; misidtotal->Draw() ;
	canvtot->SaveAs((workspacedir+"totalmisid_NOTMAIN_all_"+type+".pdf").c_str());

	delete canvtot;
//	delete t2;
//	f->Close();
	s->Close();

//---- Setup all thing for 3 different fits--------//

	vector<double> params;

        RooRealVar sig4(("sig4"),"frac of events in sig4",2.83,2.0,100.0);
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

//-------------------------------------------Learn about Errors in RooDataHist----------------------//


        cout<<" Learn about the errors "<<endl;	
        ofstream errorsheet; 
        errorsheet.open((workspacedir+"misid_error_summary_"+type+".txt").c_str());


        errorsheet<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        errorsheet<<"\\usepackage[pdftex]{graphicx}"<<endl;
        errorsheet<<"\\usepackage{url}"<<endl;
        errorsheet<<"\\usepackage{mathtools}"<<endl;
        errorsheet<<"\\usepackage{amsmath}"<<endl;
        errorsheet<<"\\usepackage{graphicx}"<<endl;
        errorsheet<<"\\usepackage[table]{xcolor}"<<endl;
        errorsheet<<"\\usepackage{amsmath,amssymb}"<<endl;
        errorsheet<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        errorsheet<<"\\usepackage{colortbl}"<<endl;
        errorsheet<<"\\begin{document}"<<endl;
        errorsheet<<"\\begin{table}[ht]"<<endl;
        errorsheet<<"\\small"<<endl;
        errorsheet<<"\\begin{center}"<<endl;
        errorsheet<<"\\begin{tabular}{| l | l | l | l | }"<<endl;
        errorsheet<<"\\hline"<<endl;
        errorsheet<<"Bin & Value  & weight & weight error  \\\\ "<<endl;
        errorsheet<<"\\hline"<<endl;


        for (int i(0); i<binnedData.numEntries(); i++)
        {
 	binnedData.get(i);
        binnedData.weightError(RooAbsData::SumW2);
        cout<<" Bin "<<i<<" x = "<<binnedData.get(i)->getRealValue("Bplus_Corrected_Mass")<<" Weight="<<binnedData.weight()<<" Weight Error= "<<binnedData.weightError(RooAbsData::SumW2)<<endl;
        errorsheet<<i<<" & "<<binnedData.get(i)->getRealValue("Bplus_Corrected_Mass")<<"& "<<binnedData.weight()<<" & "<<binnedData.weightError(RooAbsData::SumW2)<<endl;
        }

        errorsheet<<"\\hline"<<endl;
        errorsheet<<"\\end{tabular}"<<endl;
        errorsheet<<"\\end{center}"<<endl;
        errorsheet<<"\\caption{Errors.txt}"<<endl;
        errorsheet<<"\\end{table}"<<endl;
        errorsheet<<"\\end{document}"<<endl;


//--off        cout<<"Read out errors from misid variation "<<endl;
//--off
//--off
//--off        //looking at sigma of pidcutrun1
//--off
//--off        errorsheet<<"Read out errors from misid variation Run1"<<endl;
//--off        TFile* fw = new TFile((misidvariationdir+"/RooWS_Error_Mean_MisidVariation_"+i2s(desirednumofbins)+"_100_"+type+"_"+PIDcut_Run1+".root").c_str(), "READ");
//--off        RooWorkspace* ws_error = (RooWorkspace*)fw->Get("workspaceVar");
//--off        ws_error->Print();
//--off        for (int l(0); l<desirednumofbins; l++){
//--off                RooRealVar* error = ws_error->var(("ErrorVar_"+i2s(l)).c_str());
//--off                RooRealVar* mean = ws_error->var(("MeanVar_"+i2s(l)).c_str());
//--off                errorsheet<<"Mean from toys: "<<mean->getVal()<<" Error from toys: "<<error->getVal()<<endl;
//--off                if (error->getVal()==0.0)
//--off                {
//--off                error->setVal(1.0);
//--off                errorsheet<<"Mean from toys: "<<mean->getVal()<<" Since  error from toys was zero : "<<error->getVal()<<endl;
//--off                }
//--off        }
//--off
//--off//        //looking at sigma of pidcut2016
//--off//
//--off//        errorsheet<<"Read out errors from misid variation 2016"<<endl;
//--off//        TFile* fw_2016 = new TFile((misidvariationdir+"/RooWS_Error_Mean_MisidVariation_"+i2s(desirednumofbins)+"_100_"+type+"_"+PIDcut_Run2+".root").c_str(), "READ");
//--off//        RooWorkspace* ws_error_2016 = (RooWorkspace*)fw_2016->Get("workspaceVar");
//--off//        ws_error_2016->Print();
//--off//        for (int l(0); l<desirednumofbins; l++){
//--off//                RooRealVar* error_2016 = ws_error_2016->var(("ErrorVar_"+i2s(l)).c_str());
//--off//                RooRealVar* mean_2016 = ws_error_2016->var(("MeanVar_"+i2s(l)).c_str());
//--off//                errorsheet<<"Mean from toys: "<<mean_2016->getVal()<<" Error from toys: "<<error_2016->getVal()<<endl;
//--off//                if (error_2016->getVal()==0.0)
//--off//                {
//--off//                error_2016->setVal(1.0);
//--off//                errorsheet<<"Mean from toys: "<<mean_2016->getVal()<<" Since  error from toys was zero : "<<error_2016->getVal()<<endl;
//--off//                }
//--off//        }
//--off//        
//--off//        cout<<"Sum the error from misid variation "<<endl;
//--off
//--off        errorsheet<<"Sum the error from misid variation "<<endl;
//--off	 
//--off        for (int i(0); i<binnedData.numEntries(); i++)
//--off        {
//--off	RooRealVar* error = ws_error->var(("ErrorVar_"+i2s(i)).c_str());
//--off//        RooRealVar* error_2016 = ws_error_2016->var(("ErrorVar_"+i2s(i)).c_str());
//--off        
//--off        double combined_err(0);
//--off        cout<<"combining run1 and 2016 errors"<<endl;
//--off//	combined_err=addstatandsyst(error->getVal(),error_2016->getVal());
//--off        combined_err=error->getVal();
//--off
//--off 	binnedData.get(i);
//--off        binnedData.set(binnedData.weight(),addstatandsyst(binnedData.weightError(RooAbsData::SumW2),combined_err));
//--off        binnedData.weightError(RooAbsData::SumW2);
//--off        cout<<" Bin "<<i<<" x = "<<binnedData.get(i)->getRealValue("Bplus_Corrected_Mass")<<" Weight="<<binnedData.weight()<<"New Weight Error= "<<binnedData.weightError(RooAbsData::SumW2)<<endl;
//--off        errorsheet<<i<<" & "<<binnedData.get(i)->getRealValue("Bplus_Corrected_Mass")<<"& "<<binnedData.weight()<<" & "<<binnedData.weightError(RooAbsData::SumW2)<<endl;
//--off        }
//--off
//--off
//------------------------------------------Merge the last six bins------------------------------------------------//
  //      Double_t newbinning[9]={4000,4200,4400,4600,4800,5000,5200,5400,5600,5800,7000};


        
        RooBinning newbinning(4000,7000);
        newbinning.addBoundary(4200);
        newbinning.addBoundary(4400);
        newbinning.addBoundary(4600);
        newbinning.addBoundary(4800);
        newbinning.addBoundary(5000);
        newbinning.addBoundary(5200);
        newbinning.addBoundary(5400);
        newbinning.addBoundary(5600);
        newbinning.addBoundary(5800);
//        newbinning.addBoundary(7000);
    
        newbinning.Print();
       Bplus_Corrected_Mass.setBinning(newbinning);
//        newbinning.add(4200);
	RooDataHist binnedData_new("binnedData_new","binnedData_new",RooArgSet(Bplus_Corrected_Mass));//,RooArgSet(newbinning));

	for (int z(0); z<9; z++)
	{
		binnedData.get(z);
		binnedData_new.get(z);
		binnedData_new.set(binnedData.weight(),binnedData.weightError(RooAbsData::SumW2));

	}

	cout<<"See what happened to values by merging bins: "<<endl; 
	errorsheet<<"----------------merging last 6 bins-------------"<<endl;
	for (int i(0); i<9; i++)
	{
		binnedData_new.get(i);
		cout<<" Bin "<<i<<" x = "<<binnedData_new.get(i)->getRealValue("Bplus_Corrected_Mass")<<" Weight="<<binnedData_new.weight()<<"New Weight Error= "<<binnedData_new.weightError(RooAbsData::SumW2)<<endl;
		errorsheet<<i<<" & "<<binnedData_new.get(i)->getRealValue("Bplus_Corrected_Mass")<<"& "<<binnedData_new.weight()<<" & "<<binnedData_new.weightError(RooAbsData::SumW2)<<endl;
	}


	cout<<"cummulative info about last 6 bins: "<<endl;
	double value(0);
	double error(0);

	for (int j(9); j<15; j++)
	{

		binnedData.get(j);
		value+=binnedData.weight();
                errorsheet<<" Adding value for the last bin "<<binnedData.weight()<<endl;
		error+=(binnedData.weightError(RooAbsData::SumW2)*binnedData.weightError(RooAbsData::SumW2));
                errorsheet<<" Adding error for the last bin "<<binnedData.weightError(RooAbsData::SumW2)<<endl;
	}

	for (int i(9); i<10; i++)
	{
		binnedData_new.get(i);
		binnedData_new.set(value/6.0,(((sqrt(error))/6.0)));
	}

	errorsheet<<"----------------Info about the last bin-------------"<<endl;
	for (int i(9); i<10; i++)
	{
//		cout<<" Bin "<<i<<" x = "<<binnedData_new.get(i)->getRealValue("Bplus_Corrected_Mass")<<" Weight="<<binnedData_new.weight()<<"New Weight Error= "<<binnedData_new.weightError(RooAbsData::SumW2)<<endl;

		binnedData_new.get(i);
		errorsheet<<i<<" & "<<binnedData_new.get(i)->getRealValue("Bplus_Corrected_Mass")<<"& "<<binnedData_new.weight()<<" & "<<binnedData_new.weightError(RooAbsData::SumW2)<<endl;

		cout<<" Bin "<<i<<" x = "<<binnedData_new.get(i)->getRealValue("Bplus_Corrected_Mass")<<" Weight="<<binnedData_new.weight()<<"New Weight Error= "<<binnedData_new.weightError(RooAbsData::SumW2)<<endl;
	}

        cout<<"Integral of old "<<binnedData_new.sum(kTRUE)<<endl;
        cout<<"Integral of new "<<binnedData_new.sum(kTRUE)<<endl;

//-----------------------------------------Chi2 fit----------------------------------------------------------------//

        cout<<"Number of bins for chi2 fit "<<binnedData_new.numEntries()<<endl;
	RooChi2Var chi2("chi2","chi2",two_ext4,binnedData_new,RooFit::Range("sideband"),SumW2Error(kTRUE),Extended());
        
//        cout<<"Number of bins for chi2 fit "<<binnedData.numEntries()<<endl;
//	RooChi2Var chi2("chi2","chi2",two_ext4,binnedData,RooFit::Range("sideband"),SumW2Error(kTRUE),Extended());
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


        ofstream out_ana((plotdir+"NOFCME_FitResults_Bin_CHI2_forANA.tex").c_str());

        out_ana<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        out_ana<<"\\usepackage[pdftex]{graphicx}"<<endl;
        out_ana<<"\\usepackage{url}"<<endl;
        out_ana<<"\\usepackage{mathtools}"<<endl;
        out_ana<<"\\usepackage{amsmath}"<<endl;
        out_ana<<"\\usepackage{graphicx}"<<endl;
        out_ana<<"\\usepackage[table]{xcolor}"<<endl;
        out_ana<<"\\usepackage{amsmath,amssymb}"<<endl;
        out_ana<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        out_ana<<"\\usepackage{colortbl}"<<endl;
        out_ana<<"\\begin{document}"<<endl;
        out_ana<<"\\begin{table}[ht]"<<endl;
        out_ana<<"\\small"<<endl;
        out_ana<<"\\begin{center}"<<endl;
        out_ana<<"\\begin{tabular}{| l | l | }"<<endl;
        out_ana<<"\\hline"<<endl;
        out_ana<<"Variable & Value \\\\ "<<endl;
        out_ana<<"\\hline"<<endl;
        out_ana<<"mean & "<<round_to_digits(cbmeanr4.getVal(),3)<<" $\\pm$ "<<round_to_digits(cbmeanr4.getError(),3)<<" \\\\"<<endl;
        out_ana<<"$\\sigma$ & "<<round_to_digits(cbsigmar4.getVal(),3)<<" $\\pm $ "<<round_to_digits(cbsigmar4.getError(),3)<<" \\\\"<<endl;
        out_ana<<"number & "<<round_to_digits(sig4.getVal()*100.0,3)<<"$ \\pm $"<<round_to_digits(sig4.getError()*100.0,3)<<" \\\\"<<endl;
        out_ana<<"$n$ (fixed) & "<<round_to_digits(nr4.getVal(),3)<<" \\\\"<<endl;
        out_ana<<"$\\alpha$ (fixed) & "<<round_to_digits(alphar4.getVal(),3)<<" \\\\"<<endl;
        out_ana<<"\\hline"<<endl;
        out_ana<<"\\end{tabular}"<<endl;
        out_ana<<"\\end{center}"<<endl;
        out_ana<<"\\caption{$\\chi^{2}$ of the binned $\\chi^{2}$ fit to the "<<type<<" sample: "<<round_to_digits(chi2.getVal(),3)<<" .}"<<endl;
        out_ana<<"\\end{table}"<<endl;
        out_ana<<"\\end{document}"<<endl;


        TFile fillinfo("../MisidFit_info/MisidFit_info.root","RECREATE");
        TTree fillinfotree(("MisidFit_info_"+type).c_str(),("MisidFit_info_"+type).c_str());
        double mean(0);
        double mean_err(0);
        double sigma(0);
        double sigma_err(0);
        double number(0);
        double number_err(0);
        double n(0);
        double n_err(0);
        double alpha(0);
        double alpha_err(0);
        fillinfotree.Branch("mean",&mean,"mean/D");// "Cut/C");
        fillinfotree.Branch("mean_err",&mean_err,"mean_err/D");// "Cut/C");
        fillinfotree.Branch("sigma",&sigma,"sigma/D");// "Cut/C");
        fillinfotree.Branch("sigma_err",&sigma_err,"sigma_err/D");// "Cut/C");

        fillinfotree.Branch("number",&number,"number/D");// "Cut/C");
        fillinfotree.Branch("number_err",&number_err,"number_err/D");// "Cut/C");

        fillinfotree.Branch("n",&n,"n/D");// "Cut/C");
        fillinfotree.Branch("n_err",&n_err,"n_err/D");// "Cut/C");
      
	fillinfotree.Branch("alpha",&alpha,"alpha/D");// "cut/c");
        fillinfotree.Branch("alpha_err",&alpha_err,"alpha_err/D");// "Cut/C");

        mean=cbmeanr4.getVal();
        mean_err=cbmeanr4.getError();

        sigma=cbsigmar4.getVal();
        sigma_err=cbsigmar4.getError();

        number=sig4.getVal()*100.0;
        number_err=sig4.getError()*100.0;

        n=nr4.getVal();
        n_err=nr4.getError();

        alpha=alphar4.getVal();
        alpha_err=alphar4.getError();

        fillinfotree.Fill();
        fillinfotree.Write("",TObject::kOverwrite);




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

         //--------------------make a new covariance matrix-----------------------//
         double oldval02=cov_chi[0][2];
         double oldval12=cov_chi[1][2];
         double oldval22=cov_chi[2][2];
         double oldval21=cov_chi[2][1];
         double oldval20=cov_chi[2][0];

	 TMatrixDSym cov_chi_new(cov_chi);
	 cov_chi_new[0][2]=oldval02*100.0;
	 cov_chi_new[1][2]=oldval12*100.0;
	 cov_chi_new[2][2]=oldval22*10000.0;
	 cov_chi_new[2][1]=oldval21*100.0;
	 cov_chi_new[2][0]=oldval20*100.0;         
	 //cov_chi_new[0][2]=0.0;
	 //cov_chi_new[1][2]=0.0;
	 //cov_chi_new[2][1]=0.0;
	 //cov_chi_new[2][0]=0.0;
	 //cov_chi_new[1][0]=0.0;
	 //cov_chi_new[0][1]=0.0;
	 //cov_chi_new[3][3]=1.0; 
	 //cov_chi_new[4][4]=1.0;

	 cout<<"Print new matrix "<<endl;
	 cov_chi_new.Print("v");
                                                                                          

         //---------------------function that shall be passed------------------------------//
         RooExtendPdf two_ext5("two_ext5","two_ext5",twocbs3,misid_scaled);
         RooMultiVarGaussian mvg("mvg", "mvg",RooArgSet(cbmeanr4,cbsigmar4,misid_scaled),RooArgSet(mu_cbmeanr4,mu_cbsigmar4,mu_sig4),cov_chi_new);

         //RooMultiVarGaussian misidModel("misidModel", "misidModel",pars,RooArgSet(mu_sig4,mu_cbmeanr4,mu_cbsigmar4),cov_chi);
         RooProdPdf misidModel("misidModel", "model from binned chi2 fit", RooArgSet(two_ext5, mvg));


//-----------------------------------Dokonci-------------//


	Bplus_Corrected_Mass.setRange("low",4000,4500);
	Bplus_Corrected_Mass.setRange("high",5500,7000);
	Bplus_Corrected_Mass.setRange("full",4000,7000);
	Bplus_Corrected_Mass.setRange("blind",4500,5500);
	RooAbsReal* integral_low = two_ext4.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("low"));

	double int_low = integral_low->getVal(); 

	RooAbsReal* integral_high = two_ext4.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("high"));

	double int_high = integral_high->getVal();

	RooAbsReal* integral_full = two_ext4.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("full"));

	double int_full = integral_full->getVal();

	RooAbsReal* integral_blind = two_ext4.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("blind"));

	double int_blind = integral_blind->getVal();
	cout<<"Integral in low: " << int_low <<endl;
	cout<<"Integral in high: " << int_high<<endl;
	cout<<"Integral in full: " << int_full<<endl;
        cout<<"Integral in blinded: " << int_blind<<endl;
//-------------Plot non uniform fit on non-nonuniform staff-------roofit is broken----


	RooPlot* ibou_nonuni = Bplus_Corrected_Mass.frame(Title(" ")) ;
	binnedData_new.plotOn(ibou_nonuni,DataError(RooAbsData::SumW2)); 
        two_ext4.plotOn(ibou_nonuni);
	RooPlot* ibou_nonuni2 = Bplus_Corrected_Mass.frame(Title("Binned histogram Non uniform bin")) ;
	binnedData_new.plotOn(ibou_nonuni2,DataError(RooAbsData::SumW2));
	two_ext4.plotOn(ibou_nonuni2) ;
	two_ext4.paramOn(ibou_nonuni2,Layout(0.55));
   


	RooHist* hresidcom_nonuni = ibou_nonuni2->residHist();
	RooHist* hpullcom_nonuni = ibou_nonuni2->pullHist();
	RooPlot* framecom1_nonuni = Bplus_Corrected_Mass.frame(Title("Residual Distribution"));
	framecom1_nonuni->addPlotable(hresidcom_nonuni,"P");
	RooPlot* framecom2_nonuni = Bplus_Corrected_Mass.frame(Title("Pull Distribution")) ;
	framecom2_nonuni->addPlotable(hpullcom_nonuni,"P");


	TCanvas* canvibou_nonuni = new TCanvas("binnedversionmisid_nonuni","binnedversionmisid_nonuni",800,800) ;
	canvibou_nonuni->Divide(2,2) ;
	canvibou_nonuni->cd(1); gPad->SetLeftMargin(0.15) ; ibou_nonuni->GetYaxis()->SetTitleOffset(1.1) ; ibou_nonuni->GetXaxis()->SetTitle("Corrected Mass") ;  ibou_nonuni->Draw() ;
	canvibou_nonuni->cd(2); gPad->SetLeftMargin(0.15) ; ibou_nonuni2->GetYaxis()->SetTitleOffset(1.1) ; ibou_nonuni2->GetXaxis()->SetTitle("Corrected Mass") ;  ibou_nonuni2->Draw() ;
	canvibou_nonuni->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom1_nonuni->GetYaxis()->SetTitleOffset(1.1) ; framecom1_nonuni->GetXaxis()->SetTitle("Corrected Mass") ; framecom1_nonuni->Draw() ;
	canvibou_nonuni->cd(4) ; gPad->SetLeftMargin(0.15) ; framecom2_nonuni->GetYaxis()->SetTitleOffset(1.1) ; framecom2_nonuni->GetXaxis()->SetTitle("Corrected Mass") ; framecom2_nonuni->Draw() ;
	canvibou_nonuni->SaveAs((workspacedir+"totalmisidfit_NOTMAIN_nonunibin_all_"+type+".pdf").c_str());         

	delete canvibou_nonuni; 

//----------Non uni on uni plotting issue resolved--------------------//

        TColor* col4 = gROOT->GetColor(99);
        col4->SetRGB(double(128)/double(255),double(177)/double(255),double(211)/double(255)); //blue

	RooPlot* ibou = Bplus_Corrected_Mass.frame(Title(" ")) ;
	binnedData.plotOn(ibou,DataError(RooAbsData::SumW2)); 
        two_ext4.plotOn(ibou,LineColor(99));
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
	canvibou->cd(1); gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.1) ; ibou->GetXaxis()->SetTitle("Corrected Mass") ;  ibou->Draw() ;
	canvibou->cd(2); gPad->SetLeftMargin(0.15) ; ibou2->GetYaxis()->SetTitleOffset(1.1) ; ibou2->GetXaxis()->SetTitle("Corrected Mass") ;  ibou2->Draw() ;
	canvibou->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom1->GetYaxis()->SetTitleOffset(1.1) ; framecom1->GetXaxis()->SetTitle("Corrected Mass") ; framecom1->Draw() ;
	canvibou->cd(4) ; gPad->SetLeftMargin(0.15) ; framecom2->GetYaxis()->SetTitleOffset(1.1) ; framecom2->GetXaxis()->SetTitle("Corrected Mass") ; framecom2->Draw() ;
	canvibou->SaveAs((workspacedir+"totalmisidfit_NOTMAIN_all_"+type+".pdf").c_str());         

	delete canvibou; 

	//---------------------------------------------Pull Plot------------------------------------------------------------//
        ibou->Print("V");

	auto dataHist = (RooHist*)ibou->getHist("h_binnedData");

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
	auto curve1 = (RooCurve*)ibou->getObject(1);
	auto hres1 = dataHist->makePullHist(*curve1,true);

	RooPlot* frame10 = Bplus_Corrected_Mass.frame(Title(""));
	frame10->addPlotable(hres1,"P");
	TCanvas c_pullplot("pullplot", "pullplot", 800, 150);
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


	//----------Draw Histo + Pull ! dont do external function because it doesnt preserve stuff-----------------//
        //TColor* col4 = gROOT->GetColor(99);
        //col4->SetRGB(double(128)/double(255),double(177)/double(255),double(211)/double(255)); //blue



	TCanvas canv("canv", "canv", 800, 600);
	ibou->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");
        ibou->GetYaxis()->SetTitle("Entries / (200 MeV/c^{2})");
	ibou->GetYaxis()->SetTitleOffset(0.9);
	ibou->Draw();

	canv.Print((workspacedir+"plotMisidFitPretty_"+type+"_nopull.pdf").c_str());
	canv.Print((workspacedir+"plotMisidFitPretty_"+type+"_nopull.root").c_str());

	TCanvas canvTot("canvTot", "canvTot", 600, 600);
	canvTot.Divide(1,2);
	canvTot.cd(1);
	gPad->SetPad(0.005, 0.205, 0.995, 0.995);
	canv.DrawClonePad();

	canvTot.cd(2);
	gPad->SetPad(0.005, 0.005, 0.995, 0.2);
	c_pullplot.DrawClonePad();

	canvTot.Print((workspacedir+"plotMisidFitPretty_"+type+".pdf").c_str());
	canvTot.Print((workspacedir+"plotMisidFitPretty_"+type+".root").c_str());





	TCanvas* canvnew = new TCanvas("misidplot","mBplus_Corrected_Massnew",800,800) ;
	gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.1) ; ibou->GetXaxis()->SetTitle("Corrected Mass") ;  ibou->Draw();
	TFile *fm = new TFile((workspacedir+"plotmisid_all_"+type+".root").c_str(),"RECREATE");
	canvnew->Write();
	fm->Close();
	delete fm;
	delete canvnew;

//-------------Will Propagate function that is prod(F)*contraintsfromchi2(fit)-------------------//

	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	string namews8="misid";
	TFile wrkspc8((workspacedir+"myworkspace_"+namews8+".root").c_str(),"RECREATE");
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

vector<double> FitAndSplotB23MuNuDataForTraining::fitmisidcomponentall_compare(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type)
{

	cout<<"Start misid fit all components"<<endl;


        TFile* s = new TFile((dir.at(0)+"/"+misidfilenames.at(0)+type+".root").c_str());
        TTree* treep = (TTree*)s->Get("DecayTree");

        RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
        Bplus_Corrected_Mass.setRange("sideband",4000,7000);
//        Bplus_Corrected_Mass.setBins(60);
        RooRealVar crossfeedweight(weights.at(0).c_str(),weights.at(0).c_str(), 0.0 ,1.0);

        RooDataSet dp("dp","dp",RooArgSet(Bplus_Corrected_Mass),Import(*treep));
        RooDataSet dpw("dpw","dpw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treep), WeightVar(weights.at(0).c_str()));//, Import(*treew));
        dp.Print();
        dpw.Print();

        ofstream out;
        out.open((workspacedir+"misid_comp_number"+type+".txt").c_str());
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
                Bplus_Corrected_Mass.setRange("sideband",4000,7000);
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
	canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.1) ; misidtotal->Draw() ;
	canvtot->SaveAs((workspacedir+"totalmisid_NOTMAIN_all_"+type+".pdf").c_str());

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
        comp->cd(1); gPad->SetLeftMargin(0.15) ; wei_unbinned->GetYaxis()->SetTitleOffset(1.1) ; wei_unbinned->GetXaxis()->SetTitle("Corrected Mass") ;  wei_unbinned->Draw() ;
        comp->cd(2); gPad->SetLeftMargin(0.15) ; wei_binned->GetYaxis()->SetTitleOffset(1.1) ; wei_binned->GetXaxis()->SetTitle("Corrected Mass") ;  wei_binned->Draw() ;
        comp->cd(3) ; gPad->SetLeftMargin(0.15) ; chi2_binned->GetYaxis()->SetTitleOffset(1.1) ; chi2_binned->GetXaxis()->SetTitle("Corrected Mass") ; chi2_binned->Draw() ;
        comp->cd(4) ; gPad->SetLeftMargin(0.15) ; all->GetYaxis()->SetTitleOffset(1.1) ; all->GetXaxis()->SetTitle("Corrected Mass") ; all->Draw() ;
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



//void FitAndSplotB23MuNuDataForTraining::makeSWeightedTree(string extracut, string label)
//{
//   TFile fw(workspaceFileName.c_str());
//
//   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
//   if(!workspaceFit)
//   {
//      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::makeSWeightedTree, no workspace found in file "<<workspaceFileName<<endl;
//      return;
//   }
//
//   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
//   RooAbsPdf* model_total = workspaceFit->pdf("model");
//   RooRealVar* sig = workspaceFit->var("sig");
//   RooRealVar* bkg = workspaceFit->var("bkg");
//
//   if(!data || !model_total || !sig || !bkg)
//   {
//      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::makeSWeightedTree, error downloading stuff from workspace"<<endl;
//      return;
//   }
//
//
//   TFile f( (tupledir+"/"+tuplenamelow).c_str());
//   TTree* t = (TTree*)f.Get(treename.c_str());
//
//   if(!t)
//   {
//      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::makeSWeightedTree, no tree "<<treename<<" found in "<<tupledir<<"/"<<tuplenamelow<<endl;
//      return;
//   }
//
//   RooStats::SPlot wdata("wData", "wData", *data, model_total, RooArgList(*sig, *bkg));
//
//
//   double Bplus_Corrected_Mass;
//   t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
//
//   string nameNewFile(tupledir+"/"+tuplenamelow);
//   nameNewFile.insert(nameNewFile.size()-5, label);
//   TFile f2(nameNewFile.c_str(), "RECREATE");
//   TTree* t2 = t->CloneTree(0);
//   double sig_sw;
//   double bkg_sw;
//
//   t2->Branch("sig_sw", &sig_sw, "sig_sw/D");
//   t2->Branch("bkg_sw", &bkg_sw, "bkg_sw/D");
//
//
//
//   int j(0);
//
//   if(data->sumEntries() == t->GetEntries(("Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)).c_str() ) )
//   {
//      cout<<"Putting the sweights in the tree... Filling "<<data->sumEntries()<<" entries"<<endl;
//   }
//   else
//   {
//      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::makeSWeightedTree, mismatch in the number of entries"<<endl;
//      cerr<<"data: "<<data->sumEntries()<<" entries. tuple: "<<t->GetEntries(("Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)).c_str())<<" entries."<<endl;
//   }
//
//   int nEntries(t->GetEntries());
//
//   if(extracut == "") extracut = "1";
//   TTreeFormula ttf( "ttf", extracut.c_str(), t);
//
//   for(int i(0); i<nEntries; ++i)
//   {
//      t->GetEntry(i);
//
//      if(i % (nEntries/10) == 0) cout<<100*i/nEntries<<"\% "<<flush;
//
//      if(Bplus_Corrected_Mass > Bplus_Corrected_Mass_min && Bplus_Corrected_Mass < Bplus_Corrected_Mass_max) 
//      {
//         sig_sw = wdata.GetSWeight(j,"sig");
//         bkg_sw = wdata.GetSWeight(j,"bkg");
//         if(ttf.EvalInstance()) t2->Fill();
//         ++j;
//      }
//   }
//
//   t2->Write();
//
//   f2.Close();
//   fw.Close();
//   f.Close();
//}

void FitAndSplotB23MuNuDataForTraining::plotprettysim_chi2_overlay(string type, string pidcutRun1, string pidcutRun2)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw((clsdir+"fitresults_forCLs.root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
   RooDataSet* data = (RooDataSet*)workspaceFit->data(("data"));
   RooAbsPdf* model_total = workspaceFit->pdf(("normpdf"));

   Bplus_Corrected_Mass->setRange("high",5501,7000);
   Bplus_Corrected_Mass->setRange("low",4000,4499);
   Bplus_Corrected_Mass->setRange("full",4000,7000);



   if(!data || !Bplus_Corrected_Mass || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   TFile nofitdata((workspacedir+"NoFitData.root").c_str());

   RooWorkspace* workspacenofit = (RooWorkspace*)nofitdata.Get("workspaceNoFitData");

   if(!workspacenofit)
   {
	   cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<endl;
	   return;
   }

   RooRealVar* Bplus_Corrected_Massnofit = workspacenofit->var("Bplus_Corrected_Mass");
   RooDataSet* datanofit = (RooDataSet*)workspacenofit->data("data");

   if(!datanofit || !Bplus_Corrected_Massnofit)
   {
	   cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining, error downloading stuff from workspace"<<endl;
	   return;
   }






   Bplus_Corrected_Mass->setBins(30);
   RooPlot* frame = Bplus_Corrected_Mass->frame(Title(""));
   data->plotOn(frame,RooFit::Name("fitdata"));
//   model_total->plotOn(frame, RooFit::Range("low,high"), RooFit::NormRange("low,high"), RooFit::LineColor(kBlue) );
   model_total->plotOn(frame, RooFit::Range("low,high"), RooFit::NormRange("low,high"), RooFit::LineColor(kBlue) );
  
 
   frame->Print("V");


//   auto dataHist = (RooHist*) frame->getHist(("h_data"));
   auto dataHist = (RooHist*) frame->getHist(("fitdata"));

   cout<<"NGet "<<dataHist->GetN()<<endl;
  //TGraphAsymmErrors tgae(datahist->GetN());
  // tgae.SetTitle("");
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
//   if(numy=dataHist->GetY();)
//      tgae.SetPoint(i,x,y);
//      tgae.SetPointError(i, hist->GetErrorXlow(i), hist->GetErrorXhigh(i),
//            hist->GetErrorYlow(i), hist->GetErrorYhigh(i));
   }
   auto curve1 = (RooCurve*) frame->getObject(1);
   auto curve2 = (RooCurve*) frame->getObject(2);
   auto hres1 = dataHist->makePullHist(*curve1,true);
   auto hres2 = dataHist->makePullHist(*curve2,true);
  
   RooPlot* frame10 = Bplus_Corrected_Mass->frame(Title(""));
   frame10->addPlotable(hres1,"P");
   frame10->addPlotable(hres2,"P");
   TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",600,150) ;
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
   canv4->SaveAs("PULL.pdf");

   savePullPlot(*frame, plotdir+type+"pullPlot.root");
   TFile fpull((plotdir+type+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

   model_total->plotOn(frame, RooFit::Range("full"), RooFit::NormRange("low,high"), RooFit::LineColor(kBlue) );
   model_total->plotOn(frame, RooFit::LineColor(kRed),RooFit::Components(("newexpoun")),RooFit::NormRange("low,high"), RooFit::Range("full"), RooFit::Name("combinatorial"));
   model_total->plotOn(frame, RooFit::LineColor(kCyan),RooFit::Components(("misidModel")),RooFit::NormRange("low,high"), RooFit::Range("full"), RooFit::Name("mis2"));
   model_total->plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components(("newpartreco")),RooFit::NormRange("low,high"), RooFit::Range("full"), RooFit::Name("partreco"));
   datanofit->plotOn(frame, MarkerSize(0.9),MarkerColor(kGreen),LineColor(kGreen),RooFit::Name("signaldata"));


   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
   leg->AddEntry(frame->findObject("mis2"),"Misid","l");
   leg->AddEntry(frame->findObject("partreco"),"PartReco","l");
  leg->AddEntry(frame->findObject("signaldata"),"Data_SigRegion","l");
   leg->AddEntry(frame->findObject("fitdata"),"Data_FitRegion","l");



   ofstream out((plotdir+type+"FitResults_Overlay.txt").c_str());
   saveFitInfo(out, frame, 2, model_total);

   //frame10->Chi2

   TCanvas canv("canv", "canv", 600, 600);
   frame->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");
   frame->Draw();
   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   canv4->DrawClonePad();

   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitPretty_chi2_Overlay.pdf").c_str());
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitPretty_chi2_Overlay.root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitLogyPretty_chi2_Overlay.pdf").c_str());
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitLogyPretty_chi2_Overlay.root").c_str());

   fw.Close();
   fpull.Close();
}

void FitAndSplotB23MuNuDataForTraining::plotprettysim_chi2(string type, string pidcutRun1, string pidcutRun2)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw((clsdir+"fitresults_forCLs.root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
   RooDataSet* data = (RooDataSet*)workspaceFit->data(("data"));
   RooAbsPdf* model_total = workspaceFit->pdf(("normpdf"));

   Bplus_Corrected_Mass->setRange("high",5501,7000);
   Bplus_Corrected_Mass->setRange("low",4000,4499);



   if(!data || !Bplus_Corrected_Mass || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   Bplus_Corrected_Mass->setBins(60);
   RooPlot* frame = Bplus_Corrected_Mass->frame(Title(""));
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::Range("low,high"), RooFit::NormRange("low,high"), RooFit::LineColor(kBlue) );
   
   frame->Print("V");


   auto dataHist = (RooHist*) frame->getHist(("h_data"));

   cout<<"NGet "<<dataHist->GetN()<<endl;
  //TGraphAsymmErrors tgae(datahist->GetN());
  // tgae.SetTitle("");
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
//   if(numy=dataHist->GetY();)
//      tgae.SetPoint(i,x,y);
//      tgae.SetPointError(i, hist->GetErrorXlow(i), hist->GetErrorXhigh(i),
//            hist->GetErrorYlow(i), hist->GetErrorYhigh(i));
   }
   auto curve1 = (RooCurve*) frame->getObject(1);
   auto curve2 = (RooCurve*) frame->getObject(2);
   auto hres1 = dataHist->makePullHist(*curve1,true);
   auto hres2 = dataHist->makePullHist(*curve2,true);
  
   RooPlot* frame10 = Bplus_Corrected_Mass->frame(Title(""));
   frame10->addPlotable(hres1,"P");
   frame10->addPlotable(hres2,"P");
   TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",600,150) ;
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
   canv4->SaveAs("PULL.pdf");

   savePullPlot(*frame, plotdir+type+"pullPlot.root");
   TFile fpull((plotdir+type+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

   model_total->plotOn(frame, RooFit::LineColor(kRed),RooFit::Components(("newexpoun")),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("combinatorial"));
   model_total->plotOn(frame, RooFit::LineColor(kCyan),RooFit::Components(("misidModel")),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis2"));
   model_total->plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components(("newpartreco")),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("partreco"));


   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
   leg->AddEntry(frame->findObject("mis2"),"Misid","l");
   leg->AddEntry(frame->findObject("partreco"),"PartReco","l");


   ofstream out((plotdir+type+"FitResults.txt").c_str());
   saveFitInfo(out, frame, 2, model_total);

   //frame10->Chi2

   TCanvas canv("canv", "canv", 600, 600);
   frame->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");
   frame->Draw();
   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   canv4->DrawClonePad();

   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitPretty_chi2.pdf").c_str());
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitPretty_chi2.root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitLogyPretty_chi2.pdf").c_str());
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitLogyPretty_chi2.root").c_str());

   fw.Close();
   fpull.Close();
}

void FitAndSplotB23MuNuDataForTraining::plotprettysim(string type)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw((clsdir+"fitresults_forCLs.root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
   RooDataSet* data = (RooDataSet*)workspaceFit->data(("data"));
   RooAbsPdf* model_total = workspaceFit->pdf(("normpdf"));

   Bplus_Corrected_Mass->setRange("high",5501,7000);
   Bplus_Corrected_Mass->setRange("low",4000,4499);



   if(!data || !Bplus_Corrected_Mass || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   Bplus_Corrected_Mass->setBins(60);
   RooPlot* frame = Bplus_Corrected_Mass->frame(Title(""));
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::Range("low,high"), RooFit::NormRange("low,high"), RooFit::LineColor(kBlue) );
   
   frame->Print("V");


   auto dataHist = (RooHist*) frame->getHist(("h_data"));

   cout<<"NGet "<<dataHist->GetN()<<endl;
  //TGraphAsymmErrors tgae(datahist->GetN());
  // tgae.SetTitle("");
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
//   if(numy=dataHist->GetY();)
//      tgae.SetPoint(i,x,y);
//      tgae.SetPointError(i, hist->GetErrorXlow(i), hist->GetErrorXhigh(i),
//            hist->GetErrorYlow(i), hist->GetErrorYhigh(i));
   }
   auto curve1 = (RooCurve*) frame->getObject(1);
   auto curve2 = (RooCurve*) frame->getObject(2);
   auto hres1 = dataHist->makePullHist(*curve1,true);
   auto hres2 = dataHist->makePullHist(*curve2,true);
  
   RooPlot* frame10 = Bplus_Corrected_Mass->frame(Title(""));
   frame10->addPlotable(hres1,"P");
   frame10->addPlotable(hres2,"P");
   TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",600,150) ;
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
   canv4->SaveAs("PULL.pdf");

   savePullPlot(*frame, plotdir+type+"pullPlot.root");
   TFile fpull((plotdir+type+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

   model_total->plotOn(frame, RooFit::LineColor(kRed),RooFit::Components(("newexpoun")),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("combinatorial"));
   model_total->plotOn(frame, RooFit::LineColor(kCyan),RooFit::Components(("twocbs")),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis2"));
   model_total->plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components(("newpartreco")),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("partreco"));


   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
   leg->AddEntry(frame->findObject("mis2"),"Misid","l");
   leg->AddEntry(frame->findObject("partreco"),"PartReco","l");


   ofstream out((plotdir+type+"FitResults.txt").c_str());
   saveFitInfo(out, frame, 2, model_total);

   //frame10->Chi2

   TCanvas canv("canv", "canv", 600, 600);
   frame->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");
   frame->Draw();
   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   canv4->DrawClonePad();

   canvTot.Print((plotdir+type+"plotB23MuNuFitPretty.pdf").c_str());
   canvTot.Print((plotdir+type+"plotB23MuNuFitPretty.root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+type+"plotB23MuNuFitLogyPretty.pdf").c_str());
   canvTot.Print((plotdir+type+"plotB23MuNuFitLogyPretty.root").c_str());

   fw.Close();
   fpull.Close();
}



void FitAndSplotB23MuNuDataForTraining::plot()
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw(workspaceFileName.c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("normpdf");

   if(!data || !Bplus_Corrected_Mass || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   RooPlot* frame = Bplus_Corrected_Mass->frame();
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kRed) );

   savePullPlot(*frame, plotdir+"pullPlot.root");
   TFile fpull((plotdir+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

   model_total->paramOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total->plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("cb1"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->Draw();

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();

   canvTot.Print((plotdir+"plotB23MuNuFit.pdf").c_str());
   canvTot.Print((plotdir+"plotB23MuNuFit.root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+"plotB23MuNuFitLogy.pdf").c_str());
   canvTot.Print((plotdir+"plotB23MuNuFitLogy.root").c_str());

   fw.Close();
   fpull.Close();
}

void FitAndSplotB23MuNuDataForTraining::fitJpsiKData4(bool binnedFit)
{
   cout<<"fitting"<<endl;

   //Get the dataset
    TFile* f = new TFile("/vols/lhcb/ss4314/fitsignalchannelFUMSB/workspace_fitfunction/myworkspace_beforefit.root");
    RooWorkspace* ws = (RooWorkspace*)f->Get("w");
    RooAbsPdf* pdf_b = ws->pdf("normpdf");
    RooRealVar* mass = ws->var("Bplus_Corrected_Mass");
    f->Close();


   TFile fw(workspaceFileName.c_str(), "UPDATE");

   RooWorkspace* workspaceData = (RooWorkspace*)fw.Get("workspaceData");
   if(!workspaceData)
   {
      cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_Corrected_Mass = workspaceData->var("Bplus_Corrected_Mass");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !Bplus_Corrected_Mass)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   Bplus_Corrected_Mass->setBins(60);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *Bplus_Corrected_Mass), *data) ;

   Bplus_Corrected_Mass->setRange("high",5501,7000);
   Bplus_Corrected_Mass->setRange("low",4000,4499);

   RooPlot* frame = Bplus_Corrected_Mass->frame();
   data->plotOn(frame);
   RooFitResult* fit = pdf_b->fitTo(*data,RooFit::Range("low,high"), RooFit::NormRange("low,high"),Extended(kTRUE),Save(kTRUE));
   pdf_b->paramOn(frame);
   //m.getParameters(Bplus_Corrected_Mass)->Print("s");
   pdf_b->plotOn(frame, RooFit::Range("low,high"), RooFit::NormRange("low,high"));
   pdf_b->plotOn(frame, RooFit::LineColor(kRed),RooFit::NormRange("low,high"), RooFit::Components("newexpoun"), RooFit::Range("low,high"));
   pdf_b->plotOn(frame, RooFit::LineColor(kCyan), RooFit::NormRange("low,high"), RooFit::Components("twocbs"), RooFit::Range("low,high"));
   pdf_b->plotOn(frame, RooFit::LineColor(kMagenta), RooFit::NormRange("low,high"), RooFit::Components("newpartreco"), RooFit::Range("low,high"));
   

   fit->Print("V");
   TCanvas canv("canv", "canv", 600, 600);
   frame->Draw();
   canv.Print((plotdir+"plotB23MuNu.pdf").c_str());
   canv.Print((plotdir+"plotB23MuNu.root").c_str());
  //save the fit function


   RooWorkspace workspaceFit("workspaceFit", "workspaceFit");

   workspaceFit.import(*data);
   workspaceFit.import(*pdf_b);

   //workspaceFit.writeToFile(workspaceFileName.c_str());
   workspaceFit.Write("", TObject::kOverwrite);

   cout<<"Workspace for fit has been saved:"<<endl;
   workspaceFit.Print(); 


   fw.Close();
  // fl.Close();
}

vector<double> FitAndSplotB23MuNuDataForTraining::fitsignalcomponent_byyear(string weightname, string type, string year, string PIDcut, string ending)
{ 


        cout<<"Start Signal Component fit"<<endl;

	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
	RooRealVar Bplus_corMassERR("Bplus_corMassERR","Bplus_corMassERR",0,600);
	RooRealVar weightnamevar(weightname.c_str(),weightname.c_str(), 0.0 ,1.0);

	TFile* f = new TFile((sigdir+"/"+signalfilename+ending+".root").c_str());
	TTree* t = (TTree*)f->Get("DecayTree");



	RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*t), WeightVar(weightname.c_str()));
	dr.Print();
 //       dr.SumW2(kTrue);

	RooRealVar cbmeanrar(("cbmeanrar"),("cbmeanrar"+type).c_str(), 5248.0, 5200.8, 5400.0);
	RooRealVar cbsigmarar(("cbsigmarar"),("cbsigmarar"+type).c_str(),87.0,50.0,300.0);//,0.1,50) ;
	RooRealVar cbsignalrar(("cbsignalrar"),("cbsignalrar"+type).c_str(),8400,7000,9000) ;
	RooRealVar nral(("nral"),"",0.33);//0.1,0.4);
	RooRealVar alpharal(("alpharal"),"",0.1,7.0);
	RooRealVar nrar(("nrar"),"",0.92);
	RooRealVar alpharar(("alpharar"),"",0.1,5.30);
	MyCB blah(("blah"), ("blah"+type).c_str(), Bplus_Corrected_Mass, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);


//	RooRealVar cbmeanrar(("cbmeanrar"),("cbmeanrar"+type).c_str(), 5248.0, 5200.8, 5400.0);
//	RooRealVar cbsigmarar(("cbsigmarar"),("cbsigmarar"+type).c_str(),0.1,300);//,0.1,50) ;
//	RooRealVar cbsignalrar(("cbsignalrar"),("cbsignalrar"+type).c_str(),8400,7000,9000) ;
//	RooRealVar nral(("nral"),"",0.1,0.4);
//	RooRealVar alpharal(("alpharal"),"",0.1,7.0);
//	RooRealVar nrar(("nrar"),"",0.1,2.0);
//	RooRealVar alpharar(("alpharar"),"",0.1,5.30);

//	RooRealVar cbmeanrar(("cbmeanrar"),("cbmeanrar"+type).c_str(), 5248.0, 5220.8, 5270.0);
//	RooRealVar cbsigmarar(("cbsigmarar"),("cbsigmarar"+type).c_str(),85,0.1,300);//,0.1,50) ;
//	RooRealVar cbsignalrar(("cbsignalrar"),("cbsignalrar"+type).c_str(),8400,7000,9000) ;
//	RooRealVar nral(("nral"),"",0.3,0.1,0.4);
//	RooRealVar alpharal(("alpharal"),"",2.8,0.1,7.0);
//	RooRealVar nrar(("nrar"),"",0.9,0.1,2.0);
//	RooRealVar alpharar(("alpharar"),"",0.326,0.1,5.30);
//	MyCB blah(("blah"), ("blah"+type).c_str(), Bplus_Corrected_Mass, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);
	RooPlot* frame8 = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double ccrystal ball function")) ;
	dr.plotOn(frame8);
	RooFitResult* sigfit=blah.fitTo(dr,SumW2Error(kTRUE),Save());



       // for (int u(0); u<3 ;u++)
       // {

//	RooRealVar cbmeanrar_imp(("cbmeanrar_imp"),("cbmeanrar"+type).c_str(), cbmeanrar.getVal(), 5220.8, 5400.0);
//	RooRealVar cbsigmarar_imp(("cbsigmarar_imp"),("cbsigmarar"+type).c_str(),cbsigmarar.getVal(),0.1,100);//,0.1,50) ;
//	RooRealVar cbsignalrar_imp(("cbsignalrar_imp"),("cbsignalrar"+type).c_str(),cbsignalrar.getVal(),7000,9000) ;
//	RooRealVar nral_imp(("nral_imp"),"",nral.getVal(),0.1,0.4);
//	RooRealVar alpharal_imp(("alpharal_imp"),"",alpharal.getVal(),0.1,7.0);
//	RooRealVar nrar_imp(("nrar_imp"),"",nrar.getVal(),0.1,2.0);
//	RooRealVar alpharar_imp(("alpharar_imp"),"",alpharar.getVal(),0.1,5.30);
//	MyCB blah_imp(("blah_imp"), ("blah"+type).c_str(), Bplus_Corrected_Mass, cbmeanrar_imp, cbsigmarar_imp, nral_imp , alpharal_imp, nrar_imp, alpharar_imp);
//	RooPlot* frame8_imp = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double ccrystal ball function")) ;
//	dr.plotOn(frame8_imp);
//	RooFitResult* sigfit_imp=blah_imp.fitTo(dr,SumW2Error(kTRUE),Save());
//       
//	RooRealVar cbmeanrar_imp2(("cbmeanrar_imp2"),("cbmeanrar"+type).c_str(), cbmeanrar_imp.getVal(), 5220.8, 5400.0);
//	RooRealVar cbsigmarar_imp2(("cbsigmarar_imp2"),("cbsigmarar"+type).c_str(),cbsigmarar_imp.getVal(),0.1,100);//,0.1,50) ;
//	RooRealVar cbsignalrar_imp2(("cbsignalrar_imp2"),("cbsignalrar"+type).c_str(),cbsignalrar_imp.getVal(),7000,9000) ;
//	RooRealVar nral_imp2(("nral_imp2"),"",nral_imp.getVal(),0.1,0.4);
//	RooRealVar alpharal_imp2(("alpharal_imp2"),"",alpharal_imp.getVal(),0.1,7.0);
//	RooRealVar nrar_imp2(("nrar_imp2"),"",nrar_imp.getVal(),0.1,2.0);
//	RooRealVar alpharar_imp2(("alpharar_imp2"),"",alpharar_imp.getVal(),0.1,5.30);
//	MyCB blah_imp2(("blah_imp2"), ("blah"+type).c_str(), Bplus_Corrected_Mass, cbmeanrar_imp2, cbsigmarar_imp2, nral_imp2 , alpharal_imp2, nrar_imp2, alpharar_imp2);
//	RooPlot* frame8_imp2 = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double ccrystal ball function")) ;
//	dr.plotOn(frame8_imp2);
//	RooFitResult* sigfit_imp2=blah_imp2.fitTo(dr,SumW2Error(kTRUE),Save());
      //  }


//        sigfit->Print("v");

        ofstream saveit(("../byyear/"+type+ending+"FitResults_Signal.txt").c_str());
        saveFitInfoExtended(saveit, frame8, 6, &blah,sigfit);
//        saveFitInfoExtended(saveit, frame8_imp, 6, &blah_imp,sigfit_imp);
//        saveFitInfoExtended(saveit, frame8_imp2, 6, &blah_imp2,sigfit_imp2);
        saveit.close();







	blah.plotOn(frame8);
	RooPlot* frameun = Bplus_Corrected_Mass.frame(Title(" ")) ;
	dr.plotOn(frameun);
	blah.plotOn(frameun);
	blah.paramOn(frameun);
	vector<double> myresults;
	cout<<"MBplus_Corrected_Mass fitted values:"<<endl; 
	cout<<cbmeanrar.getVal()<<endl;
	cout<<cbsigmarar.getVal()<<endl;
	cout<<cbsignalrar.getVal()<<endl;
	cout<<nral.getVal()<<endl;
	cout<<alpharal.getVal()<<endl;
	cout<<nrar.getVal()<<endl;
	cout<<alpharar.getVal()<<endl; 

	myresults.push_back(cbmeanrar.getVal());
	myresults.push_back(cbsigmarar.getVal());
	myresults.push_back(nral.getVal());
	myresults.push_back(alpharal.getVal());
	myresults.push_back(nrar.getVal());
	myresults.push_back(alpharar.getVal());

        cbmeanrar.setConstant();
        cbsigmarar.setConstant();
        cbsignalrar.setConstant();
        nral.setConstant();
        alpharal.setConstant();
        nrar.setConstant();
        alpharar.setConstant();
	//C a l c u l a t e  chi squared //

	cout<<"Chi squared: "<< frame8->chiSquare() <<endl;
	RooHist* hresid = frame8->residHist();
	RooHist* hpull = frame8->pullHist();
	RooPlot* frame9 = Bplus_Corrected_Mass.frame(Title("Residual Distribution"));
	frame9->addPlotable(hresid,"P");
	RooPlot* frame10 = Bplus_Corrected_Mass.frame(Title("Pull Distribution")) ;
	frame10->addPlotable(hpull,"P"); 


        TCanvas* canvlog = new TCanvas("pimumu","pimumu",600,600) ;
        frameun->Draw();



        TCanvas canvTot("canvTot", "canvTot", 600, 600);
        canvTot.Divide(1,2);
        canvTot.cd(1);
        gPad->SetPad(0.005, 0.205, 0.995, 0.995);
        canvlog->DrawClonePad();
        delete canvlog;


        savePullPlot(*frameun, "../byyear/pullPlot_mc.root");
        TFile fpull("../byyear/pullPlot_mc.root");
        TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");



        canvTot.cd(2);
        gPad->SetPad(0.005, 0.005, 0.995, 0.2);
        gPad->SetLeftMargin(0.15) ;
        cpull->DrawClonePad();
        canvTot.Print(("../byyear/mcsigfit_NOTMAIN_moreinfo_"+type+ending+".pdf").c_str());
        canvTot.Print(("../byyear/mcsigfit_NOTMAIN_moreinfo_"+type+ending+".root").c_str());




	TCanvas* canv4 = new TCanvas("mBplus_Corrected_Massattempt5","mBplus_Corrected_Massattempt5",800,800) ;
	canv4->Divide(2,2) ;
	canv4->cd(1) ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.1) ; frame8->Draw() ;
	canv4->cd(2) ; gPad->SetLeftMargin(0.15) ; frame9->GetYaxis()->SetTitleOffset(1.1) ; frame9->Draw() ;
	canv4->cd(3) ; gPad->SetLeftMargin(0.15) ; frame10->GetYaxis()->SetTitleOffset(1.1) ; frame10->Draw() ;
	canv4->cd(4) ; gPad->SetLeftMargin(0.15) ; frameun->GetYaxis()->SetTitleOffset(1.1) ; frameun->Draw() ;
	canv4->SaveAs(("../byyear/mcsigfit_NOTMAIN"+ending+".pdf").c_str());



	delete canv4;


	return(myresults);
}


vector<double> FitAndSplotB23MuNuDataForTraining::fitsignalcomponent(string weightname, string type, string year, string PIDcut)
{ 


        cout<<"Start Signal Component fit"<<endl;

	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
	RooRealVar Bplus_corMassERR("Bplus_corMassERR","Bplus_corMassERR",0,600);
	RooRealVar weightnamevar(weightname.c_str(),weightname.c_str(), 0.0 ,1.0);

	TFile* f = new TFile((sigdir+"/"+signalfilename+"2012"+PIDcut+"Strip21.root").c_str());
	TTree* t = (TTree*)f->Get("DecayTree");



	RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*t), WeightVar(weightname.c_str()));
	dr.Print();
 //       dr.SumW2(kTrue);


	RooRealVar cbmeanrar(("cbmeanrar"),("cbmeanrar"+type).c_str(), 5248.0, 5200.8, 5400.0);
	RooRealVar cbsigmarar(("cbsigmarar"),("cbsigmarar"+type).c_str(),0.1,100);//,0.1,50) ;
	RooRealVar cbsignalrar(("cbsignalrar"),("cbsignalrar"+type).c_str(),8400,7000,9000) ;
	RooRealVar nral(("nral"),"",0.1,0.4);
	RooRealVar alpharal(("alpharal"),"",0.1,7.0);
	RooRealVar nrar(("nrar"),"",0.1,2.0);
	RooRealVar alpharar(("alpharar"),"",0.1,5.30);
	MyCB blah(("blah"), ("blah"+type).c_str(), Bplus_Corrected_Mass, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);
	RooPlot* frame8 = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double ccrystal ball function")) ;
	dr.plotOn(frame8);
	blah.fitTo(dr,SumW2Error(kTRUE));
	blah.plotOn(frame8);
	RooPlot* frameun = Bplus_Corrected_Mass.frame(Title(" ")) ;
	dr.plotOn(frameun);
	blah.plotOn(frameun);
	blah.paramOn(frameun);
	vector<double> myresults;
	cout<<"MBplus_Corrected_Mass fitted values:"<<endl; 
	cout<<cbmeanrar.getVal()<<endl;
	cout<<cbsigmarar.getVal()<<endl;
	cout<<cbsignalrar.getVal()<<endl;
	cout<<nral.getVal()<<endl;
	cout<<alpharal.getVal()<<endl;
	cout<<nrar.getVal()<<endl;
	cout<<alpharar.getVal()<<endl; 

	myresults.push_back(cbmeanrar.getVal());
	myresults.push_back(cbsigmarar.getVal());
	myresults.push_back(nral.getVal());
	myresults.push_back(alpharal.getVal());
	myresults.push_back(nrar.getVal());
	myresults.push_back(alpharar.getVal());

        cbmeanrar.setConstant();
        cbsigmarar.setConstant();
        cbsignalrar.setConstant();
        nral.setConstant();
        alpharal.setConstant();
        nrar.setConstant();
        alpharar.setConstant();
	//C a l c u l a t e  chi squared //

	cout<<"Chi squared: "<< frame8->chiSquare() <<endl;
	RooHist* hresid = frame8->residHist();
	RooHist* hpull = frame8->pullHist();
	RooPlot* frame9 = Bplus_Corrected_Mass.frame(Title("Residual Distribution"));
	frame9->addPlotable(hresid,"P");
	RooPlot* frame10 = Bplus_Corrected_Mass.frame(Title("Pull Distribution")) ;
	frame10->addPlotable(hpull,"P"); 


        TCanvas* canvlog = new TCanvas("pimumu","pimumu",600,600) ;
        frameun->Draw();



        TCanvas canvTot("canvTot", "canvTot", 600, 600);
        canvTot.Divide(1,2);
        canvTot.cd(1);
        gPad->SetPad(0.005, 0.205, 0.995, 0.995);
        canvlog->DrawClonePad();
        delete canvlog;


        savePullPlot(*frameun, workspacedir+"pullPlot_mc.root");
        TFile fpull((workspacedir+"pullPlot_mc.root").c_str());
        TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");



        canvTot.cd(2);
        gPad->SetPad(0.005, 0.005, 0.995, 0.2);
        gPad->SetLeftMargin(0.15) ;
        cpull->DrawClonePad();
        canvTot.Print((workspacedir+"mcsigfit_NOTMAIN_moreinfo_"+type+".pdf").c_str());
        canvTot.Print((workspacedir+"mcsigfit_NOTMAIN_moreinfo_"+type+".root").c_str());




	TCanvas* canv4 = new TCanvas("mBplus_Corrected_Massattempt5","mBplus_Corrected_Massattempt5",800,800) ;
	canv4->Divide(2,2) ;
	canv4->cd(1) ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.1) ; frame8->Draw() ;
	canv4->cd(2) ; gPad->SetLeftMargin(0.15) ; frame9->GetYaxis()->SetTitleOffset(1.1) ; frame9->Draw() ;
	canv4->cd(3) ; gPad->SetLeftMargin(0.15) ; frame10->GetYaxis()->SetTitleOffset(1.1) ; frame10->Draw() ;
	canv4->cd(4) ; gPad->SetLeftMargin(0.15) ; frameun->GetYaxis()->SetTitleOffset(1.1) ; frameun->Draw() ;
	canv4->SaveAs((workspacedir+"mcsigfit_NOTMAIN.pdf").c_str());



	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	//
	string namews8="signal";
	TFile wrkspc8((workspacedir+"myworkspace_"+namews8+".root").c_str(),"RECREATE"); 
	w8->import(Bplus_Corrected_Mass);
	w8->import(weightnamevar);
	w8->import(Bplus_corMassERR);
	w8->import(dr);
	w8->import(blah);

	cout<<"Signal workspace"<<endl;
	w8->Print(); 
	w8->Write();   
	wrkspc8.Write();
	delete canv4;


	return(myresults);
}



vector<double> FitAndSplotB23MuNuDataForTraining::fitpartrecocomponent(string type)    
{      


        cout<<"Starting Part Reco Fit"<<endl;

        TFile* fpr = new TFile((partrecodir+"/"+partrecofilename+type+".root").c_str());
	TTree* treez = (TTree*)fpr->Get("DecayTree");

        double num=92.54;
        RooRealVar pr_val("pr_val","pr_val",numberofpartreco);
        RooRealVar pr_error("pr_error","pr_error",numberofpartreco_error);
       
     
        RooRealVar npartreco(("npartreco"),("npartreco"),numberofpartreco,(numberofpartreco-(5.0*numberofpartreco_error)),(numberofpartreco+(5.0*numberofpartreco_error)));
        RooGaussian npartreco_con("npartreco_con","npartreco_con",npartreco,pr_val,pr_error); //Create Constraint for number of partreco candidates


	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
	RooDataSet dz("dz","dz",RooArgSet(Bplus_Corrected_Mass),Import(*treez));
	dz.Print();
	Bplus_Corrected_Mass.setRange("partreco",4000,5100);


	RooRealVar cbmeanrpr(("cbmeanrpr"),("cbmeanr"+type).c_str(),3942.0);
	RooRealVar cbsigmarpr(("cbsigmarpr"),("cbsigmar"+type).c_str(),350,700);//,0.1,50) ;
	RooRealVar nrpr(("nrpr"),"",1.0);
	RooRealVar alpharpr(("alpharpr"),"",3.9);
	RooCBShape cballrpr(("cballrpr"), "crystal ball", Bplus_Corrected_Mass, cbmeanrpr, cbsigmarpr, alpharpr, nrpr);
	RooRealVar fracpr(("fracpr"),"frac of events in cb 1",0.436);

	RooRealVar cbmeanrpr2(("cbmeanrpr2"),"cbmeanr",3188);
	RooRealVar cbsigmarpr2(("cbsigmarpr2"),"cbsigmar",350,700);//,0.1,50) ;
	RooRealVar nrpr2(("nrpr2"),"",5.0);
	RooRealVar alpharpr2(("alpharpr2"),"",0.258);
	RooCBShape cballrpr2(("cballrpr2"), "crystal ball", Bplus_Corrected_Mass, cbmeanrpr2, cbsigmarpr2, alpharpr2, nrpr2);

	RooAddPdf newpartreco(("newpartreco"),"",RooArgList(cballrpr,cballrpr2),RooArgList(fracpr));          

	RooPlot* framepartreco1 = Bplus_Corrected_Mass.frame(Title("PartReco,two CB with not common mean")) ;
	dz.plotOn(framepartreco1);
	newpartreco.fitTo(dz,RooFit::Range("partreco"));
	newpartreco.paramOn(framepartreco1);
	newpartreco.plotOn(framepartreco1);
	newpartreco.plotOn(framepartreco1, Components(cballrpr), LineColor(kGreen));
	newpartreco.plotOn(framepartreco1, Components(cballrpr2), LineColor(kRed));
	newpartreco.getParameters(Bplus_Corrected_Mass)->Print("s");

        TCanvas* canvlog = new TCanvas("pimumu","pimumu",600,600) ;
        framepartreco1->Draw();



        TCanvas canvTot("canvTot", "canvTot", 600, 600);
        canvTot.Divide(1,2);
        canvTot.cd(1);
        gPad->SetPad(0.005, 0.205, 0.995, 0.995);
        canvlog->DrawClonePad();
        delete canvlog;


        savePullPlot(*framepartreco1, workspacedir+"pullPlot_partreco.root");
        TFile fpull((workspacedir+"pullPlot_partreco.root").c_str());
        TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");



        canvTot.cd(2);
        gPad->SetPad(0.005, 0.005, 0.995, 0.2);
        gPad->SetLeftMargin(0.15) ;
        cpull->DrawClonePad();
        canvTot.Print((workspacedir+"partrecofit_NOTMAIN_moreinfo_"+type+".pdf").c_str());
        canvTot.Print((workspacedir+"partrecofit_NOTMAIN_moreinfo_"+type+".root").c_str());


        cbsigmarpr.setConstant();
        cbsigmarpr2.setConstant();


	vector<double> params;

	cout<<"HAVE LOOK AT CONVERGENCE"<<endl;
	params.push_back(cbmeanrpr.getVal());
	params.push_back(cbsigmarpr.getVal());
	params.push_back(nrpr.getVal());
	params.push_back(alpharpr.getVal());
	params.push_back(fracpr.getVal());
	params.push_back(cbmeanrpr2.getVal());
	params.push_back(cbsigmarpr2.getVal());
	params.push_back(nrpr2.getVal());
	params.push_back(alpharpr2.getVal());

	TCanvas* canvibou2 = new TCanvas("partreco","partreco",800,800) ;
	gPad->SetLeftMargin(0.15) ; framepartreco1->GetYaxis()->SetTitleOffset(1.1) ; framepartreco1->GetXaxis()->SetTitle("Corrected Mass") ;  framepartreco1->Draw() ;
	canvibou2->SaveAs((workspacedir+"partrecofit_NOTMAIN.pdf").c_str());
	delete canvibou2;

	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	string namews8="partreco";
	TFile wrkspc8((workspacedir+"myworkspace_"+namews8+".root").c_str(),"RECREATE");  
	w8->import(Bplus_Corrected_Mass);
	w8->import(dz);
	w8->import(newpartreco);
        w8->import(npartreco);
        w8->import(npartreco_con);

	cout<<"PartReco workspace"<<endl;
	w8->Print(); 
	w8->Write();   
	wrkspc8.Write();
	fpr->Close();
	return(params);
}

//vector<double> FitAndSplotB23MuNuDataForTraining::fitmisidcomponent(string type)
//{
//
//        cout<<"Start misid fit"<<endl;
//
//	TFile* f = new TFile((misiddir+"/"+kaonfilename+type+".root").c_str());
//	TTree* treek = (TTree*)f->Get("DecayTree");
//
//	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
//	Bplus_Corrected_Mass.setRange("sideband",4000,6000);
//	//		  TTree* treek =  gettreemisidkaon(kaonsamplename, cut);
//
//	//  RooRealVar p("p","p",4000,7000);
//	RooRealVar crossfeedweight("crossfeedweight","crossfeedweight", 0.0 ,1.0);
//	RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
//	RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treek), WeightVar("crossfeedweight"));//, Import(*treew));
//	dk.Print();
//	dkw.Print();
//	Bplus_Corrected_Mass.setBins(60);
//
//	dk.Print("v");
//	dkw.Print("v");
//	cout << dk.weight() << endl;
//	cout << dkw.weight() << endl; 
//	const RooArgSet* row1 = dkw.get(1);
//	row1->Print("v") ;
//	const RooArgSet* row0 = dkw.get(0);
//	row0->Print("v") ;
//
//	//		  TTree* treep =  gettreemisidpion(pionsamplename, cut);
//	TFile* s = new TFile((misiddir+"/"+pionfilename+type+".root").c_str());
//	TTree* treep = (TTree*)s->Get("DecayTree");
//
//
//
//	RooDataSet dp("dp","dp",RooArgSet(Bplus_Corrected_Mass),Import(*treep));
//	RooDataSet dpw("dpw","dpw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treep), WeightVar("crossfeedweight"));//, Import(*treew));
//	dp.Print();
//	dpw.Print();
//
//	dp.Print("v");
//	dpw.Print("v");
//	cout << dp.weight() << endl;
//	cout << dpw.weight() << endl; 
//	const RooArgSet* row3 = dpw.get(3);
//	row3->Print("v") ;
//	const RooArgSet* row4 = dpw.get(4);
//	row4->Print("v") ;
//
//	TFile* s3 = new TFile((misiddir+"/"+protonfilename+type+".root").c_str());
//	TTree* trees3 = (TTree*)s3->Get("DecayTree");
//	RooRealVar misidoverid("misidoverid","misidoverid", 0.0 ,1.0);
//
//	RooDataSet ds3("ds3","ds3",RooArgSet(Bplus_Corrected_Mass),Import(*trees3));
//	RooDataSet ds3w("ds3w","ds3w", RooArgSet(Bplus_Corrected_Mass,misidoverid), Import(*trees3), WeightVar("misidoverid"));//, Import(*treew));
//	ds3.Print();
//	ds3w.Print();
//
//	ds3.Print("v");
//	ds3w.Print("v");
//	cout << ds3.weight() << endl;
//	cout << ds3w.weight() << endl; 
//	const RooArgSet* rows3 = ds3w.get(3);
//	rows3->Print("v") ;
//	const RooArgSet* rows4 = ds3w.get(4);
//	rows4->Print("v") ;
//
//	RooPlot* frame11 = Bplus_Corrected_Mass.frame(Title("MisIDShapeKaon")) ;
//	RooPlot* frame12 = Bplus_Corrected_Mass.frame(Title("MisIDShapeNormalizedKaon")) ;
//	dk.plotOn(frame11);
//	dkw.plotOn(frame11,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
//	dkw.plotOn(frame12,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
//	double kaonmisid;
//	kaonmisid =dkw.sumEntries();
//	TPaveLabel *t3 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",kaonmisid),"brNDC");
//	frame12->addObject(t3);
//
//
//
//	RooPlot* frame13 = Bplus_Corrected_Mass.frame(Title("MisIDShapePion")) ;
//	RooPlot* frame14 = Bplus_Corrected_Mass.frame(Title("MisIDShapeNormalizedPion")) ;
//	dp.plotOn(frame13);
//	dpw.plotOn(frame13,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
//	dpw.plotOn(frame14,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
//	double pionmisid;
//	pionmisid = dpw.sumEntries();         
//	TPaveLabel *t4 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",pionmisid),"brNDC");
//	frame14->addObject(t4);
//
//
//
//	RooPlot* frameproton1 = Bplus_Corrected_Mass.frame(Title("MisIDShapeProton")) ;
//	RooPlot* frameproton2 = Bplus_Corrected_Mass.frame(Title("MisIDShapeNormalizedProton")) ;
//	ds3.plotOn(frameproton1);
//	ds3w.plotOn(frameproton1,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
//	ds3w.plotOn(frameproton2,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
//	double protonmisid;
//	protonmisid =ds3w.sumEntries();
//	TPaveLabel *tp = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",protonmisid),"brNDC");
//	frameproton2->addObject(tp);
//
//
//
//	TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,800) ;
//	canv5->Divide(3,3) ;
//	canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.1) ; frame11->GetXaxis()->SetTitle("Corrected Mass") ;  frame11->Draw() ;
//	canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.1) ; frame12->GetXaxis()->SetTitle("Corrected Mass") ; frame12->Draw() ;
//	canv5->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13->GetYaxis()->SetTitleOffset(1.1) ; frame13->GetXaxis()->SetTitle("Corrected Mass") ;  frame13->Draw() ;
//	canv5->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14->GetYaxis()->SetTitleOffset(1.1) ; frame14->GetXaxis()->SetTitle("Corrected Mass") ; frame14->Draw() ;
//	canv5->cd(5) ; gPad->SetLeftMargin(0.15) ; frameproton1->GetYaxis()->SetTitleOffset(1.1) ; frameproton1->GetXaxis()->SetTitle("Corrected Mass") ; frameproton1->Draw() ;
//	canv5->cd(6) ; gPad->SetLeftMargin(0.15) ; frameproton2->GetYaxis()->SetTitleOffset(1.1) ; frameproton2->GetXaxis()->SetTitle("Corrected Mass") ; frameproton2->Draw() ;
//	canv5->SaveAs((workspacedir+"Misid_Components_NOTMAIN.pdf").c_str());
//
//	delete canv5;
//
//
//
//	//------Adding two datasets-------------------------//  
//	dpw.append(dkw);
//	dpw.append(ds3w);
//
//
//	dpw.Print("v");
//	dpw.Print();
//	cout<< "Sum of entries for kaon and pion:" <<dpw.sumEntries()<<endl;
//	Bool_t klone;
//	klone = dpw.isWeighted();
//	if (klone==true)
//	{
//		cout<<"My dataset is weighted!" << endl; 
//	}
//	const RooArgSet* row5 = dpw.get(5);
//	cout<<"This is 5th row weight: "<<endl;
//	row5->Print("v");
//	//cout<< "Sum of entries for kaon and pion:" <<dpw.sumEntries()<<endl;
//	double misid;
//        
//        double sumofrangelow;
//        double sumofrangehigh;
//
//        double norm_low;
//        double norm_high;
//        
//        sumofrangelow = dpw.sumEntries("(Bplus_Corrected_Mass < 4500)");
//        sumofrangehigh = dpw.sumEntries("(Bplus_Corrected_Mass > 5500)");
//       
//	misid = dpw.sumEntries();           
//        norm_low = sumofrangelow/misid;
//        norm_high = sumofrangehigh/misid;
//
//
//        cout<<"Fractions in low region: "<<norm_low<<endl;
//        cout<<"Fraction in high region: "<<norm_high<<endl;
//
//        double fullmisid;
//        fullmisid=100.0*misid;
//        RooRealVar nmisid(("nmisid"),"number of misid events",fullmisid);
//        RooRealVar frac_low(("frac_low"),"number of misid events",norm_low);
//        RooRealVar frac_high(("frac_high"),"number of misid events",norm_high);
//
//	cout << dpw.weight() << endl;
//	RooPlot* misidtotal = Bplus_Corrected_Mass.frame(Title("MISIDTOTAL")) ;
//	RooPlot* misidtotal2 = Bplus_Corrected_Mass.frame(Title("MISIDtotal2")) ;
//
//	dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
//	dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));
//
//	TPaveLabel *t2 = new TPaveLabel(0.4,0.6,0.9,0.8, Form("TotMisID = %f",misid),"brNDC");
//	misidtotal->addObject(t2);
//
//
//	TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
//	canvtot->Divide(2,2) ;
//	canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.1) ; misidtotal->Draw() ;
//	canvtot->SaveAs((workspacedir+"totalmisid_NOTMAIN.pdf").c_str());
//
//	delete canvtot;
//	//		  canvshift->cd(i+1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.1) ; misidtotal->GetXaxis()->SetTitle("Corrected Mass") ;  misidtotal->Draw() ;      
//
//	//        }
//
//	// canvshift->SaveAs("misidshiftafter2bdts/triggerallvarnewSSmisidsamples.pdf");          
//
//	//---- Make Binned Histogram from unbinned and fit with 2 crystal balls--------//
//	RooDataHist* binnedData = dpw.binnedClone() ; 
//	binnedData->Print("v");
//
//	cout<< "Integral over histogram:" << binnedData->sum(kTRUE)<<endl; 
//	cout<< "Sum of weight:" << binnedData->sum(kFALSE)<<endl;
//	cout<< "Sum of entries:" << binnedData->sumEntries()<<endl;
//	cout<< "Num of bins:" << binnedData->numEntries()<<endl;  
//
//	RooPlot* ibou = Bplus_Corrected_Mass.frame(Title("Binned histogram")) ;
//	binnedData->plotOn(ibou,DataError(RooAbsData::SumW2)); 
//
//	vector<double> params;
//
//
//
//
//	RooRealVar sig2(("sig2"),"frac of events in sig2",544.0,450.0,650.0);
//	RooRealVar cbmeanr2(("cbmeanr2"),"cbmeanr", 4058.4 ,4000.0,4200.0);
//	RooRealVar cbsigmar2(("cbsigmar2"),"cbsigmar",400.,300.,800.0);//,0.1,50) ;
//	RooRealVar nr2(("nr2"),"",0.32, 0.01, 5.0);
//	RooRealVar alphar2(("alphar2"),"",0.6, 0.1, 10.0);
//	RooCBShape twocbs(("twocbs"), "crystal ball", Bplus_Corrected_Mass, cbmeanr2, cbsigmar2, alphar2, nr2);
//
//
//	twocbs.fitTo(*binnedData,RooFit::Range("sideband"));
//	twocbs.plotOn(ibou) ;
//
//	cout<<"HAVE LOOK AT CONVERGENCE"<<endl;
//	params.push_back(cbmeanr2.getVal());
//	params.push_back(cbsigmar2.getVal());
//	params.push_back(nr2.getVal());
//	params.push_back(alphar2.getVal());
//
//        sig2.setConstant();
//        cbmeanr2.setConstant();
//        cbsigmar2.setConstant();
//        nr2.setConstant();
//        alphar2.setConstant();
//        
//     
//        Bplus_Corrected_Mass.setRange("low",4000,4500);
//        Bplus_Corrected_Mass.setRange("high",5500,7000);
//        Bplus_Corrected_Mass.setRange("full",4000,7000);
//        RooAbsReal* integral_low = twocbs.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("low"));
//
//        double int_low = integral_low->getVal(); 
//
//        RooAbsReal* integral_high = twocbs.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("high"));
//        
//        double int_high = integral_high->getVal();
//   
//        RooAbsReal* integral_full = twocbs.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("full"));
//
//        double int_full = integral_full->getVal();
//
//        cout<<"Integral in low: " << int_low <<endl;
//        cout<<"Integral in high: " << int_high<<endl;
//        cout<<"Integral in full: " << int_full<<endl;
//
//	RooPlot* ibou2 = Bplus_Corrected_Mass.frame(Title("Binned histogram")) ;
//	binnedData->plotOn(ibou2,DataError(RooAbsData::SumW2));
//	twocbs.plotOn(ibou2) ;
//	twocbs.paramOn(ibou2);
//
//	RooHist* hresidcom = ibou->residHist();
//	RooHist* hpullcom = ibou->pullHist();
//	RooPlot* framecom1 = Bplus_Corrected_Mass.frame(Title("Residual Distribution"));
//	framecom1->addPlotable(hresidcom,"P");
//	RooPlot* framecom2 = Bplus_Corrected_Mass.frame(Title("Pull Distribution")) ;
//	framecom2->addPlotable(hpullcom,"P");
//
//
//	TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
//	canvibou->Divide(2,2) ;
//	canvibou->cd(1); gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.1) ; ibou->GetXaxis()->SetTitle("Corrected Mass") ;  ibou->Draw() ;
//	canvibou->cd(2); gPad->SetLeftMargin(0.15) ; ibou2->GetYaxis()->SetTitleOffset(1.1) ; ibou2->GetXaxis()->SetTitle("Corrected Mass") ;  ibou2->Draw() ;
//	canvibou->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom1->GetYaxis()->SetTitleOffset(1.1) ; framecom1->GetXaxis()->SetTitle("Corrected Mass") ; framecom1->Draw() ;
//	canvibou->cd(4) ; gPad->SetLeftMargin(0.15) ; framecom2->GetYaxis()->SetTitleOffset(1.1) ; framecom2->GetXaxis()->SetTitle("Corrected Mass") ; framecom2->Draw() ;
//	canvibou->SaveAs((workspacedir+"totalmisidfit_NOTMAIN.pdf").c_str());         
//
//	delete canvibou; 
// 
//       // ofstream out((type+"_misid_FitResults.txt").c_str());
//       // saveFitInfo(out, ibou2, 0, twocbs);
//
//
//
//       // TCanvas* canvpara = new TCanvas("seepara","seepara",800,800);
//       // canvpara->Divide(2,1);
//       // delete canvpara; 
//
//
//
//        RooWorkspace *w8 = new RooWorkspace("w","workspace");
//        string namews8="misid";
//        TFile wrkspc8((workspacedir+"myworkspace_"+namews8+".root").c_str(),"RECREATE");
//        w8->import(Bplus_Corrected_Mass);
//        w8->import(dpw);
//        w8->import(twocbs);
//        w8->import(nmisid);
//        w8->import(frac_low);
//        w8->import(frac_high);
//        cout<<"Misid workspace"<<endl;
//        w8->Print();
//        w8->Write();
//        wrkspc8.Write();
//
//
//
//
//
//	f->Close();
//	s->Close();
//	s3->Close();
//
//	return(params);
//}



void FitAndSplotB23MuNuDataForTraining::prepareWorkspaceForSimultaneousFit(string type, string year ,string PIDcut)
{
	TFile f( (datadir+"/"+tuplename+".root").c_str());
	TTree* t = (TTree*)f.Get(treename.c_str());

	if(!t)
	{
		cerr<<"ERROR: in function prepareWorkspace, no tree "<<treename<<" found in "<<datadir<<"/"<<tuplename<<endl;
		return;
	}

	t->SetBranchStatus("*", 0);
	t->SetBranchStatus("Bplus_Corrected_Mass", 1);

	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass", "Bplus_Corrected_Mass",Bplus_Corrected_Mass_min,Bplus_Corrected_Mass_max);
	RooArgSet vars(Bplus_Corrected_Mass);


	cout<<"BLABLA: "<<"Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)<<endl;

	RooDataSet data(("data"), ("data"), vars, Import(*t), Cut( ("Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)).c_str() ) );

	RooWorkspace workspaceData("workspaceData", "workspaceData"); 

	workspaceData.import(Bplus_Corrected_Mass);  
	workspaceData.import(data);

	//workspaceData.writeToFile(workspaceFileName.c_str());

	TFile fws((workspacedir+workspaceDataFile+".root").c_str(), "RECREATE");
	workspaceData.Write("",TObject::kOverwrite );

	cout<<"Workspace containing data ready:"<<endl;
        cout<<"In "<<(workspacedir+workspaceDataFile+".root").c_str()<<endl;
	workspaceData.Print();


	f.Close();
	fws.Close();
}

void FitAndSplotB23MuNuDataForTraining::calculateFOM_chi2(string type, string pidcut_Run1, string pidcut_Run2)
{
	cout<<"Calculate the figure of merit from the fit: "<<endl;
	TFile fw((clsdir+"fitresults_forCLs.root").c_str());

	RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
	if(!workspaceFit)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
		return;
	}

	RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
	RooDataSet* data = (RooDataSet*)workspaceFit->data(("data"));
	//RooAbsPdf* model_total = workspaceFit->pdf(("normsigpdf"));
        RooAbsPdf* model_exp = workspaceFit->pdf(("newexpoun"));
        RooAbsPdf* model_sig = workspaceFit->pdf(("blah"));
        RooAbsPdf* model_pr = workspaceFit->pdf(("newpartreco")); 
        RooAbsPdf* model_misid = workspaceFit->pdf(("misidModel"));
        RooRealVar* number_exp = workspaceFit->var(("nexp"));
        RooAbsReal* number_sig = workspaceFit->function(("nsigform"));
        RooRealVar* number_pr = workspaceFit->var(("npartreco"));
        RooRealVar* number_misid = workspaceFit->var(("misid_scaled"));


        //RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
        Bplus_Corrected_Mass->setRange("new",4000,7000);
	Bplus_Corrected_Mass->setRange("high",5501,7000);
	Bplus_Corrected_Mass->setRange("low",4000,4499);
        Bplus_Corrected_Mass->setRange("fit",4500,5500);


	if(!data || !model_exp || !model_sig || !model_pr || !model_misid || !number_exp )//|| !number_sig || !number_pr || !number_misid)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
//		cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<endl;
		return;
	}

//	Bplus_Corrected_Mass.setBins(60);

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

        string tags=(pidcut_Run1+" "+pidcut_Run2).c_str();

	ofstream out;
	out.open(("../FOM/FOM_chi2.txt"));
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
void FitAndSplotB23MuNuDataForTraining::calculateFOM(string type)
{
	cout<<"Calculate the figure of merit from the fit: "<<endl;
	TFile fw((clsdir+"fitresults_forCLs.root").c_str());

	RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
	if(!workspaceFit)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
		return;
	}

	RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
	RooDataSet* data = (RooDataSet*)workspaceFit->data(("data"));
	//RooAbsPdf* model_total = workspaceFit->pdf(("normsigpdf"));
        RooAbsPdf* model_exp = workspaceFit->pdf(("newexpoun"));
        RooAbsPdf* model_sig = workspaceFit->pdf(("blah"));
        RooAbsPdf* model_pr = workspaceFit->pdf(("newpartreco")); 
        RooAbsPdf* model_misid = workspaceFit->pdf(("twocbs"));
        RooRealVar* number_exp = workspaceFit->var(("nexp"));
        RooAbsReal* number_sig = workspaceFit->function(("nsigform"));
        RooRealVar* number_pr = workspaceFit->var(("npartreco"));
        RooRealVar* number_misid = workspaceFit->var(("nmisid"));


        //RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
        Bplus_Corrected_Mass->setRange("new",4000,7000);
	Bplus_Corrected_Mass->setRange("high",5501,7000);
	Bplus_Corrected_Mass->setRange("low",4000,4499);
        Bplus_Corrected_Mass->setRange("fit",4500,5500);


	if(!data || !model_exp || !model_sig || !model_pr || !model_misid || !number_exp )//|| !number_sig || !number_pr || !number_misid)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
//		cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<endl;
		return;
	}

//	Bplus_Corrected_Mass.setBins(60);

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

        string tags="NNmumorethan3";

	ofstream out;
	out.open(("../FOM/FOM.txt"));
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

void FitAndSplotB23MuNuDataForTraining::simfitseparateandsavesig_chi2fit(string year, string PIDcut)
{

          TFile* f_low = new TFile((workspacedir+"myworkspace_signal.root").c_str());
          RooWorkspace* ws_low = (RooWorkspace*)f_low->Get("w");
	  ws_low->Print();
          RooAbsPdf* pdf_sig_low = ws_low->pdf(("blah"));


          TFile* pr_low = new TFile((workspacedir+"myworkspace_partreco.root").c_str());
          RooWorkspace* wspr_low = (RooWorkspace*)pr_low->Get("w");
          RooAbsPdf* pdf_pr_low = wspr_low->pdf(("newpartreco"));
          RooAbsPdf* npr_low_con = wspr_low->pdf(("npartreco_con")); // external constraint
          RooRealVar* npr_low = wspr_low->var(("npartreco"));


          TFile* misid_low = new TFile((workspacedir+"myworkspace_misid.root").c_str());
          RooWorkspace* wsmisid_low = (RooWorkspace*)misid_low->Get("w");
          RooAbsPdf* pdf_misid_low = wsmisid_low->pdf(("misidModel"));
          RooRealVar* nmisid_low = wsmisid_low->var(("misid_scaled"));


          wsmisid_low->Print();
          cout<<"High misid workspace: "<<endl;

  //        double sesrun1(0);
      //    double ses2015(0);
    //      double ses2016(0);
    //      double ses(0);

     //     sesrun1=9.34e-10;
          //ses2015=1.16343e-8;
       //   ses2016=1.878e-9;
          

         // ses=sesrun1+ses2015;
   
        RooRealVar pr_val("pr_val","pr_val",numberofpartreco);
        RooRealVar pr_error("pr_error","pr_error",numberofpartreco_error);
       
     
        RooRealVar npartreco(("npartreco"),("npartreco"),numberofpartreco,(numberofpartreco-(5.0*numberofpartreco_error)),(numberofpartreco+(5.0*numberofpartreco_error)));
        RooGaussian npartreco_con("npartreco_con","npartreco_con",npartreco,pr_val,pr_error); //Create Constraint for number of partreco candidates

	  RooRealVar BR("BR","branching fraction",1.0e-8);

  //        double sesrun1;
  //        double sesrun1err;

  //        sesrun1=double(returnVar((sesinfo+"/info_SES_"+year+"_"+PIDcut+".root").c_str(), ("Info_"+year).c_str(), "sensitivity"));
  //        sesrun1err=double(returnVar((sesinfo+"/info_SES_"+year+"_"+PIDcut+".root").c_str(), ("Info_"+year).c_str(), "sensitivity_err"));

          RooRealVar ses_val("ses_val","ses_val",sesrun1);
          RooRealVar ses_err("ses_err","ses_err",sesrun1err);
	  RooRealVar ses_low("ses","Single event sensitivity",sesrun1,double(sesrun1-(3.0*sesrun1err)),double(sesrun1+(3.0*sesrun1err)));
	  RooGaussian ses_low_con("ses_con","ses_con",ses_low,ses_val,ses_err);          

        //  RooRealVar ses_low_2015("ses_2015","Single event sensitivity",ses2015,double(ses2015-1.39e-9),double(ses2015+1.39e-9));

  //        double ses2016;
  //        double sesrun1err;

//         RooRealVar ses_val_2016("ses_val_2016","ses_val_2016",ses2016);
//         RooRealVar ses_err_2016("ses_err_2016","ses_err_2016",ses2016err);
//         RooRealVar ses_low_2016("ses_2016","ses_2016",ses2016,double(ses2016-(3.0*ses2016err)),double(ses2016+(3.0*ses2016err)));
//         RooGaussian ses_low_2016_con("ses_2016_con","ses_2016_con",ses_low_2016,ses_val_2016,ses_err_2016);          


//          RooRealVar ses_low_2016("ses_2016","Single event sensitivity",ses2016,double(ses2016-(5.0*ses2016err)),double(ses2016+(5.0*ses2016err)));         




          RooRealVar nexp_low("nexp","n explow",0.1,2000);

//	  RooFormulaVar nsigform_low("nsigform","nsigfromformula","(@2/@0)+(@2/@1)",RooArgList(ses_low,ses_low_2016,BR));
	  RooFormulaVar nsigform_low("nsigform","nsigfromformula","(@1/@0)",RooArgList(ses_low,BR));

          cout<<"This is nsigform_low: "<<nsigform_low.getVal()<< endl;


          RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
          Bplus_Corrected_Mass.setRange("high",5501,7000);
          Bplus_Corrected_Mass.setRange("low",4000,4499);
          Bplus_Corrected_Mass.setRange("new",4000,7000);


//	  RooRealVar newexpocon("newexpocon","newexpocon",-0.3,0.3);
//	  RooExponential newexpoun("newexpoun", "exponential",Bplus_Corrected_Mass,newexpocon);

          RooRealVar newexpocon_low(("newexpocon"),"newexpocon_low",-0.3,0.3);
          RooExponential newexpoun_low(("newexpoun"), "exponential_low",Bplus_Corrected_Mass,newexpocon_low);




          cout<<"WOOHOO"<<endl;

	  // Display fit parameters.
   	  RooAddPdf normsigpdf_low(("normsigpdf"),"extended sum pdf",RooArgList(*pdf_sig_low,newexpoun_low,*pdf_misid_low,*pdf_pr_low), RooArgList(nsigform_low,nexp_low,*nmisid_low,*npr_low));
	  RooAddPdf normpdf_low(("normpdf"),"extended sum pdf",RooArgList(*pdf_misid_low,*pdf_pr_low,newexpoun_low), RooArgList(*nmisid_low,*npr_low,nexp_low)); 

          normpdf_low.Print("t");
  

        //---------LOW Data-- 


        TFile flow((workspacedir+workspaceDataFile+".root").c_str());

	RooWorkspace* workspaceData_low = (RooWorkspace*)flow.Get("workspaceData");

	if(!workspaceData_low)
	{
		cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<endl;
		return;
	}

	RooRealVar* Bplus_Corrected_Mass_low = workspaceData_low->var("Bplus_Corrected_Mass");
	RooDataSet* data_low = (RooDataSet*)workspaceData_low->data("data");

	if(!data_low || !Bplus_Corrected_Mass_low)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining, error downloading stuff from workspace"<<endl;
		return;
	}

        Int_t numofentr(0);
        numofentr=data_low->numEntries();
        cout<<"Number of entries of final data: "<<numofentr<<endl;
        ofstream newt;
        newt.open((plotdir+"NumOfEntries.txt").c_str());
        newt<<"Number of entries of final data: "<<numofentr<<endl;
        newt.close();



	// P e r f o r m   a   s i m u l t a n e o u s   f i t
	// ---------------------------------------------------

	// Perform simultaneous fit of model to data and model_ctl to data_ctl
        normpdf_low.fitTo(*data_low,RooFit::Range("low,high"),Save(kTRUE),Extended(kTRUE), ExternalConstraints(*npr_low_con));

//	newexpocon_low.setConstant();
//	nexp_low.setConstant();

        RooArgSet* params = normpdf_low.getParameters(Bplus_Corrected_Mass);
        params->writeToFile((plotdir+"SimultaneousFitResults.txt").c_str());

       


	// P l o t   m o d e l   s l i c e s   o n   d a t a    s l i c e s 
	// ----------------------------------------------------------------

	// Make a frame for the physics sample
	RooPlot* frame1 = Bplus_Corrected_Mass.frame(Bins(60),Title("No Fractional Corrected Mass Error")) ;

	//normpdf_low.paramOn(frame1, Format("NELU", AutoPrecision(2)), Layout(0.4, 0.4, 0.4));
        data_low->plotOn(frame1, MarkerSize(0.9), LineColor(kBlack),RooFit::Name("data2"),RooFit::Range("low,high"));
	normpdf_low.plotOn(frame1, Components("newexpoun"), RooFit::Range("low"),RooFit::NormRange("low") ,LineColor(kRed));
	normpdf_low.plotOn(frame1, Components("misidModel"), RooFit::Range("low"),RooFit::NormRange("low") ,LineColor(kCyan));
	normpdf_low.plotOn(frame1, Components("newpartreco"), RooFit::Range("low"),RooFit::NormRange("low"),LineColor(kMagenta));
        normpdf_low.plotOn(frame1, Components("newexpoun"), RooFit::Range("high"),RooFit::NormRange("high") ,LineColor(kRed));
        normpdf_low.plotOn(frame1, Components("misidModel"), RooFit::Range("high"),RooFit::NormRange("high") ,LineColor(kCyan));
        normpdf_low.plotOn(frame1, Components("newpartreco"), RooFit::Range("high"),RooFit::NormRange("high"),LineColor(kMagenta));
        normpdf_low.plotOn(frame1, LineColor(kBlue),RooFit::Range("high"),RooFit::NormRange("high"));
	normpdf_low.plotOn(frame1, LineColor(kBlue),RooFit::Range("low"),RooFit::NormRange("low"));

	// Plot all data tagged as physics sample

       // simPdf.plotOn(frame1,Slice(sample,"LowFCME"),RooFit::Range("low,high"),RooFit::NormRange("new"), LineColor(kGreen));


	RooPlot* frame100 = Bplus_Corrected_Mass.frame(Bins(100),Title("No Fractional Corrected Mass Error 100 bins")) ;

	//normpdf_low.paramOn(frame100, Format("NELU", AutoPrecision(2)), Layout(0.4, 0.4, 0.4));
        data_low->plotOn(frame100, MarkerSize(0.9), LineColor(kBlack),RooFit::Name("data2"),RooFit::Range("low,high"));
	normpdf_low.plotOn(frame100, Components("newexpoun"), RooFit::Range("low"),RooFit::NormRange("low") ,LineColor(kRed));
	normpdf_low.plotOn(frame100, Components("misidModel"), RooFit::Range("low"),RooFit::NormRange("low") ,LineColor(kCyan));
	normpdf_low.plotOn(frame100, Components("newpartreco"), RooFit::Range("low"),RooFit::NormRange("low"),LineColor(kMagenta));
        normpdf_low.plotOn(frame100, Components("newexpoun"), RooFit::Range("high"),RooFit::NormRange("high") ,LineColor(kRed));
        normpdf_low.plotOn(frame100, Components("misidModel"), RooFit::Range("high"),RooFit::NormRange("high") ,LineColor(kCyan));
        normpdf_low.plotOn(frame100, Components("newpartreco"), RooFit::Range("high"),RooFit::NormRange("high"),LineColor(kMagenta));
        normpdf_low.plotOn(frame100, LineColor(kBlue),RooFit::Range("high"),RooFit::NormRange("high"));
	normpdf_low.plotOn(frame100, LineColor(kBlue),RooFit::Range("low"),RooFit::NormRange("low"));

	TCanvas* c = new TCanvas("rf501_simultaneouspdf","rf403_simultaneouspdf",800,400) ;
	c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.1) ; frame1->Draw() ;
        c->SaveAs((plotdir+"FitResult_NOFCME.pdf").c_str());

	TCanvas* c_100 = new TCanvas("f","rf",800,400) ;
	c_100->cd(1) ; gPad->SetLeftMargin(0.15) ; frame100->GetYaxis()->SetTitleOffset(1.1) ; frame100->Draw() ;
        c_100->SaveAs((plotdir+"FitResult_NOFCME_100bins.pdf").c_str());

	TCanvas* c_float = new TCanvas("float","float",800,400) ;
        normpdf_low.paramOn(frame1, Format("NELU"), Layout(0.5, 0.5, 0.6));
	c_float->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.1) ; frame1->Draw() ;
        c_float->SaveAs((plotdir+"FitResult_NOFCME_withfloatingvar.pdf").c_str());


        TFile file((clsdir+"fitresults_forCLs.root").c_str(), "RECREATE");

	RooWorkspace workspaceFit("workspaceFit", "workspaceFit");

        workspaceFit.import(Bplus_Corrected_Mass);
	workspaceFit.import(*data_low);
        //workspaceFit.import(combData);
        workspaceFit.import(normpdf_low);
        workspaceFit.import(*npr_low_con);
        workspaceFit.import(ses_low_con);
//        workspaceFit.import(ses_low_2016_con);
        workspaceFit.import(normsigpdf_low,RecycleConflictNodes());
	//workspaceFit.writeToFile(workspaceFileName.c_str());
	workspaceFit.Write("", TObject::kOverwrite);
	//
	cout<<"Workspace for fit has been saved:"<<endl;
	workspaceFit.Print();
	//
	//
	file.Close();

}

//void FitAndSplotB23MuNuDataForTraining::simfitseparateandsavesig()
//{
//
//          TFile* f_low = new TFile((workspacedir+"myworkspace_signal.root").c_str());
//          RooWorkspace* ws_low = (RooWorkspace*)f_low->Get("w");
//	  ws_low->Print();
//          RooAbsPdf* pdf_sig_low = ws_low->pdf(("blah"));
//
//
//          TFile* pr_low = new TFile((workspacedir+"myworkspace_partreco.root").c_str());
//          RooWorkspace* wspr_low = (RooWorkspace*)pr_low->Get("w");
//          RooAbsPdf* pdf_pr_low = wspr_low->pdf(("newpartreco"));
//          RooRealVar* npr_low = wspr_low->var(("npartreco"));
//
//
//          TFile* misid_low = new TFile((workspacedir+"myworkspace_misid.root").c_str());
//          RooWorkspace* wsmisid_low = (RooWorkspace*)misid_low->Get("w");
//          RooAbsPdf* pdf_misid_low = wsmisid_low->pdf(("twocbs"));
//          RooRealVar* nmisid_low = wsmisid_low->var(("nmisid"));
//
//          wsmisid_low->Print();
//          cout<<"High misid workspace: "<<endl;
//
////          double sesrun1(0);
////          double ses2015(0);
////          double ses2016(0);
////          double ses(0);
//
////          sesrun1=9.34e-10;
//          //ses2015=1.16343e-8;
////          ses2016=1.87e-9;
//          
//
//         // ses=sesrun1+ses2015;
//   
//
//	  RooRealVar BR("BR","branching fraction",1.0e-8);
//	  RooRealVar ses_low("ses","Single event sensitivity",sesrun1,double(sesrun1-sesrun1err),double(sesrun1+sesrun1err));
////          RooRealVar ses_low_2015("ses_2015","Single event sensitivity",ses2015,double(ses2015-1.39e-9),double(ses2015+1.39e-9));
//          RooRealVar ses_low_2016("ses_2016","Single event sensitivity",ses2016,double(ses2016-ses2016err),double(ses2016+ses2016err));         
//
//          RooRealVar nexp_low("nexp","nexplow",0.1,2000);
//
//	  RooFormulaVar nsigform_low("nsigform","nsigfromformula","(@2/@0)+(@2/@1)",RooArgList(ses_low,ses_low_2016,BR));
//
//
//
//          RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
//          Bplus_Corrected_Mass.setRange("high",5501,7000);
//          Bplus_Corrected_Mass.setRange("low",4000,4499);
//          Bplus_Corrected_Mass.setRange("new",4000,7000);
//
//
////	  RooRealVar newexpocon("newexpocon","newexpocon",-0.3,0.3);
////	  RooExponential newexpoun("newexpoun", "exponential",Bplus_Corrected_Mass,newexpocon);
//
//          RooRealVar newexpocon_low(("newexpocon"),"newexpocon_low",-0.3,0.3);
//          RooExponential newexpoun_low(("newexpoun"), "exponential_low",Bplus_Corrected_Mass,newexpocon_low);
//
//
//
//
//          cout<<"WOOHOO"<<endl;
//
//	  // Display fit parameters.
//   	  RooAddPdf normsigpdf_low(("normsigpdf"),"extended sum pdf",RooArgList(*pdf_sig_low,newexpoun_low,*pdf_misid_low,*pdf_pr_low), RooArgList(nsigform_low,nexp_low,*nmisid_low,*npr_low));
//	  RooAddPdf normpdf_low(("normpdf"),"extended sum pdf",RooArgList(*pdf_misid_low,*pdf_pr_low,newexpoun_low), RooArgList(*nmisid_low,*npr_low,nexp_low)); 
//
//          normpdf_low.Print("t");
//  
//
//        //---------LOW Data-- 
//
//
//        TFile flow((workspacedir+workspaceDataFile+".root").c_str());
//
//	RooWorkspace* workspaceData_low = (RooWorkspace*)flow.Get("workspaceData");
//
//	if(!workspaceData_low)
//	{
//		cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<endl;
//		return;
//	}
//
//	RooRealVar* Bplus_Corrected_Mass_low = workspaceData_low->var("Bplus_Corrected_Mass");
//	RooDataSet* data_low = (RooDataSet*)workspaceData_low->data("data");
//
//	if(!data_low || !Bplus_Corrected_Mass_low)
//	{
//		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining, error downloading stuff from workspace"<<endl;
//		return;
//	}
//
//        Int_t numofentr(0);
//        numofentr=data_low->numEntries();
//        cout<<"Number of entries of final data: "<<numofentr<<endl;
//        ofstream newt;
//        newt.open((plotdir+"NumOfEntries.txt").c_str());
//        newt<<"Number of entries of final data: "<<numofentr<<endl;
//        newt.close();
//
//
//
//	// P e r f o r m   a   s i m u l t a n e o u s   f i t
//	// ---------------------------------------------------
//
//	// Perform simultaneous fit of model to data and model_ctl to data_ctl
//        normpdf_low.fitTo(*data_low,RooFit::Range("low,high"),Extended(kTRUE),Save(kTRUE));
//
//
//
//
//
//        RooArgSet* params = normpdf_low.getParameters(Bplus_Corrected_Mass);
//        params->writeToFile((plotdir+"SimultaneousFitResults.txt").c_str());
//
//       
//
//
//	// P l o t   m o d e l   s l i c e s   o n   d a t a    s l i c e s 
//	// ----------------------------------------------------------------
//
//	// Make a frame for the physics sample
//	RooPlot* frame1 = Bplus_Corrected_Mass.frame(Bins(60),Title("No Fractional Corrected Mass Error")) ;
//
//	//normpdf_low.paramOn(frame1, Format("NELU", AutoPrecision(2)), Layout(0.4, 0.4, 0.4));
//        data_low->plotOn(frame1, MarkerSize(0.9), LineColor(kBlack),RooFit::Name("data2"),RooFit::Range("low,high"));
//	normpdf_low.plotOn(frame1, Components("newexpoun"), RooFit::Range("low"),RooFit::NormRange("low") ,LineColor(kRed));
//	normpdf_low.plotOn(frame1, Components("twocbs"), RooFit::Range("low"),RooFit::NormRange("low") ,LineColor(kCyan));
//	normpdf_low.plotOn(frame1, Components("newpartreco"), RooFit::Range("low"),RooFit::NormRange("low"),LineColor(kMagenta));
//        normpdf_low.plotOn(frame1, Components("newexpoun"), RooFit::Range("high"),RooFit::NormRange("high") ,LineColor(kRed));
//        normpdf_low.plotOn(frame1, Components("twocbs"), RooFit::Range("high"),RooFit::NormRange("high") ,LineColor(kCyan));
//        normpdf_low.plotOn(frame1, Components("newpartreco"), RooFit::Range("high"),RooFit::NormRange("high"),LineColor(kMagenta));
//        normpdf_low.plotOn(frame1, LineColor(kBlue),RooFit::Range("high"),RooFit::NormRange("high"));
//	normpdf_low.plotOn(frame1, LineColor(kBlue),RooFit::Range("low"),RooFit::NormRange("low"));
//
//	// Plot all data tagged as physics sample
//
//       // simPdf.plotOn(frame1,Slice(sample,"LowFCME"),RooFit::Range("low,high"),RooFit::NormRange("new"), LineColor(kGreen));
//
//
//
//	TCanvas* c = new TCanvas("rf501_simultaneouspdf","rf403_simultaneouspdf",800,400) ;
//	c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.1) ; frame1->Draw() ;
//        c->SaveAs((plotdir+"FitResult_NOFCME.pdf").c_str());
//
//        TFile file((clsdir+"fitresults_forCLs.root").c_str(), "RECREATE");
//
//	RooWorkspace workspaceFit("workspaceFit", "workspaceFit");
//
//
//        workspaceFit.import(Bplus_Corrected_Mass);
//	workspaceFit.import(*data_low);
//        //workspaceFit.import(combData);
//        workspaceFit.import(normpdf_low);
//        workspaceFit.import(normsigpdf_low,RecycleConflictNodes());
//	//workspaceFit.writeToFile(workspaceFileName.c_str());
//	workspaceFit.Write("", TObject::kOverwrite);
//	//
//	cout<<"Workspace for fit has been saved:"<<endl;
//	workspaceFit.Print();
//	//
//	//
//	file.Close();
//
//}
