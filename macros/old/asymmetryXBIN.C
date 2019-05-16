/*.
to get asymetry of piange computed from "finalsoultion.C"
*/


void asymmetryXBIN() {

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

TCut XBin1="(Xcmtheta)<-0.65";
 TCut XBin2="abs(Xcmtheta + 0.50)<0.15";
 TCut XBin3="(Xcmtheta)>-0.35";

 TCut EBin1="(fixbeam2)<3.33";
 TCut EBin2="abs(fixbeam2 - 3.46)<0.13";
 TCut EBin3="(fixbeam2)>3.59";

 Float_t neg;
 Float_t pos;

 Double_t p1=1;
 Double_t p2=1;
 Double_t p3=1;
 Double_t ep1=1;
 Double_t ep2=1;
 Double_t ep3=1;

TFile *f = TFile::Open("~/clas/rootfiles/newer.root");
//TFile *f = TFile::Open("~/clas/rootfiles/std.root");
//TFile *f = TFile::Open("~/clas/rootfiles/dbg.root");
TTree *newt = (TTree*)f->Get("mytree");


TH1F *h1=new TH1F("h1","",20,-1.1,1.1);
TH1F *h2=new TH1F("h2","",20,-1.1,1.1);
TCanvas *c1=new TCanvas("c1","",1200,820);
 c1->Divide(2,0);
 c1->cd(1); 
 newt->Draw("cos(PIangle)>>h1",mycut&&oneB&&XBin1);
 c1->cd(2);
 newt->Draw("cos(PIangle)>>h2",mycut&&twoB&&XBin1);
 neg=h1->GetEntries();
 pos=h2->GetEntries();
 cout<<"for PIangle backward:";
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
 cout<<"A=";
 cout<<(pos-neg)/(pos+neg);
 cout<<" ";
 cout<<"err(A)=";
 cout<<sqrt( (1/(neg+pos)) + ( (pos-neg)*(pos-neg)/((pos+neg)*(pos+neg)*(pos+neg)) )  );
 cout<<" ";
 p1=((-2.0)*((pos-neg)/(pos+neg))/(-0.456));
 cout<<"P=";
 cout<< p1;
 cout<<" ";
 cout<<"err(P)=";
 ep1= ((-2)/(-0.456))*(sqrt( (1/(neg+pos)) + ( (pos-neg)*(pos-neg)/((pos+neg)*(pos+neg)*(pos+neg)) )  ));
cout<< ep1 <<endl;



TH1F *h3=new TH1F("h3","",20,-1.1,1.1);
TH1F *h4=new TH1F("h4","",20,-1.1,1.1);
TCanvas *c2=new TCanvas("c2","",1200,820);
c2->Divide(2,0);
c2->cd(1); 
newt->Draw("cos(PIangle)>>h3",mycut&&oneB&&XBin2);
c2->cd(2);
newt->Draw("cos(PIangle)>>h4",mycut&&twoB&&XBin2);
 neg=h3->GetEntries();
 pos=h4->GetEntries();
 cout<<"for PIangle middle:";
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
 cout<<"A=";
 cout<<(pos-neg)/(pos+neg);
 cout<<" ";
 cout<<"err(A)=";
 cout<<sqrt( (1/(neg+pos)) + ( (pos-neg)*(pos-neg)/((pos+neg)*(pos+neg)*(pos+neg)) )  );
 cout<<" ";
  p2=((-2.0)*((pos-neg)/(pos+neg))/(-0.456));
 cout<<"P=";
 cout<< p2;
 cout<<" ";
 cout<<"err(P)=";
 ep2= ((-2)/(-0.456))*(sqrt( (1/(neg+pos)) + ( (pos-neg)*(pos-neg)/((pos+neg)*(pos+neg)*(pos+neg)) )  ));
cout<< ep2 <<endl;



TH1F *h5=new TH1F("h5","",20,-1.1,1.1);
TH1F *h6=new TH1F("h6","",20,-1.1,1.1);
TCanvas *c3=new TCanvas("c3","",1200,820);
c3->Divide(2,0);
c3->cd(1); 
newt->Draw("cos(PIangle)>>h5",mycut&&oneB&&XBin3);
c3->cd(2);
newt->Draw("cos(PIangle)>>h6",mycut&&twoB&&XBin3);
 neg=h5->GetEntries();
 pos=h6->GetEntries();
 cout<<"for PIanble foward:";
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
 cout<<"A=";
 cout<<(pos-neg)/(pos+neg);
 cout<<" ";
 cout<<"err(A)=";
 cout<<sqrt( (1/(neg+pos)) + ( (pos-neg)*(pos-neg)/((pos+neg)*(pos+neg)*(pos+neg)) )  );
 cout<<" ";
 p3=((-2.0)*((pos-neg)/(pos+neg))/(-0.456));
 cout<<"P=";
 cout<< p3;
 cout<<" ";
 cout<<"err(P)=";
 ep3= ((-2)/(-0.456))*(sqrt( (1/(neg+pos)) + ( (pos-neg)*(pos-neg)/((pos+neg)*(pos+neg)*(pos+neg)) )  ));
cout<< ep3 <<endl;

can1 = new TCanvas("can1","how does polarisation change with theta(X)?",200,10,700,500);
   can1->SetFillColor(42);
   can1->SetGrid();
   can1->GetFrame()->SetFillColor(21);
   can1->GetFrame()->SetBorderSize(12);
   Double_t y1=1;
   Double_t y2=1;
   Double_t y3=1;
   Double_t x[3]  = {1, 2, 3};
   Double_t y[3]  = {p1, p2, p3};
   Double_t ex[3] = {0,0,0};
   Double_t ey[3] = {ep1,ep2,ep3};
   gr = new TGraphErrors(3,x,y,ex,ey);
   gr->SetTitle("Angles 1=Backwards 2=Middle 3=Foward");
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->Draw("ALP");








}


