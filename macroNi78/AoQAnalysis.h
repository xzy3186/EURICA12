//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb  6 16:06:36 2013 by ROOT version 5.34/01
// from TTree tree/tree
// found on file: treework/AoQAnalysis/temp1050.root
//////////////////////////////////////////////////////////

#ifndef AoQAnalysis_h
#define AoQAnalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>

#include <iostream>
using namespace std;
// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class AoQAnalysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   mutable Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           EventInfo_;
   Int_t           BigRIPSRIPS_;
   Int_t           BigRIPSPlastic_;
   Int_t           RIBeamOthers_;
   Int_t           RIBeam_;
   Int_t           runnumber[1];
   Double_t        BrhoCenter[2];
   Double_t        F3X[1];
   Double_t        F3A[1];
   Double_t        F3Y[1];
   Double_t        F3B[1];
   Double_t        F5X[1];
   Double_t        F5A[1];
   Double_t        F5Y[1];
   Double_t        F5B[1];
   Double_t        F7X[1];
   Double_t        F7A[1];
   Double_t        F7Y[1];
   Double_t        F7B[1];
   Double_t        fTime[7];
   Int_t           fQLRaw[7];
   Int_t           fQRRaw[7];
   Int_t           Zed[1];
   Int_t           Mass[1];

   // List of branches
   TBranch        *b_EventInfo_;   //!
   TBranch        *b_BigRIPSRIPS_;   //!
   TBranch        *b_BigRIPSPlastic_;   //!
   TBranch        *b_RIBeamOthers_;   //!
   TBranch        *b_RIBeam_;   //!
   TBranch        *b_runnumber;   //!
   TBranch        *b_BrhoCenter;   //!
   TBranch        *b_F3X;   //!
   TBranch        *b_F3A;   //!
   TBranch        *b_F3Y;   //!
   TBranch        *b_F3B;   //!
   TBranch        *b_F5X;   //!
   TBranch        *b_F5A;   //!
   TBranch        *b_F5Y;   //!
   TBranch        *b_F5B;   //!
   TBranch        *b_F7X;   //!
   TBranch        *b_F7A;   //!
   TBranch        *b_F7Y;   //!
   TBranch        *b_F7B;   //!
   TBranch        *b_fTime;   //!
   TBranch        *b_fQLRaw;   //!
   TBranch        *b_fQRRaw;   //!
   TBranch        *b_Zed;   //!
   TBranch        *b_Mass;   //!

   AoQAnalysis();
   AoQAnalysis(TTree *tree);
   AoQAnalysis(TTree *tree, const char* fout);
   virtual ~AoQAnalysis();
   //   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    Cut() const;
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry) const;
   virtual void     Init(TTree *tree);
   virtual double Loop();
   virtual Bool_t   Notify() const;
   virtual void     Show(Long64_t entry = -1);

   double Loop(const vector<double> & par) const; // for minuit2
   void SetTree(TTree *tree);

   void SetTOFOffset(double tofoffset_) const {tofoffset = tofoffset_;}
   void SetSlew(double sl1, double sl2, double sl3, double sl4) const
   {slew[0] = sl1; slew[1] = sl2; slew[2] = sl3; slew[3] = sl4;}
   void SetFirstME(int i, double xx_, double xa_,  double xd_) const {
     xx[i] = xx_;
     xa[i] = xa_;
     xd[i] = xd_;
   }
   void SetSecondME(int i, double xxx_,double xxa_,double xxd_,double xaa_,double xad_,double xdd_) const {
     xxx[i] = xxx_;
     xxa[i] = xxa_;
     xxd[i] = xxd_;
     xaa[i] = xaa_;
     xad[i] = xad_;
     xdd[i] = xdd_;
   }
   void SetThirdME(int i, double xxxx_,double xxxa_,double xxaa_,double xaaa_) const {
     xxxx[i] = xxxx_;
     xxxa[i] = xxxa_;
     xxaa[i] = xxaa_;
     xaaa[i] = xaaa_;
   }
   void SetFourthME(int i, double xaaaa_) const {
     xaaaa[i] = xaaaa_;
   }

 private:
   const char* fileout;
   //parameters for A/Q analysis 
   mutable double tofoffset;
   mutable double slew[4];
   mutable double xx[2], xa[2], xd[2];
   mutable double xxx[2], xxa[2], xxd[2], xaa[2], xad[2], xdd[2];
   mutable double xxxx[2],xxxa[2],xxaa[2],xaaa[2];
   mutable double xaaaa[2];

   mutable double delta[2];
   mutable double beta[2];
   mutable double tof37;
   mutable double tof37_calculated; // calculated from delta[0], delta[1], Zed, Mass

   double length[2];

   double u; //unified atomic mass unit
   double clight;

   void initialize();
   void initTreeOutput(TTree* tree);
   void loadParameters();
   void CorrectedTOF() const;
   void deltaCalc() const;
   void betaCalc() const;
   void tof37Calc() const;
   
   mutable double FCN; // for minuit fit
};

#endif

#ifdef AoQAnalysis_cxx
AoQAnalysis::AoQAnalysis() : fChain(0) 
{
   initialize();
   loadParameters();
   fileout="";
}

