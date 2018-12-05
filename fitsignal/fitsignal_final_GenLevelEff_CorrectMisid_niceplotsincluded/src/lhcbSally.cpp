#include "TStyle.h"
#include "TPaveText.h"
#include "TText.h"
#include "TLatex.h"
#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"
#include<string>
#include<vector>
#include "THStack.h"
#include "TLine.h"
#include "TPaveText.h"
#include <string>
#include <iostream>
#include <sstream>
#include "TStyle.h"
#include "TROOT.h"

using namespace std;
// all users - please change the name of this file to lhcbSally.C
// Commits to lhcbdocs svn of .C files are not allowed

  // define names for colours
//  Int_t black  = 1;
//  Int_t red    = 2;
//  Int_t green  = 3;
//  Int_t blue   = 4;
//  Int_t yellow = 5; 
//  Int_t magenta= 6;
//  Int_t cyan   = 7;
//  Int_t purple = 9;
  
//TStyle* lhcbSally; // general lhcb style
//TPaveText* lhcbName; // standard lhcb text for plot
//TText* lhcbLabel; // style for Ttext
//TLatex *lhcbLatex; //style for TLatex;


void lhcbSally() {

  Int_t black  = 1;
  Int_t red    = 2;
  Int_t green  = 3;
  Int_t blue   = 4;
  Int_t yellow = 5; 
  Int_t magenta= 6;
  Int_t cyan   = 7;
  Int_t purple = 9;


TStyle* lhcbSally; // general lhcb style
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
//   lhcbSally();
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
  Double_t lhcbTSize    = 0.06; 
  
  // use plain black on white colors
  gROOT->SetStyle("Plain"); 
  lhcbSally= new TStyle("lhcbSally","LHCb plots style");
  
  //lhcbSally->SetErrorX(0); //  don't suppress the error bar along X

  lhcbSally->SetFillColor(0);
  lhcbSally->SetFillStyle(1001);   // solid
  lhcbSally->SetFrameFillColor(0);
  lhcbSally->SetFrameBorderMode(0);
  lhcbSally->SetPadBorderMode(0);
  lhcbSally->SetPadColor(0);
  lhcbSally->SetCanvasBorderMode(0);
  lhcbSally->SetCanvasColor(0);
  lhcbSally->SetStatColor(0);
  lhcbSally->SetLegendBorderSize(0);
  lhcbSally->SetLegendFont(132);
  lhcbSally->SetLegendFillColor(0);

  // If you want the usual gradient palette (blue -> red)
  lhcbSally->SetPalette(1);
  // If you want colors that correspond to gray scale in black and white:
  int colors[8] = {0,5,7,3,6,2,4,1};
  lhcbSally->SetPalette(8,colors);

  // set the paper & margin sizes
  lhcbSally->SetPaperSize(20,26);
  lhcbSally->SetPadTopMargin(0.05);
  lhcbSally->SetPadRightMargin(0.05); // increase for colz plots
  lhcbSally->SetPadBottomMargin(0.16);
  lhcbSally->SetPadLeftMargin(0.14);
  
  // use large fonts
  lhcbSally->SetTextFont(lhcbFont);
  lhcbSally->SetTextSize(lhcbTSize);
  lhcbSally->SetLabelFont(lhcbFont,"x");
  lhcbSally->SetLabelFont(lhcbFont,"y");
  lhcbSally->SetLabelFont(lhcbFont,"z");
  lhcbSally->SetLabelSize(lhcbTSize,"x");
  lhcbSally->SetLabelSize(lhcbTSize,"y");
  lhcbSally->SetLabelSize(lhcbTSize,"z");
  lhcbSally->SetTitleFont(lhcbFont);
  lhcbSally->SetTitleFont(lhcbFont,"x");
  lhcbSally->SetTitleFont(lhcbFont,"y");
  lhcbSally->SetTitleFont(lhcbFont,"z");
  lhcbSally->SetTitleSize(1.2*lhcbTSize,"x");
  lhcbSally->SetTitleSize(1.2*lhcbTSize,"y");
  lhcbSally->SetTitleSize(1.2*lhcbTSize,"z");

  // use medium bold lines and thick markers
  lhcbSally->SetLineWidth(lhcbWidth);
  lhcbSally->SetFrameLineWidth(lhcbWidth);
  lhcbSally->SetHistLineWidth(lhcbWidth);
  lhcbSally->SetFuncWidth(lhcbWidth);
  lhcbSally->SetGridWidth(lhcbWidth);
  lhcbSally->SetLineStyleString(2,"[12 12]"); // postscript dashes
  lhcbSally->SetMarkerStyle(20);
  lhcbSally->SetMarkerSize(1.0);

  // label offsets
  lhcbSally->SetLabelOffset(0.010,"X");
  lhcbSally->SetLabelOffset(0.010,"Y");

  // by default, do not display histogram decorations:
  lhcbSally->SetOptStat(0);  
  //lhcbSally->SetOptStat("emr");  // show only nent -e , mean - m , rms -r
  // full opts at http://root.cern.ch/root/html/TStyle.html#TStyle:SetOptStat
  lhcbSally->SetStatFormat("6.3g"); // specified as c printf options
  lhcbSally->SetOptTitle(0);
  lhcbSally->SetOptFit(0);
  //lhcbSally->SetOptFit(1011); // order is probability, Chi2, errors, parameters
  //titles
  lhcbSally->SetTitleOffset(0.95,"X");
  lhcbSally->SetTitleOffset(0.95,"Y");
  lhcbSally->SetTitleOffset(1.2,"Z");
  lhcbSally->SetTitleFillColor(0);
  lhcbSally->SetTitleStyle(0);
  lhcbSally->SetTitleBorderSize(0);
  lhcbSally->SetTitleFont(lhcbFont,"title");
  lhcbSally->SetTitleX(0.0);
  lhcbSally->SetTitleY(1.0); 
  lhcbSally->SetTitleW(1.0);
  lhcbSally->SetTitleH(0.05);
  
  // look of the statistics box:
  lhcbSally->SetStatBorderSize(0);
  lhcbSally->SetStatFont(lhcbFont);
  lhcbSally->SetStatFontSize(0.05);
  lhcbSally->SetStatX(0.9);
  lhcbSally->SetStatY(0.9);
  lhcbSally->SetStatW(0.25);
  lhcbSally->SetStatH(0.15);

  // put tick marks on top and RHS of plots
  lhcbSally->SetPadTickX(1);
  lhcbSally->SetPadTickY(1);

  // histogram divisions: only 5 in x to avoid label overlaps
  lhcbSally->SetNdivisions(505,"x");
  lhcbSally->SetNdivisions(510,"y");
  
  gROOT->SetStyle("lhcbSally");
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

TStyle* lhcbSally_2(string ok) {

  Int_t black  = 1;
  Int_t red    = 2;
  Int_t green  = 3;
  Int_t blue   = 4;
  Int_t yellow = 5; 
  Int_t magenta= 6;
  Int_t cyan   = 7;
  Int_t purple = 9;


TStyle* lhcbSally; // general lhcb style
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
//   lhcbSally();
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
  Double_t lhcbTSize    = 0.06; 
  
  // use plain black on white colors
  gROOT->SetStyle("Plain"); 
  lhcbSally= new TStyle("lhcbSally","LHCb plots style");
  
  //lhcbSally->SetErrorX(0); //  don't suppress the error bar along X

  lhcbSally->SetFillColor(0);
  lhcbSally->SetFillStyle(1001);   // solid
  lhcbSally->SetFrameFillColor(0);
  lhcbSally->SetFrameBorderMode(0);
  lhcbSally->SetPadBorderMode(0);
  lhcbSally->SetPadColor(0);
  lhcbSally->SetCanvasBorderMode(0);
  lhcbSally->SetCanvasColor(0);
  lhcbSally->SetStatColor(0);
  lhcbSally->SetLegendBorderSize(0);
  lhcbSally->SetLegendFont(132);
  lhcbSally->SetLegendFillColor(0);

  // If you want the usual gradient palette (blue -> red)
  lhcbSally->SetPalette(1);
  // If you want colors that correspond to gray scale in black and white:
  int colors[8] = {0,5,7,3,6,2,4,1};
  lhcbSally->SetPalette(8,colors);

  // set the paper & margin sizes
  lhcbSally->SetPaperSize(20,26);
  lhcbSally->SetPadTopMargin(0.05);
  lhcbSally->SetPadRightMargin(0.05); // increase for colz plots
  lhcbSally->SetPadBottomMargin(0.16);
  lhcbSally->SetPadLeftMargin(0.14);
  
  // use large fonts
  lhcbSally->SetTextFont(lhcbFont);
  lhcbSally->SetTextSize(lhcbTSize);
  lhcbSally->SetLabelFont(lhcbFont,"x");
  lhcbSally->SetLabelFont(lhcbFont,"y");
  lhcbSally->SetLabelFont(lhcbFont,"z");
  lhcbSally->SetLabelSize(lhcbTSize,"x");
  lhcbSally->SetLabelSize(lhcbTSize,"y");
  lhcbSally->SetLabelSize(lhcbTSize,"z");
  lhcbSally->SetTitleFont(lhcbFont);
  lhcbSally->SetTitleFont(lhcbFont,"x");
  lhcbSally->SetTitleFont(lhcbFont,"y");
  lhcbSally->SetTitleFont(lhcbFont,"z");
  lhcbSally->SetTitleSize(1.2*lhcbTSize,"x");
  lhcbSally->SetTitleSize(1.2*lhcbTSize,"y");
  lhcbSally->SetTitleSize(1.2*lhcbTSize,"z");

  // use medium bold lines and thick markers
  lhcbSally->SetLineWidth(lhcbWidth);
  lhcbSally->SetFrameLineWidth(lhcbWidth);
  lhcbSally->SetHistLineWidth(lhcbWidth);
  lhcbSally->SetFuncWidth(lhcbWidth);
  lhcbSally->SetGridWidth(lhcbWidth);
  lhcbSally->SetLineStyleString(2,"[12 12]"); // postscript dashes
  lhcbSally->SetMarkerStyle(20);
  lhcbSally->SetMarkerSize(1.0);

  // label offsets
  lhcbSally->SetLabelOffset(0.010,"X");
  lhcbSally->SetLabelOffset(0.010,"Y");

  // by default, do not display histogram decorations:
  lhcbSally->SetOptStat(0);  
  //lhcbSally->SetOptStat("emr");  // show only nent -e , mean - m , rms -r
  // full opts at http://root.cern.ch/root/html/TStyle.html#TStyle:SetOptStat
  lhcbSally->SetStatFormat("6.3g"); // specified as c printf options
  lhcbSally->SetOptTitle(0);
  lhcbSally->SetOptFit(0);
  //lhcbSally->SetOptFit(1011); // order is probability, Chi2, errors, parameters
  //titles
  lhcbSally->SetTitleOffset(0.95,"X");
  lhcbSally->SetTitleOffset(0.95,"Y");
  lhcbSally->SetTitleOffset(1.2,"Z");
  lhcbSally->SetTitleFillColor(0);
  lhcbSally->SetTitleStyle(0);
  lhcbSally->SetTitleBorderSize(0);
  lhcbSally->SetTitleFont(lhcbFont,"title");
  lhcbSally->SetTitleX(0.0);
  lhcbSally->SetTitleY(1.0); 
  lhcbSally->SetTitleW(1.0);
  lhcbSally->SetTitleH(0.05);
  
  // look of the statistics box:
  lhcbSally->SetStatBorderSize(0);
  lhcbSally->SetStatFont(lhcbFont);
  lhcbSally->SetStatFontSize(0.05);
  lhcbSally->SetStatX(0.9);
  lhcbSally->SetStatY(0.9);
  lhcbSally->SetStatW(0.25);
  lhcbSally->SetStatH(0.15);

  // put tick marks on top and RHS of plots
  lhcbSally->SetPadTickX(1);
  lhcbSally->SetPadTickY(1);

  // histogram divisions: only 5 in x to avoid label overlaps
  lhcbSally->SetNdivisions(505,"x");
  lhcbSally->SetNdivisions(510,"y");
  
  gROOT->SetStyle("lhcbSally");
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

  return(lhcbSally);
 
}

void printLHCb(char* optLR="L", char* optPrelim="Final", string optText="")
//void printLHCb(string optLR="L", string optPrelim="Final", string optText="")
//void printLHCb(string optLR, string optPrelim, string optText)
{
//////////////////////////////////////////////////////////////////////////
// routine to print 'LHCb', 'LHCb Preliminary' on plots 
// options: optLR=L (top left) / R (top right) of plots
//          optPrelim= Final (LHCb), Prelim (LHCb Preliminary), Other
//          optText= text printed if 'Other' specified
////////////////////////////////////////////////////////////////////

	Int_t black  = 1;
	Int_t red    = 2;
	Int_t green  = 3;
	Int_t blue   = 4;
	Int_t yellow = 5; 
	Int_t magenta= 6;
	Int_t cyan   = 7;
	Int_t purple = 9;

        cout<<"LHCb branded"<<endl;


	TStyle* lhcbSally=lhcbSally_2(""); // general lhcb style
	TPaveText* lhcbName; // standard lhcb text for plot
	TText* lhcbLabel; // style for Ttext
	TLatex *lhcbLatex; //style for TLatex;

	if(optLR=="R"){    
		lhcbName = new TPaveText(0.70 - lhcbSally->GetPadRightMargin(),
				0.75, //- lhcbSally->SetPadTopMargin(float(0.05)),
				0.95, //- lhcbSally->GetPadRightMargin(),
				0.85,// - lhcbSally->SetPadTopMargin(float(0.05)),
				"BRNDC");

		cout<<"Choosing position"<<endl;
	}
        else if(optLR=="L"){

		cout<<"Choosing position"<<endl;
		lhcbName = new TPaveText(lhcbSally->GetPadLeftMargin() + 0.05,
				0.87 - lhcbSally->GetPadTopMargin(),
				lhcbSally->GetPadLeftMargin() + 0.20,
				0.95 - lhcbSally->GetPadTopMargin(),
				"BRNDC");
		cout<<"Choosing position"<<endl;
	}
        else if(optLR=="Lplusplus"){

		cout<<"Choosing position"<<endl;
		lhcbName = new TPaveText(lhcbSally->GetPadLeftMargin() + 0.07,
				0.77 - lhcbSally->GetPadTopMargin(),
				lhcbSally->GetPadLeftMargin() + 0.29,
				0.92 - lhcbSally->GetPadTopMargin(),
				"BRNDC");
		cout<<"Choosing position"<<endl;
	}
        else if(optLR=="LLplusplus"){

		cout<<"Choosing position"<<endl;
		lhcbName = new TPaveText(lhcbSally->GetPadLeftMargin() + 0.1,
				0.77 - lhcbSally->GetPadTopMargin(),
				lhcbSally->GetPadLeftMargin() + 0.32,
				0.92 - lhcbSally->GetPadTopMargin(),
				"BRNDC");
		cout<<"Choosing position"<<endl;
	}

        else if(optLR=="middle"){

		cout<<"Choosing position"<<endl;
		lhcbName = new TPaveText(lhcbSally->GetPadLeftMargin() + 0.3,
				0.655555 - lhcbSally->GetPadTopMargin(),
				lhcbSally->GetPadLeftMargin() + 0.52,
				0.8 - lhcbSally->GetPadTopMargin(),
				"BRNDC");
		cout<<"Choosing position"<<endl;
	}

        else if(optLR=="Lplus"){

		cout<<"Choosing position"<<endl;
		lhcbName = new TPaveText(lhcbSally->GetPadLeftMargin() + 0.1,
				0.79 - lhcbSally->GetPadTopMargin(),
				lhcbSally->GetPadLeftMargin() + 0.32,
				0.95 - lhcbSally->GetPadTopMargin(),
				"BRNDC");
		cout<<"Choosing position"<<endl;
	}
	else if(optLR=="RB"){
		lhcbName = new TPaveText(0.70 - lhcbSally->GetPadRightMargin(),
				0.25,// - lhcbSally->SetPadTopMargin(float(0.05)),
				0.95,// - lhcbSally->GetPadRightMargin(),
				0.35,// - lhcbSally->SetPadTopMargin(float(0.05)),
				"BRNDC");
		cout<<"Choosing position"<<endl;
	}

	else if(optLR=="LB"){
		lhcbName = new TPaveText(lhcbSally->GetPadLeftMargin() + 0.1,
				0.45,// - lhcbSally->SetPadTopMargin(float(0.05)),
				lhcbSally->GetPadLeftMargin() + 0.25,// - lhcbSally->GetPadRightMargin(),
				0.65,// - lhcbSally->SetPadTopMargin(float(0.05)),
				"BRNDC");
		cout<<"Choosing position"<<endl;
	}


	else{
		cout << "printLHCb: option unknown " << optLR << endl;   
	}

	if (optPrelim=="Final"){
		lhcbName->AddText("LHCb");
		cout<<"Choosing text"<<endl;
	}
	else if (optPrelim=="Prelim"){
		lhcbName->AddText("#splitline{LHCb}{#scale[1.0]{Preliminary}}");  
		cout<<"Choosing text"<<endl;
	}
	else if (optPrelim=="Uno"){
		lhcbName->AddText("#splitline{LHCb}{#scale[1.0]{Unofficial}}");
		cout<<"Choosing text"<<endl;
	}
	else if (optPrelim=="Simu"){
		lhcbName->AddText("#splitline{LHCb}{#scale[1.0]{Simulation}}");
		cout<<"Choosing text"<<endl;
	}
	else if (optPrelim=="Other"){
		lhcbName->AddText(optText.c_str());
		cout<<"Choosing text"<<endl;
	}
	else{
		cout << "printLHCb: option unknown " << optPrelim << endl;   
		cout<<"Choosing text"<<endl;
	}

//        if (optText!="Other")
//        {
//        if (optPrelim=="Other")
//        } 

	cout<<"Everything fine"<<endl;
	lhcbName->SetFillColor(0);
	lhcbName->SetTextAlign(12);
	lhcbName->SetBorderSize(0);
	lhcbName->Draw();
}

