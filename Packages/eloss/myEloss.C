// NOV 1 2011 jason bono
// made to find the corrected energy holding the proton mass constant
// see calculation in my paper labbook for NOV 1 


void myEloss(){

TFile *_file0 = TFile::Open("./reserve/short_ppm_2.root");

Float_t mp=0.938; 



//ntp->Draw(Form("%f*%f",mp,mp));

//ntp->Draw(Form("( -wo_mpi1pim*wo_mpi1pim + 2*%f*(wo_pim_E+wo_pi1_E) )/( 2*( %f - (wo_pim_E+wo_pi1_E)  )",mp,mp));

 TH1F *h=new TH1F("h","",500,0.5,3);
 TH1F *h0=new TH1F("h0","",500,0.5,3);
 //TH1F *h=new TH1F("h", "", 100, 1.2, 1.7)



 TCanvas *c=new TCanvas("c","c",1200,800); 
 c->Divide(2,1);
 c->cd(1);
 ntp->Draw(Form("( -wo_mpi1pim*wo_mpi1pim + 2*%f*(wo_pim_E+wo_pi1_E) )/( 2*( %f - (wo_pim_E+wo_pi1_E) + (wo_pim_pz + wo_pi1_pz) ) )>>h",mp,mp));
 c->cd(2);
 ntp->Draw(Form("gammas_E>>h0",mp,mp));



ntp->Draw(Form("( -mpi1pim*mpi1pim + 2*%f*(pim_E+pi1_E) )/( 2*( %f - (pim_E+pi1_E) + (pim_pz + pi1_pz) ) )>>h",mp,mp));


}
