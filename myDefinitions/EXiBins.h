#ifndef EXIBINS_H
#define EXIBINS_H


	//Jason Bono
	//April 8 2013

	const int NBinTypes = 2; //E and Xi
	const int NEBins = 3; 
	const int NXiBins = 3;
	const int NXiEParameters = 4;
	

	//parameters
	float EXiParameterA = 2.8;
	float EXiParameterB = 3.8;
	float EXiParameterC = 4.45;
	float EXiParameterD = 5.5;
	float EXiParameterE = -1.0;
	float EXiParameterF = -0.61;
	float EXiParameterG = -0.183;
	float EXiParameterH = 1.0;


	//*////	
	//energy bins
	TCut EBin[NEBins];
	EBin[0] = "beam >= 2.8 && beam <= 3.8";
	EBin[1] = "beam > 3.8 && beam <= 4.45";
	EBin[2] = "beam > 4.45 && beam <= 5.5";			
	//Xicm bins
	TCut XiBin[NXiBins];
	XiBin[0] = "Xcmtheta >= -1.0 && Xcmtheta <= -0.61";
	XiBin[1] = "Xcmtheta > -0.61 && Xcmtheta <= -0.183";
	XiBin[2] = "Xcmtheta > -0.183 && Xcmtheta <= 1.0";
	///*///	


	/*///		
	//energy bins
	TCut EBin[NEBins];
	EBin[0] = Form("beam > %f && beam < %f",EXiParameterA,EXiParameterB);
	EBin[1] = Form("beam > %f && beam < %f",EXiParameterB,EXiParameterC);
	EBin[2] = Form("beam > %f && beam < %f",,EXiParameterC,EXiParameterD);			
	//Xicm bins
	TCut XiBin[NXiBins];
	XiBin[0] = Form("Xcmtheta > %f && Xcmtheta < %f",EXiParameterE,EXiParameterF);
	XiBin[1] = Form("Xcmtheta > %f && Xcmtheta < %f",EXiParameterF,EXiParameterG);
	XiBin[2] = Form("Xcmtheta > %f && Xcmtheta < %f",EXiParameterG,EXiParameterH);
	///*///
	
	//*//Combined bins
	TCut EXiBin[NBinTypes][NEBins];
	EXiBin[0][0] = EBin[0];
	EXiBin[0][1] = EBin[1];			
	EXiBin[0][2] = EBin[2];
	EXiBin[1][0] = XiBin[0];
	EXiBin[1][1] = XiBin[1];			
	EXiBin[1][2] = XiBin[2];
	///*////
	
#endif