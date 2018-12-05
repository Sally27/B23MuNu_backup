#include "usefulFunctions.hpp"
#include <algorithm>
#include "reweightingTools.hpp"


vector<double> getUniformBinningPoly(int nbinsX, int nbinsY, vector<double>& xTab, vector< vector<double> >& yTab, TTree* t, string namevarX, string namevarY, string extracut, string nameWeight)
{
	if(extracut == "") extracut = "(1)";
	if(nameWeight == "") nameWeight = "(1)";

	//reset the tables

	xTab.resize(nbinsX+1, 0);

	yTab.resize(nbinsX, vector<double>(nbinsY+1,0));

	//first get X table

	getUniformBinning(nbinsX, &xTab[0], t, namevarX, extracut, nameWeight); 

	string currentCut;

	//get the Y table

	for(int i(0); i<nbinsX; ++i)
	{
		currentCut = namevarX+" > "+d2s(xTab[i])+" && "+ namevarX+" <= "+d2s(xTab[i+1])+" && "+extracut;
		getUniformBinning(nbinsY, &yTab[i][0], t, namevarY, currentCut, nameWeight); 
	}

	//return xlow xup ylow yup

	double xlow(numeric_limits<double>::max());
	double xup(numeric_limits<double>::min());
	double ylow(numeric_limits<double>::max());
	double yup(numeric_limits<double>::min());


	for(int i(0); i<nbinsX+1; ++i)
	{
		if(xTab[i]<xlow) xlow = xTab[i];
		if(xTab[i]>xup) xup = xTab[i];
	}


	for(int i(0); i<nbinsX; ++i)
	{
		for(int j(0); j<nbinsY+1; ++j)
		{
			if(yTab[i][j]<ylow) ylow = yTab[i][j];
			if(yTab[i][j]>yup) yup = yTab[i][j];
		}
	}

	vector<double> ret;


	for(int i(0); i<nbinsX; ++i)
	{
		yTab[i][0] = ylow;
		yTab[i][yTab[i].size()-1] = yup;
	}



	ret.push_back(xlow);
	ret.push_back(xup);
	ret.push_back(ylow);
	ret.push_back(yup);

	return ret;
}

void binTH2Poly(TH2Poly* h, vector<double> const& xTab, vector< vector<double> > const& yTab)
{
	if(xTab.size()-1 != yTab.size())
	{
		cerr<<"error in binTH2Poly: mismatch in the size of the tables"<<endl;
		return;
	}

	for(int i(0); i < xTab.size()-1; ++i)
	{
		for(int j(0); j < yTab.at(i).size()-1; ++j) h->AddBin(xTab.at(i), (yTab.at(i)).at(j), xTab.at(i+1), (yTab.at(i)).at(j+1) );
	}

}

void divide(TH2Poly* eff, TH2Poly* pass, TH2Poly* tot, bool wantBinomial)
{
	ValError veTot;
	ValError vePass;
	ValError veEff;

	for(int i(1); i<=tot->GetNumberOfBins(); ++i)
	{
		veTot.val = tot->GetBinContent(i);
		veTot.err = tot->GetBinError(i);

		vePass.val = pass->GetBinContent(i);
		vePass.err = pass->GetBinError(i);

		if(!wantBinomial) veEff = vePass / veTot;
		if(wantBinomial) veEff = getRatioWeightedBinomial(vePass, veTot);

		eff->SetBinContent(i, veEff.val);
		eff->SetBinError(i, veEff.err);
	}
}

void getUniformBinning(int nbins, double bins[], TTree* t, string namevar, string extracut) //warning, table of size nbins+1
{
	t->SetBranchStatus("*",0);
	setBranchStatusTTF(t, namevar); 
	setBranchStatusTTF(t, extracut); 

	vector<double> varValues;
	TTreeFormula ttf("ttf", namevar.c_str(), t); 

	if(extracut == "") extracut = "1";
	TTreeFormula ttfCut("ttfCut", extracut.c_str(), t);

	for(int i(0); i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		if(ttfCut.EvalInstance()) varValues.push_back(ttf.EvalInstance());
	}

	sort(varValues.begin(), varValues.end());

	double eventsPerBin(varValues.size() / nbins);

	for(int j(0); j < nbins; ++j) bins[j] = varValues[j*eventsPerBin];

	bins[nbins] = varValues[varValues.size()-1];
}

bool sortPair1(pair<double, double> p1, pair<double, double> p2) { return p1.first<p2.first;}

void getUniformBinning(int nbins, double bins[], TTree* t, string namevar, string extracut, string nameWeight) //warning, table of size nbins+1
{
	t->SetBranchStatus("*",0);
	setBranchStatusTTF(t, namevar); 
	setBranchStatusTTF(t, extracut); 
	setBranchStatusTTF(t, nameWeight);

	vector<pair<double, double> > varValues;
	TTreeFormula ttf("ttf", namevar.c_str(), t); 
	if(nameWeight == "") nameWeight = "1";
	TTreeFormula ttfWeight("ttfWeight", nameWeight.c_str(), t);

	if(extracut == "") extracut = "1";
	TTreeFormula ttfCut("ttfCut", extracut.c_str(), t);

	pair<double, double> currentPair;

	double totEvts(0);

	for(int i(0); i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		if(ttfCut.EvalInstance())
		{
			currentPair.first = ttf.EvalInstance();
			currentPair.second = ttfWeight.EvalInstance();
			varValues.push_back(currentPair);
			totEvts += currentPair.second;
		}
	}

	sort(varValues.begin(), varValues.end(), sortPair1);

	double eventsPerBin(totEvts / nbins);

	double currentSum(0);
	int j(1);

	bins[0] = varValues[0].first;

	for(int i(0); i < varValues.size(); ++i)
	{
		currentSum += varValues[i].second;        
		if(currentSum >= eventsPerBin)
		{
			//cout<<"CURRENT SUM: "<<currentSum<<endl;
			currentSum = 0;
			bins[j] = varValues[i].first;
			++j;
		}
	}


	bins[nbins] = varValues[varValues.size()-1].first;
}

