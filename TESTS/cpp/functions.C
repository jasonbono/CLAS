
#include <iostream>
using namespace std;



void printmessage ()
{
	cout << "I'm a function! \n";
}

TPythia6 *InitPythia()
{
	TPythia6* pythia = new TPythia6;
	float eMax = 5.6;
	float eGamma = 1.0;
	float eFrac = eGamma/eMax;
	pythia->SetPARP(2, 1.0);
	pythia->Initialize("FIXT","gamma","p",eMax);
	pythia->SetPARP(171,eFrac); //Set the beam energy as fraction of eMax

	pythia->SetMSEL(2);
	pythia->SetMSTP(13,2);
	pythia->SetMSTP(20,0);
	pythia->SetMSTP(58,4);
	pythia->SetMSTP(92,4);
	pythia->SetMSTP(101,1);
	pythia->SetMSTP(121,1);
	//pythia->SetMSTP(171,0.1); // for variable energy
	//pythia->SetMSTP(172,1); //What is this really for? 
	// pythia->SetPARP(2, 2.54739); //min egamma for pythia
	pythia->SetPARP(18, 0.17);
	pythia->SetPARP(89, 1000);
	pythia->SetPARP(91, 0.40);
	pythia->SetPARP(93, 2.0);
	pythia->SetPARP(99, 0.40);
	pythia->SetPARP(102, 0.5);
	pythia->SetPARP(103, 0.5);
	pythia->SetPARP(104, 0.3);
	pythia->SetPARP(111, 0.0);
	pythia->SetPARP(121, 2.0);
	pythia->SetPARP(161, 3.0);
	pythia->SetPARP(162, 24.6);
	pythia->SetPARP(165, 0.47679);
	pythia->SetPARP(166, 0.67597);
	pythia->SetPARJ(1, 0.029);
	pythia->SetPARJ(2, 0.283);
	pythia->SetPARJ(3, 1.20);
	pythia->SetPARJ(21, 0.40 );
	pythia->SetPARJ(23, 0.03);
	pythia->SetPARJ(41, 1.94);
	pythia->SetPARJ(42, 0.544);
	pythia->SetPARJ(45, 1.05 );
	pythia->SetMSTJ(12, 1);
	pythia->SetMSTJ(45, 4);
	pythia->SetMSTU(112, 4 );
	pythia->SetMSTU(113, 4 );
	pythia->SetMSTU(114, 4 );
	pythia->SetCKIN(1,1.0);  
	pythia->SetCKIN(66,100.0);
	return pythia;	
}



void functions ()
{
	printmessage ();
	TPythia6* pythia = new TPythia6;
	pythia = InitPythia();
//	InitPythia();
	pythia->GenerateEvent();

}











