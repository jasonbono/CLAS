// after the editing on oct 3 the distributions seem to be off, and the normalization factors have changed. there is an error somewhere and need to find it.

// October 3: edited to include the angles off the x and y axis.



void norm_read_root_file(){


  //open root file  
TFile *f = new TFile("~/clas/rootfiles/norm_rootfile.root"); 


 
 Float_t bbin=11;
 Float_t blow=2.74;
 Float_t bhigh=3.84;
 Float_t zbin=10;
 Float_t zlow=-1;
 Float_t zhigh=1;

 

 // read beam histograms from file
 //for ReadBeamHists(f,hbr,hbs,hzr,hzs,hnr,hns); 
 TH1F *hbr[11];
 TH1F *hbs[11];
 TH1F *hbsCS[11];
 TH1F *hzr[11];
 TH1F *hzs[11];
 TH1F *hzsCS[11];
 TH1F *hnr[11];
 TH1F *hns[11];
 TH1F *hnsCS[11];

 TH1F *hxr[11];
 TH1F *hxs[11];
 TH1F *hxsCS[11];
 TH1F *hyr[11];
 TH1F *hys[11];
 TH1F *hysCS[11];
 

 ReadBeamHists(f,hbr,hbs,hbsCS,hzr,hzs,hzsCS,hnr,hns,hnsCS,hxr,hxs,hxsCS,hyr,hys,hysCS);
 
  
 // sum the histograms
   
 TH1F *hbrsum = new TH1F("hbrsum","hbr sum",bbin,blow,bhigh);
 TH1F *hbssum = new TH1F("hbssum","hbs sum",bbin,blow,bhigh);
 TH1F *hbssumNORM = new TH1F("hbssumNORM","hbsNORM sum",bbin,blow,bhigh);
 TH1F *hbssumCS = new TH1F("hbssumCS","hbsCS sum",bbin,blow,bhigh);

 TH1F *hzrsum = new TH1F("hzrsum","hzr sum",zbin,zlow,zhigh);
 TH1F *hzssum = new TH1F("hzssum","hzs sum",zbin,zlow,zhigh);
 TH1F *hzssumNORM = new TH1F("hzssumNORM","hzsNORM sum",zbin,zlow,zhigh);
 TH1F *hzssumCS = new TH1F("hzssumCS","hzsCS sum",zbin,zlow,zhigh);

 TH1F *hnrsum = new TH1F("hnrsum","hnr sum",zbin,zlow,zhigh);
 TH1F *hnssum = new TH1F("hnssum","hns sum",zbin,zlow,zhigh);
 TH1F *hnssumNORM = new TH1F("hnssumNORM","hnsNORM sum",zbin,zlow,zhigh);
 TH1F *hnssumCS = new TH1F("hnssumCS","hnsCS sum",zbin,zlow,zhigh);

 TH1F *hxrsum = new TH1F("hxrsum","hxr sum",zbin,zlow,zhigh);
 TH1F *hxssum = new TH1F("hxssum","hxs sum",zbin,zlow,zhigh);
 TH1F *hxssumNORM = new TH1F("hxssumNORM","hxsNORM sum",zbin,zlow,zhigh);
 TH1F *hxssumCS = new TH1F("hxssumCS","hxsCS sum",zbin,zlow,zhigh);

 TH1F *hyrsum = new TH1F("hyrsum","hyr sum",zbin,zlow,zhigh);
 TH1F *hyssum = new TH1F("hyssum","hys sum",zbin,zlow,zhigh);
 TH1F *hyssumNORM = new TH1F("hyssumNORM","hysNORM sum",zbin,zlow,zhigh);
 TH1F *hyssumCS = new TH1F("hyssumCS","hysCS sum",zbin,zlow,zhigh);






 SumBeamHists(hbr,hbs,hbsCS,hbrsum,hbssum,hbssumNORM,hbssumCS,hzr,hzs,hzsCS,hzrsum,hzssum,hzssumNORM,hzssumCS,hnr,hns,hnsCS,hnrsum,hnssum,hnssumNORM,hnssumCS,hxr,hxs,hxsCS,hxrsum,hxssum,hxssumNORM,hxssumCS,hyr,hys,hysCS,hyrsum,hyssum,hyssumNORM,hyssumCS); 


}



