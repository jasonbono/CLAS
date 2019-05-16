/*

 
September 2016: Made this form gausfit.C.  The only difference is that the LaTeX output is not done for N and S/B
 
 
 
Name: gausfit.C
Author: Jason Bono
Date: October 22 2012: 
Notes: Made this from myfitGAUS5.C.  added the width limit of the gaussian.  The 

Usage: call the function gausfit(histo, Int_t tryno, low, high, term0, term1, term2, start-mean, start-width,factor, 
Double_t & myBackground, Double_t & myYield, Double_t & myRms, Double_t & myMean, Int_t & myYieldErr)





October 6 2012: made it so the error on the yield can be passed throguh to a script calling it.  for passing a variable like this just decare
a Int_t yieldErr; then when calling do somthing like myfit2GAUS(#,#,#,#,#,#,#,yieldErr).

THE ERRORS ARE Int_t objects but everything else are Double_t objects!!!!!!!!!!!!!

jason 13:  made this version (4) and added the mean of the fit. ie the posistion of the gausian.  this was also needed to define proper 
cuts for side band subtraction.


jan 13 2012: this is now called myfit2GAUS3. made it so a third variable could be passed through to an external macro. this variable is 
the sigma of this fit. the sigma will be used in nxyzangle.C for example to define the sideband cuts.

 i also changed the name of the funcntion from FITGAUS to FITGAUS3 to distinguish when calling multiple versions of this macro.


jan 9 2012: this came from myfit2gaus.C  i made this so that i could pass the fitting info to a
macro which runs this script.  changed the amount of fit parameters (added two) in fitGAUS function. i added the last two double type
called myBackground and myErrorBackground.  i then initialize theese two when i call the routine from 
"resonaceMMkpkppim.C"  i initalize them with the value zero but then a new value fills them from the fit.
this last part is done just before the "return yield" line in this script.

also changed "try" to "tryno" since try is reserved for somthing else in C.

nov 20 2011: from leis fit2GAUS.C. look for //jb X to find the places that affect the style
and //jb to find all other edits and comments

it looks like only commands within -----------number1---------------- are active.


 */


//to use this macro type in root

//.L fitGAUS.C
//fitGAUS(histogram_name, try, lowbound, highbound, p0, p1, p2, mean, width)
// the macro will draw the result
//The integer number "try" enables root to draw the fitted function (background
//and signal) without destroying the old ones.Each time when calling fitGAUS, 
//simply give a different "try" number.
//when a non-zero p2 was given, a 2nd polynomial function will be used as the
//background function
//Otherwise, when p2=0 is given, a 1st order polynomial will be used instead


//-----------------------------------------BW----------------------------------
// Quadratic background function
Double_t background(Double_t *x, Double_t *par) {
  //return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0];
  //return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
	return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0] + par[4]*x[0]*x[0]*x[0]*x[0];
}



Double_t tbackground(Double_t *x, Double_t *par) {
  return par[0]*(x[0]-par[2])*TMath::Exp(par[1]*(x[0] - par[2]));
}

//--------------------------------possible signals---------------------------------------
Double_t lorentzianPeak(Double_t *x, Double_t *par) {
  return (0.5*par[0]*par[2]/TMath::Pi()) /
          TMath::Max( 1.e-10,
                     (x[0]-par[1])*(x[0]-par[1]) + .25*par[2]*par[2]
                    );
}

Double_t lorentzianPeak2(Double_t *x, Double_t *par) {
  return (0.5*par[0]*par[2]/TMath::Pi()) /
          TMath::Max( 1.e-10,
                     (x[0]-par[1])*(x[0]-par[1]) + .25*par[2]*par[2]
                    );
}
//--------------------------------GAUSSIAN SIGNAL---------------------------------
Double_t GaussianPeak(Double_t *x, Double_t *par)
{
   Double_t arg = 0;
   if (par[2]) arg = (x[0] - par[1])/par[2];
   Double_t sig = par[0]*TMath::Exp(-0.5*arg*arg);
   return sig;
}

Double_t GaussianPeak2(Double_t *x, Double_t *par)
{
   Double_t arg = 0;
   if (par[2]) arg = (x[0] - par[1])/par[2];
   Double_t sig = par[0]*TMath::Exp(-0.5*arg*arg);
   return sig;
}



