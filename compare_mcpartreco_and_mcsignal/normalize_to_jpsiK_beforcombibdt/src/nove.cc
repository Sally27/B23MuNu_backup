#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
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
#include "usefulFunctions.hpp"
#include "ValError.hpp"
#include "mySecondClass.hpp"
#include "EfficiencyClass.hpp"
#include<iostream>

using namespace std;
//using namespace RooFit;


int main(){

	ofstream out;
	out.open("EfficiencyComparison_compared_toNormalisation_nove_beforecombibdt.tex");

	out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
	out<<"\\usepackage[pdftex]{graphicx}"<<endl;
	out<<"\\usepackage{url}"<<endl;
	out<<"\\usepackage{mathtools}"<<endl;
	out<<"\\usepackage{amsmath}"<<endl;
	out<<"\\usepackage{graphicx}"<<endl;
	out<<"\\usepackage[table]{xcolor}"<<endl;
	out<<"\\usepackage{amsmath,amssymb}"<<endl;
	out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
	out<<"\\usepackage{colortbl}"<<endl;
	out<<"\\begin{document}"<<endl;

	//        out<<"Calculation of the Single Event Sensitivity"<<endl;
	out<<"\\begin{table}[ht]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{ l | l | l }"<<endl; 
	out<<"\\hline"<<endl;
	out<<"$\\varepsilon$ & $B^+ \\rightarrow J/\\psi K^{+}$  & $B^+ \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-}$ \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"\\hline"<<endl;

	vector<int> years;

	years.push_back(2011);
	years.push_back(2012);
	years.push_back(2016);

	double number_bkk_sig(0);
	double decprodcutsig(0);

	double effrecostrsig(0);
	double effmyrecosig(0);
	double combibdtsig(0);	
	double misidbdtsig(0);
	double cormsig(0);		
	double effstripsig(0);

        

	number_bkk_sig=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_NORM.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "numbkk");
	decprodcutsig=0.16216;
	effstripsig=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_NORM.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "strip");
        double effmisidstrip=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_NORM.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "misidstrippingfull");
	effrecostrsig=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_NORM.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "mctruth");
//	effmyrecosig=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_NORM.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "toteff");

	double	efftriggersig=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_NORM.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "trigger");
	double	effjpsisig=1.0;//returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_NORM.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "jpsi");

        double fitrangesig(0.987443); //corected for ocmbi bdt


	double number_bkk_nor(0);
	double decprodcutjpsik(0);
	double effrecostrjpsik(0);
	double effmyrecojpsik(0);
	double combibdtjpsik(0);
	double misidbdtjpsik(0);
	double cormjpsik(0);
	double effstripjpsik(0);

	combibdtsig=0.508916;
	misidbdtsig=0.514685;


        vector<double> alleff;
//        alleff.push_back(decprodcutsig);
        alleff.push_back(effstripsig);
        alleff.push_back(effmisidstrip);
        alleff.push_back(effrecostrsig);
//        alleff.push_back(effmyrecosig); 
        alleff.push_back(efftriggersig);
        alleff.push_back(effjpsisig);
//        alleff.push_back(combibdtsig);
//        alleff.push_back(misidbdtsig);
        alleff.push_back(fitrangesig);

        double combsig=combibdtsig*misidbdtsig*fitrangesig;


	mySecondClass really;
	really.name_type="Normalisation";
	really.efficiency=alleff;
        
	for (int j(0); j<alleff.size(); j++)
	{
		really.printeff(j);
	}

        really.multiplyalleff();

	number_bkk_nor=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "numbkk");
	decprodcutjpsik=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "decprodcut");
	effstripjpsik=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "strip");
	effrecostrjpsik=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "mctruth");
	//effmyrecojpsik=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "toteff");
	double efftriggerjpsik=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "trigger");
	double effjpsijpsik=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "jpsi");
	double effqmin=returnEff(("../tuples/Efficiencies_"+i2s(years.at(1))+"_PR.root").c_str(), ("PartReco_MC_"+i2s(years.at(1))).c_str(), "qmincut");

	combibdtjpsik=0.245146;
	misidbdtjpsik=0.635529;
        double fitrangejpsik(0.238787); //corrected for combi bdt without combi and misid
 
        vector<double> alleff_pr;
