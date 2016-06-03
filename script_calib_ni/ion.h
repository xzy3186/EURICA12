//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun 27 12:09:58 2012 by ROOT version 5.30/01
// from TTree ion/ion
// found on file: root_dir/beta_ion_gamma_2043.root
//////////////////////////////////////////////////////////

#ifndef ion_h
#define ion_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "eurica.h"
#include "wasabi_treeinfo.h"
#include "eurica_wasabi.h"

class ion {
   public :
      TTree          *fChain;   //!pointer to the analyzed TTree or TChain
      Int_t           fCurrent; //!current Tree number in a TChain

      // Declaration of leaf types
      Long64_t        ts;
      Int_t           numdssd;
      Int_t           dstrx;
      Int_t           dstry;
      Int_t           z;
      Int_t           tx[NumDSSD];   //[numdssd]
      Int_t           ty[NumDSSD];   //[numdssd]
      Int_t           x[NumDSSD];   //[numdssd]
      Int_t           y[NumDSSD];   //[numdssd]
      Int_t           dssd_fireX[NumDSSD];   //[numdssd]
      Int_t           dssd_fireY[NumDSSD];   //[numdssd]
      Int_t           dssd_E_X[NumDSSD][60];
      Int_t           dssd_ch_X[NumDSSD][60];
      Int_t           dssd_id_X[NumDSSD][60];
      Int_t           dssd_T_X[NumDSSD][60][3];
      Int_t           dssd_E_Y[NumDSSD][40];
      Int_t           dssd_ch_Y[NumDSSD][40];
      Int_t           dssd_id_Y[NumDSSD][40];
      Int_t           dssd_T_Y[NumDSSD][40][3];

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

      Double_t        RIBeam_beta35;   //[RIBeam_]
      Double_t        RIBeam_beta57;   //[RIBeam_]
      Double_t        RIBeam_beta711;   //[RIBeam_]
      Double_t        RIBeam_aoq37;   //[RIBeam_]
      Double_t        RIBeam_zed;   //[RIBeam_]
      Int_t           RIBeam_Zed;   //[RIBeam_]
      Int_t           RIBeam_Mass;   //[RIBeam_]
      Int_t           RIBeam_flagall;   //[RIBeam_]
      Int_t           RIBeam_flagTSumX;   //[RIBeam_]
      Int_t           RIBeam_flagTOFt;   //[RIBeam_]
      Int_t           RIBeam_flagTOFq;   //[RIBeam_]
      Int_t           RIBeam_flagReaction;   //[RIBeam_]
      Int_t           RIBeam_flagdERelation;   //[RIBeam_]
      Int_t           RIBeam_flagAngle;   //[RIBeam_]

      Int_t           Qbeta_E;
      Int_t           Qbeta_T;
      Int_t           Qveto_E;
      Int_t           Qveto_T;

      Int_t           NaI_E[3];
      Int_t           NaI_T[3];

      /**** for recalculating addback *****/
      static const Int_t
         addback_hitpattern[7][7];
      Int_t           gcclhitnum[12];//hit number in each cluster
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
      TBranch        *b_ts;   //!
      TBranch        *b_numdssd;   //!
      TBranch        *b_dstrx;   //!
      TBranch        *b_dstry;   //!
      TBranch        *b_z;   //!
      TBranch        *b_tx;   //!
      TBranch        *b_ty;   //!
      TBranch        *b_x;   //!
      TBranch        *b_y;   //!
      TBranch        *b_dssd_fireX;   //!
      TBranch        *b_dssd_fireY;   //!
      TBranch        *b_dssd_E_X;
      TBranch        *b_dssd_ch_X;
      TBranch        *b_dssd_id_X;
      TBranch        *b_dssd_E_Y;
      TBranch        *b_dssd_ch_Y;
      TBranch        *b_dssd_id_Y;
      TBranch        *b_dssd_T_X;
      TBranch        *b_dssd_T_Y;

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

      TBranch        *b_RIBeam_beta35;   //!
      TBranch        *b_RIBeam_beta57;   //!
      TBranch        *b_RIBeam_beta711;   //!
      TBranch        *b_RIBeam_aoq37;   //!
      TBranch        *b_RIBeam_zed;   //!
      TBranch        *b_RIBeam_Zed;   //!
      TBranch        *b_RIBeam_Mass;   //!
      TBranch        *b_RIBeam_flagall;   //!
      TBranch        *b_RIBeam_flagTSumX;   //!
      TBranch        *b_RIBeam_flagTOFt;   //!
      TBranch        *b_RIBeam_flagTOFq;   //!
      TBranch        *b_RIBeam_flagReaction;   //!
      TBranch        *b_RIBeam_flagdERelation;   //!
      TBranch        *b_RIBeam_flagAngle;   //!

      TBranch        *b_NaI_E;
      TBranch        *b_NaI_T;

