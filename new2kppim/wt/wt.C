void wtcaspi(Int_t max, Double_t beam){
   ifstream caspidat;
   char caspiin[30];
   sprintf(caspiin, "newwt.view");
   caspidat.open(caspiin, ios::in);
   Int_t k;
   Double_t mass[2000], cos[2000];
   Double_t m[50];
   Double_t p0[50], p1[50], p2[50], p3[50], p4[50], p5[50], p6[50];

   while(caspidat){
     for(k=0;k<max;k++){
       caspidat>>mass[k]>>cos[k];
       //cout<<mass[k]<<" "<<cos[k]<<endl;
     }
   }
   caspidat.close();
   Int_t i,j;
   for(i=0;i<50;i++){
     m[i]=1.455+i*0.01;
     p0[i]=0;
     p1[i]=0;
     p2[i]=0;
     p3[i]=0;
     p4[i]=0;
     p5[i]=0;
     Double_t dm;
     for(j=0;j<max;j++){
       //dm=fabs(mass[j]-m[i]);
       //cout<<mass[j]<<" "<<m[i]<<" "<<dm<<endl;
       //getchar();
       if(fabs(mass[j]-m[i])<0.005){
	 p0[i]=p0[i]+p0cos(-cos[j]);
	 p1[i]=p1[i]+p1cos(-cos[j]);
	 p2[i]=p2[i]+p2cos(-cos[j]);
	 p3[i]=p3[i]+p3cos(-cos[j]);
	 p4[i]=p4[i]+p4cos(-cos[j]);
	 p5[i]=p5[i]+p5cos(-cos[j]);
       }
     }
     cout<<p0[i]<<endl;
   }
   TCanvas *c1=new TCanvas("c1", "", 20,20,600,600);
    TGraph *gr0=new TGraph(50,m,p0);
    TGraph *gr1=new TGraph(50,m,p1);
    TGraph *gr2=new TGraph(50,m,p2);
    TGraph *gr3=new TGraph(50,m,p3);
    TGraph *gr4=new TGraph(50,m,p4);
    TGraph *gr5=new TGraph(50,m,p5);
    gr0->SetMarkerStyle(8);
    gr0->SetMarkerSize(1);
    gr0->SetMarkerColor(4);
    gr1->SetMarkerStyle(8);
    gr1->SetMarkerSize(1);
    gr1->SetMarkerColor(4);
    gr2->SetMarkerStyle(8);
    gr2->SetMarkerSize(1);
    gr2->SetMarkerColor(4);
    gr3->SetMarkerStyle(8);
    gr3->SetMarkerSize(1);
    gr3->SetMarkerColor(4);
    gr4->SetMarkerStyle(8);
    gr4->SetMarkerSize(1);
    gr4->SetMarkerColor(4);
    gr5->SetMarkerStyle(8);
    gr5->SetMarkerSize(1);
    gr5->SetMarkerColor(4);
  c1->Divide(2,3);
   c1->cd(1);
   gr0->Draw();
   c1->cd(2);
   gr1->Draw("AP");
   c1->cd(3);
   gr2->Draw("AP");
    c1->cd(4);
   gr3->Draw("AP");
   c1->cd(5);
   gr4->Draw("AP");
    c1->cd(6);
   gr5->Draw("AP");
  
}

Double_t p0cos(Double_t x){
  Double_t x0;
  x0=1;
  return x0;

}

Double_t p1cos(Double_t x){
  return x;

}

Double_t p2cos(Double_t x){
  return 0.5*(3*x*x-1);

}

Double_t p3cos(Double_t x){
  return 0.5*(5*x*x-3*x);

}


Double_t p4cos(Double_t x){
  return (35*x**4-30*x*x+3)/8;

}


Double_t p5cos(Double_t x){
  return (63*x**5-70*x**3+15*x)/8;

}


