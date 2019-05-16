

void asymmetryALLBINS() {
  //TFile *f = TFile::Open("~/clas/rootfiles/newer.root");
  TFile *f = TFile::Open("~/clas/rootfiles/beam.root");

TTree *newt = (TTree*)f->Get("mytree");

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


 TCut negcut="cos(PIangle)<0";
 TCut poscut="cos(PIangle)>0";

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

TH1F *h1=new TH1F("h1","",20,-1.1,1.1);
 newt->Draw("cos(PIangle)>>h1",mycut&&negcut&&XBin1);
neg=h1->GetEntries();
 newt->Draw("cos(PIangle)>>h1",mycut&&poscut&&XBin1);
pos=h1->GetEntries();
p1=((-2.0)*((pos-neg)/(pos+neg))/(-0.456));
ep1= ((-2)/(-0.456))*(sqrt( (1/(neg+pos)) + ( (pos-neg)*(pos-neg)/((pos+neg)*(pos+neg)*(pos+neg)) )  ));

newt->Draw("cos(PIangle)>>h1",mycut&&negcut&&XBin2);
neg=h1->GetEntries();
 newt->Draw("cos(PIangle)>>h1",mycut&&poscut&&XBin2);
pos=h1->GetEntries();
p2=((-2.0)*((pos-neg)/(pos+neg))/(-0.456));
ep2= ((-2)/(-0.456))*(sqrt( (1/(neg+pos)) + ( (pos-neg)*(pos-neg)/((pos+neg)*(pos+neg)*(pos+neg)) )  ));

 newt->Draw("cos(PIangle)>>h1",mycut&&negcut&&XBin1);
neg=h1->GetEntries();
 newt->Draw("cos(PIangle)>>h1",mycut&&poscut&&XBin1);
pos=h1->GetEntries();
p3=((-2.0)*((pos-neg)/(pos+neg))/(-0.456));
ep3= ((-2)/(-0.456))*(sqrt( (1/(neg+pos)) + ( (pos-neg)*(pos-neg)/((pos+neg)*(pos+neg)*(pos+neg)) )  ));



 
   Double_t Xx[3]  = {1, 2, 3};
   Double_t Xy[3]  = {p1, p2, p3};
   Double_t Xex[3] = {0,0,0};
   Double_t Xey[3] = {ep1,ep2,ep3};
   



   // NOW TO DO THE SAME FOR ENERGY BINS



 newt->Draw("cos(PIangle)>>h1",mycut&&negcut&&EBin1);
neg=h1->GetEntries();
 newt->Draw("cos(PIangle)>>h1",mycut&&poscut&&EBin1);
pos=h1->GetEntries();
p1=((-2.0)*((pos-neg)/(pos+neg))/(-0.456));
ep1= ((-2)/(-0.456))*(sqrt( (1/(neg+pos)) + ( (pos-neg)*(pos-neg)/((pos+neg)*(pos+neg)*(pos+neg)) )  ));

newt->Draw("cos(PIangle)>>h1",mycut&&negcut&&EBin2);
neg=h1->GetEntries();
 newt->Draw("cos(PIangle)>>h1",mycut&&poscut&&EBin2);
pos=h1->GetEntries();
p2=((-2.0)*((pos-neg)/(pos+neg))/(-0.456));
ep2= ((-2)/(-0.456))*(sqrt( (1/(neg+pos)) + ( (pos-neg)*(pos-neg)/((pos+neg)*(pos+neg)*(pos+neg)) )  ));

 newt->Draw("cos(PIangle)>>h1",mycut&&negcut&&EBin1);
neg=h1->GetEntries();
 newt->Draw("cos(PIangle)>>h1",mycut&&poscut&&EBin1);
pos=h1->GetEntries();
p3=((-2.0)*((pos-neg)/(pos+neg))/(-0.456));
ep3= ((-2)/(-0.456))*(sqrt( (1/(neg+pos)) + ( (pos-neg)*(pos-neg)/((pos+neg)*(pos+neg)*(pos+neg)) )  ));



   Double_t Ex[3]  = {1, 2, 3};
   Double_t Ey[3]  = {p1, p2, p3};
   Double_t Eex[3] = {0,0,0};
   Double_t Eey[3] = {ep1,ep2,ep3};
/* just for reference check that this matches the accual cuts above
TCut XBin1="(Xcmtheta)<-0.65";
 TCut XBin2="abs(Xcmtheta + 0.50)<0.15";
 TCut XBin3="(Xcmtheta)>-0.35";

 TCut EBin1="(fixbeam2)<3.33";
 TCut EBin2="abs(fixbeam2 - 3.46)<0.13";
 TCut EBin3="(fixbeam2)>3.59";
*/
   can1 = new TCanvas("can1","how does polarisation change with theta(X)?",200,10,700,500);
   can1->SetFillColor(42);
   can1->SetGrid();
   can1->GetFrame()->SetFillColor(21);
   can1->GetFrame()->SetBorderSize(12);
   gr = new TGraphErrors(3,Xx,Xy,Xex,Xey);
   gr->SetTitle("X Angles  (1):cos(Xcm)<-0.65,  (2):-0.65<cos(Xcm)<-0.35,   (3):cos(Xcm)>-0.35");
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->Draw("AP");

   can2 = new TCanvas("can2","how does polarisation change with w?",200,10,700,500);
   can2->SetFillColor(42);
   can2->SetGrid();
   can2->GetFrame()->SetFillColor(21);
   can2->GetFrame()->SetBorderSize(12);
   gr2 = new TGraphErrors(3,Ex,Ey,Eex,Eey);
   gr2->SetTitle("beam energy (Gev) (1):beam<3.33, (2):3.33<beam<3.59,  (3):beam>3.59");
   gr2->SetMarkerColor(4);
   gr2->SetMarkerStyle(21);  
  gr2->Draw("AP");








}
