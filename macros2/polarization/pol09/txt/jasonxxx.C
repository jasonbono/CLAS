void jasonxxx(){
Double_t x[3]={3.65,4.35,5.1};
Double_t xe[3]={0,0,0};
Double_t xz[3]={3.675,4.375,5.125};
Double_t p[3]={0.072,-0.129,-0.109};
Double_t cz[3]={-0.482,-0.827,-3.621};
Double_t pe[3]={0.095,0.087,0.121};
Double_t cze[3]={0.633,0.559,4.026};
TGraphErrors *gp=new TGraphErrors(3,x,p,xe,pe);
TGraphErrors *gz=new TGraphErrors(2,xz,cz,xe,cze);
gp->GetHistogram()->GetXaxis()->SetRange(3.6,5.5);
gp->GetHistogram()->GetYaxis()->SetRange(-2,2);
gz->GetHistogram()->GetXaxis()->SetRange(3.6,5.5);
gz->GetHistogram()->GetYaxis()->SetRange(-2,2);

gz->GetHistogram()->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
gp->GetHistogram()->GetXaxis()->SetTitle("E_{#gamma} (GeV)");

gp->SetMarkerStyle(8);
gp->SetMarkerSize(2.5);
gp->SetMarkerColor(4);
gp->SetLineColor(4);
gz->SetMarkerStyle(21);
gz->SetMarkerSize(2.5);
gz->SetMarkerColor(6);
gz->SetLineColor(6);



gp->GetHistogram()->GetXaxis()->SetTitleSize(0.06);
gz->GetHistogram()->GetXaxis()->SetTitleSize(0.06);

TMultiGraph *mg=new TMultiGraph();

mg->Add(gp);
mg->Add(gz);
//mg->GetHistogram()->SetXTitle("E_{#gamma} (GeV)");
TCanvas *c1=new TCanvas("c1", "", 20,20,1000,600);
gPad->SetMargin(0.15,0.15,0.15,0.15);
	mg->Draw("AP");
mg->GetHistogram()->SetXTitle("E_{#gamma} (GeV)");
mg->GetXaxis()->CenterTitle();
mg->GetHistogram()->GetXaxis()->SetTitleSize(0.06);

mg->GetHistogram()->SetYTitle("Polarization");
mg->GetYaxis()->CenterTitle();
mg->GetHistogram()->GetYaxis()->SetTitleSize(0.06);

mg->GetHistogram()->GetYaxis()->SetRangeUser(-2,2);
TLegend* leg = new TLegend(.7, .7, .9, .9); //top right
   //TLegend* leg = new TLegend(.4, .6, .7, .9); // middle
   //TLegend* leg = new TLegend(.2, .7, .5, .9);//top left
       
   leg->SetFillStyle(0);
   leg->SetTextFont(132);

leg->AddEntry(gp, "P", "p");
leg->AddEntry(gz, "C_{z}", "p");

leg->Draw("SAME");
}