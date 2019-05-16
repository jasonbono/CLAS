
/*
MADE THIS SCRIPT FROM "GETCROS.C" AND TOOK OUT THE CROSS SECTION/FLUX PART

Input:
1) casyield.dat (from casyield.C)
2) casmctyield.dat
3) casgenyield.dat

Output:
1) normdata_tslope.dat
2) gen_tslope.dat
3) tslope.eps
*/

void tslope(Int_t bins, Int_t minmc){


	// - - - - - - - - - - - - - - - - -style- - - - - - - - - - - - - - - - -
   	gStyle->SetPadLeftMargin(0.3);
   	gStyle->SetPadBottomMargin(0.2);
   	gStyle->SetPadTopMargin(0.2);
   	gStyle->SetOptFit(1);
	

	// - - - - - - - - - - - - - - - - - - -decare names for the input and output files - - - - - - - - - - - - - - - - - - - - 
	ifstream mcdat, gendat, yielddat;
	ofstream slopedat, genslopedat, mcslopedat, normslopedat; //jb
	char yieldgenin[512],yieldmcin[512],psfile[512],yieldin[512], slopeout[512];
	char genslopeout[512], mcslopeout[512], normslopeout[512]; //jb
	sprintf(psfile, "./results/tslope.eps");
	TPostScript *ps = new TPostScript(psfile, 111);
	
	//three input files
	sprintf(yieldin, "./results/casyield.dat");
	sprintf(yieldmcin,"./results/casmcyield.dat");
	sprintf(yieldgenin,"./results/casgenyield.dat");
  	
	//four output files
	sprintf(slopeout, "./results/data_tslope.dat");
	sprintf(normslopeout, "./results/normdata_tslope.dat"); //jb the acceptance corrected tslope
	sprintf(genslopeout, "./results/gen_tslope.dat"); //jb
	sprintf(mcslopeout, "./results/mc_tslope.dat");  //jb

	//only actualy output two data files
  	genslopedat.open(genslopeout, ios::out);
	normslopedat.open(normslopeout, ios::out);


	//- - - - - - - - - - - - - - - - - - - - - -  - - some declarations - - - - - - - - - - - - - - - - - - - - - - - - 
	Float_t t[11]; // 11??
	
	Double_t yield[11][10], yielderr[11][10];
  	Double_t mcyield[11][10], mcyielderr[11][10];
  	Double_t genyield[11][10], genyielderr[11][10];
  	Double_t acc[11][10],accerr[11][10];
  	Double_t mcbeam[11], mcbeamerr[11];
  	Double_t genbeam[11], genbeamerr[11];
	
	Double_t tpkp[11][10],tpkperr[11][10];
	Double_t genslope[11], normslope[11];
  	Double_t databeam[11],databeamerr[11],datayield[11][10],datayielderr[11][10], normyield[11][10], normyielderr[11][10], totalnormyield[11], totalnormyielderr[11];
  	Double_t w[11], werr[11];
  	Double_t mp=0.938272;
   	Double_t fitlow, fithigh;
	// initialze array by doing myArray[10] = { 0 }
	
	//counters
	Int_t k,i;
  	Int_t tbin, tbinmax[11], fitmaxbin;
	
	//graphs
  	//TGraph *grgen[11], *grdet[11], *gracc[11], *grdata[11], *grnormyield[11]; // should convert to TGraphErrors
	TGraphErrors  *grnormyield[11], grgen[11];
	TGraph *grdet[11], *gracc[11], *grdata[11];
  	TAxis *yaxis[11];
  	TAxis *xaxis[11];
	
	//fits
	TF1 *fg[11], *fdet[11], facc, *fdata[11], *fnorm[11]; //jb fit grgen,grdet,gracc,grdata,normalizeddata
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 

	
	//============================================READING DATA FILES===============================================


	
	//-----------------------------read in the yields and errors for the DATA events------------------
	yielddat.open(yieldin, ios::in);

 	while(yielddat)
	{
    	for(k=0;k<bins;k++)
		{
      		yielddat>>databeam[k]; //Read in the beam energy for the Data events

      		Int_t check=0;
      		for(tbin=0;tbin<=9;tbin++)  //jb changed to 9 from 10
			{
				yielddat>>datayield[k][tbin]>>datayielderr[k][tbin]; // Read in yeild and the error for the Data events
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


  	//----------------------read in the yeilds and errors for the ACCEPTED events-------------------
  	tbin=0;
 
    mcdat.open(yieldmcin, ios::in);
    while(mcdat) //mcdat is the casmctyield.dat file
	{
    	for(i=0;i<bins;i++)
		{
			mcdat>>mcbeam[i];
			for(tbin=0;tbin<=9;tbin++) // jb changed to 9 from 10
			{
	    		mcdat>>mcyield[i][tbin]>>mcyielderr[i][tbin];
	  		}
	  		mcbeamerr[i]=0.01;
     	}
  	}
	mcdat.close();


	//-----------------------read in the yields and errors for GENERATED yields--------------------
	tbin=0;
    gendat.open(yieldgenin, ios::in);
    while(gendat)
	{
   		for(i=0;i<bins;i++)
		{
			gendat>>genbeam[i];
	  		for(tbin=0;tbin<=9;tbin++) //changed to 9 from 10
			{
	    		gendat>>genyield[i][tbin]>>genyielderr[i][tbin];
	  		}
			genbeamerr[i]=0.01;
    	}
 	}
    gendat.close();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~end of reading data files~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
   
	Double_t tstep;
	tstep=0.25;
	//========================Store yeilds in 2d vectors and cacluclate aceptance corrected yeilds==========================
    
	for(i=0;i<bins;i++)
	{
      	totalnormyield[i]=0; //probably dont need
      	totalnormyielderr[i]=0; //probably dont need
      	for(tbin=0;tbin<tbinmax[i];tbin++)
		{
			//cout<<genyield[i][tbin]<<endl;
			if(genyield[i][tbin]>0&&mcyield[i][tbin]>minmc) //minmc specifed when calling tslope()
			{
	  			acc[i][tbin]=mcyield[i][tbin]/genyield[i][tbin]; // acc is acceptance corrections
	  			normyield[i][tbin]=datayield[i][tbin]/acc[i][tbin]; // this is accptance corrected yeild
	  			normyielderr[i][tbin]=datayielderr[i][tbin]/acc[i][tbin];
	  			totalnormyield[i]=totalnormyield[i]+normyield[i][tbin]; // adding yeilds over all bins CAN PROBABLY TAKE THIS OUT
	  			totalnormyielderr[i]=sqrt(totalnormyielderr[i]*totalnormyielderr[i]+normyielderr[i][tbin]*normyielderr[i][tbin]);
			}	
			else 
			{
	  			acc[i][tbin]=0;
	  			normyield[i][tbin]=0;
	  			normyielderr[i][tbin]=0;
	  			totalnormyield[i]=totalnormyield[i]+normyield[i][tbin];
	  			totalnormyielderr[i]=sqrt(totalnormyielderr[i]*totalnormyielderr[i]+normyielderr[i][tbin]);	  
				//cout <<" . . . . . . . . . . . ."<<endl;
				//cout<<"maxtbin="<<tbinmax[i]<<" "<<tbin<<" "<<acc[i][tbin]<<" "<<normyield[i][tbin]<<endl;
				//cout <<" . . . . . . .THE NORMALIZED YIELDS ARE NOT BEING CALCULATED FOR THIS BIN . . . . . . ." <<endl;
				//cout <<endl;	
			}
      	}
    }
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~finished storing and calculating~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//^^^^^^^^^^^^^^^^^JB SEP 19 2012, ALL ABOVE THIS LINE HAS BEEN DEBUGED ^^^^^^^^^^^^^^^^^^^^
	
	
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

      	//if(i<1) tstep=0.15;
      	//else tstep=0.25;
		tstep=0.25;
      	for(tbin=0;tbin<tbinmax[i];tbin++)
		{
			tpkp[i][tbin]=(tbin+0.5)*tstep;
			tpkperr[i][tbin]=tstep/2;
      	}
    	//--------------------------fill the TGraph objects with the 2d vectors--------------------------
    	grgen[i]=new TGraphErrors(tbinmax[i],tpkp[i],genyield[i],tpkperr[i],genyielderr[i]);
    	grdet[i]=new TGraph(tbinmax[i],tpkp[i],mcyield[i]);
    	gracc[i]=new TGraph(tbinmax[i],tpkp[i],acc[i]);
    	grdata[i]=new TGraph(tbinmax[i],tpkp[i],datayield[i]);
    	grnormyield[i]=new TGraphErrors(tbinmax[i],tpkp[i],normyield[i],tpkperr[i],normyielderr[i]); //n x y ex ey
    	//grc[i]->GetHistogram()->SetMaximum(0.03); 
    	//draw generator yield
    	c3->Update();
     	c3->cd(1);
    	
		//----------------------------------draw graph of generated events--------------------------
		sprintf(gentitle, "E_{#gamma}: %5.4f  GeV", databeam[i]); 
   		//cout<<gentitle<<" flux is"<<flux[i]<<endl;
    	grgen[i].SetTitle(gentitle);
    	grgen[i].GetYaxis()->SetLabelSize(0.035);
    	grgen[i].GetXaxis()->SetLabelSize(0.035);
    	grgen[i].GetYaxis()->SetTitleSize(0.08);
    	grgen[i].GetXaxis()->SetTitleSize(0.08);
    	grgen[i].GetXaxis()->SetTitleOffset(1);
    	grgen[i].GetYaxis()->SetTitleOffset(1.5);
    	grgen[i].GetXaxis()->SetTitle("t'");
   		grgen[i].GetYaxis()->SetTitle("GENERATED");
    	grgen[i].GetHistogram()->SetMinimum(0);
    	grgen[i].SetMarkerStyle(8);
    	grgen[i].SetMarkerSize(1);
    	grgen[i].SetMarkerColor(4);

    	grgen[i].Draw("AP*");
		//-----------fit the graph of generaged events to an exponental
    	if(i<8){
      		fitlow=tpkp[i][1];
    	}
    	else{
      		fitlow=tpkp[i][1];
    	}
    	fitmaxbin=tbinmax[i]-2;
    	fithigh=tpkp[i][fitmaxbin];
		cout <<"=====================GENERATED EVENTS========================"<<endl;
    	cout<<fitlow<<" "<<fithigh<<" "<<tbinmax[i]<<" "<<tpkp[i][fitmaxbin]<<endl;
		cout <<"======================================================="<<endl;
		cout << endl;	
    	grgen[i].Fit("expo","", "", fitlow, fithigh);
   		fg[i] = grgen[i].GetFunction("expo");
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
		//-----------fit the graph of acceptance corrected events to an exponental-----------------------------------
    	if(i<1){
      		fitlow=tpkp[i][2];
    	}
		else if(i<2){
			fitlow=tpkp[i][1];
		}
    	else{
      		fitlow=tpkp[i][2];
    	}
    	fitmaxbin=tbinmax[i]-2;
    	fithigh=tpkp[i][fitmaxbin];
		cout <<"================ACCEPTANCE CORRECTED========================"<<endl;
		cout<<fitlow<<" "<<fithigh<<" "<<tbinmax[i]<<" "<<tpkp[i][fitmaxbin]<<endl;
		cout <<"==================================---======================"<<endl;
		cout <<endl;
    	grnormyield[i]->Fit("expo","", "", fitlow, fithigh);
   		fnorm[i] = grnormyield[i]->GetFunction("expo");
    	normslope[i]=fnorm[i]->GetParameter(1);
		c3->Update();
		
		
		
    
    	//output the Tslope results to file (for the normalized data and the generated data)
		genslopedat<<databeam[i]<<" "<<-genslope[i]<<" "<<endl;  
  		normslopedat<<databeam[i]<<" "<<-normslope[i]<<" "<<endl;
    

 	}
    genslopedat.close();
	normslopedat.close();
    c3->Update();
   	cout<<"updating c3"<<endl;
    ps->NewPage();
    c3->Clear();

 
  
   

    //---------------------------------------plot the result of Tslope-----------------------------
    TMultiGraph *mgt=new TMultiGraph();
    TGraph *genslopegraph=new TGraph(bins, databeam, genslope);
	TGraph *normslopegraph=new TGraph(bins, databeam, normslope);   
	//TGraphErrors *genslopegraph=new TGraphErrors(bins, databeam, genslope);
    genslopegraph->SetMarkerStyle(8);
    genslopegraph->SetMarkerSize(1);
    genslopegraph->SetMarkerColor(2);
    normslopegraph->SetMarkerStyle(8);
    normslopegraph->SetMarkerSize(1);
    normslopegraph->SetMarkerColor(4);
    mgt->Add(genslopegraph);
    mgt->Add(normslopegraph);
    TLegend *legt=new TLegend(0.7,0.8,0.9,0.9);
    legt->AddEntry(genslopegraph, "generated tslope", "p");
    legt->AddEntry(normslopegraph, "normalized tslope", "p");
    mgt->SetTitle("TSLOPE (GeV/c^{2})^{2} : E_{#gamma} (GeV)");
    mgt->Draw("AP");
    legt->Draw();
    c3->Update(); 
    //c3->Print("tslope.eps");
  	cout<<"updating c3"<<endl;
    ps->Close();
    //cout<<"checking ps pointer"<<endl;

    
}
 
