void wtcask(Int_t max, Double_t bmean){
   ifstream caskdat;
   char caskin[30];
   sprintf(caskin, "kkwt.view");
   caskdat.open(caskin, ios::in);
   Int_t k;
   Double_t b[2000], mass[2000], cos[2000], mass2[2000], cos2[2000];
   Double_t m[50];
   Double_t p0_1[50],p1_1[50],p2_1[50], p3_1[50],p4_1[50],p5_1[50], p6_1[50];
   Double_t p0_2[50],p1_2[50],p2_2[50], p3_2[50],p4_2[50],p5_2[50], p6_2[50];
   Double_t p0_12[50],p1_12[50],p2_12[50], p3_12[50],p4_12[50],p5_12[50], p6_12[50];
   while(caskdat){
     for(k=0;k<max;k++){
       caskdat>>b[k]>>mass[k]>>mass2[k]>>cos[k]>>cos2[k];
       //cout<<mass[k]<<" "<<cos[k]<<endl;
     }
   }
   caskdat.close();
   Int_t i,j;
   for(i=0;i<50;i++){
     m[i]=1.815+i*0.01;
     p0_1[i]=0;
     p1_1[i]=0;
     p2_1[i]=0;
     p3_1[i]=0;
     p4_1[i]=0;
     p5_1[i]=0;
     Double_t dm;
     for(j=0;j<max;j++){
       //dm=fabs(mass[j]-m_1[i]);
       //cout<<mass[j]<<" "<<m_1[i]<<" "<<dm<<endl;
       //getchar();
       if(fabs(mass[j]-m[i])<0.005){
	 p0_1[i]=p0_1[i]+p0cos(-cos[j]);
	 p1_1[i]=p1_1[i]+p1cos(-cos[j]);
	 p2_1[i]=p2_1[i]+p2cos(-cos[j]);
	 p3_1[i]=p3_1[i]+p3cos(-cos[j]);
	 p4_1[i]=p4_1[i]+p4cos(-cos[j]);
	 p5_1[i]=p5_1[i]+p5cos(-cos[j]);
	 p6_1[i]=p6_1[i]+p6cos(-cos[j]);
       }
       if(fabs(mass2[j]-m[i])<0.005&&fabs(b[j]-bmean)<0.5){
	 p0_2[i]=p0_2[i]+p0cos(-cos2[j]);
	 p1_2[i]=p1_2[i]+p1cos(-cos2[j]);
	 p2_2[i]=p2_2[i]+p2cos(-cos2[j]);
	 p3_2[i]=p3_2[i]+p3cos(-cos2[j]);
	 p4_2[i]=p4_2[i]+p4cos(-cos2[j]);
	 p5_2[i]=p5_2[i]+p5cos(-cos2[j]);
	 p6_2[i]=p6_2[i]+p6cos(-cos2[j]);
       }
     }
     p0_12[i]=p0_1[i]+p0_2[i];
     p1_12[i]=p1_1[i]+p1_2[i];
     p2_12[i]=p2_1[i]+p2_2[i];
     p3_12[i]=p3_1[i]+p3_2[i];
     p4_12[i]=p4_1[i]+p4_2[i];
     p5_12[i]=p5_1[i]+p5_2[i];
     p6_12[i]=p6_1[i]+p6_2[i];
     //cout<<p0[i]<<endl;
   }
   TCanvas *c1=new TCanvas("c1", "", 20,20,600,600);
 //   TGraph *gr_1[6], *gr_2[6], *gr_12[6];
//    for(i=0;i<6;i++){
//      gr_1[i]=new TGraph(50,m,Form("p%d_1", i));
//      gr_2[i]=new TGraph(50,m,Form("p%d_2", i));
//      gr_12[i]=new TGraph(50,m,Form("p%d_12", i));
    
//    }
    TGraph *gr0=new TGraph(50,m,p0_1);
    TGraph *gr1=new TGraph(50,m,p1_1);
    TGraph *gr2=new TGraph(50,m,p2_1);
    TGraph *gr3=new TGraph(50,m,p3_1);
    TGraph *gr4=new TGraph(50,m,p4_1);
    TGraph *gr5=new TGraph(50,m,p5_1);
    TGraph *gr6=new TGraph(50,m,p6_1);
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
    gr6->SetMarkerStyle(8);
    gr6->SetMarkerSize(1);
    gr6->SetMarkerColor(4);
  c1->Divide(2,4);
  Int_t ii;
 //  for(i=0;i++;i<7){
//     ii=i+1;
//     c1->cd(ii);
//     gr_1[i]->Draw("AP");
//   }
   c1->cd(1);
   gr0->Draw("AP");
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
    c1->cd(7);
   gr6->Draw("AP");
  
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

Double_t p6cos(Double_t x){
  return (231*x**6-315*x**4+105*x*x-5)/16;

}


