void test()
{
	TPythia6* pythia = new TPythia6;	
	float eMax = 5.6;
	float eGamma = 5.0;
	float eFrac = eGamma/eMax;
	pythia->SetPARP(2, 1.0);
	pythia->Initialize("fixt","gamma","p",eMax);
	pythia->SetPARP(171,eFrac); //Set the beam energy as fraction of eMax

	pythia->GenerateEvent();
	pythia->Pyedit(2);
	pythia->Pylist(1);
}