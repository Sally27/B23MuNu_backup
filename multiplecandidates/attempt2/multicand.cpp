#include <iostream>
#include <cmath>
#include <string>
#include "TCut.h"
#include <sstream>
#include "TFile.h"
#include "TRandom3.h"
#include <vector>
#include <stdio.h>
#include "multicand.hpp"
	multicand::multicand(const char* _name, TTree* _tree,TString _partname)
: name(_name),tree(_tree)
{
	if (_partname.Length() > 0)
	{
		addDiffParticle(_partname);
	}
	tree->SetBranchStatus("*",1);
}
multicand::~multicand()
{}
void multicand::weight(TTree* newtree)
{
}
void multicand::addDiffParticle(TString _diffParticle)
{
	diffParticle = _diffParticle;
}
TTree* multicand::reweight()
{
	TTree* reweighted_tree;
	weight(reweighted_tree);
	return reweighted_tree;
}
TTree* multicand::random_long(std::vector<TString> variables)
{
	UInt_t runno;
	ULong64_t eventno;
	TRandom3 trandom;
	tree->SetBranchStatus("*",0);
	tree->SetBranchStatus("runNumber",1);
	tree->SetBranchStatus("eventNumber",1);
	for (int i = 0; i < variables.size(); ++i)
	{
		tree->SetBranchStatus(variables[i],1);
	}
	tree->SetBranchAddress("runNumber",&runno);
	tree->SetBranchAddress("eventNumber",&eventno);
	TTree* random_tree=tree->CloneTree(0);
	int nmult=0;
	std::vector<bool> multiples;
	std::cout << "This might take a while .." << std::endl;
	for (int i=0; i<tree->GetEntries(); i++)
	{ 
		tree->GetEntry(i);
		if (i%100 == 0)
		{
			std::cout << "processed event " << i << std::endl;
		}
		double eventi = eventno;
		double runnoi = runno;  
		bool multiple = false;      
		for (int j=i+1; j<tree->GetEntries(); j++)
		{
			tree->GetEntry(j);
			double eventj = eventno;
			double runnoj = runno;  
			if (i != j)
			{
				if (eventj == eventi)
				{
					if (runnoi == runnoj)
					{
						multiple=true;
						multiples.push_back(multiple);
						nmult++;
					}
				}
			}
		}
		tree->GetEntry(i);
		if (multiple == false)
		{
			random_tree->Fill();
		}
	}
	std::cout << "percentage multiple candidates = " << 100.0*nmult/tree->GetEntries() << "%" << std::endl;
	return random_tree;
}
TTree* multicand::random()
{
	TTree* random_tree=tree->CloneTree(0);
	UInt_t runno;
	UInt_t ncand;
	ULong64_t totcand;
	ULong64_t eventno;
	TRandom3 trandom;
	tree->SetBranchAddress("runNumber",&runno);
	tree->SetBranchAddress("eventNumber",&eventno);
	tree->SetBranchAddress("nCandidate",&ncand);
	tree->SetBranchAddress("totCandidates",&totcand);
	int nmult=0;
	for (int i=0; i<tree->GetEntries(); i++)
	{ 
		tree->GetEntry(i);
		double eventnoold = eventno;
		double runnoold = runno;
		tree->GetEntry(i+1);
		double weight = 1;
		while ((runnoold == runno) && (eventno == eventnoold))
		{
			weight++;
			tree->GetEntry(i+weight);
			if (i+weight > tree->GetEntries())
			{
				break;
			}
		}
		if (weight < 2)
		{
			tree->GetEntry(i);
			random_tree->Fill();
		}
		else
		{
			nmult++;
			double rand = trandom.Uniform();
			int rand_int  = rand*weight;
			tree->GetEntry(i+rand_int);
			random_tree->Fill();
		}
		i+=weight-1;
	}
	std::cout << "percentage multiple candidates = " << 100.0*nmult/tree->GetEntries() << "%" << std::endl;
	return random_tree;
}
TTree* multicand::randomFast(std::vector<bool*> current_results)
{
	//assert(current_results.size() == tree->GetEntries());
	UInt_t runno;
	UInt_t ncand;
	ULong64_t totcand;
	ULong64_t eventno;
	TRandom3 trandom;
	double diffP;
	tree->SetBranchStatus("*",0);
	tree->SetBranchStatus("runNumber",1);
	tree->SetBranchStatus("eventNumber",1);
	tree->SetBranchAddress("runNumber",&runno);
	tree->SetBranchAddress("eventNumber",&eventno);
	tree->SetBranchAddress("nCandidate",&ncand);
	tree->SetBranchAddress("totCandidates",&totcand);
	if (diffParticle.Length())
	{
		tree->SetBranchStatus(diffParticle+"_P",1);
		tree->SetBranchAddress(diffParticle+"_P",&diffP);
	}
	int nmult=0;
	int nsamemult=0;
	for (int i=0; i<tree->GetEntries()-1; i++)
	{
		if (*current_results[i] == true)
		{
			tree->GetEntry(i);
			double eventnoold = eventno;
			double runnoold = runno;
			double diffPold;
			if (diffParticle.Length())
			{
				diffPold = diffP;
			}
			tree->GetEntry(i+1);
			int weight = 1;
			int trueweight = 1;
			while (((runnoold == runno) && (eventno == eventnoold)) && (!diffParticle.Length() || (fabs(diffPold - diffP) < 1)))
			{
				if (*current_results[i+weight] == true)
				{
					trueweight++;
				}
				weight++;
				tree->GetEntry(i+weight);
				if (i+weight > tree->GetEntries())
				{
					break;
				}
			}
			if (trueweight > 1)
			{
				nmult++;
				double rand = trandom.Uniform();
				int rand_int  = rand*trueweight;
				for (int j=0; j<trueweight; j++)
				{
					bool diff = false;
					if ((j != rand_int) && !diff)
					{
						nsamemult++;
						*current_results[i+j]=false;
					}
				}
			}
			i+=weight-1;
		}
	}
	std::cout << "percentage multiple candidates = " << 100.0*nmult/tree->GetEntries() << "%" << std::endl;
	return tree;
}