void updateWeightsAndFillTable(list<double>& weightTab, TTree* MCTree, int nBins, TTreeFormula* MCTtf, TFile* fileHisto, TH1D* targetHisto, string nameHisto, TTreeFormula* MCTtfExtraCut, string previousMCWeight)
{
	//TH1D MCHisto("MCHisto", "MCHisto", nBins, bins); 
	TH1D MCHisto(*targetHisto);
	MCHisto.Reset();

	int MCEntries(MCTree->GetEntries( (MCTtfExtraCut->GetExpFormula())  ));
	double weightedMCEntries(getEntries(MCTree, (MCTtfExtraCut->GetExpFormula()).Data(), previousMCWeight, false) );
	int MCEntriesTot(MCTree->GetEntries( ));
	MCHisto.Sumw2();

	list<double>::iterator it(weightTab.begin());

	for(int i(0); i<MCEntriesTot; ++i)
	{
		MCTree->GetEntry(i);

		if(MCTtfExtraCut->EvalInstance() )
		{
			MCHisto.Fill(MCTtf->EvalInstance(), *it); 
			++it;
		}
	}

	MCHisto.Scale( 1. / MCHisto.Integral() );

	TH1D weightHisto(*targetHisto); //nameHisto.c_str(), nameHisto.c_str(), nBins, bins);
	weightHisto.Reset();
	weightHisto.SetName(nameHisto.c_str());
	weightHisto.SetTitle(nameHisto.c_str());

	weightHisto.Divide(targetHisto, &MCHisto); 

	cout<<"computing weights for var "<<MCTtf->GetExpFormula()<<endl;

	int whichBin;
	double sumWeights(0); 
	it = weightTab.begin();

	for(int i(0); i<MCEntriesTot; ++i)
	{
		if(i % (MCEntriesTot/10) == 0) cout<<100*i/MCEntriesTot<<"\% "<<flush;

		MCTree->GetEntry(i);
		if(MCTtfExtraCut->EvalInstance() )
		{
			whichBin = weightHisto.FindBin( MCTtf->EvalInstance());
			if(whichBin == 0) whichBin = 1;
			if(whichBin > nBins) whichBin = nBins;
			(*it) *= weightHisto.GetBinContent(whichBin) ;
			sumWeights += *it;
			++it;
		}
	}

	cout<<endl;

	double rescale(weightedMCEntries  / sumWeights);   

	it = weightTab.begin();
	for(; it!=weightTab.end(); ++it) (*it) *= rescale;

	fileHisto->cd();
	weightHisto.Write();

	TCanvas canv ( (nameHisto+"_originPlots" ).c_str(), (nameHisto+"_originPlots" ).c_str(), 600, 600);
	TH1D targetHistoForPlot(*targetHisto);
	targetHistoForPlot.SetName("targetHistoForPlot");
	TH1D MCHistoForPlot(MCHisto);
	MCHistoForPlot.SetName("MCHistoForPlot");

	targetHistoForPlot.Scale( 1./targetHistoForPlot.Integral("width") );
	MCHistoForPlot.Scale( 1./MCHistoForPlot.Integral("width") );
	targetHistoForPlot.SetLineColor(2);
	targetHistoForPlot.SetMarkerColor(2);
	MCHistoForPlot.SetLineColor(4);
	MCHistoForPlot.SetMarkerColor(4);

	TAxis* axis = targetHistoForPlot.GetXaxis();
	axis->SetRangeUser( axis->GetBinLowEdge(1), axis->GetBinLowEdge(axis->GetLast()) );

	divideByBinWidth(&targetHistoForPlot);
	divideByBinWidth(&MCHistoForPlot);

	targetHistoForPlot.Draw("E1");
	MCHistoForPlot.Draw("E1same");

	canv.Write();
}



void updateWeightsAndFillTable2D(list<double>& weightTab, TTree* MCTree, int nBins, TTreeFormula* var1Ttf, TTreeFormula* var2Ttf, TFile* fileHisto, TH2Poly* targetHisto, string nameHisto, TTreeFormula* MCTtfExtraCut, string previousMCWeight)
{
	TH2Poly* MCHisto = (TH2Poly*)targetHisto->Clone("MCHisto");
	//TH1D MCHisto(*targetHisto);
	MCHisto->Reset("");

	int MCEntries(MCTree->GetEntries( (MCTtfExtraCut->GetExpFormula())  ));
	double weightedMCEntries(getEntries(MCTree, (MCTtfExtraCut->GetExpFormula()).Data(), previousMCWeight, false) );
	int MCEntriesTot(MCTree->GetEntries());
	MCHisto->Sumw2();

	list<double>::iterator it(weightTab.begin());

	for(int i(0); i<MCEntriesTot; ++i)
	{
		MCTree->GetEntry(i);

		if(MCTtfExtraCut->EvalInstance() )
		{
			MCHisto->Fill(var1Ttf->EvalInstance(), var2Ttf->EvalInstance(), *it); 
			++it;
		}

	}

	double integral(MCHisto->Integral());
	scalePoly( MCHisto, 1. / integral );

	//TH1D weightHisto(*targetHisto); 
	TH2Poly* weightHisto = (TH2Poly*)targetHisto->Clone(nameHisto.c_str());
	weightHisto->Reset("");
	weightHisto->SetTitle(nameHisto.c_str());

	divide(weightHisto, targetHisto, MCHisto, false);

	cout<<"computing weights for 2 vars "<<var1Ttf->GetExpFormula()<<" X "<<var2Ttf->GetExpFormula()<<endl;

	int whichBin;
	double sumWeights(0); 
	it = weightTab.begin();

	for(int i(0); i<MCEntriesTot; ++i)
	{
		if(i % (MCEntriesTot/10) == 0) cout<<100*i/MCEntriesTot<<"\% "<<flush;

		MCTree->GetEntry(i);
		if(MCTtfExtraCut->EvalInstance() )
		{
			whichBin = weightHisto->FindBin( var1Ttf->EvalInstance(), var2Ttf->EvalInstance());
			if(whichBin < 0) (*it) *= 1.0;
			if(whichBin >= 0) (*it) *= weightHisto->GetBinContent(whichBin) ;
			sumWeights += *it;
			++it;
		}
	}

	cout<<endl;

	double rescale(weightedMCEntries  / sumWeights);   

	it = weightTab.begin();
	for(; it!=weightTab.end(); ++it) (*it) *= rescale;

	fileHisto->cd();
	weightHisto->Write();

	delete MCHisto;
	delete weightHisto;

	//   no plots of origin histos in 2D

	//   TCanvas canv ( (nameHisto+"_originPlots" ).c_str(), (nameHisto+"_originPlots" ).c_str(), 600, 600);
	//   TH1D targetHistoForPlot(*targetHisto);
	//   targetHistoForPlot.SetName("targetHistoForPlot");
	//   TH1D MCHistoForPlot(MCHisto);
	//   MCHistoForPlot.SetName("MCHistoForPlot");
	//
	//   targetHistoForPlot.Scale( 1./targetHistoForPlot.Integral("width") );
	//   MCHistoForPlot.Scale( 1./MCHistoForPlot.Integral("width") );
	//   targetHistoForPlot.SetLineColor(2);
	//   targetHistoForPlot.SetMarkerColor(2);
	//   MCHistoForPlot.SetLineColor(4);
	//   MCHistoForPlot.SetMarkerColor(4);
	//
	//   TAxis* axis = targetHistoForPlot.GetXaxis();
	//   axis->SetRangeUser( axis->GetBinLowEdge(1), axis->GetBinLowEdge(axis->GetLast()) );
	//
	//   divideByBinWidth(&targetHistoForPlot);
	//   divideByBinWidth(&MCHistoForPlot);
	//
	//   targetHistoForPlot.Draw("E1");
	//   MCHistoForPlot.Draw("E1same");
	//
	//   canv.Write();
}



void getWeights(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, vector<string> varsReweight, int nIter,
		vector<string> fileHistoNames, vector<string> criteria, string dataWeightName, string extracut, string previousMCWeight)
{
	getWeights(fileMCTree,fileTargetTree, nameMCTree, nameTargetTree, nBins, varsReweight, nIter,
			fileHistoNames, criteria, dataWeightName ,  extracut, extracut, previousMCWeight);
}



