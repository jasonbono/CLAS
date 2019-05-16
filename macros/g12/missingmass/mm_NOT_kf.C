void mm_NOT_kf()
{

	//load the fitter
	gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS3.C");

	//choose the files ----------------------------------------------------------
	//TFile *f = TFile::Open("~/clas/macros/general/AlterRootFiles/test_v32k.root");
	//TTree *newt = (TTree*)f->Get("v32k");
	TFile *f = TFile::Open("~/clas/rootfiles/g12/large/v34k_full.root");
	TTree *newt = (TTree*)f->Get("v34k_newbasic");
	//---------------------------------------------------------------------------
	
	//cuts------------------------------------------------------------------------
	//the mass cuts from nov 22 2011
	TCut casm="abs(mlampim-1.321)<0.013";
	TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
	TCut lamm="abs(mcasmMpim - 1.116)<0.01";
	TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";
	TCut lamm2="abs(mcasmMpim-1.116)<0.02";
	//the kf confidence cut
	TCut conf = "kf_prob > 0.10";
	//---------------------------------------------------------------------------	
	
	//---------------------------------make it look good-------------------------
	printf("Welcome to the ROOT\n");
	gStyle->SetTitleXOffset(0.85);  //this: Xoff
	gStyle->SetTitleYOffset(0.95);  //this:  Yoff
	gStyle->SetTitleSize(0.06);  //this:    Xsize   
	gStyle->SetTitleYSize(0.06); //this     Ysize
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
	//----------------------------------------------------------------------------


	//create the canvases/histos
	
	TH1F *histCas[4];
	TH1F *histLam[4];
	TCanvas *can[4];	
	char cname[4];
	char hnameCas[4];
	char hnameLam[4];
	
	// loop over canvases/histos
	for (int i = 0; i < 1; i++) 
	{
		// setup canvas name
		sprintf(cname, "can_%d", i);
		sprintf(hnameCas,"histCas_%d", i);
		sprintf(hnameLam,"histLam_%d", i);
		
		
		// create a new canvas with appropriate dimensions
		can[i] = new TCanvas(cname, cname, 1600, 1100);
		
		// divide it into subpads as needed
		can[i]->Divide(2, 0);   // columns and rows are integers as needed

		// create the histograms with approprate range and binning
		histCas[i] = new TH1F(hnameCas, "", 15, 1.25, 1.4);
		histLam[i] = new TH1F(hnameLam, "", 15, 1.05, 1.2);
		
		//lable the y axis			
		histCas[i] -> GetYaxis() -> SetTitle("Events/10MeV/c^{2}");
		histLam[i] -> GetYaxis() -> SetTitle("Events/10MeV/c^{2}");


		//lable the x axis
		if (i==0 || i == 1)
		{
			histCas[i] -> GetXaxis() -> SetTitle(" MM(k^{+} + k^{+})  (GeV/c^{2})");
			histLam[i] -> GetXaxis() -> SetTitle(" MM(k^{+} + k^{+} + #pi^{-})  (GeV (GeV/c^{2})");
		}
		else if (i==2 || i==3)
		{
			histCas[i] -> GetXaxis() -> SetTitle(" M(#pi^{-} + #Lambda) (GeV/c^{2})");
			histLam[i] -> GetXaxis() -> SetTitle(" M(#Xi^{-} - #pi^{-} )(GeV/c^{2})");	
			
		}

	}

	
	//==========================================ploting the Xi==============================================

	can[0]->cd(1);
	newt->Draw("mmkpkp>>histCas_0",!conf);
	//fitGAUS3(histCas_0,1,1.25,1.4,1,0,0,1.32,0.045,3,0,0,0);
	can[0]->cd(2);
	newt->Draw("mmkpkppim>>histLam_0",!conf);
	//fitGAUS3(histLam_0,1,1.05,1.2,1,0,0,1.116,0.045,3,0,0,0);	

		

	
	
	
	
	
	
	
	
	
}