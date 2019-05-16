/*
JB august 29: this reads an kpkppim ntuple from accepted events (.a1c.root) and makes yeilds 

Input:
1) a1c.root file for MC

Outputs: 
1) casyield.newdat
2) casyield.eps

Considerations:
*/



void casmcyield(Double_t eg_min, Double_t eg_max, Double_t egstep){
	TFile *f = new TFile("~/clas/rootfiles/LINKS/MC_i4_2kppim_Basic.root");
  	TNtuple *newmc3=(TNtuple *)f->Get("gpp2kppim");
  	//Load fit2BW.C;
  	ofstream casmcyielddat;
	char casmcyieldout[512];
	char psfile[512];
	sprintf(casmcyieldout,"./results/casmcyield.dat",eg_min, eg_max);
  	sprintf(psfile,"./results/casmcyield.eps",eg_min, eg_max);
  	TPostScript *ps = new TPostScript(psfile, 111);
  	casmcyielddat.open(casmcyieldout, ios::out);
  	TCanvas *c2=new TCanvas("c2", "", 20,20,600,800);
  	Int_t egbin=(eg_max-eg_min+0.001)/egstep;
  	Int_t pads=egbin/4+1;
  	cout<<pads<<" "<<egbin<<endl;
  	Double_t elow, ehigh,emean;
  	Double_t tlow, thigh,tmean;
  	Double_t tstep=0.25;
  	const int n=100;
  	TH1F *h[n][20];
  	Int_t yield;
  	Int_t yielderr;
  	Int_t tyield[10]; 
  	Int_t tyielderr[10];
  	Int_t j,jmax;
  	for(j=0;j<=9;j++){
    	tyield[j]=-1;
    	tyielderr[j]=-10;
	}
  	yielderr=0;
   	c2->Divide(3,3);
  	c2->Update();
  	char sc[30];
  	char beamcut[30];
  	char name[50];
  	Double_t tmax;
 	for( Int_t i=1;i<=egbin;i++){
    	elow=eg_min+(i-1)*egstep;
    	ehigh=eg_min+i*egstep;
    	emean=(elow+ehigh)/2;
    	sprintf(beamcut, "beam<%f&&beam>%f", ehigh, elow);
    	//sprintf(sc, "abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<1");
    	cout<<beamcut<<" ";
    	cout<<emean<<" "<<i<<endl;
    	ps->NewPage();
     	Int_t k; 
     	if(ehigh<=2.9) {
       		tstep=0.15;
     	}
     	else {
       		tstep=0.25;
     	}
     	if(ehigh<=2.9){
       		tmax=0.75;
     	}
     	else if(ehigh<=3.2){
       		tmax=1.25;
     	}
    	else if(ehigh<=3.6){
       		tmax=1.75;
     	}
     	else {
			tmax=2.25;
     	}
 		jmax=tmax/tstep;
     	for( Int_t j=0;j<jmax;j++){
       		k=j+1;
       		c2->cd(k);
       		tlow=j*tstep;
       		thigh=(j+1)*tstep;
       		tmean=(tlow+thigh)/2;
	 		h[i][j]=new TH1F(Form("h%d_%d",i,j),Form("E_{#gamma}:%4.3f to %4.3f, t':%3.2f to %3.2f",elow, ehigh, tlow,thigh),100,1.2,1.4);
       		//h[i]->SetMaximum(1.8);
       		//h[i]->SetMinimum(1.2);
       		//h[i]->SetBins(300);
       		//h1->GetXaxis()->SetTitleSize(0.04);
       		//h1->GetXaxis()->SetTitle("MM(K^{+} K^{+})/(GeV/c^{2})");
       		//h1->GetYaxis()->SetTitleSize(0.04);
       		//h1->GetYaxis()->SetTitle("Events/(2MeV/c^{2})");
 			//newmc3->Draw(Form("mmkpkp>>h%d_%d",i,j), Form("abs(scv - stv)<1&&beam<%f&&beam>%f&&tpkp1<%f&&tpkp1>%f",ehigh, elow, thigh, tlow));
       		//newmc3->Draw(Form("mmkpkp>>h%d_%d",i,j), Form("nphoton_nb1<2&&abs(mmkpkppim-1.116)<0.033&&abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4&&abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<1.1&&beam<%f&&beam>%f&&tpkp1<%f&&tpkp1>%f",ehigh, elow, thigh, tlow));
			newmc3->Draw(Form("mmkpkp>>h%d_%d",i,j), Form("abs(mmkpkppim-1.116)<0.033&&beam<%f&&beam>%f&&tpkp1<%f&&tpkp1>%f",ehigh, elow, thigh, tlow)); //JB y05
			//h[i]->GetXaxis()->SetTitleSize(0.04);
       		//  h[i]->GetXaxis()->SetTitle("MM(K^{+} K^{+})/(GeV/c^{2})");
       		//  h[i]->GetYaxis()->SetTitleSize(0.04);
       		//  h[i]->GetYaxis()->SetTitle("Events/(2MeV/c^{2})");
       		//    new->Draw("mmkpkp>>h[i]", "abs(scv-stv)<1&&beam>elow&&beam<ehigh"&&sc);
       		// if(ehigh<=1.8){
			// 	 yield=fitBW(h[i][j], i*10+j-1, 1.48, 1.58, 1,1,1,1.52, 0.02,1.45,1.65, yielderr);
			//        }
			//        else if(ehigh<=2){
			// 	 yield=fitBW(h[i][j], i*10+j-1, 1.46, 1.64, 1,1,1,1.52, 0.02,1.45,1.65, yielderr);
			//        }
			//        else if(elow>=3.6){
			// 	 yield=fitBW(h[i][j], i*10+j-1, 1.45, 1.75, 1,1,0,1.52, 0.02,1.45,1.65, yielderr);
	 
			//        }
			//        else{
			// 	 yield=fitBW(h[i][j], i*10+j-1, 1.45, 1.75, 1,1,1,1.52, 0.02,1.45,1.65, yielderr);
			//        }
       		yield=h[i][j]->GetEntries();
       		tyield[j]=yield;
       		tyielderr[j]=0;
       		c2->Update();
		} 
		casmcyielddat<<emean<<" ";
    	for(j=0;j<=9;j++){casmcyielddat<<tyield[j]<<" "<<tyielderr[j]<<" ";}
     
    	casmcyielddat<<endl;
    	c2->Update();
	}
 	casmcyielddat.close();
 	ps->Close();
 
}

