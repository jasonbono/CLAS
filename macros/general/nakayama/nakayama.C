/*

August 20th
read the ntuple containing nakayamas results

*/

void nakayama() 
{
	TFile *fileKps = TFile::Open("/Users/Bono/clas/theory/nakayama/PRC74-035205/results/analy_K_ps.root");
	TFile *fileXps = TFile::Open("/Users/Bono/clas/theory/nakayama/PRC74-035205/results/analy_X_ps.root");
	TFile *fileKpv = TFile::Open("/Users/Bono/clas/theory/nakayama/PRC74-035205/results/analy_K_pv.root");
	TFile *fileXpv = TFile::Open("/Users/Bono/clas/theory/nakayama/PRC74-035205/results/analy_X_pv.root");
	
	TTree *ntKps = (TTree*)fileKps->Get("ntupleKps");
	TTree *ntXps = (TTree*)fileXps->Get("ntupleXps");
	TTree *ntKpv = (TTree*)fileKpv->Get("ntupleKpv");
	TTree *ntXpv = (TTree*)fileXpv->Get("ntupleXpv");
	
	TCut beam3="beam >= 2.5 && beam < 3.5";
	TCut beam4="beam >= 3.5 && beam < 4.5";
	TCut beam5="beam >= 4.5 && beam <= 5.5";
	
	TCut conf = "kf_prob > 0.10";
	
	
	//====================================DATA========================================
//	TCanvas *cdata=new TCanvas("cdata","data",1500,1000);

	//===================================NAKAYAMA=====================================
	
	//----------------------ps------------------------------------
	TCanvas *cps=new TCanvas("cKps","ps",1500,1000);
	cps->Divide(3,2);
	TLine *line = new TLine(-1,0,1,0);
    line->SetLineColor(kRed);
	//  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ K ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~		
	cps->cd(1);
	TH2F *hKps3=new TH2F("hKps3","hKps3",50,-1,1,50,-1,1);
	ntKps->Draw("analy_cas:theta_K>>hKps3",beam3,"colz");
	line->Draw();
	
	
	cps->cd(2);
	TH2F *hKps4=new TH2F("hKps4","hKps4",50,-1,1,50,-1,1);
	ntKps->Draw("analy_cas:theta_K>>hKps4",beam4,"colz");
	line->Draw();
	
	cps->cd(3);
	TH2F *hKps5=new TH2F("hKps5","hKps5",50,-1,1,50,-1,1);
	ntKps->Draw("analy_cas:theta_K>>hKps5",beam5,"colz");
	line->Draw();	
//  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ X ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~	
	cps->cd(4);
	TH2F *hXps3=new TH2F("hXps3","hXps3",50,-1,1,50,-1,1);
	ntXps->Draw("analy_cas:theta_X>>hXps3",beam3,"colz");
	line->Draw();
	
	cps->cd(5);
	TH2F *hXps4=new TH2F("hXps4","hXps4",50,-1,1,50,-1,1);
	ntXps->Draw("analy_cas:theta_X>>hXps4",beam4,"colz");
	line->Draw();
	
	cps->cd(6);
	TH2F *hXps5=new TH2F("hXps5","hXps5",50,-1,1,50,-1,1);
	ntXps->Draw("analy_cas:theta_X>>hXps5",beam5,"colz");
	line->Draw();
	
	//----------------------pv------------------------------------
	TCanvas *cpv=new TCanvas("cKpv","pv",1500,1000);
	cpv->Divide(3,2);
	//  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ K ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~		
	cpv->cd(1);
	TH2F *hKpv3=new TH2F("hKpv3","hKpv3",50,-1,1,50,-1,1);
	ntKpv->Draw("analy_cas:theta_K>>hKpv3",beam3,"colz");
	line->Draw();
		
	cpv->cd(2);
	TH2F *hKpv4=new TH2F("hKpv4","hKpv4",50,-1,1,50,-1,1);
	ntKpv->Draw("analy_cas:theta_K>>hKpv4",beam4,"colz");
	line->Draw();

	cpv->cd(3);
	TH2F *hKpv5=new TH2F("hKpv5","hKpv5",50,-1,1,50,-1,1);
	ntKpv->Draw("analy_cas:theta_K>>hKpv5",beam5,"colz");
	line->Draw();	
	//  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ X ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~	
	cpv->cd(4);
	TH2F *hXpv3=new TH2F("hXpv3","hXpv3",50,-1,1,50,-1,1);
	ntXpv->Draw("analy_cas:theta_X>>hXpv3",beam3,"colz");
	line->Draw();
	
	cpv->cd(5);
	TH2F *hXpv4=new TH2F("hXpv4","hXpv4",50,-1,1,50,-1,1);
	ntXpv->Draw("analy_cas:theta_X>>hXpv4",beam4,"colz");
	line->Draw();

	cpv->cd(6);
	TH2F *hXpv5=new TH2F("hXpv5","hXpv5",50,-1,1,50,-1,1);
	ntXpv->Draw("analy_cas:theta_X>>hXpv5",beam5,"colz");
	line->Draw();
	

	//=========================================================================




}




