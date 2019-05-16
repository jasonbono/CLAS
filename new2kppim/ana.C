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

TCut pis="mmkp2pippim>1.2&&mmkp1pippim>1.2&&mm3pi>1.3"
 TFile *f=xxx TFile("xxx.root", "WRITE");
TNtuple *xxx=(TNtuple *)f->Get("xxx");
 TFile *f1=new TFile("yyy.root", "WRITE");
  TNtuple *yyy=(TNtuple *)f1->Get("yyy");
 TCanvas *c1=new TCanvas("c1", "", 20, 20, 600, 600)
.L fit2BW.C
  c1->Divide(2,3)
TH1F *k1=new TH1F("k1", "", 150, 1.2,1.8)
k1->GetXaxis()->SetTitle("MM(K^{+} K^{+})/(GeV/c^{2})");
k1->GetXaxis()->SetTitleSize(0.05);
k1->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
k1->GetYaxis()->SetTitleSize(0.05);
TH1F *k2=new TH1F("k2", "", 150, 1.2,1.8)
k2->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
k2->GetXaxis()->SetTitleSize(0.05);
k2->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
k2->GetYaxis()->SetTitleSize(0.05);
TH1F *k2side=new TH1F("k2side", "", 150, 1.2,1.8)
k2side->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
k2side->GetXaxis()->SetTitleSize(0.05);
k2side->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
k2side->GetYaxis()->SetTitleSize(0.05);
TH1F *k2out=new TH1F("k2out", "", 150, 1.2,1.8)
k2out->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
k2out->GetXaxis()->SetTitleSize(0.05);
k2out->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
k2out->GetYaxis()->SetTitleSize(0.05);
TH1F *k5=new TH1F("k5", "", 150, 1.2,1.8)
k5->GetXaxis()->SetTitle("MM(K^{+} K^{+})/(GeV/c^{2})");
k5->GetXaxis()->SetTitleSize(0.05);
k5->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
k5->GetYaxis()->SetTitleSize(0.05);
TH1F *11=new TH1F("l1", "", 100, 0.9,1.2)
l1->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
l1->GetXaxis()->SetTitleSize(0.05);
l1->GetYaxis()->SetTitle("Events/(3MeV/c^{2})");
l1->GetYaxis()->SetTitleSize(0.05);
TH1F *10=new TH1F("l0", "", 200, 0.9,1.5)
l0->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
l0->GetXaxis()->SetTitleSize(0.05);
l0->GetYaxis()->SetTitle("Events/(3MeV/c^{2})");
l0->GetYaxis()->SetTitleSize(0.05);
TH1F *k3=new TH1F("k3", "", 50, 1.45,1.95)
k3->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k3->GetXaxis()->SetTitleSize(0.05);
k3->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3->GetYaxis()->SetTitleSize(0.05);
TH1F *k6=new TH1F("k6", "", 50, 1.45,1.95)
k6->GetXaxis()->SetTitle("MM(K^{+}K^{+})/(GeV/c^{2})");
k6->GetXaxis()->SetTitleSize(0.05);
k6->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k6->GetYaxis()->SetTitleSize(0.05);
TH1F *k3side=new TH1F("k3side", "", 50, 1.45,1.95)
k3side->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k3side->GetXaxis()->SetTitleSize(0.05);
k3side->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3side->GetYaxis()->SetTitleSize(0.05);
TH1F *k3out=new TH1F("k3out", "", 50, 1.45,1.95)
k3out->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k3out->GetXaxis()->SetTitleSize(0.05);
k3out->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3out->GetYaxis()->SetTitleSize(0.05);
TH1F *k6side=new TH1F("k6side", "", 50, 1.45,1.95)
k6side->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k6side->GetXaxis()->SetTitleSize(0.05);
k6side->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k6side->GetYaxis()->SetTitleSize(0.05);
TH1F *k4=new TH1F("k4", "", 50, 1.45,1.95)
k4->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k4->GetXaxis()->SetTitleSize(0.05);
k4->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k4->GetYaxis()->SetTitleSize(0.05);
TH1F *m1=new TH1F("m1", "", 100, 0.6,1.6)
m1->GetXaxis()->SetTitle("M(K^{+}_{1} #pi^{-})/(GeV/c^{2})");
m1->GetXaxis()->SetTitleSize(0.05);
m1->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
m1->GetYaxis()->SetTitleSize(0.05);
TH1F *m2=new TH1F("m2", "", 100, 0.6,1.6)
m2->GetXaxis()->SetTitle("M(K^{+}_{2} #pi^{-})/(GeV/c^{2})");
m2->GetXaxis()->SetTitleSize(0.05);
m2->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
m2->GetYaxis()->SetTitleSize(0.05);
TH1F *y1=new TH1F("y1", "", 20, 2.0,2.6)
y1->GetXaxis()->SetTitle("MM(K^{+}_{slow})/(GeV/c^{2})");
y1->GetXaxis()->SetTitleSize(0.05);
y1->GetYaxis()->SetTitle("Events/(30MeV/c^{2})");
y1->GetYaxis()->SetTitleSize(0.05);
TH1F *y2=new TH1F("y2", "", 20,2,2.6)
y2->GetXaxis()->SetTitle("MM(K^{+}_{slow})/(GeV/c^{2})");
y2->GetXaxis()->SetTitleSize(0.05);
y2->GetYaxis()->SetTitle("Events/(30MeV/c^{2})");
y2->GetYaxis()->SetTitleSize(0.05);
c1->cd(1)
 xxx->Draw("mmkp1>>y1",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vcut&&"abs(mmkpkp-1.535)<0.02", "E")
  c1->cd(2) 
xxx->Draw("mmkp1>>y2",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vcut&&"abs(mmkpkp-1.605)<0.02", "E")


 c1->cd(1)
xxx->Draw("sqrt(mm2kpkp)>>k1",sc&&st&&sc2&&"w>2.4")
fitGAUS(k1, 1, 1.2, 1.4, 1,1,1, 1.321,0.006, 3)
  c1->cd(2)
