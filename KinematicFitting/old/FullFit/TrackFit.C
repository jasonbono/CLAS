#include "TrackFit.h"
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
#define D0 3
#define Z0 4
#define PX 1
#define PY 2
#define PZ 3
#define Ee 0
#define VERT1_1 4
#define VERT1_2 5
#define VERT2_1 6
#define VERT2_2 7
#define Xind 3
#define Yind 4
#define Zind 5
#define FDEX(i) 5*(i)

using std::cout;
using std::ctype;
using std::endl;
using std::locale;
using std::string;
using std::transform;
using std::use_facet;


TrackFit::TrackFit(){
  _ndf = 0;
  _chi2 = 200.;
  _invariantMass = -1.;
}

void TrackFit::_Copy(const TrackFit &__stream){
  _pfout = __stream._pfout;
  _pulls = __stream._pulls;
  _chi2 = __stream._chi2;
  _ndf = __stream._ndf;
  _p4in = __stream._p4in;
  _p4out = __stream._p4out;  
  _VFit = __stream._VFit;
  _VFit.ResizeTo(5,5);
  _V.ResizeTo(__stream._V);
  _V = __stream._V;
  _invariantMass = __stream._invariantMass;
  _p_names = __stream._p_names; 	
  for(int i = 0; i < 5; i++) _sigma_fit[i] = __stream._sigma_fit[i];
}

