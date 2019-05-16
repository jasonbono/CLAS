/*
Name: Stage4.C
Author: Jason Bono
Date: October 25 2012
Purpose: plot polarization
Input: ./hists/histsStage3.root
Output: ./txt/Ebins.txt & Xibins.txt

Notes:
	!Read the comment section in GetW.C for more background!
*/


#include "/Users/Bono/clas/myDefinitions/Bins336.h" //kept for NBins definitions, must match Stage1.C

#include <iostream>
//#include <fstream>
//using namespace std;


void Stage4()
{
	//some syle for the plots
	gStyle->SetErrorX(0.0);
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);

	char *s = new char[1];
	const bool asym = 0; //0 means no
	if (asym)
	{
		cout << "calculating polarization through assymetrey:" <<endl;
		cout << "hit enter to accept" <<endl;
		gets(s);
		cout << "assymetrey method accepted!" <<endl;
	}
	else if (!asym)
	{
		cout << "calculating polarization through fitting the regression line:" <<endl;
		cout << "hit enter to accept" <<endl;
		gets(s);
		cout << "regression fit accepted!" <<endl;
	}
	
	
		
	if (asym && NPiBins != 2){
		cout <<" only select asymetery method with NPiBins = 2" <<endl;
		gROOT->ProcessLine(".q");
	}
	
	
	
	//open the ouput of Stage3.C
	TFile* fhS3 = new TFile("./hists/histsStage3.root");
	
	//open two txt files for writing	
	ofstream myEfile,myXifile;
	myEfile.open ("./txt/Ebins.txt");
	myXifile.open ("./txt/Xibins.txt");
	
	//--------------read in the histograms from stage 3-------------
	//EBins
	TH1D *hDataEx[NEBins];
	TH1D *hDataEy[NEBins];
	TH1D *hDataEz[NEBins];
	for (int i = 0; i < NEBins; i++)
	{
		hDataEx[i] = (TH1D*)fhS3->Get(Form("hDataAc-EBin%i-x",i));
		hDataEy[i] = (TH1D*)fhS3->Get(Form("hDataAc-EBin%i-y",i));
		hDataEz[i] = (TH1D*)fhS3->Get(Form("hDataAc-EBin%i-z",i));
		hDataEx[i]->SetMinimum(0);
		hDataEy[i]->SetMinimum(0);
		hDataEz[i]->SetMinimum(0);

		
		//.................more style.............
		hDataEx[i]->SetLabelSize(0.05);
		hDataEx[i]->GetXaxis()->SetTitleSize(0.07);
		hDataEx[i]->GetYaxis()->SetTitleSize(0.07);
		hDataEx[i]->SetMarkerColor(4);
		hDataEx[i]->SetLineColor(4);
		hDataEx[i]->GetXaxis()->CenterTitle();
		hDataEx[i]->GetYaxis()->CenterTitle();
		
		hDataEy[i]->SetLabelSize(0.05);
		hDataEy[i]->GetXaxis()->SetTitleSize(0.07);
		hDataEy[i]->GetYaxis()->SetTitleSize(0.07);
		hDataEy[i]->SetMarkerColor(4);
		hDataEy[i]->SetLineColor(4);
		hDataEy[i]->GetXaxis()->CenterTitle();
		hDataEy[i]->GetYaxis()->CenterTitle();
		
		hDataEz[i]->SetLabelSize(0.05);
		hDataEz[i]->GetXaxis()->SetTitleSize(0.07);
		hDataEz[i]->GetYaxis()->SetTitleSize(0.07);
		hDataEz[i]->SetMarkerColor(4);
		hDataEz[i]->SetLineColor(4);
		hDataEz[i]->GetXaxis()->CenterTitle();
		hDataEz[i]->GetYaxis()->CenterTitle();
		//...........................................	
		
	}

	//XiBins
	TH1D *hDataXix[NXiBins];
	TH1D *hDataXiy[NXiBins];
	TH1D *hDataXiz[NXiBins];
	for (int i = 0; i < NXiBins; i++)
	{
		hDataXix[i] = (TH1D*)fhS3->Get(Form("hDataAc-XiBin%i-x",i));
		hDataXiy[i] = (TH1D*)fhS3->Get(Form("hDataAc-XiBin%i-y",i));
		hDataXiz[i] = (TH1D*)fhS3->Get(Form("hDataAc-XiBin%i-z",i));
		hDataXix[i]->SetMinimum(0);
		hDataXiy[i]->SetMinimum(0);
		hDataXiz[i]->SetMinimum(0);
		
		//.................more style.............
		hDataXix[i]->SetLabelSize(0.05);
		hDataXix[i]->GetXaxis()->SetTitleSize(0.07);
		hDataXix[i]->GetYaxis()->SetTitleSize(0.07);
		hDataXix[i]->SetMarkerColor(4);
		hDataXix[i]->SetLineColor(4);
		hDataXix[i]->GetXaxis()->CenterTitle();
		hDataXix[i]->GetYaxis()->CenterTitle();
		
		hDataXiy[i]->SetLabelSize(0.05);
		hDataXiy[i]->GetXaxis()->SetTitleSize(0.07);
		hDataXiy[i]->GetYaxis()->SetTitleSize(0.07);
		hDataXiy[i]->SetMarkerColor(4);
		hDataXiy[i]->SetLineColor(4);
		hDataXiy[i]->GetXaxis()->CenterTitle();
		hDataXiy[i]->GetYaxis()->CenterTitle();
		
		hDataXiz[i]->SetLabelSize(0.05);
		hDataXiz[i]->GetXaxis()->SetTitleSize(0.07);
		hDataXiz[i]->GetYaxis()->SetTitleSize(0.07);
		hDataXiz[i]->SetMarkerColor(4);
		hDataXiz[i]->SetLineColor(4);
		hDataXiz[i]->GetXaxis()->CenterTitle();
		hDataXiz[i]->GetYaxis()->CenterTitle();
		//...........................................
		
	}
	//---------------------------------------------------------------
	
	//define the fit and the varaibles to parse the parameters to
	TF1 *F1 = new TF1("F1","pol1", -1, 1);
	TF1 *F2 = new TF1("F2", "[0] + 4.366*[0]*[1]*x", -1, 1);
	F1->SetLineWidth(2);
	F2->SetLineWidth(2);
	
	//EBins
	Double_t p0Ex[NEBins] = {0}, p0Ey[NEBins] = {0}, p0Ez[NEBins] = {0};
	Double_t p0ExEr[NEBins] = {0}, p0EyEr[NEBins] = {0}, p0EzEr[NEBins] = {0};
	Double_t p1Ex[NEBins] = {0}, p1Ey[NEBins] = {0}, p1Ez[NEBins] = {0};
	Double_t p1ExEr[NEBins] = {0}, p1EyEr[NEBins] = {0}, p1EzEr[NEBins] = {0};
	
	//XiBins
	Double_t p0Xix[NXiBins] = {0}, p0Xiy[NXiBins] = {0}, p0Xiz[NXiBins] = {0};
	Double_t p0XixEr[NXiBins] = {0}, p0XiyEr[NXiBins] = {0}, p0XizEr[NXiBins] = {0};
	Double_t p1Xix[NXiBins] = {0}, p1Xiy[NXiBins] = {0}, p1Xiz[NXiBins] = {0};
	Double_t p1XixEr[NXiBins] = {0}, p1XiyEr[NXiBins] = {0}, p1XizEr[NXiBins] = {0};
	
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EBins~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//fit and display the histograms
	TLatex *tex0=new TLatex(0.0, 0.0,"STUFF0");
	TLatex *tex1=new TLatex(0.0, 0.0,"STUFF1");
	
	Double_t yy0,yy1;
	TCanvas *cE = new TCanvas("cE","cE",2000,1000);
	cE->Divide(3,NEBins);
	for (int i = 0; i < NEBins; i++)
	{
		
		if (asym && NPiBins == 2){
			cE->cd(1 + 3*i);
			gPad->SetMargin(0.15,0.1,0.15,0.14);
			hDataEx[i]->Draw();
			cE->cd(2 + 3*i);
			gPad->SetMargin(0.15,0.1,0.15,0.14);
			hDataEy[i]->Draw();
			cE->cd(3 + 3*i);
			gPad->SetMargin(0.15,0.1,0.15,0.14);
		    hDataEz[i]->Draw();
		 	
			//fill the assymetery values
			//P0 = Denominator in A
			p0Ex[i] = hDataEx[i]->GetBinContent(1) + hDataEx[i]->GetBinContent(2);
			p0Ey[i] = hDataEy[i]->GetBinContent(1) + hDataEy[i]->GetBinContent(2);
			p0Ez[i] = hDataEz[i]->GetBinContent(1) + hDataEz[i]->GetBinContent(2);
			p0ExEr[i] = hDataEx[i]->GetBinError(1) + hDataEx[i]->GetBinError(2);
			p0EyEr[i] = hDataEy[i]->GetBinError(1) + hDataEy[i]->GetBinError(2);
			p0EzEr[i] = hDataEz[i]->GetBinError(1) + hDataEz[i]->GetBinError(2);
			//P1 = Numerator in A
			p1Ex[i] = hDataEx[i]->GetBinContent(2) - hDataEx[i]->GetBinContent(1);
			p1Ey[i] = hDataEy[i]->GetBinContent(2) - hDataEy[i]->GetBinContent(1);
			p1Ez[i] = hDataEz[i]->GetBinContent(2) - hDataEz[i]->GetBinContent(1);
			p1ExEr[i] = hDataEx[i]->GetBinError(2) + hDataEx[i]->GetBinError(1);
			p1EyEr[i] = hDataEy[i]->GetBinError(2) + hDataEy[i]->GetBinError(1);
			p1EzEr[i] = hDataEz[i]->GetBinError(2) + hDataEz[i]->GetBinError(1);
		}

		
		
		if (!asym){
			cE->cd(1 + 3*i);
			gPad->SetMargin(0.15,0.1,0.15,0.14);
			hDataEx[i]->Fit("F1","Q","",-0.5,1);
			p0Ex[i] = F1->GetParameter(0);
			p0ExEr[i] = F1->GetParError(0);
	    	p1Ex[i] = F1->GetParameter(1);
			p1ExEr[i] = F1->GetParError(1);
			hDataEx[i]->Draw(); 

			cE->cd(2 + 3*i);
			gPad->SetMargin(0.15,0.1,0.15,0.14);
			hDataEy[i]->Fit("F1","RQ");
			p0Ey[i] = F1->GetParameter(0);
			p0EyEr[i] = F1->GetParError(0);
			p1Ey[i] = F1->GetParameter(1);
			p1EyEr[i] = F1->GetParError(1);
			hDataEy[i]->Draw();

			
			cE->cd(3 + 3*i);
			gPad->SetMargin(0.15,0.1,0.15,0.14);
			hDataEz[i]->Fit("F1","RQ","",-1,0.5);
			p0Ez[i] = F1->GetParameter(0);
			p0EzEr[i] = F1->GetParError(0);
			p1Ez[i] = F1->GetParameter(1);
			p1EzEr[i] = F1->GetParError(1);
			hDataEz[i]->Draw();
		}
	}
	//compute polarization and error
	Double_t P[NEBins] = {0}, Cx[NEBins] = {0}, Cz[NEBins] = {0};
	Double_t PEr[NEBins] = {0}, CxEr[NEBins] = {0}, CzEr[NEBins] = {0};
	for (int i = 0; i < NEBins; i++)
	{
		Cx[i] = (-2*p1Ex[i])/(-0.458*p0Ex[i]);
		P[i] = (-2*p1Ey[i])/(-0.458*p0Ey[i]);
		Cz[i] = (-2*p1Ez[i])/(-0.458*p0Ez[i]);
		
		CxEr[i] = sqrt(Cx[i]*Cx[i])*sqrt((p1ExEr[i]*p1ExEr[i])/(p1Ex[i]*p1Ex[i]) + (p0ExEr[i]*p0ExEr[i])/(p0Ex[i]*p0Ex[i]));
		PEr[i] = sqrt(P[i]*P[i])*sqrt((p1EyEr[i]*p1EyEr[i])/(p1Ey[i]*p1Ey[i]) + (p0EyEr[i]*p0EyEr[i])/(p0Ey[i]*p0Ey[i]));
		CzEr[i] = sqrt(Cz[i]*Cz[i])*sqrt((p1EzEr[i]*p1EzEr[i])/(p1Ez[i]*p1Ez[i]) + (p0EzEr[i]*p0EzEr[i])/(p0Ez[i]*p0Ez[i]));
		
		//slap on the latex lables 
		//x
		cE->cd(1 + 3*i);
		yy0 = (0.35)*(hDataEx[i]->GetMaximum());
		yy1 = (0.2)*(hDataEx[i]->GetMaximum());
		tex0=new TLatex(-0.9, yy0,Form("Cx = %5.3f #pm %5.3f ",Cx[i],CxEr[i]));
		tex0->SetTextSize(0.06); 
		tex0->SetTextColor(4);
		tex0->Draw("SAME");	
		
		//y
		cE->cd(2 + 3*i);
		yy0 = (0.35)*(hDataEy[i]->GetMaximum());
		yy1 = (0.2)*(hDataEy[i]->GetMaximum());
		tex0=new TLatex(-0.9, yy0,Form("P = %5.3f #pm %5.3f ",P[i],PEr[i]));
		tex0->SetTextSize(0.06); 
		tex0->SetTextColor(4);
		tex0->Draw("SAME");
		
		//z
		cE->cd(3 + 3*i);
		yy0 = (0.35)*(hDataEz[i]->GetMaximum());
		yy1 = (0.2)*(hDataEz[i]->GetMaximum());
		tex0=new TLatex(-0.9, yy0,Form("Cz = %5.3f #pm %5.3f ",Cz[i],CzEr[i]));
		tex0->SetTextSize(0.06); 
		tex0->SetTextColor(4);
		tex0->Draw("SAME");
		
		cout <<"---------------------------------------------------------------------"<<endl;
		cout << "i = " << i << " Cx = " << Cx[i] << " pm " << CxEr[i] <<endl;
		cout << "i = " << i << " P = " << P[i] << " pm " << PEr[i] <<endl;
		cout << "i = " << i << " Cz = " << Cz[i] << " pm " << CzEr[i] <<endl;
			

	}	
	

	
	Double_t E[NEBins];
	if (NEBins == 3)
	{
		E[0] = 3.25;
		E[1] = 4.15;
		E[2] = 5.05;
	}
	if (NEBins == 2)
	{
		E[0] = 3.475;
		E[1] = 4.825;
	}
	for (int i = 0; i < NEBins; i++)
	{
		myEfile << E[i] <<" "<< Cx[i] <<" "<< CxEr[i] <<" "<< P[i] <<" "<< PEr[i] <<" "<< Cz[i] <<" "<<CzEr[i] <<endl; 
	}
	myEfile.close();
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~XiBins~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//fit and display the histograms
	TLatex *tex2=new TLatex(0.0, 0.0,"STUFF2");
	TLatex *tex3=new TLatex(0.0, 0.0,"STUFF3");

	//fit and display the histograms
	TCanvas *cXi = new TCanvas("cXi","cXi",2000,1000);
	cXi->Divide(3,NXiBins);
	for (int i = 0; i < NXiBins; i++)
	{
			
		
		if (asym && NPiBins == 2){
			cXi->cd(1 + 3*i);
			gPad->SetMargin(0.15,0.1,0.15,0.14);
			hDataXix[i]->Draw();
			cXi->cd(2 + 3*i);
			gPad->SetMargin(0.15,0.1,0.15,0.14);
			hDataXiy[i]->Draw();
			cXi->cd(3 + 3*i);
			gPad->SetMargin(0.15,0.1,0.15,0.14);
		    hDataXiz[i]->Draw();
		 	
			//fill the assymetery values
			//P0 = Denominator in A
			p0Xix[i] = hDataXix[i]->GetBinContent(1) + hDataXix[i]->GetBinContent(2);
			p0Xiy[i] = hDataXiy[i]->GetBinContent(1) + hDataXiy[i]->GetBinContent(2);
			p0Xiz[i] = hDataXiz[i]->GetBinContent(1) + hDataXiz[i]->GetBinContent(2);
			p0XixEr[i] = hDataXix[i]->GetBinError(1) + hDataXix[i]->GetBinError(2);
			p0XiyEr[i] = hDataXiy[i]->GetBinError(1) + hDataXiy[i]->GetBinError(2);
			p0XizEr[i] = hDataXiz[i]->GetBinError(1) + hDataXiz[i]->GetBinError(2);
			//P1 = Numerator in A
			p1Xix[i] = hDataXix[i]->GetBinContent(2) - hDataXix[i]->GetBinContent(1);
			p1Xiy[i] = hDataXiy[i]->GetBinContent(2) - hDataXiy[i]->GetBinContent(1);
			p1Xiz[i] = hDataXiz[i]->GetBinContent(2) - hDataXiz[i]->GetBinContent(1);
			p1XixEr[i] = hDataXix[i]->GetBinError(2) + hDataXix[i]->GetBinError(1);
			p1XiyEr[i] = hDataXiy[i]->GetBinError(2) + hDataXiy[i]->GetBinError(1);
			p1XizEr[i] = hDataXiz[i]->GetBinError(2) + hDataXiz[i]->GetBinError(1);
		}
		
		
		if (!asym){
			cXi->cd(1 + 3*i);
			gPad->SetMargin(0.15,0.1,0.15,0.14);
			hDataXix[i]->Fit("F1","RQ","",-0.5,1);
			p0Xix[i] = F1->GetParameter(0);
			p0XixEr[i] = F1->GetParError(0);
	    	p1Xix[i] = F1->GetParameter(1);
			p1XixEr[i] = F1->GetParError(1);
			hDataXix[i]->Draw(); 
		
			cXi->cd(2 + 3*i);
			gPad->SetMargin(0.15,0.1,0.15,0.14);
			hDataXiy[i]->Fit("F1","RQ");
			p0Xiy[i] = F1->GetParameter(0);
			p0XiyEr[i] = F1->GetParError(0);
			p1Xiy[i] = F1->GetParameter(1);
			p1XiyEr[i] = F1->GetParError(1);
			hDataXiy[i]->Draw();
		
			cXi->cd(3 + 3*i);
			gPad->SetMargin(0.15,0.1,0.15,0.14);
			hDataXiz[i]->Fit("F1","RQ","",-1,0.5);
			p0Xiz[i] = F1->GetParameter(0);
			p0XizEr[i] = F1->GetParError(0);
			p1Xiz[i] = F1->GetParameter(1);
			p1XizEr[i] = F1->GetParError(1);
			hDataXiz[i]->Draw();
		}
	}

	//compute polarization and error
	Double_t P[NXiBins] = {0}, Cx[NXiBins] = {0}, Cz[NXiBins] = {0};
	Double_t PEr[NXiBins] = {0}, CxEr[NXiBins] = {0}, CzEr[NXiBins] = {0};
	for (int i = 0; i < NXiBins; i++)
	{
		Cx[i] = (-2*p1Xix[i])/(-0.458*p0Xix[i]);
		P[i] = (-2*p1Xiy[i])/(-0.458*p0Xiy[i]);
		Cz[i] = (-2*p1Xiz[i])/(-0.458*p0Xiz[i]);
		
		CxEr[i] = sqrt(Cx[i]*Cx[i])*sqrt((p1XixEr[i]*p1XixEr[i])/(p1Xix[i]*p1Xix[i]) + (p0XixEr[i]*p0XixEr[i])/(p0Xix[i]*p0Xix[i]));
		PEr[i] = sqrt(P[i]*P[i])*sqrt( (p1XiyEr[i]*p1XiyEr[i])/(p1Xiy[i]*p1Xiy[i]) + (p0XiyEr[i]*p0XiyEr[i])/(p0Xiy[i]*p0Ey[i]) );
		CzEr[i] = sqrt(Cz[i]*Cz[i])*sqrt((p1XizEr[i]*p1XizEr[i])/(p1Xiz[i]*p1Xiz[i]) + (p0XizEr[i]*p0XizEr[i])/(p0Xiz[i]*p0Xiz[i]));

		//slap on the latex lables 
		//x
		cXi->cd(1 + 3*i);
		yy0 = (0.35)*(hDataXix[i]->GetMaximum());
		yy1 = (0.2)*(hDataXix[i]->GetMaximum());
		tex2=new TLatex(-0.9, yy0,Form("Cx = %5.3f #pm %5.3f ",Cx[i],CxEr[i]));
		tex2->SetTextSize(0.06); 
		tex2->SetTextColor(4);
		tex2->Draw("SAME");	
		
		//y
		cXi->cd(2 + 3*i);
		yy0 = (0.35)*(hDataXiy[i]->GetMaximum());
		yy1 = (0.2)*(hDataXiy[i]->GetMaximum());
		tex2=new TLatex(-0.9, yy0,Form("P = %5.3f #pm %5.3f ",P[i],PEr[i]));
		tex2->SetTextSize(0.06); 
		tex2->SetTextColor(4);
		tex2->Draw("SAME");
		
		//z
		cXi->cd(3 + 3*i);
		yy0 = (0.35)*(hDataXiz[i]->GetMaximum());
		yy1 = (0.2)*(hDataXiz[i]->GetMaximum());
		tex2=new TLatex(-0.9, yy0,Form("Cz = %5.3f #pm %5.3f ",Cz[i],CzEr[i]));
		tex2->SetTextSize(0.06); 
		tex2->SetTextColor(4);
		tex2->Draw("SAME");
		
		cout <<"---------------------------------------------------------------------"<<endl;
		cout << "i = " << i << " Cx = " << Cx[i] << " pm " << CxEr[i] <<endl;
		cout << "i = " << i << " P = " << P[i] << " pm " << PEr[i] <<endl;
		cout << "i = " << i << " Cz = " << Cz[i] << " pm " << CzEr[i] <<endl;
	}	
	Double_t Xi[NXiBins];
	if (NXiBins == 3)
	{
		Xi[0] = -0.66;
		Xi[1] = 0.0;
		Xi[2] = 0.66;
	}
	if (NXiBins == 3)
	{
		Xi[0] = -0.5;
		Xi[1] = 0.5;
	}
	
	
	for (int i = 0; i < NXiBins; i++)
	{
		myXifile << Xi[i] <<" "<< Cx[i] <<" "<< CxEr[i] <<" "<< P[i] <<" "<< PEr[i] <<" "<< Cz[i] <<" "<<CzEr[i] <<endl; 
	}
	myEfile.close();
	
	
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	
}