/* 

Date: April 10 2012  

Author: Jason Bono

Purpose: To show the polarization angles of the pion and masses of the particles that were generated from genr8. this root file was 
converted from ascii format to .root format.

*/

#include <Riostream.h>
#include <TMath.h>
#include "TMath.h"
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TRotation.h>
#include <TLorentzRotation.h>
#include <assert.h>
gSystem.Load("libPhysics.so");


void ShowRootFile()
{

 



	TFile *f = TFile::Open("/Users/Bono/clas/simulation/g12/myXi/genr8/ascii2root/myXi_100k.root","UPDATE");  
	TTree *newt = (TTree*)f->Get("FourVecTree");	

	TCanvas *cmass=new TCanvas("cmass","",1200,800);
	TH1F *hmkp1=new TH1F("hmkp1","mass of kp1", 400, 0.493, 0.4945);
	TH1F *hmkp2=new TH1F("hmkp2","mass of kp2", 400, 0.493, 0.4945);
	TH1F *hmpim=new TH1F("hmpim","mass of pion", 400, 0.138, 0.141);

	cmass->Divide(2,2);
	cmass->cd(1);
	newt->Draw("mkp1>>hmkp1");
	cmass->cd(2);
	newt->Draw("mkp2>>hmkp2");
	cmass->cd(3);
	newt->Draw("mpim>>hmpim");



	TCanvas *cangles=new TCanvas("cangles","",1200,800);
	TH1F *hpix=new TH1F("hpix","pion angle with x axis",100,-1.1,1.1);
	TH1F *hpiy=new TH1F("hpiy","pion angle with y axis",100,-1.1,1.1);	
	TH1F *hpiz=new TH1F("hpiz","pion angle with z axis",100,-1.1,1.1);
	//hpix->

	cangles->Divide(2,2);
	cangles->cd(1);
	newt->Draw("mr_COS_pi_x>>hpix");
	cangles->cd(2);
	newt->Draw("mr_COS_pi_y>>hpiy");
	cangles->cd(3);
	newt->Draw("mr_COS_pi_z>>hpiz");
	



	TCanvas *cmm=new TCanvas("cmm","",1200,800);
	cmm->Divide(2,0);
	cmm->cd(1);
	newt->Draw("mmkpkp");
	cmm->cd(2);
	newt->Draw("mmkpkppim");
	
	







}