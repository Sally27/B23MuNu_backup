#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH2D.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"
#include "TLegend.h"
#include "TProfile.h"
#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TString.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "TH3F.h"
#include <numeric>
#include "TGraph.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <cstring>
#include "TLegend.h"
#include "TStyle.h"
#include "TTreeFormula.h"
#include "TMultiGraph.h"
#include "TString.h"
#include "TPaveText.h"
#include "TLatex.h"
#include "TH1.h"

using namespace std;


double s2d(string str)
{
        double ret;
        istringstream is(str);
        is >> ret;
        return ret;
}

string d2s(double d)
{
        string ret;
        ostringstream os;
        os<<d;
        return os.str();
}

string f2s(float d)
{
        string ret;
        ostringstream os;
        os<<d;
        return os.str();
}


string i2s(int i)
{
        string ret;
        ostringstream os;
        os<<i;
        return os.str();
}


double i2d(int i)
{
        double ret;
        ret = double(i);
        return ret;
}




vector<double> binx(int x){

	vector<double> PArr;


//        PArr.push_back(1.0);

        for(int n=0; n < x+1; ++n)
        {
//        PArr.push_back(i2d(n+1));
        PArr.push_back(double(0.5)+(double(i2d(n)*0.25))); 
        cout<<"This is value of Br"<<PArr.at(n)<<endl;
        }

	return PArr;
}
double round_to_digits(double value, int digits)
{
    if (value == 0.0) // otherwise it will return 'nan' due to the log10() of zero
        return 0.0;

    double factor = pow(10.0, digits - ceil(log10(fabs(value))));
    return round(value * factor) / factor;
}

double computeLimit(TGraph* grobs, double low, string per, double valueofint, string type)
{


        double limit;
	vector<double> x90_values;
	x90_values.push_back(low);
	for (int h(0);h<25;h++)
	{
		double initial=x90_values.at(0);
		double finalval=initial+(h*0.01);
		x90_values.push_back(finalval);
	}
	for (int p(0);p<x90_values.size();p++)
	{

		double pointtoeval=x90_values.at(p);
		cout<< grobs->Eval(pointtoeval)<<endl;
		double newval=grobs->Eval(pointtoeval);
		if(round_to_digits(newval,2)==valueofint)
		{
			cout<<"The upper "<<type<<" limit at"<<per<<" CL with p val "<<newval<<" is "<< pointtoeval<<endl;
                        limit=pointtoeval;
                        break;
		}
	}

        return(limit);

}


vector<double> line95(int x){
        vector<double> PArr;



        for(int n=0; n < x+1; ++n)
        {
        PArr.push_back(0.05);
        cout<<"This is value of line CL 95: "<<PArr.at(n)<<endl;
        }

        return PArr;




}


vector<double> line90(int x){
        vector<double> PArr;

    
        for(int n=0; n < x+1; ++n)
        {
        PArr.push_back(0.1);
        cout<<"This is value of line CL 90: "<<PArr.at(n)<<endl;
        }

        return PArr;



}








vector<double> CLsMed2(string filename, string decaytreename, string variable){

        vector<double> PArr;
        TFile* f = new TFile(filename.c_str());
        TTree* t = (TTree*)f->Get(decaytreename.c_str());



        Double_t getvariable;

        t->SetBranchAddress(variable.c_str(), &getvariable);

        for(int n=0; n < t->GetEntries(); ++n)
        {
        t->GetEntry(n);
        PArr.push_back(getvariable);
        cout<<"This is value of ClsMedian"<<getvariable<<endl;
        }
 

        return PArr;
}





