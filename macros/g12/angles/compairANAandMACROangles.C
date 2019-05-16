






void compairANAandMACROangles(){



TFile *f = TFile::Open("~/clas/rootfiles/g12/v24k_small.root");
TTree *newt = (TTree*)f->Get("v24k");






//==========================================angles for sideband subtraction on lambda===================================


//----------------------------------------------------the missing mass--------------------------------




//hists for branches added by the analyzer
TH1F *hanaX=new TH1F("hanaX","",100, -1,1);
TH1F *hanaY=new TH1F("hanaY","",100, -1,1);
TH1F *hanaZ=new TH1F("hanaZ","",100, -1,1);


//hists for branches added by the macro
TH1F *hmroX=new TH1F("hmroX","",100, -1,1);
TH1F *hmroY=new TH1F("hmroY","",100, -1,1);
TH1F *hmroZ=new TH1F("hmroZ","",100, -1,1);




//the x axis
TCanvas *cX=new TCanvas("cX","X",1200,800);
cX->Divide(2,0);
cX->cd(1);
newt->Draw("COSth_pi_x >> hanaX");
cX->cd(2);
newt->Draw("PIanglex >> hmroX");





//the y axis
TCanvas *cY=new TCanvas("cY","Y",1200,800);
cY->Divide(2,0);
cY->cd(1);
newt->Draw("COSth_pi_y >> hanaY");
cY->cd(2);
newt->Draw("PIangle >> hmroY");



//the z axis
TCanvas *cZ=new TCanvas("cZ","Z",1200,800);
cZ->Divide(2,0);
cZ->cd(1);
newt->Draw("COSth_pi_z >> hanaZ");
cZ->cd(2);
newt->Draw("PIanglez >> hmroZ");




}

