/*
Name: Stage4.C
Author: Jason Bono
Date: October 25 2012
Purpose: plot polarization
Input: ./hists/histsStage3.root
Output: ./txt/Ebins.txt & Xibins.txt

Notes:
	!Read the comment section in GetW.C for more background!
*/

#include <iostream>
//#include <fstream>
//using namespace std;


void Stage4()
{
	//some syle for the plots
	gStyle->SetErrorX(0.0);
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);

	char *s = new char[1]; 
	const bool cheat = 0;
	if (cheat)
	{
		cout << "cheating was chosen, hit enter to accept" <<endl;	
		gets(s);
		cout << "cheating accepted" << endl;
		//gROOT->ProcessLine(".q");	
	}
	else
	{
		cout << "no cheating this time... hit enter to accept" <<endl;	
		gets(s);
		cout << "no cheating method accepted" << endl;	
		//gROOT->ProcessLine(".q");	
	}
	
	//binning (keep this consistant with all stages)
	const int NEBins = 3; 
	const int NXiBins = 3; 
	const int NPiBins = 4;
	
	//open the ouput of Stage3.C
	TFile* fhS3 = new TFile("./hists/histsStage3.root");
	
	//open two txt files for writing	
	ofstream myEfile,myXifile;
	myEfile.open ("./txt/Ebins.txt");
	myXifile.open ("./txt/Xibins.txt");
	
	//--------------read in the histograms from stage 3-------------
	//EBins
	TH1F *hDataEx[NEBins];
	TH1F *hDataEy[NEBins];
	TH1F *hDataEz[NEBins];
	for (int i = 0; i < NEBins; i++)
	{
		hDataEx[i] = (TH1F*)fhS3->Get(Form("hDataAc-EBin%i-x",i));
		hDataEy[i] = (TH1F*)fhS3->Get(Form("hDataAc-EBin%i-y",i));
		hDataEz[i] = (TH1F*)fhS3->Get(Form("hDataAc-EBin%i-z",i));
		hDataEx[i]->SetMinimum(0);
		hDataEy[i]->SetMinimum(0);
		hDataEz[i]->SetMinimum(0);

		
		//.................more style.............
		hDataEx[i]->SetLabelSize(0.05);
		hDataEx[i]->GetXaxis()->SetTitleSize(0.07);
		hDataEx[i]->GetYaxis()->SetTitleSize(0.07);
		hDataEx[i]->SetMarkerColor(4);
		hDataEx[i]->SetLineColor(4);
		hDataEx[i]->GetXaxis()->CenterTitle();
		hDataEx[i]->GetYaxis()->CenterTitle();
		
		hDataEy[i]->SetLabelSize(0.05);
		hDataEy[i]->GetXaxis()->SetTitleSize(0.07);
		hDataEy[i]->GetYaxis()->SetTitleSize(0.07);
		hDataEy[i]->SetMarkerColor(4);
		hDataEy[i]->SetLineColor(4);
		hDataEy[i]->GetXaxis()->CenterTitle();
		hDataEy[i]->GetYaxis()->CenterTitle();
		
		hDataEz[i]->SetLabelSize(0.05);
		hDataEz[i]->GetXaxis()->SetTitleSize(0.07);
		hDataEz[i]->GetYaxis()->SetTitleSize(0.07);
		hDataEz[i]->SetMarkerColor(4);
		hDataEz[i]->SetLineColor(4);
		hDataEz[i]->GetXaxis()->CenterTitle();
		hDataEz[i]->GetYaxis()->CenterTitle();
		//...........................................	
		
	}
	//now cheat
	if (cheat)
	{
		
		hDataEx[0]->SetBinContent(1, -100);
		Double_t newerr1 = 0.0001*hDataEy[1]->GetBinContent(2);
		hDataEy[0]->SetBinError(3, 10000);
		hDataEz[0]->SetBinContent(4,-100);
		hDataEz[0]->SetBinError(2,14000);
		
	}
	
	//XiBins
	TH1F *hDataXix[NXiBins];
	TH1F *hDataXiy[NXiBins];
	TH1F *hDataXiz[NXiBins];
	for (int i = 0; i < NXiBins; i++)
	{
		hDataXix[i] = (TH1F*)fhS3->Get(Form("hDataAc-XiBin%i-x",i));
		hDataXiy[i] = (TH1F*)fhS3->Get(Form("hDataAc-XiBin%i-y",i));
		hDataXiz[i] = (TH1F*)fhS3->Get(Form("hDataAc-XiBin%i-z",i));
		hDataXix[i]->SetMinimum(0);
		hDataXiy[i]->SetMinimum(0);
		hDataXiz[i]->SetMinimum(0);
		
		//.................more style.............
		hDataXix[i]->SetLabelSize(0.05);
		hDataXix[i]->GetXaxis()->SetTitleSize(0.07);
		hDataXix[i]->GetYaxis()->SetTitleSize(0.07);
		hDataXix[i]->SetMarkerColor(4);
		hDataXix[i]->SetLineColor(4);
		hDataXix[i]->GetXaxis()->CenterTitle();
		hDataXix[i]->GetYaxis()->CenterTitle();
		
		hDataXiy[i]->SetLabelSize(0.05);
		hDataXiy[i]->GetXaxis()->SetTitleSize(0.07);
		hDataXiy[i]->GetYaxis()->SetTitleSize(0.07);
		hDataXiy[i]->SetMarkerColor(4);
		hDataXiy[i]->SetLineColor(4);
		hDataXiy[i]->GetXaxis()->CenterTitle();
		hDataXiy[i]->GetYaxis()->CenterTitle();
		
		hDataXiz[i]->SetLabelSize(0.05);
		hDataXiz[i]->GetXaxis()->SetTitleSize(0.07);
		hDataXiz[i]->GetYaxis()->SetTitleSize(0.07);
		hDataXiz[i]->SetMarkerColor(4);
		hDataXiz[i]->SetLineColor(4);
		hDataXiz[i]->GetXaxis()->CenterTitle();
		hDataXiz[i]->GetYaxis()->CenterTitle();
		//...........................................
		
	}
	//---------------------------------------------------------------
	
	//define the fit and the varaibles to parse the parameters to
	TF1 *F1 = new TF1("F1","pol1", -1, 1);
	TF1 *F2 = new TF1("F2", "[0] + 4.366*[0]*[1]*x", -1, 1);
	F1->SetLineWidth(2);
	F2->SetLineWidth(2);
	
	//EBins
	Double_t p0Ex[NEBins], p0Ey[NEBins], p0Ez[NEBins];
	Double_t p0ExEr[NEBins], p0EyEr[NEBins], p0EzEr[NEBins];
	Double_t p1Ex[NEBins], p1Ey[NEBins], p1Ez[NEBins];
	Double_t p1ExEr[NEBins], p1EyEr[NEBins], p1EzEr[NEBins];
	
	//XiBins
	Double_t p0Xix[NXiBins], p0Xiy[NXiBins], p0Xiz[NXiBins];
	Double_t p0XixEr[NXiBins], p0XiyEr[NXiBins], p0XizEr[NXiBins];
	Double_t p1Xix[NXiBins], p1Xiy[NXiBins], p1Xiz[NXiBins];
	Double_t p1XixEr[NXiBins], p1XiyEr[NXiBins], p1XizEr[NXiBins];
	
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EBins~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//fit and display the histograms
	TLatex *tex0=new TLatex(0.0, 0.0,"STUFF0");
	TLatex *tex1=new TLatex(0.0, 0.0,"STUFF1");
	
	Double_t yy0,yy1;
	TCanvas *cE = new TCanvas("cE","cE",1000,500);
	cE->Divide(3,NEBins);
	for (int i = 0; i < NEBins; i++)
	{
		
		cE->cd(1 + 3*i);
		gPad->SetMargin(0.15,0.1,0.15,0.14);
		hDataEx[i]->Fit("F1","Q","",-0.5,1);
		p0Ex[i] = F1->GetParameter(0);
		p0ExEr[i] = F1->GetParError(0);
	    p1Ex[i] = F1->GetParameter(1);
		p1ExEr[i] = F1->GetParError(1);
		hDataEx[i]->Draw(); 
	//	yy0 = (0.35)*(hDataEx[i]->GetMaximum());
	//	yy1 = (0.2)*(hDataEx[i]->GetMaximum());
	//	tex0=new TLatex(-0.9, yy0,Form("p0 = %g #pm %g ",p0Ex[i],p0ExEr[i]));
	//	tex1=new TLatex(-0.9, yy1,Form("p1 = %g #pm %g ",p1Ex[i],p1ExEr[i]));
	//	tex0->SetTextSize(0.06); 
	//	tex0->SetTextColor(4);
	//	tex1->SetTextSize(0.06); 
	//	tex1->SetTextColor(4);
		//tex0->Draw("SAME");
		//tex1->Draw("SAME");
			
		cE->cd(2 + 3*i);
		gPad->SetMargin(0.15,0.1,0.15,0.14);
		hDataEy[i]->Fit("F1","RQ");
		p0Ey[i] = F1->GetParameter(0);
		p0EyEr[i] = F1->GetParError(0);
		p1Ey[i] = F1->GetParameter(1);
		p1EyEr[i] = F1->GetParError(1);
		hDataEy[i]->Draw();
	//	yy0 = (0.35)*(hDataEy[i]->GetMaximum());
	//	yy1 = (0.2)*(hDataEy[i]->GetMaximum());
	//	tex0=new TLatex(-0.9, yy0,Form("p0 = %g #pm %g ",p0Ey[i],p0EyEr[i]));
	//	tex1=new TLatex(-0.9, yy1,Form("p1 = %g #pm %g ",p1Ey[i],p1EyEr[i]));
	//	tex0->SetTextSize(0.06); 
	//	tex0->SetTextColor(4);
	//	tex1->SetTextSize(0.06); 
	//	tex1->SetTextColor(4);
		//tex0->Draw("SAME");
		//tex1->Draw("SAME");
			
		cE->cd(3 + 3*i);
		gPad->SetMargin(0.15,0.1,0.15,0.14);
		hDataEz[i]->Fit("F1","RQ","",-1,0.5);
		p0Ez[i] = F1->GetParameter(0);
		p0EzEr[i] = F1->GetParError(0);
		p1Ez[i] = F1->GetParameter(1);
		p1EzEr[i] = F1->GetParError(1);
		hDataEz[i]->Draw();
	//	yy0 = (0.35)*(hDataEz[i]->GetMaximum());
	//	yy1 = (0.2)*(hDataEz[i]->GetMaximum());
	//	tex0=new TLatex(-0.9, yy0,Form("p0 = %g #pm %g ",p0Ez[i],p0EzEr[i]));
	//	tex1=new TLatex(-0.9, yy1,Form("p1 = %g #pm %g ",p1Ez[i],p1EzEr[i]));
	//	tex0->SetTextSize(0.06); 
	//	tex0->SetTextColor(4);
	//	tex1->SetTextSize(0.06); 
	//	tex1->SetTextColor(4);
		//tex0->Draw("SAME");
		//tex1->Draw("SAME");
	}
	//compute polarization and error
	Double_t P[NEBins], Cx[NEBins], Cz[NEBins];
	Double_t PEr[NEBins], CxEr[NEBins], CzEr[NEBins];
	for (int i = 0; i < NEBins; i++)
	{
		Cx[i] = (-2*p1Ex[i])/(-0.458*p0Ex[i]);
		P[i] = (-2*p1Ey[i])/(-0.458*p0Ey[i]);
		Cz[i] = (-2*p1Ez[i])/(-0.458*p0Ez[i]);
		
		CxEr[i] = sqrt(Cx[i]*Cx[i])*sqrt((p1ExEr[i]*p1ExEr[i])/(p1Ex[i]*p1Ex[i]) + (p0ExEr[i]*p0ExEr[i])/(p0Ex[i]*p0Ex[i]));
		PEr[i] = sqrt(P[i]*P[i])*sqrt((p1ExEr[i]*p1ExEr[i])/(p1Ex[i]*p1Ex[i]) + (p0ExEr[i]*p0ExEr[i])/(p0Ex[i]*p0Ex[i]));
		CzEr[i] = sqrt(Cz[i]*Cz[i])*sqrt((p1ExEr[i]*p1ExEr[i])/(p1Ex[i]*p1Ex[i]) + (p0ExEr[i]*p0ExEr[i])/(p0Ex[i]*p0Ex[i]));
		
		//slap on the latex lables 
		//x
		cE->cd(1 + 3*i);
		yy0 = (0.35)*(hDataEx[i]->GetMaximum());
		yy1 = (0.2)*(hDataEx[i]->GetMaximum());
		tex0=new TLatex(-0.9, yy0,Form("Cx = %5.3f #pm %5.3f ",Cx[i],CxEr[i]));
		tex0->SetTextSize(0.06); 
		tex0->SetTextColor(4);
		tex0->Draw("SAME");	
		
		//y
		cE->cd(2 + 3*i);
		yy0 = (0.35)*(hDataEy[i]->GetMaximum());
		yy1 = (0.2)*(hDataEy[i]->GetMaximum());
		tex0=new TLatex(-0.9, yy0,Form("P = %5.3f #pm %5.3f ",P[i],PEr[i]));
		tex0->SetTextSize(0.06); 
		tex0->SetTextColor(4);
		tex0->Draw("SAME");
		
		//z
		cE->cd(3 + 3*i);
		yy0 = (0.35)*(hDataEz[i]->GetMaximum());
		yy1 = (0.2)*(hDataEz[i]->GetMaximum());
		tex0=new TLatex(-0.9, yy0,Form("Cz = %5.3f #pm %5.3f ",Cz[i],CzEr[i]));
		tex0->SetTextSize(0.06); 
		tex0->SetTextColor(4);
		tex0->Draw("SAME");
		
		cout <<"---------------------------------------------------------------------"<<endl;
		cout << "i = " << i << " Cx = " << Cx[i] << " pm " << CxEr[i] <<endl;
		cout << "i = " << i << " P = " << P[i] << " pm " << PEr[i] <<endl;
		cout << "i = " << i << " Cz = " << Cz[i] << " pm " << CzEr[i] <<endl;
			
		/*
		cout <<"---------------------------------------------------------------------"<<endl;
		cout << "i = " << i << " p0x = " << p0Ex[i] << " #pm " << p0ExEr[i] <<endl;
		cout << "i = " << i << " p0y = " << p0Ey[i] << " #pm " << p0EyEr[i] <<endl;
		cout << "i = " << i << " p0z = " << p0Ez[i] << " #pm " << p0EzEr[i] <<endl;
		cout <<endl;
		cout << "i = " << i << " p1x = " << p1Ex[i] << " #pm " << p1ExEr[i] <<endl;
		cout << "i = " << i << " p1y = " << p1Ey[i] << " #pm " << p1EyEr[i] <<endl;
		cout << "i = " << i << " p1z = " << p1Ez[i] << " #pm " << p1EzEr[i] <<endl;
		cout <<endl;
		*/
	}	
	
	//replot for the NSF proposal
	TCanvas *cNSF = new TCanvas("cNSF","cNSF",1000,500);
	cNSF->Divide(3,0);
	cNSF->cd(1);
	hDataEx[0]->Draw();
	
	Double_t E[NEBins];
	E[0] = 3.65;
	E[1] = 4.35;
	E[2] = 5.1;
	
	for (int i = 0; i < NEBins; i++)
	{
		myEfile << E[i] <<" "<< Cx[i] <<" "<< CxEr[i] <<" "<< P[i] <<" "<< PEr[i] <<" "<< Cz[i] <<" "<<CzEr[i] <<endl; 
	}
	myEfile.close();
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~XiBins~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//fit and display the histograms
	TLatex *tex2=new TLatex(0.0, 0.0,"STUFF2");
	TLatex *tex3=new TLatex(0.0, 0.0,"STUFF3");

	//fit and display the histograms
	TCanvas *cXi = new TCanvas("cXi","cXi",1000,500);
	cXi->Divide(3,NXiBins);
	for (int i = 0; i < NXiBins; i++)
	{
		
		cXi->cd(1 + 3*i);
		gPad->SetMargin(0.15,0.1,0.15,0.14);
		hDataXix[i]->Fit("F1","RQ","",-0.5,1);
		p0Xix[i] = F1->GetParameter(0);
		p0XixEr[i] = F1->GetParError(0);
	    p1Xix[i] = F1->GetParameter(1);
		p1XixEr[i] = F1->GetParError(1);
		hDataXix[i]->Draw(); 
		
		cXi->cd(2 + 3*i);
		gPad->SetMargin(0.15,0.1,0.15,0.14);
		hDataXiy[i]->Fit("F1","RQ");
		p0Xiy[i] = F1->GetParameter(0);
		p0XiyEr[i] = F1->GetParError(0);
		p1Xiy[i] = F1->GetParameter(1);
		p1XiyEr[i] = F1->GetParError(1);
		hDataXiy[i]->Draw();
		
		cXi->cd(3 + 3*i);
		gPad->SetMargin(0.15,0.1,0.15,0.14);
		hDataXiz[i]->Fit("F1","RQ","",-1,0.5);
		p0Xiz[i] = F1->GetParameter(0);
		p0XizEr[i] = F1->GetParError(0);
		p1Xiz[i] = F1->GetParameter(1);
		p1XizEr[i] = F1->GetParError(1);
		hDataXiz[i]->Draw();

	}

	//compute polarization and error
	Double_t P[NXiBins], Cx[NXiBins], Cz[NXiBins];
	Double_t PEr[NXiBins], CxEr[NXiBins], CzEr[NXiBins];
	for (int i = 0; i < NXiBins; i++)
	{
		Cx[i] = (-2*p1Xix[i])/(-0.458*p0Xix[i]);
		P[i] = (-2*p1Xiy[i])/(-0.458*p0Xiy[i]);
		Cz[i] = (-2*p1Xiz[i])/(-0.458*p0Xiz[i]);
		
		CxEr[i] = Cx[i]*sqrt((p1XixEr[i]*p1XixEr[i])/(p1Xix[i]*p1Xix[i]) + (p0XixEr[i]*p0XixEr[i])/(p0Xix[i]*p0Xix[i]));
		PEr[i] = P[i]*sqrt( (p1XixEr[i]*p1XixEr[i])/(p1Xix[i]*p1Xix[i]) + (p0XixEr[i]*p0XixEr[i])/(p0Xix[i]*p0Ex[i]) );
		CzEr[i] = Cz[i]*sqrt((p1XixEr[i]*p1XixEr[i])/(p1Xix[i]*p1Xix[i]) + (p0XixEr[i]*p0XixEr[i])/(p0Xix[i]*p0Xix[i]));

		//slap on the latex lables 
		//x
		cXi->cd(1 + 3*i);
		yy0 = (0.35)*(hDataXix[i]->GetMaximum());
		yy1 = (0.2)*(hDataXix[i]->GetMaximum());
		tex2=new TLatex(-0.9, yy0,Form("Cx = %5.3f #pm %5.3f ",Cx[i],CxEr[i]));
		tex2->SetTextSize(0.06); 
		tex2->SetTextColor(4);
		tex2->Draw("SAME");	
		
		//y
		cXi->cd(2 + 3*i);
		yy0 = (0.35)*(hDataXiy[i]->GetMaximum());
		yy1 = (0.2)*(hDataXiy[i]->GetMaximum());
		tex2=new TLatex(-0.9, yy0,Form("P = %5.3f #pm %5.3f ",P[i],PEr[i]));
		tex2->SetTextSize(0.06); 
		tex2->SetTextColor(4);
		tex2->Draw("SAME");
		
		//z
		cXi->cd(3 + 3*i);
		yy0 = (0.35)*(hDataXiz[i]->GetMaximum());
		yy1 = (0.2)*(hDataXiz[i]->GetMaximum());
		tex2=new TLatex(-0.9, yy0,Form("Cz = %5.3f #pm %5.3f ",Cz[i],CzEr[i]));
		tex2->SetTextSize(0.06); 
		tex2->SetTextColor(4);
		tex2->Draw("SAME");
		
		cout <<"---------------------------------------------------------------------"<<endl;
		cout << "i = " << i << " Cx = " << Cx[i] << " pm " << CxEr[i] <<endl;
		cout << "i = " << i << " P = " << P[i] << " pm " << PEr[i] <<endl;
		cout << "i = " << i << " Cz = " << Cz[i] << " pm " << CzEr[i] <<endl;
	}	
	Double_t Xi[NXiBins];
	Xi[0] = -0.66;
	Xi[1] = 0.0;
	Xi[2] = 0.66;
	
	for (int i = 0; i < NXiBins; i++)
	{
		myXifile << Xi[i] <<" "<< Cx[i] <<" "<< CxEr[i] <<" "<< P[i] <<" "<< PEr[i] <<" "<< Cz[i] <<" "<<CzEr[i] <<endl; 
	}
	myEfile.close();
	
	
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	
}