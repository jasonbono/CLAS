// October 3 edited this file to show PIanglex and PIangley

//------>>>>> edited "mycut" to the spesifications of "mynewB" "mycasB" and "mylambdaB"

// made to examine the kinimatic variables which do not make sence produced from the 
// "resultsWpointers2.C" macro.

void debug(){



  
  //TFile *f = TFile::Open("~/clas/rootfiles/nxyzREAL.root");
TFile *f = TFile::Open("~/clas/rootfiles/nxyzSIM.root");
//TFile *f = TFile::Open("~/clas/rootfiles/newer.root");
  //TFile *f = TFile::Open("~/clas/rootfiles/helicity.root");
  // TFile *f = TFile::Open("~/clas/rootfiles/helicitySIM.root");
 //TFile *f = TFile::Open("~/clas/rootfiles/dbg.root");
  //TFile *f = TFile::Open("~/clas/rootfiles/beam.root");
TTree *newt = (TTree*)f->Get("mytree");


//TH1F *h1=new TH1F("h1","Epil",200,0,6);
//TH1F *h2=new TH1F("h2","EpilCUT",200,0,6);
//TH1F *h3=new TH1F("h3","Erestcas",200,0,6);

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
TCanvas *fpi=new TCanvas("fpi","",1200,820);
fpi->Divide(2,2);
fpi->cd(1); 
newt->Draw("ppim",mycut);
fpi->cd(2); 
newt->Draw("sin(TMath::ACos(pilabtheta))*cos(pilabphi*TMath::Pi())",mycut);
fpi->cd(3); 
 newt->Draw("sin(TMath::ACos(pilabtheta))*sin(pilabphi*TMath::Pi())",mycut);
fpi->cd(4); 
 newt->Draw("pilabtheta",mycut); 



TCanvas *fpi2=new TCanvas("fpi2","",1200,820);
fpi2->Divide(2,0);
fpi2->cd(1); 
newt->Draw("TMath::ACos(pilabtheta)",mycut);
fpi2->cd(2);
newt->Draw("pilabphi*TMath::Pi()",mycut);

TCanvas *fpi3=new TCanvas("fpi3","",1200,820);
fpi3->Divide(2,0);
fpi3->cd(1); 
newt->Draw("sin(pilabphi*TMath::Pi())",mycut);
fpi3->cd(2);
newt->Draw("cos(pilabphi*TMath::Pi())",mycut);
 */


TH1F *h1=new TH1F("h1","Energy of pi+l",200,1.3,1.34);
TH1F *h2=new TH1F("h2","Energy of Xi",200,1.3,1.34);

TCanvas *c0=new TCanvas("c0","",1200,820);
c0->Divide(2,0);
c0->cd(1); 
newt->Draw("Epil>>h1",mycut);
c0->cd(2);  
newt->Draw("Erestcas>>h2",mycut);

//*/
TCanvas *f1=new TCanvas("f1","",1200,820);
TH1F *add1=new TH1F("add1","cos(PIangle)+cos(LAMBangle)",1000,-0.5,0.5);
TH1F *add2=new TH1F("add2","cos(PIanglez)+cos(LAMBanglez)",1000,-0.5,0.5);
TH1F *add3=new TH1F("add3","cos(PIanglex)+cos(LAMBanglex)",1000,-0.5,0.5);
TH1F *add4=new TH1F("add4","cos(PIangley)+cos(LAMBangley)",1000,-0.5,0.5);
f1->Divide(2,2);
 f1->cd(1);
 newt->Draw("cos(PIangle)+cos(LAMBangle)>>add1",mycut);
f1->cd(2);
newt->Draw("cos(PIanglez)+cos(LAMBanglez)>>add2",mycut);
 f1->cd(3);
 newt->Draw("cos(PIanglex)+cos(LAMBanglex)>>add3",mycut);
f1->cd(4);
newt->Draw("cos(PIangley)+cos(LAMBangley)>>add4",mycut);



/*
TCanvas *c1=new TCanvas("c1","",1200,820);
c1->Divide(2,2);
c1->cd(1);
newt->Draw("PIangleLAB");
c1->cd(2);
newt->Draw("PIangle");
c1->cd(3);
newt->Draw("LAMBangleLAB");
c1->cd(4); 
newt->Draw("LAMBangle");
*/ 


TH1F *h3=new TH1F("h3","cos(PIangle)",50,-1.1,1.1);
TH1F *h4=new TH1F("h4","cos(PIanglez)",50,-1.1,1.1);
TH1F *h5=new TH1F("h5","cos(PIanglex)",50,-1.1,1.1);
TH1F *h6=new TH1F("h6","cos(PIangley)",50,-1.1,1.1);
TCanvas *c1b=new TCanvas("c1b","",1200,820);
c1b->Divide(2,2);
c1b->cd(1);
 newt->Draw("cos(PIangle)>>h3",mycut);
c1b->cd(2);
newt->Draw("cos(PIanglez)>>h4",mycut);
c1b->cd(3);
 newt->Draw("cos(PIanglex)>>h5",mycut);
c1b->cd(4);
newt->Draw("cos(PIangley)>>h6",mycut);





/*
TCut lab="LABcasDOTnormLAB==0";
TCut cm="LABcasDOTnormCM==0";
TCanvas *c2=new TCanvas("c2","",1200,820);
 c2->Divide(2,3);
 c2->cd(1);
newt->Draw("LABcasDOTnormLAB");
 c2->cd(2);
newt->Draw("LABcasDOTnormCM");
 c2->cd(3);
 newt->Draw("LABcasDOTnormLAB",lab);
 c2->cd(4);
 newt->Draw("LABcasDOTnormCM",cm);
 c2->cd(5);
 newt->Draw("LABcasDOTnormLAB",!cm);
 c2->cd(6);
 newt->Draw("LABcasDOTnormCM",!lab);
*/

/*
TCanvas *c3=new TCanvas("c3","",1200,820);
c3->Divide(2,3);
c3->cd(1);
newt->Draw("Xlabtheta");
c3->cd(2);
newt->Draw("Xcmtheta");
c3->cd(3);
newt->Draw("Xlabtheta",lab&&cm);
c3->cd(4);
newt->Draw("Xcmtheta",lab&&cm);
c3->cd(5);
newt->Draw("Xlabtheta",!lab&&!cm);
c3->cd(6);
newt->Draw("Xcmtheta",!lab&&!cm);
*/


// TCanvas *c4=new TCanvas("c4","",600,400);
// newt->Draw("normdiff");
 //*/
}
