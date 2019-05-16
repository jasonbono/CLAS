
// TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/hadded/2kppim-v05.root");
// TTree *tData = (TTree*)fData->Get("v05");


 TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v16/hadded/2kppim-v16_Basic.root");
 TTree *tData = (TTree*)fData->Get("v16");

// TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v15/hadded/2kppim-v15_Basic_Mass3.root");
// TTree *tData = (TTree*)fData->Get("v15");

void ShowCuts(){	
	//BetaVsP();
	//Vertex();	
	Mass2d();
}


void BetaVsP(){
	StyleUp();
	gStyle->SetTitleXOffset(0.9);
	gStyle->SetTitleYOffset(0.8);
	gStyle->SetTitleSize(0.04);
	gStyle->SetTitleYSize(0.05);
	Float_t mpim = 0.13957;
	Float_t mkp = 0.49367;
	TF1 *fkaon = new TF1("fkaon","x/sqrt(x*x + 0.49367*0.49367)",0,4);
	TF1 *fpion = new TF1("fpion","x/sqrt(x*x + 0.13957*0.13957)",0,1);
	fkaon->SetLineWidth(2);
	fpion->SetLineWidth(2);
	fkaon->SetLineStyle(1);
	fpion->SetLineStyle(1);
	fkaon->SetLineColor(46);
	fpion->SetLineColor(46);
	
	TCanvas *ck1=new TCanvas("ck1","K^{+}_{fast}",1000,800);
	TH2F *h=new TH2F("h","K^{+}_{fast}",150, 0, 4, 150, 0.4, 1.2);
	h->GetYaxis()->SetTitle("   tof_#beta");
	h->GetXaxis()->SetTitle("p (GeV/c)");
	tData->Draw("tofbetakp1:pkp1>>h","","contz");
	fkaon->Draw("same");
		
	TCanvas *ck2=new TCanvas("ck2","K^{+}_{slow}",1000,800);
	TH2F *h=new TH2F("h","K^{+}_{slow}",150, 0,3.5, 150, 0.4, 1.2);
	h->GetYaxis()->SetTitle("   tof_#beta");
	h->GetXaxis()->SetTitle("p (GeV/c)");
	tData->Draw("tofbetakp2:pkp2>>h","","contz");
	fkaon->Draw("same");
		
	TCanvas *cpi=new TCanvas("cpi","#pi^{-}",1000,800);
	TH2F *h=new TH2F("h","#pi^{-}",150, 0, 1, 150, 0.4, 1.2);
	h->GetYaxis()->SetTitle("   tof_#beta");
	h->GetXaxis()->SetTitle("p (GeV/c)");
	tData->Draw("tofbetapim:ppim>>h","","contz");
	fpion->Draw("same");
	
	TCanvas *ctemp=new TCanvas("ctemp","",1,1);
}





void Vertex(){
	StyleUp();
	TH2F *h=new TH2F("h","",100,-120,-55,100,0,8);
	h->GetYaxis()->SetTitle("Transverse Vertex Position (cm)");
	h->GetXaxis()->SetTitle("z Vertex Position (cm)");
	tData->Draw("sqrt(vx*vx+vy*vy):vz>>h","vz>-110","COLZ");
	TCanvas *c=new TCanvas("c","",1,1);
}



void Mass2d(){
	StyleUp();
	TH2F *h=new TH2F("h","",100,1.29,1.38,100,1.08,1.15);
	h->GetYaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c)");
	h->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c)");
	tData->Draw("mmkpkppim : mmkpkp>>h","","COLZ");
	
	
	TH2F *h2=new TH2F("h2","",150,1.3,1.34,150,1.10,1.14);
	h2->GetYaxis()->SetTitle("M(#Xi^{-} - #pi^{-}) (GeV/c)");
	h2->GetXaxis()->SetTitle("M(#Lambda + #pi^{-}) (GeV/c)");
	tData->Draw("mcasmMpim : mlampim>>h2","","COLZ");
	TCanvas *c=new TCanvas("c","",1,1);
}





StyleUp()
{
	gStyle->SetTitleXOffset(0.7);
	gStyle->SetTitleYOffset(0.65);
	gStyle->SetTitleSize(0.06);
	gStyle->SetTitleYSize(0.06); 
	gStyle->SetPadTopMargin(0.02);
	gStyle->SetCanvasBorderMode(1);
	gStyle->SetPadBorderMode(1);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPadColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetFrameFillStyle(1001);
	gStyle->SetFillStyle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
}
