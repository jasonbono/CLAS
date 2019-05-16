
TFile* fdata = new TFile("/Users/Bono/clas/rootfiles/g12/ppippim/full/ppippim-v03.root");  
TTree *tdata = (TTree*)fdata->Get("v03");



TFile* fdataFidAll = new TFile("/Users/Bono/clas/rootfiles/g12/ppippim/partial/ppippim-v03-Partial_Phi_FidAll.root");  
TTree *tdataFidReg = (TTree*)fdataFidAll->Get("v03Reg"); 
TTree *tdataFidTight = (TTree*)fdataFidAll->Get("v03Tight");
TTree *tdataFidLoose = (TTree*)fdataFidAll->Get("v03Loose");


//////////set the tree and the string (for printing canvases)/////////
//set what kind of fiducial tree here (Red,Tight,Loose)
//TTree *myt = tdataFidReg;
//char* FidType = "FidReg";
//TTree *myt = tdataFidLoose;
//char* FidType = "FidLoose";
//TTree *myt = tdataFidTight;
//char* FidType = "FidTight";

TTree *myt = tdata;
char* FidType = "NoFid";

void ppippim_datafeature()
{
	StyleUp();

	//ShowFidEffect_PhiVsTheta();
	//ShowFidEffect_clas();
	//ShowFidEffect_PhiVsP();

	/*//beam
	//gStyle->SetOptStat(0);
	TH1F *hbeam=new TH1F("hbeam","",50,1.1,5.5);
	TH1F *hbeamFid=new TH1F("hbeamFid","",50,1.1,5.5);
	hbeamFid->SetLineColor(2);
	hbeam->GetXaxis()->SetTitle("beam");
	myt->Draw("beam>>hbeam");
	myt->Draw("beam>>hbeamFid","","Same");

	float temp1 = hbeamFid->GetEntries();
	float temp2 = hbeam->GetEntries();
	normfac = temp1/temp2;
	hbeam->Add(hbeam, normfac - 1);
	TCanvas *cbeam=new TCanvas("cbeam","cbeam",1000,800);
	hbeam->Draw();
	hbeamFid->Draw("SAME");
	///*////

	
	/*/phi vs theta
	TH2F *hclas2_pip=new TH2F("hclas2_pip","",200,0,90,200,-30,330);
	hclas2_pip->GetXaxis()->SetTitle("#theta  (#pi^{+})");
	hclas2_pip->GetYaxis()->SetTitle("#phi  (#pi^{+})");
	TCanvas *cphiVtheta2_pip=new TCanvas("cphiVtheta2_pip","cphiVtheta2_pip",1000,800);
	myt->Draw("pipphiclas : piplabtheta >> hclas2_pip","","colz");
	
	TH2F *hclas3_pip=new TH2F("hclas3_pip","",200,-1,1,200,1,1);
	hclas3_pip->GetXaxis()->SetTitle("#theta sin(#phi)  (#pi^{+})");
	hclas3_pip->GetYaxis()->SetTitle("#theta cos(#phi)  (#pi^{+})");
	TCanvas *cclas3_pip=new TCanvas("cclas3_pip","cclas3_pip",1000,800);
	myt->Draw("piplabtheta*cos(piplabphi*TMath::Pi()) : piplabtheta*sin(piplabphi*TMath::Pi()) >>hclas3_pip","","colz");
	
	
	
	TH2F *hclas2_pim=new TH2F("hclas2_pim","",200,0,90,200,-30,330);
	hclas2_pim->GetXaxis()->SetTitle("#theta  (#pi^{-})");
	hclas2_pim->GetYaxis()->SetTitle("#phi  (#pi^{-})");
	TCanvas *cphiVtheta2_pim=new TCanvas("cphiVtheta2_pim","cphiVtheta2_pim",1000,800);
	myt->Draw("pimphiclas : pimlabtheta >> hclas2_pim","","colz");
	
	TH2F *hclas3_pim=new TH2F("hclas3_pim","",200,-1,1,200,1,1);
	hclas3_pim->GetXaxis()->SetTitle("#theta sin(#phi)  (#pi^{-})");
	hclas3_pim->GetYaxis()->SetTitle("#theta cos(#phi)  (#pi^{-})");
	TCanvas *cclas3_pim=new TCanvas("cclas3_pim","cclas3_pim",1000,800);
	myt->Draw("pimlabtheta*cos(pimlabphi*TMath::Pi()) : pimlabtheta*sin(pimlabphi*TMath::Pi()) >>hclas3_pim","","colz");
	
	
	
	TH2F *hclas2_p=new TH2F("hclas2_p","",200,0,90,200,-30,330);
	hclas2_p->GetXaxis()->SetTitle("#theta  (P)");
	hclas2_p->GetYaxis()->SetTitle("#phi  (P)");
	TCanvas *cphiVtheta2_p=new TCanvas("cphiVtheta2_p","cphiVtheta2_p",1000,800);
	myt->Draw("pphiclas : plabtheta >> hclas2_p","","colz");
	
	TH2F *hclas3_p=new TH2F("hclas3_p","",200,-1,1,200,1,1);
	hclas3_p->GetXaxis()->SetTitle("#theta sin(#phi)  (P)");
	hclas3_p->GetYaxis()->SetTitle("#theta cos(#phi)  (P)");
	TCanvas *cclas3_p=new TCanvas("cclas3_p","cclas3_p",1000,800);
	myt->Draw("plabtheta*cos(plabphi*TMath::Pi()) : plabtheta*sin(plabphi*TMath::Pi()) >>hclas3_p","","colz");
	///*///



	/*/phi vs momentum for after fiducial cuts
	TH2F *hPhiVsP_pip=new TH2F("hPhiVsP_pip","",50,0,5,200,-30,330);
	hPhiVsP_pip->GetXaxis()->SetTitle("Momentum  (#pi^{+})");
	hPhiVsP_pip->GetYaxis()->SetTitle("#phi  (#pi^{+})");
	TCanvas *cPhiVsP_pip=new TCanvas("cPhiVsP_pip","cPhiVsP_pip",1000,800);
	myt->Draw("pipphiclas : ppip >> hPhiVsP_pip","","colz");
	
	TH2F *hPhiVsP_pim=new TH2F("hPhiVsP_pim","",50,0,5,200,-30,330);
	hPhiVsP_pim->GetXaxis()->SetTitle("Momentum  (#pi^{-})");
	hPhiVsP_pim->GetYaxis()->SetTitle("#phi  (#pi^{-})");
	TCanvas *cPhiVsP_pim=new TCanvas("cPhiVsP_pim","cPhiVsP_pim",1000,800);
	myt->Draw("pimphiclas : ppim >> hPhiVsP_pim","","colz");
	
	TH2F *hPhiVsP_p=new TH2F("hPhiVsP_p","",50,0,5,200,-30,330);
	hPhiVsP_p->GetXaxis()->SetTitle("Momentum  (P)");
	hPhiVsP_p->GetYaxis()->SetTitle("#phi  (P)");
	TCanvas *cPhiVsP_p=new TCanvas("cPhiVsP_p","cPhiVsP_p",1000,800);
	myt->Draw("pphiclas : pp >> hPhiVsP_p","","colz");
	
	cPhiVsP_p->Print(Form("~/Desktop/PhiVsP_p_%s.png",FidType));
	cPhiVsP_pip->Print(Form("~/Desktop/PhiVsP_pip_%s.png",FidType));
	cPhiVsP_pim->Print(Form("~/Desktop/PhiVsP_pim_%s.png",FidType));
	///*///
	



	/*//timing
	TH1F *ht=new TH1F("ht","",500,-3,3);
	ht->GetXaxis()->SetTitle("stv - scv");
	TCanvas *ct=new TCanvas("ct","ct",1000,800);
	ct->cd(1);
	myt->Draw("stv - scv >>ht");
	///*////




	/*//vertex
	TH1F *hvx=new TH1F("hvx","",400,-5,5);
	hvx->GetXaxis()->SetTitle("vx");
	TH1F *hvy=new TH1F("hvy","",400,-5,5);
	hvy->GetXaxis()->SetTitle("vy");
	TH1F *hvz=new TH1F("hvz","",500,-120,-60);
	hvz->GetXaxis()->SetTitle("vz");
	TH1F *hvt=new TH1F("hvt","",400,0,5);
	hvt->GetXaxis()->SetTitle("vt");
	
	
	TCanvas *cv=new TCanvas("cv","cv",1000,800);
	cv->Divide(2,2);
	cv->cd(1);
	myt->Draw("vx>>hvx");
	cv->cd(2);
	myt->Draw("vy>>hvy");
	cv->cd(3);
	myt->Draw("vz>>hvz");
	cv->cd(4);
	myt->Draw("sqrt(vx*vx + vy*vy)>>hvt");
	///*////



	/*/// particle lab theta
	TH1F *htp=new TH1F("htp","",500,0,120);
	TH1F *htpip=new TH1F("htpip","",500,0,120);
	TH1F *htpim=new TH1F("htpim","",500,0,120);
	htp->GetXaxis()->SetTitle("#theta(Proton))");
	htpip->GetXaxis()->SetTitle("#theta(#pi+))");
	htpim->GetXaxis()->SetTitle("#theta(#pi-))");	
	TCanvas *ctparticle=new TCanvas("ctparticle","ctparticle",1000,800);
	ctparticle->Divide(2,2);
	ctparticle->cd(1);
	myt->Draw("plabtheta>>htp");
	ctparticle->cd(2);
	myt->Draw("piplabtheta>>htpip");
	ctparticle->cd(3);
	myt->Draw("pimlabtheta>>htpim");
	ctparticle->cd(4);
	///*////





	/*// particle momenta
	TH1F *hpp=new TH1F("hpp","",500,0,3);
	TH1F *hppip=new TH1F("hppip","",500,0,3);
	TH1F *hppim=new TH1F("hppim","",500,0,3);
	hpp->GetXaxis()->SetTitle("p(Proton))");
	hppip->GetXaxis()->SetTitle("p(#pi+))");
	hppim->GetXaxis()->SetTitle("p(#pi-))");	
	TCanvas *cpparticle=new TCanvas("cpparticle","cpparticle",1000,800);
	cpparticle->Divide(2,2);
	cpparticle->cd(1);
	myt->Draw("pp>>hpp");
	cpparticle->cd(2);
	myt->Draw("ppip>>hppip");
	cpparticle->cd(3);
	myt->Draw("ppim>>hppim");
	cpparticle->cd(4);
	///*////


	/*///2d p vs theta
	gStyle->SetOptStat(0);
	TH2F *hpvt=new TH2F("hpvt","",200,0,90,200,0,4);
	TH2F *hpvtp= (TH2F*)hpvt->Clone("hpvtp");
	TH2F *hpvtpip= (TH2F*)hpvt->Clone("hpvtpip");
	TH2F *hpvtpim= (TH2F*)hpvt->Clone("hpvtpim");
	
	hpvtp->GetYaxis()->SetTitle("p (Proton)");
	hpvtp->GetXaxis()->SetTitle("#theta (Proton)");
	hpvtpip->GetYaxis()->SetTitle("p (#pi +)");
	hpvtpip->GetXaxis()->SetTitle("#theta (#pi +)");
	hpvtpim->GetYaxis()->SetTitle("p (#pi -)");
	hpvtpim->GetXaxis()->SetTitle("#theta (#pi -)");
	

	
	TCanvas *cpvt=new TCanvas("cpvt","cpvt",1000,800);
	cpvt->Divide(2,2);
	cpvt->cd(1);
	myt->Draw("pp : plabtheta >>hpvtp","","colz");
	cpvt->cd(2);
	myt->Draw("ppip : piplabtheta >>hpvtpip","","colz");
	cpvt->cd(3);
	myt->Draw("ppim : pimlabtheta >>hpvtpim","","colz");
	cpvt->cd(4);
	///*////


	/*//missing momentum
	TH1F *hp=new TH1F("hp","",500,-0.3,0.3);
	TH1F *hpx= (TH1F*)hp->Clone("hpx");
	hpx->GetXaxis()->SetTitle("Px");
	TH1F *hpy= (TH1F*)hp->Clone("hpy");
	hpy->GetXaxis()->SetTitle("Py");
	TH1F *hpz= (TH1F*)hp->Clone("hpz");
	hpz->GetXaxis()->SetTitle("Pz");
	TH1F *hpt= (TH1F*)hp->Clone("hpt");
	hpt->GetXaxis()->SetTitle("Pt");
	TCanvas *cp=new TCanvas("cp","cp",1000,800);
	cp->Divide(2,2);
	cp->cd(1);
	myt->Draw("missx>>hpx");
	cp->cd(2);
	myt->Draw("missy>>hpy");
	cp->cd(3);
	myt->Draw("missz>>hpz");
	cp->cd(4);
	myt->Draw("sqrt(missx*missx + missy*missy)>>hpt");
	///*////
	
	/*///missing mass
	TH1F *hm=new TH1F("hm","",100,-0.3,0.3);
	TH1F *hmm2ppippim= (TH1F*)hm->Clone("hmm2ppippim");
	hmm2ppippim->GetXaxis()->SetTitle("mm2ppippim");
	TCanvas *cm=new TCanvas("cm","cm",1000,800);
	cm->cd(1);
	myt->Draw("mm2ppippim>>hmm2ppippim");
	///*////


	/*///2d p vs m and p vs p
	gStyle->SetOptStat(0);
	TH2F *hpzvpt=new TH2F("hpzvpt","",200,0,0.1,200,-0.1,0.1);
	hpzvpt->GetYaxis()->SetTitle("Pz");
	hpzvpt->GetXaxis()->SetTitle("Pt");
	TH2F *hpzvm=new TH2F("hpzvm","",200,-0.2,0.2,200,-0.1,0.1);
	hpzvm->GetYaxis()->SetTitle("Pz");
	hpzvm->GetXaxis()->SetTitle("mm2");
	TH2F *hptvm=new TH2F("hptvm","",200,-0.2,0.2,200,0,0.1);
	hptvm->GetYaxis()->SetTitle("Pt");
	hptvm->GetXaxis()->SetTitle("mm2");
	
	TCanvas *c2d=new TCanvas("c2d","c2d",1000,800);
	c2d->Divide(2,2);
	c2d->cd(1);
	myt->Draw("missz : sqrt(missx*missx + missy*missy) >>hpzvpt","","colz");
	c2d->cd(2);
	myt->Draw("missz : mm2ppippim >>hpzvm","","colz");
	c2d->cd(3);
	myt->Draw("sqrt(missx*missx + missy*missy) : mm2ppippim >>hptvm","","colz");
	c2d->cd(4);
	///*////




	

	Sec6_ThetaVsPhi();




}


