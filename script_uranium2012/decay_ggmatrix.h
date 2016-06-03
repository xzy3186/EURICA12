//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Nov  9 03:11:39 2012 by ROOT version 5.32/00
// from TTree decay/decay
// found on file: ../root/sistopper/decay104-112.root
//////////////////////////////////////////////////////////

#ifndef decay_ggmatrix_h
#define decay_ggmatrix_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class decay_ggmatrix {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Long64_t        t;
   Int_t           x;
   Int_t           y;
   Int_t           z;
   Int_t           deltaz;
   Int_t           dssd_E;
   Int_t           numdssd;
   Int_t           dssd_ex[8];
   Int_t           dssd_ey[8];
   //Int_t           dssd_E_X[8][60];   //[numdssd]
   //Int_t           dssd_ch_X[8][60];   //[numdssd]
   //Int_t           dssd_id_X[8][60];   //[numdssd]
   //Int_t           dssd_E_Y[8][40];   //[numdssd]
   //Int_t           dssd_ch_Y[8][40];   //[numdssd]
   //Int_t           dssd_id_Y[8][40];   //[numdssd]
   //Int_t           dssd_T_X[8][60][10];   //[numdssd]
   //Int_t           dssd_T_Y[8][40][10];   //[numdssd]

   Double_t        pid_Delta_F3F5;
   Double_t        pid_TOF_F3F7;
   Double_t        pid_Beta_F3F5;
   Double_t        pid_Beta_F5F7;
   Double_t        pid_AoQ_F3F5;
   Double_t        pid_Zet_F11;
   Double_t        bigrips_zet;
   Double_t        bigrips_aoq;
   Double_t        bigrips_beta;

   Double_t        aoq;
   Double_t        zet;
   Double_t        mass;
   Int_t           Mass;
   Int_t           Zed;

   Int_t           Qbeta_E;
   Int_t           Qbeta_T;
   Int_t           Qveto_E;
   Int_t           Qveto_T;
   Int_t           NaI_E[3];
   Int_t           NaI_T[3];
   Int_t           index;
   Int_t           run;
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
   TBranch        *b_t;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_z;   //!
   TBranch        *b_deltaz;   //!
   TBranch        *b_dssd_E;   //!
   TBranch        *b_numdssd;   //!
   TBranch        *b_dssd_ex;   //!
   TBranch        *b_dssd_ey;   //!
   //TBranch        *b_dssd_E_X;   //!
   //TBranch        *b_dssd_ch_X;   //!
   //TBranch        *b_dssd_id_X;   //!
   //TBranch        *b_dssd_E_Y;   //!
   //TBranch        *b_dssd_ch_Y;   //!
   //TBranch        *b_dssd_id_Y;   //!
   //TBranch        *b_dssd_T_X;   //!
   //TBranch        *b_dssd_T_Y;   //!

   TBranch        *b_pid_Delta_F3F5;   //!
   TBranch        *b_pid_TOF_F3F7;   //!
   TBranch        *b_pid_Beta_F3F5;   //!
   TBranch        *b_pid_Beta_F5F7;   //!
   TBranch        *b_pid_AoQ_F3F5;   //!
   TBranch        *b_pid_Zet_F11;   //!
   TBranch        *b_bigrips_zet;   //!
   TBranch        *b_bigrips_aoq;   //!
   TBranch        *b_bigrips_beta;   //!

   TBranch        *b_aoq;   //!
   TBranch        *b_zet;   //!
   TBranch        *b_mass;   //!
   TBranch        *b_Zed;   //!
   TBranch        *b_Mass;   //!

   TBranch        *b_Qbeta_E;   //!
   TBranch        *b_Qbeta_T;   //!
   TBranch        *b_Qveto_E;   //!
   TBranch        *b_Qveto_T;   //!
   TBranch        *b_NaI_E;
   TBranch        *b_NaI_T;
   TBranch        *b_index;   //!
   TBranch        *b_run;   //!
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

   decay_ggmatrix(char *filename, TTree *tree=0);
   virtual ~decay_ggmatrix();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   /**** for recalculating addback *****/
   virtual void     GammaAddback();
   virtual void     GetRawAddback();
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

   fChain->SetBranchAddress("t", &t, &b_t);
   fChain->SetBranchAddress("x", &x, &b_x);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("z", &z, &b_z);
   fChain->SetBranchAddress("deltaz", &deltaz, &b_deltaz);
   fChain->SetBranchAddress("dssd_E", &dssd_E, &b_dssd_E);
   fChain->SetBranchAddress("dssd_ex", dssd_ex, &b_dssd_ex);
   fChain->SetBranchAddress("dssd_ey", dssd_ey, &b_dssd_ey);
   //fChain->SetBranchAddress("dssd_E_X", dssd_E_X, &b_dssd_E_X);
   //fChain->SetBranchAddress("dssd_ch_X", dssd_ch_X, &b_dssd_ch_X);
   //fChain->SetBranchAddress("dssd_id_X", dssd_id_X, &b_dssd_id_X);
   //fChain->SetBranchAddress("dssd_E_Y", dssd_E_Y, &b_dssd_E_Y);
   //fChain->SetBranchAddress("dssd_ch_Y", dssd_ch_Y, &b_dssd_ch_Y);
   //fChain->SetBranchAddress("dssd_id_Y", dssd_id_Y, &b_dssd_id_Y);
   //fChain->SetBranchAddress("dssd_T_X", dssd_T_X, &b_dssd_T_X);
   //fChain->SetBranchAddress("dssd_T_Y", dssd_T_Y, &b_dssd_T_Y);

   fChain->SetBranchAddress("pid_Delta_F3F5", &pid_Delta_F3F5, &b_pid_Delta_F3F5);
   fChain->SetBranchAddress("pid_TOF_F3F7", &pid_TOF_F3F7, &b_pid_TOF_F3F7);
   fChain->SetBranchAddress("pid_Beta_F3F5", &pid_Beta_F3F5, &b_pid_Beta_F3F5);
   fChain->SetBranchAddress("pid_Beta_F5F7", &pid_Beta_F5F7, &b_pid_Beta_F5F7);
   fChain->SetBranchAddress("pid_AoQ_F3F5", &pid_AoQ_F3F5, &b_pid_AoQ_F3F5);
   fChain->SetBranchAddress("pid_Zet_F11", &pid_Zet_F11, &b_pid_Zet_F11);
   fChain->SetBranchAddress("bigrips_aoq", &bigrips_aoq, &b_bigrips_aoq);
   fChain->SetBranchAddress("bigrips_zet", &bigrips_zet, &b_bigrips_zet);
   fChain->SetBranchAddress("bigrips_beta", &bigrips_beta, &b_bigrips_beta);

   fChain->SetBranchAddress("zet", &zet, &b_zet);
   fChain->SetBranchAddress("aoq", &aoq, &b_aoq);
   fChain->SetBranchAddress("mass", &mass, &b_mass);
   fChain->SetBranchAddress("Zed", &Zed, &b_Zed);
   fChain->SetBranchAddress("Mass", &Mass, &b_Mass);

   fChain->SetBranchAddress("Qbeta_E", &Qbeta_E, &b_Qbeta_E);
   fChain->SetBranchAddress("Qbeta_T", &Qbeta_T, &b_Qbeta_T);
   fChain->SetBranchAddress("Qveto_E", &Qveto_E, &b_Qveto_E);
   fChain->SetBranchAddress("Qveto_T", &Qveto_T, &b_Qveto_T);
   fChain->SetBranchAddress("NaI_E", NaI_E, &b_NaI_E);
   fChain->SetBranchAddress("NaI_T", NaI_T, &b_NaI_T);
   fChain->SetBranchAddress("index", &index, &b_index);
   fChain->SetBranchAddress("run", &run, &b_run);
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