//===========================================FITTING==================================================
Double_t background(Double_t *x, Double_t *par) {
	//return par[0] + par[1]*x[0] + par[2]*x[0]*x[0]+ par[3]*x[0]*x[0]*x[0];
	return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
}


Double_t lorentzianPeak(Double_t *x, Double_t *par) {
  return (0.5*par[0]*par[2]/TMath::Pi()) /
          TMath::Max( 1.e-10,
                     (x[0]-par[1])*(x[0]-par[1]) + .25*par[2]*par[2]
                    );
}

Double_t lorentzianPeak2(Double_t *x, Double_t *par) {
  return (0.5*par[0]*par[2]/TMath::Pi()) /
          TMath::Max( 1.e-10,
                     (x[0]-par[1])*(x[0]-par[1]) + .25*par[2]*par[2]
                    );
}

Double_t GaussianPeak(Double_t *x, Double_t *par)
// The signal function: a gaussian
{
   Double_t arg = 0;
   if (par[2]) arg = (x[0] - par[1])/par[2];
   Double_t sig = par[0]*TMath::Exp(-0.5*arg*arg);
   return sig;
}


// Sum of background and peak function
Double_t fitFunction(Double_t *x, Double_t *par) {
  return background(x,par) + GaussianPeak(x,&par[3]);
}

Double_t fitFunctionBW(Double_t *x, Double_t *par) {
  return background(x,par) + lorentzianPeak(x,&par[3]);
}