void Sec6_ThetaVsPhi()
{
	StyleUp();
	TH2F *hPhiVsTheta_pip=new TH2F("hPhiVsTheta_pip","",200,-30,30,200,0,90);
	hPhiVsTheta_pip->GetXaxis()->SetTitle("#theta  (#pi^{+})");
	hPhiVsTheta_pip->GetYaxis()->SetTitle("#phi  (#pi^{+})");
	TH2F *hPhiVsTheta_pip_1= (TH2F*)hPhiVsTheta_pip->Clone("hPhiVsTheta_pip_1");
	TH2F *hPhiVsTheta_pip_2= (TH2F*)hPhiVsTheta_pip->Clone("hPhiVsTheta_pip_2");
	TH2F *hPhiVsTheta_pip_3= (TH2F*)hPhiVsTheta_pip->Clone("hPhiVsTheta_pip_3");
	TH2F *hPhiVsTheta_pip_4= (TH2F*)hPhiVsTheta_pip->Clone("hPhiVsTheta_pip_4");	
	TCanvas *cPhiVsTheta_pip=new TCanvas("cPhiVsTheta_pip","cPhiVsTheta_pip",1000,800);
	cPhiVsTheta_pip->Divide(2,0);
	cPhiVsTheta_pip->cd(1);
	tdataFidTight->Draw("piplabtheta : pipphidiff >> hPhiVsTheta_pip_3","pimsector==6","colz");
	cPhiVsTheta_pip->cd(2);

}





