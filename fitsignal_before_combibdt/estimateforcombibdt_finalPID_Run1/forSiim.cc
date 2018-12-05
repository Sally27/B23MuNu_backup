
void FitAndSplotB23MuNuDataForTraining::simultaneouspdfminenew()
{

          TFile* f_low = new TFile("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous/workspace_preparation/myworkspace_signal_LowFCME.root");
          RooWorkspace* ws_low = (RooWorkspace*)f_low->Get("w");
	  ws_low->Print();
          RooAbsPdf* pdf_sig_low = ws_low->pdf(("blah_"+typelow).c_str());

          TFile* f_high = new TFile("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous/workspace_preparation/myworkspace_signal_HighFCME.root");
          RooWorkspace* ws_high = (RooWorkspace*)f_high->Get("w");
          RooAbsPdf* pdf_sig_high = ws_high->pdf(("blah_"+typehigh).c_str());

          TFile* pr_low = new TFile("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous/workspace_preparation/myworkspace_partreco_LowFCME.root");
          RooWorkspace* wspr_low = (RooWorkspace*)pr_low->Get("w");
          RooAbsPdf* pdf_pr_low = wspr_low->pdf(("newpartreco_"+typelow).c_str());
          RooRealVar* npr_low = wspr_low->var(("npartreco_"+typelow).c_str());

          TFile* pr_high = new TFile("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous/workspace_preparation/myworkspace_partreco_HighFCME.root");
          RooWorkspace* wspr_high = (RooWorkspace*)pr_high->Get("w");
          RooAbsPdf* pdf_pr_high = wspr_high->pdf(("newpartreco_"+typehigh).c_str());
          RooRealVar* npr_high = wspr_high->var(("npartreco_"+typehigh).c_str());

          TFile* misid_low = new TFile("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous/workspace_preparation/myworkspace_misid_LowFCME.root");
          RooWorkspace* wsmisid_low = (RooWorkspace*)misid_low->Get("w");
          RooAbsPdf* pdf_misid_low = wsmisid_low->pdf(("twocbs_"+typelow).c_str());
          RooRealVar* nmisid_low = wsmisid_low->var(("nmisid_"+typelow).c_str());
          RooRealVar* frac_lowCM_low = wsmisid_low->var(("frac_low_"+typelow).c_str());
          RooRealVar* frac_highCM_low = wsmisid_low->var(("frac_high_"+typelow).c_str());

          double trial;
          trial = (nmisid_low->getVal())*(double(frac_lowCM_low->getVal())+double(frac_highCM_low->getVal()));
          RooRealVar newmisid_low("newmisid_low","newmisid_low",trial);          



          TFile* misid_high = new TFile("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous/workspace_preparation/myworkspace_misid_HighFCME.root");
          RooWorkspace* wsmisid_high = (RooWorkspace*)misid_high->Get("w");
          RooAbsPdf* pdf_misid_high = wsmisid_high->pdf(("twocbs_"+typehigh).c_str());
          RooRealVar* nmisid_high = wsmisid_high->var(("nmisid_"+typehigh).c_str());
          RooRealVar* frac_lowCM_high = wsmisid_high->var(("frac_low_"+typehigh).c_str());
          RooRealVar* frac_highCM_high = wsmisid_high->var(("frac_high_"+typehigh).c_str());
        //  misid_high->Close();

          cout<<"Printing workspces for misid: "<<endl;
          wsmisid_low->Print();
          cout<<"High misid workspace: "<<endl;
          wsmisid_high->Print();

            

	  RooRealVar BR("BR","branching fraction",1.0e-8);
	  RooRealVar ses("ses","Single event sensitivity",9.0e-10,8.0e-10,1.0e-9);

          RooRealVar nexp_low("nexp_low","n explow",0.1,1500);
          RooRealVar nexp_high("nexp_high","n exphigh",0.1,1500);

	  RooFormulaVar nsigform_low("nsigform_low","nsigfromformula","@1/@0",RooArgList(ses,BR));
          RooFormulaVar nsigform_high("nsigform_high","nsigfromformula","@1/@0",RooArgList(ses,BR));



          RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,10000);
          Bplus_Corrected_Mass.setRange("high",5501,10000);
          Bplus_Corrected_Mass.setRange("low",4000,4499);
          Bplus_Corrected_Mass.setRange("new",4000,10000);


	  RooRealVar newexpocon("newexpocon","newexpocon",-0.3,0.3);
	  RooExponential newexpoun("newexpoun", "exponential",Bplus_Corrected_Mass,newexpocon);




        cout<<"WOOHOO"<<endl;

	RooAddPdf normpdf_low(("normpdf_"+typelow).c_str(),"extended sum pdf",RooArgList(newexpoun,*pdf_misid_low,*pdf_pr_low), RooArgList(nexp_low,*nmisid_low,*npr_low)); 

        normpdf_low.Print("t");

        RooAddPdf normpdf_high(("normpdf_"+typehigh).c_str(),"extended sum pdf",RooArgList(*pdf_misid_high,*pdf_pr_high,newexpoun), RooArgList(*nmisid_high,*npr_high,nexp_high));

  

        //---------LOW Data-------------------------------------// 


        TFile flow("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous/workspace_preparation/FitB23MuNuworkspace_LowFCME.root");

	RooWorkspace* workspaceData_low = (RooWorkspace*)flow.Get("workspaceData");

	if(!workspaceData_low)
	{
		cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<endl;
		return;
	}

	RooRealVar* Bplus_Corrected_Mass_low = workspaceData_low->var("Bplus_Corrected_Mass");
	RooDataSet* data_low = (RooDataSet*)workspaceData_low->data("data_LowFCME");

	if(!data_low || !Bplus_Corrected_Mass_low)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining, error downloading stuff from workspace"<<endl;
		return;
	}


        TFile fhigh("/vols/lhcb/ss4314/fitsignalchannelFUMSB_simultaneous/workspace_preparation/FitB23MuNuworkspace_HighFCME.root");

	RooWorkspace* workspaceData_high = (RooWorkspace*)fhigh.Get("workspaceData");

	if(!workspaceData_high)
	{
		cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<endl;
		return;
	}

	RooRealVar* Bplus_Corrected_Mass_high = workspaceData_high->var("Bplus_Corrected_Mass");
	RooDataSet* data_high = (RooDataSet*)workspaceData_high->data("data_HighFCME");

	if(!data_high || !Bplus_Corrected_Mass_high)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining, error downloading stuff from workspace"<<endl;
		return;
	}

	// C r e a t e   i n d e x   c a t e g o r y   a n d   j o i n   s a m p l e s 
	// ---------------------------------------------------------------------------

	// Define category to distinguish physics and control samples events
	RooCategory sample("sample","sample") ;
	sample.defineType("LowFCME") ;
	sample.defineType("HighFCME") ;

	// Construct combined dataset in (x,sample)
	RooDataSet combData("combData","combined data",Bplus_Corrected_Mass,Index(sample),Import("LowFCME",*data_low),Import("HighFCME",*data_high)) ;



	// C o n s t r u c t   a   s i m u l t a n e o u s   p d f   i n   ( x , s a m p l e )
	// -----------------------------------------------------------------------------------

	// Construct a simultaneous pdf using category sample as index
	RooSimultaneous simPdf("simPdf","simultaneous pdf",sample) ;

	// Associate model with the physics state and model_ctl with the control state
	simPdf.addPdf(normpdf_low,"LowFCME") ;
	simPdf.addPdf(normpdf_high,"HighFCME") ;



	// P e r f o r m   a   s i m u l t a n e o u s   f i t
	// ---------------------------------------------------

	// Perform simultaneous fit of model to data and model_ctl to data_ctl
	simPdf.fitTo(combData,RooFit::Range("low,high"),Extended(kTRUE),Save(kTRUE)) ;


	// P l o t   m o d e l   s l i c e s   o n   d a t a    s l i c e s 
	// ----------------------------------------------------------------

	// Make a frame for the physics sample
	RooPlot* frame1 = Bplus_Corrected_Mass.frame(Bins(60),Title("Low Fractional Corrected Mass Error")) ;

	// Plot all data tagged as physics sample
	combData.plotOn(frame1,Cut("sample==sample::LowFCME")) ;

	// Plot "physics" slice of simultaneous pdf. 
	// NBL You _must_ project the sample index category with data using ProjWData 
	// as a RooSimultaneous makes no prediction on the shape in the index category 
	// and can thus not be integrated