void getWeights(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, vector<string> varsReweight, int nIter,
		vector<string> fileHistoNames, vector<string> criteria, string dataWeightName, string extraMCCut, string extraTargetCut, string previousMCWeight)
{
	if( criteria.size() != fileHistoNames.size() )
	{
		cerr<<"ERROR: in function getWeights, mismatch in the number of criteria."<<endl;
		return;
	}

	string newExtraMCCut;
	string newExtraTargetCut;

	string fileHistoName;
	for(int i(0); i<criteria.size(); ++i)
	{
		newExtraMCCut = criteria[i];
		newExtraTargetCut = criteria[i];
		if(extraMCCut != "") newExtraMCCut += ( " && "+extraMCCut );  
		if(extraTargetCut != "") newExtraTargetCut += ( " && "+extraTargetCut );  

		cout<<"Getting the weights for criterium "<<criteria[i]<<endl; 
		fileHistoName = fileHistoNames[i];
		getWeights(fileMCTree, fileTargetTree, nameMCTree, nameTargetTree, nBins, varsReweight, nIter, fileHistoName, dataWeightName, newExtraMCCut, newExtraTargetCut, previousMCWeight);
	}
}


void getWeights(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, vector<string> varsReweight, int nIter,
		string fileHistoName, string dataWeightName, string extracut, string previousMCWeight)
{

	getWeights(fileMCTree, fileTargetTree, nameMCTree, nameTargetTree, nBins, varsReweight, nIter,
			fileHistoName, dataWeightName, extracut, extracut, previousMCWeight);
}

void getWeights(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, vector<string> varsReweight, int nIter,
		string fileHistoName, string dataWeightName, string extraMCCut, string extraTargetCut, string previousMCWeight)
{
	cout<<"Computing the MC correction weights..."<<endl;

	//Prepare the trees

	TFile MCFile(fileMCTree.c_str(), "UPDATE");
	TTree* MCTree = (TTree*)MCFile.Get(nameMCTree.c_str());

	TFile targetFile(fileTargetTree.c_str());
	TTree* targetTree = (TTree*)targetFile.Get(nameTargetTree.c_str());

	if(MCTree == 0 || targetTree == 0)
	{
		cerr<<"ERROR: in getWeights, no tree found"<<endl;
		return;
	}

	//declare some useful shit

	if(extraMCCut == "") extraMCCut = "1";
	if(extraTargetCut == "") extraTargetCut = "1";

	int MCEntries(MCTree->GetEntries(extraMCCut.c_str()));
	int MCEntriesTot(MCTree->GetEntries());
	double WeightedMCEntries(getEntries(MCTree, extraMCCut.c_str(), previousMCWeight) );
	double WeightedMCEntriesTot(getEntries(MCTree, "", previousMCWeight) );
	int targetEntries(targetTree->GetEntries(extraTargetCut.c_str()));
	int targetEntriesTot(targetTree->GetEntries());
	int nVars(varsReweight.size());

	//Prepare  the binning tables and empty target histos

	cout<<"Preparing uniform bins..."<<endl;

	double binTabs[nBins+1];
	vector<TH1D*> targetHistos;//(nVars, 0);

	for(int i(0); i<nVars; ++i)
	{
		getUniformBinning( nBins, binTabs, MCTree, varsReweight[i], extraMCCut);
		targetHistos.push_back(new TH1D( ("dataDistribution"+i2s(i)).c_str(), ("dataDistribution"+i2s(i)).c_str(), nBins, binTabs ));
		targetHistos[i] -> Sumw2();
	}


	//Prepare TTree formulae

	vector<TTreeFormula*> MCTtfVec;//(nVars,0);
	vector<TTreeFormula*> targetTtfVec;//(nVars, 0);

	MCTree->SetBranchStatus("*", 0); 
	targetTree->SetBranchStatus("*", 0); 

	for(int i(0); i<nVars; ++i)
	{
		setBranchStatusTTF(MCTree, varsReweight[i]);
		setBranchStatusTTF(targetTree, varsReweight[i]);
		setBranchStatusTTF(MCTree, extraMCCut.c_str());
		setBranchStatusTTF(targetTree, extraTargetCut.c_str());
		MCTtfVec.push_back( new TTreeFormula( ("formulaMC"+i2s(i)).c_str(), (varsReweight[i]).c_str(), MCTree) );
		targetTtfVec.push_back( new TTreeFormula( ("formulaData"+i2s(i)).c_str(), (varsReweight[i]).c_str(), targetTree) );
	}

	//prepare formulae for the extracut 

	TTreeFormula MCTtfExtraCut("MCTtfExtraCut", extraMCCut.c_str(), MCTree );
	TTreeFormula targetTtfExtraCut( "targetTtfExtraCut", extraTargetCut.c_str(), targetTree ); 



	//link the target weights (sweights)

	double dataWeight(1.);
	if(dataWeightName != "") 
	{
		targetTree->SetBranchStatus(dataWeightName.c_str(), 1);
		targetTree->SetBranchAddress(dataWeightName.c_str(), &dataWeight);
	}



	//fill the target histos 

	cout<<"Filling of the target histograms..."<<endl;

	double temp;
	for(int jVar(0); jVar < nVars; ++jVar)
	{
		for(int i(0); i < targetEntriesTot; ++i)
		{
			targetTree->GetEntry(i);      
			if(targetTtfExtraCut.EvalInstance() )
			{
				temp = targetTtfVec[jVar] -> EvalInstance();
				targetHistos[jVar] -> Fill(temp, dataWeight);
			}
		}
		targetHistos[jVar] -> Scale( 1./targetHistos[jVar]->Integral() );
	}

	//prepare where to save the reweighting histos

	TFile fileHisto(fileHistoName.c_str(), "RECREATE");

	//if the MC tree has previously been weighted, the weight table has to be filled with the initial weights

	cout<<"Get the MC initial weights..."<<endl;

	list<double> weights(MCEntries,1.);

	if( previousMCWeight != "" )
	{
		setBranchStatusTTF(MCTree, previousMCWeight);
		TTreeFormula MCTtfPreviousWeight("MCTtfPreviousWeight", previousMCWeight.c_str(),  MCTree );

		list<double>::iterator it(weights.begin());

		for(int i(0); i < MCEntriesTot; ++i)
		{
			MCTree->GetEntry(i);
			if(MCTtfExtraCut.EvalInstance())
			{
				*it = MCTtfPreviousWeight.EvalInstance();
				++it;
			}
		}
	}


	//Prepare the weight of the tree 

	cout<<"Computation of the weights..."<<endl;

	for(int iIter(0); iIter < nIter; ++iIter)
	{
		for(int jVar(0); jVar < nVars; ++jVar)
		{
			updateWeightsAndFillTable(weights, MCTree, nBins,  MCTtfVec[jVar],
					&fileHisto, targetHistos[jVar], ("weights_Iter"+i2s(iIter)+"Var"+i2s(jVar)).c_str(), &MCTtfExtraCut, previousMCWeight);
		}
	}

	for(int i(0); i<nVars; ++i)
	{
		delete MCTtfVec[i];
		delete targetTtfVec[i];
		delete targetHistos[i];
	}

	//   fReweightedTree.Close();
	MCFile.Close();
	targetFile.Close();
	fileHisto.Close();
}  


