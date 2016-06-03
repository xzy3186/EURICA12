{
   TChain *decay = new TChain ("decay");
   decay->Add("root/final/ni78test/decay_new1*.root");
   decay->Add("root/final/cu81test/decay_new5*.root");
}
