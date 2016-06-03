//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb 15 10:23:11 2013 by ROOT version 5.34/03
// from TTree decay/decay
// found on file: ../root/sistopper/ni78test/decay_new1032.root
//////////////////////////////////////////////////////////

#ifndef decay_ggmatrix_h
#define decay_ggmatrix_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TObject.h>
#include <TClonesArray.h>

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxbeta = 100;

class decay_ggmatrix {
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

   /**** for recalculating addback *****/
   static const Int_t
                   addback_hitpattern[7][7];
   Int_t           abclhitnum[12];//hit number in each cluster
   Int_t           abcrhit[12][7];//cristals hit by gamma in one cluster
   Int_t           abDGFe[12][7];
   Int_t           abDGFt[12][7];
   Int_t           abTDCs[12][7];
   Int_t           abTDCl[12][7];
   Double_t        abE[12][7];
   Double_t        abT[12][7];
   static const Double_t        energy_thr;//minimum energy for addback, in unit of keV
   static const Double_t        time_thr;//time window of addback, in unit of ns

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

   decay_ggmatrix(char *filename, TTree *tree=0);
   virtual ~decay_ggmatrix();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   /**** for recalculating addback *****/
   virtual void     GammaAddback(int decay_index);
   virtual void     GetRawAddback(int decay_index);
   virtual Int_t    CheckAddback2(int cl, int cr1, int cr2);
   virtual Int_t    CheckAddback3(int cl, int cr1, int cr2, int cr3);
   virtual Int_t    CheckAbPosition(int cl, int cr1, int cr2);
   virtual Int_t    CheckAbEnergy(int cl, int cr1, int cr2);
   virtual Int_t    CheckAbTime(int cl, int cr1, int cr2);
   virtual Int_t    FindMaxE(int cl, int *cr, int dim);
   Double_t         rand05();
};

decay_ggmatrix::decay_ggmatrix(char *filename, TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
      if (!f || !f->IsOpen()) {
         f = new TFile(filename);
      }
      f->GetObject("decay",tree);

   }
   Init(tree);
}

decay_ggmatrix::~decay_ggmatrix()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t decay_ggmatrix::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t decay_ggmatrix::LoadTree(Long64_t entry)
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

void decay_ggmatrix::Init(TTree *tree)
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
   Notify();
}

Bool_t decay_ggmatrix::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void decay_ggmatrix::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t decay_ggmatrix::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

/***** for addback ****/
const Double_t decay_ggmatrix::time_thr=100;
const Double_t decay_ggmatrix::energy_thr=200;

