#ifndef ACPI20E3_H
#define ACPI20E3_H

	//total number is 4451
	//for three energy bins want about 1483
	//after being further divided into 6 more pion bins want about 247

	const string bintype ("var"); //for if statments other option is "fixed"
	const int NEBins = 3; 
	const int NXiBins = 3;
	const int NPiAcBins = 20;
	

	//energy bins
	TCut EBin[NEBins];
	EBin[0] = "beam > 2.8 && beam < 3.8 ";
	EBin[1] = "beam > 3.8 && beam < 4.45 ";
	EBin[2] = "beam > 4.45 && beam < 5.5 ";			
	//Xicm bins
	TCut XiBin[NXiBins];
	XiBin[0] = "Xcmtheta > -1.0 && Xcmtheta < -0.61";
	XiBin[1] = "Xcmtheta > -0.61 && Xcmtheta < -0.183";
	XiBin[2] = "Xcmtheta > -0.183 && Xcmtheta < 1.0";

				
				
	//
	//pi bins
	TCut  PixAcBin[NPiAcBins];
	PixAcBin[0] = "COS_pi_x > -1.0 && COS_pi_x < -0.9";
	PixAcBin[1] = "COS_pi_x > -0.9 && COS_pi_x < -0.8";
	PixAcBin[2] = "COS_pi_x > -0.8 && COS_pi_x < -0.7";  
	PixAcBin[3] = "COS_pi_x > -0.7 && COS_pi_x < -0.6";
	PixAcBin[4] = "COS_pi_x > -0.6 && COS_pi_x < -0.5";
	PixAcBin[5] = "COS_pi_x > -0.5 && COS_pi_x < -0.4";
	PixAcBin[6] = "COS_pi_x > -0.4 && COS_pi_x < -0.3";
	PixAcBin[7] = "COS_pi_x > -0.3 && COS_pi_x < -0.2";
	PixAcBin[8] = "COS_pi_x > -0.2 && COS_pi_x < -0.1";  
	PixAcBin[9] = "COS_pi_x > -0.1 && COS_pi_x < 0.0";
	PixAcBin[10] = "COS_pi_x > 0.0 && COS_pi_x < 0.1";
	PixAcBin[11] = "COS_pi_x > 0.1 && COS_pi_x < 0.2";	
	PixAcBin[12] = "COS_pi_x > 0.2 && COS_pi_x < 0.3";
	PixAcBin[13] = "COS_pi_x > 0.3 && COS_pi_x < 0.4";
	PixAcBin[14] = "COS_pi_x > 0.4 && COS_pi_x < 0.5";	
	PixAcBin[15] = "COS_pi_x > 0.5 && COS_pi_x < 0.6";
	PixAcBin[16] = "COS_pi_x > 0.6 && COS_pi_x < 0.7";
	PixAcBin[17] = "COS_pi_x > 0.7 && COS_pi_x < 0.8";	
	PixAcBin[18] = "COS_pi_x > 0.8 && COS_pi_x < 0.9";
	PixAcBin[19] = "COS_pi_x > 0.9 && COS_pi_x < 1.0";
	
	TCut  PiyAcBin[NPiAcBins];
	PiyAcBin[0] = "COS_pi_y > -1.0 && COS_pi_y < -0.9";
	PiyAcBin[1] = "COS_pi_y > -0.9 && COS_pi_y < -0.8";
	PiyAcBin[2] = "COS_pi_y > -0.8 && COS_pi_y < -0.7";  
	PiyAcBin[3] = "COS_pi_y > -0.7 && COS_pi_y < -0.6";
	PiyAcBin[4] = "COS_pi_y > -0.6 && COS_pi_y < -0.5";
	PiyAcBin[5] = "COS_pi_y > -0.5 && COS_pi_y < -0.4";
	PiyAcBin[6] = "COS_pi_y > -0.4 && COS_pi_y < -0.3";
	PiyAcBin[7] = "COS_pi_y > -0.3 && COS_pi_y < -0.2";
	PiyAcBin[8] = "COS_pi_y > -0.2 && COS_pi_y < -0.1";  
	PiyAcBin[9] = "COS_pi_y > -0.1 && COS_pi_y < 0.0";
	PiyAcBin[10] = "COS_pi_y > 0.0 && COS_pi_y < 0.1";
	PiyAcBin[11] = "COS_pi_y > 0.1 && COS_pi_y < 0.2";	
	PiyAcBin[12] = "COS_pi_y > 0.2 && COS_pi_y < 0.3";
	PiyAcBin[13] = "COS_pi_y > 0.3 && COS_pi_y < 0.4";
	PiyAcBin[14] = "COS_pi_y > 0.4 && COS_pi_y < 0.5";	
	PiyAcBin[15] = "COS_pi_y > 0.5 && COS_pi_y < 0.6";
	PiyAcBin[16] = "COS_pi_y > 0.6 && COS_pi_y < 0.7";
	PiyAcBin[17] = "COS_pi_y > 0.7 && COS_pi_y < 0.8";	
	PiyAcBin[18] = "COS_pi_y > 0.8 && COS_pi_y < 0.9";
	PiyAcBin[19] = "COS_pi_y > 0.9 && COS_pi_y < 1.0";
	
	TCut  PizAcBin[NPiAcBins];
	PizAcBin[0] = "COS_pi_z > -1.0 && COS_pi_z < -0.9";
	PizAcBin[1] = "COS_pi_z > -0.9 && COS_pi_z < -0.8";
	PizAcBin[2] = "COS_pi_z > -0.8 && COS_pi_z < -0.7";  
	PizAcBin[3] = "COS_pi_z > -0.7 && COS_pi_z < -0.6";
	PizAcBin[4] = "COS_pi_z > -0.6 && COS_pi_z < -0.5";
	PizAcBin[5] = "COS_pi_z > -0.5 && COS_pi_z < -0.4";
	PizAcBin[6] = "COS_pi_z > -0.4 && COS_pi_z < -0.3";
	PizAcBin[7] = "COS_pi_z > -0.3 && COS_pi_z < -0.2";
	PizAcBin[8] = "COS_pi_z > -0.2 && COS_pi_z < -0.1";  
	PizAcBin[9] = "COS_pi_z > -0.1 && COS_pi_z < 0.0";
	PizAcBin[10] = "COS_pi_z > 0.0 && COS_pi_z < 0.1";
	PizAcBin[11] = "COS_pi_z > 0.1 && COS_pi_z < 0.2";	
	PizAcBin[12] = "COS_pi_z > 0.2 && COS_pi_z < 0.3";
	PizAcBin[13] = "COS_pi_z > 0.3 && COS_pi_z < 0.4";
	PizAcBin[14] = "COS_pi_z > 0.4 && COS_pi_z < 0.5";	
	PizAcBin[15] = "COS_pi_z > 0.5 && COS_pi_z < 0.6";
	PizAcBin[16] = "COS_pi_z > 0.6 && COS_pi_z < 0.7";
	PizAcBin[17] = "COS_pi_z > 0.7 && COS_pi_z < 0.8";	
	PizAcBin[18] = "COS_pi_z > 0.8 && COS_pi_z < 0.9";
	PizAcBin[19] = "COS_pi_z > 0.9 && COS_pi_z < 1.0";

#endif