xxx->Draw("sqrt(mm2kpkppim)>>l1",sc&&st&&sc2&&"w>2.4"&&cas)
    fitGAUS(l1, 2, 0.95,1.15, 1,1,1, 1.115,0.006, 3)

  c1->cd(3)
xxx->Draw("sqrt(mm2kpkp)>>k5",sc&&st&&sc2&&"w>2.4"&&lambda)

fitGAUS(k5, 5, 1.2, 1.4, 1,1,1, 1.321,0.006, 3)
  c1->cd(4)
xxx->Draw("sqrt(mm2kpkppim)>>k2",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&vcut)
xxx->Draw("sqrt(mm2kpkppim)>>k2out",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&vout)
  k2out->Scale(0.912)
fitGAUS(k2, 3, 1.2, 1.4, 1,1,1, 1.315,0.006, 3)
   k2out->SetFillStyle(3004)
    k2out->SetFillColor(1)
    k2out->Draw("same")

    k2side->SetFillStyle(3004)
    k2side->SetFillColor(1)

xxx->Draw("sqrt(mm2kpkppim)>>k2side",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1"&&tof&&cas2side)
fitGAUS(k2, 3, 1.2, 1.4, 1,1,1, 1.315,0.006, 3)
    k2side->Draw("same")
  c1->cd(5)
  xxx->Draw("mcaspim>>k3",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vcut, "E")
  xxx->Draw("mcaspim>>k3out",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vout, "E")
  k3out->SetFillStyle(3004)
    k3out->SetFillColor(1)
   k3out->Scale(0.912)
 k3->Draw("E")
  k3out->Draw("SAME")

  k3side->SetFillStyle(3004)
    k3side->SetFillColor(1)

xxx->Draw("mcaspim>>k3side",sc&&st&&sc2&&"beam>2.6&&npip<1"&&cas2side)
    k3side->Scale(0.3612)
fitBW2(k3, 4, 1.515, 1.67, 1,1,1,1.54, 0.025, 1.6, 0.03, 3)
    k3side->Draw("same")



  c1->cd(6)


xxx->Draw("mkp1pim>>m1",sc&&st&&sc2&&"w>2.4"&&cas2)
  c1->cd(6)


xxx->Draw("sqrt(mm2kpkp)>>k6",sc2&&sc&&st&&"beam>2.6&&npip<1"&&cas2)
 k6side->SetFillStyle(3004)
    k6side->SetFillColor(1)
xxx->Draw("sqrt(mm2kpkp)>>k6side",sc&&st&&sc2&&"beam>2.6&&npip<1"&&cas2side)
    k6side->Scale(0.3612)
fitBW2(k6, 6, 1.515, 1.67, 1,1,1,1.54, 0.02, 1.6, 0.05, 3)
    k6side->Draw("same")


xxx->Draw("mkp2pim>>m2",sc&&st&&sc2&&"w>2.4"&&cas2)



xxx->Draw("mcaspim>>k4",sc&&!st&&sc2&&"w>2.4"&&cas2&&tof)
xxx->Draw("sqrt(mm2kpkppim)>>l0",sc&&st&&sc2&&"w>2.4")
    fitGAUS(l1, 2, 0.95,1.15, 1,1,1, 1.115,0.006, 3)

    c1->cd(1)
TH1F *t1=new TH1F("t1", "", 400, -4,4)
t1->GetXaxis()->SetTitle("#Delta t (ns)");
t1->GetXaxis()->SetTitleSize(0.05);
t1->GetYaxis()->SetTitle("");
t1->GetYaxis()->SetTitleSize(0.05);
t1->SetLineColor(2)
xxx->Draw("sctkp1-sclkp1/(betakp1*29.99)-scv>>t1",st&&sc2&&"npip<1&&nkm<1&&npim<2&&beam>2.6"&&vcut)
TH1F *t2=new TH1F("t2", "", 400, -4,4)
t2->GetXaxis()->SetTitle("#Delta t (ns)");
t2->GetXaxis()->SetTitleSize(0.05);
t2->GetYaxis()->SetTitle("");
t2->GetYaxis()->SetTitleSize(0.05);
t2->SetFillColor(4)
xxx->Draw("sctkp1-sclkp1/(betakp1*29.99)-scv>>t2",sc&&st&&sc2&&"npip<1&&nkm<1&&npim<2&&beam>2.6"&&vcut)
  t1->Draw("same")

  c1->cd(2)
TH1F *t3=new TH1F("t3", "", 400, -4,4)
t3->GetXaxis()->SetTitle("#Delta t (ns)");
t3->GetXaxis()->SetTitleSize(0.05);
t3->GetYaxis()->SetTitle("");
t3->GetYaxis()->SetTitleSize(0.05);
t3->SetLineColor(2)
xxx->Draw("sctkp2-sclkp2/(betakp2*29.99)-scv>>t3",st&&sc&&"npip<1&&nkm<1&&npim<2&&beam>2.6"&&vcut)
TH1F *t4=new TH1F("t4", "", 400, -4,4)
t4->GetXaxis()->SetTitle("#Delta t (ns)");
t4->GetXaxis()->SetTitleSize(0.05);
t4->GetYaxis()->SetTitle("");
t4->GetYaxis()->SetTitleSize(0.05);
t4->SetFillColor(4)
xxx->Draw("sctkp2-sclkp2/(betakp2*29.99)-scv>>t4",sc2&&st&&sc&&"npip<1&&nkm<1&&npim<2&&beam>2.6"&&vcut)
  t3->Draw("same")

   c1->cd(3)
TH1F *z1=new TH1F("z1", "", 120, -40,20)
z1->GetXaxis()->SetTitle("Vz (cm)");
z1->GetXaxis()->SetTitleSize(0.05);
z1->GetYaxis()->SetTitle("");
z1->GetYaxis()->SetTitleSize(0.05);
z1->SetLineColor(2)
xxx->Draw("vz>>z1",st&&sc2&&sc&&"npip<1&&nkm<1&&npim<2&&beam>2.6")
TH1F *z2=new TH1F("z2", "", 120, -40,20)
z2->GetXaxis()->SetTitle("Vz (cm)");
z2->GetXaxis()->SetTitleSize(0.05);
z2->GetYaxis()->SetTitle("");
z2->GetYaxis()->SetTitleSize(0.05);
z2->SetFillColor(4)
xxx->Draw("vz>>z2",sc2&&st&&sc&&"npip<1&&nkm<1&&npim<2&&beam>2.6&&abs(vz+10)<21")
  z1->Draw()
  z2->Draw("same")
   c1->cd(4)
  TH2F *r1=new TH2F("r1", "", 100, -10,10,100, -10,10)
r1->GetXaxis()->SetTitle("Vx (cm)");
r1->GetXaxis()->SetTitleSize(0.05);
r1->GetYaxis()->SetTitle("Vy (cm)");
r1->GetYaxis()->SetTitleSize(0.05);
r1->SetLineColor(2)
xxx->Draw("vy:vx>>r1",st&&sc2&&sc&&"npip<1&&nkm<1&&npim<2&&beam>2.6"&&cas2)

  c1->cd(4)
  TH2F *r2=new TH2F("r2", "", 100, -10,10,100, -10,10)
r2->GetXaxis()->SetTitle("Vx (cm)");
r2->GetXaxis()->SetTitleSize(0.05);
r2->GetYaxis()->SetTitle("Vy (cm)");
r2->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("vy:vx>>r2",st&&sc2&&sc&&"npip<1&&nkm<1&&npim<2&&beam>2.6&&(vx^2+vy^2)<4"&&cas2)
 r2->SetMarkerColor(2)
 r1->Draw()
  r2->Draw("same")

 c1->cd(1) 
 TH2F *s1=new TH2F("s1", "", 100,1.3,1.6, 50,1.5,2)
s1->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
s1->GetXaxis()->SetTitleSize(0.05);
s1->GetYaxis()->SetTitle("MM(K^{+} K^{+})/(GeV/c^{2})");
s1->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("sqrt(mm2kpkp):sqrt(mm2kpkppim)>>s1",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&np<2"&&pis)
  s1->Draw("CONT")
gStyle->SetPalette(1)
  c1->cd(2) 
  TH2F *s2=new TH2F("s2", "", 100,0.8,1.8, 100,0.8,1.8)
s2->GetXaxis()->SetTitle("MM(K^{+} K^{+})/(GeV/c^{2})");
s2->GetXaxis()->SetTitleSize(0.05);
s2->GetYaxis()->SetTitle("MM(3#pi^{+})/(GeV/c^{2})");
s2->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("mm3pi:sqrt(mm2kpkp)>>s2",sc&&st&&sc2&&"beam>2.6&&npip<1")
  s2->Draw("COL")
  c1->cd(3) 
  TH2F *s3=new TH2F("s3", "", 100,0.8,1.8, 100,0.8,1.8)
s3->GetXaxis()->SetTitle("MM(K^{+} K^{+})/(GeV/c^{2})");
s3->GetXaxis()->SetTitleSize(0.05);
s3->GetYaxis()->SetTitle("MM(K^{+}_{fast} #pi^{+}#pi^{-})/(GeV/c^{2})");
s3->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("mmkp1pippim:sqrt(mm2kpkp)>>s3",sc&&st&&sc2&&"beam>2.6&&npip<1")
  s3->Draw("COL")
  c1->cd(4) 
  TH2F *s4=new TH2F("s4", "", 100,0.8,1.8, 100,0.8,1.8)
s4->GetXaxis()->SetTitle("MM(K^{+} K^{+})/(GeV/c^{2})");
s4->GetXaxis()->SetTitleSize(0.05);
s4->GetYaxis()->SetTitle("MM(K^{+}_{slow} #pi^{+}#pi^{-})/(GeV/c^{2})");
s4->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("mmkp2pippim:sqrt(mm2kpkp)>>s4",sc&&st&&sc2&&"beam>2.6&&npip<1")
  s4->Draw("COL")


  c1->cd(1)
  TH2F *s5=new TH2F("s5", "", 50,1.7,2.2, 70,2,2.7)
s5->GetXaxis()->SetTitle("M(#Xi^{0} K^{+})/(GeV/c^{2})");
s5->GetXaxis()->SetTitleSize(0.05);
s5->GetYaxis()->SetTitle("M(#Xi^{0} K^{+}#pi^{-})/(GeV/c^{2})");
s5->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("mmkp2:mcaskp1>>s5",sc&&st&&sc2&&"beam>2.6&&npip<1"&&cas2p&&pis)
 TH2F *s6=new TH2F("s6", "", 50,1.7,2.2, 70,2,2.7)
s6->GetXaxis()->SetTitle("M(#Xi^{0} K^{+})/(GeV/c^{2})");
s6->GetXaxis()->SetTitleSize(0.05);
s6->GetYaxis()->SetTitle("M(#Xi^{0} K^{+}#pi^{-})/(GeV/c^{2})");
s6->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("mmkp1:mcaskp2>>s6",sc&&st&&sc2&&"beam>2.6&&npip<1"&&cas2p&&pis)
   s5->Add(s6)
  s5->Draw("COL")
  c1->cd(2)
  s5->ProjectionX("h2")
  h2->Draw()
c1->cd(3)
  s5->ProjectionX("h3")
  h3->Draw()
  c1->cd(4)
  TH2F *s7=new TH2F("s7", "", 100,1.2,1.6, 50,0.5,1)
s7->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-})/(GeV/c^{2})");
s7->GetXaxis()->SetTitleSize(0.05);
s7->GetYaxis()->SetTitle("M(K^{+}#pi^{-})/(GeV/c^{2})");
s7->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("mkp1pim:sqrt(mm2kpkppim)>>s7",sc&&st&&sc2&&"beam>2.6&&npip<1"&&pis&&"sqrt(mm2kpkp)>1.5")
  s7->Draw("COL")
  TH2F *s8=new TH2F("s8", "", 100,1.2,1.6, 50,0.5,1)
