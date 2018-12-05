#include "lumi.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include "TTree.h"
#include "math.h"
#include <sstream>
#include "TLatex.h"
#include <string>
	lumi::lumi(TFile* _file)
: file(_file)
{
	prescale=1.0;
}

lumi::~lumi()
{}


void lumi::addPrescale(double _prescale)
{
	prescale=_prescale;
}

double lumi::getLumi1()
{
	tree = (TTree*)file->Get("GetIntegratedLuminosity/LumiTuple;1");
	Double_t luminosity;
	tree->SetBranchAddress("IntegratedLuminosity",&luminosity);
	double totallumi=0;
	for (int i=0; i<tree->GetEntries(); i++)
	{
		tree->GetEntry(i);
		totallumi+=luminosity;
	}
	double nearest = floorf(totallumi)*prescale;
	return nearest;
}

double lumi::getLumi2()
{
	tree = (TTree*)file->Get("GetIntegratedLuminosity/LumiTuple");
	if (tree)
	{
		Double_t luminosity;
		tree->SetBranchAddress("IntegratedLuminosity",&luminosity);
		double totallumi=0;
		for (int i=0; i<tree->GetEntries(); i++)
		{
			tree->GetEntry(i);
			totallumi+=luminosity;
		}
		double nearest = (floorf(totallumi/10.0 + 0.5)/100)*prescale;
		return nearest;
	}
	else return getLumi1();
}

void lumi::print(double x, double y)
{
	double luminosity = getLumi2();
	TLatex stuff;
	stuff.SetTextSize(0.055);
	std::ostringstream ss;
	ss << luminosity;
	ss << " fb^{-1}";
	stuff.DrawLatex(x,y,ss.str().c_str());
}



