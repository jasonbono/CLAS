//from lei


//to use this macro type in root

//.L fitGAUS.C
//fitGAUS(histogram_name, try, lowbound, highbound, p0, p1, p2, mean, width) 
// JB. also include bin width after "width", he forgot to put that!!!!
// the macro will draw the result
//The integer number "try" enables root to draw the fitted function (background
//and signal) without destroying the old ones.Each time when calling fitGAUS, 
//simply give a different "try" number.
//when a non-zero p2 was given, a 2nd polynomial function will be used as the
//background function
//Otherwise, when p2=0 is given, a 1st order polynomial will be used instead

// Quadratic background function


#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"

Double_t p2background(Double_t *x, Double_t *par) {
  //return par[0] + par[1]*x[0] + par[2]*x[0]*x[0]+ par[3]*x[0]*x[0]*x[0];
  return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
}



Double_t GaussianPeak(Double_t *x, Double_t *par)
// The signal function: a gaussian
{
   Double_t arg = 0;
   if (par[2]) arg = (x[0] - par[1])/par[2];
   Double_t sig = par[0]*TMath::Exp(-0.5*arg*arg);
   return sig;
}


// Sum of background and peak function
Double_t fitGAUSFunction(Double_t *x, Double_t *par) {
  return p2background(x,par) + GaussianPeak(x,&par[3]);
}


void fitGAUS(TH1F *histo, Int_t try, Double_t low, Double_t high, Double_t term0, Double_t term1,Double_t term2, Double_t mean, Double_t width, Double_t factor)
{
  //TText *sum[100];
  // create a TF1 with the range from tl to th and 6 parameters
  TF1 *fitFcn = new TF1("fitFcn",fitGAUSFunction, low, high, 6);

  // first try without starting values for the parameters
  // This defaults to 1 for each param.
  //histo->Fit("fitFcn", "E");

  // second try: set start values for some parameters
  fitFcn->SetLineWidth(1); 
  fitFcn->SetLineColor(2); 
  //  fitFcn->SetParameter(0, term0); // pol c0
  //fitFcn->SetParameter(1, term1);   // pol c1
  if(term0!=0) {fitFcn->SetParameter(0, term0); }// pol c2
  else {fitFcn->FixParameter(0,0);}
  if(term1!=0) {fitFcn->SetParameter(1, term1); }// pol c2
  else {fitFcn->FixParameter(1,0);}
  if(term2!=0) {fitFcn->SetParameter(2, term2); }// pol c2
  else {fitFcn->FixParameter(2,0);}
//fitFcn->SetParameter(3, height); // hight

  fitFcn->SetParameter(4, mean); // width
  fitFcn->SetParameter(5, width);   // peak
  fitFcn->SetParLimits(5, 0,10000);   // peak
  histo->Fit("fitFcn","EV","",low,high);
  histo->Draw("E");
  // improve the picture:
  TF1 *backFcn = new TF1(Form("backFcn_%i", try), p2background,low,high,3);
   TF1 *signalFcn = new TF1(Form("signalFcn_%i", try), GaussianPeak,low,high,3);
  // signalFcn->SetLineColor(2);
  // signalFcn->SetLineWidth(1);
  
  Double_t par[6];

  // writes the fit results into the par array
   fitFcn->GetParameters(par);

   backFcn->SetParameters(par);
    backFcn->SetLineStyle(2);
 backFcn->SetLineColor(4);
   backFcn->SetLineWidth(1);
  
   backFcn->Draw("same");

   signalFcn->SetParameters(&par[3]);
    signalFcn->SetLineStyle(2);
 signalFcn->SetLineColor(3);
   signalFcn->SetLineWidth(1);
  
   //signalFcn->Draw("same");
   Double_t Intg = signalFcn->Integral(par[4]-factor*par[5],par[4]+factor*par[5]);
   Double_t Intb = backFcn->Integral(par[4]-factor*par[5],par[4]+factor*par[5]);
   cout<<"Integral of function is "<<Intg<<" "<<Intb<<endl;
   //cout<<"binwidth is "<<binw<<endl;
   Double_t binw = histo->GetBinWidth(1);
   Int_t yield = Intg/binw;
   //Double_t ratio = Intg/Intb;
   
   
   cout<<"Integral of histogram is "<<yield<<endl;
   TAxis *x=histo->GetXaxis();
   TAxis *y=histo->GetYaxis();
 
   Double_t startx=x->GetXmin()+0.55*(x->GetXmax()-x->GetXmin());
  Double_t starty=0.65*histo->GetMaximum();
  Double_t starty1=0.55*histo->GetMaximum();
  Double_t starty0=0.75*histo->GetMaximum();
  Double_t starty2=0.95*histo->GetMaximum();
  Double_t starty3=0.85*histo->GetMaximum();
  // cout<<startx<<" "<<starty<<endl;
  //TLatex *sum=new TLatex(startx, starty,Form("Ye_t starty0=0.85*histo->GetMaximum();
   TLatex *sum=new TLatex(startx, starty,Form("Yield: %i",yield));
   //TLatex *sum1=new TLatex(startx, starty1,Form("S/B ratio: %6.2f",ratio));
   TLatex *sum0=new TLatex(startx, starty0,Form("Range: #pm %2.1f #sigma",factor));
   TLatex *sum2=new TLatex(startx, starty2,Form("Mean:%5.4f",par[4]));
   TLatex *sum3=new TLatex(startx, starty3,Form("#sigma:%5.4f",par[5]));
   sum->SetTextSize(0.05);
   sum->SetTextColor(2);
   sum->Draw("same");
   //sum1->SetTextSize(0.05);
   //sum1->SetTextColor(2);
   //sum1->Draw("same");
   sum0->SetTextSize(0.05);
   sum0->SetTextColor(2);
   sum0->Draw("same");
   sum2->SetTextSize(0.05);
   sum2->SetTextColor(4);
   sum2->Draw("same");
   sum3->SetTextSize(0.05);
   sum3->SetTextColor(4);
   sum3->Draw("same");
}
