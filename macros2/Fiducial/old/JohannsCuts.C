/*
To plot the cuts outlined by johann in his forwarded email title "fiducial cuts".


both the tight cuts and the loose cuts will be overlaid data and the reconstructed events


*/
void JohannsCuts()
{


	TFile *fData = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05-Basic-Mass.root");
	TTree *tData = (TTree*)fData->Get("v05");
	TFile *fMC = TFile::Open("~/clas/rootfiles/LINKS/MC-i6-2kppim_Basic_Mass.root");
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim");

/*

	TTree *tree;
	const string choice;
	cout << "For Data or MC? (type Data or MC)";
	cin >> choice;
	if (choice.compare("Data") == 0) 
	{		
		tree = tData;
	}
	else if (choice.compare("MC") == 0)
	{
		tree = tMC;
	}

*/	
	
	
	//Define the functions (t for tight, l for loose)
	TF1 *fnegt = new TF1("fnegt","0.016/(0.95 - x) + 0.32",0,0.95);
	TF1 *fnegl = new TF1("fnegt","0.016/(0.96 - x) + 0.18",0,0.96);
	TF1 *fpost = new TF1("fpost","0.001/(0.97 - x) + 0.33",0,0.97);
	TF1 *fposl = new TF1("fpost","0.001/(0.985 - x) + 0.15",0,0.985);
	fnegt->SetLineColor(4);
	fnegl->SetLineColor(2);
	fpost->SetLineColor(4);
	fposl->SetLineColor(2);
	


	fnegt->SetNpx(1000);
	fnegl->SetNpx(1000);
	fpost->SetNpx(1000);
	fposl->SetNpx(1000);
	
	
	tree = tData;

	//K1
	TCanvas *cK1=new TCanvas("cK1","cK1",1200,800);
	TH2F *hK1=new TH2F("hK1","",200,0.8,1,200,0,3.8);
	hK1->GetYaxis()->SetTitle("Momentum (GeV)");
	hK1->GetXaxis()->SetTitle("Cos(#Theta)");
	tree->Draw("pkp1:kp1labtheta>>hK1","","colz");  //kp1labtheta is actualy the cosine of its title
	fpost->Draw("same");
	fposl->Draw("same");

	//K2
	TCanvas *cK2=new TCanvas("cK2","cK2",1200,800);
	TH2F *hK2=new TH2F("hK2","",200,0.5,1,200,0,2.5);
	hK2->GetYaxis()->SetTitle("Momentum (GeV)");
	hK2->GetXaxis()->SetTitle("Cos(#Theta)");
	tree->Draw("pkp2:kp2labtheta>>hK2","","colz");
	fpost->Draw("same");
	fposl->Draw("same");
	
	
	//PI
	TCanvas *cPI=new TCanvas("cPI","cPI",1200,800);
	TH2F *hPI=new TH2F("hPI","",200,0.2,1,200,0,1);
	hPI->GetYaxis()->SetTitle("Momentum (GeV)");
	hPI->GetXaxis()->SetTitle("Cos(#Theta)");
	tree->Draw("ppim:pilabtheta>>hPI","","colz");
	fnegt->Draw("same");
	fnegl->Draw("same");
	
	
	
		

	
}