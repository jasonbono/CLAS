

void runyields()
{
	//setup the energy range
	Double_t emin = 2.3;
	Double_t emin = 5.6;
	Double_t estep = 0.5;
	
	//
	gROOT->ProcessLine(".L ./casyield.C");
	gROOT->ProcessLine(".L ./casgenyield.C");
	gROOT->ProcessLine(".L ./casmcyield.C");

	
	casyield(emin, emax, estep);
	casgenyield(emin, emax, estep);
	casmcyield(emin, emax, estep);
	
}