// preconditions: ROOT file f is opened and ready for reading, h is a TH1F histogram of size 11
// postconditions: Read the cos theta histograms from file and save them in h
void ReadBeamHists(TFile *f, TH1F * hbr[11],TH1F * hbs[11],TH1F * hbsCS[11], TH1F * hzr[11],TH1F * hzs[11],TH1F * hzsCS[11],TH1F * hnr[11],TH1F * hns[11],TH1F * hnsCS[11], TH1F * hxr[11],TH1F * hxs[11],TH1F * hxsCS[11],TH1F * hyr[11],TH1F * hys[11],TH1F * hysCS[11]) {
 
 // local variables
  TString name;

  // statements
  for (Int_t i = 0; i <= 10; i++) {
    // set up name for the histogram
    name = Form("b_real%d",i);
    hbr[i] = (TH1F*)f->Get(name.Data())->Clone();
    name = Form("b_sim%d",i);
    hbs[i] = (TH1F*)f->Get(name.Data())->Clone();
    hbsCS[i] = (TH1F*)f->Get(name.Data())->Clone();
    name = Form("z_real%d",i);
    hzr[i] = (TH1F*)f->Get(name.Data())->Clone();
    name = Form("z_sim%d",i);
    hzs[i] = (TH1F*)f->Get(name.Data())->Clone();
    hzsCS[i] = (TH1F*)f->Get(name.Data())->Clone();
    name = Form("n_real%d",i);
    hnr[i] = (TH1F*)f->Get(name.Data())->Clone();
    name = Form("n_sim%d",i);
    hns[i] = (TH1F*)f->Get(name.Data())->Clone();
    hnsCS[i] = (TH1F*)f->Get(name.Data())->Clone();

    name = Form("x_real%d",i);
    hxr[i] = (TH1F*)f->Get(name.Data())->Clone();
    name = Form("x_sim%d",i);
    hxs[i] = (TH1F*)f->Get(name.Data())->Clone();
    hxsCS[i] = (TH1F*)f->Get(name.Data())->Clone();
    name = Form("y_real%d",i);
    hyr[i] = (TH1F*)f->Get(name.Data())->Clone();
    name = Form("y_sim%d",i);
    hys[i] = (TH1F*)f->Get(name.Data())->Clone();
    hysCS[i] = (TH1F*)f->Get(name.Data())->Clone();


 }

  cout << "Finished reading histograms from file and cloning them: \n";

  return;
}


//preconditions: have all the binned beam histograms stored localy as hbr[i]
//postconditons: have summed the histrograms in hbrsum

