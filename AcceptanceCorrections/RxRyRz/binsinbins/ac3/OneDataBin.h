#ifndef ONEDATABIN_H
#define ONEDATABIN_H

//for 3x4 binning
const int Nb = 1; //nuber of beam bins
const int Nc = 1; //number of xi bins
TCut EXibin[Nb][Nc];
Double_t EVal[Nb + 1];
Double_t XVal[Nb][Nc + 1];
EXibin[0][0] = " beam > 2.8 && beam < 5.5 && Xcmtheta > -1 && Xcmtheta < 1 " ; 
//EXibin[0][1] = " beam > 2.8 && beam < 5.5 && Xcmtheta > -1 && Xcmtheta < 1 " ; 
//EXibin[1][0] = " beam > 2.8 && beam < 5.5 && Xcmtheta > -1 && Xcmtheta < 1 " ; 
//EXibin[1][1] = " beam > 2.8 && beam < 5.5 && Xcmtheta > -1 && Xcmtheta < 1 " ; 
EVal[0] = 2.8;
EVal[1] = 5.5;
//EVal[0] = 2.8;
//EVal[1] = 5.5;
XVal[0][0] = -1;
XVal[0][1] = 1;
//XVal[1][0] = -1;
//XVal[1][1] = 1;