#include "KinLine.h"
#include <cmath>
#include "TDecompQRH.h"
#include "TRandom.h"
#include "MultiScat.c"
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <locale>
#include <string>

using std::cout;
using std::ctype;
using std::endl;
using std::locale;
using std::string;
using std::transform;
using std::use_facet;

double AlphaTrack(const TLorentzVector &__p4){
  
  int sector = 0;
  double pi = 3.14159;
  double phi_lab = __p4.Phi();
  double phi = (180./pi)*phi_lab;
  
  if(std::abs(phi) <= 30.) sector = 1;
  else if(phi > 0.){
    if(phi <= 90.) sector = 2;
    else if(phi <= 150) sector = 3;
    else sector = 4;
  }
  else {
    // phi < 0
    if(std::abs(phi) <= 90.) sector = 6;
    else if(std::abs(phi) <= 150.) sector = 5;
    else sector = 4;
  }
  return (pi/3.)*(sector - 1);
}
//_____________________________________________________________________________

/// Calculates the tracking angle \f$ \lambda \f$.
double LambdaTrack(const TLorentzVector &__p4){
  
  double lambda;
  double p_mag = __p4.P();
  double x = __p4.X()/p_mag,y = __p4.Y()/p_mag;
  
  double alpha = AlphaTrack(__p4);
  lambda = asin(cos(alpha)*y - sin(alpha)*x);
  return lambda;
}
//_____________________________________________________________________________

/// Calculates the tracking angle \f$ \phi \f$.
double PhiTrack(const TLorentzVector &__p4) {
  
  double phi;
  double z = __p4.Pz()/__p4.P(); // normalized z_lab
  double lambda = LambdaTrack(__p4);
  
  phi = acos(z/cos(lambda));
  return phi;
}

/// Calculates EC phi tracking angle \f$ \phi \f$.
double EcPhiDeg(const TLorentzVector &__p4) {
  double phi2;
  double phid = __p4.Phi() * 180./3.1416;
  
  if(phid < -30.) phi2 = phid + 360.;
  else phi2 = phid;
  phid = fmod(phi2+30.,60.) - 30.;  
  
  return phid;
}
//To correct CLAS tracking matrix
/* 
   C00 = pow(0.001*eBeamEnergy=4.018),2)/3;
   for each charged particle
   C11 = c11*pow(p_mag,4);
   C22 = c22;
   C33 = c33;
   C12 = -c12*q*p_mag*p_mag;
   C21 = C12;
   C13 = -c13*q*p_mag*p_mag;
   C31 = C13;
   C23 = c23;
   C32 = C23; 
*/

