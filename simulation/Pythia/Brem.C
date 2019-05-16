


//generate bremstrulong 





void Brem()
{
	
	//------------------specify how many events----------------------
	const int nToGen = 100;
	

	//-----------------make tree to write to--------------------------
	TFile* file = TFile::Open("brem.root", "RECREATE");
	TTree *t1 = new TTree("t1","generatedEvents");

	
	//--------------------initize the pythia object-----------------
	TPythia6* pythia = new TPythia6;
	pythia = InitPythia();

	
	//----------fill the beam array and draw its distribution------------
	Float_t beam[nToGen];
	makebeam(nToGen,beam);


	//=============================loop============================
	int killEvent = 1;
	float eMax = 5.6;
	float eGamma = 0.0;
	float eFrac = 0.0;
	for (Int_t i = 0; i<= nToGen; i++)
	{
		eGamma = beam[i];
		eFrac = eGamma/eMax;
		pythia->SetPARP(171,eFrac);
		pythia->SetPARP(172,eFrac);
		cout << "generating event with eGamma = " << eGamma << " and fraction eFrac = " << eFrac << endl;	
		pythia->GenerateEvent();
		pythia->Pyedit(2); //Remove decayed particles
		pythia->Pylist(1);
		//TClonesArray* particles = (TClonesArray*)pythia->GetListOfParticles();
		//t1->Branch("branch", &particles);
		//for(Int_t j=0;j<pythia->GetNumberOfParticles();j++)
		//{
		//	if(pythia->GetK(j,2)!=211) particle->RemoveAt(j);
			
		//}
		
		
		int numParticles = pythia->GetNumberOfParticles();
	    TObjArray *particles = pythia->GetListOfParticles();
	    TMCParticle *myParticle;
		for(int j = 0; j < numParticles; j++) 
		{
			myParticle = (TMCParticle*)particles->At(j);
			cout << myParticle->GetKS() << "  " << myParticle->GetKF() << "  " << myParticle->GetName() << "  " << myParticle->GetParent() <<endl;
			 
		}
		
		
		
		
		
		
		
		if (killEvent == 0) t1->Fill(); //Fill the tree
	
		
	}

	//file->Write();
	//file->Close();

	gApplication->Terminate();
}







//functions

//----------------------------------------------------
void makebeam(const int nToGen, Float_t beam[nToGen])
{
	gROOT->Reset();
 	gROOT->SetStyle("Plain");
 	gStyle->SetOptStat(0);

 	TRandom *testRand=new TRandom();
 	Double_t eMin = 1.7;
 	Double_t eMax = 5.6;
 	TH1D *h101 = new TH1D("h101","",100,eMax,eMin);

	Double_t eGamma;
 	Double_t distribution = 0.0;
 	Double_t distributionMax = 1.0/eMin;
 	Double_t testVal = distributionMax + 1.0;
 	//Int_t nToGen = 100000;

 	for (Int_t i = 0; i<= nToGen; i++) 
	{
   		testVal = distributionMax + 1.0;
   		while(testVal>distribution)
		{
     		eGamma = testRand->Uniform(eMin,eMax);
     		distribution = 1.0/eGamma;
     		distributionMax = 1.0/eMin;
     		testVal = testRand->Uniform(0.0,distributionMax);
			beam[i] = eGamma;
			
   		}	
  		h101->Fill(eGamma);
	}
 	h101->Draw();
}





//-------------------------------------------------------
TPythia6 *InitPythia()
{
	TPythia6* pythia = new TPythia6;
	float eMax = 5.6;
	float eGamma = 3.0;
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


//---------------------------------------------------------







