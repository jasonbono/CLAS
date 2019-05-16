

//here is some old stuff, not needed but kept for reference
//#include "/Users/Bono/clas/myDefinitions/EXiBins.h"
//#include "/Users/Bono/clas/myDefinitions/EXiBins.h"
///Users/Bono/clas/myDefinitions/Hypersphere.h // this currently has 4-sigma cuts


//choose the file below based on which binning scheem you want to obtain a corection for
//#include "/Users/Bono/clas/macros2/Asymmetry/Binning/DataEXiBins_3and3.h"
#include "/Users/Bono/clas/macros2/Asymmetry/Binning/DataEXiBins_3x3.h"

//------Define Global Varibles---------
///edit theese 5 quantities if changing widths
float sigmaA = 0.0113;
float sigmaB = 0.0107;
float sigmaC = 0.0031;
float sigmaD = 0.0030;
float depth = 3;

//theese are fixed
float widthA = depth*sigmaA;
float widthB = depth*sigmaB;
float widthC = depth*sigmaC;
float widthD = depth*sigmaD;
float MASS_Xi = 1.32131;
float MASS_Lambda = 1.115683;




TFile *fDataB = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v16/hadded/2kppim-v16_Basic.root");
TTree *tDataB = (TTree*)fDataB->Get("v16");

TFile *ftemp = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v16/hadded/2kppim-v16_Basic.root");
TTree *ttemp = (TTree*)ftemp->Get("v16");





