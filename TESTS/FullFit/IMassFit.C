#include "IMassFit.h"
#include "TVectorD.h"
#include "TArrayD.h"
#include "TMath.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <locale>
#include <string>

#define MOM 0
#define LAMBDA 1
#define PHI 2
#define PX 1
#define PY 2
#define PZ 3
#define Ee 0

#define INDEX(i) 3*(i)

using std::cout;
using std::ctype;
using std::endl;
using std::locale;
using std::string;
using std::transform;
using std::use_facet;


IMassFit::IMassFit(){
  _ndf = 0;
  _chi2 = 200.;
  _invariantMass = -1.;
}

void IMassFit::_Copy(const IMassFit &__stream){
  _pfout = __stream._pfout;
  _pulls = __stream._pulls;
  _chi2 = __stream._chi2;
  _ndf = __stream._ndf;
  _p4in = __stream._p4in;
  _p4out = __stream._p4out;  
  _VFit = __stream._VFit;
  _VFit.ResizeTo(3,3);
  _V.ResizeTo(__stream._V);
  _V = __stream._V;
  _invariantMass = __stream._invariantMass;
  _p_names = __stream._p_names; 	
  for(int i = 0; i < 3; i++) _sigma_fit[i] = __stream._sigma_fit[i];
}

void IMassFit::_MainFitter(){

  const int numParts = (int)_p4in.size();
  const int dim = 3*numParts; // number of measured quantites
  if(_V.GetNrows() != dim || _V.GetNcols() != dim){
    std::cout << "Error! <IMassFit::_MainFitter> Variance matrix size is NOT "
	      << "correct for current number of particles. For " << numParts
	      << " particles, the Variance matrix should be " << dim << " x "
	      << dim << ", but the matrix passed in is " << _V.GetNrows()
	      << " x " << _V.GetNcols() << std::endl;
    abort();
  }
  
  int num_const=4,num_part=3,num_unk=3,num_meas=dim;
  
  _ndf = 1;
  
  int i;
  double theta[numParts];     
  double alpha[numParts],mass[numParts],lambda[numParts],phi[numParts];
  double p[numParts],erg[numParts],px[numParts],py[numParts],pz[numParts];
    
  TVectorD eta0(dim),eta(dim);  
  TVectorD xi(num_unk),x(num_unk),delx(num_unk),xix(num_unk);  
  TMatrixD d_unk(num_const,num_unk),d_unkT(num_unk,num_const);
  TMatrixD d_kno(num_const,num_meas),d_knoT(num_meas,num_const);
  TVectorD f(num_const);  
  TVectorD eps(dim);  
  TMatrixD epsmatrix(1,dim), epsmatrixT(dim,1);  
  TVectorD delta(dim);  
  TVectorD xsi(3);   
  TMatrixD Gd_kno(num_const,num_const);
  TMatrixD _Vfit(dim,dim);
  TMatrixD particle(num_part,4);  
  String particle_name;
  Float_t _Pmom,_lambda,_phi,cosl,sinl,cosp,sinp,cosa,sina;
  
  for(i = 0; i < numParts; i++) {
    if(_p_names[i] == "n" or _p_names[i] == "gamma") {
      eta0(INDEX(i)+MOM) = _p4in[i].P();
      eta0(INDEX(i)+LAMBDA) = _p4in[i].Theta();
      eta0(INDEX(i)+PHI) = _p4in[i].Phi();	
      if(_p_names[i] == "gamma") mass[i] = 0.00000000;
    }    
    else {
      eta0(INDEX(i)+MOM) = _p4in[i].P(); // |p|
      eta0(INDEX(i)+LAMBDA) = LambdaTrack(_p4in[i]); // tracking angle lambda
      eta0(INDEX(i)+PHI) = PhiTrack(_p4in[i]); // tracking angle phi
      alpha[i] = AlphaTrack(_p4in[i]); // this angle doesn't change
      mass[i] = _p4in[i].M(); // particle's mass
    }
    particle(i,PX)=_p4in[i].Px();
    particle(i,PY)=_p4in[i].Py();
    particle(i,PZ)=_p4in[i].Pz();
    particle(i,Ee)=_p4in[i].E();   	    
  }
  
  eta = eta0; 
  
  double p2=0.0;
  for (i=PX;i<=PZ;i++){
    particle(2,i)=particle(0,i)+particle(1,i);
    p2+=particle(2,i)*particle(2,i);
  }
      
  particle(2,Ee)=sqrt(p2+_invariantMass*_invariantMass);
  
  xi(MOM)=sqrt(p2);
  xi(LAMBDA)=asin(particle(2,PZ)/xi(MOM));
  xi(PHI)=atan2(particle(2,PY),particle(2,PX));
  
  x = xi;  
  
  f(Ee)= particle(0,Ee)+particle(1,Ee)-particle(2,Ee);
  
  d_unk.Zero();
  d_unkT.Zero();
  d_kno.Zero();
  d_knoT.Zero();
  delta.Zero();
  xsi.Zero();
  
  for(int iter = 0; iter < 10; iter++){
        
    for(i = 0; i < numParts; i++){
      if(_p_names[i] == "n" or _p_names[i] == "gamma") {
	p[i] = eta(INDEX(i)+0);
	theta[i] = eta(INDEX(i)+1);
	phi[i] = eta(INDEX(i)+2);
	erg[i] = sqrt(p[i]*p[i] + mass[i]*mass[i]);
	px[i] = p[i]*sin(theta[i])*cos(phi[i]);
	py[i] = p[i]*sin(theta[i])*sin(phi[i]);
	pz[i] = p[i]*cos(theta[i]);
      } 
      else {  	
	p[i] = eta(INDEX(i)+0);
        lambda[i] = eta(INDEX(i)+1);
        phi[i] = eta(INDEX(i)+2);
        erg[i] = sqrt(p[i]*p[i] + mass[i]*mass[i]);
        px[i] = p[i]*(cos(lambda[i])*sin(phi[i])*cos(alpha[i]) 
		      - sin(lambda[i])*sin(alpha[i]));
        py[i] = p[i]*(cos(lambda[i])*sin(phi[i])*sin(alpha[i]) 
		      + sin(lambda[i])*cos(alpha[i]));
        pz[i] = p[i]*cos(lambda[i])*cos(phi[i]);  
      }
    }      
    
    _Pmom=xi(MOM);
    _lambda=xi(LAMBDA);
    _phi=xi(PHI);
    
    cosl=cos(_lambda);
    sinl=sin(_lambda);
    cosp=cos(_phi);
    sinp=sin(_phi);
    
    // derivative of f with respect to unknowns	
    
    d_unk(1,0)=-cosl*cosp;
    d_unk(1,1)=_Pmom*sinl*cosp;
    d_unk(1,2)=_Pmom*cosl*sinp;
    
    d_unk(2,0)=-cosl*sinp;
    d_unk(2,1)=_Pmom*sinl*sinp;
    d_unk(2,2)=-_Pmom*cosl*cosp;
    
    d_unk(3,0)=-sinl;
    d_unk(3,1)=-_Pmom*cosl;  
    d_unk(3,2)=0;	
    
    d_unk(0,0)=-_Pmom/sqrt(_Pmom*_Pmom+_invariantMass*_invariantMass); 
    d_unk(0,1)=0;
    d_unk(0,2)=0;    
    
    // derivative of f with respect to knowns 
    
    d_kno(0,0) = 1.;
    d_kno(3,0) = -1; 

    for(i = 0; i < numParts; i++){               
      if(_p_names[i] == "n" or _p_names[i] == "gamma") {
	d_kno(Ee,INDEX(i)+MOM) = -p[i]/erg[i];
	d_kno(PX,INDEX(i)+MOM) = sin(theta[i])*cos(phi[i]);
	d_kno(PY,INDEX(i)+MOM) = sin(theta[i])*sin(phi[i]);
	d_kno(PZ,INDEX(i)+MOM) = cos(theta[i]);
	d_kno(Ee,INDEX(i)+LAMBDA) = 0.;
	d_kno(PX,INDEX(i)+LAMBDA) = p[i]*cos(theta[i])*cos(phi[i]);
	d_kno(PY,INDEX(i)+LAMBDA) = p[i]*cos(theta[i])*sin(phi[i]);
	d_kno(PZ,INDEX(i)+LAMBDA) = -p[i]*sin(theta[i]);
	d_kno(Ee,INDEX(i)+PHI) = 0.;
	d_kno(PX,INDEX(i)+PHI) = -p[i]*sin(theta[i])*sin(phi[i]);
	d_kno(PY,INDEX(i)+PHI) = p[i]*sin(theta[i])*cos(phi[i]);
	d_kno(PZ,INDEX(i)+PHI) = 0.;
      }	    
      else {    
	d_kno(Ee,INDEX(i)+MOM) = -p[i]/erg[i];
	d_kno(PX,INDEX(i)+MOM) = cos(lambda[i])*sin(phi[i])*cos(alpha[i]) 
	  - sin(lambda[i])*sin(alpha[i]);	
	d_kno(PY,INDEX(i)+MOM) = cos(lambda[i])*sin(phi[i])*sin(alpha[i]) 
	  + sin(lambda[i])*cos(alpha[i]);
	d_kno(PZ,INDEX(i)+MOM) = cos(lambda[i])*cos(phi[i]);	
	d_kno(Ee,INDEX(i)+LAMBDA) = 0.;
	d_kno(PX,INDEX(i)+LAMBDA) = p[i]*(-sin(lambda[i])*sin(phi[i])*cos(alpha[i])
			   - cos(lambda[i])*sin(alpha[i]));
	d_kno(PY,INDEX(i)+LAMBDA) = p[i]*(-sin(lambda[i])*sin(phi[i])*sin(alpha[i])
			   + cos(lambda[i])*cos(alpha[i]));
	d_kno(PZ,INDEX(i)+LAMBDA) = p[i]*(-sin(lambda[i])*cos(phi[i]));
	d_kno(Ee,INDEX(i)+PHI) = 0.;	
	d_kno(PX,INDEX(i)+PHI) = p[i]*cos(lambda[i])*cos(phi[i])*cos(alpha[i]);	
	d_kno(PY,INDEX(i)+PHI) = p[i]*cos(lambda[i])*cos(phi[i])*sin(alpha[i]);	
	d_kno(PZ,INDEX(i)+PHI) = p[i]*cos(lambda[i])*(-sin(phi[i]));
      }    
    }
    
    d_unkT.Transpose(d_unk);    
    d_knoT.Transpose(d_kno);
    Gd_kno = d_kno * _V * d_knoT;  

    Gd_kno.Invert();
    
    xsi = ((d_unkT * Gd_kno * d_unk).Invert())*(d_unkT * Gd_kno * f); 
    x -= xsi;
    delta = _V * d_knoT * Gd_kno * (f - d_unk*xsi);

    eta -= delta;
    
    // Store the new values for the particle 4-vectors 
    
    _Pmom=xi(MOM);
    _lambda=xi(LAMBDA);
    _phi=xi(PHI);      
    cosl=cos(_lambda);
    sinl=sin(_lambda);
    cosp=cos(_phi);
    sinp=sin(_phi);
    
    particle(2,PX)=_Pmom*cosl*cosp;
    particle(2,PY)=_Pmom*cosl*sinp;
    particle(2,PZ)=_Pmom*sinl;
    particle(2,Ee)=sqrt(_Pmom*_Pmom+_invariantMass*_invariantMass);
    
    for (i=0;i<2;i++){
      mass[i] = _p4in[i].M();
      alpha[i] = AlphaTrack(_p4in[i]);
      _Pmom=eta(INDEX(i)+MOM);
      _lambda=eta(INDEX(i)+LAMBDA);
      _phi=eta(INDEX(i)+PHI);
      
      cosl=cos(_lambda);
      sinl=sin(_lambda);
      cosp=cos(_phi);
      sinp=sin(_phi);
      cosa=cos(alpha[i]);
      sina=sin(alpha[i]);  
      
      particle(i,PX)=_Pmom*(cosl*sinp*cosa-sinl*sina);
      particle(i,PY)=_Pmom*(cosl*sinp*sina+sinl*cosa);
      particle(i,PZ)=_Pmom*cosl*cosp;
      particle(i,Ee)=sqrt(_Pmom*_Pmom+mass[i]*mass[i]);
    }

    // Compute the new value for the constraint vector f
    
    for (i=0;i<4;i++) {
      f(i)=particle(0,i)+particle(1,i)-particle(2,i);
    }    
        
    eps = eta0 - eta;
    
    TMatrixDColumn(epsmatrixT,0) = eps;
    epsmatrix.Transpose(epsmatrixT);
    _chi2 = (epsmatrix * d_knoT * Gd_kno * d_kno * epsmatrixT)(0,0); 
    
    if(TMath::Prob(_chi2,_ndf) < 1.e-10) break;
    
  } 
  
  eps = eta0 - eta;
  TMatrixDColumn(epsmatrixT,0) = eps;
  
  _Vfit = _V - _V*d_knoT*Gd_kno*d_kno*_V 
    + _V*d_knoT*Gd_kno*d_unk*((d_unkT*Gd_kno*d_unk).Invert())*d_unkT*Gd_kno*d_kno*_V;
  
  _pulls.resize(dim);
  for(i = 0; i < dim; i++)
    _pulls[i] = -eps(i)/sqrt(_V(i,i) - _Vfit(i,i));
  _chi2 = (epsmatrix * d_knoT * Gd_kno * d_kno * epsmatrixT)(0,0); 
  _p4out.resize(numParts);
  for(i = 0; i < numParts; i++) _p4out[i].SetPxPyPzE(px[i],py[i],pz[i],erg[i]);
  
  _pfout.SetPxPyPzE(particle(2,PX),particle(2,PY),particle(2,PZ),particle(2,Ee));  
  
  xix(0)=particle(2,PX);
  xix(1)=particle(2,PY);  
  xix(2)=particle(2,PZ);
    
  this->_SetNewFitV((d_unkT * Gd_kno * d_unk).Invert(),xix);  
  this->_SetFitParticleErrors((d_unkT * Gd_kno * d_unk).Invert(),xix);  
}

