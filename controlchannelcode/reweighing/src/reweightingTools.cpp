#include "usefulFunctions.hpp"
#include <algorithm>
#include "reweightingTools.hpp"




void getUniformBinning(int nbins, double bins[], TTree* t, string namevar, string extracut) //warning, table of size nbins+1
{
   t->SetBranchStatus("*",0);
   setBranchStatusTTF(t, namevar); 
   setBranchStatusTTF(t, extracut); 

   vector<double> varValues;
   TTreeFormula ttf("ttf", namevar.c_str(), t); 

   if(extracut == "") extracut == 1;
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

void updateWeightsAndFillTable(list<double>& weightTab, TTree* MCTree, int nBins, TTreeFormula* MCTtf, TFile* fileHisto, TH1D* targetHisto, string nameHisto, TTreeFormula* MCTtfExtraCut)
{
   //TH1D MCHisto("MCHisto", "MCHisto", nBins, bins); 
   TH1D MCHisto(*targetHisto);
   MCHisto.Reset();

   int MCEntries(MCTree->GetEntries( (MCTtfExtraCut->GetExpFormula())  ));
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

   //MCHisto.Divide(targetHisto);

   TH1D weightHisto(*targetHisto); //nameHisto.c_str(), nameHisto.c_str(), nBins, bins);
   weightHisto.Reset();
   weightHisto.SetName(nameHisto.c_str());
   weightHisto.SetTitle(nameHisto.c_str());

   weightHisto.Divide(targetHisto, &MCHisto); 

   cout<<"computing weights for var "<<MCTtf->GetName()<<endl;

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

  double rescale(MCEntries  / sumWeights);   

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





void getWeights(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, vector<string> varsReweight, int nIter,
    vector<string> fileHistoNames, vector<string> criteria, string dataWeightName, string extracut)
{
   if( criteria.size() != fileHistoNames.size() )
   {
      cerr<<"ERROR: in function getWeights, mismatch in the number of criteria."<<endl;
      return;
   }

   string newExtraCut;
   string fileHistoName;
   for(int i(0); i<criteria.size(); ++i)
   {
      newExtraCut = criteria[i];
      if(extracut != "") newExtraCut += ( " && "+extracut );  

      cout<<"Getting the weights for criterium "<<criteria[i]<<endl; 
      fileHistoName = fileHistoNames[i];
      getWeights(fileMCTree, fileTargetTree, nameMCTree, nameTargetTree, nBins, varsReweight, nIter, fileHistoName, dataWeightName, newExtraCut);
   }
}


void getWeights(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, vector<string> varsReweight, int nIter,
    string fileHistoName, string dataWeightName, string extracut)
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

   if(extracut == "") extracut = "1";

   int MCEntries(MCTree->GetEntries(extracut.c_str()));
   int MCEntriesTot(MCTree->GetEntries());
   int targetEntries(targetTree->GetEntries(extracut.c_str()));
   int targetEntriesTot(targetTree->GetEntries());
   int nVars(varsReweight.size());

  //Prepare  the binning tables and empty target histos
  
   

   cout<<"Preparing uniform bins..."<<endl;

   double binTabs[nBins+1];
   vector<TH1D*> targetHistos;//(nVars, 0);

   for(int i(0); i<nVars; ++i)
   {
      getUniformBinning( nBins, binTabs, MCTree, varsReweight[i], extracut);
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
      setBranchStatusTTF(MCTree, extracut.c_str());
      setBranchStatusTTF(targetTree, extracut.c_str());
      MCTtfVec.push_back( new TTreeFormula( ("formulaMC"+i2s(i)).c_str(), (varsReweight[i]).c_str(), MCTree) );
      targetTtfVec.push_back( new TTreeFormula( ("formulaData"+i2s(i)).c_str(), (varsReweight[i]).c_str(), targetTree) );
   }

   //prepare formulae for the extracut 

   TTreeFormula MCTtfExtraCut("MCTtfExtraCut", extracut.c_str(), MCTree );
   TTreeFormula targetTtfExtraCut( "targetTtfExtraCut", extracut.c_str(), targetTree ); 

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

   //Prepare the weight of the tree 

   cout<<"Computation of the weights..."<<endl;

   list<double> weights(MCEntries,1.);

   for(int iIter(0); iIter < nIter; ++iIter)
   {
      for(int jVar(0); jVar < nVars; ++jVar)
      {
         updateWeightsAndFillTable(weights, MCTree, nBins,  MCTtfVec[jVar],
          &fileHisto, targetHistos[jVar], ("weights_Iter"+i2s(iIter)+"Var"+i2s(jVar)).c_str(), &MCTtfExtraCut );
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


void applyWeightsToTree( string fileTree, string nameTree, vector<string> varsReweight, int nIter, string nameHistoFile, string extracut, string MCNewWeightName)
{
   //Get the Tree

   TFile f(fileTree.c_str(), "UPDATE");
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
   //prepare ttreeformula to perform the cut


   if( extracut == "" ) extracut = "1";
   else setBranchStatusTTF(t, extracut);

   TTreeFormula ttf("ttf", extracut.c_str(), t);
   
   //Fill the weight table

   cout<<"Filling the weights..."<<endl;

   list<double> weights(nEntries, 1.);
   list<double>::iterator it(weights.begin());
   
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

   double sumWeights(0);
   
   it = weights.begin();
   for(; it!=weights.end(); ++it) sumWeights += *it;
      
   double rescale(nEntries  / sumWeights);   
   
   it = weights.begin();
   for(; it!=weights.end(); ++it) (*it) *= rescale;

  //filling the tree with the weights 


   f.cd();
   cout<<"Filling the tree with the computed weights..."<<endl;

   t->SetBranchStatus("*", 1);
   t->SetBranchStatus(MCNewWeightName.c_str(), 0);

   
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
   }
   cout<<endl<<" done!"<<endl;

   reweightedTree->Write("", TObject::kOverwrite);

   //close everything
   //
   f.Close();
   fHisto.Close();
}



void applyWeightsToTree( string fileTree, string nameTree,  vector<string> varsReweight, int nIter, vector<string> namesHistoFile, vector<string> criteria, string extracut, string MCNewWeightName)
{
   //Check the criteria:
   
   if(namesHistoFile.size() != criteria.size() )
   {
      cerr<<"ERROR: in function applyWeightsToTree, the number of criteria don't match number of files";
      return;
   }
   int nCriteria(criteria.size());

   //Get the Tree

   TFile f(fileTree.c_str(), "UPDATE");
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
   
   //Fill the weight table

   cout<<"Filling the weights..."<<endl;

   list<double> weights(nEntries, 1.);
   list<double>::iterator it(weights.begin());
   
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
               }

               ++it;
            }
         }
      }
   }

   //Getting the weights' normalisations

   vector<double> normalisationCats(nCriteria, 0);
   for(int i(0); i<nCriteria; ++i) normalisationCats[i] = sumWeightsCats[i] / sumNCats[i];

   //filling the tree with the weights 


   f.cd();
   cout<<"Filling the tree with the computed weights..."<<endl;

   t->SetBranchStatus("*", 1);
   t->SetBranchStatus(MCNewWeightName.c_str(), 0);

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

         dataMCWeight = (*it)/normalisationCats[goodCriteria];
         reweightedTree->Fill();
         ++it;
      }
   }
   cout<<endl<<" done!"<<endl;

   reweightedTree->Write("", TObject::kOverwrite);

   //close everything
   
   f.Close();

   for(int i(0); i<nCriteria; ++i)
   {
      if(vecTtfs[i] != NULL) delete vecTtfs[i];
      if(criteriaTTFs[i] != NULL) delete criteriaTTFs[i];
      fHistos[i] -> Close();
      if(fHistos[i] != NULL) delete fHistos[i];
   }
}
