void kstaryield(Double_t eg_min, Double_t eg_max, Double_t egstep){
  TFile *f = new TFile("kstarmc.root");
  TNtuple *kstarmc=(TNtuple *)f->Get("kstarmc");
  //Load fit2BW.C;
  ofstream kstaryielddat;
  char kstaryieldout[30], psfile[30];
   sprintf(kstaryieldout,"kstaryield_%5.4f_%5.4f.newdat",eg_min, eg_max);
  sprintf(psfile,"kstaryield_%5.4f_%5.4f.ps",eg_min, eg_max);
  TPostScript *ps = new TPostScript(psfile, 111);
  kstaryielddat.open(kstaryieldout, ios::out);
  TCanvas *c2=new TCanvas("c2", "", 20,20,600,800);
  Int_t egbin=(eg_max-eg_min)/egstep;
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
    tyielderr[j]=-10;}

  yielderr=0;
   c2->Divide(3,4);
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
     tstep=0.2;
     jmax=2/tstep;
 
     for( Int_t j=0;j<jmax;j++){
       k=j+1;
       c2->cd(k);
       tlow=-1+j*tstep;
       thigh=-1+(j+1)*tstep;
       tmean=(tlow+thigh)/2;
       if(thigh>=0.6||(elow>=3.6&&thigh<=-0.8)){
	 h[i][j]=new TH1F(Form("h%d_%d",i,j),Form("E_{#gamma}:%5.4f to %5.4f, Cos*(#theta_{K^{*+}}):%3.2f to %3.2f",elow, ehigh, tlow,thigh),100,0.6,1.6);}
       else {
	 h[i][j]=new TH1F(Form("h%d_%d",i,j),Form("E_{#gamma}:%5.4f to %5.4f, Cos*(#theta_{K^{*+}}):%3.2f to %3.2f",elow, ehigh, tlow,thigh),200,0.6,1.6);
       }
       
       //h[i]->SetMaximum(1.8);
       //h[i]->SetMinimum(1.2);
       //h[i]->SetBins(300);
       //h1->GetXaxis()->SetTitleSize(0.04);
       //h1->GetXaxis()->SetTitle("MM(K^{+} K^{+})/(GeV/c^{2})");
       //h1->GetYaxis()->SetTitleSize(0.04);
       //h1->GetYaxis()->SetTitle("Events/(2MeV/c^{2})");
       
       //kstarmc->Draw(Form("mmkpkp>>h%d_%d",i,j), Form("abs(scv-stv)<1&&beam<%f&&beam>%f&&tpkp1<%f&&tpkp1>%f&&abs(vz+10)<21",ehigh, elow, thigh, tlow));
       kstarmc->Draw(Form("conmkppi0>>h%d_%d",i,j), Form("abs(scv-stv)<1&&abs(mppim-1.1159)<0.0048&&abs(sctkp-sclkp/(betakp*29.99)-scv)<1&&abs(mm2kpppi-0.0166)<0.0246&&nkm<1&&npip<1&&np<2&&npim<2&&nkp<2&&ngamma<3&&beam<%f&&beam>%f&&(-lamcmtheta)<%f&&(-lamcmtheta)>%f",ehigh, elow, thigh, tlow));
       //yield=fitBW(h[i][j],i*10+j-1,0.65,1.2,1,1,1,1,0.892,0.051,0.7,1.15,yielderr);
       Int_t hentry=0;
       hentry=h[i][j]->GetEntries();
 //       if(hentry<1||yield>hentry){
// 	 tyield[j]=0;
// 	 tyielderr[j]=-10;
//        }
//        else{
// 	 tyield[j]=yield;
// 	 tyielderr[j]=yielderr;
//        }    
       tyield[j]=hentry;
       tyielderr[j]=sqrt(hentry);
       c2->Update();
     } 
     kstaryielddat<<emean<<" ";
     for(j=0;j<10;j++){kstaryielddat<<tyield[j]<<" "<<tyielderr[j]<<" ";}
     
     kstaryielddat<<endl;
     c2->Update();
     }
 kstaryielddat.close();
 ps->Close();
 
 }


Double_t background(Double_t *x, Double_t *par) {
  //return par[0] + par[1]*x[0] + par[2]*x[0]*x[0]+ par[3]*x[0]*x[0]*x[0];
  Double_t mth=0.63;
  Double_t dm=x[0]-mth;
  //return par[0] + par[1]*dm + par[2]*dm**2 + par[3]*dm**3;
  return par[0]*dm**par[1]*TMath::Exp(-par[2]*dm-par[3]*dm**2);
}

Double_t q(Double_t m){
  //Double_t ml=1.115683;
  Double_t mkp=0.494;
  Double_t mpi0=0.13498;
  Double_t mth=0.63;
  if(m>mth){
    return sqrt(((m**2+mkp**2-mpi0**2)/(2*m))**2-mkp**2);
  }
  else {return 0;}

}

