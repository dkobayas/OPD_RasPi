int makePlotADC(TString datatag = "sample") {
  TFile *fin = new TFile("../Data/root/"+datatag+".root", "read");
  TTree *tin = (TTree*)fin->Get("raw");
  
  int nev = tin->GetEntries(); 
  float time, ADC0, ADC1;
  tin->SetBranchAddress("Time", &time);
  tin->SetBranchAddress("ADC0", &ADC0);
  tin->SetBranchAddress("ADC1", &ADC1);
 
  TH1F* h_adc0 = new TH1F("h_adc0", "h_adc0;ADC;n entries", 1024, 0, 1.65);
  TH1F* h_adc1 = new TH1F("h_adc1", "h_adc1;ADC;n entries", 1024, 0, 1.65);
  for(int iev=0; iev<nev; iev++) {
    tin->GetEntry(iev);
    h_adc0->Fill(ADC0);
    h_adc1->Fill(ADC1);
  }
  h_adc0->Draw();
  h_adc1->Draw("same");
  return 0;

}
