/* 
April 10 2012:  

March 27: added a branch to test the energy of the Xi and the pim+lambda system after the Xi boost to check the Xi boost.

March 11:  version 2: added options that specifies the file to add angles to and also outputs the % of progress done.

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


void Addxyz_acii2root()
{

 
 //
 TFile *f = TFile::Open("/Users/Bono/clas/simulation/g12/myXi/genr8/ascii2root/myXi_100k.root","UPDATE");  
 TTree *addedt = (TTree*)f->Get("FourVecTree2");


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
 Float_t kp1x,kp1y,kp1z,kp1t;
 Float_t pimx,pimy,pimz,pimt;
 Float_t lamx,lamy,lamz,lamt;	
 Float_t kp2x,kp2y,kp2z,kp2t;

 // set branch varables
 addedt->SetBranchAddress("beam", &beam);
 addedt->SetBranchAddress("kp1x",&kp1x);
 addedt->SetBranchAddress("kp1y",&kp1y);
 addedt->SetBranchAddress("kp1z",&kp1z);
 addedt->SetBranchAddress("kp1t",&kp1t);
 addedt->SetBranchAddress("pimx",&pimx);
 addedt->SetBranchAddress("pimy",&pimy);
 addedt->SetBranchAddress("pimz",&pimz);
 addedt->SetBranchAddress("pimt",&pimt);
 addedt->SetBranchAddress("lamx",&lamx);
 addedt->SetBranchAddress("lamy",&lamy);
 addedt->SetBranchAddress("lamz",&lamz);
 addedt->SetBranchAddress("lamt",&lamt);
 addedt->SetBranchAddress("kp2x",&kp2x);
 addedt->SetBranchAddress("kp2y",&kp2y);
 addedt->SetBranchAddress("kp2z",&kp2z);
 addedt->SetBranchAddress("kp2t",&kp2t);

 // the new branches are the angles, plus some tests
 Float_t mr_COS_pi_x, mr_COS_pi_y, mr_COS_pi_z;
 Float_t mr_COS_lam_x, mr_COS_lam_y, mr_COS_lam_z;
 Float_t mr_Energy_Xi, mr_Energy_lampim;


 //THIS IS TO COMPAIR THE RESULTS FOR WHEN THE PRODUCTION PLANE WAS DEFINED IN THE LAB FRAME
 Float_t mr_COS_pi_y_LAB;
 Float_t mr_COS_lam_y_LAB;


 //setting the branches for adding
 TBranch *mr_COS_pi_xBranch = addedt->Branch("mr_COS_pi_x", &mr_COS_pi_x, "mr_COS_pi_x/F");
 TBranch *mr_COS_pi_yBranch = addedt->Branch("mr_COS_pi_y", &mr_COS_pi_y, "mr_COS_pi_y/F");
 TBranch *mr_COS_pi_zBranch = addedt->Branch("mr_COS_pi_z", &mr_COS_pi_z, "mr_COS_pi_z/F");

 TBranch *mr_COS_lam_xBranch = addedt->Branch("mr_COS_lam_x", &mr_COS_lam_x, "mr_COS_lam_x/F");
 TBranch *mr_COS_lam_yBranch = addedt->Branch("mr_COS_lam_y", &mr_COS_lam_y, "mr_COS_lam_y/F");
 TBranch *mr_COS_lam_zBranch = addedt->Branch("mr_COS_lam_z", &mr_COS_lam_z, "mr_COS_lam_z/F"); 

 TBranch *mr_Energy_Xi_Branch = addedt->Branch("mr_Energy_Xi", &mr_Energy_Xi, "mr_Energy_Xi/F"); 
 TBranch *mr_Energy_lampim_Branch = addedt->Branch("mr_Energy_lampim", &mr_Energy_lampim, "mr_Energy_lampim/F"); 

 //begin the loop
 Int_t nentries = (Int_t)addedt->GetEntries(); 
 for (Int_t i=0; i<nentries; i++) 
 {
  addedt->GetEntry(i);

  //output the progress every 100 entries
  if(i % 100==0)
  {
   cout << "progress: " <<  (i*100)/nentries << " %  complete" << endl;
  }
  //---------------------------------------------------------------------FILL 3&4 VECTORS-------------------------------------------------------------
  //PHOTON 3&4-vec 
  Xb=0;
  Yb=0;
  Zb=beam; 
  Tb.SetXYZ(Xb,Yb,Zb);
  Fb.SetXYZM(Tb(0),Tb(1),Tb(2),Mb);

//cout << "Zb=" << Zb <<endl;

  //PROTON 3&4-vec
  Xpr=0;
  Ypr=0;
  Zpr=0;
  Tpr.SetXYZ(Xpr,Ypr,Zpr);
  Fpr.SetXYZM(Tpr(0),Tpr(1),Tpr(2),Mpr);

  //KAON1 3&4-vec
  Xk1=kp1x;
  Yk1=kp1y;
  Zk1=kp1z;
  Tk1.SetXYZ(Xk1,Yk1,Zk1);
  Fk1.SetXYZM(Tk1(0),Tk1(1),Tk1(2),Mk);
//cout << "Zk1=" << Zk1 <<endl;
  //KAON2 3&4-vec
  Xk2=kp2x;
  Yk2=kp2y;
  Zk2=kp2z;
  Tk2.SetXYZ(Xk2,Yk2,Zk2);
  Fk2.SetXYZM(Tk2(0),Tk2(1),Tk2(2),Mk);

  //kp1+kp2 3&4-vec
  Tkpkp.SetXYZ(Xk1 + Xk2, Yk1 + Yk2, Zk1 + Zk2);
  Fkpkp.SetPxPyPzE( Fk1(0) + Fk2(0) , Fk1(1) + Fk2(1), Fk1(2) + Fk2(2), Fk1(3) + Fk2(3) );

  //CASCADE 3&4-vec: try unconstraining the mass since the kaons are constrained.
  Tcas.SetXYZ(Tb(0)+Tpr(0)-Tk1(0)-Tk2(0), Tb(1)+Tpr(1)-Tk1(1)-Tk2(1), Tb(2)+Tpr(2)-Tk1(2)-Tk2(2));
  Fcas.SetPxPyPzE(Tcas(0), Tcas(1), Tcas(2), Fb.Energy() + Fpr.Energy() - Fk1.Energy() - Fk2.Energy() );
  FcasPDG.SetXYZM(Tcas(0), Tcas(1), Tcas(2), Mcas);

  //also set the four vector in the oppisite direction of the cascade
  Tnegcas.SetXYZ(-Tcas(0),-Tcas(1),-Tcas(2));
  Fnegcas.SetXYZM(Tnegcas(0), -Tnegcas(1),-Tnegcas(2),Mcas);

  //PION 3&4-vec
  Xpi=pimx;
  Ypi=pimy;
  Zpi=pimz;
  Tpi.SetXYZ(Xpi,Ypi,Zpi);
  Fpi.SetXYZM(Tpi(0),Tpi(1),Tpi(2),Mpi);

  //LAMBDA 3&4-vec---------SEP6 THIS WAS EDITED TO UNCONSTRAIN THE MASS OF LAMBDA
  Tl.SetXYZ(Tb(0) + Tpr(0) - Tk1(0) - Tk2(0) - Tpi(0), Tb(1) + Tpr(1) - Tk1(1) - Tk2(1) - Tpi(1), Tb(2) + Tpr(2) - Tk1(2) - Tk2(2) - Tpi(2));
  Fl.SetPxPyPzE(Tl(0), Tl(1), Tl(2), Fb.Energy() + Fpr.Energy() - Fk1.Energy() - Fk2.Energy() - Fpi.Energy());
  FlPDG.SetXYZM(Tl(0), Tl(1), Tl(2), Ml);
  // Tl.SetXYZ(Tcas(0)-Tpi(0),Tcas(1)-Tpi(1),Tcas(2)-Tpi(2));
  // Fl.SetPxPyPzE(Tl(0),Tl(1),Tl(2),Fcas.Energy()-Fpi.Energy());
  // FlPDG.SetXYZM(Tl(0),Tl(1),Tl(2),Ml);

  //CENTER OF MASS 4 vec
  //Fcm.SetPxPyPzE(Fb(0)+Fpr(0),Fb(1)+Fpr(1),Fb(2)+Fpr(2),Fb(3)+Fpr(3));




//===============================================================================BOOSTS======================================================================================





  //......................................................Boost Xi rest frame, fill 3 vector, boost back to lab......................................................
  BcasPDG = -FcasPDG.BoostVector();

  FcasPDG.Boost(BcasPDG); 
  Fcas.Boost(BcasPDG);
  Fpi.Boost(BcasPDG);
  Fl.Boost(BcasPDG);
  Fb.Boost(BcasPDG);
  Fk1.Boost(BcasPDG);
  Fk2.Boost(BcasPDG);
  Fnegcas.Boost(BcasPDG);
  Fkpkp.Boost(BcasPDG);
  FlPDG.Boost(BcasPDG);

  //CHECK THIS FRAME
  //cout << "       mass of cascade =  " << Mcas << endl;
  //cout << "       FcasPDG.Energy  =  " << FcasPDG.Energy() <<endl;
  //cout << "        Fcas.Energy    =  " << Fcas.Energy() <<endl; 
  //cout << "   (Fpi + Fl).Energy() =  " << (Fpi + Fl).Energy() << endl;
  //cout << "(Fpi + FlPDG).Energy() =  " << (Fpi + FlPDG).Energy() << endl;
  // so the unconstrain lambda and cascade correcpond to eachother which was because simply of definition.
  //also see fromt here that the constrained lambda and pion give many total energyies that are close to the rest mass of Xi which is an indicator that we are in the correct frame.



  TcasCAS.SetXYZ(Fcas(0), Fcas(1), Fcas(2));
  TpiCAS.SetXYZ(Fpi(0), Fpi(1), Fpi(2));
  TlCAS.SetXYZ(Fl(0), Fl(1), Fl(2));
  TbCAS.SetXYZ(Fb(0), Fb(1), Fb(2));
  Tk1CAS.SetXYZ(Fk1(0), Fk1(1), Fk1(2));
  Tk2CAS.SetXYZ(Fk2(0), Fk2(1), Fk2(2));
  TnegcasCAS.SetXYZ(Fnegcas(0), Fnegcas(1), Fnegcas(2));
  TkpkpCAS.SetXYZ(Fkpkp(0), Fkpkp(1), Fkpkp(2));
  TlPDGCAS.SetXYZ(FlPDG(0), FlPDG(1), FlPDG(2));

  //now also check that the lamba and the kaon are back to back
  //cout << "pion :  px=" << TpiCAS.x() << ", py=" << TpiCAS.y()<< ", pz=" << TpiCAS.z() <<endl;
  //cout << "lamb :  px=" << TlPDGCAS.x() << ", py=" << TlPDGCAS.y()<< ", pz=" << TlPDGCAS.z() <<endl;
  //cout << "total:  px=" << TpiCAS.x() + TlPDGCAS.x() << ", py=" << TpiCAS.y() + TlPDGCAS.y() << ", pz=" << TpiCAS.z() + TlPDGCAS.z() <<endl;
  //cout << "total: mag=" << (TpiCAS + TlPDGCAS).Mag() << endl; 
  //OK it is never quite zero momentum.  this is because the boost is using the PDG cascade and we are looking at the pion and the PDG lambda.
  // so small errors in the measurment of the pion momentum manifest themselves here. however with missing mass cuts the particles should be 
  //"more" back to back. THE LESSON IS THAT THE PDG LAMBDA IS CLOSER TO BACK TO BACK
	

  //before boosting back get the energy of 
  mr_Energy_Xi = FcasPDG.Energy();
  mr_Energy_lampim = (Fpi + FlPDG).Energy();


  //boost back
  		/*FcasPDG.Boost(-BcasPDG);
  		Fcas.Boost(-Bcas);
  		Fpi.Boost(-Bcas);
  		Fl.Boost(-Bcas);
  		Fb.Boost(-Bcas);
  		Fk1.Boost(-Bcas);
  		Fk2.Boost(-Bcas);
  		Fnegcas.Boost(-Bcas);
  		Fkpkp.Boost(-Bcas);
  		FlPDG.Boost(-BcasPDG);
		*/

