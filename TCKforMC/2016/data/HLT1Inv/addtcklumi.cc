#include "TH1F.h"
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
#include<algorithm>
#include "TTreeFormula.h"
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TMath.h"
#include<numeric>

using namespace std;



void addtcklumi()
{

	cout<<"Calculating proportions lumi per tck"<<endl;  

	Double_t lumi_per_tck;
        Int_t tck;

        double mylumipertck[] = {12743055.567371905,35008142.329824954,24781890.31062283,78421511.967228904,107004473.5624754,118057866.57099138,23462870.248419043,414618897.99871576,72141162.402934104,22758628.700477272,6864696.8157746429,31699249.866111349,575253262.05024362,44129677.830457017,89725722.716856629,1136242.3102465812};

       vector<double> l_p_tck(mylumipertck, mylumipertck+sizeof(mylumipertck) / sizeof(double) );
        
	int tcks[] = {287905280,287905283,287905284,287905285,288495113,288626185,288691721,288757257,288822793,288822798,288888329,288888334,288888335,288888337,288888338,288888339};
	vector<int>  tckid(tcks, tcks+sizeof(tcks) / sizeof(int) );

       cout<<accumulate(l_p_tck.begin(),l_p_tck.end(),0.0) ;
       double sum(0);
       sum=accumulate(l_p_tck.begin(),l_p_tck.end(),0.0 );


       for(int i(0); i<l_p_tck.size(); i++)
       {
	       cout<<"For "<<tckid.at(i)<<" : "<<100*(l_p_tck.at(i)/sum)<<endl;

       }


return;
}
 