s8->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-})/(GeV/c^{2})");
s8->GetXaxis()->SetTitleSize(0.05);
s8->GetYaxis()->SetTitle("M(K^{+}#pi^{-})/(GeV/c^{2})");
s8->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("mkp2pim:sqrt(mm2kpkppim)>>s8",sc&&st&&sc2&&"beam>2.6&&npip<1"&&pis&&"sqrt(mm2kpkp)>1.5")
  s8->Draw("COL")
  s7->Add(s8)
  s7->Draw("COL")







//cuts variation
TH1F *k2=new TH1F("k2", "", 150, 1.2,1.8)
k2->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
k2->GetXaxis()->SetTitleSize(0.05);
k2->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
k2->GetYaxis()->SetTitleSize(0.05);
TH1F *k3=new TH1F("k3", "", 50, 1.45,1.95)
k3->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k3->GetXaxis()->SetTitleSize(0.05);
k3->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3->GetYaxis()->SetTitleSize(0.05);
TH1F *k2sc=new TH1F("k2sc", "", 150, 1.2,1.8)
k2sc->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
k2sc->GetXaxis()->SetTitleSize(0.05);
k2sc->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
k2sc->GetYaxis()->SetTitleSize(0.05);
TH1F *k3sc=new TH1F("k3sc", "", 50, 1.45,1.95)
k3sc->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k3sc->GetXaxis()->SetTitleSize(0.05);
k3sc->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3sc->GetYaxis()->SetTitleSize(0.05);
TH1F *k2tof=new TH1F("k2tof", "", 150, 1.2,1.8)
k2tof->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
k2tof->GetXaxis()->SetTitleSize(0.05);
k2tof->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
k2tof->GetYaxis()->SetTitleSize(0.05);
TH1F *k3tof=new TH1F("k3tof", "", 50, 1.45,1.95)
k3tof->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k3tof->GetXaxis()->SetTitleSize(0.05);
k3tof->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3tof->GetYaxis()->SetTitleSize(0.05);
c1->cd(1)
xxx->Draw("sqrt(mm2kpkppim)>>k2",st&&"beam>2.6&&npip<1")
fitGAUS(k2, 1, 1.2, 1.4, 1,1,1, 1.315,0.006, 3)
  c1->cd(2)
  xxx->Draw("mfixcaspim>>k3",st&&"beam>2.6&&npip<1"&&cas2&&pis, "E")