// -----------------------------Sum of background and peak function---------------------
Double_t fitFunction(Double_t *x, Double_t *par) {
  return background(x,par) + GaussianPeak(x,&par[5]); //jb raised index
}

Double_t fitFunctionBW(Double_t *x, Double_t *par) {
  return background(x,par) + lorentzianPeak(x,&par[3]);
}

Double_t fitFunctionBW2p3(Double_t *x, Double_t *par) {
  return background(x,par) + lorentzianPeak(x,&par[4])+ lorentzianPeak2(x,&par[7]);
}

Double_t fitFunctionGAUS2p2(Double_t *x, Double_t *par) {
  return background(x,par) + GaussianPeak(x,&par[3])+ GaussianPeak2(x,&par[6]);
}

Double_t fitFunctionBW2tb(Double_t *x, Double_t *par) {
  return tbackground(x,par) + lorentzianPeak(x,&par[3])+ lorentzianPeak2(x,&par[6]);
}

Double_t fitFunctionBW2(Double_t *x, Double_t *par) {
  return GaussianPeak(x,par) + lorentzianPeak(x,&par[3])+ lorentzianPeak2(x,&par[6]);
}



//------------------------------------number1-------------------------------------------

// CALL THIS
Double_t  gausfit(TH1F *histo, Int_t tryno, Double_t low, Double_t high, Double_t term0, 
  Double_t term1, Double_t term2, Double_t term3, Double_t term4, Double_t mean, Double_t width, Double_t widthFloat, Double_t factor, 
  Double_t & myBackground, Double_t & myYield, Double_t & myRms, Double_t & myMean, Int_t & myYieldErr) //jb added term3 + 4
{
	
  // create a TF1 with the range from tl to th and 6 parameters
  TF1 *fitFcn = new TF1("fitFcn",fitFunction, low, high, 8); //jb raised amout of indexies

  // first try without starting values for the parameters
  // This defaults to 1 for each param.
  //histo->Fit("fitFcn", "E");

  // second try: set start values for some parameters

  fitFcn->SetParameter(0, term0); // pol c0
  fitFcn->SetParameter(1, term1);   // pol c1
  if(term2!=0) {fitFcn->SetParameter(2, term2); }// pol c2
  else {fitFcn->FixParameter(2,0);}
  fitFcn->SetParameter(3, term3); //jb set
   fitFcn->SetParameter(4, term4); 
  if(term1==0&&term2==0){
    fitFcn->SetParLimits(0,0,100000);
  }
//fitFcn->SetParameter(3, height); // hight
  //Double_t widthFloat =  0.004;
  Double_t widthLow = width - widthFloat;
  Double_t widthHigh = width + widthFloat;
  fitFcn->SetParameter(6, mean); //jb raised
  fitFcn->SetParameter(7, width);  //jb raised
  fitFcn->SetParLimits(7, widthLow, widthHigh);   //jb set range for the width
  fitFcn->SetLineWidth(1);   // peak
  
  fitFcn->SetLineColor(4);  //jb X added. this give the color of the peak

  histo->Fit("fitFcn","EV","",low,high);

  // improve the picture:
  TF1 *backFcn = new TF1(Form("backFcn_%i", tryno), background,low,high,5); //jb raised the amount of parameters
  backFcn->SetLineColor(4); //jb was 4: does nothing
  backFcn->SetLineWidth(1);
  TF1 *signalFcn = new TF1(Form("signalFcn_%i", tryno), GaussianPeak,low,high,3);
  // signalFcn->SetLineColor(2);  //jb uncommented this
  // signalFcn->SetLineWidth(5);
  histo->Draw("E");
  Double_t par[8]; //jb raised the dimention

  // writes the fit results into the par array
   fitFcn->GetParameters(par);

   backFcn->SetParameters(par);
   backFcn->SetLineStyle(2);
   backFcn->SetLineColor(2);  //jb X this is the bacround line color
   backFcn->SetLineWidth(1);
  
   backFcn->Draw("same"); // this is the backround shown in the plot

   signalFcn->SetParameters(&par[5]); //jb raised starting index
   signalFcn->SetLineStyle(2);  
   signalFcn->SetLineColor(4);
   signalFcn->SetLineWidth(2);
  
   //   signalFcn->Draw("same");  //jb X this gives a pure gaussian with out the bacround if uncommented
   Double_t Intg = signalFcn->Integral(par[6]-factor*par[7],par[6]+factor*par[7]); //raised indexies
   Double_t Intb = backFcn->Integral(par[6]-factor*par[7],par[6]+factor*par[7]);  //raised indexies
  // cout<<"Integral of function: (intg) "<<Intg<<" "<<" and (intb) "<<Intb<<endl;
   //cout<<"binwidth is "<<binw<<endl;
   Double_t binw = histo->GetBinWidth(1);
   Int_t yield = Intg/binw;
   Int_t yieldb = Intb/binw;
   Double_t ratio = Intg/Intb;
   Double_t yieldF = yield;  //jb made to  convert to double to ratio2 could be computed
   Double_t yieldbF = yieldb; //jb made to  convert to double to ratio2 could be computed
   Double_t ratio2 = yieldF/yieldbF;  //jb made as a check
   Double_t M1Err=fitFcn->GetParError(6); //jb raised 
   Double_t G1Err=fitFcn->GetParError(7); //jb raisd 
   // Int_t N1Err=(fitFcn->GetParError(3))*yield/par[3];
   Int_t N1Err=yield*sqrt(((fitFcn->GetParError(5))/par[5])**2+((fitFcn->GetParError(7))/par[7])**2);  //raised indexies
   
   
   
  // cout<<"Integral of histogram is (yield): "<<yield<<endl;   //jb this is the one: 
   // need to add another statement
  // cout<<" integral of background hist is (yieldb): "<<yieldb<<endl;  //jb nov 24 2011
 //  cout<<" signal to background is (ratio=intg/intb) "<<ratio<<endl;  //jb nov 24 2011
 //  cout<<" CHECK. signal to background is (ratio2=yield/yieldb) "<<ratio2<<endl;  //jb


//now i want to parse the number yieldb
   TAxis *x=histo->GetXaxis();
   TAxis *y=histo->GetYaxis();
 
   Double_t startx=x->GetXmin()+0.1*(x->GetXmax()-x->GetXmin());
  Double_t starty=0.65*histo->GetMaximum();
  Double_t starty1=0.55*histo->GetMaximum();
  Double_t starty0=0.75*histo->GetMaximum();
  Double_t starty2=0.95*histo->GetMaximum();
  Double_t starty3=0.85*histo->GetMaximum();
  
   TLatex *sum=new TLatex(startx, starty,Form("N: %i #pm %i",yield, N1Err));
   TLatex *sum1=new TLatex(startx, starty1,Form("S/B ratio: %6.2f",ratio));
   TLatex *sum0=new TLatex(startx, starty0,Form("Range: #pm %2.1f #sigma",factor));
   TLatex *sum2=new TLatex(startx, starty2,Form("M:%5.4f #pm %5.4f",par[6], M1Err));  //jb raised index
   TLatex *sum3=new TLatex(startx, starty3,Form("#sigma:%5.4f #pm %5.4f",par[7], G1Err)); //jb raised index
   sum->SetTextSize(0.06);
   sum->SetTextColor(4);  //jb X  this is the N: color
   //sum->Draw("same");
	sum1->SetTextSize(0.06); //jb jan11 2012
	sum1->SetTextColor(2); //jb jan11 2012
	//sum1->Draw("same");  //jb jan11 2012
   sum2->SetTextSize(0.06);
   sum2->SetTextColor(4);
   sum2->Draw("same");
   sum3->SetTextSize(0.06);
   sum3->SetTextColor(4);
   sum3->Draw("same");



  // store background and its error 
  myBackground = yieldb;
  myYield = yield;
  myRms = par[7];  //jb raised index
  myMean = par[6]; //jb raised index
  myYieldErr = N1Err;
  return yield;
 }


