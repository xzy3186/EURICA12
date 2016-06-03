//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun 27 12:09:50 2012 by ROOT version 5.30/01
// from TTree beta/beta
// found on file: root_dir/beta_ion_gamma_2043.root
//////////////////////////////////////////////////////////

#ifndef beta_h
#define beta_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "eurica_wasabi.h"

class beta {
   public :
      TTree          *fChain;   //!pointer to the analyzed TTree or TChain
      Int_t           fCurrent; //!current Tree number in a TChain

      // Declaration of leaf types
      Long64_t        ts;
      Int_t           z;
      Float_t         x;
      Float_t         y;
      Int_t           x1;
      Int_t           y1;
      Int_t           x2;
      Int_t           y2;
      Int_t           ex;
      Int_t           ey;
      Int_t           tx;
      Int_t           ty;
      Int_t           numdssd;
      Int_t           dstrx;
      Int_t           dstry;
      Int_t           dssd_mulhit;
      Int_t           dssd_fire[NumDSSD];
      Int_t           dssd_ex[NumDSSD];
      Int_t           dssd_ey[NumDSSD];
      Int_t           dssd_zmult[NumDSSD];
      Float_t         dssd_x[NumDSSD][5];
      Float_t         dssd_y[NumDSSD][5];
      Int_t           dssd_E;
      Int_t           dssd_E_X[NumDSSD][60];
      Int_t           dssd_ch_X[NumDSSD][60];
      Int_t           dssd_id_X[NumDSSD][60];
      Int_t           dssd_T_X[NumDSSD][60][3];
      Int_t           dssd_E_Y[NumDSSD][40];
      Int_t           dssd_ch_Y[NumDSSD][40];
      Int_t           dssd_id_Y[NumDSSD][40];
      Int_t           dssd_T_Y[NumDSSD][40][3];
      Int_t           dssd_fastout[64][3];

      Int_t           Qbeta_E;
      Int_t           Qveto_E;
      Int_t           Qveto_T;
      Int_t           Qbeta_T;

      Int_t           NaI_E[3];
      Int_t           NaI_T[3];

      Int_t           gc_hit;
      Int_t           gc_ch[84];   //[gc_hit]
      Int_t           gc_DGFe[84];   //[gc_hit]
      Int_t           gc_DGFt[84];   //[gc_hit]
      Int_t           gc_TDCs[84];   //[gc_hit]
      Int_t           gc_TDCl[84];   //[gc_hit]
      Double_t        gc_E[84];   //[gc_hit]
      Double_t        gc_T[84];   //[gc_hit]

      Int_t           ab_hit;
      Int_t           ab_ch[84];   //[gc_hit]
      Int_t           ab_DGFe[84];   //[gc_hit]
      Int_t           ab_DGFt[84];   //[gc_hit]
      Int_t           ab_TDCs[84];   //[gc_hit]
      Int_t           ab_TDCl[84];   //[gc_hit]
      Double_t        ab_E[84];   //[gc_hit]
      Double_t        ab_T[84];   //[gc_hit]

      // List of branches
      TBranch        *b_ts;   //!
      TBranch        *b_z;   //!
      TBranch        *b_x;   //!
      TBranch        *b_y;   //!
      TBranch        *b_x1;   //!
      TBranch        *b_y1;   //!
      TBranch        *b_x2;   //!
      TBranch        *b_y2;   //!
      TBranch        *b_ex;   //!
      TBranch        *b_ey;   //!
      TBranch        *b_tx;   //!
      TBranch        *b_ty;   //!
      TBranch        *b_numdssd;   //!
      TBranch        *b_dstrx;   //!
      TBranch        *b_dstry;   //!
      TBranch        *b_dssd_mulhit;
      TBranch        *b_dssd_fire;
      TBranch        *b_dssd_ex;
      TBranch        *b_dssd_ey;
      TBranch        *b_dssd_zmult;
      TBranch        *b_dssd_x;
      TBranch        *b_dssd_y;
      TBranch        *b_dssd_E;
      TBranch        *b_dssd_E_X;
      TBranch        *b_dssd_ch_X;
      TBranch        *b_dssd_id_X;
      TBranch        *b_dssd_E_Y;
      TBranch        *b_dssd_ch_Y;
      TBranch        *b_dssd_id_Y;
      TBranch        *b_dssd_T_X;
      TBranch        *b_dssd_T_Y;
      TBranch        *b_dssd_fastout;

