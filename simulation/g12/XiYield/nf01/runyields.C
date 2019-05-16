/*

Author: Jason Bono
Date: November 5 2012

Usage: root -l tslope.C (specify the energy binning width "estep")

Purpose:  To obtain the t-slope of the data as a function of beam energy. This is used as an input for the next iteration of simulation. 

Background: Yeilds are obtained as a function of 't and beam energy for data,MC & gen. The yeilds in each energy bin are fitted to an exponential, the coeffecient of 
which are identified as the t-slope.

*/


void runyields()
{
	//setup the energy range
	Double_t emin = 2.8;
	Double_t emax = 5.5;
	Int_t Nesteps = 8;
	Double_t estep = (emax - emin)/Nesteps;	
	cout <<"Nesteps = "<< Nesteps << "  estep = " << estep <<endl;

	gROOT->ProcessLine(".L ./casyield.C");
	gROOT->ProcessLine(".L ./casmcyield.C");
	gROOT->ProcessLine(".L ./casgenyield.C");
	gROOT->ProcessLine(".L ./tslope.C");
	
	cout << "=========running casyield========="<<endl;
	casyield(emin, emax, estep);
	cout << "running casmcyield" <<endl;
	casmcyield(emin, emax, estep);
	cout << "running casgenyield" <<endl;
	casgenyield(emin, emax, estep);
	cout << "running tslope" <<endl;
	tslope(Nesteps,10);
	
	cout << "opening the eps files" <<endl;
	system("open ./results/*.eps");
	
	cout << "-----------------------this was produced with the following--------------------------" <<endl;
	cout <<"emin: "<<emin<<"  emax: "<<emax<<"  estep:"<<estep<<"  Nesteps: "<<Nesteps<<endl;
	cout << "quiting" <<endl;
	gROOT->ProcessLine(".q");

	
}