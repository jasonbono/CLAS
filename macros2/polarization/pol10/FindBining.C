/*

Name: FindBining.C
Author: Jason Bono
Date: Feb 12 2013
Purpose: To find the optimal binning width

*/

#include "/Users/Bono/clas/myDefinitions/Bins226.h"

#include "/Users/Bono/clas/myDefinitions/Hypersphere.h"


void FindBining()
{

	TFile* fData = new TFile("~/clas/rootfiles/LINKS/2kppim-v05.root");	
	TTree *tData = (TTree*)fData->Get("v05_Basic");

	TCut cut=hypersphere;  //hypersphere defined in headder file

	//the hist model is for plotting the beam
	TH1D *h=new TH1D("h","",27,2.8,5.5);
	h->GetYaxis()->SetTitle("Events");  
	h->GetXaxis()->SetTitle("Beam Energy (GeV)");
	h->SetMinimum(0);
	
	
	//declare some rank 2 (arrays)
	int YieldEx[NPiBins][NEBins] = {0}, YieldEy[NPiBins][NEBins] = {0}, YieldEz[NPiBins][NEBins] = {0};
	int YieldXix[NPiBins][NXiBins] = {0}, YieldXiy[NPiBins][NXiBins] = {0}, YieldXiz[NPiBins][NXiBins] = {0};
	TH1D *hEx[NPiBins][NEBins], *hEy[NPiBins][NEBins], *hEz[NPiBins][NEBins];	
	TH1D *hXix[NPiBins][NXiBins], *hXiy[NPiBins][NXiBins], *hXiz[NPiBins][NXiBins];	

	//loop over pion bins
	for (int i = 0; i < NPiBins; i++)
	{
		//loop over energy bins
		for (int j = 0; j < NEBins; j++)
		{
			//energy binning
			hEx[i][j] = (TH1D*)h->Clone(Form("h-PixBin%i-EBin%i",i,j));
			tData->Draw(Form("beam>>h-PixBin%i-EBin%i",i,j),cut&&EBin[j]&&PixBin[i]);
			YieldEx[i][j] = hEx[i][j]->GetEntries();
			hEy[i][j] = (TH1D*)h->Clone(Form("h-PiyBin%i-EBin%i",i,j));
			tData->Draw(Form("beam>>h-PiyBin%i-EBin%i",i,j),cut&&EBin[j]&&PiyBin[i]);
			YieldEy[i][j] = hEy[i][j]->GetEntries();
			hEz[i][j] = (TH1D*)h->Clone(Form("h-PizBin%i-EBin%i",i,j));
			tData->Draw(Form("beam>>h-PizBin%i-EBin%i",i,j),cut&&EBin[j]&&PizBin[i]);
			YieldEz[i][j] = hEz[i][j]->GetEntries();
			
			//cout << " - - - EBins below - - - " << endl;
			//cout <<"YieldEx_PiBin"<< i << "_EBin" << j <<" = " << YieldEx[i][j] << endl;
			//cout <<"YieldEy_PiBin"<< i << "_EBin" << j <<" = " << YieldEy[i][j] << endl;
			//cout <<"YieldEz_PiBin"<< i << "_EBin" << j <<" = " << YieldEz[i][j] << endl;
			//cout <<"........................."<<endl;
			//cout << endl;
			
		}
		
		//loop over Xi bins
		for (int j = 0; j < NXiBins; j++)
		{
			//*//Xi binning
			hXix[i][j] = (TH1D*)h->Clone(Form("h-PixBin%i-XiBin%i",i,j));
			tData->Draw(Form("beam>>h-PixBin%i-XiBin%i",i,j),cut&&XiBin[j]&&PixBin[i]);		
			YieldXix[i][j] = hXix[i][j]->GetEntries();	
			hXiy[i][j] = (TH1D*)h->Clone(Form("h-PiyBin%i-XiBin%i",i,j));
			tData->Draw(Form("beam>>h-PiyBin%i-XiBin%i",i,j),cut&&XiBin[j]&&PiyBin[i]);		
			YieldXiy[i][j] = hXiy[i][j]->GetEntries();
			hXiz[i][j] = (TH1D*)h->Clone(Form("h-PizBin%i-XiBin%i",i,j));
			tData->Draw(Form("beam>>h-PizBin%i-XiBin%i",i,j),cut&&XiBin[j]&&PizBin[i]);		
			YieldXiz[i][j] = hXiz[i][j]->GetEntries();	
			
			//cout << " - - - XiBins below - - - " << endl;
			//cout <<"YieldXix_PiBin"<< i << "_XiBin" << j <<" = " << YieldXix[i][j] << endl;
			//cout <<"YieldXiy_PiBin"<< i << "_XiBin" << j <<" = " << YieldXiy[i][j] << endl;
			//cout <<"YieldXiz_PiBin"<< i << "_XiBin" << j <<" = " << YieldXiz[i][j] << endl;
			//cout << "................................."<<endl;
			//cout << endl;
			//*///
			
		}
	}	
	

	
	
	
	
	//-------------spit out the results-----------------------------------------
	
	//Ebins
	for (int j = 0; j < NEBins; j++)
	{
		cout << endl;
		cout << " - - -pix EBin  " << j <<"  - - - " << endl;
		for (int i = 0; i < NPiBins; i++)
		{
			cout << YieldEx[i][j] << endl;
		}
		
		cout << endl;
		cout << " - - -piy EBin  " << j <<"  - - - " << endl;
		for (int i = 0; i < NPiBins; i++)
		{
			cout << YieldEy[i][j] << endl;
		}
		
		cout << endl;
		cout << " - - -piz EBin  " << j <<"  - - - " << endl;
		for (int i = 0; i < NPiBins; i++)
		{
			cout << YieldEz[i][j] << endl;
		}
		cout << endl;
	}
	
	
	cout <<" . . . . . . . . . . . . . . . . . . . . "<< endl;
	
	//Xibins
	for (int j = 0; j < NXiBins; j++)
	{
		cout << endl;
		cout << " - - -pix XiBin  " << j <<"  - - - " << endl;
		for (int i = 0; i < NPiBins; i++)
		{
			cout << YieldXix[i][j] << endl;
		}
		
		cout << endl;
		cout << " - - -piy XiBin  " << j <<"  - - - " << endl;
		for (int i = 0; i < NPiBins; i++)
		{
			cout << YieldXiy[i][j] << endl;
		}
		
		cout << endl;
		cout << " - - -piz XiBin  " << j <<"  - - - " << endl;
		for (int i = 0; i < NPiBins; i++)
		{
			cout << YieldXiz[i][j] << endl;
		}
		cout << endl;
	}
	
	
	//cout <<"........................."<<endl;
	///cout << endl;
			
			//cout <<"YieldEx_PiBin"<< i << "_EBin" << j <<" = " << YieldEx[i][j] << endl;
			//cout <<"YieldEy_PiBin"<< i << "_EBin" << j <<" = " << YieldEy[i][j] << endl;
			//cout <<"YieldEz_PiBin"<< i << "_EBin" << j <<" = " << YieldEz[i][j] << endl;

			
			//cout << " - - - XiBins below - - - " << endl;
			//cout <<"YieldXix_PiBin"<< i << "_XiBin" << j <<" = " << YieldXix[i][j] << endl;
			//cout <<"YieldXiy_PiBin"<< i << "_XiBin" << j <<" = " << YieldXiy[i][j] << endl;
			//cout <<"YieldXiz_PiBin"<< i << "_XiBin" << j <<" = " << YieldXiz[i][j] << endl;
			//cout << "................................."<<endl;
			//cout << endl;
	
	
	
	
	
	//----------- check for consistancy-------------------------------------
	int Totalx_E_all = 0,Totalx_Xi_all = 0;
	int Totaly_E_all = 0,Totaly_Xi_all = 0;
	int Totalz_E_all = 0,Totalz_Xi_all = 0;
	
	int Totalx_E[NEBins] = {0},Totalx_Xi[NXiBins] = {0};
	int Totaly_E[NEBins] = {0},Totaly_Xi[NXiBins] = {0};
	int Totalz_E[NEBins] = {0},Totalz_Xi[NXiBins] = {0};
	
	//loop over pion bins
	for (int i = 0; i < NPiBins; i++)
	{
		//loop over energy bins
		for (int j = 0; j < NEBins; j++)
		{
			Totalx_E_all += YieldEx[i][j];
			Totaly_E_all += YieldEy[i][j];
			Totalz_E_all += YieldEz[i][j];
			
			Totalx_E[j] += YieldEx[i][j]; 
			Totaly_E[j] += YieldEy[i][j]; 
			Totalz_E[j] += YieldEz[i][j]; 
		}

		//loop over Xi bins
		for (int j = 0; j < NXiBins; j++)
		{
			Totalx_Xi_all += YieldXix[i][j];
			Totaly_Xi_all += YieldXiy[i][j];
			Totalz_Xi_all += YieldXiz[i][j];
			Totalx_Xi[j] += YieldXix[i][j]; 
			Totaly_Xi[j] += YieldXiy[i][j]; 
			Totalz_Xi[j] += YieldXiz[i][j]; 
			

			
		}

	}



	cout << "totals per bin" <<endl;
	cout << "Totalx_E[0] = " << Totalx_E[0] <<endl;
	cout << "Totalx_E[1] = " << Totalx_E[1] <<endl;
	cout << "Totaly_E[0] = " << Totaly_E[0] <<endl;
	cout << "Totaly_E[1] = " << Totaly_E[1] <<endl;
	cout << "Totalz_E[0] = " << Totalz_E[0] <<endl;
	cout << "Totalz_E[1] = " << Totalz_E[1] <<endl;
	cout << endl;
	cout << "Totalx_Xi[0] = " << Totalx_Xi[0] <<endl;
	cout << "Totalx_Xi[1] = " << Totalx_Xi[1] <<endl;
	cout << "Totaly_Xi[0] = " << Totaly_Xi[0] <<endl;
	cout << "Totaly_Xi[1] = " << Totaly_Xi[1] <<endl;
	cout << "Totalz_Xi[0] = " << Totalz_Xi[0] <<endl;
	cout << "Totalz_Xi[1] = " << Totalz_Xi[1] <<endl;

	cout <<endl;
	
	cout << "totals_all" <<endl;
	cout << "Totalx_E_all = " << Totalx_E_all <<endl;
	cout << "Totaly_E_all = " << Totaly_E_all <<endl;
	cout << "Totalz_E_all = " << Totalz_E_all <<endl;
	cout << "Totalx_Xi_all = " << Totalx_Xi_all <<endl;
	cout << "Totaly_Xi_all = " << Totaly_Xi_all <<endl;
	cout << "Totalz_Xi_all = " << Totalz_Xi_all <<endl;


// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .






}