void decay_ggmatrix::GammaAddback(int decay_index){
   int max_ch;

   GetRawAddback(decay_index);
   int cl=0, cr[3]={0,0,0};
   beta_ab_hit[decay_index]=0;
   for(cl = 0; cl<12; cl++){
      if(abclhitnum[cl]==2){
         //std::cout<<abT[cl][0]<<", "<<abT[cl][1]<<std::endl;
         if(CheckAddback2(cl,0,1)==1){
            //std::cout<<"come here"<<std::endl;
            cr[0]=0;
            cr[1]=1;
            max_ch = FindMaxE(cl,cr,2);
            beta_ab_ch[decay_index][beta_ab_hit[decay_index]] = cl*7 + abcrhit[cl][max_ch];
            beta_ab_DGFe[decay_index][beta_ab_hit[decay_index]] = abDGFe[cl][max_ch];
            beta_ab_DGFt[decay_index][beta_ab_hit[decay_index]] = abDGFt[cl][max_ch];
            beta_ab_TDCs[decay_index][beta_ab_hit[decay_index]] = abTDCs[cl][max_ch];
            beta_ab_TDCl[decay_index][beta_ab_hit[decay_index]] = abTDCl[cl][max_ch];
            beta_ab_E[decay_index][beta_ab_hit[decay_index]] = abE[cl][0] + abE[cl][1];
            beta_ab_T[decay_index][beta_ab_hit[decay_index]] = abT[cl][max_ch];
            beta_ab_hit[decay_index]++;
         }else{
            for(int i=0; i<abclhitnum[cl]; i++){
               beta_ab_ch[decay_index][beta_ab_hit[decay_index]] = cl*7 + abcrhit[cl][i];
               beta_ab_DGFe[decay_index][beta_ab_hit[decay_index]] = abDGFe[cl][i];
               beta_ab_DGFt[decay_index][beta_ab_hit[decay_index]] = abDGFt[cl][i];
               beta_ab_TDCs[decay_index][beta_ab_hit[decay_index]] = abTDCs[cl][i];
               beta_ab_TDCl[decay_index][beta_ab_hit[decay_index]] = abTDCl[cl][i];
               beta_ab_E[decay_index][beta_ab_hit[decay_index]] = abE[cl][i];
               beta_ab_T[decay_index][beta_ab_hit[decay_index]] = abT[cl][i];
               beta_ab_hit[decay_index]++;
            }
         }
      }else if(abclhitnum[cl]==3){
         if(CheckAddback3(cl,0,1,2)==1){
            cr[0]=0;
            cr[1]=1;
            cr[2]=2;
            max_ch = FindMaxE(cl,cr,3);
            beta_ab_ch[decay_index][beta_ab_hit[decay_index]] = cl*7 + abcrhit[cl][max_ch];
            beta_ab_DGFe[decay_index][beta_ab_hit[decay_index]] = abDGFe[cl][max_ch];
            beta_ab_DGFt[decay_index][beta_ab_hit[decay_index]] = abDGFt[cl][max_ch];
            beta_ab_TDCs[decay_index][beta_ab_hit[decay_index]] = abTDCs[cl][max_ch];
            beta_ab_TDCl[decay_index][beta_ab_hit[decay_index]] = abTDCl[cl][max_ch];
            beta_ab_E[decay_index][beta_ab_hit[decay_index]] = abE[cl][0] + abE[cl][1] + abE[cl][2];
            beta_ab_T[decay_index][beta_ab_hit[decay_index]] = abT[cl][max_ch];
            beta_ab_hit[decay_index]++;
         }else if(CheckAddback2(cl,0,1)==1){
            cr[0]=0;
            cr[1]=1;
            max_ch = FindMaxE(cl,cr,2);
            beta_ab_ch[decay_index][beta_ab_hit[decay_index]] = cl*7 + abcrhit[cl][max_ch];
            beta_ab_DGFe[decay_index][beta_ab_hit[decay_index]] = abDGFe[cl][max_ch];
            beta_ab_DGFt[decay_index][beta_ab_hit[decay_index]] = abDGFt[cl][max_ch];
            beta_ab_TDCs[decay_index][beta_ab_hit[decay_index]] = abTDCs[cl][max_ch];
            beta_ab_TDCl[decay_index][beta_ab_hit[decay_index]] = abTDCl[cl][max_ch];
            beta_ab_E[decay_index][beta_ab_hit[decay_index]] = abE[cl][0] + abE[cl][1];
            beta_ab_T[decay_index][beta_ab_hit[decay_index]] = abT[cl][max_ch];
            beta_ab_hit[decay_index]++;
            beta_ab_ch[decay_index][beta_ab_hit[decay_index]] = cl*7 + abcrhit[cl][2];
            beta_ab_DGFe[decay_index][beta_ab_hit[decay_index]] = abDGFe[cl][2];
            beta_ab_DGFt[decay_index][beta_ab_hit[decay_index]] = abDGFt[cl][2];
            beta_ab_TDCs[decay_index][beta_ab_hit[decay_index]] = abTDCs[cl][2];
            beta_ab_TDCl[decay_index][beta_ab_hit[decay_index]] = abTDCl[cl][2];
            beta_ab_E[decay_index][beta_ab_hit[decay_index]] = abE[cl][2];
            beta_ab_T[decay_index][beta_ab_hit[decay_index]] = abT[cl][2];
            beta_ab_hit[decay_index]++;
         }else if(CheckAddback2(cl,0,2)==1){
            cr[0]=0;
            cr[1]=2;
            max_ch = FindMaxE(cl,cr,2);
            beta_ab_ch[decay_index][beta_ab_hit[decay_index]] = cl*7 + abcrhit[cl][max_ch];
            beta_ab_DGFe[decay_index][beta_ab_hit[decay_index]] = abDGFe[cl][max_ch];
            beta_ab_DGFt[decay_index][beta_ab_hit[decay_index]] = abDGFt[cl][max_ch];
            beta_ab_TDCs[decay_index][beta_ab_hit[decay_index]] = abTDCs[cl][max_ch];
            beta_ab_TDCl[decay_index][beta_ab_hit[decay_index]] = abTDCl[cl][max_ch];
            beta_ab_E[decay_index][beta_ab_hit[decay_index]] = abE[cl][0] + abE[cl][2];
            beta_ab_T[decay_index][beta_ab_hit[decay_index]] = abT[cl][max_ch];
            beta_ab_hit[decay_index]++;
            beta_ab_ch[decay_index][beta_ab_hit[decay_index]] = cl*7 + abcrhit[cl][1];
            beta_ab_DGFe[decay_index][beta_ab_hit[decay_index]] = abDGFe[cl][1];
            beta_ab_DGFt[decay_index][beta_ab_hit[decay_index]] = abDGFt[cl][1];
            beta_ab_TDCs[decay_index][beta_ab_hit[decay_index]] = abTDCs[cl][1];
            beta_ab_TDCl[decay_index][beta_ab_hit[decay_index]] = abTDCl[cl][1];
            beta_ab_E[decay_index][beta_ab_hit[decay_index]] = abE[cl][1];
            beta_ab_T[decay_index][beta_ab_hit[decay_index]] = abT[cl][1];
            beta_ab_hit[decay_index]++;
         }else if(CheckAddback2(cl,1,2)==1){
            cr[0]=1;
            cr[1]=2;
            max_ch = FindMaxE(cl,cr,2);
            beta_ab_ch[decay_index][beta_ab_hit[decay_index]] = cl*7 + abcrhit[cl][max_ch];
            beta_ab_DGFe[decay_index][beta_ab_hit[decay_index]] = abDGFe[cl][max_ch];
            beta_ab_DGFt[decay_index][beta_ab_hit[decay_index]] = abDGFt[cl][max_ch];
            beta_ab_TDCs[decay_index][beta_ab_hit[decay_index]] = abTDCs[cl][max_ch];
            beta_ab_TDCl[decay_index][beta_ab_hit[decay_index]] = abTDCl[cl][max_ch];
            beta_ab_E[decay_index][beta_ab_hit[decay_index]] = abE[cl][1] + abE[cl][2];
            beta_ab_T[decay_index][beta_ab_hit[decay_index]] = abT[cl][max_ch];
            beta_ab_hit[decay_index]++;
            beta_ab_ch[decay_index][beta_ab_hit[decay_index]] = cl*7 + abcrhit[cl][0];
            beta_ab_DGFe[decay_index][beta_ab_hit[decay_index]] = abDGFe[cl][0];
            beta_ab_DGFt[decay_index][beta_ab_hit[decay_index]] = abDGFt[cl][0];
            beta_ab_TDCs[decay_index][beta_ab_hit[decay_index]] = abTDCs[cl][0];
            beta_ab_TDCl[decay_index][beta_ab_hit[decay_index]] = abTDCl[cl][0];
            beta_ab_E[decay_index][beta_ab_hit[decay_index]] = abE[cl][0];
            beta_ab_T[decay_index][beta_ab_hit[decay_index]] = abT[cl][0];
            beta_ab_hit[decay_index]++;
         }else{
            for(int i=0; i<abclhitnum[cl]; i++){
               beta_ab_ch[decay_index][beta_ab_hit[decay_index]] = cl*7 + abcrhit[cl][i];
               beta_ab_DGFe[decay_index][beta_ab_hit[decay_index]] = abDGFe[cl][i];
               beta_ab_DGFt[decay_index][beta_ab_hit[decay_index]] = abDGFt[cl][i];
               beta_ab_TDCs[decay_index][beta_ab_hit[decay_index]] = abTDCs[cl][i];
               beta_ab_TDCl[decay_index][beta_ab_hit[decay_index]] = abTDCl[cl][i];
               beta_ab_E[decay_index][beta_ab_hit[decay_index]] = abE[cl][i];
               beta_ab_T[decay_index][beta_ab_hit[decay_index]] = abT[cl][i];
               beta_ab_hit[decay_index]++;
            }
         }
      }else{
         for(int i=0; i<abclhitnum[cl]; i++){
            beta_ab_ch[decay_index][beta_ab_hit[decay_index]] = cl*7 + abcrhit[cl][i];
            beta_ab_DGFe[decay_index][beta_ab_hit[decay_index]] = abDGFe[cl][i];
            beta_ab_DGFt[decay_index][beta_ab_hit[decay_index]] = abDGFt[cl][i];
            beta_ab_TDCs[decay_index][beta_ab_hit[decay_index]] = abTDCs[cl][i];
            beta_ab_TDCl[decay_index][beta_ab_hit[decay_index]] = abTDCl[cl][i];
            beta_ab_E[decay_index][beta_ab_hit[decay_index]] = abE[cl][i];
            beta_ab_T[decay_index][beta_ab_hit[decay_index]] = abT[cl][i];
            beta_ab_hit[decay_index]++;
         }
      }
   }
}

