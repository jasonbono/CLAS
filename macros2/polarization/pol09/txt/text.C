void text(){

	//*//<-----  
	ifstream in("Winfo.txt"); // input
  	if(!in) {
    	cout << "Cannot open test.txt file.\n";
		gROOT->ProcessLine(".q");
  	}
	const Int_t NWBins = 11;
	float W[NWBins] = {0},Werr[NWBins] = {0};

	for (int i = 0; i < NWBins ; i++) 
	{
  		in >> W[i] >> Werr[i];
  		cout << W[i] << " " << Werr[i] << "\n";
	}
		in.close();	
	
	//*///
}









