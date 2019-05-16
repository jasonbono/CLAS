/*
JB september 13: this reads an ntuple from generated events (.gamp.root) and makes yeilds 




Author: Jason Bono
Date: October 31 2012
Useage: 
	1) .L casgenyield.C 
	2) casgenyield(3.3,5.5,0.3)

Purpose: Gets the yields as a function of 





Input:
1) gamp.root file for Gen

Outputs: 
1) casgenyield.dat
2) casgenyield.eps

Considerations:  
1) 
2) 

*/

void casgenyield(Double_t eg_min, Double_t eg_max, Double_t egstep){
	cout <<"TEST0" <<endl;
  	TFile *f = new TFile("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t4-t4-gamproot-10.root");
  	TNtuple *newgamp3=(TNtuple *)f->Get("GampTree");
  	//Load fit2BW.C;
  	ofstream casgenyielddat;
  	char casgenyieldout[512], psfile[512];
  	sprintf(casgenyieldout,"./results/casgenyield.dat",eg_min, eg_max);
  	sprintf(psfile,"./results/casgenyield.eps",eg_min, eg_max);
  	//sprintf(casgenyieldout,"./results/casgenyield_%4.3f_%4.3f.dat",eg_min, eg_max);
  	//sprintf(psfile,"./results/casgenyield_%4.3f_%4.3f.eps",eg_min, eg_max);
  	TPostScript *ps = new TPostScript(psfile, 111);
  	casgenyielddat.open(casgenyieldout, ios::out);
  	TCanvas *c2=new TCanvas("c2", "", 20,20,600,800);
  	Int_t egbin=(eg_max-eg_min+0.001)/egstep;
	cout<<"min="<<eg_min<<" max="<<eg_max<< " step="<<egstep<<"  bin="<<egbin<<endl; 
  	Int_t pads=egbin/4+1;
  	//cout<<pads<<" "<<egbin<<endl;
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
  	char beagenut[30];  //jb in the other macros its called beamcut
  	char name[50];
  	Double_t tmax;
 	for( Int_t i=1;i<=egbin;i++){
     	elow=eg_min+(i-1)*egstep;
    	ehigh=eg_min+i*egstep;
    	emean=(elow+ehigh)/2;
    	sprintf(beagenut, "beam<%f&&beam>%f", ehigh, elow);
    	
    	cout<<beagenut<<" ";
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
       		//h[i]->SetMaximum(1.8);
       		//h[i]->SetMinimum(1.2);
       		//h[i]->SetBins(300);
       		//h1->GetXaxis()->SetTitleSize(0.04);
       		//h1->GetXaxis()->SetTitle("MM(K^{+} K^{+})/(GeV/c^{2})");
       		//h1->GetYaxis()->SetTitleSize(0.04);
       		//h1->GetYaxis()->SetTitle("Events/(2MeV/c^{2})");
       		newgamp3->Draw(Form("mmkpkp>>h%d_%d",i,j), Form("beam<%f&&beam>%f&&tpkp1<%f&&tpkp1>%f",ehigh, elow, thigh, tlow));
       		//h[i]->GetXaxis()->SetTitleSize(0.04);
       		//  h[i]->GetXaxis()->SetTitle("MM(K^{+} K^{+})/(GeV/c^{2})");
       		//  h[i]->GetYaxis()->SetTitleSize(0.04);
       		//  h[i]->GetYaxis()->SetTitle("Events/(2MeV/c^{2})");
       		//    new->Draw("mmkpkp>>h[i]", "abs(scv-stv)<1&&beam>elow&&beam<ehigh"&&sc);
       		// if(ehigh<=1.8){
			// 	 yield=fitBW(h[i][j], i*10+j-1, 1.48, 1.58, 1,1,1,1.52, 0.02,1.45,1.65, yielderr);
			//        }
			//        else if(ehigh<=2){
			// 	 yield=fitBW(h[i][j], i*10+j-1, 1.46, 1.64, 1,1,1,1.52, 0.02,1.45,1.65, yielderr);
			//        }
			//        else if(elow>=3.6){
			// 	 yield=fitBW(h[i][j], i*10+j-1, 1.45, 1.75, 1,1,0,1.52, 0.02,1.45,1.65, yielderr);
	 
			//        }
			//        else{
			// 	 yield=fitBW(h[i][j], i*10+j-1, 1.45, 1.75, 1,1,1,1.52, 0.02,1.45,1.65, yielderr);
			//        }
       		yield=h[i][j]->GetEntries()*100;
			yielderr=sqrt(yield);
       		tyield[j]=yield;
       		tyielderr[j]=0;
       		c2->Update();
     	} 
     	casgenyielddat<<emean<<" ";
     	for(j=0;j<=9;j++){casgenyielddat<<tyield[j]<<" "<<tyielderr[j]<<" ";} 
     
     	casgenyielddat<<endl;
     	c2->Update();
     }
 	casgenyielddat.close();
 	ps->Close(); 
}
