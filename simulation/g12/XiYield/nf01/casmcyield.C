/*
JB august 29: this reads an kpkppim ntuple from accepted events (.a1c.root) and makes yeilds 

Input:
1) a1c.root file for MC

Outputs: 
1) casmcyield.dat
2) casmcyield.eps

Considerations:
*/



void casmcyield(Double_t eg_min, Double_t eg_max, Double_t egstep){
	TFile *f = new TFile("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t4-t4-2kppim_Basic_Mass3.root");
  	TNtuple *newmc3=(TNtuple *)f->Get("gpp2kppim");
  	//Load fit2BW.C;
  	ofstream casmcyielddat;
	char casmcyieldout[512];
	char psfile[512];
	sprintf(casmcyieldout,"./results/casmcyield.dat",eg_min, eg_max);
  	sprintf(psfile,"./results/casmcyield.eps",eg_min, eg_max);
  	TPostScript *ps = new TPostScript(psfile, 111);
  	casmcyielddat.open(casmcyieldout, ios::out);
  	TCanvas *c2=new TCanvas("c2", "", 20,20,600,800);
  	Int_t egbin=(eg_max-eg_min+0.001)/egstep;
  	Int_t pads=egbin/4+1;
  	cout<<pads<<" "<<egbin<<endl;
  	Double_t elow, ehigh,emean;
  	Double_t tlow, thigh,tmean;
  	Double_t tstep=0.25;
  	const int n=100;
  	TH1F *h[n][20];
  	Int_t yield;
  	Int_t yielderr;
  	Int_t tyield[10]; 
  	Int_t tyielderr[10];
  	Int_t j,jmax;
  	for(j=0;j<=9;j++){
    	tyield[j]=-1;
    	tyielderr[j]=-10;
	}
  	yielderr=0;
   	c2->Divide(3,3);
  	c2->Update();
  	char sc[30];
  	char beamcut[30];
  	char name[50];
  	Double_t tmax;
 	for( Int_t i=1;i<=egbin;i++){
    	elow=eg_min+(i-1)*egstep;
    	ehigh=eg_min+i*egstep;
    	emean=(elow+ehigh)/2;
    	sprintf(beamcut, "beam<%f&&beam>%f", ehigh, elow);
    	//sprintf(sc, "abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<1");
    	cout<<beamcut<<" ";
    	cout<<emean<<" "<<i<<endl;
    	ps->NewPage();
     	Int_t k; 
     	if(ehigh<=2.9) {
       		tstep=0.15;
     	}
     	else {
       		tstep=0.25;
     	}
     	if(ehigh<=2.9){
       		tmax=0.75;
     	}
     	else if(ehigh<=3.2){
       		tmax=1.25;
     	}
    	else if(ehigh<=3.6){
       		tmax=1.75;
     	}
     	else {
			tmax=2.25;
     	}
 		jmax=tmax/tstep;
     	for( Int_t j=0;j<jmax;j++){
       		k=j+1;
       		c2->cd(k);
       		tlow=j*tstep;
       		thigh=(j+1)*tstep;
       		tmean=(tlow+thigh)/2;
	 		h[i][j]=new TH1F(Form("h%d_%d",i,j),Form("E_{#gamma}:%4.3f to %4.3f, t':%3.2f to %3.2f",elow, ehigh, tlow,thigh),100,1.2,1.8);
			newmc3->Draw(Form("mmkpkp>>h%d_%d",i,j), Form("beam<%f&&beam>%f&&tpkp1<%f&&tpkp1>%f",ehigh, elow, thigh, tlow));
       		yield=h[i][j]->GetEntries();
			yielderr=sqrt(yield);
       		tyield[j]=yield;
       		tyielderr[j]=0;
       		c2->Update();
		} 
		casmcyielddat<<emean<<" ";
    	for(j=0;j<=9;j++){casmcyielddat<<tyield[j]<<" "<<tyielderr[j]<<" ";}
     
    	casmcyielddat<<endl;
    	c2->Update();
	}
 	casmcyielddat.close();
 	ps->Close();
 
}