//        alleff_pr.push_back(decprodcutjpsik);
        alleff_pr.push_back(effstripjpsik);
        alleff_pr.push_back(effrecostrjpsik);
        //alleff_pr.push_back(effmyrecojpsik); 
        alleff_pr.push_back(efftriggerjpsik);
        alleff_pr.push_back(effjpsijpsik);
//        alleff_pr.push_back(combibdtjpsik);
//        alleff_pr.push_back(misidbdtjpsik);
        alleff_pr.push_back(fitrangejpsik);
//        alleff_pr.push_back(effqmin);

        double combipr=combibdtjpsik*misidbdtjpsik*fitrangejpsik;
 

	mySecondClass really_pr;
	really_pr.name_type="Partially Reconstructed Background";
	really_pr.efficiency=alleff_pr;
        
	for (int j(0); j<alleff_pr.size(); j++)
	{
		really_pr.printeff(j);
	}

  
        really_pr.multiplyalleff();


	out << "$\\varepsilon_{gen}$ &" << round_to_digits(decprodcutsig,3) << " & " << round_to_digits(decprodcutjpsik,3) <<" \\\\ "<<endl;
	out << "Events in Bookeeping &" << round_to_digits(number_bkk_sig,7) << " & " << round_to_digits(number_bkk_nor,7) <<" \\\\ "<<endl;
	out << "$\\varepsilon_{strip}$ &" << round_to_digits(effstripsig,3) << " & " << round_to_digits(effstripjpsik,3) <<" \\\\ "<<endl;
	out << "$\\varepsilon_{mctruth}$ &" << round_to_digits(effrecostrsig,3) << " & " << round_to_digits(effrecostrjpsik,3) <<" \\\\ "<<endl; 
	out << "$\\varepsilon_{misidstrippfull}$ &" << round_to_digits(effmisidstrip,3) << " & " << " - " <<" \\\\ "<<endl; 
	out << "$\\varepsilon_{trigger}$ &" << round_to_digits(efftriggersig,3) << " & " << round_to_digits(efftriggerjpsik,3) <<" \\\\ "<<endl;
	out << "$\\varepsilon_{J/\\psi}$ &" << round_to_digits(effjpsisig,3) << " & " << round_to_digits(effjpsijpsik,3) <<" \\\\ "<<endl;
//	out << "$\\varepsilon_{qmin}$ &" << " - " << " & " << round_to_digits(effqmin,3) <<" \\\\ "<<endl;
//	out << "$\\varepsilon_{combibdt}$ &" << round_to_digits(combibdtsig,3) << " & " << round_to_digits(combibdtjpsik,3) <<" \\\\ "<<endl;
//	out << "$\\varepsilon_{misidbdt}$ &" << round_to_digits(misidbdtsig,3) << " & " << round_to_digits(misidbdtjpsik,3) <<" \\\\ "<<endl;
//	out << "$\\varepsilon_{fitrange}$ &" << round_to_digits(fitrangesig,3) << " & " << round_to_digits(fitrangejpsik,3) <<" \\\\ "<<endl;
	out<<"\\hline"<<endl;
        out<< "$\\varepsilon_{selection}$ & "<<round_to_digits(really.multiplyalleff(),3) <<" & "<<round_to_digits(really_pr.multiplyalleff(),3)<<" \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{MC efficiency comparison between Signal and Part Reco samples up to multivariate selection. There was no trigger applied on the part reco sample as it would be mismodelled as most of trigger lines selected look for muon, hence taking conservative approach of not requiring trigger will over-estimate the partreco efficiency for this category.}"<<endl;
	out<<"\\end{table}"<<endl;


