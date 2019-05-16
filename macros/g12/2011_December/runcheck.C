

// December 1 2011:  this was created to look at stv:scv-stv surface plots


void runcheck(){
  TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
  //TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");
TTree *newt = (TTree*)f->Get("g12ana_v15");











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


TCut runs1=" run > 56360 && run < 56470 ";
TCut runs2=" run > 56470 && run < 56510 ";
TCut runs3=" run > 56510 && run < 56560 ";



	TCanvas *c0=new TCanvas("c0","",1200,800);
	TH1F *hcas1=new TH1F("hcas1","",50,1,1.6);
	TH1F *hcas2=new TH1F("hcas2","",50,1,1.6);
	TH1F *hcas3=new TH1F("hcas3","",50,1,1.6);
	c0->Divide(3,0);
	c0->cd(1);
	newt->Draw("sqrt(mm2kpkp)>>hcas1",newbasic&&lam&&runs1);
	c0->cd(2);
	newt->Draw("sqrt(mm2kpkp)>>hcas2",newbasic&&lam&&runs2);
	c0->cd(3);
	newt->Draw("sqrt(mm2kpkp)>>hcas3",newbasic&&lam&&runs3);
	
	
	TCanvas *c1=new TCanvas("c1","",1200,800);
	TH1F *hlam1=new TH1F("hlam1","",50,0.8,1.4);
	TH1F *hlam2=new TH1F("hlam2","",50,0.8,1.4);
	TH1F *hlam3=new TH1F("hlam3","",50,0.8,1.4);
	c1->Divide(3,0);
	c1->cd(1);
	newt->Draw("sqrt(mm2kpkppim)>>hlam1",newbasic&&cas&&runs1);
	c1->cd(2);
	newt->Draw("sqrt(mm2kpkppim)>>hlam2",newbasic&&cas&&runs2);
	c1->cd(3);
	newt->Draw("sqrt(mm2kpkppim)>>hlam3",newbasic&&cas&&runs3);
	
	
	TCanvas *c2=new TCanvas("c2","",1200,800);
	TH1F *hrun=new TH1F("hrun","",200,56360,56560);
	newt->Draw("run>>hrun");
	
	
}