c1->cd(3)
xxx->Draw("sqrt(mm2kpkppim)>>k2sc",sc&&st&&sc2&&"beam>2.6&&npip<1")
fitGAUS(k2sc, 2, 1.2, 1.4, 1,1,1, 1.315,0.006, 3)
  c1->cd(4)
  xxx->Draw("mfixcaspim>>k3sc",sc&&st&&sc2&&"beam>2.6&&npip<1"&&cas2&&pis, "E")
c1->cd(5)
xxx->Draw("sqrt(mm2kpkppim)>>k2tof",sc&&st&&sc2&&"beam>2.6&&npip<1"&&tof)
fitGAUS(k2tof, 3, 1.2, 1.4, 1,1,1, 1.315,0.006, 3)
  c1->cd(6)
  xxx->Draw("mfixcaspim>>k3tof",sc&&st&&sc2&&"beam>2.6&&npip<1"&&cas2&&tof&&pis, "E")

//cuts variation
TH1F *k2=new TH1F("k2", "", 150, 1.2,1.8)
k2->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
k2->GetXaxis()->SetTitleSize(0.05);
k2->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
k2->GetYaxis()->SetTitleSize(0.05);
TH1F *k3=new TH1F("k3", "", 50, 1.45,1.95)
k3->GetXaxis()->SetTitle("MM(K^{+}K^{+})/(GeV/c^{2})");
k3->GetXaxis()->SetTitleSize(0.05);
k3->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3->GetYaxis()->SetTitleSize(0.05);
TH1F *k2sc=new TH1F("k2sc", "", 150, 1.2,1.8)
k2sc->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
k2sc->GetXaxis()->SetTitleSize(0.05);
k2sc->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
k2sc->GetYaxis()->SetTitleSize(0.05);
TH1F *k3sc=new TH1F("k3sc", "", 50, 1.45,1.95)
k3sc->GetXaxis()->SetTitle("MM(K^{+}K^{+})/(GeV/c^{2})");
k3sc->GetXaxis()->SetTitleSize(0.05);
k3sc->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3sc->GetYaxis()->SetTitleSize(0.05);
TH1F *k2tof=new TH1F("k2tof", "", 150, 1.2,1.8)
k2tof->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
k2tof->GetXaxis()->SetTitleSize(0.05);
k2tof->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
k2tof->GetYaxis()->SetTitleSize(0.05);
TH1F *k3tof=new TH1F("k3tof", "", 50, 1.45,1.95)
k3tof->GetXaxis()->SetTitle("MM(K^{+}K^{+})/(GeV/c^{2})");
k3tof->GetXaxis()->SetTitleSize(0.05);
k3tof->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3tof->GetYaxis()->SetTitleSize(0.05);
c1->cd(1)
xxx->Draw("sqrt(mm2kpkppim)>>k2",st&&"beam>2.6&&npip<1")
fitGAUS(k2, 1, 1.2, 1.4, 1,1,1, 1.315,0.006, 3)
  c1->cd(2)
  xxx->Draw("sqrt(psmm2kpkp)>>k3",st&&"beam>2.6&&npip<1"&&cas2&&pis, "E")
