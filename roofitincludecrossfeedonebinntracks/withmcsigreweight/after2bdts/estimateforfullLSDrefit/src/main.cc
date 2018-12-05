#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TH1.h"
#include "TRandom.h"
#include "RooCBShape.h"
#include "Riostream.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 
#include "RooPlot.h"
#include "RooHist.h"
#include "RooKeysPdf.h"
#include "RooNDKeysPdf.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooFitResult.h"
#include "RooGenericPdf.h"
#include "RooMCStudy.h"
#include "RooChi2MCSModule.h"
#include "TPaveLabel.h"
#include "TLegend.h"
#include "TLatex.h"
#include <vector>
#include <string>
#include "TTreeFormula.h"
#include "TString.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include "MyCB.hpp"
#include "fittingB23munudifferentprobnnmuhyp.hpp"
#include "TPaveText.h"
#include "TROOT.h"
#include "TStyle.h"

using namespace std;
using namespace RooFit ;

int main(int argc, char *argv[]){

        //takes polarity and stripping as arguments
        //--------------------------------------SAMPLES-------------------------------------------------------------------------------------// 

        //kaonsample=("/vols/lhcb/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplesVS2/bin/modifiedandcut"+tags.at(i)+stripping+polarity+"B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic.root").c_str()
       
        //pionsample=("/vols/lhcb/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplesVS2/bin/modifiedandcut"+tags.at(i)+stripping+polarity+"B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root").c_str()
 
        //mcsample=("/vols/lhcb/ss4314/cutonBDTs/MisidBackTonomu1mu3ETAtighterproton/B23MuNuMCallvar_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic.root").c_str()
 
        //partrecosample=("/vols/lhcb/ss4314/cutonBDTs/MisidBackTonomu1mu3ETAtighterproton/B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic.root")

        //combisource=(""/vols/lhcb/ss4314/cutonBDTs/MisidBackTonomu1mu3ETAtighterproton/Data2012and2011_corrm_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic.root"")

        //----------------------------------------------------------------------------------------------------------------------------------//


        gROOT->ProcessLine(".x lhcbSally.C");
	int l;
	l=0;
	if(l==0.0)
	{
	
		//----------------Define MC cuts------------------------------//

		TCanvas* canvshifttotal = new TCanvas("changeofmisidtotal","changeofmisidtotal",800,800) ;
		canvshifttotal->Divide(4,4);


                string stripping=argv[1]; 
                string polarity=argv[2];


		for(int h(14); h<15; h++)
		{


			int indexofcut=h;

			vector<string> muonpidcuts; 


                        //---------------GET MC EFFICIENCIES FROM PIDCALIB-------??
                        string muonideffpath=("/vols/lhcb/ss4314/PIDCalibEfficiencies/ideff/muon/PerfHists_Mu_"+stripping+"_"+polarity+"_P_ETA.root").c_str();
                        string nameofmuonidhist=("PerfHists_Mu_"+stripping+"_"+polarity+"_P_ETA.root").c_str();




			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.6)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.5)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.4)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.25)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.35)_All");


                        //---------------------GET TUPLE TO REWEIGHT----------------------------------------------------------//

			string mcmuonsample="/vols/lhcb/ss4314/cutonBDTs/MisidBackTonomu1mu3ETAtighterproton/B23MuNuMCallvar_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic.root";
			string mcmuonhist="B23MuNuMCallvar_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic.root";

			vector<string> mcname;

			mcname.push_back("Basic cut");
			mcname.push_back("Dllmumore05");
			mcname.push_back("Dllmumore1");
			mcname.push_back("Dllmumore15");
			mcname.push_back("Dllmumore2");
			mcname.push_back("Dllmuminkmore05");
			mcname.push_back("Dllmuminkmore1");
			mcname.push_back("Dllmuminkmore15");
			mcname.push_back("Dllmuminkmore2");
			mcname.push_back("NNmuminuspimorem06");
			mcname.push_back("NNmuminuspimorem05");
			mcname.push_back("NNmuminuspimorem04");
			mcname.push_back("NNmumore02");
			mcname.push_back("NNmumore025");
			mcname.push_back("NNmumore03");
			mcname.push_back("NNmumore035");


                        //------------------AVERAGE EFFICIENCY of the MC SAMPLE FINAL MC EFF-----------------------------------------------//

			double mu1eff, mu2eff, mu3eff;
			mu1eff= calaveffofasamplemu1(mcmuonsample, muonideffpath , muonpidcuts.at(indexofcut), "mu1_P", "mu1_ETA", "mu1weight", mcmuonhist);
			cutTree(mcmuonhist, "DecayTree", mcmuonhist, "mu1weight != -1.0");
			mu2eff= calaveffofasamplemu1(mcmuonhist, muonideffpath , muonpidcuts.at(indexofcut), "mu2_P", "mu2_ETA", "mu2weight", mcmuonhist);
			cutTree(mcmuonhist, "DecayTree", mcmuonhist, "mu2weight != -1.0");
			mu3eff= calaveffofasamplemu1(mcmuonhist, muonideffpath , muonpidcuts.at(indexofcut), "mu3_P", "mu1_ETA", "mu3weight", mcmuonhist);
			cutTree(mcmuonhist, "DecayTree", mcmuonhist, "mu3weight != -1.0");

			cout<<"mu1 efficiency: "<<mu1eff<<endl;
			cout<<"mu2 efficiency: "<<mu2eff<<endl;
			cout<<"mu3 efficiency: "<<mu3eff<<endl;
			double finalmceff;
			finalmceff=mu1eff*mu2eff*mu3eff;
			cout<<"FINAL MC eff"<<finalmceff<<endl;


                        //----------------MULTIPLY  the EFFICIENCIES and make a branch----------------------------------------------------//

			addmultiplicationofbranches(mcmuonhist, "mu1weight","mu2weight","mu3weight","mcweight",("B23MuNuMC"+mcname.at(indexofcut)+stripping+polarity+".root").c_str());

                          
                        //----------------FIT REWEIGHTED MC-------------------------------------------------------------------------------//

			vector<double> mcsigval;
			mcsigval=paramfitsignal(("B23MuNuMC"+mcname.at(indexofcut)+stripping+polarity+".root").c_str(),"mcweight");

			//------------Define Combinatorial Cuts--------------------//

			vector<string> combinatorialcuts;

			combinatorialcuts.push_back("");
			combinatorialcuts.push_back("(mu3_PIDmu > 0.5) && (mu2_PIDmu > 0.5) && (mu1_PIDmu > 0.5)");
			combinatorialcuts.push_back("(mu3_PIDmu > 1.0) && (mu2_PIDmu > 1.0) && (mu1_PIDmu > 1.0)");
			combinatorialcuts.push_back("(mu3_PIDmu > 1.5) && (mu2_PIDmu > 1.5) && (mu1_PIDmu > 1.5)");
			combinatorialcuts.push_back("(mu3_PIDmu > 2.0) && (mu2_PIDmu > 2.0) && (mu1_PIDmu > 2.0)");
			combinatorialcuts.push_back("(mu3_PIDmu - mu3_PIDK > 0.5) && (mu2_PIDmu - mu2_PIDK > 0.5) && (mu1_PIDmu - mu3_PIDK > 0.5)");
			combinatorialcuts.push_back("(mu3_PIDmu - mu3_PIDK > 1.0) && (mu2_PIDmu - mu2_PIDK > 1.0) && (mu1_PIDmu - mu3_PIDK > 1.0)");
			combinatorialcuts.push_back("(mu3_PIDmu - mu3_PIDK > 1.5) && (mu2_PIDmu - mu2_PIDK > 1.5) && (mu1_PIDmu - mu3_PIDK > 1.5)");
			combinatorialcuts.push_back("(mu3_PIDmu - mu3_PIDK > 2.0) && (mu2_PIDmu - mu2_PIDK > 2.0) && (mu1_PIDmu - mu3_PIDK > 2.0)");
			combinatorialcuts.push_back("(mu3_NNmu - mu3_NNpi > -0.6) && (mu2_NNmu - mu2_NNpi > -0.6) && (mu1_NNmu - mu1_NNpi > -0.6)");
			combinatorialcuts.push_back("(mu3_NNmu - mu3_NNpi > -0.5) && (mu2_NNmu - mu2_NNpi > -0.5) && (mu1_NNmu - mu1_NNpi > -0.5)");
			combinatorialcuts.push_back("(mu3_NNmu - mu3_NNpi > -0.4) && (mu2_NNmu - mu2_NNpi > -0.4) && (mu1_NNmu - mu1_NNpi > -0.4)");
			combinatorialcuts.push_back("(mu3_NNmu > 0.2) && (mu2_NNmu > 0.2) && (mu1_NNmu > 0.2)");
			combinatorialcuts.push_back("(mu3_NNmu > 0.25) && (mu2_NNmu > 0.25) && (mu1_NNmu > 0.25)");
			combinatorialcuts.push_back("(mu3_NNmu > 0.3) && (mu2_NNmu > 0.3) && (mu1_NNmu > 0.3)");
			combinatorialcuts.push_back("(mu3_NNmu > 0.35) && (mu2_NNmu > 0.35) && (mu1_NNmu > 0.35)");



                        vector<string> cuts;
			cuts.push_back(combinatorialcuts.at(indexofcut).c_str());
			vector<double> numofcomb;



			//-------Define tags on misid----------------------------//
			
                        vector<string> tags;
			tags.push_back((mcname.at(indexofcut)).c_str());





			//------PLOT unbinned histogram for For Signal with fitted values------------//

    //                   RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",2500,10000);
      //                 RooRealVar weightnamevar("mcweight","mcweight", 0.0 ,1.0);

      //                 TFile* f = new TFile((file).c_str());
        //               TTree* t = (TTree*)f->Get("DecayTree");