void IMassFit::_ResetForNewFit(){
  int size = (int)_p4in.size();
  _p4out.resize(size);
  _pulls.resize(3*size);
  
  for(int i = 0; i < 3; i++) _sigma_fit[i] = 0.;
}

double IMassFit::Fit(double __invariantMass){
  
  this->_ResetForNewFit();
  
  _invariantMass = __invariantMass;
  // run the fit
  this->_MainFitter();
  
  // return the confidence level
  return this->Prob();
  
}

void IMassFit::_ZeroOutFit(){
  for(int i = 0; i < (int)_pulls.size(); i++) _pulls[i] = 0.0;
  _chi2 = 0.0;
  _ndf = 0;
  for(int i = 0; i < (int)_p4out.size(); i++) _p4out[i].SetXYZT(0.,0.,0.,0.);  
}

void IMassFit::_SetFitParticleErrors(const TMatrixD &__fitpartV,
				     const TVectorD &__x){
  
  double p = sqrt(__x(0)*__x(0) + __x(1)*__x(1) + __x(2)*__x(2));
  TLorentzVector p4(__x(0),__x(1),__x(2),sqrt(p*p + pow(_invariantMass,2)));
  
  // kinematic quantities in tracking coordinates
  double phi = PhiTrack(p4);
  double lam = LambdaTrack(p4);
  double alpha = AlphaTrack(p4);
  
  // fit particle errors in lab coordinates
  double sigma_px_2 = __fitpartV(0,0);
  double sigma_py_2 = __fitpartV(1,1);
  double sigma_pz_2 = __fitpartV(2,2);
  
  // jacobian elements needed
  double dp_dpx = __x(0)/p;
  double dp_dpy = __x(1)/p;
  double dp_dpz = __x(2)/p;
  
  double dlam_dpx = (-sin(alpha) - sin(lam)*dp_dpx)/(p*cos(lam));
  double dlam_dpy = (cos(alpha) - sin(lam)*dp_dpy)/(p*cos(lam));
  double dlam_dpz = -tan(lam)*dp_dpz/p;
  
  double dphi_dpx = (sin(lam)*p*cos(phi)*dlam_dpx - dp_dpx*cos(lam)*cos(phi))
    /(-sin(phi)*p*cos(lam));
  double dphi_dpy = (sin(lam)*p*cos(phi)*dlam_dpy - dp_dpy*cos(lam)*cos(phi))
    /(-sin(phi)*p*cos(lam));
  double dphi_dpz = (1 + sin(lam)*p*cos(phi)*dlam_dpz 
		     - dp_dpz*cos(lam)*cos(phi))/(-sin(phi)*p*cos(lam));
  
  // get error on p
  _sigma_fit[0] = sqrt(sigma_px_2*(dp_dpx*dp_dpx) 
			   + sigma_py_2*(dp_dpy*dp_dpy)
			   + sigma_pz_2*(dp_dpz*dp_dpz));
  
  // get error on lambda
  _sigma_fit[1] = sqrt(sigma_px_2*(dlam_dpx*dlam_dpx) 
			   + sigma_py_2*(dlam_dpy*dlam_dpy)
			   + sigma_pz_2*(dlam_dpz*dlam_dpz));
  
  // get error on phi
  _sigma_fit[2] = sqrt(sigma_px_2*(dphi_dpx*dphi_dpx) 
			   + sigma_py_2*(dphi_dpy*dphi_dpy)
			   + sigma_pz_2*(dphi_dpz*dphi_dpz));
  
}

