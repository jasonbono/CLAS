#ifndef DATAEXIBINS_H
#define DATAEXIBINS_H

//for 3 and 3 binning
const int Nb = 2; //nuber of bin types
const int Nc = 3; //number of e and xi bins
TCut EXibin[Nb][Nc];
const char* EXibinString[Nb][Nc];
//Double_t EVal[Nb + 1][Nc];
Double_t XVal[Nb][Nc + 1]; 
XVal[0][0] = 1000;
EXibin[0][0] = " beam > 2.8000 && beam < 3.8125 && Xcmtheta > -1 && Xcmtheta < 1 " ;
EXibin[0][1] = " beam > 3.8125 && beam < 4.4335 && Xcmtheta > -1 && Xcmtheta < 1 " ;
EXibin[0][2] = " beam > 4.4335 && beam < 5.5000 && Xcmtheta > -1 && Xcmtheta < 1 " ;
EXibin[1][0] = " beam > 2.8000 && beam < 5.5000 && Xcmtheta > -1 && Xcmtheta < -0.6100 " ;
EXibin[1][1] = " beam > 2.8000 && beam < 5.5000 && Xcmtheta > -0.6100 && Xcmtheta < -0.1900 " ;
EXibin[1][2] = " beam > 2.8000 && beam < 5.5000 && Xcmtheta > -0.1900 && Xcmtheta < 1 " ;


EXibinString[0][0] = " 2.80 <  E_{#gamma} < 3.81 :: -1 < cos(#theta_{#Xi}^{cm}) < 1 " ;
EXibinString[0][1] = " 3.81 <  E_{#gamma} < 4.43 ::  -1 < cos(#theta_{#Xi}^{cm}) < 1 " ;
EXibinString[0][2] = " 4.43 <  E_{#gamma} < 5.50 ::  -1 < cos(#theta_{#Xi}^{cm}) < 1 " ;
EXibinString[1][0] = " 2.80 <  E_{#gamma} < 5.50 ::  -1 < cos(#theta_{#Xi}^{cm}) < -0.61 " ;
EXibinString[1][1] = " 2.80 <  E_{#gamma} < 5.50 ::  -0.61 < cos(#theta_{#Xi}^{cm}) < -0.19 " ;
EXibinString[1][2] = " 2.80 <  E_{#gamma} < 5.50 ::  -0.19 < cos(#theta_{#Xi}^{cm}) < 1 " ;

Double_t PhotonPol[Nb][Nc];
PhotonPol[0][0] = 0.44676;
PhotonPol[0][1] = 0.53868;
PhotonPol[0][2] = 0.59226;
PhotonPol[1][0] = 0.52553;
PhotonPol[1][1] = 0.52553;
PhotonPol[1][2] = 0.52553;



const char* EString[Nb][Nc];
EString[0][0] = "2.8000 <  E_{#gamma} < 3.8125" ; 
EString[0][1] = "3.8125 <  E_{#gamma} < 4.4335"; 
EString[0][2] = "4.4335 <  E_{#gamma} < 5.5000"; 
EString[1][0] = "2.8000 <  E_{#gamma} < 5.5000" ; 
EString[1][1] =  "2.8000 <  E_{#gamma} < 5.5000" ; 
EString[1][2] =  "2.8000 <  E_{#gamma} < 5.5000" ; 

const char* XString[Nb][Nc];
XString[0][0] = "-1 < cos(#theta_{#Xi}^{cm}) < 1" ;
XString[0][1] = "-1 < cos(#theta_{#Xi}^{cm}) < 1" ;
XString[0][2] = "-1 < cos(#theta_{#Xi}^{cm}) < 1" ;
XString[1][0] = "-1 < cos(#theta_{#Xi}^{cm}) < -0.6100" ;
XString[1][1] = "-0.6100 < cos(#theta_{#Xi}^{cm}) < -0.1900 " ; 
XString[1][2] = "-0.1900 < cos(#theta_{#Xi}^{cm}) < 1 " ;
