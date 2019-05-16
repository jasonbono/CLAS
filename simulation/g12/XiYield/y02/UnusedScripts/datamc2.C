/*

??????????????????????? wont use

JB September 13

Input:
1)  .root 
2)  .a1c.root

Output:
1)  datamccomp2.ps
2)  fitcomp.gif

Considerations:
1) What does this do?
2)What is the diffrence between datamc2.C and datamc.C?

*/


void compdatamc2(Double_t eg_min, Double_t eg_max, Int_t bins){
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
  sprintf(psfile,"./results/datamccomp2.ps");
  TPostScript *ps = new TPostScript(psfile, 111);
  TCanvas *c2=new TCanvas("c2", "", 20,20,600,800);
  Double_t egstep=(eg_max-eg_min)/bins;
  gStyle->SetOptStat(0);
  c2->Divide(2,5);
  c2->cd(1);
  TH1F *hkp1labpeak[11], *hkp2labpeak[11], *hkp1labmc[11], *hkp2labmc[11];
  TH1F *hkp1labside[11], *hkp2labside[11];
  TH1F *hpkp1peak[11], *hpkp2peak[11], *hpkp1mc[11], *hpkp2mc[11];
  TH1F *hpkp1side[11], *hpkp2side[11];
  TH1F *hcaslabpeak[11],  *hcaslabmc[11];
  TH1F *hcaslabside[11];
  TH1F *hmkkpeak[11],  *hmkkmc[11];
  TH1F *hmkkside[11];

  TH1F *hcask1side[11], *hcask2side[11];
  TH1F *hcask1peak[11], *hcask2peak[11],*hcasdata[11], *hcasmc[11];
  TH1F *hcask1mc[11], *hcask2mc[11];
  TH1F *hkp1labtotal, *hkp2labtotal,*hkp12labtotal, *hcask2total, *hcask12total, *hcask1total;
  TH1F *hpkp1total, *hpkp2total, *hpkp12total,  *hcaslabtotal, *hmkktotal;
  TH1F *hpkp1totalmc, *hpkp2totalmc, *hpkp12totalmc, *hcaslabtotalmc, *hmkktotalmc;
  TH1F *hkp1labtotalmc, *hkp2labtotalmc,*hkp12labtotalmc, *hcask12totalmc,*hcask2totalmc, *hcask1totalmc;
  //angle data
  hkp1labtotal=new TH1F("hkp1labtotal",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 11,0.75,1);
  hkp2labtotal=new TH1F("hkp2labtotal",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 11,0.6,1);
  hkp12labtotal=new TH1F("hkp12labtotal",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 11,0.6,1);
  hcaslabtotal=new TH1F("hcaslabtotal",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 11,-1,-0.85);
  //momentum data
  hpkp1total=new TH1F("hpkp1total",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 25, 0,2.5);
  hpkp2total=new TH1F("hpkp2total",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 25, 0,2.5);
  hpkp12total=new TH1F("hpkp12total",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 25, 0,2.5);

  //mass data
  hcask1total=new TH1F("hcask1total",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max),35,1.7,2.4);
  hcask2total=new TH1F("hcask2total",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 35,1.7,2.4);
  hcask12total=new TH1F("hcask12total",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 35,1.7,2.4);
  hmkktotal=new TH1F("hmkktotal",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 30,0.98,1.58);

  //angel mc
  hkp1labtotalmc=new TH1F("hkp1labtotalmc",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 11,0.75,1);
  hkp2labtotalmc=new TH1F("hkp2labtotalmc",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 11,0.6,1);
  hkp12labtotalmc=new TH1F("hkp12labtotalmc",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 11,0.6,1);
  hcaslabtotalmc=new TH1F("hcaslabtotalmc",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 11,-1,-0.85);

  //mass mc
  hcask1totalmc=new TH1F("hcask1totalmc",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max),35,1.7,2.4);
  hcask2totalmc=new TH1F("hcask2totalmc",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 35,1.7,2.4);
  hcask12totalmc=new TH1F("hcask12totalmc",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 35,1.7,2.4);
  hmkktotalmc=new TH1F("hmkktotalmc",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 30, 0.98, 1.58);

  //momentum mc
  hpkp1totalmc=new TH1F("hpkp1totalmc",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 25, 0,2.5);
  hpkp2totalmc=new TH1F("hpkp2totalmc",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 25, 0,2.5);
  hpkp12totalmc=new TH1F("hpkp12totalmc",Form("E_{#gamma}:%3.2f to %3.2f",eg_min, eg_max), 25, 0,2.5);
 
  Int_t datayield[11], mcyield[11],databg[11]; 
  Double_t dataratio[11],  mcratio[11], scale[11], peakentry[11], mcentry[11]; ;
  Double_t sidescale[11], pscale[11];
  Double_t datamean[11],databeam[11], datasigma[11], mcmean[11], mcsigma[11];
  Double_t elow, ehigh, emean;
  Int_t i;
   for(i=0;i<bins;i++){
     elow=eg_min+i*egstep;
     ehigh=eg_min+(i+1)*egstep;
    emean=(elow+ehigh)/2;
    databeam[i]=emean;
    //momentum
    hpkp1peak[i]=new TH1F(Form("hpkp1peak%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 25, 0,2.5);
    hpkp1peak[i]->GetXaxis()->SetTitle("P_{K^{+}_{fast}}");
    hpkp1peak[i]->SetLineColor(2);
    hpkp1side[i]=new TH1F(Form("hpkp1side%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 25, 0,2.5);
    hpkp2peak[i]=new TH1F(Form("hpkp2peak%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 25, 0,2.5);
    hpkp2peak[i]->GetXaxis()->SetTitle("P_{K^{+}_{slow}}");
    hpkp2peak[i]->SetLineColor(2);
    hpkp2side[i]=new TH1F(Form("hpkp2side%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 25, 0,2.5);
    hpkp1mc[i]=new TH1F(Form("hpkp1mc%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 25, 0,2.5);
    hpkp1mc[i]->SetLineColor(4);
     hpkp2mc[i]=new TH1F(Form("hpkp2mc%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 25, 0,2.5);
    hpkp2mc[i]->SetLineColor(4);
    //K+ angles
    hkp1labpeak[i]=new TH1F(Form("hkp1labpeak%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 11,0.75,1);
    hkp1labpeak[i]->GetXaxis()->SetTitle("Cos(#theta_K^{+}_{fast})");
    hkp1labpeak[i]->SetLineColor(2);
    hkp1labside[i]=new TH1F(Form("hkp1labside%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 11,0.75,1);
    hkp2labpeak[i]=new TH1F(Form("hkp2labpeak%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 11,0.6,1);
    hkp2labpeak[i]->GetXaxis()->SetTitle("Cos(#theta_K^{+}_{slow})");
    hkp2labpeak[i]->SetLineColor(2);
    hkp2labside[i]=new TH1F(Form("hkp2labside%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 11,0.6,1);
    hkp1labmc[i]=new TH1F(Form("hkp1labmc%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 11,0.75,1);
    hkp1labmc[i]->SetLineColor(4);
     hkp2labmc[i]=new TH1F(Form("hkp2labmc%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 11,0.6,1);
    hkp2labmc[i]->SetLineColor(4);

    //Xi- angles
    hcaslabpeak[i]=new TH1F(Form("hcaslabpeak%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 11,-1,-0.85);
    hcaslabpeak[i]->GetXaxis()->SetTitle("Cos(#theta_#Xi^{-})");
    hcaslabpeak[i]->SetLineColor(2);
    hcaslabside[i]=new TH1F(Form("hcaslabside%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 11,-1,-0.85);
    hcaslabmc[i]=new TH1F(Form("hcaslabmc%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 11,-1,-0.85);
    hcaslabmc[i]->SetLineColor(4);



    //data mass spectra
    hcask1peak[i]=new TH1F(Form("hcask1peak%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 35, 1.7,2.4);
    hcask1peak[i]->GetXaxis()->SetTitle("M(#Xi^{-}K^{+}_{fast})");
    hcask1peak[i]->SetLineColor(2);
    hcask2peak[i]=new TH1F(Form("hcask2peak%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 35, 1.7,2.4);
    hcask2peak[i]->GetXaxis()->SetTitle("M(#Xi^{-}K^{+}_{slow})");
    hcask2peak[i]->SetLineColor(2);
    hcask1side[i]=new TH1F(Form("hcask1side%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 35, 1.7,2.4);
    hcask2side[i]=new TH1F(Form("hcask2side%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 35, 1.7,2.4);
    //data M(KK)
    hmkkpeak[i]=new TH1F(Form("hmkkpeak%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 30, 0.98,1.58);
    hmkkpeak[i]->GetXaxis()->SetTitle("M(K^{+}K^{+})");
    hmkkpeak[i]->SetLineColor(2);
    hmkkside[i]=new TH1F(Form("hmkkside%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 30, 0.98,1.58);
    hmkkside[i]->SetLineColor(4);

    //MM(KK) data
    hcasdata[i]=new TH1F(Form("hcasdata%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 150, 1.2,1.8);
    hcasdata[i]->GetXaxis()->SetTitle("MM(K^{+}K^{+})");
    hcasdata[i]->SetLineColor(2);

    //mc (KXi) mass spectra
    hcask1mc[i]=new TH1F(Form("hcask1mc%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 35, 1.7,2.4);
    hcask1mc[i]->GetXaxis()->SetTitle("M(#Xi^{-}K^{+}_{fast})");
    hcask1mc[i]->SetLineColor(4);
    hcask2mc[i]=new TH1F(Form("hcask2mc%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 35, 1.7,2.4);
    hcask2mc[i]->GetXaxis()->SetTitle("M(#Xi^{-}K^{+}_{slow})");
    hcask2mc[i]->SetLineColor(4);
    //mc M(KK)
    hmkkmc[i]=new TH1F(Form("hmkkmc%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 30, 0.98,1.58);
    hmkkmc[i]->GetXaxis()->SetTitle("M(K^{+}K^{+})");
    hmkkmc[i]->SetLineColor(4);


    //mc MM(KK)
    hcasmc[i]=new TH1F(Form("hcasmc%d",i),Form("E_{#gamma}:%3.2f to %3.2f",elow, ehigh), 150, 1.2,1.8);
    hcasmc[i]->GetXaxis()->SetTitle("MM(K^{+}K^{+})");
    hcasmc[i]->SetLineColor(2);
   ps->NewPage();

    c2->cd(1);
    xxx->Draw(Form("mmkpkp>>hcasdata%d",i), Form("beam<%f&&beam>%f",ehigh, elow));
   datamean[i]=1.32;
   datasigma[i]=0.006;
   mcmean[i]=1.32;
   mcsigma[i]=0.006;
   datayield[i]=0, mcyield[i]=0, mcratio[i]=0;
   datayield[i]=fitGAUS(hcasdata[i], i*11+1, 1.2,1.4, 1,1,1,datamean[i],datasigma[i],3,dataratio[i]);
   if(dataratio[i]) {databg[i]=datayield[i]/dataratio[i];}
   else {databg[i]=0;}
   c2->Update();
   c2->cd(2);
   mc->Draw(Form("mmkpkp>>hcasmc%d",i), Form("beam<%f&&beam>%f",ehigh, elow));
   mcyield[i]=fitGAUS(hcasmc[i], i*11+2, 1.2,1.4, 0,0,0,mcmean[i],mcsigma[i],3,mcratio[i]);
   c2->Update();

   //K+ angles
   c2->cd(3);
   xxx->Draw(Form("kp1labtheta>>hkp1labpeak%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, datamean[i], datasigma[i]));
   xxx->Draw(Form("kp1labtheta>>hkp1labside%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<6*%f&&abs(mmkpkp-%f)>3*%f",ehigh, elow, datamean[i], datasigma[i], datamean[i], datasigma[i]));
   sidescale[i]=(datayield[i]/dataratio[i])/(hkp1labside[i]->GetEntries());
   hkp1labside[i]->Scale(sidescale[i]);
   hkp1labpeak[i]->Add(hkp1labside[i],-1);
   mc->Draw(Form("kp1labtheta>>hkp1labmc%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, mcmean[i], mcsigma[i]));
    peakentry[i]=hkp1labpeak[i]->GetEntries();
    mcentry[i]=hkp1labmc[i]->GetEntries();
    scale[i]=peakentry[i]/mcentry[i];
    hkp1labmc[i]->Draw();
    c2->Update();
    hkp1labmc[i]->Scale(scale[i]);
    hkp1labpeak[i]->Draw("E");
    hkp1labmc[i]->Draw("same");
    cout<<"fitresults "<<datamean[i]<<" "<<datasigma[i]<<" "<<endl;
   c2->Update();


   c2->cd(4);
   xxx->Draw(Form("kp2labtheta>>hkp2labpeak%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, datamean[i], datasigma[i]));
   xxx->Draw(Form("kp2labtheta>>hkp2labside%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<6*%f&&abs(mmkpkp-%f)>3*%f",ehigh, elow, datamean[i], datasigma[i], datamean[i], datasigma[i]));
   hkp2labside[i]->Scale(sidescale[i]);
   hkp2labpeak[i]->Add(hkp2labside[i],-1);
   mc->Draw(Form("kp2labtheta>>hkp2labmc%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, mcmean[i], mcsigma[i]));
   hkp2labmc[i]->Draw();
   c2->Update();
   hkp2labmc[i]->Scale(scale[i]);
   hkp2labpeak[i]->Draw("E");
   hkp2labmc[i]->Draw("same");
   c2->Update();
   c2->cd(5);
   xxx->Draw(Form("-Xlabtheta>>hcaslabpeak%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, datamean[i], datasigma[i]));
   xxx->Draw(Form("-Xlabtheta>>hcaslabside%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<6*%f&&abs(mmkpkp-%f)>3*%f",ehigh, elow, datamean[i], datasigma[i], datamean[i], datasigma[i]));
   hcaslabside[i]->Scale(sidescale[i]);
   hcaslabpeak[i]->Add(hcaslabside[i],-1);
   mc->Draw(Form("-Xlabtheta>>hcaslabmc%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, mcmean[i], mcsigma[i]));
   hcaslabmc[i]->Draw();
   c2->Update();
   hcaslabmc[i]->Scale(scale[i]);
   hcaslabpeak[i]->Draw("E");
   hcaslabmc[i]->Draw("same");
   c2->Update();

   //momentum
   c2->cd(6);
   xxx->Draw(Form("pkp1>>hpkp1peak%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, datamean[i], datasigma[i]));
   xxx->Draw(Form("pkp1>>hpkp1side%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<6*%f&&abs(mmkpkp-%f)>3*%f",ehigh, elow, datamean[i], datasigma[i], datamean[i], datasigma[i]));
   //hpkp1side[i]->Scale(sidescale[i]);
   //hpkp1peak[i]->Add(hpkp1side[i],-1);
   mc->Draw(Form("pkp1>>hpkp1mc%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, mcmean[i], mcsigma[i]));
   hpkp1mc[i]->Draw();
   pscale[i]=(hpkp1peak[i]->GetEntries())/(hpkp1mc[i]->GetEntries());
   c2->Update();
   hpkp1mc[i]->Scale(pscale[i]);
   hpkp1peak[i]->Draw("E");
   hpkp1mc[i]->Draw("same");
   c2->Update();
  c2->cd(7);
   xxx->Draw(Form("pkp2>>hpkp2peak%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, datamean[i], datasigma[i]));
   xxx->Draw(Form("pkp2>>hpkp2side%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<6*%f&&abs(mmkpkp-%f)>3*%f",ehigh, elow, datamean[i], datasigma[i], datamean[i], datasigma[i]));
   //hpkp2side[i]->Scale(sidescale[i]);
   //hpkp2peak[i]->Add(hpkp2side[i],-1);
   mc->Draw(Form("pkp2>>hpkp2mc%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, mcmean[i], mcsigma[i]));
   hpkp2mc[i]->Draw();
   c2->Update();
   hpkp2mc[i]->Scale(pscale[i]);
   hpkp2peak[i]->Draw("E");
   hpkp2mc[i]->Draw("same");
   c2->Update();



   c2->cd(8);
   xxx->Draw(Form("mcaskp1>>hcask1peak%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, datamean[i], datasigma[i]));
   xxx->Draw(Form("mcaskp1>>hcask1side%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<6*%f&&abs(mmkpkp-%f)>3*%f",ehigh, elow, datamean[i], datasigma[i], datamean[i], datasigma[i]));
   hcask1side[i]->Scale(sidescale[i]);
   hcask1peak[i]->Add(hcask1side[i],-1);
   mc->Draw(Form("mcaskp1>>hcask1mc%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, mcmean[i], mcsigma[i]));
   hcask1mc[i]->Draw();
   c2->Update();
   hcask1mc[i]->Scale(scale[i]);
   hcask1peak[i]->Draw("E");
   hcask1mc[i]->Draw("same");
   c2->Update();
   c2->cd(9);
   xxx->Draw(Form("mcaskp2>>hcask2peak%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, datamean[i], datasigma[i]));
   xxx->Draw(Form("mcaskp2>>hcask2side%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<6*%f&&abs(mmkpkp-%f)>3*%f",ehigh, elow, datamean[i], datasigma[i], datamean[i], datasigma[i]));
   hcask2side[i]->Scale(sidescale[i]);
   hcask2peak[i]->Add(hcask2side[i],-1);
   mc->Draw(Form("mcaskp2>>hcask2mc%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, mcmean[i], mcsigma[i]));
   hcask2mc[i]->Draw();
   c2->Update();
   hcask2mc[i]->Scale(scale[i]);
   hcask2peak[i]->Draw("E");
   hcask2mc[i]->Draw("same");
   c2->Update();
   c2->cd(10);
   xxx->Draw(Form("mkpkp>>hmkkpeak%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, datamean[i], datasigma[i]));
   xxx->Draw(Form("mkpkp>>hmkkside%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<6*%f&&abs(mmkpkp-%f)>3*%f",ehigh, elow, datamean[i], datasigma[i], datamean[i], datasigma[i]));
   hmkkside[i]->Scale(sidescale[i]);
   hmkkpeak[i]->Add(hmkkside[i],-1);
   mc->Draw(Form("mkpkp>>hmkkmc%d",i), Form("beam<%f&&beam>%f&&abs(mmkpkp-%f)<3*%f",ehigh, elow, mcmean[i], mcsigma[i]));
   hmkkmc[i]->Draw();
   c2->Update();
   hmkkmc[i]->Scale(scale[i]);
   hmkkpeak[i]->Draw("E");
   hmkkmc[i]->Draw("same");
   c2->Update();
   }
   ps->NewPage();
   c2->Clear();
   c2->Divide(3,4);
   for(i=0;i<bins;i++){
     //angle
     hkp1labtotal->Add(hkp1labpeak[i]);
     hkp2labtotal->Add(hkp2labpeak[i]);
     hkp12labtotal->Add(hkp1labpeak[i]);
     hkp12labtotal->Add(hkp2labpeak[i]);
     hcaslabtotal->Add(hcaslabpeak[i]);
     //momentum
     hpkp1total->Add(hpkp1peak[i]);
     hpkp2total->Add(hpkp2peak[i]);
     hpkp12total->Add(hpkp1peak[i]);
     hpkp12total->Add(hpkp2peak[i]);
     //mass
     hcask1total->Add(hcask1peak[i]);
     hcask2total->Add(hcask2peak[i]);
     hcask12total->Add(hcask1peak[i]);
     hcask12total->Add(hcask2peak[i]);
     hmkktotal->Add(hmkkpeak[i]);

     //angle
     hkp1labtotalmc->Add(hkp1labmc[i]);
     hkp2labtotalmc->Add(hkp2labmc[i]);
     hkp12labtotalmc->Add(hkp1labmc[i]);
     hkp12labtotalmc->Add(hkp2labmc[i]);
     hcaslabtotalmc->Add(hcaslabmc[i]);
     //momentum
     hpkp1totalmc->Add(hpkp1mc[i]);
     hpkp2totalmc->Add(hpkp2mc[i]);
     hpkp12totalmc->Add(hpkp1mc[i]);
     hpkp12totalmc->Add(hpkp2mc[i]);
     //mass
     hcask1totalmc->Add(hcask1mc[i]);
     hcask2totalmc->Add(hcask2mc[i]);
     hcask12totalmc->Add(hcask1mc[i]);
     hcask12totalmc->Add(hcask2mc[i]);
     hmkktotalmc->Add(hmkkmc[i]);
   }
   //data angle
   hkp1labtotal->GetXaxis()->SetTitle("Cos(#theta^{*}_{K^{+}_{fast}})");
   hkp1labtotal->SetLineColor(2);
   hkp2labtotal->GetXaxis()->SetTitle("Cos(#theta^{*}_{K^{+}_{slow}})");
   hkp2labtotal->SetLineColor(2);
   hkp12labtotal->GetXaxis()->SetTitle("Cos(#theta^{*}_{K^{+}_{1,2}})");
   hkp12labtotal->SetLineColor(2);
   hcaslabtotal->GetXaxis()->SetTitle("Cos(#theta^{*}_{#Xi^{-}})");
   hcaslabtotal->SetLineColor(2);
  //data momentum
   hpkp1total->GetXaxis()->SetTitle("P_{K^{+}_{fast}}");
   hpkp1total->SetLineColor(2);
   hpkp2total->GetXaxis()->SetTitle("P_{K^{+}_{slow}}");
   hpkp2total->SetLineColor(2);
   hpkp12total->GetXaxis()->SetTitle("P_{K^{+}_{1,2}}");
   hpkp12total->SetLineColor(2);

   //data mass
   hcask1total->GetXaxis()->SetTitle("M(#Xi^{-}K^{+}_{fast})");
   hcask1total->SetLineColor(2);
   hcask2total->GetXaxis()->SetTitle("M(#Xi^{-}K^{+}_{fast})");
   hcask2total->SetLineColor(2);
   hcask12total->GetXaxis()->SetTitle("M(#Xi^{-}K^{+}_{1,2})");
   hcask12total->SetLineColor(2);
   hmkktotal->GetXaxis()->SetTitle("M(K^{+}K^{+})");
   hmkktotal->SetLineColor(2);
   //mc angle 
   hkp1labtotalmc->GetXaxis()->SetTitle("Cos(#theta_K^{+}_{fast})");
   hkp1labtotalmc->SetLineColor(4);
   hkp2labtotalmc->GetXaxis()->SetTitle("Cos(#theta_K^{+}_{slow})");
   hkp2labtotalmc->SetLineColor(4);
   hkp12labtotalmc->SetLineColor(4);
   hcaslabtotalmc->SetLineColor(4);
   //mc momentum
   hpkp1totalmc->SetLineColor(4);
   hpkp2totalmc->SetLineColor(4);
   hpkp12totalmc->SetLineColor(4);

   //mc mass
   hcask1totalmc->GetXaxis()->SetTitle("M(#Xi^{-}K^{+}_{fast})");
   hcask1totalmc->SetLineColor(4);
   hcask2totalmc->GetXaxis()->SetTitle("M(#Xi^{-}K^{+}_{fast})");
   hcask2totalmc->SetLineColor(4);
   hcask12totalmc->SetLineColor(4);
   hmkktotalmc->SetLineColor(4);
   c2->cd(1);
   hkp1labtotal->Draw("E");
   hkp1labtotalmc->Draw("SAME");
   c2->Update();
   c2->cd(2);
   hkp2labtotal->Draw("E");
   hkp2labtotalmc->Draw("SAME");
   c2->Update();
   c2->cd(3);
   hkp12labtotal->Draw("E");
   hkp12labtotalmc->Draw("SAME");
   c2->Update();
   c2->cd(4);
   hcaslabtotal->Draw("E");
   hcaslabtotalmc->Draw("SAME");
   c2->Update();
   c2->cd(5);
   hpkp1total->Draw("E");
   hpkp1totalmc->Draw("SAME");
   c2->Update();
   c2->cd(6);
   hpkp2total->Draw("E");
   hpkp2totalmc->Draw("SAME");
   c2->Update();
   c2->cd(7);
   hpkp12total->Draw("E");
   hpkp12totalmc->Draw("SAME");
   c2->Update();

   //momentum
   c2->cd(8);
   hcask1total->Draw("E");
   hcask1totalmc->Draw("SAME");
   c2->Update();
   c2->cd(9);
   hcask2total->Draw("E");
   hcask2totalmc->Draw("SAME");
  
   c2->Update();
   c2->cd(10);
   hcask12total->Draw("E");
   hcask12totalmc->Draw("SAME");
  
   c2->Update();
   c2->cd(11);
   hmkktotal->Draw("E");
   hmkktotalmc->Draw("SAME");
  
   c2->Update();
   ps->NewPage();
   c2->Clear();
   c2->Divide(1,2);
    TGraph *grdatamean=new TGraph(bins, databeam, datamean);
   TGraph *grdatasigma=new TGraph(bins, databeam, datasigma);
    TGraph *grmcmean=new TGraph(bins, databeam, mcmean);
   TGraph *grmcsigma=new TGraph(bins, databeam, mcsigma);
   grdatamean->SetMarkerStyle(2);
   grdatamean->SetMarkerSize(1);
   grdatamean->SetMarkerColor(30);
   grmcmean->SetMarkerStyle(8);
   grmcmean->SetMarkerSize(1);
   grmcmean->SetMarkerColor(4);

   //sigma
   grdatasigma->SetMarkerStyle(2);
   grdatasigma->SetMarkerSize(1);
   grdatasigma->SetMarkerColor(30);
   grmcsigma->SetMarkerStyle(8);
   grmcsigma->SetMarkerSize(1);
   grmcsigma->SetMarkerColor(4);
   c2->cd(1);
  TMultiGraph *mgm=new TMultiGraph();
   mgm->Add(grdatamean);
   mgm->Add(grmcmean);
   TLegend *leg=new TLegend(0.7,0.8,0.9,0.9);
   leg->AddEntry(grdatamean, "data", "p");
   leg->AddEntry(grmcmean, "simulation", "p");
   mgm->SetTitle("Mean(#Xi^{-}) : E_{#gamma} (GeV)");
   mgm->Draw("AP");
   leg->Draw();
     c2->cd(2);
  TMultiGraph *mgs=new TMultiGraph();
   mgs->Add(grdatasigma);
   mgs->Add(grmcsigma);
   TLegend *legs=new TLegend(0.7,0.8,0.9,0.9);
   legs->AddEntry(grdatasigma, "data", "p");
   legs->AddEntry(grmcsigma, "simulation", "p");
   mgs->SetTitle("#sigma(#Xi^{-}) : E_{#gamma} (GeV)");
   mgs->Draw("AP");
   legs->Draw();
   c2->Update();
  
  ps->Close();
  c2->Print("./results/fitcomp.gif");
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
Double_t  fitGAUS(TH1F *histo, Int_t try, Double_t low, Double_t high, Double_t term0, Double_t term1,Double_t term2, Double_t &mean, Double_t &width, Double_t factor, Double_t &ratio)
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
   ratio = Intg/Intb;
   mean=par[4];
   width=par[5];
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

