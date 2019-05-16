// sim events only go up to 3.84 gev real data goes up to 4 gev
// cs[11] was the cross section of the reaction from leis 2007 paper titled below
// Cascade production in the reactions gamma p ---> K+ K+ (X) and gamma p ---> K+ K+ pi- (X)
// want to go one bin extra on the low side and 2 bins extra on the high side
// this should give 11+3=14 bins:  need to always display 1 extra on the high side to see it.

void LOOPnormanglezbyCS(){

 TFile *f1 = TFile::Open("~/clas/rootfiles/helicity.root");
 TTree *realt = (TTree*)f1->Get("mytree");
 TFile *f2 = TFile::Open("~/clas/rootfiles/helicitySIM.root");
 TTree *simt = (TTree*)f2->Get("mytree");

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

 TCut beam0="abs(beam-2.79)<0.05";
 TCut beam1="abs(beam-2.89)<0.05";
 TCut beam2="abs(beam-2.99)<0.05";
 TCut beam3="abs(beam-3.09)<0.05";
 TCut beam4="abs(beam-3.19)<0.05";
 TCut beam5="abs(beam-3.29)<0.05";
 TCut beam6="abs(beam-3.39)<0.05";
 TCut beam7="abs(beam-3.49)<0.05";
 TCut beam8="abs(beam-3.59)<0.05";
 TCut beam9="abs(beam-3.69)<0.05";
 TCut beam10="abs(beam-3.79)<0.05";
 
 //lb=limit beam... this is needed because i only have cross sections for 2.74 gev and higher. this effectively cuts off the one bin lower 
     TCut rb="abs(beam-3.29)<0.55";

     Float_t beambin=14;
     Float_t beamlow=2.64;
     Float_t beamhigh=3.94;
     
     Float_t zbin=10;
     Float_t zlow=-1;
     Float_t zhigh=1;


TH1F *realbeam[11];
TH1F *simbeam[13];
TH1F *realhist[13];
TH1F *simhist[13];
for( Int_t i=0;i<12;i++){
realbeam[i]=new TH1F(Form("rb%d",i),"",beambin,beamlow,beamhigh);
simbeam[i]=new TH1F(Form("sb%d",i),"",beambin,beamlow,beamhigh);
realhist[i]=new TH1F(Form("r%d",i),"",zbin,zlow,zhigh);
simhist[i]=new TH1F(Form("s%d",i),"",zbin,zlow,zhigh);
 }


// realt->Draw("beam>>rb0",mycut);
// simt->Draw("beam>>sb0",mycut);

//-----------DEFINE CROSS SECTION-------------

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


//-----------------show real beam, with full and restricted domain and the simulated beam before and after cross section corrections------
TH1F *TOTrealbeam=new TH1F("TOTrealbeam","",beambin,beamlow,beamhigh); 
TH1F *TOTrealbeam2=new TH1F("TOTrealbeam2","",beambin,beamlow,beamhigh); 
TH1F *TOTsimbeam=new TH1F("TOTsimbeam","",beambin,beamlow,beamhigh); 
TH1F *TOTsimbeam2=new TH1F("TOTsimbeam2","",beambin,beamlow,beamhigh); 
TCanvas *c0=new TCanvas("c0","",1200,800);
 c0->Divide(2,2);
   c0->cd(1);
   realt->Draw("beam>>TOTrealbeam",mycut);
   c0->cd(3);
    realt->Draw("beam>>TOTrealbeam2",mycut&&rb);
    c0->cd(2);
    simt->Draw("beam>>TOTsimbeam",mycut&&rb);
   
    c0->cd(4);


 
 

simt->Draw("beam>>sb0",mycut&&beam0&&rb);
simt->Draw("beam>>sb1",mycut&&beam1&&rb);
simt->Draw("beam>>sb2",mycut&&beam2&&rb);
simt->Draw("beam>>sb3",mycut&&beam3&&rb);
simt->Draw("beam>>sb4",mycut&&beam4&&rb);
simt->Draw("beam>>sb5",mycut&&beam5&&rb);
simt->Draw("beam>>sb6",mycut&&beam6&&rb);
simt->Draw("beam>>sb7",mycut&&beam7&&rb);
simt->Draw("beam>>sb8",mycut&&beam8&&rb);
simt->Draw("beam>>sb9",mycut&&beam9&&rb);
simt->Draw("beam>>sb10",mycut&&beam10&&rb);

// now here introduce NORMsb to preserve the original beam hist from simulation events
// this will be integrated over and normalized to the data.
TH1F *NORMsb0=(TH1F*)sb0->Clone();
TH1F *NORMsb1=(TH1F*)sb1->Clone();
TH1F *NORMsb2=(TH1F*)sb2->Clone();
TH1F *NORMsb3=(TH1F*)sb3->Clone();
TH1F *NORMsb4=(TH1F*)sb4->Clone();
TH1F *NORMsb5=(TH1F*)sb5->Clone();
TH1F *NORMsb6=(TH1F*)sb6->Clone();
TH1F *NORMsb7=(TH1F*)sb7->Clone();
TH1F *NORMsb8=(TH1F*)sb8->Clone();
TH1F *NORMsb9=(TH1F*)sb9->Clone();
TH1F *NORMsb10=(TH1F*)sb10->Clone();
TOTsimbeam2->Add(sb0);
TOTsimbeam2->Add(sb1);
TOTsimbeam2->Add(sb2);
TOTsimbeam2->Add(sb3);
TOTsimbeam2->Add(sb4);
TOTsimbeam2->Add(sb5);
TOTsimbeam2->Add(sb6);
TOTsimbeam2->Add(sb7);
TOTsimbeam2->Add(sb8);
TOTsimbeam2->Add(sb9);
TOTsimbeam2->Add(sb10);

// normalizing with factor0
Double_t factor0 = TOTrealbeam2->Integral("width") / TOTsimbeam->Integral("width");
NORMsb0->Scale(factor0);
NORMsb1->Scale(factor0);
NORMsb2->Scale(factor0);
NORMsb3->Scale(factor0);
NORMsb4->Scale(factor0);
NORMsb5->Scale(factor0);
NORMsb6->Scale(factor0);
NORMsb7->Scale(factor0);
NORMsb8->Scale(factor0);
NORMsb9->Scale(factor0);
NORMsb10->Scale(factor0);
//now save this to a vecotr for later plotting
 Float_t bBINsim[11];
bBINsim[0]=NORMsb0->GetEntries();
bBINsim[1]=NORMsb1->GetEntries();
bBINsim[2]=NORMsb2->GetEntries();
bBINsim[3]=NORMsb3->GetEntries();
bBINsim[4]=NORMsb0->GetEntries();
bBINsim[5]=NORMsb0->GetEntries();
bBINsim[6]=NORMsb0->GetEntries();
bBINsim[7]=NORMsb0->GetEntries();
bBINsim[8]=NORMsb0->GetEntries();
bBINsim[9]=NORMsb0->GetEntries();
bBINsim[10]=NORMsb0->GetEntries();

///--------NOW SCALE THE BEAM HISTOGRAM ACCORDING TO CROSS SECTION-------------------------
///------------------FIGGURE OUT A WAY TO INCREMENT THIS IN 2 LINES----------------------
sb0->Scale(cs[0]);
sb1->Scale(cs[1]);
sb2->Scale(cs[2]);
sb3->Scale(cs[3]);
sb4->Scale(cs[4]);
sb5->Scale(cs[5]);
sb6->Scale(cs[6]);
sb7->Scale(cs[7]);
sb8->Scale(cs[8]);
sb9->Scale(cs[9]);
sb10->Scale(cs[10]);
TOTsimbeam2->Add(sb0);
TOTsimbeam2->Add(sb1);
TOTsimbeam2->Add(sb2);
TOTsimbeam2->Add(sb3);
TOTsimbeam2->Add(sb4);
TOTsimbeam2->Add(sb5);
TOTsimbeam2->Add(sb6);
TOTsimbeam2->Add(sb7);
TOTsimbeam2->Add(sb8);
TOTsimbeam2->Add(sb9);
TOTsimbeam2->Add(sb10);
TOTsimbeam2->Draw();

//---------------now saving the CS corrected beam to a vector with normalization----------
// will plot bBINsimCS later
Double_t factor1 = TOTrealbeam2->Integral("width") / TOTsimbeam2->Integral("width");

TH1F *CSsb0=(TH1F*)sb0->Clone();
TH1F *CSsb1=(TH1F*)sb1->Clone();
TH1F *CSsb2=(TH1F*)sb2->Clone();
TH1F *CSsb3=(TH1F*)sb3->Clone();
TH1F *CSsb4=(TH1F*)sb4->Clone();
TH1F *CSsb5=(TH1F*)sb5->Clone();
TH1F *CSsb6=(TH1F*)sb6->Clone();
TH1F *CSsb7=(TH1F*)sb7->Clone();
TH1F *CSsb8=(TH1F*)sb8->Clone();
TH1F *CSsb9=(TH1F*)sb9->Clone();
TH1F *CSsb10=(TH1F*)sb10->Clone();
CSsb0->Scale(factor1);
CSsb1->Scale(factor1);
CSsb2->Scale(factor1);
CSsb3->Scale(factor1);
CSsb4->Scale(factor1);
CSsb5->Scale(factor1);
CSsb6->Scale(factor1);
CSsb7->Scale(factor1);
CSsb8->Scale(factor1);
CSsb9->Scale(factor1);
CSsb10->Scale(factor1);

 Float_t bBINsimCS[11];
 bBINsimCS[0]=CSsb0->GetEntries();
 bBINsimCS[1]=CSsb1->GetEntries();
 bBINsimCS[2]=CSsb2->GetEntries();
 bBINsimCS[3]=CSsb3->GetEntries(); 
 bBINsimCS[4]=CSsb4->GetEntries();
 bBINsimCS[5]=CSsb5->GetEntries();
 bBINsimCS[6]=CSsb6->GetEntries();
 bBINsimCS[7]=CSsb7->GetEntries();
 bBINsimCS[8]=CSsb8->GetEntries();
 bBINsimCS[9]=CSsb9->GetEntries();
 bBINsimCS[10]=CSsb10->GetEntries();

 //--------------------------- now make the beam plots---------------------------------------------
//--------------------------- fill vectors --------------------------------------------- 
TCanvas *cb=new TCanvas("cb","",1200,800);
 Float_t bEN[11];
 Float_t bBINreal[11];
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

 TGraph *gbsim = new TGraph (11,bEN,bBINsimCS);

gbsim->SetMarkerStyle(21);
gbsim->SetMarkerColor(1);
gbsim->Draw("AP"); 


 //----------------that gives the beam energy distribution-------------
   //------------now looking at cos(anglez) hists in beam bins--------------- 
TCanvas *c1=new TCanvas("c1","",1200,800);
 c1->Divide(4,3);
 c1->cd(1);
simt->Draw("cos(PIanglez)>>s0",mycut&&beam0&&rb);
 c1->cd(2);
simt->Draw("cos(PIanglez)>>s1",mycut&&beam1&&rb);
c1->cd(3);
simt->Draw("cos(PIanglez)>>s2",mycut&&beam2&&rb);
c1->cd(4);
simt->Draw("cos(PIanglez)>>s3",mycut&&beam3&&rb);
c1->cd(5);
simt->Draw("cos(PIanglez)>>s4",mycut&&beam4&&rb);
c1->cd(6);
simt->Draw("cos(PIanglez)>>s5",mycut&&beam5&&rb);
c1->cd(7);
simt->Draw("cos(PIanglez)>>s6",mycut&&beam6&&rb);
c1->cd(8);
simt->Draw("cos(PIanglez)>>s7",mycut&&beam7&&rb);
c1->cd(9);
simt->Draw("cos(PIanglez)>>s8",mycut&&beam8&&rb); 
c1->cd(10);
simt->Draw("cos(PIanglez)>>s9",mycut&&beam9&&rb);
c1->cd(11);
simt->Draw("cos(PIanglez)>>s10",mycut&&beam10&&rb); 

TH1F *SCALEs0=(TH1F*)s0->Clone();
TH1F *SCALEs1=(TH1F*)s1->Clone();
TH1F *SCALEs2=(TH1F*)s2->Clone();
TH1F *SCALEs3=(TH1F*)s3->Clone();
TH1F *SCALEs4=(TH1F*)s4->Clone();
TH1F *SCALEs5=(TH1F*)s5->Clone();
TH1F *SCALEs6=(TH1F*)s6->Clone();
TH1F *SCALEs7=(TH1F*)s7->Clone();
TH1F *SCALEs8=(TH1F*)s8->Clone();
TH1F *SCALEs9=(TH1F*)s9->Clone();
TH1F *SCALEs10=(TH1F*)s10->Clone();

SCALEs0->Scale(cs[0]);
SCALEs1->Scale(cs[1]);
SCALEs2->Scale(cs[2]);
SCALEs3->Scale(cs[3]);
SCALEs4->Scale(cs[4]);
SCALEs5->Scale(cs[5]);
SCALEs6->Scale(cs[6]);
SCALEs7->Scale(cs[7]);
SCALEs8->Scale(cs[8]);
SCALEs9->Scale(cs[9]);
SCALEs10->Scale(cs[10]);

 c1->cd(1);
 SCALEs0->Draw();
 c1->cd(2);
 SCALEs1->Draw();
 c1->cd(3);
 SCALEs2->Draw();
 c1->cd(4);
 SCALEs3->Draw();
 c1->cd(5);
 SCALEs4->Draw();
 c1->cd(6);
 SCALEs5->Draw();
 c1->cd(7);
 SCALEs6->Draw();
 c1->cd(8);
 SCALEs7->Draw();
 c1->cd(9);
 SCALEs8->Draw();
 c1->cd(10);
 SCALEs9->Draw();
 c1->cd(11);
 SCALEs10->Draw();


 //-------------now adding the cosZ hists for each energy bin----------------------
TCanvas *c2=new TCanvas("c2","",1200,800);
 c2->Divide(2,2);
 c2->cd(1);
 TH1F *realtotal=new TH1F("realtotal","",zbin,zlow,zhigh);
 TH1F *simoriginal=new TH1F("simoriginal","",zbin,zlow,zhigh);
 TH1F *simtotal=new TH1F("simtotal","",zbin,zlow,zhigh);
 realt->Draw("cos(PIanglez)>>realtotal",mycut&&rb);
 c2->cd(2);
 simt->Draw("cos(PIanglez)>>simoriginal",mycut&&rb);
 c2->cd(3);
 simtotal->Add(SCALEs0);
 simtotal->Add(SCALEs1);
 simtotal->Add(SCALEs2);
 simtotal->Add(SCALEs3);
 simtotal->Add(SCALEs4);
 simtotal->Add(SCALEs5);
 simtotal->Add(SCALEs6);
 simtotal->Add(SCALEs7);
 simtotal->Add(SCALEs8);
 simtotal->Add(SCALEs9);
 simtotal->Add(SCALEs10);
 //simtotal->Draw();
 //TH1F *simtotalnorm=(TH1F*)simtotal->Clone();
Double_t normfactor = realtotal->Integral("width") / simtotal->Integral("width");
simtotal->Scale(normfactor);
simtotal->Draw();
//c2->cd(3);
// TH1F *simoriginal=new TH1F("simoriginal","",zbin,zlow,zhigh);
// simt->Draw("cos(PIanglez)>>simoriginal",mycut&&rb);
//------------------------scale sim events--------------



}
