/*
JB September 13

Input:
1)  .root 
2)  .a1c.root

Output: 
1) datamccomp.ps 
2) mean.corrections.eps
*/
void compdatamccor(Double_t eg_min, Double_t eg_max, Int_t bins){
 TFile *fdata = new TFile("v37k_full_newbasic.root");
  TNtuple *xxx=(TNtuple *)fdata->Get("v37k");
  xxx->Draw(">>yieldlist","abs(scv-stv)<1&&abs(vz+10)<21&&abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<1&&abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<1");
  TEventList *list=(TEventList *)gDirectory->Get("yieldlist");
  xxx->SetEventList(list);

 TFile *fmc = new TFile("MC_v07_v37k.root");
  TNtuple *mc=(TNtuple *)fmc->Get("v37k");
  mc->Draw(">>yieldlist2","abs(scv-stv)<1&&abs(vz+10)<21&&abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<1&&abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<1");
  TEventList *list2=(TEventList *)gDirectory->Get("yieldlist2");
  mc->SetEventList(list2);

char psfile[512];
  sprintf(psfile,"./results/datamccomp.ps");
  TPostScript *ps = new TPostScript(psfile, 111);
  TCanvas *c2=new TCanvas("c2", "", 20,20,600,800);
  Double_t egstep=(eg_max-eg_min)/bins;
  gStyle->SetOptStat(0);
  c2->Divide(2,2);

  Double_t datamean[11],databeam[11],databeamerr[11],  datasigma[11], mcmean[11], mcsigma[11];
  Double_t datameanerr[11], datasigmaerr[11], mcmeanerr[11], mcsigmaerr[11];
  Double_t data1mean[11], data1sigma[11],data1meanerr[11], data1sigmaerr[11];
  Double_t data2mean[11], data2sigma[11],data2meanerr[11], data2sigmaerr[11];
  TH1F *hcasdata[11], *hcasdata1[11], *hcasdata2[11], *hcasmc[11];

  Double_t elow, ehigh, emean;
  Int_t i;
   for(i=0;i<bins;i++){
     elow=eg_min+i*egstep;
     ehigh=eg_min+(i+1)*egstep;
    emean=(elow+ehigh)/2;
    databeam[i]=emean;
    databeamerr[i]=egstep/2;
    //MM(KK) data, MM+ELOSS
    hcasdata[i]=new TH1F(Form("hcasdata%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 150, 1.2,1.8);
    hcasdata[i]->GetXaxis()->SetTitle("MM(K^{+}K^{+})");
    hcasdata[i]->SetLineColor(2);
    //MM(KK) data, MM+ELOSS+PCOR
    hcasdata1[i]=new TH1F(Form("hcasdata1%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 150, 1.2,1.8);
    hcasdata1[i]->GetXaxis()->SetTitle("MM(K^{+}K^{+})");
    hcasdata1[i]->SetLineColor(2);
    //MM(KK) data, PS+ELOSS+PCOR
    hcasdata2[i]=new TH1F(Form("hcasdata2%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 150, 1.2,1.8);
    hcasdata2[i]->GetXaxis()->SetTitle("MM(K^{+}K^{+})");
    hcasdata2[i]->SetLineColor(2);

 
    //mc MM(KK)
    hcasmc[i]=new TH1F(Form("hcasmc%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 150, 1.2,1.8);
    hcasmc[i]->GetXaxis()->SetTitle("MM(K^{+}K^{+})");
    hcasmc[i]->SetLineColor(2);
   ps->NewPage();
  datamean[i]=1.32;
   datasigma[i]=0.006;
  data1mean[i]=1.32;
   data1sigma[i]=0.006;
  data2mean[i]=1.32;
   data2sigma[i]=0.006;
   mcmean[i]=1.32;
   mcsigma[i]=0.006;

    c2->cd(1);
    //MM+ELOSS
    xxx->Draw(Form("mmkpkp0>>hcasdata%d",i), Form("beam<%f&&beam>%f",ehigh, elow));
    fitGAUS(hcasdata[i], i*11+1, 1.2,1.4, 1,1,1,datamean[i],datameanerr[i],datasigma[i],datasigmaerr[i],3);




   //MM+ELOSS+PCOR
   c2->cd(2);
    xxx->Draw(Form("mmkpkp>>hcasdata1%d",i), Form("beam<%f&&beam>%f",ehigh, elow));
    fitGAUS(hcasdata1[i], i*11+2, 1.2,1.4, 1,1,1,data1mean[i],data1meanerr[i],data1sigma[i],data1sigmaerr[i],3);
   c2->Update();
   //PS+ELOSS+PCOR
   c2->cd(3);
    xxx->Draw(Form("psmmkpkp>>hcasdata2%d",i), Form("beam<%f&&beam>%f",ehigh, elow));
   data2mean[i]=1.32;
   data2sigma[i]=0.006;
   mcmean[i]=1.32;
   mcsigma[i]=0.006;
   fitGAUS(hcasdata2[i], i*11+3, 1.2,1.4, 1,1,1,data2mean[i],data2meanerr[i],data2sigma[i],data2sigmaerr[i],3);
 

   c2->Update();
   //MC
   c2->cd(4);
   mc->Draw(Form("mmkpkp>>hcasmc%d",i), Form("beam<%f&&beam>%f",ehigh, elow));
   fitGAUS(hcasmc[i], i*11+4, 1.2,1.4, 0,0,0,mcmean[i],mcmeanerr[i],mcsigma[i],mcsigmaerr[i],3);
   c2->Update();

 
   }
   ps->NewPage();
   c2->Clear();
   c2->Divide(1,2);
   
    TGraphErrors *grdatamean=new TGraphErrors(bins, databeam, datamean, databeamerr, datameanerr);
   TGraphErrors *grdatasigma=new TGraphErrors(bins, databeam, datasigma, databeamerr, datasigmaerr);
    TGraphErrors *grdata1mean=new TGraphErrors(bins, databeam, data1mean, databeamerr, data1meanerr);
   TGraphErrors *grdata1sigma=new TGraphErrors(bins, databeam, data1sigma, databeamerr, data1sigmaerr);
    TGraphErrors *grdata2mean=new TGraphErrors(bins, databeam, data2mean, databeamerr, data2meanerr);
   TGraphErrors *grdata2sigma=new TGraphErrors(bins, databeam, data2sigma, databeamerr, data2sigmaerr);
    TGraphErrors *grmcmean=new TGraphErrors(bins, databeam, mcmean, databeamerr, mcmeanerr);
   TGraphErrors *grmcsigma=new TGraphErrors(bins, databeam, mcsigma, databeamerr, mcsigmaerr);
   grmcmean->SetMarkerStyle(8);
   grmcmean->SetMarkerSize(1);
   grmcmean->SetMarkerColor(4);
   grmcsigma->SetMarkerStyle(8);
   grmcsigma->SetMarkerSize(1);
   grmcsigma->SetMarkerColor(4);

   //data 
   grdatamean->SetMarkerStyle(22);
   grdatamean->SetMarkerSize(1);
   grdatamean->SetMarkerColor(30);
   grdatasigma->SetMarkerStyle(22);
   grdatasigma->SetMarkerSize(1);
   grdatasigma->SetMarkerColor(30);
   //data 1
   grdata1mean->SetMarkerStyle(25);
   grdata1mean->SetMarkerSize(1);
   grdata1mean->SetMarkerColor(2);
   grdata1sigma->SetMarkerStyle(25);
   grdata1sigma->SetMarkerSize(1);
   grdata1sigma->SetMarkerColor(2);
   //data 2
   grdata2mean->SetMarkerStyle(23);
   grdata2mean->SetMarkerSize(1);
   grdata2mean->SetMarkerColor(6);
   grdata2sigma->SetMarkerStyle(23);
   grdata2sigma->SetMarkerSize(1);
   grdata2sigma->SetMarkerColor(6);
   c2->cd(1);
  TMultiGraph *mgm=new TMultiGraph();
   mgm->Add(grdatamean);
   mgm->Add(grdata1mean);
   mgm->Add(grdata2mean);
   mgm->Add(grmcmean);
   TLegend *leg=new TLegend(0.7,0.8,0.9,0.9);
   leg->AddEntry(grdatamean, "ELOSS+TAGGER_{MM}", "p");
   leg->AddEntry(grdata1mean, "ELOSS+PCOR+TAGGER_{MM}", "p");
   leg->AddEntry(grdata2mean, "ELOSS+PCOR+TAGGER_{PS}", "p");
   leg->AddEntry(grmcmean, "simulation", "p");
   mgm->SetTitle("Mean(#Xi^{-}) : E_{#gamma} (GeV)");
   mgm->Draw("AP");
   leg->Draw();
     c2->cd(2);
  TMultiGraph *mgs=new TMultiGraph();
   mgs->Add(grdatasigma);
   mgs->Add(grdata1sigma);
   mgs->Add(grdata2sigma);
   mgs->Add(grmcsigma);
   TLegend *legs=new TLegend(0.7,0.8,0.9,0.9);
   legs->AddEntry(grdatasigma, "ELOSS+TAGGER_{MM}", "p");
   legs->AddEntry(grdata1sigma, "ELOSS+PCOR+TAGGER_{MM}", "p");
   legs->AddEntry(grdata2sigma, "ELOSS+PCOR+TAGGER_{PS}", "p");
   legs->AddEntry(grmcsigma, "simulation", "p");
   mgs->SetTitle("#sigma(#Xi^{-}) : E_{#gamma} (GeV)");
   mgs->Draw("AP");
   legs->Draw();
   c2->Update();
  
  ps->Close();
  c2->Print("./results/mean.corrections.eps");
}


Double_t background(Double_t *x, Double_t *par) {
  //return par[0] + par[1]*x[0] + par[2]*x[0]*x[0]+ par[3]*x[0]*x[0]*x[0];
  return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
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
void  fitGAUS(TH1F *histo, Int_t try, Double_t low, Double_t high, Double_t term0, Double_t term1,Double_t term2, Double_t &mean, Double_t &meanerr, Double_t &width,Double_t &widtherr, Double_t factor)
{
  //TText *sum[100];
  // create a TF1 with the range from tl to th and 6 parameters
  TF1 *fitFcn = new TF1("fitFcn",fitFunction, low, high, 6);

  // first try without starting values for the parameters
  // This defaults to 1 for each param.
  //histo->Fit("fitFcn", "E");

  // second try: set start values for some parameters

  fitFcn->SetParameter(0, term0); // pol c0
  if(term2!=0) {  fitFcn->SetParameter(1, term1); }  // pol c1
  else {fitFcn->FixParameter(1,0);}

  if(term2!=0) {fitFcn->SetParameter(2, term2); }// pol c2
  else {fitFcn->FixParameter(2,0);}
//fitFcn->SetParameter(3, height); // hight

  fitFcn->SetParameter(4, mean); // width
  fitFcn->SetParLimits(4,mean-width, mean+width); // width

fitFcn->SetParameter(5, width);   // peak
 
  fitFcn->SetParLimits(3, 0,10000);   // peak
  fitFcn->SetParLimits(5, 0.003, 2*width);   // peak
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
   //ratio = Intg/Intb;
   mean=par[4];
   meanerr=fitFcn->GetParError(4);
   width=par[5];
   widtherr=fitFcn->GetParError(5);
   Double_t GammaErr=fitFcn->GetParError(5);
   //yielderr=yield*GammaErr/par[5];
   
  
   
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
   //TLatex *sum1=new TLatex(startx, starty1,Form("S/B ratio: %6.2f",ratio));
   TLatex *sum0=new TLatex(startx, starty0,Form("Range: #pm %2.1f #sigma",factor));
   TLatex *sum2=new TLatex(startx, starty2,Form("Mean:%5.4f",par[4]));
   TLatex *sum3=new TLatex(startx, starty3,Form("#sigma:%5.4f",par[5]));
   sum->SetTextSize(0.05);
   sum->SetTextColor(2);
   sum->Draw("same");
   //sum1->SetTextSize(0.05);
   //sum1->SetTextColor(2);
   //sum1->Draw("same");
   sum0->SetTextSize(0.05);
   sum0->SetTextColor(2);
   sum0->Draw("same");
   sum2->SetTextSize(0.05);
   sum2->SetTextColor(4);
   sum2->Draw("same");
   sum3->SetTextSize(0.05);
   sum3->SetTextColor(4);
   sum3->Draw("same");
   //return yield;
}

