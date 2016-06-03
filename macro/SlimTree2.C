void SlimTree(TTree* tree, char * outputfile, char * gate=""){
  TFile *fout = new TFile(outputfile,"recreate");
  TString sgate(gate);
  tree->CopyTree(sgate);
  fout->Write();
  fout->Close();

}
