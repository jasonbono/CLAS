/*.
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

 //TFile *f = new TFile("finalsoultion.root");
 TFile *f = new TFile("newer.root");
 //TTree *newt = (TTree*)f->Get("new");

TH1F *h1=new TH1F("h1","",100,-1.1,1.1);
TH1F *h2=new TH1F("h2","",100,-1.1,1.1);
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



TH1F *h3=new TH1F("h3","",100,-1.1,1.1);
TH1F *h4=new TH1F("h4","",100,-1.1,1.1);
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



TH1F *h5=new TH1F("h5","",100,-1.1,1.1);
TH1F *h6=new TH1F("h6","",100,-1.1,1.1);
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


TH1F *h7=new TH1F("h7","",100,-1.1,1.1);
TH1F *h8=new TH1F("h8","",100,-1.1,1.1);
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

}