TMatrixD CorrectCLAS_V(const TMatrixD &__VTrack,
		       const std::vector<String> &__p_names,
                       const std::vector<TLorentzVector> &__p4,
                       const std::vector<TVector3> &__vert,
                       bool __multi,bool __isMC,String &__xid){
  
  TMatrixD V(__VTrack); // start it off as the tracking Variance matrix
  
  // VTrack must be square
  if(__VTrack.GetNrows() != __VTrack.GetNcols()){
    std::cout << "Error! <CorrectCLAS_V> Tracking Variance matrix passed to "
	      << "this function is NOT square. Size is " 
	      << __VTrack.GetNrows() << " x " << __VTrack.GetNcols()
	      << std::endl;
    abort();
  }
  
  int numParts = (int)__p4.size();  
  if(__VTrack.GetNrows() != (3*numParts + 1)){
    std::cout << "Error! <CorrectCLAS_V> Tracking Variance matrix size is NOT"
	      << " consistent with number of particle 4-momenta passed in. "
	      << numParts << " particles given so Variance matrix should be "
	      << (3*numParts+1) << " x " << (3*numParts+1) << " but has "
	      << __VTrack.GetNrows() << " rows and columns." << std::endl;
    abort();
  }
  
  static bool first_call = true;
  static double pPars[2][6][15][3],lamPars[2][6][15],phiPars[2][6][15];
  
  if(first_call && __multi==false) {
    // initialize the parameter arrays
    ReadInResParams(pPars,lamPars,phiPars);
    first_call = false;
  }
  double res_scale=1,p_res_scale=1,p_scale=1,r_scale=1,sigma_eloss,lam_sig_ms,
    phi_sig_ms,p_offset;
  int part_index,sector,bin,cell=7;
  double e_gamma_res;
  if(__xid == "g10a") e_gamma_res = 3.776;   
  if(__xid == "g11a") e_gamma_res = 4.018;
  if(__xid == "g12") e_gamma_res = 5.715;
  if(__xid == "g13a") e_gamma_res = 2.655;
  
  e_gamma_res *= 0.001/sqrt(3.);   
  
  if(__xid == "g10a"){ res_scale = 1.2;
    cell =6;
    if(__isMC) res_scale *= 1.3;
  }     
  if(__xid == "g11a"){ res_scale = 1.5;
    p_scale = 1.0;
    r_scale = 1.0;
    cell = 7;
    if(__isMC) res_scale *= 1.4;
  }  
  if(__xid == "g12"){ res_scale = 2.83;
    p_scale = 1.94;
    r_scale = 1.3;     
    cell = 7;
    if(__isMC) res_scale *= 1.1;
  }   
  if(__xid == "g13a"){ res_scale = 4.9;
    p_scale = 2.4;
    r_scale = 1.7;   
    cell =6;   
    if(__isMC) res_scale *= 1.12;
  }   
  
  double ecP_sig, ecTh_sig, ecPhi_sig;
  // set up the Variance matrix
  V(0,0) = pow(e_gamma_res,2); // tagged photon sigma^2
  float ms,el;
  double beta,theta,thetad,p_mag,sthetsq,gamma;
  
  for(int i = 0; i < numParts; i++){      
    beta = __p4[i].Beta();
    gamma = __p4[i].Gamma();
    theta = __p4[i].Theta();
    p_mag = __p4[i].P();
    
    thetad = theta * 180./3.1416;
    
    
    if (__p_names[i] == "n") { 		 			 		
      ecP_sig = 3*(0.02706-0.05436*p_mag+0.0737*p_mag*p_mag);
      ecPhi_sig = 3*(5.808-139.8*pow(theta,1)+1463*pow(theta,2)-8634*pow(theta,3)
		     +31700*pow(theta,4)-75220*pow(theta,5)+115600*pow(theta,6)
		     -111300*pow(theta,7)+61010*pow(theta,8)-14530*pow(theta,9));
      ecTh_sig =2*(0.01885-0.008987*pow(p_mag,1)+0.003421*pow(p_mag,2));
      V(3*i+1,3*i+1) = pow(ecP_sig,2);
      V(3*i+1,3*i+2) = 0.25*ecTh_sig*ecP_sig;//V(1,2) is p theta correlation
      V(3*i+1,3*i+3) = 0.0;//V(1,3) is p phi correlation
      V(3*i+2,3*i+1) = 0.25*ecTh_sig*ecP_sig;//V(2,1) is p theta correlation 
      V(3*i+2,3*i+2) = pow(ecTh_sig,2);
      V(3*i+2,3*i+3) = 0.0;//V(2,3) is theta phi correlation                      
      V(3*i+3,3*i+1) = 0.0;//V(3,1) is p phi correlation
      V(3*i+3,3*i+2) = 0.0;//V(3,2) is theta phi correlation
      V(3*i+3,3*i+3) = pow(ecPhi_sig,2);       
    }
    if (__p_names[i] == "gamma" && __xid == "g11a"){	
      ecP_sig = 0.0945*sqrt(p_mag);
      if(__isMC) ecP_sig = 0.093*sqrt(p_mag)+0.003;
      ecTh_sig = (0.04552-0.1343*p_mag+0.2281*p_mag*p_mag-0.1631*p_mag*p_mag*p_mag
		  +0.04339*p_mag*p_mag*p_mag*p_mag);
      ecPhi_sig =0.9*(0.1414-0.3961*p_mag+0.427*p_mag*p_mag-0.04099*p_mag*p_mag*p_mag
		      -0.1203*p_mag*p_mag*p_mag*p_mag);      
      V(3*i+1,3*i+1) = pow(ecP_sig,2);
      V(3*i+1,3*i+2) = 0.4*ecTh_sig*ecP_sig;
      V(3*i+1,3*i+3) = 0.01*ecP_sig*ecPhi_sig;
      V(3*i+2,3*i+1) = 0.4*ecTh_sig*ecP_sig;  
      V(3*i+2,3*i+2) = pow(ecTh_sig,2);
      V(3*i+2,3*i+3) = 0.008*ecTh_sig*ecPhi_sig;                        
      V(3*i+3,3*i+1) = 0.01*ecP_sig*ecPhi_sig;
      V(3*i+3,3*i+2) = 0.008*ecTh_sig*ecPhi_sig;
      V(3*i+3,3*i+3) = pow(ecPhi_sig,2);   
    }     
    if (__p_names[i] == "gamma" && __xid == "g12"){	
      ecP_sig = 0.106*sqrt(p_mag);
      if(__isMC) ecP_sig = 0.093*sqrt(p_mag)+0.003;
      ecTh_sig = (0.04552-0.1343*p_mag+0.2281*p_mag*p_mag-0.1631*p_mag*p_mag*p_mag
		  +0.04339*p_mag*p_mag*p_mag*p_mag);
      ecPhi_sig =0.7*(0.1414-0.3961*p_mag+0.427*p_mag*p_mag-0.04099*p_mag*p_mag*p_mag
		      -0.1203*p_mag*p_mag*p_mag*p_mag);      
      V(3*i+1,3*i+1) = pow(ecP_sig,2);
      V(3*i+1,3*i+2) = 0.38*ecTh_sig*ecP_sig;
      V(3*i+1,3*i+3) = 0.011*ecP_sig*ecPhi_sig;
      V(3*i+2,3*i+1) = 0.41*ecTh_sig*ecP_sig;  
      V(3*i+2,3*i+2) = pow(ecTh_sig,2);
      V(3*i+2,3*i+3) = 0.0078*ecTh_sig*ecPhi_sig;                        
      V(3*i+3,3*i+1) = 0.012*ecP_sig*ecPhi_sig;
      V(3*i+3,3*i+2) = 0.0082*ecTh_sig*ecPhi_sig;
      V(3*i+3,3*i+3) = pow(ecPhi_sig,2);   
    }     
    if (__p_names[i] == "gamma" && __xid == "g13a"){	
      ecP_sig = 0.90*(0.109-0.3739*p_mag+0.6731*p_mag*p_mag);                     
      if(__isMC) ecP_sig = 0.093*sqrt(p_mag)+0.003;
      ecTh_sig = (0.04552-0.1343*p_mag+0.2281*p_mag*p_mag-0.1631*p_mag*p_mag*p_mag
		  +0.04339*p_mag*p_mag*p_mag*p_mag);
      ecPhi_sig =(0.1414-0.3961*p_mag+0.427*p_mag*p_mag-0.04099*p_mag*p_mag*p_mag
		  -0.1203*p_mag*p_mag*p_mag*p_mag);      
      V(3*i+1,3*i+1) = pow(ecP_sig,2);
      V(3*i+1,3*i+2) = 0.39*ecTh_sig*ecP_sig;
      V(3*i+1,3*i+3) = 0.011*ecP_sig*ecPhi_sig;
      V(3*i+2,3*i+1) = 0.385*ecTh_sig*ecP_sig;  
      V(3*i+2,3*i+2) = pow(ecTh_sig,2);
      V(3*i+2,3*i+3) = 0.0078*ecTh_sig*ecPhi_sig;                        
      V(3*i+3,3*i+1) = 0.012*ecP_sig*ecPhi_sig;
      V(3*i+3,3*i+2) = 0.0076*ecTh_sig*ecPhi_sig;
      V(3*i+3,3*i+3) = pow(ecPhi_sig,2);   
    }
    if (__p_names[i] == "gamma" && __xid == "g10a"){	
      ecP_sig = 0.096*sqrt(p_mag);
      if(__isMC) ecP_sig = 0.093*sqrt(p_mag)+0.003;
      ecTh_sig = pow(0.023/5.45,2);
      ecPhi_sig = pow(0.023/(5.45*sin(thetad)),2);
      V(3*i+1,3*i+1) = pow(ecP_sig,2);
      V(3*i+1,3*i+2) = 0.3*ecTh_sig*ecP_sig;
      V(3*i+1,3*i+3) = 0.02*ecP_sig*ecPhi_sig;
      V(3*i+2,3*i+1) = 0.33*ecTh_sig*ecP_sig;  
      V(3*i+2,3*i+2) = pow(ecTh_sig,2);
      V(3*i+2,3*i+3) = 0.007*ecTh_sig*ecPhi_sig;                        
      V(3*i+3,3*i+1) = 0.014*ecP_sig*ecPhi_sig;
      V(3*i+3,3*i+2) = 0.0076*ecTh_sig*ecPhi_sig;
      V(3*i+3,3*i+3) = pow(ecPhi_sig,2);   
    }
    
    if(__multi==false &&  __p_names[i]!="gamma" && __p_names[i]!="n"  && __p_names[i]!="fit") {                                                      
      if(__p4[i].M() < .7) part_index = 1; // use pion parameters
      else part_index = 0; // use proton parameters
      
      sector = GetSectorFromP4(__p4[i]);
      bin = GetThetaBin(theta);
      
      if(part_index  == 0 && bin > 10) bin = 10;
      
      // get resolution/eloss parameters
      p_res_scale = pPars[part_index][sector-1][bin][0];
      sigma_eloss = pPars[part_index][sector-1][bin][1];
      if(__isMC) p_res_scale *= 1.4;
      
      if(part_index == 0 && p_mag > 2.) p_res_scale *= 1.25;
      if(part_index == 0){
	if(p_mag > 0.4) sigma_eloss *= 0.8;
	else if(p_mag < 0.3) sigma_eloss *= 1.25;
      }
      
      // scale resolution errors
      V(3*i+1,3*i+1) *= pow(p_res_scale,2);
      
      // add in eloss errors
      if(beta < .765)
	V(3*i+1,3*i+1) += pow(sigma_eloss*gamma/beta,2)*(1.-beta*beta/2.);
      else
	V(3*i+1,3*i+1) += pow(sigma_eloss/.765,2)
	  *(1.-.765*.765/2.)/(1.-.765*.765);
      
      p_offset = pPars[part_index][sector-1][bin][2];
      V(3*i+1,3*i+1) += p_offset*p_offset + 2*p_offset*sqrt(V(3*i+1,3*i+1));
      
      // scale angular resolution errors
      lam_sig_ms = lamPars[part_index][sector-1][bin];
      phi_sig_ms = phiPars[part_index][sector-1][bin];
      
      V(3*i+2,3*i+2) *= pow(res_scale,2);
      V(3*i+3,3*i+3) *= pow(res_scale,2);
      
      // add in multiple scattering errors 
      V(3*i+2,3*i+2) += pow(lam_sig_ms/(p_mag*beta),2);
      V(3*i+3,3*i+3) += pow(phi_sig_ms/(p_mag*beta),2);
      
      // scale off diagnol elements by resolution scale factors
      V(3*i+1,3*i+2) *= res_scale*p_res_scale; 
      V(3*i+2,3*i+1) = V(3*i+1,3*i+2);
      V(3*i+1,3*i+3) *= res_scale*p_res_scale; 
      V(3*i+3,3*i+1) = V(3*i+1,3*i+3);
      V(3*i+2,3*i+3) *= res_scale*res_scale;
      V(3*i+3,3*i+2) = V(3*i+2,3*i+3);
    }
    
    if(__multi==true &&  __p_names[i]!="gamma" && __p_names[i]!="n"  && __p_names[i]!="fit") { 
                                                            
      Float_t res_scaleLam,res_scalePhi;	 
      /*
	These can change to suit neglected 
	effects no taken into account from
	below 
      */
      p_res_scale = 2.2*r_scale;
      res_scaleLam = res_scale*2.2*r_scale;	 
      res_scalePhi = res_scale*2.2*r_scale;       
      /*
	if(__p_names[i]=="p"){
	p_res_scale = 1.95;
	res_scaleLam = res_scale*2.0;	 
	res_scalePhi = res_scale*3.9;
	}
	else if(__p_names[i]=="pi+" ||"pi-" ||"pip"||"pim"){	 
	p_res_scale = 1.95;
	res_scaleLam = res_scale*2.0;	 
	res_scalePhi = res_scale*3.9;	 
	} 
      */       
      if(__isMC) p_res_scale *= 1.4;
      
      
      // scale angular resolution and energy loss using the lynch/Dhal formalism
      sthetsq = (__p4[i].Px()*__p4[i].Px() + __p4[i].Py()*__p4[i].Py())/(p_mag*p_mag);
      
      MultiScat(__p4[i],__vert[i],&ms,&el,cell);
      
      V(3*i+1,3*i+1) *= pow(p_res_scale,2);
      
      // add in eloss errors
      V(3*i+1,3*i+1) += el*0.3;
      
      // scale res terms
      V(3*i+2,3*i+2) *= pow(res_scaleLam,2);
      V(3*i+3,3*i+3) *= pow(res_scalePhi,2);
      
      // add in multiple scattering errors 
      V(3*i+2,3*i+2) +=ms*0.33;
      V(3*i+3,3*i+3) +=0.0033*ms/sthetsq;
      
      // scale off diagnol elements by resolution scale factors
      V(3*i+1,3*i+2) *= res_scaleLam*p_res_scale; 
      V(3*i+2,3*i+1) = V(3*i+1,3*i+2);
      V(3*i+1,3*i+3) *= res_scalePhi*p_res_scale; 
      V(3*i+3,3*i+1) = V(3*i+1,3*i+3);
      V(3*i+2,3*i+3) *= res_scalePhi*res_scaleLam;
      V(3*i+3,3*i+2) = V(3*i+2,3*i+3);		
      
      
    }
    
  }
  
  return V;
}