void applyWeightsToTree( string fileTree, string nameTree, vector<string> varsReweight, int nIter, string nameHistoFile, string extracut, string MCNewWeightName, string previousWeightName, bool keepNormalisationSame)
{
	//Get the Tree

	TFile f(fileTree.c_str());//, "UPDATE");
	TTree* t = (TTree*)f.Get(nameTree.c_str());      

	if(!t)
	{
		cerr<<"ERROR: in function applyWeightsToTree, no tree found"<<endl;
		f.Close();
		return;
	}

	int nEntries( t->GetEntries(extracut.c_str()));
	int nEntriesTot( t->GetEntries());
	int nVars(varsReweight.size());

	double nEntriesWeighted( getEntries(t, extracut, previousWeightName) );

	//Prepare TTreeFormula pointing to the list of variables

	cout<<"Preparing formulae..."<<endl;

	vector<TTreeFormula*> vecTtfs;//(nVars, 0);

	t->SetBranchStatus("*", 0); 
	for(int i(0); i<nVars; ++i)
	{
		setBranchStatusTTF(t, varsReweight[i]);
		vecTtfs.push_back( new TTreeFormula( ("formula"+i2s(i)).c_str(), (varsReweight[i]).c_str(), t) );
	}
	//prepare ttreeformula to perform the cut


	if( extracut == "" ) extracut = "1";
	else setBranchStatusTTF(t, extracut);

	TTreeFormula ttf("ttf", extracut.c_str(), t);


	//if the MC tree has previously been weighted, the weight table has to be filled with the initial weights


	list<double> weights(nEntries,1.);
	list<double>::iterator it(weights.begin());

	if( previousWeightName != "" )
	{
		setBranchStatusTTF(t, previousWeightName);
		TTreeFormula MCTtfPreviousWeight("MCTtfPreviousWeight", previousWeightName.c_str(), t );

		for(int i(0); i < nEntriesTot; ++i)
		{
			t->GetEntry(i);
			if( ttf.EvalInstance() )
			{
				*it = MCTtfPreviousWeight.EvalInstance();
				++it;
			}
		}
	}


	//Fill the weight table

	cout<<"Filling the weights..."<<endl;

	it = weights.begin();


	TFile fHisto(nameHistoFile.c_str());
	TH1D* histo;


	int whichBin(0);
	int nBins;

	for(int iIter(0); iIter < nIter; ++iIter)
	{
		for(int iVar(0); iVar<nVars;  ++iVar)
		{
			histo = (TH1D*)fHisto.Get( ("weights_Iter"+i2s(iIter)+"Var"+i2s(iVar)).c_str() ); 
			nBins = histo->GetXaxis()->GetNbins();
			if(!histo)
			{
				cerr<<"ERROR: in function applyWeightsToTree, no weight histo found. Exit."<<endl;
				f.Close();
				fHisto.Close();
				return;
			}
			cout<<"Correcting weights according to "<<histo->GetTitle()<<"..."<<endl;

			it = weights.begin();

			for(int iTree(0); iTree<nEntriesTot; ++iTree)
			{
				if(iTree % (nEntriesTot/10) == 0) cout<<100*iTree/nEntriesTot<<"\% "<<flush;
				t->GetEntry(iTree);
				if(ttf.EvalInstance())
				{
					whichBin = histo->FindBin( vecTtfs[iVar]->EvalInstance());
					if(whichBin == 0) whichBin = 1;
					if(whichBin > nBins) whichBin = nBins;
					(*it) *= histo->GetBinContent(whichBin) ;
					++it;
				}
			}
		}
	}

	//Normalise the weights

	if(keepNormalisationSame)
	{
		double sumWeights(0);

		it = weights.begin();
		for(; it!=weights.end(); ++it) sumWeights += *it;

		double rescale(nEntriesWeighted  / sumWeights);   

		it = weights.begin();
		for(; it!=weights.end(); ++it) (*it) *= rescale;
	}

	//filling the tree with the weights 


	f.cd();
	cout<<"Filling the tree with the computed weights..."<<endl;

	t->SetBranchStatus("*", 1);
	cout<<"====================="<<endl<<"Errors from TTreeFormula don't matter from here"<<endl;
	t->SetBranchStatus(MCNewWeightName.c_str(), 0);
	cout<<"====================="<<endl<<"From now on errors matter"<<endl;

	string fileTreeInter(fileTree);
	fileTreeInter.insert(fileTreeInter.size()-5, "ToErase");

	TFile f2(fileTreeInter.c_str(), "RECREATE");
	TTree* reweightedTree = t->CloneTree(0);   
	double dataMCWeight;
	reweightedTree->Branch(MCNewWeightName.c_str(), &dataMCWeight, (MCNewWeightName+"/d").c_str());

	it = weights.begin();

	for(int i(0); i < t->GetEntries(); ++i)
	{
		if(i % (nEntriesTot/10) == 0) cout<<100*i/nEntriesTot<<"\% "<<flush;

		t->GetEntry(i);
		if(ttf.EvalInstance())
		{
			dataMCWeight = *it;
			reweightedTree->Fill();
			++it;
		}
		if(!ttf.EvalInstance())
		{
			dataMCWeight = 0;
			reweightedTree->Fill();
		}
	}
	cout<<endl<<" done!"<<endl;

	reweightedTree->Write("", TObject::kOverwrite);

	//close everything
	//
	f.Close();
	fHisto.Close();
	f2.Close();

	rename(fileTreeInter.c_str(), fileTree.c_str());
}

