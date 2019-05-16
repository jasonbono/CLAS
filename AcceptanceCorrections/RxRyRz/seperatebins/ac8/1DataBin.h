#ifndef DATAEXIBINS_H
#define DATAEXIBINS_H


const int Nc = 1;
TCut EXibin[2][Nc];
Double_t EVal[Nc + 1];
Double_t XVal[Nc + 1];


	EXibin[0][0] = " beam > 2.8 && beam < 5.5"; 
 	EXibin[1][0] = " Xcmtheta > -1 && Xcmtheta < -1 "; 

 	EVal[0] = 2.8;
 	EVal[1] = 5.5;

 	XVal[0] = -1;
 	XVal[1] = 0.8;