c1->cd(3)
xxx->Draw("sqrt(mm2kpkppim)>>k2sc",sc&&st&&sc2&&"beam>2.6&&npip<1")
fitGAUS(k2sc, 2, 1.2, 1.4, 1,1,1, 1.315,0.006, 3)
  c1->cd(4)
  xxx->Draw("sqrt(psmm2kpkp)>>k3sc",sc&&st&&sc2&&"beam>2.6&&npip<1"&&cas2&&pis, "E")
c1->cd(5)
xxx->Draw("sqrt(mm2kpkppim)>>k2tof",sc&&st&&sc2&&"beam>2.6&&npip<1"&&tof)
fitGAUS(k2tof, 3, 1.2, 1.4, 1,1,1, 1.315,0.006, 3)
  c1->cd(6)
  xxx->Draw("sqrt(psmm2kpkp)>>k3tof",sc&&st&&sc2&&"beam>2.6&&npip<1"&&cas2&&tof&&pis, "E")



TH1F *kt1=new TH1F("kt1", "", 50, 1.5,2)
kt1->GetXaxis()->SetTitle("MM(K^{+}K^{+})/(GeV/c^{2})");
kt1->GetXaxis()->SetTitleSize(0.05);
kt1->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
kt1->GetYaxis()->SetTitleSize(0.05);
TH1F *kt2=new TH1F("kt2", "", 50, 1.5,2)
kt2->GetXaxis()->SetTitle("MM(K^{+}K^{+})/(GeV/c^{2})");
kt2->GetXaxis()->SetTitleSize(0.05);
kt2->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
kt2->GetYaxis()->SetTitleSize(0.05);
TH1F *t1=new TH1F("t1", "", 70, 0.3,0.65)
t1->GetXaxis()->SetTitle("TOF_MASS(K^{+}_{fast})(GeV/c^{2})");
t1->GetXaxis()->SetTitleSize(0.05);
t1->GetYaxis()->SetTitle("Events/(5MeV/c^{2})");
t1->GetYaxis()->SetTitleSize(0.05);
TH1F *t2=new TH1F("t2", "", 70, 0.3,0.65)
t2->GetXaxis()->SetTitle("TOF_MASS(K^{+}_{fast})(GeV/c^{2})");
t2->GetXaxis()->SetTitleSize(0.05);
t2->GetYaxis()->SetTitle("Events/(5MeV/c^{2})");
t2->GetYaxis()->SetTitleSize(0.05);
TCut sct1="abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.8"
TCut sct2="abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.2"
  c1->cd(1)
  xxx->Draw("tofmasskp1>>t1", "abs(scv-stv)<0.5&&beam>3.3"&&sct1&&sc2)
c1->cd(2)
  xxx->Draw("mmkpkp>>kt1", "abs(scv-stv)<0.5&&beam>3.3"&&sct1&&sc2)
 c1->cd(3)
  xxx->Draw("tofmasskp1>>t2", "abs(scv-stv)<0.5&&beam>3.3"&&sct2&&sc2)
c1->cd(4)
  xxx->Draw("mmkpkp>>kt2", "abs(scv-stv)<0.5&&beam>3.3"&&sct2&&sc2)
c1->Print("newplots/mmkpkp.2sccuts.eps")
c1->Print("newplots/mmkpkp.2sccuts.gif")


//angles
  gStyle->SetPalette(1)
  TH2F *s1=new TH2F("s1", "", 50,1.45,1.95,10,-1,1)
  s1->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})")
s1->GetXaxis()->SetTitleSize(0.05);
s1->GetYaxis()->SetTitle("Cos(#theta_{#pi^{-}}^{HEL})");
s1->GetYaxis()->SetTitleSize(0.05);

xxx->Draw("pihtheta:mfixcaspim>>s1",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&cas2&&vcut)
  s1->Draw("CONT")
 TH2F *s2=new TH2F("s2", "", 50,1.45,1.95,10,-1,1)
  s2->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})")
s2->GetXaxis()->SetTitleSize(0.05);
s2->GetYaxis()->SetTitle("Cos(#theta_{#pi^{-}}^{HEL})");
s2->GetYaxis()->SetTitleSize(0.05);

xxx->Draw("pihtheta:mfixcaspim>>s2",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&cas2&&vout)
  s2->Draw("CONT")
  s2->Scale(0.646)
  s1->Add(s2,-1)
  s1->Draw("CONT")
  c1->Print("mcaspimVSpihtheta.gif")
 c1->Print("mcaspimVSpihtheta.eps")


  TH2F *s3=new TH2F("s3", "", 50,1.45,1.95,10,-1,1)
  s3->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})")
s3->GetXaxis()->SetTitleSize(0.05);
s3->GetYaxis()->SetTitle("Cos(#theta_{(#Xi^{0}#pi^{-})}^{*})");
s3->GetYaxis()->SetTitleSize(0.05);

xxx->Draw("Xcmtheta:mfixcaspim>>s3",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&cas2&&vcut)
  s3->Draw("CONT")
 TH2F *s4=new TH2F("s4", "", 50,1.45,1.95,10,-1,1)
  s4->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})")
s4->GetXaxis()->SetTitleSize(0.05);
s4->GetYaxis()->SetTitle("Cos(#theta_{(#Xi^{0}#pi^{-})}^{*})");
s4->GetYaxis()->SetTitleSize(0.05);

xxx->Draw("Xcmtheta:mfixcaspim>>s4",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&cas2&&vout)
  s4->Draw("CONT")
  s4->Scale(0.646)
  s3->Add(s4,-1)
  s3->Draw("CONT")
 c1->Print("mcaspimVSxcmtheta.gif")
 c1->Print("mcaspimVSxcmtheta.eps")


 c1->cd(1) 
 TH1F *a1=new TH1F("a1", "|M(#Xi^{0}#pi^{-})-1.535|<0.02", 11,-1,1)