void IMassFit::_SetNewFitV(const TMatrixD &__fitpartV,
				     const TVectorD &__x){
  _VFit.ResizeTo(3,3);
    
  double p = sqrt(__x(0)*__x(0) + __x(1)*__x(1) + __x(2)*__x(2));
  TLorentzVector p4(__x(0),__x(1),__x(2),sqrt(p*p + pow(_invariantMass,2)));
  
  // kinematic quantities in tracking coordinates
  double phi = PhiTrack(p4);
  double lam = LambdaTrack(p4);
  double alpha = AlphaTrack(p4);
  
  // fit particle errors in lab coordinates
  double sigma_px_2 = __fitpartV(0,0);
  double sigma_py_2 = __fitpartV(1,1);
  double sigma_pz_2 = __fitpartV(2,2);
  
  // jacobian elements needed
  double dp_dpx = __x(0)/p;
  double dp_dpy = __x(1)/p;
  double dp_dpz = __x(2)/p;
  
  double dlam_dpx = (-sin(alpha) - sin(lam)*dp_dpx)/(p*cos(lam));
  double dlam_dpy = (cos(alpha) - sin(lam)*dp_dpy)/(p*cos(lam));
  double dlam_dpz = -tan(lam)*dp_dpz/p;
  
  double dphi_dpx = (sin(lam)*p*cos(phi)*dlam_dpx - dp_dpx*cos(lam)*cos(phi))
    /(-sin(phi)*p*cos(lam));
  double dphi_dpy = (sin(lam)*p*cos(phi)*dlam_dpy - dp_dpy*cos(lam)*cos(phi))
    /(-sin(phi)*p*cos(lam));
  double dphi_dpz = (1 + sin(lam)*p*cos(phi)*dlam_dpz 
		     - dp_dpz*cos(lam)*cos(phi))/(-sin(phi)*p*cos(lam));
  
  _VFit(0,0) = sigma_px_2*(dp_dpx*dp_dpx) 
			   + sigma_py_2*(dp_dpy*dp_dpy)
			   + sigma_pz_2*(dp_dpz*dp_dpz);
			   
  _VFit(1,1) = sigma_px_2*(dlam_dpx*dlam_dpx) 
			   + sigma_py_2*(dlam_dpy*dlam_dpy)
			   + sigma_pz_2*(dlam_dpz*dlam_dpz);
  
  _VFit(2,2) = sigma_px_2*(dphi_dpx*dphi_dpx) 
			   + sigma_py_2*(dphi_dpy*dphi_dpy)
			   + sigma_pz_2*(dphi_dpz*dphi_dpz);			   
			     
  _VFit(1,0) = sigma_px_2*(dp_dpx*dlam_dpx) 
			   + sigma_py_2*(dp_dpy*dlam_dpy)
			   + sigma_pz_2*(dp_dpz*dlam_dpz);
			   
  _VFit(0,1) = _VFit(1,0);
    
  _VFit(2,0) = sigma_px_2*(dp_dpx*dphi_dpx) 
			   + sigma_py_2*(dp_dpy*dphi_dpy)
			   + sigma_pz_2*(dp_dpz*dphi_dpz);
			   			   
  _VFit(0,2) = _VFit(2,0);  
    
  _VFit(2,1) = sigma_px_2*(dlam_dpx*dphi_dpx) 
			   + sigma_py_2*(dlam_dpy*dphi_dpy)
			   + sigma_pz_2*(dlam_dpz*dphi_dpz);
			     			     
  _VFit(1,2) = _VFit(2,1); 
  
}
