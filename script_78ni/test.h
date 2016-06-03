//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug  9 13:25:53 2013 by ROOT version 5.34/03
// from TTree decay/decay
// found on file: ../root/final/ni78test/decay_new1032.root
//////////////////////////////////////////////////////////

#ifndef test_h
#define test_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TObject.h>
#include <TClonesArray.h>

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxbeta = 38;
const Int_t kMaxbg = 37;

class test {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //CImp            *imp;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           run;
   Long64_t        ts;
   Int_t           z;
   Int_t           x;
   Int_t           y;
   Int_t           tx;
   Int_t           ty;
   Int_t           IfInterest;
   Double_t        beta35;
   Double_t        beta57;
   Double_t        beta711;
   Double_t        aoq37;
   Double_t        zed;
   Int_t           Zed;
   Int_t           Mass;
   Int_t           flagall;
   Int_t           flagTSumX;
   Int_t           flagTOFt;
   Int_t           flagTOFq;
   Int_t           flagReaction;
   Int_t           flagdERelation;
   Int_t           flagAngle;
   Int_t           gc_hit;
   Int_t           gc_ch[84];
   Int_t           gc_DGFe[84];
   Int_t           gc_TDCs[84];
   Int_t           gc_DGFt[84];
   Int_t           gc_TDCl[84];
   Double_t        gc_E[84];
   Double_t        gc_T[84];
   Int_t           ab_hit;
   Int_t           ab_ch[84];
   Int_t           ab_DGFe[84];
   Int_t           ab_TDCs[84];
   Int_t           ab_DGFt[84];
   Int_t           ab_TDCl[84];
   Double_t        ab_E[84];
   Double_t        ab_T[84];
   Int_t           beta_;
   UInt_t          beta_fUniqueID[kMaxbeta];   //[beta_]
   UInt_t          beta_fBits[kMaxbeta];   //[beta_]
   Long64_t        beta_t[kMaxbeta];   //[beta_]
   Int_t           beta_z[kMaxbeta];   //[beta_]
   Float_t         beta_x[kMaxbeta];   //[beta_]
   Float_t         beta_y[kMaxbeta];   //[beta_]
   Int_t           beta_ex[kMaxbeta];   //[beta_]
   Int_t           beta_ey[kMaxbeta];   //[beta_]
   Int_t           beta_mulx[kMaxbeta];   //[beta_]
   Int_t           beta_muly[kMaxbeta];   //[beta_]
   Int_t           beta_deltaz[kMaxbeta];   //[beta_]
   Double_t        beta_deltaxy[kMaxbeta];   //[beta_]
   Int_t           beta_E[kMaxbeta];   //[beta_]
   Int_t           beta_dssd_fire[kMaxbeta][8];   //[beta_]
   Int_t           beta_flag_side[kMaxbeta];   //[beta_]
   Int_t           beta_dssd_ex[kMaxbeta][8];   //[beta_]
   Int_t           beta_dssd_ey[kMaxbeta][8];   //[beta_]
   Int_t           beta_dssd_zmult[kMaxbeta][8];   //[beta_]
   Float_t         beta_dssd_x[kMaxbeta][8][5];   //[beta_]
   Float_t         beta_dssd_y[kMaxbeta][8][5];   //[beta_]
   Int_t           beta_NaI_E[kMaxbeta][3];   //[beta_]
   Int_t           beta_NaI_T[kMaxbeta][3];   //[beta_]
   Int_t           beta_Qbeta_E[kMaxbeta];   //[beta_]
   Int_t           beta_Qbeta_T[kMaxbeta];   //[beta_]
   Int_t           beta_Qveto_E[kMaxbeta];   //[beta_]
   Int_t           beta_Qveto_T[kMaxbeta];   //[beta_]
   Int_t           beta_gc_hit[kMaxbeta];   //[beta_]
   Int_t           beta_gc_ch[kMaxbeta][84];   //[beta_]
   Int_t           beta_gc_DGFe[kMaxbeta][84];   //[beta_]
   Int_t           beta_gc_TDCs[kMaxbeta][84];   //[beta_]
   Int_t           beta_gc_DGFt[kMaxbeta][84];   //[beta_]
   Int_t           beta_gc_TDCl[kMaxbeta][84];   //[beta_]
   Double_t        beta_gc_E[kMaxbeta][84];   //[beta_]
   Double_t        beta_gc_T[kMaxbeta][84];   //[beta_]
   Int_t           beta_ab_hit[kMaxbeta];   //[beta_]
   Int_t           beta_ab_ch[kMaxbeta][84];   //[beta_]
   Int_t           beta_ab_DGFe[kMaxbeta][84];   //[beta_]
   Int_t           beta_ab_TDCs[kMaxbeta][84];   //[beta_]
   Int_t           beta_ab_DGFt[kMaxbeta][84];   //[beta_]
   Int_t           beta_ab_TDCl[kMaxbeta][84];   //[beta_]
   Double_t        beta_ab_E[kMaxbeta][84];   //[beta_]
   Double_t        beta_ab_T[kMaxbeta][84];   //[beta_]
   Int_t           bg_;
   UInt_t          bg_fUniqueID[kMaxbg];   //[bg_]
   UInt_t          bg_fBits[kMaxbg];   //[bg_]
   Long64_t        bg_t[kMaxbg];   //[bg_]
   Int_t           bg_z[kMaxbg];   //[bg_]
   Float_t         bg_x[kMaxbg];   //[bg_]
   Float_t         bg_y[kMaxbg];   //[bg_]
   Int_t           bg_ex[kMaxbg];   //[bg_]
   Int_t           bg_ey[kMaxbg];   //[bg_]
   Int_t           bg_mulx[kMaxbg];   //[bg_]
   Int_t           bg_muly[kMaxbg];   //[bg_]
   Int_t           bg_deltaz[kMaxbg];   //[bg_]
   Double_t        bg_deltaxy[kMaxbg];   //[bg_]
   Int_t           bg_E[kMaxbg];   //[bg_]
   Int_t           bg_dssd_fire[kMaxbg][8];   //[bg_]
   Int_t           bg_flag_side[kMaxbg];   //[bg_]
   Int_t           bg_dssd_ex[kMaxbg][8];   //[bg_]
   Int_t           bg_dssd_ey[kMaxbg][8];   //[bg_]
   Int_t           bg_dssd_zmult[kMaxbg][8];   //[bg_]
   Float_t         bg_dssd_x[kMaxbg][8][5];   //[bg_]
   Float_t         bg_dssd_y[kMaxbg][8][5];   //[bg_]
   Int_t           bg_NaI_E[kMaxbg][3];   //[bg_]
   Int_t           bg_NaI_T[kMaxbg][3];   //[bg_]
   Int_t           bg_Qbeta_E[kMaxbg];   //[bg_]
   Int_t           bg_Qbeta_T[kMaxbg];   //[bg_]
   Int_t           bg_Qveto_E[kMaxbg];   //[bg_]
   Int_t           bg_Qveto_T[kMaxbg];   //[bg_]
   Int_t           bg_gc_hit[kMaxbg];   //[bg_]
   Int_t           bg_gc_ch[kMaxbg][84];   //[bg_]
   Int_t           bg_gc_DGFe[kMaxbg][84];   //[bg_]
   Int_t           bg_gc_TDCs[kMaxbg][84];   //[bg_]
   Int_t           bg_gc_DGFt[kMaxbg][84];   //[bg_]
   Int_t           bg_gc_TDCl[kMaxbg][84];   //[bg_]
   Double_t        bg_gc_E[kMaxbg][84];   //[bg_]
   Double_t        bg_gc_T[kMaxbg][84];   //[bg_]
   Int_t           bg_ab_hit[kMaxbg];   //[bg_]
   Int_t           bg_ab_ch[kMaxbg][84];   //[bg_]
   Int_t           bg_ab_DGFe[kMaxbg][84];   //[bg_]
   Int_t           bg_ab_TDCs[kMaxbg][84];   //[bg_]
   Int_t           bg_ab_DGFt[kMaxbg][84];   //[bg_]
   Int_t           bg_ab_TDCl[kMaxbg][84];   //[bg_]
   Double_t        bg_ab_E[kMaxbg][84];   //[bg_]
   Double_t        bg_ab_T[kMaxbg][84];   //[bg_]