void TrackFit::_MainFitter(){
  
  const int numParts = (int)_p4in.size();
  const int dim = 5*numParts; // number of measured quantites
  if(_V.GetNrows() != dim || _V.GetNcols() != dim){
    std::cout << "Error! <TrackFit::_MainFitter> Variance matrix size is NOT "
	      << "correct for current number of particles. For " << numParts
	      << " particles, the Variance matrix should be " << dim << " x "
	      << dim << ", but the matrix passed in is " << _V.GetNrows()
	      << " x " << _V.GetNcols() << std::endl;
    abort();
  }
  
  int num_const=8,num_part=3,num_unk=6,num_meas=dim;
  
  _ndf = 2;
  
  int i;
  double theta[numParts];     
  double alpha[numParts],mass[numParts],lambda[numParts],phi[numParts];
  double p[numParts],erg[numParts],px[numParts],py[numParts],pz[numParts];
  Float_t d0,z0;
    
  TVectorD eta0(dim),eta(dim);  
  TVectorD xi(num_unk),x(num_unk),delx(num_unk),xix(num_unk);  
  TMatrixD d_unk(num_const,num_unk),d_unkT(num_unk,num_const);
  TMatrixD d_kno(num_const,num_meas),d_knoT(num_meas,num_const);
  TVectorD f(num_const);  
  TVectorD eps(dim);  
  TMatrixD epsmatrix(1,dim), epsmatrixT(dim,1);  
  TVectorD delta(dim);  
  TVectorD xsi(num_unk);   
  TMatrixD Gd_kno(num_const,num_const);
  TMatrixD _Vfit(dim,dim);
  TMatrixD particle(num_part,4);  
  String particle_name;
  Float_t _Pmom,_lambda,_phi,cosl,sinl,cosp,sinp,cosa,sina;
  
  for(i = 0; i < numParts; i++){
    if(_p_names[i] == "n" || _p_names[i] == "gamma"){
      mass[i] = _p4in[i].M();
      alpha[i] = AlphaTrack(_p4in[i]);
      cosp=cos(PhiTrack(_p4in[i]));
      sinp=sin(PhiTrack(_p4in[i]));
      sinl=sin(LambdaTrack(_p4in[i]));
      cosl=cos(LambdaTrack(_p4in[i]));
      sina=sin(alpha[i]);
      cosa=cos(alpha[i]);
      eta0(FDEX(i)+MOM) = _p4in[i].P();
      eta0(FDEX(i)+LAMBDA) = _p4in[i].Theta();
      eta0(FDEX(i)+PHI) = _p4in[i].Phi();            
      eta0(FDEX(i)+D0)= _VERTin[i].Y()*cosa-_VERTin[i].X()*sina
	-(_VERTin[i].X()*cosa+_VERTin[i].Y()*sina)
	*tan(LambdaTrack(_p4in[i])/sin(PhiTrack(_p4in[i])));		
      eta0(FDEX(i)+Z0)= (_VERTin[i].X()*cosa+_VERTin[i].Y())
	*cos(_p4in[i].Phi())-_VERTin[i].Z()*sina;
    }    
    else {
      mass[i] = _p4in[i].M();
      alpha[i] = AlphaTrack(_p4in[i]);
      cosp=cos(PhiTrack(_p4in[i]));
      sinp=sin(PhiTrack(_p4in[i]));
      sinl=sin(LambdaTrack(_p4in[i]));
      cosl=cos(LambdaTrack(_p4in[i]));
      sina=sin(alpha[i]);
      cosa=cos(alpha[i]);		
      eta0(FDEX(i)+MOM) = _p4in[i].P(); // |p|
      eta0(FDEX(i)+LAMBDA) = LambdaTrack(_p4in[i]); // tracking angle lambda
      eta0(FDEX(i)+PHI) = PhiTrack(_p4in[i]); // tracking angle phi    
      eta0(FDEX(i)+D0) = (_VERTin[i].X()*cosa+_VERTin[i].Y()*sina)
	*cosp-_VERTin[i].Z()*sina;	
      eta0(FDEX(i)+Z0) =_VERTin[i].Y()*cosa-_VERTin[i].X()*sina
	-(_VERTin[i].X()*cosa+_VERTin[i].Y()*sina)
	*tan(LambdaTrack(_p4in[i]))/sinp;
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
    xi(Xind)= _VERTin[0].X();
    xi(Yind)= _VERTin[0].Y();
    xi(Zind)= _VERTin[0].Z();  
    
    x = xi;    
    
    f(Ee)= particle(0,Ee)+particle(1,Ee)-particle(2,Ee);    
    
  
  
  for(i=0;i<2;i++){
      alpha[i] = AlphaTrack(_p4in[i]);
      z0=eta(FDEX(i)+Z0);
      d0=eta(FDEX(i)+D0);
      cosp=cos(eta(FDEX(i)+PHI));
      sinp=sin(eta(FDEX(i)+PHI));
      sinl=sin(eta(FDEX(i)+LAMBDA));
      cosl=cos(eta(FDEX(i)+LAMBDA));
      sina=sin(alpha[i]);
      cosa=cos(alpha[i]);
    
    f(VERT1_1+2*i)=(xi(Yind)-z0*cosa)*cosl*cosp
      -(xi(Zind)+d0/sinp)*(cosl*sinp*sina+sinl*cosa);
    f(VERT1_2+2*i)=(xi(Xind)+z0*sina)*cosl*cosp
      -(xi(Zind)+d0/sinp)*(cosl*sinp*cosa-sinl*sina);
  }  
  
  d_unk.Zero();
  d_unkT.Zero();
  d_kno.Zero();
  d_knoT.Zero();
  delta.Zero();
  xsi.Zero();  
 
  for(int iter = 0; iter < 10; iter++){
     
    for(i = 0; i < numParts; i++){
      if(_p_names[i] == "n" || _p_names[i] == "gamma") {
	p[i] = eta(FDEX(i)+0);
	theta[i] = eta(FDEX(i)+1);
	phi[i] = eta(FDEX(i)+2);
	erg[i] = sqrt(p[i]*p[i] + mass[i]*mass[i]);
	px[i] = p[i]*sin(theta[i])*cos(phi[i]);
	py[i] = p[i]*sin(theta[i])*sin(phi[i]);
	pz[i] = p[i]*cos(theta[i]);
      } 
      else {  	
	p[i] = eta(FDEX(i)+0);
        lambda[i] = eta(FDEX(i)+1);
        phi[i] = eta(FDEX(i)+2);
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

    d_unk(PX,MOM)=-cosl*cosp;
    d_unk(PX,LAMBDA)=_Pmom*sinl*cosp;
    d_unk(PX,PHI)=_Pmom*cosl*sinp;
    
    d_unk(PY,MOM)=-cosl*sinp;
    d_unk(PY,LAMBDA)=_Pmom*sinl*sinp;
    d_unk(PY,PHI)=-_Pmom*cosl*cosp;
    
    d_unk(PZ,MOM)=-sinl;
    d_unk(PZ,LAMBDA)=-_Pmom*cosl;  
    d_unk(PZ,PHI)=0;	
    
    d_unk(Ee,MOM)=-_Pmom/sqrt(_Pmom*_Pmom+_invariantMass*_invariantMass); 
    d_unk(Ee,LAMBDA)=0;
    d_unk(Ee,PHI)=0;    

    for(i = 0; i < numParts; i++){
      alpha[i] = AlphaTrack(_p4in[i]);
      mass[i] = _p4in[i].M();
      erg[i] = sqrt(p[i]*p[i] + mass[i]*mass[i]);
      _Pmom=fabs(_p4in[i].P());
      _lambda=LambdaTrack(_p4in[i]);
      _phi=PhiTrack(_p4in[i]);
      z0=eta(FDEX(i)+Z0);
      d0=eta(FDEX(i)+D0);
      
      Float_t x=xi(Xind);
      Float_t y=xi(Yind);
      Float_t z=xi(Zind);
      
      sina=sin(alpha[i]);
      cosa=cos(alpha[i]);
      sinl=sin(_lambda);
      cosl=cos(_lambda);
      sinp=sin(_phi);
      cosp=cos(_phi);       
      
      d_unk(VERT1_1+2*i,Yind)=cosl*cosp; //check this sign at some point
      d_unk(VERT1_1+2*i,Zind)=-cosl*sinp*sina-sinl*cosa;
      d_unk(VERT1_2+2*i,Xind)=cosl*cosp;  
      d_unk(VERT1_2+2*i,Zind)=-cosl*sinp*cosa+sinl*sina;
      
      // derivative of f with respect to knowns   
      
      d_kno(VERT1_1+2*i,FDEX(i)+Z0) = -cosa*cosl*cosp;
      d_kno(VERT1_1+2*i,FDEX(i)+D0) = (-1./sinp)*(cosl*sinp*sina+sinl*cosa);;	
      d_kno(VERT1_1+2*i,FDEX(i)+LAMBDA)=
	  (z0*cosa-y)*sinl*cosp+(z+d0/sinp)*(sinl*sinp*sina-cosl*cosa);
      d_kno(VERT1_1+2*i,FDEX(i)+PHI)=
	  (z0*cosa-y)*cosl*sinp-z*cosl*cosp*sina+d0*sinl*cosa*cosp/sinp/sinp;
      d_kno(VERT1_2+2*i,FDEX(i)+Z0) =sina*cosl*cosp;
      d_kno(VERT1_2+2*i,FDEX(i)+D0) =(-1./sinp)*(cosl*sinp*cosa-sinl*sina);	
      d_kno(VERT1_2+2*i,FDEX(i)+LAMBDA)=
	  (-1.)*(x+z0*sina)*sinl*cosp+(z+d0/sinp)*(sinl*sinp*cosa+cosl*sina);
      d_kno(VERT1_2+2*i,FDEX(i)+PHI)
	  =(-1.)*(x+z0*sina)*cosl*sinp-z*cosl*cosp*cosa
	  -d0*sinl*sina*cosp/sinp/sinp;

      if(_p_names[i] == "n" ||  _p_names[i] == "gamma") {
	d_kno(Ee,FDEX(i)+MOM) = -p[i]/erg[i];
	d_kno(PX,FDEX(i)+MOM) = sin(theta[i])*cos(phi[i]);
	d_kno(PY,FDEX(i)+MOM) = sin(theta[i])*sin(phi[i]);
	d_kno(PZ,FDEX(i)+MOM) = cos(theta[i]);
	d_kno(Ee,FDEX(i)+LAMBDA) = 0.;
	d_kno(PX,FDEX(i)+LAMBDA) = p[i]*cos(theta[i])*cos(phi[i]);
	d_kno(PY,FDEX(i)+LAMBDA) = p[i]*cos(theta[i])*sin(phi[i]);
	d_kno(PZ,FDEX(i)+LAMBDA) = -p[i]*sin(theta[i]);
	d_kno(Ee,FDEX(i)+PHI) = 0.;
	d_kno(PX,FDEX(i)+PHI) = -p[i]*sin(theta[i])*sin(phi[i]);
	d_kno(PY,FDEX(i)+PHI) = p[i]*sin(theta[i])*cos(phi[i]);
	d_kno(PZ,FDEX(i)+PHI) = 0.;
      }	    
      else {  
      	d_kno(Ee,FDEX(i)+MOM) = -p[i]/erg[i];
	d_kno(PX,FDEX(i)+MOM) = cos(lambda[i])*sin(phi[i])*cos(alpha[i]) 
	  - sin(lambda[i])*sin(alpha[i]);	
	d_kno(PY,FDEX(i)+MOM) = cos(lambda[i])*sin(phi[i])*sin(alpha[i]) 
	  + sin(lambda[i])*cos(alpha[i]);
	d_kno(PZ,FDEX(i)+MOM) = cos(lambda[i])*cos(phi[i]);	
	d_kno(Ee,FDEX(i)+LAMBDA) = 0.;
	d_kno(PX,FDEX(i)+LAMBDA) = p[i]*(-sin(lambda[i])*sin(phi[i])*cos(alpha[i])
			   - cos(lambda[i])*sin(alpha[i]));
	d_kno(PY,FDEX(i)+LAMBDA) = p[i]*(-sin(lambda[i])*sin(phi[i])*sin(alpha[i])
			   + cos(lambda[i])*cos(alpha[i]));
	d_kno(PZ,FDEX(i)+LAMBDA) = p[i]*(-sin(lambda[i])*cos(phi[i]));
	d_kno(Ee,FDEX(i)+PHI) = 0.;	
	d_kno(PX,FDEX(i)+PHI) = p[i]*cos(lambda[i])*cos(phi[i])*cos(alpha[i]);	
	d_kno(PY,FDEX(i)+PHI) = p[i]*cos(lambda[i])*cos(phi[i])*sin(alpha[i]);	
	d_kno(PZ,FDEX(i)+PHI) = p[i]*cos(lambda[i])*(-sin(phi[i]));
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
      for(i=0;i<2;i++){
         mass[i] = _p4in[i].M();
	 alpha[i] = AlphaTrack(_p4in[i]);
	_Pmom=fabs(eta(FDEX(i)+MOM));
	_lambda=eta(FDEX(i)+LAMBDA);
	_phi=eta(FDEX(i)+PHI);
	
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
          

    for (i=0;i<2;i++){
      mass[i] = _p4in[i].M();
      alpha[i] = AlphaTrack(_p4in[i]);
      _lambda=LambdaTrack(_p4in[i]);
      _phi=PhiTrack(_p4in[i]);
      
      z0=eta(FDEX(i)+Z0);
      d0=eta(FDEX(i)+D0);
      cosl=cos(_lambda);
      sinl=sin(_lambda);
      cosp=cos(_phi);
      sinp=sin(_phi);
      sina=sin(alpha[i]);
      cosa=cos(alpha[i]);
      
      f(VERT1_1+2*i)=(xi(Yind)-z0*cosa)*cosl*cosp
	-(xi(Zind)+d0/sinp)*(cosl*sinp*sina+sinl*cosa);
      f(VERT1_2+2*i)=(xi(Xind)+z0*sina)*cosl*cosp
	-(xi(Zind)+d0/sinp)*(cosl*sinp*cosa-sinl*sina);
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

  z0=eta(5*0+Z0);
  d0=eta(5*0+D0);
  alpha[1] = AlphaTrack(_p4in[1]);
  _phi=PhiTrack(_p4in[1]);
  cosa=cos(alpha[1]);
  sina=sin(alpha[1]);
  sinp=sin(_phi);
  
  _Vert.SetXYZ(-z0*sina,z0*cosa,-d0/sinp);
  _pfout.SetPxPyPzE(particle(2,PX),particle(2,PY),particle(2,PZ),particle(2,Ee)); 

  xix(0)=particle(2,PX);
  xix(1)=particle(2,PY);  
  xix(2)=particle(2,PZ);
  xix(3)=-z0*sina;
  xix(4)=z0*cosa;
  xix(5)=-d0/sinp;
       
  this->_SetNewFitV((d_unkT * Gd_kno * d_unk).Invert(),xix);  
  this->_SetFitParticleErrors((d_unkT * Gd_kno * d_unk).Invert(),xix);  
  
}

void TrackFit::_ResetForNewFit(){
  int size = (int)_p4in.size();
  _p4out.resize(size);
  _pulls.resize(5*size);
  
  for(int i = 0; i < 3; i++) _sigma_fit[i] = 0.;
}

double TrackFit::Fit(double __invariantMass){
  
  this->_ResetForNewFit();
  
  _invariantMass = __invariantMass;
  // run the fit
  this->_MainFitter();
  
  // return the confidence level
  return this->Prob();
  
}


void TrackFit::_ZeroOutFit(){
  for(int i = 0; i < (int)_pulls.size(); i++) _pulls[i] = 0.0;
  _chi2 = 0.0;
  _ndf = 0;
  for(int i = 0; i < (int)_p4out.size(); i++) _p4out[i].SetXYZT(0.,0.,0.,0.);  
}

  void TrackFit::_SetFitParticleErrors(const TMatrixD &__fitpartV,
  const TVectorD &__x){
  
  double p = sqrt(__x(0)*__x(0) + __x(1)*__x(1) + __x(2)*__x(2));
  TLorentzVector p4(__x(0),__x(1),__x(2),sqrt(p*p + pow(_invariantMass,2)));
  
  double phi = PhiTrack(p4);
  double lam = LambdaTrack(p4);
  double alpha = AlphaTrack(p4);
  
  double sigma_px_2 = __fitpartV(0,0);
  double sigma_py_2 = __fitpartV(1,1);
  double sigma_pz_2 = __fitpartV(2,2);
  
  double sigma_x_2 = __fitpartV(3,3);
  double sigma_y_2 = __fitpartV(4,4);
  double sigma_z_2 = __fitpartV(5,5);  
  
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

  double dD0_dx = cos(alpha)*cos(phi); 
  double dD0_dy = sin(alpha)*cos(phi);  
  double dD0_dz = -sin(alpha);
  
  double dZ0_dx = -sin(alpha)-cos(alpha)*tan(lam)/sin(phi); 
  double dZ0_dy = cos(alpha)+sin(alpha)*tan(lam)/sin(phi);  
  double dZ0_dz = 0;    
    
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
   
  // get error on d0
  _sigma_fit[3] = sqrt(sigma_x_2*(dD0_dx*dD0_dx) 
  + sigma_y_2*(dD0_dy*dD0_dy)
  + sigma_z_2*(dD0_dz*dD0_dz));
  
  // get error on z0
  _sigma_fit[4] = sqrt(sigma_x_2*(dZ0_dx*dZ0_dx) 
  + sigma_y_2*(dZ0_dy*dZ0_dy)
  + sigma_z_2*(dZ0_dz*dZ0_dz));  
  
  
  }
  
  void TrackFit::_SetNewFitV(const TMatrixD &__fitpartV,
  const TVectorD &__x){
  _VFit.ResizeTo(5,5);
  
  double p = sqrt(__x(0)*__x(0) + __x(1)*__x(1) + __x(2)*__x(2));
  TLorentzVector p4(__x(0),__x(1),__x(2),sqrt(p*p + pow(_invariantMass,2)));
  
  double phi = PhiTrack(p4);
  double lam = LambdaTrack(p4);
  double alpha = AlphaTrack(p4);
  
  double sigma_px_2 = __fitpartV(0,0);
  double sigma_py_2 = __fitpartV(1,1);
  double sigma_pz_2 = __fitpartV(2,2);
  
  double sigma_x_2 = __fitpartV(3,3);
  double sigma_y_2 = __fitpartV(4,4);
  double sigma_z_2 = __fitpartV(5,5);  
  
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
  
  double dD0_dx = cos(alpha)*cos(phi); 
  double dD0_dy = sin(alpha)*cos(phi);  
  double dD0_dz = -sin(alpha);
  
  double dZ0_dx = -sin(alpha)-cos(alpha)*tan(lam)/sin(phi); 
  double dZ0_dy = cos(alpha)+sin(alpha)*tan(lam)/sin(phi);  
  double dZ0_dz = 0;      
  
  _VFit(0,0) = sigma_px_2*(dp_dpx*dp_dpx) 
  + sigma_py_2*(dp_dpy*dp_dpy)
  + sigma_pz_2*(dp_dpz*dp_dpz);
  
  _VFit(1,1) = sigma_px_2*(dlam_dpx*dlam_dpx) 
  + sigma_py_2*(dlam_dpy*dlam_dpy)
  + sigma_pz_2*(dlam_dpz*dlam_dpz);
  
  _VFit(2,2) = sigma_px_2*(dphi_dpx*dphi_dpx) 
  + sigma_py_2*(dphi_dpy*dphi_dpy)
  + sigma_pz_2*(dphi_dpz*dphi_dpz);
  
  _VFit(3,3) = sqrt(sigma_x_2*(dD0_dx*dD0_dx) 
  + sigma_y_2*(dD0_dy*dD0_dy)
  + sigma_z_2*(dD0_dz*dD0_dz));
    
  _VFit(4,4) = sqrt(sigma_x_2*(dZ0_dx*dZ0_dx) 
  + sigma_y_2*(dZ0_dy*dZ0_dy)
  + sigma_z_2*(dZ0_dz*dZ0_dz));    
      
  _VFit(1,0) = sigma_px_2*(dp_dpx*dlam_dpx) 
  + sigma_py_2*(dp_dpy*dlam_dpy)
  + sigma_pz_2*(dp_dpz*dlam_dpz);
  
  _VFit(0,1) = _VFit(1,0);
  
  _VFit(2,0) = sigma_px_2*(dp_dpx*dphi_dpx) 
  + sigma_py_2*(dp_dpy*dphi_dpy)
  + sigma_pz_2*(dp_dpz*dphi_dpz);
  
  _VFit(0,2) = _VFit(2,0);  
  
  _VFit(3,0) = sqrt(sigma_x_2)*sqrt(sigma_px_2)*(dD0_dx*dp_dpx) 
  + sqrt(sigma_y_2)*sqrt(sigma_py_2)*(dD0_dy*dp_dpy)
  + sqrt(sigma_z_2)*sqrt(sigma_pz_2)*(dD0_dz*dp_dpz);
  
  _VFit(0,3) = _VFit(3,0); 
  
  _VFit(4,0) = sqrt(sigma_x_2)*sqrt(sigma_px_2)*(dZ0_dx*dp_dpx) 
  + sqrt(sigma_y_2)*sqrt(sigma_py_2)*(dZ0_dy*dp_dpy)
  + sqrt(sigma_z_2)*sqrt(sigma_pz_2)*(dZ0_dz*dp_dpz);
  
  _VFit(0,4) = _VFit(4,0); 
   
  _VFit(2,1) = sigma_px_2*(dlam_dpx*dphi_dpx) 
  + sigma_py_2*(dlam_dpy*dphi_dpy)
  + sigma_pz_2*(dlam_dpz*dphi_dpz);
  
  _VFit(1,2) = _VFit(2,1);  
   
  _VFit(3,1) = sqrt(sigma_x_2)*sqrt(sigma_px_2)*(dD0_dx*dlam_dpx) 
  + sqrt(sigma_y_2)*sqrt(sigma_py_2)*(dD0_dy*dlam_dpy)
  + sqrt(sigma_z_2)*sqrt(sigma_pz_2)*(dD0_dz*dlam_dpz);  
  
  _VFit(1,3) = _VFit(3,1);
  
  _VFit(4,1) = sqrt(sigma_x_2)*sqrt(sigma_px_2)*(dZ0_dx*dlam_dpx) 
  + sqrt(sigma_y_2)*sqrt(sigma_py_2)*(dZ0_dy*dlam_dpy)
  + sqrt(sigma_z_2)*sqrt(sigma_pz_2)*(dZ0_dz*dlam_dpz);  
  
  _VFit(1,4) = _VFit(4,1);  
      
  _VFit(3,2) = sqrt(sigma_x_2)*sqrt(sigma_px_2)*(dD0_dx*dphi_dpx) 
  + sqrt(sigma_y_2)*sqrt(sigma_py_2)*(dD0_dy*dphi_dpy)
  + sqrt(sigma_z_2)*sqrt(sigma_pz_2)*(dD0_dz*dphi_dpz);  
  
  _VFit(2,3) = _VFit(3,2);
  
  _VFit(4,2) = sqrt(sigma_x_2)*sqrt(sigma_px_2)*(dZ0_dx*dphi_dpx) 
  + sqrt(sigma_y_2)*sqrt(sigma_py_2)*(dZ0_dy*dphi_dpy)
  + sqrt(sigma_z_2)*sqrt(sigma_pz_2)*(dZ0_dz*dphi_dpz);  
  
  _VFit(2,4) = _VFit(4,2);  
  
  _VFit(4,3) = sigma_x_2*(dZ0_dx*dD0_dx) 
  + sigma_y_2*(dZ0_dy*dD0_dy)
  + sigma_z_2*(dZ0_dz*dD0_dz);  
  
  _VFit(3,4) = _VFit(4,3);    

  }