//	out<<" Assuming branching fractions $\\mathcal{B}(B^+ \\rightarrow \\mu^+ \\mu^- \\mu^+ ) = 1\\times10^{-8}$ and $\\mathcal{B}(B^+ \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-} ) = 1\\times10^{-7}$  \\newline Before BDTs: \\newline $ \\frac{\\mathcal{B}(B^+ \\rightarrow \\mu^+ \\mu^- \\mu^+ ) = 1\\times10^{-8} \\times \\varepsilon_{reco = gen + strip + truthm + jpsi + trigger + qmin}="<<sigfirst<<"}{\\mathcal{B}(B^+ \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-} ) = 1.0\\times10^{-7} \\times \\varepsilon_{reco = }= "<<partrecofisrt<< "} = \\frac{ "<<sigfirst*1.0e-8<<" }{ "<<partrecofisrt*1.0e-7<<"} = "<<firstratio<<" $ "<<endl;

//	out<<" After BDTs: \\newline $ \\frac{\\mathcal{B}(B^+ \\rightarrow \\mu^+ \\mu^- \\mu^+ ) = 1\\times10^{-8} \\times \\varepsilon_{reco} = " <<sigfirst<<" \\times \\varepsilon_{bdts}= "<<combibdtsig*misidbdtsig<<" }{ \\mathcal{B}(B^+ \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-} ) = 1\\times10^{-7} \\times \\varepsilon_{reco} = " <<partrecofisrt<< " \\times \\varepsilon_{bdts}= " << combibdtjpsik*misidbdtjpsik <<"} = \\frac{ "<<sigsec*1.0e-8<<" }{ "<<partrecosec*1.0e-7<<" }  = "<< secratio<<" $"<<endl;



	//total stuff//


        EfficiencyClass lowpr;
        EfficiencyClass highpr;
        EfficiencyClass nopr;

        EfficiencyClass lownorm;
        EfficiencyClass highnorm;
        EfficiencyClass nonorm;
//        string path=lowpr.returnLow_pr();

        cout<<"Returning selection efficiencies for Jpsik"<<endl;
	lowpr.calculate_total_seleff(double(number_bkk_sig), lowpr.return_file("norm","low"),"low");
	highpr.calculate_total_seleff(double(number_bkk_sig), highpr.return_file("norm","high"),"high");
	nopr.calculate_total_seleff(double(number_bkk_sig), nopr.return_file("norm","no"),"no");


        cout<<"Returning selection efficiencies for Part reco"<<endl;
        lowpr.calculate_total_seleff(double(number_bkk_nor), lowpr.return_file("pr","low"),"low");
        highpr.calculate_total_seleff(double(number_bkk_nor), highpr.return_file("pr","high"),"high");
        nopr.calculate_total_seleff(double(number_bkk_nor), nopr.return_file("pr","no"),"no");


        lowpr.return_gen_eff("pr");
        highpr.return_gen_eff("norm");


        vector<string> group;
        group.push_back("low");
        group.push_back("high");
        group.push_back("no");


        vector<string> year;
        year.push_back("2011");
        year.push_back("2012");
        year.push_back("2016");


        EfficiencyClass overall;

        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{l | l | l}"<<endl; 
        out<<"\\hline"<<endl;
        out<<"Properties & Run1 (2012 MC) & 2016 (2012 MC) "<<" \\\\ "<<endl;
        

        out<<"\\hline"<<endl;
        out<<"\\hline"<<endl;