//      TTree* t = gettreemcsig(file.c_str(),weightname.c_str());
//
//                //  RooRealVar r("r","r",2500,10000);
//                //     RooDataSet dr("dr","dr",RooArgSet(Bplus_Corrected_Mass),Import(*t));
//                     RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*t), WeightVar(weightname.c_str()));
//                          dr.Print();


                        TFile* f = new TFile(("B23MuNuMC"+mcname.at(indexofcut)+stripping+polarity+".root").c_str());
                        TTree* t = (TTree*)f->Get("DecayTree");


			RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",2500,10000);
			RooRealVar weightnamevar("weightname","weightname",0.0,1.0);

//			TTree* treer = gettreemcsig(("B23MuNuMC"+mcname.at(indexofcut)+stripping+polarity+".root").c_str(),"mcweight");
			RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*t), WeightVar("mcweight"));



			RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", mcsigval.at(0));
			RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",mcsigval.at(1));//,0.1,50) ;
			RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
			RooRealVar nral("nral","",mcsigval.at(2));
			RooRealVar alpharal("alpharal","",mcsigval.at(3));
			RooRealVar nrar("nrar","",mcsigval.at(4));
			RooRealVar alpharar("alpharar","",mcsigval.at(5));





			MyCB blah("blah", "blah", Bplus_Corrected_Mass, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);
			RooPlot* frame8 = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double crystal ball function")) ;
			dr.plotOn(frame8);
			blah.fitTo(dr);
			blah.plotOn(frame8,DataError(RooAbsData::SumW2));



			//C a l c u l a t e  chi squared //

			cout<<"Chi squared: "<< frame8->chiSquare() <<endl;
			RooHist* hresid = frame8->residHist();
			RooHist* hpull = frame8->pullHist();
			RooPlot* frame9 = Bplus_Corrected_Mass.frame(Title("Residual Distribution"));
			frame9->addPlotable(hresid,"P");
			RooPlot* frame10 = Bplus_Corrected_Mass.frame(Title("Pull Distribution")) ;
			frame10->addPlotable(hpull,"P"); 

			TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",800,800) ;
			canv4->Divide(2,2) ;
			canv4->cd(1) ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->GetXaxis()->SetTitle("Corrected Mass") ; frame8->Draw() ;
			canv4->cd(2) ; gPad->SetLeftMargin(0.15) ; frame9->GetYaxis()->SetTitleOffset(1.4) ; frame9->GetXaxis()->SetTitle("Corrected Mass") ; frame9->Draw() ;
			canv4->cd(3) ; gPad->SetLeftMargin(0.15) ; frame10->GetYaxis()->SetTitleOffset(1.4) ; frame10->GetXaxis()->SetTitle("Corrected Mass") ;  frame10->Draw() ;
			canv4->SaveAs(("fitdscbunbinned"+mcname.at(indexofcut)+".pdf").c_str());

			TCanvas* canvsig = new TCanvas("Sig","Sig",800,800);
			gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->GetXaxis()->SetTitle("Corrected Mass") ; frame8->Draw() ;
			canvsig->SaveAs(("fitmcsig"+mcname.at(indexofcut)+stripping+polarity+".pdf").c_str()); 

                         f->Close();
                         delete canv4;
                         delete canvsig;
                         //f.Delete;
			//        return(1);

			//--------Fit with 2CBS Part Reco Fit-----------//

                       
                        string partrecosource="/vols/lhcb/ss4314/cutonBDTs/MisidBackTonomu1mu3ETAtighterproton/B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic.root";
                                              
                        TFile* fpr = new TFile((partrecosource).c_str());
                        TTree* treez = (TTree*)fpr->Get("DecayTree");

		//	TTree* treez =  gettreepartreco(partrecosource.c_str());
			RooDataSet dz("dz","dz",RooArgSet(Bplus_Corrected_Mass),Import(*treez));
			dz.Print();
			Bplus_Corrected_Mass.setRange("partreco",2500,5100);


			RooRealVar cbmeanrpr("cbmeanrpr","cbmeanr",3942.0);
			RooRealVar cbsigmarpr("cbsigmarpr","cbsigmar",409);//,0.1,50) ;
			RooRealVar nrpr("nrpr","",1.0);
			RooRealVar alpharpr("alpharpr","",3.9);
			RooCBShape cballrpr("cballrpr", "crystal ball", Bplus_Corrected_Mass, cbmeanrpr, cbsigmarpr, alpharpr, nrpr);
			RooRealVar fracpr("fracpr","frac of events in cb 1",0.436);

			RooRealVar cbmeanrpr2("cbmeanrpr2","cbmeanr",3188);
			RooRealVar cbsigmarpr2("cbsigmarpr2","cbsigmar",420);//,0.1,50) ;
			RooRealVar nrpr2("nrpr2","",5.0);
			RooRealVar alpharpr2("alpharpr2","",0.258);
			RooCBShape cballrpr2("cballrpr2", "crystal ball", Bplus_Corrected_Mass, cbmeanrpr2, cbsigmarpr2, alpharpr2, nrpr2);

			RooAddPdf newpartreco("newpartreco","",RooArgList(cballrpr,cballrpr2),RooArgList(fracpr));          

			RooPlot* framepartreco1 = Bplus_Corrected_Mass.frame(Title("PartReco,two CB with not common mean")) ;
			dz.plotOn(framepartreco1);
			newpartreco.fitTo(dz,RooFit::Range("partreco"));
			newpartreco.plotOn(framepartreco1);
			newpartreco.plotOn(framepartreco1, Components(cballrpr), LineColor(kGreen));
			newpartreco.plotOn(framepartreco1, Components(cballrpr2), LineColor(kRed));
			newpartreco.getParameters(Bplus_Corrected_Mass)->Print("s");
			RooArgSet* params=newpartreco.getParameters(Bplus_Corrected_Mass);
			TLatex latex;

			params->printLatex(OutputFile("la.tex"));

			TCanvas* canvibou2 = new TCanvas("partreco","partreco",800,800) ;
			gPad->SetLeftMargin(0.15) ; framepartreco1->GetYaxis()->SetTitleOffset(1.4) ; framepartreco1->GetXaxis()->SetTitle("Corrected Mass") ;  framepartreco1->Draw() ;
			canvibou2->SaveAs(("partrecofit"+stripping+polarity+".pdf").c_str());
                        delete canvibou2;
                        
                        fpr->Close();

			TCanvas* canvshift = new TCanvas("changeofmisid","changeofmisid",800,800) ;
			canvshift->Divide(3,3) ;



                        //------------------FIT COMBINATORIAL and MISID------------------//


			int i(0);

			for(int(i=0); i<1; i++)

			{

                                //------------------FITS COMBINATORIAL with cuts and extrapolate and make root file with tag name-----------//


				vector<double> mycombicon;
                                string mycombisource= "/vols/lhcb/ss4314/cutonBDTs/MisidBackTonomu1mu3ETAtighterproton/Combi_Merged.root";
				mycombicon=paramfitcombi(mycombisource.c_str(),cuts.at(i),tags.at(i));

                                TFile* fcombi = new TFile(("combi_cut"+tags.at(i)+".root").c_str());
                                TTree* tree = (TTree*)fcombi->Get("DecayTree");


				//TTree* tree = gettreecomb(mycombisource.c_str(), cuts.at(i),tags.at(i));


				cout<<"Number of entries in this tree"<<tree->GetEntries()<<endl;

				//RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",2500,10000);
				RooDataSet ds("ds","ds",RooArgSet(Bplus_Corrected_Mass),Import(*tree));
				ds.Print();

				Bplus_Corrected_Mass.setRange("sideband",2500,10000);


				RooRealVar o("o","o",mycombicon.at(0)-mycombicon.at(1));
				RooExponential expoun("expoun", "exponential",Bplus_Corrected_Mass,o);
				RooPlot* frame6 = Bplus_Corrected_Mass.frame(Title("Fit with exponential function Unbinned")) ;
				ds.plotOn(frame6);

				expoun.fitTo(ds,RooFit::Range("sideband"));
				expoun.plotOn(frame6);

				cout<<"Chi squared: "<< frame6->chiSquare() <<endl;
				RooHist* hresidcom = frame6->residHist();
				RooHist* hpullcom = frame6->pullHist();
				RooPlot* framecom1 = Bplus_Corrected_Mass.frame(Title("Residual Distribution"));
				framecom1->addPlotable(hresidcom,"P");
				RooPlot* framecom2 = Bplus_Corrected_Mass.frame(Title("Pull Distribution")) ;
				framecom2->addPlotable(hpullcom,"P");



				TCanvas* canv2 = new TCanvas("myattempt3","myattempt3",800,800) ;
				canv2->Divide(2,2) ;
				canv2->cd(1) ; gPad->SetLeftMargin(0.15) ; frame6->GetYaxis()->SetTitleOffset(1.4) ;  frame6->GetXaxis()->SetTitle("Corrected Mass") ; frame6->Draw() ;
				canv2->cd(2) ; gPad->SetLeftMargin(0.15) ; framecom1->GetYaxis()->SetTitleOffset(1.4) ; framecom1->GetXaxis()->SetTitle("Corrected Mass") ; framecom1->Draw() ;
				canv2->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom2->GetYaxis()->SetTitleOffset(1.4) ; framecom2->GetXaxis()->SetTitle("Corrected Mass") ; framecom2->Draw() ;
				canv2->SaveAs("FittingCombiUnBinnedmain.pdf");
                                delete canv2;
                             
				//          return(1);  



				//----------------New Attempt-----------------------------------------------------------------------------------------------------------------//



				RooRealVar tot("tot", "tot", tree->GetEntries()); //Number of Entries in Side band

				RooExponential model("model","model",Bplus_Corrected_Mass,o);


				Bplus_Corrected_Mass.setRange("signal",2500,10000);

				RooFitResult* rfr = model.fitTo(ds,RooFit::Minos(1), RooFit::Range("sideband"), RooFit::Save());

				TCanvas* cv = new TCanvas("cv","cv",800,800);
				RooPlot *frame = Bplus_Corrected_Mass.frame(Bins(25),Title("Toy fit"));
				ds.plotOn(frame);
				model.plotOn(frame,RooFit::Range("sideband"));
				model.paramOn(frame);
				RooAbsReal* igmass_mod0 = model.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("sideband"));
				RooAbsReal* igmass_mod1 = model.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("signal"));
				RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(@1/@0)*@2" , RooArgList(*igmass_mod0, *igmass_mod1, tot));
				cout<<"Integral in the sideband wrt to the sideband :" <<" igmass_mod0->getValV(): "<< igmass_mod0->getValV()<<endl;
				cout<<"Integral in the signal wrt to the sideband:" <<" igmass_mod1->getValV(): "<< igmass_mod1->getValV()<<endl;
				cout<<"Integral: outcome :" <<" igmass_mod3->getValV(): "<<igmass_reg.getValV()<<endl;

				TPaveLabel *texpo = new TPaveLabel(0.3,0.6,0.6,0.8, Form("Exp SB %f, Exp SR %f, const %f ",double(tree->GetEntries()),igmass_reg.getValV(),double(mycombicon.at(0))),"BRNDC");
				frame->addObject(texpo);

				frame->GetXaxis()->SetTitle("Corrected Mass");
				frame->Draw();


				cv->SaveAs(("thexpo"+tags.at(i)+".pdf").c_str());
                                delete cv;
                                //delete texpo;
                                //fcombi->Close();

				cout<<"This is what I push back for combinatorial: "<<igmass_reg.getValV()<<endl;
				numofcomb.push_back(igmass_reg.getValV());


			

                                //-------------------------------------FIRST fit misid with two double crystal balls-----------------------------------------------------//


				vector<double> paramsformisid;
				paramsformisid=fitmisidcuts3samples(("/vols/lhcb/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplesPionKaontighterproton/triggerallvarnewSSmisidsamplesVS3/finaltuples/modifiedandcut"+tags.at(i)+"B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic.root").c_str(), ("/vols/lhcb/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplesPionKaontighterproton/triggerallvarnewSSmisidsamplesVS3/finaltuples/modifiedandcut"+tags.at(i)+"B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root").c_str(),("/vols/lhcb/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplesPionProtontighterproton/finaltuples/modifiedandcut"+tags.at(i)+"B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic.root").c_str(),tags.at(i));

                                string kaonsamplename=("/vols/lhcb/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplesPionKaontighterproton/triggerallvarnewSSmisidsamplesVS3/finaltuples/modifiedandcut"+tags.at(i)+"B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic.root").c_str();
                                string pionsamplename=("/vols/lhcb/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplesPionKaontighterproton/triggerallvarnewSSmisidsamplesVS3/finaltuples/modifiedandcut"+tags.at(i)+"B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root").c_str();
       
                                string protonsamplename=("/vols/lhcb/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplesPionProtontighterproton/finaltuples/modifiedandcut"+tags.at(i)+"B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic.root").c_str();