void ShowFidEffect_PhiVsP()
{	
	StyleUp();
	TH2F *hPhiVsP_pip=new TH2F("hPhiVsP_pip","",50,0,5,200,-30,330);
	hPhiVsP_pip->GetXaxis()->SetTitle("Momentum  (#pi^{+})");
	hPhiVsP_pip->GetYaxis()->SetTitle("#phi  (#pi^{+})");	
	TH2F *hPhiVsP_pip_1= (TH2F*)hPhiVsP_pip->Clone("hPhiVsP_pip_1");
	TH2F *hPhiVsP_pip_2= (TH2F*)hPhiVsP_pip->Clone("hPhiVsP_pip_2");
	TH2F *hPhiVsP_pip_3= (TH2F*)hPhiVsP_pip->Clone("hPhiVsP_pip_3");
	TH2F *hPhiVsP_pip_4= (TH2F*)hPhiVsP_pip->Clone("hPhiVsP_pip_4");	
	TCanvas *cPhiVsP_pip=new TCanvas("cPhiVsP_pip","cPhiVsP_pip",1000,800);
	cPhiVsP_pip->Divide(4,0);
	cPhiVsP_pip->cd(1);
	tdata->Draw("pipphiclas : ppip >> hPhiVsP_pip_1","","colz");
	cPhiVsP_pip->cd(2);
	tdataFidLoose->Draw("pipphiclas : ppip >> hPhiVsP_pip_2","","colz");
	cPhiVsP_pip->cd(3);
	tdataFidReg->Draw("pipphiclas : ppip >> hPhiVsP_pip_3","","colz");
	cPhiVsP_pip->cd(4);
	tdataFidTight->Draw("pipphiclas : ppip >> hPhiVsP_pip_4","","colz");
	cPhiVsP_pip->Print("~/Desktop/PhiVsP_pip.png");
	
	TH2F *hPhiVsP_pim=new TH2F("hPhiVsP_pim","",50,0,5,200,-30,330);
	hPhiVsP_pim->GetXaxis()->SetTitle("Momentum  (#pi^{-})");
	hPhiVsP_pim->GetYaxis()->SetTitle("#phi  (#pi^{-})");	
	TH2F *hPhiVsP_pim_1= (TH2F*)hPhiVsP_pim->Clone("hPhiVsP_pim_1");
	TH2F *hPhiVsP_pim_2= (TH2F*)hPhiVsP_pim->Clone("hPhiVsP_pim_2");
	TH2F *hPhiVsP_pim_3= (TH2F*)hPhiVsP_pim->Clone("hPhiVsP_pim_3");
	TH2F *hPhiVsP_pim_4= (TH2F*)hPhiVsP_pim->Clone("hPhiVsP_pim_4");	
	TCanvas *cPhiVsP_pim=new TCanvas("cPhiVsP_pim","cPhiVsP_pim",1000,800);
	cPhiVsP_pim->Divide(4,0);
	cPhiVsP_pim->cd(1);
	tdata->Draw("pimphiclas : ppim >> hPhiVsP_pim_1","","colz");
	cPhiVsP_pim->cd(2);
	tdataFidLoose->Draw("pimphiclas : ppim >> hPhiVsP_pim_2","","colz");
	cPhiVsP_pim->cd(3);
	tdataFidReg->Draw("pimphiclas : ppim >> hPhiVsP_pim_3","","colz");
	cPhiVsP_pim->cd(4);
	tdataFidTight->Draw("pimphiclas : ppim >> hPhiVsP_pim_4","","colz");
	cPhiVsP_pim->Print("~/Desktop/PhiVsP_pim.png");
	
	
	TH2F *hPhiVsP_p=new TH2F("hPhiVsP_p","",50,0,5,200,-30,330);
	hPhiVsP_p->GetXaxis()->SetTitle("Momentum  (p)");
	hPhiVsP_p->GetYaxis()->SetTitle("#phi  (p)");	
	TH2F *hPhiVsP_p_1= (TH2F*)hPhiVsP_p->Clone("hPhiVsP_p_1");
	TH2F *hPhiVsP_p_2= (TH2F*)hPhiVsP_p->Clone("hPhiVsP_p_2");
	TH2F *hPhiVsP_p_3= (TH2F*)hPhiVsP_p->Clone("hPhiVsP_p_3");
	TH2F *hPhiVsP_p_4= (TH2F*)hPhiVsP_p->Clone("hPhiVsP_p_4");	
	TCanvas *cPhiVsP_p=new TCanvas("cPhiVsP_p","cPhiVsP_p",1000,800);
	cPhiVsP_p->Divide(4,0);
	cPhiVsP_p->cd(1);
	tdata->Draw("pphiclas : pp >> hPhiVsP_p_1","","colz");
	cPhiVsP_p->cd(2);
	tdataFidLoose->Draw("pphiclas : pp >> hPhiVsP_p_2","","colz");
	cPhiVsP_p->cd(3);
	tdataFidReg->Draw("pphiclas : pp >> hPhiVsP_p_3","","colz");
	cPhiVsP_p->cd(4);
	tdataFidTight->Draw("pphiclas : pp >> hPhiVsP_p_4","","colz");
	cPhiVsP_p->Print("~/Desktop/PhiVsP_p.png");
}



