void SlimTree(char * inputfile, char * outputfile, char * gate=""){

  //  gROOT->ProcessLine(".x /home/ur12/analysis/users/sumikama/GateForPid.C");
  TFile *infile  = new TFile(inputfile,"READ");
  TFile *fout = new TFile(outputfile,"recreate");
  TString sgate(gate);
  ((TTree*)infile->Get("tree"))->CopyTree(sgate);
  fout->Write();
  fout->Close();

}