      TBranch        *b_Qbeta_E;
      TBranch        *b_Qbeta_T;
      TBranch        *b_Qveto_E;
      TBranch        *b_Qveto_T;

      ion();
      virtual void     GetTree(char *filename, TTree *tree=0);
      virtual Int_t    Cut(Long64_t entry);
      virtual Int_t    GetEntry(Long64_t entry);
      virtual Long64_t LoadTree(Long64_t entry);
      virtual void     Init(TTree *tree);
      virtual Bool_t   Notify();
      virtual void     Show(Long64_t entry = -1);
      virtual void     GetTsEntry(map <Long64_t,Long64_t> &mts);
      virtual void     TreeBranch(TTree *tree);
      virtual void     SyncSi(eurica_wasabi &DSSD);
      virtual void     SyncTS(eurica_wasabi &DSSD);
      virtual void     SyncQbeta(eurica_wasabi &DSSD);
      virtual void     SyncBigRIPS(eurica_wasabi &DSSD);
      virtual void     SyncPID(eurica_wasabi &DSSD);
      virtual void     SyncNaI(eurica_wasabi &DSSD);
      virtual void     SyncGamma(eurica_wasabi &gamma);
      virtual void     ResetGe();
      virtual void     IonGetPos_TDC(Int_t &z, Int_t *x, Int_t *y);
      virtual void     IonGetDepth(Int_t &z);
      virtual void     IonGetX(Int_t zz, Int_t &xx);
      virtual void     IonGetY(Int_t zz, Int_t &yy);
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
      /**** for specific isotope *****/
      virtual Int_t    IfInterest();
      virtual Int_t    IfMnFe();
      virtual Int_t    IfCo();
      virtual Int_t    IfNi();
      virtual Int_t    IfCu();
      virtual Int_t    IfZn();
      virtual Int_t    IfGa();
      virtual Int_t    IfGe();
      virtual Int_t    IfAg();
      virtual Int_t    IfPd();
      virtual Int_t    IfRh();
      virtual Int_t    IfRu();
      virtual Int_t    IfTc();
      virtual Int_t    IfMo();
      virtual Int_t    IfSn();
      virtual Int_t    IfIn();
      virtual Int_t    IfCd();
};

ion::ion(){
}

void ion::GetTree(char *filename, TTree *tree)
{
   // if parameter tree is not specified (or zero), connect the file
   // used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
      if (!f || !f->IsOpen()) {
         f = new TFile(filename);
      }
      f->GetObject("ion",tree);

   }
   Init(tree);
}