void SumBeamHists(TH1F * hbr[11],TH1F * hbs[11],TH1F * hbsCS[11], TH1F * & hbrsum, TH1F * & hbssum,TH1F * & hbssumNORM,TH1F * & hbssumCS,TH1F * hzr[11],TH1F * hzs[11],TH1F * hzsCS[11], TH1F * & hzrsum, TH1F * & hzssum,TH1F * & hzssumNORM,TH1F * & hzssumCS,TH1F * hnr[11],TH1F * hns[11],TH1F * hnsCS[11], TH1F * & hnrsum, TH1F * & hnssum,TH1F * & hnssumNORM,TH1F * & hnssumCS,TH1F * hxr[11],TH1F * hxs[11],TH1F * hxsCS[11], TH1F * & hxrsum, TH1F * & hxssum,TH1F * & hxssumNORM,TH1F * & hxssumCS,TH1F * hyr[11],TH1F * hys[11],TH1F * hysCS[11], TH1F * & hyrsum, TH1F * & hyssum,TH1F * & hyssumNORM,TH1F * & hyssumCS){


  for (Int_t i = 0; i <= 10; i++) {
    hbrsum->Add(hbr[i]);
    hbssum->Add(hbs[i]);
    hzrsum->Add(hzr[i]);
    hzssum->Add(hzs[i]);
    hnrsum->Add(hnr[i]);
    hnssum->Add(hns[i]);

    hxrsum->Add(hxr[i]);
    hxssum->Add(hxs[i]);
    hyrsum->Add(hyr[i]);
    hyssum->Add(hys[i]);


  }

  // hbrsum->Draw();
  // hbssum->Draw();

 Float_t factor[10]; 
 Float_t nbRealEvents;
 Float_t nbSimEvents;
Float_t  nbSimEventsCS;

 Float_t nzRealEvents;
 Float_t nzSimEvents;
Float_t  nzSimEventsCS;

 Float_t nnRealEvents;
 Float_t nnSimEvents;
Float_t  nnSimEventsCS;


 Float_t nxRealEvents;
 Float_t nxSimEvents;
Float_t  nxSimEventsCS;

 Float_t nyRealEvents;
 Float_t nySimEvents;
Float_t  nySimEventsCS;

  
 nbRealEvents=hbrsum->Integral();
 nbSimEvents=hbssum->Integral();
 factor[0]= (nbRealEvents)/(nbSimEvents);
 cout << "finished summing beam histograms" <<endl;
 cout << "nbRealEvents: "<< nbRealEvents << "  nbSimEvents:" << nbSimEvents <<endl;
 cout << "factor[0]:" << factor[0] <<endl;

 nzRealEvents=hzrsum->Integral();
 nzSimEvents=hzssum->Integral();
 cout << "nzRealEvents: "<< nzRealEvents << "  nzSimEvents:" << nzSimEvents <<endl;

 nnRealEvents=hnrsum->Integral();
 nnSimEvents=hnssum->Integral();
 cout << "nnRealEvents: "<< nnRealEvents << "  nnSimEvents:" << nnSimEvents <<endl;

 nxRealEvents=hxrsum->Integral();
 nxSimEvents=hxssum->Integral();
 cout << "nxRealEvents: "<< nxRealEvents << "  nxSimEvents:" << nxSimEvents <<endl;

 nyRealEvents=hyrsum->Integral();
 nySimEvents=hyssum->Integral();
 cout << "nyRealEvents: "<< nyRealEvents << "  nySimEvents:" << nySimEvents <<endl;

 //now scale the sim events
TH1F *hbssumNORM=(TH1F*)hbssum->Clone();
TH1F *hzssumNORM=(TH1F*)hzssum->Clone();
TH1F *hnssumNORM=(TH1F*)hnssum->Clone();
TH1F *hxssumNORM=(TH1F*)hxssum->Clone();
TH1F *hyssumNORM=(TH1F*)hyssum->Clone();
 hbssumNORM->Scale(factor[0]);
 hzssumNORM->Scale(factor[0]);
 hnssumNORM->Scale(factor[0]);
 hxssumNORM->Scale(factor[0]);
 hyssumNORM->Scale(factor[0]);

 cout << "checking that the sim events are normalized: integral over hbssumNORM=" << hbssumNORM->Integral() <<endl;
 cout << " and int of hzssumNORM=" << hzssumNORM->Integral() << "and int of hnssumNORM=" << hzssumNORM->Integral() << endl;

///////////////////////////////now for the crosssecton correction///////////////////////////////

Float_t cs[11];
 cs[0]=2.201;
 cs[1]=3.226;
 cs[2]=5.885;
 cs[3]=6.870;
 cs[4]=6.172;
 cs[5]=8.114;
 cs[6]=8.067;
 cs[7]=7.413;
 cs[8]=8.037;
 cs[9]=8.516;
 cs[10]=11.057;

 Double_t flux[11];
  flux[0]=1.686573472327;
  flux[1]=1.605062572366;
  flux[2]=1.619865319963;
  flux[3]=1.404234476285;
  flux[4]=1.993007897069;
  flux[5]=1.529323614915;
  flux[6]=1.315989264057;
  flux[7]=1.452006834897;
  flux[8]=1.424185903507;
  flux[9]=1.401769518627;
  flux[10]=1.361787638923;

 Double_t csf[11];
  //now define csf as the cs*flux
   for( Int_t i=0;i<=10;i++){
     csf[i]=cs[i]*flux[i];

     hbsCS[i]->Scale(csf[i]);
     hbssumCS->Add(hbsCS[i]);
     
     hzsCS[i]->Scale(csf[i]);
     hzssumCS->Add(hzsCS[i]);
     
     hnsCS[i]->Scale(csf[i]);
     hnssumCS->Add(hnsCS[i]);

     hxsCS[i]->Scale(csf[i]);
     hxssumCS->Add(hxsCS[i]);

     hysCS[i]->Scale(csf[i]);
     hyssumCS->Add(hysCS[i]);


   }
   nbSimEventsCS=hbssumCS->Integral();
  factor[1]=(nbRealEvents)/(nbSimEventsCS);
 
 hbssumCS->Scale(factor[1]);
 hzssumCS->Scale(factor[1]);
 hnssumCS->Scale(factor[1]);
 hxssumCS->Scale(factor[1]);
 hyssumCS->Scale(factor[1]);


  cout << "hbssumCS normalized, the total integral is:" << hbssumCS->Integral() <<endl;
cout << "hzssumCS normalized, the total integral is:" << hzssumCS->Integral() <<endl;
cout << "hnssumCS normalized, the total integral is:" << hnssumCS->Integral() <<endl;


//--------------------------------------------------------------------------------------------
//---------------now read all of the histograms into vectors for ploting-------------------


 Float_t vbr[11]; 
 Float_t vbs[11];
 Float_t vbsNORM[11];
 Float_t vbsCS[11]; 

 Float_t vzr[10]; 
 Float_t vzs[10]; 
 Float_t vzsNORM[10];
 Float_t vzsCS[10]; 

 Float_t vnr[10]; 
 Float_t vns[10];
 Float_t vnsNORM[10]; 
 Float_t vnsCS[10]; 

 Float_t vxr[10]; 
 Float_t vxs[10]; 
 Float_t vxsNORM[10];
 Float_t vxsCS[10]; 

 Float_t vyr[10]; 
 Float_t vys[10];
 Float_t vysNORM[10]; 
 Float_t vysCS[10]; 


 Float_t evbr[11]; 
 Float_t evbsNORM[11];
 Float_t evbsCS[11]; 

 Float_t evzr[10]; 
 Float_t evzsNORM[10];
 Float_t evzsCS[10]; 

 Float_t evnr[10]; 
 Float_t evnsNORM[10]; 
 Float_t evnsCS[10]; 

 Float_t evxr[10]; 
 Float_t evxsNORM[10];
 Float_t evxsCS[10]; 

 Float_t evyr[10]; 
 Float_t evysNORM[10]; 
 Float_t evysCS[10]; 

 for (Int_t j = 0; j <= 10; j++) {  // NOTE: bin 0: underflow, bin: nBins + 1 is overflow
   // get the content of the bin from the histogram    
   vbr[j] = hbrsum->GetBinContent(j+1);
   vbs[j] = hbssum->GetBinContent(j+1);
   vbsNORM[j] = hbssumNORM->GetBinContent(j+1);
   vbsCS[j] = hbssumCS->GetBinContent(j+1);
   
   evbr[j] = sqrt(vbr[j]);
   evbsNORM[j] = sqrt(vbs[j])*(factor[0]);
   evbsCS[j] = sqrt(vbs[j])*(factor[1]);



 }

 for (Int_t k = 0; k <= 9; k++) {  // NOTE: bin 0: underflow, bin: nBins + 1 is overflow
   // get the content of the bin from the histogram    
   vzr[k] = hzrsum->GetBinContent(k+1);
   vzs[k] = hzssum->GetBinContent(k+1);
   vzsNORM[k] = hzssumNORM->GetBinContent(k+1);
   vzsCS[k] = hzssumCS->GetBinContent(k+1);

   vnr[k] = hnrsum->GetBinContent(k+1);
   vns[k] = hnssum->GetBinContent(k+1);
   vnsNORM[k] = hnssumNORM->GetBinContent(k+1);
   vnsCS[k] = hnssumCS->GetBinContent(k+1);



   vxr[k] = hxrsum->GetBinContent(k+1);
   vxs[k] = hxssum->GetBinContent(k+1);
   vxsNORM[k] = hxssumNORM->GetBinContent(k+1);
   vxsCS[k] = hxssumCS->GetBinContent(k+1);

   vyr[k] = hyrsum->GetBinContent(k+1);
   vys[k] = hyssum->GetBinContent(k+1);
   vysNORM[k] = hyssumNORM->GetBinContent(k+1);
   vysCS[k] = hyssumCS->GetBinContent(k+1);



   evzr[k] = sqrt(vzr[k]);
   evzsNORM[k] = sqrt(vzs[k])*(factor[0]);
   evzsCS[k] = sqrt(vzs[k])*(factor[1]);
    
   evnr[k] = sqrt(vnr[k]);
   evnsNORM[k] = sqrt(vns[k])*(factor[0]);
   evnsCS[k] = sqrt(vns[k])*(factor[1]);



   evxr[k] = sqrt(vxr[k]);
   evxsNORM[k] = sqrt(vxs[k])*(factor[0]);
   evxsCS[k] = sqrt(vxs[k])*(factor[1]);
    
   evyr[k] = sqrt(vyr[k]);
   evysNORM[k] = sqrt(vys[k])*(factor[0]);
   evysCS[k] = sqrt(vys[k])*(factor[1]);

 }



/////////////////////// now to plot the vectors///////////////////////////////////////////
Float_t bEN[11];
Float_t ebEN[11]; 
 bEN[0]=2.79;
 bEN[1]=2.89;
 bEN[2]=2.99;
 bEN[3]=3.09;
 bEN[4]=3.19;
 bEN[5]=3.29;
 bEN[6]=3.39;
 bEN[7]=3.49;
 bEN[8]=3.59;
 bEN[9]=3.69;
 bEN[10]=3.79;
 ebEN[0]=0;
 ebEN[1]=0;
 ebEN[2]=0;
 ebEN[3]=0;
 ebEN[4]=0;
 ebEN[5]=0;
 ebEN[6]=0;
 ebEN[7]=0;
 ebEN[8]=0;
 ebEN[9]=0;
 ebEN[10]=0;

Float_t cos[10];
Float_t ecos[10];
 cos[0]=-0.9;
 cos[1]=-0.7;
 cos[2]=-0.5;
 cos[3]=-0.3;
 cos[4]=-0.1;
 cos[5]=0.1;
 cos[6]=0.3;
 cos[7]=0.5;
 cos[8]=0.7;
 cos[9]=0.9;

 ecos[0]=-0;
 ecos[1]=-0;
 ecos[2]=-0;
 ecos[3]=-0;
 ecos[4]=-0;
 ecos[5]=0;
 ecos[6]=0;
 ecos[7]=0;
 ecos[8]=0;
 ecos[9]=0;

TCanvas *c0=new TCanvas("c0","",800,600);
  gb0 = new TGraphErrors(11,bEN,vbr,ebEN,evbr);
  gb0->SetMarkerStyle(21);
  gb0->SetMarkerColor(1);
  gb0->SetTitle("beam"); 
  gb0->Draw("AP");


  gb1 = new TGraphErrors(11,bEN,vbsNORM,ebEN,evbsNORM);
  gb1->SetMarkerStyle(22);
  gb1->SetMarkerColor(2);   
  gb1->Draw("P");

  gb2 = new TGraphErrors(11,bEN,vbsCS,ebEN,evbsCS);
  gb2->SetMarkerStyle(20);
  gb2->SetMarkerColor(3);   
  gb2->Draw("P");






TCanvas *c1=new TCanvas("c1","",800,600);
  gz0 = new TGraphErrors(10,cos,vzr,ecos,evzr);
  gz0->SetMarkerStyle(21);
  gz0->SetMarkerColor(1);  
  gz0->SetTitle("z angle"); 
  gz0->Draw("AP");


  gz1 = new TGraphErrors(10,cos,vzsNORM,ecos,evzsNORM);
  gz1->SetMarkerStyle(22);
  gz1->SetMarkerColor(2);   
  gz1->Draw("P");

  gz2 = new TGraphErrors(10,cos,vzsCS,ecos,evzsCS);
  gz2->SetMarkerStyle(20);
  gz2->SetMarkerColor(3);   
  gz2->Draw("P");




TCanvas *c2=new TCanvas("c2","",800,600);
  gn0 = new TGraphErrors(10,cos,vnr,ecos,evnr);
  gn0->SetMarkerStyle(21);
  gn0->SetMarkerColor(1);  
  gn0->SetTitle("n angle");  
  gn0->Draw("AP");


  gn1 = new TGraphErrors(10,cos,vnsNORM,ecos,evnsNORM);
  gn1->SetMarkerStyle(22);
  gn1->SetMarkerColor(2);   
  gn1->Draw("P");

  gn2 = new TGraphErrors(10,cos,vnsCS,ecos,evnsCS);
  gn2->SetMarkerStyle(20);
  gn2->SetMarkerColor(3);   
  gn2->Draw("P");



  //---------x and y
TCanvas *c3=new TCanvas("c3","",800,600);
  gx0 = new TGraphErrors(10,cos,vxr,ecos,evxr);
  gx0->SetMarkerStyle(21);
  gx0->SetMarkerColor(1);
  gx0->SetTitle("x angle");    
  gx0->Draw("AP");

  gx1 = new TGraphErrors(10,cos,vxsNORM,ecos,evxsNORM);
  gx1->SetMarkerStyle(22);
  gx1->SetMarkerColor(2);   
  gx1->Draw("P");

  gx2 = new TGraphErrors(10,cos,vxsCS,ecos,evxsCS);
  gx2->SetMarkerStyle(20);
  gx2->SetMarkerColor(3);   
  gx2->Draw("P");




TCanvas *c4=new TCanvas("c4","",800,600);
  gy0 = new TGraphErrors(10,cos,vyr,ecos,evyr);
  gy0->SetMarkerStyle(21);
  gy0->SetMarkerColor(1);  
  gy0->SetTitle("y angle");  
  gy0->Draw("AP");


  gy1 = new TGraphErrors(10,cos,vysNORM,ecos,evysNORM);
  gy1->SetMarkerStyle(22);
  gy1->SetMarkerColor(2);   
  gy1->Draw("P");

  gy2 = new TGraphErrors(10,cos,vysCS,ecos,evysCS);
  gy2->SetMarkerStyle(20);
  gy2->SetMarkerColor(3);   
  gy2->Draw("P");













}
















