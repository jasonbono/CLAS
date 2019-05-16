// sim events only go up to 3.84 gev real data goes up to 4 gev
// cs[11] was the cross section of the reaction from leis 2007 paper titled below
// Cascade production in the reactions gamma p ---> K+ K+ (X) and gamma p ---> K+ K+ pi- (X)
// want to go one bin extra on the low side and 2 bins extra on the high side
// this should give 11+3=14 bins:  need to always display 1 extra on the high side to see it.

void normanglezbyCS(){

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
 realbeam[0]=new TH1F("rb0","",beambin,beamlow,beamhigh);
 realbeam[1]=new TH1F("rb1","",beambin,beamlow,beamhigh);
 realbeam[2]=new TH1F("rb2","",beambin,beamlow,beamhigh);
 realbeam[3]=new TH1F("rb3","",beambin,beamlow,beamhigh);
 realbeam[4]=new TH1F("rb4","",beambin,beamlow,beamhigh);
 realbeam[5]=new TH1F("rb5","",beambin,beamlow,beamhigh);
 realbeam[6]=new TH1F("rb6","",beambin,beamlow,beamhigh);
 realbeam[7]=new TH1F("rb7","",beambin,beamlow,beamhigh);
 realbeam[8]=new TH1F("rb8","",beambin,beamlow,beamhigh);
 realbeam[9]=new TH1F("rb9","",beambin,beamlow,beamhigh);
 realbeam[10]=new TH1F("rb10","",beambin,beamlow,beamhigh);

 TH1F *simbeam[13];
 simbeam[0]=new TH1F("sb0","",beambin,beamlow,beamhigh);
 simbeam[1]=new TH1F("sb1","",beambin,beamlow,beamhigh);
 simbeam[2]=new TH1F("sb2","",beambin,beamlow,beamhigh);
 simbeam[3]=new TH1F("sb3","",beambin,beamlow,beamhigh);
 simbeam[4]=new TH1F("sb4","",beambin,beamlow,beamhigh);
 simbeam[5]=new TH1F("sb5","",beambin,beamlow,beamhigh);
 simbeam[6]=new TH1F("sb6","",beambin,beamlow,beamhigh);
 simbeam[7]=new TH1F("sb7","",beambin,beamlow,beamhigh);
 simbeam[8]=new TH1F("sb8","",beambin,beamlow,beamhigh);
 simbeam[9]=new TH1F("sb9","",beambin,beamlow,beamhigh);
 simbeam[10]=new TH1F("sb10","",beambin,beamlow,beamhigh);


TH1F *realhist[13];
realhist[0]=new TH1F("r0","",zbin,zlow,zhigh);
realhist[1]=new TH1F("r1","",zbin,zlow,zhigh);
realhist[2]=new TH1F("r2","",zbin,zlow,zhigh);
realhist[3]=new TH1F("r3","",zbin,zlow,zhigh);
realhist[4]=new TH1F("r4","",zbin,zlow,zhigh);
realhist[5]=new TH1F("r5","",zbin,zlow,zhigh);
realhist[6]=new TH1F("r6","",zbin,zlow,zhigh);
realhist[7]=new TH1F("r7","",zbin,zlow,zhigh);
realhist[8]=new TH1F("r8","",zbin,zlow,zhigh);
realhist[9]=new TH1F("r9","",zbin,zlow,zhigh);
realhist[10]=new TH1F("r10","",zbin,zlow,zhigh);


TH1F *simhist[13];
simhist[0]=new TH1F("s0","",zbin,zlow,zhigh);
simhist[1]=new TH1F("s1","",zbin,zlow,zhigh);
simhist[2]=new TH1F("s2","",zbin,zlow,zhigh);
simhist[3]=new TH1F("s3","",zbin,zlow,zhigh);
simhist[4]=new TH1F("s4","",zbin,zlow,zhigh);
simhist[5]=new TH1F("s5","",zbin,zlow,zhigh);
simhist[6]=new TH1F("s6","",zbin,zlow,zhigh);
simhist[7]=new TH1F("s7","",zbin,zlow,zhigh);
simhist[8]=new TH1F("s8","",zbin,zlow,zhigh);
simhist[9]=new TH1F("s9","",zbin,zlow,zhigh);
simhist[10]=new TH1F("s10","",zbin,zlow,zhigh);

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


 // first a test... for some reason whenever i scale my histogram it re draws it automaticly
 //so have to use clone
/*
TCanvas *test0c=new TCanvas("test0c","",900,700);
simt->Draw("cos(PIanglez)>>s0",mycut&&beam0);

TH1F *SCALEs0=(TH1F*)s0->Clone();
//SCALEs0->SetName("hist");

TCanvas *test1c=new TCanvas("test1c","",900,700);
SCALEs0->Scale(cs[0]);
SCALEs0->Draw();
*/

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

   //------------looking at  cos(anglez) hists in beam bins--------------- 
TCanvas *c1=new TCanvas("c1","",4000,800);
 c1->Divide(11,2);
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

 c1->cd(12);
 SCALEs0->Draw();
 c1->cd(13);
 SCALEs1->Draw();
 c1->cd(14);
 SCALEs2->Draw();
 c1->cd(15);
 SCALEs3->Draw();
 c1->cd(16);
 SCALEs4->Draw();
 c1->cd(17);
 SCALEs5->Draw();
 c1->cd(18);
 SCALEs6->Draw();
 c1->cd(19);
 SCALEs7->Draw();
 c1->cd(20);
 SCALEs8->Draw();
 c1->cd(21);
 SCALEs9->Draw();
 c1->cd(22);
 SCALEs10->Draw();

 //-------------add the hists
TCanvas *c2=new TCanvas("c2","",1200,800);
 c2->Divide(2,2);
 c2->cd(1);
 TH1F *realtotal=new TH1F("realtotal","",zbin,zlow,zhigh);
 realt->Draw("cos(PIanglez)>>realtotal",mycut&&rb);

TH1F *simtotal=new TH1F("simtotal","",zbin,zlow,zhigh);
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
 c2->cd(2);
 simtotal->Draw();
TH1F *simtotalnorm=(TH1F*)simtotal->Clone();
Double_t normfactor = realtotal->Integral("width") / simtotal->Integral("width");
simtotalnorm->Scale(normfactor);
simtotalnorm->Draw();
 c2->cd(3);
   TH1F *simoriginal=new TH1F("simoriginal","",zbin,zlow,zhigh);
   simt->Draw("cos(PIanglez)>>simoriginal",mycut&&rb);
//------------------------scale sim events--------------

/*

//TCanvas *c1=new TCanvas("c1","",1200,820);
// c1->Divide(5,2);
// c1->cd(1);
 realt->Draw("beam>>b0",mycut&&beam1); 
 //c1->cd(2);
 realt->Draw("beam>>b1",mycut&&beam2); 
 //c1->cd(3);
 realt->Draw("beam>>b2",mycut&&beam3); 
 //c1->cd(4);
 realt->Draw("beam>>b3",mycut&&beam4); 
 //c1->cd(5);
 realt->Draw("beam>>b4",mycut&&beam5); 
 //c1->cd(6);
realt->Draw("cos(PIanglez)>>r0",mycut&&beam1);
//c1->cd(7);
realt->Draw("cos(PIanglez)>>r1",mycut&&beam2);
//c1->cd(8);
realt->Draw("cos(PIanglez)>>r2",mycut&&beam3);
//c1->cd(9);
realt->Draw("cos(PIanglez)>>r3",mycut&&beam4);
//c1->cd(10);
realt->Draw("cos(PIanglez)>>r4",mycut&&beam5);

*/

/*
 Double_t nr[5];
 Double_t er[5];
 nr[0]=r0->GetEntries();
 nr[1]=r1->GetEntries();
 nr[2]=r2->GetEntries();
 nr[3]=r3->GetEntries();
 nr[4]=r4->GetEntries();
 er[0]=sqrt(nr[0]);
 er[1]=sqrt(nr[1]);
 er[2]=sqrt(nr[2]); 
 er[3]=sqrt(nr[3]);
 er[4]=sqrt(nr[4]);
*/

//char *histname = new char[10];
// sprintf(histname, "h_x_%d",xx);
// myhist[xx]=new TH1F(histname,"",100,-0.25,0.25);
// for (Int_t iii=0;iii<nentries; iii++) {
// 	Double_t binx=h_x->GetBinContent(iii);
//	myhist[xx]->SetBinContent(iii,binx);
	// }
 
//-------------------------------sim events


/*

//TCanvas *c2=new TCanvas("c2","",1200,820);
// c2->Divide(5,2);
// c2->cd(1);
 simt->Draw("beam>>sb0",mycut&&beam1); 
 //c2->cd(2);
 simt->Draw("beam>>sb1",mycut&&beam2); 
 //c2->cd(3);
 simt->Draw("beam>>sb2",mycut&&beam3); 
 //c2->cd(4);
 simt->Draw("beam>>sb3",mycut&&beam4); 
 //c2->cd(5);
 simt->Draw("beam>>sb4",mycut&&beam5); 
 //c2->cd(6);
simt->Draw("cos(PIanglez)>>s0",mycut&&beam1);
//c2->cd(7);
simt->Draw("cos(PIanglez)>>s1",mycut&&beam2);
//c2->cd(8);
simt->Draw("cos(PIanglez)>>s2",mycut&&beam3);
//c2->cd(9);
simt->Draw("cos(PIanglez)>>s3",mycut&&beam4);
//c2->cd(10);
simt->Draw("cos(PIanglez)>>s4",mycut&&beam5);




 Double_t factor[5];
factor[0] = b0->Integral("width") / sb0->Integral("width");
factor[1] = b1->Integral("width") / sb1->Integral("width");
factor[2] = b2->Integral("width") / sb2->Integral("width");
factor[3] = b3->Integral("width") / sb3->Integral("width");
factor[4] = b4->Integral("width") / sb4->Integral("width");

 Double_t ns[5];
 Double_t es[5];
 Double_t norms[5];
 ns[0]=s0->GetEntries();
 ns[1]=s1->GetEntries();
 ns[2]=s2->GetEntries();
 ns[3]=s3->GetEntries();
 ns[4]=s4->GetEntries();
 es[0]=sqrt(ns[0])*factor[0];
 es[1]=sqrt(ns[1])*factor[1];
 es[2]=sqrt(ns[2])*factor[2]; 
 es[3]=sqrt(ns[3])*factor[3];
 es[4]=sqrt(ns[4])*factor[4];
 norms[0]=ns[0]*factor[0];
 norms[1]=ns[1]*factor[1];
 norms[2]=ns[2]*factor[2]; 
 norms[3]=ns[3]*factor[3];
 norms[4]=ns[4]*factor[4];


s0->Scale(factor[0]);
s1->Scale(factor[1]);
s2->Scale(factor[2]);
s3->Scale(factor[3]);
s4->Scale(factor[4]);
// c2->cd(6);
//s0->Draw("SAME");
//c2->cd(7);
//s1->Draw("SAME");
//c2->cd(8);
//s2->Draw("SAME");
//c2->cd(9);
//s3->Draw("SAME");
//c2->cd(10);
//s4->Draw("SAME");

//c2->Update();

TH1F *newh=new TH1F("newh","renormalized cos(PIanglez)",zbin,zlow,zhigh);
 newh->Add(s0);
 newh->Add(s1);
 newh->Add(s2);
 newh->Add(s3);
 newh->Add(s4);


 //TCanvas *c3=new TCanvas("c3","",1200,820);
TH1F *finalh=new TH1F("finalh","cos(PIanglez)",zbin,zlow,zhigh);
 realt->Draw("cos(PIanglez)>>finalh",mycut); 
 newh->SetLineColor(2);
 newh->Draw("SAME");
 //newh->Fill(50);
 // c3->Update();


 */


}