   // List of branches
   TBranch        *b_imp_fUniqueID;   //!
   TBranch        *b_imp_fBits;   //!
   TBranch        *b_imp_run;   //!
   TBranch        *b_imp_ts;   //!
   TBranch        *b_imp_z;   //!
   TBranch        *b_imp_x;   //!
   TBranch        *b_imp_y;   //!
   TBranch        *b_imp_tx;   //!
   TBranch        *b_imp_ty;   //!
   TBranch        *b_imp_IfInterest;   //!
   TBranch        *b_imp_beta35;   //!
   TBranch        *b_imp_beta57;   //!
   TBranch        *b_imp_beta711;   //!
   TBranch        *b_imp_aoq37;   //!
   TBranch        *b_imp_zed;   //!
   TBranch        *b_imp_Zed;   //!
   TBranch        *b_imp_Mass;   //!
   TBranch        *b_imp_flagall;   //!
   TBranch        *b_imp_flagTSumX;   //!
   TBranch        *b_imp_flagTOFt;   //!
   TBranch        *b_imp_flagTOFq;   //!
   TBranch        *b_imp_flagReaction;   //!
   TBranch        *b_imp_flagdERelation;   //!
   TBranch        *b_imp_flagAngle;   //!
   TBranch        *b_imp_gc_hit;   //!
   TBranch        *b_imp_gc_ch;   //!
   TBranch        *b_imp_gc_DGFe;   //!
   TBranch        *b_imp_gc_TDCs;   //!
   TBranch        *b_imp_gc_DGFt;   //!
   TBranch        *b_imp_gc_TDCl;   //!
   TBranch        *b_imp_gc_E;   //!
   TBranch        *b_imp_gc_T;   //!
   TBranch        *b_imp_ab_hit;   //!
   TBranch        *b_imp_ab_ch;   //!
   TBranch        *b_imp_ab_DGFe;   //!
   TBranch        *b_imp_ab_TDCs;   //!
   TBranch        *b_imp_ab_DGFt;   //!
   TBranch        *b_imp_ab_TDCl;   //!
   TBranch        *b_imp_ab_E;   //!
   TBranch        *b_imp_ab_T;   //!
   TBranch        *b_beta_;   //!
   TBranch        *b_beta_fUniqueID;   //!
   TBranch        *b_beta_fBits;   //!
   TBranch        *b_beta_t;   //!
   TBranch        *b_beta_z;   //!
   TBranch        *b_beta_x;   //!
   TBranch        *b_beta_y;   //!
   TBranch        *b_beta_ex;   //!
   TBranch        *b_beta_ey;   //!
   TBranch        *b_beta_mulx;   //!
   TBranch        *b_beta_muly;   //!
   TBranch        *b_beta_deltaz;   //!
   TBranch        *b_beta_deltaxy;   //!
   TBranch        *b_beta_E;   //!
   TBranch        *b_beta_dssd_fire;   //!
   TBranch        *b_beta_flag_side;   //!
   TBranch        *b_beta_dssd_ex;   //!
   TBranch        *b_beta_dssd_ey;   //!
   TBranch        *b_beta_dssd_zmult;   //!
   TBranch        *b_beta_dssd_x;   //!
   TBranch        *b_beta_dssd_y;   //!
   TBranch        *b_beta_NaI_E;   //!
   TBranch        *b_beta_NaI_T;   //!
   TBranch        *b_beta_Qbeta_E;   //!
   TBranch        *b_beta_Qbeta_T;   //!
   TBranch        *b_beta_Qveto_E;   //!
   TBranch        *b_beta_Qveto_T;   //!
   TBranch        *b_beta_gc_hit;   //!
   TBranch        *b_beta_gc_ch;   //!
   TBranch        *b_beta_gc_DGFe;   //!
   TBranch        *b_beta_gc_TDCs;   //!
   TBranch        *b_beta_gc_DGFt;   //!
   TBranch        *b_beta_gc_TDCl;   //!
   TBranch        *b_beta_gc_E;   //!
   TBranch        *b_beta_gc_T;   //!
   TBranch        *b_beta_ab_hit;   //!
   TBranch        *b_beta_ab_ch;   //!
   TBranch        *b_beta_ab_DGFe;   //!
   TBranch        *b_beta_ab_TDCs;   //!
   TBranch        *b_beta_ab_DGFt;   //!
   TBranch        *b_beta_ab_TDCl;   //!
   TBranch        *b_beta_ab_E;   //!
   TBranch        *b_beta_ab_T;   //!
   TBranch        *b_bg_;   //!
   TBranch        *b_bg_fUniqueID;   //!
   TBranch        *b_bg_fBits;   //!
   TBranch        *b_bg_t;   //!
   TBranch        *b_bg_z;   //!
   TBranch        *b_bg_x;   //!
   TBranch        *b_bg_y;   //!
   TBranch        *b_bg_ex;   //!
   TBranch        *b_bg_ey;   //!
   TBranch        *b_bg_mulx;   //!
   TBranch        *b_bg_muly;   //!
   TBranch        *b_bg_deltaz;   //!
   TBranch        *b_bg_deltaxy;   //!
   TBranch        *b_bg_E;   //!
   TBranch        *b_bg_dssd_fire;   //!
   TBranch        *b_bg_flag_side;   //!
   TBranch        *b_bg_dssd_ex;   //!
   TBranch        *b_bg_dssd_ey;   //!
   TBranch        *b_bg_dssd_zmult;   //!
   TBranch        *b_bg_dssd_x;   //!
   TBranch        *b_bg_dssd_y;   //!
   TBranch        *b_bg_NaI_E;   //!
   TBranch        *b_bg_NaI_T;   //!
   TBranch        *b_bg_Qbeta_E;   //!
   TBranch        *b_bg_Qbeta_T;   //!
   TBranch        *b_bg_Qveto_E;   //!
   TBranch        *b_bg_Qveto_T;   //!
   TBranch        *b_bg_gc_hit;   //!
   TBranch        *b_bg_gc_ch;   //!
   TBranch        *b_bg_gc_DGFe;   //!
   TBranch        *b_bg_gc_TDCs;   //!
   TBranch        *b_bg_gc_DGFt;   //!
   TBranch        *b_bg_gc_TDCl;   //!
   TBranch        *b_bg_gc_E;   //!
   TBranch        *b_bg_gc_T;   //!
   TBranch        *b_bg_ab_hit;   //!
   TBranch        *b_bg_ab_ch;   //!
   TBranch        *b_bg_ab_DGFe;   //!
   TBranch        *b_bg_ab_TDCs;   //!
   TBranch        *b_bg_ab_DGFt;   //!
   TBranch        *b_bg_ab_TDCl;   //!
   TBranch        *b_bg_ab_E;   //!
   TBranch        *b_bg_ab_T;   //!

