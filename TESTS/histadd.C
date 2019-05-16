//histadd.C jul 1. created to learn how to add histograms.

#include <Riostream.h>


void histadd(){


  TFile *f = new TFile("new.root");

  
  //new->Draw("pow(beam,2)");
  //new->Draw("beam+run*2000");
  //THEESE WORK FINE


lamb="beam";
 new->Draw("lamb");







}
