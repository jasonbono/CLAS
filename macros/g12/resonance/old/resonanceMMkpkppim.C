/*

jan 9: changed the fitting routine to myfit2GAUS2 so that i could pass varibles through. here i passed 
the gaussian yield and the background yield.  i will probably not use the gauss yeild but i 
wanted to put through two variables as an example of how to do this beacus it is diffrent for only
one varible.  i also changed the name of this macro.

Jan 2 2012:  added a plot of mm(kpkp) and made it run for nearly the 

nov 23 2011: took this from mcas1690. it is just an improvment on cuts to get a clean cascade peak in the mmkpkppim spectrum



nov 22 2011:  this macro cuts on the cas0 in the mmkpkppim spectrum to search for resonances of casm at 1690 or 1620. 
cas(1530) is already well known.
note that the ground state of casm and cas0 are at 1321 and 1314 respetively 
so it should NOT be possible for the ground state of casm(1321)->cas0(1314)+pim(139) 


 So looking primaraly for: 
 casm(1690)->cas0(1314)+pim(139)


 */


void resonanceMMkpkppim(){
//TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");
TTree *newt = (TTree*)f->Get("g12ana_v15");
//TFile *f = TFile::Open("~/clas/rootfiles/g12/large/g12ana_v16_58090.root");
//TTree *newt = (TTree*)f->Get("g12ana_v16");
gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS2.C");


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

//=========================the most recent cuts as of nov22========================
//need to relax a few cuts here after showing lei my overlay plots.
 TCut n="np<2&&npip<1&&nkm<1";
 TCut np="nphoton_nb1<2";
 TCut vcut="abs(vz+90)<21&&sqrt(vx^2+vy^2)<8";  // relaxed this alot to allow for weak decays
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





 TCut tof22="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<0.5";
 TCut tof12="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.15"; // wont include tof1 cuts because it takes out to much signal.



 TCut cas0="abs(sqrt(mm2kpkppim) - 1.3137)<0.0381";
 TCut cas0sb="abs(sqrt(mm2kpkppim) - 1.25655)<0.01905  || abs(sqrt(mm2kpkppim) - 1.37085)<0.01905";


 //----------------------------------------------------------------------------------
 //newt->Draw(">>basiclist", newbasic);
 //TEventList *list=(TEventList *)gDirectory->Get("basiclist");
 //newt->SetEventList(list);
  



 //THE DECAY PRODUCT
 //*

 TCanvas *c0=new TCanvas("c0","",1200,800);
 TH1F *h0=new TH1F("h0","",35,1.15,1.5);
 TH1F *h0pk=new TH1F("h0pk","",350,1.15,1.5);
 TH1F *h0sb=new TH1F("h0sb","",350,1.15,1.5);
 h0->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h0->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
 h0pk->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h0pk->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
 h0sb->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h0sb->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 

//plot the cascade ground state spectra and fit it 
 newt->Draw("sqrt(mm2kpkppim)>>h0", newbasic&&"beam>3.6&&sqrt(mm2kpkp)>1.35&&(vx^2+vy^2)<3"&&tof22&&tof12);
 

 Double_t myBackground = 0.0;
 Double_t myYield = 0.0;
 fitGAUS(h0,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield);

cout << "=====================================================\n" 
	<< "My background: " << myBackground << endl
	<< "My Yield: " << myYield << endl;

// now seperatly overlay the peak and the side bands
 
 TCanvas *c00=new TCanvas("c00","",1200,800);
 newt->Draw("sqrt(mm2kpkppim)>>h0sb", newbasic&&"beam>3.6&&sqrt(mm2kpkp)>1.35&&(vx^2+vy^2)<3"&&tof22&&tof12&&cas0sb);
 newt->Draw("sqrt(mm2kpkppim)>>h0pk", newbasic&&"beam>3.6&&sqrt(mm2kpkp)>1.35&&(vx^2+vy^2)<3"&&tof22&&tof12&&cas0);
 h0pk->Draw();
 h0sb->SetFillColor(2);
 h0sb->SetFillStyle(3004);
 h0sb->Draw("same");

// from here need the quantity "yieldb" from myfit2GAUS.C 
// and want to get the number of entries in the sidebands
// this is for normalisation

 //Float_t nbg=yieldb
Float_t nbg=myBackground;
 Float_t nsb = h0sb->GetEntries();
 // nplot=nbg   nplot=nsb*f=nbg -> f=nbg/nsb so multiply the hist by f
 Float_t fac = nbg/nsb;

 //*/


 // THE SEARCHED RESONANCE 
//*
 //this bock shows the invarent mass spectrum of the pim + cascade0
 TCanvas *c1=new TCanvas("c1","",1200,800);
 TH1F *h1=new TH1F("h1","",60,1.4,2);
 TH1F *h1sb=new TH1F("h1sb","",60,1.4,2);
 h1->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h1->GetXaxis()->SetTitle("M(#pi^{-}#Xi^{0}) (GeV/c^{2})");  
 h1sb->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h1sb->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})");

 newt->Draw("mcaspim>>h1sb", newbasic&&"beam>3.6&&(vx^2+vy^2)<3"&&tof22&&tof12&&cas0sb);
 newt->Draw("mcaspim>>h1", newbasic&&"beam>3.6&&(vx^2+vy^2)<3"&&tof22&&tof12&&cas0,"e");

 TH1F *h1sbNorm=new TH1F("h1sbNorm","",60,1.4,2);
 h1sbNorm->Add(h1sb, 1.17333);
 h1sbNorm->SetFillColor(2);
 h1sbNorm->SetFillStyle(3004);
 h1sbNorm->Draw("same");



//*/// below here shows the missing mass spectrum of kp1 kp2
 TCanvas *c2=new TCanvas("c2","",1200,800);
 TH1F *h2=new TH1F("h2","",60,1.4,2);
 TH1F *h2sb=new TH1F("h2sb","",60,1.4,2);
 h2->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h2->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})");  
 h2sb->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h2sb->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})");

 newt->Draw("sqrt(mm2kpkp)>>h2sb", newbasic&&"beam>3.6&&(vx^2+vy^2)<3"&&tof22&&tof12&&cas0sb);
 newt->Draw("sqrt(mm2kpkp)>>h2", newbasic&&"beam>3.6&&(vx^2+vy^2)<3"&&tof22&&tof12&&cas0,"e");
 
 h2sb->SetFillColor(2);
 h2sb->SetFillStyle(3004);
 h2sb->Draw("same");



//*/





 //c0->Print("~/clas/pics/11_nov11/proposal/g12/resonanceMMkpkppim.eps");
 //c0->Print("~/clas/pics/11_nov29/resonanceMMkpkppim.eps");


}