   test(TTree *tree=0);
   virtual ~test();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef test_cxx
test::test(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../root/final/ni78test/decay_new1032.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../root/final/ni78test/decay_new1032.root");
      }
      f->GetObject("decay",tree);

   }
   Init(tree);
}

test::~test()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t test::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t test::LoadTree(Long64_t entry)
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

void test::Init(TTree *tree)
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

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_imp_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_imp_fBits);
   fChain->SetBranchAddress("run", &run, &b_imp_run);
   fChain->SetBranchAddress("ts", &ts, &b_imp_ts);
   fChain->SetBranchAddress("z", &z, &b_imp_z);
   fChain->SetBranchAddress("x", &x, &b_imp_x);
   fChain->SetBranchAddress("y", &y, &b_imp_y);
   fChain->SetBranchAddress("tx", &tx, &b_imp_tx);
   fChain->SetBranchAddress("ty", &ty, &b_imp_ty);
   fChain->SetBranchAddress("IfInterest", &IfInterest, &b_imp_IfInterest);
   fChain->SetBranchAddress("beta35", &beta35, &b_imp_beta35);
   fChain->SetBranchAddress("beta57", &beta57, &b_imp_beta57);
   fChain->SetBranchAddress("beta711", &beta711, &b_imp_beta711);
   fChain->SetBranchAddress("aoq37", &aoq37, &b_imp_aoq37);
   fChain->SetBranchAddress("zed", &zed, &b_imp_zed);
   fChain->SetBranchAddress("Zed", &Zed, &b_imp_Zed);
   fChain->SetBranchAddress("Mass", &Mass, &b_imp_Mass);
   fChain->SetBranchAddress("flagall", &flagall, &b_imp_flagall);
   fChain->SetBranchAddress("flagTSumX", &flagTSumX, &b_imp_flagTSumX);
   fChain->SetBranchAddress("flagTOFt", &flagTOFt, &b_imp_flagTOFt);
   fChain->SetBranchAddress("flagTOFq", &flagTOFq, &b_imp_flagTOFq);
   fChain->SetBranchAddress("flagReaction", &flagReaction, &b_imp_flagReaction);
   fChain->SetBranchAddress("flagdERelation", &flagdERelation, &b_imp_flagdERelation);
   fChain->SetBranchAddress("flagAngle", &flagAngle, &b_imp_flagAngle);
   fChain->SetBranchAddress("gc_hit", &gc_hit, &b_imp_gc_hit);
   fChain->SetBranchAddress("gc_ch[84]", gc_ch, &b_imp_gc_ch);
   fChain->SetBranchAddress("gc_DGFe[84]", gc_DGFe, &b_imp_gc_DGFe);
   fChain->SetBranchAddress("gc_TDCs[84]", gc_TDCs, &b_imp_gc_TDCs);
   fChain->SetBranchAddress("gc_DGFt[84]", gc_DGFt, &b_imp_gc_DGFt);
   fChain->SetBranchAddress("gc_TDCl[84]", gc_TDCl, &b_imp_gc_TDCl);
   fChain->SetBranchAddress("gc_E[84]", gc_E, &b_imp_gc_E);
   fChain->SetBranchAddress("gc_T[84]", gc_T, &b_imp_gc_T);
   fChain->SetBranchAddress("ab_hit", &ab_hit, &b_imp_ab_hit);
   fChain->SetBranchAddress("ab_ch[84]", ab_ch, &b_imp_ab_ch);
   fChain->SetBranchAddress("ab_DGFe[84]", ab_DGFe, &b_imp_ab_DGFe);
   fChain->SetBranchAddress("ab_TDCs[84]", ab_TDCs, &b_imp_ab_TDCs);
   fChain->SetBranchAddress("ab_DGFt[84]", ab_DGFt, &b_imp_ab_DGFt);
   fChain->SetBranchAddress("ab_TDCl[84]", ab_TDCl, &b_imp_ab_TDCl);
   fChain->SetBranchAddress("ab_E[84]", ab_E, &b_imp_ab_E);
   fChain->SetBranchAddress("ab_T[84]", ab_T, &b_imp_ab_T);
   fChain->SetBranchAddress("beta", &beta_, &b_beta_);
   fChain->SetBranchAddress("beta.fUniqueID", beta_fUniqueID, &b_beta_fUniqueID);
   fChain->SetBranchAddress("beta.fBits", beta_fBits, &b_beta_fBits);
   fChain->SetBranchAddress("beta.t", beta_t, &b_beta_t);
   fChain->SetBranchAddress("beta.z", beta_z, &b_beta_z);
   fChain->SetBranchAddress("beta.x", beta_x, &b_beta_x);
   fChain->SetBranchAddress("beta.y", beta_y, &b_beta_y);
   fChain->SetBranchAddress("beta.ex", beta_ex, &b_beta_ex);
   fChain->SetBranchAddress("beta.ey", beta_ey, &b_beta_ey);
   fChain->SetBranchAddress("beta.mulx", beta_mulx, &b_beta_mulx);
   fChain->SetBranchAddress("beta.muly", beta_muly, &b_beta_muly);
   fChain->SetBranchAddress("beta.deltaz", beta_deltaz, &b_beta_deltaz);
   fChain->SetBranchAddress("beta.deltaxy", beta_deltaxy, &b_beta_deltaxy);
   fChain->SetBranchAddress("beta.E", beta_E, &b_beta_E);
   fChain->SetBranchAddress("beta.dssd_fire[8]", beta_dssd_fire, &b_beta_dssd_fire);
   fChain->SetBranchAddress("beta.flag_side", beta_flag_side, &b_beta_flag_side);
   fChain->SetBranchAddress("beta.dssd_ex[8]", beta_dssd_ex, &b_beta_dssd_ex);
   fChain->SetBranchAddress("beta.dssd_ey[8]", beta_dssd_ey, &b_beta_dssd_ey);
   fChain->SetBranchAddress("beta.dssd_zmult[8]", beta_dssd_zmult, &b_beta_dssd_zmult);
   fChain->SetBranchAddress("beta.dssd_x[8][5]", beta_dssd_x, &b_beta_dssd_x);
   fChain->SetBranchAddress("beta.dssd_y[8][5]", beta_dssd_y, &b_beta_dssd_y);
   fChain->SetBranchAddress("beta.NaI_E[3]", beta_NaI_E, &b_beta_NaI_E);
   fChain->SetBranchAddress("beta.NaI_T[3]", beta_NaI_T, &b_beta_NaI_T);
   fChain->SetBranchAddress("beta.Qbeta_E", beta_Qbeta_E, &b_beta_Qbeta_E);
   fChain->SetBranchAddress("beta.Qbeta_T", beta_Qbeta_T, &b_beta_Qbeta_T);
   fChain->SetBranchAddress("beta.Qveto_E", beta_Qveto_E, &b_beta_Qveto_E);
   fChain->SetBranchAddress("beta.Qveto_T", beta_Qveto_T, &b_beta_Qveto_T);
   fChain->SetBranchAddress("beta.gc_hit", beta_gc_hit, &b_beta_gc_hit);
   fChain->SetBranchAddress("beta.gc_ch[84]", beta_gc_ch, &b_beta_gc_ch);
   fChain->SetBranchAddress("beta.gc_DGFe[84]", beta_gc_DGFe, &b_beta_gc_DGFe);
   fChain->SetBranchAddress("beta.gc_TDCs[84]", beta_gc_TDCs, &b_beta_gc_TDCs);
   fChain->SetBranchAddress("beta.gc_DGFt[84]", beta_gc_DGFt, &b_beta_gc_DGFt);
   fChain->SetBranchAddress("beta.gc_TDCl[84]", beta_gc_TDCl, &b_beta_gc_TDCl);
   fChain->SetBranchAddress("beta.gc_E[84]", beta_gc_E, &b_beta_gc_E);
   fChain->SetBranchAddress("beta.gc_T[84]", beta_gc_T, &b_beta_gc_T);
   fChain->SetBranchAddress("beta.ab_hit", beta_ab_hit, &b_beta_ab_hit);
   fChain->SetBranchAddress("beta.ab_ch[84]", beta_ab_ch, &b_beta_ab_ch);
   fChain->SetBranchAddress("beta.ab_DGFe[84]", beta_ab_DGFe, &b_beta_ab_DGFe);
   fChain->SetBranchAddress("beta.ab_TDCs[84]", beta_ab_TDCs, &b_beta_ab_TDCs);
   fChain->SetBranchAddress("beta.ab_DGFt[84]", beta_ab_DGFt, &b_beta_ab_DGFt);
   fChain->SetBranchAddress("beta.ab_TDCl[84]", beta_ab_TDCl, &b_beta_ab_TDCl);
   fChain->SetBranchAddress("beta.ab_E[84]", beta_ab_E, &b_beta_ab_E);
   fChain->SetBranchAddress("beta.ab_T[84]", beta_ab_T, &b_beta_ab_T);
   fChain->SetBranchAddress("bg", &bg_, &b_bg_);
   fChain->SetBranchAddress("bg.fUniqueID", bg_fUniqueID, &b_bg_fUniqueID);
   fChain->SetBranchAddress("bg.fBits", bg_fBits, &b_bg_fBits);
   fChain->SetBranchAddress("bg.t", bg_t, &b_bg_t);
   fChain->SetBranchAddress("bg.z", bg_z, &b_bg_z);
   fChain->SetBranchAddress("bg.x", bg_x, &b_bg_x);
   fChain->SetBranchAddress("bg.y", bg_y, &b_bg_y);
   fChain->SetBranchAddress("bg.ex", bg_ex, &b_bg_ex);
   fChain->SetBranchAddress("bg.ey", bg_ey, &b_bg_ey);
   fChain->SetBranchAddress("bg.mulx", bg_mulx, &b_bg_mulx);
   fChain->SetBranchAddress("bg.muly", bg_muly, &b_bg_muly);
   fChain->SetBranchAddress("bg.deltaz", bg_deltaz, &b_bg_deltaz);
   fChain->SetBranchAddress("bg.deltaxy", bg_deltaxy, &b_bg_deltaxy);
   fChain->SetBranchAddress("bg.E", bg_E, &b_bg_E);
   fChain->SetBranchAddress("bg.dssd_fire[8]", bg_dssd_fire, &b_bg_dssd_fire);
   fChain->SetBranchAddress("bg.flag_side", bg_flag_side, &b_bg_flag_side);
   fChain->SetBranchAddress("bg.dssd_ex[8]", bg_dssd_ex, &b_bg_dssd_ex);
   fChain->SetBranchAddress("bg.dssd_ey[8]", bg_dssd_ey, &b_bg_dssd_ey);
   fChain->SetBranchAddress("bg.dssd_zmult[8]", bg_dssd_zmult, &b_bg_dssd_zmult);
   fChain->SetBranchAddress("bg.dssd_x[8][5]", bg_dssd_x, &b_bg_dssd_x);
   fChain->SetBranchAddress("bg.dssd_y[8][5]", bg_dssd_y, &b_bg_dssd_y);
   fChain->SetBranchAddress("bg.NaI_E[3]", bg_NaI_E, &b_bg_NaI_E);
   fChain->SetBranchAddress("bg.NaI_T[3]", bg_NaI_T, &b_bg_NaI_T);
   fChain->SetBranchAddress("bg.Qbeta_E", bg_Qbeta_E, &b_bg_Qbeta_E);
   fChain->SetBranchAddress("bg.Qbeta_T", bg_Qbeta_T, &b_bg_Qbeta_T);
   fChain->SetBranchAddress("bg.Qveto_E", bg_Qveto_E, &b_bg_Qveto_E);
   fChain->SetBranchAddress("bg.Qveto_T", bg_Qveto_T, &b_bg_Qveto_T);
   fChain->SetBranchAddress("bg.gc_hit", bg_gc_hit, &b_bg_gc_hit);
   fChain->SetBranchAddress("bg.gc_ch[84]", bg_gc_ch, &b_bg_gc_ch);
   fChain->SetBranchAddress("bg.gc_DGFe[84]", bg_gc_DGFe, &b_bg_gc_DGFe);
   fChain->SetBranchAddress("bg.gc_TDCs[84]", bg_gc_TDCs, &b_bg_gc_TDCs);
   fChain->SetBranchAddress("bg.gc_DGFt[84]", bg_gc_DGFt, &b_bg_gc_DGFt);
   fChain->SetBranchAddress("bg.gc_TDCl[84]", bg_gc_TDCl, &b_bg_gc_TDCl);
   fChain->SetBranchAddress("bg.gc_E[84]", bg_gc_E, &b_bg_gc_E);
   fChain->SetBranchAddress("bg.gc_T[84]", bg_gc_T, &b_bg_gc_T);
   fChain->SetBranchAddress("bg.ab_hit", bg_ab_hit, &b_bg_ab_hit);
   fChain->SetBranchAddress("bg.ab_ch[84]", bg_ab_ch, &b_bg_ab_ch);
   fChain->SetBranchAddress("bg.ab_DGFe[84]", bg_ab_DGFe, &b_bg_ab_DGFe);
   fChain->SetBranchAddress("bg.ab_TDCs[84]", bg_ab_TDCs, &b_bg_ab_TDCs);
   fChain->SetBranchAddress("bg.ab_DGFt[84]", bg_ab_DGFt, &b_bg_ab_DGFt);
   fChain->SetBranchAddress("bg.ab_TDCl[84]", bg_ab_TDCl, &b_bg_ab_TDCl);
   fChain->SetBranchAddress("bg.ab_E[84]", bg_ab_E, &b_bg_ab_E);
   fChain->SetBranchAddress("bg.ab_T[84]", bg_ab_T, &b_bg_ab_T);
   Notify();
}

Bool_t test::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void test::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t test::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef test_cxx
