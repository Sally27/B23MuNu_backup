
void paperPlot(Float_t targetEffic = 0.7, Int_t model = 1) {

  colorPaletteD();
  //gStyle->SetPalette(51,0); //51 for deep sea

  TFile *f = new TFile("EvalUBDT.root");

  ///////////////////////////////
  // 1) plot dalitz efficiency //
  ///////////////////////////////
  TCanvas *c1 = new TCanvas("c1","c1",125,25,600,500);
  gStyle->SetOptStat(0);
  c1->SetFillColor(10);
  c1->SetLeftMargin(0.18);
  c1->SetRightMargin(0.12);
  c1->SetTopMargin(0.05);
  c1->SetBottomMargin(0.18);

  TString algo[2] = {"uBDT","BDT"};
  for(int i=0; i<2; i++){
    TH2F* h = (TH2F*)f->Get(Form("hdalpass_%s_eff%0.2f",algo[i].Data(),targetEffic));
    h->GetXaxis()->SetTitle("m_{ab}^{2}");
    h->GetYaxis()->SetTitle("m_{ac}^{2}");

    float titleSize=0.08;
    float labelSize=0.06;
    h->GetXaxis()->SetNdivisions(5); h->GetXaxis()->SetRangeUser(0.,0.9);
    h->GetXaxis()->SetTitleSize(titleSize);
    h->GetXaxis()->SetLabelSize(labelSize);
    h->GetYaxis()->SetNdivisions(5); h->GetYaxis()->SetRangeUser(0.,0.9);
    h->GetYaxis()->SetTitleSize(titleSize);
    h->GetYaxis()->SetLabelSize(labelSize);
    h->SetMaximum(1.0);
    h->Draw("colz");
    
    gPad->Update();
    TPaletteAxis *palette = (TPaletteAxis*)h->GetListOfFunctions()->FindObject("palette");
    palette->SetX2NDC(0.94);
    palette->SetX1NDC(0.89);
    palette->SetY2NDC(0.95);
    palette->SetY1NDC(0.18);
    
    TLatex *tx1 = new TLatex(0.6,0.75,algo[i]);
    tx1->Draw("same"); tx1->SetTextSize(0.08);
    c1->Print(Form("model%d_%s.pdf",model,algo[i].Data()));
  }

  ///////////////////////
  // 2) plot ROC curve //
  ///////////////////////
  TH1F* h2 = new TH1F("",";Signal Efficiency;Background Rejection",50,0.0,1.0);
  float titleSize=0.07;
  float labelSize=0.06;
  h2->GetXaxis()->SetNdivisions(5);
  h2->GetXaxis()->SetTitleOffset(1.15);
  h2->GetXaxis()->SetTitleSize(titleSize);
  h2->GetXaxis()->SetLabelSize(labelSize);
  h2->GetYaxis()->SetNdivisions(5);
  h2->GetYaxis()->SetTitleOffset(1.15);
  h2->GetYaxis()->SetTitleSize(titleSize);
  h2->GetYaxis()->SetLabelSize(labelSize);
  h2->GetYaxis()->SetRangeUser(0.,1.0);
  h2->Draw();

  TGraph* gROC_UBDT   = (TGraph*)f->Get("ROC_uBDT");
  TGraph* gROC_UBDTnew = new TGraph(gROC_UBDT->GetN());
  TFile *fTMVA = new TFile("TMVAUBDT.root");
  TH1F* hROC_BDT = (TH1F*)fTMVA->Get("Method_BDT/BDT/MVA_BDT_trainingRejBvsS");
  Double_t effic, bkgdRej;
  for(int i=0; i<gROC_UBDT->GetN(); i++){
    gROC_UBDT->GetPoint(i,effic,bkgdRej);
    int iBin = hROC_BDT->FindBin(effic);
    float bdtBkgdRej = hROC_BDT->GetBinContent(iBin);
    //if(bdtBkgdRej<bkgdRej && effic<0.6) {
    //gROC_UBDTnew->SetPoint(i,effic,bdtBkgdRej);
    //}
    //else
    gROC_UBDTnew->SetPoint(i,effic,bkgdRej);
  }
  gROC_UBDTnew->SetLineColor(kBlue); gROC_UBDTnew->SetLineStyle(7);
  gROC_UBDTnew->SetLineWidth(3);
  hROC_BDT->SetLineColor(kBlack); hROC_BDT->SetLineWidth(3);
  hROC_BDT->Draw("c same"); gROC_UBDTnew->Draw("c same");

  TLegend *leg = new TLegend(0.4,0.65,0.65,0.78);
  leg->SetEntrySeparation(0.0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.04);
  leg->SetLineColor(0);
  leg->AddEntry(hROC_BDT,"BDT","l");
  leg->AddEntry(gROC_UBDTnew,"uBDT","l");
  leg->Draw("same");

  c1->Print(Form("model%d_ROC.pdf",model));

  /////////////////////////////
  // 3) plot pmin efficiency //
  /////////////////////////////
  TH1F* h3 = new TH1F("",";Mean Signal Efficiency; Signal Efficiency",50,0.0,1.0);
  float titleSize=0.07;
  float labelSize=0.06;
  h3->GetXaxis()->SetNdivisions(5);
  h3->GetXaxis()->SetTitleOffset(1.15);
  h3->GetXaxis()->SetTitleSize(titleSize);
  h3->GetXaxis()->SetLabelSize(labelSize);
  h3->GetYaxis()->SetNdivisions(5);
  h3->GetYaxis()->SetTitleOffset(1.15);
  h3->GetYaxis()->SetTitleSize(titleSize);
  h3->GetYaxis()->SetLabelSize(labelSize);
  h3->GetYaxis()->SetRangeUser(0.0,1.0);
  h3->Draw();

  TGraph* gLowUBDT  = (TGraph*)f->Get("lowPmin_uBDT");
  TGraph* gHighUBDT = (TGraph*)f->Get("highPmin_uBDT");
  TGraph* gLowBDT   = (TGraph*)f->Get("lowPmin_BDT");
  TGraph* gHighBDT  = (TGraph*)f->Get("highPmin_BDT");
  gLowUBDT->SetLineColor(kBlue); gHighUBDT->SetLineColor(kBlue);
  gLowUBDT->SetLineStyle(7); gHighUBDT->SetLineStyle(9);
  gLowUBDT->Draw("c same"); gHighUBDT->Draw("c same");
  gLowBDT->SetLineColor(kBlack); gHighBDT->SetLineColor(kBlack);
  gLowBDT->SetLineStyle(5);
  gLowBDT->Draw("c same"); gHighBDT->Draw("c same");

  TLine *ln = new TLine(0.0,0.0,1.0,1.0);
  ln->SetLineStyle(2); ln->SetLineWidth(2);
  ln->SetLineColor(kGray);
  ln->Draw("same");

  TLegend *leg = new TLegend(0.2,0.67,0.47,0.94);
  leg->SetEntrySeparation(0.0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.04);
  leg->SetLineColor(0);
  leg->AddEntry(gLowBDT,"BDT Region A","l");
  leg->AddEntry(gHighBDT,"BDT Region B","l");
  leg->AddEntry(gLowUBDT,"uBDT Region A","l");
  leg->AddEntry(gHighUBDT,"uBDT Region B","l");
  leg->Draw("same");

  c1->Print(Form("model%d_pminEffic.pdf",model));

  return;
}

//deep sea cutoff at 0.2
void colorPaletteD() {
  const int Number = 3;
  double Red[Number]    = { 0.0, 0.0, 0.0};  //sent Mike 3:05
  double Green[Number]  = { 0.0, 0.1, 1.0}; //0.06, 0.1, 1.0};
  double Blue[Number]   = { 0.0, 0.5, 1.0};  //0.3, 0.5, 1.0};
  double Length[Number] = { 0.0, 0.15, 1.0};  //0.0, 0.3, 1.0};
  int nb=20;
  TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
}
