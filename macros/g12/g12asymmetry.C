/*
// should be similar to the g11 version:  PIangle_ANA is already cos(thea)!!!!!!!!!!!!!

nov 17 2011: this was taken from clas/macros/asymmetry.C mostly to have working code in a single orginaze directory, small edits will take place. added energybins and a new plot


*/


void g12asymmetry() {
TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");
TTree *newt = (TTree*)f->Get("g12ana_v15");


//------------------------------------------COPY-------------------------------------------------- 
  
  TCut np="nphoton_nb2<6";  // doesnt do much anything right now

  TCut beam="beam>3.6";
  TCut st="abs(stv-scv)<1";
  TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<1";
  TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<1";
  TCut vcut="abs(vz+90)<21&&(vx^2+vy^2)<8";
  TCut mybasic=beam&&st&&tof1&&tof2&&vcut;

  TCut casm="abs(mlampim-1.32131)<0.05";
  TCut lamm="abs(mcasmMpim - 1.11568) < 0.05";
  TCut cas="abs(sqrt(mm2kpkp)-1.32131)<0.02";
  TCut lam="abs(sqrt(mm2kpkppim)-1.11568)<0.03";

  TCut total=mybasic&&np&&casm&&lamm&&cas&&lam;

  //-------------------------------------------COPY----------------------------------------------



 // this is added to break the data up
 TCut oneB="PIangle_ANA<0";
 TCut twoB="PIangle_ANA>0";


 TCut beam1="beam<3.33";
 TCut beam2="beam>3.33&&beam<3.59";
 TCut beam3="beam>3.59";




 //=============================energy bins================================================================

/*


 TH1F *hb1=new TH1F("hb1","beam1",20,-1.1,1.1);
 TH1F *hb2=new TH1F("hb2","beam1",20,-1.1,1.1);
 TH1F *hb3=new TH1F("hb3","beam2",20,-1.1,1.1);
 TH1F *hb4=new TH1F("hb4","beam2",20,-1.1,1.1);
 TH1F *hb5=new TH1F("hb5","beam3",20,-1.1,1.1);
 TH1F *hb6=new TH1F("hb6","beam3",20,-1.1,1.1);

 TCanvas *c0=new TCanvas("c0","",1200,820);
 c0->Divide(3,2);
 c0->cd(1); 
 newt->Draw("PIangle_ANA>>hb1",total&&oneB&&beam1);
 c0->cd(2);
 newt->Draw("PIangle_ANA>>hb2",total&&twoB&&beam1);
 c0->cd(3); 
 newt->Draw("PIangle_ANA>>hb3",total&&oneB&&beam2);
 c0->cd(4);
 newt->Draw("PIangle_ANA>>hb4",total&&twoB&&beam2); 
 c0->cd(5); 
 newt->Draw("PIangle_ANA>>hb5",total&&oneB&&beam3);
 c0->cd(6);
 newt->Draw("PIangle_ANA>>hb6",total&&twoB&&beam3);
 //so odd numbers are for when cos is negitive
 
 Float_t neg1=hb1->GetEntries();
 Float_t pos1=hb2->GetEntries();
 Float_t neg2=hb3->GetEntries();
 Float_t pos2=hb4->GetEntries();
 Float_t neg3=hb5->GetEntries();
 Float_t pos3=hb6->GetEntries();

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


 // use zero error for beam
 ex[0]=0;
 ex[1]=0;
 ex[2]=0;
 
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
 gr->SetMarkerColor(4);
 gr->SetMarkerStyle(21); 
 gr->Draw("AP");

 //*/


 //=============================================================================================
// ------computing the assymetry for all bins in cos(PIangle) when n-hat is defined in the cascade frame-------

//*

 Float_t neg;
 Float_t pos;

 TH1F *h3=new TH1F("h3","",20,-1.1,1.1);
 TH1F *h4=new TH1F("h4","",20,-1.1,1.1);
 TCanvas *c2=new TCanvas("c2","",1200,820);
 c2->Divide(2,0);
 c2->cd(1); 
 newt->Draw("PIangle_ANA>>h3",total&&oneB);
 c2->cd(2);
 newt->Draw("PIangle_ANA>>h4",total&&twoB);
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
 newt->Draw("PIangle_ANA>>h3",total);


//*/

}


