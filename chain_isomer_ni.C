{
   TChain *tree = new TChain ("tree");
   tree->Add("root/sistopper/ni78test/EURICA_GGMatrix1*.root");
   tree->Add("root/sistopper/cu81test/EURICA_GGMatrix5*.root");
   //ion->Add("root/sistopper/cu81test/beta_ion*.root");
   //tree->Add("root/sistopper/eurica_ggmatrix_old/EURICA_GGMatrix5*.root");
}
