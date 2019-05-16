void plotcros(Int_t bins, Double_t estep){
  Int_t i;
  Double_t beam[19], beamerr[19],w[19], werr[19];
  Double_t sigbeam[23], sigbeamerr[23],sigw[23], sigwerr[23];
  Double_t sigcros[23]={0.643241, 0.759652, 0.823982, 0.887194, 0.607188, 0.629681, 0.471254, 0.475415, 0.390884, 0.380114, 0.39604, 0.294703, 0.295912, 0.32745, 0.262228, 0.248578, 0.190327, 0.220846, 0.235915, 0.182447, 0.209451, 0.240892, 0.306719};
  Double_t sigcrosstat[23]={.0213071, 0.014216, 0.0181368, 0.0143648, 0.0168586, 0.013918, 0.0104931, 0.0106135, 0.0102217, 0.0101058, 0.00910806, 0.00735169, 0.00861354, 0.00692428, 0.00670139, 0.00685769, 0.00564834, 0.00602223, 0.00650238, 0.00607867,0.00513143, 0.00666968, 0.00835432};
  Double_t sigcroserr[23];

  Double_t g1beam[81]={0.944, 0.969, 0.994, 1.019, 1.044, 1.069, 1.094, 1.119, 1.144, 1.169, 1.194, 1.219, 1.244, 1.269, 1.294, 1.320, 1.345, 1.370, 1.395, 1.421, 1.446, 1.471, 1.496, 1.521, 1.546, 1.571, 1.596, 1.621, 1.647, 1.672, 1.698, 1.723, 1.748, 1.774, 1.799, 1.824, 1.849, 1.875, 1.900, 1.925, 1.950, 1.975, 2.001, 2.026, 2.051, 2.076, 2.101, 2.126, 2.151, 2.177, 2.202, 2.227, 2.253, 2.278, 2.303, 2.328, 2.353, 2.378, 2.405, 2.430, 2.455, 2.480, 2.505, 2.530, 2.555, 2.580, 2.605, 2.630, 2.655, 2.680, 2.704, 2.729, 2.754, 2.778, 2.803, 2.827, 2.852, 2.876, 2.901, 2.925,
2.950};
  Double_t g1beamerr[81], g1w[81], g1werr[81];
  Double_t g1lcros[81]={0.870, 1.247, 1.605, 1.911, 2.046, 2.188, 2.233, 2.238, 2.216, 1.969, 2.144, 2.124, 2.203, 2.207, 2.361, 2.398, 2.323, 2.388, 2.381, 2.513, 2.418, 2.447, 2.397, 2.431, 2.251, 2.224, 2.009, 1.892, 1.849, 1.715, 1.675, 1.653, 1.660, 1.601, 1.477, 1.507, 1.474, 1.441, 1.401, 1.385, 1.357, 1.308, 1.291, 1.278, 1.184, 1.151, 1.144, 1.122, 1.086, 1.095, 1.045, 1.005, 0.981, 0.977, 0.972, 0.903, 0.933, 0.000, 0.000, 1.018, 0.874, 0.785, 0.804, 0.805, 0.780, 0.759, 0.781, 0.767, 0.766, 0.749, 0.764, 0.707, 0.735, 0.698, 0.679, 0.692, 0.699, 0.646, 0.684, 0.618,0.672};
  Double_t  g1lcroserr[81]={0.072, 0.074, 0.067, 0.081, 0.062, 0.097, 0.080, 0.103, 0.062, 0.057, 0.053, 0.045, 0.071, 0.046, 0.066, 0.057, 0.045, 0.044, 0.038, 0.051, 0.036, 0.035, 0.036, 0.034, 0.032, 0.030, 0.027, 0.061, 0.059, 0.044, 0.040, 0.050, 0.049, 0.054, 0.030, 0.041, 0.045, 0.062, 0.047, 0.051, 0.050, 0.061, 0.048, 0.059, 0.052, 0.049, 0.049, 0.042, 0.039, 0.034, 0.030, 0.043, 0.029, 0.037, 0.028, 0.046, 0.032, 0.000, 0.000, 0.101, 0.028, 0.030, 0.028, 0.034, 0.033, 0.035, 0.031, 0.032, 0.037, 0.035, 0.050, 0.029, 0.053, 0.034, 0.045, 0.032, 0.028, 0.038, 0.034, 0.044,0.034};
  Double_t  g1scros[81]={0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.610, 0.661, 0.988, 1.064, 1.148, 1.265, 1.441, 1.617, 1.805, 2.054, 2.112, 2.427, 2.327, 2.542, 2.380, 2.205, 2.136, 2.099, 1.932, 1.864, 1.690, 1.671, 1.617, 1.585, 1.512, 1.492, 1.561, 1.485, 1.446, 1.448, 1.326, 1.393, 1.285, 1.316, 1.230, 1.145, 1.139, 1.191, 1.130, 1.079, 1.051, 1.064, 0.994, 1.086, 0.978, 0.946, 0.914, 0.865, 0.919, 0.807, 0.876, 0.000, 0.000, 1.039, 0.808, 0.679, 0.740, 0.739, 0.702, 0.665, 0.693, 0.673, 0.668, 0.613, 0.693, 0.682, 0.753, 0.633, 0.643, 0.653, 0.624, 0.609, 0.597, 0.645,0.603};
  Double_t  g1scroserr[81]={0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.042, 0.058, 0.041, 0.044, 0.071, 0.064, 0.072, 0.079, 0.106, 0.102, 0.065, 0.059, 0.062, 0.147, 0.122, 0.087, 0.053, 0.060, 0.069, 0.049, 0.055, 0.040, 0.043, 0.041, 0.025, 0.028, 0.036, 0.031, 0.031, 0.031, 0.027, 0.040, 0.030, 0.032, 0.028, 0.030, 0.028, 0.033, 0.036, 0.034, 0.032, 0.030, 0.027, 0.032, 0.029, 0.028, 0.028, 0.026, 0.032, 0.029, 0.034, 0.000, 0.000, 0.103, 0.041, 0.036, 0.037, 0.039, 0.044, 0.052, 0.038, 0.036, 0.040, 0.040, 0.032, 0.036, 0.047, 0.047, 0.049, 0.039, 0.054, 0.047, 0.039, 0.035,0.035};

  Double_t cros[19]={0.628443, 0.656835, 0.46707, 0.456805, 0.327353, 0.356056, 0.329173, 0.306172, 0.33644, 0.31985, 0.281502, 0.297406, 0.255473, 0.269075, 0.286556, 0.22822, 0.231085, 0.261197, 0.233006};
  Double_t croserr[19]={0.0520223, 0.044252, 0.046071, 0.0557869, 0.0292612, 0.0315783, 0.0343993, 0.0278336, 0.0355856, 0.0345357, 0.0323299, 0.0211578, 0.0210267, 0.0201891, 0.0209937, 0.0199824, 0.0169385, 0.0193005, 0.0204372};
  Double_t mp=0.938272;
  Int_t g1bins=81;
  Int_t sigbins=23;
  Double_t g1estep;
  for(i=0;i<bins;i++){
    beam[i]=2.0+i*estep;
    beamerr[i]=estep/2.0;
    w[i]=sqrt((mp+beam[i])**2-beam[i]**2);
    werr[i]=mp*beamerr[i]/w[i];
    
  }
  for(i=0;i<sigbins;i++){
    sigbeam[i]=1.6+i*estep;
    sigbeamerr[i]=estep/2.0;
    sigw[i]=sqrt((mp+sigbeam[i])**2-sigbeam[i]**2);
    sigwerr[i]=mp*sigbeamerr[i]/sigw[i];
    sigcroserr[i]=sqrt(sigcrosstat[i]**2+(0.15*sigcros[i])**2);
  }
  Int_t ii;
 for(i=0;i<g1bins;i++){
   ii=i-1;
   if(i==0) {
     g1estep=g1beam[1]-g1beam[0];
   }
   else{
          g1estep=g1beam[ii]-g1beam[i];

   }
    g1beamerr[i]=g1estep/2.0;
    g1w[i]=sqrt((mp+g1beam[i])**2-g1beam[i]**2);
    g1werr[i]=mp*g1beamerr[i]/g1w[i];
    
  }
 Int_t sigmabins=g1bins-6;
 TGraphErrors *grwkstar=new TGraphErrors(bins, w, cros, werr, croserr);
 TGraphErrors *grwsigma=new TGraphErrors(sigbins, sigw, sigcros, sigwerr, sigcroserr);
 TGraphErrors *grwg1lam=new TGraphErrors(g1bins, g1w, g1lcros, g1werr, g1lcroserr);
 TGraphErrors *grwg1sig=new TGraphErrors(sigmabins, &g1w[6], &g1scros[6], &g1werr[6], &g1scroserr[6]);

 TGraphErrors *grkstar=new TGraphErrors(bins, beam, cros, beamerr, croserr);
 TGraphErrors *grsigma=new TGraphErrors(sigbins, sigbeam, sigcros, sigbeamerr, sigcroserr);
 TGraphErrors *grg1lam=new TGraphErrors(g1bins, g1beam, g1lcros, g1beamerr, g1lcroserr);
 TGraphErrors *grg1sig=new TGraphErrors(sigmabins, &g1beam[6], &g1scros[6], &g1beamerr[6], &g1scroserr[6]);
 grkstar->SetMarkerStyle(20);
 grkstar->SetMarkerColor(2);
 grkstar->SetMarkerSize(1);
 grsigma->SetMarkerStyle(29);
 grsigma->SetMarkerColor(30);
 grsigma->SetMarkerSize(1);
 grg1lam->SetMarkerStyle(22);
 grg1lam->SetMarkerColor(4);
 grg1lam->SetMarkerSize(1);
 grg1sig->SetMarkerStyle(25);
 grg1sig->SetMarkerColor(6);
 grg1sig->SetMarkerSize(1);

 grwkstar->SetMarkerStyle(20);
 grwkstar->SetMarkerColor(2);
 grwkstar->SetMarkerSize(1);
 grwsigma->SetMarkerStyle(29);
 grwsigma->SetMarkerColor(30);
 grwsigma->SetMarkerSize(1);
 grwg1lam->SetMarkerStyle(22);
 grwg1lam->SetMarkerColor(4);
 grwg1lam->SetMarkerSize(1);
 grwg1sig->SetMarkerStyle(25);
 grwg1sig->SetMarkerColor(6);
 grwg1sig->SetMarkerSize(1);

 TMultiGraph *grbeam=new TMultiGraph();
 grbeam->Add(grkstar);
 grbeam->Add(grsigma);
 grbeam->Add(grg1lam);
 grbeam->Add(grg1sig);
 TLegend *legbeam=new TLegend(0.4,0.8,0.9,0.9);
 legbeam->AddEntry(grkstar, "#sigma(#gamma p#rightarrow K^{*+}#Lambda), CLAS", "p");
 legbeam->AddEntry(grsigma, "#sigma(#gamma p#rightarrow K^{+}#Sigma^{0}(1385)), CLAS", "p");
 legbeam->AddEntry(grg1lam, "#sigma(#gamma p#rightarrow K^{+}#Lambda), Bradford et al, CLAS", "p");
 legbeam->AddEntry(grg1sig, "#sigma(#gamma p#rightarrow K^{+}#Sigma^{0}), Bradford et al, CLAS", "p");
 TMultiGraph *grw=new TMultiGraph();
 grw->Add(grwkstar);
 //grw->Add(grwsigma);
 grw->Add(grwg1lam);
 grw->Add(grwg1sig);
 TLegend *legw=new TLegend(0.4,0.8,0.9,0.9);
 legw->AddEntry(grwkstar, "#sigma(#gamma p#rightarrow K^{*+}#Lambda), CLAS", "p");
 //legw->AddEntry(grwsigma, "#sigma(#gamma p#rightarrow K^{+}#Sigma^{0}(1385)), CLAS", "p");
 legw->AddEntry(grwg1lam, "#sigma(#gamma p#rightarrow K^{+}#Lambda), Bradford et al, CLAS", "p");
 legw->AddEntry(grwg1sig, "#sigma(#gamma p#rightarrow K^{+}#Sigma^{0}), Bradford et al, CLAS", "p");

 char psfile[30];
 sprintf(psfile, "comcros.ps");
 TPostScript *ps = new TPostScript(psfile, 111);
 ps->NewPage();
 TCanvas *c1=new TCanvas("c1", "",20,20,600,800);
 c1->Divide(1,2);
 c1->cd(1);
 grbeam->Draw("AP");
 grbeam->GetHistogram()->SetYTitle("#sigma (#mu b)");
 grbeam->GetHistogram()->SetXTitle("E_{#gamma} (GeV)");
 grbeam->Draw("AP");
 legbeam->Draw();
 c1->cd(2);
 grw->Draw("AP");
 grw->GetHistogram()->SetYTitle("#sigma (#mu b)");
 grw->GetHistogram()->SetXTitle("w (GeV)");
 grw->Draw("AP");
 legw->Draw();
 ps->Close();

}