//================================================================= define the coordinate system==========================================================================


  //coordinates in the lab frame.......................................................................................................................................
  		/*TVector3 VecZ_lab, UnitVecZ_lab;
  		TVector3 VecY_lab, UnitVecY_lab;
  		TVector3 VecX_lab, UnitVecX_lab;

  		UnitVecZ_lab = (Tb);
  		UnitVecZ_lab = UnitVecZ_lab.Unit();

  		UnitVecY_lab = Tcas.Cross(Tb);
  		UnitVecY_lab = UnitVecY_lab.Unit();

  		UnitVecX_lab = UnitVecZ_lab.Cross(UnitVecY_lab);
  		UnitVecX_lab = UnitVecX_lab.Unit();
		*/
  //for checking the negcas vector is also a way of computing the coordinates
  TVector3 UnitVecY_lab2;
  UnitVecY_lab2 = Tb.Cross(Tnegcas);
  UnitVecY_lab2 =  UnitVecY_lab2.Unit();
 

  //cout << " mag of vecy2:  " << UnitVecY_lab2.Mag() << "  of beam:  "<< Tb.Mag() << "  of Tnegcas: " << Tnegcas.Mag() << endl;
  //cout << " mag of vecy:  " << UnitVecY_lab.Mag() << "  of beam:  "<< Tb.Mag() << "  of Tcas: " << Tcas.Mag() << endl;
  //cout << "Tcas.Dot(Tnegcas)/(Tcas.Mag()*Tnegcas.Mag()) = " << Tcas.Dot(Tnegcas)/(Tcas.Mag()*Tnegcas.Mag()) << endl;
  //cout << " UnitVecY_lab.Dot(UnitVecY_lab2) =  " << UnitVecY_lab.Dot(UnitVecY_lab2) <<endl;
  //GOOD...SO HAVE SHOWN THAT THE NEGITIVE CASCADE VECTOR SERVES AS AN EQUIVILAT MEANS OF CALCULATION OF THE COORDINATES
  // this one does not work for the cm frame


  // yet another way of computation for checking
  		//TVector3 UnitVecY_lab3;
  		//UnitVecY_lab3 = Tb.Cross(Tkpkp);
  		//UnitVecY_lab3 =  UnitVecY_lab3.Unit();

  // cout << " UnitVecY_lab.Dot(UnitVecY_lab3) =  " << UnitVecY_lab.Dot(UnitVecY_lab3) <<endl;
  //GOOD so this works in the lab frame





  // coordinates in the CM frame...................................................................................................................................
  		/*TVector3 UnitVecZ_cm;
  		TVector3 UnitVecY_cm;
  		TVector3 UnitVecX_cm;

  		UnitVecZ_cm = (TbCM);
  		UnitVecZ_cm = UnitVecZ_cm.Unit();
 
  		UnitVecY_cm = TcasCM.Cross(TbCM);
  		UnitVecY_cm = UnitVecY_cm.Unit();
 
  		UnitVecX_cm = UnitVecZ_cm.Cross(UnitVecY_cm);
  		UnitVecX_cm = UnitVecX_cm.Unit();
		*/


  // first some checks that the coordinates are the same as when calculated in the lab frame
  //cout << " check mags in cm: " << UnitVecX_cm.Mag() << ", " << UnitVecY_cm.Mag()<< ", "  << UnitVecZ_cm.Mag()  << endl;
  //cout << " check mags in lab: " << UnitVecX_lab.Mag() << ", " << UnitVecY_lab.Mag()<< ", "  << UnitVecZ_lab.Mag()  << endl;
  //cout << "check orthogonlality in lab:  " << UnitVecX_lab.Dot(UnitVecY_lab) << ", " << UnitVecZ_lab.Dot(UnitVecY_lab) << ", " << UnitVecX_lab.Dot(UnitVecZ_lab) << endl;  
  //cout << "check orthogonlality in cm:  " << UnitVecX_cm.Dot(UnitVecY_cm) << ", " << UnitVecZ_cm.Dot(UnitVecY_cm) << ", " << UnitVecX_cm.Dot(UnitVecZ_cm) << endl;  
  //cout << "check equivalance between lab & cm:  " << UnitVecX_lab.Dot(UnitVecX_cm) << ", " << UnitVecY_lab.Dot(UnitVecY_cm) << ", " << UnitVecZ_lab.Dot(UnitVecZ_cm) << endl; 
  //GOOD SO THE COORDINATE SYSTEM IS EQUVILANT WHEN CALCULATED IN THE LAB AND CM FRAME

  // the first alternate way of calculating y
  		//TVector3 UnitVecY_cm2;
  		//UnitVecY_cm2 = TbCM.Cross(TnegcasCM);
  		//UnitVecY_cm2 =  UnitVecY_cm2.Unit();
  // this way is inconsistant with the lab results


  // the second alternate way of calculating y
  		//TVector3 UnitVecY_cm3;
  		//UnitVecY_cm3 = TbCM.Cross(TkpkpCM);
  		//UnitVecY_cm3 =  UnitVecY_cm3.Unit();

  //cout << " UnitVecY_cm.Dot(UnitVecY_cm3) =  " << UnitVecY_cm.Dot(UnitVecY_cm3) <<endl;
  //GOOD this shows that using the kpkp or cas vector is equivilant when defining the Y axis which is what is needed for the Xi frame since its P will be zero here

  //cout << "check that the cascade is back to back with kpkp:" << TcasCM.Dot(TkpkpCM)/(TcasCM.Mag()*TkpkpCM.Mag()) << endl;
  //GOOD this shows they are back to back.


  //Xi rest frame.........................................................................................................................................
  // first need the sum of the momentum vectors for k1 and k2.
  // TkpkpCAS = (Tk1CAS(0) + Tk2CAS(0), Tk1CAS(1) + Tk2CAS(1), Tk1CAS(2) + Tk2CAS(2));


  TVector3 UnitVecZ_cas;
  TVector3 UnitVecY_cas;
  TVector3 UnitVecX_cas;

  UnitVecZ_cas = (TbCAS);
  UnitVecZ_cas = UnitVecZ_cas.Unit();

  UnitVecY_cas = TbCAS.Cross(TkpkpCAS);
  UnitVecY_cas = UnitVecY_cas.Unit();

  UnitVecX_cas = UnitVecZ_cas.Cross(UnitVecY_cas);
  UnitVecX_cas.Unit();



  //check that the coordinates are the same as when calculated in the lab frame
  // cout << " check mags in Xi: " << UnitVecX_cas.Mag() << ", " << UnitVecY_cas.Mag()<< ", "  << UnitVecZ_cas.Mag()  << endl;
  // cout << "check orthogonlality in Xi:  " << UnitVecX_cas.Dot(UnitVecY_cas) << ", " << UnitVecZ_cas.Dot(UnitVecY_cas) << ", " << UnitVecX_cas.Dot(UnitVecZ_cas) <<endl;  
  // cout << "check equivalance between lab & Xi:  " << UnitVecX_lab.Dot(UnitVecX_cas) << ", " << UnitVecY_lab.Dot(UnitVecY_cas) << ", " << UnitVecZ_lab.Dot(UnitVecZ_cas) << endl; 
  //shows only equal for the Y direction and the dot product for X and Y between lab and Xi frames are the same for each event.
  // this is intrpreted as a rotation about the Y direction as a result of the boost in the inplane Xi direction.
  // since the beam is rotated from this perspective by an equal amout (same as z axis) then we should take this set of coordinates to evaluate the true angles.
  // i would like to show that one can boost to the cm then to the Xi and get the same coordinate system but this was bascialy proven when showing the equivaliance between the 
  // coordinates in the lab frame and the cm frame.

  //the old shit....................................................................
  LABnorm = Tb.Cross(Tcas);
  LABnorm = LABnorm.Unit();
  //cout << "see if the old calculation of n was correct" << LABnorm.Dot(UnitVecY_cas) << endl;
  //yes up to a minus sign