//	simPdf.plotOn(frame1,Slice(sample,"LowFCME"),RooFit::Range("low,high"),RooFit::NormRange("new"), LineColor(kGreen));
	simPdf.plotOn(frame1,Slice(sample,"LowFCME"),ProjWData(sample,combData),RooFit::Range("low,high"),RooFit::NormRange("new"));
	simPdf.plotOn(frame1,Slice(sample,"LowFCME"),Components("newexpoun"),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kRed),RooFit::Range("lowi,high"),RooFit::NormRange("new"));
        simPdf.plotOn(frame1,Slice(sample,"LowFCME"),Components(("twocbs_"+typelow).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low,high"), RooFit::NormRange("new"));
        simPdf.plotOn(frame1,Slice(sample,"LowFCME"),Components(("newpartreco_"+typelow).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low,high"),RooFit::NormRange("new"));
       // simPdf.plotOn(frame1,Slice(sample,"LowFCME"),RooFit::Range("low,high"),RooFit::NormRange("new"), LineColor(kGreen));

	// The same plot for the control sample slice
	RooPlot* frame2 = Bplus_Corrected_Mass.frame(Bins(60),Title("High Fractional Corrected Mass Error")) ;
	combData.plotOn(frame2,Cut("sample==sample::HighFCME")) ;
	simPdf.plotOn(frame2,Slice(sample,"HighFCME"),ProjWData(sample,combData),RooFit::Range("low,high"),RooFit::NormRange("new"));//,RooFit::Range("low,high"),RooFit::NormRange("full"));
	simPdf.plotOn(frame2,Slice(sample,"HighFCME"),Components("newexpoun"),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low,high"),RooFit::NormRange("new"));//,RooFit::Range("low,high"), RooFit::NormRange("full")) ;
        simPdf.plotOn(frame2,Slice(sample,"HighFCME"),Components(("twocbs_"+typehigh).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low,high"),RooFit::NormRange("new"));//,RooFit::Range("low,high"), RooFit::NormRange("full"));
        simPdf.plotOn(frame2,Slice(sample,"HighFCME"),Components(("newpartreco_"+typehigh).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low,high"),RooFit::NormRange("new"));//,RooFit::Range("low,high"),RooFit::NormRange("full")) ;

	TCanvas* c = new TCanvas("rf501_simultaneouspdf","rf403_simultaneouspdf",800,400) ;
	c->Divide(2) ;
	c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
	c->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
        c->SaveAs("SimfitMineNew.pdf");

        TFile file("fitresults.root", "RECREATE");

	RooWorkspace workspaceFit("workspaceFit", "workspaceFit");

        workspaceFit.import(Bplus_Corrected_Mass);
	workspaceFit.import(*data_low);
	workspaceFit.import(*data_high);
        workspaceFit.import(normpdf_low);
        workspaceFit.import(normpdf_high,RecycleConflictNodes());

	//workspaceFit.writeToFile(workspaceFileName.c_str());
	workspaceFit.Write("", TObject::kOverwrite);
	//
	cout<<"Workspace for fit has been saved:"<<endl;
	workspaceFit.Print();
	//
	//
	file.Close();

}
