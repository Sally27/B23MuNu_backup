#include<iostream>
#include<TLegend.h>
#include<TH1F.h>
#include<TFile.h>
#include<TTree.h>
#include<TCanvas.h>
#include<TStyle.h>
#include<string>


using namespace std; 

void plot_tmvaresponse(string filename = "TMVA.root")
{
	TFile* f = new TFile(filename.c_str());
	TTree* t =(TTree*)f->Get("TrainTree");
	Int_t classID;
	t->SetBranchAddress("classID", &classID);
	Float_t BDT; 
	t->SetBranchAddress("BDT", &BDT);

	double binmin(-0.8);
	double binmax(0.6);

	TH1F* hsig = new TH1F("hsig", "", 50, binmin, binmax);
	TH1F* hbkg = new TH1F("hbkg", "", 50, binmin, binmax);

	unsigned long int entries(t->GetEntries());
	int modulo(entries/100);

	for(unsigned long int i(0); i<entries; ++i)
	{
		if(i%modulo == 0) cout<<floor(100*i/(1.*entries))<<"% processed"<<endl;
		t->GetEntry(i);
		if(classID==1) hbkg->Fill(BDT);
		if(classID==0) hsig->Fill(BDT);
	}     

	hbkg->Scale(1./(1.*hbkg->GetBinContent(hbkg->GetMaximumBin())));
	hsig->Scale(1./(1.*hsig->GetBinContent(hsig->GetMaximumBin())));

	hsig->SetFillColor(kBlue-7);
	hsig->SetFillStyle(3375);
	hbkg->SetFillColor(kGreen-7);
	hbkg->SetFillStyle(3357);


	hsig->GetYaxis()->SetRangeUser(0,1.3);
	hbkg->GetYaxis()->SetRangeUser(0,1.3);

	TCanvas* c = new TCanvas("c", "c", 400, 300);

	hsig->GetXaxis()->SetTitle("BDT output");
        //hsig->GetXaxis()->SetTitleSize(0.066);
//        hsig->GetXaxis()->SetTitleOffset(1);
//        hsig->GetXaxis()->SetLabelSize(0.066);
//        hsig->GetXaxis()->SetLabelOffset(0.015);
        hsig->GetXaxis()->SetNdivisions(510);
        hsig->GetYaxis()->SetNdivisions(507);
//        hsig->GetYaxis()->SetTitleSize(0.066);
//        hsig->GetYaxis()->SetTitleOffset(1.);
//        hsig->GetYaxis()->SetLabelSize(0.066);

	hsig->Draw();
	hbkg->Draw("same");	
	//f.Close();




	TTree* t2 =(TTree*)f->Get("TestTree");
	Int_t classID2;
	t2->SetBranchAddress("classID", &classID2);
	Float_t BDT2; 
	t2->SetBranchAddress("BDT", &BDT2);

	TH1F* hsig2 = new TH1F("hsig2", "", 50, binmin, binmax);
	TH1F* hbkg2 = new TH1F("hbkg2", "", 50, binmin, binmax );


	entries = t2->GetEntries();
	modulo = (entries/100);

	for(unsigned long int i(0); i<entries; ++i)
	{
		if(i%modulo == 0) cout<<floor(100*i/(1.*entries))<<"% processed"<<endl;
		t2->GetEntry(i);
		if(classID2==1) hbkg2->Fill(BDT2);
		if(classID2==0) hsig2->Fill(BDT2);
	}     




	hbkg2->Sumw2();
	hsig2->Sumw2();
	hbkg2->Scale(1./(1.*hbkg2->GetBinContent(hbkg2->GetMaximumBin())));
	//hbkg2->SetLineColor(kBlue-7);
	hsig2->Scale(1./(1.*hsig2->GetBinContent(hsig2->GetMaximumBin())));
	//hsig2->SetLineColor(kGreen-7);


        hsig2->SetMarkerColor(kBlue-7);
        hbkg2->SetMarkerColor(kGreen-7);

	TLegend* leg = new TLegend(0.55, 0.78, 0.92, 0.92);
	leg->AddEntry(hsig, "signal, training", "F");
	leg->AddEntry(hbkg,"background, training", "F");
	//leg->AddEntry(hsig2,"sig, test", "PE");
	//leg->AddEntry(hbkg2,"bkg, test", "PE");
        leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetTextSize(0.055);
	
	TLegend* leg2 = new TLegend(0.25, 0.48, 0.62, 0.62);
	//leg->AddEntry(hsig, "sig, training", "F");
	//leg->AddEntry(hbkg,"bkg, training", "F");
	leg2->AddEntry(hsig2,"signal, test", "PE");
	leg2->AddEntry(hbkg2,"background, test", "PE");
        leg2->SetFillColor(0);
	leg2->SetLineColor(0);
	leg2->SetTextSize(0.055);

	leg->Draw();
	leg2->Draw();
	hsig2->Draw("E0same");
	hbkg2->Draw("E0same");	
}