void applyWeightsToTree( string fileTree, string nameTree,  vector<string> varsReweight, int nIter, vector<string> namesHistoFile, vector<string> criteria, string extracut,
		string MCNewWeightName, string previousWeightName, bool keepNormalisationSame)
{
	//Check the criteria:

	if(namesHistoFile.size() != criteria.size() )
	{
		cerr<<"ERROR: in function applyWeightsToTree, the number of criteria don't match number of files";
		return;
	}
	int nCriteria(criteria.size());

	//Get the Tree

	TFile f(fileTree.c_str());//, "UPDATE");
	TTree* t = (TTree*)f.Get(nameTree.c_str());

	if(!t)
	{
		cerr<<"ERROR: in function applyWeightsToTree, no tree found"<<endl;
		f.Close();
		return;
	}

	int nEntries( t->GetEntries(extracut.c_str()));
	int nEntriesTot( t->GetEntries());
	int nVars(varsReweight.size());

	//Prepare TTreeFormula pointing to the list of variables

	cout<<"Preparing formulae..."<<endl;

	vector<TTreeFormula*> vecTtfs;//(nVars, 0);

	t->SetBranchStatus("*", 0);
	for(int i(0); i<nVars; ++i)
	{
		setBranchStatusTTF(t, varsReweight[i]);
		vecTtfs.push_back( new TTreeFormula( ("formula"+i2s(i)).c_str(), (varsReweight[i]).c_str(), t) );
	}

	//prepare ttreeformula to select histo

	vector<TTreeFormula*> criteriaTTFs;
	for(int i(0); i<nCriteria; ++i)
	{
		setBranchStatusTTF(t, criteria[i]);
		criteriaTTFs.push_back( new TTreeFormula( ("criteria"+i2s(i)).c_str(), (criteria[i]).c_str(), t) );
	}

	vector<bool> criteriaPassed(nCriteria, false );


	//prepare ttreeformula to perform the cut

	if( extracut == "" ) extracut = "1";
	else setBranchStatusTTF(t, extracut);

	TTreeFormula ttf("ttf", extracut.c_str(), t);

	//if the MC tree has previously been weighted, the weight table has to be filled with the initial weights

	list<double> weights(nEntries,1.);
	list<double>::iterator it(weights.begin());

	if(previousWeightName == "") previousWeightName = "1";
	setBranchStatusTTF(t, previousWeightName);
	TTreeFormula MCTtfPreviousWeight("MCTtfPreviousWeight", previousWeightName.c_str(), t );


	if( previousWeightName != "1" )
	{
		for(int i(0); i < nEntriesTot; ++i)
		{
			t->GetEntry(i);
			if( ttf.EvalInstance() )
			{
				*it = MCTtfPreviousWeight.EvalInstance();
				++it;
			}
		}
	}

	//Fill the weight table

	cout<<"Filling the weights..."<<endl;

	vector<TFile*> fHistos(nCriteria, NULL);
	for(int i(0); i<nCriteria; ++i)  fHistos[i] = new TFile( (namesHistoFile[i]).c_str() );

	vector<TH1D*> histos(nCriteria, NULL);
	TH1D* histo(0);


	int whichBin(0);
	int nBins;
	int nTrueCriteria(0);
	int goodCriteria(0);

	vector<double> sumWeightsCats(nCriteria, 0.); // these are used to normalise the weights in each trigger category
	vector<double> sumNCats(nCriteria, 0.);
	vector<double> sumNCatsWeighted(nCriteria, 0.);

	for(int iIter(0); iIter < nIter; ++iIter)
	{
		for(int iVar(0); iVar<nVars;  ++iVar)
		{
			//first must load all the histos

			for(int i(0); i < nCriteria; ++i)
			{
				histos[i] = (TH1D*)fHistos[i]->Get( ("weights_Iter"+i2s(iIter)+"Var"+i2s(iVar)).c_str() );
				histos[i]->SetName( ("weights_Iter"+i2s(iIter)+"Var"+i2s(iVar)+"Criteria"+i2s(i)).c_str() );
				if(!histos[i])
				{
					cerr<<"ERROR: in function applyWeightsToTree, error loading one histo. Exit."<<endl;
					f.Close();
					return;
				}
			}

			cout<<"Correcting weights according to "<<histos[0]->GetTitle()<<"..."<<endl;

			it = weights.begin();

			for(int iTree(0); iTree<nEntriesTot; ++iTree)
			{
				if(iTree % (nEntriesTot/10) == 0) cout<<100*iTree/nEntriesTot<<"\% "<<flush;
				t->GetEntry(iTree);

				//first must get the histos corresponding to the right criterium

				nTrueCriteria = 0;

				for(int i(0); i<nCriteria; ++i)
				{
					if( criteriaTTFs[i] -> EvalInstance() )
					{
						++ nTrueCriteria;
						goodCriteria = i;
					}
				}

				if(nTrueCriteria != 1)
				{
					cerr<<"ERROR: CHRISTUS BITUS!!!!! Problem with the number of good criteria: nTrueCriteria = "<<nTrueCriteria<<". You are fucked! F-U-C-K-E-D!!!!"<<endl;
					f.Close();
					return;
				}

				histo = histos[goodCriteria];
				nBins = histo->GetXaxis()->GetNbins();

				//Fill the table

				if(ttf.EvalInstance())

				{
					whichBin = histo->FindBin( vecTtfs[iVar]->EvalInstance());
					if(whichBin == 0) whichBin = 1;
					if(whichBin > nBins) whichBin = nBins;
					(*it) *= histo->GetBinContent(whichBin) ;

					//if this is the final step of the loop, the normalisation of the weights has to be prepared

					if(iIter == nIter-1 && iVar == nVars-1)
					{
						sumWeightsCats[goodCriteria] += (*it);
						sumNCats[goodCriteria]++;
						sumNCatsWeighted[goodCriteria] += MCTtfPreviousWeight.EvalInstance();
					}

					++it;
				}
			}
		}
	}

	//Getting the weights' normalisations

	vector<double> normalisationCats(nCriteria, 0);
	for(int i(0); i<nCriteria; ++i) normalisationCats[i] = sumWeightsCats[i] / sumNCatsWeighted[i];

	//filling the tree with the weights 

	string fileTreeInter(fileTree);
	fileTreeInter.insert(fileTreeInter.size()-5, "ToErase");

	f.cd();
	cout<<"Filling the tree with the computed weights..."<<endl;

	t->SetBranchStatus("*", 1);
	cout<<"====================="<<endl<<"Errors from TTreeFormula don't matter from here"<<endl;
	t->SetBranchStatus(MCNewWeightName.c_str(), 0);
	cout<<"====================="<<endl<<"From now on errors matter"<<endl;

	TFile f2(fileTreeInter.c_str(), "RECREATE");

	TTree* reweightedTree = t->CloneTree(0);
	double dataMCWeight;
	reweightedTree->Branch(MCNewWeightName.c_str(), &dataMCWeight, (MCNewWeightName+"/d").c_str());

	it = weights.begin();

	for(int i(0); i < t->GetEntries(); ++i)
	{
		if(i % (nEntriesTot/10) == 0) cout<<100*i/nEntriesTot<<"\% "<<flush;

		t->GetEntry(i);


		{
			for(int i(0); i<nCriteria; ++i)
			{
				if( criteriaTTFs[i] -> EvalInstance() ) goodCriteria = i;
			}

			if(keepNormalisationSame) dataMCWeight = (*it)/normalisationCats[goodCriteria];
			if(!keepNormalisationSame) dataMCWeight = (*it);
			reweightedTree->Fill();
			++it;
		}
		if(!ttf.EvalInstance())
		{
			dataMCWeight = 0;
			reweightedTree->Fill();
		}
	}
	cout<<endl<<" done!"<<endl;

	reweightedTree->Write("", TObject::kOverwrite);

	//close everything

	f.Close();
	f2.Close();

	for(int i(0); i<nCriteria; ++i)
	{
		if(criteriaTTFs[i] != NULL) delete criteriaTTFs[i];
		fHistos[i] -> Close();
		if(fHistos[i] != NULL) delete fHistos[i];
	}
	for(int i(0); i<nVars; ++i)
	{
		if(vecTtfs[i] != NULL) delete vecTtfs[i];
	}

	rename(fileTreeInter.c_str(), fileTree.c_str());
}


