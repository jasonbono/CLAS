// sim events only go up to 3.84 gev real data goes up to 4 gev
// cs[11] was the cross section of the reaction from leis 2007 paper titled below
// Cascade production in the reactions gamma p ---> K+ K+ (X) and gamma p ---> K+ K+ pi- (X)
// want to go one bin extra on the low side and 2 bins extra on the high side
// this should give 11+3=14 bins:  need to always display 1 extra on the high side to see it.

void normbyfluxNcs(){

 TFile *f1 = TFile::Open("~/clas/rootfiles/helicity.root");
 TTree *realt = (TTree*)f1->Get("mytree");
 TFile *f2 = TFile::Open("~/clas/rootfiles/helicitySIM.root");
 TTree *simt = (TTree*)f2->Get("mytree");

 // create a new ROOT file for output
 TFile *outFile = new TFile("myrootfile.root", "RECREATE");


 TCut mycasB="abs(sqrt(mm2kpkp)-1.322)<0.03";
 TCut mylambdaB="abs(sqrt(mm2kpkppim)-1.1162)<0.03";
 TCut mycasmB="abs(mlampim-1.320)<0.03"; //cut narrower, shift wider
 TCut myksB="abs(mkp1pim-0.835)<0.165"; //cut shift and wider, shift wider
 TCut myks2B="abs(mkp2pim-0.758)<0.115";// shift and made wider, shift wider
 TCut myscB="abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.5"; //made narrower, wider
 TCut mysc2B="abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<0.5"; //made much narrower, wider
 TCut mystB="abs((scv-stv)-0.0)<0.5";// made much narrower, totaly changed-- fixed error
 TCut mytofB="abs(tofmasskp1-0.5)<0.15&&abs(tofmasskp2-0.5)<0.15";//made narrower, fixed
 TCut myvcutB="abs(vz+9.0)<21&&(vx^2+vy^2)<9";//??,fixed
 TCut mynewB=mycasmB&&myksB&&myks2B&&myscB&&mysc2B&&mystB&&mytofB&&myvcutB;
 TCut mycut=mynewB&&mycasB&&mylambdaB;


 TCut beam[11];
 for (int i = 0; i < 11; i++) {
   Float_t beamcutVal = 2.79 + .1*i;
   beam[i] = Form("abs(beam-%.2f)<0.05", beamcutVal);
 }


//-----------DEFINE CROSS SECTION, FLUX, AND BEAM ENERGY VECTOR-------------

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

  //now redfine cs as the crosssetion*flux
for( Int_t i=0;i<11;i++){
  cs[i]=cs[i]*flux[i];
 }
Float_t bEN[11];
Float_t ebEN[11];
for( Int_t i=0;i<11;i++){
bEN[i] = 2.79 + .1*i;
ebEN[i] = 0; 
} 

 //rb=restrict beam... this is needed because i only have cross sections for 2.74 gev and higher. this effectively cuts off the one bin lower 
     TCut rb="abs(beam-3.29)<0.55";

     Float_t beambin=14;
     Float_t beamlow=2.64;
     Float_t beamhigh=3.94;
     
     Float_t zbin=10;
     Float_t zlow=-1;
     Float_t zhigh=1;


TH1F *realbeam[11];
TH1F *simbeam[13];
for( Int_t i=0;i<11;i++){
realbeam[i]=new TH1F(Form("hrb%d",i),"",beambin,beamlow,beamhigh);
simbeam[i]=new TH1F(Form("hsb%d",i),"",beambin,beamlow,beamhigh);

 }

// obtain the normalisation factor, using rb0 and sb0 temporaraly
 realt->Draw("beam>>hrb0",mycut&&rb);
 simt->Draw("beam>>hsb0",mycut&&rb);
 Double_t factor0 = hrb0->Integral("width") / hsb0->Integral("width");
 cout << "the normalizstion factor to get from sim events to data is factor0= " ;
 cout << factor0 << endl;
 cout << "total events for real are ";
 cout << hrb0->GetEntries() << endl;
 cout << "total events for simulation are ";
 cout << hsb0->GetEntries() << endl;
 cout << "checking the normfactor should be valued at ";
 cout << (hrb0->GetEntries())/(hsb0->GetEntries()) << endl;

 
 
 // NOW FILL SIMULATED BEAM IN TO 11 SEPERATE BINS replacing hsb0 with what it should be
Float_t vsb[11];
 Float_t vrb[11];
Float_t evsb[11];
 Float_t evrb[11];

for( Int_t i=0;i<11;i++){
simt->Draw(Form("beam>>hsb%d",i),mycut&&rb&&beam[i]);
realt->Draw(Form("beam>>hrb%d",i),mycut&&rb&&beam[i]);
 }


//now fill hsb and hrb to vsb a vector with errors
 
for( Int_t i=0;i<11;i++){

 vrb[i]=realbeam[i]->GetEntries();
 evrb[i]=sqrt(realbeam[i]->GetEntries());
 vsb[i]=(simbeam[i]->GetEntries())*(factor0);
 evsb[i]=sqrt(simbeam[i]->GetEntries())*(factor0);

   
 cout << "vsb";
   cout << i;
 cout << "=";
 cout << vsb[i] ;
 cout << "+-";
 cout << evsb[i]<< endl;
 }
for( Int_t i=0;i<11;i++){
cout << "vrb";
   cout << i;
 cout << "=";
 cout << vrb[i];
 cout << "+-";
 cout << evrb[i]<< endl;
 }
//another check to make sure vectors are normalized
 Float_t sum0=0;
 Float_t sum1=0;
Float_t sum2=0;
 Float_t sum3=0;
for( Int_t i=0;i<11;i++){
  sum0=sum0+vsb[i];
 }
  cout << "sum0=";
  cout << sum0 << endl;
  


//now add cross section
  Float_t vsbCS[11];
Float_t evsbCS[11];
  for( Int_t i=0;i<11;i++){
    vsbCS[i]=(simbeam[i]->GetEntries())*cs[i];
sum1=sum1+vsbCS[i];
  }
  cout <<"the total 'number' of 'events' for CS corrected is ";
  cout << sum1 << endl;
for( Int_t i=0;i<11;i++){
  vsbCS[i]=vsbCS[i]*sum0/sum1;
  evsbCS[i]=sqrt(simbeam[i]->GetEntries())*cs[i]*sum0/sum1;
  sum2=sum2+vsbCS[i];
cout << "vsbCS";
   cout << i;
 cout << "=";
 cout << vsbCS[i];
 cout << "+-";
 cout << evsbCS[i]<< endl;
 }

cout <<"checking vsbCS is normalized shold get that sum2 is 1091: sum2=";
  cout << sum2 << endl;

  // last check, make sure the real events give the right total
for( Int_t i=0;i<11;i++){
  sum3=sum3+vrb[i];
  }
 cout << "final check for real vecs: total is...";
   cout << sum3 << endl;


   //ploting vrb, vsb, vsbCS with errors with bEN
   //gr = new TGraphErrors(n,x,y,ex,ey);
   gb0 = new TGraphErrors(11,bEN,vrb,ebEN,evrb);
  gb0->SetMarkerStyle(21);
  gb0->SetMarkerColor(1);   
 gb0->Draw("AP");

gb1 = new TGraphErrors(11,bEN,vsb,ebEN,evsb);
 gb1->SetMarkerStyle(22);
  gb1->SetMarkerColor(2);  
  gb1->Draw("P");

gb2 = new TGraphErrors(11,bEN,vsbCS,ebEN,evsbCS);
 gb2->SetMarkerStyle(24);
  gb2->SetMarkerColor(3);  
  gb2->Draw("P");

   /////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////ANGLEZ/////////////////////////////////////////////



// NOW FILL REAL AND SIMULATED cosPIanglez IN TO 11 SEPERATE BINS 


///*

TH1F *realz[11];
TH1F *simz[11];
TH1F *simzCS[11];
TH1F *simzNORM[11];

// for adding the beam bins
 TH1F *hsum_realz=new TH1F("hsum_realz","",zbin,zlow,zhigh);
 TH1F *hsum_simz=new TH1F("hsum_simz","",zbin,zlow,zhigh);
 TH1F *hsum_simzCS=new TH1F("hsum_simzCS","",zbin,zlow,zhigh);
 TH1F *hsum_simzNORM=new TH1F("hsum_simzNORM","",zbin,zlow,zhigh);

  //fill z angles in 11 energy bins and scale by normalisation AND cs seperatly and adding them
for( Int_t i=0;i<11;i++){
  realz[i]=new TH1F(Form("hrz%d",i),"",zbin,zlow,zhigh);  
  simz[i]=new TH1F(Form("hsz%d",i),"",zbin,zlow,zhigh);
  realt->Draw(Form("cos(PIanglez)>>hrz%d",i),mycut&&rb&&beam[i]);
  simt->Draw(Form("cos(PIanglez)>>hsz%d",i),mycut&&rb&&beam[i]);
  simzNORM[i]=(TH1F*)simz[i]->Clone();
  simzCS[i]=(TH1F*)simz[i]->Clone();
  //scale dem
  simzNORM[i]->Scale(factor0);
  simzCS[i]->Scale(cs[i]*(sum0/sum1));
  // add dem
  hsum_realz->Add(realz[i]);
  hsum_simz->Add(simz[i]);
  hsum_simzNORM->Add(simzNORM[i]);
  hsum_simzCS->Add(simzCS[i]);
} 
//*/
 outFile->Write();
 outFile->Close();










//---------------------------------------------------------------------------------------//









//now the check that all integrals are 1091 execpt for check[1] which is not normalized
//////////////// Float_t check[4];
///////////////// check[0]=hsum_realz->Integral();
////////////////check[1]=hsum_simz->Integral();
///////////////check[2]=hsum_simzNORM->Integral();
///////////////check[3]=hsum_simzCS->Integral();
///////////////for( Int_t k=0;k<4;k++){
///////////////  cout << check[k] << endl;
/////////////// } //bang

// now to break down into cuts on angle, and write to a vectors
// there are indeed only 10 bins for angle {-1, -.8, -.6, -.4, -.2, 0, .2, .4, .6, .8} 
//Float_t vrz[10];
//Float_t vsz[10];
//Float_t vszCS[10];
//Float_t evsz[10];
//Float_t evrz[10];
//Float_t evszCS[10];
 
//TH1F *realz_abins[10];
//TH1F *simz_abins[10];
//TH1F *simzCS_abins[10];
//TH1F *simzNORM_abins[10];
//TCut angle[10];

//the cut
//for (int j = 0; j < 10; j++) {
//   Float_t anglecutVal = -0.9 + .2*j;
//   beam[j] = Form("abs(cos(PIangleZ)-%.2f)<0.1", anglecutVal);

  //the angle bined hist forms
//  realz_abins[j]=new TH1F(Form("hrz_abins%d",j),"",zbin,zlow,zhigh);
//  simz_abins[j]=new TH1F(Form("hsz_abins%d",j),"",zbin,zlow,zhigh);
//  simzNORM_abins[j]=new TH1F(Form("hsz_abins%d",j),"",zbin,zlow,zhigh);
//  simzCS_abins[j]=new TH1F(Form("hsz_abins%d",j),"",zbin,zlow,zhigh);



}





// vrz[j]=realz[j]->GetEntries();
// evrz[j]=sqrt(realz[j]->GetEntries());
 
// vsz[j]=(simz[j]->GetEntries())*(factor0);
// evsz[j]=sqrt(simz[j]->GetEntries())*(factor0);
 
// vszCS[i]=(simbeam[i]->GetEntries())*cs[i]*(sum0/sum1);
 // evszCS[i]=sqrt(simbeam[i]->GetEntries())*cs[i]*(sum0/sum1);

 //}








