/*
 *  findlambda.h
 *  
 *
 *  Created by Jason Bono on 6/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

TFile *_file0 = TFile::Open("new.root")
TCut sc="abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.5"
TCut sc2="abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<1"
TCut ks="abs(mkp1pim-0.892)<0.08"
TCut st="abs(scv-stv)<1"
TCut vcut="abs(vz+10)<21&&(vx^2+vy^2)<8"
TCut vout="(vx^2+vy^2)>8"
TCut ks2="abs(mkp2pim-0.892)<0.08"
TCut cas="abs(sqrt(mm2kpkp)-1.322)<3*0.0077"
TCut cas2="abs(sqrt(mm2kpkppim)-1.3172)<3*0.0066"
TCut cas2p="abs(sqrt(mm2kpkppim)-1.315)<3*(1+(beam-2.6)/2)*0.0074"
TCut cas2pside="abs(sqrt(mm2kpkppim)-1.315)<4*(1+(beam-2.6)/4)*0.0074&&abs(sqrt(mm2kpkppim)-1.315)>4*(1+(beam-2.6)/4)*0.0074"
TCut cas2side="abs(sqrt(mm2kpkppim)-1.315)<6*0.0074&&abs(sqrt(mm2kpkppim)-1.315)>3*0.0074"
TCut lambda="abs(sqrt(mm2kpkppim)-1.1162)<3*0.0088"  
TCut casm="abs(mlampim-1.3224)<3*0.004"
TCut tof="abs(tofmasskp1-0.494)<0.07&&abs(tofmasskp2-0.494)<0.07"
TCut b="abs(fixbeam-psbeam)<0.02 || abs(fixbeam-beam)<0.02"
TCut b="abs(fixbeam-psbeam)/psbeam<0.0035 || abs(fixbeam-beam)/psbeam<0.0035"
TCut bcut="abs(fixbeam-psbeam)/psbeam<0.027 || abs(fixbeam-beam)/psbeam<0.027"
root [26] TH1F *k2=new TH1F("k2", "", 150, 1.2,1.8)   
k2->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})"); 
k2->GetXaxis()->SetTitleSize(0.05);
 k2->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
k2->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("sqrt(mm2kpkppim)>>k2",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&vcut)
new->Draw("sqrt(mm2kpkppim)>>k2",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&vcut)