//                                return(1); 
 
                                TFile* s2 = new TFile((kaonsamplename).c_str());
                                TTree* treek = (TTree*)s2->Get("DecayTree");



                                TFile* s = new TFile((pionsamplename).c_str());
                                TTree* treep = (TTree*)s->Get("DecayTree");



                                TFile* s3 = new TFile((protonsamplename).c_str());
                                TTree* trees3 = (TTree*)s3->Get("DecayTree");
                                

//				TTree* treek =  gettreemisidkaon(("/vols/lhcb/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplesPionKaontighterproton/triggerallvarnewSSmisidsamplesVS3/finaltuples/modifiedandcut"+tags.at(i)+"B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic.root").c_str(),tags.at(i));

				//  RooRealVar p("p","p",2500,10000);
				RooRealVar weightnamevar("crossfeedweight","crossfeedweight", 0.0 ,1.0);
				RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
				RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*treek), WeightVar("crossfeedweight"));//, Import(*treew));
				dk.Print();
				dkw.Print();
				Bplus_Corrected_Mass.setBins(100);

				dk.Print("v");
				dkw.Print("v");
				cout << dk.weight() << endl;
				cout << dkw.weight() << endl; 
				const RooArgSet* row1 = dkw.get(1);
				row1->Print("v") ;
				const RooArgSet* row0 = dkw.get(0);
				row0->Print("v") ;

