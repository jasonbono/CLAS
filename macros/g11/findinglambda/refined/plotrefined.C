void plotrefined(){

TFile *_file0 = TFile::Open("new.root");
TH1F *h2=new TH1F("h2","",200,0.5,2.0);


 TCut sc="abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.5";
 TCut sc2="abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<1";
 TCut ks="abs(mkp1pim-0.892)<0.08";
 TCut st="abs(scv-stv)<1";
 TCut vcut="abs(vz+10)<21&&(vx^2+vy^2)<8";
 //TCut vout="(vx^2+vy^2)>8";///BAD FOR CASCADE PLOTING!
 TCut ks2="abs(mkp2pim-0.892)<0.08";
 TCut cas="abs(sqrt(mm2kpkp)-1.322)<3*0.0077";
//TCut cas2="abs(sqrt(mm2kpkppim)-1.3172)<3*0.0066";
//TCut cas2p="abs(sqrt(mm2kpkppim)-1.315)<3*(1+(beam-2.6)/2)*0.0074";
//TCut cas2pside="abs(sqrt(mm2kpkppim)-1.315)<4*(1+(beam-2.6)/4)*0.0074&&abs(sqrt(mm2kpkppim)-1.315)>4*(1+(beam-2.6)/4)*0.0074";
//TCut cas2side="abs(sqrt(mm2kpkppim)-1.315)<6*0.0074&&abs(sqrt(mm2kpkppim)-1.315)>3*0.0074";
 TCut lambda="abs(sqrt(mm2kpkppim)-1.1162)<3*0.0088";
 TCut casm="abs(mlampim-1.3224)<3*0.004";
 TCut tof="abs(tofmasskp1-0.494)<0.07&&abs(tofmasskp2-0.494)<0.07";
//TCut b="abs(fixbeam-psbeam)<0.02 || abs(fixbeam-beam)<0.02";
//TCut b="abs(fixbeam-psbeam)/psbeam<0.0035 || abs(fixbeam-beam)/psbeam<0.0035";
//TCut bcut="abs(fixbeam-psbeam)/psbeam<0.027 || abs(fixbeam-beam)/psbeam<0.027"; //BAD FOR CASCADE CUT



//plot cascade
//new->Draw("sqrt(mm2kpkp)>>h2",sc&&sc2&&st&&vcut&&ks2&&tof&&lambda);//&&bcut);

 //plot lambda
 new->Draw("sqrt(mm2kpkppim)>>h2",sc&&sc2&&st&&vcut&&ks2&&tof&&cas);//&&bcut);

 //h2->Fit("gaus","","",1,1.3);

}
