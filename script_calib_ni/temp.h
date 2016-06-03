//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb 21 14:53:59 2013 by ROOT version 5.34/03
// from TTree decay/decay
// found on file: ../root/sistopper/ni78test/decay_new1013.root
//////////////////////////////////////////////////////////

#ifndef temp_h
#define temp_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TObject.h>
#include <TClonesArray.h>

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxbeta = 33;
const Int_t kMaxbg = 12;

class temp {
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
   Double_t        pid_Delta_F3F5;
   Double_t        pid_TOF_F3F7;
   Double_t        pid_Beta_F3F5;
   Double_t        pid_Beta_F5F7;
   Double_t        pid_AoQ_F3F5;
   Double_t        pid_Zet_F11;
   Double_t        bigrips_aoq;
   Double_t        bigrips_zet;
   Double_t        bigrips_beta;
   Double_t        aoq;
   Double_t        zet;
   Double_t        mass;
   Int_t           Mass;
   Int_t           Zed;
   Int_t           beta_;
   UInt_t          beta_fUniqueID[kMaxbeta];   //[beta_]
   UInt_t          beta_fBits[kMaxbeta];   //[beta_]
   Int_t           beta_t[kMaxbeta];   //[beta_]
   Int_t           beta_z[kMaxbeta];   //[beta_]
   Int_t           beta_x[kMaxbeta];   //[beta_]
   Int_t           beta_y[kMaxbeta];   //[beta_]
   Int_t           beta_ex[kMaxbeta];   //[beta_]
   Int_t           beta_ey[kMaxbeta];   //[beta_]
   Int_t           beta_deltaz[kMaxbeta];   //[beta_]
   Int_t           beta_deltaxy[kMaxbeta];   //[beta_]
   Int_t           beta_E[kMaxbeta];   //[beta_]
   Int_t           beta_dssd_fire[kMaxbeta][8];   //[beta_]
   Int_t           beta_dssd_ex[kMaxbeta][8];   //[beta_]
   Int_t           beta_dssd_ey[kMaxbeta][8];   //[beta_]
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
   Int_t           bg_t[kMaxbg];   //[bg_]
   Int_t           bg_z[kMaxbg];   //[bg_]
   Int_t           bg_x[kMaxbg];   //[bg_]
   Int_t           bg_y[kMaxbg];   //[bg_]
   Int_t           bg_ex[kMaxbg];   //[bg_]
   Int_t           bg_ey[kMaxbg];   //[bg_]
   Int_t           bg_deltaz[kMaxbg];   //[bg_]
   Int_t           bg_deltaxy[kMaxbg];   //[bg_]
   Int_t           bg_E[kMaxbg];   //[bg_]
   Int_t           bg_dssd_fire[kMaxbg][8];   //[bg_]
   Int_t           bg_dssd_ex[kMaxbg][8];   //[bg_]
   Int_t           bg_dssd_ey[kMaxbg][8];   //[bg_]
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
   TBranch        *b_imp_pid_Delta_F3F5;   //!
   TBranch        *b_imp_pid_TOF_F3F7;   //!
   TBranch        *b_imp_pid_Beta_F3F5;   //!
   TBranch        *b_imp_pid_Beta_F5F7;   //!
   TBranch        *b_imp_pid_AoQ_F3F5;   //!
   TBranch        *b_imp_pid_Zet_F11;   //!
   TBranch        *b_imp_bigrips_aoq;   //!
   TBranch        *b_imp_bigrips_zet;   //!
   TBranch        *b_imp_bigrips_beta;   //!
   TBranch        *b_imp_aoq;   //!
   TBranch        *b_imp_zet;   //!
   TBranch        *b_imp_mass;   //!
   TBranch        *b_imp_Mass;   //!
   TBranch        *b_imp_Zed;   //!
   TBranch        *b_beta_;   //!
   TBranch        *b_beta_fUniqueID;   //!
   TBranch        *b_beta_fBits;   //!
   TBranch        *b_beta_t;   //!
   TBranch        *b_beta_z;   //!
   TBranch        *b_beta_x;   //!
   TBranch        *b_beta_y;   //!
   TBranch        *b_beta_ex;   //!
   TBranch        *b_beta_ey;   //!
   TBranch        *b_beta_deltaz;   //!
   TBranch        *b_beta_deltaxy;   //!
   TBranch        *b_beta_E;   //!
   TBranch        *b_beta_dssd_fire;   //!
   TBranch        *b_beta_dssd_ex;   //!
   TBranch        *b_beta_dssd_ey;   //!
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
   TBranch        *b_bg_deltaz;   //!
   TBranch        *b_bg_deltaxy;   //!
   TBranch        *b_bg_E;   //!
   TBranch        *b_bg_dssd_fire;   //!
   TBranch        *b_bg_dssd_ex;   //!
   TBranch        *b_bg_dssd_ey;   //!
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

