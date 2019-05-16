/*
Name: Stage4.C
Author: Jason Bono
Date: October 25 2012
Purpose: plot polarization


Notes: The input from GetW.C is needed as an input for the W vector which normaized the beam energy spectrum for Xi->lambda + pim events
*/

#include <iostream>
//#include <fstream>
//using namespace std;


  

void Stage4()
{

	gStyle->SetOptFit(); 
	

	//binning (keep this consistant with all stages)
	const int NEBins = 3; 
	const int NXiBins = 3; 
	const int NPiBins = 4;
	
	//open the ouput of Stage3.C
	TFile* fhS3 = new TFile("./hists/histsStage3.root");
	//TFile* fhS4 = new TFile("./hists/histsStage4.root","RECREATE");
	//open two txt files for writing
	
	ofstream myEfile,myXifile;
	myEfile.open ("./txt/Ebins.txt");
	myXifile.open ("./txt/Xibins.txt");
	
	//--------------read in the histograms from stage 3-------------
	//EBins
	TH1F *hDataEx[NEBins];
	TH1F *hDataEy[NEBins];
	TH1F *hDataEz[NEBins];
	for (int i = 0; i < NEBins; i++)
	{
		hDataEx[i] = (TH1F*)fhS3->Get(Form("hDataAc-EBin%i-x",i));
		hDataEy[i] = (TH1F*)fhS3->Get(Form("hDataAc-EBin%i-y",i));
		hDataEz[i] = (TH1F*)fhS3->Get(Form("hDataAc-EBin%i-z",i));
		hDataEx[i]->SetMinimum(0);
		hDataEy[i]->SetMinimum(0);
		hDataEz[i]->SetMinimum(0);
	}
	//XiBins
	TH1F *hDataXix[NXiBins];
	TH1F *hDataXiy[NXiBins];
	TH1F *hDataXiz[NXiBins];
	for (int i = 0; i < NXiBins; i++)
	{
		hDataXix[i] = (TH1F*)fhS3->Get(Form("hDataAc-XiBin%i-x",i));
		hDataXiy[i] = (TH1F*)fhS3->Get(Form("hDataAc-XiBin%i-y",i));
		hDataXiz[i] = (TH1F*)fhS3->Get(Form("hDataAc-XiBin%i-z",i));
		hDataXix[i]->SetMinimum(0);
		hDataXiy[i]->SetMinimum(0);
		hDataXiz[i]->SetMinimum(0);
	}
	//---------------------------------------------------------------
	
	
	//define the fit and the varaibles to parse the parameters to
	TF1 *F1 = new TF1("F1","pol1", -1, 1);
	
	//EBins
	Double_t p0Ex[NEBins], p0Ey[NEBins], p0Ez[NEBins];
	Double_t p0ExEr[NEBins], p0EyEr[NEBins], p0EzEr[NEBins];
	Double_t p1Ex[NEBins], p1Ey[NEBins], p1Ez[NEBins];
	Double_t p1ExEr[NEBins], p1EyEr[NEBins], p1EzEr[NEBins];
	
	//XiBins
	Double_t p0Xix[NXiBins], p0Xiy[NXiBins], p0Xiz[NXiBins];
	Double_t p0XixEr[NXiBins], p0XiyEr[NXiBins], p0XizEr[NXiBins];
	Double_t p1Xix[NXiBins], p1Xiy[NXiBins], p1Xiz[NXiBins];
	Double_t p1XixEr[NXiBins], p1XiyEr[NXiBins], p1XizEr[NXiBins];
	
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EBins~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//fit and display the histograms
	TCanvas *cE = new TCanvas("cE","cE",1000,500);
	cE->Divide(3,NEBins);
	for (int i = 0; i < NEBins; i++)
	{
		
		cE->cd(1 + 3*i);
		hDataEx[i]->Fit("F1","ERQ");
		p0Ex[i] = F1->GetParameter(0);
		p0ExEr[i] = F1->GetParError(0);
	    p1Ex[i] = F1->GetParameter(1);
		p1ExEr[i] = F1->GetParError(1);
		hDataEx[i]->Draw(); 
		
		cE->cd(2 + 3*i);
		hDataEy[i]->Fit("F1","ERQ");
		p0Ey[i] = F1->GetParameter(0);
		p0EyEr[i] = F1->GetParError(0);
		p1Ey[i] = F1->GetParameter(1);
		p1EyEr[i] = F1->GetParError(1);
		hDataEy[i]->Draw();
		
		cE->cd(3 + 3*i);
		hDataEz[i]->Fit("F1","ERQ");
		p0Ez[i] = F1->GetParameter(0);
		p0EzEr[i] = F1->GetParError(0);
		p1Ez[i] = F1->GetParameter(1);
		p1EzEr[i] = F1->GetParError(1);
		hDataEz[i]->Draw();

	}

	//compute polarization and error
	Double_t P[NEBins], Cx[NEBins], Cz[NEBins];
	Double_t PEr[NEBins], CxEr[NEBins], CzEr[NEBins];
	for (int i = 0; i < NEBins; i++)
	{
		Cx[i] = (-2*p1Ex[i])/(-0.458*p0Ex[i]);
		P[i] = (-2*p1Ey[i])/(-0.458*p0Ey[i]);
		Cz[i] = (-2*p1Ez[i])/(-0.458*p0Ez[i]);
		
		CxEr[i] = Cx[i]*sqrt((p1ExEr[i]*p1ExEr[i])/(p1Ex[i]*p1Ex[i]) + (p0ExEr[i]*p0ExEr[i])/(p0Ex[i]*p0Ex[i]));
		PEr[i] = P[i]*sqrt( (p1ExEr[i]*p1ExEr[i])/(p1Ex[i]*p1Ex[i]) + (p0ExEr[i]*p0ExEr[i])/(p0Ex[i]*p0Ex[i]) );
		CzEr[i] = Cz[i]*sqrt((p1ExEr[i]*p1ExEr[i])/(p1Ex[i]*p1Ex[i]) + (p0ExEr[i]*p0ExEr[i])/(p0Ex[i]*p0Ex[i]));
		
		cout <<"---------------------------------------------------------------------"<<endl;
		cout << "i = " << i << " Cx = " << Cx[i] << " pm " << CxEr[i] <<endl;
		cout << "i = " << i << " P = " << P[i] << " pm " << PEr[i] <<endl;
		cout << "i = " << i << " Cz = " << Cz[i] << " pm " << CzEr[i] <<endl;
		
		
		/*
		cout <<"---------------------------------------------------------------------"<<endl;
		cout << "i = " << i << " p0x = " << p0Ex[i] << " #pm " << p0ExEr[i] <<endl;
		cout << "i = " << i << " p0y = " << p0Ey[i] << " #pm " << p0EyEr[i] <<endl;
		cout << "i = " << i << " p0z = " << p0Ez[i] << " #pm " << p0EzEr[i] <<endl;
		cout <<endl;
		cout << "i = " << i << " p1x = " << p1Ex[i] << " #pm " << p1ExEr[i] <<endl;
		cout << "i = " << i << " p1y = " << p1Ey[i] << " #pm " << p1EyEr[i] <<endl;
		cout << "i = " << i << " p1z = " << p1Ez[i] << " #pm " << p1EzEr[i] <<endl;
		cout <<endl;
		*/
	}	
	
	Double_t E[NEBins];
	E[0] = 3.65;
	E[1] = 4.35;
	E[2] = 5.1;
	
	for (int i = 0; i < NEBins; i++)
	{
		myEfile << E[i] <<" "<< Cx[i] <<" "<< CxEr[i] <<" "<< P[i] <<" "<< PEr[i] <<" "<< Cz[i] <<" "<<CzEr[i] <<endl; 
	}
	myEfile.close();
	
	
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	

	
	
	
	
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~XiBins~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//fit and display the histograms
	TCanvas *cXi = new TCanvas("cXi","cXi",1000,500);
	cXi->Divide(3,NXiBins);
	for (int i = 0; i < NXiBins; i++)
	{
		
		cXi->cd(1 + 3*i);
		hDataXix[i]->Fit("F1","ERQ");
		p0Xix[i] = F1->GetParameter(0);
		p0XixEr[i] = F1->GetParError(0);
	    p1Xix[i] = F1->GetParameter(1);
		p1XixEr[i] = F1->GetParError(1);
		hDataXix[i]->Draw(); 
		
		cXi->cd(2 + 3*i);
		hDataXiy[i]->Fit("F1","ERQ");
		p0Xiy[i] = F1->GetParameter(0);
		p0XiyEr[i] = F1->GetParError(0);
		p1Xiy[i] = F1->GetParameter(1);
		p1XiyEr[i] = F1->GetParError(1);
		hDataXiy[i]->Draw();
		
		cXi->cd(3 + 3*i);
		hDataXiz[i]->Fit("F1","ERQ");
		p0Xiz[i] = F1->GetParameter(0);
		p0XizEr[i] = F1->GetParError(0);
		p1Xiz[i] = F1->GetParameter(1);
		p1XizEr[i] = F1->GetParError(1);
		hDataXiz[i]->Draw();

	}

	//compute polarization and error
	Double_t P[NXiBins], Cx[NXiBins], Cz[NXiBins];
	Double_t PEr[NXiBins], CxEr[NXiBins], CzEr[NXiBins];
	for (int i = 0; i < NXiBins; i++)
	{
		Cx[i] = (-2*p1Xix[i])/(-0.458*p0Xix[i]);
		P[i] = (-2*p1Xiy[i])/(-0.458*p0Xiy[i]);
		Cz[i] = (-2*p1Xiz[i])/(-0.458*p0Xiz[i]);
		
		CxEr[i] = Cx[i]*sqrt((p1XixEr[i]*p1XixEr[i])/(p1Xix[i]*p1Xix[i]) + (p0XixEr[i]*p0XixEr[i])/(p0Xix[i]*p0Xix[i]));
		PEr[i] = P[i]*sqrt( (p1XixEr[i]*p1XixEr[i])/(p1Xix[i]*p1Xix[i]) + (p0XixEr[i]*p0XixEr[i])/(p0Xix[i]*p0Ex[i]) );
		CzEr[i] = Cz[i]*sqrt((p1XixEr[i]*p1XixEr[i])/(p1Xix[i]*p1Xix[i]) + (p0XixEr[i]*p0XixEr[i])/(p0Xix[i]*p0Xix[i]));
		
		cout <<"---------------------------------------------------------------------"<<endl;
		cout << "i = " << i << " Cx = " << Cx[i] << " pm " << CxEr[i] <<endl;
		cout << "i = " << i << " P = " << P[i] << " pm " << PEr[i] <<endl;
		cout << "i = " << i << " Cz = " << Cz[i] << " pm " << CzEr[i] <<endl;
		
		

	}	
	
	Double_t Xi[NXiBins];
	Xi[0] = -0.66;
	Xi[1] = 0.0;
	Xi[2] = 0.66;
	
	for (int i = 0; i < NXiBins; i++)
	{
		myXifile << Xi[i] <<" "<< Cx[i] <<" "<< CxEr[i] <<" "<< P[i] <<" "<< PEr[i] <<" "<< Cz[i] <<" "<<CzEr[i] <<endl; 
	}
	myEfile.close();
	
	
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}