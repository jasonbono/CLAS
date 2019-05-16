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

	
	

	//binning (keep this consistant with all stages)
	const int NEBins = 3; 
	const int NXiBins = 3; 
	const int NPiBins = 4;
	
	//open the ouput of Stage2.C and make a new file to write
	TFile* fhS3 = new TFile("./hists/histsStage3.root");
	TFile* fhS4 = new TFile("./hists/histsStage4.root","RECREATE");
	
	
	//read in the histograms from stage 3
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
	
	//define the fit and the varaibles to parse the parameters to
	TF1 *F1 = new TF1("F1","pol1", -1, 1);

	Double_t p0Ex[NEBins], p0Ey[NEBins], p0Ez[NEBins];
	Double_t p0ExEr[NEBins], p0EyEr[NEBins], p0EzEr[NEBins];
	Double_t p1Ex[NEBins], p1Ey[NEBins], p1Ez[NEBins];
	Double_t p1ExEr[NEBins], p1EyEr[NEBins], p1EzEr[NEBins];
	
	
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
	//open a file for writing
	ofstream myfile;
	myfile.open ("./txt/energybins.txt");
	for (int i = 0; i < NEBins; i++)
	{
		myfile << E[i] <<" "<< Cx[i] <<" "<< CxEr[i] <<" "<< P[i] <<" "<< PEr[i] <<" "<< Cz[i] <<" "<<CzEr[i] <<endl; 
	}
	myfile.close();
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}