      TBranch        *b_NaI_E;
      TBranch        *b_NaI_T;

      TBranch        *b_Qbeta_E;
      TBranch        *b_Qbeta_T;
      TBranch        *b_Qveto_E;
      TBranch        *b_Qveto_T;

      TBranch        *b_gc_hit;   //!
      TBranch        *b_gc_ch;   //!
      TBranch        *b_gc_DGFe;   //!
      TBranch        *b_gc_DGFt;   //!
      TBranch        *b_gc_TDCs;   //!
      TBranch        *b_gc_TDCl;   //!
      TBranch        *b_gc_E;   //!
      TBranch        *b_gc_T;   //!

      TBranch        *b_ab_hit;   //!
      TBranch        *b_ab_ch;   //!
      TBranch        *b_ab_DGFe;   //!
      TBranch        *b_ab_DGFt;   //!
      TBranch        *b_ab_TDCs;   //!
      TBranch        *b_ab_TDCl;   //!
      TBranch        *b_ab_E;   //!
      TBranch        *b_ab_T;   //!

      beta();
      virtual void     GetTree(char *filename, TTree *tree=0);
      virtual Int_t    Cut(Long64_t entry);
      virtual Int_t    GetEntry(Long64_t entry);
      virtual Long64_t LoadTree(Long64_t entry);
      virtual void     Init(TTree *tree);
      virtual void     BranchStatus();
      virtual Bool_t   Notify();
      virtual void     Show(Long64_t entry = -1);
      virtual void     GetTsEntry(multimap <Long64_t, pair<pair<Long64_t, Int_t>, pair<pair<Int_t, Int_t>, pair<Int_t, Int_t> > > > &mts);
      virtual void     TreeBranch(TTree *tree);
      virtual void     SyncSi(eurica_wasabi &DSSD);
      virtual void     SyncTS(eurica_wasabi &DSSD);
      virtual void     SyncQbeta(eurica_wasabi &DSSD);
      virtual void     SyncNaI(eurica_wasabi &DSSD);
      virtual void     SyncGamma(eurica_wasabi &gamma);
      virtual void     ResetGe();
};

beta::beta(){
}

void beta::GetTree(char *filename, TTree *tree)
{
   // if parameter tree is not specified (or zero), connect the file
   // used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
      if (!f || !f->IsOpen()) {
         f = new TFile(filename);
      }
      f->GetObject("beta",tree);

   }
   Init(tree);
}

