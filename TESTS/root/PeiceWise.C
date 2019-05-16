void PeiceWise() {
   
   TF1 *f1 = new TF1("f1", "(x<45)*(1*(x - 2)/(x - 3 + 4)) + (x>45)*x", 11, 65);

   TH1F *h1 = new TH1F("h1","h1",100,11,65);
   double data;
   for (int i = 0; i < 10000; i++) {
      data = f1->GetRandom();
      h1->Fill(data);
   }
   h1->Draw();
}