Double_t fitFunctionBW2(Double_t *x, Double_t *par) {
  return background(x,par) + lorentzianPeak(x,&par[3])+ lorentzianPeak2(x,&par[6]);
}

//__RelBWFun:  Relativistic Breit-Wigner Function __________________________________
// Copied From:
//C      SUBROUTINE MAKE_BWMASS(GENERATOR,MASS,NF,PF,L,G0,IFLG)
//C     Created : 27-MAR-2005  Author : A.Artamonov
double RelBWFun(Double_t *x, Double_t *par)
{
    static double pi = 3.141592; // pi
    static double mp = 0.93827;  // PDG proton mass
    static double mk = 0.49378;  // PDG K+/K- mass
    static double ml = 1.51950;  // PDG L(1520) mass
    static double wl = 0.01560;  // PDG L(1520) width
    static double r0 = 5.07883;  // interaction radius [1/GeV]
 
    double mx = x;
    double g0 = par[0]; // width
    double m0 = par[1]; // mass
    double c0 = par[2]; // normalization

    // m0->m1+m2
    int L  = 1;     // angular momentum
    int L2 = 2*L+1; // l-squared
    double m1 = mp; // decay mass #1
    double m2 = mk; // decay mass #2
    double bf0,bfx; // Blatt-Weisskopf barrier functions

    if ( m0<m1+m2 || mx<m1+m2 ) return 0.;

    // decay momenta
    double p0 = sqrt( (m0*m0-pow(m1+m2,2)) * (m0*m0-pow(m1-m2,2)) );
    double px = sqrt( (mx*mx-pow(m1+m2,2)) * (mx*mx-pow(m1-m2,2)) );
    p0 /= 2*m0;
    px /= 2*mx;

    // Blatt-Weisskopf barrier function
    if (L==0) {
	bf0 = bfx = 1.0;
    }
    else if (L==1) {
	bf0 = 1 + pow(p0*r0,2);
	bfx = 1 + pow(px*r0,2);
    }
    else if (L==2) {
	bf0 = 9 + 3*pow(p0*r0,2) + pow(p0*r0,4);
	bfx = 9 + 3*pow(px*r0,2) + pow(px*r0,4);
    }
    else return 0.;

    // dynamic resonance width
    double gx = g0*(m0/mx)*pow(px/p0,L2) * bf0/bfx;

    // compute Breit-Wigner
    double aa = m0*m0-mx*mx;
    double bb = m0*gx;
    double cc = sqrt(2*mx*bb/pi) / (aa*aa+bb*bb);
    double are = aa*cc; // real part
    double aim = bb*cc; // imaginary part
    double BreitWigner = c0 * ( are*are + aim*aim );

    return BreitWigner;
}


double RelVoigtianFun(Double_t *x, Double_t *par)
{
    double i, xx, fbw, sum = 0.0;
    //par[0]=Width parameter of B.W.
    //par[1]=Mean of peak
    //par[2]=Total area 
    //par[3]=Sigma

    // Control constants
    double np = 100.0;      // number of convolution steps
    double sc =   5.0;      // convolution extends to +-sc Gaussian sigmas

    // Range of convolution integral
    //    double xlow = x[0] - sc * par[3];
    //    double xupp = x[0] + sc * par[3];
    double xlow = 1.44;
    double xupp  = 1.8;
    double step = (xupp-xlow) / np;

    // Convolution integral of B.W. and Gaussian by sum
    for(i=1.0; i<=np/2; i++) {

	xx = xlow + (i-.5)*step;
	fbw = RelBWFun(xx,par);
	sum += fbw * TMath::Gaus(x[0],xx,par[3]);

	xx = xupp - (i-.5)*step;
	fbw = RelBWFun(xx,par);
	sum += fbw * TMath::Gaus(x[0],xx,par[3]);

    }

    return (par[2] * step * sum / par[3]);
}


double RelVoigtianBgFun(Double_t *x, Double_t *par) {
    return ( background(x,par)+ RelVoigtianFun(x,&par[3]) );
}


