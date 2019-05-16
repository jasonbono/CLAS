
void GetHists()
{	
	const int Np = 15;  //number of momentum bins	
	const int Nt = 15;  //number of theta bins	
	const int Ns = 6;
	
	StyleUp();
	
	//input
	TFile* fdata = new TFile("/Users/Bono/clas/rootfiles/g12/ppippim/full/ppippim-v03_Phi.root");  
	TTree *tdata = (TTree*)fdata->Get("v03");	
	//output
	TFile* fOutput = new TFile(Form("./hists/Phi-%i-%ibins.root",Np,Nt),"RECREATE");
	
	
	
	TCut pip_ptcut[Np][Nt];
	TCut pim_ptcut[Np][Nt];
	if (Np == 3 && Nt == 3)
	{
		pip_ptcut[0][0] =  " (ppip > 0.000000 && ppip < 0.511000 )&&(piplabtheta > 0.000000 && piplabtheta < 34.951500 ) " ; 
		pip_ptcut[0][1] =  " (ppip > 0.000000 && ppip < 0.511000 )&&(piplabtheta > 34.951500 && piplabtheta < 52.105499 ) " ; 
		pip_ptcut[0][2] =  " (ppip > 0.000000 && ppip < 0.511000 )&&(piplabtheta > 52.105499 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[1][0] =  " (ppip > 0.511000 && ppip < 0.881000 )&&(piplabtheta > 0.000000 && piplabtheta < 24.916500 ) " ; 
		pip_ptcut[1][1] =  " (ppip > 0.511000 && ppip < 0.881000 )&&(piplabtheta > 24.916500 && piplabtheta < 37.939499 ) " ; 
		pip_ptcut[1][2] =  " (ppip > 0.511000 && ppip < 0.881000 )&&(piplabtheta > 37.939499 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[2][0] =  " (ppip > 0.881000 && ppip < 4.000000 )&&(piplabtheta > 0.000000 && piplabtheta < 15.034500 ) " ; 
		pip_ptcut[2][1] =  " (ppip > 0.881000 && ppip < 4.000000 )&&(piplabtheta > 15.034500 && piplabtheta < 23.566500 ) " ; 
		pip_ptcut[2][2] =  " (ppip > 0.881000 && ppip < 4.000000 )&&(piplabtheta > 23.566500 && piplabtheta < 90.000000 ) " ; 

		pim_ptcut[0][0] =  " (ppim > 0.000000 && ppim < 0.602600 )&&(pimlabtheta > 0.000000 && pimlabtheta < 41.197498 ) " ; 
		pim_ptcut[0][1] =  " (ppim > 0.000000 && ppim < 0.602600 )&&(pimlabtheta > 41.197498 && pimlabtheta < 55.489498 ) " ; 
		pim_ptcut[0][2] =  " (ppim > 0.000000 && ppim < 0.602600 )&&(pimlabtheta > 55.489498 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[1][0] =  " (ppim > 0.602600 && ppim < 0.903800 )&&(pimlabtheta > 0.000000 && pimlabtheta < 31.207500 ) " ; 
		pim_ptcut[1][1] =  " (ppim > 0.602600 && ppim < 0.903800 )&&(pimlabtheta > 31.207500 && pimlabtheta < 41.611500 ) " ; 
		pim_ptcut[1][2] =  " (ppim > 0.602600 && ppim < 0.903800 )&&(pimlabtheta > 41.611500 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[2][0] =  " (ppim > 0.903800 && ppim < 4.000000 )&&(pimlabtheta > 0.000000 && pimlabtheta < 20.452499 ) " ; 
		pim_ptcut[2][1] =  " (ppim > 0.903800 && ppim < 4.000000 )&&(pimlabtheta > 20.452499 && pimlabtheta < 28.156500 ) " ; 
		pim_ptcut[2][2] =  " (ppim > 0.903800 && ppim < 4.000000 )&&(pimlabtheta > 28.156500 && pimlabtheta < 90.000000 ) " ;
	}

	if (Np == 15 && Nt == 15)
	{
		pip_ptcut[0][0] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 0.000000 && piplabtheta < 23.143499 ) " ; 
		pip_ptcut[0][1] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 23.143499 && piplabtheta < 29.479500 ) " ; 
		pip_ptcut[0][2] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 29.479500 && piplabtheta < 34.357498 ) " ; 
		pip_ptcut[0][3] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 34.357498 && piplabtheta < 38.587502 ) " ; 
		pip_ptcut[0][4] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 38.587502 && piplabtheta < 42.367500 ) " ; 
		pip_ptcut[0][5] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 42.367500 && piplabtheta < 45.877499 ) " ; 
		pip_ptcut[0][6] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 45.877499 && piplabtheta < 48.982498 ) " ; 
		pip_ptcut[0][7] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 48.982498 && piplabtheta < 51.907501 ) " ; 
		pip_ptcut[0][8] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 51.907501 && piplabtheta < 54.760502 ) " ; 
		pip_ptcut[0][9] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 54.760502 && piplabtheta < 57.748501 ) " ; 
		pip_ptcut[0][10] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 57.748501 && piplabtheta < 60.943501 ) " ; 
		pip_ptcut[0][11] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 60.943501 && piplabtheta < 64.705498 ) " ; 
		pip_ptcut[0][12] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 64.705498 && piplabtheta < 69.322502 ) " ; 
		pip_ptcut[0][13] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 69.322502 && piplabtheta < 75.730499 ) " ; 
		pip_ptcut[0][14] =  " (ppip > 0.000000 && ppip < 0.245000 )&&(piplabtheta > 75.730499 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[1][0] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 0.000000 && piplabtheta < 19.192499 ) " ; 
		pip_ptcut[1][1] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 19.192499 && piplabtheta < 25.528500 ) " ; 
		pip_ptcut[1][2] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 25.528500 && piplabtheta < 30.163500 ) " ; 
		pip_ptcut[1][3] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 30.163500 && piplabtheta < 34.357498 ) " ; 
		pip_ptcut[1][4] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 34.357498 && piplabtheta < 38.263500 ) " ; 
		pip_ptcut[1][5] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 38.263500 && piplabtheta < 41.863499 ) " ; 
		pip_ptcut[1][6] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 41.863499 && piplabtheta < 45.382500 ) " ; 
		pip_ptcut[1][7] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 45.382500 && piplabtheta < 48.757500 ) " ; 
		pip_ptcut[1][8] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 48.757500 && piplabtheta < 51.961498 ) " ; 
		pip_ptcut[1][9] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 51.961498 && piplabtheta < 55.165501 ) " ; 
		pip_ptcut[1][10] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 55.165501 && piplabtheta < 58.234501 ) " ; 
		pip_ptcut[1][11] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 58.234501 && piplabtheta < 61.519501 ) " ; 
		pip_ptcut[1][12] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 61.519501 && piplabtheta < 65.425499 ) " ; 
		pip_ptcut[1][13] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 65.425499 && piplabtheta < 71.302498 ) " ; 
		pip_ptcut[1][14] =  " (ppip > 0.245000 && ppip < 0.317400 )&&(piplabtheta > 71.302498 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[2][0] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 0.000000 && piplabtheta < 16.546499 ) " ; 
		pip_ptcut[2][1] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 16.546499 && piplabtheta < 22.063499 ) " ; 
		pip_ptcut[2][2] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 22.063499 && piplabtheta < 26.995501 ) " ; 
		pip_ptcut[2][3] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 26.995501 && piplabtheta < 31.063499 ) " ; 
		pip_ptcut[2][4] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 31.063499 && piplabtheta < 34.708500 ) " ; 
		pip_ptcut[2][5] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 34.708500 && piplabtheta < 38.317501 ) " ; 
		pip_ptcut[2][6] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 38.317501 && piplabtheta < 41.683498 ) " ; 
		pip_ptcut[2][7] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 41.683498 && piplabtheta < 44.968498 ) " ; 
		pip_ptcut[2][8] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 44.968498 && piplabtheta < 48.361500 ) " ; 
		pip_ptcut[2][9] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 48.361500 && piplabtheta < 51.691502 ) " ; 
		pip_ptcut[2][10] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 51.691502 && piplabtheta < 55.129501 ) " ; 
		pip_ptcut[2][11] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 55.129501 && piplabtheta < 58.630501 ) " ; 
		pip_ptcut[2][12] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 58.630501 && piplabtheta < 62.572498 ) " ; 
		pip_ptcut[2][13] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 62.572498 && piplabtheta < 67.936501 ) " ; 
		pip_ptcut[2][14] =  " (ppip > 0.317400 && ppip < 0.383000 )&&(piplabtheta > 67.936501 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[3][0] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 0.000000 && piplabtheta < 15.367500 ) " ; 
		pip_ptcut[3][1] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 15.367500 && piplabtheta < 20.110500 ) " ; 
		pip_ptcut[3][2] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 20.110500 && piplabtheta < 24.079500 ) " ; 
		pip_ptcut[3][3] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 24.079500 && piplabtheta < 27.697500 ) " ; 
		pip_ptcut[3][4] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 27.697500 && piplabtheta < 31.531500 ) " ; 
		pip_ptcut[3][5] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 31.531500 && piplabtheta < 34.852501 ) " ; 
		pip_ptcut[3][6] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 34.852501 && piplabtheta < 38.218498 ) " ; 
		pip_ptcut[3][7] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 38.218498 && piplabtheta < 41.530499 ) " ; 
		pip_ptcut[3][8] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 41.530499 && piplabtheta < 44.761501 ) " ; 
		pip_ptcut[3][9] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 44.761501 && piplabtheta < 48.073502 ) " ; 
		pip_ptcut[3][10] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 48.073502 && piplabtheta < 51.691502 ) " ; 
		pip_ptcut[3][11] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 51.691502 && piplabtheta < 55.633499 ) " ; 
		pip_ptcut[3][12] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 55.633499 && piplabtheta < 60.106499 ) " ; 
		pip_ptcut[3][13] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 60.106499 && piplabtheta < 65.884499 ) " ; 
		pip_ptcut[3][14] =  " (ppip > 0.383000 && ppip < 0.446200 )&&(piplabtheta > 65.884499 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[4][0] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 0.000000 && piplabtheta < 15.052500 ) " ; 
		pip_ptcut[4][1] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 15.052500 && piplabtheta < 19.678499 ) " ; 
		pip_ptcut[4][2] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 19.678499 && piplabtheta < 23.323500 ) " ; 
		pip_ptcut[4][3] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 23.323500 && piplabtheta < 26.392500 ) " ; 
		pip_ptcut[4][4] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 26.392500 && piplabtheta < 29.452499 ) " ; 
		pip_ptcut[4][5] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 29.452499 && piplabtheta < 32.926498 ) " ; 
		pip_ptcut[4][6] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 32.926498 && piplabtheta < 36.085499 ) " ; 
		pip_ptcut[4][7] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 36.085499 && piplabtheta < 39.208500 ) " ; 
		pip_ptcut[4][8] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 39.208500 && piplabtheta < 42.484501 ) " ; 
		pip_ptcut[4][9] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 42.484501 && piplabtheta < 45.805500 ) " ; 
		pip_ptcut[4][10] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 45.805500 && piplabtheta < 49.324501 ) " ; 
		pip_ptcut[4][11] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 49.324501 && piplabtheta < 53.347500 ) " ; 
		pip_ptcut[4][12] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 53.347500 && piplabtheta < 58.099499 ) " ; 
		pip_ptcut[4][13] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 58.099499 && piplabtheta < 64.237503 ) " ; 
		pip_ptcut[4][14] =  " (ppip > 0.446200 && ppip < 0.510200 )&&(piplabtheta > 64.237503 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[5][0] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 0.000000 && piplabtheta < 14.746500 ) " ; 
		pip_ptcut[5][1] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 14.746500 && piplabtheta < 18.832500 ) " ; 
		pip_ptcut[5][2] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 18.832500 && piplabtheta < 22.297501 ) " ; 
		pip_ptcut[5][3] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 22.297501 && piplabtheta < 25.330500 ) " ; 
		pip_ptcut[5][4] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 25.330500 && piplabtheta < 28.075500 ) " ; 
		pip_ptcut[5][5] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 28.075500 && piplabtheta < 30.946501 ) " ; 
		pip_ptcut[5][6] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 30.946501 && piplabtheta < 34.276501 ) " ; 
		pip_ptcut[5][7] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 34.276501 && piplabtheta < 37.336498 ) " ; 
		pip_ptcut[5][8] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 37.336498 && piplabtheta < 40.396500 ) " ; 
		pip_ptcut[5][9] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 40.396500 && piplabtheta < 43.636501 ) " ; 
		pip_ptcut[5][10] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 43.636501 && piplabtheta < 47.038502 ) " ; 
		pip_ptcut[5][11] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 47.038502 && piplabtheta < 51.025501 ) " ; 
		pip_ptcut[5][12] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 51.025501 && piplabtheta < 55.912498 ) " ; 
		pip_ptcut[5][13] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 55.912498 && piplabtheta < 62.329498 ) " ; 
		pip_ptcut[5][14] =  " (ppip > 0.510200 && ppip < 0.575400 )&&(piplabtheta > 62.329498 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[6][0] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 0.000000 && piplabtheta < 14.224500 ) " ; 
		pip_ptcut[6][1] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 14.224500 && piplabtheta < 17.959499 ) " ; 
		pip_ptcut[6][2] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 17.959499 && piplabtheta < 21.082500 ) " ; 
		pip_ptcut[6][3] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 21.082500 && piplabtheta < 24.043501 ) " ; 
		pip_ptcut[6][4] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 24.043501 && piplabtheta < 26.743500 ) " ; 
		pip_ptcut[6][5] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 26.743500 && piplabtheta < 29.335501 ) " ; 
		pip_ptcut[6][6] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 29.335501 && piplabtheta < 32.053501 ) " ; 
		pip_ptcut[6][7] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 32.053501 && piplabtheta < 35.167500 ) " ; 
		pip_ptcut[6][8] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 35.167500 && piplabtheta < 38.110500 ) " ; 
		pip_ptcut[6][9] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 38.110500 && piplabtheta < 41.134499 ) " ; 
		pip_ptcut[6][10] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 41.134499 && piplabtheta < 44.392502 ) " ; 
		pip_ptcut[6][11] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 44.392502 && piplabtheta < 47.929501 ) " ; 
		pip_ptcut[6][12] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 47.929501 && piplabtheta < 52.546501 ) " ; 
		pip_ptcut[6][13] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 52.546501 && piplabtheta < 58.900501 ) " ; 
		pip_ptcut[6][14] =  " (ppip > 0.575400 && ppip < 0.643000 )&&(piplabtheta > 58.900501 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[7][0] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 0.000000 && piplabtheta < 13.612500 ) " ; 
		pip_ptcut[7][1] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 13.612500 && piplabtheta < 16.996500 ) " ; 
		pip_ptcut[7][2] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 16.996500 && piplabtheta < 19.858500 ) " ; 
		pip_ptcut[7][3] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 19.858500 && piplabtheta < 22.522499 ) " ; 
		pip_ptcut[7][4] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 22.522499 && piplabtheta < 25.267500 ) " ; 
		pip_ptcut[7][5] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 25.267500 && piplabtheta < 27.796499 ) " ; 
		pip_ptcut[7][6] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 27.796499 && piplabtheta < 30.235500 ) " ; 
		pip_ptcut[7][7] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 30.235500 && piplabtheta < 32.737499 ) " ; 
		pip_ptcut[7][8] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 32.737499 && piplabtheta < 35.653500 ) " ; 
		pip_ptcut[7][9] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 35.653500 && piplabtheta < 38.380501 ) " ; 
		pip_ptcut[7][10] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 38.380501 && piplabtheta < 41.206501 ) " ; 
		pip_ptcut[7][11] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 41.206501 && piplabtheta < 44.545502 ) " ; 
		pip_ptcut[7][12] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 44.545502 && piplabtheta < 48.613499 ) " ; 
		pip_ptcut[7][13] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 48.613499 && piplabtheta < 55.093498 ) " ; 
		pip_ptcut[7][14] =  " (ppip > 0.643000 && ppip < 0.714600 )&&(piplabtheta > 55.093498 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[8][0] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 0.000000 && piplabtheta < 12.847500 ) " ; 
		pip_ptcut[8][1] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 12.847500 && piplabtheta < 15.952500 ) " ; 
		pip_ptcut[8][2] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 15.952500 && piplabtheta < 18.607500 ) " ; 
		pip_ptcut[8][3] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 18.607500 && piplabtheta < 21.082500 ) " ; 
		pip_ptcut[8][4] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 21.082500 && piplabtheta < 23.548500 ) " ; 
		pip_ptcut[8][5] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 23.548500 && piplabtheta < 26.005501 ) " ; 
		pip_ptcut[8][6] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 26.005501 && piplabtheta < 28.309500 ) " ; 
		pip_ptcut[8][7] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 28.309500 && piplabtheta < 30.505501 ) " ; 
		pip_ptcut[8][8] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 30.505501 && piplabtheta < 32.701500 ) " ; 
		pip_ptcut[8][9] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 32.701500 && piplabtheta < 35.383499 ) " ; 
		pip_ptcut[8][10] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 35.383499 && piplabtheta < 38.101501 ) " ; 
		pip_ptcut[8][11] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 38.101501 && piplabtheta < 41.161499 ) " ; 
		pip_ptcut[8][12] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 41.161499 && piplabtheta < 45.247501 ) " ; 
		pip_ptcut[8][13] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 45.247501 && piplabtheta < 51.385502 ) " ; 
		pip_ptcut[8][14] =  " (ppip > 0.714600 && ppip < 0.791800 )&&(piplabtheta > 51.385502 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[9][0] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 0.000000 && piplabtheta < 12.073500 ) " ; 
		pip_ptcut[9][1] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 12.073500 && piplabtheta < 14.872500 ) " ; 
		pip_ptcut[9][2] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 14.872500 && piplabtheta < 17.221500 ) " ; 
		pip_ptcut[9][3] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 17.221500 && piplabtheta < 19.561501 ) " ; 
		pip_ptcut[9][4] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 19.561501 && piplabtheta < 21.811501 ) " ; 
		pip_ptcut[9][5] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 21.811501 && piplabtheta < 24.070499 ) " ; 
		pip_ptcut[9][6] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 24.070499 && piplabtheta < 26.221500 ) " ; 
		pip_ptcut[9][7] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 26.221500 && piplabtheta < 28.273500 ) " ; 
		pip_ptcut[9][8] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 28.273500 && piplabtheta < 30.262501 ) " ; 
		pip_ptcut[9][9] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 30.262501 && piplabtheta < 32.278500 ) " ; 
		pip_ptcut[9][10] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 32.278500 && piplabtheta < 34.645500 ) " ; 
		pip_ptcut[9][11] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 34.645500 && piplabtheta < 37.813499 ) " ; 
		pip_ptcut[9][12] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 37.813499 && piplabtheta < 41.737499 ) " ; 
		pip_ptcut[9][13] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 41.737499 && piplabtheta < 47.929501 ) " ; 
		pip_ptcut[9][14] =  " (ppip > 0.791800 && ppip < 0.878600 )&&(piplabtheta > 47.929501 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[10][0] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 0.000000 && piplabtheta < 11.299500 ) " ; 
		pip_ptcut[10][1] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 11.299500 && piplabtheta < 13.846500 ) " ; 
		pip_ptcut[10][2] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 13.846500 && piplabtheta < 16.006500 ) " ; 
		pip_ptcut[10][3] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 16.006500 && piplabtheta < 18.148500 ) " ; 
		pip_ptcut[10][4] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 18.148500 && piplabtheta < 20.227501 ) " ; 
		pip_ptcut[10][5] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 20.227501 && piplabtheta < 22.153500 ) " ; 
		pip_ptcut[10][6] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 22.153500 && piplabtheta < 24.115499 ) " ; 
		pip_ptcut[10][7] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 24.115499 && piplabtheta < 26.059500 ) " ; 
		pip_ptcut[10][8] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 26.059500 && piplabtheta < 28.012501 ) " ; 
		pip_ptcut[10][9] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 28.012501 && piplabtheta < 29.911501 ) " ; 
		pip_ptcut[10][10] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 29.911501 && piplabtheta < 31.945499 ) " ; 
		pip_ptcut[10][11] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 31.945499 && piplabtheta < 34.402500 ) " ; 
		pip_ptcut[10][12] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 34.402500 && piplabtheta < 38.416500 ) " ; 
		pip_ptcut[10][13] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 38.416500 && piplabtheta < 44.275501 ) " ; 
		pip_ptcut[10][14] =  " (ppip > 0.878600 && ppip < 0.982600 )&&(piplabtheta > 44.275501 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[11][0] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 0.000000 && piplabtheta < 10.471500 ) " ; 
		pip_ptcut[11][1] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 10.471500 && piplabtheta < 12.775500 ) " ; 
		pip_ptcut[11][2] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 12.775500 && piplabtheta < 14.773500 ) " ; 
		pip_ptcut[11][3] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 14.773500 && piplabtheta < 16.663500 ) " ; 
		pip_ptcut[11][4] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 16.663500 && piplabtheta < 18.544500 ) " ; 
		pip_ptcut[11][5] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 18.544500 && piplabtheta < 20.326500 ) " ; 
		pip_ptcut[11][6] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 20.326500 && piplabtheta < 22.018499 ) " ; 
		pip_ptcut[11][7] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 22.018499 && piplabtheta < 23.692499 ) " ; 
		pip_ptcut[11][8] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 23.692499 && piplabtheta < 25.447500 ) " ; 
		pip_ptcut[11][9] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 25.447500 && piplabtheta < 27.247499 ) " ; 
		pip_ptcut[11][10] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 27.247499 && piplabtheta < 29.245501 ) " ; 
		pip_ptcut[11][11] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 29.245501 && piplabtheta < 31.558500 ) " ; 
		pip_ptcut[11][12] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 31.558500 && piplabtheta < 34.609501 ) " ; 
		pip_ptcut[11][13] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 34.609501 && piplabtheta < 40.378502 ) " ; 
		pip_ptcut[11][14] =  " (ppip > 0.982600 && ppip < 1.115000 )&&(piplabtheta > 40.378502 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[12][0] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 0.000000 && piplabtheta < 9.769500 ) " ; 
		pip_ptcut[12][1] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 9.769500 && piplabtheta < 11.695500 ) " ; 
		pip_ptcut[12][2] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 11.695500 && piplabtheta < 13.414500 ) " ; 
		pip_ptcut[12][3] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 13.414500 && piplabtheta < 15.079500 ) " ; 
		pip_ptcut[12][4] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 15.079500 && piplabtheta < 16.663500 ) " ; 
		pip_ptcut[12][5] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 16.663500 && piplabtheta < 18.175501 ) " ; 
		pip_ptcut[12][6] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 18.175501 && piplabtheta < 19.660500 ) " ; 
		pip_ptcut[12][7] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 19.660500 && piplabtheta < 21.181499 ) " ; 
		pip_ptcut[12][8] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 21.181499 && piplabtheta < 22.666500 ) " ; 
		pip_ptcut[12][9] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 22.666500 && piplabtheta < 24.268499 ) " ; 
		pip_ptcut[12][10] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 24.268499 && piplabtheta < 26.077499 ) " ; 
		pip_ptcut[12][11] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 26.077499 && piplabtheta < 28.255501 ) " ; 
		pip_ptcut[12][12] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 28.255501 && piplabtheta < 31.153500 ) " ; 
		pip_ptcut[12][13] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 31.153500 && piplabtheta < 35.527500 ) " ; 
		pip_ptcut[12][14] =  " (ppip > 1.115000 && ppip < 1.300200 )&&(piplabtheta > 35.527500 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[13][0] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 0.000000 && piplabtheta < 8.968500 ) " ; 
		pip_ptcut[13][1] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 8.968500 && piplabtheta < 10.669500 ) " ; 
		pip_ptcut[13][2] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 10.669500 && piplabtheta < 11.974500 ) " ; 
		pip_ptcut[13][3] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 11.974500 && piplabtheta < 13.162500 ) " ; 
		pip_ptcut[13][4] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 13.162500 && piplabtheta < 14.323500 ) " ; 
		pip_ptcut[13][5] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 14.323500 && piplabtheta < 15.493500 ) " ; 
		pip_ptcut[13][6] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 15.493500 && piplabtheta < 16.744499 ) " ; 
		pip_ptcut[13][7] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 16.744499 && piplabtheta < 17.995501 ) " ; 
		pip_ptcut[13][8] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 17.995501 && piplabtheta < 19.309500 ) " ; 
		pip_ptcut[13][9] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 19.309500 && piplabtheta < 20.731501 ) " ; 
		pip_ptcut[13][10] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 20.731501 && piplabtheta < 22.315500 ) " ; 
		pip_ptcut[13][11] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 22.315500 && piplabtheta < 24.295500 ) " ; 
		pip_ptcut[13][12] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 24.295500 && piplabtheta < 27.049500 ) " ; 
		pip_ptcut[13][13] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 27.049500 && piplabtheta < 31.234501 ) " ; 
		pip_ptcut[13][14] =  " (ppip > 1.300200 && ppip < 1.641400 )&&(piplabtheta > 31.234501 && piplabtheta < 90.000000 ) " ; 
		pip_ptcut[14][0] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 0.000000 && piplabtheta < 7.348500 ) " ; 
		pip_ptcut[14][1] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 7.348500 && piplabtheta < 8.383500 ) " ; 
		pip_ptcut[14][2] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 8.383500 && piplabtheta < 9.328500 ) " ; 
		pip_ptcut[14][3] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 9.328500 && piplabtheta < 10.273500 ) " ; 
		pip_ptcut[14][4] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 10.273500 && piplabtheta < 11.092500 ) " ; 
		pip_ptcut[14][5] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 11.092500 && piplabtheta < 11.893500 ) " ; 
		pip_ptcut[14][6] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 11.893500 && piplabtheta < 12.721500 ) " ; 
		pip_ptcut[14][7] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 12.721500 && piplabtheta < 13.558500 ) " ; 
		pip_ptcut[14][8] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 13.558500 && piplabtheta < 14.467500 ) " ; 
		pip_ptcut[14][9] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 14.467500 && piplabtheta < 15.457500 ) " ; 
		pip_ptcut[14][10] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 15.457500 && piplabtheta < 16.636499 ) " ; 
		pip_ptcut[14][11] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 16.636499 && piplabtheta < 18.166500 ) " ; 
		pip_ptcut[14][12] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 18.166500 && piplabtheta < 20.218500 ) " ; 
		pip_ptcut[14][13] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 20.218500 && piplabtheta < 23.566500 ) " ; 
		pip_ptcut[14][14] =  " (ppip > 1.641400 && ppip < 4.000000 )&&(piplabtheta > 23.566500 && piplabtheta < 90.000000 ) " ; 



		pim_ptcut[0][0] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 0.000000 && pimlabtheta < 35.788502 ) " ; 
		pim_ptcut[0][1] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 35.788502 && pimlabtheta < 39.793499 ) " ; 
		pim_ptcut[0][2] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 39.793499 && pimlabtheta < 43.150501 ) " ; 
		pim_ptcut[0][3] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 43.150501 && pimlabtheta < 46.084499 ) " ; 
		pim_ptcut[0][4] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 46.084499 && pimlabtheta < 48.802502 ) " ; 
		pim_ptcut[0][5] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 48.802502 && pimlabtheta < 51.421501 ) " ; 
		pim_ptcut[0][6] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 51.421501 && pimlabtheta < 54.022499 ) " ; 
		pim_ptcut[0][7] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 54.022499 && pimlabtheta < 56.569500 ) " ; 
		pim_ptcut[0][8] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 56.569500 && pimlabtheta < 59.179501 ) " ; 
		pim_ptcut[0][9] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 59.179501 && pimlabtheta < 61.915501 ) " ; 
		pim_ptcut[0][10] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 61.915501 && pimlabtheta < 64.840500 ) " ; 
		pim_ptcut[0][11] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 64.840500 && pimlabtheta < 68.080498 ) " ; 
		pim_ptcut[0][12] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 68.080498 && pimlabtheta < 72.067497 ) " ; 
		pim_ptcut[0][13] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 72.067497 && pimlabtheta < 77.260498 ) " ; 
		pim_ptcut[0][14] =  " (ppim > 0.000000 && ppim < 0.331000 )&&(pimlabtheta > 77.260498 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[1][0] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 0.000000 && pimlabtheta < 30.235500 ) " ; 
		pim_ptcut[1][1] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 30.235500 && pimlabtheta < 33.772499 ) " ; 
		pim_ptcut[1][2] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 33.772499 && pimlabtheta < 36.886501 ) " ; 
		pim_ptcut[1][3] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 36.886501 && pimlabtheta < 39.793499 ) " ; 
		pim_ptcut[1][4] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 39.793499 && pimlabtheta < 42.502499 ) " ; 
		pim_ptcut[1][5] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 42.502499 && pimlabtheta < 45.193501 ) " ; 
		pim_ptcut[1][6] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 45.193501 && pimlabtheta < 47.884499 ) " ; 
		pim_ptcut[1][7] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 47.884499 && pimlabtheta < 50.557499 ) " ; 
		pim_ptcut[1][8] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 50.557499 && pimlabtheta < 53.356499 ) " ; 
		pim_ptcut[1][9] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 53.356499 && pimlabtheta < 56.209499 ) " ; 
		pim_ptcut[1][10] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 56.209499 && pimlabtheta < 59.179501 ) " ; 
		pim_ptcut[1][11] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 59.179501 && pimlabtheta < 62.518501 ) " ; 
		pim_ptcut[1][12] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 62.518501 && pimlabtheta < 66.694504 ) " ; 
		pim_ptcut[1][13] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 66.694504 && pimlabtheta < 72.940498 ) " ; 
		pim_ptcut[1][14] =  " (ppim > 0.331000 && ppim < 0.418600 )&&(pimlabtheta > 72.940498 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[2][0] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 0.000000 && pimlabtheta < 27.706499 ) " ; 
		pim_ptcut[2][1] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 27.706499 && pimlabtheta < 31.243500 ) " ; 
		pim_ptcut[2][2] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 31.243500 && pimlabtheta < 34.276501 ) " ; 
		pim_ptcut[2][3] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 34.276501 && pimlabtheta < 37.165501 ) " ; 
		pim_ptcut[2][4] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 37.165501 && pimlabtheta < 39.919498 ) " ; 
		pim_ptcut[2][5] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 39.919498 && pimlabtheta < 42.691502 ) " ; 
		pim_ptcut[2][6] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 42.691502 && pimlabtheta < 45.481499 ) " ; 
		pim_ptcut[2][7] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 45.481499 && pimlabtheta < 48.226501 ) " ; 
		pim_ptcut[2][8] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 48.226501 && pimlabtheta < 51.133499 ) " ; 
		pim_ptcut[2][9] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 51.133499 && pimlabtheta < 54.148499 ) " ; 
		pim_ptcut[2][10] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 54.148499 && pimlabtheta < 57.343498 ) " ; 
		pim_ptcut[2][11] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 57.343498 && pimlabtheta < 60.979500 ) " ; 
		pim_ptcut[2][12] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 60.979500 && pimlabtheta < 65.578499 ) " ; 
		pim_ptcut[2][13] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 65.578499 && pimlabtheta < 72.427498 ) " ; 
		pim_ptcut[2][14] =  " (ppim > 0.418600 && ppim < 0.487800 )&&(pimlabtheta > 72.427498 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[3][0] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 0.000000 && pimlabtheta < 26.203501 ) " ; 
		pim_ptcut[3][1] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 26.203501 && pimlabtheta < 29.713499 ) " ; 
		pim_ptcut[3][2] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 29.713499 && pimlabtheta < 32.746498 ) " ; 
		pim_ptcut[3][3] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 32.746498 && pimlabtheta < 35.635502 ) " ; 
		pim_ptcut[3][4] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 35.635502 && pimlabtheta < 38.389500 ) " ; 
		pim_ptcut[3][5] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 38.389500 && pimlabtheta < 41.098499 ) " ; 
		pim_ptcut[3][6] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 41.098499 && pimlabtheta < 43.843498 ) " ; 
		pim_ptcut[3][7] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 43.843498 && pimlabtheta < 46.516499 ) " ; 
		pim_ptcut[3][8] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 46.516499 && pimlabtheta < 49.378502 ) " ; 
		pim_ptcut[3][9] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 49.378502 && pimlabtheta < 52.501499 ) " ; 
		pim_ptcut[3][10] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 52.501499 && pimlabtheta < 55.867500 ) " ; 
		pim_ptcut[3][11] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 55.867500 && pimlabtheta < 59.638500 ) " ; 
		pim_ptcut[3][12] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 59.638500 && pimlabtheta < 64.219498 ) " ; 
		pim_ptcut[3][13] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 64.219498 && pimlabtheta < 70.591499 ) " ; 
		pim_ptcut[3][14] =  " (ppim > 0.487800 && ppim < 0.547400 )&&(pimlabtheta > 70.591499 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[4][0] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 0.000000 && pimlabtheta < 25.015499 ) " ; 
		pim_ptcut[4][1] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 25.015499 && pimlabtheta < 28.471500 ) " ; 
		pim_ptcut[4][2] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 28.471500 && pimlabtheta < 31.540501 ) " ; 
		pim_ptcut[4][3] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 31.540501 && pimlabtheta < 34.366501 ) " ; 
		pim_ptcut[4][4] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 34.366501 && pimlabtheta < 37.030499 ) " ; 
		pim_ptcut[4][5] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 37.030499 && pimlabtheta < 39.586498 ) " ; 
		pim_ptcut[4][6] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 39.586498 && pimlabtheta < 42.169498 ) " ; 
		pim_ptcut[4][7] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 42.169498 && pimlabtheta < 44.716499 ) " ; 
		pim_ptcut[4][8] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 44.716499 && pimlabtheta < 47.452499 ) " ; 
		pim_ptcut[4][9] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 47.452499 && pimlabtheta < 50.575500 ) " ; 
		pim_ptcut[4][10] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 50.575500 && pimlabtheta < 53.932499 ) " ; 
		pim_ptcut[4][11] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 53.932499 && pimlabtheta < 57.586498 ) " ; 
		pim_ptcut[4][12] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 57.586498 && pimlabtheta < 61.663502 ) " ; 
		pim_ptcut[4][13] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 61.663502 && pimlabtheta < 67.360497 ) " ; 
		pim_ptcut[4][14] =  " (ppim > 0.547400 && ppim < 0.602200 )&&(pimlabtheta > 67.360497 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[5][0] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 0.000000 && pimlabtheta < 23.998501 ) " ; 
		pim_ptcut[5][1] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 23.998501 && pimlabtheta < 27.292500 ) " ; 
		pim_ptcut[5][2] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 27.292500 && pimlabtheta < 30.253500 ) " ; 
		pim_ptcut[5][3] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 30.253500 && pimlabtheta < 32.881500 ) " ; 
		pim_ptcut[5][4] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 32.881500 && pimlabtheta < 35.401501 ) " ; 
		pim_ptcut[5][5] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 35.401501 && pimlabtheta < 37.768501 ) " ; 
		pim_ptcut[5][6] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 37.768501 && pimlabtheta < 40.090500 ) " ; 
		pim_ptcut[5][7] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 40.090500 && pimlabtheta < 42.394501 ) " ; 
		pim_ptcut[5][8] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 42.394501 && pimlabtheta < 44.824501 ) " ; 
		pim_ptcut[5][9] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 44.824501 && pimlabtheta < 47.641499 ) " ; 
		pim_ptcut[5][10] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 47.641499 && pimlabtheta < 50.881500 ) " ; 
		pim_ptcut[5][11] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 50.881500 && pimlabtheta < 54.436501 ) " ; 
		pim_ptcut[5][12] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 54.436501 && pimlabtheta < 58.441502 ) " ; 
		pim_ptcut[5][13] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 58.441502 && pimlabtheta < 63.481499 ) " ; 
		pim_ptcut[5][14] =  " (ppim > 0.602200 && ppim < 0.655400 )&&(pimlabtheta > 63.481499 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[6][0] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 0.000000 && pimlabtheta < 23.125500 ) " ; 
		pim_ptcut[6][1] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 23.125500 && pimlabtheta < 26.176500 ) " ; 
		pim_ptcut[6][2] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 26.176500 && pimlabtheta < 28.957500 ) " ; 
		pim_ptcut[6][3] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 28.957500 && pimlabtheta < 31.387501 ) " ; 
		pim_ptcut[6][4] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 31.387501 && pimlabtheta < 33.628502 ) " ; 
		pim_ptcut[6][5] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 33.628502 && pimlabtheta < 35.752499 ) " ; 
		pim_ptcut[6][6] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 35.752499 && pimlabtheta < 37.777500 ) " ; 
		pim_ptcut[6][7] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 37.777500 && pimlabtheta < 39.883499 ) " ; 
		pim_ptcut[6][8] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 39.883499 && pimlabtheta < 42.079498 ) " ; 
		pim_ptcut[6][9] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 42.079498 && pimlabtheta < 44.455502 ) " ; 
		pim_ptcut[6][10] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 44.455502 && pimlabtheta < 47.452499 ) " ; 
		pim_ptcut[6][11] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 47.452499 && pimlabtheta < 50.917500 ) " ; 
		pim_ptcut[6][12] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 50.917500 && pimlabtheta < 54.967499 ) " ; 
		pim_ptcut[6][13] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 54.967499 && pimlabtheta < 59.863499 ) " ; 
		pim_ptcut[6][14] =  " (ppim > 0.655400 && ppim < 0.710200 )&&(pimlabtheta > 59.863499 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[7][0] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 0.000000 && pimlabtheta < 22.279499 ) " ; 
		pim_ptcut[7][1] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 22.279499 && pimlabtheta < 25.006500 ) " ; 
		pim_ptcut[7][2] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 25.006500 && pimlabtheta < 27.499500 ) " ; 
		pim_ptcut[7][3] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 27.499500 && pimlabtheta < 29.695499 ) " ; 
		pim_ptcut[7][4] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 29.695499 && pimlabtheta < 31.675501 ) " ; 
		pim_ptcut[7][5] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 31.675501 && pimlabtheta < 33.565498 ) " ; 
		pim_ptcut[7][6] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 33.565498 && pimlabtheta < 35.419498 ) " ; 
		pim_ptcut[7][7] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 35.419498 && pimlabtheta < 37.264500 ) " ; 
		pim_ptcut[7][8] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 37.264500 && pimlabtheta < 39.271500 ) " ; 
		pim_ptcut[7][9] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 39.271500 && pimlabtheta < 41.476501 ) " ; 
		pim_ptcut[7][10] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 41.476501 && pimlabtheta < 43.996498 ) " ; 
		pim_ptcut[7][11] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 43.996498 && pimlabtheta < 47.272499 ) " ; 
		pim_ptcut[7][12] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 47.272499 && pimlabtheta < 51.268501 ) " ; 
		pim_ptcut[7][13] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 51.268501 && pimlabtheta < 56.596500 ) " ; 
		pim_ptcut[7][14] =  " (ppim > 0.710200 && ppim < 0.767800 )&&(pimlabtheta > 56.596500 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[8][0] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 0.000000 && pimlabtheta < 21.352501 ) " ; 
		pim_ptcut[8][1] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 21.352501 && pimlabtheta < 23.755501 ) " ; 
		pim_ptcut[8][2] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 23.755501 && pimlabtheta < 25.942499 ) " ; 
		pim_ptcut[8][3] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 25.942499 && pimlabtheta < 27.913500 ) " ; 
		pim_ptcut[8][4] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 27.913500 && pimlabtheta < 29.740499 ) " ; 
		pim_ptcut[8][5] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 29.740499 && pimlabtheta < 31.441500 ) " ; 
		pim_ptcut[8][6] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 31.441500 && pimlabtheta < 33.133499 ) " ; 
		pim_ptcut[8][7] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 33.133499 && pimlabtheta < 34.816502 ) " ; 
		pim_ptcut[8][8] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 34.816502 && pimlabtheta < 36.589500 ) " ; 
		pim_ptcut[8][9] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 36.589500 && pimlabtheta < 38.596500 ) " ; 
		pim_ptcut[8][10] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 38.596500 && pimlabtheta < 40.909500 ) " ; 
		pim_ptcut[8][11] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 40.909500 && pimlabtheta < 43.645500 ) " ; 
		pim_ptcut[8][12] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 43.645500 && pimlabtheta < 47.623501 ) " ; 
		pim_ptcut[8][13] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 47.623501 && pimlabtheta < 53.140499 ) " ; 
		pim_ptcut[8][14] =  " (ppim > 0.767800 && ppim < 0.830600 )&&(pimlabtheta > 53.140499 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[9][0] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 0.000000 && pimlabtheta < 20.416500 ) " ; 
		pim_ptcut[9][1] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 20.416500 && pimlabtheta < 22.558500 ) " ; 
		pim_ptcut[9][2] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 22.558500 && pimlabtheta < 24.484501 ) " ; 
		pim_ptcut[9][3] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 24.484501 && pimlabtheta < 26.239500 ) " ; 
		pim_ptcut[9][4] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 26.239500 && pimlabtheta < 27.922501 ) " ; 
		pim_ptcut[9][5] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 27.922501 && pimlabtheta < 29.533501 ) " ; 
		pim_ptcut[9][6] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 29.533501 && pimlabtheta < 31.072500 ) " ; 
		pim_ptcut[9][7] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 31.072500 && pimlabtheta < 32.674500 ) " ; 
		pim_ptcut[9][8] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 32.674500 && pimlabtheta < 34.348499 ) " ; 
		pim_ptcut[9][9] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 34.348499 && pimlabtheta < 36.175499 ) " ; 
		pim_ptcut[9][10] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 36.175499 && pimlabtheta < 38.344501 ) " ; 
		pim_ptcut[9][11] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 38.344501 && pimlabtheta < 40.945499 ) " ; 
		pim_ptcut[9][12] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 40.945499 && pimlabtheta < 44.428501 ) " ; 
		pim_ptcut[9][13] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 44.428501 && pimlabtheta < 50.080502 ) " ; 
		pim_ptcut[9][14] =  " (ppim > 0.830600 && ppim < 0.902200 )&&(pimlabtheta > 50.080502 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[10][0] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 0.000000 && pimlabtheta < 19.507500 ) " ; 
		pim_ptcut[10][1] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 19.507500 && pimlabtheta < 21.451500 ) " ; 
		pim_ptcut[10][2] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 21.451500 && pimlabtheta < 23.107500 ) " ; 
		pim_ptcut[10][3] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 23.107500 && pimlabtheta < 24.718500 ) " ; 
		pim_ptcut[10][4] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 24.718500 && pimlabtheta < 26.239500 ) " ; 
		pim_ptcut[10][5] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 26.239500 && pimlabtheta < 27.715500 ) " ; 
		pim_ptcut[10][6] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 27.715500 && pimlabtheta < 29.164499 ) " ; 
		pim_ptcut[10][7] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 29.164499 && pimlabtheta < 30.595501 ) " ; 
		pim_ptcut[10][8] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 30.595501 && pimlabtheta < 32.143501 ) " ; 
		pim_ptcut[10][9] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 32.143501 && pimlabtheta < 33.871498 ) " ; 
		pim_ptcut[10][10] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 33.871498 && pimlabtheta < 35.869499 ) " ; 
		pim_ptcut[10][11] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 35.869499 && pimlabtheta < 38.452499 ) " ; 
		pim_ptcut[10][12] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 38.452499 && pimlabtheta < 41.809502 ) " ; 
		pim_ptcut[10][13] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 41.809502 && pimlabtheta < 47.263500 ) " ; 
		pim_ptcut[10][14] =  " (ppim > 0.902200 && ppim < 0.988600 )&&(pimlabtheta > 47.263500 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[11][0] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 0.000000 && pimlabtheta < 18.409500 ) " ; 
		pim_ptcut[11][1] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 18.409500 && pimlabtheta < 20.146500 ) " ; 
		pim_ptcut[11][2] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 20.146500 && pimlabtheta < 21.595501 ) " ; 
		pim_ptcut[11][3] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 21.595501 && pimlabtheta < 22.963499 ) " ; 
		pim_ptcut[11][4] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 22.963499 && pimlabtheta < 24.313499 ) " ; 
		pim_ptcut[11][5] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 24.313499 && pimlabtheta < 25.618500 ) " ; 
		pim_ptcut[11][6] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 25.618500 && pimlabtheta < 26.995501 ) " ; 
		pim_ptcut[11][7] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 26.995501 && pimlabtheta < 28.399500 ) " ; 
		pim_ptcut[11][8] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 28.399500 && pimlabtheta < 29.875500 ) " ; 
		pim_ptcut[11][9] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 29.875500 && pimlabtheta < 31.585501 ) " ; 
		pim_ptcut[11][10] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 31.585501 && pimlabtheta < 33.565498 ) " ; 
		pim_ptcut[11][11] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 33.565498 && pimlabtheta < 36.067501 ) " ; 
		pim_ptcut[11][12] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 36.067501 && pimlabtheta < 39.424500 ) " ; 
		pim_ptcut[11][13] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 39.424500 && pimlabtheta < 44.311501 ) " ; 
		pim_ptcut[11][14] =  " (ppim > 0.988600 && ppim < 1.102600 )&&(pimlabtheta > 44.311501 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[12][0] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 0.000000 && pimlabtheta < 17.023500 ) " ; 
		pim_ptcut[12][1] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 17.023500 && pimlabtheta < 18.481501 ) " ; 
		pim_ptcut[12][2] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 18.481501 && pimlabtheta < 19.759501 ) " ; 
		pim_ptcut[12][3] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 19.759501 && pimlabtheta < 20.947500 ) " ; 
		pim_ptcut[12][4] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 20.947500 && pimlabtheta < 22.063499 ) " ; 
		pim_ptcut[12][5] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 22.063499 && pimlabtheta < 23.197500 ) " ; 
		pim_ptcut[12][6] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 23.197500 && pimlabtheta < 24.322500 ) " ; 
		pim_ptcut[12][7] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 24.322500 && pimlabtheta < 25.546499 ) " ; 
		pim_ptcut[12][8] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 25.546499 && pimlabtheta < 26.950500 ) " ; 
		pim_ptcut[12][9] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 26.950500 && pimlabtheta < 28.543501 ) " ; 
		pim_ptcut[12][10] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 28.543501 && pimlabtheta < 30.505501 ) " ; 
		pim_ptcut[12][11] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 30.505501 && pimlabtheta < 33.007500 ) " ; 
		pim_ptcut[12][12] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 33.007500 && pimlabtheta < 36.382500 ) " ; 
		pim_ptcut[12][13] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 36.382500 && pimlabtheta < 40.891499 ) " ; 
		pim_ptcut[12][14] =  " (ppim > 1.102600 && ppim < 1.271800 )&&(pimlabtheta > 40.891499 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[13][0] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 0.000000 && pimlabtheta < 15.331500 ) " ; 
		pim_ptcut[13][1] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 15.331500 && pimlabtheta < 16.357500 ) " ; 
		pim_ptcut[13][2] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 16.357500 && pimlabtheta < 17.320499 ) " ; 
		pim_ptcut[13][3] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 17.320499 && pimlabtheta < 18.238501 ) " ; 
		pim_ptcut[13][4] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 18.238501 && pimlabtheta < 19.120501 ) " ; 
		pim_ptcut[13][5] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 19.120501 && pimlabtheta < 19.993500 ) " ; 
		pim_ptcut[13][6] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 19.993500 && pimlabtheta < 20.893499 ) " ; 
		pim_ptcut[13][7] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 20.893499 && pimlabtheta < 21.865499 ) " ; 
		pim_ptcut[13][8] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 21.865499 && pimlabtheta < 22.972500 ) " ; 
		pim_ptcut[13][9] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 22.972500 && pimlabtheta < 24.250500 ) " ; 
		pim_ptcut[13][10] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 24.250500 && pimlabtheta < 25.924500 ) " ; 
		pim_ptcut[13][11] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 25.924500 && pimlabtheta < 28.273500 ) " ; 
		pim_ptcut[13][12] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 28.273500 && pimlabtheta < 31.549500 ) " ; 
		pim_ptcut[13][13] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 31.549500 && pimlabtheta < 36.139500 ) " ; 
		pim_ptcut[13][14] =  " (ppim > 1.271800 && ppim < 1.585400 )&&(pimlabtheta > 36.139500 && pimlabtheta < 90.000000 ) " ; 
		pim_ptcut[14][0] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 0.000000 && pimlabtheta < 12.451500 ) " ; 
		pim_ptcut[14][1] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 12.451500 && pimlabtheta < 13.306500 ) " ; 
		pim_ptcut[14][2] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 13.306500 && pimlabtheta < 13.972500 ) " ; 
		pim_ptcut[14][3] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 13.972500 && pimlabtheta < 14.584500 ) " ; 
		pim_ptcut[14][4] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 14.584500 && pimlabtheta < 15.196500 ) " ; 
		pim_ptcut[14][5] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 15.196500 && pimlabtheta < 15.835500 ) " ; 
		pim_ptcut[14][6] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 15.835500 && pimlabtheta < 16.546499 ) " ; 
		pim_ptcut[14][7] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 16.546499 && pimlabtheta < 17.347500 ) " ; 
		pim_ptcut[14][8] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 17.347500 && pimlabtheta < 18.229500 ) " ; 
		pim_ptcut[14][9] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 18.229500 && pimlabtheta < 19.210501 ) " ; 
		pim_ptcut[14][10] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 19.210501 && pimlabtheta < 20.398500 ) " ; 
		pim_ptcut[14][11] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 20.398500 && pimlabtheta < 21.928499 ) " ; 
		pim_ptcut[14][12] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 21.928499 && pimlabtheta < 24.052500 ) " ; 
		pim_ptcut[14][13] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 24.052500 && pimlabtheta < 27.895500 ) " ; 
		pim_ptcut[14][14] =  " (ppim > 1.585400 && ppim < 4.000000 )&&(pimlabtheta > 27.895500 && pimlabtheta < 90.000000 ) " ;		
	}


	TCut pip_seccut[Ns];
	pip_seccut[0] = "pipsector == 1";
	pip_seccut[1] = "pipsector == 2";
	pip_seccut[2] = "pipsector == 3";
	pip_seccut[3] = "pipsector == 4";
	pip_seccut[4] = "pipsector == 5";
	pip_seccut[5] = "pipsector == 6";
	TCut pim_seccut[Ns];	
	pim_seccut[0] = "pimsector == 1";
	pim_seccut[1] = "pimsector == 2";
	pim_seccut[2] = "pimsector == 3";
	pim_seccut[3] = "pimsector == 4";
	pim_seccut[4] = "pimsector == 5";
	pim_seccut[5] = "pimsector == 6";





	///////////////////////////////////////////////// begin pip calculation ////////////////////////////////////////////////////	
	//get bin centers for momentum	
	//TCanvas *cpcenter_pip = new TCanvas("cpcenter_pip","cpcenter_pip",1000,800);
	//cpcenter_pip->Divide(Np,Nt);
	int cancount = 1;	
	TH1F *hpcenter_pip[Np][Nt];
	Double_t pcenter_pip[Np][Nt] = {0};
	Double_t prms_pip[Np][Nt] = {0};
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{ 
		//	cpcenter_pip->cd(cancount);
			hpcenter_pip[p][t] = new TH1F(Form("hpcenter_pip_p%i_t%i",p,t),"",200,0,4);
			tdata->Draw(Form("ppip>>hpcenter_pip_p%i_t%i",p,t),pip_ptcut[p][t]);
			hpcenter_pip[p][t]->GetXaxis()->SetTitle("pip momentum (GeV)");
			hpcenter_pip[p][t]->Write();
			cancount += 1;
		}
	}
	
	
	//get bin centers for theta	
	//TCanvas *ctcenter_pip = new TCanvas("ctcenter_pip","ctcenter_pip",1000,800);
	//ctcenter_pip->Divide(Np,Nt);
	int cancount = 1;	
	TH1F *htcenter_pip[Np][Nt];
	Double_t tcenter_pip[Np][Nt] = {0};
	Double_t trms_pip[Np][Nt] = {0};
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{ 
		//	ctcenter_pip->cd(cancount);
			htcenter_pip[p][t] = new TH1F(Form("htcenter_pip_p%i_t%i",p,t),"",200,0,180);
			tdata->Draw(Form("piplabtheta>>htcenter_pip_p%i_t%i",p,t),pip_ptcut[p][t]);
			htcenter_pip[p][t]->GetXaxis()->SetTitle("pip #theta (deg)");
			htcenter_pip[p][t]->Write();
			cancount += 1;
			
			tcenter_pip[p][t] =  htcenter_pip[p][t]->GetMean();
			cout << "tcenter pip = " << htcenter_pip[p][t]->GetMean() <<endl;
		}
	}
	cout << "tcenters pip = " <<tcenter_pip[0][0] << ",  " <<tcenter_pip[0][1] <<",  " << tcenter_pip[0][2] <<endl;
	

	
	
	//TCanvas *cphi_pip[Np][Nt];
	TH1F *hphidiff_pip[Np][Nt][Ns];
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
			//cphi_pip[p][t] = new TCanvas(Form("cphi_pip_p%i_t%i",p,t),Form("cphi_pip_p%i_t%i",p,t),1000,800);
			//cphi_pip[p][t]->Divide(2,3);
			for (int s=0; s<Ns; s++)
			{
			//	cphi_pip[p][t]->cd(s+1);
				hphidiff_pip[p][t][s] = new TH1F(Form("hphidiff_pip_p%i_t%i_s%i",p,t,s),"",100,-30,30);
				hphidiff_pip[p][t][s]->GetXaxis()->SetTitle("#phi (#pi +)");
				hphidiff_pip[p][t][s]->GetYaxis()->SetTitle(Form("sector_%i pt-slice_%i_%i ",s+1,p,t)); 
				tdata->Draw(Form("pipphidiff>>hphidiff_pip_p%i_t%i_s%i",p,t,s),pip_ptcut[p][t]&&pip_seccut[s]);
				hphidiff_pip[p][t][s]->Write();
			}
		}
	}
	///////////////////////////////////////////////// end pip calculation ////////////////////////////////////////////////////	
	
	
	
	
	
	
	
	
	
	
	
	///////////////////////////////////////////////// begin pim calculation ////////////////////////////////////////////////////	
	//get bin centers for momentum	
	//TCanvas *cpcenter_pim = new TCanvas("cpcenter_pim","cpcenter_pim",1000,800);
	//cpcenter_pim->Divide(Np,Nt);
	int cancount = 1;	
	TH1F *hpcenter_pim[Np][Nt];
	Double_t pcenter_pim[Np][Nt] = {0};
	Double_t prms_pim[Np][Nt] = {0};
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{ 
		//	cpcenter_pim->cd(cancount);
			hpcenter_pim[p][t] = new TH1F(Form("hpcenter_pim_p%i_t%i",p,t),"",200,0,4);
			tdata->Draw(Form("ppim>>hpcenter_pim_p%i_t%i",p,t),pim_ptcut[p][t]);
			hpcenter_pim[p][t]->GetXaxis()->SetTitle("pim momentum (GeV)");
			hpcenter_pim[p][t]->Write();
			cancount += 1;
		}
	}
	
	
	//get bin centers for theta	
	//TCanvas *ctcenter_pim = new TCanvas("ctcenter_pim","ctcenter_pim",1000,800);
	//ctcenter_pim->Divide(Np,Nt);
	int cancount = 1;	
	TH1F *htcenter_pim[Np][Nt];
	Double_t tcenter_pim[Np][Nt] = {0};
	Double_t trms_pim[Np][Nt] = {0};
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{ 
		//	ctcenter_pim->cd(cancount);
			htcenter_pim[p][t] = new TH1F(Form("htcenter_pim_p%i_t%i",p,t),"",200,0,180);
			tdata->Draw(Form("pimlabtheta>>htcenter_pim_p%i_t%i",p,t),pim_ptcut[p][t]);
			htcenter_pim[p][t]->GetXaxis()->SetTitle("pim #theta (deg)");
			htcenter_pim[p][t]->Write();
			cancount += 1;
			
			tcenter_pim[p][t] =  htcenter_pim[p][t]->GetMean();
			cout << "tcenter pim = " << htcenter_pim[p][t]->GetMean() <<endl;
		}
	}
	cout << "tcenters pim = " <<tcenter_pim[0][0] << ",  " <<tcenter_pim[0][1] <<",  " << tcenter_pim[0][2] <<endl;
	

	
	
	//TCanvas *cphi_pim[Np][Nt];
	TH1F *hphidiff_pim[Np][Nt][Ns];
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
			//cphi_pim[p][t] = new TCanvas(Form("cphi_pim_p%i_t%i",p,t),Form("cphi_pim_p%i_t%i",p,t),1000,800);
			//cphi_pim[p][t]->Divide(2,3);
			for (int s=0; s<Ns; s++)
			{
			//	cphi_pim[p][t]->cd(s+1);
				hphidiff_pim[p][t][s] = new TH1F(Form("hphidiff_pim_p%i_t%i_s%i",p,t,s),"",100,-30,30);
				hphidiff_pim[p][t][s]->GetXaxis()->SetTitle("#phi (#pi -)");
				hphidiff_pim[p][t][s]->GetYaxis()->SetTitle(Form("sector_%i pt-slice_%i_%i ",s+1,p,t)); 
				tdata->Draw(Form("pimphidiff>>hphidiff_pim_p%i_t%i_s%i",p,t,s),pim_ptcut[p][t]&&pim_seccut[s]);
				hphidiff_pim[p][t][s]->Write();
			}
		}
	}
	///////////////////////////////////////////////// end pim calculation ////////////////////////////////////////////////////	
	
	
	
	
	
	



	



}

////////////////////////////////////////////////////////////////////////


StyleUp()
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