void DilutionForPaper()
{

    
    //*
    //setup the style
    StyleUp();
    //get the cuts
    TCut CutABCD,CutABCD_sb,CutABCD_sb2;
    GetHyperSphereCut(CutABCD);
    GetHyperSphereSideBand(CutABCD_sb);
    GetHyperSphereSideBand2(CutABCD_sb2);
    //get the hists
    GetHists();

    //int bintype = 0; //0=E bins, 1=Xi bins
    //int i=2; //bin number

    
    const char* binstring[Nb][Nc];
    float P[Nb][Nc] = {};
    float eP[Nb][Nc] = {};
    float Cx[Nb][Nc] = {};
    float eCx[Nb][Nc] = {};
    float Cz[Nb][Nc] = {};
    float eCz[Nb][Nc] = {};
    float new_P[Nb][Nc] = {};
    float new_eP[Nb][Nc] = {};
    float new_Cx[Nb][Nc] = {};
    float new_eCx[Nb][Nc] = {};
    float new_Cz[Nb][Nc] = {};
    float new_eCz[Nb][Nc] = {};
    
    //also handel the systematic uncertainty
    float sysABS_P = sqrt(pow(0.008,2) + pow(0.02,2));
    float sysREL_P = 0.026;
    float sysABS_Cx = sqrt(pow(0.114,2) + pow(0.005,2) + pow(0.005,2));
    float sysREL_Cx = sqrt(pow(0.026,2) + pow(0.03,2));
    float sysABS_Cz = sqrt( pow(0.011,2) + pow(0.048,2) + pow(0.02,2));
    float sysREL_Cz = sqrt(pow(0.026,2) + pow(0.03,2));

    float TotSys_P[Nb][Nc] = {};
    float TotSys_Cx[Nb][Nc] = {};
    float TotSys_Cz[Nb][Nc] = {};
    
    float TotErr_P[Nb][Nc] = {};
    float TotErr_Cx[Nb][Nc] = {};
    float TotErr_Cz[Nb][Nc] = {};
    
    
    
    if(Nb == 2){
        P[0][0] = -0.010;
        P[0][1] = -0.079;
        P[0][2] = 0.005;
        P[1][0] = -0.039;
        P[1][1] = 0.130;
        P[1][2] = -0.168;
        
        eP[0][0] = 0.106;
        eP[0][1] = 0.107;
        eP[0][2] = 0.105;
        eP[1][0] = 0.107;
        eP[1][1] = 0.107;
        eP[1][2] = 0.105;
        
        Cx[0][0] = 0.188;
        Cx[0][1] = -0.074;
        Cx[0][2] = -0.018;
        Cx[1][0] = -0.184;
        Cx[1][1] = 0.322;
        Cx[1][2] = 0.010;
        
        eCx[0][0] = 0.354;
        eCx[0][1] = 0.305;
        eCx[0][2] = 0.272;
        eCx[1][0] = 0.290;
        eCx[1][1] = 0.304;
        eCx[1][2] = 0.344;
        
        Cz[0][0] = 0.470;
        Cz[0][1] = 0.589;
        Cz[0][2] = 0.001;
        Cz[1][0] = 0.456;
        Cz[1][1] = 0.431;
        Cz[1][2] = 0.112;
        
        eCz[0][0] = 0.313;
        eCz[0][1] = 0.253;
        eCz[0][2] = 0.217;
        eCz[1][0] = 0.282;
        eCz[1][1] = 0.246;
        eCz[1][2] = 0.257;

        binstring[0][0] = "beam > 2.800000 && beam < 3.812500 && Xcmtheta > -1.000000 && Xcmtheta < 1.000000 ";
        binstring[0][1] = "beam > 3.812500 && beam < 4.433500 && Xcmtheta > -1.000000 && Xcmtheta < 1.000000 ";
        binstring[0][2] = "beam > 4.433500 && beam < 5.500000 && Xcmtheta > -1.000000 && Xcmtheta < 1.000000 ";
        binstring[1][0] = "beam > 2.800000 && beam < 5.500000 && Xcmtheta > -1.000000 && Xcmtheta < -0.610000 ";
        binstring[1][1] = "beam > 2.800000 && beam < 5.500000 && Xcmtheta > -0.610000 && Xcmtheta < -0.190000 ";
        binstring[1][2] = "beam > 2.800000 && beam < 5.500000 && Xcmtheta > -0.190000 && Xcmtheta < 1.000000 ";
        
    }
    else if(Nb == 3){
        P[0][0] = -0.078;
        P[0][1] = 0.138;
        P[0][2] = -0.090;
        P[1][0] = -0.131;
        P[1][1] = 0.139;
        P[1][2] = -0.233;
        P[2][0] = 0.030;
        P[2][1] = 0.085;
        P[2][2] = -0.099;
        
        eP[0][0] = 0.184;
        eP[0][1] = 0.183;
        eP[0][2] = 0.181;
        eP[1][0] = 0.184;
        eP[1][1] = 0.189;
        eP[1][2] = 0.184;
        eP[2][0] = 0.182;
        eP[2][1] = 0.183;
        eP[2][2] = 0.182;
        
        binstring[0][0] = "beam > 2.800000 && beam < 3.812500 && Xcmtheta > -1.000000 && Xcmtheta < -0.630000 " ;
        binstring[0][1] = "beam > 2.800000 && beam < 3.812500 && Xcmtheta > -0.630000 && Xcmtheta < -0.230000 " ;
        binstring[0][2] = "beam > 2.800000 && beam < 3.812500 && Xcmtheta > -0.230000 && Xcmtheta < 1.000000 " ;
        binstring[1][0] = "beam > 3.812500 && beam < 4.433500 && Xcmtheta > -1.000000 && Xcmtheta < -0.610000 " ;
        binstring[1][1] = "beam > 3.812500 && beam < 4.433500 && Xcmtheta > -0.610000 && Xcmtheta < -0.190000 " ;
        binstring[1][2] = "beam > 3.812500 && beam < 4.433500 && Xcmtheta > -0.190000 && Xcmtheta < 1.000000 " ;
        binstring[2][0] = "beam > 4.433500 && beam < 5.500000 && Xcmtheta > -1.000000 && Xcmtheta < -0.570000 " ;
        binstring[2][1] = "beam > 4.433500 && beam < 5.500000 && Xcmtheta > -0.570000 && Xcmtheta < -0.110000 " ;
        binstring[2][2] = "beam > 4.433500 && beam < 5.500000 && Xcmtheta > -0.110000 && Xcmtheta < 1.000000 " ;
        
    }
    
    
    
    ofstream Pfile,Cxfile,Czfile;
    if(Nb == 2){

        Pfile.open ("./output/finalP_6bins.txt",std::ios::trunc);
        Cxfile.open ("./output/finalCx_6bins.txt",std::ios::trunc);
        Czfile.open ("./output/finalCz_6bins.txt",std::ios::trunc);
    }
    else if(Nb == 3){
        Pfile.open ("./output/finalP_9bins.txt",std::ios::trunc);
    }
    
        
//    Pfile << "Pfile stuff.\n";
//    Cxfile << "Cxfile stuff.\n";
//    Czfile << "Czfile stuff.\n";

    
    for (int bintype = 0; bintype < Nb; bintype++) {
        for (int i = 0; i < Nc; i++){
    
    //draw all four plots
    TCanvas *c=new TCanvas("c","c",1000,800);
    c->Divide(2,2);
    c->cd(1);
    tDataB->Draw("mmkpkp >> hA",CutABCD&&EXibin[bintype][i]);
    c->cd(2);
    tDataB->Draw("mmkpkppim >> hB",CutABCD&&EXibin[bintype][i]);
    c->cd(3);
    tDataB->Draw("mlampim >> hC",CutABCD&&EXibin[bintype][i]);
    c->cd(4);
    tDataB->Draw("mcasmMpim >> hD",CutABCD&&EXibin[bintype][i]);
    
    
    //side band
    c->cd(1);
    tDataB->Draw("mmkpkp >> hA_sb",CutABCD_sb&&EXibin[bintype][i],"SAME");
    c->cd(2);
    tDataB->Draw("mmkpkppim >> hB_sb",CutABCD_sb&&EXibin[bintype][i],"SAME");
    c->cd(3);
    tDataB->Draw("mlampim >> hC_sb",CutABCD_sb&&EXibin[bintype][i],"SAME");
    c->cd(4);
    tDataB->Draw("mcasmMpim >> hD_sb",CutABCD_sb&&EXibin[bintype][i],"SAME");
    
    //side band
    c->cd(1);
    tDataB->Draw("mmkpkp >> hA_sb2",CutABCD_sb2&&EXibin[bintype][i],"SAME");
    c->cd(2);
    tDataB->Draw("mmkpkppim >> hB_sb2",CutABCD_sb2&&EXibin[bintype][i],"SAME");
    c->cd(3);
    tDataB->Draw("mlampim >> hC_sb2",CutABCD_sb2&&EXibin[bintype][i],"SAME");
    c->cd(4);
    tDataB->Draw("mcasmMpim >> hD_sb2",CutABCD_sb2&&EXibin[bintype][i],"SAME");
    
    float Num = hD->GetEntries();
    float eNum = sqrt(Num);
    float NumSB = hD_sb->GetEntries();
    float eNumSB = sqrt(NumSB);
    float Sum = Num+NumSB;
    float eSum = sqrt(Sum);
    float BG = NumSB/(Sum);
    float eBG = BG*sqrt(std::pow(eNumSB/NumSB,2) + std::pow(eSum/Sum,2));
//            float eBG = 9;
    float DilFac = 1 - BG; //the dilution factor is the amount by which the results were diluted by the background, to correct, divide this number
    float eDilFac = eBG;
            
    cout << binstring[bintype][i] <<endl;
    cout << "bin type = " << bintype <<", bin number = " << i <<endl;
    cout << "number = " << Num << ", sideband = " << NumSB <<endl;
    cout <<"Bacground Fraction  = " << BG << " "<< " +/- " << eBG <<endl;
    cout <<"Dilution Factor  = " << DilFac << " "<< " +/- " << eDilFac <<endl;


            
    
    //fix the polarization and error
    new_P[bintype][i] = P[bintype][i]/DilFac;
    new_eP[bintype][i] = sqrt(eP[bintype][i]/DilFac*eP[bintype][i]/DilFac + fabs(P[bintype][i])*eDilFac*fabs(P[bintype][i])*eDilFac);
    TotSys_P[bintype][i] = sqrt(pow(new_P[bintype][i]*sysREL_P,2) + pow(sysABS_P,2));
    TotErr_P[bintype][i] = sqrt(pow(TotSys_P[bintype][i],2) + pow(new_eP[bintype][i],2));
    cout << "Old P = " << P[bintype][i] << ", New P = " << new_P[bintype][i] <<endl;
    cout << "Old eP = " << eP[bintype][i] << ", New eP = " << eP[bintype][i]/DilFac << " + " << fabs(P[bintype][i])*eDilFac
    << " = " << new_eP[bintype][i] <<endl;
    
    new_Cx[bintype][i] = Cx[bintype][i]/DilFac;
    new_eCx[bintype][i] = sqrt(eCx[bintype][i]/DilFac*eCx[bintype][i]/DilFac + fabs(Cx[bintype][i])*eDilFac*fabs(Cx[bintype][i])*eDilFac);
    TotSys_Cx[bintype][i] = sqrt(pow(new_Cx[bintype][i]*sysREL_Cx,2) + pow(sysABS_Cx,2));
    TotErr_Cx[bintype][i] = sqrt(pow(TotSys_Cx[bintype][i],2) + pow(new_eCx[bintype][i],2));
    cout << "Old Cx = " << Cx[bintype][i] << ", New Cx = " << new_Cx[bintype][i] <<endl;
    cout << "Old eCx = " << eCx[bintype][i] << ", New eCx = " << eCx[bintype][i]/DilFac << " + " << fabs(Cx[bintype][i])*eDilFac
    << " = " << new_eCx[bintype][i] <<endl;
            
            
    new_Cz[bintype][i] = Cz[bintype][i]/DilFac;
    new_eCz[bintype][i] = sqrt(eCz[bintype][i]/DilFac*eCz[bintype][i]/DilFac + fabs(Cz[bintype][i])*eDilFac*fabs(Cz[bintype][i])*eDilFac);
            TotSys_Cz[bintype][i] = sqrt(pow(new_Cz[bintype][i]*sysREL_Cz,2) + pow(sysABS_Cz,2));
            TotErr_Cz[bintype][i] = sqrt(pow(TotSys_Cz[bintype][i],2) + pow(new_eCz[bintype][i],2));
    cout << "Old Cz = " << Cz[bintype][i] << ", New Cz = " << new_Cz[bintype][i] <<endl;
    cout << "Old eCz = " << eCz[bintype][i] << ", New eCz = " << eCz[bintype][i]/DilFac << " + " << fabs(Cz[bintype][i])*eDilFac
    << " = " << new_eCz[bintype][i] <<endl;
            
    cout <<"--------------------------------------"<<endl;
           
            
        
            Pfile << binstring[bintype][i]  << endl;
            Pfile <<"Dilution Factor  = " << DilFac <<" +/- " << eDilFac <<endl;
            Pfile << "Old P = " << P[bintype][i] << " +/- " << eP[bintype][i] <<endl;
            Pfile << "New P = " << new_P[bintype][i] << " +/- (" << eP[bintype][i]/DilFac << " + " << fabs(P[bintype][i])*eDilFac <<  " = " << new_eP[bintype][i] << " )"<<endl;
            Pfile << "Total Systematic = " << TotSys_P[bintype][i] << ", Total Statistical = " << new_eP[bintype][i] << ", Total Error = " << TotErr_P[bintype][i] <<endl<<endl;
            if(Nb == 2){
            Cxfile << binstring[bintype][i]  << endl;
            Cxfile <<"Dilution Factor  = " << DilFac <<" +/- " << eDilFac <<endl;
            Cxfile << "Old Cx = " << Cx[bintype][i] << " +/- " << eCx[bintype][i] <<endl;
            Cxfile << "New Cx = " << new_Cx[bintype][i] << " +/- (" << eCx[bintype][i]/DilFac << " + " << fabs(Cx[bintype][i])*eDilFac <<  " = " << new_eCx[bintype][i] << " )"<<endl;
            Cxfile << "Total Systematic = " << TotSys_Cx[bintype][i] << ", Total Statistical = " << new_eCx[bintype][i] << ", Total Error = " << TotErr_Cx[bintype][i] <<endl<<endl;
            
            Czfile << binstring[bintype][i]  << endl;
            Czfile <<"Dilution Factor  = " << DilFac <<" +/- " << eDilFac <<endl;
            Czfile << "Old Cz = " << Cz[bintype][i] << " +/- " << eCz[bintype][i] <<endl;
            Czfile << "New Cz = " << new_Cz[bintype][i] << " +/- (" << eCz[bintype][i]/DilFac << " + " << fabs(Cz[bintype][i])*eDilFac <<  " = " << new_eCz[bintype][i] << " )"<<endl;
            Czfile << "Total Systematic = " << TotSys_Cz[bintype][i] << ", Total Statistical = " << new_eCz[bintype][i] << ", Total Error = " << TotErr_Cz[bintype][i] <<endl<<endl;

        }

            
    
    }
}
    
    if(Nb == 2){
        Pfile.close();
        Cxfile.close();
        Czfile.close();
    }
    else if(Nb == 3){
        Pfile.close();
    }



    
}




