void ShowFidEffect_PhiVsTheta()
{
	StyleUp();
	TH2F *hPhiVsTheta_pip=new TH2F("hPhiVsTheta_pip","",200,0,90,200,-30,330);
	hPhiVsTheta_pip->GetXaxis()->SetTitle("#theta  (#pi^{+})");
	hPhiVsTheta_pip->GetYaxis()->SetTitle("#phi  (#pi^{+})");
	TH2F *hPhiVsTheta_pip_1= (TH2F*)hPhiVsTheta_pip->Clone("hPhiVsTheta_pip_1");
	TH2F *hPhiVsTheta_pip_2= (TH2F*)hPhiVsTheta_pip->Clone("hPhiVsTheta_pip_2");
	TH2F *hPhiVsTheta_pip_3= (TH2F*)hPhiVsTheta_pip->Clone("hPhiVsTheta_pip_3");
	TH2F *hPhiVsTheta_pip_4= (TH2F*)hPhiVsTheta_pip->Clone("hPhiVsTheta_pip_4");	
	TCanvas *cPhiVsTheta_pip=new TCanvas("cPhiVsTheta_pip","cPhiVsTheta_pip",1000,800);
	cPhiVsTheta_pip->Divide(4,0);
	cPhiVsTheta_pip->cd(1);
	tdata->Draw("pipphiclas : piplabtheta >> hPhiVsTheta_pip_1","","colz");
	cPhiVsTheta_pip->cd(2);
	tdataFidLoose->Draw("pipphiclas : piplabtheta >> hPhiVsTheta_pip_2","","colz");
	cPhiVsTheta_pip->cd(3);	
	tdataFidReg->Draw("pipphiclas : piplabtheta >> hPhiVsTheta_pip_3","","colz");
	cPhiVsTheta_pip->cd(4);
	tdataFidTight->Draw("pipphiclas : piplabtheta >> hPhiVsTheta_pip_4","","colz");
	cPhiVsTheta_pip->Print("~/Desktop/PhiVsTheta_pip.png");
	
	
	TH2F *hPhiVsTheta_pim=new TH2F("hPhiVsTheta_pim","",200,0,90,200,-30,330);
	hPhiVsTheta_pim->GetXaxis()->SetTitle("#theta  (#pi^{-})");
	hPhiVsTheta_pim->GetYaxis()->SetTitle("#phi  (#pi^{-})");
	TH2F *hPhiVsTheta_pim_1= (TH2F*)hPhiVsTheta_pim->Clone("hPhiVsTheta_pim_1");
	TH2F *hPhiVsTheta_pim_2= (TH2F*)hPhiVsTheta_pim->Clone("hPhiVsTheta_pim_2");
	TH2F *hPhiVsTheta_pim_3= (TH2F*)hPhiVsTheta_pim->Clone("hPhiVsTheta_pim_3");
	TH2F *hPhiVsTheta_pim_4= (TH2F*)hPhiVsTheta_pim->Clone("hPhiVsTheta_pim_4");
	TCanvas *cPhiVsTheta_pim=new TCanvas("cPhiVsTheta_pim","cPhiVsTheta_pim",1000,800);
	cPhiVsTheta_pim->Divide(4,0);
	cPhiVsTheta_pim->cd(1);
	tdata->Draw("pimphiclas : pimlabtheta >> hPhiVsTheta_pim_1","","colz");
	cPhiVsTheta_pim->cd(2);
	tdataFidLoose->Draw("pimphiclas : pimlabtheta >> hPhiVsTheta_pim_2","","colz");
	cPhiVsTheta_pim->cd(3);	
	tdataFidReg->Draw("pimphiclas : pimlabtheta >> hPhiVsTheta_pim_3","","colz");
	cPhiVsTheta_pim->cd(4);
	tdataFidTight->Draw("pimphiclas : pimlabtheta >> hPhiVsTheta_pim_4","","colz");
	cPhiVsTheta_pim->Print("~/Desktop/PhiVsTheta_pim.png");


	TH2F *hPhiVsTheta_p=new TH2F("hPhiVsTheta_p","",200,0,90,200,-30,330);
	hPhiVsTheta_p->GetXaxis()->SetTitle("#theta  (p)");
	hPhiVsTheta_p->GetYaxis()->SetTitle("#phi  (p)");
	TH2F *hPhiVsTheta_p_1= (TH2F*)hPhiVsTheta_p->Clone("hPhiVsTheta_p_1");
	TH2F *hPhiVsTheta_p_2= (TH2F*)hPhiVsTheta_p->Clone("hPhiVsTheta_p_2");
	TH2F *hPhiVsTheta_p_3= (TH2F*)hPhiVsTheta_p->Clone("hPhiVsTheta_p_3");
	TH2F *hPhiVsTheta_p_4= (TH2F*)hPhiVsTheta_p->Clone("hPhiVsTheta_p_4");
	TCanvas *cPhiVsTheta_p=new TCanvas("cPhiVsTheta_p","cPhiVsTheta_p",1000,800);
	TCanvas *cPhiVsTheta_p=new TCanvas("cPhiVsTheta_p","cPhiVsTheta_p",1000,800);
	cPhiVsTheta_p->Divide(4,0);
	cPhiVsTheta_p->cd(1);
	tdata->Draw("pphiclas : plabtheta >> hPhiVsTheta_p_1","","colz");
	cPhiVsTheta_p->cd(2);
	tdataFidLoose->Draw("pphiclas : plabtheta >> hPhiVsTheta_p_2","","colz");
	cPhiVsTheta_p->cd(3);	
	tdataFidReg->Draw("pphiclas : plabtheta >> hPhiVsTheta_p_3","","colz");
	cPhiVsTheta_p->cd(4);
	tdataFidTight->Draw("pphiclas : plabtheta >> hPhiVsTheta_p_4","","colz");
	cPhiVsTheta_p->Print("~/Desktop/PhiVsTheta_p.png");
	
}