Int_t ion::GetEntry(Long64_t entry)
{
   // Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ion::LoadTree(Long64_t entry)
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

void ion::Init(TTree *tree)
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
   fChain->SetBranchAddress("dstrx", &dstrx, &b_dstrx);
   fChain->SetBranchAddress("dstry", &dstry, &b_dstry);
   fChain->SetBranchAddress("z", &z, &b_z);
   fChain->SetBranchAddress("tx", tx, &b_tx);
   fChain->SetBranchAddress("ty", ty, &b_ty);
   fChain->SetBranchAddress("x", x, &b_x);
   fChain->SetBranchAddress("y", y, &b_y);
   fChain->SetBranchAddress("dssd_fireX", dssd_fireX, &b_dssd_fireX);
   fChain->SetBranchAddress("dssd_fireY", dssd_fireY, &b_dssd_fireY);
   //fChain->SetBranchAddress("dssd_E_X", dssd_E_X, &b_dssd_E_X);
   //fChain->SetBranchAddress("dssd_ch_X", dssd_ch_X, &b_dssd_ch_X);
   //fChain->SetBranchAddress("dssd_id_X", dssd_id_X, &b_dssd_id_X);
   //fChain->SetBranchAddress("dssd_E_Y", dssd_E_Y, &b_dssd_E_Y);
   //fChain->SetBranchAddress("dssd_ch_Y", dssd_ch_Y, &b_dssd_ch_Y);
   //fChain->SetBranchAddress("dssd_id_Y", dssd_id_Y, &b_dssd_id_Y);
   //fChain->SetBranchAddress("dssd_T_X", dssd_T_X, &b_dssd_T_X);
   //fChain->SetBranchAddress("dssd_T_Y", dssd_T_Y, &b_dssd_T_Y);

   fChain->SetBranchAddress("ab_hit", &ab_hit, &b_ab_hit);
   fChain->SetBranchAddress("ab_ch", ab_ch, &b_ab_ch);
   fChain->SetBranchAddress("ab_DGFe", ab_DGFe, &b_ab_DGFe);
   fChain->SetBranchAddress("ab_DGFt", ab_DGFt, &b_ab_DGFt);
   fChain->SetBranchAddress("ab_TDCs", ab_TDCs, &b_ab_TDCs);
   fChain->SetBranchAddress("ab_TDCl", ab_TDCl, &b_ab_TDCl);
   fChain->SetBranchAddress("ab_E", ab_E, &b_ab_E);
   fChain->SetBranchAddress("ab_T", ab_T, &b_ab_T);

   fChain->SetBranchAddress("gc_hit", &gc_hit, &b_gc_hit);
   fChain->SetBranchAddress("gc_ch", gc_ch, &b_gc_ch);
   fChain->SetBranchAddress("gc_DGFe", gc_DGFe, &b_gc_DGFe);
   fChain->SetBranchAddress("gc_DGFt", gc_DGFt, &b_gc_DGFt);
   fChain->SetBranchAddress("gc_TDCs", gc_TDCs, &b_gc_TDCs);
   fChain->SetBranchAddress("gc_TDCl", gc_TDCl, &b_gc_TDCl);
   fChain->SetBranchAddress("gc_E", gc_E, &b_gc_E);
   fChain->SetBranchAddress("gc_T", gc_T, &b_gc_T);

   fChain->SetBranchAddress("RIBeam_beta35", &RIBeam_beta35, &b_RIBeam_beta35);
   fChain->SetBranchAddress("RIBeam_beta57", &RIBeam_beta57, &b_RIBeam_beta57);
   fChain->SetBranchAddress("RIBeam_beta711", &RIBeam_beta711, &b_RIBeam_beta711);
   fChain->SetBranchAddress("RIBeam_aoq37", &RIBeam_aoq37, &b_RIBeam_aoq37);
   fChain->SetBranchAddress("RIBeam_zed", &RIBeam_zed, &b_RIBeam_zed);
   fChain->SetBranchAddress("RIBeam_Zed", &RIBeam_Zed, &b_RIBeam_Zed);
   fChain->SetBranchAddress("RIBeam_Mass", &RIBeam_Mass, &b_RIBeam_Mass);
   fChain->SetBranchAddress("RIBeam_flagall", &RIBeam_flagall, &b_RIBeam_flagall);
   fChain->SetBranchAddress("RIBeam_flagTSumX", &RIBeam_flagTSumX, &b_RIBeam_flagTSumX);
   fChain->SetBranchAddress("RIBeam_flagTOFt", &RIBeam_flagTOFt, &b_RIBeam_flagTOFt);
   fChain->SetBranchAddress("RIBeam_flagTOFq", &RIBeam_flagTOFq, &b_RIBeam_flagTOFq);
   fChain->SetBranchAddress("RIBeam_flagReaction", &RIBeam_flagReaction, &b_RIBeam_flagReaction);
   fChain->SetBranchAddress("RIBeam_flagdERelation", &RIBeam_flagdERelation, &b_RIBeam_flagdERelation);
   fChain->SetBranchAddress("RIBeam_flagAngle", &RIBeam_flagAngle, &b_RIBeam_flagAngle);

   fChain->SetBranchAddress("Qbeta_E", &Qbeta_E, &b_Qbeta_E);
   fChain->SetBranchAddress("Qbeta_T", &Qbeta_T, &b_Qbeta_T);
   fChain->SetBranchAddress("Qveto_E", &Qveto_E, &b_Qveto_E);
   fChain->SetBranchAddress("Qveto_T", &Qveto_T, &b_Qveto_T);

   fChain->SetBranchAddress("NaI_E", NaI_E, &b_NaI_E);
   fChain->SetBranchAddress("NaI_T", NaI_T, &b_NaI_T);

   Notify();
}