xxx->Draw("pihtheta>>a1",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&cas2&&vcut&&"abs(mfixcaspim-1.535)<0.02")
a1->GetXaxis()->SetTitle("Cos(#theta_{#pi^{-}}^{HEL})");
a1->GetXaxis()->SetTitleSize(0.07);
  TH1F *a1side=new TH1F("a1side", "", 11,-1,1)
xxx->Draw("pihtheta>>a1side",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&vout&&cas2&&"abs(mfixcaspim-1.535)<0.02")
    a1side->Scale(0.646)
 a1->Add(a1side,-1)
  a1->Draw("E")  

    c1->cd(3)
TH1F *a2=new TH1F("a2", "|M(#Xi^{0}#pi^{-})-1.605|<0.02", 11,-1,1)
  TH1F *a2side=new TH1F("a2side", "", 11,-1,1)
a2->GetXaxis()->SetTitle("Cos(#theta_{#pi^{-}}^{HEL})");
a2->GetXaxis()->SetTitleSize(0.07);
xxx->Draw("pihtheta>>a2",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&vcut&&cas2&&"abs(mcaspim-1.605)<0.02")
xxx->Draw("pihtheta>>a2side",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&vout&&cas2side&&"abs(mcaspim-1.605)<0.02")
    a2side->Scale(0.646)
  a2->Add(a2side,-1)
  a2->Draw("E")

    c1->cd(2)

TH1F *a3=new TH1F("a3", "|M(#Xi^{0}#pi^{-})-1.655|<0.02", 11,-1,1)
  TH1F *a3side=new TH1F("a3side", "", 11,-1,1)
a3->GetXaxis()->SetTitle("Cos(#theta_{#pi^{-}}^{HEL})");
a3->GetXaxis()->SetTitleSize(0.07);
xxx->Draw("pihtheta>>a3",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&vcut&&cas2&&"abs(mcaspim-1.655)<0.02")
xxx->Draw("pihtheta>>a3side",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&vout&&cas2side&&"abs(mcaspim-1.655)<0.02")
    a3side->Scale(0.646)
  a3->Add(a3side,-1)
  a3->Draw("E")

  c1->cd(4)
TH1F *a4=new TH1F("a4", "|M(#Xi^{0}#pi^{-})-1.565|<0.02", 11,-1,1)
  TH1F *a4side=new TH1F("a4side", "", 11,-1,1)
