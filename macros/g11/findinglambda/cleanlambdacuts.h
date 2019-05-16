/*
 *  cleanlambdacuts.h
 *  
 *
 *  Created by Jason Bono on 6/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 **this macro is just a copy of the steps that lei and i took in his office
 **when he showed me the way to obtain a very clean lambda distribution
 **the first plot is with out the "dd" cut, the second one is the one with it.
 */

TFile *_file0 = TFile::Open("new.root")
TH1F *h2=new TH1F("h2","",100,1.0,1.6)
.!grep TCut ~/.root_hist
TCut sc="abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.5"
TCut sc2="abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<1"
TCut ks="abs(mkp1pim-0.892)<0.08"
TCut st="abs(scv-stv)<1"
TCut vcut="abs(vz+10)<21&&(vx^2+vy^2)<8"
new->Draw("sqrt(mm2kpkppim)>>h2", sc&&sc2)


TCut dd="abs(sqrt(mm2kpkp)-1.32)<0.02"
new->Draw("sqrt(mm2kpkppim)>>h2", sc&&sc2&&dd)