Bool_t ion::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ion::Show(Long64_t entry)
{
   // Print contents of entry.
   // If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ion::Cut(Long64_t entry)
{
   // This function may be called from Loop.
   // returns  1 if entry is accepted.
   // returns -1 otherwise.
   return 1;
}

void ion::GetTsEntry(map<Long64_t,Long64_t> &mts){
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   for(Long64_t jentries=0; jentries<nentries; jentries++){
      Long64_t ientry = LoadTree(jentries);
      if(ientry<0){
         break;
      }
      nb = fChain->GetEntry(jentries);
      nbytes+=nb;
      mts.insert(pair<Long64_t,Long64_t> (ts,jentries));
      //cout<<ts<<", "<<jentries<<endl;
   }
}

void ion::TreeBranch(TTree *tree){
   numdssd = NumDSSD;
   dstrx = NumDSSD*NumStrX;
   dstry = NumDSSD*NumStrY;
   tree->Branch("ts",&ts,"ts/L");
   tree->Branch("numdssd",&numdssd,"numdssd/I");
   tree->Branch("dstrx",&dstrx,"dstrx/I");
   tree->Branch("dstry",&dstry,"dstry/I");

   tree->Branch("z", &z, "z/I");
   tree->Branch("x", x, "x[numdssd]/I");
   tree->Branch("y", y, "y[numdssd]/I");
   tree->Branch("tx", tx, "tx[numdssd]/I");
   tree->Branch("ty", ty, "ty[numdssd]/I");
   tree->Branch("dssd_fireX", dssd_fireX, "dssd_fireX[numdssd]/I");
   tree->Branch("dssd_fireY", dssd_fireY, "dssd_fireY[numdssd]/I");
   tree->Branch("dssd_E_X",dssd_E_X,"dssd_E_X[numdssd][60]/I");
   tree->Branch("dssd_ch_X",dssd_ch_X,"dssd_ch_X[numdssd][60]/I");
   tree->Branch("dssd_id_X",dssd_id_X,"dssd_id_X[numdssd][60]/I");
   tree->Branch("dssd_E_Y",dssd_E_Y,"dssd_E_Y[numdssd][40]/I");
   tree->Branch("dssd_ch_Y",dssd_ch_Y,"dssd_ch_Y[numdssd][40]/I");
   tree->Branch("dssd_id_Y",dssd_id_Y,"dssd_id_Y[numdssd][40]/I");
   tree->Branch("dssd_T_X",dssd_T_X,"dssd_T_X[numdssd][60][3]/I");
   tree->Branch("dssd_T_Y",dssd_T_Y,"dssd_T_Y[numdssd][40][3]/I");

   /****** without addback ******/
   tree->Branch("gc_hit",&gc_hit,"gc_hit/I");
   tree->Branch("gc_ch",gc_ch,"gc_ch[gc_hit]/I");
   tree->Branch("gc_DGFe",gc_DGFe,"gc_DGFe[gc_hit]/I");
   tree->Branch("gc_DGFt",gc_DGFt,"gc_DGFt[gc_hit]/I");
   tree->Branch("gc_TDCs",gc_TDCs,"gc_TDCs[gc_hit]/I");
   tree->Branch("gc_TDCl",gc_TDCl,"gc_TDCl[gc_hit]/I");
   tree->Branch("gc_E",gc_E,"gc_E[gc_hit]/D");
   tree->Branch("gc_T",gc_T,"gc_T[gc_hit]/D");

   /****** with addback ******/
   tree->Branch("ab_hit",&ab_hit,"ab_hit/I");
   tree->Branch("ab_ch",ab_ch,"ab_ch[ab_hit]/I");
   tree->Branch("ab_DGFe",ab_DGFe,"ab_DGFe[ab_hit]/I");
   tree->Branch("ab_DGFt",ab_DGFt,"ab_DGFt[ab_hit]/I");
   tree->Branch("ab_TDCs",ab_TDCs,"ab_TDCs[ab_hit]/I");
   tree->Branch("ab_TDCl",ab_TDCl,"ab_TDCl[ab_hit]/I");
   tree->Branch("ab_E",ab_E,"ab_E[ab_hit]/D");
   tree->Branch("ab_T",ab_T,"ab_T[ab_hit]/D");

   tree->Branch("RIBeam_beta35",&RIBeam_beta35,"RIBeam_beta35/D");
   tree->Branch("RIBeam_beta57",&RIBeam_beta57,"RIBeam_beta57/D");
   tree->Branch("RIBeam_beta711",&RIBeam_beta711,"RIBeam_beta711/D");
   tree->Branch("RIBeam_aoq37",&RIBeam_aoq37,"RIBeam_aoq37/D");
   tree->Branch("RIBeam_zed",&RIBeam_zed,"RIBeam_zed/D");
   tree->Branch("RIBeam_Zed",&RIBeam_Zed,"RIBeam_Zed/I");
   tree->Branch("RIBeam_Mass",&RIBeam_Mass,"RIBeam_Mass/I");
   tree->Branch("RIBeam_flagall",&RIBeam_flagall,"RIBeam_flagall/I");
   tree->Branch("RIBeam_flagTSumX",&RIBeam_flagTSumX,"RIBeam_flagTSumX/I");
   tree->Branch("RIBeam_flagTOFt",&RIBeam_flagTOFt,"RIBeam_flagTOFt/I");
   tree->Branch("RIBeam_flagTOFq",&RIBeam_flagTOFq,"RIBeam_flagTOFq/I");
   tree->Branch("RIBeam_flagReaction",&RIBeam_flagReaction,"RIBeam_flagReaction/I");
   tree->Branch("RIBeam_flagdERelation",&RIBeam_flagdERelation,"RIBeam_flagdERelation/I");
   tree->Branch("RIBeam_flagAngle",&RIBeam_flagAngle,"RIBeam_flagAngle/I");

   tree->Branch("Qbeta_E",&Qbeta_E,"Qbeta_E/I");
   tree->Branch("Qbeta_T",&Qbeta_T,"Qbeta_T/I");
   tree->Branch("Qveto_E",&Qveto_E,"Qveto_E/I");
   tree->Branch("Qveto_T",&Qveto_T,"Qveto_T/I");

   tree->Branch("NaI_E",NaI_E,"NaI_E[3]/I");
   tree->Branch("NaI_T",NaI_T,"NaI_T[3]/I");
}

void ion::SyncSi(eurica_wasabi &DSSD){
   memcpy(dssd_E_X, DSSD.dssd_E_X, sizeof(DSSD.dssd_E_X));
   memcpy(dssd_ch_X, DSSD.dssd_ch_X, sizeof(DSSD.dssd_ch_X));
   memcpy(dssd_id_X, DSSD.dssd_id_X, sizeof(DSSD.dssd_id_X));
   memcpy(dssd_E_Y, DSSD.dssd_E_Y, sizeof(DSSD.dssd_E_Y));
   memcpy(dssd_ch_Y, DSSD.dssd_ch_Y, sizeof(DSSD.dssd_ch_Y));
   memcpy(dssd_id_Y, DSSD.dssd_id_Y, sizeof(DSSD.dssd_id_Y));
   memcpy(dssd_T_X, DSSD.dssd_T_X, sizeof(DSSD.dssd_T_X));
   memcpy(dssd_T_Y, DSSD.dssd_T_Y, sizeof(DSSD.dssd_T_Y));
   memcpy(dssd_fireX, DSSD.dssd_fireX, sizeof(DSSD.dssd_fireX));
   memcpy(dssd_fireY, DSSD.dssd_fireY, sizeof(DSSD.dssd_fireY));
   memcpy(x, DSSD.dssd_X, sizeof(DSSD.dssd_X));
   memcpy(y, DSSD.dssd_Y, sizeof(DSSD.dssd_Y));
   z = DSSD.dssd_Z;
   int z_temp = z;
   //if(z==7){
   //   cout<<DSSD.ts<<endl;
   //}
   IonGetPos_TDC(z,x,y);
   //if(z_temp != z){
   //   cout<<"Q_beta = "<<Qbeta_E<<", z1 = "<<z_temp<<", z = "<<z<<endl;
   //}
   for(int i=0; i<NumDSSD; i++){
      tx[i]=0;
      ty[i]=0;
   }
   for(int i=0; i<=z; i++){
      tx[i]=dssd_T_X[i][x[i]][0];
      ty[i]=dssd_T_Y[i][y[i]][0];
   }
}

void ion::IonGetPos_TDC(Int_t &zz, Int_t *xx, Int_t *yy)
{
   /**********initialize*************/
   zz=-1;
   Int_t strip_x=-1, strip_y=-1;
   for(int i=0; i<NumDSSD; i++){
      xx[i]=-1;
      yy[i]=-1;
   }
   /**********************************/
   IonGetDepth(zz);
   for(int k=0; k<=zz; k++){
      if(k>=NumDSSD){
         continue;
      }
      if(dssd_fireX[k]==1){
         IonGetX(k,strip_x);
      }else{
         strip_x=xx[0];
      }
      if(dssd_fireY[k]==1){
         IonGetY(k,strip_y);
      }else{
         strip_y=yy[0];
      }
      xx[k]=strip_x;
      yy[k]=strip_y;
   }
}

void ion::IonGetDepth(Int_t &zz){
   Int_t *fire_DSSD = new Int_t [NumDSSD+2];
   Int_t *HI_firedX = new Int_t [NumDSSD+1];
   Int_t *HI_firedY = new Int_t [NumDSSD+1];

   int flag;
   if(DSSD1HGAIN == 1){
      flag = 9;
   }else{
      flag = 0;
   }

   /**********initialize*************/
   for(int i=0; i<NumDSSD; i++){
      fire_DSSD[i]=0;
      HI_firedX[i]=0;
      HI_firedY[i]=0;
   }
   /*********************************/
   for(int k=0; k<NumDSSD; k++){
      if(k!=flag){
         if(k<5){
            for(int i=0; i<NumStrX; i++){
               if(dssd_T_X[k][i][0]>-500 && dssd_T_X[k][i][0]<700){
                  HI_firedX[k]=1;
                  break;
               }
            }
         }else{
            for(int i=2; i<NumStrX; i=i+2){
               if(dssd_T_X[k][i-2][0]>-500 && dssd_T_X[k][i-2][0]<700 && dssd_T_X[k][i][0]>-500 && dssd_T_X[k][i][0]<700){
                  HI_firedX[k]=1;
                  break;
               }
            }
         }
      }else{
         for(int i=0; i<NumStrX; i++){
            if(dssd_T_X[k][i][0]>-50000 && dssd_E_X[k][i]>100){
               HI_firedX[k]=1;
               break;
            }
         }
      }
   }
   for(int k=0; k<NumDSSD; k++){
      if(k!=flag){
         if(k<5){
            for(int i=0; i<NumStrY; i++){
               if(dssd_T_Y[k][i][0]>-500 && dssd_T_Y[k][i][0]<1000){
                  HI_firedY[k]=1;
                  break;
               }
            }
         }else{
            for(int i=1; i<NumStrY; i++){
               if(dssd_T_Y[k][i-1][0]>-500 && dssd_T_Y[k][i-1][0]<1000 && dssd_T_Y[k][i][0]>-500 && dssd_T_Y[k][i][0]<1000){
                  HI_firedY[k]=1;
                  break;
               }
            }
         }
      }else{
         for(int i=0; i<NumStrY; i++){
            if(dssd_T_Y[k][i][0]>-50000 && dssd_E_Y[k][i]>100){
               HI_firedY[k]=1;
               break;
            }
         }
      }
   }
   /***** special case for dead channel ****/
   if(HI_firedY[2]==1&&HI_firedY[3]==0){
      if((dssd_T_Y[3][15][0]>200&&dssd_T_Y[3][15][0]<700)||(dssd_T_Y[3][17][0]>200&&dssd_T_Y[3][17][0]<700)){
         HI_firedY[3]=1;
      }
   }
   if(HI_firedX[2]==1&&HI_firedX[3]==0){
      if((dssd_T_X[3][12][0]>200&&dssd_T_X[3][12][0]<700)||(dssd_T_X[3][14][0]>200&&dssd_T_X[3][14][0]<700)){
         HI_firedX[3]=1;
      }
   }
   /****************************************/
   for(int i=0; i<NumDSSD; i++){
      if(i<5){
         if(HI_firedX[i]==1 && HI_firedY[i]==1){
            fire_DSSD[i]=1;
         }
      }else{
         if(HI_firedX[i]==1 || HI_firedY[i]==1){
            fire_DSSD[i]=1;
         }
      }
   }
   if(Qbeta_E>200&&Qbeta_T>-50000){
      fire_DSSD[NumDSSD]=1;
   }else{
      fire_DSSD[NumDSSD]=0;
   }
   fire_DSSD[NumDSSD+1]=0;
   if(fire_DSSD[0]==1){
      //if(fire_DSSD[NumDSSD]==1){
      //   zz=8;
      //}else{
      for(int i=0; i<=NumDSSD; i++){
         if(fire_DSSD[i]==1 && fire_DSSD[i+1]==0){
            zz=i;
            break;
         }
      }
      //}
   }else{
      zz=-1;
   }
   for(int i=0; i<NumDSSD; i++){
      dssd_fireX[i] = HI_firedX[i];
      dssd_fireY[i] = HI_firedY[i];
      //cout<<fire_DSSD[i]<<", ";
   }
   //cout<<endl;
}

void ion::IonGetX(Int_t zz, Int_t &xx){
   int flag;
   if(DSSD1HGAIN == 1){
      flag = 9;
   }else{
      flag = 0;
   }

   Int_t max_temp;
   if(zz==flag){
      max_temp = 0;
      for(int i=0; i<NumStrX; i++){
         if(dssd_T_X[zz][i][0]>-50000 && dssd_E_X[zz][i]>max_temp){
            xx=i;
            max_temp = dssd_E_X[zz][i];
         }
      }
   }else{
      max_temp = 1500;
      for(int i=0; i<NumStrX; i++){
         if(dssd_T_X[zz][i][0]>-500 && dssd_T_X[zz][i][0]<700 && dssd_T_X[zz][i][0]<max_temp){
            xx=i;
            max_temp = dssd_T_X[zz][i][0];
         }
      }
   }
   /**** special case for dead channel ****/
   if(zz==3){
      if(x[2]==13){
         xx=13;
      }
   }
   /***************************************/
}

void ion::IonGetY(Int_t zz, Int_t &yy){
   int flag;
   if(DSSD1HGAIN == 1){
      flag = 9;
   }else{
      flag = 0;
   }

   Int_t max_temp;
   if(zz==flag){
      max_temp = 0;
      for(int i=0; i<NumStrY; i++){
         if(dssd_T_Y[zz][i][0]>-50000 && dssd_E_Y[zz][i]>max_temp){
            yy=i;
            max_temp = dssd_E_Y[zz][i];
         }
      }
   }else{
      max_temp = 1500;
      for(int i=0; i<NumStrY; i++){
         if(dssd_T_Y[zz][i][0]>-500 && dssd_T_Y[zz][i][0]<1000 && dssd_T_Y[zz][i][0]<max_temp){
            yy=i;
            max_temp = dssd_T_Y[zz][i][0];
         }
      }
   }
   /**** special case for dead channel ****/
   if(zz==3){
      if(y[2]==16){
         yy=16;
      }
   }
   /***************************************/
}

void ion::SyncTS(eurica_wasabi &DSSD){
   ts = DSSD.ts;
}

void ion::SyncQbeta(eurica_wasabi &DSSD){
   Qbeta_E = DSSD.Qbeta_E;
   Qbeta_T = DSSD.Qbeta_T;
   Qveto_E = DSSD.Qveto_E;
   Qveto_T = DSSD.Qveto_T;
}

void ion::SyncBigRIPS(eurica_wasabi &DSSD){
}

void ion::SyncPID(eurica_wasabi &DSSD){
}

void ion::SyncNaI(eurica_wasabi &DSSD){
   memcpy(NaI_E, DSSD.NaI_E, sizeof(DSSD.NaI_E));
   memcpy(NaI_T, DSSD.NaI_T, sizeof(DSSD.NaI_T));
}

void ion::SyncGamma(eurica_wasabi &gamma){
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

void ion::ResetGe(){
   gc_hit=0;
   ab_hit=0;
}

/***** for addback ****/
const Double_t ion::time_thr=105;
const Double_t ion::energy_thr=150;

void ion::GammaAddback(){
   int max_ch;

   GetRawAddback();
   int cl=0, cr[3]={0,0,0};
   ab_hit=0;
   for(cl = 0; cl<12; cl++){
      if(gcclhitnum[cl]==2){
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
            abclhitnum[cl]++;
         }else{
            for(int i=0; i<gcclhitnum[cl]; i++){
               ab_ch[ab_hit] = cl*7 + abcrhit[cl][i];
               ab_DGFe[ab_hit] = abDGFe[cl][i];
               ab_DGFt[ab_hit] = abDGFt[cl][i];
               ab_TDCs[ab_hit] = abTDCs[cl][i];
               ab_TDCl[ab_hit] = abTDCl[cl][i];
               ab_E[ab_hit] = abE[cl][i];
               ab_T[ab_hit] = abT[cl][i];
               ab_hit++;
               abclhitnum[cl]++;
            }
         }
      }else if(gcclhitnum[cl]==3){
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
            abclhitnum[cl]++;
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
            abclhitnum[cl]++;
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
            abclhitnum[cl]++;
            ab_ch[ab_hit] = cl*7 + abcrhit[cl][1];
            ab_DGFe[ab_hit] = abDGFe[cl][1];
            ab_DGFt[ab_hit] = abDGFt[cl][1];
            ab_TDCs[ab_hit] = abTDCs[cl][1];
            ab_TDCl[ab_hit] = abTDCl[cl][1];
            ab_E[ab_hit] = abE[cl][1];
            ab_T[ab_hit] = abT[cl][1];
            ab_hit++;
            abclhitnum[cl]++;
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
            abclhitnum[cl]++;
            ab_ch[ab_hit] = cl*7 + abcrhit[cl][0];
            ab_DGFe[ab_hit] = abDGFe[cl][0];
            ab_DGFt[ab_hit] = abDGFt[cl][0];
            ab_TDCs[ab_hit] = abTDCs[cl][0];
            ab_TDCl[ab_hit] = abTDCl[cl][0];
            ab_E[ab_hit] = abE[cl][0];
            ab_T[ab_hit] = abT[cl][0];
            ab_hit++;
            abclhitnum[cl]++;
         }else{
            for(int i=0; i<gcclhitnum[cl]; i++){
               ab_ch[ab_hit] = cl*7 + abcrhit[cl][i];
               ab_DGFe[ab_hit] = abDGFe[cl][i];
               ab_DGFt[ab_hit] = abDGFt[cl][i];
               ab_TDCs[ab_hit] = abTDCs[cl][i];
               ab_TDCl[ab_hit] = abTDCl[cl][i];
               ab_E[ab_hit] = abE[cl][i];
               ab_T[ab_hit] = abT[cl][i];
               ab_hit++;
               abclhitnum[cl]++;
            }
         }
      }else{
         for(int i=0; i<gcclhitnum[cl]; i++){
            ab_ch[ab_hit] = cl*7 + abcrhit[cl][i];
            ab_DGFe[ab_hit] = abDGFe[cl][i];
            ab_DGFt[ab_hit] = abDGFt[cl][i];
            ab_TDCs[ab_hit] = abTDCs[cl][i];
            ab_TDCl[ab_hit] = abTDCl[cl][i];
            ab_E[ab_hit] = abE[cl][i];
            ab_T[ab_hit] = abT[cl][i];
            ab_hit++;
            abclhitnum[cl]++;
         }
      }
   }
}

