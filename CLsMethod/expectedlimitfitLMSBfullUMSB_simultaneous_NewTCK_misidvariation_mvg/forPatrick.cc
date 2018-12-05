
    if(scratch==0){


	    TFile* f = new TFile("fitresults_forCLs_2.root","READ");
	    RooWorkspace* ws = (RooWorkspace*)f->Get("workspaceFit");
	    RooAbsPdf* pdf = ws->pdf("simPdfsig");
	    RooAbsPdf* pdf_LL = ws->pdf("normsigpdf_LowFCME");
	    RooAbsPdf* pdf_DD = ws->pdf("normsigpdf_HighFCME");
	    RooAbsData* data = ws->data("combData");
	    RooCategory* cat = (RooCategory*)ws->cat("sample");
	    RooRealVar* BF = ws->var("BR");
	    RooRealVar* mass = ws->var("Bplus_Corrected_Mass");





            cout<<"Everything Ok "<<endl;
	    pdf->getParameters(*mass)->Print("v") ; 
	    RooAbsData* data2 = signal_datasets.at(0);


	    BF->setVal(CLsBF);
	    BF->setConstant(true);

	    pdf->getParameters(*mass)->Print("s") ; 

	    TCanvas* canvasprefit= new TCanvas("fit2", "Fit2",800,800);
	    canvasprefit->Divide(2) ;
	    RooPlot* frame5 = mass->frame(Title("Initial first dataset LFCME- NO FIT"),Bins(60)) ;
	    data2->plotOn(frame5,Cut("sample==sample::LowFCME"));
	    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),ProjWData(*cat,*data2));
	    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kRed));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kCyan));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kMagenta));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kGreen));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
	    cout<<" LOL "<<endl;
	    RooPlot* frame6 = mass->frame(Title("Initital first dataset HFCME- NO FIT"),Bins(60)) ;
	    data2->plotOn(frame6,Cut("sample==sample::HighFCME")) ;
	    pdf->plotOn(frame6,Slice(*cat,"HighFCME"),ProjWData(*cat,*data2));
	    pdf->plotOn(frame6,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kRed));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame6,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kCyan));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame6,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kMagenta));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame6,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kGreen));
	    canvasprefit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame5->GetYaxis()->SetTitleOffset(1.4) ; frame5->Draw() ;
	    canvasprefit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame6->GetYaxis()->SetTitleOffset(1.4) ; frame6->Draw() ;
	    canvasprefit->SaveAs(("Prefit_signaldata_numoftoys"+i2s(nToys)+"_injectsig_"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
	    delete canvasprefit;


	    RooFitResult* cool = pdf->fitTo(*data2,RooFit::Extended(true),RooFit::Save(true),RooFit::NumCPU(1));//,ExternalConstraints(RooArgSet(*m_num,*m_num_high,*m_sigma,*m_sigma_high,*m_mean_high,*m_mean)));


	    TCanvas* canvas2= new TCanvas("fit2", "Fit2",800,800);
	    canvas2->Divide(2) ;
	    RooPlot* frame3 = mass->frame(Title("Fitting first dataset LFCME"),Bins(60)) ;
	    data2->plotOn(frame3,Cut("sample==sample::LowFCME"));
	    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data2));
	    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kRed));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kCyan));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kMagenta));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kGreen));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
	    cout<<" LOL "<<endl;
	    RooPlot* frame4 = mass->frame(Title("Fitting first dataset HFCME"),Bins(60)) ;
	    data2->plotOn(frame4,Cut("sample==sample::HighFCME")) ;
	    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data2));
	    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kRed));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kCyan));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kMagenta));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kGreen));
	    canvas2->cd(1) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
	    canvas2->cd(2) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
	    canvas2->SaveAs(("FirstTry_signaldata_numoftoys"+i2s(nToys)+"_injectsig_"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
	    delete canvas2;

	    int ranges(0);
	    if (ranges==1){
		    RooAbsReal* all = pdf->createIntegral(*mass,RooFit::NormSet(*mass),RooFit::Range("new_lol"));
		    RooAbsReal* allfit = pdf->createIntegral(*mass,RooFit::NormSet(*mass),RooFit::Range("fit_lol"));
		    RooAbsReal* allfit2 = pdf->createIntegral(*mass,RooFit::NormSet(*mass),RooFit::Range("low_lol,high_lol"));
		    cout<<"Integral in the 4000 to 7000 wrt to the 4.0-7.0 :"<< all->getVal()<<endl;
		    cout<<"Integral in 4500 - 5500: " << allfit->getVal()<<endl;
		    cout<<"Integral in the l < 4500 and u msbd > 5500: " << allfit2->getVal()<<endl;
	    }

	    BF->setConstant(false);
	    BF->setVal(0.0);
	    BF->setConstant(true);

	    TCanvas* canvas3= new TCanvas("fit3", "Fit3",800,800);
	    RooAbsData* data3 = signal_datasets.at(0);

	    RooFitResult* data_intresult_fixed = pdf->fitTo(*data3,RooFit::Extended(true),RooFit::Save(true),RooFit::NumCPU(1));//,ExternalConstraints(RooArgSet(*m_num,*m_num_high,*m_sigma,*m_sigma_high,*m_mean_high,*m_mean)));

	    RooPlot* xframe3 = mass->frame(Title("signal example")) ;
	    data3->plotOn(xframe3);
	    pdf->plotOn(xframe3);
	    gPad->SetLeftMargin(0.15) ; xframe3->GetYaxis()->SetTitleOffset(1.4) ; xframe3->Draw() ;
	    canvas3->SaveAs(("signaldata_numoftoys"+i2s(nToys)+"_injectsig_"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());

	    delete f;
    }