//				TTree* treep =  gettreemisidpion(("/vols/lhcb/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplesPionKaontighterproton/triggerallvarnewSSmisidsamplesVS3/finaltuples/modifiedandcut"+tags.at(i)+"B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root").c_str(),tags.at(i));


				RooDataSet dp("dp","dp",RooArgSet(Bplus_Corrected_Mass),Import(*treep));
				RooDataSet dpw("dpw","dpw", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*treep), WeightVar("crossfeedweight"));//, Import(*treew));
				dp.Print();
				dpw.Print();

				dp.Print("v");
				dpw.Print("v");
				cout << dp.weight() << endl;
				cout << dpw.weight() << endl; 
				const RooArgSet* row3 = dpw.get(3);
				row3->Print("v") ;
				const RooArgSet* row4 = dpw.get(4);
				row4->Print("v") ;

				RooRealVar misidoverid("misidoverid","misidoverid", 0.0 ,1.0);
				RooDataSet ds3("ds3","ds3",RooArgSet(Bplus_Corrected_Mass),Import(*trees3));
				RooDataSet ds3w("ds3w","ds3w", RooArgSet(Bplus_Corrected_Mass,misidoverid), Import(*trees3), WeightVar("misidoverid"));//, Import(*treew));
				ds3.Print();
				ds3w.Print();

				ds3.Print("v");
				ds3w.Print("v");
				cout << ds3.weight() << endl;
				cout << ds3w.weight() << endl; 
				const RooArgSet* rows3 = ds3w.get(3);
				rows3->Print("v") ;
				const RooArgSet* rows4 = ds3w.get(4);
				rows4->Print("v") ;



				RooPlot* frame11 = Bplus_Corrected_Mass.frame(Title("MisIDShapeKaon")) ;
				RooPlot* frame12 = Bplus_Corrected_Mass.frame(Title("MisIDShapeNormalizedKaon")) ;
				dk.plotOn(frame11);
				dkw.plotOn(frame11,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
				dkw.plotOn(frame12,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
				double kaonmisidsoft;
				kaonmisidsoft =dkw.sumEntries();
				TPaveLabel *t3 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",kaonmisidsoft),"brNDC");
				frame12->addObject(t3);



				RooPlot* frame13 = Bplus_Corrected_Mass.frame(Title("MisIDShapePion")) ;
				RooPlot* frame14 = Bplus_Corrected_Mass.frame(Title("MisIDShapeNormalizedPion")) ;
				dp.plotOn(frame13);
				dpw.plotOn(frame13,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
				dpw.plotOn(frame14,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
				double pionmisidsoft;
				pionmisidsoft = dpw.sumEntries();         
				TPaveLabel *t4 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",pionmisidsoft),"brNDC");
				frame14->addObject(t4);

				RooPlot* frameproton1 = Bplus_Corrected_Mass.frame(Title("MisIDShapeProton")) ;
				RooPlot* frameproton2 = Bplus_Corrected_Mass.frame(Title("MisIDShapeNormalizedProton")) ;
				ds3.plotOn(frameproton1);
				ds3w.plotOn(frameproton1,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
				ds3w.plotOn(frameproton2,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
				double protonmisid;
				protonmisid =ds3w.sumEntries();
				TPaveLabel *tp = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",protonmisid),"brNDC");
				frameproton2->addObject(tp);



				TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,800) ;
				canv5->Divide(3,3) ;
				canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->GetXaxis()->SetTitle("Corrected Mass") ;  frame11->Draw() ;
				canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->GetXaxis()->SetTitle("Corrected Mass") ; frame12->Draw() ;
				canv5->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13->GetYaxis()->SetTitleOffset(1.4) ; frame13->GetXaxis()->SetTitle("Corrected Mass") ;  frame13->Draw() ;
				canv5->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14->GetYaxis()->SetTitleOffset(1.4) ; frame14->GetXaxis()->SetTitle("Corrected Mass") ; frame14->Draw() ;
                                canv5->cd(5) ; gPad->SetLeftMargin(0.15) ; frameproton1->GetYaxis()->SetTitleOffset(1.4) ; frameproton1->GetXaxis()->SetTitle("Corrected Mass") ; frameproton1->Draw() ;
                                canv5->cd(6) ; gPad->SetLeftMargin(0.15) ; frameproton2->GetYaxis()->SetTitleOffset(1.4) ; frameproton2->GetXaxis()->SetTitle("Corrected Mass") ; frameproton2->Draw() ;

				canv5->SaveAs(("FittingMisIDUnBinnedErrorsInMain"+stripping+polarity+tags.at(i)+".pdf").c_str());
                                
                                delete canv5;



				//------Adding two datasets-------------------------//
				

 
				dpw.append(dkw);
                                dpw.append(ds3w);
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
				double misid;
				misid = dpw.sumEntries();           

				cout << dpw.weight() << endl;
				RooPlot* misidtotal = Bplus_Corrected_Mass.frame(Title("MISIDTOTAL")) ;
				RooPlot* misidtotal2 = Bplus_Corrected_Mass.frame(Title("MISIDtotal2")) ;

				dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
				dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));

				TPaveLabel *t2 = new TPaveLabel(0.4,0.6,0.9,0.8, Form("TotMisID = %f, with %s",misid,(tags.at(i)).c_str()),"brNDC");
				misidtotal->addObject(t2);


				TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
				canvtot->Divide(2,2) ;
				canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
				canvtot->SaveAs(("TotalMisIDfit"+tags.at(i)+".pdf").c_str());
                                delete canvtot;
                                
				canvshift->cd(i+1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->GetXaxis()->SetTitle("Corrected Mass") ;  misidtotal->Draw() ;      

                                
                               

				//---- Make Binned Histogram from unbinned and fit with 2 crystal balls--------//


				RooDataHist* binnedData = dpw.binnedClone() ; 
			
                                binnedData->Print("v");

				cout<< "Integral over histogram:" << binnedData->sum(kTRUE)<<endl; 
				cout<< "Sum of weight:" << binnedData->sum(kFALSE)<<endl;
				cout<< "Sum of entries:" << binnedData->sumEntries()<<endl;
				cout<< "Num of bins:" << binnedData->numEntries()<<endl;  

				RooPlot* ibou = Bplus_Corrected_Mass.frame(Title("Binned histogram")) ;
				binnedData->plotOn(ibou,DataError(RooAbsData::SumW2)); 

				RooRealVar cbmeanr1("cbmeanr1","cbmeanr", paramsformisid.at(0));
				RooRealVar cbsigmar1("cbsigmar1","cbsigmar",paramsformisid.at(1));//,0.1,50) ;
				RooRealVar nr1("nr1","",paramsformisid.at(2));
				RooRealVar alphar1("alphar1","",paramsformisid.at(3));
				RooCBShape cballr1("cballr1", "crystal ball", Bplus_Corrected_Mass, cbmeanr1, cbsigmar1, alphar1, nr1);
				RooRealVar frac1("frac1","frac of events in cb 1",paramsformisid.at(4)); 

				RooRealVar cbmeanr2("cbmeanr2","cbmeanr", paramsformisid.at(5));
				RooRealVar cbsigmar2("cbsigmar2","cbsigmar",paramsformisid.at(6));//,0.1,50) ;
				RooRealVar nr2("nr2","",paramsformisid.at(7));
				RooRealVar alphar2("alphar2","",paramsformisid.at(8));
				RooCBShape cballr2("cballr2", "crystal ball", Bplus_Corrected_Mass, cbmeanr2, cbsigmar2, alphar2, nr2);



				RooAddPdf twocbs("twocbs","",RooArgList(cballr1,cballr2),RooArgList(frac1));

				twocbs.fitTo(*binnedData);
				twocbs.plotOn(ibou) ;

				TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
				gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->GetXaxis()->SetTitle("Corrected Mass") ;  ibou->Draw() ;
				canvibou->SaveAs(("BinnedHistogramofMISID2cbs"+stripping+polarity+tags.at(i)+".pdf").c_str());         

                                delete canvibou;

				//PERFORM unbinned  minimum likelihood fit //



				RooRealVar nsig("nsig","number of signal events",100,0,1000) ;
				RooRealVar nbkg1("nbkg1","number of backgnd events",100,0,1000) ;
				RooRealVar nbkg2("nbkg2","number of backgnd events2",100,0,1000) ;
				RooRealVar nbkg3("nbkg3","number of backgnd events3",100,0,1000) ;

				RooAddPdf sume("sume","extended sum pdf",RooArgList(blah,expoun,twocbs,newpartreco), RooArgList(nsig,nbkg1,nbkg2,nbkg3));


				//Generate Toy

				RooDataSet *datafinal = sume.generate(RooArgSet(Bplus_Corrected_Mass),1000) ;
				RooFitResult* myfit = sume.fitTo(*datafinal,Extended(kTRUE),Save()) ;
				myfit->Print() ;  

				// Create RooPlot object with r on the axis.

				RooPlot* finalfitframe=Bplus_Corrected_Mass.frame(Bins(50));//, Name("myfinalfit"), Title("myfinalfit"));
				datafinal->plotOn(finalfitframe, MarkerSize(0.9));

				// Display fit parameters.

				sume.paramOn(finalfitframe, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9) );


				// Plot all components
				sume.plotOn(finalfitframe, Components(expoun), RooFit::Range("full"), LineColor(kRed),RooFit::Name("combinatorial"));
				sume.plotOn(finalfitframe, Components(blah), RooFit::Range("full"), LineColor(kGreen),RooFit::Name("signall"));
				sume.plotOn(finalfitframe, Components(twocbs), RooFit::Range("full"), LineColor(kCyan),RooFit::Name("misid"));
				sume.plotOn(finalfitframe, Components(newpartreco), RooFit::Range("full"), LineColor(kMagenta),RooFit::Name("partreco"));
				// Plot total PDF.

				sume.plotOn(finalfitframe,LineColor(kBlue),RooFit::Name("fit")); // plot fit pdf

				TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
				leg->AddEntry(finalfitframe->findObject("combinatorial"),"Combinatorial","l");
				leg->AddEntry(finalfitframe->findObject("signall"),"B^{+} -> #mu^{+}","l"); 
				leg->AddEntry(finalfitframe->findObject("misid"),"MisID","l");
				leg->AddEntry(finalfitframe->findObject("partreco"),"B^{+} -> D^{+} #pi #mu #mu","l");

				//C a l c u l a t e  chi squared //

				cout<<"Chi squared: "<< finalfitframe->chiSquare() <<endl;
				RooHist* hresidfit = finalfitframe->residHist();
				RooHist* hpullfit = finalfitframe->pullHist();
				RooPlot* framenew1 = Bplus_Corrected_Mass.frame(Title("Residual Distribution"));
				framenew1->addPlotable(hresidfit,"P");
				RooPlot* framenew2 = Bplus_Corrected_Mass.frame(Title("Pull Distribution")) ;
				framenew2->addPlotable(hpullfit,"P"); 


				//Scaled fit- number of different components for toy fit//



				double scaledmisid=(100)*misid;// only 5.8 inverse femtobarns
				double numberofsigevents=((10.3308)*finalmceff);
				double numberofcombi=igmass_reg.getValV();
				double numberofpartreco=54.65;
				double totalforfit=numberofsigevents+numberofcombi+scaledmisid+numberofpartreco;

				cout<<"Amount of misid going into the fit: "<<scaledmisid<<endl;
				cout<<"Amount of combi gong into the fit: "<<igmass_reg.getValV()<<endl;
				cout<<"Amount of partreco: "<<numberofpartreco<<endl;
				cout<<"Amount of sig events: "<<numberofsigevents<<endl;



				RooRealVar nsig00("nsig00","number of signal events",numberofsigevents) ;
				RooRealVar nbkg11("nbkg11","number of backgnd events",numberofcombi) ;
				RooRealVar nbkg22("nbkg22","number of backgnd events2",scaledmisid) ;
				RooRealVar nbkg33("nbkg33","number of backgnd events3",numberofpartreco);
                                 
                                RooRealVar totalev("totalev","number all ev",totalforfit);

				Bplus_Corrected_Mass.setRange("truesig",4900,6000);


				// Create RooPlot object with r on the axis.

				RooPlot* finalfitframetruesig=Bplus_Corrected_Mass.frame(Bins(50), Name("Toy fit"), Title("Toy fit"));

				Bplus_Corrected_Mass.setRange("fitrange",4500,10000);

				// Display fit parameters.
				RooAddPdf normpdf("normpdf","extended sum pdf",RooArgList(blah,expoun,twocbs,newpartreco), RooArgList(nsig00,nbkg11,nbkg22,nbkg33)); 
				RooDataSet *datafinalnorm = normpdf.generate(RooArgSet(Bplus_Corrected_Mass),totalforfit)  ;
				datafinalnorm->plotOn(finalfitframetruesig, MarkerSize(0.9));

				normpdf.paramOn(finalfitframetruesig, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9));//,ShowConstants() );

				// Plot all components
				normpdf.plotOn(finalfitframetruesig, Components(expoun), RooFit::Range("full"), LineColor(kRed),RooFit::Name("combinatorial2"));
				normpdf.plotOn(finalfitframetruesig, Components(blah), RooFit::Range("full"), LineColor(kGreen),RooFit::Name("signal2"));
				normpdf.plotOn(finalfitframetruesig, Components(twocbs), RooFit::Range("full"), LineColor(kCyan),RooFit::Name("misid2"));
				normpdf.plotOn(finalfitframetruesig, Components(newpartreco), RooFit::Range("full"), LineColor(kMagenta),RooFit::Name("partreco2"));



				// Plot total PDF. + for FOM use the region between 4500,5500 MeV

				Bplus_Corrected_Mass.setRange("fitreg",4500,5500);

				RooAbsReal* combinatorial = expoun.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("full"));
				RooAbsReal* combinatorialfit = expoun.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("fitreg"));
				RooFormulaVar combinatorialres("combinatorialres", "combinatorialres", "(@1/@0)*@2" , RooArgList(*combinatorial, *combinatorialfit, nbkg11 ));
				cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< combinatorial->getVal()<<endl;
				cout<<"Integral in the signal wrt figreg" << combinatorialfit->getVal()<<endl;
				cout<<"Integral: outcome :"<<combinatorialres.getVal()<<endl;

				RooAbsReal* mymisid = twocbs.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("full"));
				RooAbsReal* mymisidfit = twocbs.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("fitreg"));
				RooFormulaVar mymisidres("mymisidres", "mymisidres", "(@1/@0)*@2" , RooArgList(*mymisid, *mymisidfit, nbkg22 ));
				cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mymisid->getVal()<<endl;
				cout<<"Integral in the signal wrt figreg" << mymisidfit->getVal()<<endl;
				cout<<"Integral: outcome :"<<mymisidres.getVal()<<endl;

				RooAbsReal* mysig = blah.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("full"));
				RooAbsReal* mysigfit = blah.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("fitreg"));
				RooFormulaVar mysigres("mysigres", "mysigres", "(@1/@0)*@2" , RooArgList(*mysig, *mysigfit, nsig00 ));
				cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mysig->getVal()<<endl;
				cout<<"Integral in the signal wrt figreg" << mysigfit->getVal()<<endl;
				cout<<"Integral: outcome :"<<mysigres.getVal()<<endl;

				RooAbsReal* mypr = newpartreco.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("full"));
				RooAbsReal* myprfit = newpartreco.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("fitreg"));
				RooFormulaVar myprres("myprres", "myprres", "(@1/@0)*@2" , RooArgList(*mypr, *myprfit, nbkg33 ));
				cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mypr->getVal()<<endl;
				cout<<"Integral in the signal wrt figreg" << myprfit->getVal()<<endl;
				cout<<"Integral: outcome :"<<myprres.getVal()<<endl;

                                // Expected Number for region between 4000 and 4500 MeV//
                               
                                Bplus_Corrected_Mass.setRange("lsdreg",2500,4500);

                                //RooAbsReal* combinatorial = expoun.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("full"));
                                RooAbsReal* combinatorialfitlsd = expoun.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("lsdreg"));
                                RooFormulaVar combinatorialreslsd("combinatorialreslsd", "combinatorialreslsd", "(@1/@0)*@2" , RooArgList(*combinatorial, *combinatorialfitlsd, nbkg11 ));
                                cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< combinatorial->getVal()<<endl;
                                cout<<"Integral in the signal wrt lsdreg" << combinatorialfitlsd->getVal()<<endl;
                                cout<<"Integral: outcome :"<<combinatorialreslsd.getVal()<<endl;

                                //RooAbsReal* mymisid = twocbs.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("full"));
                                RooAbsReal* mymisidfitlsd = twocbs.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("lsdreg"));
                                RooFormulaVar mymisidreslsd("mymisidreslsd", "mymisidreslsd", "(@1/@0)*@2" , RooArgList(*mymisid, *mymisidfitlsd, nbkg22 ));
                                cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mymisid->getVal()<<endl;
                                cout<<"Integral in the signal wrt lsdreg" << mymisidfitlsd->getVal()<<endl;
                                cout<<"Integral: outcome :"<<mymisidreslsd.getVal()<<endl;

                                //RooAbsReal* mysig = blah.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("full"));
                                RooAbsReal* mysigfitlsd = blah.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("lsdreg"));
                                RooFormulaVar mysigreslsd("mysigreslsd", "mysigreslsd", "(@1/@0)*@2" , RooArgList(*mysig, *mysigfitlsd, nsig00 ));
                                cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mysig->getVal()<<endl;
                                cout<<"Integral in the signal wrt lsdreg" << mysigfitlsd->getVal()<<endl;
                                cout<<"Integral: outcome :"<<mysigreslsd.getVal()<<endl;

                                //RooAbsReal* mypr = newpartreco.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("full"));
                                RooAbsReal* myprfitlsd = newpartreco.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("lsdreg"));
                                RooFormulaVar myprreslsd("myprreslsd", "myprreslsd", "(@1/@0)*@2" , RooArgList(*mypr, *myprfitlsd, nbkg33 ));
                                cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mypr->getVal()<<endl;
                                cout<<"Integral in the signal wrt lsdreg" << myprfitlsd->getVal()<<endl;
                                cout<<"Integral: outcome :"<<myprreslsd.getVal()<<endl;

                              
				double punzimetric(0);
				punzimetric=double(mysigres.getVal())/(sqrt(double(combinatorialres.getVal())+double(mymisidres.getVal())+double(myprres.getVal()))+double(3.0/2.0));

				cout<<"My punzi calc: "<< sqrt(double(combinatorialres.getVal())+double(mymisidres.getVal())+double(myprres.getVal())) << " " <<combinatorialres.getVal() << " " << mymisidres.getVal()<< " " << (myprres.getVal())<<endl;
				cout<<"My punzi metric: "<< punzimetric << "Num of sig"<< mysigres.getVal() << endl;

				ofstream out;
				out.open(("STATISTICS"+stripping+polarity+tags.at(i)+".txt").c_str());
				out<<"\\begin{table}[h]"<<endl;
				out<<"\\begin{center}"<<endl;
				out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
				out<<"\\hline"<<endl;
				out<<"Sample &   cut & 3fb$^{-1}$ \\\\ "<<endl;
				out<<"misid  & "<<tags.at(i)<<" & "<< scaledmisid <<" \\\\ " <<endl;
				out<<"mcsig  & "<<tags.at(i)<<" & "<< numberofsigevents <<"  \\\\ "<<endl;
				out<<"combi  & "<<tags.at(i) <<" & "<< numberofcombi <<" \\\\ "<<endl;
				out<<"partreco  & "<<"no cut"<<" & " << numberofpartreco << " \\\\ "<<endl;
				out<<"\\hline"<<endl;
				out<<"Sample REG 4.5-5.5 &  cut & 3fb$^{-1}$ \\\\ "<<endl;
				out<<"\\hline"<<endl;
				out<<"misid  & "<<tags.at(i)<<" & "<< mymisidres.getVal() <<" \\\\ " <<endl;
				out<<"mcsig  & "<<tags.at(i)<<" & "<< mysigres.getVal() <<"  \\\\ "<<endl;
				out<<"combi  & "<<tags.at(i) <<" & "<< combinatorialres.getVal() <<" \\\\ "<<endl;
				out<<"partreco  & "<<"no cut"<< " & " << myprres.getVal() << " \\\\ "<<endl;
				out<<"\\hline"<<endl;
				out<<"punzi metric & " <<" S/sqrt(B)+3/2 & "<< punzimetric << " & "<< " \\\\ "<<endl;
                                out<<"Sample REG 4.0-4.5 &  cut & 3fb$^{-1}$ \\\\ "<<endl;
                                out<<"\\hline"<<endl;
                                out<<"misid  & "<<tags.at(i)<<" & "<< mymisidreslsd.getVal() <<" \\\\ " <<endl;
                                out<<"mcsig  & "<<tags.at(i)<<" & "<< mysigreslsd.getVal() <<"  \\\\ "<<endl;
                                out<<"combi  & "<<tags.at(i) <<" & "<< combinatorialreslsd.getVal() <<" \\\\ "<<endl;
                                out<<"partreco  & "<<"no cut"<< " & " << myprreslsd.getVal() << " \\\\ "<<endl;
                                out<<"\\hline"<<endl;

				out<<"\\hline"<<endl;
				out<<"\\end{tabular}"<<endl;
				out<<"\\end{center}"<<endl;
				out<<"\\caption{STATISTICS"<<stripping+polarity+tags.at(i)<<".txt}"<<endl;
				out<<"\\end{table}"<<endl;



				normpdf.plotOn(finalfitframetruesig,LineColor(kBlue),RooFit::Name("fit2")); // plot fit pdf

				TLegend *leg2 = new TLegend(0.6,0.6,0.8,0.8);
				leg2->AddEntry(finalfitframetruesig->findObject("combinatorial2"),"Combinatorial Data","l");
				leg2->AddEntry(finalfitframetruesig->findObject("signal2"),"B^{+} -> #mu^{+} #mu^{-} #mu^{+} MC","l"); 
				leg2->AddEntry(finalfitframetruesig->findObject("misid2"),"MisID Data","l");
				leg2->AddEntry(finalfitframetruesig->findObject("partreco2"),"B^{+} -> (D^{0} -> #pi #pi) #mu MC","l");

				finalfitframetruesig->SetMaximum(70);

				TCanvas* canvasfit2 = new TCanvas("fit2", "Fit2",800,800);
				gPad->SetLeftMargin(0.15) ; finalfitframetruesig->GetYaxis()->SetTitleOffset(1.4) ; finalfitframetruesig->GetXaxis()->SetTitle("Corrected Mass"); finalfitframetruesig->GetXaxis()->SetRangeUser(4500,10000); finalfitframetruesig->Draw(); leg2->Draw();
				canvasfit2->SaveAs(("finalfitnormalizedana"+stripping+polarity+tags.at(i)+".pdf").c_str());
                                
                                delete canvasfit2; 



				//		  TPaveLabel *t5 = new TPaveLabel(0.5,0.5,0.9,0.7, Form("TotMisID = %f \\ TotComb = %f \\ with %s",scaledmisid,numberofcombi,(tags.at(i)).c_str()),"brNDC");
				//t5->SetTextSize(0.0);
				//                  finalfitframetruesig->addObject(t5);

				TPaveText *text = new TPaveText(0.5, 0.3, 0.9, 0.5, "NBNDC");
				text->AddText(("TotMisID = "+d2s(scaledmisid)).c_str());
				text->AddText(("TotComb = "+d2s(numberofcombi)).c_str());
				text->AddText((tags.at(i)).c_str());

				text->SetTextSize(0.05);
				text->SetFillColor(0);
				text->SetLineColor(0);
				finalfitframetruesig->addObject(text);
				//   frame->Draw()



				TCanvas* canvasfit = new TCanvas("fit", "Fit",800,800);
				canvasfit->Divide(2,2) ;
				canvasfit->cd(1) ; gPad->SetLeftMargin(0.15) ; finalfitframe->GetYaxis()->SetTitleOffset(1.4) ; finalfitframe->Draw(); leg->Draw();
				canvasfit->cd(2) ; gPad->SetLeftMargin(0.15) ; framenew1->GetYaxis()->SetTitleOffset(1.4) ; framenew1->Draw();
				canvasfit->cd(3) ; gPad->SetLeftMargin(0.15) ; framenew2->GetYaxis()->SetTitleOffset(1.4) ; framenew2->Draw();
				canvasfit->cd(4) ; gPad->SetLeftMargin(0.15) ; finalfitframetruesig->GetYaxis()->SetTitleOffset(1.4) ; finalfitframetruesig->Draw(); leg2->Draw();
				canvasfit->SaveAs(("finalfitnormalized"+tags.at(i)+".pdf").c_str());

                                delete canvasfit;
				canvshifttotal->cd(indexofcut+1) ; gPad->SetLeftMargin(0.15) ; finalfitframetruesig->GetYaxis()->SetTitleOffset(1.4) ; finalfitframetruesig->GetXaxis()->SetTitle("Corrected Mass"); finalfitframetruesig->Draw(); leg2->Draw();

                                TCanvas* lsmd = new TCanvas("LMSD", "LMSD",800,800); 
                                
                                TFile* lsmdfile = new TFile("/vols/lhcb/ss4314/cutonProbnnmu/probnnmugreaterthen03/Data2012and2011_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_Probnnmu3.root");
                                TTree* lsmdtree = (TTree*)lsmdfile->Get("DecayTree");                       
                                RooDataSet dlsmd("dlsmd","dlsmd",RooArgSet(Bplus_Corrected_Mass),Import(*lsmdtree));
                                dlsmd.Print();
                                RooPlot* framedlsmd = Bplus_Corrected_Mass.frame(Title("Fit to toydata vs LMSD"),Bins(150)) ;
                                //dlsmd.plotOn(framedlsmd);
                                //rf-r>plotOn(framedlsmd,Bplus_Corrected_Mass);
                                RooRealVar nzero("nzero","number of signal events",0) ; 
