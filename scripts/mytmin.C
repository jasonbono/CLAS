/* 
Author: Jason Bono (compiled from denis's scripts)
Date: Sep 5 2012
Purpose: to calculate the minimum t transfer 
Usage: 
call tmin
plab=beam
ma=0 (photon mass)
mb=0.938272 (proton mass)
mc=0.493667 (k+ mass)
md=1.32131 (Xi- mass)

*/

//function prototypes
Float_t s(Float_t, Float_t, Float_t);
Float_t pprime(Float_t, Float_t, Float_t);
Float_t ener(Float_t, Float_t);

Float_t tmin(Float_t plab,Float_t ma,Float_t mb,Float_t mc,Float_t md)
{
  Float_t Ea;
  Float_t Ec;
  Float_t pcma;
  Float_t pcmc;
  Float_t w;

  Float_t ret = -1000.0;
 

  w = sqrt(s(plab,ma,mb));
  // check that all masses are greater or equal to 0.0
  if (ma >= 0.0 && mb >= 0.0 && mc >= 0.0 && md >= 0.0) {
    if ((w > ma + mb) && (w >= mc + md)) {
      
      pcma = pprime(w,ma,mb);
      pcmc = pprime(w,mc,md);
      

	  Ea = ener(pcma,ma);
      Ec = ener(pcmc,mc);
      ret = (ma*ma+mc*mc-2.0*Ea*Ec+2.0*pcma*pcmc);
    }
  }
  return(ret);
}

Float_t pprime(Float_t w,Float_t m,Float_t m3)
{
  {
    return(sqrt(0.25*pow(w*w-m*m+m3*m3,2.0)/(w*w)-m3*m3));
  }
}


Float_t s(Float_t pbeam,Float_t mbeam,Float_t mtarget)
{
  {
    return(mbeam*mbeam+mtarget*mtarget+2.0*sqrt(pbeam*pbeam+mbeam*mbeam)*
mtarget);
  }
}


Float_t ener(Float_t p,Float_t m)
{
  {
    return(sqrt(p*p+m*m));
  }
}
