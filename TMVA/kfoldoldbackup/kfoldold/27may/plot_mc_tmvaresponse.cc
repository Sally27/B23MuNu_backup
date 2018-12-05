#include<iostream>
#include<TH1F.h>
#include<TFile.h>
#include<TTree.h>
#include<string>
#include<TLegend.h>
#include<TCanvas.h>
#include<TStyle.h>
#include<sstream>

using namespace std;

string int2str(int nbr);

void plot_mc_tmvaresponse(string filename)
{
	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get("BcTuple/DecayTree");

	TH1F* h_a2 = new TH1F("h_a2", "", 100, -0.8, 0.6);
	TH1F* h_psi2s = new TH1F("h_psi2s", "", 100, -0.8, 0.6);

	t->SetBranchStatus("*",0);
	t->SetBranchStatus("frompsi2s",1);
	t->SetBranchStatus("BDT_response",1);

	bool frompsi2s;
	t->SetBranchAddress("frompsi2s", &frompsi2s);
	float BDT_response;
	t->SetBranchAddress("BDT_response", &BDT_response);	

	for(int i(0); i<t->GetEntries();++i)
	{
		t->GetEntry(i);
		if(frompsi2s) h_psi2s->Fill(BDT_response);
		if(!frompsi2s) h_a2->Fill(BDT_response);
	} 

	h_psi2s->SetLineColor(2);



	TCanvas* c = new TCanvas("c","c",800,300);
	gPad->SetBottomMargin(0.15);
        h_a2->GetXaxis()->CenterTitle();
        h_a2->GetXaxis()->SetTitle("BDT output");
        h_a2->GetXaxis()->SetTitleSize(0.066);
        h_a2->GetXaxis()->SetTitleOffset(1);
        h_a2->GetXaxis()->SetLabelSize(0.066);
        h_a2->GetXaxis()->SetLabelOffset(0.015);
        h_a2->GetXaxis()->SetNdivisions(510);
        h_a2->GetYaxis()->SetNdivisions(507);
        h_a2->GetYaxis()->CenterTitle();
        h_a2->GetYaxis()->SetTitleSize(0.066);
        h_a2->GetYaxis()->SetTitleOffset(1.);
        h_a2->GetYaxis()->SetLabelSize(0.066);


	h_a2->SetMarkerStyle(20);
        h_a2->SetMarkerSize(0.7);
        h_a2->SetMarkerColor(4);
        h_psi2s->SetMarkerStyle(20);
        h_psi2s->SetMarkerSize(0.7);
        h_psi2s->SetMarkerColor(2);


	TLegend* leg = new TLegend(0.1, 0.7, 0.35, 0.9);

	string txt_psi2s(int2str(h_psi2s->GetEntries()));
	txt_psi2s = "from #psi(2S) ("+txt_psi2s+" ev.) ";
	string txt_a2(int2str(h_a2 ->GetEntries()));
	txt_a2 = "from a_{1}^{+} ("+txt_a2+" ev.) "; 

	leg->AddEntry(h_a2, txt_a2.c_str());
	leg->AddEntry(h_psi2s, txt_psi2s.c_str());
	leg->SetFillColor(0);
	

	h_a2->Sumw2();
	h_psi2s->Sumw2();
	h_a2->Scale(1./(1.*h_a2->GetBinContent(h_a2->GetMaximumBin())));
	h_psi2s->Scale(1./(1.*h_psi2s->GetBinContent(h_psi2s->GetMaximumBin())));



	gStyle->SetOptStat(0);
	h_a2->Draw("E0");
	h_psi2s->Draw("E0same");
	leg->Draw();
	 	
}

string int2str(int nbr)
{
        stringstream ss;
        ss<<nbr;
        return ss.str();
}
