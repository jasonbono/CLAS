#include "VertFit.h"
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
#define _VERT1_1 0
#define _VERT1_2 1
#define _VERT2_1 2
#define _VERT2_2 3
#define _D0 0
#define _Z0 1
#define _Xind 0
#define _Yind 1
#define _Zind 2

#define INDEX(i) 3*(i)

using std::cout;
using std::ctype;
using std::endl;
using std::locale;
using std::string;
using std::transform;
using std::use_facet;


VertFit::VertFit(){
  _ndf = 0;
  _chi2 = 200.;
  _invariantMass = -1.;
}

void VertFit::_Copy(const VertFit &__stream){
  _pulls = __stream._pulls;
  _chi2 = __stream._chi2;
  _ndf = __stream._ndf;
  _p4in = __stream._p4in;
  _p4out = __stream._p4out;  
  _VFit = __stream._VFit;
  _VFit.ResizeTo(2,2);
  _V.ResizeTo(__stream._V);
  _V = __stream._V;
  _invariantMass = __stream._invariantMass;
  _p_names = __stream._p_names; 	
  for(int i = 0; i < 2; i++) _sigma_fit[i] = __stream._sigma_fit[i];
}

void VertFit::_MainFitter(){
  
  const int numParts = (int)_p4in.size();
  const int dim = 2*numParts; // number of measured quantites
  if(_V.GetNrows() != dim || _V.GetNcols() != dim){
    std::cout << "Error! <VertFit::_MainFitter> Variance matrix size is NOT "
	      << "correct for current number of particles. For " << numParts
	      << " particles, the Variance matrix should be " << dim << " x "
	      << dim << ", but the matrix passed in is " << _V.GetNrows()
	      << " x " << _V.GetNcols() << std::endl;
    abort();
  }
  
  int num_const=4,num_part=3,num_unk=3,num_meas=dim;
  
  _ndf = 1;
  
  int i;
  double alpha[numParts],mass[numParts],d0,z0;
    
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
      eta0(2*i+_D0)= _VERTin[i].Y()*cosa-_VERTin[i].X()*sina
	-(_VERTin[i].X()*cosa+_VERTin[i].Y()*sina)
	*tan(LambdaTrack(_p4in[i])/sin(PhiTrack(_p4in[i])));			
      eta0(2*i+_Z0)= (_VERTin[i].X()*cosa+_VERTin[i].Y())
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
      eta0(2*i+_D0) = (_VERTin[i].X()*cosa+_VERTin[i].Y()*sina)
	*cosp-_VERTin[i].Z()*sina;	
      eta0(2*i+_Z0) =_VERTin[i].Y()*cosa-_VERTin[i].X()*sina
	-(_VERTin[i].X()*cosa+_VERTin[i].Y()*sina)*tan(LambdaTrack(_p4in[i]))/
	sinp;
    }
  }
  
  eta = eta0; 
    
  xi(_Xind)= _VERTin[0].X();
  xi(_Yind)= _VERTin[0].Y();
  xi(_Zind)= _VERTin[0].Z();  
  
  x = xi;  
  
  for(i=0;i<2;i++){
    alpha[i] = AlphaTrack(_p4in[i]);
    z0=eta(2*i+_Z0);
    d0=eta(2*i+_D0);
    cosp=cos(PhiTrack(_p4in[i]));
    sinp=sin(PhiTrack(_p4in[i]));
    sinl=sin(LambdaTrack(_p4in[i]));
    cosl=cos(LambdaTrack(_p4in[i]));
    sina=sin(alpha[i]);
    cosa=cos(alpha[i]);
    
    f(_VERT1_1+2*i)=(xi(_Yind)-z0*cosa)*cosl*cosp
      -(xi(_Zind)+d0/sinp)*(cosl*sinp*sina+sinl*cosa);
    f(_VERT1_2+2*i)=(xi(_Xind)+z0*sina)*cosl*cosp
      -(xi(_Zind)+d0/sinp)*(cosl*sinp*cosa-sinl*sina);
  }  
  
  for(int iter = 0; iter < 10; iter++){
    
    for(i = 0; i < numParts; i++){
      
      alpha[i] = AlphaTrack(_p4in[i]);
      mass[i] = _p4in[i].M();
      _Pmom=_p4in[i].P();
      _lambda=LambdaTrack(_p4in[i]);
      _phi=PhiTrack(_p4in[i]);
      z0=eta(2*i+_Z0);
      d0=eta(2*i+_D0);
      
      sina=sin(alpha[i]);
      cosa=cos(alpha[i]);
      sinl=sin(_lambda);
      cosl=cos(_lambda);
      sinp=sin(_phi);
      cosp=cos(_phi);       
      
      // derivative of f with respect to unknowns	
      
      d_unk(_VERT1_1+2*i,_Yind)=cosl*cosp; //check this sign at some point
      d_unk(_VERT1_1+2*i,_Zind)=-cosl*sinp*sina-sinl*cosa;
      d_unk(_VERT1_2+2*i,_Xind)=cosl*cosp;  
      d_unk(_VERT1_2+2*i,_Zind)=-cosl*sinp*cosa+sinl*sina;
      
      // derivative of f with respect to knowns   
      
      d_kno(_VERT1_1+2*i,2*i+_Z0) = -cosa*cosl*cosp;
      d_kno(_VERT1_1+2*i,2*i+_D0) = (-1./sinp)*(cosl*sinp*sina+sinl*cosa);;	
      d_kno(_VERT1_2+2*i,2*i+_Z0) =sina*cosl*cosp;
      d_kno(_VERT1_2+2*i,2*i+_D0) =(-1./sinp)*(cosl*sinp*cosa-sinl*sina);	
      
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
    
    for (i=0;i<2;i++){
      mass[i] = _p4in[i].M();
      alpha[i] = AlphaTrack(_p4in[i]);
      _lambda=LambdaTrack(_p4in[i]);
      _phi=PhiTrack(_p4in[i]);
      
      z0=eta(2*i+_Z0);
      d0=eta(2*i+_D0);
      cosl=cos(_lambda);
      sinl=sin(_lambda);
      cosp=cos(_phi);
      sinp=sin(_phi);
      sina=sin(alpha[i]);
      cosa=cos(alpha[i]);
      
      f(_VERT1_1+2*i)=(xi(_Yind)-z0*cosa)*cosl*cosp
	-(xi(_Zind)+d0/sinp)*(cosl*sinp*sina+sinl*cosa);
      f(_VERT1_2+2*i)=(xi(_Xind)+z0*sina)*cosl*cosp
	-(xi(_Zind)+d0/sinp)*(cosl*sinp*cosa-sinl*sina);
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
  
  z0=eta(2*0+_Z0);
  d0=eta(2*0+_D0);
  alpha[1] = AlphaTrack(_p4in[1]);
  _phi=PhiTrack(_p4in[1]);
  cosa=cos(alpha[1]);
  sina=sin(alpha[1]);
  sinp=sin(_phi);
  
  _Vert.SetXYZ(-z0*sina,z0*cosa,-d0/sinp);
  
  xix(0)=-z0*sina;
  xix(1)=z0*cosa;
  xix(2)=-d0/sinp; 
   
  this->_SetNewFitV((d_unkT * Gd_kno * d_unk).Invert(),xix);  
  this->_SetFitParticleErrors((d_unkT * Gd_kno * d_unk).Invert(),xix);  
  
}

void VertFit::_ResetForNewFit(){
  int size = (int)_p4in.size();
  _p4out.resize(size);
  _pulls.resize(3*size);
  
  for(int i = 0; i < 2; i++) _sigma_fit[i] = 0.;
}

double VertFit::Fit(){
  
  this->_ResetForNewFit();
  
  // run the fit
  this->_MainFitter();
  
  // return the confidence level
  return this->Prob();
}

void VertFit::_ZeroOutFit(){
  for(int i = 0; i < (int)_pulls.size(); i++) _pulls[i] = 0.0;
  _chi2 = 0.0;
  _ndf = 0;
  for(int i = 0; i < (int)_p4out.size(); i++) _p4out[i].SetXYZT(0.,0.,0.,0.);  
}

  void VertFit::_SetFitParticleErrors(const TMatrixD &__fitpartV,
  const TVectorD &__x){
  
  double p = sqrt(__x(0)*__x(0) + __x(1)*__x(1) + __x(2)*__x(2));
  TLorentzVector p4(__x(0),__x(1),__x(2),sqrt(p*p + pow(_invariantMass,2)));
  
  // kinematic quantities in tracking coordinates
  double phi = PhiTrack(p4);
  double lam = LambdaTrack(p4);
  double alpha = AlphaTrack(p4);
 
  double sigma_x_2 = __fitpartV(0,0);
  double sigma_y_2 = __fitpartV(1,1);
  double sigma_z_2 = __fitpartV(2,2);   

  double dD0_dx = cos(alpha)*cos(phi); 
  double dD0_dy = sin(alpha)*cos(phi);  
  double dD0_dz = -sin(alpha);
  
  double dZ0_dx = -sin(alpha)-cos(alpha)*tan(lam)/sin(phi); 
  double dZ0_dy = cos(alpha)+sin(alpha)*tan(lam)/sin(phi);  
  double dZ0_dz = 0;   
 
  // get error on d0
  _sigma_fit[0] = sqrt(sigma_x_2*(dD0_dx*dD0_dx) 
  + sigma_y_2*(dD0_dy*dD0_dy)
  + sigma_z_2*(dD0_dz*dD0_dz));
  
  // get error on z0
  _sigma_fit[1] = sqrt(sigma_x_2*(dZ0_dx*dZ0_dx) 
  + sigma_y_2*(dZ0_dy*dZ0_dy)
  + sigma_z_2*(dZ0_dz*dZ0_dz));  
  
  }
  
  void VertFit::_SetNewFitV(const TMatrixD &__fitpartV,
  const TVectorD &__x){
  _VFit.ResizeTo(2,2);
  
  double p = sqrt(__x(0)*__x(0) + __x(1)*__x(1) + __x(2)*__x(2));
  TLorentzVector p4(__x(0),__x(1),__x(2),sqrt(p*p + pow(_invariantMass,2)));
  
  // kinematic quantities in tracking coordinates
  double phi = PhiTrack(p4);
  double lam = LambdaTrack(p4);
  double alpha = AlphaTrack(p4);
  
  double sigma_x_2 = __fitpartV(0,0);
  double sigma_y_2 = __fitpartV(1,1);
  double sigma_z_2 = __fitpartV(2,2);  
    
  double dD0_dx = cos(alpha)*cos(phi); 
  double dD0_dy = sin(alpha)*cos(phi);  
  double dD0_dz = -sin(alpha);
  
  double dZ0_dx = -sin(alpha)-cos(alpha)*tan(lam)/sin(phi); 
  double dZ0_dy = cos(alpha)+sin(alpha)*tan(lam)/sin(phi);  
  double dZ0_dz = 0;      
  
  
  _VFit(0,0) = sqrt(sigma_x_2*(dD0_dx*dD0_dx) 
  + sigma_y_2*(dD0_dy*dD0_dy)
  + sigma_z_2*(dD0_dz*dD0_dz));
    
  _VFit(1,1) = sqrt(sigma_x_2*(dZ0_dx*dZ0_dx) 
  + sigma_y_2*(dZ0_dy*dZ0_dy)
  + sigma_z_2*(dZ0_dz*dZ0_dz));    
       
  _VFit(1,0) = sigma_x_2*(dZ0_dx*dD0_dx) 
  + sigma_y_2*(dZ0_dy*dD0_dy)
  + sigma_z_2*(dZ0_dz*dD0_dz);  
  
  _VFit(0,1) = _VFit(0,1);    
  
  }