//                                ds.plotOn(framedlsmd,MarkerColor(kBlue),LineColor(kBlue));
//                                model.plotOn(framedlsmd,RooFit::Range("full"), RooFit::Normalization(1.0));
                                //dlsmd.plotOn(framedlsmd);
                                datafinalnorm->plotOn(framedlsmd, MarkerSize(0.1), MarkerColor(kBlue),LineColor(kBlue));
                                normpdf.plotOn(framedlsmd, Components(expoun), RooFit::Range("full"), LineColor(kRed), RooFit::LineStyle(kDashed),RooFit::Name("combinatoriallsd"));
                                normpdf.plotOn(framedlsmd, Components(blah), RooFit::Range("full"), LineColor(kGreen), RooFit::LineStyle(kDashed),RooFit::Name("signallsd"));
                                normpdf.plotOn(framedlsmd, Components(twocbs), RooFit::Range("full"), LineColor(kCyan), RooFit::LineStyle(kDashed),RooFit::Name("misidlsd"));
                                normpdf.plotOn(framedlsmd, Components(newpartreco), RooFit::Range("full"), LineColor(kMagenta), RooFit::LineStyle(kDashed),RooFit::Name("partrecolsd"));
                                normpdf.plotOn(framedlsmd, LineColor(kBlue), RooFit::Name("fitlsd"));
                                dlsmd.plotOn(framedlsmd,MarkerSize(0.9),RooFit::Name("datalsd"));
                              
                                TLegend *leglsd = new TLegend(0.6,0.6,0.8,0.8);
                                leglsd->AddEntry(framedlsmd->findObject("combinatoriallsd"),"Combinatorial Data","l");
                                leglsd->AddEntry(framedlsmd->findObject("signallsd"),"B^{+} -> #mu^{+} #mu^{-} #mu^{+} MC","l");
                                leglsd->AddEntry(framedlsmd->findObject("misidlsd"),"MisID Data","l");
                                leglsd->AddEntry(framedlsmd->findObject("partrecolsd"),"B^{+} -> (D^{0} -> #pi #pi) #mu MC","l");
                                leglsd->AddEntry(framedlsmd->findObject("fitlsd"),"Fit","l");
                                leglsd->AddEntry(framedlsmd->findObject("datalsd"),"Data","l");