TMatrixD CorrectCLAS_V5(const TMatrixD &__VTrack,
			const std::vector<String> &__p_names,
			const std::vector<TLorentzVector> &__p4,
			const std::vector<TVector3> &__vert,
			bool __multi,bool __isMC,String &__xid){
  
  TMatrixD V(__VTrack); // start it off as the tracking Variance matrix
  
  // VTrack must be square
  if(__VTrack.GetNrows() != __VTrack.GetNcols()){
    std::cout << "Error! <correctCLAS_V> Tracking Variance matrix passed to "
	      << "this function is NOT square. Size is " 
	      << __VTrack.GetNrows() << " x " << __VTrack.GetNcols()
	      << std::endl;
    abort();
  }
  
  int numParts = (int)__p4.size();  
  if(__VTrack.GetNrows() != (5*numParts)){
    std::cout << "Error! <correctCLAS_V> Tracking Variance matrix size is NOT"
	      << " consistent with number of particle 4-momenta passed in. "
	      << numParts << " particles given so Variance matrix should be "
	      << (5*numParts) << " x " << (5*numParts) << " but has "
	      << __VTrack.GetNrows() << " rows and columns." << std::endl;
    abort();
  }
  Float_t alpha[numParts];
  static bool first_call = true;
  static double pPars[2][6][15][3],lamPars[2][6][15],phiPars[2][6][15];
  
  if(first_call && __multi==false) {
    // initialize the parameter arrays
    ReadInResParams(pPars,lamPars,phiPars);
    first_call = false;
  }
  double res_scale=1,p_res_scale=1,p_scale=1,r_scale=1,sigma_eloss,lam_sig_ms,
    phi_sig_ms,p_offset;
  int part_index,sector,bin,cell=7;
  if(__xid != "g10a" && __xid != "g11a" && __xid != "g12" && __xid != "g13a"){ 
    std::cout<<"Experiment not known, use either g10a, g11a, g12 or g13"<<std::endl;
    abort();
  }
  
  double e_gamma_res;
  if(__xid == "g10a") e_gamma_res = 3.776;   
  if(__xid == "g11a") e_gamma_res = 4.018;
  if(__xid == "g12") e_gamma_res = 5.715;
  if(__xid == "g13a") e_gamma_res = 2.655;
  
  e_gamma_res *= 0.001/sqrt(3.);   
  
  if(__xid == "g10a"){ res_scale = 1.2;
    cell =6;
    if(__isMC) res_scale *= 1.3;
  }     
  if(__xid == "g11a"){ res_scale = 1.5;
    p_scale = 1.0;
    r_scale = 1.0;
    cell = 7;
    if(__isMC) res_scale *= 1.4;
  }  
  if(__xid == "g12"){ res_scale = 2.83;
    p_scale = 1.94;
    r_scale = 1.3;     
    cell = 7;
    if(__isMC) res_scale *= 1.1;
  }   
  if(__xid == "g13a"){ res_scale = 4.9;
    p_scale = 2.4;
    r_scale = 1.7;   
    cell =6;   
    if(__isMC) res_scale *= 1.12;
  }   
  
  double ecP_sig, ecTh_sig, ecPhi_sig;
  // set up the Variance matrix
  V(0,0) = pow(e_gamma_res,2); // tagged photon sigma^2
  float ms,el;
  double beta,theta,thetad,p_mag,sthetsq,gamma;
  
  for(int i = 0; i < numParts; i++){      
    beta = __p4[i].Beta();
    gamma = __p4[i].Gamma();
    theta = __p4[i].Theta();
    p_mag = __p4[i].P();
    
    thetad = theta * 180./3.1416;
    
    
    if (__p_names[i] == "n") { 		 			 		
      ecP_sig = 3*(0.02706-0.05436*p_mag+0.0737*p_mag*p_mag);
      ecPhi_sig = 3*(5.808-139.8*pow(theta,1)+1463*pow(theta,2)-8634*pow(theta,3)
		     +31700*pow(theta,4)-75220*pow(theta,5)+115600*pow(theta,6)
		     -111300*pow(theta,7)+61010*pow(theta,8)-14530*pow(theta,9));
      ecTh_sig =2*(0.01885-0.008987*pow(p_mag,1)+0.003421*pow(p_mag,2));
      V(5*i+0,5*i+0) = pow(ecP_sig,2);
      V(5*i+0,5*i+1) = 0.25*ecTh_sig*ecP_sig;//V(1,2) is p theta correlation
      V(5*i+0,5*i+2) = 0.0;//V(1,3) is p phi correlation
      V(5*i+1,5*i+0) = 0.25*ecTh_sig*ecP_sig;//V(2,1) is p theta correlation 
      V(5*i+1,5*i+1) = pow(ecTh_sig,2);
      V(5*i+1,5*i+2) = 0.0;//V(2,3) is theta phi correlation                      
      V(5*i+2,5*i+0) = 0.0;//V(3,1) is p phi correlation
      V(5*i+2,5*i+1) = 0.0;//V(3,2) is theta phi correlation
      V(5*i+2,5*i+2) = pow(ecPhi_sig,2);       
    }
    if (__p_names[i] == "gamma" && __xid == "g11a"){	
      ecP_sig = 0.0945*sqrt(p_mag);
      if(__isMC) ecP_sig = 0.093*sqrt(p_mag)+0.003;
      ecTh_sig = (0.04552-0.1343*p_mag+0.2281*p_mag*p_mag-0.1631*p_mag*p_mag*p_mag
		  +0.04339*p_mag*p_mag*p_mag*p_mag);
      ecPhi_sig =0.9*(0.1414-0.3961*p_mag+0.427*p_mag*p_mag-0.04099*p_mag*p_mag*p_mag
		      -0.1203*p_mag*p_mag*p_mag*p_mag);      
      V(5*i+0,5*i+0) = pow(ecP_sig,2);
      V(5*i+0,5*i+1) = 0.4*ecTh_sig*ecP_sig;
      V(5*i+0,5*i+2) = 0.01*ecP_sig*ecPhi_sig;
      V(5*i+1,5*i+0) = 0.4*ecTh_sig*ecP_sig;  
      V(5*i+1,5*i+1) = pow(ecTh_sig,2);
      V(5*i+1,5*i+2) = 0.008*ecTh_sig*ecPhi_sig;                        
      V(5*i+2,5*i+0) = 0.01*ecP_sig*ecPhi_sig;
      V(5*i+2,5*i+1) = 0.008*ecTh_sig*ecPhi_sig;
      V(5*i+2,5*i+2) = pow(ecPhi_sig,2);   
    }     
    if (__p_names[i] == "gamma" && __xid == "g12"){	
      ecP_sig = 0.106*sqrt(p_mag);
      if(__isMC) ecP_sig = 0.093*sqrt(p_mag)+0.003;
      ecTh_sig = (0.04552-0.1343*p_mag+0.2281*p_mag*p_mag-0.1631*p_mag*p_mag*p_mag
		  +0.04339*p_mag*p_mag*p_mag*p_mag);
      ecPhi_sig =0.7*(0.1414-0.3961*p_mag+0.427*p_mag*p_mag-0.04099*p_mag*p_mag*p_mag
		      -0.1203*p_mag*p_mag*p_mag*p_mag);      
      V(5*i+0,5*i+0) = pow(ecP_sig,2);
      V(5*i+0,5*i+1) = 0.38*ecTh_sig*ecP_sig;
      V(5*i+0,5*i+2) = 0.011*ecP_sig*ecPhi_sig;
      V(5*i+1,5*i+0) = 0.41*ecTh_sig*ecP_sig;  
      V(5*i+1,5*i+1) = pow(ecTh_sig,2);
      V(5*i+1,5*i+2) = 0.0078*ecTh_sig*ecPhi_sig;                        
      V(5*i+2,5*i+0) = 0.012*ecP_sig*ecPhi_sig;
      V(5*i+2,5*i+1) = 0.0082*ecTh_sig*ecPhi_sig;
      V(5*i+2,5*i+2) = pow(ecPhi_sig,2);   
    }     
    if (__p_names[i] == "gamma" && __xid == "g13a"){	
      ecP_sig = 0.90*(0.109-0.3739*p_mag+0.6731*p_mag*p_mag);                     
      if(__isMC) ecP_sig = 0.093*sqrt(p_mag)+0.003;
      ecTh_sig = (0.04552-0.1343*p_mag+0.2281*p_mag*p_mag-0.1631*p_mag*p_mag*p_mag
		  +0.04339*p_mag*p_mag*p_mag*p_mag);
      ecPhi_sig =(0.1414-0.3961*p_mag+0.427*p_mag*p_mag-0.04099*p_mag*p_mag*p_mag
		  -0.1203*p_mag*p_mag*p_mag*p_mag);      
      V(5*i+0,5*i+0) = pow(ecP_sig,2);
      V(5*i+0,5*i+1) = 0.39*ecTh_sig*ecP_sig;
      V(5*i+0,5*i+2) = 0.011*ecP_sig*ecPhi_sig;
      V(5*i+1,5*i+0) = 0.385*ecTh_sig*ecP_sig;  
      V(5*i+1,5*i+1) = pow(ecTh_sig,2);
      V(5*i+1,5*i+2) = 0.0078*ecTh_sig*ecPhi_sig;                        
      V(5*i+2,5*i+0) = 0.012*ecP_sig*ecPhi_sig;
      V(5*i+2,5*i+1) = 0.0076*ecTh_sig*ecPhi_sig;
      V(5*i+2,5*i+2) = pow(ecPhi_sig,2);   
    }
    if (__p_names[i] == "gamma" && __xid == "g10a"){	
      ecP_sig = 0.096*sqrt(p_mag);
      if(__isMC) ecP_sig = 0.093*sqrt(p_mag)+0.003;
      ecTh_sig = pow(0.023/5.45,2);
      ecPhi_sig = pow(0.023/(5.45*sin(thetad)),2);
      V(5*i+0,5*i+0) = pow(ecP_sig,2);
      V(5*i+0,5*i+1) = 0.3*ecTh_sig*ecP_sig;
      V(5*i+0,5*i+2) = 0.02*ecP_sig*ecPhi_sig;
      V(5*i+1,5*i+0) = 0.33*ecTh_sig*ecP_sig;  
      V(5*i+1,5*i+1) = pow(ecTh_sig,2);
      V(5*i+1,5*i+2) = 0.007*ecTh_sig*ecPhi_sig;                        
      V(5*i+2,5*i+0) = 0.014*ecP_sig*ecPhi_sig;
      V(5*i+2,5*i+1) = 0.0076*ecTh_sig*ecPhi_sig;
      V(5*i+2,5*i+2) = pow(ecPhi_sig,2);   
    } 
    
    if(__multi==false &&  __p_names[i]!="gamma" && __p_names[i]!="n"  && __p_names[i]!="fit") {                                                      
      if(__p4[i].M() < .7) part_index = 1; // use pion parameters
      else part_index = 0; // use proton parameters
      
      sector = GetSectorFromP4(__p4[i]);
      bin = GetThetaBin(theta);
      
      if(part_index  == 0 && bin > 10) bin = 10;
      
      // get resolution/eloss parameters
      p_res_scale = pPars[part_index][sector-1][bin][0];
      sigma_eloss = pPars[part_index][sector-1][bin][1];
      if(__isMC) p_res_scale *= 1.4;
      
      if(part_index == 0 && p_mag > 2.) p_res_scale *= 1.25;
      if(part_index == 0){
	if(p_mag > 0.4) sigma_eloss *= 0.8;
	else if(p_mag < 0.3) sigma_eloss *= 1.25;
      }
      
      // scale resolution errors
      V(5*i+0,5*i+0) *= pow(p_res_scale,2);
      
      // add in eloss errors
      if(beta < .765)
	V(5*i+0,5*i+0) += pow(sigma_eloss*gamma/beta,2)*(1.-beta*beta/2.);
      else
	V(5*i+0,5*i+0) += pow(sigma_eloss/.765,2)
	  *(1.-.765*.765/2.)/(1.-.765*.765);
      
      p_offset = pPars[part_index][sector-1][bin][2];
      V(5*i+0,5*i+0) += p_offset*p_offset + 2*p_offset*sqrt(V(3*i+0,3*i+0));
      
      // scale angular resolution errors
      lam_sig_ms = lamPars[part_index][sector-1][bin];
      phi_sig_ms = phiPars[part_index][sector-1][bin];
      
      V(5*i+1,5*i+1) *= pow(res_scale,2);
      V(5*i+2,5*i+2) *= pow(res_scale,2);
      
      // add in multiple scattering errors 
      V(5*i+1,5*i+1) += pow(lam_sig_ms/(p_mag*beta),2);
      V(5*i+2,5*i+2) += pow(phi_sig_ms/(p_mag*beta),2);
     
      // scale off diagnol elements by resolution scale factors
      V(5*i+0,5*i+1) *= res_scale*p_res_scale; 
      V(5*i+1,5*i+0) = V(5*i+0,5*i+1);
      V(5*i+0,5*i+2) *= res_scale*p_res_scale; 
      V(5*i+2,5*i+0) = V(5*i+0,5*i+2);
      V(5*i+1,5*i+2) *= res_scale*res_scale;
      V(5*i+2,5*i+1) = V(5*i+1,5*i+2);
      V(5*i+0,5*i+3) *= p_res_scale;
      V(5*i+3,5*i+0) = V(5*i+0,5*i+3);
      V(5*i+0,5*i+4) *= p_res_scale;
      V(5*i+4,5*i+0) = V(5*i+0,5*i+4);
      V(5*i+1,5*i+3) *= res_scale;
      V(5*i+3,5*i+1) = V(5*i+1,5*i+3);
      V(5*i+1,5*i+4) *= res_scale;
      V(5*i+4,5*i+1) = V(5*i+1,5*i+4);
      V(5*i+2,5*i+3) *= res_scale;
      V(5*i+3,5*i+2) = V(5*i+2,5*i+3);
      V(5*i+2,5*i+4) *= res_scale;
      V(5*i+4,5*i+2) = V(5*i+2,5*i+4);       
       
    }
    
    if(__multi==true &&  __p_names[i]!="gamma" && __p_names[i]!="n"  && __p_names[i]!="fit") {                                                      
      Float_t res_scaleLam,res_scalePhi;	 
      p_res_scale = 2.2*r_scale;
      res_scaleLam = res_scale*2.2*r_scale;	 
      res_scalePhi = res_scale*2.2*r_scale;             
      // scale angular resolution and energy loss using the lynch/Dhal formalism
      MultiScat(__p4[i],__vert[i],&ms,&el,cell);		 
      Float_t _lambda = LambdaTrack(__p4[i]);
      Float_t _phi = PhiTrack(__p4[i]);
      alpha[i] = AlphaTrack(__p4[i]);
      Float_t sina=sin(alpha[i]);
      Float_t cosa=cos(alpha[i]);
      Float_t delta_x2 = 50;
      Float_t d0 =__vert[i].Y()*cosa-__vert[i].X()*sina
	-(__vert[i].X()*cosa+__vert[i].Y()*sina)*tan(LambdaTrack(__p4[i])
						     /sin(PhiTrack(__p4[i])));      
      // add in eloss errors
      V(5*i+0,5*i+0) +=  el;
      
      // scale res terms
      V(5*i+1,5*i+1) *= pow(res_scaleLam,2);
      V(5*i+2,5*i+2) *= pow(res_scalePhi,2);      
      
      // angular multiple scattering
      sthetsq = (__p4[i].Px()*__p4[i].Px() + __p4[i].Py()*__p4[i].Py())/p_mag*p_mag;
      Float_t cthetsq = 1.0 - sthetsq;
      
      // add in multiple scattering errors 
      V(5*i+1,5*i+1) += ms*0.33;
      V(5*i+2,5*i+2) += 0.0033*ms/sthetsq;
      
      V(5*i+3,5*i+3) += 0.0033*ms/sthetsq/6.
	*(delta_x2*sin(_phi)*sin(_phi)*(sin(_phi)*sin(_phi)
					+cos(_phi)*cos(_phi)*sin(_lambda)*sin(_lambda))
	  +d0*d0/tan(_phi)/tan(_phi)*(1.0 + cthetsq)/sthetsq);      
      V(5*i+4,5*i+4) += 0.0033*ms/sthetsq/6.*cos(_lambda)*cos(_lambda); 	                 
     
      // scale off diagnol elements by resolution scale factors
      V(5*i+0,5*i+1) *= res_scale*p_res_scale; 
      V(5*i+1,5*i+0) = V(5*i+0,5*i+1);
      V(5*i+0,5*i+2) *= res_scale*p_res_scale; 
      V(5*i+2,5*i+0) = V(5*i+0,5*i+2);
      V(5*i+1,5*i+2) *= res_scale*res_scale;
      V(5*i+2,5*i+1) = V(5*i+1,5*i+2); 
      V(5*i+0,5*i+3) *= p_res_scale;
      V(5*i+3,5*i+0) = V(5*i+0,5*i+3);
      V(5*i+0,5*i+4) *= p_res_scale;
      V(5*i+4,5*i+0) = V(5*i+0,5*i+4);
      V(5*i+1,5*i+3) *= res_scale;
      V(5*i+3,5*i+1) = V(5*i+1,5*i+3);
      V(5*i+1,5*i+4) *= res_scale;
      V(5*i+4,5*i+1) = V(5*i+1,5*i+4);
      V(5*i+2,5*i+3) *= res_scale;
      V(5*i+3,5*i+2) = V(5*i+2,5*i+3);
      V(5*i+2,5*i+4) *= res_scale;
      V(5*i+4,5*i+2) = V(5*i+2,5*i+4);       
  
    }
    
  }
  
  return V;
} 
TMatrixD CorrectCLAS_V3(const TMatrixD &__VTrack,
			const std::vector<String> &__p_names,
			const std::vector<TLorentzVector> &__p4,
			const std::vector<TVector3> &__vert,
			bool __multi,bool __isMC,String &__xid){
  
  TMatrixD V(__VTrack); // start it off as the tracking Variance matrix
  
  // VTrack must be square
  if(__VTrack.GetNrows() != __VTrack.GetNcols()){
    std::cout << "Error! <correctCLAS_V> Tracking Variance matrix passed to "
	      << "this function is NOT square. Size is " 
	      << __VTrack.GetNrows() << " x " << __VTrack.GetNcols()
	      << std::endl;
    abort();
  }
  
  int numParts = (int)__p4.size();  
  if(__VTrack.GetNrows() != (3*numParts)){
    std::cout << "Error! <correctCLAS_V> Tracking Variance matrix size is NOT"
	      << " consistent with number of particle 4-momenta passed in. "
	      << numParts << " particles given so Variance matrix should be "
	      << (3*numParts) << " x " << (3*numParts) << " but has "
	      << __VTrack.GetNrows() << " rows and columns." << std::endl;
    abort();
  }
  
  static bool first_call = true;
  static double pPars[2][6][15][3],lamPars[2][6][15],phiPars[2][6][15];
  
  if(first_call && __multi==false) {
    // initialize the parameter arrays
    ReadInResParams(pPars,lamPars,phiPars);
    first_call = false;
  }
  double res_scale=1,p_res_scale=1,p_scale=1,r_scale=1,sigma_eloss,lam_sig_ms,
    phi_sig_ms,p_offset;
  int part_index,sector,bin,cell=7;
  if(__xid != "g10a" && __xid != "g11a" && __xid != "g12" && __xid != "g13a"){ 
    std::cout<<"Experiment not known, use either g10a, g11a, g12 or g13"<<std::endl;
    abort();
  }
  
  double e_gamma_res;
  if(__xid == "g10a") e_gamma_res = 3.776;   
  if(__xid == "g11a") e_gamma_res = 4.018;
  if(__xid == "g12") e_gamma_res = 5.715;
  if(__xid == "g13a") e_gamma_res = 2.655;
  
  
  e_gamma_res *= 0.001/sqrt(3.);   
  
  if(__xid == "g10a"){ res_scale = 1.2;
    cell =6;
    if(__isMC) res_scale *= 1.3;
  }     
  if(__xid == "g11a"){ res_scale = 1.5;
    p_scale = 1.0;
    r_scale = 1.0;
    cell = 7;
    if(__isMC) res_scale *= 1.4;
  }  
  if(__xid == "g12"){ res_scale = 2.83;
    p_scale = 1.94;
    r_scale = 1.3;     
    cell = 7;
    if(__isMC) res_scale *= 1.1;
  }   
  if(__xid == "g13a"){ res_scale = 4.9;
    p_scale = 2.4;
    r_scale = 1.7;   
    cell =6;   
    if(__isMC) res_scale *= 1.12;
  }  
  
  double ecP_sig, ecTh_sig, ecPhi_sig;
  // set up the Variance matrix
  V(0,0) = pow(e_gamma_res,2); // tagged photon sigma^2
  float ms,el;
  double beta,theta,thetad,p_mag,sthetsq,gamma;
  
  for(int i = 0; i < numParts; i++){      
    beta = __p4[i].Beta();
    gamma = __p4[i].Gamma();
    theta = __p4[i].Theta();
    p_mag = __p4[i].P();
    
    thetad = theta * 180./3.1416;
    
    if (__p_names[i] == "n") { 		 			 		
      ecP_sig = 3*(0.02706-0.05436*p_mag+0.0737*p_mag*p_mag);
      ecPhi_sig = 3*(5.808-139.8*pow(theta,1)+1463*pow(theta,2)-8634*pow(theta,3)
		     +31700*pow(theta,4)-75220*pow(theta,5)+115600*pow(theta,6)
		     -111300*pow(theta,7)+61010*pow(theta,8)-14530*pow(theta,9));
      ecTh_sig =2*(0.01885-0.008987*pow(p_mag,1)+0.003421*pow(p_mag,2));
      V(3*i+0,3*i+0) = pow(ecP_sig,2);
      V(3*i+0,3*i+1) = 0.25*ecTh_sig*ecP_sig;//V(1,2) is p theta correlation
      V(3*i+0,3*i+2) = 0.0;//V(1,3) is p phi correlation
      V(3*i+1,3*i+0) = 0.25*ecTh_sig*ecP_sig;//V(2,1) is p theta correlation 
      V(3*i+1,3*i+1) = pow(ecTh_sig,2);
      V(3*i+1,3*i+2) = 0.0;//V(2,3) is theta phi correlation                      
      V(3*i+2,3*i+0) = 0.0;//V(3,1) is p phi correlation
      V(3*i+2,3*i+1) = 0.0;//V(3,2) is theta phi correlation
      V(3*i+2,3*i+2) = pow(ecPhi_sig,2);       
    }
    if (__p_names[i] == "gamma" && __xid == "g11a"){	
      ecP_sig = 0.0945*sqrt(p_mag);
      if(__isMC) ecP_sig = 0.093*sqrt(p_mag)+0.003;
      ecTh_sig = (0.04552-0.1343*p_mag+0.2281*p_mag*p_mag-0.1631*p_mag*p_mag*p_mag
		  +0.04339*p_mag*p_mag*p_mag*p_mag);
      ecPhi_sig =0.9*(0.1414-0.3961*p_mag+0.427*p_mag*p_mag-0.04099*p_mag*p_mag*p_mag
		      -0.1203*p_mag*p_mag*p_mag*p_mag);      
      V(3*i+0,3*i+0) = pow(ecP_sig,2);
      V(3*i+0,3*i+1) = 0.4*ecTh_sig*ecP_sig;
      V(3*i+0,3*i+2) = 0.01*ecP_sig*ecPhi_sig;
      V(3*i+1,3*i+0) = 0.4*ecTh_sig*ecP_sig;  
      V(3*i+1,3*i+1) = pow(ecTh_sig,2);
      V(3*i+1,3*i+2) = 0.008*ecTh_sig*ecPhi_sig;                        
      V(3*i+2,3*i+0) = 0.01*ecP_sig*ecPhi_sig;
      V(3*i+2,3*i+1) = 0.008*ecTh_sig*ecPhi_sig;
      V(3*i+2,3*i+2) = pow(ecPhi_sig,2);   
    }     
    if (__p_names[i] == "gamma" && __xid == "g12"){	
      ecP_sig = 0.106*sqrt(p_mag);
      if(__isMC) ecP_sig = 0.093*sqrt(p_mag)+0.003;
      ecTh_sig = (0.04552-0.1343*p_mag+0.2281*p_mag*p_mag-0.1631*p_mag*p_mag*p_mag
		  +0.04339*p_mag*p_mag*p_mag*p_mag);
      ecPhi_sig =0.7*(0.1414-0.3961*p_mag+0.427*p_mag*p_mag-0.04099*p_mag*p_mag*p_mag
		      -0.1203*p_mag*p_mag*p_mag*p_mag);      
      V(3*i+0,3*i+0) = pow(ecP_sig,2);
      V(3*i+0,3*i+1) = 0.38*ecTh_sig*ecP_sig;
      V(3*i+0,3*i+2) = 0.011*ecP_sig*ecPhi_sig;
      V(3*i+1,3*i+0) = 0.41*ecTh_sig*ecP_sig;  
      V(3*i+1,3*i+1) = pow(ecTh_sig,2);
      V(3*i+1,3*i+2) = 0.0078*ecTh_sig*ecPhi_sig;                        
      V(3*i+2,3*i+0) = 0.012*ecP_sig*ecPhi_sig;
      V(3*i+2,3*i+1) = 0.0082*ecTh_sig*ecPhi_sig;
      V(3*i+2,3*i+2) = pow(ecPhi_sig,2);   
    }     
    if (__p_names[i] == "gamma" && __xid == "g13a"){	
      ecP_sig = 0.90*(0.109-0.3739*p_mag+0.6731*p_mag*p_mag);                     
      if(__isMC) ecP_sig = 0.093*sqrt(p_mag)+0.003;
      ecTh_sig = (0.04552-0.1343*p_mag+0.2281*p_mag*p_mag-0.1631*p_mag*p_mag*p_mag
		  +0.04339*p_mag*p_mag*p_mag*p_mag);
      ecPhi_sig =(0.1414-0.3961*p_mag+0.427*p_mag*p_mag-0.04099*p_mag*p_mag*p_mag
		  -0.1203*p_mag*p_mag*p_mag*p_mag);      
      V(3*i+0,3*i+0) = pow(ecP_sig,2);
      V(3*i+0,3*i+1) = 0.39*ecTh_sig*ecP_sig;
      V(3*i+0,3*i+2) = 0.011*ecP_sig*ecPhi_sig;
      V(3*i+1,3*i+0) = 0.385*ecTh_sig*ecP_sig;  
      V(3*i+1,3*i+1) = pow(ecTh_sig,2);
      V(3*i+1,3*i+2) = 0.0078*ecTh_sig*ecPhi_sig;                        
      V(3*i+2,3*i+0) = 0.012*ecP_sig*ecPhi_sig;
      V(3*i+2,3*i+1) = 0.0076*ecTh_sig*ecPhi_sig;
      V(3*i+2,3*i+2) = pow(ecPhi_sig,2);   
    }
    if (__p_names[i] == "gamma" && __xid == "g10a"){	
      ecP_sig = 0.096*sqrt(p_mag);
      if(__isMC) ecP_sig = 0.093*sqrt(p_mag)+0.003;
      ecTh_sig = pow(0.023/5.45,2);
      ecPhi_sig = pow(0.023/(5.45*sin(thetad)),2);
      V(3*i+0,3*i+0) = pow(ecP_sig,2);
      V(3*i+0,3*i+1) = 0.3*ecTh_sig*ecP_sig;
      V(3*i+0,3*i+2) = 0.02*ecP_sig*ecPhi_sig;
      V(3*i+1,3*i+0) = 0.33*ecTh_sig*ecP_sig;  
      V(3*i+1,3*i+1) = pow(ecTh_sig,2);
      V(3*i+1,3*i+2) = 0.007*ecTh_sig*ecPhi_sig;                        
      V(3*i+2,3*i+0) = 0.014*ecP_sig*ecPhi_sig;
      V(3*i+2,3*i+1) = 0.0076*ecTh_sig*ecPhi_sig;
      V(3*i+2,3*i+2) = pow(ecPhi_sig,2);   
    }
    
    if(__multi==false &&  __p_names[i]!="gamma" && __p_names[i]!="n"  && __p_names[i]!="fit") {                                                      
      if(__p4[i].M() < .7) part_index = 1; // use pion parameters
      else part_index = 0; // use proton parameters
      
      sector = GetSectorFromP4(__p4[i]);
      bin = GetThetaBin(theta);
      
      if(part_index  == 0 && bin > 10) bin = 10;
      
      // get resolution/eloss parameters
      p_res_scale = pPars[part_index][sector-1][bin][0];
      sigma_eloss = pPars[part_index][sector-1][bin][1];
      if(__isMC) p_res_scale *= 1.4;
      
      if(part_index == 0 && p_mag > 2.) p_res_scale *= 1.25;
      if(part_index == 0){
	if(p_mag > 0.4) sigma_eloss *= 0.8;
	else if(p_mag < 0.3) sigma_eloss *= 1.25;
      }
      
      // scale resolution errors
      V(3*i+0,3*i+0) *= pow(p_res_scale,2);
      
      // add in eloss errors
      if(beta < .765)
	V(3*i+0,3*i+0) += pow(sigma_eloss*gamma/beta,2)*(1.-beta*beta/2.);
      else
	V(3*i+0,3*i+0) += pow(sigma_eloss/.765,2)
	  *(1.-.765*.765/2.)/(1.-.765*.765);
      
      p_offset = pPars[part_index][sector-1][bin][2];
      V(3*i+0,3*i+0) += p_offset*p_offset + 2*p_offset*sqrt(V(3*i+0,3*i+0));
      
      // scale angular resolution errors
      lam_sig_ms = lamPars[part_index][sector-1][bin];
      phi_sig_ms = phiPars[part_index][sector-1][bin];
      
      V(3*i+1,3*i+1) *= pow(res_scale,2);
      V(3*i+2,3*i+2) *= pow(res_scale,2);
      
      // add in multiple scattering errors 
      V(3*i+1,3*i+1) += pow(lam_sig_ms/(p_mag*beta),2);
      V(3*i+2,3*i+2) += pow(phi_sig_ms/(p_mag*beta),2);
      
      // scale off diagnol elements by resolution scale factors
      V(3*i+0,3*i+1) *= res_scale*p_res_scale; 
      V(3*i+1,3*i+0) = V(3*i+0,3*i+1);
      V(3*i+0,3*i+2) *= res_scale*p_res_scale; 
      V(3*i+2,3*i+0) = V(3*i+0,3*i+2);
      V(3*i+1,3*i+2) *= res_scale*res_scale;
      V(3*i+2,3*i+1) = V(3*i+1,3*i+2);
    
    }
    
    if(__multi==true &&  __p_names[i]!="gamma" && __p_names[i]!="n"  && __p_names[i]!="fit") {
      Float_t res_scaleLam,res_scalePhi;	 
      p_res_scale = 2.2*r_scale;
      res_scaleLam = res_scale*2.2*r_scale;	 
      res_scalePhi = res_scale*2.2*r_scale;      
      if(__isMC) p_res_scale *= 1.4;                                                      
      
      // scale angular resolution and energy loss using the lynch/Dhal formalism
      sthetsq = (__p4[i].Px()*__p4[i].Px() + __p4[i].Py()*__p4[i].Py())/p_mag*p_mag;
      
      MultiScat(__p4[i],__vert[i],&ms,&el,cell);		 
      // add in eloss errors
      V(3*i+0,3*i+0) += el;			 
      // scale angular terms
      V(3*i+1,3*i+1) *= pow(res_scaleLam,2);
      V(3*i+2,3*i+2) *= pow(res_scalePhi,2);		 
      // add in multiple scattering errors 		 
      V(3*i+1,3*i+1) += ms;
      V(3*i+2,3*i+2) += 0.0033*ms/sthetsq;
      
      // scale off diagnol elements by resolution scale factors
      V(3*i+0,3*i+1) *= res_scale*p_res_scale; 
      V(3*i+1,3*i+0) = V(3*i+0,3*i+1);
      V(3*i+0,3*i+2) *= res_scale*p_res_scale; 
      V(3*i+2,3*i+0) = V(3*i+0,3*i+2);
      V(3*i+1,3*i+2) *= res_scale*res_scale;
      V(3*i+2,3*i+1) = V(3*i+1,3*i+2);	

    }
    
  }
  
  return V;
}
TMatrixD CorrectVert_V(const TMatrixD &__VTrack,
		       const std::vector<String> &__p_names,
                       const std::vector<TLorentzVector> &__p4,
                       const std::vector<TVector3> &__vert){
  
  TMatrixD V(__VTrack); // start it off as the tracking Variance matrix
  
  // VTrack must be square
  if(__VTrack.GetNrows() != __VTrack.GetNcols()){
    std::cout << "Error! <correctCLAS_V> Tracking Variance matrix passed to "
	      << "this function is NOT square. Size is " 
	      << __VTrack.GetNrows() << " x " << __VTrack.GetNcols()
	      << std::endl;
    abort();
  }
  
  int numParts = (int)__p4.size();  
  if(__VTrack.GetNrows() != (2*numParts)){
    std::cout << "Error! <correctCLAS_V> Tracking Variance matrix size is NOT"
	      << " consistent with number of particle 4-momenta passed in. "
	      << numParts << " particles given so Variance matrix should be "
	      << (2*numParts) << " x " << (2*numParts) << " but has "
	      << __VTrack.GetNrows() << " rows and columns." << std::endl;
    abort();
  }
  for(int i = 0; i < numParts; i++){
    if(  __p_names[i]!="gamma" && __p_names[i]!="n"  && __p_names[i]!="fit") {
      Float_t ms=0,el=0,alpha[2];
      Int_t cell=7;
      MultiScat(__p4[i],__vert[i],&ms,&el,cell);		 
      Float_t _lambda = LambdaTrack(__p4[i]);
      Float_t _phi = PhiTrack(__p4[i]);
      alpha[i] = AlphaTrack(__p4[i]);
      Float_t sina=sin(alpha[i]);
      Float_t cosa=cos(alpha[i]);
      Float_t delta_x2 = 50;
      Float_t p_mag = fabs(__p4[i].P());
      Float_t d0 =__vert[i].Y()*cosa-__vert[i].X()*sina
	-(__vert[i].X()*cosa+__vert[i].Y()*sina)*tan(LambdaTrack(__p4[i])
						     /sin(PhiTrack(__p4[i])));      
      
      // angular multiple scattering
      Float_t sthetsq = (__p4[i].Px()*__p4[i].Px() + __p4[i].Py()*__p4[i].Py())/p_mag*p_mag;
      Float_t cthetsq = 1.0 - sthetsq;
      
      V(2*i+0,2*i+0) += 0.0033*ms/sthetsq/6.
	*(delta_x2*sin(_phi)*sin(_phi)*(sin(_phi)*sin(_phi)
					+cos(_phi)*cos(_phi)*sin(_lambda)*sin(_lambda))
	  +d0*d0/tan(_phi)/tan(_phi)*(1.0 + cthetsq)/sthetsq);      
      V(2*i+1,2*i+1) += 0.0033*ms/sthetsq/6.*cos(_lambda)*cos(_lambda); 
    } 
  }    
  return V;
}


