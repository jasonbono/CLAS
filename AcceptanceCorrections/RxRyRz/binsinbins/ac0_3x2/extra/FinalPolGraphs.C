







void FinalPolGraphs()
{
	
	
	
	//StyleUp();
	const int Nb = 2,Nc = 3,Nd = 3; 	//b=bintype, c=binnumber, d=piaxis
	const int Np = 10; //number of pion bins	
	int Nk = 50; //# of pion bins used to get the acceptance parameters	
	const char* BinType[Nb] = {"E","Xi"};
	const char* BinNumber[Nc] = {"0","1","2"};
	const char* Axis[Nd] = {"x","y","z"};


	//interactively choose Data or Simulation
	cout << "enter choice (Data or MC):";
	const string choice;
	cin >> choice;
	if (choice.compare("Data") == 0)
	{
	  	cout <<"The data will be evaluated" <<endl;	
		ifstream in(Form("./txt/PolResults-%ibins.txt",Nk)); 
	}
	else if (choice.compare("MC") == 0) 
	{
		cout <<"The simulation will be evaluated" <<endl;
		ifstream in(Form("./txt/SimTestPolResults-%ibins.txt",Nk)); 
	}
	else
	{ 
		cout << "choice error, quiting! " <<endl;
		gROOT->ProcessLine(".q");
	}



	//read in info from text file
	if(!in)
	{
	    cout << "Cannot open txt file.\n";
		gROOT->ProcessLine(".q");
	}
	double Polarization[Nb][Nc][Nd] = {0}, ePolarization[Nb][Nc][Nd] = {0};
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{
	  			in >> Polarization[b][c][d] >>  ePolarization[b][c][d] ;
				cout << Polarization[b][c][d] << " " <<  ePolarization[b][c][d] << endl;	 			
			}
		}
	}
	in.close();
	
	//histogram of 18 points
	TCanvas* cDist = new TCanvas("cDist","",1200,1000);
	TH1F* h = new TH1F("h","",10,-1,1);
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{
			
				h->Fill(Polarization[b][c][d]);
			
			}
		}
	}
	h->Draw();



	//Graph the Polarization as a function of bin
	TCanvas* cPol = new TCanvas("cPol","",1200,1000);
	cPol->Divide(Nb,Nd);
	int cancount = 1;
	for (int b = 0; b < Nb; b++)
	{
		for (int d = 0; d < Nd; d++)
		{
			double x[Nc] = {0},y[Nc] = {0},ex[Nc] = {0},ey[Nc] = {0},;
			for (int c = 0; c < Nc; c++)
			{	
				x[c] = c;		
				y[c] =  Polarization[b][c][d];
			 	ex[c] = 0;
				ey[c] = 0;
			}
			cPol->cd(cancount);
			cancount += 1;			
			TGraphErrors *grPol = new TGraphErrors(Nc,x,y,ex,ey);
			grPol->Draw("A*");
		}
	}	
	
	
	
	
	
	
	
	
	
	
}