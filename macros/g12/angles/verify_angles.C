//  march 27 2012: this was made to test the angles computed from Addxyz_2.C and v34k.cc are in agreement and are correct



void verify_angles()
{
 
 TFile *f = TFile::Open("~/clas/rootfiles/g12/tiny/v25k_tiny.root");
 TTree *newt = (TTree*)f->Get("v25k");
 

// TFile *f = TFile::Open("~/clas/rootfiles/g12/v34k_00.root","UPDATE");  
// TTree *addedt = (TTree*)f->Get("v34k");






 //=========================the most recent cuts as of nov22========================
 //need to relax a few cuts here after showing lei my overlay plots.
 TCut n="np<2&&npip<1&&nkm<1";
 TCut np="nphoton_nb1<2";
 TCut vcut="abs(vz+90)<30&&sqrt(vx^2+vy^2)<7";  // relaxed this alot to allow for weak decays
 TCut beam="beam>3.3"; //relaxed this from 3.6
 TCut st="abs(stv-scv)<1";
 TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";
 TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<1.1";  // this is relaxed because the slower particle has a lower time resoultion.
 TCut newbasic=n&&np&&vcut&&beam&&st&&tof1&&tof2;

 //theese are best defined in this part of the code to prevent discrepenceys when changing cuts in geometry.
 TCut allbut_vz=n&&np&&"sqrt(vx^2+vy^2)<7"&&beam&&st&&tof1&&tof2;
 TCut allbut_vr=n&&np&&"abs(vz+90)<30"&&beam&&st&&tof1&&tof2;

 TCut casm="abs(mlampim-1.321)<0.013";
 TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
 TCut lamm="abs(mcasmMpim - 1.116)<0.01";
 TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";
 TCut lamm2="abs(mcasmMpim-1.116)<0.02"; //lei used this cut rather than lamm
 //----------------------------------------------------------------------------------







 //==============================================now make sure pion and lambda are back to back============================



 // should be centered about zero for all axis
 TCanvas *c0=new TCanvas("c0","",1200,800);
 c0->Divide(3,0);
 c0->cd(1);
 newt->Draw("mr_COS_pi_x + mr_COS_lam_x");
 c0->cd(2); 
 newt->Draw("mr_COS_pi_y + mr_COS_lam_y");
 c0->cd(3); 
 newt->Draw("mr_COS_pi_z + mr_COS_lam_z");



 // also should be centered about zero
 TCanvas *c1=new TCanvas("c1","",1200,800);
 c1->Divide(3,0);
 c1->cd(1);
 newt->Draw("COSth_pi_x + COSth_lam_x");
 c1->cd(2); 
 newt->Draw("COSth_pi_y + COSth_lam_y");
 c1->cd(3); 
 newt->Draw("COSth_pi_z + COSth_lam_z");





// this should also be zero since i am subracting the same histogram
 TCanvas *c2=new TCanvas("c2","",1200,800);
 c2->Divide(3,0);
 c2->cd(1);
 newt->Draw("COSth_pi_x - mr_COS_lam_x");
 c2->cd(2); 
 newt->Draw("COSth_pi_y - mr_COS_lam_y");
 c2->cd(3); 
 newt->Draw("COSth_pi_z - mr_COS_lam_z");





}