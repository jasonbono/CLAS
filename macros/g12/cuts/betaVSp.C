





void betaVSp(){




//TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
//TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");
//TTree *newt = (TTree*)f->Get("g12ana_v15");
TFile *f = TFile::Open("~/clas/rootfiles/g12/large/reserve/g12ana_v16_58090.root");
TTree *newt = (TTree*)f->Get("g12ana_v16");



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

//==================================================NEW CUTS====================================================
TCut tof3="abs(vtime-(sctpim-sclpim/(betapim*29.99)))<0.4";








//--------------------------------------------------------------------------------------------------------------


// now b=p/e. e=sqrt(m^2 + p^2) => b^2 = (p^2) / (m^2 + p^2)

// the masses
Float_t mpim = 0.13957;  //note it is the same mass as pip
Float_t mkp = 0.49367;
Float_t mpr = 0.93827;



//----------------------------------now some tests--------------------------------------------

/*
// a test to compare diffrent calculated values of beta. plots 2 and 3 should be the same
TCanvas *ctest2=new TCanvas("ctest2","",1200,800);
ctest2 -> Divide(4,1);
ctest2 -> cd(1);
newt -> Draw(Form("pkp1/sqrt((pkp1*pkp1) + (%f*%f))" , mpim, mpim ));
ctest2 -> cd(2);
newt -> Draw(Form("pkp1/sqrt((pkp1*pkp1) + (%f*%f))" , mkp, mkp ));
ctest2 -> cd(3);
newt -> Draw("betakp1");
ctest2 -> cd(4);
newt -> Draw("tofbetakp1");


//looking at the range of pkp1,pkp2,ppim
TCanvas *ctest3=new TCanvas("ctest3","",1200,800);
ctest3 -> Divide(3,1);
ctest3 -> cd(1);
newt->Draw("pkp1");
ctest3 -> cd(2);
newt->Draw("pkp2");
ctest3 -> cd(3);
TH1F *testpim = new TH1F("testpim","",100,0,10);
newt->Draw("ppim>>testpim");
//this shows that there are little events with momentum (of kaons or pions) below 0.8 gev
*/


//-----------------------------------------------------------------------------------------------------



//making the histograms
TH2F *skp1[6];
TH2F *skp2[6];
TH2F *spim[6];
for( Int_t i=0;i<6;i++){
skp1[i]=new TH2F(Form("skp1_%d",i),"",200, 0, 4, 200, 0, 1.2);
skp2[i]=new TH2F(Form("skp2_%d",i),"",200, 0, 2.5, 200, 0, 1.2);
spim[i]=new TH2F(Form("spim_%d",i),"",200, 0, 1.0, 200, 0, 1.2);


skp1[i]->GetYaxis()->SetTitle("#beta");  
skp1[i]->GetXaxis()->SetTitle("p (GeV/c)");
skp2[i]->GetYaxis()->SetTitle("beta");  
skp2[i]->GetXaxis()->SetTitle("p (GeV/c)");
spim[i]->GetYaxis()->SetTitle("beta");  
spim[i]->GetXaxis()->SetTitle("p (GeV/c)");

skp1[i]->GetYaxis()->SetLabelSize(0.05);  
skp1[i]->GetXaxis()->SetLabelSize(0.05);

skp1[i]->GetXaxis()->CenterTitle();
skp1[i]->GetYaxis()->CenterTitle();
}


// now the functions
TF1 *fkaon = new TF1("fkaon","x/sqrt(x*x + 0.49367*0.49367)",0,4);
TF1 *fpion = new TF1("fpion","x/sqrt(x*x + 0.13957*0.13957)",0,1);
fkaon->SetLineWidth(2);
fpion->SetLineWidth(2);
fkaon->SetLineStyle(1);
fpion->SetLineStyle(1);
fkaon->SetLineColor(46);
fpion->SetLineColor(46);


//some cosmetics
gStyle->SetOptLogz(0);
gStyle->SetPalette(1);


//with no cuts
TCanvas *c0=new TCanvas("c0","no cuts",1200,800);
//c0->Divide(3,0);
//c0->cd(1);
newt->Draw("tofbetakp1:pkp1 >> skp1_0","","contz");
fkaon->Draw("same");
//c0->cd(2);
//newt->Draw("tofbetakp2:pkp2 >> skp2_0","","contz");
//fkaon->Draw("same");  
//c0->cd(3);
//newt->Draw("tofbetapim:ppim >> spim_0","","contz");
//fpion->Draw("same");


//with tof cuts
//TCanvas *c1=new TCanvas("c1","tof cuts",1200,800);
//c1->Divide(3,0);
//c1->cd(1);
//newt->Draw("tofbetakp1:pkp1 >> skp1_1",tof1,"contz");
//fkaon->Draw("same");
//c1->cd(2);
//newt->Draw("tofbetakp2:pkp2 >> skp2_1",tof2,"contz");
//fkaon->Draw("same");
//c1->cd(3);
//newt->Draw("tofbetapim:ppim >> spim_1",tof3,"contz");
//fpion->Draw("same");

//with st cuts
TCanvas *c2=new TCanvas("c2","st cuts",1200,800);
//c2->Divide(3,0);
//c2->cd(1);
newt->Draw("tofbetakp1:pkp1 >> skp1_2",st,"contz");
fkaon->Draw("same");
//c2->cd(2);
//newt->Draw("tofbetakp2:pkp2 >> skp2_2",st,"contz");
//fkaon->Draw("same");
//c2->cd(3);
//newt->Draw("tofbetapim:ppim >> spim_2",st,"contz");
//fpion->Draw("same");





//with st&& cuts
TCanvas *c3=new TCanvas("c3"," st&&tof ",1200,800);
//c3->Divide(3,0);
//c3->cd(1);
newt->Draw("tofbetakp1:pkp1 >> skp1_3",st&&tof1,"contz");
fkaon->Draw("same");
//c3->cd(2);
//newt->Draw("tofbetakp2:pkp2 >> skp2_3",st&&tof2,"contz");
//fkaon->Draw("same");
//c3->cd(3);
//newt->Draw("tofbetapim:ppim >> spim_3",st&&tof3,"contz");
//fpion->Draw("same");




//with st&&tof&&~ cuts
TCanvas *c4=new TCanvas("c4","st&&tof&&casm&&lamm",1200,800);
//c4->Divide(3,0);
//c4->cd(1);
newt->Draw("tofbetakp1:pkp1 >> skp1_4",st&&tof1&&casm&&lamm,"contz");
fkaon->Draw("same");
//c4->cd(2);
//newt->Draw("tofbetakp2:pkp2 >> skp2_4",st&&tof1&&tof2&&tof3&&casm&&lamm,"contz");
//fkaon->Draw("same");
//c4->cd(3);
//newt->Draw("tofbetapim:ppim >> spim_4",st&&tof1&&tof2&&tof3&&casm&&lamm,"contz");
//fpion->Draw("same");



//==========SHOW THE QUANTITIES THAT WERE CUT ON=================
TCanvas *cST=new TCanvas("cST"," st ",1200,800);

TH1F *hST = new TH1F("hST","",200,-1,10);
TH1F *hSTb = new TH1F("hSTb","",200,-1,10);

hST->GetYaxis()->SetTitle(" counts ");
hST->GetXaxis()->SetTitle("|STvtime - SCvtime|  (ns)");  
hST->GetYaxis()->SetLabelSize(0.05);  
hST->GetXaxis()->SetLabelSize(0.05);
hST->GetXaxis()->CenterTitle();
hST->GetYaxis()->CenterTitle();

newt->Draw("abs(stv-scv) >> hST");
newt->Draw("abs(stv-scv) >> hSTb",st);
hSTb -> SetFillColor(3);
hST -> Draw();
hSTb -> Draw("same");

//-----------------------------------------------------
TCanvas *cTOF=new TCanvas("cTof"," tof",1200,800);

TH1F *hTOF = new TH1F("hTOF","",200,-1,10);
TH1F *hTOFb = new TH1F("hTOFb","",200,-1,10);

hTOF->GetYaxis()->SetTitle(" counts ");
hTOF->GetXaxis()->SetTitle("|vtime-(sctKP-sclKP/VelocityKP|  (ns)");  
hTOF->GetYaxis()->SetLabelSize(0.05);  
hTOF->GetXaxis()->SetLabelSize(0.05);
hTOF->GetXaxis()->CenterTitle();
hTOF->GetYaxis()->CenterTitle();

newt->Draw("abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))>> hTOF");
newt->Draw("abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))>> hTOFb",tof1);
hTOFb -> SetFillColor(3);
hTOF -> Draw();
hTOFb -> Draw("same");













}



