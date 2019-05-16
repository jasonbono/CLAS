
/*

April 12 2012:  made this macro after making the reduced resonance root file for v37k. 
looking for a clear signal at 1620 mev in the spectrum of MMKPKP. 
this uses side band subraction and uses the !conf cut as the side band events.


*/


void show_Xim()
{
	
	gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS3.C");
	TFile *f = TFile::Open("/Users/Bono/clas/rootfiles/g12/Reduced/2kppim-v05-resonance.root");
	TTree *tRes = (TTree*)f->Get("v05_resonance");
	
	TH1F *h0=new TH1F("h0","Xi0",50,1.2,1.5); //300/50 = 6MeV
	h0->GetYaxis()->SetTitle("Events/6MeV/c^{2}");  
	h0->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
	
	TCanvas *can=new TCanvas("can","",1500,800);
	tRes->Draw("mmkpkppim>>h0");
 	fitGAUS3(h0,1,1.2,1.5,1,1,1,1.321,0.02,3, 1, 1, 1);
}

void show_Xi0()
{
	
	gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS3.C");
	TFile *f = TFile::Open("/Users/Bono/clas/rootfiles/g12/Reduced/2kppim-v05-resonance.root");
	TTree *tRes = (TTree*)f->Get("v05_resonance");
	
	TH1F *h0=new TH1F("h0","Xi0",50,1.2,1.5); //300/50 = 6MeV
	h0->GetYaxis()->SetTitle("Events/6MeV/c^{2}");  
	h0->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
	
	TCanvas *can=new TCanvas("can","",1500,800);
	tRes->Draw("mmkpkppim>>h0");
 	fitGAUS3(h0,1,1.2,1.5,1,1,1,1.321,0.02,3, 1, 1, 1);
}
void res_kf_mm()
{
	TFile *f = TFile::Open("/Users/Bono/clas/rootfiles/g12/Reduced/2kppim-v05-resonance.root");
	TTree *tRes = (TTree*)f->Get("v05_resonance");

	//TCut conf2 = "kf2_prob > 0.05";
	TCut cXi0 = "abs(mmkpkppim - 1.313) < 0.0380";
	TCut cJason =  "abs(mcaspim - mmkpkp) < 0.05 ";
	TCut cut = cXi0&&cJason;


	//------------------------------prepare histograms----------------------------------
	TH1F *h0=new TH1F("h0","Xi0",500,0.9,1.9);
	TH1F *h1=new TH1F("h1","resonance",300,1.4,2.0);
	h0->GetYaxis()->SetTitle("Events/2MeV/c^{2}");  
	h0->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
	h1->GetYaxis()->SetTitle("Events/2MeV/c^{2}");  
	h1->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})");
	TH1F *hbg = (TH1F*)h1->Clone("hbg");
	TH1F *hbgn = (TH1F*)h1->Clone("hbgn");
	TH1F *hsub = (TH1F*)h1->Clone("hsub");
	hbg->SetTitle("unnormalized background");
	hbgn->SetTitle("normalized background");
	hsub->SetTitle("background subtracted");
	//--------------------------------------------


	// both spectrums
	TCanvas *can=new TCanvas("can","",1500,800);
	can->Divide(2,0);
	can->cd(1);	
	tRes->Draw("mmkpkppim>>h0",cut);
	h0->Draw();	
	can->cd(2);
	tRes->Draw("mmkpkp>>h1",cut);
	h1->Draw("E");



	//background of kpkp
	//TH1F *hbg=new TH1F("hbg","",120,1.4,2.0);
	TCanvas *canbg=new TCanvas("canbg","",1500,800);
	tRes->Draw("mmkpkp>>hbg",!cut);
	hbg->Draw("E");


	
	//normaized bg
	Float_t fac = (h1->GetEntries())/(hbg->GetEntries());	
	TCanvas *canbgn=new TCanvas("canbgn","",1500,800);
	//TH1F *hbgn=new TH1F("hbgn","",120,1.4,2.0);
	hbgn->Add(hbg, fac);
	hbgn->Draw("E");



	//hist with background subtraction
	TCanvas *csub=new TCanvas("csub","",1500,800);
	//TH1F *hsub=new TH1F("hsub","",120,1.4,2.0);
	hsub->Add(h1, 1);
	hsub->Add(hbgn,-1);
	hsub->Draw();


	//can->Print("/Users/Bono/clas/macros/g12/resonance/pics/res_kf_mm.C/mmkpkppim.eps");
	//cbg->Print("/Users/Bono/clas/macros/g12/resonance/pics/res_kf_mm.C/bg.eps");
	//cbgn->Print("/Users/Bono/clas/macros/g12/resonance/pics/res_kf_mm.C/bgn.eps");
	//csub->Print("/Users/Bono/clas/macros/g12/resonance/pics/res_kf_mm.C/sub.eps");


}






void res_kf_m()
{

	TFile *f = TFile::Open("/Users/Bono/clas/rootfiles/g12/Reduced/2kppim-v05-resonance.root");
	TTree *tRes = (TTree*)f->Get("v05_resonance");

	TCut cXi0 = "abs(mmkpkppim - 1.313) < 0.03";
	TCut cJason =  "abs(mcaspim - mmkpkp) < 0.03 ";
	TCut cut = cXi0&&cJason;


	//------------------------------prepare histograms----------------------------------
	TH1F *h0=new TH1F("h0","Xi0",500,0.9,1.9);
	TH1F *h1=new TH1F("h1","resonance",300,1.4,2.0);
	h0->GetYaxis()->SetTitle("Events/2MeV/c^{2}");  
	h0->GetXaxis()->SetTitle("M(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
	h1->GetYaxis()->SetTitle("Events/2MeV/c^{2}");  
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
	tRes->Draw("mmkpkppim>>h0",cut);
	h0->Draw();	
	can->cd(2);
	tRes->Draw("mcaspim>>h1",cut);
	h1->Draw("E");


	//background of kpkp
	//TH1F *hbg=new TH1F("hbg","",120,1.4,2.0);
	TCanvas *cbg=new TCanvas("cbg","",1500,800);
	tRes->Draw("mcaspim>>hbg",!cut);
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

	//can->Print("/Users/Bono/clas/macros/g12/resonance/pics/res_kf_m.C/mmkpkppim.eps");
	//cbg->Print("/Users/Bono/clas/macros/g12/resonance/pics/res_kf_m.C/bg.eps");
	//cbgn->Print("/Users/Bono/clas/macros/g12/resonance/pics/res_kf_m.C/bgn.eps");
	//csub->Print("/Users/Bono/clas/macros/g12/resonance/pics/res_kf_m.C/sub.eps");

}


