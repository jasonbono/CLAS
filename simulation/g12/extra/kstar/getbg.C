void getbg(Double_t eg_min, Double_t eg_max, Double_t egstep){
  TFile *f = new TFile("sigmamc.root");
  sigmamc->Draw(">>yieldlist","abs(scv-stv)<1&&abs(mppim-1.1159)<0.0048&&abs(sctkp-sclkp/(betakp*29.99)-scv)<1&&abs(mm2kpppi-0.0166)<0.0246&&nkm<1&&npip<1&&np<2&&npim<2&&nkp<2");  
  TEventList *list=(TEventList *)gDirectory->Get("yieldlist");
  sigmamc->SetEventList(list);
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  //TNtuple *sigmamc=(TNtuple *)f->Get("sigmamc");
  //Load fit2BW.C;
  ofstream getbgdat;
  char getbgout[30], psfile[30];
   sprintf(getbgout,"getbg_%5.4f_%5.4f.newdat",eg_min, eg_max);
  sprintf(psfile,"getbg_%5.4f_%5.4f.ps",eg_min, eg_max);
  TPostScript *ps = new TPostScript(psfile, 111);
  getbgdat.open(getbgout, ios::out);
  TCanvas *c2=new TCanvas("c2", "", 20,20,600,800);
  Int_t egbin=(eg_max-eg_min)/egstep;
  Int_t pads=egbin/4+1;
  cout<<pads<<" "<<egbin<<endl;
  Double_t elow, ehigh,emean;
  Double_t tlow, thigh,tmean;
  Double_t tstep=0.25;
  const int n=100;
  TH1F *h[n][20];
  Double_t bg0[30][10];
  Double_t bg1[30][10];
  Double_t bg2[30][10];
  Double_t bg3[30][10];
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
  for( Int_t i=1;i<=egbin+1;i++){
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
       if(thigh<=0){
	 h[i][j]=new TH1F(Form("h%d_%d",i,j),Form("E_{#gamma}:%5.4f to %5.4f, Cos*(#theta_{K^{*+}}):%3.2f to %3.2f",elow, ehigh, tlow,thigh),40,0.6,1.5);}
       else {
	 h[i][j]=new TH1F(Form("h%d_%d",i,j),Form("E_{#gamma}:%5.4f to %5.4f, Cos*(#theta_{K^{*+}}):%3.2f to %3.2f",elow, ehigh, tlow,thigh),40,0.6,1.5);
       }
       
       //h[i]->SetMaximum(1.8);
       //h[i]->SetMinimum(1.2);
       //h[i]->SetBins(300);
       //h1->GetXaxis()->SetTitleSize(0.04);
       //h1->GetXaxis()->SetTitle("MM(K^{+} K^{+})/(GeV/c^{2})");
       //h1->GetYaxis()->SetTitleSize(0.04);
       //h1->GetYaxis()->SetTitle("Events/(2MeV/c^{2})");
       
       //sigmamc->Draw(Form("mmkpkp>>h%d_%d",i,j), Form("abs(scv-stv)<1&&beam<%f&&beam>%f&&tpkp1<%f&&tpkp1>%f&&abs(vz+10)<21",ehigh, elow, thigh, tlow));
       //sigmamc->Draw(Form("conmkppi0>>h%d_%d",i,j), Form("abs(scv-stv)<1&&abs(mppim-1.1159)<0.0048&&abs(sctkp-sclkp/(betakp*29.99)-scv)<1&&abs(mm2kpppi-0.0166)<0.0246&&nkm<1&&npip<1&&np<2&&npim<2&&nkp<2&&ngamma<3&&beam<%f&&beam>%f&&(-lamcmtheta)<%f&&(-lamcmtheta)>%f",ehigh, elow, thigh, tlow));
       sigmamc->Draw(Form("conmkppi0>>h%d_%d",i,j), Form("beam<%f&&beam>%f&&(-lamcmtheta)<%f&&(-lamcmtheta)>%f",ehigh, elow, thigh, tlow), "E");
       bg0[i][j]=1;
       bg1[i][j]=1;
       bg2[i][j]=1;
       bg3[i][j]=1;
       fitBG(h[i][j],i*10+j-1,0.63,1.2,bg0[i][j],bg1[i][j],bg2[i][j],bg3[i][j]);
       c2->Update();
     } 
     getbgdat<<emean<<" ";
     for(j=0;j<10;j++){getbgdat<<bg0[i][j]<<" "<<bg1[i][j]<<" "<<bg2[i][j]<<" "<<bg3[i][j]<<" ";}
     
     getbgdat<<endl;
     c2->Update();
     }
 getbgdat.close();
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

Double_t fitBGFunction(Double_t *x, Double_t *par) {
  return background(x,par);
}

Double_t fitFunctionBW(Double_t *x, Double_t *par) {
  return background(x,par) + bwPeak(x,&par[4]);
}

Double_t fitFunctionBW2(Double_t *x, Double_t *par) {
  return background(x,par) + bwPeak(x,&par[6])+ bwPeak2(x,&par[9]);
}





void  fitBG(TH1F *histo, Int_t try, Double_t low, Double_t high, Double_t &term0, Double_t &term1,Double_t &term2, Double_t &term3)
{
  //TText *sum[100];
  // create a TF1 with the range from tl to th and 9 parameters
  TF1 *fitFcn = new TF1("fitFcn",fitBGFunction, low, high, 4);

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

  histo->Fit("fitFcn","EV","",low,high);
  histo->Draw("E");
  // improve the picture:
  TF1 *backFcn = new TF1(Form("backFcn_%i", try), background,low,high,4);
  backFcn->SetLineColor(4);
  backFcn->SetLineWidth(1);
  
  Double_t par[4];

  // writes the fit results into the par array
   fitFcn->GetParameters(par);
   term0=par[0];
   term1=par[1];
   term2=par[2];
   term3=par[3];

   backFcn->SetParameters(par);
   backFcn->SetLineStyle(2);
   backFcn->SetLineColor(2);
   backFcn->SetLineWidth(1);
   
   backFcn->Draw("same");
   
}