   temp(TTree *tree=0);
   virtual ~temp();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef temp_cxx
temp::temp(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../root/sistopper/ni78test/decay_new1013.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../root/sistopper/ni78test/decay_new1013.root");
      }
      f->GetObject("decay",tree);

   }
   Init(tree);
}

temp::~temp()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t temp::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t temp::LoadTree(Long64_t entry)
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

void temp::Init(TTree *tree)
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
   fChain->SetBranchAddress("pid_Delta_F3F5", &pid_Delta_F3F5, &b_imp_pid_Delta_F3F5);
   fChain->SetBranchAddress("pid_TOF_F3F7", &pid_TOF_F3F7, &b_imp_pid_TOF_F3F7);
   fChain->SetBranchAddress("pid_Beta_F3F5", &pid_Beta_F3F5, &b_imp_pid_Beta_F3F5);
   fChain->SetBranchAddress("pid_Beta_F5F7", &pid_Beta_F5F7, &b_imp_pid_Beta_F5F7);
   fChain->SetBranchAddress("pid_AoQ_F3F5", &pid_AoQ_F3F5, &b_imp_pid_AoQ_F3F5);
   fChain->SetBranchAddress("pid_Zet_F11", &pid_Zet_F11, &b_imp_pid_Zet_F11);
   fChain->SetBranchAddress("bigrips_aoq", &bigrips_aoq, &b_imp_bigrips_aoq);
   fChain->SetBranchAddress("bigrips_zet", &bigrips_zet, &b_imp_bigrips_zet);
   fChain->SetBranchAddress("bigrips_beta", &bigrips_beta, &b_imp_bigrips_beta);
   fChain->SetBranchAddress("aoq", &aoq, &b_imp_aoq);
   fChain->SetBranchAddress("zet", &zet, &b_imp_zet);
   fChain->SetBranchAddress("mass", &mass, &b_imp_mass);
   fChain->SetBranchAddress("Mass", &Mass, &b_imp_Mass);
   fChain->SetBranchAddress("Zed", &Zed, &b_imp_Zed);
   fChain->SetBranchAddress("beta", &beta_, &b_beta_);
   fChain->SetBranchAddress("beta.fUniqueID", beta_fUniqueID, &b_beta_fUniqueID);
   fChain->SetBranchAddress("beta.fBits", beta_fBits, &b_beta_fBits);
   fChain->SetBranchAddress("beta.t", beta_t, &b_beta_t);
   fChain->SetBranchAddress("beta.z", beta_z, &b_beta_z);
   fChain->SetBranchAddress("beta.x", beta_x, &b_beta_x);
   fChain->SetBranchAddress("beta.y", beta_y, &b_beta_y);
   fChain->SetBranchAddress("beta.ex", beta_ex, &b_beta_ex);
   fChain->SetBranchAddress("beta.ey", beta_ey, &b_beta_ey);
   fChain->SetBranchAddress("beta.deltaz", beta_deltaz, &b_beta_deltaz);
   fChain->SetBranchAddress("beta.deltaxy", beta_deltaxy, &b_beta_deltaxy);
   fChain->SetBranchAddress("beta.E", beta_E, &b_beta_E);
   fChain->SetBranchAddress("beta.dssd_fire[8]", beta_dssd_fire, &b_beta_dssd_fire);
   fChain->SetBranchAddress("beta.dssd_ex[8]", beta_dssd_ex, &b_beta_dssd_ex);
   fChain->SetBranchAddress("beta.dssd_ey[8]", beta_dssd_ey, &b_beta_dssd_ey);
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
   fChain->SetBranchAddress("bg.deltaz", bg_deltaz, &b_bg_deltaz);
   fChain->SetBranchAddress("bg.deltaxy", bg_deltaxy, &b_bg_deltaxy);
   fChain->SetBranchAddress("bg.E", bg_E, &b_bg_E);
   fChain->SetBranchAddress("bg.dssd_fire[8]", bg_dssd_fire, &b_bg_dssd_fire);
   fChain->SetBranchAddress("bg.dssd_ex[8]", bg_dssd_ex, &b_bg_dssd_ex);
   fChain->SetBranchAddress("bg.dssd_ey[8]", bg_dssd_ey, &b_bg_dssd_ey);
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

Bool_t temp::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void temp::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t temp::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef temp_cxx
