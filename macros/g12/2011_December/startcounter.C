// december 16 this is to look at the stv distributions with isSThit()


void startcounter(){

  TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v16.root");
TTree *newt = (TTree*)f->Get("g12ana_v16");



/*
//============= this is from leis_beautify.C which i changed a bit========================
//===============this is the final configuration that he used in his paper========
 printf("Welcome to the ROOT\n");
 gStyle->SetTitleXOffset(0.85);  //this: Xoff
 gStyle->SetTitleYOffset(0.95);  //this:  Yoff
 gStyle->SetTitleSize(0.07);  //this:    Xsize   
 gStyle->SetTitleYSize(0.07); //this     Ysize
 //gStyle->SetLabelFont(72);
 gStyle->SetPadLeftMargin(0.19);   // this: Yaxis 
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
*/

//*
//=========================the most recent cuts as of nov22========================
//need to relax a few cuts here after showing lei my overlay plots.
 TCut n="np<2&&npip<1&&nkm<1";
 TCut np="nphoton_nb1<2";
 TCut vcut="abs(vz+90)<30&&sqrt(vx^2+vy^2)<7";  // relaxed this alot to allow for weak decays
 TCut beam="beam>3.3"; //relaxed this from 3.6
 TCut st="abs(stv-scv)<1";
 TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";
 TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<1.1";  // this is relaxed because the slower particle has a lower time resoultion.
 TCut newbasic=n&&np&&vcut&&beam&&st&&tof1&&tof2;
 
 //theese are best defined in this part of the code to prevent discrepenceys when changing cuts in geometry.
TCut allbut_vz=n&&np&&"sqrt(vx^2+vy^2)<7"&&beam&&st&&tof1&&tof2;
TCut allbut_vr=n&&np&&"abs(vz+90)<30"&&beam&&st&&tof1&&tof2;

 TCut casm="abs(mlampim-1.321)<0.013";
 TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
 TCut lamm="abs(mcasmMpim - 1.116)<0.01";
 TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";
 TCut lamm2="abs(mcasmMpim-1.116)<0.02"; //lei used this cut rather than lamm
//----------------------------------------------------------------------------------



TCut kp1g="goodSTkp1==1";
TCut kp2g="gootSTkp2==1";
TCut pimg="goodSTpim==1";
TCut kp1b="goodSTkp1==0";
TCut kp2b="gootSTkp2==0";
TCut pimb="goodSTpim==0";

TCut c1g1=kp1b && kp2b && pimg;
TCut c1g2=kp1b && kp2g && pimb;
TCut c1g3=kp1g && kp2b && pimb;

TCut c2g1=kp1g && kp2g && pimb;
TCut c2g2=kp1g && kp2b && pimg;
TCut c2g3=kp1b && kp2g && pimg;

TCut c0g = kp1b && kp2b && pimb;
TCut c1g = c1g1 || c1g2 || c1g3;
TCut c2g = c2g1 || c2g2 || c2g3;
TCut c3g = kp1g && kp2g && pimg;

TH1F *h0g=new TH1F("h0g","",200,-100,100);
TH1F *h1g=new TH1F("h1g","",200,-100,100);
TH1F *h2g=new TH1F("h2g","",200,-100,100);
TH1F *h3g=new TH1F("h3g","",200,-100,100);
TH1F *hall=new TH1F("hall","",200,-100,100);


TCanvas *c0=new TCanvas("c0","",1200,800);
newt->Draw("stvkp1>>h0g",c0g);
TCanvas *c1=new TCanvas("c1","",1200,800);
newt->Draw("stvkp1>>h1g",c1g);
TCanvas *c2=new TCanvas("c2","",1200,800);
newt->Draw("stvkp1>>h2g",c2g);
TCanvas *c3=new TCanvas("c3","",1200,800);
newt->Draw("stvkp1>>h3g",c3g);
TCanvas *c4=new TCanvas("c4","",1200,800);
newt->Draw("stvkp1>>hall");





// now to check the number of events in histogram

Float_t n0g,n1g,n2g,n3g,nall;
n0g=h0g->GetEntries();
n1g=h1g->GetEntries();
n2g=h2g->GetEntries();
n3g=h3g->GetEntries();
nall=hall->GetEntries();


// theese 2 numbers should be the same, and they are.
cout << n0g + n1g + n2g + n3g << endl;
cout << nall << endl;



cout << "percent of events with 3 good hits are: " << n3g/nall <<endl;
cout << "percent of events with 2 good hits are: " << n2g/nall <<endl;
cout << "percent of events with 1 good hits are: " << n1g/nall <<endl;


//------------------------------------------------------------------------------------------------
// so have determined that 66% of the events in skim have 3 good hits, and 29% have 2 good hits.
// now to look at the histograms with only 2 good hits

TCanvas *c5=new TCanvas("c5","",1200,800);
c5->Divide(3,0);
c5->cd(1);
newt->Draw("stvkp1",c2g);
c5->cd(2);
newt->Draw("stvkp2",c2g);
c5->cd(3);
newt->Draw("stvpim",c2g);


// for the events with 2 good hits want to see what particle is most often the bad one.

TH1F *h2gkp1=new TH1F("h2gkp1","",200,-100,100);
TH1F *h2gkp2=new TH1F("h2gkp2","",200,-100,100);
TH1F *h2gpim=new TH1F("h2gpim","",200,-100,100);
TCanvas *c5=new TCanvas("c5","",1200,800);
newt->Draw("stvkp1>>h2gkp1",c2g&&kp1b);
newt->Draw("stvkp1>>h2gkp2",c2g&&kp2b);
newt->Draw("stvkp1>>h2gpim",c2g&&pimb);

Float_t nkp1b,nkp2b,npimb;
nkp1b=h2gkp1->GetEntries();
nkp2b=h2gkp2->GetEntries();
npimb=h2gpim->GetEntries();
cout << " for 2 good hits the percent of events with kp1 is bad is: " << nkp1b/n2g <<endl;
cout << " for 2 good hits the percent of events with kp2 is bad is: " << nkp2b/n2g <<endl;
cout << " for 2 good hits the percent of events with pim is bad is: " << npimb/n2g <<endl;
cout << " a check: the follow number should be one:  " << (nkp1b + nkp2b + npimb) / n2g <<endl;
// the above found that about 47% of the bad hits are due to pim



//----------------------------------------------------------------------------------
// now to determine what present of the events have only 2 good tracks after doing various other cuts:


TCanvas *c6=new TCanvas("c6","",1200,800);
TH1F *h2gbasic=new TH1F("h2gbasic","",200,-100,100);
TH1F *h3gbasic=new TH1F("h3gbasic","",200,-100,100);
TH1F *hallbasic=new TH1F("hallbasic","",200,-100,100);

newt->Draw("stvkp1>>h2gbasic",newbasic && c2g);
newt->Draw("stvkp1>>h3gbasic",newbasic && c3g);
newt->Draw("stvkp1>>hallbasic",newbasic);

Float_t n2gbasic,n3gbasic,nallbasic;
n2gbasic=h2gbasic->GetEntries();
n3gbasic=h3gbasic->GetEntries();
nallbasic=hallbasic->GetEntries();


cout << "number of events with 2 good tracks left after mybasic cuts are applied are: " << n2gbasic << endl;
cout << "number of events with 3 good tracks left after mybasic cuts are applied are: " << n3gbasic << endl;
cout << "number of events total left after mybasic cuts are applied are: " << nallbasic << endl;
cout << "percent of events with 2 good hits for mybasic cut are: " << n2gbasic/nallbasic <<endl;
cout << "percent of events with 3 good hits for mybasic cut are: " << n3gbasic/nallbasic <<endl;




//TCanvas *c6=new TCanvas("c6","",1200,800);
//c6->Divide(3,2);
//c6->cd(1);

































/*
TCanvas *c0=new TCanvas("c0","",1200,800);
newt->Draw("stvkp1>>hgood","goodSTkp1==1&&gootSTkp2==1&&goodSTpim==1");
TCanvas *c1=new TCanvas("c1","",1200,800);
newt->Draw("stvkp1>>hbad","goodSTkp1==0&&gootSTkp2==0&&goodSTpim==0");
TCanvas *c2=new TCanvas("c2","",1200,800);
newt->Draw("stvkp1>>hall");
*/


//goodSTkp1");


}















