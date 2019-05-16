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
   Float_t t[19];
  ifstream mcdat, gendat;
  ofstream slopedat,crosdat, totalcrosdat;
  Double_t BR;
  BR=0.5*0.64;
  TF1 *fg[19], *fc[19], *fce[19];
  char genin[30],mcin[30],psfile[30],yieldin[30],fluxin[30], slopeout[30],crosout[30], totalcrosout[30];
  sprintf(yieldin, "kstaryield.dat");
  sprintf(fluxin, "kstarflux.dat");
  sprintf(slopeout, "tslope.dat");
  sprintf(crosout, "crosout.dat");
  sprintf(totalcrosout, "totalcrosout.dat");
  Int_t k;
  Int_t cosbin, cosbinmin[19], fitmaxbin;
  Double_t genslope[19], crosslope[19], fitcros[19], fitecros[19];
  //Double_t tcros[19]={};
  //Double_t tcroserr[19]={0.691142,0.959883,1.21248,0.709859,0.544812,1.51145,0.728856,0.555364,0.643226,1.29739,2.22284};
  Double_t oldcros[7]={1.2,1.51,0.5,0.46,0.6,0.78,0.12};
  Double_t oldcroserr[7]={0.49,0.57,0.19,0.19,0.25,0.29,0.06};
  Double_t oldbeam[7]={1.85,1.95,2.2,2.6,3.0,3.4,4.7};
  Double_t oldbeamerr[7]={0.05,0.05,0.2,0.2,0.2,0.2,1.1};
 Double_t databeam[19],databeamerr[19],datayield[19][10],datayielderr[19][10], normyield[19][10], normyielderr[19][10], totalnormyield[19], totalnormyielderr[19], w[19], werr[19];
  Double_t bg[19];
  //Double_t bg[19]={1.13049, 1.18169, 1.1783, 1.18175, 1.17314, 1.1737, 1.25825, 1.1279, 1.18164, 1.12222};
  Double_t fluxbeam[19],flux[19],lowflux[19],highflux[19],coskstar[19][10],coskstarerr[19][10];
   Double_t fitlow, fithigh;
  //read in yield info
  yielddat.open(yieldin, ios::in);
  slopedat.open(slopeout, ios::out);
  crosdat.open(crosout, ios::out);
  totalcrosdat.open(totalcrosout, ios::out);
  Double_t mp=0.93827;
  crosdat<<"Egamma(GeV)"<<"\t"<<"Cos*(theta_K+))"<<"\t"<<"dXsec(#mub)"<<" "<<"dXsecErr(#mub)"<<endl;
  totalcrosdat<<"Egamma(GeV)"<<"\t"<<"Xsec=Sigma(dXseci)"<<"\t"<<"Xsec=Int(dXsec)_exponential"<<" "<<"Xsec=Int(dXsec)_pol4"<<"\t"<<"Xsec_error"<<endl;
  while(yielddat){
    //cout<<"number of beam bins is " <<bins<<endl;
    for(k=0;k<bins;k++){
      yielddat>>databeam[k];
      Int_t check=0;
      for(cosbin=0;cosbin<10;cosbin++){
	yielddat>>datayield[k][cosbin]>>datayielderr[k][cosbin];
	if(datayield[k][cosbin]>1&&!check){
	  cosbinmin[k]=cosbin;
	  check=1;
	}
	cout<<datayield[k][cosbin]<<" ";

      }
      databeamerr[k]=0.05;
      w[k]=sqrt(mp*mp+2*mp*databeam[k]);
      werr[k]=mp*databeamerr[k]/w[k];
      cout<<"mininum nonzero bin is bin number "<<cosbinmin[k]<<endl;
      cout<<"k="<<k<<endl;
      //getchar();
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
  sprintf(psfile, "cros.ps");
  TPostScript *ps = new TPostScript(psfile, 111);
  Int_t i;
  Double_t yield[19][10], yielderr[19][10];
  Double_t mcyield[19][10], mcyielderr[19][10];
  Double_t genyield[19][10], genyielderr[19][10];
  Double_t acc[19][10],accerr[19][10];
  Double_t cros[19][10],croserr[19][10];
  Double_t crosw[10][19],croswerr[10][19];
  Double_t totalcros[19], totalcroserr[19];
  Double_t mcbeam[19], mcbeamerr[19];
  Double_t genbeam[19], genbeamerr[19];
  TGraphErrors *gr1[19];
  TGraphErrors *grc[19],*grce[19];
  TGraphErrors *grw[10];
  TGraph *grgen[19], *grdet[19], *gracc[19], *grdata[19], *grnormyield[19];
  TAxis *yaxis[19];
  TAxis *xaxis[19];
 

 




  //TGraph *gr1[4];
  cosbin=0;
    sprintf(mcin,"kstarmctyield.dat");
    mcdat.open(mcin, ios::in);
    //cout<<mcin<<" "<<cosbin<<endl;
    while(mcdat){
      for(i=0;i<bins;i++){
	mcdat>>mcbeam[i];
	  for(cosbin=0;cosbin<10;cosbin++){
	    mcdat>>mcyield[i][cosbin]>>mcyielderr[i][cosbin];
	  }
	  mcbeamerr[i]=0.01;
      }
    }
   
   mcdat.close();

  cosbin=0;
      sprintf(genin,"kstargentyield.dat");
    gendat.open(genin, ios::in);
    //cout<<genin<<" "<<cosbin<<endl;
    while(gendat){
      for(i=0;i<bins;i++){
	gendat>>genbeam[i];
	  for(cosbin=0;cosbin<10;cosbin++){
	    gendat>>genyield[i][cosbin]>>genyielderr[i][cosbin];
	    cout<<genbeam[i]<<" "<<genyield[i][cosbin]<<endl;

	  }
		  genbeamerr[i]=0.01;
      }
    }
    gendat.close();
    //end of reading data files

    cout<<"here"<<endl;

    //Now calulating cros sections
    for(i=0;i<bins;i++){
      Double_t cosstep;
      cosstep=0.2;
      totalcros[i]=0;
      totalcroserr[i]=0;
      totalnormyield[i]=0;
      totalnormyielderr[i]=0;
     //cout<<"number of cosbins is "<<cosbinmin[i]<<endl;
      //for(cosbin=0;cosbin<cosbinmin[i];cosbin++){
      for(cosbin=0;cosbin<10;cosbin++){
	cout<<genyield[i][cosbin]<<endl;
	if(genyield[i][cosbin]>0&&mcyield[i][cosbin]>minmc){
	  //acc[i][cosbin]=mcyield[i][cosbin]/genevents;
	  cout<<"cosbin= "<<cosbin<<endl;
	  acc[i][cosbin]=mcyield[i][cosbin]/genyield[i][cosbin];
	  normyield[i][cosbin]=datayield[i][cosbin]/acc[i][cosbin];
	  normyielderr[i][cosbin]=datayielderr[i][cosbin]/acc[i][cosbin];
	  //BR=1
	  //>2 photons correction factor:1.06
	  //ST resolution factor:1.05
	  //tagger constant background:bg[i]
	  //tripping factor 1/1.08
	  bg[i]=1.15;
	  cros[i][cosbin]=normyield[i][cosbin]*0.58*1.06*1000000*1.05*bg[i]/(BR*flux[i]*1.08)/cosstep;
	  croserr[i][cosbin]=normyielderr[i][cosbin]*0.58*1.06*1000000*1.05**bg[i]/(BR*flux[i]*1.08)/cosstep;
	  crosw[cosbin][i]=cros[i][cosbin]*cosstep;
	  croswerr[cosbin][i]=croserr[i][cosbin]*cosstep;

	  totalnormyield[i]=totalnormyield[i]+normyield[i][cosbin];
	  totalnormyielderr[i]=sqrt(totalnormyielderr[i]*totalnormyielderr[i]+normyielderr[i][cosbin]*normyielderr[i][cosbin]);
	 //cout<<"cosbinmin="<<cosbinmin[i]<<" "<<"beam bin "<<i<<" cosbin "<<cosbin<<" "<<acc[i][cosbin]<<" "<<normyield[i][cosbin]<<" "<<totalnormyield[i]<<endl;
	}
	else {
	  acc[i][cosbin]=0;
	  normyield[i][cosbin]=0;
	  cros[i][cosbin]=0;
	  croserr[i][cosbin]=0;
	  normyielderr[i][cosbin]=0;
	  totalnormyield[i]=totalnormyield[i]+normyield[i][cosbin];
	  totalnormyielderr[i]=sqrt(totalnormyielderr[i]*totalnormyielderr[i]+normyielderr[i][cosbin]);	  
	//cout<<"maxcosbin="<<cosbinmin[i]<<" "<<cosbin<<" "<<acc[i][cosbin]<<" "<<normyield[i][cosbin]<<endl;
	
	}
      }
      //totalcros[i]=totalcros[i]*0.58*1.06*1000000000/(BR*flux[i])*cosstep;
	totalcros[i]=totalnormyield[i]*0.58*1.06*1000000*1.05*bg[i]/(BR*flux[i]*1.08);
      //totalcroserr[i]=totalcroserr[i]*0.58*1.06*1000000000/(BR*flux[i])*cosstep;
     totalcroserr[i]=totalnormyielderr[i]*0.58*1.06*1000000*1.05*bg[i]/(BR*flux[i]*1.08);
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
      cosstep=0.2;
      Int_t maxbins;
      maxbins=2/cosstep;
      for(cosbin=0;cosbin<maxbins;cosbin++){
	coskstar[i][cosbin]=-1+(cosbin+0.5)*cosstep;
	coskstarerr[i][cosbin]=cosstep/2;
      }
    //create cros section graph

    //grc[i]=new TGraphErrors(cosbinmin[i],coskstar[i],cros[i],coskstarerr[i],croserr[i]);
    //grgen[i]=new TGraph(cosbinmin[i],coskstar[i],genyield[i]);
    //grdet[i]=new TGraph(cosbinmin[i],coskstar[i],mcyield[i]);
    //gracc[i]=new TGraph(cosbinmin[i],coskstar[i],acc[i]);
    //grdata[i]=new TGraph(cosbinmin[i],coskstar[i],datayield[i]);
    //grnormyield[i]=new TGraph(10,coskstar[i],normyield[i]);
      grce[i]=new TGraphErrors(10,coskstar[i],cros[i],coskstarerr[i],croserr[i]);
      grc[i]=new TGraphErrors(8,&coskstar[i][2],&cros[i][2],&coskstarerr[i][2],&croserr[i][2]);
      grgen[i]=new TGraph(10,coskstar[i],genyield[i]);
      grdet[i]=new TGraph(10,coskstar[i],mcyield[i]);
      gracc[i]=new TGraph(10,coskstar[i],acc[i]);
      grdata[i]=new TGraph(10,coskstar[i],datayield[i]);
      grnormyield[i]=new TGraph(10,coskstar[i],normyield[i]);
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
      grgen[i]->GetXaxis()->SetTitle("Cos^{*}(#theta_{K^{*+}})");
      grgen[i]->GetYaxis()->SetTitle("N_generator");
      grgen[i]->GetHistogram()->SetMinimum(0);
      grgen[i]->SetMarkerStyle(8);
      grgen[i]->SetMarkerSize(1);
      grgen[i]->SetMarkerColor(4);

      grgen[i]->Draw("AP*");
      // fitlow=coskstar[i][0];
 //    if(i<8){
//       fitmaxbin=10-2;
//     }
//     else{
//       //fitlow=coskstar[i][1];
//       fitmaxbin=10-1;
//     }
//     //    fitmaxbin=10-1;
//     fithigh=coskstar[i][fitmaxbin];
    Int_t fitminbin=cosbinmin[i]+1;
    // fitlow=coskstar[i][fitminbin];
    if(databeam[i]>3.0||(databeam[i]<2.9&&databeam[i]>2.7)) {
      if(databeam[i]<3.8&&databeam[i]>3.6){
	fitlow=0.3;
      }
      else fitlow=0;
    }
    else fitlow=coskstar[i][fitminbin];
    fithigh=1;
     cout<<fitlow<<" "<<fithigh<<" "<<10<<" "<<coskstar[i][fitmaxbin]<<endl;
     //getchar();
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
    grdet[i]->GetXaxis()->SetTitle("Cos^{*}(#theta_{K^{*+}})");
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
    gracc[i]->GetXaxis()->SetTitle("Cos^{*}(#theta_{K^{*+}})");
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
    grdata[i]->GetXaxis()->SetTitle("Cos^{*}(#theta_{K^{*+}})");
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
    grnormyield[i]->GetXaxis()->SetTitle("Cos^{*}(#theta_{K^{*+}})");
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
    grc[i]->GetXaxis()->SetTitle("Cos^{*}(#theta_{K^{*+}})");
   grc[i]->GetYaxis()->SetTitle("d#sigma/dCos^{*}(#theta_{K^{*+}})");
    grc[i]->GetHistogram()->SetMinimum(0);
    grc[i]->SetMarkerStyle(8);
    grc[i]->SetMarkerSize(1);
    grc[i]->SetMarkerColor(4);

    grce[i]->Fit("expo","R", "SAME", fitlow, fithigh);
    fce[i] = grce[i]->GetFunction("expo");
    fitecros[i]=(fce[i]->Integral(-1,1));
    crosslope[i]=fce[i]->GetParameter(1);
    grce[i]->Draw("AP*");
    c3->Update();
    c3_6->Clear();
    //fitcros[i]=(fc[i]->Integral(-1,1));
    grc[i]->Fit("pol4","R", "SAME", -0.5, fithigh);
    fc[i] = grc[i]->GetFunction("pol4");
    fc[i]->SetLineColor(2);
    fce[i]->SetLineColor(4);
    //crosslope[i]=fc[i]->GetParameter(1);
    fitcros[i]=(fc[i]->Integral(-0.6,1));
    grc[i]->Draw("AP*");
    fce[i]->SetRange(-1,1);
    fce[i]->Draw("SAME");
    c3->Update();
    //getchar();
    slopedat<<databeam[i]<<" "<<-genslope[i]<<" "<<-crosslope[i]<<" "<<endl;
    //crosdat<<databeam[i]<<" "<<fitcros[i]<<" "<<totalcros[i]<<" "<<endl;
    Int_t maxbin;
    if(databeam[i]<3.3) maxbin=10;
    else maxbin=10;
    Int_t ii;
    for(ii=0;ii<maxbin;ii++){
      crosdat<<databeam[i]<<"\t\t\t"<<coskstar[i][ii]<<"\t\t"<<cros[i][ii]<<"\t"<<croserr[i][ii]<<"\t"<<endl;
    }
    totalcrosdat<<databeam[i]<<"\t"<<totalcros[i]<<"\t"<<fitecros[i]<<"\t"<<fitcros[i]<<"\t"<<totalcroserr[i]<<" "<<endl;
   
    // ps->NewPage();
    //cout<<"total cross section for "<<databeam[i]<<" is "<<totalcros[i]<<endl;
    //cout<<"total norm yield for "<<databeam[i]<<" is "<<totalnormyield[i]<<endl;
    //cout<<"flux for "<<databeam[i]<<" is "<<flux[i]<<endl;
    }
    slopedat.close();
    crosdat.close();
    totalcrosdat.close();
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
    TGraphErrors *grwcros=new TGraphErrors(bins, w, totalcros,werr,totalcroserr);
     TGraphErrors *grwfitcros=new TGraphErrors(bins, w, fitcros,werr,totalcroserr);
     //TGraphErrors *grtcros=new TGraphErrors(bins, databeam,tcros,databeamerr,tcroserr);
     TGraphErrors *groldcros=new TGraphErrors(7, oldbeam,oldcros,oldbeamerr,oldcroserr);
    char crostitle[30];
    sprintf(crostitle, "#sigma(E_{#gamma}) / (#mub)");
    grcros->SetTitle(crostitle);
    grwcros->SetTitle("#sigma(w) / (#mub)");
    grwfitcros->SetTitle("#sigma(w) / (#mub)");
    grcros->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
    grwcros->GetXaxis()->SetTitle("w (GeV)");
    grwfitcros->GetXaxis()->SetTitle("w (GeV)");
    
      grcros->GetYaxis()->SetLabelSize(0.035);
  
    grcros->GetHistogram()->SetMinimum(0);
    grcros->SetMarkerStyle(8);
    grcros->SetMarkerSize(1);
    grcros->SetMarkerColor(30);
 
    grfitcros->GetHistogram()->SetMinimum(0);
    grfitcros->SetMarkerStyle(8);
    grfitcros->SetMarkerSize(1);
    grfitcros->SetMarkerColor(2);

  //   grtcros->GetHistogram()->SetMinimum(0);
//     grtcros->SetMarkerStyle(8);
//     grtcros->SetMarkerSize(1);
//     grtcros->SetMarkerColor(4);
 
   groldcros->GetHistogram()->SetMinimum(0);
    groldcros->SetMarkerStyle(8);
    groldcros->SetMarkerSize(1);
    groldcros->SetMarkerColor(4);
    ps->NewPage();
    c3->Clear();
    c3->Divide(2,5);
    Int_t jj,jp;
    for(jj=0;jj<10;jj++){
      grw[jj]=new TGraphErrors(19,w,crosw[jj],werr,croswerr[jj]);
      grw[jj]->SetTitle(Form("Cos(#theta_{K^{*+}})=%2.1f",coskstar[0][jj]));
      grw[jj]->GetYaxis()->SetTitle("#sigma(#mub)");
      grw[jj]->GetXaxis()->SetTitle("w (GeV)");
      grw[jj]->GetYaxis()->SetTitleSize(0.08);
      grw[jj]->GetXaxis()->SetTitleSize(0.08);
      jp=jj+1;
      c3->cd(jp);
      grw[jj]->Draw("AP");
    }
    c3->Update();
    ps->NewPage();
    c3->Clear();
    c3->Divide(1,2);
    c3->cd(1);
    TMultiGraph *mgw=new TMultiGraph();
    mgw->SetTitle("#sigma(#mub) VS w(GeV), Cos(#theta_{K^{*+}})<0.2");
    Int_t style[10]={20,21,22,23,24,25,26,27,28,29};
    Int_t color[10]={1,1,1,2,3,4,5,6,7,8};
    for(jj=2;jj<6;jj++){
      grw[jj]->SetMarkerStyle(style[jj]);
      grw[jj]->SetMarkerColor(color[jj]);
      mgw->Add(grw[jj]);
    }   
    mgw->Draw("AP");
    c3->Update();
   c3->cd(2);
    TMultiGraph *mgw2=new TMultiGraph();
    mgw2->SetTitle("#sigma(#mub) VS w(GeV), Cos(#theta_{K^{*+}})>0.2");
     for(jj=6;jj<10;jj++){
      grw[jj]->SetMarkerStyle(style[jj]);
      grw[jj]->SetMarkerColor(color[jj]);
      mgw2->Add(grw[jj]);
    }   
    mgw2->Draw("AP");
    c3->Update();
    ps->NewPage();
 
    c3->Clear();
    c3->Divide(3,4);
    Int_t dspad, grcindex;
    for(dspad=1;dspad<=10;dspad++){
      c3->cd(dspad);
      grcindex=dspad-1;
      grc[grcindex]->Draw("AP");
      fce[grcindex]->Draw("SAME");
    }
    c3->Update();
    //c3->Print("dsdcos1.gif");
    ////c3->Print("dsdcos.gif");
    //c3->Print("dsdcos1.eps");
    ps->NewPage();
    c3->Clear();
    c3->Divide(3,4);
     for(dspad=1;dspad<=9;dspad++){
      c3->cd(dspad);
      grcindex=dspad+9;
      grc[grcindex]->Draw("AP");
      fce[grcindex]->Draw("SAME");
    }
     c3->Update();
     //c3->Print("dsdcros2.gif");
     //c3->Print("dsdcros2.eps");
      ps->NewPage();
    c3->Clear();
    grwcros->Draw("AP");
    c3->Update(); 
    c3->Clear();
    grwfitcros->Draw("AP");
    c3->Update(); 
    //compare with other results
    ps->NewPage();
    c3->Clear();
    TMultiGraph *mgc=new TMultiGraph();
    mgc->SetTitle("#sigma(#mub) VS E_{#gamma}(GeV)");
    mgc->Add(grcros);
    mgc->Add(grfitcros);
    mgc->Add(groldcros);
    TLegend *legc=new TLegend(0.4,0.8,0.9,0.9);
    legc->AddEntry(grcros, "#sigma_{total}=#Sigma#sigma_{i}(Cos^{*}(#theta_{K^{*+}}))", "p");
    legc->AddEntry(grfitcros, "#sigma_{total}=#int d#sigma/dCos^{*}(#theta_{K^{*+}})", "p");
    legc->AddEntry(groldcros, "K^{+}#Lambda cross section, ERBE", "p");
    mgc->Draw("AP");
    legc->Draw();
    c3->Update();
    //c3->Print("newXsec.gif");
    //c3->Print("newXsec.eps");
    ps->NewPage();
    c3->Clear();
    
    //plot the result of cos slope
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
    TLegend *legt=new TLegend(0.5,0.8,0.9,0.9);
    legt->AddEntry(inslope, "simulation Cos(#theta_{K^{+}}) slope", "p");
    legt->AddEntry(outslope, "d#sigma/dCos(#theta_{K^{+}})  slope", "p");
    mgt->Draw("AP");
    legt->Draw();
    c3->Update();
    //c3->Print("cosslope.gif");
    //c3->Print("cosslope.eps");
   //cout<<"updating c2"<<endl;
    ps->Close();
    
}
 

 //  //plot all crosection as a function o ft slope together
//   TMultiGraph *mg=new TMultiGraph();
//    mg->Add(gr1[0]);
//   mg->Add(gr1[1]);
//   mg->Add(gr1[2]);
//   mg->Add(gr1[3]);
//   //mg->GetYaxis()->SetTitle("Efficiency");
//   //mg->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
//   TLegend *leg=new TLegend(0.7,0.7,0.9,0.9);
//   for(i=0;i<4;i++){
//     //cout<<t[i]<<endl;
//     Double_t tslope=t[i];
//     char title[30];
//     sprintf(title, "tslope: %2.1f", tslope);
//     leg->AddEntry(gr1[i], title, "p");
//   }
//   c2->cd(3);
//   mg->Draw("AP");
//   leg->Draw();

//   //draw cros section
//  TMultiGraph *mgc=new TMultiGraph();
//    mgc->Add(grc[0]);
//   mgc->Add(grc[1]);
//   mgc->Add(grc[2]);
//   mgc->Add(grc[3]);
//   //mgc->GetYaxis()->SetTitle("Efficiency");
//   //mgc->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
//   TLegend *legc=new TLegend(0.7,0.7,0.9,0.9);
//   for(i=0;i<4;i++){
//     //cout<<t[i]<<endl;
//     Double_t tslope=t[i];
//     char title[30];
//     sprintf(title, "tslope: %2.1f", tslope);
//     legc->AddEntry(grc[i], title, "p");
//   }
//   c2->cd(4);
//   mgc->Draw("AP");
//   legc->Draw();

//}
