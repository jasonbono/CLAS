

//nov 17 2011:  should be similar to the g11 version

void g12newcuts(){


  TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");
  TTree *newt = (TTree*)f->Get("g12ana_v15");







  TH2F *s2=new TH2F("s2", "", 40, 1., 1.3, 40, 1.25,1.45);
  g12ana_v15->Draw("sqrt(mm2kpkp):sqrt(mm2kpkppim)>>s2", mybasic); 
  gStyle->SetPalette(1);
  g12ana_v15->Draw("sqrt(mm2kpkp):sqrt(mm2kpkppim)>>s2", mybasic, "CONT");

  TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.02";
  TCut cas="abs(sqrt(mm2kpkp)-1.32)<0.02";


  TH1F *t2=new TH1F("t2", "", 60, 1., 1.3);
  g12ana_v15->Draw("sqrt(mm2kpkppim)>>t2", mybasic&&cas);

  t2->Fit("gaus", "", "", 1.09,1.15);

  /*

 EXT PARAMETER                                   STEP         FIRST   
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
   1  Constant     2.32933e+01   2.40207e+00   2.08627e-03   3.22703e-06
   2  Mean         1.11574e+00   1.63793e-03   1.86352e-06   1.08561e-04
   3  Sigma        1.70561e-02   1.87242e-03   3.37874e-05   2.43436e-04

so 3 sigma is 0.068 but lei did 0.051 below

  */


  TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.051";
  TH1F *t3=new TH1F("t3", "", 120, 1.2, 1.5);
  g12ana_v15->Draw("mlampim>>t3", mybasic&&lam);
  //from here he was "generous" with the following cut:
  TCut cas="abs(mlampim-1.32)<0.007"; 
  //note that now cas is on mlampi and NOT on mm
  g12ana_v15->Draw("sqrt(mm2kpkppim)>>t2", mybasic&&cas);



  //now demonstrating how to super impose plots to show the cuts.


  
  TH1F *t2_1=new TH1F("t2_1", "", 60, 1., 1.3);
  g12ana_v15->Draw("sqrt(mm2kpkppim)>>t2_1", mybasic&&cas);
  g12ana_v15->Draw("sqrt(mm2kpkppim)>>t2", mybasic&&cas&&"nphoton_nb0==1", "SAME");
    t2_1->SetLineColor(2);
    t2->SetLineColor(4);
    g12ana_v15->Draw("sqrt(mm2kpkppim)>>t2", mybasic&&cas&&"nphoton_nb1<2", "SAME");
    t2->Rebin(2);
    c0->Clear();
    g12ana_v15->Draw("sqrt(mm2kpkppim)>>t2", mybasic&&cas&&"nphoton_nb1<2", "SAME");



    TCanvas *c0=new TCanvas("c2", "", 20,20,600,600);


    TH1F *t2=new TH1F("t2", "", 60, 1., 1.3);  

    TH1F *t2_1=new TH1F("t2_1", "", 60, 1., 1.3);

  g12ana_v15->Draw("sqrt(mm2kpkppim)>>t2", mybasic&&cas&&"nphoton_nb1<2");
  g12ana_v15->Draw("sqrt(mm2kpkppim)>>t2", mybasic&&cas);


  //showing the what is now called lam cuts
  TCut mmlam="abs(sqrt(mm2kpkppim)-1.116)<0.02";
  g12ana_v15->Draw("sqrt(mm2kpkppim)>>t2_1", mybasic&&cas&&mmlam);
  t2->Draw("E");
  t2_1->SetFillColor(2);
  t2_1->Draw("SAME");


  // now looking for the best tof cuts
  TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.7";
  g12ana_v15->Draw("mlampim>>t3", lam&&!tof1);

  TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.5";
  g12ana_v15->Draw("mlampim>>t3", lam&&!tof1);


  TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.2";
  g12ana_v15->Draw("mlampim>>t3", lam&&!tof1);

  TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.2";
  g12ana_v15->Draw("mlampim>>t3", lam&&tof1);

  // now add on the tof2 cut but wont show






  ////////=========================================================== now what i did==========================


  //  the newly determined by me: 



  // TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.068";  // i this is 3 sigma of the beak if you cut TCut cas="abs(sqrt(mm2kpkp)-1.32)<0.02"; which came from looking at the
    //surface plot of mmkpkpim:mmkpkppim to get a starting point.


  // from above get:    
  TCut casm="abs(mlampim-1.32)<0.007";  // this comes from using the new lam on the spectrum
  //then replot and find
  TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.02";  //see pic
  /*
 this is found and seen by doing:
 TH1F *t2=new TH1F("t2", "", 60, 1., 1.3);  
 TH1F *t2_1=new TH1F("t2_1", "", 60, 1., 1.3);
 g12ana_v15->Draw("sqrt(mm2kpkppim)>>t2", mybasic&&cas);
 TCut mmlam="abs(sqrt(mm2kpkppim)-1.116)<0.02";
 g12ana_v15->Draw("sqrt(mm2kpkppim)>>t2_1", mybasic&&cas&&mmlam);
 t2->Draw("E");
 t2_1->SetFillColor(2);
 t2_1->Draw("SAME");
 */


  TCut np="nphoton_nb2<3"; // this seems to enhance the most

  TCut vcut="abs(vz+90)<24&&(vx^2+vy^2)<20";
  TCut beam="beam>3.6";  //determinde from doing g12ana_v15->Draw("mlampim>>t3", lam&&tof1&&tof2&&"beam>3.27")
  TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4"; // through plotting what lei plotted as shown above
  TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<0.4"; // similarly found what cut gave the best mlampim spectum


  //now fitting a gaussian to  g12ana_v15->Draw("mcasmMpim>>t2", np&&vcut&&beam&&tof1&&tof2&&casm)
  //gives an RMS of 0.00372 so the cut is
  TCut lamm="abs(mcasmMpim - 1.116)<0.013";

  // now all i have left is cas:  plotting mmkpkp with all above cuts gives mean of 1.322 and rms of 0.015 so 3 sigma is 0.045

  TCut cas="abs(sqrt(mm2kpkp - 1.321))<0.045";



  //---------------------------------------- in summary first time around have-----------------------------------------

  TCut np="nphoton_nb2<3";
  TCut vcut="abs(vz+90)<24&&(vx^2+vy^2)<20";
  TCut beam="beam>3.6"; 
  TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";
  TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<0.4";

  TCut newbasic=np&&vcut&&beam&&tof1&&tof2;
  
  TCut casm="abs(mlampim-1.321)<0.007";
  TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.02";
  TCut lamm="abs(mcasmMpim - 1.116)<0.013";
  TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.045";
  //----------------------------------------------------------------------

  //plotting over gives an for casm of 0.00369 which gives 0.011 so: 
  TCut casm="abs(mlampim-1.321)<0.011";



 


  //upon redoing.....................................

  //the basic stays the same
  TCut np="nphoton_nb2<3";
  TCut vcut="abs(vz+90)<24&&(vx^2+vy^2)<20";
  TCut beam="beam>3.6"; 
  TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";
  TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<0.4";

  TCut newbasic=np&&vcut&&beam&&tof1&&tof2;



  TCut casm="abs(mlampim-1.321)<0.018";
  TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.144";
  TCut lamm="abs(mcasmMpim - 1.116)<0.031";
  TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.083";

  //2nd iteration----------------------------------------------------------------------
  TCut casm="abs(mlampim-1.321)<0.016";
  TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.063";
  TCut lamm="abs(mcasmMpim - 1.116)<0.024";
  TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.057";

  //3rd iteration--------------------------------------------------------------------------
  TCut casm="abs(mlampim-1.321)<0.013";
  TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.039";
  TCut lamm="abs(mcasmMpim - 1.116)<0.015";
  TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";

  //added
  TCut id1="mmkp1pippim<1.42&&mmkp1pippim>1.174";
  TCut id2="mmkp1pippim<1.314&&mmkp1pippim>1.145";



  // so the newest cuts are:


  TCut id1="mmkp1pippim<1.42&&mmkp1pippim>1.174";
  TCut id2="mmkp1pippim<1.314&&mmkp1pippim>1.145";
  TCut np="nphoton_nb2<3";
  TCut vcut="abs(vz+90)<24&&(vx^2+vy^2)<20";
  TCut beam="beam>3.6"; 
  TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";
  TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<0.4";

  TCut newbasic=id1&&id2&&np&&vcut&&beam&&tof1&&tof2;

  TCut casm="abs(mlampim-1.321)<0.013";
  TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.039";
  TCut lamm="abs(mcasmMpim - 1.116)<0.015";
  TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";



  // 4th iteration
  TCut casm="abs(mlampim-1.321)<0.013";
  TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
  TCut lamm="abs(mcasmMpim - 1.116)<0.01";
  TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";

  //=========== this does not seem to be working out. i will try and redo all cuts only and exclude cuts on cas and lam for now.


  TH1F *h1=new TH1F("h1","",100,1,1.2);
  TH1F *h2=new TH1F("h2","",100,1.2,1.4);

 

   TCut np="nphoton_nb1<2";
  TCut vcut="abs(vz+90)<24&&(vx^2+vy^2)<20";
  TCut beam="beam>3.6"; 
st
  TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";
  TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<0.4";
  TCut newbasic=np&&vcut&&beam&&tof1&&tof2;




  g12ana_v15->Draw("(mcasmMpim)>>h1",newbasic);
  g12ana_v15->Draw("(mlampim)>>h2",newbasic);
  TH2F *s0=new TH2F("s0","",100,1.08,1.14,100,1.28,1.34);
  g12ana_v15->Draw("mlampim:mcasmMpim>>s0",newbasic,"CONT");


  //---------------------------------------------------------------------------------------------------------------------------------------------

  /* 
   * lei wanted to me to take out id1 and id2.
   * add sc
   * np was changed to "nphoton_nb1<2"
   * he wants me to show all 4 mass plots


final cuts as of now are below.  may need to changed st cut.

   */



  TCut np="nphoton_nb1<2";
  TCut vcut="abs(vz+90)<24&&(vx^2+vy^2)<20";
  TCut beam="beam>3.6"; 
  TCut st="abs(stv-scv)<1";
  TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";
  TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<0.4";
  TCut newbasic=np&&vcut&&beam&&st&&tof1&&tof2;


  TCut casm="abs(mlampim-1.321)<0.013";
  TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
  TCut lamm="abs(mcasmMpim - 1.116)<0.01";
  TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";

TCut lamm2="abs(mcasmMpim-1.116)<0.015";

TCut n="np<2&&npip<1&&nkm<1"

















}







