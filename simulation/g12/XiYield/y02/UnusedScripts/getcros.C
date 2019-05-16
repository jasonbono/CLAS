/*

MADE tslope.C FROM THIS SCRIPT

JB this macro brings in casflux.dat, where does this come from?

Input:

1) casyield.dat (from casyield.C)
2) casflux.dat

Output:
1) tslope.dat
2) crosout.dat

Considerations:
1) The output of casyield.C is .newdat but the input of getcros.C is .dat? 
i may have to change this.

2) getting a seg-fault when calling

3) dont know how to call properly (ie need to look up the meaning of "bins" and "minmc")

*/
void getcros(Int_t bins, Int_t minmc){
 //  Float_t t[4]={0.1,0.5,1.0,1.5};
//   ifstream mcdat[4];
   ifstream yielddat,fluxdat;
  
//   Int_t color[4]={5,2,4,30};
//   Int_t Style[4]={8,8,8,8};
   gStyle->SetPadLeftMargin(0.3);
   gStyle->SetPadBottomMargin(0.2);
   gStyle->SetPadTopMargin(0.2);
   gStyle->SetOptFit(1);
   Float_t t[11];
  ifstream mcdat, gendat;
  ofstream slopedat,crosdat;
  Double_t BR;
  BR=1;
  TF1 *fg[11], *fc[11];
  char genin[512],mcin[512],psfile[512],yieldin[512],fluxin[512], slopeout[512],crosout[512];
  sprintf(yieldin, "./results/casyield.dat");
  sprintf(fluxin, "./results/casflux.dat");
  sprintf(slopeout, "./results/tslope.dat");
  sprintf(crosout, "./results/crosout.dat");
  Int_t k;
  Int_t tbin, tbinmax[11], fitmaxbin;
  Double_t genslope[11], crosslope[11], fitcros[11];
  Double_t databeam[11],databeamerr[11],datayield[11][10],datayielderr[11][10], normyield[11][10], normyielderr[11][10], totalnormyield[11], totalnormyielderr[11];
  Double_t w[11], werr[11];
  Double_t bg[11]={1.13049, 1.18169, 1.1783, 1.18175, 1.17314, 1.1737, 1.25825, 1.1279, 1.18164, 1.12222,1.12};
  Double_t fluxbeam[11],flux[11],lowflux[11],highflux[11],tpkp[11][10],tpkperr[11][10];
  Double_t mp=0.938272;
   Double_t fitlow, fithigh;
  //read in yield info
  yielddat.open(yieldin, ios::in);
  slopedat.open(slopeout, ios::out);
  crosdat.open(crosout, ios::out);
  while(yielddat){
    //cout<<"number of beam bins is " <<bins<<endl;
    for(k=0;k<bins;k++){
      yielddat>>databeam[k];
      Int_t check=0;
      for(tbin=0;tbin<=10;tbin++){
	yielddat>>datayield[k][tbin]>>datayielderr[k][tbin];
	if((datayield[k][tbin]<1||datayield[k][tbin]>5000)&&!check&&tbin>1){
	  tbinmax[k]=tbin;
	  check=1;
	}
	//cout<<datayield[k][tbin]<<" ";

      }
      w[k]=sqrt(mp*mp+2*mp*databeam[k]);
      werr[k]=0.01;
      databeamerr[k]=0.05;
      //cout<<"number of t bins is "<<tbinmax[k]<<endl;
      //cout<<"k="<<k<<endl;
    }
  }
  yielddat.close();

  //read in flux info
  fluxdat.open(fluxin, ios::in);
  while(fluxdat){
    for(k=0;k<bins;k++){
      fluxdat>>fluxbeam[k]>>lowflux[k]>>highflux[k]>>flux[k];
      //cout<<k<<" "<<fluxbeam[k]<<" "<<flux[k]<<endl;
    }
  }
  fluxdat.close();
  sprintf(psfile, "acc.ps");
  TPostScript *ps = new TPostScript(psfile, 111);
  Int_t i;
  Double_t yield[11][10], yielderr[11][10];
  Double_t mcyield[11][10], mcyielderr[11][10];
  Double_t genyield[11][10], genyielderr[11][10];
  Double_t acc[11][10],accerr[11][10];
  Double_t cros[11][10],croserr[11][10];
  Double_t totalcros[11], totalcroserr[11];
  Double_t mcbeam[11], mcbeamerr[11];
  Double_t genbeam[11], genbeamerr[11];
  TGraphErrors *gr1[11];
  TGraphErrors *grc[11];
  TGraph *grgen[11], *grdet[11], *gracc[11], *grdata[11], *grnormyield[11];
  TAxis *yaxis[11];
  TAxis *xaxis[11];
 

 




  //TGraph *gr1[4];
  tbin=0;
    sprintf(mcin,"casmctyield.dat");
    mcdat.open(mcin, ios::in);
    //cout<<mcin<<" "<<tbin<<endl;
    while(mcdat){
      for(i=0;i<bins;i++){
	mcdat>>mcbeam[i];
	  for(tbin=0;tbin<=10;tbin++){
	    mcdat>>mcyield[i][tbin]>>mcyielderr[i][tbin];
	  }
	  mcbeamerr[i]=0.01;
      }
    }
   
   mcdat.close();

  tbin=0;
      sprintf(genin,"casgentyield.dat");
    gendat.open(genin, ios::in);
    //cout<<genin<<" "<<tbin<<endl;
    while(gendat){
      for(i=0;i<bins;i++){
	gendat>>genbeam[i];
	  for(tbin=0;tbin<=10;tbin++){
	    gendat>>genyield[i][tbin]>>genyielderr[i][tbin];
	    cout<<genbeam[i]<<" "<<genyield[i][tbin]<<endl;

	  }
		  genbeamerr[i]=0.01;
      }
    }
    gendat.close();
    //end of reading data files

   Double_t tstep;
   if(i<1) tstep=0.15;
   else tstep=0.25;


    //Now calulating cros sections
    for(i=0;i<bins;i++){
      totalcros[i]=0;
      totalcroserr[i]=0;
      totalnormyield[i]=0;
      totalnormyielderr[i]=0;
     //cout<<"number of tbins is "<<tbinmax[i]<<endl;
      for(tbin=0;tbin<tbinmax[i];tbin++){
	cout<<genyield[i][tbin]<<endl;
	if(genyield[i][tbin]>0&&mcyield[i][tbin]>minmc){
	  //acc[i][tbin]=mcyield[i][tbin]/genevents;
	  acc[i][tbin]=mcyield[i][tbin]/genyield[i][tbin];
	  normyield[i][tbin]=datayield[i][tbin]/acc[i][tbin];
	  normyielderr[i][tbin]=datayielderr[i][tbin]/acc[i][tbin];
	  //BR=0.25*0.69*0.45
	  //>2 photons correction factor:1.06
	  //ST resolution factor:1.05
	  //tagger constant background:bg[i]
	  //tripping factor 1/1.08
	  cros[i][tbin]=normyield[i][tbin]*0.58*1.06*1000000000*1.05*bg[i]/(BR*flux[i]*1.08);
	  croserr[i][tbin]=normyielderr[i][tbin]*0.58*1.06*1000000000*1.05*bg[i]/(BR*flux[i]*1.08);
	  totalnormyield[i]=totalnormyield[i]+normyield[i][tbin];
	  totalnormyielderr[i]=sqrt(totalnormyielderr[i]*totalnormyielderr[i]+normyielderr[i][tbin]*normyielderr[i][tbin]);
	 //cout<<"tbinmax="<<tbinmax[i]<<" "<<"beam bin "<<i<<" tbin "<<tbin<<" "<<acc[i][tbin]<<" "<<normyield[i][tbin]<<" "<<totalnormyield[i]<<endl;
	}
	else {
	  acc[i][tbin]=0;
	  normyield[i][tbin]=0;
	  cros[i][tbin]=0;
	  croserr[i][tbin]=0;
	  normyielderr[i][tbin]=0;
	  totalnormyield[i]=totalnormyield[i]+normyield[i][tbin];
	  totalnormyielderr[i]=sqrt(totalnormyielderr[i]*totalnormyielderr[i]+normyielderr[i][tbin]);	  
	//cout<<"maxtbin="<<tbinmax[i]<<" "<<tbin<<" "<<acc[i][tbin]<<" "<<normyield[i][tbin]<<endl;
	
	}
      }
      //totalcros[i]=totalcros[i]*0.58*1.06*1000000000/(BR*flux[i])*tstep;
	totalcros[i]=totalnormyield[i]*0.58*1.06*1000000000*1.05*bg[i]/(BR*flux[i]*1.08);
      //totalcroserr[i]=totalcroserr[i]*0.58*1.06*1000000000/(BR*flux[i])*tstep;
     totalcroserr[i]=totalnormyielderr[i]*0.58*1.06*1000000000*1.05*bg[i]/(BR*flux[i]*1.08);
     //cout<<"total cro section for beam="<<databeam[i]<<" is "<<totalcros[i]<<endl;
    }
    gStyle->SetOptTitle(1);
     TCanvas *c3=new TCanvas("c3", "", 20,20,600,800);
     Int_t pad;
        //char title[30];
    for(i=0;i<bins;i++){
      char gentitle[30], dettitle[30], acctitle[30], datatitle[30], normtitle[30], crostitle[30];
     //cout<<"beam bin"<<i<<" "<<databeam[i]<<endl;
      ps->NewPage();
      c3->Clear();
      c3->Divide(2,3);

      c3->Update();
      if(i<1) tstep=0.15;
      else tstep=0.25;
      for(tbin=0;tbin<tbinmax[i];tbin++){
	tpkp[i][tbin]=(tbin+0.5)*tstep;
	tpkperr[i][tbin]=tstep/2;
      }
    //create cros section graph

    grc[i]=new TGraphErrors(tbinmax[i],tpkp[i],cros[i],tpkperr[i],croserr[i]);
    grgen[i]=new TGraph(tbinmax[i],tpkp[i],genyield[i]);
    grdet[i]=new TGraph(tbinmax[i],tpkp[i],mcyield[i]);
    gracc[i]=new TGraph(tbinmax[i],tpkp[i],acc[i]);
    grdata[i]=new TGraph(tbinmax[i],tpkp[i],datayield[i]);
    grnormyield[i]=new TGraph(tbinmax[i],tpkp[i],normyield[i]);
    //grc[i]->GetHistogram()->SetMaximum(0.03); 
    //draw generator yield
    c3->Update();
     c3->cd(1);
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
   grgen[i]->GetYaxis()->SetTitle("N_generator");
    grgen[i]->GetHistogram()->SetMinimum(0);
    grgen[i]->SetMarkerStyle(8);
    grgen[i]->SetMarkerSize(1);
    grgen[i]->SetMarkerColor(4);

    grgen[i]->Draw("AP*");
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
     //draw detected 
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
   grdet[i]->GetYaxis()->SetTitle("N_detected");
    grdet[i]->GetHistogram()->SetMinimum(0);
    grdet[i]->SetMarkerStyle(8);
    grdet[i]->SetMarkerSize(1);
    grdet[i]->SetMarkerColor(4);

    grdet[i]->Draw("AP*");
    //draw acceptance
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
   gracc[i]->GetYaxis()->SetTitle("Efficiency");
    gracc[i]->GetHistogram()->SetMinimum(0);
    gracc[i]->SetMarkerStyle(8);
    gracc[i]->SetMarkerSize(1);
    gracc[i]->SetMarkerColor(4);

    gracc[i]->Draw("AP*");
    //draw data yield
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
   grdata[i]->GetYaxis()->SetTitle("data yield");
    grdata[i]->GetHistogram()->SetMinimum(0);
    grdata[i]->SetMarkerStyle(8);
    grdata[i]->SetMarkerSize(1);
    grdata[i]->SetMarkerColor(4);

    grdata[i]->Draw("AP*");
    //draw acc corrected yield
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
   grnormyield[i]->GetYaxis()->SetTitle("acc corrected yield");
    grnormyield[i]->GetHistogram()->SetMinimum(0);
    grnormyield[i]->SetMarkerStyle(8);
    grnormyield[i]->SetMarkerSize(1);
    grnormyield[i]->SetMarkerColor(4);

    grnormyield[i]->Draw("AP*");
    //draw differential Xsection
     c3->Update();
    c3->cd(6);
    sprintf(crostitle, "E_{#gamma}: %5.4f  GeV", databeam[i]); 
    grc[i]->SetTitle(crostitle);
    grc[i]->GetYaxis()->SetLabelSize(0.035);
    grc[i]->GetXaxis()->SetLabelSize(0.035);
    grc[i]->GetYaxis()->SetTitleSize(0.08);
    grc[i]->GetXaxis()->SetTitleSize(0.08);
    grc[i]->GetXaxis()->SetTitleOffset(1);
    grc[i]->GetYaxis()->SetTitleOffset(1.5);
    grc[i]->GetXaxis()->SetTitle("t'");
   grc[i]->GetYaxis()->SetTitle("d#sigma/dt * tstep");
    grc[i]->GetHistogram()->SetMinimum(0);
    grc[i]->SetMarkerStyle(8);
    grc[i]->SetMarkerSize(1);
    grc[i]->SetMarkerColor(4);

    grc[i]->Draw("AP*");
    grc[i]->Fit("expo","R", "SAME", fitlow, fithigh);
    fc[i] = grc[i]->GetFunction("expo");
    crosslope[i]=fc[i]->GetParameter(1);
    if(i<8){
      fitcros[i]=(fc[i]->Integral(0,3))/(tpkp[i][2]-tpkp[i][1]);
    }
    else{
      fitcros[i]=(fc[i]->Integral(tpkp[i][1],3))/(tpkp[i][2]-tpkp[i][1])+cros[i][0];
  
    }
    c3->Update();
    //getchar();
    slopedat<<databeam[i]<<" "<<-genslope[i]<<" "<<-crosslope[i]<<" "<<endl;
    crosdat<<databeam[i]<<" "<<fitcros[i]<<" "<<totalcros[i]<<" "<<endl;
    // ps->NewPage();
    //cout<<"total cross section for "<<databeam[i]<<" is "<<totalcros[i]<<endl;
    //cout<<"total norm yield for "<<databeam[i]<<" is "<<totalnormyield[i]<<endl;
    //cout<<"flux for "<<databeam[i]<<" is "<<flux[i]<<endl;
    }
    slopedat.close();
    crosdat.close();
    c3->Update();
   //cout<<"updating c3"<<endl;
    //ps->NewPage();
    //TCanvas *c2=new TCanvas("c2", "",20,20,800,600);
    // c2->Divide(2,1);
    //c2->cd(1);
    ps->NewPage();
    c3->Clear();
    TGraph *gr0=new TGraph(bins,fluxbeam,flux);
    //TXaxis *fxaxis=gr0->GetXaxis();
    //fxaxis->SetTitle("E_{#gamma} (GeV)");
    //TYaxis *fyaxis=gr0->GetYaxis();
  //fYaxis->SetTitle("flux");
    char fluxtitle[30];
    sprintf(fluxtitle, "Flux");
    gr0->SetTitle(fluxtitle);
    gr0->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
    gr0->SetMarkerStyle(8);
    gr0->SetMarkerColor(4);
    gr0->SetMarkerSize(1);
    gr0->Draw("AP");
    c3->Update();
    TGraphErrors *grcros=new TGraphErrors(bins, databeam, totalcros,databeamerr,totalcroserr);
     TGraphErrors *grfitcros=new TGraphErrors(bins, databeam, fitcros,databeamerr,totalcroserr);
   
    grcros->GetHistogram()->SetMinimum(0);
    grcros->SetMarkerStyle(8);
    grcros->SetMarkerSize(1);
    grcros->SetMarkerColor(30);
 
    grfitcros->GetHistogram()->SetMinimum(0);
    grfitcros->SetMarkerStyle(8);
    grfitcros->SetMarkerSize(1);
    grfitcros->SetMarkerColor(1);
    TMultiGraph *mgc=new TMultiGraph();
   mgc->Add(grcros);
    mgc->Add(grfitcros);
     ps->NewPage();
    c3->Clear();
    TLegend *legc=new TLegend(0.7,0.8,0.9,0.9);
    legc->AddEntry(grcros, "#sigma_{total}=#Sigma(#sigma_{i})", "p");
    legc->AddEntry(grfitcros, "#sigma_{total}=#int d#sigma/dt", "p");
    mgc->SetTitle("#sigma (nb) : E_{#gamma} (GeV)");
    mgc->Draw("AP");
    legc->Draw();
    c3->Update(); 
   //c3->Print("cros.eps");
    //compare with other results
    ps->NewPage();
   c3->Clear();

   //plot the cros section vs w
  TGraphErrors *grwcros=new TGraphErrors(bins, w, totalcros,werr,totalcroserr);
     TGraphErrors *grwfitcros=new TGraphErrors(bins, w, fitcros,werr,totalcroserr);
   
    grwcros->GetHistogram()->SetMinimum(0);
    grwcros->SetMarkerStyle(8);
    grwcros->SetMarkerSize(1);
    grwcros->SetMarkerColor(30);
 
    grwfitcros->GetHistogram()->SetMinimum(0);
    grwfitcros->SetMarkerStyle(8);
    grwfitcros->SetMarkerSize(1);
    grwfitcros->SetMarkerColor(1);
    TMultiGraph *mgcw=new TMultiGraph();
   mgcw->Add(grwcros);
    mgcw->Add(grwfitcros);
     ps->NewPage();
    c3->Clear();
    TLegend *legcw=new TLegend(0.7,0.8,0.9,0.9);
    legcw->AddEntry(grcros, "#sigma_{total}=#Sigma(#sigma_{i})", "p");
    legcw->AddEntry(grfitcros, "#sigma_{total}=#int d#sigma/dt", "p");
    mgcw->SetTitle("#sigma (nb) : w (GeV)");
    mgcw->Draw("AP");
    legcw->Draw();
    c3->Update(); 
    //c3->Print("crosw.eps");
    //compare with other results
    ps->NewPage();
   c3->Clear();

    //plot the result of t slope
    TMultiGraph *mgt=new TMultiGraph();
    TGraph *inslope=new TGraph(bins, databeam, genslope);    
    TGraph *outslope=new TGraph(bins, databeam, crosslope);    
    inslope->SetMarkerStyle(8);
    inslope->SetMarkerSize(1);
    inslope->SetMarkerColor(2);
    outslope->SetMarkerStyle(8);
    outslope->SetMarkerSize(1);
    outslope->SetMarkerColor(4);
    mgt->Add(inslope);
    mgt->Add(outslope);
    TLegend *legt=new TLegend(0.7,0.8,0.9,0.9);
    legt->AddEntry(inslope, "simulation t slope", "p");
    legt->AddEntry(outslope, "d#sigma/dt  slope", "p");
    mgt->SetTitle("t slope (GeV/c^{2})^{2} : E_{#gamma} (GeV)");
    mgt->Draw("AP");
    legt->Draw();
    c3->Update(); 
    //c3->Print("tslope.eps");
  cout<<"updating c3"<<endl;
    ps->Close();
    cout<<"checking ps pointer"<<endl;
    
}
 