Double_t  fitGAUS(TH1F *histo, Int_t try, Double_t low, Double_t high, Double_t term0, Double_t term1,Double_t term2, Double_t mean, Double_t width, Double_t factor)
{
  //TText *sum[100];
  // create a TF1 with the range from tl to th and 6 parameters
  TF1 *fitFcn = new TF1("fitFcn",fitFunction, low, high, 6);

  // first try without starting values for the parameters
  // This defaults to 1 for each param.
  //histo->Fit("fitFcn", "E");

  // second try: set start values for some parameters

  fitFcn->SetParameter(0, term0); // pol c0
  fitFcn->SetParameter(1, term1);   // pol c1
  if(term2!=0) {fitFcn->SetParameter(2, term2); }// pol c2
  else {fitFcn->FixParameter(2,0);}
//fitFcn->SetParameter(3, height); // hight

 fitFcn->SetParameter(5, width);   // peak
  fitFcn->SetParameter(4, mean); // width
fitFcn->SetParameter(5, width);   // peak
  fitFcn->SetParLimits(5, 0,10000);   // peak
  fitFcn->SetLineWidth(1);   // peak
  histo->Fit("fitFcn","EV","",low,high);

  // improve the picture:
  TF1 *backFcn = new TF1(Form("backFcn_%i", try), background,low,high,3);
  backFcn->SetLineColor(4);
  backFcn->SetLineWidth(1);
  TF1 *signalFcn = new TF1(Form("signalFcn_%i", try), GaussianPeak,low,high,3);
  // signalFcn->SetLineColor(2);
  // signalFcn->SetLineWidth(5);
  
  Double_t par[6];

  // writes the fit results into the par array
   fitFcn->GetParameters(par);

   backFcn->SetParameters(par);
    backFcn->SetLineStyle(2);
 backFcn->SetLineColor(2);
   backFcn->SetLineWidth(1);
  
   backFcn->Draw("same");

   signalFcn->SetParameters(&par[3]);
    signalFcn->SetLineStyle(2);
 signalFcn->SetLineColor(4);
   signalFcn->SetLineWidth(1);
  
   signalFcn->Draw("same");
   Double_t Intg = signalFcn->Integral(par[4]-factor*par[5],par[4]+factor*par[5]);
   Double_t Intb = backFcn->Integral(par[4]-factor*par[5],par[4]+factor*par[5]);
   cout<<"Integral of function is "<<Intg<<" "<<Intb<<endl;
   //cout<<"binwidth is "<<binw<<endl;
   Double_t binw = histo->GetBinWidth(1);
   Int_t yield = Intg/binw;
   Double_t ratio = Intg/Intb;
   
   
   cout<<"Integral of histogram is "<<yield<<endl;
   TAxis *x=histo->GetXaxis();
   TAxis *y=histo->GetYaxis();
 
   Double_t startx=x->GetXmin()+0.55*(x->GetXmax()-x->GetXmin());
  Double_t starty=0.65*histo->GetMaximum();
  Double_t starty1=0.55*histo->GetMaximum();
  Double_t starty0=0.75*histo->GetMaximum();
  Double_t starty2=0.95*histo->GetMaximum();
  Double_t starty3=0.85*histo->GetMaximum();
  // cout<<startx<<" "<<starty<<endl;
  //TLatex *sum=new TLatex(startx, starty,Form("Ye_t starty0=0.85*histo->GetMaximum();
   TLatex *sum=new TLatex(startx, starty,Form("Yield: %i",yield));
   TLatex *sum1=new TLatex(startx, starty1,Form("S/B ratio: %6.2f",ratio));
   TLatex *sum0=new TLatex(startx, starty0,Form("Range: #pm %2.1f #sigma",factor));
   TLatex *sum2=new TLatex(startx, starty2,Form("Mean:%5.4f",par[4]));
   TLatex *sum3=new TLatex(startx, starty3,Form("#sigma:%5.4f",par[5]));
   sum->SetTextSize(0.05);
   sum->SetTextColor(2);
   sum->Draw("same");
   sum1->SetTextSize(0.05);
   sum1->SetTextColor(2);
   sum1->Draw("same");
   sum0->SetTextSize(0.05);
   sum0->SetTextColor(2);
   sum0->Draw("same");
   sum2->SetTextSize(0.05);
   sum2->SetTextColor(4);
   sum2->Draw("same");
   sum3->SetTextSize(0.05);
   sum3->SetTextColor(4);
   sum3->Draw("same");
   return yield;
}