//                              RooAddPdf misidpdf("misidpdf","extended supdf",RooArgList(expoun,twocbs),RooArgList(nzero,nbkg22));
//                              RooDataSet *datamisid = misidpdf.generate(RooArgSet(Bplus_Corrected_Mass),scaledmisid);

 //                             datamisid->plotOn(framedlsmd, MarkerSize(0.9), MarkerColor(kCyan),LineColor(kCyan));
                                
                              //  dpw.plotOn(framedlsmd,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
                                
                                // normpdf.plotOn(framedlsmd, Components(expoun), RooFit::Range("sideband"), LineColor(kRed));
                               // expoun.fitTo(ds,RooFit::Range("sideband"));                               
 
                                //RooAbsReal* myintegral = normpdf.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("lsdreg"));
                                //RooFormulaVar myprreslsd("myprreslsd", "myprreslsd", "(@1/@0)*@2" , RooArgList(*mypr, *myprfitlsd, nbkg33 ));
                                //cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mypr->getVal()<<endl;
                               
                                RooAbsReal* myintegral = normpdf.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("full"));
                                RooAbsReal* myintegrallsd = normpdf.createIntegral(Bplus_Corrected_Mass,RooFit::NormSet(Bplus_Corrected_Mass),RooFit::Range("lsdreg"));
                                RooFormulaVar myintlsd("myintlsd", "myintlsd", "(@1/@0)*@2" , RooArgList(*myintegral, *myintegrallsd, totalev));
                                cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< myintegral->getVal()<<endl;
                                cout<<"Integral in the signal wrt lsdreg" << myintegrallsd->getVal()<<endl;
                                cout<<"Integral toy dat outcome :"<<myintlsd.getVal()<<endl; 
                                //cout<<"Integral od toy data: outcome :"<<myintegral->getVal()<<endl;


                                gPad->SetLeftMargin(0.15) ; framedlsmd->GetYaxis()->SetTitleOffset(1.4) ; framedlsmd->Draw(); leglsd->Draw();
                                lsmd->SaveAs("lsmd.pdf");

                                
                                TCanvas* lsmd2 = new TCanvas("LMSD2", "LMSD2",800,800);
                                RooDataSet dlsmd2("dlsmd2","dlsmd2",RooArgSet(Bplus_Corrected_Mass),Import(*lsmdtree));
                                dlsmd2.Print();
                                RooPlot* framedlsmd2 = Bplus_Corrected_Mass.frame(Title("Fit to my beautiful LMSD"),Bins(100));
                                ds.plotOn(framedlsmd2,MarkerColor(kBlue),LineColor(kBlue));
                                model.plotOn(framedlsmd2,RooFit::Range("sideband"), RooFit::Normalization(1.0));
                                binnedData->plotOn(framedlsmd2,DataError(RooAbsData::SumW2));
                                twocbs.fitTo(*binnedData);
                                twocbs.plotOn(framedlsmd2);  


                                gPad->SetLeftMargin(0.15) ; framedlsmd2->GetYaxis()->SetTitleOffset(1.4) ; framedlsmd2->Draw();
                                lsmd2->SaveAs("lsmd2.pdf");

                                                               

				//Scaled fit- number of different components for toy fit//



				//Scaled fit- number of different components for toy fit//




		}

		canvshift->SaveAs("misidshiftbasiccutforallthreecombinethetwo.pdf");
                delete canvshift;         
	}
	canvshifttotal->SaveAs("changeofmisidfinalfit.pdf") ;
        delete canvshifttotal;
        cout<<"la la"<<endl; 

}
cout<<"la la la"<<endl;
return(0);


}


