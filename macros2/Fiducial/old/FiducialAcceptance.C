

void FiducialAcceptance()
{

	const float PI = 3.14159265;

	//~~~~~~~~~~~~~~~~~~~~~files~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//MC
	TFile* fMC = new TFile("~/clas/rootfiles/LINKS/MC_i4_2kppim_Basic_Mass.root");  
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
	//Gen
	TFile* fGen = new TFile("~/clas/rootfiles/LINKS/MC_i4_gamp_100.root");
	TTree *tGen = (TTree*)fGen->Get("GampTree_100");
	Double_t gampfactor = 100;


	TH1F *h=new TH1F("h","",500,-2,5);
	TH1F *hMC[9],*hGen[9], *hef[9]; ;
	for (int i = 0; i < 9; i++)
	{
		hMC[i] = (TH1F*)h->Clone(Form("hMC%i",i));
		hGen[i] = (TH1F*)h->Clone(Form("hGen%i",i));
		hef[i] = (TH1F*)h->Clone(Form("hef%i",i));
		
		if(i < 3)
		{
			hMC[i]->SetAxisRange(0,3.5,"X");
			hGen[i]->SetAxisRange(0,3.5,"X");
			hef[i]->SetAxisRange(0,3.5,"X");
		}
		else if (i > 5)
		{
			hMC[i]->SetAxisRange(-1.1,1.1,"X");
			hGen[i]->SetAxisRange(-1.1,1.1,"X");
			hef[i]->SetAxisRange(-1.1,1.1,"X");
		}
		else
		{
			hMC[i]->SetAxisRange(0,1.1,"X");
			hGen[i]->SetAxisRange(0,1.1,"X");
			hef[i]->SetAxisRange(0,1.1,"X");
		}
	}

	TCanvas *cMC=new TCanvas("cMC","cMC",1000,800);
	cMC->Divide(3,3);
	cMC->cd(1);
	tMC->Draw("pkp1>>hMC0","","E");
	cMC->cd(2);
	tMC->Draw("pkp2>>hMC1","","E");
	cMC->cd(3);
	tMC->Draw("ppim>>hMC2","","E");
	cMC->cd(4);
	tMC->Draw("kp1labtheta>>hMC3","","E");
	cMC->cd(5);
	tMC->Draw("kp2labtheta>>hMC4","","E");
	cMC->cd(6);
	tMC->Draw("pilabtheta>>hMC5","","E");
	cMC->cd(7);
	tMC->Draw("kp1labphi>>hMC6","","E");
	cMC->cd(8);
	tMC->Draw("kp2labphi>>hMC7","","E");
	cMC->cd(9);
	tMC->Draw("pilabphi>>hMC8","","E");




	TString Genpkp1 = "sqrt(kp1x*kp1x + kp1y*kp1y + kp1z*kp1z)>>hGen0";
	TString Genpkp2 = "sqrt(kp2x*kp2x + kp2y*kp2y + kp2z*kp2z)>>hGen1";
	TString Genppim = "sqrt(pim1x*pim1x + pim1y*pim1y + pim1z*pim1z)>>hGen2";
	TString Genkp1labtheta = "kp1z/(sqrt(kp1x*kp1x + kp1y*kp1y + kp1z*kp1z))>>hGen3";
	TString Genkp2labtheta = "kp2z/(sqrt(kp2x*kp2x + kp2y*kp2y + kp2z*kp2z))>>hGen4";
	TString Genpimlabtheta = "pim1z/(sqrt(pim1x*pim1x + pim1y*pim1y + pim1z*pim1z))>>hGen5";
	TString Genkp1labphi = "2*TMath::ATan(kp1y/kp1x)/3.14159265>>hGen6";  //the factor of two comes from the fact that the atan in phi() used in the 2kppim analyzer has a range of {-pi,pi} where root's ATan has a range of {-pi/2,pi/2}
	TString Genkp2labphi = "2*TMath::ATan(kp2y/kp2x)/3.14159265>>hGen7";
	TString Genpimlabphi = "2*TMath::ATan(pim1y/pim1x)/3.14159265>>hGen8";
	

		
	TCanvas *cGen=new TCanvas("cGen","cGen",1000,800);
	cGen->Divide(3,3);

	cGen->cd(1);
	tGen->Draw(Genpkp1,"","E");
	cGen->cd(2);
	tGen->Draw(Genpkp2,"","E");
	cGen->cd(3);
	tGen->Draw(Genppim,"","E");
	cGen->cd(4);
	tGen->Draw(Genkp1labtheta,"","E");
	cGen->cd(5);
	tGen->Draw(Genkp2labtheta,"","E");
	cGen->cd(6);
	tGen->Draw(Genpimlabtheta,"","E");
	cGen->cd(7);
	tGen->Draw(Genkp1labphi,"","E");
	cGen->cd(8);
	tGen->Draw(Genkp2labphi,"","E");
	cGen->cd(9);
	tGen->Draw(Genpimlabphi,"","E");
	
	
	
	

	TCanvas *cef=new TCanvas("cef","cef",1000,800);
	cef->Divide(3,3);
	//cef->cd(1);
	//hGen[1]->Draw("E");
	for (int i = 0; i < 9; i++)
	{	
		cef->cd(i + 1);
		hef[i]->Sumw2();
		hef[i]->Divide(hMC[i],hGen[i],1,gampfactor); //the 100 multiplies the Gen histograms by 100
		hef[i]->Draw("E");
		
	}
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	

}