Int_t decay_ggmatrix::CheckAddback2(int cl, int cr1, int cr2){
   int result = CheckAbPosition(cl,cr1,cr2)*CheckAbEnergy(cl,cr1,cr2)*CheckAbTime(cl,cr1,cr2);
   if(result == 1){
      return 1;
   }else{
      return 0;
   }
}

Int_t decay_ggmatrix::CheckAddback3(int cl, int cr1, int cr2, int cr3){
   if(CheckAddback2(cl,cr1,cr2)==1){
      if(CheckAddback2(cl,cr1,cr3)==1 || CheckAddback2(cl,cr2,cr3)==1){
         return 1;
      }else{
         return 0;
      }
   }else{
      return 0;
   }
}

void decay_ggmatrix::GetRawAddback(int decay_index){
   int cl, cr;
   for(int i=0; i<12; i++){
      abclhitnum[i]=0;
      for(int j=0; j<12; j++){
         abcrhit[i][j]=-1;
         abDGFe[i][j]=-1;
         abDGFt[i][j]=-1;
         abTDCs[i][j]=-1;
         abTDCl[i][j]=-1;
         abE[i][j]=-1;
         abT[i][j]=-1;
      }
   }
   for(int i=0; i<gc_hit[decay_index]; i++){
      cl=beta_gc_ch[decay_index][i]/7;
      cr=beta_gc_ch[decay_index][i]%7;
      abcrhit[cl][abclhitnum[cl]]=cr;
      abDGFe[cl][abclhitnum[cl]]=beta_gc_DGFe[decay_index][i];
      abDGFt[cl][abclhitnum[cl]]=beta_gc_DGFt[decay_index][i];
      abTDCs[cl][abclhitnum[cl]]=beta_gc_TDCs[decay_index][i];
      abTDCl[cl][abclhitnum[cl]]=beta_gc_TDCl[decay_index][i];
      abE[cl][abclhitnum[cl]]=beta_gc_E[decay_index][i];
      abT[cl][abclhitnum[cl]]=beta_gc_T[decay_index][i];
      abclhitnum[cl]++;
   }
}

