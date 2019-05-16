/*


jan 30 2012: added binning for foward and backward cascade angles in the center of mass frame.

nov 17 2011: this was taken from clas/macros/asymmetry.C mostly to have working code in a single orginaze directory, small edits will take place. added energybins and a new plot


*/


void g11polarisation() {



//-------------------change this for real and simulation--------------------------------

  TFile *f = TFile::Open("~/clas/rootfiles/g11/nxyzREAL.root");
  //TFile *f = TFile::Open("~/clas/rootfiles/g11/nxyzSIM.root");

 TTree *newt = (TTree*)f->Get("mytree");



//============= this is from leis_beautify.C which i changed a bit========================
//===============this is the final configuration that he used in his paper========
printf("Welcome to the ROOT\n");
 gStyle->SetTitleXOffset(0.85);  //this: Xoff
 gStyle->SetTitleYOffset(0.75);  //this:  Yoff
 gStyle->SetTitleSize(0.07);  //this:    Xsize   
 gStyle->SetTitleYSize(0.07); //this     Ysize
 //gStyle->SetLabelFont(72);
 gStyle->SetPadLeftMargin(0.11);   // this: Yaxis 
 gStyle->SetPadBottomMargin(0.15);  // this: Xaxis
 gStyle->SetPadTopMargin(0.02); // was 0.02
 gStyle->SetCanvasBorderMode(1);
 gStyle->SetPadBorderMode(1);
 gStyle->SetFrameBorderMode(0);
 gStyle->SetPadColor(0);
 gStyle->SetCanvasColor(0);
 gStyle->SetFrameFillColor(0);
 gStyle->SetFrameFillStyle(1001);
 gStyle->SetFrameFillStyle(0);
 gStyle->SetFillStyle(0);
 gStyle->SetOptStat(0);
//====================================================================





//============================the g11 cuts================================================
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

 TCut oneB="cos(PIangle)<0";
 TCut twoB="cos(PIangle)>0";

 TCut beam1="beam<3.33";
 TCut beam2="beam>3.33&&beam<3.59";
 TCut beam3="beam>3.59";

TCut fwd = " Xcmtheta > 0 ";  //jb jan30
TCut bcw = " Xcmtheta < 0 ";  //jb jan30


 //--------------------------------------------------------------------------------------------------------






 //=============================================================================================



 TH1F *hb1=new TH1F("hb1","beam1",20,-1.1,1.1);
 TH1F *hb2=new TH1F("hb2","beam1",20,-1.1,1.1);
 TH1F *hb3=new TH1F("hb3","beam2",20,-1.1,1.1);
 TH1F *hb4=new TH1F("hb4","beam2",20,-1.1,1.1);
 TH1F *hb5=new TH1F("hb5","beam3",20,-1.1,1.1);
 TH1F *hb6=new TH1F("hb6","beam3",20,-1.1,1.1);

 TCanvas *c0=new TCanvas("c0","",1200,820);
 c0->Divide(3,2);
 c0->cd(1); 
 newt->Draw("cos(PIangle)>>hb1",mycut&&oneB&&beam1);
 c0->cd(2);
 newt->Draw("cos(PIangle)>>hb2",mycut&&twoB&&beam1);
 c0->cd(3); 
 newt->Draw("cos(PIangle)>>hb3",mycut&&oneB&&beam2);
 c0->cd(4);
 newt->Draw("cos(PIangle)>>hb4",mycut&&twoB&&beam2); 
 c0->cd(5); 
 newt->Draw("cos(PIangle)>>hb5",mycut&&oneB&&beam3);
 c0->cd(6);
 newt->Draw("cos(PIangle)>>hb6",mycut&&twoB&&beam3);
 //so odd numbers are for when cos is negitive
 
 Float_t neg1=hb1->GetEntries();
 Float_t pos1=hb2->GetEntries();
 Float_t neg2=hb3->GetEntries();
 Float_t pos2=hb4->GetEntries();
 Float_t neg3=hb5->GetEntries();
 Float_t pos3=hb6->GetEntries();
 /*
 Float_t eneg1=sqrt(neg1);
 Float_t epos1=sqrt(pos1);
 Float_t eneg2=sqrt(neg2);
 Float_t epos2=sqrt(pos2);
 Float_t eneg3=sqrt(neg1);
 Float_t epos3=sqrt(pos3);
 */


	

 Float_t a1= ((pos1-neg1)/(pos1+neg1));
 Float_t p1= a1*4.385964;
 Float_t a2= ((pos2-neg2)/(pos2+neg2));
 Float_t p2= a2*4.385964;
 Float_t a3= ((pos3-neg3)/(pos3+neg3));
 Float_t p3= a3*4.385964;

 cout<<"p1="<<p1<<"  p2="<<p2<<"  p3="<<p3<<endl;




 Float_t x[3],ex[3],y[3],ey[3];

 // this is just a way of representing the beam energy in steps of .26 gev around the cuts
 // this should really be computed from the mean of the beam distributions for each cut but
 // will do this for now
 x[0]=3.2;
 x[1]=3.46;
 x[2]=3.72;


 // the intervals for beam energy
 ex[0]=0.13;
 ex[1]=0.13;
 ex[2]=0.13;
 
 //this is the polarization
 y[0]=p1;
 y[1]=p2;
 y[2]=p3;

 //error derived in paper notebook
 ey[0]=4.385964*sqrt( (1/(neg1+pos1)) + ((neg1-pos1)**2)/((neg1+pos1)**3)  );
 ey[1]=4.385964*sqrt( (1/(neg2+pos2)) + ((neg2-pos2)**2)/((neg2+pos2)**3)  );
 ey[2]=4.385964*sqrt( (1/(neg3+pos3)) + ((neg3-pos3)**2)/((neg3+pos3)**3)  );

 TCanvas *c1=new TCanvas("c1","",1200,820);
 gr = new TGraphErrors(3,x,y,ex,ey);
 // gr->GetYaxis()->SetRange(-5.25,5.0);
 gr->SetMarkerColor(4);
 gr->SetMarkerStyle(21); 
 gr->GetYaxis()->SetTitle("Polarization");  
 gr->GetXaxis()->SetTitle("E#gamma (GeV)"); 
 //gr->GetYaxis()->SetRange(-5.25,5.0);
 gr->SetMaximum(1.);
 gr -> SetMinimum(-1.);

gr->GetYaxis()->SetLabelSize(0.05);  
gr->GetXaxis()->SetLabelSize(0.05);
gr->GetXaxis()->CenterTitle();
gr->GetYaxis()->CenterTitle();

 gr->Draw("AP");
 //c1->Print("~/clas/pics/11_nov11/proposal/g11/g11polarisation.eps");
//c1->Print("~/clas/pics/11_nov29/g11polarisation.eps");




 //=============================================================================================
 //========================================now bin in Xcmtheta==================================
 //=============================================================================================


// quck test of forward backward cuts
TCanvas *cTest=new TCanvas("cTest","",1200,820);
cTest -> Divide(3,0);
cTest -> cd(1);
newt -> Draw("Xcmtheta");
cTest -> cd(2);
newt -> Draw("Xcmtheta",fwd);
cTest -> cd(3);
newt -> Draw("Xcmtheta",bcw);



TH1F *hx1=new TH1F("hx1","",20,-1.1,1.1);
TH1F *hx2=new TH1F("hx2","",20,-1.1,1.1);
TH1F *hx3=new TH1F("hx3","",20,-1.1,1.1);
TH1F *hx4=new TH1F("hx4","",20,-1.1,1.1);


TCanvas *cX=new TCanvas("cX","",1200,820);
cX->Divide(2,2);
cX->cd(1); 
newt->Draw("cos(PIangle)>>hx1",mycut&&oneB&&fwd);
cX->cd(2);
newt->Draw("cos(PIangle)>>hx2",mycut&&twoB&&fwd);
cX->cd(3); 
newt->Draw("cos(PIangle)>>hx3",mycut&&oneB&&bcw);
cX->cd(4);
newt->Draw("cos(PIangle)>>hx4",mycut&&twoB&&bcw); 


//so odd numbers are for when cos is negitive


Float_t Xneg1 = hx1 -> GetEntries();
Float_t Xpos1 = hx2 -> GetEntries();
Float_t Xneg2 = hx3 -> GetEntries();
Float_t Xpos2 = hx4 -> GetEntries();
/*
Float_t eneg1=sqrt(neg1);
Float_t epos1=sqrt(pos1);
Float_t eneg2=sqrt(neg2);
Float_t epos2=sqrt(pos2);
Float_t eneg3=sqrt(neg1);
Float_t epos3=sqrt(pos3);
*/


	
Float_t Xa1= ((Xpos1-Xneg1)/(Xpos1+Xneg1));
Float_t Xp1= Xa1*4.385964;
Float_t Xa2= ((Xpos2-Xneg2)/(Xpos2+Xneg2));
Float_t Xp2= Xa2*4.385964;
cout << "Xp1=" << Xp1 << "  Xp2=" << Xp2 << endl;


Float_t Xx[2],Xex[2],Xy[2],Xey[2];


Xx[0] = -0.5;
Xx[1] = 0.5;
Xex[0]=0.5;
Xex[1]=0.5;


//this is the polarization
Xy[0]=Xp1;
Xy[1]=Xp2;

//error derived in paper notebook
Xey[0]=4.385964*sqrt( (1/(Xneg1+Xpos1)) + ((Xneg1-Xpos1)**2)/((Xneg1+Xpos1)**3)  );
Xey[1]=4.385964*sqrt( (1/(Xneg2+Xpos2)) + ((Xneg2-Xpos2)**2)/((Xneg2+Xpos2)**3)  );
cout << "Xep1=" << Xp1 << "  Xep2=" << Xp2 << endl;



TCanvas *cX2=new TCanvas("cX2","",1200,820);
gr = new TGraphErrors(2, Xx, Xy, Xex, Xey);
// gr->GetYaxis()->SetRange(-5.25,5.0);
gr -> SetMarkerColor(4);
gr -> SetMarkerStyle(21); 
gr -> GetYaxis()->SetTitle("Polarization");  
gr -> GetXaxis()->SetTitle("Cos(#Theta_{#Xi^{-}})"); 
//gr->GetYaxis()->SetRange(-5.25,5.0);
gr -> SetMaximum(1.);
gr -> SetMinimum(-1.);

gr->GetYaxis()->SetLabelSize(0.05);  
gr->GetXaxis()->SetLabelSize(0.05);
gr->GetXaxis()->CenterTitle();
gr->GetYaxis()->CenterTitle();

gr -> Draw("AP");

















































 //================================this is old=============================================================
// ------computing the assymetry for all bins in cos(PIangle) when n-hat is defined in the cascade frame-------

/*

 Float_t neg;
 Float_t pos;

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
 cout << "polarization=";
 cout << (4.385964)*(pos-neg)/(pos+neg) <<endl;

 Float_t a= ((pos-neg)/(pos+neg));
 Float_t p= a*4.385964;


 TH1F *h3=new TH1F("h3",Form("asymmetry=%f polarization=%f ",a,p),50,-1.1,1.1);
 TCanvas *c1b=new TCanvas("c1b","",1200,820);
 newt->Draw("cos(PIangle)>>h3",mycut);


//*/

}