void ShowFidEffect_clas()
{
	StyleUp();
	TH2F *hclas_pip=new TH2F("hclas_pip","",200,-1,1,200,1,1);
	hclas_pip->GetXaxis()->SetTitle("#theta sin(#phi)  (#pi^{+})");
	hclas_pip->GetYaxis()->SetTitle("#theta cos(#phi)  (#pi^{+})");
	TH2F *hclas_pip_1= (TH2F*)hclas_pip->Clone("hclas_pip_1");
	TH2F *hclas_pip_2= (TH2F*)hclas_pip->Clone("hclas_pip_2");
	TH2F *hclas_pip_3= (TH2F*)hclas_pip->Clone("hclas_pip_3");
	TH2F *hclas_pip_4= (TH2F*)hclas_pip->Clone("hclas_pip_4");
	TCanvas *cclas_pip=new TCanvas("cclas_pip","cclas_pip",1000,800);
	cclas_pip->Divide(2,2);
	cclas_pip->cd(1);
	tdata->Draw("piplabtheta*cos(piplabphi*TMath::Pi()) : piplabtheta*sin(piplabphi*TMath::Pi()) >> hclas_pip_1","","colz");
	cclas_pip->cd(2);
	tdataFidLoose->Draw("piplabtheta*cos(piplabphi*TMath::Pi()) : piplabtheta*sin(piplabphi*TMath::Pi()) >> hclas_pip_2","","colz");
	cclas_pip->cd(3);
	tdataFidReg->Draw("piplabtheta*cos(piplabphi*TMath::Pi()) : piplabtheta*sin(piplabphi*TMath::Pi()) >> hclas_pip_3","","colz");
	cclas_pip->cd(4);
	tdataFidTight->Draw("piplabtheta*cos(piplabphi*TMath::Pi()) : piplabtheta*sin(piplabphi*TMath::Pi()) >> hclas_pip_4","","colz");
	cclas_pip->Print("~/Desktop/clas_pip.png");
	
	TH2F *hclas_pim=new TH2F("hclas_pim","",200,-1,1,200,1,1);
	hclas_pim->GetXaxis()->SetTitle("#theta sin(#phi)  (#pi^{-})");
	hclas_pim->GetYaxis()->SetTitle("#theta cos(#phi)  (#pi^{-})");
	TH2F *hclas_pim_1= (TH2F*)hclas_pim->Clone("hclas_pim_1");
	TH2F *hclas_pim_2= (TH2F*)hclas_pim->Clone("hclas_pim_2");
	TH2F *hclas_pim_3= (TH2F*)hclas_pim->Clone("hclas_pim_3");
	TH2F *hclas_pim_4= (TH2F*)hclas_pim->Clone("hclas_pim_4");
	TCanvas *cclas_pim=new TCanvas("cclas_pim","cclas_pim",1000,800);
	cclas_pim->Divide(2,2);
	cclas_pim->cd(1);
	tdata->Draw("pimlabtheta*cos(pimlabphi*TMath::Pi()) : pimlabtheta*sin(pimlabphi*TMath::Pi()) >> hclas_pim_1","","colz");
	cclas_pim->cd(2);
	tdataFidLoose->Draw("pimlabtheta*cos(pimlabphi*TMath::Pi()) : pimlabtheta*sin(pimlabphi*TMath::Pi()) >> hclas_pim_2","","colz");
	cclas_pim->cd(3);
	tdataFidReg->Draw("pimlabtheta*cos(pimlabphi*TMath::Pi()) : pimlabtheta*sin(pimlabphi*TMath::Pi()) >> hclas_pim_3","","colz");
	cclas_pim->cd(4);
	tdataFidTight->Draw("pimlabtheta*cos(pimlabphi*TMath::Pi()) : pimlabtheta*sin(pimlabphi*TMath::Pi()) >> hclas_pim_4","","colz");
	cclas_pim->Print("~/Desktop/clas_pim.png");
	
	TH2F *hclas_p=new TH2F("hclas_p","",200,-1,1,200,1,1);
	hclas_p->GetXaxis()->SetTitle("#theta sin(#phi)  (p)");
	hclas_p->GetYaxis()->SetTitle("#theta cos(#phi)  (p)");
	TH2F *hclas_p_1= (TH2F*)hclas_p->Clone("hclas_p_1");
	TH2F *hclas_p_2= (TH2F*)hclas_p->Clone("hclas_p_2");
	TH2F *hclas_p_3= (TH2F*)hclas_p->Clone("hclas_p_3");
	TH2F *hclas_p_4= (TH2F*)hclas_p->Clone("hclas_p_4");
	TCanvas *cclas_p=new TCanvas("cclas_p","cclas_p",1000,800);
	cclas_p->Divide(2,2);
	cclas_p->cd(1);
	tdata->Draw("plabtheta*cos(plabphi*TMath::Pi()) : plabtheta*sin(plabphi*TMath::Pi()) >> hclas_p_1","","colz");
	cclas_p->cd(2);
	tdataFidLoose->Draw("plabtheta*cos(plabphi*TMath::Pi()) : plabtheta*sin(plabphi*TMath::Pi()) >> hclas_p_2","","colz");
	cclas_p->cd(3);
	tdataFidReg->Draw("plabtheta*cos(plabphi*TMath::Pi()) : plabtheta*sin(plabphi*TMath::Pi()) >> hclas_p_3","","colz");
	cclas_p->cd(4);
	tdataFidTight->Draw("plabtheta*cos(plabphi*TMath::Pi()) : plabtheta*sin(plabphi*TMath::Pi()) >> hclas_p_4","","colz");
	cclas_p->Print("~/Desktop/clas_p.png");
}


StyleUp()
{
	gStyle->SetTitleXOffset(0.5);
	gStyle->SetTitleYOffset(0.65);
	gStyle->SetTitleSize(0.08);
	gStyle->SetTitleYSize(0.07); 
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
}

