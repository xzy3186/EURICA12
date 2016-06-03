//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov  8 23:28:07 2012 by ROOT version 5.32/00
// from TTree tree/tree
// found on file: WASABI_EURICA1002.root
//////////////////////////////////////////////////////////

#ifndef gamma_gamma_h
#define gamma_gamma_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class gamma_gamma {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Long64_t        ts;
   Int_t           numdssd;
   Int_t           numadc;
   Int_t           numtdc;
   Int_t           IF_BETA;
   Int_t           IF_ION;
   Int_t           scal[32];
   Int_t           ADC[24][32];   //[numadc]
   Int_t           TDC[7][128][10];   //[numtdc]
   Int_t           dssd_E_X[8][60];   //[numdssd]
   Int_t           dssd_ch_X[8][60];   //[numdssd]
   Int_t           dssd_id_X[8][60];   //[numdssd]
   Int_t           dssd_E_Y[8][40];   //[numdssd]
   Int_t           dssd_ch_Y[8][40];   //[numdssd]
   Int_t           dssd_id_Y[8][40];   //[numdssd]
   Int_t           dssd_T_X[8][60][10];   //[numdssd]
   Int_t           dssd_T_Y[8][40][10];   //[numdssd]
   Int_t           dssd_X[8];   //[numdssd]
   Int_t           dssd_Y[8];   //[numdssd]
   Int_t           dssd_Z;
   Int_t           dssd8_fastout[32][10];
   Int_t           dssd8_timediff[32];
   Int_t           bigrips_F3PPAC1X1;
   Int_t           bigrips_F3PPAC1X2;
   Int_t           bigrips_F3PPAC2X1;
   Int_t           bigrips_F3PPAC2X2;
   Int_t           bigrips_F5PPAC1X1;
   Int_t           bigrips_F5PPAC1X2;
   Int_t           bigrips_F5PPAC2X1;
   Int_t           bigrips_F5PPAC2X2;
   Int_t           bigrips_F3L;
   Int_t           bigrips_F3R;
   Int_t           bigrips_F7L;
   Int_t           bigrips_F7R;
   Int_t           bigrips_F11L;
   Int_t           bigrips_F11R;
   Int_t           bigrips_IC1e;
   Int_t           bigrips_IC2e;
   Int_t           bigrips_IC3e;
   Int_t           bigrips_IC4e;
   Int_t           bigrips_IC5e;
   Int_t           bigrips_IC6e;
   Int_t           Qbeta1_E;
   Int_t           Qbeta2_E;
   Int_t           Qbeta_T;
   Int_t           Qveto_E;
   Int_t           NaI1_E;
   Int_t           NaI2_E;
   Int_t           NaI3_E;
   Int_t           NaI1_T;
   Int_t           NaI2_T;
   Int_t           NaI3_T;
   Double_t        pid_Delta_F3F5;
   Double_t        pid_TOF_F3F7;
   Double_t        pid_Beta_F3F5;
   Double_t        pid_Beta_F5F7;
   Double_t        pid_AoQ_F3F5;
   Double_t        pid_Zet_F11;
   Int_t           gc_hit;
   Int_t           gc_ch[84];   //[gc_hit]
   Int_t           gc_DGFe[84];   //[gc_hit]
   Int_t           gc_DGFt[84];   //[gc_hit]
   Int_t           gc_TDCs[84];   //[gc_hit]
   Int_t           gc_TDCl[84];   //[gc_hit]
   Double_t        gc_E[84];   //[gc_hit]
   Double_t        gc_T[84];   //[gc_hit]
   Int_t           ab_hit;
   Int_t           ab_ch[84];   //[ab_hit]
   Int_t           ab_DGFe[84];   //[ab_hit]
   Int_t           ab_DGFt[84];   //[ab_hit]
   Int_t           ab_TDCs[84];   //[ab_hit]
   Int_t           ab_TDCl[84];   //[ab_hit]
   Double_t        ab_E[84];   //[ab_hit]
   Double_t        ab_T[84];   //[ab_hit]

   // List of branches
   TBranch        *b_ts;   //!
   TBranch        *b_numdssd;   //!
   TBranch        *b_numadc;   //!
   TBranch        *b_numtdc;   //!
   TBranch        *b_IF_BETA;   //!
   TBranch        *b_IF_ION;   //!
   TBranch        *b_scal;   //!
   TBranch        *b_ADC;   //!
   TBranch        *b_TDC;   //!
   TBranch        *b_dssd_E_X;   //!
   TBranch        *b_dssd_ch_X;   //!
   TBranch        *b_dssd_id_X;   //!
   TBranch        *b_dssd_E_Y;   //!
   TBranch        *b_dssd_ch_Y;   //!
   TBranch        *b_dssd_id_Y;   //!
   TBranch        *b_dssd_T_X;   //!
   TBranch        *b_dssd_T_Y;   //!
   TBranch        *b_dssd_X;   //!
   TBranch        *b_dssd_Y;   //!
   TBranch        *b_dssd_Z;   //!
   TBranch        *b_dssd8_fastout;   //!
   TBranch        *b_dssd8_timediff;   //!
   TBranch        *b_bigrips_F3PPAC1X1;   //!
   TBranch        *b_bigrips_F3PPAC1X2;   //!
   TBranch        *b_bigrips_F3PPAC2X1;   //!
   TBranch        *b_bigrips_F3PPAC2X2;   //!
   TBranch        *b_bigrips_F5PPAC1X1;   //!
   TBranch        *b_bigrips_F5PPAC1X2;   //!
   TBranch        *b_bigrips_F5PPAC2X1;   //!
   TBranch        *b_bigrips_F5PPAC2X2;   //!
   TBranch        *b_bigrips_F3L;   //!
   TBranch        *b_bigrips_F3R;   //!
   TBranch        *b_bigrips_F7L;   //!
   TBranch        *b_bigrips_F7R;   //!
   TBranch        *b_bigrips_F11L;   //!
   TBranch        *b_bigrips_F11R;   //!
   TBranch        *b_bigrips_IC1e;   //!
   TBranch        *b_bigrips_IC2e;   //!
   TBranch        *b_bigrips_IC3e;   //!
   TBranch        *b_bigrips_IC4e;   //!
   TBranch        *b_bigrips_IC5e;   //!
   TBranch        *b_bigrips_IC6e;   //!
   TBranch        *b_Qbeta1_E;   //!
   TBranch        *b_Qbeta2_E;   //!
   TBranch        *b_Qbeta_T;   //!
   TBranch        *b_Qveto_E;   //!
   TBranch        *b_NaI1_E;   //!
   TBranch        *b_NaI2_E;   //!
   TBranch        *b_NaI3_E;   //!
   TBranch        *b_NaI1_T;   //!
   TBranch        *b_NaI2_T;   //!
   TBranch        *b_NaI3_T;   //!
   TBranch        *b_pid_Delta_F3F5;   //!
   TBranch        *b_pid_TOF_F3F7;   //!
   TBranch        *b_pid_Beta_F3F5;   //!
   TBranch        *b_pid_Beta_F5F7;   //!
   TBranch        *b_pid_AoQ_F3F5;   //!
   TBranch        *b_pid_Zet_F11;   //!
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

   gamma_gamma(char *filename, TTree *tree=0);
   virtual ~gamma_gamma();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