//------------------------------------------------------------------------------------------


//-------------------number2-------------------------------------------------------------


void fitBW(TH1F *histo, Int_t tryno, Double_t low, Double_t high, Double_t term0, Double_t term1,Double_t term2, Double_t mean, Double_t width, Double_t factor)
{
  //TText *sum[100];
  // create a TF1 with the range from tl to th and 6 parameters
  TF1 *fitFcn = new TF1("fitFcn",fitFunctionBW, low, high, 6);

  // first try without starting values for the parameters
  // This defaults to 1 for each param.
  //histo->Fit("fitFcn", "E");

  // second try: set start values for some parameters

  fitFcn->SetParameter(0, term0); // pol c0
  fitFcn->SetParameter(1, term1);   // pol c1
  if(term2!=0) {fitFcn->SetParameter(2, term2); }// pol c2
  else {fitFcn->FixParameter(2,0);}
  //fitFcn->SetParameter(3, 1);

  fitFcn->SetParameter(4, mean); // width
  fitFcn->SetParameter(5, width);   // peak
  fitFcn->SetParLimits(5, 0,10000);   // peak
  fitFcn->SetLineWidth(2);   // peak
  histo->Fit("fitFcn","EV","",low,high);

  // improve the picture:
  TF1 *backFcn = new TF1(Form("backFcn_%i", tryno), background,low,high,3);
  backFcn->SetLineColor(4);
  backFcn->SetLineWidth(2);
  TF1 *signalFcn = new TF1(Form("signalFcn_%i", tryno), lorentzianPeak,low,high,3);
  // signalFcn->SetLineColor(2);
  // signalFcn->SetLineWidth(5);
  
  Double_t par[6];

  // writes the fit results into the par array
   fitFcn->GetParameters(par);

   backFcn->SetParameters(par);
    backFcn->SetLineStyle(2);
 backFcn->SetLineColor(2);
   backFcn->SetLineWidth(2);
  
     backFcn->Draw("same");

   signalFcn->SetParameters(&par[3]);
    signalFcn->SetLineStyle(2);
 signalFcn->SetLineColor(4);
 signalFcn->SetLineWidth(1);  //jb affects nothing
 
 
 signalFcn->Draw("same");  //jb affects nothing
   Double_t Intg = signalFcn->Integral(par[4]-factor*par[5],par[4]+factor*par[5]);
   Double_t Intb = backFcn->Integral(par[4]-factor*par[5],par[4]+factor*par[5]);
//   cout<<"Integral of function is "<<Intg<<" "<<Intb<<endl;
   //cout<<"binwidth is "<<binw<<endl;
   Double_t binw = histo->GetBinWidth(1);
   Int_t yield = Intg/binw;
   Double_t ratio = Intg/Intb;
   
//   cout<<"Integral of histogram is "<<yield<<endl;
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
  TLatex *sum=new TLatex(startx, starty,Form("N: %i",yield));
   TLatex *sum1=new TLatex(startx, starty1,Form("S/B ratio: %6.2f",ratio));
   TLatex *sum0=new TLatex(startx, starty0,Form("Range: #pm %2.1f #sigma",factor));
   TLatex *sum2=new TLatex(startx, starty2,Form("Mean:%5.4f",par[4]));
   TLatex *sum3=new TLatex(startx, starty3,Form("#Gamma:%5.4f",par[5]));
   sum->SetTextSize(0.05);
   sum->SetTextColor(2);
   sum->Draw("same");  //jb affects nothing
   sum1->SetTextSize(0.05);
   sum1->SetTextColor(2);
   sum1->Draw("same"); //jb affects nothing
   sum0->SetTextSize(0.05);
   sum0->SetTextColor(2);
   sum0->Draw("same"); //jb affects nothing
   sum2->SetTextSize(0.05);
   sum2->SetTextColor(4);
   sum2->Draw("same"); //jb affects nothing
   sum3->SetTextSize(0.05);
   sum3->SetTextColor(4);
   sum3->Draw("same");
 }

