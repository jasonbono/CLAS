

void looptest(){
  TH1F *h[10];
  Int_t d=4;
  for ( Int_t i=0;i<10;i++){
h[i]=new TH1F(Form("h_%d", i),"",10,0,10);    

  }

  h[4]->Draw();

}