TMatrixD ReduceFromFit(const TMatrixD &__VMat,const TMatrixD &__FitV){
  
  /*This will reset the last two particle terms in the covariance matrix
    to the new particle terms. 
  */
  
  TMatrixD V(__VMat);
  
  if(__FitV.GetNrows() != __FitV.GetNcols()){
    std::cout << "Error! <ReduceFromFit> Particle covariance matrix passed to "
	      << "this function is NOT square. Size is " 
	      << __FitV.GetNrows() << " x " << __FitV.GetNcols()
	      << std::endl;
    abort();
  }
  
  if(__FitV.GetNrows() != 3){
    std::cout << "Error! <ReduceFromFit> Paricle covariance matrix size is NOT"
	      << " consistent with a single particle. "
	      << " matrix must be 3 x 3 but has "
	      << __FitV.GetNrows() << " rows and columns." << std::endl;
    abort();
  }
  
  if(__VMat.GetNrows() != __VMat.GetNcols()){
    std::cout << "Error! <ReduceFromFit> Tracking Variance matrix passed to "
	      << "this function is NOT square. Size is " 
	      << __VMat.GetNrows() << " x " << __VMat.GetNcols()
	      << std::endl;
    abort();
  }
  
  Int_t numParts = (__VMat.GetNrows()-1)/3;
  
  V.ResizeTo(3*(numParts-1)+1,3*(numParts-1)+1);
  Int_t j = (numParts-1)-1;
  
  V(j+1,j+1)= __FitV(0,0);
  V(j+2,j+2)= __FitV(1,1);
  V(j+3,j+3)= __FitV(2,2);
  V(j+1,j+2)= V(j+2,j+1)= __FitV(1,0);
  V(j+3,j+1)= V(j+1,j+3)= __FitV(0,2);
  V(j+2,j+3)= V(j+3,j+2)= __FitV(2,1);     
  
  return V;
}

