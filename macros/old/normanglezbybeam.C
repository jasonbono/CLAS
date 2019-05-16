
void normanglezbybeam(){

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

 /*
 TH1F *h1=new TH1F("h1","real",12,2.5,5.5);
 TH1F *h2=new TH1F("h2","sim",12,2.5,5.5);

 TCanvas *c0=new TCanvas("c0","",1200,820);
 c0->Divide(2,0);
 c0->cd(1); 
 realt->Draw("beam>>h1",mycut);
 c0->cd(2);  
 simt->Draw("beam>>h2",mycut);
 c0->cd(0);
 */

 TCut beam1="abs(beam-2.875)<0.125";
 TCut beam2="abs(beam-3.125)<0.125";
 TCut beam3="abs(beam-3.375)<0.125";
 TCut beam4="abs(beam-3.625)<0.125";
 TCut beam5="abs(beam-3.875)<0.125";
/*
 TH1F *realhist[1000];
 char *histname = new char[10];
 // sprintf(histname, "h_x_%d",xx);
 realhist[xx]=new TH1F(histname,"",100,-0.25,0.25);
 for (Int_t iii=0;iii<nentries; iii++) {
 	Double_t binx=h_x->GetBinContent(iii);
 	myhist[xx]->SetBinContent(iii,binx);
 }
*/



 TH1F *realbeam[5];
 realbeam[0]=new TH1F("b0","",12,2.5,5.5);
 realbeam[1]=new TH1F("b1","",12,2.5,5.5);
 realbeam[2]=new TH1F("b2","",12,2.5,5.5);
 realbeam[3]=new TH1F("b3","",12,2.5,5.5);
 realbeam[4]=new TH1F("b4","",12,2.5,5.5);

TH1F *realhist[5];
realhist[0]=new TH1F("r0","",10,-1,1);
realhist[1]=new TH1F("r1","",10,-1,1);
realhist[2]=new TH1F("r2","",10,-1,1);
realhist[3]=new TH1F("r3","",10,-1,1);
realhist[4]=new TH1F("r4","",10,-1,1);

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


//char *histname = new char[10];
// sprintf(histname, "h_x_%d",xx);
// myhist[xx]=new TH1F(histname,"",100,-0.25,0.25);
// for (Int_t iii=0;iii<nentries; iii++) {
// 	Double_t binx=h_x->GetBinContent(iii);
//	myhist[xx]->SetBinContent(iii,binx);
	// }
 
//-------------------------------sim events



 TH1F *simbeam[5];
 simbeam[0]=new TH1F("sb0","",12,2.5,5.5);
 simbeam[1]=new TH1F("sb1","",12,2.5,5.5);
 simbeam[2]=new TH1F("sb2","",12,2.5,5.5);
 simbeam[3]=new TH1F("sb3","",12,2.5,5.5);
 simbeam[4]=new TH1F("sb4","",12,2.5,5.5);

TH1F *realhist[5];
simhist[0]=new TH1F("s0","",10,-1,1);
simhist[1]=new TH1F("s1","",10,-1,1);
simhist[2]=new TH1F("s2","",10,-1,1);
simhist[3]=new TH1F("s3","",10,-1,1);
simhist[4]=new TH1F("s4","",10,-1,1);

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

TH1F *newh=new TH1F("newh","renormalized cos(PIanglez)",10,-1,1);
 newh->Add(s0);
 newh->Add(s1);
 newh->Add(s2);
 newh->Add(s3);
 newh->Add(s4);


 //TCanvas *c3=new TCanvas("c3","",1200,820);
TH1F *finalh=new TH1F("finalh","cos(PIanglez)",10,-1,1);
 realt->Draw("cos(PIanglez)>>finalh",mycut); 
 newh->SetLineColor(2);
 newh->Draw("SAME");
 //newh->Fill(50);
 // c3->Update();





 //TCut beam1="abs(beam-2.875)<0.125";
 //TCut beam2="abs(beam-3.125)<0.125";
 //TCut beam3="abs(beam-3.375)<0.125";
 //TCut beam4="abs(beam-3.625)<0.125";
 // TCut beam5="abs(beam-3.875)<0.125";
/*
 Float_t be[5] = {2.875,3.152,3.375,3.625,3.875};
 Float_t ebe[5] = {0,0,0,0,0};


 TCanvas *c4=new TCanvas("c4","",1200,820);

TGraphErrors *gr1 = new TGraphErrors(5,be,nr,ebe,er);
   gr1->SetMarkerColor(kBlue);
   gr1->SetMarkerStyle(21);
   gr1->Draw("LP");
*/
}
