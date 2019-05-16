/*.
comment out the TH1F that is not being used in the end of this code according to if its simulated data or not.
the assymentry is just written but figgure out a way to imbed the calculation in the display of the histogram

to get asymetry of piange computed from "finalsoultion.C"
*/


void asymmetry() {

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

 TCut oneA="cos(PIangleLAB)<0";
 TCut twoA="cos(PIangleLAB)>0";
 TCut oneB="cos(PIangle)<0";
 TCut twoB="cos(PIangle)>0";
 TCut oneC="cos(LAMBangleLAB)<0";
 TCut twoC="cos(LAMBangleLAB)>0";
 TCut oneD="cos(LAMBangle)<0";
 TCut twoD="cos(LAMBangle)>0";

 Float_t neg;
 Float_t pos;

 // TFile *f = TFile::Open("~/clas/rootfiles/beam.root");
 //  TFile *f = TFile::Open("~/clas/rootfiles/std.root");
 TFile *f = TFile::Open("~/clas/rootfiles/helicity.root");
TTree *newt = (TTree*)f->Get("mytree");

TH1F *h1=new TH1F("h1","",20,-1.1,1.1);
TH1F *h2=new TH1F("h2","",20,-1.1,1.1);
/*
TCanvas *c1=new TCanvas("c1","",1200,820);
c1->Divide(2,0);
c1->cd(1); 
newt->Draw("cos(PIangleLAB)>>h1",mycut&&oneA);
c1->cd(2);
newt->Draw("cos(PIangleLAB)>>h2",mycut&&twoA);
 neg=h1->GetEntries();
 pos=h2->GetEntries();
 cout<<"for PIangleLAB:";
 cout<<" ";
 cout<<"neg=";
 cout<<neg;
 cout<<" ";
 cout<<"pos=";
 cout<<pos;
 cout<<" ";
 cout<<"total=";
 cout<<neg+pos;
 cout<<" ";
 cout<<"diff=";
 cout<<pos+neg;
 cout<<" ";
 cout<<"asymmetry=";
 cout<<(pos-neg)/(pos+neg)<<endl;

*/

TH1F *h3=new TH1F("h3","",20,-1.1,1.1);
TH1F *h4=new TH1F("h4","",20,-1.1,1.1);
TCanvas *c2=new TCanvas("c2","",1200,820);
c2->Divide(2,0);
c2->cd(1); 
newt->Draw("cos(PIangle)>>h3",mycut&&oneB);
c2->cd(2);
newt->Draw("cos(PIangle)>>h4",mycut&&twoB);
 neg=h3->GetEntries();
 pos=h4->GetEntries();
 cout<<"for PIangle:";
 cout<<" "; 
 cout<<"neg=";
 cout<<neg;
 cout<<" ";
 cout<<"pos=";
 cout<<pos;
 cout<<" ";
 cout<<"total=";
 cout<<neg+pos;
 cout<<" ";
 cout<<"diff=";
 cout<<pos+neg;
 cout<<" ";
 cout<<"asymmetry=";
 cout<<(pos-neg)/(pos+neg)<<endl;

 /*

TH1F *h5=new TH1F("h5","",20,-1.1,1.1);
TH1F *h6=new TH1F("h6","",20,-1.1,1.1);
TCanvas *c3=new TCanvas("c3","",1200,820);
c3->Divide(2,0);
c3->cd(1); 
newt->Draw("cos(LAMBangleLAB)>>h5",mycut&&oneC);
c3->cd(2);
newt->Draw("cos(LAMBangleLAB)>>h6",mycut&&twoC);
 neg=h5->GetEntries();
 pos=h6->GetEntries();
 cout<<"for LAMBangleLAB:";
 cout<<" "; 
cout<<"neg=";
 cout<<neg;
 cout<<" ";
 cout<<"pos=";
 cout<<pos;
 cout<<" ";
 cout<<"total=";
 cout<<neg+pos;
 cout<<" ";
 cout<<"diff=";
 cout<<pos+neg;
 cout<<" ";
 cout<<"asymmetry=";
 cout<<(pos-neg)/(pos+neg)<<endl;


TH1F *h7=new TH1F("h7","",20,-1.1,1.1);
TH1F *h8=new TH1F("h8","",20,-1.1,1.1);
TCanvas *c4=new TCanvas("c4","",1200,820);
c4->Divide(2,0);
c4->cd(1); 
newt->Draw("cos(LAMBangle)>>h7",mycut&&oneD);
c4->cd(2);
newt->Draw("cos(LAMBangle)>>h8",mycut&&twoD);
 neg=h7->GetEntries();
 pos=h8->GetEntries();
 cout<<"for LAMBangle:";
 cout<<" ";
 cout<<"neg=";
 cout<<neg;
 cout<<" ";
 cout<<"pos=";
 cout<<pos;
 cout<<" ";
 cout<<"total=";
 cout<<neg+pos;
 cout<<" ";
 cout<<"diff=";
 cout<<pos+neg;
 cout<<" ";
 cout<<"asymmetry=";
 cout<<(pos-neg)/(pos+neg)<<endl;


//}


*/
TH1F *h3=new TH1F("h3","neg=557 pos=582 total=1139 diff=1139 asymmetry=0.0219491",50,-1.1,1.1);
//TH1F *h3=new TH1F("h3","neg=35211 pos=35155 total=70366 diff=70366 asymmetry=-0.000795839",300,-1.1,1.1);

TCanvas *c1b=new TCanvas("c1b","",1200,820);
newt->Draw("cos(PIangle)>>h3",mycut);

}


