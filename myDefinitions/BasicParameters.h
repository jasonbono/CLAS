#ifndef BASICPARAMETERS_H
#define BASICPARAMETERS_H




	float BasicParameterA = 2, BasicParameterB = 1, BasicParameterC = 1;
	float BasicParameterD = 2;
	float BasicParameterE = 90, BasicParameterF = 30, BasicParameterG = 7;
	float BasicParameterH = 2.8;
	float BasicParameterI = 1;
	float BasicParameterJ = 0.4;
	float BasicParameterK = 1.1;
	
		
	TCut BasicCut_n = "np < BasicParameterA && npip < BasicParameterB && nkm < BasicParameterC";
	TCut BasicCut_np = "nphoton_nb1 < BasicParameterD";
	TCut BasicCut_vcut = "abs(vz + BasicParameterE) < BasicParameterF && sqrt(vx*vx+vy*vy) < BasicParameterG";
	TCut BasicCut_beam = "beam > BasicParameterH";
	TCut BasicCut_st = "abs(stv - scv) < BasicParameterI";
	TCut BasicCut_tof1 = "abs(vtime - (sctkp1 - sclkp1/(betakp1*29.99))) < BasicParameterJ";
	TCut BasicCut_tof2 = "abs(vtime - (sctkp2 - sclkp2/(betakp2*29.99))) < BasicParameterK";

	TCut BasicCut_all = BasicCut_n && BasicCut_np && BasicCut_vcut && BasicCut_beam && BasicCut_st && BasicCut_tof1 && BasicCut_tof2;






#endif