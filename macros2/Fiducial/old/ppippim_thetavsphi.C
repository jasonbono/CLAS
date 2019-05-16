void ppippim_thetavsphi()
{
	
	const int Np = 3;  //number of momentum bins	
	const int Nt = 3;  //number of theta bins
	const int Ns = 6; //number of sectors
	
	
	TCut Fid_Cut50[Np][Nt][Ns];
	Fid_Cut50[0][0][0] = " ((pipphidiff > -26.700000 && pipphidiff < 25.500000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.000000 && piplabtheta < 0.615050 )))&&(pipsector == 1) " ;
	Fid_Cut50[0][0][1] = " ((pipphidiff > -26.100000 && pipphidiff < 26.100000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.000000 && piplabtheta < 0.615050 )))&&(pipsector == 2) " ;
	Fid_Cut50[0][0][2] = " ((pipphidiff > -26.100000 && pipphidiff < 26.100000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.000000 && piplabtheta < 0.615050 )))&&(pipsector == 3) " ;
	Fid_Cut50[0][0][3] = " ((pipphidiff > -26.100000 && pipphidiff < 26.100000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.000000 && piplabtheta < 0.615050 )))&&(pipsector == 4) " ;
	Fid_Cut50[0][0][4] = " ((pipphidiff > -26.700000 && pipphidiff < 26.100000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.000000 && piplabtheta < 0.615050 )))&&(pipsector == 5) " ;
	Fid_Cut50[0][0][5] = " ((pipphidiff > -26.700000 && pipphidiff < 25.500000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.000000 && piplabtheta < 0.615050 )))&&(pipsector == 6) " ;
	Fid_Cut50[0][1][0] = " ((pipphidiff > -26.700000 && pipphidiff < 26.100000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.615050 && piplabtheta < 0.813250 )))&&(pipsector == 1) " ;
	Fid_Cut50[0][1][1] = " ((pipphidiff > -26.700000 && pipphidiff < 26.100000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.615050 && piplabtheta < 0.813250 )))&&(pipsector == 2) " ;
	Fid_Cut50[0][1][2] = " ((pipphidiff > -26.100000 && pipphidiff < 26.100000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.615050 && piplabtheta < 0.813250 )))&&(pipsector == 3) " ;
	Fid_Cut50[0][1][3] = " ((pipphidiff > -26.700000 && pipphidiff < 26.100000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.615050 && piplabtheta < 0.813250 )))&&(pipsector == 4) " ;
	Fid_Cut50[0][1][4] = " ((pipphidiff > -26.700000 && pipphidiff < 26.100000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.615050 && piplabtheta < 0.813250 )))&&(pipsector == 5) " ;
	Fid_Cut50[0][1][5] = " ((pipphidiff > -26.700000 && pipphidiff < 25.500000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.615050 && piplabtheta < 0.813250 )))&&(pipsector == 6) " ;
	Fid_Cut50[0][2][0] = " ((pipphidiff > -25.500000 && pipphidiff < 23.700000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.813250 && piplabtheta < 1.000000 )))&&(pipsector == 1) " ;
	Fid_Cut50[0][2][1] = " ((pipphidiff > -26.100000 && pipphidiff < 23.700000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.813250 && piplabtheta < 1.000000 )))&&(pipsector == 2) " ;
	Fid_Cut50[0][2][2] = " ((pipphidiff > -24.900000 && pipphidiff < 24.900000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.813250 && piplabtheta < 1.000000 )))&&(pipsector == 3) " ;
	Fid_Cut50[0][2][3] = " ((pipphidiff > -24.300000 && pipphidiff < 24.900000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.813250 && piplabtheta < 1.000000 )))&&(pipsector == 4) " ;
	Fid_Cut50[0][2][4] = " ((pipphidiff > -24.300000 && pipphidiff < 24.900000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.813250 && piplabtheta < 1.000000 )))&&(pipsector == 5) " ;
	Fid_Cut50[0][2][5] = " ((pipphidiff > -25.500000 && pipphidiff < 23.700000)&&((ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.813250 && piplabtheta < 1.000000 )))&&(pipsector == 6) " ;
	Fid_Cut50[1][0][0] = " ((pipphidiff > -26.700000 && pipphidiff < 26.100000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.000000 && piplabtheta < 0.775150 )))&&(pipsector == 1) " ;
	Fid_Cut50[1][0][1] = " ((pipphidiff > -26.100000 && pipphidiff < 26.100000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.000000 && piplabtheta < 0.775150 )))&&(pipsector == 2) " ;
	Fid_Cut50[1][0][2] = " ((pipphidiff > -26.700000 && pipphidiff < 26.700000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.000000 && piplabtheta < 0.775150 )))&&(pipsector == 3) " ;
	Fid_Cut50[1][0][3] = " ((pipphidiff > -26.700000 && pipphidiff < 26.700000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.000000 && piplabtheta < 0.775150 )))&&(pipsector == 4) " ;
	Fid_Cut50[1][0][4] = " ((pipphidiff > -26.700000 && pipphidiff < 26.100000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.000000 && piplabtheta < 0.775150 )))&&(pipsector == 5) " ;
	Fid_Cut50[1][0][5] = " ((pipphidiff > -27.300000 && pipphidiff < 26.100000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.000000 && piplabtheta < 0.775150 )))&&(pipsector == 6) " ;
	Fid_Cut50[1][1][0] = " ((pipphidiff > -26.100000 && pipphidiff < 24.900000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.775150 && piplabtheta < 0.903350 )))&&(pipsector == 1) " ;
	Fid_Cut50[1][1][1] = " ((pipphidiff > -26.100000 && pipphidiff < 25.500000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.775150 && piplabtheta < 0.903350 )))&&(pipsector == 2) " ;
	Fid_Cut50[1][1][2] = " ((pipphidiff > -25.500000 && pipphidiff < 25.500000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.775150 && piplabtheta < 0.903350 )))&&(pipsector == 3) " ;
	Fid_Cut50[1][1][3] = " ((pipphidiff > -26.100000 && pipphidiff < 25.500000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.775150 && piplabtheta < 0.903350 )))&&(pipsector == 4) " ;
	Fid_Cut50[1][1][4] = " ((pipphidiff > -26.100000 && pipphidiff < 26.100000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.775150 && piplabtheta < 0.903350 )))&&(pipsector == 5) " ;
	Fid_Cut50[1][1][5] = " ((pipphidiff > -26.100000 && pipphidiff < 24.900000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.775150 && piplabtheta < 0.903350 )))&&(pipsector == 6) " ;
	Fid_Cut50[1][2][0] = " ((pipphidiff > -23.700000 && pipphidiff < 23.100000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.903350 && piplabtheta < 1.000000 )))&&(pipsector == 1) " ;
	Fid_Cut50[1][2][1] = " ((pipphidiff > -23.700000 && pipphidiff < 23.100000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.903350 && piplabtheta < 1.000000 )))&&(pipsector == 2) " ;
	Fid_Cut50[1][2][2] = " ((pipphidiff > -23.100000 && pipphidiff < 23.700000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.903350 && piplabtheta < 1.000000 )))&&(pipsector == 3) " ;
	Fid_Cut50[1][2][3] = " ((pipphidiff > -22.500000 && pipphidiff < 23.700000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.903350 && piplabtheta < 1.000000 )))&&(pipsector == 4) " ;
	Fid_Cut50[1][2][4] = " ((pipphidiff > -23.100000 && pipphidiff < 23.700000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.903350 && piplabtheta < 1.000000 )))&&(pipsector == 5) " ;
	Fid_Cut50[1][2][5] = " ((pipphidiff > -23.700000 && pipphidiff < 23.100000)&&((ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.903350 && piplabtheta < 1.000000 )))&&(pipsector == 6) " ;
	Fid_Cut50[2][0][0] = " ((pipphidiff > -26.100000 && pipphidiff < 24.900000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.000000 && piplabtheta < 0.906250 )))&&(pipsector == 1) " ;
	Fid_Cut50[2][0][1] = " ((pipphidiff > -26.100000 && pipphidiff < 25.500000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.000000 && piplabtheta < 0.906250 )))&&(pipsector == 2) " ;
	Fid_Cut50[2][0][2] = " ((pipphidiff > -25.500000 && pipphidiff < 25.500000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.000000 && piplabtheta < 0.906250 )))&&(pipsector == 3) " ;
	Fid_Cut50[2][0][3] = " ((pipphidiff > -26.100000 && pipphidiff < 25.500000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.000000 && piplabtheta < 0.906250 )))&&(pipsector == 4) " ;
	Fid_Cut50[2][0][4] = " ((pipphidiff > -26.100000 && pipphidiff < 25.500000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.000000 && piplabtheta < 0.906250 )))&&(pipsector == 5) " ;
	Fid_Cut50[2][0][5] = " ((pipphidiff > -26.100000 && pipphidiff < 24.900000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.000000 && piplabtheta < 0.906250 )))&&(pipsector == 6) " ;
	Fid_Cut50[2][1][0] = " ((pipphidiff > -23.700000 && pipphidiff < 23.100000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.906250 && piplabtheta < 0.961650 )))&&(pipsector == 1) " ;
	Fid_Cut50[2][1][1] = " ((pipphidiff > -24.300000 && pipphidiff < 23.100000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.906250 && piplabtheta < 0.961650 )))&&(pipsector == 2) " ;
	Fid_Cut50[2][1][2] = " ((pipphidiff > -23.700000 && pipphidiff < 24.300000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.906250 && piplabtheta < 0.961650 )))&&(pipsector == 3) " ;
	Fid_Cut50[2][1][3] = " ((pipphidiff > -23.700000 && pipphidiff < 24.300000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.906250 && piplabtheta < 0.961650 )))&&(pipsector == 4) " ;
	Fid_Cut50[2][1][4] = " ((pipphidiff > -23.700000 && pipphidiff < 23.700000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.906250 && piplabtheta < 0.961650 )))&&(pipsector == 5) " ;
	Fid_Cut50[2][1][5] = " ((pipphidiff > -24.300000 && pipphidiff < 23.700000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.906250 && piplabtheta < 0.961650 )))&&(pipsector == 6) " ;
	Fid_Cut50[2][2][0] = " ((pipphidiff > -21.300000 && pipphidiff < 19.500000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.961650 && piplabtheta < 1.000000 )))&&(pipsector == 1) " ;
	Fid_Cut50[2][2][1] = " ((pipphidiff > -20.700000 && pipphidiff < 18.900000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.961650 && piplabtheta < 1.000000 )))&&(pipsector == 2) " ;
	Fid_Cut50[2][2][2] = " ((pipphidiff > -19.500000 && pipphidiff < 20.700000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.961650 && piplabtheta < 1.000000 )))&&(pipsector == 3) " ;
	Fid_Cut50[2][2][3] = " ((pipphidiff > -20.100000 && pipphidiff < 20.100000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.961650 && piplabtheta < 1.000000 )))&&(pipsector == 4) " ;
	Fid_Cut50[2][2][4] = " ((pipphidiff > -19.500000 && pipphidiff < 21.300000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.961650 && piplabtheta < 1.000000 )))&&(pipsector == 5) " ;
	Fid_Cut50[2][2][5] = " ((pipphidiff > -21.300000 && pipphidiff < 20.100000)&&((ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.961650 && piplabtheta < 1.000000 )))&&(pipsector == 6) " ;
	
	
	TCut Total_Fid_Cut50;
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
			for (int s=0; s<Ns; s++)
			{
				Total_Fid_Cut50 = Total_Fid_Cut50 || Fid_Cut50[p][t][s] ;
			}
		}
	}
	
	
	StyleUp();
	TFile* fdata = new TFile("/Users/Bono/clas/rootfiles/g12/ppippim/partial/ppippim-v01-partial_Phi.root");  
	TTree *tdata = (TTree*)fdata->Get("v01");
	



	TCut pip_ptcut[Np][Nt];
	pip_ptcut[0][0] = "(ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.000000 && piplabtheta < 0.615050 )";
	pip_ptcut[0][1] = "(ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.615050 && piplabtheta < 0.813250 )";
	pip_ptcut[0][2] = "(ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.813250 && piplabtheta < 1.000000 )";
	pip_ptcut[1][0] = "(ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.000000 && piplabtheta < 0.775150 )";
	pip_ptcut[1][1] = "(ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.775150 && piplabtheta < 0.903350 )";
	pip_ptcut[1][2] = "(ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.903350 && piplabtheta < 1.000000 )";
	pip_ptcut[2][0] = "(ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.000000 && piplabtheta < 0.906250 )";
	pip_ptcut[2][1] = "(ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.906250 && piplabtheta < 0.961650 )";
	pip_ptcut[2][2] = "(ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.961650 && piplabtheta < 1.000000 )";
	

	TCut pip_seccut[Ns];
	pip_seccut[0] = "pipsector == 1";
	pip_seccut[1] = "pipsector == 2";
	pip_seccut[2] = "pipsector == 3";
	pip_seccut[3] = "pipsector == 4";
	pip_seccut[4] = "pipsector == 5";
	pip_seccut[5] = "pipsector == 6";
	
	
	
	/*//show clas detector
	TH2F *hclas=new TH2F("hclas","",200,-1,1,200,0,1);
	TCanvas *cclas=new TCanvas("cclas","cclas",1000,800);
	tdata->Draw("plabtheta : plabphi >>hclas","","colz");
	
	TH2F *hclas2=new TH2F("hclas2","",200,-1,1,200,1,1);
	hclas2->GetXaxis()->SetTitle("#theta sin(#phi)  (Proton)");
	hclas2->GetYaxis()->SetTitle("#theta cos(#phi)  (Proton)");
	TCanvas *cclas2=new TCanvas("cclas2","cclas2",1000,800);
	tdata->Draw("plabtheta*cos(plabphi*TMath::Pi()) : plabtheta*sin(plabphi*TMath::Pi()) >>hclas2",Total_Fid_Cut50,"colz");
	///*///
	
	
	//*//show clas detector with total cuts
	TH2F *hclas=new TH2F("hclas","",200,-1,1,200,0,1);
	TCanvas *cclas=new TCanvas("cclas","cclas",1000,800);
	tdata->Draw("plabtheta : plabphi >>hclas","","colz");
	
	TH2F *hclas2=new TH2F("hclas2","",200,-1,1,200,1,1);
	hclas2->GetXaxis()->SetTitle("#theta sin(#phi)  (Proton)");
	hclas2->GetYaxis()->SetTitle("#theta cos(#phi)  (Proton)");
	TCanvas *cclas2=new TCanvas("cclas2","cclas2",1000,800);
	tdata->Draw("plabtheta*cos(plabphi*TMath::Pi()) : plabtheta*sin(plabphi*TMath::Pi()) >>hclas2",Total_Fid_Cut50,"colz");
	///*///
	
	

	
	/*//nocuts
	TH2F *htvp[Np][Nt][Ns];
	TCanvas *ctvp[Np][Nt];
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
			ctvp[p][t]=new TCanvas(Form("ctvp%i%i",p,t),Form("ctvp%i%i",p,t),1000,800);
			ctvp[p][t]->Divide(3,2);
			for (int s=0; s<Ns; s++)
			{
				ctvp[p][t]->cd(s+1);
				htvp[p][t][s]=new TH2F(Form("htvp%i%i%i",p,t,s),Form("htvp%i%i%i",p,t,s),100,-30,30,100,0,1);
				tdata->Draw(Form("plabtheta : pipphidiff >> htvp%i%i%i",p,t,s),pip_seccut[s]&&pip_ptcut[p][t],"colz");
			}
		}
	}
	///*////
	
	
	
	/*//fiducial cuts
	TH2F *htvp50[Np][Nt][Ns];
	TCanvas *ctvp50[Np][Nt];
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
			ctvp50[p][t]=new TCanvas(Form("ctvp50%i%i",p,t),Form("ctvp50%i%i",p,t),1000,800);
			ctvp50[p][t]->Divide(3,2);
			for (int s=0; s<Ns; s++)
			{
				ctvp50[p][t]->cd(s+1);
				htvp50[p][t][s]=new TH2F(Form("htvp50%i%i%i",p,t,s),"",100,-30,30,100,0,1);
				tdata->Draw(Form("plabtheta : pipphidiff >> htvp50%i%i%i",p,t,s),Fid_Cut50[p][t][s],"colz");
			}
		}
	}
	///*////
	

	
	
	
	
}














////////////////////////////////////////////////////////////////////////

Double_t g2(Double_t *x, Double_t *par) {
   Double_t r1 = Double_t((x[0]-par[1])/par[2]);
   Double_t r2 = Double_t((x[1]-par[3])/par[4]);
   return par[0]*TMath::Exp(-0.5*(r1*r1+r2*r2));
}   
Double_t fun2(Double_t *x, Double_t *par) {
   Double_t *p1 = &par[0];
   Double_t *p2 = &par[5];
   Double_t *p3 = &par[10];
   Double_t result = g2(x,p1) + g2(x,p2) + g2(x,p3);
   return result;
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
	gStyle->SetOptFit(1);
}

