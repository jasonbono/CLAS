/*

nov 22 2011:

this was made to show the first results of the n angles with side band subtraction.
first will develop it without errors, then will add those later.

the sideband subtraction parameters came from the sigma produced by g12finalmplot.C which is

sigma_cas = 0.0145 -> sig*3=0.0435
sigma_lam = 0.0146 -> sig*3=0.0438 

here will do a cut on both, then sideband subtract on only one at a time.  
for the first go, i will sideband subtract for the lambda.


 */



void nangle(){
//TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
//TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");
//TTree *newt = (TTree*)f->Get("g12ana_v15");
TFile *f = TFile::Open("~/clas/rootfiles/g12/large/g12ana_v16_58090.root");
TTree *newt = (TTree*)f->Get("g12ana_v16");


gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS.C");


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


 //++++++++++++++++++++++++++++++the sideband cuts++++++++++++++++++++++++++++++++++
 // note im going to redifine the lambda and cascade cut here to sig*3=0.0435
 // 0.0435 for cascade
 // 0.0438 for lambda
 TCut lam3="abs(sqrt(mm2kpkppim)-1.116)<0.0438";
 TCut cas3="abs(sqrt(mm2kpkp) - 1.321)<0.0435";


 TCut lamSidebands="abs(sqrt(mm2kpkppim)- 1.1817)<0.0219||abs(sqrt(mm2kpkppim)- 1.0503)<0.0219";
 TCut lamTherest="abs(sqrt(mm2kpkppim)- 1.116)>0.0876";


 //and the side bands are defined:
 // 1.116+6*sigma=1.116+0.0876=1.2036
 // 1.116-0.0876=1.0284
 //TCut lamSidebands="abs(sqrt(mm2kpkppim)-1.2036)<0.0438||abs(sqrt(mm2kpkppim)-1.0284)<0.0438";
//want to have normalized side bands so use 1.2036 - 0.01095 & 1.0284 + 0.01095 = 1.19265 & 1.03935
//TCut lamSidebands="abs(sqrt(mm2kpkppim)- 1.19265)<0.0219||abs(sqrt(mm2kpkppim)- 1.03935)<0.0219";

//--------------------------------------------------------------------------------------------






//==========================================angles for sideband subtraction on lambda===================================


//----------------------------------------------------the missing mass--------------------------------
 TCanvas *c0=new TCanvas("c0","",1200,800);
 c0->Divide(2,1);
 c0_2->Divide(1,2);
 c0->cd(1); 

//need bin boundary to be on 1.0722 AND 1.1598 which gives a width of 0.0876.
// want close to 10Mev bins which means binwidth of 0.01 or more:
// so can fit in close 8 bins into the 0.0876 inverval; 0.0876/8=0.01095=BINWIDTH
// now want range to be close to 0.9-1.3: so want:
// 0.9 + x= 1.0722 - n*0.01095 :: try to minimize |x|, with n an integer
// -> x = 0.1722 - n*0.01095 =>  minimizing |x| means finding the n such that |x| is minimum:
// well 0.1722/0.01095 = 15.726...  so can thus choose n=16 and have
//x=  0.1722 - 0.16425 = 0.00795:
// so can bin starting at 0.90795 and have the number of bins close to
// b*0.01095 = 1.3 - 0.9 => b=37 is the closest integer
// now to find the range take xmax= 0.90795 + 37*=0.01095=1.3131



//well 1.1598





 TH1F *hlam=new TH1F("hlam","",37, 0.90795,1.3131);
 TH1F *hlamS = (TH1F*)hlam->Clone("hlamS");
 //TH1F *hlamALL = (TH1F*)hlam->Clone("hlamALL");
 newt->Draw("sqrt(mm2kpkppim)>>hlam",newbasic&&casm&&lam3);
 // TH1F *hlamS=new TH1F("hlamS","",40,0.9,1.3);
 newt->Draw("sqrt(mm2kpkppim)>>hlamS",newbasic&&casm&&lamSidebands);
 hlamS->SetFillStyle(3004);
 TH1F *hlamALL=new TH1F("hlamALL","",37,0.90795,1.3131);
 newt->Draw("sqrt(mm2kpkppim)>>hlamALL",newbasic&&casm&&lamTherest);
 
 hlam->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 hlam->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
 //hlamALL->SetFillColor(3);
 //hlamALL->Draw();
 /// hlam->SetFillColor(4);
 hlam->Draw("E");
 hlamS->SetFillColor(2);
 hlamS->SetFillStyle(3004);
 hlamS->Draw("same"); 
 hlamALL->Draw("samee");

 // the below fitting routine showed that the number of backround events are 176
 //fitGAUS(hlamALL,1,1,1.2,1,1,1,1.116,0.05,3);

 //--------------------now for some normalization---------------------------
 Float_t nside= hlamS->GetEntries();
 Float_t nback=176;
 cout <<"nside is: "<< nside << "   number in backround is : " <<nback<<endl;
 // so the number of events in the sides are 150, and want to match this to 176
 

 //----------------------------------------------------the angles overlay-------------------------------------------- 

 //====================================for the right hand plots=======================
 printf("Welcome to the ROOT\n");
 gStyle->SetTitleXOffset(0.85);  //this: Xoff
 gStyle->SetTitleYOffset(0.75);  //this:  Yoff
 gStyle->SetTitleSize(0.08);  //this:    Xsize   
 gStyle->SetTitleYSize(0.08); //this     Ysize
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






 c0_2->cd(1);
 TH1F *hn=new TH1F("hn","",10,-1,1); 
 hn->SetMinimum(0);
 newt->Draw("cos(PIangle)>>hn",newbasic&&casm&&lam3);
 TH1F *hnS=new TH1F("hnS","",10,-1,1); 
 TH1F *hnSnorm = (TH1F*)hnS->Clone("hnSnorm");
 hnS->SetMinimum(0);
 newt->Draw("cos(PIangle)>>hnS",newbasic&&casm&&lamSidebands);


 //176/150=1.1733333333...
 hnSnorm->Add(hnS, 1.17333);
 cout<<"number here should be 176  "<< hnSnorm->GetEntries() <<endl;
 hn->GetYaxis()->SetTitle("Events");  
 hn->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}})");   

 
 // hn->SetFillColor(4);
  hn->Draw();
  hnSnorm->SetFillColor(2);
  hnSnorm->SetFillStyle(3004);
  hnSnorm->Draw("SAME"); 



 //-----------------------------------------------the subtracted hists-------------------------
  c0_2->cd(2);
  // TH1F *hntotal = (TH1F*)hn->Clone("hntotal");
  TH1F *hntotal=new TH1F("hntotal","",10,-1,1); 

  hntotal->Add(hn,1);
  hntotal->Add(hnSnorm,-1);
  hntotal->SetMinimum(0);
  //hntotal->SetFillColor(3);
  hntotal->Draw();
  hntotal->GetYaxis()->SetTitle("Events");
  hntotal->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}})");   



  //c0->Print("~/clas/pics/11_nov11/proposal/g12/nangles.eps");
  c0->Print("~/clas/pics/11_nov29/g12nangles.eps");




}
