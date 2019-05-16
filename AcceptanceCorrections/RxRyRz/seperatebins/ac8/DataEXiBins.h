#ifndef DATAEXIBINS_H
#define DATAEXIBINS_H


const int Nc = 3;
TCut EXibin[2][Nc];
Double_t EVal[Nc + 1];
Double_t XVal[Nc + 1];


//*
//if (Nc == 3)
//{
	EXibin[0][0] = " beam > 2.800000 && beam < 3.812500"; 
 	EXibin[0][1] = " beam > 3.812500 && beam < 4.433500"; 
 	EXibin[0][2] = " beam > 4.433500 && beam < 5.500000"; 
 	EXibin[1][0] = " Xcmtheta > -1.000000 && Xcmtheta < -0.613000 " ; 
 	EXibin[1][1] = " Xcmtheta > -0.613000 && Xcmtheta < -0.199000 " ; 
 	EXibin[1][2] = " Xcmtheta > -0.199000 && Xcmtheta < 0.800000 " ; 
 	EVal[0] = 2.8;
 	EVal[1] = 3.8125;
 	EVal[2] = 4.4335;
 	EVal[3] = 5.5;
 	XVal[0] = -1;
 	XVal[1] = -0.613;
 	XVal[2] = -0.199;
 	XVal[3] = 0.8;
//}
///*/


/*
//if (Nc == 4)
//{	
	EXibin[0][0] = " beam > 2.800000 && beam < 3.677500"; 
	EXibin[0][1] = " beam > 3.677500 && beam < 4.082500"; 
	EXibin[0][2] = " beam > 4.082500 && beam < 4.622500"; 
	EXibin[0][3] = " beam > 4.622500 && beam < 5.500000"; 
	EXibin[1][0] = " Xcmtheta > -1.000000 && Xcmtheta < -0.703000 " ; 
	EXibin[1][1] = " Xcmtheta > -0.703000 && Xcmtheta < -0.433000 " ; 
	EXibin[1][2] = " Xcmtheta > -0.433000 && Xcmtheta < -0.073000 " ; 
	EXibin[1][3] = " Xcmtheta > -0.073000 && Xcmtheta < 0.800000 " ; 
	EVal[0] = 2.8;
	EVal[1] = 3.6775;
	EVal[2] = 4.0825;
	EVal[3] = 4.6225;
	EVal[4] = 5.5;
	XVal[0] = -1;
	XVal[1] = -0.703;
	XVal[2] = -0.433;
	XVal[3] = -0.073;
	XVal[4] = 0.8;
//}

//*/