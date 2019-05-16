#include <iostream>
using namespace std;

const int nSeries = 3; //n column
const int nPoints = 3; //n row in data file
struct DataStruct {
    Float_t x[nPoints];
    Float_t N[nSeries][nPoints];
    Float_t Nerr[nSeries][nPoints];
    
};


const Int_t colorsLei[5] = {1, 2, 4, 6, 8};
const Int_t styleLei[5] = {22, 21, 20, 23, 33};

void jason(){
    DataStruct nsfStruct;
    ReadFile(nsfStruct,"./txt/Ebins.txt");
	//ReadFile(nsfStruct,"./txt/Xibins.txt");
    
    Plot(nsfStruct,"E_{#gamma}","Polarization");
	//Plot(nsfStruct,"#Xi^{-} Angle","Polarization");

}

void ReadFile(DataStruct & aStruct, TString fileName) {
    ifstream str(fileName.Data());
    
    Float_t temp = 0.0;
    for (Int_t i = 0; i < nPoints; i++) {
        str >> aStruct.x[i];  // read the energy bin value
        for (Int_t j = 0; j < nSeries; j++) {
            str >> aStruct.N[j][i] >> temp;
            aStruct.Nerr[j][i] = fabs(temp);
            // cout << temp << " " << fabs(temp) <<endl;
            //cout << "check: " << aStruct.Nerr[i][j] << " calc: " << sqrt(aStruct.N[i][j]) << endl;
            //aStruct.x[i][j] = -0.9 + (0.2*j);
            //cout << i << " " << j << " " << aStruct.N[i][j] << endl;
        }
    }
    str.close();
}

void Plot(DataStruct & aStruct, TString xTitle, TString yTitle) {
    TGraphErrors* gr[nSeries];
    TCanvas* can = new TCanvas("can", "canvas", 1200, 1000);
    //can->Divide(2, 3);
    
    gStyle->SetTitle(0);
    
    TLegend* leg = new TLegend(.7, .7, .9, .9); //top right
    //TLegend* leg = new TLegend(.4, .6, .7, .9); // middle
    //TLegend* leg = new TLegend(.2, .7, .5, .9);//top left
        
    leg->SetFillStyle(0);
    leg->SetTextFont(132);
        
    for (Int_t i = 0; i < nSeries; i++) {
        //cout << "begin point:[" << i << "]" << endl:
        gr[i] = new TGraphErrors(nPoints, aStruct.x, aStruct.N[i], 0, aStruct.Nerr[i]);
        
        //can->cd(i+1);
        gPad->SetMargin(.15, .1, .15, .1);
        gr[i]->SetMarkerSize(1.5);
        gr[i]->SetMarkerColor(colorsLei[i]);
        gr[i]->SetMarkerStyle(21);
        gr[i]->GetXaxis()->SetTitle(xTitle.Data());
        gr[i]->GetXaxis()->CenterTitle();
        gr[i]->GetYaxis()->SetTitle(yTitle.Data());
        gr[i]->GetYaxis()->CenterTitle();
        gr[i]->SetTitle();
        gr[i]->GetYaxis()->SetTitleOffset(1.8);
        gr[i]->GetYaxis()->SetRangeUser(-3, 3);
        TString opt = (i == 0) ? "AP" : "Psame";
        gr[i]->Draw(opt.Data());
        gPad->Update();
        
        //TString names[3] = {"C_{x}","p","C_{z}"};
        leg->AddEntry(gr[i], (i==0)?"C_{x}":(i==1)?"P":"C_{z}", "p");
        //cout<<"end point:["<<i<<"]"<<endl:
    }
    
    leg->Draw("same");
    gPad->Update();
    
}
