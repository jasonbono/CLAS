/*

//jb y02 deleeted extra lines trying to clean up the code.

deleete: crosout, crosdat, bg, fluxbeam, cros[] +errors, totalcros[] +errors


MADE THIS SCRIPT FROM "GETCROS.C" AND TOOK OUT THE CROSS SECTION/FLUX PART

JB this macro brings in casflux.dat, where does this come from?

Input:

1) casyield.dat (from casyield.C)
2) casmctyield.dat
3) casgenyield.dat

Output:
1) tslope.dat
2) crosout.dat
3) acc.eps

Considerations:
1) The output of casyield.C is .newdat but the input of getcros.C is .dat? 
i may have to change this.

2) getting a seg-fault when calling

3) dont know how to call properly (ie need to look up the meaning of "bins" and "minmc")
minmc is how low of a yeild you are willing to look at for the mc data

*/
void tslope(Int_t bins, Int_t minmc){

	ifstream yielddat,fluxdat;
  
   	gStyle->SetPadLeftMargin(0.3);
   	gStyle->SetPadBottomMargin(0.2);
   	gStyle->SetPadTopMargin(0.2);
   	gStyle->SetOptFit(1);
   	Float_t t[11]; //// 11
  	ifstream mcdat, gendat;
  	ofstream slopedat;
  	Double_t BR;
  	BR=1;
  	TF1 *fg[11]; // jb fg is the exponential fit of grgen, 
	char genin[512],mcin[512],psfile[512],yieldin[512], slopeout[512];
	sprintf(yieldin, "./results/casyield.dat");
  	sprintf(slopeout, "./results/tslope.dat");
  	Int_t k;
  	Int_t tbin, tbinmax[11], fitmaxbin;
	Double_t tpkp[11][10],tpkperr[11][10];
	Double_t genslope[11];
  	Double_t databeam[11],databeamerr[11],datayield[11][10],datayielderr[11][10], normyield[11][10], normyielderr[11][10], totalnormyield[11], totalnormyielderr[11];
  	Double_t w[11], werr[11];
  	Double_t mp=0.938272;
   	Double_t fitlow, fithigh;
  	//read in yield info

	
	
	//============================================READING DATA FILES===============================================
	
	//-----------------------------read in the yields and errors for the DATA events------------------
	yielddat.open(yieldin, ios::in);
  	slopedat.open(slopeout, ios::out);
 	while(yielddat)
	{
    	cout<<"...............number of beam bins is " << bins << endl;
    	for(k=0;k<bins;k++)
		{
      		yielddat>>databeam[k]; //beam energy of data
			cout << " ~~~~~~~~~~~~~~~~~~~~~~~the beam energy is " << databeam[k] <<endl;
			cout << "and the bin k is" << k <<endl;
      		Int_t check=0;
      		for(tbin=0;tbin<=10;tbin++) //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!this goes to 10 bins, may be a formating error in the yeild scripts
			{
				yielddat>>datayield[k][tbin]>>datayielderr[k][tbin]; // take in the yeild and the error
				cout<< "            ~~~~~~~~~~~~~~~~~~ ebin, tbin is " << k << ", " << tbin << "~~~~~~~~~~~~" <<endl; 
				cout<< "             number of t bins is " <<tbinmax[k]<<endl;
				cout << "           the data yeild is " << datayield[k][tbin] << "  and the error is " << datayielderr[k][tbin] << endl;
				if((datayield[k][tbin]<1||datayield[k][tbin]>5000)&&!check&&tbin>1)
				{
	  				tbinmax[k]=tbin;
	  				check=1;
				}
      		}
      		w[k]=sqrt(mp*mp+2*mp*databeam[k]);
      		werr[k]=0.01;
      		databeamerr[k]=0.05;
    	}
  	}
  	yielddat.close();

 	sprintf(psfile, "./results/tslope.eps");
  	TPostScript *ps = new TPostScript(psfile, 111);
  	Int_t i;
  	Double_t yield[11][10], yielderr[11][10];
  	Double_t mcyield[11][10], mcyielderr[11][10];
  	Double_t genyield[11][10], genyielderr[11][10];
  	Double_t acc[11][10],accerr[11][10];
  	Double_t mcbeam[11], mcbeamerr[11];
  	Double_t genbeam[11], genbeamerr[11];
  	TGraphErrors *gr1[11];
	//JB  	TGraphErrors *grc[11];
  	TGraph *grgen[11], *grdet[11], *gracc[11], *grdata[11], *grnormyield[11]; //jb what is det
  	TAxis *yaxis[11];
  	TAxis *xaxis[11];

  	//----------------------read in the yeilds and errors for the ACCEPTED events-------------------
  	tbin=0;
    sprintf(mcin,"casmctyield.dat");
    mcdat.open(mcin, ios::in);
    //cout << " mcin= " <<mcin<< "   tbin= "<<tbin<<endl;
    while(mcdat) //mcdat is the casmctyield.dat file
	{
    	for(i=0;i<bins;i++)
		{
			mcdat>>mcbeam[i];
			for(tbin=0;tbin<=10;tbin++)
			{
	    		mcdat>>mcyield[i][tbin]>>mcyielderr[i][tbin];
	  		}
	  		mcbeamerr[i]=0.01;
     	}
  	}
	mcdat.close();

	//-----------------------read in the yields and errors for GENERATED yields--------------------
  	tbin=0;
    sprintf(genin,"casgentyield.dat");
    gendat.open(genin, ios::in);
    cout<< "genin = " <<genin<<"  tbin =  "<<tbin<<endl;
    while(gendat)
	{
   		for(i=0;i<bins;i++)
		{
			gendat>>genbeam[i];
	  		for(tbin=0;tbin<=10;tbin++)
			{
	    		gendat>>genyield[i][tbin]>>genyielderr[i][tbin];
	    		cout<<genbeam[i]<<" "<<genyield[i][tbin]<<endl;
	  		}
			genbeamerr[i]=0.01;
    	}
 	}
    gendat.close();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~end of reading data files~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   
	Double_t tstep;
   	if(i<1) tstep=0.15;
   	else tstep=0.25;
   	
	//========================Store yeilds in 2d vectors and cacluclate aceptance corrected yeilds==========================
    
	for(i=0;i<bins;i++)
	{
      	totalnormyield[i]=0;
      	totalnormyielderr[i]=0;
      	for(tbin=0;tbin<tbinmax[i];tbin++)
		{
			cout<<genyield[i][tbin]<<endl;
			if(genyield[i][tbin]>0&&mcyield[i][tbin]>minmc) //minmc specifed when calling tslope()
			{
	  			acc[i][tbin]=mcyield[i][tbin]/genyield[i][tbin]; // acc is acceptance corrections
	  			normyield[i][tbin]=datayield[i][tbin]/acc[i][tbin]; // this is accptance corrected yeild
	  			normyielderr[i][tbin]=datayielderr[i][tbin]/acc[i][tbin];
	  			totalnormyield[i]=totalnormyield[i]+normyield[i][tbin]; // adding yeilds over all bins CAN PROBABLY TAKE THIS OUT
	  			totalnormyielderr[i]=sqrt(totalnormyielderr[i]*totalnormyielderr[i]+normyielderr[i][tbin]*normyielderr[i][tbin]);
	 			cout<<"tbinmax="<<tbinmax[i]<<" "<<"beam bin "<<i<<" tbin "<<tbin<<" "<<acc[i][tbin]<<" "<<normyield[i][tbin]<<" "<<totalnormyield[i]<<endl;
			}	
			else 
			{
	  			acc[i][tbin]=0;
	  			normyield[i][tbin]=0;
	  			normyielderr[i][tbin]=0;
	  			totalnormyield[i]=totalnormyield[i]+normyield[i][tbin];
	  			totalnormyielderr[i]=sqrt(totalnormyielderr[i]*totalnormyielderr[i]+normyielderr[i][tbin]);	  
				cout<<"maxtbin="<<tbinmax[i]<<" "<<tbin<<" "<<acc[i][tbin]<<" "<<normyield[i][tbin]<<endl;
				cout <<"~~~~~~~~~~~~~THE NORMALIZED YIELDS ARE NOT BEING CALCULATED FOR THIS BIN~~~~~~~~~~~~" <<endl;	
			}
      	}
    }
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~finished storing and calculating~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	//=====================================================GRAPH=========================================================
    
	//---------------------------------setup--------------------------
	gStyle->SetOptTitle(1);
    TCanvas *c3=new TCanvas("c3", "", 20,20,600,800);
    Int_t pad;
    for(i=0;i<bins;i++)
	{
      	char gentitle[30], dettitle[30], acctitle[30], datatitle[30], normtitle[30]; //jb what is det? it means detected, for A1C
     	//cout<<"beam bin"<<i<<" "<<databeam[i]<<endl;
      	ps->NewPage();
      	c3->Clear();
      	c3->Divide(2,3);
      	c3->Update();

      	if(i<1) tstep=0.15;
      	else tstep=0.25;
      	for(tbin=0;tbin<tbinmax[i];tbin++)
		{
			tpkp[i][tbin]=(tbin+0.5)*tstep;
			tpkperr[i][tbin]=tstep/2;
      	}
    	//--------------------------fill the TGraph objects with the 2d vectors--------------------------
    	grgen[i]=new TGraph(tbinmax[i],tpkp[i],genyield[i]);
    	grdet[i]=new TGraph(tbinmax[i],tpkp[i],mcyield[i]);
    	gracc[i]=new TGraph(tbinmax[i],tpkp[i],acc[i]);
    	grdata[i]=new TGraph(tbinmax[i],tpkp[i],datayield[i]);
    	grnormyield[i]=new TGraph(tbinmax[i],tpkp[i],normyield[i]);
    	//grc[i]->GetHistogram()->SetMaximum(0.03); 
    	//draw generator yield
    	c3->Update();
     	c3->cd(1);
    	
		//----------------------------------draw graph of generated events--------------------------
		sprintf(gentitle, "E_{#gamma}: %5.4f  GeV", databeam[i]); 
   		//cout<<gentitle<<" flux is"<<flux[i]<<endl;
    	grgen[i]->SetTitle(gentitle);
    	grgen[i]->GetYaxis()->SetLabelSize(0.035);
    	grgen[i]->GetXaxis()->SetLabelSize(0.035);
    	grgen[i]->GetYaxis()->SetTitleSize(0.08);
    	grgen[i]->GetXaxis()->SetTitleSize(0.08);
    	grgen[i]->GetXaxis()->SetTitleOffset(1);
    	grgen[i]->GetYaxis()->SetTitleOffset(1.5);
    	grgen[i]->GetXaxis()->SetTitle("t'");
   		grgen[i]->GetYaxis()->SetTitle("GENERATED");
    	grgen[i]->GetHistogram()->SetMinimum(0);
    	grgen[i]->SetMarkerStyle(8);
    	grgen[i]->SetMarkerSize(1);
    	grgen[i]->SetMarkerColor(4);

    	grgen[i]->Draw("AP*");
		//-----------fit the graph of generaged events to an exponental
    	if(i<8){
      		fitlow=tpkp[i][0];
    	}
    	else{
      		fitlow=tpkp[i][1];
    	}
    	fitmaxbin=tbinmax[i]-2;
    	fithigh=tpkp[i][fitmaxbin];
    	cout<<fitlow<<" "<<fithigh<<" "<<tbinmax[i]<<" "<<tpkp[i][fitmaxbin]<<endl;
    	grgen[i]->Fit("expo","", "", fitlow, fithigh);
   		fg[i] = grgen[i]->GetFunction("expo");
    	genslope[i]=fg[i]->GetParameter(1);
     	//-------------------------------------draw graph of detected (a1c) events-------------------------------- 
    	c3->Update();
      	c3->cd(2);
    	sprintf(dettitle, "E_{#gamma}: %5.4f  GeV", databeam[i]); 
    	grdet[i]->SetTitle(dettitle);
    	grdet[i]->GetYaxis()->SetLabelSize(0.035);
    	grdet[i]->GetXaxis()->SetLabelSize(0.035);
    	grdet[i]->GetYaxis()->SetTitleSize(0.08);
    	grdet[i]->GetXaxis()->SetTitleSize(0.08);
    	grdet[i]->GetXaxis()->SetTitleOffset(1);
    	grdet[i]->GetYaxis()->SetTitleOffset(1.5);
    	grdet[i]->GetXaxis()->SetTitle("t'");
   		grdet[i]->GetYaxis()->SetTitle("A1C");
    	grdet[i]->GetHistogram()->SetMinimum(0);
    	grdet[i]->SetMarkerStyle(8);
    	grdet[i]->SetMarkerSize(1);
    	grdet[i]->SetMarkerColor(4);
	
    	grdet[i]->Draw("AP*");
    	//-------------------------draw graph of acceptance---------------------------------------
    	c3->Update();
    	c3->cd(3);
    	sprintf(acctitle, "E_{#gamma}: %5.4f  GeV", databeam[i]); 
    	gracc[i]->SetTitle(acctitle);
    	gracc[i]->GetYaxis()->SetLabelSize(0.035);
    	gracc[i]->GetXaxis()->SetLabelSize(0.035);
    	gracc[i]->GetYaxis()->SetTitleSize(0.08);
    	gracc[i]->GetXaxis()->SetTitleSize(0.08);
    	gracc[i]->GetXaxis()->SetTitleOffset(1);
    	gracc[i]->GetYaxis()->SetTitleOffset(1.5);
    	gracc[i]->GetXaxis()->SetTitle("t'");
    	gracc[i]->GetYaxis()->SetTitle("EFFICIENCY");
    	gracc[i]->GetHistogram()->SetMinimum(0);
    	gracc[i]->SetMarkerStyle(8);
    	gracc[i]->SetMarkerSize(1);
    	gracc[i]->SetMarkerColor(4);

    	gracc[i]->Draw("AP*");
    	//--------------------------draw graph of data events--------------------------------------
    	c3->Update();
    	c3->cd(4);
    	sprintf(datatitle, "E_{#gamma}: %5.4f  GeV", databeam[i]); 
    	grdata[i]->SetTitle(datatitle);
    	grdata[i]->GetYaxis()->SetLabelSize(0.035);
    	grdata[i]->GetXaxis()->SetLabelSize(0.035);
    	grdata[i]->GetYaxis()->SetTitleSize(0.08);
    	grdata[i]->GetXaxis()->SetTitleSize(0.08);
    	grdata[i]->GetXaxis()->SetTitleOffset(1);
    	grdata[i]->GetYaxis()->SetTitleOffset(1.5);
    	grdata[i]->GetXaxis()->SetTitle("t'");
    	grdata[i]->GetYaxis()->SetTitle("DATA");
    	grdata[i]->GetHistogram()->SetMinimum(0);
    	grdata[i]->SetMarkerStyle(8);
    	grdata[i]->SetMarkerSize(1);
    	grdata[i]->SetMarkerColor(4);

    	grdata[i]->Draw("AP*");
    	//-----------------------------draw final graph of acceptance corrected yeilds---------------
    	c3->Update();
    	c3->cd(5);
    	sprintf(normtitle, "E_{#gamma}: %5.4f  GeV", databeam[i]); 
    	grnormyield[i]->SetTitle(normtitle);
    	grnormyield[i]->GetYaxis()->SetLabelSize(0.035);
    	grnormyield[i]->GetXaxis()->SetLabelSize(0.035);
    	grnormyield[i]->GetYaxis()->SetTitleSize(0.08);
    	grnormyield[i]->GetXaxis()->SetTitleSize(0.08);
    	grnormyield[i]->GetXaxis()->SetTitleOffset(1);
    	grnormyield[i]->GetYaxis()->SetTitleOffset(1.5);
    	grnormyield[i]->GetXaxis()->SetTitle("t'");
    	grnormyield[i]->GetYaxis()->SetTitle("CORRECTED");
    	grnormyield[i]->GetHistogram()->SetMinimum(0);
    	grnormyield[i]->SetMarkerStyle(8);
    	grnormyield[i]->SetMarkerSize(1);
    	grnormyield[i]->SetMarkerColor(4);

    	grnormyield[i]->Draw("AP*");
		c3->Update();
    	//---------------------------draw Tslope------------------------------------
    
    

    	// write to slopedat which is the output file tslope.dat,
		slopedat<<databeam[i]<<" "<<-genslope[i]<<" "<<endl;  //JB added: genslope is the exponental fit parameter for the generated events
    	//JB slopedat<<databeam[i]<<" "<<-genslope[i]<<" "<<-crosslope[i]<<" "<<endl; 
		
    

 	}
    slopedat.close();
    c3->Update();
   	cout<<"updating c3"<<endl;
    ps->NewPage();
    c3->Clear();

 
  
   
  
    //---------------------------------------plot the result of Tslope-----------------------------
    TMultiGraph *mgt=new TMultiGraph();
    TGraph *inslope=new TGraph(bins, databeam, genslope);    
    //jb TGraph *outslope=new TGraph(bins, databeam, crosslope);    
    inslope->SetMarkerStyle(8);
    inslope->SetMarkerSize(1);
    inslope->SetMarkerColor(2);
    //outslope->SetMarkerStyle(8);
    //outslope->SetMarkerSize(1);
    //outslope->SetMarkerColor(4);
    mgt->Add(inslope);
    //mgt->Add(outslope);
    TLegend *legt=new TLegend(0.7,0.8,0.9,0.9);
    legt->AddEntry(inslope, "simulation t slope", "p");
    //legt->AddEntry(outslope, "d#sigma/dt  slope", "p");
    mgt->SetTitle("t slope (GeV/c^{2})^{2} : E_{#gamma} (GeV)");
    mgt->Draw("AP");
    legt->Draw();
    c3->Update(); 
    //c3->Print("tslope.eps");
  	cout<<"updating c3"<<endl;
    ps->Close();
    //cout<<"checking ps pointer"<<endl;
    
}
 