Double_t  fitBW(TH1F *histo, Int_t try, Double_t low, Double_t high, Double_t term0, Double_t term1,Double_t term2, Double_t mean, Double_t width, Double_t fitlow, Double_t fithigh, Int_t &yielderr)
{
  //TText *sum[100];
  // create a TF1 with the range from tl to th and 6 parameters
  TF1 *fitFcn = new TF1("fitFcn",fitFunctionBW, low, high, 6);

  // first try without starting values for the parameters
  // This defaults to 1 for each param.
  //histo->Fit("fitFcn", "E");

  // second try: set start values for some parameters

  fitFcn->SetParameter(0, term0); // pol c0
  fitFcn->SetParameter(1, term1);   // pol c1
  if(term2!=0) {fitFcn->SetParameter(2, term2); }// pol c2
  else {fitFcn->FixParameter(2,0);}
//fitFcn->SetParameter(3, height); // hight

  fitFcn->SetParameter(4, mean); // width
  fitFcn->SetParameter(5, width);   // peak
  fitFcn->SetParLimits(5, 0,10000);   // peak
  fitFcn->SetLineWidth(1);   // peak
  histo->Fit("fitFcn","EV","",low,high);

  // improve the picture:
  TF1 *backFcn = new TF1(Form("backFcn_%i", try), background,low,high,3);
  backFcn->SetLineColor(4);
  backFcn->SetLineWidth(1);
  TF1 *signalFcn = new TF1(Form("signalFcn_%i", try), lorentzianPeak,low,high,3);
  // signalFcn->SetLineColor(2);
  // signalFcn->SetLineWidth(5);
  
  Double_t par[6];

  // writes the fit results into the par array
   fitFcn->GetParameters(par);

   backFcn->SetParameters(par);
    backFcn->SetLineStyle(2);
 backFcn->SetLineColor(2);
   backFcn->SetLineWidth(1);
  
   backFcn->Draw("same");

   signalFcn->SetParameters(&par[3]);
    signalFcn->SetLineStyle(2);
 signalFcn->SetLineColor(4);
   signalFcn->SetLineWidth(1);
  
   signalFcn->Draw("same");
   Double_t Intg = signalFcn->Integral(fitlow,fithigh);
   Double_t Intb = backFcn->Integral(fitlow,fithigh);
   cout<<"Integral of function is "<<Intg<<" "<<Intb<<endl;
   //cout<<"binwidth is "<<binw<<endl;
   Double_t binw = histo->GetBinWidth(1);
   Int_t yield = Intg/binw;
   Double_t GammaErr=fitFcn->GetParError(5);
   yielderr=yield*GammaErr/par[5];
   
   cout<<"\ngammaerr "<<GammaErr<<" "<<par[5]<<" "<<yielderr<<endl;
   Double_t ratio = Intg/Intb;
   
   
   cout<<"Integral of histogram is "<<yield<<endl;
   TAxis *x=histo->GetXaxis();
   TAxis *y=histo->GetYaxis();
 
   Double_t startx=x->GetXmin()+0.35*(x->GetXmax()-x->GetXmin());
  Double_t starty=0.65*histo->GetMaximum();
  Double_t starty1=0.55*histo->GetMaximum();
  Double_t starty0=0.75*histo->GetMaximum();
  Double_t starty2=0.95*histo->GetMaximum();
  Double_t starty3=0.85*histo->GetMaximum();
  // cout<<startx<<" "<<starty<<endl;
  //TLatex *sum=new TLatex(startx, starty,Form("Ye_t starty0=0.85*histo->GetMaximum();
   TLatex *sum=new TLatex(startx, starty,Form("Yield: %i",yield));
   TLatex *sum1=new TLatex(startx, starty1,Form("Yield Err: %i",yielderr));
   TLatex *sum0=new TLatex(startx, starty0,Form("Range: %1.3f to %1.3f",fitlow, fithigh));
   TLatex *sum2=new TLatex(startx, starty2,Form("Mean:%5.4f",par[4]));
   TLatex *sum3=new TLatex(startx, starty3,Form("#Gamma:%5.4f",par[5]));
   sum->SetTextSize(0.065);
   sum->SetTextColor(2);
   sum->Draw("same");
   sum1->SetTextSize(0.065);
   sum1->SetTextColor(2);
   sum1->Draw("same");
   sum0->SetTextSize(0.065);
   sum0->SetTextColor(2);
   sum0->Draw("same");
   sum2->SetTextSize(0.065);
   sum2->SetTextColor(4);
   sum2->Draw("same");
   sum3->SetTextSize(0.065);
   sum3->SetTextColor(4);
   sum3->Draw("same");
   return yield;
}