//==============================================================================THE ANGLES================================================================================

  //pion:
  mr_COS_pi_x = cos(UnitVecX_cas.Angle(TpiCAS));
  mr_COS_pi_y = cos(UnitVecY_cas.Angle(TpiCAS));
  mr_COS_pi_z = cos(UnitVecZ_cas.Angle(TpiCAS));

  //lambda: here we are using the PDG cascade
  mr_COS_lam_x = cos(UnitVecX_cas.Angle(TlPDGCAS));
  mr_COS_lam_y = cos(UnitVecY_cas.Angle(TlPDGCAS));
  mr_COS_lam_z = cos(UnitVecZ_cas.Angle(TlPDGCAS));


//==============================================================================FILL THE BRANCHES AND END=======================================================================

  //pion
  mr_COS_pi_xBranch->Fill();
  mr_COS_pi_yBranch->Fill();
  mr_COS_pi_zBranch->Fill();
 
  //lambda
  mr_COS_lam_xBranch->Fill();
  mr_COS_lam_yBranch->Fill();
  mr_COS_lam_zBranch->Fill();

  //the tests
  mr_Energy_Xi_Branch->Fill();
  mr_Energy_lampim_Branch->Fill();

  }
 addedt->Write("", TObject::kOverwrite);
 gROOT->ProcessLine(".q");
}
