// October 3: edited to include the angles off the x and y axis.

// sim events only go up to 3.84 gev real data goes up to 4 gev
// cs[11] was the cross section of the reaction from leis 2007 paper titled below
// Cascade production in the reactions gamma p ---> K+ K+ (X) and gamma p ---> K+ K+ pi- (X)
// want to go one bin extra on the low side and 2 bins extra on the high side
// this should give 11+3=14 bins:  need to always display 1 extra on the high side to see it.

void norm_write_root_file(){

 TFile *f1 = TFile::Open("~/clas/rootfiles/nxyzREAL.root");
 TTree *realt = (TTree*)f1->Get("mytree");
 TFile *f2 = TFile::Open("~/clas/rootfiles/nxyzSIM.root");
 TTree *simt = (TTree*)f2->Get("mytree");

 // create a new ROOT file for output
 TFile *outFile = new TFile("~/clas/rootfiles/norm_rootfile.root", "RECREATE");


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


 TCut beam[11];
 for (int i = 0; i < 11; i++) {
   Float_t beamcutVal = 2.79 + .1*i;
   beam[i] = Form("abs(beam-%.2f)<0.05", beamcutVal);
 }


 TCut rb="abs(beam-3.29)<0.55";

 Float_t beambin=11;
 Float_t beamlow=2.74;
 Float_t beamhigh=3.84;
     
 Float_t zbin=10;
 Float_t zlow=-1;
 Float_t zhigh=1;


 TH1F *b_real[11];
 TH1F *b_sim[11];
 TH1F *z_real[11];
 TH1F *z_sim[11];
 TH1F *n_real[11];
 TH1F *n_sim[11];

 TH1F *x_real[11];
 TH1F *x_sim[11];
 TH1F *y_real[11];
 TH1F *y_sim[11];


for( Int_t i=0;i<11;i++){

   b_real[i]=new TH1F(Form("b_real%d",i),"",beambin,beamlow,beamhigh);
   b_sim[i]=new TH1F(Form("b_sim%d",i),"",beambin,beamlow,beamhigh);

   z_real[i]=new TH1F(Form("z_real%d",i),"",zbin,zlow,zhigh);
   z_sim[i]=new TH1F(Form("z_sim%d",i),"",zbin,zlow,zhigh);

   n_real[i]=new TH1F(Form("n_real%d",i),"",zbin,zlow,zhigh);
   n_sim[i]=new TH1F(Form("n_sim%d",i),"",zbin,zlow,zhigh);

   x_real[i]=new TH1F(Form("x_real%d",i),"",zbin,zlow,zhigh);
   x_sim[i]=new TH1F(Form("x_sim%d",i),"",zbin,zlow,zhigh);

   y_real[i]=new TH1F(Form("y_real%d",i),"",zbin,zlow,zhigh);
   y_sim[i]=new TH1F(Form("y_sim%d",i),"",zbin,zlow,zhigh);
}



 // NOW FILl BEAM COSANGLEZ COSANGLEN FROM REAL AND SIMULATED EVENT IN TO 11 SEPERATE BEAM BINS 

 for( Int_t i=0;i<11;i++){
   realt->Draw(Form("beam>>b_real%d",i),mycut&&rb&&beam[i]);
   simt->Draw(Form("beam>>b_sim%d",i),mycut&&rb&&beam[i]);

   realt->Draw(Form("cos(PIanglez)>>z_real%d",i),mycut&&rb&&beam[i]);
   simt->Draw(Form("cos(PIanglez)>>z_sim%d",i),mycut&&rb&&beam[i]);
   
   realt->Draw(Form("cos(PIangle)>>n_real%d",i),mycut&&rb&&beam[i]);
   simt->Draw(Form("cos(PIangle)>>n_sim%d",i),mycut&&rb&&beam[i]);
   
   
   realt->Draw(Form("cos(PIanglex)>>x_real%d",i),mycut&&rb&&beam[i]);
   simt->Draw(Form("cos(PIanglex)>>x_sim%d",i),mycut&&rb&&beam[i]);
   
   realt->Draw(Form("cos(PIangley)>>y_real%d",i),mycut&&rb&&beam[i]);
   simt->Draw(Form("cos(PIangley)>>y_sim%d",i),mycut&&rb&&beam[i]);
   
 }




 outFile->Write();
 outFile->Close();
 
 
}