void decay_ggmatrix::GammaAddback(){
   int max_ch;

   GetRawAddback();
   int cl=0, cr[3]={0,0,0};
   ab_hit=0;
   for(cl = 0; cl<12; cl++){
      if(abclhitnum[cl]==2){
         //std::cout<<abT[cl][0]<<", "<<abT[cl][1]<<std::endl;
         if(CheckAddback2(cl,0,1)==1){
            //std::cout<<"come here"<<std::endl;
            cr[0]=0;
            cr[1]=1;
            max_ch = FindMaxE(cl,cr,2);
            ab_ch[ab_hit] = cl*7 + abcrhit[cl][max_ch];
            ab_DGFe[ab_hit] = abDGFe[cl][max_ch];
            ab_DGFt[ab_hit] = abDGFt[cl][max_ch];
            ab_TDCs[ab_hit] = abTDCs[cl][max_ch];
            ab_TDCl[ab_hit] = abTDCl[cl][max_ch];
            ab_E[ab_hit] = abE[cl][0] + abE[cl][1];
            ab_T[ab_hit] = abT[cl][max_ch];
            ab_hit++;
         }else{
            for(int i=0; i<abclhitnum[cl]; i++){
               ab_ch[ab_hit] = cl*7 + abcrhit[cl][i];
               ab_DGFe[ab_hit] = abDGFe[cl][i];
               ab_DGFt[ab_hit] = abDGFt[cl][i];
               ab_TDCs[ab_hit] = abTDCs[cl][i];
               ab_TDCl[ab_hit] = abTDCl[cl][i];
               ab_E[ab_hit] = abE[cl][i];
               ab_T[ab_hit] = abT[cl][i];
               ab_hit++;
            }
         }
      }else if(abclhitnum[cl]==3){
         if(CheckAddback3(cl,0,1,2)==1){
            cr[0]=0;
            cr[1]=1;
            cr[2]=2;
            max_ch = FindMaxE(cl,cr,3);
            ab_ch[ab_hit] = cl*7 + abcrhit[cl][max_ch];
            ab_DGFe[ab_hit] = abDGFe[cl][max_ch];
            ab_DGFt[ab_hit] = abDGFt[cl][max_ch];
            ab_TDCs[ab_hit] = abTDCs[cl][max_ch];
            ab_TDCl[ab_hit] = abTDCl[cl][max_ch];
            ab_E[ab_hit] = abE[cl][0] + abE[cl][1] + abE[cl][2];
            ab_T[ab_hit] = abT[cl][max_ch];
            ab_hit++;
         }else if(CheckAddback2(cl,0,1)==1){
            cr[0]=0;
            cr[1]=1;
            max_ch = FindMaxE(cl,cr,2);
            ab_ch[ab_hit] = cl*7 + abcrhit[cl][max_ch];
            ab_DGFe[ab_hit] = abDGFe[cl][max_ch];
            ab_DGFt[ab_hit] = abDGFt[cl][max_ch];
            ab_TDCs[ab_hit] = abTDCs[cl][max_ch];
            ab_TDCl[ab_hit] = abTDCl[cl][max_ch];
            ab_E[ab_hit] = abE[cl][0] + abE[cl][1];
            ab_T[ab_hit] = abT[cl][max_ch];
            ab_hit++;
            ab_ch[ab_hit] = cl*7 + abcrhit[cl][2];
            ab_DGFe[ab_hit] = abDGFe[cl][2];
            ab_DGFt[ab_hit] = abDGFt[cl][2];
            ab_TDCs[ab_hit] = abTDCs[cl][2];
            ab_TDCl[ab_hit] = abTDCl[cl][2];
            ab_E[ab_hit] = abE[cl][2];
            ab_T[ab_hit] = abT[cl][2];
            ab_hit++;
         }else if(CheckAddback2(cl,0,2)==1){
            cr[0]=0;
            cr[1]=2;
            max_ch = FindMaxE(cl,cr,2);
            ab_ch[ab_hit] = cl*7 + abcrhit[cl][max_ch];
            ab_DGFe[ab_hit] = abDGFe[cl][max_ch];
            ab_DGFt[ab_hit] = abDGFt[cl][max_ch];
            ab_TDCs[ab_hit] = abTDCs[cl][max_ch];
            ab_TDCl[ab_hit] = abTDCl[cl][max_ch];
            ab_E[ab_hit] = abE[cl][0] + abE[cl][2];
            ab_T[ab_hit] = abT[cl][max_ch];
            ab_hit++;
            ab_ch[ab_hit] = cl*7 + abcrhit[cl][1];
            ab_DGFe[ab_hit] = abDGFe[cl][1];
            ab_DGFt[ab_hit] = abDGFt[cl][1];
            ab_TDCs[ab_hit] = abTDCs[cl][1];
            ab_TDCl[ab_hit] = abTDCl[cl][1];
            ab_E[ab_hit] = abE[cl][1];
            ab_T[ab_hit] = abT[cl][1];
            ab_hit++;
         }else if(CheckAddback2(cl,1,2)==1){
            cr[0]=1;
            cr[1]=2;
            max_ch = FindMaxE(cl,cr,2);
            ab_ch[ab_hit] = cl*7 + abcrhit[cl][max_ch];
            ab_DGFe[ab_hit] = abDGFe[cl][max_ch];
            ab_DGFt[ab_hit] = abDGFt[cl][max_ch];
            ab_TDCs[ab_hit] = abTDCs[cl][max_ch];
            ab_TDCl[ab_hit] = abTDCl[cl][max_ch];
            ab_E[ab_hit] = abE[cl][1] + abE[cl][2];
            ab_T[ab_hit] = abT[cl][max_ch];
            ab_hit++;
            ab_ch[ab_hit] = cl*7 + abcrhit[cl][0];
            ab_DGFe[ab_hit] = abDGFe[cl][0];
            ab_DGFt[ab_hit] = abDGFt[cl][0];
            ab_TDCs[ab_hit] = abTDCs[cl][0];
            ab_TDCl[ab_hit] = abTDCl[cl][0];
            ab_E[ab_hit] = abE[cl][0];
            ab_T[ab_hit] = abT[cl][0];
            ab_hit++;
         }else{
            for(int i=0; i<abclhitnum[cl]; i++){
               ab_ch[ab_hit] = cl*7 + abcrhit[cl][i];
               ab_DGFe[ab_hit] = abDGFe[cl][i];
               ab_DGFt[ab_hit] = abDGFt[cl][i];
               ab_TDCs[ab_hit] = abTDCs[cl][i];
               ab_TDCl[ab_hit] = abTDCl[cl][i];
               ab_E[ab_hit] = abE[cl][i];
               ab_T[ab_hit] = abT[cl][i];
               ab_hit++;
            }
         }
      }else{
         for(int i=0; i<abclhitnum[cl]; i++){
            ab_ch[ab_hit] = cl*7 + abcrhit[cl][i];
            ab_DGFe[ab_hit] = abDGFe[cl][i];
            ab_DGFt[ab_hit] = abDGFt[cl][i];
            ab_TDCs[ab_hit] = abTDCs[cl][i];
            ab_TDCl[ab_hit] = abTDCl[cl][i];
            ab_E[ab_hit] = abE[cl][i];
            ab_T[ab_hit] = abT[cl][i];
            ab_hit++;
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

void decay_ggmatrix::GetRawAddback(){
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
   for(int i=0; i<gc_hit; i++){
      cl=gc_ch[i]/7;
      cr=gc_ch[i]%7;
      abcrhit[cl][abclhitnum[cl]]=cr;
      abDGFe[cl][abclhitnum[cl]]=gc_DGFe[i];
      abDGFt[cl][abclhitnum[cl]]=gc_DGFt[i];
      abTDCs[cl][abclhitnum[cl]]=gc_TDCs[i];
      abTDCl[cl][abclhitnum[cl]]=gc_TDCl[i];
      abE[cl][abclhitnum[cl]]=gc_E[i];
      abT[cl][abclhitnum[cl]]=gc_T[i];
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
