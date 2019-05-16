/*
Author: Jason Bono
Date: May 6
Useage:
	1) .L casyield.
	2) casyield(3.3,5.5,0.3)
	
Input:
1) .root file for data

Output: 
1) casyield.dat
2) casyield.eps

Considerations:  
1) take off the kf cut when the kpkp data is finished skiming.
2) make sure

*/
void casyield(Double_t eg_min, Double_t eg_max, Double_t egstep)
{

	//------------------setup input and output, declare some main objects----------------------------
	//TFile *f = new TFile("~/clas/rootfiles/LINKS/2kppim-v05-Basic-Mass.root");
 	//TNtuple *xxx=(TNtuple *)f->Get("v05");
	TFile *f = new TFile("/Users/Bono/clas/rootfiles/g12/2kppim/v15/hadded/2kppim-v15_Basic_Mass3.root");
	TNtuple *xxx=(TNtuple *)f->Get("v15");
  	ofstream casyielddat;
	char casyieldout[512];  //jb added this to be 512 since 30 was causing segfaults 
	char psfile[512];
	sprintf(casyieldout,"./results/casyield.dat",eg_min, eg_max);  //output data file
  	sprintf(psfile,"./results/casyield.eps",eg_min, eg_max);  //output ps file
  	TPostScript *ps = new TPostScript(psfile, 111);
  	casyielddat.open(casyieldout, ios::out);
  	TCanvas *c2=new TCanvas("c2", "", 20,20,600,800);
  	//JB Int_t egbin=(eg_max-eg_min)/egstep;
  	Int_t egbin=(eg_max-eg_min+0.001)/egstep; //JB
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
	Int_t total =0;
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
    	cout<<beamcut<<" ";
    	cout<<emean<<" "<<i<<endl;
    	ps->NewPage();
    	Int_t k;
///*
		if(ehigh<=2.9) {
       		tstep=0.15;
     	}
     	else {
       		tstep=0.25;
     	}
///*/
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
       		if(thigh>=1.25||elow<=3.6){
	 			h[i][j]=new TH1F(Form("h%d_%d",i,j),Form("E_{#gamma}:%5.4f to %5.4f, t':%3.2f to %3.2f",elow, ehigh, tlow,thigh),100,1.2,1.8);
			}
       		else {
	 			h[i][j]=new TH1F(Form("h%d_%d",i,j),Form("E_{#gamma}:%5.4f to %5.4f, t':%3.2f to %3.2f",elow, ehigh, tlow,thigh),150,1.2,1.8);
       		}
			xxx->Draw(Form("mmkpkp>>h%d_%d",i,j), Form("beam<%f&&beam>%f&&tpkp1<%f&&tpkp1>%f",ehigh, elow, thigh, tlow));
  			yield=h[i][j]->GetEntries();
			total += yield;
			yielderr=sqrt(yield);
       		tyield[j]=yield;
       		tyielderr[j]=yielderr;
       		c2->Update();
     	} 
     	casyielddat<<emean<<" ";
     	for(j=0;j<=9;j++){casyielddat<<tyield[j]<<" "<<tyielderr[j]<<" ";}
     
     	casyielddat<<endl;
     	c2->Update();
	}
 	casyielddat.close();
 	ps->Close();
	cout <<"jmax =" <<jmax <<endl;
	cout <<"total events = " <<total<<endl;
	
}


