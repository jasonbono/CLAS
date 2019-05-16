


void CheckGampPol()
{
	
	const float alpha = -0.458;
	

		TFile *file = TFile::Open("/Users/Bono/clas/rootfiles/LINKS/MC-i5-PosPol-gamproot.root");
		TTree *PosTree = (TTree*)file->Get("GampTree");
		TTree *NegTree = (TTree*)file->Get("GampTree");

/*	
	TFile *file = TFile::Open("./PolarizedGamp.root");
	TTree *PosTree = (TTree*)file->Get("PosPolarized_Gamp");
	TTree *NegTree = (TTree*)file->Get("NegPolarized_Gamp");
*/	
	TCanvas *cPol = new TCanvas("cPol","cPol",1000,800);
	cPol ->Divide(3,2);
	TH1F *h = new TH1F("h","",20,-1,1);
	TH1F *hPol[6];
	for (int i =0; i < 6; i++)
	{
		hPol[i] = (TH1F*)h->Clone(Form("h%i",i));
		hPol[i]->SetMinimum(0);		
	}


	cPol->cd(1);
	PosTree->Draw("COS_pi_x >>h0");
	cPol->cd(2);
	PosTree->Draw("COS_pi_y >>h1");
	cPol->cd(3);
	PosTree->Draw("COS_pi_z >>h2");
	cPol->cd(4);
	NegTree->Draw("COS_pi_x >>h3");
	cPol->cd(5);
	NegTree->Draw("COS_pi_y >>h4");
	cPol->cd(6);
	NegTree->Draw("COS_pi_z >>h5");
	
	TF1 *f1 = new TF1("f1",Form("[0] - [0]*%f*[1]*x",alpha),-1,1);
	double p0[6] = {0}, p1[6] = {0}, ep0[6] = {0}, ep1[6] = {0};
	double Polarization[6] = {0}, ePolarization[6] = {0};	
	for (int i =0; i < 6; i++)
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
		Polarization[i] = (-1/alpha)*(p1[i]/p0[i]);
		ePolarization[i] = (-1/alpha)*( (ep0[i])*(p1[i]/(p0[i]*p0[i])) + (ep1[i]/p0[i])  );
		//*///
		
		cout << "p0 = " << p0[i] << "  ep0 = " << ep0[i] <<"  p1 = " << p1[i] << "  ep1 = " << ep1[i] <<endl;
	}
	
	
	//*///
	TLatex *mytex=new TLatex(0.0, 0.0,"mytex");
	for (int i =0; i < 6; i++)
	{
		cPol->cd(i + 1);
		mytex=new TLatex(-0.4, 0,Form("P = %5.3f #pm %5.3f ",Polarization[i],ePolarization[i]));
		mytex->Draw("SAME");
	}
	
	///*////
	
	
	
}