Int_t ion::CheckAddback2(int cl, int cr1, int cr2){
   int result = CheckAbPosition(cl,cr1,cr2)*CheckAbEnergy(cl,cr1,cr2)*CheckAbTime(cl,cr1,cr2);
   if(result == 1){
      return 1;
   }else{
      return 0;
   }
}

Int_t ion::CheckAddback3(int cl, int cr1, int cr2, int cr3){
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

void ion::GetRawAddback(){
   int cl, cr;
   for(int i=0; i<12; i++){
      gcclhitnum[i]=0;
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
      abcrhit[cl][gcclhitnum[cl]]=cr;
      abDGFe[cl][gcclhitnum[cl]]=gc_DGFe[i];
      abDGFt[cl][gcclhitnum[cl]]=gc_DGFt[i];
      abTDCs[cl][gcclhitnum[cl]]=gc_TDCs[i];
      abTDCl[cl][gcclhitnum[cl]]=gc_TDCl[i];
      abE[cl][gcclhitnum[cl]]=gc_E[i];
      abT[cl][gcclhitnum[cl]]=gc_T[i];
      gcclhitnum[cl]++;
   }
}

Int_t ion::CheckAbPosition(int cl, int cr1, int cr2){
   if(addback_hitpattern[abcrhit[cl][cr1]][abcrhit[cl][cr2]]==1){
      return 1;
   }else{
      return 0;
   }
}

Int_t ion::CheckAbEnergy(int cl, int cr1, int cr2){
   if(abE[cl][cr1]+abE[cl][cr2]>energy_thr){
      return 1;
   }else{
      return 0;
   }
}

Int_t ion::CheckAbTime(int cl, int cr1, int cr2){
   Double_t time_diff = fabs(abT[cl][cr1]-abT[cl][cr2]);
   //std::cout<<"diff = "<<time_diff<<", thr = "<<time_thr<<std::endl;
   if(time_diff < time_thr){
      //std::cout<<"come here"<<std::endl;
      return 1;
   }else{
      return 0;
   }
}

Int_t ion::FindMaxE(int cl, int *cr, int dim){
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

const int ion::addback_hitpattern[7][7] = {
   {0,1,0,0,0,1,1},
   {1,0,1,0,0,0,1},
   {0,1,0,1,0,0,1},
   {0,0,1,0,1,0,1},
   {0,0,0,1,0,1,1},
   {1,0,0,0,1,0,1},
   {1,1,1,1,1,1,1},
};

Double_t ion::rand05()
{
   return rand()*1./RAND_MAX - 0.5;
}

Int_t ion::IfMnFe(){
   if(RIBeam_Zed<=26){
      return 1;
   }
   return 0;
}
Int_t ion::IfCo(){
   if(RIBeam_Zed==27){
      //if(RIBeam_Mass>73){
         return 1;
      //}
   }
   return 0;
}
Int_t ion::IfNi(){
   if(RIBeam_Zed==28){
      if(RIBeam_Mass>=77){
      //if(RIBeam_Mass==74){
         return 1;
      }
   }
   return 0;
}
Int_t ion::IfCu(){
   if(RIBeam_Zed==29){
      if(RIBeam_Mass>=80){
         return 1;
      }
   }
   return 0;
}
Int_t ion::IfZn(){
   if(RIBeam_Zed==30){
      if(RIBeam_Mass>=83){
         return 1;
      }
   }
   return 0;
}
Int_t ion::IfGa(){
   if(RIBeam_Zed==31){
      if(RIBeam_Mass>=85){
      //if(RIBeam_Mass==83){
         return 1;
      }
   }
   return 0;
}
Int_t ion::IfGe(){
   if(RIBeam_Zed==32){
      if(RIBeam_Mass>=87){
         return 1;
      }
   }
   return 0;
}
Int_t ion::IfAg(){
   if(RIBeam_Zed==47){
      if(RIBeam_Mass>127){
         return 1;
      }
   }
   return 0;
}
Int_t ion::IfPd(){
   if(RIBeam_Zed==46){
      if(RIBeam_Mass>123){
         return 1;
      }
   }
   return 0;
}
Int_t ion::IfRh(){
   if(RIBeam_Zed==45){
      if(RIBeam_Mass>120){
         return 1;
      }
   }
   return 0;
}
Int_t ion::IfRu(){
   if(RIBeam_Zed==44){
      if(RIBeam_Mass>117){
         return 1;
      }
   }
   return 0;
}
Int_t ion::IfTc(){
   if(RIBeam_Zed==43){
      if(RIBeam_Mass>117){
         return 1;
      }
   }
   return 0;
}
Int_t ion::IfMo(){
   if(RIBeam_Zed==42){
      if(RIBeam_Mass>114){
         return 1;
      }
   }
   return 0;
}
Int_t ion::IfSn(){
   if(RIBeam_Zed==50){
      if(RIBeam_Mass>135){
         return 1;
      }
   }
   return 0;
}
Int_t ion::IfIn(){
   if(RIBeam_Zed==49){
      if(RIBeam_Mass>132){
         return 1;
      }
   }
   return 0;
}
Int_t ion::IfCd(){
   if(RIBeam_Zed==48){
      if(RIBeam_Mass>130){
         return 1;
      }
   }
   return 0;
}

Int_t ion::IfInterest(){
   if(IfCo() || IfNi() || IfCu() || IfZn() || IfGa() || IfGe() || IfMnFe()){
   //if(IfGa()){
      return 1;
   }
   return 0;
}
#endif // #ifdef ion_cxx
