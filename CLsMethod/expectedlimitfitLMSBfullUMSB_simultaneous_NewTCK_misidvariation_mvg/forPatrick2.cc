
double fitTwiceOld2_con_new(RooDataSet* data,int nToys, double CLsBF, TTree* treename, bool update)
{       

   TFile f_comp("fitresults_forCLs_3.root","READ");
   RooWorkspace* ws = (RooWorkspace*)f_comp.Get("workspaceFit");
   RooAbsPdf* model = ws->pdf("simPdfsig");
   RooAbsPdf* model_LL = ws->pdf("normsigpdf_LowFCME");
   RooAbsPdf* model_DD = ws->pdf("normsigpdf_HighFCME");
   RooCategory* cat = (RooCategory*)ws->cat("sample");
   RooRealVar* BF = ws->var("BR");
   RooRealVar* Bplus_Corrected_Mass = ws->var("Bplus_Corrected_Mass");


   cout<<"These are the constraints"<<endl;

    BF->setConstant(false);
    BF->setVal(CLsBF);
    BF->removeError();
    BF->setConstant(true);


   Bplus_Corrected_Mass->setRange("high3",5000,7000);
   Bplus_Corrected_Mass->setRange("low3",4000,5000);
   Bplus_Corrected_Mass->setRange("full3",4000,7000);

   Bplus_Corrected_Mass->setRange("high2",5000,7000);
   Bplus_Corrected_Mass->setRange("low2",4000,5000);
   Bplus_Corrected_Mass->setRange("full2",4000,7000);
    

    model->getParameters(*Bplus_Corrected_Mass)->Print("v") ; 
    RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),RooFit::Range("low2,high2"),RooFit::Save(true));

    if (nToys==0)
    {


    TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
    firstfit->Divide(2) ;
    RooPlot* frame1 = Bplus_Corrected_Mass->frame(Title("firstfitLowFCME"),Bins(60)) ;
    data->plotOn(frame1,Cut("sample==sample::LowFCME")) ;
    cout<<"PLOT FINISH in fit old"<<endl;
    model->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data),RooFit::Range("low2"),RooFit::NormRange("low2"));
    model->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data),RooFit::Range("high2"),RooFit::NormRange("high2"));
    model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low2"), RooFit::NormRange("low2"));
    model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low2"), RooFit::NormRange("low2"));
    model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low2"),RooFit::NormRange("low2"));
    model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low2"),RooFit::NormRange("low2"));

    model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high2"), RooFit::NormRange("high2"));
    model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high2"), RooFit::NormRange("high2"));
    model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high2"),RooFit::NormRange("high2"));
    model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high2"),RooFit::NormRange("high2"));


    cout<<"PLOT FINISH in fit old 2"<<endl;
    RooPlot* frame2 = Bplus_Corrected_Mass->frame(Title("firstfitHighFCME"),Bins(60)) ;
    data->plotOn(frame2,Cut("sample==sample::HighFCME")) ;
    model->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data),RooFit::Range("low2"),RooFit::NormRange("low2"));
    model->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data),RooFit::Range("high2"),RooFit::NormRange("high2"));

    model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low2"), RooFit::NormRange("low2"));
    model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low2"), RooFit::NormRange("low2"));
    model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low2"),RooFit::NormRange("low2"));
    model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low2"),RooFit::NormRange("low2"));

    model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high2"), RooFit::NormRange("high2"));
    model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high2"), RooFit::NormRange("high2"));
    model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high2"),RooFit::NormRange("high2"));
    model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high2"),RooFit::NormRange("high2"));

    firstfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
    firstfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
    firstfit->SaveAs(("fitTwiceOld2_dataresult_free_fitnumber_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
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


    BF->setConstant(false);
    BF->setVal(0.0);
    BF->setConstant(true);

    cout<<"Fitting dataresult_fixed"<<endl;

    RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Range("low3,high3"),RooFit::Extended(true),RooFit::Save(true));

    if (nToys==0)
    {
    TCanvas* secondfit= new TCanvas("secondfit", "secondfit",800,800);
    secondfit->Divide(2);
    RooPlot* frame3 = Bplus_Corrected_Mass->frame(Title("secondfitlowFCME"),Bins(60)) ;
    data->plotOn(frame3,Cut("sample==sample::LowFCME"));
//    model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
    model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data),RooFit::Range("low3"),RooFit::NormRange("low3"));
    model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data),RooFit::Range("high3"),RooFit::NormRange("high3"));
    model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low3"), RooFit::NormRange("low3"));
    model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low3"), RooFit::NormRange("low3"));
    model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low3"),RooFit::NormRange("low3"));
    model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low3"),RooFit::NormRange("low3"));

    model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high3"), RooFit::NormRange("high3"));
    model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high3"), RooFit::NormRange("high3"));
    model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high3"),RooFit::NormRange("high3"));
    model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high3"),RooFit::NormRange("high3"));
    cout<<"PLOT FINISH 3"<<endl;
    RooPlot* frame4 = Bplus_Corrected_Mass->frame(Title("secondfitHighFCME"),Bins(60)) ;
    data->plotOn(frame4,Cut("sample==sample::HighFCME")) ;
//    model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
    model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data),RooFit::Range("low3"),RooFit::NormRange("low3"));
    model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data),RooFit::Range("high3"),RooFit::NormRange("high3"));
    model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low3"), RooFit::NormRange("low3"));
    model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low3"), RooFit::NormRange("low3"));
    model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low3"),RooFit::NormRange("low3"));
    model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low3"),RooFit::NormRange("low3"));

    model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high3"), RooFit::NormRange("high3"));
    model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high3"), RooFit::NormRange("high3"));
    model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high3"),RooFit::NormRange("high3"));
    model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high3"),RooFit::NormRange("high3"));

    secondfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
    secondfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
    secondfit->SaveAs(("fitTwiceOld2_dataresult_fixed_fitnumber_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
    delete secondfit;
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



   cout<<"Non zero sig hypothesis: "<<dataresult_free->minNll()<<endl;
   cout<<"Zero sig hypo: "<<dataresult_fixed->minNll()<<endl;
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