Double_t  fitRelBW(TH1F *histo, Int_t try, Double_t low, Double_t high, Double_t term0, Double_t term1,Double_t term2, Double_t width, Double_t mean, Double_t gsigma, Double_t fitlow, Double_t fithigh, Int_t &yielderr)
{
  //TText *sum[100];
  // create a TF1 with the range from tl to th and 6 parameters
  TF1 *fitFcn = new TF1("fitFcn",RelVoigtianBgFun, low, high, 7);

  // first try without starting values for the parameters
  // This defaults to 1 for each param.
  //histo->Fit("fitFcn", "E");

  // second try: set start values for some parameters

  fitFcn->SetParameter(0, term0); // pol c0
  fitFcn->SetParameter(1, term1);   // pol c1
  if(term2!=0) {fitFcn->SetParameter(2, term2); }// pol c2
  else {fitFcn->FixParameter(2,0);}
//fitFcn->SetParameter(3, height); // hight

   fitFcn->FixParameter(3, width);   // peak
   fitFcn->SetParameter(4, mean); // width
   //fitFcn->SetParLimits(4, mean-width/3,mean+width/3);   // mean
  //fitFcn->SetParLimits(5, 0,10000000);   // area
  fitFcn->SetParameter(6, gsigma);   // gaussian sigma
  //fitFcn->SetParLimits(6, 0.003,0.012);   // gaussian sigma

  fitFcn->SetLineWidth(1);   // peak
  histo->Fit("fitFcn","EV","",low,high);

  // improve the picture:
  TF1 *backFcn = new TF1(Form("backFcn_%i", try), background,low,high,3);
  backFcn->SetLineColor(4);
  backFcn->SetLineWidth(1);
  TF1 *signalFcn = new TF1(Form("signalFcn_%i", try), lorentzianPeak,low,high,4);
  // signalFcn->SetLineColor(2);
  // signalFcn->SetLineWidth(5);
  
  Double_t par[7];

  // writes the fit results into the par array
   fitFcn->GetParameters(par);

   backFcn->SetParameters(par);
    backFcn->SetLineStyle(2);
 backFcn->SetLineColor(2);
   backFcn->SetLineWidth(1);
  
   backFcn->Draw("same");

   signalFcn->SetParameters(&par[3]);
    signalFcn->SetLineStyle(2);
 signalFcn->SetLineColor(4);
   signalFcn->SetLineWidth(1);
  
   signalFcn->Draw("same");
   Double_t Intg = signalFcn->Integral(fitlow,fithigh);
   Double_t Intb = backFcn->Integral(fitlow,fithigh);
   cout<<"Integral of function is "<<Intg<<" "<<Intb<<endl;
   //cout<<"binwidth is "<<binw<<endl;
   Double_t binw = histo->GetBinWidth(1);
   Int_t yield = Intg/binw;
   Double_t GammaErr=fitFcn->GetParError(3);
   //yielderr=yield*GammaErr/par[3];
   
   //cout<<"\ngammaerr "<<GammaErr<<" "<<par[3]<<" "<<yielderr<<endl;
   Double_t ratio = Intg/Intb;
   
   
   cout<<"Integral of histogram is "<<yield<<endl;
   TAxis *x=histo->GetXaxis();
   TAxis *y=histo->GetYaxis();
 
   Double_t startx=x->GetXmin()+0.35*(x->GetXmax()-x->GetXmin());
  Double_t starty=0.65*histo->GetMaximum();
  Double_t starty1=0.55*histo->GetMaximum();
  Double_t starty0=0.75*histo->GetMaximum();
  Double_t starty2=0.95*histo->GetMaximum();
  Double_t starty3=0.85*histo->GetMaximum();
  // cout<<startx<<" "<<starty<<endl;
  //TLatex *sum=new TLatex(startx, starty,Form("Ye_t starty0=0.85*histo->GetMaximum();
   TLatex *sum=new TLatex(startx, starty,Form("Yield: %i",yield));
   //TLatex *sum1=new TLatex(startx, starty1,Form("Yield Err: %i",yielderr));
   TLatex *sum1=new TLatex(startx, starty1,Form("gaussian sigma: %5.4f",par[5]));
   TLatex *sum0=new TLatex(startx, starty0,Form("Range: %1.3f to %1.3f",fitlow, fithigh));
   TLatex *sum2=new TLatex(startx, starty2,Form("Mean:%5.4f",par[4]));
   TLatex *sum3=new TLatex(startx, starty3,Form("#Gamma:%5.4f",par[3]));
   sum->SetTextSize(0.065);
   sum->SetTextColor(2);
   sum->Draw("same");
   sum1->SetTextSize(0.065);
   sum1->SetTextColor(2);
   sum1->Draw("same");
   sum0->SetTextSize(0.065);
   sum0->SetTextColor(2);
   sum0->Draw("same");
   sum2->SetTextSize(0.065);
   sum2->SetTextColor(4);
   sum2->Draw("same");
   sum3->SetTextSize(0.065);
   sum3->SetTextColor(4);
   sum3->Draw("same");
   return yield;
}





