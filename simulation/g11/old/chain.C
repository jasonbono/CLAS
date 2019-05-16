
#include <stdio.h>
#include <iostream.h>
void chain(){



 TChain *simchain=new TChain("simchain");
 for (Int_t l=2; l<3; l++) {
   TString SL;
 SL.Form("./rootfiles/eg%d.94_3.04.v18xi.root/g112kppim",l);
 simchain->Add(SL);
   
 simchain->Add("./rootfiles/eg3.94_3.04.v18xi.root/g112kppim");
   //cout <<l<<endl; 
}  
simchain->Draw("run");
//f3Chain->Merge("temp.root")

}
