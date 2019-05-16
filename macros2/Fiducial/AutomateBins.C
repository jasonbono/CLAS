



void AutomateBins()
{
	TFile* fdata = new TFile("/Users/Bono/clas/rootfiles/g12/ppippim/full/ppippim-v03_Phi.root");
	TTree *tdata = (TTree*)fdata->Get("v03");
	
	const int Ni = 10000; //number of bins displayed in histograms
	const int Np = 3; //number of momentum bins to derive
	const float plow = 0;
	const float phigh = 4;
	const int Nt = 3; //number of momentum bins to derive
	const float tlow = 0;
	const float thigh = 180;


	////////////////////////////////// begin calculation for pip ///////////////////////////////////////////////
	TCut plowcut_pip = Form("ppip > %f",plow);
	TCut phighcut_pip = Form("ppip < %f",phigh);
	TH1F *hp_pip=new TH1F("hp_pip","",Ni,plow,phigh);
	hp_pip->GetXaxis()->SetTitle("p(#pi+))");
	tdata->Draw("ppip>>hp_pip",plowcut_pip&&phighcut_pip);
	Int_t pCritera_pip = hp_pip->GetEntries()/Np;
	int pbinlow_pip = hp_pip->GetXaxis()->FindBin(plow);
	int pbinhigh_pip = hp_pip->GetXaxis()->FindBin(phigh);

	
	float ptempval_pip = 0;
	int pbin_pip = 0;
	int ppop_pip =0;
	float pval_pip[Np - 1] = {0};
	for (int p=0; p<Np -1; p++)
	{
		for (int i=1; i<Ni; i++)
		{
			pbin_pip = pbinlow_pip + i;
			
			ppop_pip = hp_pip->Integral(pbinlow_pip,pbin_pip);
			if (ppop_pip >= pCritera_pip)
			{
				ptempval_pip = hp_pip->GetBinCenter(pbin_pip);
				pval_pip[p] = ptempval_pip; //store the value
				pbinlow_pip = pbin_pip; //lowbin for the next p iteration should be the current bin for this iteration.
				i = Ni; //kill i loop the loop		
			}
		}
	}
	

	//create all the p cuts.
	float pVal_pip[Np+1];
	pVal_pip[0] = plow;
	pVal_pip[Np] = phigh;
	for (int p=0; p< Np - 1; p++)
	{
		pVal_pip[p+1] = pval_pip[p];
	}
	for (int p=0; p< Np+1; p++)
	{
		cout << "pVal_pip[" <<p<<"] = "<<pVal_pip[p]<<endl;
	}
	TCut pcut_pip[Np];
	for (int p=0; p<Np; p++)
	{
		pcut_pip[p] =  Form("ppip > %f && ppip < %f ",pVal_pip[p],pVal_pip[p+1]);
		TString temp = pcut_pip[p];
		cout << temp <<endl;
	}
	
	
	//----------------theta-----------------------------
	TCut tcut_pip[Np][Nt];

	TCut tlowcut_pip = Form("piplabtheta > %f",tlow);
	TCut thighcut_pip = Form("piplabtheta < %f",thigh);
	TH1F *ht_pip=new TH1F("ht_pip","",Ni,tlow,thigh);
	ht_pip->GetXaxis()->SetTitle("Cos(#theta)(#pi+))");
	for (int p=0; p<Np; p++)
	{
		tdata->Draw("piplabtheta>>ht_pip",tlowcut_pip&&thighcut_pip&&pcut_pip[p]);
		Int_t tCritera_pip = ht_pip->GetEntries()/Nt;
		cout << "total entries in theta = " << ht_pip->GetEntries() << " tCritera_pip = " << tCritera_pip <<endl;
		int tbinlow_pip = ht_pip->GetXaxis()->FindBin(tlow);
		int tbinhigh_pip = ht_pip->GetXaxis()->FindBin(thigh);
		
		float ttempval_pip = 0;
		int tbin_pip = 0;
		int tpop_pip =0;
		float tval_pip[Nt - 1] = {0};
		for (int t=0; t<Nt -1; t++)
		{
			for (int i=1; i<Ni; i++)
			{
				tbin_pip = tbinlow_pip + i;

				tpop_pip = ht_pip->Integral(tbinlow_pip,tbin_pip);
				if (tpop_pip >= tCritera_pip)
				{
					ttempval_pip = ht_pip->GetBinCenter(tbin_pip);
					tval_pip[t] = ttempval_pip; //store the value
					tbinlow_pip = tbin_pip; //lowbin for the next t iteration should be the current bin for this iteration.
					i = Ni; //kill i loop the loop		
				}
			}
		}
		
		//create all the t cuts.
		float tVal_pip[Nt+1];
		tVal_pip[0] = tlow;
		tVal_pip[Nt] = thigh;
		for (int t=0; t< Nt - 1; t++)
		{
			tVal_pip[t+1] = tval_pip[t];
		}
		for (int t=0; t< Nt+1; t++)
		{
			cout << "tVal_pip[" <<t<<"] = "<<tVal_pip[t]<<endl;
		}
		for (int t=0; t<Nt; t++)
		{
			tcut_pip[p][t] =  Form("piplabtheta > %f && piplabtheta < %f ",tVal_pip[t],tVal_pip[t+1]);
			TString temp = tcut_pip[p][t];
			cout << temp <<endl;
		}
	}		
	/////////////////////////////////// finished with calculation for pip ///////////////////////////////////////////////








	/////////////////////////////////// begin calculation for pim ///////////////////////////////////////////////

	TCut plowcut_pim = Form("ppim > %f",plow);
	TCut phighcut_pim = Form("ppim < %f",phigh);
	TH1F *hp_pim=new TH1F("hp_pim","",Ni,plow,phigh);
	hp_pim->GetXaxis()->SetTitle("p(#pi-))");
	tdata->Draw("ppim>>hp_pim",plowcut_pim&&phighcut_pim);
	Int_t pCritera_pim = hp_pim->GetEntries()/Np;
	int pbinlow_pim = hp_pim->GetXaxis()->FindBin(plow);
	int pbinhigh_pim = hp_pim->GetXaxis()->FindBin(phigh);

	
	float ptempval_pim = 0;
	int pbin_pim = 0;
	int ppop_pim =0;
	float pval_pim[Np - 1] = {0};
	for (int p=0; p<Np -1; p++)
	{
		for (int i=1; i<Ni; i++)
		{
			pbin_pim = pbinlow_pim + i;
			
			ppop_pim = hp_pim->Integral(pbinlow_pim,pbin_pim);
			if (ppop_pim >= pCritera_pim)
			{
				ptempval_pim = hp_pim->GetBinCenter(pbin_pim);
				pval_pim[p] = ptempval_pim; //store the value
				pbinlow_pim = pbin_pim; //lowbin for the next p iteration should be the current bin for this iteration.
				i = Ni; //kill i loop the loop		
			}
		}
	}
	

	//create all the p cuts.
	float pVal_pim[Np+1];
	pVal_pim[0] = plow;
	pVal_pim[Np] = phigh;
	for (int p=0; p< Np - 1; p++)
	{
		pVal_pim[p+1] = pval_pim[p];
	}
	for (int p=0; p< Np+1; p++)
	{
		cout << "pVal_pim[" <<p<<"] = "<<pVal_pim[p]<<endl;
	}
	TCut pcut_pim[Np];
	for (int p=0; p<Np; p++)
	{
		pcut_pim[p] =  Form("ppim > %f && ppim < %f ",pVal_pim[p],pVal_pim[p+1]);
		TString temp = pcut_pim[p];
		cout << temp <<endl;
	}
	
	
	//----------------theta-----------------------------
	TCut tcut_pim[Np][Nt];

	TCut tlowcut_pim = Form("pimlabtheta > %f",tlow);
	TCut thighcut_pim = Form("pimlabtheta < %f",thigh);
	TH1F *ht_pim=new TH1F("ht_pim","",Ni,tlow,thigh);
	ht_pim->GetXaxis()->SetTitle("Cos(#theta)(#pi-))");
	for (int p=0; p<Np; p++)
	{
		tdata->Draw("pimlabtheta>>ht_pim",tlowcut_pim&&thighcut_pim&&pcut_pim[p]);
		Int_t tCritera_pim = ht_pim->GetEntries()/Nt;
		cout << "total entries in theta = " << ht_pim->GetEntries() << " tCritera_pim = " << tCritera_pim <<endl;
		int tbinlow_pim = ht_pim->GetXaxis()->FindBin(tlow);
		int tbinhigh_pim = ht_pim->GetXaxis()->FindBin(thigh);
		
		float ttempval_pim = 0;
		int tbin_pim = 0;
		int tpop_pim =0;
		float tval_pim[Nt - 1] = {0};
		for (int t=0; t<Nt -1; t++)
		{
			for (int i=1; i<Ni; i++)
			{
				tbin_pim = tbinlow_pim + i;

				tpop_pim = ht_pim->Integral(tbinlow_pim,tbin_pim);
				if (tpop_pim >= tCritera_pim)
				{
					ttempval_pim = ht_pim->GetBinCenter(tbin_pim);
					tval_pim[t] = ttempval_pim; //store the value
					tbinlow_pim = tbin_pim; //lowbin for the next t iteration should be the current bin for this iteration.
					i = Ni; //kill i loop the loop		
				}
			}
		}
		
		//create all the t cuts.
		float tVal_pim[Nt+1];
		tVal_pim[0] = tlow;
		tVal_pim[Nt] = thigh;
		for (int t=0; t< Nt - 1; t++)
		{
			tVal_pim[t+1] = tval_pim[t];
		}
		for (int t=0; t< Nt+1; t++)
		{
			cout << "tVal_pim[" <<t<<"] = "<<tVal_pim[t]<<endl;
		}
		for (int t=0; t<Nt; t++)
		{
			tcut_pim[p][t] =  Form("pimlabtheta > %f && pimlabtheta < %f ",tVal_pim[t],tVal_pim[t+1]);
			TString temp = tcut_pim[p][t];
			cout << temp <<endl;
		}
	}		



/////////////////////////////////// finished with calculation for pim ///////////////////////////////////////////////






	//spit out the final results
	cout <<endl<<endl<<endl;
	TCut ptcut_pip[Np][Nt];
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
			ptcut_pip[p][t] = pcut_pip[p]&&tcut_pip[p][t];
			TString temp = ptcut_pip[p][t];
			cout << "pip_ptcut["<<p<<"]["<<t<<"] = " << " \" " << temp << " \" ; " <<endl;
		}
	}
	
	cout <<endl<<endl<<endl;
	TCut ptcut_pim[Np][Nt];
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
			ptcut_pim[p][t] = pcut_pim[p]&&tcut_pim[p][t];
			TString temp = ptcut_pim[p][t];
			cout << "pim_ptcut["<<p<<"]["<<t<<"] = " << " \" " << temp << " \" ; " <<endl;
		}
	}



}	






































