/*
Author: Jason Bono
Date: Jun 19 2013
Purpose: To predict the location and width of the extra peak in the
spectrum of ~(lambda + pim) assuming it is due to the decay of the lambda

Usage: root> .x PredictWiggle.C

*/


void PredictWiggle()
{
	
	double MXi = 1.32131;
	double MLam = 1.115683;
	double MProton = 0.938272;
	double MPim = 0.13957018;
	
	
	//calculate energy of lamda and the good pion
	double Epim,Elam;
	Epim = (MXi*MXi + MPim*MPim - MLam*MLam)/(2*MXi);
	Elam = (MXi*MXi + MLam*MLam - MPim*MPim)/(2*MXi);
	cout << "Epim = " << Epim << "   Elam = " << Elam <<endl;

	//calculate momenum of lamda and the good pion (assume in pion in negitive x direction)
	double Ppim,Plam;
	Ppim = -sqrt(Epim*Epim - MPim*MPim);
	Plam = sqrt(Elam*Elam - MLam*MLam); 
	cout << "Ppim = " << Ppim << "   Plam = " << Plam <<endl;

	//calculate beta of lamda and good pion
	double Bpim,Blam;
	Bpim = Ppim/Epim;
	Blam = Plam/Elam;
	cout << "Bpim = " << Bpim << "   Blam = " << Blam <<endl;
	
	//calculate gamma of lamda and good pion
	double Gpim,Glam;
	Gpim = 1/sqrt(1 - Bpim*Bpim);
	Glam = 1/sqrt(1 - Blam*Blam);
	cout << "Gpim = " << Gpim << "   Glam = " << Glam <<endl;
	
	
	//decay products of lambda have the lambda velocity plus some extra velocity from  the energy of the decay
	//on average the extra velocity is perpendicular if decay is isotropic
	//therefore can assume the pi- in the lam->pi-+proton has on average, the pathagorean sum of the lambda velocity and the extra boost	
	//the Extra boost to the pion has energy (in the frame of the lambda)
	double Eextra = (MLam*MLam + MPim*MPim - MProton*MProton)/(2*MLam);
	//with momentum
	double Pextra = sqrt(Eextra*Eextra - MPim*MPim);
	//thus having beta
	double Bextra = Pextra/Eextra;
	cout << "  Eextra = " << Eextra << "  Pextra = " << Pextra << "  Bextra = " << Bextra <<endl;
	
	//calculate three possible sums of the Betas (addition, subtraction & pathagoriean coresponding to parallel, antiparallel & perpendicular)
	double Bmax = Blam + Bextra;
	double Bmin = Blam - Bextra;
	double Bavg = sqrt(Blam*Blam + Bextra*Bextra);
	cout << "  Bmax = " << Bmax << "  Bmin = " << Bmin << "  Bavg = " << Bavg <<endl;
	
	//calculate three possible gamma factors
	double Gmax = 1/sqrt(1 - Bmax*Bmax);
	double Gmin = 1/sqrt(1 - Bmin*Bmin);
	double Gavg = 1/sqrt(1 - Bavg*Bavg);
	cout << "  Gmax = " << Gmax << "  Gmin = " << Gmin << "  Gavg = " << Gavg <<endl;
	
	//calculate the three posible momenta of the new pion 
	double Pmax = Gmax*Bmax*MPim;
	double Pmin = Gmin*Bmin*MPim;
	double Pavg = Gavg*Bavg*MPim;
	cout << "  Pmax = " << Pmax << "  Pmin = " << Pmin << "  Pavg = " << Pavg <<endl;
	
	//get the components of Pavg
	double Px = Gavg*Blam*MPim;
	double Py = Gavg*Bextra*MPim;
	cout << "Px = " << Px << "  Py = " << Py << "  sqrt(Px*Px+Py*Py) = " << sqrt(Px*Px+Py*Py) <<endl;
	
	//calculate the three possible energies of the new pion
	double Emax = Pmax/Bmax;
	double Emin = Pmin/Bmin;
	double Eavg = Pavg/Bavg;
	cout << "  Emax = " << Emax << "  Emin = " << Emin << "  Eavg = " << Eavg <<endl;
	
	//set the fourvectors of the lambda and good pion (again all in x direction)
	TLorentzVector vgood;
	vgood.SetPxPyPzE(Plam+Ppim,0,0,Elam + Epim);
	//same with min max & avg
	TLorentzVector vmax,vmin,vavg;
	vmax.SetPxPyPzE(Plam+Pmax,0,0,Elam+Emax);
	vmin.SetPxPyPzE(Plam+Pmin,0,0,Elam+Emin);
	vavg.SetPxPyPzE(Plam+Px,Py,0,Elam+Eavg);
	
	//calculate the invarent masses
	double Mgood,Mmax,Mmin,Mavg;
	Mgood = vgood.Mag();
	Mmax = vmax.M();
	Mmin = vmin.M();
	Mavg = vavg.M();
	cout << "  Mgood = " << Mgood << "  Mmax = " << Mmax << "  Mmin = " << Mmin <<endl; 
	cout << "Mavg = " <<Mavg<<endl;  
	

	

}