//        out << "$\\mathcal{L}$ &"<<(1e-15)*(l2011lumi.val)<<"$\\pm$"<<(1e-15)*(l2011lumi.err) <<" fb$^{-1}$ &"<<(1e-15)*(l2012lumi.val)<<"$\\pm$"<<(1e-15)*(l2012lumi.err) <<" fb$^{-1}$ &  "<<(1e-15)*(l2016lumi.val)<<"$\\pm$"<<(1e-15)*(l2016lumi.err) <<" fb$^{-1}$ \\\\ "<<endl;
//        out << "$\\sigma(pp \\rightarrow b\\bar{b})$ & "<<(1e6)*(bquark2011.val)<<"$\\pm$" <<(1e6)*(bquark2011.err)<<"$\\mu$b$^{-1}$ & "<<(1e6)*(bquark2012.val)<<"$\\pm$" <<(1e6)*(bquark2012.err)<<"$\\mu$b$^{-1}$ & "<<(1e6)*(bquark2016.val)<<"$\\pm$" <<(1e6)*(bquark2016.err)<<"$\\mu$b$^{-1}$ \\\\ "<<endl;
//        out << "$2.0\\times f(b\\rightarrow B^{+})$ "<<"& 2$\\times$"<<fragfrac.val<<"$\\pm$"<<fragfrac.err<<"& 2$\\times$"<<fragfrac.val<<"$\\pm$"<<fragfrac.err<<"& 2$\\times$"<<fragfrac.val<<"$\\pm$"<<fragfrac.err<<" \\\\ "<<endl;
        out << "$\\mathcal{B}(B^+ \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-})$ & "<<round_to_digits((overall.calculateProduct_BR("pr").val),3)<<"$\\pm$"<<round_to_digits((overall.calculateProduct_BR("pr").err),3)<<" &"<< round_to_digits((overall.calculateProduct_BR("pr").val),3)<<"$\\pm$"<<round_to_digits((overall.calculateProduct_BR("pr").err),3)<<" \\\\ "<<endl;
        out << "$\\mathcal{B}(B^+ \\rightarrow (J/\\psi \\rightarrow \\mu^+ \\mu^{-}) K^{+}$ &"<<round_to_digits((overall.calculateProduct_BR("norm").val),3)<<"$\\pm$"<<round_to_digits((overall.calculateProduct_BR("norm").err),3)<<"& "  << round_to_digits((overall.calculateProduct_BR("norm").val),3)<<"$\\pm$"<<round_to_digits((overall.calculateProduct_BR("norm").err),3)<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\varepsilon_{gen}$ & " << round_to_digits((overall.return_gen_eff("pr").val),3)<<"$\\pm$" <<round_to_digits((overall.return_gen_eff("pr").err),3)<<" & Using 2012 " <<" \\\\ "<<endl;
//        out << "$\\varepsilon_{sel}$ &  " << round_to_digits(overall.calculate_total_seleff(double(number_bkk_nor)),3), round_to_digits((overall.return_file("pr","no"),"no").val,3)<<"$\\pm$"<<round_to_digits(overall.calculate_total_seleff(double(number_bkk_nor)),3), round_to_digits((overall.return_file("pr","no"),"no").err,3)<<" & Using 2012 " <<" \\\\ "<<endl;
	out << "$\\varepsilon_{sel}$ &  " << round_to_digits(overall.calculate_total_seleff(double(number_bkk_nor), overall.return_file("pr","no"),"no").val,3)/effqmin<<"$\\pm$"<<round_to_digits(overall.calculate_total_seleff(double(number_bkk_nor), overall.return_file("pr","no"),"no").err,3)/effqmin<<" & Using 2012 " <<" \\\\ "<<endl;

//----------------------------------------------------divide by qmin---------------- important//


        out<<"\\hline"<<endl;
        out << "$\\varepsilon_{gennorm}$ & " << round_to_digits(overall.return_gen_eff("norm").val,3)<<"$\\pm$" <<round_to_digits(overall.return_gen_eff("norm").err,3)<<" &  Using 2012" <<" \\\\ "<<endl;