Double_t bwPeak(Double_t *x, Double_t *par) {
  //cout<<q(x[0])<<" "<<q(par[1])<<" "<<endl;
  Double_t gamma=par[2]*(2*q(par[1])**2)/TMath::Max(1.e-10, q(x[0])**2+q(par[1])**2)*(q(x[0])/
			 TMath::Max(1.e-5,
				    q(par[1]))
										     )**3;
  return par[0]*x[0]*gamma/
    TMath::Max( 1.e-10,((x[0]**2-par[1]**2)**2+(par[1]*gamma)**2));
}

Double_t bwPeak2(Double_t *x, Double_t *par) {
  //Double_t gamma=par[2]*(q(x[0])/TMath::Max( 1.e-5,q(par[1])))**3;
  //return par[0]*x[0]*gamma/
  //  TMath::Max( 1.e-10,((x[0]**2-par[1]**2)**2+(par[1]*gamma)**2));

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
  return background(x,par) + bwPeak(x,&par[4]);
}

Double_t fitFunctionBW2(Double_t *x, Double_t *par) {
  return background(x,par) + bwPeak(x,&par[6])+ bwPeak2(x,&par[9]);
}



Double_t  fitGAUS(TH1F *histo, Int_t try, Double_t low, Double_t high, Double_t term0, Double_t term1,Double_t term2, Double_t mean, Double_t width, Double_t factor, Int_t &yielderr)
{
  //TText *sum[100];
  // create a TF1 with the range from tl to th and 6 parameters
  TF1 *fitFcn = new TF1("fitFcn",fitFunction, low, high, 6);
  fitFcn->SetLineStyle(2);
  fitFcn->SetLineColor(4);
  fitFcn->SetLineWidth(1);
  

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
 fitFcn->SetParLimits(4, mean-0.005,mean+0.005);   // peak
fitFcn->SetParameter(5, width);   // peak
 fitFcn->SetParLimits(5, 0.005, 0.01);   // peak
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
   //   signalFcn->SetLineStyle(2);
   //signalFcn->SetLineColor(4);
   //signalFcn->SetLineWidth(1);
  
   //signalFcn->Draw("same");
   Double_t Intg = signalFcn->Integral(par[4]-factor*par[5],par[4]+factor*par[5]);
   Double_t Intb = backFcn->Integral(par[4]-factor*par[5],par[4]+factor*par[5]);
   cout<<"Integral of function is "<<Intg<<" "<<Intb<<endl;
   //cout<<"binwidth is "<<binw<<endl;
   Double_t binw = histo->GetBinWidth(1);
   Int_t yield = Intg/binw;
   Double_t ratio = Intg/Intb;
   Double_t GammaErr=fitFcn->GetParError(5);
   yielderr=yield*GammaErr/par[5];
   
  
   
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





Double_t  fitBW(TH1F *histo, Int_t try, Double_t low, Double_t high, Double_t term0, Double_t term1,Double_t term2, Double_t term3, Double_t mean, Double_t width, Double_t fitlow, Double_t fithigh, Int_t &yielderr)
{
  //TText *sum[100];
  // create a TF1 with the range from tl to th and 9 parameters
  TF1 *fitFcn = new TF1("fitFcn",fitFunctionBW, low, high, 7);

  // first try without starting values for the parameters
  // This defaults to 1 for each param.
  //histo->Fit("fitFcn", "E");

  // second try: set start values for some parameters
 if(term0!=0) {fitFcn->SetParameter(0, term0);
   fitFcn->SetParLimits(0, 0,100000);  
   
 } // pol c0
  else {fitFcn->FixParameter(0,0);}
  if(term1!=0) {fitFcn->SetParameter(1, term1);} // pol c0
  else {fitFcn->FixParameter(1,0);}
   if(term2!=0) {fitFcn->SetParameter(2, term2); }// pol c2
  else {fitFcn->FixParameter(2,0);}
  if(term3!=0) {fitFcn->SetParameter(3, term3);} // pol c3
  else {fitFcn->FixParameter(3,0);}
//fitFcn->SetParameter(4, height); // hight

  fitFcn->SetParLimits(4, 0,100000);  

  fitFcn->SetParameter(5, mean); // mass
  fitFcn->SetParLimits(5, mean-0.005,mean+0.005);   
  fitFcn->SetParameter(6, width);   // width
  fitFcn->SetParLimits(6, width-0.002,width+0.005);  
   fitFcn->SetLineWidth(1);  
  histo->Fit("fitFcn","EV","",low,high);

  // improve the picture:
  TF1 *backFcn = new TF1(Form("backFcn_%i", try), background,low,high,6);
  backFcn->SetLineColor(4);
  backFcn->SetLineWidth(1);
  TF1 *signalFcn = new TF1(Form("signalFcn_%i", try), bwPeak,low,high,3);
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
   
   signalFcn->SetParameters(&par[4]);
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
   Double_t GammaErr=fitFcn->GetParError(6);
   yielderr=yield*GammaErr/par[6];
   
   cout<<"\ngammaerr "<<GammaErr<<" "<<par[6]<<" "<<yielderr<<endl;
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
   TLatex *sum2=new TLatex(startx, starty2,Form("Mean:%5.4f",par[5]));
   TLatex *sum3=new TLatex(startx, starty3,Form("#Gamma:%5.4f",par[6]));
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





void fitBW2(TH1F *histo, Int_t try, Double_t low, Double_t high, Double_t term0, Double_t term1,Double_t term2, Double_t term3, Double_t term4,Double_t term5, Double_t mean, Double_t width, Double_t mean2, Double_t width2, Double_t factor)
{
  //TText *sum[100];
  // create a TF1 with the range from tl to th and 6 parameters
  TF1 *fitFcn = new TF1("fitFcn",fitFunctionBW2, low, high, 12);

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
  if(term3!=0) {fitFcn->SetParameter(3, term3);} // pol c3
  else {fitFcn->FixParameter(3,0);}
  if(term4!=0) {fitFcn->SetParameter(4, term4);} // pol c4
  else {fitFcn->FixParameter(4,0);}
   if(term5!=0) {fitFcn->SetParameter(5, term5); }// pol c5
  else {fitFcn->FixParameter(5,0);}
//fitFcn->SetParameter(6, height); // hight

  fitFcn->SetParLimits(6,0,100000);   // peak
  fitFcn->SetParameter(7, mean); // width
  //fitFcn->SetParameter(8, width);   // peak
  fitFcn->SetParLimits(8, width-0.005, width+0.01);   // peak
  fitFcn->SetParLimits(9,0,10000);   // peak
  fitFcn->SetParameter(10, mean2); // width
  fitFcn->SetParLimits(10, mean2-0.005, mean2+0.005);   // peak
  fitFcn->SetParameter(11, width2);   // peak
  fitFcn->SetParLimits(11, width2-0.005, width2+0.005);   // peak
  fitFcn->SetLineWidth(1);   // peak
  histo->Fit("fitFcn","EV","",low,high);

  // improve the picture:
  TF1 *backFcn = new TF1(Form("backFcn_%i", try), background,low,high,6);
  backFcn->SetLineColor(4);
  backFcn->SetLineWidth(1);
  TF1 *signalFcn = new TF1(Form("signalFcn_%i", try), bwPeak,low,high,3);
  TF1 *signalFcn2 = new TF1(Form("signalFcn2_%i", try), bwPeak2,low,high,3);
  // signalFcn->SetLineColor(2);
  // signalFcn->SetLineWidth(5);
  
  Double_t par[12];

  // writes the fit results into the par array
   fitFcn->GetParameters(par);
   Double_t xsq = fitFcn->GetChisquare();
   Double_t ndf = fitFcn->GetNDF();
   backFcn->SetParameters(&par[0]);
    backFcn->SetLineStyle(2);
 backFcn->SetLineColor(2);
   backFcn->SetLineWidth(1);
  
   backFcn->Draw("same");

   signalFcn->SetParameters(&par[6]);
    signalFcn->SetLineStyle(2);
 signalFcn->SetLineColor(4);
   signalFcn->SetLineWidth(1);
  
   signalFcn->Draw("same");


  signalFcn2->SetParameters(&par[9]);
    signalFcn2->SetLineStyle(2);
 signalFcn2->SetLineColor(4);
   signalFcn2->SetLineWidth(1);
  
   signalFcn2->Draw("same");
   Double_t Intg = signalFcn->Integral(par[7]-factor*par[8],par[7]+factor*par[8]);
 Double_t Intg2 = signalFcn2->Integral(par[10]-factor*par[11],par[10]+factor*par[11]);
   Double_t Intb = backFcn->Integral(par[7]-factor*par[8],par[7]+factor*par[8]);
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
   TLatex *sum=new TLatex(startx, starty,Form("Mean2:%5.4f",par[10]));
   TLatex *sum1=new TLatex(startx, starty1,Form("#Gamma2: %5.4f",par[11]));
   TLatex *sum10=new TLatex(startx, starty10,Form("Yield: %i",yield));
    TLatex *sum2=new TLatex(startx, starty2,Form("Mean:%5.4f",par[7]));
   TLatex *sum3=new TLatex(startx, starty3,Form("#Gamma:%5.4f",par[8]));
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

