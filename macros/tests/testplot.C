// need to learn how to set range ingraph independantly of the range of first vector

void testplot(){
 
  TCanvas *c0=new TCanvas("c0","",1200,800);
//c0->cd(0);
 Float_t x[3];
 Float_t y[3];
Float_t y2[3];
  x[0]=1;
  x[1]=2;
  x[2]=3;
  y[0]=9;
  y[1]=8;
  y[2]=7;
  y2[0]=7;
  y2[1]=8;
  y2[2]=9;
  TGraph *gb0 = new TGraph (3,x,y);
  
 gb0->SetMarkerStyle(21);
 gb0->SetMarkerColor(1);
 gb0->Draw("AP");
gb0->SetLineColor(4);
 TGraph *gb1 = new TGraph (3,x,y2);
 gb1->SetMarkerStyle(22);
 gb1->SetMarkerColor(2);
gb1->SetLineColor(5);
gb1->Draw("P");


}


//gr3->SetMarkerStyle(21);
//gr3->Draw("APL");
