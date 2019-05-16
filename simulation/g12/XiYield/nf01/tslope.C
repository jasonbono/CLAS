
/*
MADE THIS SCRIPT FROM "GETCROS.C" AND TOOK OUT THE CROSS SECTION/FLUX PART

Input:
1) casyield.dat (from casyield.C)
2) casmctyield.dat
3) casgenyield.dat

Output:
1) tslope.eps
2) datanorm_tslope.dat
3) gen_tslope.dat
*/

void tslope(Int_t bins, Int_t minmc){


	//style
   	gStyle->SetPadLeftMargin(0.3);
   	gStyle->SetPadBottomMargin(0.2);
   	gStyle->SetPadTopMargin(0.2);
   	gStyle->SetOptFit(1);
		

	//the three input files (see below for reading)
	char yielddatain[512],yieldmcin[512],yieldgenin[512];
	sprintf(yielddatain, "./results/casyield.dat");
	sprintf(yieldmcin,"./results/casmcyield.dat");
	sprintf(yieldgenin,"./results/casgenyield.dat");
  	

	//the ps output file
	char psfile[512];
	sprintf(psfile, "./results/tslope.eps");
	TPostScript *ps = new TPostScript(psfile, 111);


	//the two data output files
	ofstream DataNormSlopeDat;
	char datanormslopeout[512];
	sprintf(datanormslopeout, "./results/datanorm_tslope.dat"); //the acceptance corrected tslope
	DataNormSlopeDat.open(datanormslopeout, ios::out);
	
	ofstream GenSlopeDat;
	char genslopeout[512];
	sprintf(genslopeout, "./results/gen_tslope.dat");
  	GenSlopeDat.open(genslopeout, ios::out);


	//some declarations 
	Float_t t[11]; // 11??	
	Double_t yield[11][10], yielderr[11][10];
  	Double_t mcyield[11][10], mcyielderr[11][10];
  	Double_t genyield[11][10], genyielderr[11][10];
  	Double_t acc[11][10],accerr[11][10];
  	Double_t mcbeam[11], mcbeamerr[11];
  	Double_t genbeam[11], genbeamerr[11];
	Double_t tpkp[11][10],tpkperr[11][10];
	Double_t genslope[11], datanormslope[11];
	Double_t genslopeerr[11], datanormslopeerr[11];
	Double_t databeam[11],databeamerr[11],datayield[11][10],datayielderr[11][10], datanormyield[11][10], datanormyielderr[11][10];
	Double_t overlaymcyield[11][10];
	//Double_t totaldatanormyield[11], totaldatanormyielderr[11];
  	Double_t w[11], werr[11];
  	Double_t mp=0.938272;
   	Double_t fitlow, fithigh;

	//counters
	Int_t k,i;
  	Int_t tbin, tbinmax[11], fitmaxbin;
	
	//graphs
	TGraphErrors  *grdatanormyield[11], grgen[11];
	TGraph *grdet[11], *gracc[11], *grdata[11];
	TGraph *groverlaymc[11];
	TMultiGraph *mgoverlay[11];
  	TAxis *yaxis[11];
  	TAxis *xaxis[11];
	
	//fits
	TF1 *fg[11], *fdet[11], facc, *fdata[11], *fdatanorm[11]; //jb fit grgen,grdet,gracc,grdata,normalizeddata


	//READING IN DATA FILES
	//read data
	ifstream yielddat;
	yielddat.open(yielddatain, ios::in);
 	float datatotal[11] = {0};
	int test = 0;
	if(yielddat)
	{
		test+=1;
		cout << "in this loop " <<test<<endl;
    	for(k=0;k<bins;k++)
		{
      		yielddat>>databeam[k]; //Read in the beam energy for the Data events

      		Int_t check=0;
      		for(tbin=0;tbin<=9;tbin++)  //jb changed to 9 from 10
			{
				yielddat>>datayield[k][tbin]>>datayielderr[k][tbin]; // Read in yeild and the error for the Data events
				if(datayield[k][tbin]>0)
				{
					cout <<" adding data: " << datayield[k][tbin] <<endl;
					datatotal[k] += datayield[k][tbin];
				}
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
	yielddat.close();

  	//read mc
  	ifstream mcdat; 
    mcdat.open(yieldmcin, ios::in);
    tbin=0;
	float mctotal[11] = {0}, overlayfactor[11] = {0};
	if(mcdat) //mcdat is the casmctyield.dat file
	{
    	for(i=0;i<bins;i++)
		{
			mcdat>>mcbeam[i];
			for(tbin=0;tbin<=9;tbin++) // jb changed to 9 from 10
			{
	    		mcdat>>mcyield[i][tbin]>>mcyielderr[i][tbin];
				if(mcyield[i][tbin]>0)
				{	
					//cout << "i = " <<i<<"  tbin="<<tbin<<endl;
					//cout <<" adding mc: " << mcyield[i][tbin] <<endl;
					mctotal[i] += mcyield[i][tbin];
				}
	  		}
	  		mcbeamerr[i]=0.01;
			//calculate normaization factor in each energy bin (to overlay mc and data)
			overlayfactor[i] = datatotal[i]/mctotal[i];
			//cout << "overlayfactor["<<i<<"] = "<< overlayfactor[i] <<endl;
     	}
  	}
	mcdat.close();

	//now apply factor to generate new array of mc events to overlay with the data
	//float overlaymcyield[11][10] = {0};
	//float overlaymcyielder[11][10] = {0};
	for(i=0;i<bins;i++)
	{
		for(tbin=0;tbin<=9;tbin++)
		{	
			if (mcyield[i][tbin] > 0)
			{
				overlaymcyield[i][tbin] =  overlayfactor[i]*mcyield[i][tbin];
			}
			if (mcyield[i][tbin] < 0)
			{
				overlaymcyield[i][tbin] =  mcyield[i][tbin];
			}
			cout << " overlayfactor = " << overlaymcyield[i][tbin] << " mcyield " << mcyield[i][tbin] <<endl; 
			cout << "overlaymcyield " << overlaymcyield[i][tbin] <<endl;
		}
	}
	

	//read gen
	ifstream gendat;
    gendat.open(yieldgenin, ios::in);
    tbin=0;
	if(gendat)
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
  
	

  	//Store yeilds in 2d arrays and cacluclate aceptance corrected yeilds
	Double_t tstep;
	tstep=0.25;    
	for(i=0;i<bins;i++)
	{
      	//totaldatanormyield[i]=0; //probably dont need
      	//totaldatanormyielderr[i]=0; //probably dont need
      	for(tbin=0;tbin<tbinmax[i];tbin++)
		{
			//cout<<genyield[i][tbin]<<endl;
			if(genyield[i][tbin]>0&&mcyield[i][tbin]>minmc) //minmc specifed when calling tslope()
			{
	  			acc[i][tbin]=mcyield[i][tbin]/genyield[i][tbin]; // acc is acceptance corrections
	  			datanormyield[i][tbin]=datayield[i][tbin]/acc[i][tbin]; // this is accptance corrected yeild
	  			datanormyielderr[i][tbin]=datayielderr[i][tbin]/acc[i][tbin];
	  			//totaldatanormyield[i]=totaldatanormyield[i]+datanormyield[i][tbin]; // adding yeilds over all bins CAN PROBABLY TAKE THIS OUT
	  			//totaldatanormyielderr[i]=sqrt(totaldatanormyielderr[i]*totaldatanormyielderr[i]+datanormyielderr[i][tbin]*datanormyielderr[i][tbin]);
			}	
			else 
			{
	  			acc[i][tbin]=0;
	  			datanormyield[i][tbin]=0;
	  			datanormyielderr[i][tbin]=0;
	  			//totaldatanormyield[i]=totaldatanormyield[i]+datanormyield[i][tbin];
	  			//totaldatanormyielderr[i]=sqrt(totaldatanormyielderr[i]*totaldatanormyielderr[i]+datanormyielderr[i][tbin]);	  	
			}
      	}
    }
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~finished storing and calculating~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	
	
	
	
	//=====================================================GRAPH=========================================================
    
	gStyle->SetOptTitle(1);
    TCanvas *c3=new TCanvas("c3", "", 20,20,600,800);
    Int_t pad;
    for(i=0;i<bins;i++)
	{
      	char gentitle[30], dettitle[30], acctitle[30], datatitle[30], datanormtitle[30]; //jb what is det? it means detected, for A1C
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
			//tpkperr[i][tbin]=tstep/2;
			tpkperr[i][tbin]=0;
      	}
    	//--------------------------fill the TGraph objects with the 2d vectors--------------------------
    	grgen[i]=new TGraphErrors(tbinmax[i],tpkp[i],genyield[i],tpkperr[i],genyielderr[i]);
    	grdet[i]=new TGraph(tbinmax[i],tpkp[i],mcyield[i]);
    	gracc[i]=new TGraph(tbinmax[i],tpkp[i],acc[i]);
    	grdata[i]=new TGraph(tbinmax[i],tpkp[i],datayield[i]);
    	grdatanormyield[i]=new TGraphErrors(tbinmax[i],tpkp[i],datanormyield[i],tpkperr[i],datanormyielderr[i]); //n x y ex ey
		groverlaymc[i]=new TGraph(tbinmax[i],tpkp[i],overlaymcyield[i]);
		//groverlaymc[i]=new TGraph(tbinmax[i],tpkp[i],datayield[i]);
		mgoverlay[i]=new TMultiGraph();
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
		//-----------fit the graph of generated events to an exponental
    	if(i<8){
      		fitlow=tpkp[i][0];
    	}
    	else{
      		fitlow=tpkp[i][0];
    	}
    	fitmaxbin=tbinmax[i]-1;
    	fithigh=tpkp[i][fitmaxbin];
		cout <<"=====================GENERATED EVENTS========================"<<endl;
    	cout<<fitlow<<" "<<fithigh<<" "<<tbinmax[i]<<" "<<tpkp[i][fitmaxbin]<<endl;
		cout <<"======================================================="<<endl;
		cout << endl;	
    	grgen[i].Fit("expo","", "", fitlow, fithigh);
   		fg[i] = grgen[i].GetFunction("expo");
    	genslope[i]=fg[i]->GetParameter(1);
		genslopeerr[i]=fg[i]->GetParError(1);
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
    	grdet[i]->SetMarkerColor(2);
	
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
    	//-----------------------------draw graph of acceptance corrected yeilds---------------
    	c3->Update();
    	c3->cd(5);
    	sprintf(datanormtitle, "E_{#gamma}: %5.4f  GeV", databeam[i]); 
    	grdatanormyield[i]->SetTitle(datanormtitle);
    	grdatanormyield[i]->GetYaxis()->SetLabelSize(0.035);
    	grdatanormyield[i]->GetXaxis()->SetLabelSize(0.035);
    	grdatanormyield[i]->GetYaxis()->SetTitleSize(0.08);
    	grdatanormyield[i]->GetXaxis()->SetTitleSize(0.08);
    	grdatanormyield[i]->GetXaxis()->SetTitleOffset(1);
    	grdatanormyield[i]->GetYaxis()->SetTitleOffset(1.5);
    	grdatanormyield[i]->GetXaxis()->SetTitle("t'");
    	grdatanormyield[i]->GetYaxis()->SetTitle("DATA CORRECTED");
    	grdatanormyield[i]->GetHistogram()->SetMinimum(0);
    	grdatanormyield[i]->SetMarkerStyle(8);
    	grdatanormyield[i]->SetMarkerSize(1);
    	grdatanormyield[i]->SetMarkerColor(4);

    	grdatanormyield[i]->Draw("AP*");
		//-----------fit the graph of acceptance corrected events to an exponental-----------------------------------
    	if(i<1){
      		fitlow=tpkp[i][1];
    	}
		else if(i<2){
			fitlow=tpkp[i][1];
		}
    	else{
      		fitlow=tpkp[i][1];
    	}
    	fitmaxbin=tbinmax[i]-1;
    	fithigh=tpkp[i][fitmaxbin];
		cout <<"================ACCEPTANCE CORRECTED========================"<<endl;
		cout<<fitlow<<" "<<fithigh<<" "<<tbinmax[i]<<" "<<tpkp[i][fitmaxbin]<<endl;
		cout <<"==================================---======================"<<endl;
		cout <<endl;
    	grdatanormyield[i]->Fit("expo","", "", fitlow, fithigh);
   		fdatanorm[i] = grdatanormyield[i]->GetFunction("expo");
    	datanormslope[i]=fdatanorm[i]->GetParameter(1);
		datanormslopeerr[i]=fdatanorm[i]->GetParError(1);

		
		
		///-----------------------------draw graph of overlay---------------
		c3->Update();
    	c3->cd(6);
  		groverlaymc[i]->SetMarkerColor(2);
		mgoverlay[i]->Add(groverlaymc[i]);
		mgoverlay[i]->Add(grdata[i]);
		mgoverlay[i]->Draw("AP*");
		
		c3->Update();
		
    
    	//output the Tslope results to file (for the normalized data and the generated data)
		GenSlopeDat<<databeam[i]<<" "<<-genslope[i]<<" "<<endl;  
		DataNormSlopeDat<<databeam[i]<<" "<<-datanormslope[i]<<" "<<endl;

	}
    GenSlopeDat.close();
	DataNormSlopeDat.close();
    c3->Update();
   	cout<<"updating c3"<<endl;
    ps->NewPage();
    c3->Clear();

 
  
   

    //---------------------------------------plot the result of Tslope-----------------------------
    TMultiGraph *mgt=new TMultiGraph();
    

	TGraphErrors *genslopegraph=new TGraphErrors(bins, databeam, genslope, databeamerr, genslopeerr);
	TGraphErrors *datanormslopegraph=new TGraphErrors(bins, databeam, datanormslope, databeamerr, datanormslopeerr);   

    genslopegraph->SetMarkerStyle(8);
    genslopegraph->SetMarkerSize(1);
    genslopegraph->SetMarkerColor(2);
	genslopegraph->SetMaximum(0);
    datanormslopegraph->SetMarkerStyle(8);
    datanormslopegraph->SetMarkerSize(1);
    datanormslopegraph->SetMarkerColor(4);
	datanormslopegraph->SetMaximum(0);
    mgt->Add(genslopegraph);
    mgt->Add(datanormslopegraph);
	mgt->SetMaximum(0);
    TLegend *legt=new TLegend(0.7,0.8,0.9,0.9);
    legt->AddEntry(genslopegraph, "Generated tslope", "p");
    legt->AddEntry(datanormslopegraph, "Normalized Data tslope", "p");
    mgt->SetTitle("TSLOPE (GeV/c^{2})^{2} : E_{#gamma} (GeV)");
    mgt->Draw("AP");
    legt->Draw();
    c3->Update(); 
    //c3->Print("tslope.eps");
  	cout<<"updating c3"<<endl;
    ps->Close();
    //cout<<"checking ps pointer"<<endl;





    
}
 