void StyleUp()
{
    gStyle->SetTitleXOffset(0.5);
    gStyle->SetTitleYOffset(0.65);
    gStyle->SetTitleSize(0.08);
    gStyle->SetTitleYSize(0.07);
    gStyle->SetPadTopMargin(0.02);
    gStyle->SetCanvasBorderMode(1);
    gStyle->SetPadBorderMode(1);
    gStyle->SetFrameBorderMode(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetFrameFillColor(0);
    gStyle->SetFrameFillStyle(1001);
    gStyle->SetFillStyle(0);
    gStyle->SetOptStat(1);
}



//------------------------
void GetHyperSphereCut(TCut &CutABCD)
{
    
    CutABCD = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) < 1"
                   ,MASS_Xi,MASS_Xi,widthA,widthA,MASS_Lambda,MASS_Lambda,widthB,widthB,MASS_Xi,MASS_Xi,widthC,widthC,MASS_Lambda,MASS_Lambda,widthD,widthD);
    
}



void GetHyperSphereSideBand(TCut &CutABCD_sb)
{
    TCut cond1,cond2;
    
    
    cond1 = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) > 1"
                 ,MASS_Xi,MASS_Xi,widthA,widthA,MASS_Lambda,MASS_Lambda,widthB,widthB,MASS_Xi,MASS_Xi,widthC,widthC,MASS_Lambda,MASS_Lambda,widthD,widthD);
    
    cond2 = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) < 1.189207"
                 ,MASS_Xi,MASS_Xi,widthA,widthA,MASS_Lambda,MASS_Lambda,widthB,widthB,MASS_Xi,MASS_Xi,widthC,widthC,MASS_Lambda,MASS_Lambda,widthD,widthD);
    
    CutABCD_sb = cond1&&cond2;
}

