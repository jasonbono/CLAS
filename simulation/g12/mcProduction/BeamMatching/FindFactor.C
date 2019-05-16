


#include "/Users/Bono/clas/myDefinitions/WBins.h" //to provide cut definitions WBin[27]

void FindFactor()
{


	//~~~~~~~~~~~~~~~~~~~~~files~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Data	
	TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v15/hadded/2kppim-v15_Basic_Mass3.root");
	TTree *tData = (TTree*)fData->Get("v15");
	//MC
	TFile *fMC = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t5-t5-2kppim_Basic_Mass3.root");
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
	//Gen
	TFile *fGen = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t5-t5-gamproot-10.root");
	TTree *tGen = (TTree*)fGen->Get("GampTree");
	Double_t gampfactor = 10;
	
	
	
	//declarations
	
	Double_t n[NWBins] = {0}, r[NWBins] = {0},  g[NWBins] = {0}; //data, reconstructed, generated
	Double_t e[NWBins] = {0}, Grel[NWBins] = {0}; //efficency, relitive generation factors
	Double_t HighGrel = 0; //the higest valued element in the Grel array
	Double_t NormFac = 0; //the factor by which to multiply Grel to get Gabs
	Double_t Gabs[NWBins] = {0};  //absoulte generation numbers to use as an input to genr8. this should match the data
	

	//set up can
	TCanvas *cn=new TCanvas("cn","cn",800,600);	
	TCanvas *cr=new TCanvas("cr","cr",800,600);
	TCanvas *cg=new TCanvas("cg","cg",800,600);
	cn->Divide(6,5);
	cr->Divide(6,5);
	cg->Divide(6,5);
	
	//set up hist
	TH1F *h=new TH1F("h","",100,2.6,5.6);
	h->GetYaxis()->SetTitle("Events/3MeV/");  
	h->GetXaxis()->SetTitle(" Eg (GeV)");
	TH1F *hn[NWBins], *hr[NWBins], *hg[NWBins];
	
	//fill the hists
	for (int i = 0; i < NWBins ; i++)
 	{
		//Data
		cn->cd(i + 1);
		hn[i] = (TH1F*)h->Clone(Form("hn%i",i));	
		tData->Draw(Form("beam>>hn%i",i),WBin[i]);	
		n[i] = hn[i]->GetEntries();

		//MC
		cr->cd(i + 1);
		hr[i] = (TH1F*)h->Clone(Form("hr%i",i));	
		tMC->Draw(Form("beam>>hr%i",i),WBin[i]);	
		r[i] = hr[i]->GetEntries();
		
		//Gen
		cg->cd(i + 1);
		hg[i] = (TH1F*)h->Clone(Form("hg%i",i));	
		tGen->Draw(Form("beam>>hg%i",i),WBin[i]);	
		g[i] = hg[i]->GetEntries();
		
		//calculate effecency
		e[i] = r[i]/g[i];
		//calculate generation factors
		Grel[i] = n[i]/e[i];
		
		//find the highest element in Grel
		if (i > 0)
		{
		//	if (Grel[i] > Grel[i-1]) //wrong!
			if (Grel[i] > HighGrel)
			{
				HighGrel = Grel[i];
				NormFac = 100000.0/HighGrel; //based on 100K events
			}
		}							
		
	}
	
	//compute the absoulte generation numbers
	for (int i = 0; i < NWBins ; i++)
 	{
		Gabs[i] = NormFac*Grel[i];
		
		//checking
		cout <<" {n, r, g} = {" <<n[i]<<", "<<r[i]<<", "<<g[i]<<"}"<<endl;
		cout <<" {e, Grel, HighGrel} = {" <<e[i]<<", "<<Grel[i]<<", "<<HighGrel<<"}"<<endl;
		cout <<" {NormFac, Gabs} = {" <<NormFac<<", "<<Gabs[i]<<"}"<<endl;
		cout <<endl;
	}
	
	//
	Float_t Tot = 0;
	for (int i = 0; i < NWBins ; i++)
 	{
		cout << Form(" beam = %f",2.8 + 0.1*i) << "  Generate " << Gabs[i] <<"  events"<<endl;
		Tot += Gabs[i];
	
	}
	
	cout << "Total events generated = " <<Tot<<" * 0.1/stepsize" <<endl;
	cout << "copy and past the following: " <<endl;
	for (int i = 0; i < NWBins ; i++)
 	{
		int temp = Gabs[i];
		//push(@m,17093);
		cout <<"push(@m,"<<temp<<");"<<endl;
	}
	
	
	for (int i = 0; i < NWBins ; i++)
 	{
		int temp = Gabs[i];
		//push(@m,17093);
		cout <<i<<endl;
	}
	
	
	
	
	
	
	
	
}