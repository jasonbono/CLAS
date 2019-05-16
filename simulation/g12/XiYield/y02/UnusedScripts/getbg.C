/*
DONT NEED THIS SCRIPT FOR NOW, WILL NEED IF ABSOULTE CROSS SECTIONS ARE TO BE CALCULATED

*/
void getbg(){
 TFile *fdata = new TFile("new.root");
  TNtuple *new=(TNtuple *)fdata->Get("new");
 
 TFile *fmc = new TFile("yyy.root");
  TNtuple *yyy=(TNtuple *)fmc->Get("yyy");
  TH1F *bd=new TH1F("bd", "",16,3.3,4.9);
  TH1F *bm=new TH1F("bm", "",16,3.3,4.9);
  char psfile[30];
  sprintf(psfile,"normalized3pibg.ps");
  TPostScript *ps = new TPostScript(psfile, 111);
  TCanvas *c2=new TCanvas("c2", "", 20,20,600,800);
  c2->cd();
  new->Draw("psbeam>>bd", "abs(scv-stv)<1&&abs(sqrt(mm2kpkppim)-1.3145)<6*0.0060&&abs(sqrt(mm2kpkppim)-1.3145)>3*0.0060&&abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.8&&abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<1.5");
  //new->Draw("psbeam>>bd", "abs(scv-stv)<1&&abs(sqrt(mm2kpkppim)-1.3145)<6*0.0060&&abs(sqrt(mm2kpkppim)-1.3145)>3*0.0060");
  c2->Update();
  //yyy->Draw("beam>>bm", "abs(scv-stv)<1&&abs(sqrt(mm2kpkppim)-1.3145)<200*0.0060&&abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.8&&abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<1.5");
yyy->Draw("beam>>bm", "abs(scv-stv)<1&&abs(sqrt(mm2kpkppim)-1.3145)<6*0.0060&&abs(sqrt(mm2kpkppim)-1.3145)>3*0.0060");
  c2->Update();
  Double_t databins[16], mcbins[16], scale[16];
  Int_t i=0;
  Int_t j=0;
  Int_t bin=0;
  Double_t eg_max=4.9, eg_min=3.3, egstep=0.1,elow, ehigh;
  TH1F *hc[16], *hctotal, *hdc;
  TH1F *hx[16], *hxtotal, *hdx, *hdx0;
  hctotal=new TH1F(Form("hc%d", i),Form("E_{#gamma}:%3.2f to %3.2f",3.3,4.9),50,1.25,1.45);
   hxtotal=new TH1F(Form("hx%d", i),Form("E_{#gamma}:%3.2f to %3.2f",3.3, 4.9),50,1.45,1.95);
   hdc=new TH1F("hdc", "",50,1.25,1.45);
   hdx=new TH1F("hdx", "", 50,1.45,1.95);
   hdx0=new TH1F("hdx0", "", 50,1.45,1.95);
   new->Draw("sqrt(mm2kpkppim)>>hdc",  "abs(scv-stv)<1&&abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.8&&abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<1.5&&beam>3.3");
   c2->Update();
   //getchar();
   new->Draw("mfixcaspim>>hdx",  "abs(scv-stv)<1&&abs(sqrt(mm2kpkppim)-1.3145)<3*0.0060&&abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.8&&abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<1.5&&beam>3.3");
   c2->Update();
   //getchar();
  for(i=0;i<16;i++){
     elow=egstep*i+eg_min;
    ehigh=elow+egstep;
    hc[i]=new TH1F(Form("hc%d", i),Form("E_{#gamma}:%5.4f to %5.4f",elow, ehigh),50,1.25,1.45);
    hx[i]=new TH1F(Form("hx%d", i),Form("E_{#gamma}:%5.4f to %5.4f",elow, ehigh),50,1.45,1.95);
    yyy->Draw(Form("sqrt(mm2kpkppim)>>hc%d",i), Form("abs(scv-stv)<1&&beam<%f&&beam>%f",ehigh, elow));
      c2->Update();
      //getchar();
    yyy->Draw(Form("mcaspim>>hx%d",i), Form("abs(scv-stv)<1&&abs(sqrt(mm2kpkppim)-1.3145)<3*0.0060&&beam<%f&&beam>%f",ehigh, elow));
      c2->Update();
     //getchar();

    databins[i]=0;
    bin=i+1;
    databins[i]=bd->GetBinContent(bin);
    mcbins[i]=bm->GetBinContent(bin);
    
    if(mcbins[i]) {
      scale[i]=databins[i]/mcbins[i];
    }
    else {
      scale[i]=0;
    }
    hx[i]->Scale(scale[i]);
    hc[i]->Scale(scale[i]);
    
    hxtotal->Add(hx[i],1);
    hctotal->Add(hc[i],1);
    cout<<databins[i]<<" "<<mcbins[i]<<" "<<scale[i]<<endl;

    
  }
  //ps-NewPage();
  hdx->SetLineColor(2);
  hdx->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
  hdx->GetXaxis()->SetTitleSize(0.05);
  hdx->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
  hdx->GetYaxis()->SetTitleSize(0.05);
  hxtotal->SetFillColor(4);
  hxtotal->SetFillStyle(3004);
  hdx->Draw();
  hxtotal->Draw("same");
  c2->Update();
  //c2->Print("casx.eps");
  //getchar();
  //ps->NewPage();
  hdc->SetLineColor(2);
  hdc->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
  hdc->GetXaxis()->SetTitleSize(0.05);
  hdc->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
  hdc->GetYaxis()->SetTitleSize(0.05);
  hctotal->SetFillColor(4);
  hctotal->SetFillStyle(3004);
  hdc->Draw();
  hctotal->Draw("same");
  c2->Update();
  //c2->Print("cas0.eps");
  //getchar();
  hdx0->Add(hdx,1);
  hdx0->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
  hdx0->GetXaxis()->SetTitleSize(0.05);
  hdx0->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
  hdx0->GetYaxis()->SetTitleSize(0.05);
  hdx0->Add(hxtotal,-1);
  hdx0->Draw("E");
  c2->Print("casx.sub.gif");
  c2->Print("casx.sub.eps");
  ps->Close();
 
}