//------------------------------------------------------------------------------------------


//---------------------------------------number3-----------------------------------------

void fitBW2(TH1F *histo, Int_t tryno, Double_t low, Double_t high, Double_t term0, Double_t term1,Double_t term2, Double_t mean, Double_t width, Double_t mean2, Double_t width2, Double_t factor)
{
  //TText *sum[100];
  // create a TF1 with the range from tl to th and 6 parameters
  TF1 *fitFcn = new TF1("fitFcn",fitFunctionBW2tb, low, high, 9);

  // first try without starting values for the parameters
  // This defaults to 1 for each param.
  //histo->Fit("fitFcn", "E");

  // second try: set start values for some parameters

  if(term0!=0) {
    fitFcn->SetParameter(0, term0);
    fitFcn->SetParLimits(0, 0,100000);
  } // pol c0
  else {fitFcn->FixParameter(0,0);}
  if(term1!=0) {
    fitFcn->SetParameter(1, term1);
    //fitFcn->SetParLimits(1, term1-0.003, term1+0.003);
   
  } // pol c0
  else {fitFcn->FixParameter(1,0);}
   if(term2!=0) {
     fitFcn->SetParameter(2, term2); 
     //fitFcn->SetParLimits(2, term2, term2*2);
   
   }// pol c2
  else {fitFcn->FixParameter(2,0);}
//fitFcn->SetParameter(3, height); // hight
     fitFcn->SetParLimits(3, 0,100000);
   fitFcn->SetParameter(4, mean); // width
  fitFcn->SetParameter(5, width);   // peak
  //fitFcn->SetParLimits(5, width-0.001, width+0.001);   // peak
  fitFcn->SetParLimits(6, 0,100000);
  fitFcn->SetParameter(7, mean2); // width
  fitFcn->SetParameter(8, width2);   // peak
  //fitFcn->SetParLimits(8, width2-0.005, width2); 
  fitFcn->SetLineWidth(2);   // peak
  histo->Fit("fitFcn","EV","",low,high);

  // improve the picture:
  TF1 *backFcn = new TF1(Form("backFcn_%i", tryno), tbackground,low,high,3);
  backFcn->SetLineColor(4);
  backFcn->SetLineWidth(2);
  TF1 *signalFcn = new TF1(Form("signalFcn_%i", tryno), lorentzianPeak,low,high,3);
  TF1 *signalFcn2 = new TF1(Form("signalFcn2_%i", tryno), lorentzianPeak2,low,high,3);
  // signalFcn->SetLineColor(2);
  // signalFcn->SetLineWidth(5);
  
  Double_t par[9];

  // writes the fit results into the par array
   fitFcn->GetParameters(par);
   histo->Draw("E");
   Double_t xsq = fitFcn->GetChisquare();
   Double_t ndf = fitFcn->GetNDF();
   backFcn->SetParameters(&par[0]);
    backFcn->SetLineStyle(2);
    backFcn->SetLineColor(2);  //jb affects nothing
   backFcn->SetLineWidth(1);
  
    backFcn->Draw("same");  //jb affects nothing

   signalFcn->SetParameters(&par[3]);
    signalFcn->SetLineStyle(2);
 signalFcn->SetLineColor(4);
   signalFcn->SetLineWidth(1);
  
    signalFcn->Draw("same"); //jb affects nothing


  signalFcn2->SetParameters(&par[6]);
  signalFcn2->SetLineStyle(2);
  signalFcn2->SetLineColor(4);  //jb does nothing
   signalFcn2->SetLineWidth(1);
  
    signalFcn2->Draw("same");   //jb affects nothing
   Double_t Intg = signalFcn->Integral(par[4]-factor*par[5],par[4]+factor*par[5]);
 Double_t Intg2 = signalFcn2->Integral(par[7]-factor*par[8],par[7]+factor*par[8]);
   Double_t Intb = backFcn->Integral(par[4]-factor*par[5],par[4]+factor*par[5]);
//   cout<<"Integral of function is "<<Intg<<" "<<Intb<<endl;
   //cout<<"binwidth is "<<binw<<endl;
   Double_t binw = histo->GetBinWidth(1);
   Int_t yield = Intg/binw;
   Int_t yield2 = Intg2/binw;
   //Double_t ratio = Intg/Intb;
   
   
 //  cout<<"Integral of histogram is "<<yield<<endl;
   TAxis *x=histo->GetXaxis();
   TAxis *y=histo->GetYaxis();
 
   Double_t startx=x->GetXmin()+0.65*(x->GetXmax()-x->GetXmin());
  Double_t starty=0.7*histo->GetMaximum();
  Double_t starty1=0.6*histo->GetMaximum();
  Double_t starty30=0.5*histo->GetMaximum();
  Double_t starty0=0.4*histo->GetMaximum();
  Double_t starty2=1.0*histo->GetMaximum();
  Double_t starty3=0.9*histo->GetMaximum();
  Double_t starty10=0.8*histo->GetMaximum();
  // cout<<startx<<" "<<starty<<endl;
  //TLatex *sum=new TLatex(startx, starty,Form("Ye_t starty0=0.85*histo->GetMaximum();
   TLatex *sum=new TLatex(startx, starty,Form("Mean2:%5.4f",par[7]));
   TLatex *sum1=new TLatex(startx, starty1,Form("#Gamma2: %5.4f",par[8]));
   TLatex *sum10=new TLatex(startx, starty10,Form("Yield: %i",yield));
    TLatex *sum2=new TLatex(startx, starty2,Form("Mean:%5.4f",par[4]));
   TLatex *sum3=new TLatex(startx, starty3,Form("#Gamma:%5.4f",par[5]));
   TLatex *sum30=new TLatex(startx, starty30,Form("Yield2: %i",yield2));
   TLatex *sum4=new TLatex(startx, starty0,Form("#chi^{2}/Ndf: %5.1f/%5.1f",xsq, ndf));
   sum->SetTextSize(0.05);
   sum->SetTextColor(2);  //jb affects nothing
   sum->Draw("same");
   sum1->SetTextSize(0.05);
   sum1->SetTextColor(2);
   sum1->Draw("same");  //jb affects nothing
   sum10->SetTextSize(0.05);
   sum10->SetTextColor(2);
   sum10->Draw("same");
    sum2->SetTextSize(0.05);
   sum2->SetTextColor(4);
   sum2->Draw("same");
   sum3->SetTextSize(0.05);
   sum3->SetTextColor(4);
   sum3->Draw("same");
   sum30->SetTextSize(0.05);
   sum30->SetTextColor(4);
   sum30->Draw("same");
  sum4->SetTextSize(0.05);
   sum4->SetTextColor(4);
   sum4->Draw("same");
 }

