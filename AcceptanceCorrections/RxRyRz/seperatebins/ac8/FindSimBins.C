
void FindSimBins()
{
	TFile* fMC = new TFile("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t4-t4-2kppim_Basic_Mass3.root"); 
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim");

	const int Ni = 10000; //number of bins displayed in histograms
	const int Nb = 300; //number of energy bins to derive
	const float blow = 2.8;
	const float bhigh = 5.5;
	const int Nx = 300; //number of Xi bins to derive
	const float xlow = -1;
	const float xhigh = 1;
	
	
	////////////////
	
	////////////////// begin energy calculation ///////////////////////////////////////////////
	TCut blowcut = Form("beam > %f",blow);
	TCut bhighcut = Form("beam < %f",bhigh);
	TH1F *hb=new TH1F("hb","",Ni,blow,bhigh);
	hb->GetXaxis()->SetTitle("beam (GeV)");
	tMC->Draw("beam>>hb",blowcut&&bhighcut);
	Int_t bCritera = hb->GetEntries()/Nb;
	int bbinlow = hb->GetXaxis()->FindBin(blow);
	int bbinhigh = hb->GetXaxis()->FindBin(bhigh);
	
	
	float btempval = 0;
	int bbin = 0;
	int bpop =0;
	float bval[Nb - 1] = {0};
	for (int b=0; b<Nb -1; b++)
	{
		for (int i=1; i<Ni; i++)
		{
			bbin = bbinlow + i;
			
			bpop = hb->Integral(bbinlow,bbin);
			if (bpop >= bCritera)
			{
				btempval = hb->GetBinCenter(bbin);
				bval[b] = btempval; //store the value
				bbinlow = bbin; //lowbin for the next b iteration should be the current bin for this iteration.
				i = Ni; //kill i loop the loop		
			}
		}
	}
	

	//create all the beam cuts.
	float bVal[Nb+1];
	bVal[0] = blow;
	bVal[Nb] = bhigh;
	for (int b=0; b< Nb - 1; b++)
	{
		bVal[b+1] = bval[b];
	}

	TCut bcut[Nb];
	for (int b=0; b<Nb; b++)
	{
		bcut[b] =  Form(" exibin[0][%i] = \" beam > %f && beam < %f\"; ",b,bVal[b],bVal[b+1]);
		TString temp = bcut[b];
		cout << temp << endl;
	}
	
	
	
	////////////////////////////////// begin cos(Theta_Xi) calculation ///////////////////////////////////////////////
	TCut xlowcut = Form("Xcmtheta > %f",xlow);
	TCut xhighcut = Form("Xcmtheta < %f",xhigh);
	TH1F *hx=new TH1F("hx","",Ni,xlow,xhigh);
	hx->GetXaxis()->SetTitle("Xcmtheta (GeV)");
	tMC->Draw("Xcmtheta>>hx",xlowcut&&xhighcut);
	Int_t xCritera = hx->GetEntries()/Nx;
	int xbinlow = hx->GetXaxis()->FindBin(xlow);
	int xbinhigh = hx->GetXaxis()->FindBin(xhigh);
	
	
	float xtempval = 0;
	int xbin = 0;
	int xpop =0;
	float xval[Nx - 1] = {0};
	for (int x=0; x<Nx -1; x++)
	{
		for (int i=1; i<Ni; i++)
		{
			xbin = xbinlow + i;
			
			xpop = hx->Integral(xbinlow,xbin);
			if (xpop >= xCritera)
			{
				xtempval = hx->GetBinCenter(xbin);
				xval[x] = xtempval; //store the value
				xbinlow = xbin; //lowbin for the next x iteration should be the current bin for this iteration.
				i = Ni; //kill i loop the loop		
			}
		}
	}
	

	//create all the Xcmtheta cuts.
	float xVal[Nx+1];
	xVal[0] = xlow;
	xVal[Nx] = xhigh;
	for (int x=0; x< Nx - 1; x++)
	{
		xVal[x+1] = xval[x];
	}
	TCut xcut[Nx];
	for (int x=0; x<Nx; x++)
	{
		xcut[x] =  Form(" exibin[1][%i] = \" Xcmtheta > %f && Xcmtheta < %f \" ; ",x,xVal[x],xVal[x+1]);
		TString temp = xcut[x];
		cout << temp << endl;
	}


	for (int b=0; b< Nb+1; b++)
	{
		cout << "eVal[" <<b<<"] = "<<bVal[b]<<";"<<endl;
	}
	for (int x=0; x< Nx+1; x++)
	{
		cout << "xVal[" <<x<<"] = "<<xVal[x]<<";"<<endl;
	}


	cout << "number of energy and xi bin is respectivly: " << Nb <<" and " << Nx <<endl;	
	cout << "number of entries in each energy and xi bin is respectivly: " << bCritera <<" and " << xCritera <<endl;
	
	
	
	
	
}