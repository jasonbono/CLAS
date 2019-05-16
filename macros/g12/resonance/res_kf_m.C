/*

April 13 2012:  made this macro after making the reduced resonance root file for v37k. 
looking for a clear signal at 1620 mev in the spectrum of M(Xi0 + pim). 
this uses side band subraction and uses the !conf cut as the side band events.

THIS DOES NOT COMPUTE THE ERRORS PROPERLY.

*/



void res_kf_m()
{
	TFile *f = TFile::Open("~/clas/rootfiles/g12/resonate/v37k_full_resonate.root");
	TTree *newt = (TTree*)f->Get("v37k_resonate");



	TCut conf2="kf2_prob > 0.1";
	TCut proton = "np == 1";
	TCut cut = conf2 && proton;

	//------------------------------prepare histograms----------------------------------
	TH1F *h0=new TH1F("h0","Xi0",100,0.9,1.9);
	TH1F *h1=new TH1F("h1","resonance",120,1.4,2.0);
	h0->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	h0->GetXaxis()->SetTitle("M(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
	h1->GetYaxis()->SetTitle("Events/5MeV/c^{2}");  
	h1->GetXaxis()->SetTitle("M(#Xi^{0} + #pi^{-}) (GeV/c^{2})");	
	TH1F *hbg = (TH1F*)h1->Clone("hbg");
	TH1F *hbgn = (TH1F*)h1->Clone("hbgn");
	TH1F *hsub = (TH1F*)h1->Clone("hsub");
	
	hbg->SetTitle("unnormalized background");
	hbgn->SetTitle("normalized background");
	hsub->SetTitle("background subtracted");
	//---------------------------------------------------------------------------------



	// both spectrums
	TCanvas *can=new TCanvas("can","",1500,800);
	can->Divide(2,0);
	can->cd(1);	
	newt->Draw("mmkpkppim>>h0",cut);
	h0->Draw();	
	can->cd(2);
	newt->Draw("mcaspim>>h1",cut);
	h1->Draw("E");


	//background of kpkp
	//TH1F *hbg=new TH1F("hbg","",120,1.4,2.0);
	TCanvas *cbg=new TCanvas("cbg","",1500,800);
	newt->Draw("mcaspim>>hbg",!cut);
	hbg->Draw("E");

	
	//normaized bg
	Float_t fac = (h1->GetEntries())/(hbg->GetEntries());	
	cout << "fac = h1/hbg = " << fac <<endl;
	TCanvas *cbgn=new TCanvas("cbgn","",1500,800);
	//TH1F *hbgn=new TH1F("hbgn","",120,1.4,2.0);
	hbgn->Add(hbg, fac);
	hbgn->Draw("E");


	//hist with background subtraction
	TCanvas *csub=new TCanvas("csub","",1500,800);
	//TH1F *hsub=new TH1F("hsub","",120,1.4,2.0);
	hsub->Add(h1, 1);
	hsub->Add(hbgn,-1);
	hsub->Draw();

can->Print("/Users/Bono/clas/macros/g12/resonance/pics/res_kf_m.C/mmkpkppim.eps");
cbg->Print("/Users/Bono/clas/macros/g12/resonance/pics/res_kf_m.C/bg.eps");
cbgn->Print("/Users/Bono/clas/macros/g12/resonance/pics/res_kf_m.C/bgn.eps");
csub->Print("/Users/Bono/clas/macros/g12/resonance/pics/res_kf_m.C/sub.eps");

}