gamma_gamma::gamma_gamma(char *filename, TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
      if (!f || !f->IsOpen()) {
         f = new TFile(filename);
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

gamma_gamma::~gamma_gamma()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t gamma_gamma::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t gamma_gamma::LoadTree(Long64_t entry)
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

void gamma_gamma::Init(TTree *tree)
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
   fChain->SetBranchAddress("numdssd", &numdssd, &b_numdssd);
   fChain->SetBranchAddress("numadc", &numadc, &b_numadc);
   fChain->SetBranchAddress("numtdc", &numtdc, &b_numtdc);
   fChain->SetBranchAddress("IF_BETA", &IF_BETA, &b_IF_BETA);
   fChain->SetBranchAddress("IF_ION", &IF_ION, &b_IF_ION);
   fChain->SetBranchAddress("scal", scal, &b_scal);
   fChain->SetBranchAddress("ADC", ADC, &b_ADC);
   fChain->SetBranchAddress("TDC", TDC, &b_TDC);
   fChain->SetBranchAddress("dssd_E_X", dssd_E_X, &b_dssd_E_X);
   fChain->SetBranchAddress("dssd_ch_X", dssd_ch_X, &b_dssd_ch_X);
   fChain->SetBranchAddress("dssd_id_X", dssd_id_X, &b_dssd_id_X);
   fChain->SetBranchAddress("dssd_E_Y", dssd_E_Y, &b_dssd_E_Y);
   fChain->SetBranchAddress("dssd_ch_Y", dssd_ch_Y, &b_dssd_ch_Y);
   fChain->SetBranchAddress("dssd_id_Y", dssd_id_Y, &b_dssd_id_Y);
   fChain->SetBranchAddress("dssd_T_X", dssd_T_X, &b_dssd_T_X);
   fChain->SetBranchAddress("dssd_T_Y", dssd_T_Y, &b_dssd_T_Y);
   fChain->SetBranchAddress("dssd_X", dssd_X, &b_dssd_X);
   fChain->SetBranchAddress("dssd_Y", dssd_Y, &b_dssd_Y);
   fChain->SetBranchAddress("dssd_Z", &dssd_Z, &b_dssd_Z);
   fChain->SetBranchAddress("dssd8_fastout", dssd8_fastout, &b_dssd8_fastout);
   fChain->SetBranchAddress("dssd8_timediff", dssd8_timediff, &b_dssd8_timediff);
   fChain->SetBranchAddress("bigrips_F3PPAC1X1", &bigrips_F3PPAC1X1, &b_bigrips_F3PPAC1X1);
   fChain->SetBranchAddress("bigrips_F3PPAC1X2", &bigrips_F3PPAC1X2, &b_bigrips_F3PPAC1X2);
   fChain->SetBranchAddress("bigrips_F3PPAC2X1", &bigrips_F3PPAC2X1, &b_bigrips_F3PPAC2X1);
   fChain->SetBranchAddress("bigrips_F3PPAC2X2", &bigrips_F3PPAC2X2, &b_bigrips_F3PPAC2X2);
   fChain->SetBranchAddress("bigrips_F5PPAC1X1", &bigrips_F5PPAC1X1, &b_bigrips_F5PPAC1X1);
   fChain->SetBranchAddress("bigrips_F5PPAC1X2", &bigrips_F5PPAC1X2, &b_bigrips_F5PPAC1X2);
   fChain->SetBranchAddress("bigrips_F5PPAC2X1", &bigrips_F5PPAC2X1, &b_bigrips_F5PPAC2X1);
   fChain->SetBranchAddress("bigrips_F5PPAC2X2", &bigrips_F5PPAC2X2, &b_bigrips_F5PPAC2X2);
   fChain->SetBranchAddress("bigrips_F3L", &bigrips_F3L, &b_bigrips_F3L);
   fChain->SetBranchAddress("bigrips_F3R", &bigrips_F3R, &b_bigrips_F3R);
   fChain->SetBranchAddress("bigrips_F7L", &bigrips_F7L, &b_bigrips_F7L);
   fChain->SetBranchAddress("bigrips_F7R", &bigrips_F7R, &b_bigrips_F7R);
   fChain->SetBranchAddress("bigrips_F11L", &bigrips_F11L, &b_bigrips_F11L);
   fChain->SetBranchAddress("bigrips_F11R", &bigrips_F11R, &b_bigrips_F11R);
   fChain->SetBranchAddress("bigrips_IC1e", &bigrips_IC1e, &b_bigrips_IC1e);
   fChain->SetBranchAddress("bigrips_IC2e", &bigrips_IC2e, &b_bigrips_IC2e);
   fChain->SetBranchAddress("bigrips_IC3e", &bigrips_IC3e, &b_bigrips_IC3e);
   fChain->SetBranchAddress("bigrips_IC4e", &bigrips_IC4e, &b_bigrips_IC4e);
   fChain->SetBranchAddress("bigrips_IC5e", &bigrips_IC5e, &b_bigrips_IC5e);
   fChain->SetBranchAddress("bigrips_IC6e", &bigrips_IC6e, &b_bigrips_IC6e);
   fChain->SetBranchAddress("Qbeta1_E", &Qbeta1_E, &b_Qbeta1_E);
   fChain->SetBranchAddress("Qbeta2_E", &Qbeta2_E, &b_Qbeta2_E);
   fChain->SetBranchAddress("Qbeta_T", &Qbeta_T, &b_Qbeta_T);
   fChain->SetBranchAddress("Qveto_E", &Qveto_E, &b_Qveto_E);
   fChain->SetBranchAddress("NaI1_E", &NaI1_E, &b_NaI1_E);
   fChain->SetBranchAddress("NaI2_E", &NaI2_E, &b_NaI2_E);
   fChain->SetBranchAddress("NaI3_E", &NaI3_E, &b_NaI3_E);
   fChain->SetBranchAddress("NaI1_T", &NaI1_T, &b_NaI1_T);
   fChain->SetBranchAddress("NaI2_T", &NaI2_T, &b_NaI2_T);
   fChain->SetBranchAddress("NaI3_T", &NaI3_T, &b_NaI3_T);
   fChain->SetBranchAddress("pid_Delta_F3F5", &pid_Delta_F3F5, &b_pid_Delta_F3F5);
   fChain->SetBranchAddress("pid_TOF_F3F7", &pid_TOF_F3F7, &b_pid_TOF_F3F7);
   fChain->SetBranchAddress("pid_Beta_F3F5", &pid_Beta_F3F5, &b_pid_Beta_F3F5);
   fChain->SetBranchAddress("pid_Beta_F5F7", &pid_Beta_F5F7, &b_pid_Beta_F5F7);
   fChain->SetBranchAddress("pid_AoQ_F3F5", &pid_AoQ_F3F5, &b_pid_AoQ_F3F5);
   fChain->SetBranchAddress("pid_Zet_F11", &pid_Zet_F11, &b_pid_Zet_F11);
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

Bool_t gamma_gamma::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void gamma_gamma::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t gamma_gamma::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef gamma_gamma_cxx
