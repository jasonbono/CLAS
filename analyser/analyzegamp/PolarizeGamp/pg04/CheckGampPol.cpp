#include <iostream>
#include <fstream>
#include <string>
#include <tmath.h>
#include <stdlib.h>
#include <string>
#include <stdio.h>

#include <TF1.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TRandom3.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>


using namespace std;


int main(int argc, char *argv[]) //use argc & argv to pass the file names through the commandline

{

	const float alpha = -0.458;
	
	std::string f(argv[1]);
	TFile *file = TFile::Open(f.c_str());	
	TTree *tree = (TTree*)file->Get("GampTree");

	
	
	

	TCanvas *cPol = new TCanvas("cPol","cPol",1000,800);
	cPol ->Divide(3,1);
	TH1F *h = new TH1F("h","",20,-1,1);
	TH1F *hPol[3];
	for (int i =0; i < 3; i++)
	{
		hPol[i] = (TH1F*)h->Clone(Form("h%i",i));
		hPol[i]->SetMinimum(0);		
	}


	cPol->cd(1);
	tree->Draw("COS_pi_x >>h0");
	cPol->cd(2);
	tree->Draw("COS_pi_y >>h1");
	cPol->cd(3);
	tree->Draw("COS_pi_z >>h2");
/*
	cPol->cd(4);
	NegTree->Draw("COS_pi_x >>h3");
	cPol->cd(5);
	NegTree->Draw("COS_pi_y >>h4");
	cPol->cd(3);
	NegTree->Draw("COS_pi_z >>h5");
*/		
	TF1 *f1 = new TF1("f1",Form("[0] + [0]*%f*[1]*x",alpha),-1,1);
	double p0[3] = {0}, p1[3] = {0}, ep0[3] = {0}, ep1[3] = {0};
	double Polarization[3] = {0}, ePolarization[3] = {0};	
	for (int i =0; i < 3; i++)
	{
		//*///
		cPol->cd(i + 1);
		hPol[i]->Fit("f1","E");
		p0[i] = f1->GetParameter(0);
		ep0[i] = f1->GetParError(0);
		p1[i] = f1->GetParameter(1);
		ep1[i] = f1->GetParError(1);
		Polarization[i] = p1[i];
		ePolarization[i] = ep1[i];
		//*///
		/*///
		hPol[i]->Fit("pol1");
		TF1 *myfit = hPol[i]->GetFunction("pol1");
		p0[i] = myfit->GetParameter(0);
		ep0[i] = myfit->GetParError(0);
		p1[i] = myfit->GetParameter(1);
		ep1[i] = myfit->GetParError(1);
		Polarization[i] = (1/alpha)*(p1[i]/p0[i]);
		ePolarization[i] = (1/alpha)*( (ep0[i])*(p1[i]/(p0[i]*p0[i])) + (ep1[i]/p0[i])  );
		//*///
		
		cout << "p0 = " << p0[i] << "  ep0 = " << ep0[i] <<"  p1 = " << p1[i] << "  ep1 = " << ep1[i] <<endl;
	}
	
	
	//*///
	TLatex *mytex=new TLatex(0.0, 0.0,"mytex");
	for (int i =0; i < 3; i++)
	{
		cPol->cd(i + 1);
		mytex=new TLatex(-0.4, 4000,Form("P = %5.3f #pm %5.3f ",Polarization[i],ePolarization[i]));
		mytex->Draw("SAME");
	}
	
	///*////
	
	
	cPol->Print("./result.eps");
	
	
}