void scalePoly(TH2Poly* h, double scaleFactor)
{
	for(int i(1); i<=h->GetNumberOfBins(); ++i)
	{
		h->SetBinContent(i, scaleFactor*h->GetBinContent(i));
		h->SetBinError(i, scaleFactor*h->GetBinError(i));
	}
}


void applyWeightsToTree2D( string fileTree, string nameTree, vector<string> varsReweight, int nIter, string nameHistoFile, string extracut, string MCNewWeightName, string previousWeightName, bool keepNormalisationSame)
{
	vector<string> criteria(1, "(1)"); 
	vector<string> namesHistoFiles(1, nameHistoFile);

	applyWeightsToTree2D( fileTree, nameTree,  varsReweight, nIter, namesHistoFiles, criteria, extracut, 
			MCNewWeightName, previousWeightName, keepNormalisationSame);
}

void applyWeightsToTree2D( string fileTree, string nameTree,  vector<string> varsReweight, int nIter, vector<string> namesHistoFile, vector<string> criteria, string extracut, 
		string MCNewWeightName, string previousWeightName, bool keepNormalisationSame)
{
	//Check the criteria:

	if(namesHistoFile.size() != criteria.size() )
	{
		cerr<<"ERROR: in function applyWeightsToTree2D, the number of criteria don't match number of files";
		return;
	}
	int nCriteria(criteria.size());

	//Get the Tree

	TFile f(fileTree.c_str());//, "UPDATE");
	TTree* t = (TTree*)f.Get(nameTree.c_str());      

	if(!t)
	{
		cerr<<"ERROR: in function applyWeightsToTree2D, no tree found"<<endl;
		f.Close();
		return;
	}

	int nEntries( t->GetEntries(extracut.c_str()));
	int nEntriesTot( t->GetEntries());
	int nVars(varsReweight.size());

	//Prepare TTreeFormula pointing to the list of variables

	cout<<"Preparing formulae..."<<endl;

	string var2D1, var2D2;
	bool is2D;

	vector<TTreeFormula*> vecTtfs1(nVars, NULL);
	vector<TTreeFormula*> vecTtfs2(nVars, NULL);

	vector<string> varsReweight1(nVars, ""); 
	vector<string> varsReweight2(nVars, "");

	for(int i(0); i<nVars; ++i)
	{
		is2D = separateString(varsReweight[i], var2D1, var2D2);
		if(!is2D) varsReweight1[i]  =  varsReweight[i];
		if(is2D)
		{
			varsReweight1[i] = var2D1;
			varsReweight2[i] = var2D2;
		}
	}

	t->SetBranchStatus("*", 0); 

	for(int i(0); i<nVars; ++i)
	{
		setBranchStatusTTF(t, varsReweight1[i]);
		vecTtfs1[i] =  new TTreeFormula( ("formula"+i2s(i)).c_str(), (varsReweight1[i]).c_str(), t);
		if(varsReweight2[i] != "")
		{
			setBranchStatusTTF(t, varsReweight2[i]);
			vecTtfs2[i] =  new TTreeFormula( ("formula2D2"+i2s(i)).c_str(), (varsReweight2[i]).c_str(), t);
		}
	}

	//prepare ttreeformula to select histo

	vector<TTreeFormula*> criteriaTTFs;
	for(int i(0); i<nCriteria; ++i)
	{
		setBranchStatusTTF(t, criteria[i]);
		criteriaTTFs.push_back( new TTreeFormula( ("criteria"+i2s(i)).c_str(), (criteria[i]).c_str(), t) );
	}

	vector<bool> criteriaPassed(nCriteria, false );

	//prepare ttreeformula to perform the cut

	if( extracut == "" ) extracut = "1";
	else setBranchStatusTTF(t, extracut);

	TTreeFormula ttf("ttf", extracut.c_str(), t);

	//if the MC tree has previously been weighted, the weight table has to be filled with the initial weights

	list<double> weights(nEntries,1.);
	list<double>::iterator it(weights.begin());

	if(previousWeightName == "") previousWeightName = "1";
	setBranchStatusTTF(t, previousWeightName);
	TTreeFormula MCTtfPreviousWeight("MCTtfPreviousWeight", previousWeightName.c_str(), t );


	if( previousWeightName != "1" )
	{
		for(int i(0); i < nEntriesTot; ++i)
		{
			t->GetEntry(i);
			if( ttf.EvalInstance() )
			{
				*it = MCTtfPreviousWeight.EvalInstance();
				++it;
			}
		}
	}

	//Fill the weight table

	cout<<"Filling the weights..."<<endl;

	vector<TFile*> fHistos(nCriteria, NULL); 
	for(int i(0); i<nCriteria; ++i)  fHistos[i] = new TFile( (namesHistoFile[i]).c_str() );

	vector<TH1*> histos(nCriteria, NULL);
	TH1* histo(NULL);


	int whichBin(0);
	int nBins;
	int nTrueCriteria(0);
	int goodCriteria(0);

	vector<double> sumWeightsCats(nCriteria, 0.); // these are used to normalise the weights in each trigger category
	vector<double> sumNCats(nCriteria, 0.);
	vector<double> sumNCatsWeighted(nCriteria, 0.);

	for(int iIter(0); iIter < nIter; ++iIter)
	{
		for(int iVar(0); iVar<nVars;  ++iVar)
		{
			//first must load all the histos

			for(int i(0); i < nCriteria; ++i)
			{
				histos[i] = (TH1*)fHistos[i]->Get( ("weights_Iter"+i2s(iIter)+"Var"+i2s(iVar)).c_str() ); 
				histos[i]->SetName( ("weights_Iter"+i2s(iIter)+"Var"+i2s(iVar)+"Criteria"+i2s(i)).c_str() );
				if(!histos[i])
				{
					cerr<<"ERROR: in function applyWeightsToTree2D, error loading one histo. Exit."<<endl;
					f.Close();
					return;
				}
			}

			cout<<"Correcting weights according to "<<histos[0]->GetTitle()<<"..."<<endl;

			it = weights.begin();

			for(int iTree(0); iTree<nEntriesTot; ++iTree)
			{
				if(iTree % (nEntriesTot/10) == 0) cout<<100*iTree/nEntriesTot<<"\% "<<flush;
				t->GetEntry(iTree);

				//first must get the histos corresponding to the right criterium

				nTrueCriteria = 0;

				for(int i(0); i<nCriteria; ++i)
				{
					if( criteriaTTFs[i] -> EvalInstance() )
					{
						++ nTrueCriteria;
						goodCriteria = i;
					}
				}

				if(nTrueCriteria != 1)
				{
					cerr<<"ERROR: CHRISTUS BITUS!!!!! Problem with the number of good criteria: nTrueCriteria = "<<nTrueCriteria<<". You are fucked! F-U-C-K-E-D!!!!"<<endl;
					f.Close();
					return;
				}

				histo = histos[goodCriteria];
				nBins = histo->GetXaxis()->GetNbins();

				//Fill the table

				if(ttf.EvalInstance())
				{
					if(varsReweight2[iVar] == "")
					{
						whichBin = histo->FindBin( vecTtfs1[iVar]->EvalInstance());
						if(whichBin == 0) whichBin = 1;
						if(whichBin > nBins) whichBin = nBins;
						(*it) *= histo->GetBinContent(whichBin) ;
					}
					if(varsReweight2[iVar] != "")
					{
						whichBin = histo->FindBin( vecTtfs1[iVar]->EvalInstance(), vecTtfs2[iVar]->EvalInstance());
						if(whichBin >= 0) (*it) *= histo->GetBinContent(whichBin) ;
					}

					//if this is the final step of the loop, the normalisation of the weights has to be prepared

					if(iIter == nIter-1 && iVar == nVars-1)
					{
						sumWeightsCats[goodCriteria] += (*it);
						sumNCats[goodCriteria]++;
						sumNCatsWeighted[goodCriteria] += MCTtfPreviousWeight.EvalInstance();
					}

					++it;
				}
			}
		}
	}

	//Getting the weights' normalisations

	vector<double> normalisationCats(nCriteria, 0);
	for(int i(0); i<nCriteria; ++i) normalisationCats[i] = sumWeightsCats[i] / sumNCatsWeighted[i];

	//filling the tree with the weights 

	string fileTreeInter(fileTree);
	fileTreeInter.insert(fileTreeInter.size()-5, "ToErase");

	f.cd();
	cout<<"Filling the tree with the computed weights..."<<endl;

	t->SetBranchStatus("*", 1);
	cout<<"====================="<<endl<<"Errors from TTreeFormula don't matter from here"<<endl;
	t->SetBranchStatus(MCNewWeightName.c_str(), 0);
	cout<<"====================="<<endl<<"From now on errors matter"<<endl;

	TFile f2(fileTreeInter.c_str(), "RECREATE");

	TTree* reweightedTree = t->CloneTree(0);   
	double dataMCWeight;
	reweightedTree->Branch(MCNewWeightName.c_str(), &dataMCWeight, (MCNewWeightName+"/d").c_str());

	it = weights.begin();

	for(int i(0); i < t->GetEntries(); ++i)
	{
		if(i % (nEntriesTot/10) == 0) cout<<100*i/nEntriesTot<<"\% "<<flush;

		t->GetEntry(i);
		if(ttf.EvalInstance())
		{
			for(int i(0); i<nCriteria; ++i)
			{
				if( criteriaTTFs[i] -> EvalInstance() ) goodCriteria = i;
			}

			if(keepNormalisationSame) dataMCWeight = (*it)/normalisationCats[goodCriteria];
			if(!keepNormalisationSame) dataMCWeight = (*it);
			reweightedTree->Fill();
			++it;
		}
		if(!ttf.EvalInstance())
		{
			dataMCWeight = 0;
			reweightedTree->Fill();
		}
	}
	cout<<endl<<" done!"<<endl;

	reweightedTree->Write("", TObject::kOverwrite);

	//close everything

	f.Close();
	f2.Close();

	for(int i(0); i<nCriteria; ++i)
	{
		if(criteriaTTFs[i] != NULL) delete criteriaTTFs[i];
		fHistos[i] -> Close();
		if(fHistos[i] != NULL) delete fHistos[i];
	}
	for(int i(0); i<nVars; ++i)
	{
		if(vecTtfs1[i] != NULL) delete vecTtfs1[i];
		if(vecTtfs2[i] != NULL) delete vecTtfs2[i];
	}

	rename(fileTreeInter.c_str(), fileTree.c_str());
}