AoQAnalysis::AoQAnalysis(TTree *tree) : fChain(0) 
{
   Init(tree);
   initialize();
   loadParameters();
   fileout="";
}

AoQAnalysis::AoQAnalysis(TTree *tree, const char* fout) : fChain(0) 
{
   Init(tree);
   initialize();
   loadParameters();
   fileout=fout;
}

AoQAnalysis::~AoQAnalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AoQAnalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AoQAnalysis::LoadTree(Long64_t entry) const
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

void AoQAnalysis::Init(TTree *tree)
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
   fChain->SetBranchStatus("*",0);
   fChain->SetBranchStatus("EventInfo.runnumber",1);
   fChain->SetBranchStatus("BigRIPSRIPS.center_brho",1);
   fChain->SetBranchStatus("RIBeamOthers.F3X",1);
   fChain->SetBranchStatus("RIBeamOthers.F3A",1);
   fChain->SetBranchStatus("RIBeamOthers.F3Y",1);
   fChain->SetBranchStatus("RIBeamOthers.F3B",1);
   fChain->SetBranchStatus("RIBeamOthers.F5X",1);
   fChain->SetBranchStatus("RIBeamOthers.F5A",1);
   fChain->SetBranchStatus("RIBeamOthers.F5Y",1);
   fChain->SetBranchStatus("RIBeamOthers.F5B",1);
   fChain->SetBranchStatus("RIBeamOthers.F7X",1);
   fChain->SetBranchStatus("RIBeamOthers.F7A",1);
   fChain->SetBranchStatus("RIBeamOthers.F7Y",1);
   fChain->SetBranchStatus("RIBeamOthers.F7B",1);
   fChain->SetBranchStatus("BigRIPSPlastic.fTime",1);
   fChain->SetBranchStatus("BigRIPSPlastic.fQLRaw",1);
   fChain->SetBranchStatus("BigRIPSPlastic.fQRRaw",1);
   fChain->SetBranchStatus("RIBeam.Zed",1);
   fChain->SetBranchStatus("RIBeam.Mass",1);

   fChain->SetBranchAddress("EventInfo", &EventInfo_, &b_EventInfo_);
   fChain->SetBranchAddress("EventInfo.runnumber", &runnumber, &b_runnumber);
   fChain->SetBranchAddress("BigRIPSRIPS", &BigRIPSRIPS_, &b_BigRIPSRIPS_);
   fChain->SetBranchAddress("BigRIPSRIPS.center_brho", &BrhoCenter, &b_BrhoCenter);
   fChain->SetBranchAddress("RIBeamOthers", &RIBeamOthers_, &b_RIBeamOthers_);
   fChain->SetBranchAddress("RIBeamOthers.F3X", &F3X, &b_F3X);
   fChain->SetBranchAddress("RIBeamOthers.F3A", &F3A, &b_F3A);
   fChain->SetBranchAddress("RIBeamOthers.F3Y", &F3Y, &b_F3Y);
   fChain->SetBranchAddress("RIBeamOthers.F3B", &F3B, &b_F3B);
   fChain->SetBranchAddress("RIBeamOthers.F5X", &F5X, &b_F5X);
   fChain->SetBranchAddress("RIBeamOthers.F5A", &F5A, &b_F5A);
   fChain->SetBranchAddress("RIBeamOthers.F5Y", &F5Y, &b_F5Y);
   fChain->SetBranchAddress("RIBeamOthers.F5B", &F5B, &b_F5B);
   fChain->SetBranchAddress("RIBeamOthers.F7X", &F7X, &b_F7X);
   fChain->SetBranchAddress("RIBeamOthers.F7A", &F7A, &b_F7A);
   fChain->SetBranchAddress("RIBeamOthers.F7Y", &F7Y, &b_F7Y);
   fChain->SetBranchAddress("RIBeamOthers.F7B", &F7B, &b_F7B);
   fChain->SetBranchAddress("BigRIPSPlastic", &BigRIPSPlastic_, &b_BigRIPSPlastic_);
   fChain->SetBranchAddress("BigRIPSPlastic.fTime", &fTime, &b_fTime);
   fChain->SetBranchAddress("BigRIPSPlastic.fQLRaw", &fQLRaw, &b_fQLRaw);
   fChain->SetBranchAddress("BigRIPSPlastic.fQRRaw", &fQRRaw, &b_fQRRaw);
   fChain->SetBranchAddress("RIBeam", &RIBeam_, &b_RIBeam_);
   fChain->SetBranchAddress("RIBeam.Zed", &Zed, &b_Zed);
   fChain->SetBranchAddress("RIBeam.Mass", &Mass, &b_Mass);
   Notify();
}

Bool_t AoQAnalysis::Notify() const
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AoQAnalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
//Int_t AoQAnalysis::Cut(Long64_t entry)
Int_t AoQAnalysis::Cut() const 
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
  //if(Zed[0]>26 && Zed[0]<31 && F5A[0] >-200&&F5A[0]<200&&F5X[0]>-200&&F5X[0]<200) {
  if(Zed[0]>0) {
    return 1;
  } else {
    return -1;
  }
}
#endif // #ifdef AoQAnalysis_cxx