void fitBW2(TH1F *histo, Int_t try, Double_t low, Double_t high, Double_t term0, Double_t term1,Double_t term2, Double_t mean, Double_t width, Double_t mean2, Double_t width2, Double_t factor)
{
  //TText *sum[100];
  // create a TF1 with the range from tl to th and 6 parameters
  TF1 *fitFcn = new TF1("fitFcn",fitFunctionBW2, low, high, 9);

  // first try without starting values for the parameters
  // This defaults to 1 for each param.
  //histo->Fit("fitFcn", "E");

  // second try: set start values for some parameters

  if(term0!=0) {fitFcn->SetParameter(0, term0);} // pol c0
  else {fitFcn->FixParameter(0,0);}
  if(term1!=0) {fitFcn->SetParameter(1, term1);} // pol c0
  else {fitFcn->FixParameter(1,0);}
   if(term2!=0) {fitFcn->SetParameter(2, term2); }// pol c2
  else {fitFcn->FixParameter(2,0);}
//fitFcn->SetParameter(3, height); // hight

  fitFcn->SetParameter(4, mean); // width
  //fitFcn->SetParameter(5, width);   // peak
  fitFcn->SetParLimits(5, width-0.005, width+0.01);   // peak
  fitFcn->SetParameter(7, mean2); // width
  fitFcn->SetParameter(8, width2);   // peak
  fitFcn->SetLineWidth(1);   // peak
  histo->Fit("fitFcn","EV","",low,high);

  // improve the picture:
  TF1 *backFcn = new TF1(Form("backFcn_%i", try), background,low,high,3);
  backFcn->SetLineColor(4);
  backFcn->SetLineWidth(1);
  TF1 *signalFcn = new TF1(Form("signalFcn_%i", try), lorentzianPeak,low,high,3);
  TF1 *signalFcn2 = new TF1(Form("signalFcn2_%i", try), lorentzianPeak2,low,high,3);
  // signalFcn->SetLineColor(2);
  // signalFcn->SetLineWidth(5);
  
  Double_t par[9];

  // writes the fit results into the par array
   fitFcn->GetParameters(par);
   Double_t xsq = fitFcn->GetChisquare();
   Double_t ndf = fitFcn->GetNDF();
   backFcn->SetParameters(&par[0]);
    backFcn->SetLineStyle(2);
 backFcn->SetLineColor(2);
   backFcn->SetLineWidth(1);
  
   backFcn->Draw("same");

   signalFcn->SetParameters(&par[3]);
    signalFcn->SetLineStyle(2);
 signalFcn->SetLineColor(4);
   signalFcn->SetLineWidth(1);
  
   signalFcn->Draw("same");


  signalFcn2->SetParameters(&par[6]);
    signalFcn2->SetLineStyle(2);
 signalFcn2->SetLineColor(4);
   signalFcn2->SetLineWidth(1);
  
   signalFcn2->Draw("same");
   Double_t Intg = signalFcn->Integral(par[4]-factor*par[5],par[4]+factor*par[5]);
 Double_t Intg2 = signalFcn2->Integral(par[7]-factor*par[8],par[7]+factor*par[8]);
   Double_t Intb = backFcn->Integral(par[4]-factor*par[5],par[4]+factor*par[5]);
   cout<<"Integral of function is "<<Intg<<" "<<Intb<<endl;
   //cout<<"binwidth is "<<binw<<endl;
   Double_t binw = histo->GetBinWidth(1);
   Int_t yield = Intg/binw;
   Int_t yield2 = Intg2/binw;
   //Double_t ratio = Intg/Intb;
   
   
   cout<<"Integral of histogram is "<<yield<<endl;
   TAxis *x=histo->GetXaxis();
   TAxis *y=histo->GetYaxis();
 
   Double_t startx=x->GetXmin()+0.65*(x->GetXmax()-x->GetXmin());
  Double_t starty=0.7*histo->GetMaximum();
  Double_t starty1=0.6*histo->GetMaximum();
  Double_t starty30=0.5*histo->GetMaximum();
  Double_t starty0=0.4*histo->GetMaximum();
  Double_t starty2=1.0*histo->GetMaximum();
  Double_t starty3=0.9*histo->GetMaximum();
  Double_t starty10=0.8*histo->GetMaximum();
  // cout<<startx<<" "<<starty<<endl;
  //TLatex *sum=new TLatex(startx, starty,Form("Ye_t starty0=0.85*histo->GetMaximum();
   TLatex *sum=new TLatex(startx, starty,Form("Mean2:%5.4f",par[7]));
   TLatex *sum1=new TLatex(startx, starty1,Form("#Gamma2: %5.4f",par[8]));
   TLatex *sum10=new TLatex(startx, starty10,Form("Yield: %i",yield));
    TLatex *sum2=new TLatex(startx, starty2,Form("Mean:%5.4f",par[4]));
   TLatex *sum3=new TLatex(startx, starty3,Form("#Gamma:%5.4f",par[5]));
   TLatex *sum30=new TLatex(startx, starty30,Form("Yield2: %i",yield2));
   TLatex *sum4=new TLatex(startx, starty0,Form("#chi^{2}/Ndf: %5.1f/%5.1f",xsq, ndf));
   sum->SetTextSize(0.065);
   sum->SetTextColor(2);
   sum->Draw("same");
   sum1->SetTextSize(0.065);
   sum1->SetTextColor(2);
   sum1->Draw("same");
   sum10->SetTextSize(0.065);
   sum10->SetTextColor(2);
   sum10->Draw("same");
    sum2->SetTextSize(0.065);
   sum2->SetTextColor(4);
   sum2->Draw("same");
   sum3->SetTextSize(0.065);
   sum3->SetTextColor(4);
   sum3->Draw("same");
   sum30->SetTextSize(0.065);
   sum30->SetTextColor(4);
   sum30->Draw("same");
  sum4->SetTextSize(0.065);
   sum4->SetTextColor(4);
   sum4->Draw("same");
 }

