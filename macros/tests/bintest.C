// to test binning

void bintest(){


  Float_t high=4;
  Float_t low=0;
  Float_t bin=4;
  TH1F *hist_1=new TH1F("hist_1","",bin,low,high);
    hist_1.Fill(0,1);
hist_1.Fill(1,2);
hist_1.Fill(2,3);
hist_1.Fill(3,4);
 hist_1.Fill(4,5);
  hist_1.Draw();


  // from lei's code
for( Int_t j=0;j<jmax;j++){
       k=j+1;
       c2->cd(k);
       tlow=-1+j*tstep;
       thigh=-1+(j+1)*tstep;
       tmean=(tlow+thigh)/2;
       if(thigh<=0){
         h[i][j]=new TH1F(Form("h%d_%d",i,j),Form("E_{#gamma}:%5.4f to %5.4f, Cos*(#theta_{K^{*+}}):%3.2f to %3.2f",elow, ehigh, tlow,thigh),40,0.6,1.5);}
       else {
         h[i][j]=new TH1F(Form("h%d_%d",i,j),Form("E_{#gamma}:%5.4f to %5.4f, Cos*(#theta_{K^{*+}}):%3.2f to %3.2f",elow, ehigh, tlow,thigh),40,0.6,1.5);
       }

xxx->Draw(Form("mmkpkp>>h%d_%d",i,j), Form("abs(scv-stv)<1&&beam<%f&&beam>%f&&tpkp1<%f&&tpkp1>%f&&abs(vz+10)<21",ehigh, elow, thigh, tlow));
xxx->Draw(Form("conmkppi0>>h%d_%d",i,j), Form("beam<%f&&beam>%f&&(-lamcmtheta)<%f&&(-lamcmtheta)>%f",ehigh, elow, thigh, tlow), "E");



TF1 *backFcn = new TF1(Form("backFcn_%i", try), background,low,high,6);

}