//-------------------------------------------------------------------------------------

//-----------------------------------number4---------------------------------------------

void fitGAUS2(TH1F *histo, Int_t tryno, Double_t low, Double_t high, Double_t term0, Double_t term1,Double_t term2, Double_t mean, Double_t width, Double_t mean2, Double_t width2, Double_t factor)
{
  //TText *sum[100];
  // create a TF1 with the range from tl to th and 6 parameters
  TF1 *fitFcn = new TF1("fitFcn",fitFunctionGAUS2p2, low, high, 9);

  // first try without starting values for the parameters
  // This defaults to 1 for each param.
  //histo->Fit("fitFcn", "E");

  // second try: set start values for some parameters

  if(term0!=0) {
    fitFcn->SetParameter(0, term0);
    //fitFcn->SetParLimits(0, 0,100000);
  } // pol c0
  else {fitFcn->FixParameter(0,0);}
  if(term1!=0) {
    fitFcn->SetParameter(1, term1);
    //fitFcn->SetParLimits(1, term1-0.003, term1+0.003);
   
  } // pol c0
  else {fitFcn->FixParameter(1,0);}
   if(term2!=0) {
     fitFcn->SetParameter(2, term2); 
     //fitFcn->SetParLimits(2, term2, term2*2);
   
   }// pol c2
  else {fitFcn->FixParameter(2,0);}
//fitFcn->SetParameter(3, height); // hight
     fitFcn->SetParLimits(3, 0,100000);
   fitFcn->SetParameter(4, mean); // width
  fitFcn->SetParLimits(4, mean-0.005,mean+0.005);
  fitFcn->SetParameter(5, width);   // peak
  fitFcn->SetParLimits(5, width-0.005,width+0.005);
   fitFcn->SetParLimits(6, 0,100000);
  fitFcn->SetParameter(7, mean2); // width
  fitFcn->SetParLimits(7, mean2-0.005,mean2+0.005);
  fitFcn->SetParameter(8, width2);   // peak
  //fitFcn->SetParLimits(8, 0,0.02);
  fitFcn->SetLineWidth(2);   // peak
  fitFcn->SetLineColor(4);   // peak   //jb
  histo->Fit("fitFcn","EV","",low,high);
  histo->Draw("E");
 
  // improve the picture:
  TF1 *backFcn = new TF1(Form("backFcn_%i", tryno), background,low,high,3);
   backFcn->SetLineWidth(2);
  TF1 *signalFcn = new TF1(Form("signalFcn_%i", tryno), GaussianPeak,low,high,3);
  TF1 *signalFcn2 = new TF1(Form("signalFcn2_%i", tryno), GaussianPeak2,low,high,3);
  // signalFcn->SetLineColor(2);
  // signalFcn->SetLineWidth(5);
  
  Double_t par[9];

  // writes the fit results into the par array
   fitFcn->GetParameters(par);
   Double_t xsq = fitFcn->GetChisquare();
   Double_t ndf = fitFcn->GetNDF();
   backFcn->SetParameters(&par[0]);
    backFcn->SetLineStyle(2);
 backFcn->SetLineColor(2);
   backFcn->SetLineWidth(2);
  
   backFcn->Draw("same");  //jb affects nothing

   signalFcn->SetParameters(&par[3]);
    signalFcn->SetLineStyle(2);
 signalFcn->SetLineColor(4);
   signalFcn->SetLineWidth(2);
  
   //signalFcn->Draw("same");

  signalFcn2->SetParameters(&par[6]);
  signalFcn2->SetLineStyle(2);
  signalFcn2->SetLineColor(4);
  signalFcn2->SetLineWidth(2);
  
   //signalFcn2->Draw("same");
   Double_t Intg = signalFcn->Integral(par[4]-factor*par[5],par[4]+factor*par[5]);
 Double_t Intg2 = signalFcn2->Integral(par[7]-factor*par[8],par[7]+factor*par[8]);
   Double_t Intb = backFcn->Integral(par[4]-factor*par[5],par[4]+factor*par[5]);
 //  cout<<"Integral of function is "<<Intg<<" "<<Intb<<endl;
   //cout<<"binwidth is "<<binw<<endl;
   Double_t binw = histo->GetBinWidth(1);
   Int_t yield = Intg/binw;
   Int_t yield2 = Intg2/binw;
   //Double_t ratio = Intg/Intb;
   
   
//   cout<<"Integral of histogram is "<<yield<<endl;
   TAxis *x=histo->GetXaxis();
   TAxis *y=histo->GetYaxis();
 
   Double_t startx=x->GetXmin()+0.65*(x->GetXmax()-x->GetXmin());
  Double_t starty=0.7*histo->GetMaximum();
  Double_t starty1=0.6*histo->GetMaximum();
  Double_t starty30=0.5*histo->GetMaximum();
  Double_t starty0=0.4*histo->GetMaximum();
  Double_t starty2=1.0*histo->GetMaximum();
  Double_t starty3=0.9*histo->GetMaximum();
  Double_t starty10=0.8*histo->GetMaximum();
  // cout<<startx<<" "<<starty<<endl;
  //TLatex *sum=new TLatex(startx, starty,Form("Ye_t starty0=0.85*histo->GetMaximum();
   TLatex *sum=new TLatex(startx, starty,Form("Mean2:%5.4f",par[7]));
   TLatex *sum1=new TLatex(startx, starty1,Form("#sigma2: %5.4f",par[8]));
   TLatex *sum10=new TLatex(startx, starty10,Form("Yield: %i",yield));
    TLatex *sum2=new TLatex(startx, starty2,Form("Mean:%5.4f",par[4]));
   TLatex *sum3=new TLatex(startx, starty3,Form("#sigma:%5.4f",par[5]));
   TLatex *sum30=new TLatex(startx, starty30,Form("Yield2: %i",yield2));
   TLatex *sum4=new TLatex(startx, starty0,Form("#chi^{2}/Ndf: %5.1f/%5.1f",xsq, ndf));
   sum->SetTextSize(0.05);
   sum->SetTextColor(2);
   sum->Draw("same");
   sum1->SetTextSize(0.05);
   sum1->SetTextColor(2);
   sum1->Draw("same");
   sum10->SetTextSize(0.05);
   sum10->SetTextColor(2);
   sum10->Draw("same");
    sum2->SetTextSize(0.05);
   sum2->SetTextColor(4);
   sum2->Draw("same");
   sum3->SetTextSize(0.05);
   sum3->SetTextColor(4);
   sum3->Draw("same");
   sum30->SetTextSize(0.05);
   sum30->SetTextColor(4);
   sum30->Draw("same");
  sum4->SetTextSize(0.05);
   sum4->SetTextColor(4);
   sum4->Draw("same");
 }

