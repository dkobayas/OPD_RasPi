int makeTree( TString filename="sample"){
	// read input file
	TString infname = "../Data/dat/"+filename+".dat";
	ifstream ifs(infname);
	int line_num = 1;

	// output tree preparation
        float time = -1;	
	float adc0 = -1;
	float adc1 = -1;
	TTree *tree = new TTree("OPD_data", "OPD_data");
	tree->Branch("Time", &time, "Time");
	tree->Branch("ADC0", &adc0, "ADC0");
	tree->Branch("ADC1", &adc1, "ADC1");
	
	// event loop
	ifs>>time>>adc0>>adc1;
    	while(!ifs.eof()) {
		cout<<"Time " << time << "[sec]: ADC="<<adc0<<"[V],"<<adc1<<"[V]"<<endl;
		tree->Fill();
		ifs>>time>>adc0>>adc1;
  	}

	// Writing to output file
	TString ofn = "../Data/root/"+filename+".root";
    	TFile *fout = new TFile(ofn, "recreate");
    	tree->Write();  
    	fout->Close();

	return 0;
}
