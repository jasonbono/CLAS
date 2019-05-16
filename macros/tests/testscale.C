


void testscale(){

  TH1F *h1=new TH1F("h1","",16,0,100);

  h1->Fill(1,10);
 h1->Fill(2,5);
  h1->Draw();
  Float_t n[10];

  n[0]=h1->GetEntries();
  n[1]=h1->Integral();

  cout << n[0] << endl;
  cout << n[1] << endl;

  h1->Scale(10);
n[2]=h1->Integral("width");
cout << n[2] << endl;


}