void GetHyperSphereSideBand2(TCut &CutABCD_sb2)
{
    TCut cond1,cond2;
    
    
    cond1 = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) > 1.189207"
                 ,MASS_Xi,MASS_Xi,widthA,widthA,MASS_Lambda,MASS_Lambda,widthB,widthB,MASS_Xi,MASS_Xi,widthC,widthC,MASS_Lambda,MASS_Lambda,widthD,widthD);
    
    cond2 = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) < 1.316074"
                 ,MASS_Xi,MASS_Xi,widthA,widthA,MASS_Lambda,MASS_Lambda,widthB,widthB,MASS_Xi,MASS_Xi,widthC,widthC,MASS_Lambda,MASS_Lambda,widthD,widthD);
    
    CutABCD_sb2 = cond1&&cond2;
}


//------------------------
void GetHists()
{
    //hist models
    TH1F *hCas=new TH1F("hCas","",100,1.25,1.35);  //160   //480
    hCas->SetMinimum(0);
    hCas->SetFillColor(4);
    TH1F *hLam=new TH1F("hLam","",100,1.05,1.15); //160  //480
    hLam->SetMinimum(0);
    hLam->SetFillColor(4);
    
    //good signal hists
    hA = (TH1F*)hCas->Clone("hA");
    hA->GetYaxis()->SetTitle("Events/1MeV/c^{2}");
    hA->GetXaxis()->SetTitle(" MM(K^{+}K^{+}) (GeV/c^{2})");
    hC = (TH1F*)hCas->Clone("hC");
    hC->GetYaxis()->SetTitle("Events/1MeV/c^{2}");
    hC->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");
    hB = (TH1F*)hLam->Clone("hB");
    hB->GetYaxis()->SetTitle("Events/1MeV/c^{2}");
    hB->GetXaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
    hD = (TH1F*)hLam->Clone("hD");
    hD->GetYaxis()->SetTitle("Events/1MeV/c^{2}");
    hD->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-}) (GeV/c^{2})");
    
    //sideband hists
    hA_sb = (TH1F*)hA->Clone("hA_sb");
    hA_sb->SetMinimum(0);
    hA_sb->SetFillColor(2);
    hC_sb = (TH1F*)hC->Clone("hC_sb");
    hC_sb->SetMinimum(0);
    hC_sb->SetFillColor(2);
    hB_sb = (TH1F*)hB->Clone("hB_sb");
    hB_sb->SetMinimum(0);
    hB_sb->SetFillColor(2);
    hD_sb = (TH1F*)hD->Clone("hD_sb");
    hD_sb->SetMinimum(0);
    hD_sb->SetFillColor(2);
    
    //sideband2 hists
    hA_sb2 = (TH1F*)hA->Clone("hA_sb2");
    hA_sb2->SetMinimum(0);
    hA_sb2->SetFillColor(1);
    hC_sb2 = (TH1F*)hC->Clone("hC_sb2");
    hC_sb2->SetMinimum(0);
    hC_sb2->SetFillColor(1);
    hB_sb2 = (TH1F*)hB->Clone("hB_sb2");
    hB_sb2->SetMinimum(0);
    hB_sb2->SetFillColor(1);
    hD_sb2 = (TH1F*)hD->Clone("hD_sb2");
    hD_sb2->SetMinimum(0);
    hD_sb2->SetFillColor(1);
    
    
    //for fit spectra
    hAfit = (TH1F*)hCas->Clone("hAfit");
    hAfit->GetYaxis()->SetTitle("Events/1MeV/c^{2}");
    hAfit->GetXaxis()->SetTitle(" MM(K^{+}K^{+}) (GeV/c^{2})");
    hCfit = (TH1F*)hCas->Clone("hCfit");
    hCfit->GetYaxis()->SetTitle("Events/1MeV/c^{2}");
    hCfit->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");
    hBfit = (TH1F*)hLam->Clone("hBfit");
    hBfit->GetYaxis()->SetTitle("Events/1MeV/c^{2}");
    hBfit->GetXaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
    hDfit = (TH1F*)hLam->Clone("hDfit");
    hDfit->GetYaxis()->SetTitle("Events/1MeV/c^{2}");
    hDfit->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-}) (GeV/c^{2})");
}