const std::vector<TVector3> VertConvert(std::vector<TVector3> &__vert){
  //assume VERT bank vertex and adjusts to D0 Z0 resolutions
  for(int i=0;i<2;i++){
    __vert[i].SetY(__vert[i].Y()+gRandom->Gaus(0,0.43)); 
    __vert[i].SetX(__vert[i].X()+gRandom->Gaus(0,0.43));
    __vert[i].SetZ(__vert[i].Z()+gRandom->Gaus(0,0.04)); 
  }
  return __vert;
}


const std::vector<TVector3> SmearVector(std::vector<TVector3> &__vert,Double_t sigma){
  //smears each component of the vector by sigma
  for(int i=0;i<2;i++){
    __vert[i].SetY(__vert[i].Y()+gRandom->Gaus(0,sigma)); 
    __vert[i].SetX(__vert[i].X()+gRandom->Gaus(0,sigma));
    __vert[i].SetZ(__vert[i].Z()+gRandom->Gaus(0,sigma)); 
  }
  return __vert;
}

Double_t SmearUtility(){
  Double_t sigma = gRandom->Gaus(0,1);
  return sigma;
}

Double_t SmearUtility(Double_t var,Double_t parm_a, Double_t parm_b, Double_t parm_c){
  Double_t sigma = parm_a*var*var + parm_b*var + parm_c;
  sigma = gRandom->Gaus(0,sigma);
  sigma = exp(-var*var/2*sigma*sigma);
  return sigma;
}

