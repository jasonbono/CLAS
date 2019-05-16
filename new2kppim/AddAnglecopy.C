
#ifndef __CINT__
#include <Riostream.h>
#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TRotation.h>
#include <TLorentzRotation.h>
#include <assert.h>
#endif



void AddAngle(){

  TFile *f = new TFile("pdstB.root", "UPDATE");
  TTree *dimuons = (TTree*)f->Get("dimuons");
  Float_t Tr0_Px;
  Float_t Tr0_Py;
  Float_t Tr0_Pz;
  Float_t Tr1_Px;
  Float_t Tr1_Py;
  Float_t Tr1_Pz;cd


  //BDM: BeamDecayNorm
  Float_t costhBDN;

  gSystem->Load("libPhysics");
  Double_t Muon_Mass = 0.105658367;





  dimuons->SetBranchAddress("Tr0_px", &Tr0_Px);
  dimuons->SetBranchAddress("Tr0_py", &Tr0_Py);
  dimuons->SetBranchAddress("Tr0_pz", &Tr0_Pz);
  dimuons->SetBranchAddress("Tr1_px", &Tr1_Px);
  dimuons->SetBranchAddress("Tr1_py", &Tr1_Py);
  dimuons->SetBranchAddress("Tr1_pz", &Tr1_Pz);
  TBranch *costhBDNBranch = dimuons->Branch("costhBDN", &costhBDN, "costhBDN/F");




\
  TH1F *a5=new TH1F("a5", "", 100,-1,1);

  Int_t nentries = (Int_t)dimuons->GetEntries();
  for (Int_t i=0; i<nentries; i++) {
    dimuons->GetEntry(i);



    TVector3 u1, u0;
    TVector3 beam;
    TVector3 norm;


    beam.SetXYZ(0,0,100);




    u0.SetXYZ(Tr0_Px, Tr0_Py, Tr0_Pz);
    u1.SetXYZ(Tr1_Px, Tr1_Py, Tr1_Pz);
    norm = u0.Cross(u1);
    Double_t angleBeamDecayNorm;
    angleBeamDecayNorm = beam.Angle(norm);



    costhBDN = cos(angleBeamDecayNorm);

    a5->Fill(costhBDN);

    costhBDNBranch->Fill();

 }


  dimuons->Write("", TObject::kOverwrite);



}