Int_t decay_ggmatrix::CheckAbPosition(int cl, int cr1, int cr2){
   if(addback_hitpattern[abcrhit[cl][cr1]][abcrhit[cl][cr2]]==1){
      return 1;
   }else{
      return 0;
   }
}

Int_t decay_ggmatrix::CheckAbEnergy(int cl, int cr1, int cr2){
   if(abE[cl][cr1]+abE[cl][cr2]>energy_thr){
      return 1;
   }else{
      return 0;
   }
}

Int_t decay_ggmatrix::CheckAbTime(int cl, int cr1, int cr2){
   Double_t time_diff = fabs(abT[cl][cr1]-abT[cl][cr2]);
   //std::cout<<"diff = "<<time_diff<<", thr = "<<time_thr<<std::endl;
   if(time_diff < time_thr){
      //std::cout<<"come here"<<std::endl;
      return 1;
   }else{
      return 0;
   }
}

Int_t decay_ggmatrix::FindMaxE(int cl, int *cr, int dim){
   int max_ch=0;
   int max_E=0;
   for(int i=0; i<dim; i++){
      if(abE[cl][cr[i]]>max_E){
         max_ch=cr[i];
         max_E=abE[cl][cr[i]];
      }
   }
   return max_ch;
}

const int decay_ggmatrix::addback_hitpattern[7][7] = {
   {0,1,0,0,0,1,1},
   {1,0,1,0,0,0,1},
   {0,1,0,1,0,0,1},
   {0,0,1,0,1,0,1},
   {0,0,0,1,0,1,1},
   {1,0,0,0,1,0,1},
   {1,1,1,1,1,1,1},
};

Double_t decay_ggmatrix::rand05()
{
   return rand()*1./RAND_MAX - 0.5;
}
#endif // #ifdef decay_ggmatrix_cxx