Int_t beta::GetEntry(Long64_t entry)
{
   // Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t beta::LoadTree(Long64_t entry)
{
   // Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void beta::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("ts", &ts, &b_ts);
   fChain->SetBranchAddress("z", &z, &b_z);
   fChain->SetBranchAddress("x", &x, &b_x);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("x1", &x1, &b_x1);
   fChain->SetBranchAddress("y1", &y1, &b_y1);
   fChain->SetBranchAddress("x2", &x2, &b_x2);
   fChain->SetBranchAddress("y2", &y2, &b_y2);
   fChain->SetBranchAddress("ex", &ex, &b_ex);
   fChain->SetBranchAddress("ey", &ey, &b_ey);
   fChain->SetBranchAddress("tx", &tx, &b_tx);
   fChain->SetBranchAddress("ty", &ty, &b_ty);
   fChain->SetBranchAddress("numdssd", &numdssd, &b_numdssd);
   fChain->SetBranchAddress("dstrx", &dstrx, &b_dstrx);
   fChain->SetBranchAddress("dstry", &dstry, &b_dstry);
   fChain->SetBranchAddress("dssd_mulhit", &dssd_mulhit, &b_dssd_mulhit);
   fChain->SetBranchAddress("dssd_fire", dssd_fire, &b_dssd_fire);
   fChain->SetBranchAddress("dssd_ex", dssd_ex, &b_dssd_ex);
   fChain->SetBranchAddress("dssd_ey", dssd_ey, &b_dssd_ey);
   fChain->SetBranchAddress("dssd_zmult", dssd_zmult, &b_dssd_zmult);
   fChain->SetBranchAddress("dssd_x", dssd_x, &b_dssd_x);
   fChain->SetBranchAddress("dssd_y", dssd_y, &b_dssd_y);
   fChain->SetBranchAddress("dssd_E", &dssd_E, &b_dssd_E);
   //fChain->SetBranchAddress("dssd_E_X", dssd_E_X, &b_dssd_E_X);
   //fChain->SetBranchAddress("dssd_ch_X", dssd_ch_X, &b_dssd_ch_X);
   //fChain->SetBranchAddress("dssd_id_X", dssd_id_X, &b_dssd_id_X);
   //fChain->SetBranchAddress("dssd_E_Y", dssd_E_Y, &b_dssd_E_Y);
   //fChain->SetBranchAddress("dssd_ch_Y", dssd_ch_Y, &b_dssd_ch_Y);
   //fChain->SetBranchAddress("dssd_id_Y", dssd_id_Y, &b_dssd_id_Y);
   //fChain->SetBranchAddress("dssd_T_X", dssd_T_X, &b_dssd_T_X);
   //fChain->SetBranchAddress("dssd_T_Y", dssd_T_Y, &b_dssd_T_Y);
   //fChain->SetBranchAddress("dssd_fastout", dssd_fastout, &b_dssd_fastout);

   fChain->SetBranchAddress("Qbeta_E", &Qbeta_E, &b_Qbeta_E);
   fChain->SetBranchAddress("Qbeta_T", &Qbeta_T, &b_Qbeta_T);
   fChain->SetBranchAddress("Qveto_E", &Qveto_E, &b_Qveto_E);
   fChain->SetBranchAddress("Qveto_T", &Qveto_T, &b_Qveto_T);

   fChain->SetBranchAddress("NaI_E", NaI_E, &b_NaI_E);
   fChain->SetBranchAddress("NaI_T", NaI_T, &b_NaI_T);

   fChain->SetBranchAddress("gc_hit", &gc_hit, &b_gc_hit);
   fChain->SetBranchAddress("gc_ch", gc_ch, &b_gc_ch);
   fChain->SetBranchAddress("gc_DGFe", gc_DGFe, &b_gc_DGFe);
   fChain->SetBranchAddress("gc_DGFt", gc_DGFt, &b_gc_DGFt);
   fChain->SetBranchAddress("gc_TDCs", gc_TDCs, &b_gc_TDCs);
   fChain->SetBranchAddress("gc_TDCl", gc_TDCl, &b_gc_TDCl);
   fChain->SetBranchAddress("gc_E", gc_E, &b_gc_E);
   fChain->SetBranchAddress("gc_T", gc_T, &b_gc_T);
   fChain->SetBranchAddress("ab_hit", &ab_hit, &b_ab_hit);
   fChain->SetBranchAddress("ab_ch", ab_ch, &b_ab_ch);
   fChain->SetBranchAddress("ab_DGFe", ab_DGFe, &b_ab_DGFe);
   fChain->SetBranchAddress("ab_DGFt", ab_DGFt, &b_ab_DGFt);
   fChain->SetBranchAddress("ab_TDCs", ab_TDCs, &b_ab_TDCs);
   fChain->SetBranchAddress("ab_TDCl", ab_TDCl, &b_ab_TDCl);
   fChain->SetBranchAddress("ab_E", ab_E, &b_ab_E);
   fChain->SetBranchAddress("ab_T", ab_T, &b_ab_T);
   Notify();
}

void beta::BranchStatus()
{
   fChain->SetBranchStatus("*",0);
   fChain->SetBranchStatus("ts");
   fChain->SetBranchStatus("z");
   fChain->SetBranchStatus("x");
   fChain->SetBranchStatus("y");
   fChain->SetBranchStatus("x1");
   fChain->SetBranchStatus("y1");
   fChain->SetBranchStatus("x2");
   fChain->SetBranchStatus("y2");
   fChain->SetBranchStatus("ex");
   fChain->SetBranchStatus("ey");
   fChain->SetBranchStatus("tx");
   fChain->SetBranchStatus("ty");
   fChain->SetBranchStatus("numdssd");
   fChain->SetBranchStatus("dssd_mulhit");
   fChain->SetBranchStatus("dssd_fire");
   fChain->SetBranchStatus("dssd_ex");
   fChain->SetBranchStatus("dssd_ey");
   fChain->SetBranchStatus("dssd_zmult");
   fChain->SetBranchStatus("dssd_x");
   fChain->SetBranchStatus("dssd_y");
   fChain->SetBranchStatus("dssd_E");
   fChain->SetBranchStatus("Qbeta_E");
   fChain->SetBranchStatus("Qbeta_T");
   fChain->SetBranchStatus("Qveto_E");
   fChain->SetBranchStatus("Qveto_T");
   fChain->SetBranchStatus("gc_hit");
   fChain->SetBranchStatus("gc_ch");
   fChain->SetBranchStatus("gc_TDCs");
   fChain->SetBranchStatus("gc_TDCl");
   fChain->SetBranchStatus("gc_E");
   fChain->SetBranchStatus("gc_T");
   fChain->SetBranchStatus("ab_hit");
   fChain->SetBranchStatus("ab_ch");
   fChain->SetBranchStatus("ab_TDCs");
   fChain->SetBranchStatus("ab_TDCl");
   fChain->SetBranchStatus("ab_E");
   fChain->SetBranchStatus("ab_T");
}

Bool_t beta::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void beta::Show(Long64_t entry)
{
   // Print contents of entry.
   // If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t beta::Cut(Long64_t entry)
{
   // This function may be called from Loop.
   // returns  1 if entry is accepted.
   // returns -1 otherwise.
   return 1;
}

void beta::GetTsEntry(multimap <Long64_t, pair<pair<Long64_t, Int_t>, pair<pair<Int_t, Int_t>, pair<Int_t, Int_t> > > > &mts){
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   for(Long64_t jentries=0; jentries<nentries; jentries++){
      Long64_t ientry = LoadTree(jentries);
      if(ientry<0){
         break;
      }
      nb = fChain->GetEntry(jentries);
      nbytes+=nb;
      mts.insert(make_pair(ts, make_pair(make_pair(jentries,z), make_pair(make_pair(x1,x2),make_pair(y1,y2) ) ) ) );
   }
}

void beta::TreeBranch(TTree *tree){
   numdssd = NumDSSD;
   dstrx = NumDSSD*NumStrX;
   dstry = NumDSSD*NumStrY;
   tree->Branch("ts",&ts,"ts/L");
   tree->Branch("z",&z,"z/I");
   tree->Branch("x",&x,"x/F");
   tree->Branch("y",&y,"y/F");
   tree->Branch("x1",&x1,"x1/I");
   tree->Branch("y1",&y1,"y1/I");
   tree->Branch("x2",&x2,"x2/I");
   tree->Branch("y2",&y2,"y2/I");
   tree->Branch("ex",&ex,"ex/I");
   tree->Branch("ey",&ey,"ey/I");
   tree->Branch("tx",&tx,"tx/I");
   tree->Branch("ty",&ty,"ty/I");
   tree->Branch("numdssd",&numdssd,"numdssd/I");
   tree->Branch("dstrx",&dstrx,"dstrx/I");
   tree->Branch("dstry",&dstry,"dstry/I");
   tree->Branch("dssd_mulhit",&dssd_mulhit,"dssd_mult/I");
   tree->Branch("dssd_fire",dssd_fire,"dssd_fire[numdssd]/I");
   tree->Branch("dssd_ex",dssd_ex,"dssd_ex[numdssd]/I");
   tree->Branch("dssd_ey",dssd_ey,"dssd_ey[numdssd]/I");
   tree->Branch("dssd_zmult",dssd_zmult,"dssd_zmult[numdssd]/I");
   tree->Branch("dssd_x",dssd_x,"dssd_x[numdssd][5]/F");
   tree->Branch("dssd_y",dssd_y,"dssd_y[numdssd][5]/F");
   tree->Branch("dssd_E",&dssd_E,"dssd_E/I");
   tree->Branch("dssd_E_X",dssd_E_X,"dssd_E_X[numdssd][60]/I");
   tree->Branch("dssd_ch_X",dssd_ch_X,"dssd_ch_X[numdssd][60]/I");
   tree->Branch("dssd_id_X",dssd_id_X,"dssd_id_X[numdssd][60]/I");
   tree->Branch("dssd_E_Y",dssd_E_Y,"dssd_E_Y[numdssd][40]/I");
   tree->Branch("dssd_ch_Y",dssd_ch_Y,"dssd_ch_Y[numdssd][40]/I");
   tree->Branch("dssd_id_Y",dssd_id_Y,"dssd_id_Y[numdssd][40]/I");
   tree->Branch("dssd_T_X",dssd_T_X,"dssd_T_X[numdssd][60][3]/I");
   tree->Branch("dssd_T_Y",dssd_T_Y,"dssd_T_Y[numdssd][40][3]/I");
   tree->Branch("dssd_fastout",dssd_fastout,"dssd_fastout[64][3]/I");

   tree->Branch("Qbeta_E",&Qbeta_E,"Qbeta_E/I");
   tree->Branch("Qbeta_T",&Qbeta_T,"Qbeta_T/I");
   tree->Branch("Qveto_E",&Qveto_E,"Qveto_E/I");
   tree->Branch("Qveto_T",&Qveto_T,"Qveto_T/I");

   tree->Branch("gc_hit",&gc_hit,"gc_hit/I");
   tree->Branch("gc_ch",gc_ch,"gc_ch[gc_hit]/I");
   tree->Branch("gc_DGFe",gc_DGFe,"gc_DGFe[gc_hit]/I");
   tree->Branch("gc_DGFt",gc_DGFt,"gc_DGFt[gc_hit]/I");
   tree->Branch("gc_TDCs",gc_TDCs,"gc_TDCs[gc_hit]/I");
   tree->Branch("gc_TDCl",gc_TDCl,"gc_TDCl[gc_hit]/I");
   tree->Branch("gc_E",gc_E,"gc_E[gc_hit]/D");
   tree->Branch("gc_T",gc_T,"gc_T[gc_hit]/D");

   tree->Branch("ab_hit",&ab_hit,"ab_hit/I");
   tree->Branch("ab_ch",ab_ch,"ab_ch[ab_hit]/I");
   tree->Branch("ab_DGFe",ab_DGFe,"ab_DGFe[ab_hit]/I");
   tree->Branch("ab_DGFt",ab_DGFt,"ab_DGFt[ab_hit]/I");
   tree->Branch("ab_TDCs",ab_TDCs,"ab_TDCs[ab_hit]/I");
   tree->Branch("ab_TDCl",ab_TDCl,"ab_TDCl[ab_hit]/I");
   tree->Branch("ab_E",ab_E,"ab_E[ab_hit]/D");
   tree->Branch("ab_T",ab_T,"ab_T[ab_hit]/D");

   tree->Branch("NaI_E",NaI_E,"NaI_E[3]/I");
   tree->Branch("NaI_T",NaI_T,"NaI_T[3]/I");
}

void beta::SyncSi(eurica_wasabi &DSSD){
   memcpy(dssd_E_X, DSSD.dssd_E_X, sizeof(DSSD.dssd_E_X));
   memcpy(dssd_ch_X, DSSD.dssd_ch_X, sizeof(DSSD.dssd_ch_X));
   memcpy(dssd_id_X, DSSD.dssd_id_X, sizeof(DSSD.dssd_id_X));
   memcpy(dssd_E_Y, DSSD.dssd_E_Y, sizeof(DSSD.dssd_E_Y));
   memcpy(dssd_ch_Y, DSSD.dssd_ch_Y, sizeof(DSSD.dssd_ch_Y));
   memcpy(dssd_id_Y, DSSD.dssd_id_Y, sizeof(DSSD.dssd_id_Y));
   memcpy(dssd_T_X, DSSD.dssd_T_X, sizeof(DSSD.dssd_T_X));
   memcpy(dssd_T_Y, DSSD.dssd_T_Y, sizeof(DSSD.dssd_T_Y));
}

void beta::SyncTS(eurica_wasabi &DSSD){
   ts = DSSD.ts;
}

void beta::SyncQbeta(eurica_wasabi &DSSD){
   Qbeta_E = DSSD.Qbeta_E;
   Qbeta_T = DSSD.Qbeta_T;
   Qveto_E = DSSD.Qveto_E;
   Qveto_T = DSSD.Qveto_T;
   memcpy(dssd_fastout, DSSD.dssd_fastout, sizeof(DSSD.dssd_fastout));
}

void beta::SyncGamma(eurica_wasabi &gamma){
   gc_hit=gamma.gc_hit;
   memcpy(gc_ch, gamma.gc_ch, sizeof(gamma.gc_ch));
   memcpy(gc_DGFe, gamma.gc_DGFe, sizeof(gamma.gc_DGFe));
   memcpy(gc_DGFt, gamma.gc_DGFt, sizeof(gamma.gc_DGFt));
   memcpy(gc_TDCs, gamma.gc_TDCs, sizeof(gamma.gc_TDCs));
   memcpy(gc_TDCl, gamma.gc_TDCl, sizeof(gamma.gc_TDCl));
   memcpy(gc_E, gamma.gc_E, sizeof(gamma.gc_E));
   memcpy(gc_T, gamma.gc_T, sizeof(gamma.gc_T));
   ab_hit=gamma.ab_hit;
   memcpy(ab_ch, gamma.ab_ch, sizeof(gamma.ab_ch));
   memcpy(ab_DGFe, gamma.ab_DGFe, sizeof(gamma.ab_DGFe));
   memcpy(ab_DGFt, gamma.ab_DGFt, sizeof(gamma.ab_DGFt));
   memcpy(ab_TDCs, gamma.ab_TDCs, sizeof(gamma.ab_TDCs));
   memcpy(ab_TDCl, gamma.ab_TDCl, sizeof(gamma.ab_TDCl));
   memcpy(ab_E, gamma.ab_E, sizeof(gamma.ab_E));
   memcpy(ab_T, gamma.ab_T, sizeof(gamma.ab_T));
}

void beta::ResetGe(){
   gc_hit=0;
   ab_hit=0;
}

void beta::SyncNaI(eurica_wasabi &DSSD){
   memcpy(NaI_E, DSSD.NaI_E, sizeof(DSSD.NaI_E));
   memcpy(NaI_T, DSSD.NaI_T, sizeof(DSSD.NaI_T));
}
#endif // #ifdef beta_cxx
