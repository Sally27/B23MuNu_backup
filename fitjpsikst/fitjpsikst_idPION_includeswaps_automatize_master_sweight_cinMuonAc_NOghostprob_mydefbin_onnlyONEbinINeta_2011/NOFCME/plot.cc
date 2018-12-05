void misIDmu(){


	gStyle->SetOptTitle(0);

	double momentum[13] = {3000 , 6000 , 9300 , 10000 , 12600 , 15600 , 17500 , 21500 , 27000 , 32000 , 40000 , 60000 , 70000};
	double momentum_err[13] = {0., 0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0. };


	Int_t nbins = 13;
	Double_t set1[nbins], set1_err[nbins];
	string set1_name = "Pi isMuon==0";
	int set1_color = kRed;
	int set1_style = 1;

	set1[0] = 0.973; set1_err[0] = 0.03; 
	set1[1] = 1.32; set1_err[1] = 0.04; 
	set1[2] = 1.49; set1_err[2] = 0.1; 
	set1[3] = 1.87; set1_err[3] = 0.09; 
	set1[4] = 1.87; set1_err[4] = 0.11; 
	set1[5] = 2.25; set1_err[5] = 0.19; 
	set1[6] = 2.27; set1_err[6] = 0.16; 
	set1[7] = 2.89; set1_err[7] = 0.22; 
	set1[8] = 3.00; set1_err[8] = 0.32; 
	set1[9] = 4.1; set1_err[9] = 0.4; 
	set1[10] = 4.2; set1_err[10] = 0.4; 
	set1[11] = 5.5; set1_err[11] = 1.1; 
	set1[12] = 7.6; set1_err[12] = 1.2; 


	Double_t set2[nbins], set2_err[nbins];
	string set2_name = "Pi isMuon==0 && PIDmu>0";
	int set2_color = kGreen+2;
	int set2_style = 1;

	set2[0] = 2.3; set2_err[0] = 0.4; 
	set2[1] = 1.95; set2_err[1] = 0.14; 
	set2[2] = 1.97; set2_err[2] = 0.28; 
	set2[3] = 2.26; set2_err[3] = 0.2; 
	set2[4] = 1.66; set2_err[4] = 0.15; 
	set2[5] = 2.08; set2_err[5] = 0.26; 
	set2[6] = 2.1; set2_err[6] = 0.21; 
	set2[7] = 2.68; set2_err[7] = 0.27; 
	set2[8] = 2.53; set2_err[8] = 0.34; 
	set2[9] = 3.7; set2_err[9] = 0.5; 
	set2[10] = 3.6; set2_err[10] = 0.4; 
	set2[11] = 3.3; set2_err[11] = 0.9; 
	set2[12] = 7.2; set2_err[12] = 1.4; 



	Double_t set3[nbins], set3_err[nbins];
	string set3_name = "Pi isMuon==0 && PIDmu>0 && PIDmuK>0";
	int set3_color = kBlue;
	int set3_style = 1;

	set3[0] = 2.9; set3_err[0] = 0.7; 
	set3[1] = 1.75; set3_err[1] = 0.13; 
	set3[2] = 1.94; set3_err[2] = 0.31; 
	set3[3] = 1.95; set3_err[3] = 0.19; 
	set3[4] = 1.46; set3_err[4] = 0.15; 
	set3[5] = 1.9; set3_err[5] = 0.25; 
	set3[6] = 2.02; set3_err[6] = 0.21; 
	set3[7] = 2.27; set3_err[7] = 0.24; 
	set3[8] = 2.12; set3_err[8] = 0.3; 
	set3[9] = 3.3; set3_err[9] = 0.5; 
	set3[10] = 3.1; set3_err[10] = 0.4; 
	set3[11] = 2.4; set3_err[11] = 0.8; 
	set3[12] = 6.7; set3_err[12] = 1.6; 


	Double_t set4[nbins], set4_err[nbins];
	string set4_name = "Pi isMuon==0 && nShared==0";
	int set4_color = kRed;
	int set4_style = kDashed;

	set4[0] = 0.66; set4_err[0] = 0.04; 
	set4[1] = 1.01; set4_err[1] = 0.05; 
	set4[2] = 1.13; set4_err[2] = 0.11; 
	set4[3] = 1.28; set4_err[3] = 0.099; 
	set4[4] = 1.12; set4_err[4] = 0.1; 
	set4[5] = 1.36; set4_err[5] = 0.17; 
	set4[6] = 1.38; set4_err[6] = 0.14; 
	set4[7] = 1.54; set4_err[7] = 0.17; 
	set4[8] = 1.29; set4_err[8] = 0.21; 
	set4[9] = 1.95; set4_err[9] = 0.3; 
	set4[10] = 1.59; set4_err[10] = 0.26; 
	set4[11] = 1.8; set4_err[11] = 0.6; 
	set4[12] = 2.7; set4_err[12] = 0.7; 



	Double_t set5[nbins], set5_err[nbins];
	string set5_name = "Pi isMuon==0 && nShared==0 && ProbNNmu>0.5";
	int set5_color = kCyan;
	int set5_style = kDashed;

	set5[0] = 1.8; set5_err[0] = 1.4; 
	set5[1] = 1.7; set5_err[1] = 0.4; 
	set5[2] = 2.46; set5_err[2] = 0.99; 
	set5[3] = 1.28; set5_err[3] = 0.27; 
	set5[4] = 0.92; set5_err[4] = 0.19; 
	set5[5] = 1.34; set5_err[5] = 0.31; 
	set5[6] = 1.33; set5_err[6] = 0.23; 
	set5[7] = 1.31; set5_err[7] = 0.22; 
	set5[8] = 1.07; set5_err[8] = 0.25; 
	set5[9] = 2.1; set5_err[9] = 0.4; 
	set5[10] = 1.34; set5_err[10] = 0.28; 
	set5[11] = 2.2; set5_err[11] = 0.8; 
	set5[12] = 3; set5_err[12] = 1; 




	Double_t set6[nbins], set6_err[nbins];
	string set6_name = "Pi isMuon==0 && nShared==0 && PIDmu>0 && PIDmuK>0";
	int set6_color = kBlue;
	int set6_style = kDashed;

	set6[0] = 2.5; set6_err[0] = 0.8; 
	set6[1] = 1.55; set6_err[1] = 0.15; 
	set6[2] = 1.57; set6_err[2] = 0.29; 
	set6[3] = 1.34; set6_err[3] = 0.16; 
	set6[4] = 1.1; set6_err[4] = 0.14; 
	set6[5] = 1.54; set6_err[5] = 0.25; 
	set6[6] = 1.52; set6_err[6] = 0.19; 
	set6[7] = 1.42; set6_err[7] = 0.19; 
	set6[8] = 1.17; set6_err[8] = 0.23; 
	set6[9] = 2.1; set6_err[9] = 0.4; 
	set6[10] = 1.47; set6_err[10] = 0.28; 
	set6[11] = 1.2; set6_err[11] = 0.6; 
	set6[12] = 2.6; set6_err[12] = 0.9; 


	Double_t set7[nbins], set7_err[nbins];
	string set7_name = "Pi isMuon==0 && nShared==0 && PIDmu>0 && PIDmuK>0 && ProbNNmu>0.3";
	int set7_color = kMagenta;
	int set7_style = kDashed;


	set7[0] = 5; set7_err[0] = 5; 
	set7[1] = 1.48; set7_err[1] = 0.21; 
	set7[2] = 1.8; set7_err[2] = 0.5; 
	set7[3] = 1.57; set7_err[3] = 0.23; 
	set7[4] = 1.13; set7_err[4] = 0.17; 
	set7[5] = 1.65; set7_err[5] = 0.29; 
	set7[6] = 1.43; set7_err[6] = 0.21; 
	set7[7] = 1.51; set7_err[7] = 0.22; 
	set7[8] = 1.3; set7_err[8] = 0.27; 
	set7[9] = 2.1; set7_err[9] = 0.4; 
	set7[10] = 1.49; set7_err[10] = 0.3; 
	set7[11] = 1.4; set7_err[11] = 0.7; 
	set7[12] = 2.7; set7_err[12] = 1.1; 



	TCanvas *cv = new TCanvas("set1_cv", "set1_cv");
	TLegend *leg = new TLegend(.1,.7,.3,.9);
	leg->SetFillColor(0);
	//mg.SetFillColor(0);<------------compiler doesn't like this particular command
	//
	TGraphErrors* set1_gr = new TGraphErrors(nbins,momentum,set1, momentum_err, set1_err);
	set1_gr->SetLineColor(set1_color);
	set1_gr->SetLineStyle(set1_style);
	set1_gr->Draw("AL");
	set1_gr->GetXaxis()->SetTitle("p [MeV/c]");
	set1_gr->GetYaxis()->SetTitle("Ratio of #pi misID: B #rightarrow J/#psi K^{*0} / PIDCalib");
	leg->AddEntry(set1_gr,set1_name.c_str(),"L");

	TGraphErrors* set2_gr = new TGraphErrors(nbins,momentum,set2, momentum_err, set2_err);
	set2_gr->SetTitle(set2_name.c_str());
	set2_gr->SetLineColor(set2_color);
	set2_gr->SetLineStyle(set2_style);
	set2_gr->Draw("L");
	leg->AddEntry(set2_gr,set2_name.c_str(),"L");

	TGraphErrors* set3_gr = new TGraphErrors(nbins,momentum,set3, momentum_err, set3_err);
	set3_gr->SetTitle(set3_name.c_str());
	set3_gr->SetLineColor(set3_color);
	set3_gr->SetLineStyle(set3_style);
	set3_gr->Draw("L");
	leg->AddEntry(set3_gr,set3_name.c_str(),"L");

	TGraphErrors* set4_gr = new TGraphErrors(nbins,momentum,set4, momentum_err, set4_err);
	set4_gr->SetTitle(set4_name.c_str());
	set4_gr->SetLineColor(set4_color);
	set4_gr->SetLineStyle(set4_style);
	set4_gr->Draw("L");
	leg->AddEntry(set4_gr,set4_name.c_str(),"L");

	TGraphErrors* set5_gr = new TGraphErrors(nbins,momentum,set5, momentum_err, set5_err);
	set5_gr->SetTitle(set5_name.c_str());
	set5_gr->SetLineColor(set5_color);
	set5_gr->SetLineStyle(set5_style);
	set5_gr->Draw("L");
	leg->AddEntry(set5_gr,set5_name.c_str(),"L");

	TGraphErrors* set6_gr = new TGraphErrors(nbins,momentum,set6, momentum_err, set6_err);
	set6_gr->SetTitle(set6_name.c_str());
	set6_gr->SetLineColor(set6_color);
	set6_gr->SetLineStyle(set6_style);
	set6_gr->Draw("L");
	leg->AddEntry(set6_gr,set6_name.c_str(),"L");


	TGraphErrors* set7_gr = new TGraphErrors(nbins,momentum,set7, momentum_err, set7_err);
	set7_gr->SetTitle(set7_name.c_str());
	set7_gr->SetLineColor(set7_color);
	set7_gr->SetLineStyle(set7_style);
	set7_gr->Draw("L");
	leg->AddEntry(set7_gr,set7_name.c_str(),"L");


	leg->DrawClone("Same");





}