a4->GetXaxis()->SetTitle("Cos(#theta_{#pi^{-}}^{HEL})");
a4->GetXaxis()->SetTitleSize(0.07);
xxx->Draw("pihtheta>>a4",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&vcut&&cas2&&"abs(mcaspim-1.565)<0.02")
xxx->Draw("pihtheta>>a4side",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&npim<2"&&vout&&cas2side&&"abs(mcaspim-1.565)<0.02")
    a4side->Scale(0.646)
  a4->Add(a4side,-1)
  a4->Draw("E")


  c1->cd(1)
TH1F *k3a=new TH1F("k3a", "-1<Cos(#theta_{#pi^{-}}^{HEL})<1", 50, 1.45,1.95)
k3a->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k3a->GetXaxis()->SetTitleSize(0.05);
k3a->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3a->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("mfixcaspim>>k3a",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vcut&&"pihtheta<1")
  c1->cd(2)
TH1F *k3b=new TH1F("k3b", "Cos(#theta_{#pi^{-}}^{HEL})<0", 50, 1.45,1.95)
k3b->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k3b->GetXaxis()->SetTitleSize(0.05);
k3b->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3b->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("mfixcaspim>>k3b",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vcut&&"pihtheta<0")
TH1F *k3bout=new TH1F("k3bout", "Cos(#theta_{#pi^{-}}^{HEL})<0", 50, 1.45,1.95)
k3bout->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k3bout->GetXaxis()->SetTitleSize(0.05);
k3bout->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3bout->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("mfixcaspim>>k3bout",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vout&&"pihtheta<0")
  k3bout->Scale(0.646)
k3bout->SetFillStyle(3004)
k3bout->SetFillColor(2)
  k3b->Draw()
  k3bout->Draw("same")
  c1->cd(3)
TH1F *k3c=new TH1F("k3c", "0<Cos(#theta_{#pi^{-}}^{HEL})<0.5", 50, 1.45,1.95)
k3c->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k3c->GetXaxis()->SetTitleSize(0.07);
k3c->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3c->GetYaxis()->SetTitleSize(0.07);
xxx->Draw("mfixcaspim>>k3c",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vcut&&"abs(pihtheta-0.25)<0.25")
TH1F *k3cout=new TH1F("k3cout", "Cos(#theta_{#pi^{-}}^{HEL})<0", 50, 1.45,1.95)
k3cout->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k3cout->GetXaxis()->SetTitleSize(0.07);
k3cout->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3cout->GetYaxis()->SetTitleSize(0.07);
xxx->Draw("mfixcaspim>>k3cout",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vout&&"abs(pihtheta-0.25)<0.25")
  k3cout->Scale(0.646)
k3cout->SetFillStyle(3004)
k3cout->SetFillColor(2)
  k3c->Draw()
  k3cout->Draw("same")
  c1->cd(4)
TH1F *k3d=new TH1F("k3d", "Cos(#theta_{#pi^{-}}^{HEL})>0.5", 50, 1.45,1.95)
k3d->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k3d->GetXaxis()->SetTitleSize(0.07);
k3d->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3d->GetYaxis()->SetTitleSize(0.07);
xxx->Draw("mfixcaspim>>k3d",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vcut&&"pihtheta>0.5")
TH1F *k3dout=new TH1F("k3dout", "Cos(#theta_{#pi^{-}}^{HEL})<0", 50, 1.45,1.95)
k3dout->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k3dout->GetXaxis()->SetTitleSize(0.07);
k3dout->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3dout->GetYaxis()->SetTitleSize(0.07);
xxx->Draw("mfixcaspim>>k3dout",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vout&&"pihtheta>0.5")
  k3dout->Scale(0.646)
k3dout->SetFillStyle(3004)
k3dout->SetFillColor(2)
  k3d->Draw()
  k3dout->Draw("same")
c1->Print("mcaspim.pihthetacut.eps")
c1->Print("mcaspim.pihthetacut.gif")


  c1->cd(1)
TH1F *m3a=new TH1F("m3a", "-1<Cos(#theta_{(#Xi^{0}#pi^{-})}^{*})<1", 50, 1.45,1.95)
m3a->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
m3a->GetXaxis()->SetTitleSize(0.07);
m3a->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
m3a->GetYaxis()->SetTitleSize(0.07);
xxx->Draw("mfixcaspim>>m3a",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vcut&&"Xcmtheta<1")
TH1F *m3aout=new TH1F("m3aout", "Cos(#theta_{(#Xi^{0}#pi^{-})}^{*})<0", 50, 1.45,1.95)
m3aout->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
m3aout->GetXaxis()->SetTitleSize(0.07);
m3aout->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
m3aout->GetYaxis()->SetTitleSize(0.07);
xxx->Draw("mfixcaspim>>m3aout",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vout&&"Xcmtheta<1")
  m3aout->Scale(0.646)
m3aout->SetFillStyle(3004)
m3aout->SetFillColor(2)
  m3a->Draw()
  m3aout->Draw("same")
  c1->cd(2)
TH1F *m3b=new TH1F("m3b", "Cos(#theta_{(#Xi^{0}#pi^{-})}^{*})<0", 50, 1.45,1.95)
m3b->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
m3b->GetXaxis()->SetTitleSize(0.07);
m3b->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
m3b->GetYaxis()->SetTitleSize(0.07);
xxx->Draw("mfixcaspim>>m3b",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vcut&&"Xcmtheta<0")
TH1F *m3bout=new TH1F("m3bout", "Cos(#theta_{(#Xi^{0}#pi^{-})}^{*})<0", 50, 1.45,1.95)
m3bout->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
m3bout->GetXaxis()->SetTitleSize(0.07);
m3bout->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
m3bout->GetYaxis()->SetTitleSize(0.07);
xxx->Draw("mfixcaspim>>m3bout",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vout&&"Xcmtheta<0")
  m3bout->Scale(0.646)
m3bout->SetFillStyle(3004)
m3bout->SetFillColor(2)
  m3b->Draw()
  m3bout->Draw("same")
  c1->cd(3)
TH1F *m3c=new TH1F("m3c", "0<Cos(#theta_{(#Xi^{0}#pi^{-})}^{*})<0.5", 50, 1.45,1.95)
m3c->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
m3c->GetXaxis()->SetTitleSize(0.07);
m3c->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
m3c->GetYaxis()->SetTitleSize(0.07);
xxx->Draw("mfixcaspim>>m3c",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vcut&&"abs(Xcmtheta-0.25)<0.25")
TH1F *m3cout=new TH1F("m3cout", "Cos(#theta_{(#Xi^{0}#pi^{-})}^{*})<0", 50, 1.45,1.95)
m3cout->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
m3cout->GetXaxis()->SetTitleSize(0.07);
m3cout->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
m3cout->GetYaxis()->SetTitleSize(0.07);
xxx->Draw("mfixcaspim>>m3cout",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vout&&"abs(Xcmtheta-0.25)<0.25")
  m3cout->Scale(0.646)
m3cout->SetFillStyle(3004)
m3cout->SetFillColor(2)
  m3c->Draw()
  m3cout->Draw("same")
  c1->cd(4)
TH1F *m3d=new TH1F("m3d", "Cos(#theta_{(#Xi^{0}#pi^{-})}^{*})>0.5", 50, 1.45,1.95)
m3d->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
m3d->GetXaxis()->SetTitleSize(0.07);
m3d->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
m3d->GetYaxis()->SetTitleSize(0.07);
xxx->Draw("mfixcaspim>>m3d",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vcut&&"Xcmtheta>0.5")
TH1F *m3dout=new TH1F("m3dout", "Cos(#theta_{(#Xi^{0}#pi^{-})}^{*})<0", 50, 1.45,1.95)
m3dout->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
m3dout->GetXaxis()->SetTitleSize(0.07);
m3dout->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
m3dout->GetYaxis()->SetTitleSize(0.07);
xxx->Draw("mfixcaspim>>m3dout",sc&&st&&sc2&&"beam>2.6&&npip<1&&npim<2&&nkm<1"&&cas2&&vout&&"Xcmtheta>0.5")
  m3dout->Scale(0.646)
m3dout->SetFillStyle(3004)
m3dout->SetFillColor(2)
  m3d->Draw()
  m3dout->Draw("same")
c1->Print("mcaspim.xcmthetacut.eps")
c1->Print("mcaspim.xcmthetacut.gif")


  TH2F *ms=new TH2F("ms", "", 80,1.05,1.45,60,1.2,1.8)
  ms->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-})/(GeV/c^{2})")
 ms->GetYaxis()->SetTitle("MM(K^{+}K^{+})/(GeV/c^{2})")
  xxx->Draw("mmkpkp:sqrt(mm2kpkppim)>>ms", sc&&st&&sc2&&"beam>2.6"&&vcut)


  c2->cd(1)
  TH2F *ms1=new TH2F("ms1", "", 80,0.65,1.45,80,0.8,1.6)
  ms1->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-})/(GeV/c^{2})")
 ms1->GetYaxis()->SetTitle("MM(K_{fast}^{+}#pi_{slow}^{+}#pi^{-})/(GeV/c^{2})")
  xxx->Draw("mmkp1pippim:sqrt(mm2kpkppim)>>ms1", sc&&st&&sc2&&"beam>2.6"&&vcut)
 c2->cd(2)

  TH2F *ms2=new TH2F("ms2", "", 80,0.65,1.45,80,0.8,1.6)
  ms2->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-})/(GeV/c^{2})")
 ms2->GetYaxis()->SetTitle("MM(K_{slow}^{+}#pi_{fast}^{+}#pi^{-})/(GeV/c^{2})")
 ms2->GetYaxis()->SetTitleSize(0.06);
 ms2->GetYaxis()->SetTitleOffset(1);
 xxx->Draw("mmkp2pippim:sqrt(mm2kpkppim)>>ms2", sc&&st&&sc2&&"beam>2.6"&&vcut, "CONTZ")