//        out << "$\\varepsilon_{selnorm}$ & " << round_to_digits(overall.calculate_total_seleff(double(number_bkk_sig)),3), round_to_digits((overall.return_file("norm","no"),"no").val,3)<<"$\\pm$"<<round_to_digits(overall.calculate_total_seleff(double(number_bkk_sig)),3), round_to_digits((overall.return_file("norm","no"),"no").err,3)<<" & Using 2012 " <<" \\\\ "<<endl;
        out << "$\\varepsilon_{selnorm}$ & " <<round_to_digits(overall.calculate_total_seleff(double(number_bkk_sig), overall.return_file("norm","no"),"no").val,3)<<"$\\pm$"<<round_to_digits(overall.calculate_total_seleff(double(number_bkk_sig), overall.return_file("norm","no"),"no").err,3)<<" & Using 2012 " <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;



        TFile fillinfo("../PR_info/PR_Yield.root","RECREATE");
//        TTree fillinfotree("PR_Yield","PR_Yield");








        for (int i(0); i<3; i++)
        {
        EfficiencyClass forpr;
        EfficiencyClass fornorm;
        EfficiencyClass finalp;

        ValError pr_prod=forpr.calculateProduct_BR_eff(group.at(i), "pr", lowpr.return_gen_eff("pr"), lowpr.calculate_total_seleff(double(number_bkk_nor), lowpr.return_file("pr",group.at(i)),group.at(i))/effqmin);
        ValError norm_prod=lownorm.calculateProduct_BR_eff(group.at(i), "norm", lownorm.return_gen_eff("norm"), lownorm.calculate_total_seleff(double(number_bkk_sig), lownorm.return_file("norm",group.at(i)),group.at(i)));
        ValError num_obs=fornorm.return_num_obs(group.at(i),"2012");
        ValError num_obs_2016=fornorm.return_num_obs(group.at(i),"2016");
     
        ValError relnum, relnum_2016; 
        relnum=finalp.calculateProduct_BR_eff_number_obs(group.at(i),"2012",pr_prod,norm_prod);
        relnum_2016=finalp.calculateProduct_BR_eff_number_obs(group.at(i),"2016",pr_prod,norm_prod);
        out << "$ \\mathcal{B} \\times \\varepsilon_{pr} $ "<<(group.at(i))<<" &  " <<round_to_digits(pr_prod.val,3)<<"$\\pm$"<< round_to_digits(pr_prod.err,3)<<" & Using 2012"<<" \\\\ "<<endl;
        out << "$ \\mathcal{B} \\times \\varepsilon_{norm} $ " <<(group.at(i))<<" &  " <<round_to_digits(norm_prod.val,3)<<"$\\pm$"<< round_to_digits(norm_prod.err,3)<<" & Using 2012"<<" \\\\ "<<endl;
        out << "$ \\frac{\\mathcal{B} \\times \\varepsilon_{pr}}{\\mathcal{B} \\times \\varepsilon_{norm}}$ "<<(group.at(i))<<"  &  "<< round_to_digits((pr_prod/norm_prod).val,3)<<"$\\pm$"<< round_to_digits((pr_prod/norm_prod).err,3)<<"  & Using 2012"<<" \\\\ "<<endl; 
        out << "N($B^+ \\rightarrow (J/\\psi \\rightarrow \\mu^+ \\mu^{-}) K^{+}$) "<<(group.at(i))<<" & "<<round_to_digits(num_obs.val,3)<<"$\\pm$"<<round_to_digits(num_obs.err,3)<<" & "<<round_to_digits(num_obs_2016.val,3)<<"$\\pm$"<<round_to_digits(num_obs_2016.err,3)<<" \\\\ "<<endl;
        out << "N($B^+ \\rightarrow (D^{0} \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-}) \\mu^+ \\nu$ "<<(group.at(i))<<" & "<<"\\textbf{"<<round_to_digits(relnum.val,3)<<"$\\pm$"<<round_to_digits(relnum.err,3)<<"}"<<" & "<<"\\textbf{"<<round_to_digits(relnum_2016.val,3)<<"$\\pm$"<<round_to_digits(relnum_2016.err,3)<<"}"<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;

        double numofevents(0);
        double numofevents_err(0);
        double numofevents_2016(0);
        double numofevents_2016_err(0);


        double numofevents_all(0);
        double numofevents_all_err(0);
      
        fillinfo.cd();
        TTree fillinfotree(("PR_Yield_"+group.at(i)).c_str(),("PR_Yield_"+group.at(i)).c_str());
     
        fillinfotree.Branch(("numofevents_"+group.at(i)).c_str(),&numofevents,("numofevents_"+group.at(i)+"/D").c_str());// "Cut/C");
        fillinfotree.Branch(("numofevents_err_"+group.at(i)).c_str(),&numofevents_err,("numofevents_err_"+group.at(i)+"/D").c_str());// "Cut/C");

        fillinfotree.Branch(("numofevents_2016_"+group.at(i)).c_str(),&numofevents_2016,("numofevents_2016_"+group.at(i)+"/D").c_str());// "Cut/C");
        fillinfotree.Branch(("numofevents_2016_err_"+group.at(i)).c_str(),&numofevents_2016_err,("numofevents_2016_err_"+group.at(i)+"/D").c_str());// "Cut/C");

        fillinfotree.Branch(("numofevents_all_"+group.at(i)).c_str(),&numofevents_all,("numofevents_all_"+group.at(i)+"/D").c_str());// "Cut/C");
        fillinfotree.Branch(("numofevents_all_err_"+group.at(i)).c_str(),&numofevents_all_err,("numofevents_all_err_"+group.at(i)+"/D").c_str());// "Cut/C");

        numofevents=relnum.val;
        numofevents_err=relnum.err;

        numofevents_2016=relnum_2016.val;
        numofevents_2016_err=relnum_2016.err;

        numofevents_all=(relnum+relnum_2016).val;
        numofevents_all_err=(relnum+relnum_2016).err;

        fillinfotree.Fill();
        fillinfotree.Write("",TObject::kOverwrite);
	}


     //   fillinfo.cd();
     //   fillinfotree.Fill();
     //   fillinfotree.Write("",TObject::kOverwrite);


        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Calculation of number of events that comes from partially reconstructed backgrounds, assuming 2012 efficiencies but extrapolating to 2011,2012,2016 samples. $\\mathcal{B}(B^+ \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-})$ is obtained by multiplying  $\\mathcal{B}(D^{0} \\rightarrow K^+ \\pi^- \\mu^+ \\mu^{-}) $ and $\\mathcal{B}(B^{+} \\rightarrow D l^{+} \\nu $ anything) = "<<round_to_digits(overall.calculateProduct_BR("pr").val,3)<<"$\\pm$"<< round_to_digits(overall.calculateProduct_BR("pr").err,3)<<". Normalisation channel $B^+ \\rightarrow (J/\\psi \\rightarrow \\mu^+ \\mu^{-}) K^{+}$ was used to normalize to using Run1 and 2016 yields. Assumes PIDratio 1 and qmin cut needs to be accounted for}"<<endl;
        out<<"\\label{tab:prsum}"<<endl;
        out<<"\\end{table}"<<endl;
//        EfficiencyClass highpr;
//        EfficiencyClass nopr;

      




	out<<"\\newpage"<<endl;
	out<<"\\end{document}"<<endl;



	out.close();


        



	//	cout<<mctrutheff*jpsieff*nSharedeff*qmineff<<endl;
	//	double brfr=1e-8;
	//	double ppbbX=284e-6;
	//	double bBplus= 2*0.4;
	//	double datacoll=3e15;
	//	double decprodcut =0.185;
	//	double effrecostrip= 0.111;
	//
	//	double finaleff;
	//	finaleff=ppbbX*bBplus*brfr*datacoll*decprodcut*effrecostrip*jpsieff*nSharedeff*qmineff*triggereff; 
	//	cout<<"Final Num Of Events: "<<finaleff<<endl;




	return(0);



}