void getWeightsWith2D(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, int nBins2D1, int nBins2D2, vector<string> varsReweight, int nIter,
		vector<string> fileHistoNames,  vector<string> criteria, string dataWeightName, string extraMCCut, string extraTargetCut, string previousMCWeight)
{
	if( criteria.size() != fileHistoNames.size() )
	{
		cerr<<"ERROR: in function getWeightsWith2D, mismatch in the number of criteria."<<endl;
		return;
	}

	string newExtraMCCut;
	string newExtraTargetCut;

	string fileHistoName;
	for(int i(0); i<criteria.size(); ++i)
	{
		newExtraMCCut = criteria[i];
		newExtraTargetCut = criteria[i];
		if(extraMCCut != "") newExtraMCCut += ( " && "+extraMCCut );  
		if(extraTargetCut != "") newExtraTargetCut += ( " && "+extraTargetCut );  

		cout<<"Getting the weights for criterium "<<criteria[i]<<endl; 
		fileHistoName = fileHistoNames[i];
		getWeightsWith2D(fileMCTree, fileTargetTree, nameMCTree, nameTargetTree, nBins, nBins2D1, nBins2D2, varsReweight, nIter, fileHistoName, dataWeightName, newExtraMCCut, newExtraTargetCut, previousMCWeight);
	}
}

