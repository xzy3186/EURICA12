{
   TChain *decay = new TChain ("decay");
   decay->Add("root/sistopper/ni78test/decay_old/DECAY_GGMatrix1*.root");
   decay->Add("root/sistopper/cu81test/decay_old/DECAY_GGMatrix5*.root");
}