c2->cd(3)

  TH2F *ms3=new TH2F("ms3", "", 80,0.65,1.45,110,0.8,1.9)
  ms3->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-})/(GeV/c^{2})")
 ms3->GetYaxis()->SetTitle("MM(#pi_{slow}^{+}#pi_{fast}^{+}#pi^{-})/(GeV/c^{2})")
 ms3->GetYaxis()->SetTitleSize(0.06);
 ms3->GetYaxis()->SetTitleOffset(1);
 xxx->Draw("mm3pi:sqrt(mm2kpkppim)>>ms3", sc&&st&&sc2&&"beam>2.6"&&vcut, "CONTZ")


.L ~/scripts/macros/fitGAUS.C

 c1->cd(1)
TH1F *11=new TH1F("l1", "", 100, 0.9,1.2)
l1->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
l1->GetXaxis()->SetTitleSize(0.05);
l1->GetYaxis()->SetTitle("Events/(3MeV/c^{2})");
l1->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("sqrt(mm2kpkppim)>>l1",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&np<2"&&cas)
fitGAUS(l1, 1, 0.9,1.2, 1,1,1, 1.115,0.01, 3)

  c1->cd(2)
TH1F *k1=new TH1F("k1", "", 150, 1.25,1.7)
k1->GetXaxis()->SetTitle("MM(K^{+} K^{+})/(GeV/c^{2})");
k1->GetXaxis()->SetTitleSize(0.05);
k1->GetYaxis()->SetTitle("Events/(3MeV/c^{2})");
k1->GetYaxis()->SetTitleSize(0.05);
xxx->Draw("mmkpkp>>k1",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&np<2"&&lambda, "E")
fitGAUS(k1, 2, 1.28,1.4, 1,1,1, 1.321,0.01, 3)



TH1F *10=new TH1F("l0", "", 200, 0.9,1.5)
l0->GetXaxis()->SetTitle("MM(K^{+} K^{+}#pi^{-})/(GeV/c^{2})");
l0->GetXaxis()->SetTitleSize(0.05);
l0->GetYaxis()->SetTitle("Events/(3MeV/c^{2})");
l0->GetYaxis()->SetTitleSize(0.05);
TH1F *10out=new TH1F("l0out", "", 200, 0.9,1.5)


xxx->Draw("sqrt(mm2kpkppim)>>l0out",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&np<2"&&vout,"E")
xxx->Draw("sqrt(mm2kpkppim)>>l0",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&np<2"&&vcut,"E")
l0out->SetFillColor(2)
l0out->SetFillStyle(3004)
  l0out->Scale(0.912)
l0out->Draw("SAME")

  c1->cd(1)
TH1F *p0=new TH1F("p0", "", 50, 0,1)
p0->GetXaxis()->SetTitle("Confidence Level (CL)");
  xxx->Draw("cl>>p0",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&np<2"&&vcut&&cas2, "E");
TH1F *p1=new TH1F("p1", "", 50, 0,1)
p1->GetXaxis()->SetTitle("Confidence Level (CL)");
  xxx->Draw("cl>>p1",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&np<2"&&vcut&&cas2&&"cl>0.1");
p1->SetFillColor(2)
  p0->Draw("E")
  p1->Draw("same");
c1->cd(2)
  TH1F *x0=new TH1F("x0", "", 150, 1.2,1.8)
x0->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
x0->GetXaxis()->SetTitleSize(0.05);
x0->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
x0->GetYaxis()->SetTitleSize(0.05);
x0->SetTitle("CL>0.1")
  xxx->Draw("sqrt(mm2kpkppim)>>x0",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&np<2"&&vcut&&cas2&&"cl>0.1", "E");
x0->SetFillColor(2)
  TH1F *x1=new TH1F("x1", "", 150, 1.2,1.8)
x1->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
x1->GetXaxis()->SetTitleSize(0.05);
x1->GetYaxis()->SetTitle("Events/(4MeV/c^{2})");
x1->GetYaxis()->SetTitleSize(0.05);
x1->SetTitle("CL>0.1")
  xxx->Draw("sqrt(mm2kpkppim)>>x1",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&np<2"&&vcut, "E");
x0->Draw("same")

  c1->cd(3)
TH1F *k0=new TH1F("k0", "", 50, 1.45,1.95)
k0->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k0->GetXaxis()->SetTitleSize(0.05);
k0->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k0->GetYaxis()->SetTitleSize(0.05);
k0->SetTitle("CL>0.1")
  xxx->Draw("fitmmkpkp>>k0",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&np<2"&&vcut&&cas2, "E");
c1->cd(4)
TH1F *k3=new TH1F("k3", "", 50, 1.45,1.95)
k3->GetXaxis()->SetTitle("M(#Xi^{0}#pi^{-})/(GeV/c^{2})");
k3->GetXaxis()->SetTitleSize(0.05);
k3->GetYaxis()->SetTitle("Events/(10MeV/c^{2})");
k3->GetYaxis()->SetTitleSize(0.05);
k3->SetTitle("CL>0.1")
  xxx->Draw("fitmmkpkp>>k3",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&np<2"&&vcut&&cas2&&"cl>0.1", "E");


TH1F *b1=new TH1F("b1", "", 20,3,5)
b1->GetXaxis()->SetTitleSize(0.05);
b1->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
  xxx->Draw("beam>>b1",sc&&st&&sc2&&"beam>2.6&&npip<1&&nkm<1&&np<2"&&vcut&&cas2&&"cl>0.1");