void getWeightsWith2D(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, int nBins2D1, int nBins2D2, vector<string> varsReweight, int nIter,
		string fileHistoName, string dataWeightName, string extraMCCut, string extraTargetCut, string previousMCWeight)
{
	cout<<"Computing the MC correction weights (2D enabled)..."<<endl;

	//Prepare the trees

	TFile MCFile(fileMCTree.c_str(), "UPDATE");
	TTree* MCTree = (TTree*)MCFile.Get(nameMCTree.c_str());


	TFile targetFile(fileTargetTree.c_str());
	TTree* targetTree = (TTree*)targetFile.Get(nameTargetTree.c_str());

	if(MCTree == 0 || targetTree == 0)
	{
		cerr<<"ERROR: in getWeights, no tree found"<<endl;
		return;
	}

	//declare some useful shit

	if(extraMCCut == "") extraMCCut = "1";
	if(extraTargetCut == "") extraTargetCut = "1";

	int MCEntries(MCTree->GetEntries(extraMCCut.c_str()));
	int MCEntriesTot(MCTree->GetEntries());
	double WeightedMCEntries(getEntries(MCTree, extraMCCut.c_str(), previousMCWeight) );
	double WeightedMCEntriesTot(getEntries(MCTree, "", previousMCWeight) );
	int targetEntries(targetTree->GetEntries(extraTargetCut.c_str()));
	int targetEntriesTot(targetTree->GetEntries());
	int nVars(varsReweight.size());


	string var2D1;
	string var2D2;
	bool is2D;
	vector<double> polyMinMax(4,0.);
	TH1D* current1DH(NULL);
	TH2Poly* current2DH(NULL);

	//separate the 2D vars

	vector<string> varsReweight1(nVars, "");
	vector<string> varsReweight2(nVars, "");

	for(int i(0); i<nVars; ++i)
	{
		is2D = separateString(varsReweight[i], var2D1, var2D2);
		if(!is2D) varsReweight1[i]  =  varsReweight[i];
		if(is2D)
		{
			varsReweight1[i] = var2D1;
			varsReweight2[i] = var2D2;
		}
	}



	//Prepare  the binning tables and empty target histos

	cout<<"Preparing uniform bins..."<<endl;

	double binTabs[nBins+1];
	vector<double> binTabs2D1;
	vector< vector<double> > binTabs2D2;
	vector<TH1*> targetHistos;//(nVars, 0);

	for(int i(0); i<nVars; ++i)
	{
		if(varsReweight2[i] == "")
		{
			getUniformBinning( nBins, binTabs, MCTree, varsReweight[i], extraMCCut);
			targetHistos.push_back(new TH1D( ("dataDistribution"+i2s(i)).c_str(), ("dataDistribution"+i2s(i)).c_str(), nBins, binTabs ));
			targetHistos[i] -> Sumw2();
		}
		if(varsReweight2[i] != "")
		{
			polyMinMax = getUniformBinningPoly(nBins2D1, nBins2D2, binTabs2D1, binTabs2D2, MCTree, varsReweight1[i], varsReweight2[i], extraMCCut, previousMCWeight);
			current2DH = new TH2Poly( ("dataDistribution"+i2s(i)).c_str(), ("dataDistribution"+i2s(i)).c_str(), polyMinMax.at(0), polyMinMax.at(1), polyMinMax.at(2), polyMinMax.at(3) );
			current2DH -> Sumw2();
			binTH2Poly(current2DH, binTabs2D1, binTabs2D2);
			targetHistos.push_back(current2DH);
		}
	}


	//Prepare TTree formulae

	vector<TTreeFormula*> MCTtfVec1(nVars, NULL);
	vector<TTreeFormula*> targetTtfVec1(nVars, NULL);
	vector<TTreeFormula*> MCTtfVec2(nVars, NULL);
	vector<TTreeFormula*> targetTtfVec2(nVars, NULL);

	MCTree->SetBranchStatus("*", 0); 
	targetTree->SetBranchStatus("*", 0); 

	setBranchStatusTTF(MCTree, extraMCCut.c_str());
	setBranchStatusTTF(targetTree, extraTargetCut.c_str());

	for(int i(0); i<nVars; ++i)
	{
		setBranchStatusTTF(MCTree, varsReweight1[i]);
		setBranchStatusTTF(targetTree, varsReweight1[i]);

		MCTtfVec1[i] = ( new TTreeFormula( ("formulaMC"+i2s(i)).c_str(), (varsReweight1[i]).c_str(), MCTree) );
		targetTtfVec1[i] = ( new TTreeFormula( ("formulaData"+i2s(i)).c_str(), (varsReweight1[i]).c_str(), targetTree) );

		if(varsReweight2[i] != "")
		{
			setBranchStatusTTF(MCTree, varsReweight2[i]);
			setBranchStatusTTF(targetTree, varsReweight2[i]);

			MCTtfVec2[i] = ( new TTreeFormula( ("formulaMC"+i2s(i)+"2").c_str(), (varsReweight2[i]).c_str(), MCTree) );
			targetTtfVec2[i] = ( new TTreeFormula( ("formulaData"+i2s(i)+"2").c_str(), (varsReweight2[i]).c_str(), targetTree) );
		}
	}

	//prepare formulae for the extracut 

	TTreeFormula MCTtfExtraCut("MCTtfExtraCut", extraMCCut.c_str(), MCTree );
	TTreeFormula targetTtfExtraCut( "targetTtfExtraCut", extraTargetCut.c_str(), targetTree ); 

	//link the target weights (sweights)

	double dataWeight(1.);
	if(dataWeightName != "") 
	{
		targetTree->SetBranchStatus(dataWeightName.c_str(), 1);
		targetTree->SetBranchAddress(dataWeightName.c_str(), &dataWeight);
	}

	//fill the target histos 

	cout<<"Filling of the target histograms..."<<endl;

	double temp1, temp2;
	for(int jVar(0); jVar < nVars; ++jVar)
	{
		for(int i(0); i < targetEntriesTot; ++i)
		{
			targetTree->GetEntry(i);      
			if(targetTtfExtraCut.EvalInstance() )
			{
				if(varsReweight2[jVar] == "")
				{
					temp1 = targetTtfVec1[jVar] -> EvalInstance();
					current1DH = (TH1D*)targetHistos[jVar];
					current1DH -> Fill(temp1, dataWeight);
				}
				if(varsReweight2[jVar] != "")
				{
					temp1 = targetTtfVec1[jVar] -> EvalInstance();
					temp2 = targetTtfVec2[jVar] -> EvalInstance();
					current2DH = (TH2Poly*)targetHistos[jVar];
					current2DH -> Fill(temp1, temp2, dataWeight);

				}
			}
		}

		if(varsReweight2[jVar] == "") targetHistos[jVar] -> Scale( 1./targetHistos[jVar]->Integral() );
		if(varsReweight2[jVar] != "") scalePoly( (TH2Poly*)targetHistos[jVar],  1./targetHistos[jVar]->Integral() );
	}

	//prepare where to save the reweighting histos

	TFile fileHisto(fileHistoName.c_str(), "RECREATE");

	//if the MC tree has previously been weighted, the weight table has to be filled with the initial weights

	cout<<"Get the MC initial weights..."<<endl;

	list<double> weights(MCEntries,1.);

	if( previousMCWeight != "" )
	{
		setBranchStatusTTF(MCTree, previousMCWeight);
		TTreeFormula MCTtfPreviousWeight("MCTtfPreviousWeight", previousMCWeight.c_str(),  MCTree );

		list<double>::iterator it(weights.begin());

		for(int i(0); i < MCEntriesTot; ++i)
		{
			MCTree->GetEntry(i);
			if(MCTtfExtraCut.EvalInstance())
			{
				*it = MCTtfPreviousWeight.EvalInstance();
				++it;
			}
		}
	}


	//Prepare the weight of the tree 

	cout<<"Computation of the weights..."<<endl;

	for(int iIter(0); iIter < nIter; ++iIter)
	{
		for(int jVar(0); jVar < nVars; ++jVar)
		{
			if(varsReweight2[jVar] == "") updateWeightsAndFillTable(weights, MCTree, nBins,  MCTtfVec1[jVar],
					&fileHisto, (TH1D*)targetHistos[jVar], ("weights_Iter"+i2s(iIter)+"Var"+i2s(jVar)).c_str(), &MCTtfExtraCut, previousMCWeight);

			if(varsReweight2[jVar] != "") updateWeightsAndFillTable2D(weights, MCTree, nBins,  MCTtfVec1[jVar],  MCTtfVec2[jVar], &fileHisto, 
					(TH2Poly*)targetHistos[jVar], ("weights_Iter"+i2s(iIter)+"Var"+i2s(jVar)).c_str(), &MCTtfExtraCut, previousMCWeight);
		}
	}

	for(int i(0); i<nVars; ++i)
	{
		delete MCTtfVec1[i];
		if(MCTtfVec2[i] != NULL) delete MCTtfVec2[i];
		delete targetTtfVec1[i];
		if(targetTtfVec2[i] != NULL) delete targetTtfVec2[i];
		delete targetHistos[i];
	}

	//   fReweightedTree.Close();
	MCFile.Close();
	targetFile.Close();
	fileHisto.Close();
}  