TVector3 TrackToCLAS(Double_t p,Double_t lam,Double_t phi,Double_t alpha){
  TVector3 Vout;
  Double_t px = p*(cos(lam)*sin(phi)*cos(alpha)-sin(lam)*sin(alpha));
  Double_t py = p*(cos(lam)*sin(phi)*sin(alpha)+sin(lam)*cos(alpha));
  Double_t pz = p*cos(lam)*cos(phi);
  Vout.SetXYZ(px,py,pz);
  return Vout;
}


//_____________________________________________________________________________

/// Reads in the CLAS resolution parameters
bool ReadInResParams(double __pPars[2][6][15][3],double __lamPars[2][6][15],
		     double __phiPars[2][6][15]){
  
  std::ifstream *inFile = 0;
  String fileName_base = "./parms/";
  String fileName;
  String p_names[2];
  p_names[0] = "p";
  p_names[1] = "pi";
  int num_rows_read,bin,sector;
  double par[3];
  
  for(int part = 0; part < 2; part++){
    // open |p| pars files
    fileName = fileName_base + "g12parm_mom." + p_names[part];
    inFile = new std::ifstream(fileName.c_str());
    
    if(!(inFile->is_open())){
      // file didn't open
      std::cout << "Error! <ReadInResParams> File read error: " << fileName
		<< " Unable to open file." << std::endl;
      return false;
    }
    
    num_rows_read = 0;
    while(*inFile >> sector){
      num_rows_read++;
      *inFile >> bin >> par[0] >> par[1] >> par[2];
      for(int i = 0; i < 3; i++) __pPars[part][sector-1][bin][i] = par[i];
    }
    
    // check correct number of rows were read in
    if(!CheckRowsRead(fileName,num_rows_read)) return false;
    delete inFile; inFile = 0;
    
    // read in lambda tracking angle pars
    fileName = fileName_base + "g12parm_lam." + p_names[part];
    inFile = new std::ifstream(fileName.c_str());
    
    if(!(inFile->is_open())){
      // file didn't open
      std::cout << "Error! <ReadInResParams> File read error: " << fileName
		<< " Unable to open file." << std::endl;
      return false;
    }
    
    num_rows_read = 0;
    while(*inFile >> sector){
      num_rows_read++;
      *inFile >> bin >> par[0];
      __lamPars[part][sector-1][bin] = par[0];
    }
    
    // check correct number of rows were read in
    if(!CheckRowsRead(fileName,num_rows_read)) return false;
    delete inFile; inFile = 0;
    
    // read in phi tracking angle pars
    fileName = fileName_base + "g12parm_phi." + p_names[part];
    inFile = new std::ifstream(fileName.c_str());
    
    if(!(inFile->is_open())){ // file didn't open
      std::cout << "Error! <ReadInResParams> File read error: " << fileName
		<< " Unable to open file." << std::endl;
      return false;
    }
    
    num_rows_read = 0;
    while(*inFile >> sector){
      num_rows_read++;
      *inFile >> bin >> par[0];
      __phiPars[part][sector-1][bin] = par[0];
    }
    
    // check correct number of rows were read in
    if(!CheckRowsRead(fileName,num_rows_read)) return false;
    delete inFile; inFile = 0;
  }
  
  return true;
}
