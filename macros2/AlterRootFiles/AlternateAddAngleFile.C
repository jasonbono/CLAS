/* 


MARCH 2 2012:  CREATED THIS MACRO STARTING FROM g12nxyz_AddAngles.C.  the point of this was to make a final macro which would add all three angles and match with the angles 
calculated by the analyzer.  there were three main goals:

1) change the naming conventions of the axies to conform with bradford.
2) correct the way that the inplane (x & z) angles are computed.
3) clean up the code and make it easier to read


*/



#include <Riostream.h>
#include <TMath.h>
#include "TMath.h"
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TRotation.h>
#include <TLorentzRotation.h>
#include <assert.h>
gSystem.Load("libPhysics.so");

void AlternateAddAngleFile(TString passed)
{



	string input(passed);
	string filename = input.substr(0,input.find_last_of("."));
	string extention = input.substr(input.find_last_of("."));
	string tackon("_cm");
	string output = filename + tackon + extention;
	cout <<"input = "<< input <<"   output = " <<output<<endl;


	//string treename("gpp2kppim");
	string treename("v15");
	TFile *file = TFile::Open(input.c_str());  
	TTree *tOriginal = (TTree*)file->Get(treename.c_str()); 
	TFile *fileNew = new TFile(output.c_str(),"RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = treename.c_str();

// TFile *file = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v14/test.root");
// TTree *tOriginal = (TTree*)file->Get("v14");

 //four vectors
 TLorentzVector Fb;
 TLorentzVector Fpr;
 TLorentzVector Fk1;
 TLorentzVector Fk2;
 TLorentzVector Fcas;
 TLorentzVector Fpi;
 TLorentzVector Fl;
 TLorentzVector Fcm; 
 TLorentzVector Fkpkp;
 TLorentzVector Fnegcas;
 TLorentzVector FcasPDG;
 TLorentzVector FlPDG;

 //lab frame
 TVector3 Tb;
 TVector3 Tpr;
 TVector3 Tk1;
 TVector3 Tk2;
 TVector3 Tcas;
 TVector3 Tpi;
 TVector3 Tl;
 TVector3 Tcm;  
 TVector3 Tkpkp;
 TVector3 Tnegcas;
 TVector3 TlPDG;

 //center of mass frame 
 TVector3 TbCM;
 TVector3 TprCM;
 TVector3 Tk1CM;
 TVector3 Tk2CM;
 TVector3 TcasCM;
 TVector3 TpiCM;
 TVector3 TlCM;
 TVector3 TcmCM;
 TVector3 TkpkpCM;
 TVector3 TnegcasCM;
  TVector3 TlPDGCM;

 //Xi rest frame
 TVector3 TbCAS;
 TVector3 TprCAS;
 TVector3 Tk1CAS;
 TVector3 Tk2CAS;
 TVector3 TcasCAS;
 TVector3 TpiCAS;
 TVector3 TlCAS;
 TVector3 TcmCAS;
 TVector3 TkpkpCAS;
 TVector3 TnegcasCAS;
 TVector3 TlPDGCAS;

 //components of momentum
 Float_t Xb;
 Float_t Yb;
 Float_t Zb;
 Float_t Xpr;
 Float_t Ypr;
 Float_t Zpr;
 Float_t Xk1;
 Float_t Yk1;
 Float_t Zk1;
 Float_t Xk2;
 Float_t Yk2;
 Float_t Zk2;
 Float_t Xcas;
 Float_t Ycas;
 Float_t Zcas;
 Float_t Xpi;
 Float_t Ypi;
 Float_t Zpi;
 Float_t Xl;
 Float_t Yl;
 Float_t Zl; 
 
 //masses of particles
 Float_t Mb=0.0;
 Float_t Mpr=0.938272;
 Float_t Mk=0.493667;
 Float_t Mcas=1.32131;
 Float_t Mpi=0.13957;
 Float_t Ml=1.115683;      
 
 //Boost vectors 
 TVector3 Bcas;
 TVector3 Bcm;

 //out of production plane vectors, theese two should be equal
 TVector3 LABnorm;
 TVector3 CMnorm;

 // create branch varables
 Float_t beam;
 Float_t pkp1;
 Float_t kp1labtheta;
 Float_t kp1labphi;
 Float_t pkp2;
 Float_t kp2labtheta;
 Float_t kp2labphi;
 Float_t ppim;
 Float_t pilabtheta;
 Float_t pilabphi;




 // set prexisiting branch varables
 tOriginal->SetBranchAddress("beam", &beam);
 tOriginal->SetBranchAddress("pkp1", &pkp1);
 tOriginal->SetBranchAddress("kp1labtheta", &kp1labtheta);
 tOriginal->SetBranchAddress("kp1labphi", &kp1labphi);
 tOriginal->SetBranchAddress("pkp2", &pkp2);
 tOriginal->SetBranchAddress("kp2labtheta", &kp2labtheta);
 tOriginal->SetBranchAddress("kp2labphi", &kp2labphi);
 tOriginal->SetBranchAddress("ppim", &ppim);
 tOriginal->SetBranchAddress("pilabtheta", &pilabtheta);
 tOriginal->SetBranchAddress("pilabphi", &pilabphi);
 //if it was already added from the analyzer
 Float_t COS_pi_x;
 Float_t COS_pi_y; 
 Float_t COS_pi_z;
 tOriginal->SetBranchAddress("COS_pi_x", &COS_pi_x);
 tOriginal->SetBranchAddress("COS_pi_y", &COS_pi_y);
 tOriginal->SetBranchAddress("COS_pi_z", &COS_pi_z);

 // the new branches are the angles, plus some tests
 Float_t mr_COS_pi_x, mr_COS_pi_y, mr_COS_pi_z;
 Float_t mr_COS_lam_x, mr_COS_lam_y, mr_COS_lam_z;
 Float_t cm_COS_pi_x, cm_COS_pi_y, cm_COS_pi_z;
 Float_t cm_COS_lam_x, cm_COS_lam_y, cm_COS_lam_z;
 Float_t lab_COS_pi_x, lab_COS_pi_y, lab_COS_pi_z;
 Float_t lab_COS_lam_x, lab_COS_lam_y, lab_COS_lam_z;


 //setting the branches for adding
 TBranch *mr_COS_pi_xBranch = tNew->Branch("mr_COS_pi_x", &mr_COS_pi_x, "mr_COS_pi_x/F");
 TBranch *mr_COS_pi_yBranch = tNew->Branch("mr_COS_pi_y", &mr_COS_pi_y, "mr_COS_pi_y/F");
 TBranch *mr_COS_pi_zBranch = tNew->Branch("mr_COS_pi_z", &mr_COS_pi_z, "mr_COS_pi_z/F");
 TBranch *cm_COS_pi_xBranch = tNew->Branch("cm_COS_pi_x", &cm_COS_pi_x, "cm_COS_pi_x/F");
 TBranch *cm_COS_pi_yBranch = tNew->Branch("cm_COS_pi_y", &cm_COS_pi_y, "cm_COS_pi_y/F");
 TBranch *cm_COS_pi_zBranch = tNew->Branch("cm_COS_pi_z", &cm_COS_pi_z, "cm_COS_pi_z/F");









 TVector3 UnitVecZ;
 TVector3 UnitVecY;
 TVector3 UnitVecX;
 TVector3 UnitVecZ_cm;
 TVector3 UnitVecY_cm;
 TVector3 UnitVecX_cm;
 TVector3 UnitVecZ_cas;
 TVector3 UnitVecY_cas;
 TVector3 UnitVecX_cas;




 //begin the loop
 Int_t nentries = (Int_t)tOriginal->GetEntries(); 
 for (Int_t i=0; i<nentries; i++) 
 {
	
  		if(i % 10==0) { 
		// do a cout every every 10 entries
		 Float_t tempi = i;
		 Float_t tempN = nentries;
	     cout <<"nentires is" << nentries << "   i=" << i <<"  have completed  " << (tempi/tempN)*100 << "% of the job" << endl;
  }	
	
  tOriginal->GetEntry(i);


  //---------------------------------------------------------------------FILL 3&4 VECTORS-------------------------------------------------------------
  //PHOTON 3&4-vec 
  Xb=0;
  Yb=0;
  Zb=beam; 
  Tb.SetXYZ(Xb,Yb,Zb);
  Fb.SetXYZM(Tb(0),Tb(1),Tb(2),Mb);

  //PROTON 3&4-vec
  Xpr=0;
  Ypr=0;
  Zpr=0;
  Tpr.SetXYZ(Xpr,Ypr,Zpr);
  Fpr.SetXYZM(Tpr(0),Tpr(1),Tpr(2),Mpr);

  //KAON1 3&4-vec
  Xk1=pkp1*sin(TMath::ACos(kp1labtheta))*cos(kp1labphi*TMath::Pi());
  Yk1=pkp1*sin(TMath::ACos(kp1labtheta))*sin(kp1labphi*TMath::Pi());
  Zk1=pkp1*kp1labtheta;
  Tk1.SetXYZ(Xk1,Yk1,Zk1);
  Fk1.SetXYZM(Tk1(0),Tk1(1),Tk1(2),Mk);

  //KAON2 3&4-vec
  Xk2=pkp2*sin(TMath::ACos(kp2labtheta))*cos(kp2labphi*TMath::Pi());
  Yk2=pkp2*sin(TMath::ACos(kp2labtheta))*sin(kp2labphi*TMath::Pi());
  Zk2=pkp2*kp2labtheta;
  Tk2.SetXYZ(Xk2,Yk2,Zk2);
  Fk2.SetXYZM(Tk2(0),Tk2(1),Tk2(2),Mk);

  //kp1+kp2 3&4-vec
  Tkpkp.SetXYZ(Xk1 + Xk2, Yk1 + Yk2, Zk1 + Zk2);
  Fkpkp.SetPxPyPzE( Fk1(0) + Fk2(0) , Fk1(1) + Fk2(1), Fk1(2) + Fk2(2), Fk1(3) + Fk2(3) );

  //CASCADE 3&4-vec: try unconstraining the mass since the kaons are constrained.
  Tcas.SetXYZ(Tb(0)+Tpr(0)-Tk1(0)-Tk2(0), Tb(1)+Tpr(1)-Tk1(1)-Tk2(1), Tb(2)+Tpr(2)-Tk1(2)-Tk2(2));
  Fcas.SetPxPyPzE(Tcas(0), Tcas(1), Tcas(2), Fb.Energy() + Fpr.Energy() - Fk1.Energy() - Fk2.Energy() );
  FcasPDG.SetXYZM(Tcas(0), Tcas(1), Tcas(2), Mcas);

  //PION 3&4-vec
  Xpi=ppim*sin(TMath::ACos(pilabtheta))*cos(pilabphi*TMath::Pi());
  Ypi=ppim*sin(TMath::ACos(pilabtheta))*sin(pilabphi*TMath::Pi());
  Zpi=ppim*pilabtheta;
  Tpi.SetXYZ(Xpi,Ypi,Zpi);
  Fpi.SetXYZM(Tpi(0),Tpi(1),Tpi(2),Mpi);


  //CENTER OF MASS 4 vec
  Fcm.SetPxPyPzE(Fb(0)+Fpr(0),Fb(1)+Fpr(1),Fb(2)+Fpr(2),Fb(3)+Fpr(3));




//===============================================================================BOOSTS======================================================================================



  //boost to cm
  Bcm = -Fcm.BoostVector();
  Fpi.Boost(Bcm);
  Fb.Boost(Bcm);
  Fkpkp.Boost(Bcm);
  FcasPDG.Boost(Bcm);
	//fill cm three vectors
  	TpiCM.SetXYZ(Fpi(0), Fpi(1), Fpi(2));
  	TbCM.SetXYZ(Fb(0), Fb(1), Fb(2));
  	TkpkpCM.SetXYZ(Fkpkp(0), Fkpkp(1), Fkpkp(2));
	//boost to xi
	BcasPDG = -FcasPDG.BoostVector();
    Fpi.Boost(BcasPDG);
  	Fb.Boost(BcasPDG);
  	Fkpkp.Boost(BcasPDG);
		//fill xi three vectors
  		TpiCAS.SetXYZ(Fpi(0), Fpi(1), Fpi(2));
  		TbCAS.SetXYZ(Fb(0), Fb(1), Fb(2));
  		TkpkpCAS.SetXYZ(Fkpkp(0), Fkpkp(1), Fkpkp(2));
	//boost back to cm
  // 	Fpi.Boost(-Bcas);
  // 	Fb.Boost(-Bcas);
  // 	Fkpkp.Boost(-Bcas);
  // 
  // 
  // //boost back to lab
  // Fpi.Boost(-Bcm);
  // Fb.Boost(-Bcm);
  // Fkpkp.Boost(-Bcm);
  // FcasPDG.Boost(-Bcm);


//================================================================= define the coordinate system==========================================================================
  //lab coordinates
  UnitVecZ = (Tb);
  UnitVecZ = UnitVecZ.Unit();
  UnitVecY = Tb.Cross(Tkpkp);
  UnitVecY = UnitVecY.Unit();
  UnitVecX = UnitVecY.Cross(UnitVecZ);
  UnitVecX.Unit();
  // cout << "UnitVecX.X() = "<<UnitVecX.X() << "  UnitVecX.Y() = "<<UnitVecX.Y()  << "  UnitVecX.Z() = "<<UnitVecX.Z() <<endl;
  // cout << "UnitVecY.X() = "<<UnitVecY.X() << "  UnitVecY.Y() = "<<UnitVecY.Y()  << "  UnitVecY.Z() = "<<UnitVecY.Z() <<endl;
  // cout << "UnitVecZ.X() = "<<UnitVecZ.X() << "  UnitVecZ.Y() = "<<UnitVecZ.Y()  << "  UnitVecZ.Z() = "<<UnitVecZ.Z() <<endl;


 //CM coordinates
  UnitVecZ_cm = (TbCM);
  UnitVecZ_cm = UnitVecZ_cm.Unit();
  UnitVecY_cm = TbCM.Cross(TkpkpCM);
  UnitVecY_cm = UnitVecY_cm.Unit();
  UnitVecX_cm = UnitVecY_cm.Cross(UnitVecZ_cm);
  UnitVecX_cm.Unit();
  // cout << "UnitVecX_cm.X() = "<<UnitVecX_cm.X() << "  UnitVecX_cm.Y() = "<<UnitVecX_cm.Y()  << "  UnitVecX_cm.Z() = "<<UnitVecX_cm.Z() <<endl;
  // cout << "UnitVecY_cm.X() = "<<UnitVecY_cm.X() << "  UnitVecY_cm.Y() = "<<UnitVecY_cm.Y()  << "  UnitVecY_cm.Z() = "<<UnitVecY_cm.Z() <<endl;
  // cout << "UnitVecZ_cm.X() = "<<UnitVecZ_cm.X() << "  UnitVecZ_cm.Y() = "<<UnitVecZ_cm.Y()  << "  UnitVecZ_cm.Z() = "<<UnitVecZ_cm.Z() <<endl;


  //gotfried jackson coordinates
  UnitVecZ_cas = (TbCAS);
  UnitVecZ_cas = UnitVecZ_cas.Unit();
  UnitVecY_cas = TbCAS.Cross(TkpkpCAS);
  UnitVecY_cas = UnitVecY_cas.Unit();
  UnitVecX_cas = UnitVecY_cas.Cross(UnitVecZ_cas);
  UnitVecX_cas.Unit();
  // cout << "UnitVecX_cas.X() = "<<UnitVecX_cas.X() << "  UnitVecX_cas.Y() = "<<UnitVecX_cas.Y()  << "  UnitVecX_cas.Z() = "<<UnitVecX_cas.Z() <<endl;
  // cout << "UnitVecY_cas.X() = "<<UnitVecY_cas.X() << "  UnitVecY_cas.Y() = "<<UnitVecY_cas.Y()  << "  UnitVecY_cas.Z() = "<<UnitVecY_cas.Z() <<endl;
  // cout << "UnitVecZ_cas.X() = "<<UnitVecZ_cas.X() << "  UnitVecZ_cas.Y() = "<<UnitVecZ_cas.Y()  << "  UnitVecZ_cas.Z() = "<<UnitVecZ_cas.Z() <<endl;
//==============================================================================THE ANGLES================================================================================
  //lab pion angles:
  // lab_COS_pi_x = cos(UnitVecX.Angle(TpiCAS));
  // lab_COS_pi_y = cos(UnitVecY.Angle(TpiCAS));
  // lab_COS_pi_z = cos(UnitVecZ.Angle(TpiCAS));
  // cout <<" lab_COS_pi_x "<< lab_COS_pi_x <<"  COS_pi_x "<< COS_pi_x << " lab diff=" << COS_pi_x - lab_COS_pi_x <<endl;
  // cout <<" lab_COS_pi_y "<< lab_COS_pi_y <<"  COS_pi_y "<< COS_pi_y << " lab diff=" << COS_pi_y - lab_COS_pi_y <<endl;
  // cout <<" lab_COS_pi_z "<< lab_COS_pi_z <<"  COS_pi_z "<< COS_pi_z << " lab diff=" << COS_pi_z - lab_COS_pi_z <<endl;


  //cm pion angles:
  cm_COS_pi_x = cos(UnitVecX.Angle(TpiCAS));
  cm_COS_pi_y = cos(UnitVecY.Angle(TpiCAS));
  cm_COS_pi_z = cos(UnitVecZ.Angle(TpiCAS));
  cout <<" cm_COS_pi_x "<< cm_COS_pi_x <<"  COS_pi_x "<< COS_pi_x << " cm diff=" << COS_pi_x - cm_COS_pi_x <<endl;
  cout <<" cm_COS_pi_y "<< cm_COS_pi_y <<"  COS_pi_y "<< COS_pi_y << " cm diff=" << COS_pi_y - cm_COS_pi_y <<endl;
  cout <<" cm_COS_pi_z "<< cm_COS_pi_z <<"  COS_pi_z "<< COS_pi_z << " cm diff=" << COS_pi_z - cm_COS_pi_z <<endl;



  //gotfriend jackson pion angles:
  mr_COS_pi_x = cos(UnitVecX_cas.Angle(TpiCAS));
  mr_COS_pi_y = cos(UnitVecY_cas.Angle(TpiCAS));
  mr_COS_pi_z = cos(UnitVecZ_cas.Angle(TpiCAS));
  cout <<" mr_COS_pi_x "<< mr_COS_pi_x <<"  COS_pi_x "<< COS_pi_x << "  diff=" << COS_pi_x - mr_COS_pi_x <<endl;
  cout <<" mr_COS_pi_y "<< mr_COS_pi_y <<"  COS_pi_y "<< COS_pi_y << "  diff=" << COS_pi_y - mr_COS_pi_y <<endl;
  cout <<" mr_COS_pi_z "<< mr_COS_pi_z <<"  COS_pi_z "<< COS_pi_z << "  diff=" << COS_pi_z - mr_COS_pi_z <<endl;



  //cout <<i<<endl;
  //cout <<endl;

//==============================================================================FILL THE BRANCHES AND END=======================================================================




  tNew->Fill();



  }

 //fill the Basic tree
 cout <<"Filling the Basic tree" <<endl; 
 tNew->Write(tNewName);
 gROOT->ProcessLine(".q");
}
