#ifndef HYPERSPHERE_H
#define HYPERSPHERE_H




	//----------------------------------MASS CUTS------------------------------------------ 
	//------Define Varibles For Hyperspherecut---------
	float sigmaA = 0.0113;
	float sigmaB = 0.0107;
	float sigmaC = 0.0031;
	float sigmaD = 0.0030;
	float depth = 3;

	//theese are fixed
	float widthA = depth*sigmaA;
	float widthB = depth*sigmaB;
	float widthC = depth*sigmaC;
	float widthD = depth*sigmaD;
	float MASS_Xi = 1.321;
	float MASS_Lambda = 1.116;
	// . . . . . . . . . . . . . .


	TCut hypersphere = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) < 1"
		,MASS_Xi,MASS_Xi,widthA,widthA,MASS_Lambda,MASS_Lambda,widthB,widthB,MASS_Xi,MASS_Xi,widthC,widthC,MASS_Lambda,MASS_Lambda,widthD,widthD);








#endif
