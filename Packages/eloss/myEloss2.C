void myEloss2(){

TFile *_file0 = TFile::Open("./reserve/short_ppm_2.root");

Float_t mp=0.93827; 

 TCut misE="abs(miss4v_E)<0.025";
 TCut fit="Fit_Prob>0.1";
 TCut misp="abs(miss4v_px)<0.025&&abs(miss4v_py)<0.025&&abs(miss4v_pz)<0.025";



  // correct E divided by measured E is R.  R for all runs in this root file.
TCanvas *c0 = new TCanvas("c0", "c0",11,48,1123,536);
TH1F *h1=new TH1F("h1", "", 100, 0.95,1.05) ;
 ntp->Draw(Form("(( -mpi1pim*mpi1pim + 2*%f*(pim_E+pi1_E) )/( 2*( %f - (pim_E+pi1_E) + (pim_pz + pi1_pz) ) ))/beamE>>h1",mp,mp),fit&&misE );


 //R vs RUN
TCanvas *c1 = new TCanvas("c1", "c1",11,48,1123,536);
 TH2F *s1=new TH2F("s1", "", 100,56300,57000,100, 0.95,1.05) ;
 ntp->Draw(Form("((( -mpi1pim*mpi1pim + 2*%f*(pim_E+pi1_E) )/( 2*( %f - (pim_E+pi1_E) + (pim_pz + pi1_pz) ) ))/beamE):RUN>>s1",mp,mp),fit&&misp,"colz" );



 //***************i want to match the proton mass distribution on the g12 wiki*************


 // this should give the mass of the proton
TCanvas *c2 = new TCanvas("c2", "c2",11,48,1123,536);
 ntp->Draw(Form("sqrt(( %f*%f + mpi1pim*mpi1pim + 2*%f*( beamE - pim_E - pi1_E) - 2*beamE*(pim_pz + pi1_pz) ))",mp,mp,mp),fit&&misE );


 // this should also give the mass of the proton, energy must have been calculated by momentum.
TCanvas *c3 = new TCanvas("c3", "c2",11,48,1123,536);
 ntp->Draw("sqrt((proton_E*proton_E - proton_px*proton_px - proton_py*proton_py - proton_pz*proton_pz)) ",fit&&misE );


}
