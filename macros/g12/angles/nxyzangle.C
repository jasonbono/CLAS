/*

jan 14: cleaned up macro by puting the n angle stuff witht the xyz angle stuff. also added the hists for the sideband subtraction of the cascade.

jan 13: automated the way that the sideband cuts are defined.

jan 12 2012: 
adding the angle plots from the events in the peak of the cascade spectrum and the sideband of spectrum. going to call all extra variables that dont have 
lambda or cascade in the name title & title2 for lambda and cascade events respectively.
so for example im adding fac2 which comes from the estimated background of the cascadem signal.  i plotted the cascadem the same way as in "g12finalmplot.C"


jan 11 2012:  expanded on nangle.C to include x y and z angles.  this part of the code is written much better than the nangle part.  eventualy i would like to 
clean up the n angle part but for now i will leave it since it works. 


nov 22 2011:
this was made to show the first results of the n angles with side band subtraction.
first will develop it without errors, then will add those later.

the sideband subtraction parameters came from the sigma produced by g12finalmplot.C which is

sigma_cas = 0.0145 -> sig*3=0.0435
sigma_lam = 0.0146 -> sig*3=0.0438 

here will do a cut on both, then sideband subtract on only one at a time.  
for the first go, i will sideband subtract for the lambda.


 */



void nxyzangle(){
//TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");
TTree *newt = (TTree*)f->Get("g12ana_v15");
//TFile *f = TFile::Open("~/clas/rootfiles/g12/large/g12ana_v16_58090.root");
//TTree *newt = (TTree*)f->Get("g12ana_v16");
gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS4.C");

//============= this is from leis_beautify.C which i changed a bit========================
//===============this is the final configuration that he used in his paper========
 printf("Welcome to the ROOT\n");
 gStyle->SetTitleXOffset(0.85);  //this: Xoff
 gStyle->SetTitleYOffset(0.95);  //this:  Yoff
 gStyle->SetTitleSize(0.07);  //this:    Xsize   
 gStyle->SetTitleYSize(0.07); //this     Ysize
 //gStyle->SetLabelFont(72);
 gStyle->SetPadLeftMargin(0.19);   // this: Yaxis 
 gStyle->SetPadBottomMargin(0.15);  // this: Xaxis
 gStyle->SetPadTopMargin(0.02); // was 0.02
 gStyle->SetCanvasBorderMode(1);
 gStyle->SetPadBorderMode(1);
 gStyle->SetFrameBorderMode(0);
 gStyle->SetPadColor(0);
 gStyle->SetCanvasColor(0);
 gStyle->SetFrameFillColor(0);
 gStyle->SetFrameFillStyle(1001);
 gStyle->SetFrameFillStyle(0);
 gStyle->SetFillStyle(0);
 gStyle->SetOptStat(0);
//====================================================================


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


 //++++++++++++++++++++++++++++++the sideband cuts++++++++++++++++++++++++++++++++++
 // note im going to redifine the lambda and cascade cut here to sig*3=0.0435
 // 0.0435 for cascade
 // 0.0438 for lambda
 TCut lam3="abs(sqrt(mm2kpkppim)-1.116)<0.0438";
 TCut cas3="abs(sqrt(mm2kpkp) - 1.321)<0.0435";


 TCut lamSidebands="abs(sqrt(mm2kpkppim)- 1.1817)<0.0219||abs(sqrt(mm2kpkppim)- 1.0503)<0.0219";
 TCut lamTherest="abs(sqrt(mm2kpkppim)- 1.116)>0.0876";


 //and the lambda side bands are defined:
 // 1.116+6*sigma=1.116+0.0876=1.2036
 // 1.116-0.0876=1.0284
 //TCut lamSidebands="abs(sqrt(mm2kpkppim)-1.2036)<0.0438||abs(sqrt(mm2kpkppim)-1.0284)<0.0438";
//want to have normalized side bands so use 1.2036 - 0.01095 & 1.0284 + 0.01095 = 1.19265 & 1.03935
//TCut lamSidebands="abs(sqrt(mm2kpkppim)- 1.19265)<0.0219||abs(sqrt(mm2kpkppim)- 1.03935)<0.0219";

//--------------------------------------------------------------------------------------------






//==========================================angles for sideband subtraction on lambda===================================


//----------------------------------------------------the missing mass--------------------------------


//need bin boundary to be on 1.0722 AND 1.1598 which gives a width of 0.0876.
// want close to 10Mev bins which means binwidth of 0.01 or more:
// so can fit in close 8 bins into the 0.0876 inverval; 0.0876/8=0.01095=BINWIDTH
// now want range to be close to 0.9-1.3: so want:
// 0.9 + x= 1.0722 - n*0.01095 :: try to minimize |x|, with n an integer
// -> x = 0.1722 - n*0.01095 =>  minimizing |x| means finding the n such that |x| is minimum:
// well 0.1722/0.01095 = 15.726...  so can thus choose n=16 and have
//x=  0.1722 - 0.16425 = 0.00795:
// so can bin starting at 0.90795 and have the number of bins close to
// b*0.01095 = 1.3 - 0.9 => b=37 is the closest integer
// now to find the range take xmax= 0.90795 + 37*=0.01095=1.3131
//well 1.1598







//==============================================================================================================================
//=====================================ESTIMATE THE BACKGROUND AND DEFINE SIDEBANDS=============================================
//==============================================================================================================================

	//get the estimated events in the background of the spectrum of LAMBDA using the fitting routine (same plot as in g12finalmplots.C)
	TCanvas *clamfit=new TCanvas("clamfit","",1200,800);
	TH1F *hlamfit=new TH1F("hlamfit","",37, 0.90795,1.3131);
	hlamfit->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hlamfit->GetXaxis()->SetTitle("#Lambda^{0}     MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
	newt->Draw("sqrt(mm2kpkppim)>>hlamfit",newbasic&&casm);

	Double_t myBackground = 0.0;
	Double_t myYield = 0.0;
	Double_t myRms = 0.0;
	Double_t myMean = 0.0;
	fitGAUS4(hlamfit,1,1,1.2,1,1,1,1.116,0.05,3, myBackground, myYield, myRms, myMean);


	//now get the estimated events of the bacground spectrum of the CASCADEM using the fitting routine. (same plot as in g12finalmplots.C)
	TCanvas *ccasfit=new TCanvas("ccasfit","",1200,800);
	TH1F *hcasfit=new TH1F("hcasfit","",40,1.1,1.5);
	hcasfit->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hcasfit->GetXaxis()->SetTitle("#Xi^{-}     MM(K^{+}K^{+}) (GeV/c^{2})");
	newt->Draw("sqrt(mm2kpkp)>>hcasfit",newbasic&&lamm);

	Double_t myBackground2 = 0.0;
	Double_t myYield2 = 0.0;
	Double_t myRms2 = 0.0;
	Double_t myMean2 = 0.0;
	fitGAUS4(hcasfit,1,1.1,1.5,1,1,0,1.32,0.01,3,myBackground2, myYield2, myRms2, myMean2);
	
	
	cout << "=====================================================\n" 
	<< "My background (from lambda): " << myBackground << endl
	<< "My Yield (from lambda): " << myYield << endl
	<< "My Rms (from lambda): " << myRms << endl
	<< "My Mean (from lambda): " << myMean << endl;
	cout << "=====================================================\n" 
	<< "My background (from cascade): " << myBackground2 << endl
	<< "My Yield (from cascade): " << myYield2 << endl
    << "My Rms (from cascade): " << myRms2 << endl
	<< "My Mean (from cascade): " << myMean2 << endl;
	
//-----------------------------------------------now define the cuts----------------------------------------------------------

 
	// defineing the peak and side bands for the lambda0
	TCut lamp = Form("abs(sqrt(mm2kpkppim) - %f) < 3*%f" , myMean, myRms);
	cout << Form("abs(sqrt(mm2kpkppim) - %f) < 3*%f" , myMean, myRms) << endl;
	TCut lamsb = Form("abs(sqrt(mm2kpkppim) - (%f + 4.5*%f)) < 1.5 * %f || abs(sqrt(mm2kpkppim) - (%f - 4.5*%f)) < 1.5 * %f" , myMean, myRms, myRms, myMean, myRms, myRms);
	cout << Form("abs(sqrt(mm2kpkppim) - (%f + 4.5*%f))) < 1.5 * %f || abs(sqrt(mm2kpkppim) - (%f - 4.5*%f)) < 1.5 * %f" , myMean, myRms, myRms, myMean, myRms, myRms) << endl;

	// defineing the peak and side bands for the cascadem
	TCut casp = Form("abs(sqrt(mm2kpkp) - %f) < 3*%f" , myMean2, myRms2);
	cout << Form("abs(sqrt(mm2kpkp) - %f) < 3*%f" , myMean2, myRms2) << endl;
	TCut cassb = Form("abs(sqrt(mm2kpkp) - (%f + 4.5*%f)) < 1.5 * %f || abs(sqrt(mm2kpkp) - (%f - 4.5*%f)) < 1.5 * %f" , myMean2, myRms2, myRms2, myMean2, myRms2, myRms2);
	cout << Form("abs(sqrt(mm2kpkp) - (%f + 4.5*%f))) < 1.5 * %f || abs(sqrt(mm2kpkp) - (%f - 4.5*%f)) < 1.5 * %f" , myMean2, myRms2, myRms2, myMean2, myRms2, myRms2) << endl;





	TCanvas *ccuts=new TCanvas("ccuts","",1200,800);
	ccuts->Divide(2,1);
	ccuts->cd(1);
	
	
	// now plot the lambda0 to check out the cuts
	TH1F *hlamp=new TH1F("hlamp","",37, 0.90795,1.3131);
	TH1F *hlamsb=new TH1F("hlamsb","",37, 0.90795,1.3131);
	hlamp->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hlamp->GetXaxis()->SetTitle("#Lambda^{0}     MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
	newt->Draw("sqrt(mm2kpkppim)>>hlamp",newbasic&&casm&&lamp);
	newt->Draw("sqrt(mm2kpkppim)>>hlamsb",newbasic&&casm&&lamsb);
	hlamp->Draw();
	hlamsb->SetFillColor(2);
	hlamsb->SetFillStyle(3004);
	hlamsb->Draw("same");
	ccuts->cd(2);


	// now plot the cascade- to check out the cuts
	TH1F *hcasp=new TH1F("hcasp","",40, 1.1,1.5);
	TH1F *hcassb=new TH1F("hcassb","",40, 1.1,1.5);
	hcasp->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hcasp->GetXaxis()->SetTitle("#Xi^{-}     MM(K^{+}K^{+}) (GeV/c^{2})"); 
	newt->Draw("sqrt(mm2kpkp)>>hcasp",newbasic&&lamm&&casp);
	newt->Draw("sqrt(mm2kpkp)>>hcassb",newbasic&&lamm&&cassb);
	hcasp->Draw();
	hcassb->SetFillColor(2);
	hcassb->SetFillStyle(3004);
	hcassb->Draw("same");
	
	
	
//------------------------------------------------------------------------------------------------------------------------------
////=============================================end of background================================================================
//------------------------------------------------------------------------------------------------------------------------------






//==================================get the normaliation factors fac and fac2===================================================
	Float_t nside = hlamsb->GetEntries();
	Float_t nback = myBackground;
	Float_t fac = nback/nside;
	
		
	Float_t nside2 = hcassb->GetEntries();
	Float_t nback2 = myBackground2;
	Float_t fac2 = nback2/nside2;

	
	cout <<"nside is: "<< nside << "   number in backround is for lambda is  : " << nback << endl;
	cout <<"the normalization factor for lambda is fac = " << fac << endl;
	
	cout <<"nside2 is: "<< nside2 << "   number in backround is for cascade is  : " <<nback2 << endl;
	cout <<"the normalization factor for cascade is fac2 = " << fac2 << endl;
//------------------------------------------------------------------------------------------------------------------------------





//===============================================================================================================
//===========================NOW DOING THE X Y Z N ANGLES========================================================
//===============================================================================================================

	//============= this is from leis_beautify.C which i changed a bit========================
	//===============this is the final configuration that he used in his paper========
 	printf("Welcome to the ROOT\n");
	gStyle->SetTitleXOffset(0.85);  //this: Xoff
	gStyle->SetTitleYOffset(0.95);  //this:  Yoff
	gStyle->SetTitleSize(0.07);  //this:    Xsize   
	gStyle->SetTitleYSize(0.07); //this     Ysize
	//gStyle->SetLabelFont(72);
	gStyle->SetPadLeftMargin(0.19);   // this: Yaxis 
	gStyle->SetPadBottomMargin(0.15);  // this: Xaxis
	gStyle->SetPadTopMargin(0.02); // was 0.02
	gStyle->SetCanvasBorderMode(1);
	gStyle->SetPadBorderMode(1);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPadColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetFrameFillStyle(1001);
	gStyle->SetFrameFillStyle(0);
	gStyle->SetFillStyle(0);
 	gStyle->SetOptStat(0);
	//====================================================================

	//define 2 canvases for each lab coord
	TCanvas *cX=new TCanvas("cX","",1200,800);
	TCanvas *cY=new TCanvas("cY","",1200,800);
	TCanvas *cZ=new TCanvas("cZ","",1200,800);
	TCanvas *cN=new TCanvas("cN","",1200,800);

	TCanvas *cX2=new TCanvas("cX2","",1200,800);
	TCanvas *cY2=new TCanvas("cY2","",1200,800);
	TCanvas *cZ2=new TCanvas("cZ2","",1200,800);
	TCanvas *cN2=new TCanvas("cN2","",1200,800);

	cX->Divide(2,1);
	cY->Divide(2,1);
	cZ->Divide(2,1);
	cN->Divide(2,1);
	cX->cd(1);	
	cY->cd(1);	
	cZ->cd(1);	
	cN->cd(1);

	cX2->Divide(2,1);
	cY2->Divide(2,1);
	cZ2->Divide(2,1);
	cN2->Divide(2,1);
	cX2->cd(1);	
	cY2->cd(1);	
	cZ2->cd(1);	
	cN2->cd(1);	
	
	
	
	//define all hists needed
	TH1F *hX=new TH1F("hX","",10,-1,1);
	TH1F *hXside=new TH1F("hXside","",10,-1,1);
	TH1F *hXsideNorm=new TH1F("hXsideNorm","",10,-1,1);
	TH1F *hXsub=new TH1F("hXsub","",10,-1,1);
	TH1F *hX2=new TH1F("hX2","",10,-1,1);		
	TH1F *hXside2=new TH1F("hXside2","",10,-1,1);
	TH1F *hXsideNorm2=new TH1F("hXsideNorm2","",10,-1,1);
	TH1F *hXsub2=new TH1F("hXsub2","",10,-1,1);
	
	
	TH1F *hY=new TH1F("hY","",10,-1,1);
	TH1F *hYside=new TH1F("hYside","",10,-1,1);
	TH1F *hYsideNorm=new TH1F("hYsideNorm","",10,-1,1);
	TH1F *hYsub=new TH1F("hYsub","",10,-1,1);
	TH1F *hY2=new TH1F("hY2","",10,-1,1);
	TH1F *hYside2=new TH1F("hYside2","",10,-1,1);
	TH1F *hYsideNorm2=new TH1F("hYsideNorm2","",10,-1,1);
	TH1F *hYsub2=new TH1F("hYsub2","",10,-1,1);

	
	TH1F *hZ=new TH1F("hZ","",10,-1,1);
	TH1F *hZside=new TH1F("hZside","",10,-1,1);
	TH1F *hZsideNorm=new TH1F("hZsideNorm","",10,-1,1);
	TH1F *hZsub=new TH1F("hZsub","",10,-1,1);
	TH1F *hZ2=new TH1F("hZ2","",10,-1,1);
	TH1F *hZside2=new TH1F("hZside2","",10,-1,1);
	TH1F *hZsideNorm2=new TH1F("hZsideNorm2","",10,-1,1);
	TH1F *hZsub2=new TH1F("hZsub2","",10,-1,1);	
	
	
	TH1F *hN=new TH1F("hN","",10,-1,1);
	TH1F *hNside=new TH1F("hNside","",10,-1,1);
	TH1F *hNsideNorm=new TH1F("hNsideNorm","",10,-1,1);
	TH1F *hNsub=new TH1F("hNsub","",10,-1,1);
	TH1F *hN2=new TH1F("hN2","",10,-1,1);
	TH1F *hNside2=new TH1F("hNside2","",10,-1,1);
	TH1F *hNsideNorm2=new TH1F("hNsideNorm2","",10,-1,1);
	TH1F *hNsub2=new TH1F("hNsub2","",10,-1,1);

	
	//name axis
	hX->GetYaxis()->SetTitle("Events");
    hX->GetXaxis()->SetTitle("from lam peak cos(#theta_{x}^{#pi^{-}})");
	hXsub->GetYaxis()->SetTitle("Events");
    hXsub->GetXaxis()->SetTitle("subtracted cos(#theta_{x}^{#pi^{-}})");
	hX2->GetYaxis()->SetTitle("Events");
    hX2->GetXaxis()->SetTitle("from cas peak cos(#theta_{x}^{#pi^{-}})");
	hXsub2->GetYaxis()->SetTitle("Events");
    hXsub2->GetXaxis()->SetTitle("subtracted2 cos(#theta_{x}^{#pi^{-}})");		
	
	hY->GetYaxis()->SetTitle("Events");
    hY->GetXaxis()->SetTitle("from lam peak cos(#theta_{y}^{#pi^{-}})");
	hYsub->GetYaxis()->SetTitle("Events");
    hYsub->GetXaxis()->SetTitle("subtracted cos(#theta_{y}^{#pi^{-}})");
	hY2->GetYaxis()->SetTitle("Events");
    hY2->GetXaxis()->SetTitle("from cas peak cos(#theta_{y}^{#pi^{-}})");
	hYsub2->GetYaxis()->SetTitle("Events");
    hYsub2->GetXaxis()->SetTitle("subtracted2 cos(#theta_{y}^{#pi^{-}})");

	hZ->GetYaxis()->SetTitle("Events");
    hZ->GetXaxis()->SetTitle("from lam peak cos(#theta_{z}^{#pi^{-}})");
	hZsub->GetYaxis()->SetTitle("Events");
    hZsub->GetXaxis()->SetTitle("subtracted cos(#theta_{z}^{#pi^{-}})");
	hZ2->GetYaxis()->SetTitle("Events");
    hZ2->GetXaxis()->SetTitle("from cas peak cos(#theta_{z}^{#pi^{-}})");
	hZsub2->GetYaxis()->SetTitle("Events");
    hZsub2->GetXaxis()->SetTitle("subtracted2 cos(#theta_{z}^{#pi^{-}})");
	
	hN->GetYaxis()->SetTitle("Events");
    hN->GetXaxis()->SetTitle("from lam peak cos(#theta_{n}^{#pi^{-}})");
	hNsub->GetYaxis()->SetTitle("Events");
    hNsub->GetXaxis()->SetTitle("subtracted cos(#theta_{n}^{#pi^{-}})");
	hN2->GetYaxis()->SetTitle("Events");
    hN2->GetXaxis()->SetTitle("from cas peak cos(#theta_{n}^{#pi^{-}})");
	hNsub2->GetYaxis()->SetTitle("Events");
    hNsub2->GetXaxis()->SetTitle("subtracted2 cos(#theta_{n}^{#pi^{-}})");

	
	
	//fill hists for lam            changed lam3->lamp   and lamSidebands->lamsb  jan14
	newt->Draw("cos(PIanglex)>>hX",newbasic&&casm&&lamp);
	newt->Draw("cos(PIanglex)>>hXside",newbasic&&casm&&lamsb);
	
	newt->Draw("cos(PIangley)>>hY",newbasic&&casm&&lamp);
	newt->Draw("cos(PIangley)>>hYside",newbasic&&casm&&lamsb);
	
	newt->Draw("cos(PIanglez)>>hZ",newbasic&&casm&&lamp);
	newt->Draw("cos(PIanglez)>>hZside",newbasic&&casm&&lamsb);

	newt->Draw("cos(PIangle)>>hN",newbasic&&casm&&lamp);
	newt->Draw("cos(PIangle)>>hNside",newbasic&&casm&&lamsb);

	//fill hists for cas
	newt->Draw("cos(PIanglex)>>hX2",newbasic&&lamm&&casp);
	newt->Draw("cos(PIanglex)>>hXside2",newbasic&&lamm&&cassb);
	
	newt->Draw("cos(PIangley)>>hY2",newbasic&&lamm&&casp);
	newt->Draw("cos(PIangley)>>hYside2",newbasic&&lamm&&cassb);
	
	newt->Draw("cos(PIanglez)>>hZ2",newbasic&&lamm&&casp);
	newt->Draw("cos(PIanglez)>>hZside2",newbasic&&lamm&&cassb);

	newt->Draw("cos(PIangle)>>hN2",newbasic&&lamm&&casp);
	newt->Draw("cos(PIangle)>>hNside2",newbasic&&lamm&&cassb);	
	
	
	// fill normalized hists and subtracted hists for lam
	hXsideNorm->Add(hXside,fac);
	hXsub->Add(hX,1);
	hXsub->Add(hXsideNorm,-1);
	
	hYsideNorm->Add(hYside,fac);
	hYsub->Add(hY,1);
	hYsub->Add(hYsideNorm,-1);
	
	hZsideNorm->Add(hZside,fac);
	hZsub->Add(hZ,1);
	hZsub->Add(hZsideNorm,-1);
	
	hNsideNorm->Add(hNside,fac);
	hNsub->Add(hN,1);
	hNsub->Add(hNsideNorm,-1);
	
	// fill normalized hists and subtracted hists for cas
	hXsideNorm2->Add(hXside2,fac2);
	hXsub2->Add(hX2,1);
	hXsub2->Add(hXsideNorm2,-1);
	
	hYsideNorm2->Add(hYside2,fac2);
	hYsub2->Add(hY2,1);
	hYsub2->Add(hYsideNorm2,-1);
	
	hZsideNorm2->Add(hZside2,fac2);
	hZsub2->Add(hZ2,1);
	hZsub2->Add(hZsideNorm2,-1);
	
	hNsideNorm2->Add(hNside2,fac2);
	hNsub2->Add(hN2,1);
	hNsub2->Add(hNsideNorm2,-1);
	
		
	//set the min y value to be zero for proper display
	hX->SetMinimum(0);
	hXside->SetMinimum(0);
	hXsideNorm->SetMinimum(0);
	hXsub->SetMinimum(0);
	
	hY->SetMinimum(0);
	hYside->SetMinimum(0);
	hYsideNorm->SetMinimum(0);
	hYsub->SetMinimum(0);
	
	hZ->SetMinimum(0);
	hZside->SetMinimum(0);
	hZsideNorm->SetMinimum(0);
	hZsub->SetMinimum(0);
	
	hN->SetMinimum(0);
	hNside->SetMinimum(0);
	hNsideNorm->SetMinimum(0);
	hNsub->SetMinimum(0);
	
	
	hX2->SetMinimum(0);
	hXside2->SetMinimum(0);
	hXsideNorm2->SetMinimum(0);
	hXsub2->SetMinimum(0);
	
	hY2->SetMinimum(0);
	hYside2->SetMinimum(0);
	hYsideNorm2->SetMinimum(0);
	hYsub2->SetMinimum(0);
	
	hZ2->SetMinimum(0);
	hZside2->SetMinimum(0);
	hZsideNorm2->SetMinimum(0);
	hZsub2->SetMinimum(0);
	
	hN2->SetMinimum(0);
	hNside2->SetMinimum(0);
	hNsideNorm2->SetMinimum(0);
	hNsub2->SetMinimum(0);
	
	//let the sideNorm hists be red
	hXsideNorm->SetFillColor(2);
	hXsideNorm->SetFillStyle(3004);
	hYsideNorm->SetFillColor(2);
	hYsideNorm->SetFillStyle(3004);
	hZsideNorm->SetFillColor(2);
	hZsideNorm->SetFillStyle(3004);
	hNsideNorm->SetFillColor(2);
	hNsideNorm->SetFillStyle(3004);
	
	hXsideNorm2->SetFillColor(2);
	hXsideNorm2->SetFillStyle(3004);
	hYsideNorm2->SetFillColor(2);
	hYsideNorm2->SetFillStyle(3004);
	hZsideNorm2->SetFillColor(2);
	hZsideNorm2->SetFillStyle(3004);
	hNsideNorm2->SetFillColor(2);
	hNsideNorm2->SetFillStyle(3004);
	
	//Now Draw the hists
	cX->cd(1);
	hX->Draw();
	hXsideNorm->Draw("same");	
	cX->cd(2);
	hXsub->Draw();
	
	cY->cd(1);
	hY->Draw();
	hYsideNorm->Draw("same");	
	cY->cd(2);
	hYsub->Draw();
	
	cZ->cd(1);
	hZ->Draw();
	hZsideNorm->Draw("same");	
	cZ->cd(2);
	hZsub->Draw();
	
	cN->cd(1);
	hN->Draw();
	hNsideNorm->Draw("same");	
	cN->cd(2);
	hNsub->Draw();
	
	
	cX2->cd(1);
	hX2->Draw();
	hXsideNorm2->Draw("same");	
	cX2->cd(2);
	hXsub2->Draw();
	
	cY2->cd(1);
	hY2->Draw();
	hYsideNorm2->Draw("same");	
	cY2->cd(2);
	hYsub2->Draw();
	
	cZ2->cd(1);
	hZ2->Draw();
	hZsideNorm2->Draw("same");	
	cZ2->cd(2);
	hZsub2->Draw();
	
	cN2->cd(1);
	hN2->Draw();
	hNsideNorm2->Draw("same");	
	cN2->cd(2);
	hNsub2->Draw();
	
	
	
	
	
	
	cout << "number of events in hXsideNorm hYsideNorm hZsideNorm hNsideNorm is: " <<
		hXsideNorm->GetEntries() << " " << hYsideNorm->GetEntries() << " " << hZsideNorm->GetEntries() << hNsideNorm->GetEntries() << endl;
	
	
	
	
	
	
	
	
	

	//=================================================================================================================================
	//=================================================plot the n angles===============================================================
	//======================================this is old code that i dont want to deleete===============================================



	/*
	 TCanvas *c0=new TCanvas("c0","",1200,800);
	 c0->Divide(2,1);
	 c0_2->Divide(1,2);
	 c0->cd(1);

	 TH1F *hlam=new TH1F("hlam","",37, 0.90795,1.3131);
	 TH1F *hlamS = (TH1F*)hlam->Clone("hlamS"); // the lamda sideband
	 TH1F *hlamS2 = (TH1F*)hlam->Clone("hlamS2"); // the cascade sideband

	 newt->Draw("sqrt(mm2kpkppim)>>hlam",newbasic&&casm&&lam3);
	 newt->Draw("sqrt(mm2kpkppim)>>hlamS",newbasic&&casm&&lamSidebands);
	 //hlamS->SetFillStyle(3004);
	 TH1F *hlamALL=new TH1F("hlamALL","",37,0.90795,1.3131);
	 newt->Draw("sqrt(mm2kpkppim)>>hlamALL",newbasic&&casm&&lamTherest);

	 hlam->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	 hlam->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
	 //hlamALL->SetFillColor(3);
	 //hlamALL->Draw();
	 /// hlam->SetFillColor(4);
	 hlam->Draw("E");
	 hlamS->SetFillColor(2);
	 hlamS->SetFillStyle(3004);
	 hlamS->Draw("same"); 
	 hlamALL->Draw("samee");



	 //--------------------normalization---------------------------
	 Float_t nside= hlamS->GetEntries();
	 Float_t nback=myBackground;
	Float_t fac=nback/nside;
	 cout <<"nside is: "<< nside << "   number in backround is : " <<nback<<endl;
	 cout <<"the normalization factor fac=" << fac << endl;


	/*


	 //----------------------------------------------------the angles overlay-------------------------------------------- 

	 //====================================for the right hand plots=======================
	 printf("Welcome to the ROOT\n");
	 gStyle->SetTitleXOffset(0.85);  //this: Xoff
	 gStyle->SetTitleYOffset(0.75);  //this:  Yoff
	 gStyle->SetTitleSize(0.08);  //this:    Xsize   
	 gStyle->SetTitleYSize(0.08); //this     Ysize
	 //gStyle->SetLabelFont(72);
	 gStyle->SetPadLeftMargin(0.11);   // this: Yaxis 
	 gStyle->SetPadBottomMargin(0.15);  // this: Xaxis
	 gStyle->SetPadTopMargin(0.02); // was 0.02
	 gStyle->SetCanvasBorderMode(1);
	 gStyle->SetPadBorderMode(1);
	 gStyle->SetFrameBorderMode(0);
	 gStyle->SetPadColor(0);
	 gStyle->SetCanvasColor(0);
	 gStyle->SetFrameFillColor(0);
	 gStyle->SetFrameFillStyle(1001);
	 gStyle->SetFrameFillStyle(0);
	 gStyle->SetFillStyle(0);
	 gStyle->SetOptStat(0);
	//====================================================================




	 c0_2->cd(1);
	 TH1F *hn=new TH1F("hn","",10,-1,1); 
	 hn->SetMinimum(0);
	 newt->Draw("cos(PIangle)>>hn",newbasic&&casm&&lam3);
	 TH1F *hnS=new TH1F("hnS","",10,-1,1); 
	 TH1F *hnSnorm = (TH1F*)hnS->Clone("hnSnorm");
	 hnS->SetMinimum(0);
	 newt->Draw("cos(PIangle)>>hnS",newbasic&&casm&&lamSidebands);

	 hnSnorm->Add(hnS, fac);
	 cout<<"number here should be the same as number in background "<< hnSnorm->GetEntries() <<endl;
	 hn->GetYaxis()->SetTitle("Events");  
	 hn->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}})");   


	 // hn->SetFillColor(4);
	  hn->Draw();
	  hnSnorm->SetFillColor(2);
	  hnSnorm->SetFillStyle(3004);
	  hnSnorm->Draw("SAME"); 


	 //-----------------------------------------------the subtracted hists-------------------------
	  c0_2->cd(2);
	  // TH1F *hntotal = (TH1F*)hn->Clone("hntotal");
	  TH1F *hntotal=new TH1F("hntotal","",10,-1,1); 

	  hntotal->Add(hn,1);
	  hntotal->Add(hnSnorm,-1);
	  hntotal->SetMinimum(0);
	  //hntotal->SetFillColor(3);
	  hntotal->Draw();
	  hntotal->GetYaxis()->SetTitle("Events");
	  hntotal->GetXaxis()->SetTitle("subtracted cos(#theta^{#pi^{-}})");   




	*/


	//------------------------------------------------------------------------------------------------------------------------------
	////=============================================end of ploting n angles================================================================
	//------------------------------------------------------------------------------------------------------------------------------

	
	
	
	

	
	}
