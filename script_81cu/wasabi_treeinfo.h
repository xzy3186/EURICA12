//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb  3 13:35:17 2012 by ROOT version 5.30/01
// from TTree DSSD/data
// found on file: ../DSSD_100Sn/root_dir/DSSD_0083.root
// outtree.pid_reset();
//////////////////////////////////////////////////////////

#ifndef wasabi_treeinfo_h
#define wasabi_treeinfo_h

#include "Riostream.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TArtWASABI.hh>

#define NumDSSD 8
#define NumStrX 60
#define NumStrY 40
#define NumADC 24 //23ADC+1QDC
#define NumTDC 7
#define NumTDCmulti 3
#define TDC_Pos_minchan 4

#define DSSD1HGAIN 1

const Int_t maxeventinfo = 1;

class wasabi {
   public :
      TTree          *fChain;   //!pointer to the analyzed TTree or TChain
      Int_t           fCurrent; //!current Tree number in a TChain

      // Declaration of leaf types
      Int_t           EventInfo_;
      UInt_t          EventInfo_fUniqueID[maxeventinfo];   //[EventInfo_]
      UInt_t          EventInfo_fBits[maxeventinfo];   //[EventInfo_]
      TString         EventInfo_fName[maxeventinfo];
      TString         EventInfo_fTitle[maxeventinfo];
      Int_t           EventInfo_runnumber[maxeventinfo];   //[EventInfo_]
      Int_t           EventInfo_eventnumber[maxeventinfo];   //[EventInfo_]
      TString         EventInfo_subsysname[maxeventinfo];
      ULong64_t       EventInfo_timestamp[maxeventinfo];   //[EventInfo_]
      Int_t           EventInfo_comp_val[maxeventinfo];   //[EventInfo_]
      UInt_t          EventInfo_fBit[maxeventinfo];   //[EventInfo_]

      Int_t           numdssd;
      Int_t           numtdc;
      Int_t           numadc;
      Int_t           dstrx;
      Int_t           dstry;
      Int_t           scal[32];
      Int_t           IF_BETA;
      Int_t           IF_ION;

      Int_t           DSSD_E[NumDSSD][100];
      Int_t           DSSD_T[NumDSSD][100][3];
      Int_t           ADC[NumADC][32];
      Int_t           TDC[NumTDC][128][3];
      Int_t           dssd_E_X[NumDSSD][60];
      Int_t           dssd_ch_X[NumDSSD][60];
      Int_t           dssd_id_X[NumDSSD][60];
      Int_t           dssd_T_X[NumDSSD][60][3];
      Int_t           dssd_T_Xoff[NumDSSD][60];
      Int_t           dssd_E_Y[NumDSSD][40];
      Int_t           dssd_ch_Y[NumDSSD][40];
      Int_t           dssd_id_Y[NumDSSD][40];
      Int_t           dssd_T_Y[NumDSSD][40][3];
      Int_t           dssd_T_Yoff[NumDSSD][40];
      Int_t           dssd_X[NumDSSD];
      Int_t           dssd_Y[NumDSSD];
      Int_t           dssd_Z;
      Int_t           dssd_fireX[NumDSSD];
      Int_t           dssd_fireY[NumDSSD];
      Int_t	          dssd_fastout[64][3];

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
      Int_t           bigrips_ICe[6];

      Int_t           Qbeta_E;
      Int_t           Qbeta_T;
      Int_t           Qveto_E;
      Int_t           Qveto_T;

      Int_t           NaI_E[3];
      Int_t           NaI_T[3];

      Double_t        bigrips_F3PPAC1_TDiffX;
      Double_t        bigrips_F3PPAC2_TDiffX;
      Double_t        bigrips_F5PPAC1_TDiffX;
      Double_t        bigrips_F5PPAC2_TDiffX;
      Double_t        bigrips_F3PPAC1_X;
      Double_t        bigrips_F3PPAC2_X;
      Double_t        bigrips_F5PPAC1_X;
      Double_t        bigrips_F5PPAC2_X;
      Double_t        bigrips_F3_X;
      Double_t        bigrips_F3_A;
      Double_t        bigrips_F5_X;
      Double_t        bigrips_F5_A;
      Double_t        bigrips_dERaw;
      Double_t        bigrips_dE;

      Double_t        fTOFLength[6];     // length for the TOF 0=f3f7,1=f3f5,2=f5f7,3=f8f11,4=zds first half,5 = zds, second half           
      Double_t        fBeta[8];                             // 0=F3F5, 1=F5F7, The first 4 are measured values, the last four are recalculated 
      Double_t        fGamma[8];
      Double_t        fDelta[6];            // fDelta=(p-p0)/p0*100, 0=F3F5,
      Double_t        fBrhoSet[12];                         // 0=F3F5, 1=F5F7 Magnet values for Brho
      Double_t        fBrhoReal[12];                        // Real BrhoValues
      Double_t        fZetCoef[4][2];
      Double_t        fAoQ[12];                             // Calclulated Aoq from Brho and Beta;
      Double_t        fZet[4];

      // 0: F3PPAC1A,  1: F3PPAC2A, 2: F5PPAC1A, 3: F5PPAC2A
      Double_t        fTX1[10];    
      Double_t        fTX2[10];    
      Double_t        fTY1[10];	
      Double_t        fTY2[10];
      Double_t        fA[10];
      Double_t        fTSum[10][2];                           //[detector][x,y]
      Double_t        fTDiff[10][2];
      Double_t        fX[10];                               // position at PPAC
      Double_t        fX_FP[10];                            // position at focal plane
      Double_t        fA_FP[10];                            // angle at focal plane
      Double_t        fTF3SCI_L;
      Double_t        fTF3SCI_R;
      Double_t        fTF7SCI_L;
      Double_t        fTF7SCI_R;
      Double_t        fTOF_F3F7;

      Double_t        pid_Delta_F3F5;
      Double_t        pid_TOF_F3F7;
      Double_t        pid_Beta_F3F5;
      Double_t        pid_Beta_F5F7;
      Double_t        pid_AoQ_F3F5;
      Double_t        pid_Zet_F11;

      // List of branches
      TBranch        *b_IF_BETA;
      TBranch        *b_IF_ION;

      TBranch        *b_EventInfo_;   //!
      TBranch        *b_EventInfo_fUniqueID;   //!
      TBranch        *b_EventInfo_fBits;   //!
      TBranch        *b_EventInfo_fName;   //!
      TBranch        *b_EventInfo_fTitle;   //!
      TBranch        *b_EventInfo_runnumber;   //!
      TBranch        *b_EventInfo_eventnumber;   //!
      TBranch        *b_EventInfo_subsysname;   //!
      TBranch        *b_EventInfo_timestamp;   //!
      TBranch        *b_EventInfo_comp_val;   //!
      TBranch        *b_EventInfo_fBit;   //!

      TBranch        *b_numdssd;
      TBranch        *b_numadc;
      TBranch        *b_numtdc;
      TBranch        *b_dstrx;
      TBranch        *b_dstry;
      TBranch        *b_scal;

      TBranch        *b_DSSD_E;
      TBranch        *b_DSSD_T;
      TBranch        *b_dssd_E_X;
      TBranch        *b_dssd_ch_X;
      TBranch        *b_dssd_id_X;
      TBranch        *b_dssd_E_Y;
      TBranch        *b_dssd_ch_Y;
      TBranch        *b_dssd_id_Y;
      TBranch        *b_dssd_T_X;
      TBranch        *b_dssd_T_Y;
      TBranch        *b_dssd_X;
      TBranch        *b_dssd_Y;
      TBranch        *b_dssd_Z;
      TBranch        *b_dssd_fireX;
      TBranch        *b_dssd_fireY;
      TBranch	     *b_ADC;
      TBranch	     *b_TDC;
      TBranch	     *b_dssd_fastout;

      TBranch        *b_bigrips_F3PPAC1X1;
      TBranch        *b_bigrips_F3PPAC1X2;
      TBranch        *b_bigrips_F3PPAC2X1;
      TBranch        *b_bigrips_F3PPAC2X2;
      TBranch        *b_bigrips_F5PPAC1X1;
      TBranch        *b_bigrips_F5PPAC1X2;
      TBranch        *b_bigrips_F5PPAC2X1;
      TBranch        *b_bigrips_F5PPAC2X2;
      TBranch        *b_bigrips_F3L;
      TBranch        *b_bigrips_F3R;
      TBranch        *b_bigrips_F7L;
      TBranch        *b_bigrips_F7R;
      TBranch        *b_bigrips_F11L;
      TBranch        *b_bigrips_F11R;
      TBranch        *b_bigrips_ICe;

      TBranch        *b_bigrips_F3PPAC1_TDiffX;
      TBranch        *b_bigrips_F3PPAC2_TDiffX;
      TBranch        *b_bigrips_F5PPAC1_TDiffX;
      TBranch        *b_bigrips_F5PPAC2_TDiffX;
      TBranch        *b_bigrips_F3PPAC1_X;
      TBranch        *b_bigrips_F3PPAC2_X;
      TBranch        *b_bigrips_F5PPAC1_X;
      TBranch        *b_bigrips_F5PPAC2_X;
      TBranch        *b_bigrips_F3_X;
      TBranch        *b_bigrips_F3_A;
      TBranch        *b_bigrips_F5_X;
      TBranch        *b_bigrips_F5_A;
      TBranch        *b_bigrips_dERaw;
      TBranch        *b_bigrips_dE;

      TBranch        *b_pid_Delta_F3F5;
      TBranch        *b_pid_TOF_F3F7;
      TBranch        *b_pid_Beta_F3F5;
      TBranch        *b_pid_Beta_F5F7;
      TBranch        *b_pid_AoQ_F3F5;
      TBranch        *b_pid_Zet_F11;

      TBranch        *b_Qbeta_E;
      TBranch        *b_Qbeta_T;
      TBranch        *b_Qveto_E;
      TBranch        *b_Qveto_T;

      TBranch        *b_NaI_E;
      TBranch        *b_NaI_T;

      wasabi();
      //virtual ~wasabi();
      //
      virtual void CopyToTArt(TArtWASABI *w);

      virtual void     GetTree(char* filename,TTree *tree=0);
      virtual void     ReleaseTree();
      virtual Int_t    Cut(Long64_t entry);
      virtual Int_t    GetEntry(Long64_t entry);
      virtual Long64_t LoadTree(Long64_t entry);
      virtual void     Init(TTree *tree);
      virtual Bool_t   Notify();
      virtual void     Show(Long64_t entry = -1);
      virtual void     GetTsEntry(map<Long64_t,Long64_t> &mts);
      virtual void     TreeBranch(TTree *tree);
      virtual void     ResetLeaf();
      virtual void     IfBeta(Int_t &IF_BETA, Int_t &IF_ION);
      virtual void     IonGetPos_TDC(Int_t &z, Int_t *x, Int_t *y);
      virtual void     IonGetDepth(Int_t &z);
      virtual void     IonGetXY(Int_t z, Int_t &x, Int_t &y);
      virtual void     BetaGetPos(Int_t &mult, map <Int_t,vector <pair<Int_t,Int_t> > > &beta_event);

      /*********** for mapping and calibration ***************/
      virtual void     read_calib_table();
      virtual void     read_mapping_table();
      virtual void     read_threshold_table();
      virtual void     read_bigrips_parameters();
      virtual void     dssd_E_mapping();
      virtual void     dssd_T_mapping();
      virtual void     TDC_getref();
      virtual void     TDC_getoff();
      virtual void     bigrips_mapping();
      virtual void     Qbeta_mapping();
      virtual void     NaI_mapping();
      virtual void     pid_reset();

      Double_t  rand05();
      void             set_bigrips_parameters();
      void             Process_BigRips_Analysis();
   private:
      Double_t         fCh2nsPlastic[10];		          // 0= F3L, 1= F3R, 2=F7L, 3=F7R
      Double_t         fCh2nsPlasticRatio[10];		  // 0= F3L, 1= F3R, 2=F7L, 3=F7R
      Double_t         fCh2nsPlasticBigRIPS[10];		  // 0= F3L, 1= F3R, 2=F7L, 3=F7R
      Double_t         fPlasticCh_offRelative[10];		  // 0= F3L, 1= F3R, 2=F7L, 3=F7R
      Double_t         fTOFOffset[10];                       // 0=F3-F7
      Double_t         fTOFOffsetBigRIPS[10];                // 0=F3-F7

      Double_t         fCh2MeVIC[2][2];		          // for IC, 
      Double_t         fCh2MeVICRatio[2];		  
      Double_t         fICCh_offRelative[2];		  
      Double_t         fCh2MeVICBigRIPS[2][2];		  

      Double_t         fCh2nsPPAC[36][5];		          // A,X1,Y1,X2,Y2 
      Double_t         fCh2nsPPACRatio[36][5];		          // A,X1,Y1,X2,Y2 sumikama
      Double_t         fCh2nsPPACBigRIPS[36][5];		          // A,X1,Y1,X2,Y2 
      Double_t         fxns_off[36];		          // 
      Double_t         fxns_offBigRIPS[36];              //
      Double_t         fxch_offRelative[36][5];		          // 
      Double_t         fF7SciLBigRIPSRaw;              //
      Double_t         fXFactor[10];
      Double_t         fXOffset[10];
      Double_t         fXPos_Off[10];
      Double_t         fXZPos[10];		          // z position for x ppac
      //artificial shift to A/Q and Z for online analysis
      Double_t         fAoQ_shift;
      Double_t         fZed_shift;
      Double_t        DSSD_CHtoE[NumDSSD][100][2];
      Int_t           ADC_thr[NumADC][32];
      Int_t           TDC_ref[NumTDC];
      Int_t           ADCtoDSSD[NumADC*32];
      Int_t           ADCtoSTRIP[NumADC*32];
      Int_t           TDCtoDSSD[NumTDC*128];
      Int_t           TDCtoSTRIP[NumTDC*128];
      Int_t           QbetaTDCch[2];
      Int_t           NaITDCch[3];
      Double_t        fBrhoSet0;
      Double_t        fBrhoSet1;
      Double_t        fCh2MeVICBigRIPS10;
      Double_t        fCh2MeVICBigRIPS11;
      Double_t        fZetCoef10;
      Double_t        fZetCoef11;
      Double_t        AoQ_shift;
      Double_t        Zed_shift;
};

wasabi::wasabi(){
   numdssd = NumDSSD;
   numadc = NumADC;
   numtdc = NumTDC;
   dstrx = NumDSSD*NumStrX;
   dstry = NumDSSD*NumStrY;
}

//wasabi::~wasabi()
//{
//   if (!fChain) return;
//   delete fChain->GetCurrentFile();
//}

void wasabi::GetTree(char *filename,TTree *tree)
{
   // if parameter tree is not specified (or zero), connect the file
   // used to generate this class and read the Tree.
   if (tree == 0) {
      //      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../DSSD_100Sn/root_dir/DSSD_0083.root");
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
      if (!f || !f->IsOpen()) {
         f = new TFile(filename);
      }
      f->GetObject("WASABI",tree);

   }
   Init(tree);
}
void wasabi::ReleaseTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t wasabi::GetEntry(Long64_t entry)
{
   // Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t wasabi::LoadTree(Long64_t entry)
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

void wasabi::Init(TTree *tree)
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

   fChain->SetBranchAddress("IF_BETA", &IF_BETA, &b_IF_BETA);
   fChain->SetBranchAddress("IF_ION", &IF_ION, &b_IF_ION);

   fChain->SetBranchAddress("EventInfo", &EventInfo_, &b_EventInfo_);
   fChain->SetBranchAddress("EventInfo.fUniqueID", EventInfo_fUniqueID, &b_EventInfo_fUniqueID);
   fChain->SetBranchAddress("EventInfo.fBits", EventInfo_fBits, &b_EventInfo_fBits);
   fChain->SetBranchAddress("EventInfo.fName", EventInfo_fName, &b_EventInfo_fName);
   fChain->SetBranchAddress("EventInfo.fTitle", EventInfo_fTitle, &b_EventInfo_fTitle);
   fChain->SetBranchAddress("EventInfo.runnumber", EventInfo_runnumber, &b_EventInfo_runnumber);
   fChain->SetBranchAddress("EventInfo.eventnumber", EventInfo_eventnumber, &b_EventInfo_eventnumber);
   fChain->SetBranchAddress("EventInfo.subsysname", EventInfo_subsysname, &b_EventInfo_subsysname);
   fChain->SetBranchAddress("EventInfo.timestamp", EventInfo_timestamp, &b_EventInfo_timestamp);
   fChain->SetBranchAddress("EventInfo.comp_val", EventInfo_comp_val, &b_EventInfo_comp_val);
   fChain->SetBranchAddress("EventInfo.fBit", EventInfo_fBit, &b_EventInfo_fBit);

   fChain->SetBranchAddress("DSSD_E", DSSD_E, &b_DSSD_E);
   fChain->SetBranchAddress("DSSD_T", DSSD_T, &b_DSSD_T);
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
   fChain->SetBranchAddress("dssd_fireX", dssd_fireX, &b_dssd_fireX);
   fChain->SetBranchAddress("dssd_fireY", dssd_fireY, &b_dssd_fireY);
   fChain->SetBranchAddress("ADC", ADC, &b_ADC);
   fChain->SetBranchAddress("TDC", TDC, &b_TDC);
   fChain->SetBranchAddress("dssd_fastout", dssd_fastout, &b_dssd_fastout);

   fChain->SetBranchAddress("scal", scal, &b_scal);

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
   fChain->SetBranchAddress("bigrips_ICe", bigrips_ICe, &b_bigrips_ICe);

   fChain->SetBranchAddress("Qbeta_E", &Qbeta_E, &b_Qbeta_E);
   fChain->SetBranchAddress("Qbeta_T", &Qbeta_T, &b_Qbeta_T);
   fChain->SetBranchAddress("Qveto_E", &Qveto_E, &b_Qveto_E);
   fChain->SetBranchAddress("Qveto_T", &Qveto_T, &b_Qveto_T);

   fChain->SetBranchAddress("NaI_E", NaI_E, &b_NaI_E);
   fChain->SetBranchAddress("NaI_T", NaI_T, &b_NaI_T);

   fChain->SetBranchAddress("bigrips_F3PPAC1_X",&bigrips_F3PPAC1_X,&b_bigrips_F3PPAC1_X);
   fChain->SetBranchAddress("bigrips_F3PPAC2_X",&bigrips_F3PPAC2_X,&b_bigrips_F3PPAC2_X);
   fChain->SetBranchAddress("bigrips_F5PPAC1_X",&bigrips_F5PPAC1_X,&b_bigrips_F5PPAC1_X);
   fChain->SetBranchAddress("bigrips_F5PPAC2_X",&bigrips_F5PPAC2_X,&b_bigrips_F5PPAC2_X);
   fChain->SetBranchAddress("bigrips_F3_X",&bigrips_F3_X,&b_bigrips_F3_X);
   fChain->SetBranchAddress("bigrips_F3_A",&bigrips_F3_A,&b_bigrips_F3_A);
   fChain->SetBranchAddress("bigrips_F5_X",&bigrips_F5_X,&b_bigrips_F5_X);
   fChain->SetBranchAddress("bigrips_F5_A",&bigrips_F5_A,&b_bigrips_F5_A);
   fChain->SetBranchAddress("bigrips_F3PPAC1_TDiffX",&bigrips_F3PPAC1_TDiffX,&b_bigrips_F3PPAC1_TDiffX);
   fChain->SetBranchAddress("bigrips_F3PPAC2_TDiffX",&bigrips_F3PPAC2_TDiffX,&b_bigrips_F3PPAC2_TDiffX);
   fChain->SetBranchAddress("bigrips_F5PPAC1_TDiffX",&bigrips_F5PPAC1_TDiffX,&b_bigrips_F5PPAC1_TDiffX);
   fChain->SetBranchAddress("bigrips_F5PPAC2_TDiffX",&bigrips_F5PPAC2_TDiffX,&b_bigrips_F5PPAC2_TDiffX);
   fChain->SetBranchAddress("bigrips_dERaw",&bigrips_dERaw,&b_bigrips_dERaw);
   fChain->SetBranchAddress("bigrips_dE",&bigrips_dE,&b_bigrips_dE);

   fChain->SetBranchAddress("pid_Delta_F3F5",&pid_Delta_F3F5,&b_pid_Delta_F3F5);
   fChain->SetBranchAddress("pid_TOF_F3F7",&pid_TOF_F3F7,&b_pid_TOF_F3F7);
   fChain->SetBranchAddress("pid_Beta_F3F5",&pid_Beta_F3F5,&b_pid_Beta_F3F5);
   fChain->SetBranchAddress("pid_Beta_F5F7",&pid_Beta_F5F7,&b_pid_Beta_F5F7);
   fChain->SetBranchAddress("pid_AoQ_F3F5",&pid_AoQ_F3F5,&b_pid_AoQ_F3F5);
   fChain->SetBranchAddress("pid_Zet_F11", &pid_Zet_F11,&b_pid_Zet_F11);

   Notify();
}

Bool_t wasabi::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void wasabi::Show(Long64_t entry)
{
   // Print contents of entry.
   // If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t wasabi::Cut(Long64_t entry)
{
   // This function may be called from Loop.
   // returns  1 if entry is accepted.
   // returns -1 otherwise.
   return 1;
}

void wasabi::GetTsEntry(map<Long64_t,Long64_t> &mts)
{
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t ts;
   Long64_t nbytes = 0, nb = 0;
   for(Long64_t jentries=0; jentries<nentries; jentries++){
      Long64_t ientry = LoadTree(jentries);
      if(ientry<0){
         break;
      }
      nb = fChain->GetEntry(jentries);
      nbytes+=nb;
      ts=EventInfo_timestamp[0];
      mts.insert(pair<Long64_t,Long64_t> (ts,jentries));
   }
}

void wasabi::TreeBranch(TTree *tree)
{
   tree->Branch("IF_BETA",&IF_BETA,"IF_BETA/I");
   tree->Branch("IF_ION",&IF_ION,"IF_ION/I");

   tree->Branch("numdssd",&numdssd,"numdssd/I");
   tree->Branch("numadc",&numadc,"numadc/I");
   tree->Branch("numtdc",&numtdc,"numtdc/I");
   tree->Branch("dstrx",&dstrx,"dstrx/I");
   tree->Branch("dstry",&dstry,"dstry/I");
   tree->Branch("scal",scal,"scal[32]/I");
   tree->Branch("dssd_E_X",dssd_E_X,"dssd_E_X[numdssd][60]/I");
   tree->Branch("dssd_ch_X",dssd_ch_X,"dssd_ch_X[numdssd][60]/I");
   tree->Branch("dssd_id_X",dssd_id_X,"dssd_id_X[numdssd][60]/I");
   tree->Branch("dssd_E_Y",dssd_E_Y,"dssd_E_Y[numdssd][40]/I");
   tree->Branch("dssd_ch_Y",dssd_ch_Y,"dssd_ch_Y[numdssd][40]/I");
   tree->Branch("dssd_id_Y",dssd_id_Y,"dssd_id_Y[numdssd][40]/I");
   tree->Branch("dssd_T_X",dssd_T_X,"dssd_T_X[numdssd][60][3]/I");
   tree->Branch("dssd_T_Y",dssd_T_Y,"dssd_T_Y[numdssd][40][3]/I");
   tree->Branch("dssd_X",dssd_X,"dssd_X[numdssd]/I");
   tree->Branch("dssd_Y",dssd_Y,"dssd_Y[numdssd]/I");
   tree->Branch("dssd_Z",&dssd_Z,"dssd_Z/I");
   tree->Branch("dssd_fireX",dssd_fireX,"dssd_fireX[numdssd]/I");
   tree->Branch("dssd_fireY",dssd_fireY,"dssd_fireY[numdssd]/I");
   tree->Branch("ADC",ADC,"ADC[numadc][32]/I");
   tree->Branch("TDC",TDC,"TDC[numtdc][128][3]/I");
   tree->Branch("dssd_fastout",dssd_fastout,"dssd_fastout[64][3]/I");
   tree->Branch("DSSD_E",DSSD_E,"DSSD_E[numdssd][100]/I");
   tree->Branch("DSSD_T",DSSD_T,"DSSD_T[numdssd][100][3]/I");

   tree->Branch("bigrips_F3PPAC1X1",&bigrips_F3PPAC1X1,"bigrips_F3PPAC1X1/I");
   tree->Branch("bigrips_F3PPAC1X2",&bigrips_F3PPAC1X2,"bigrips_F3PPAC1X2/I");
   tree->Branch("bigrips_F3PPAC2X1",&bigrips_F3PPAC2X1,"bigrips_F3PPAC2X1/I");
   tree->Branch("bigrips_F3PPAC2X2",&bigrips_F3PPAC2X2,"bigrips_F3PPAC2X2/I");
   tree->Branch("bigrips_F5PPAC1X1",&bigrips_F5PPAC1X1,"bigrips_F5PPAC1X1/I");
   tree->Branch("bigrips_F5PPAC1X2",&bigrips_F5PPAC1X2,"bigrips_F5PPAC1X2/I");
   tree->Branch("bigrips_F5PPAC2X1",&bigrips_F5PPAC2X1,"bigrips_F5PPAC2X1/I");
   tree->Branch("bigrips_F5PPAC2X2",&bigrips_F5PPAC2X2,"bigrips_F5PPAC2X2/I");
   tree->Branch("bigrips_F3L",&bigrips_F3L,"bigrips_F3L/I");
   tree->Branch("bigrips_F3R",&bigrips_F3R,"bigrips_F3R/I");
   tree->Branch("bigrips_F7L",&bigrips_F7L,"bigrips_F7L/I");
   tree->Branch("bigrips_F7R",&bigrips_F7R,"bigrips_F7R/I");
   tree->Branch("bigrips_F11L",&bigrips_F11L,"bigrips_F11L/I");
   tree->Branch("bigrips_F11R",&bigrips_F11R,"bigrips_F11R/I");
   tree->Branch("bigrips_ICe",bigrips_ICe,"bigrips_ICe[6]/I");

   tree->Branch("Qbeta_E",&Qbeta_E,"Qbeta_E/I");
   tree->Branch("Qbeta_T",&Qbeta_T,"Qbeta_T/I");
   tree->Branch("Qveto_E",&Qveto_E,"Qveto_E/I");
   tree->Branch("Qveto_T",&Qveto_T,"Qveto_T/I");

   tree->Branch("NaI_E",NaI_E,"NaI_E[3]/I");
   tree->Branch("NaI_T",NaI_T,"NaI_T[3]/I");

   tree->Branch("bigrips_F3PPAC1_TDiffX",&bigrips_F3PPAC1_TDiffX,"bigrips_F3PPAC1_TDiffX/D");
   tree->Branch("bigrips_F3PPAC2_TDiffX",&bigrips_F3PPAC2_TDiffX,"bigrips_F3PPAC2_TDiffX/D");
   tree->Branch("bigrips_F5PPAC1_TDiffX",&bigrips_F5PPAC1_TDiffX,"bigrips_F5PPAC1_TDiffX/D");
   tree->Branch("bigrips_F5PPAC2_TDiffX",&bigrips_F5PPAC2_TDiffX,"bigrips_F5PPAC2_TDiffX/D");
   tree->Branch("bigrips_F3PPAC1_X",&bigrips_F3PPAC1_X,"bigrips_F3PPAC1_X/D");
   tree->Branch("bigrips_F3PPAC2_X",&bigrips_F3PPAC2_X,"bigrips_F3PPAC2_X/D");
   tree->Branch("bigrips_F5PPAC1_X",&bigrips_F5PPAC1_X,"bigrips_F5PPAC1_X/D");
   tree->Branch("bigrips_F5PPAC2_X",&bigrips_F5PPAC2_X,"bigrips_F5PPAC2_X/D");
   tree->Branch("bigrips_F3_X",&bigrips_F3_X,"bigrips_F3_X/D");
   tree->Branch("bigrips_F3_A",&bigrips_F3_A,"bigrips_F3_A/D");
   tree->Branch("bigrips_F5_X",&bigrips_F5_X,"bigrips_F5_X/D");
   tree->Branch("bigrips_F5_A",&bigrips_F5_A,"bigrips_F5_A/D");
   tree->Branch("bigrips_dERaw",&bigrips_dERaw,"bigrips_dERaw/D");
   tree->Branch("bigrips_dE",&bigrips_dE,"bigrips_dE/D");

   tree->Branch("pid_Delta_F3F5",&pid_Delta_F3F5,"pid_Delta_F3F5/D");
   tree->Branch("pid_TOF_F3F7",&pid_TOF_F3F7,"pid_TOF_F3F7/D");
   tree->Branch("pid_Beta_F3F5",&pid_Beta_F3F5,"pid_Beta_F3F5/D");
   tree->Branch("pid_Beta_F5F7",&pid_Beta_F5F7,"pid_Beta_F5F7/D");
   tree->Branch("pid_AoQ_F3F5",&pid_AoQ_F3F5,"pid_AoQ_F3F5/D");
   tree->Branch("pid_Zet_F11", &pid_Zet_F11,"pid_Zet_F11/D");
}

void wasabi::ResetLeaf(){
   for (int k=0; k<32; k++){
      scal[k]=-1;
   }
   for (int k=0; k<64; k++){
      for (int i=0; i<3; i++){
         dssd_fastout[k][i]=-100000;
      }
   }
   dssd_Z=-1;
   for(int k=0; k<NumDSSD; k++){
      dssd_X[k] = -1;
      dssd_Y[k] = -1;
      dssd_fireX[k] = 0;
      dssd_fireY[k] = 0;
   }
   for(int k=0; k<NumTDC; k++){
      for(int i=0; i<128; i++){
         for (int j= 0;j<NumTDCmulti;j++){
            TDC[k][i][j] = -100000;
         }
      }
   }
   for(int k=0; k<NumADC; k++){
      for(int i=0; i<32; i++){
         ADC[k][i] = -1;
      }
   }

}

void wasabi::IfBeta(Int_t &IF_BETA, Int_t &IF_ION)
{
   IF_BETA=1;
   IF_ION=0;
   //Int_t hi_chain[8]; //to restore resistive chain data
   if(bigrips_F7L>-50000 || bigrips_F11L>-50000){
      IF_ION=1;
      IF_BETA=0;
   }else{
      for(int k=0; k<NumDSSD; k++){
         for(int i=0; i<NumStrX; i++){
            if (dssd_E_X[k][i]>3500){
               IF_BETA=0;
               break;
            }
         }
         for(int i=0; i<NumStrY; i++){
            if (dssd_E_Y[k][i]>3500){
               IF_BETA=0;
               break;
            }
         }
         if(IF_BETA==0){
            break;
         }
      }
   }
}

void wasabi::IonGetPos_TDC(Int_t &z, Int_t *x, Int_t *y)
{
   /**********initialize*************/
   z=-1;
   Int_t strip_x=-1, strip_y=-1;
   for(int i=0; i<NumDSSD; i++){
      x[i]=-1;
      y[i]=-1;
   }
   /**********************************/
   IonGetDepth(z);
   for(int k=0; k<NumDSSD; k++){
      if(dssd_fireX[k]*dssd_fireY[k]==1){
         IonGetXY(k,strip_x,strip_y);
         x[k]=strip_x;
         y[k]=strip_y;
      }
   }
}

void wasabi::IonGetDepth(Int_t &z){
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
       for(int i=0; i<NumStrX; i++){
          if(dssd_T_X[k][i][0]>-500 && dssd_T_X[k][i][0]<500){
             HI_firedX[k]=1;
             break;
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
       for(int i=0; i<NumStrY; i++){
          if(dssd_T_Y[k][i][0]>-500 && dssd_T_Y[k][i][0]<1000){
             HI_firedY[k]=1;
             break;
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
      if(HI_firedX[i]==1 && HI_firedY[i]==1){
         fire_DSSD[i]=1;
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
      //   z=8;
      //}else{
         for(int i=0; i<=NumDSSD; i++){
            if(fire_DSSD[i]==1 && fire_DSSD[i+1]==0){
               z=i;
               break;
            }
         }
      //}
   }else{
      z=-1;
   }
   for(int i=0; i<NumDSSD; i++){
      dssd_fireX[i] = HI_firedX[i];
      dssd_fireY[i] = HI_firedY[i];
      //cout<<dssd_fireX[i]<<", ";
   }
   //cout<<endl;
}

void wasabi::IonGetXY(Int_t z, Int_t &x, Int_t &y){
   int flag;
   if(DSSD1HGAIN == 1){
      flag = 9;
   }else{
      flag = 0;
   }

   Int_t max_temp;
   if(z==flag){
      max_temp = 0;
      for(int i=0; i<NumStrX; i++){
         if(dssd_T_X[z][i][0]>-50000 && dssd_E_X[z][i]>max_temp){
            x=i;
            max_temp = dssd_E_X[z][i];
         }
      }
      max_temp = 0;
      for(int i=0; i<NumStrY; i++){
         if(dssd_T_Y[z][i][0]>-50000 && dssd_E_Y[z][i]>max_temp){
            y=i;
            max_temp = dssd_E_Y[z][i];
         }
      }
   }else{
      max_temp = 1500;
      for(int i=0; i<NumStrX; i++){
         if(dssd_T_X[z][i][0]>-500 && dssd_T_X[z][i][0]<500 && dssd_T_X[z][i][0]<max_temp){
            x=i;
            max_temp = dssd_T_X[z][i][0];
         }
      }
      max_temp = 1500;
      for(int i=0; i<NumStrY; i++){
         if(dssd_T_Y[z][i][0]>-500 && dssd_T_Y[z][i][0]<1000 && dssd_T_Y[z][i][0]<max_temp){
            y=i;
            max_temp = dssd_T_Y[z][i][0];
         }
      }
   }
   /**** special case for dead channel ****/
   if(z==3){
      if(dssd_Y[2]==16){
         y=16;
      }
      if(dssd_X[2]==13){
         x=13;
      }
   }
   /***************************************/
   //if(z==0){
   //   cout<<"x = "<<x<<", y = "<<y<<endl;
   //}
}

void wasabi::BetaGetPos(Int_t &mult, map<Int_t,vector<pair<Int_t,Int_t> > > &beta_event)
{//mult is the multiplicity of beta event. map(z,vector(pair(x,y))) restore position
   //information of beta decay.
   mult=0;
   for(Int_t z=0; z<NumDSSD; z++){
      vector<pair<Int_t,Int_t> > beta_dssd;
      for(Int_t x=0; x<NumStrX; x++){
         if(dssd_T_X[z][x][0]>-50000 && dssd_E_X[z][x]>10){
            //cout << "x-strip found" << endl;
            for(Int_t y=0; y<NumStrY; y++){
               //cout << dssd_T_Y[z][y][0] << "  " << dssd_E_Y[z][y] <<endl;
               if(dssd_T_Y[z][y][0]>-50000 && dssd_E_Y[z][y]>10){
                  //cout << "y-strip found" << endl;
                  mult++;
                  beta_dssd.push_back(pair<Int_t,Int_t> (x,y));
               }
            }
         }
      }
      if(beta_dssd.size()>0){
         beta_event[z]=beta_dssd;
      }
   }
}

void wasabi::read_calib_table(){
   ifstream in_calib;
   Double_t p1, p0;
   Double_t s1, s2;
   in_calib.open("DSSD_E_calib.input", ios::in);
   Int_t dssd_index, strip_index;
   for(int i=0; i<NumDSSD; i++){
      for(int j=0; j<100; j++){
         DSSD_CHtoE[i][j][0]=1;
         DSSD_CHtoE[i][j][1]=0;
      }
   }
   while (in_calib.good()){
      in_calib >>dssd_index>>strip_index>>p1>>p0>>s1>>s2;
      DSSD_CHtoE[dssd_index][strip_index][0]=p1;
      DSSD_CHtoE[dssd_index][strip_index][1]=p0;
      if(dssd_index>=4 && strip_index<60){
         DSSD_CHtoE[dssd_index][strip_index+1][0]=p1;
         DSSD_CHtoE[dssd_index][strip_index+1][1]=p0;
      }
   }
}

void wasabi::read_threshold_table(){
   ifstream in_threshold;
   in_threshold.open("ADC_thr.input", ios::in);
   Int_t ADC_index, ch_index, threshold;
   for(int i=0; i<NumADC; i++){
      for(int j=0; j<32; j++){
         ADC_thr[i][j]=0;
      }
   }
   while (in_threshold.good()){
      in_threshold >>ADC_index>>ch_index>>threshold;
      ADC_thr[ADC_index][ch_index]=threshold;
   }
}

void wasabi::read_mapping_table(){
   ifstream in_ADC, in_TDC, in_Qbeta, in_NaI;
   Int_t ADC_index, TDC_index, ch_index, index, DSSD_index, strip_index;

   /**** initialize all the array of DSSD ADC mapping table ****/
   for(index=0; index<NumADC*32; index++){
      ADCtoDSSD[index]=-1;
      ADCtoSTRIP[index]=-1;
   }
   /**** start reading table and filling into array ****/
   in_ADC.open("ADC_table.input", ios::in);
   while (in_ADC.good()){
      in_ADC >>ADC_index>>ch_index>>index>>DSSD_index>>strip_index;
      ADCtoDSSD[index]=DSSD_index;
      ADCtoSTRIP[index]=strip_index;
   }
   in_ADC.close();

   /**** initialize all the array of DSSD TDC mapping table ****/
   for(index=0; index<NumTDC*128; index++){
      TDCtoDSSD[index]=-1;
      TDCtoSTRIP[index]=-1;
   }
   /**** start reading table and filling into array ****/
   in_TDC.open("TDC_table.input", ios::in);
   while (in_TDC.good()){
      in_TDC >>TDC_index>>ch_index>>index>>DSSD_index>>strip_index;
      //cout << in_TDC << "  " << TDC_index<< "  " <<ch_index<< "  " <<index<< "  " <<DSSD_index<< "  " <<strip_index<<endl;
      TDCtoDSSD[index]=DSSD_index;
      TDCtoSTRIP[index]=strip_index;
   }
   in_TDC.close();

   in_Qbeta.open("Qbeta_T_mapping.input", ios::in);
   in_Qbeta >>QbetaTDCch[0];
   in_Qbeta >>QbetaTDCch[1];
   in_Qbeta.close();

   in_NaI.open("NaI_T_mapping.input", ios::in);
   in_NaI >>NaITDCch[0];
   in_NaI >>NaITDCch[1];
   in_NaI >>NaITDCch[2];
   in_NaI.close();
}

void wasabi::dssd_E_mapping(){
   int x, y, i, j, index;
   /**** initialize all the array of DSSD ****/
   for(x=0; x<NumDSSD; x++){
      for(y=0; y<100; y++){
         DSSD_E[x][y]=-1;
      }
      for(y=0; y<60; y++){
         dssd_E_X[x][y]=-1;
         dssd_ch_X[x][y]=y;
         dssd_id_X[x][y]=x;
      }
      for(y=0; y<40; y++){
         dssd_E_Y[x][y]=-1;
         dssd_ch_Y[x][y]=y;
         dssd_id_Y[x][y]=x;
      }
   }
   /**** start mapping ****/
   for(i=0; i<NumADC-2; i++){
      for(j=0; j<32; j++){
         if(ADC[i][j]<0){
            continue;
         }
         index=i*32+j;
         x=ADCtoDSSD[index]-1;
         y=ADCtoSTRIP[index]-1;
         if(x<0 || y<0){
            continue;
         }
         if(x>=4 && y<60){
            DSSD_E[x][y]=ADC[i][j];
            DSSD_E[x][y-1]=ADC[i][j];
         }else{
            DSSD_E[x][y]=ADC[i][j];
         }
      }
   }
   for(int i=0; i<NumDSSD;i++){
      for(int j=0; j<NumStrX;j++){
         if(DSSD_E[i][j]>0){
            dssd_E_X[i][j] = (Int_t) ((DSSD_E[i][j]+rand05())*DSSD_CHtoE[i][j][0]+DSSD_CHtoE[i][j][1]);
         }
      }
      for(int j=0; j<NumStrY;j++){
         if(DSSD_E[i][j+60]>0){
            dssd_E_Y[i][j] = (Int_t) ((DSSD_E[i][j+60]+rand05())*DSSD_CHtoE[i][j+60][0]+DSSD_CHtoE[i][j+60][1]+rand05());
         }
      }
   }
   /**** For special case ****/
   dssd_E_Y[3][5]=-1;
}

void wasabi::TDC_getref(){
   for(int i=0; i<NumTDC; i++){
      TDC_ref[i]=-1;
   }
   TDC_ref[0]=TDC[0][15][0];
   TDC_ref[1]=TDC[1][15][0];
   TDC_ref[2]=TDC[2][112][0];
   TDC_ref[3]=TDC[3][0][0];
   TDC_ref[4]=TDC[4][96][0];
   TDC_ref[5]=TDC[5][7][0];
   //TDC_ref[6]=0;
   TDC_ref[6]=TDC[6][15][0];
}

void wasabi::TDC_getoff(){
   ifstream in_TDC;
   Int_t dssd_index, strip_index, offset, sigma;
   /**** initialize all the TDC offset table ****/
   for(int i=0; i<NumDSSD; i++){
      for(int j=0; j<NumStrX; j++){
         dssd_T_Xoff[i][j]=0;
      }
      for(int j=0; j<NumStrY; j++){
         dssd_T_Yoff[i][j]=0;
      }
   }
   /**** start reading table and filling into array ****/
   in_TDC.open("DSSD_T_offset.input", ios::in);
   while (in_TDC.good()){
      in_TDC >>dssd_index>>strip_index>>offset>>sigma;
      if(strip_index<60){
         if(dssd_index<4){
            dssd_T_Xoff[dssd_index][strip_index] = offset;
         }else{
            if(strip_index%2==0){
               dssd_T_Xoff[dssd_index][strip_index] = offset;
               dssd_T_Xoff[dssd_index][strip_index+1] = offset;
            }
         }
      }else{
         dssd_T_Yoff[dssd_index][strip_index-60] = offset;
      }
   }
   in_TDC.close();
}

void wasabi::dssd_T_mapping(){
   int x, y, i, j, index;
   /**** initialize all the array of DSSD ****/
   for(x=0; x<NumDSSD; x++){
      for(y=0; y<100; y++){
         for (int k = 0; k<NumTDCmulti;k++){
            DSSD_T[x][y][k]=-100000;
         }
      }
   }
   /**** start mapping ****/
   for(i=0; i<NumTDC-1; i++){
      for(j=0; j<128; j++){
         if(TDC[i][j][0]<0){
            continue;
         }
         index=i*128+j;
         x=TDCtoDSSD[index]-1;
         y=TDCtoSTRIP[index]-1;
         if(x<0 || y<0){
            continue;
         }
         if(x>=4 && y<60){
            for(int k=0; k<NumTDCmulti; k++){
               if(TDC[i][j][k]<0){
                  continue;
               }
               DSSD_T[x][y][k]=TDC[i][j][k]-TDC_ref[i];
               DSSD_T[x][y-1][k]=TDC[i][j][k]-TDC_ref[i];
            }
         }else{
            for(int k=0; k<NumTDCmulti; k++){
               DSSD_T[x][y][k]=TDC[i][j][k]-TDC_ref[i];
            }
         }
      }
   }
   for(int i=0; i<NumDSSD;i++){
      for(int j=0; j<NumStrX;j++){
         for(int k= 0;k< NumTDCmulti;k++){
            dssd_T_X[i][j][k] = DSSD_T[i][j][k] - dssd_T_Xoff[i][j];
         }
      }
      for(int j=0; j<NumStrY;j++){
         for(int k= 0;k< NumTDCmulti;k++){
            dssd_T_Y[i][j][k] = DSSD_T[i][j+60][k] - dssd_T_Yoff[i][j];
         }
      }
   }
}

void wasabi::bigrips_mapping(){
   bigrips_F3PPAC1X1=TDC[6][6][0]-TDC_ref[6];
   bigrips_F3PPAC1X2=TDC[6][7][0]-TDC_ref[6];
   bigrips_F3PPAC2X1=TDC[6][8][0]-TDC_ref[6];
   bigrips_F3PPAC2X2=TDC[6][9][0]-TDC_ref[6];
   bigrips_F5PPAC1X1=TDC[6][10][0]-TDC_ref[6];
   bigrips_F5PPAC1X2=TDC[6][11][0]-TDC_ref[6];
   bigrips_F5PPAC2X1=TDC[6][12][0]-TDC_ref[6];
   bigrips_F5PPAC2X2=TDC[6][13][0]-TDC_ref[6];
   bigrips_F3L=TDC[6][2][0]-TDC_ref[6];
   bigrips_F3R=TDC[6][3][0]-TDC_ref[6];
   bigrips_F7L=TDC[6][4][0]-TDC_ref[6];
   bigrips_F7R=TDC[6][5][0]-TDC_ref[6];
   bigrips_F11L=TDC[6][0][0]-TDC_ref[6];
   bigrips_F11R=TDC[6][1][0]-TDC_ref[6];
   for(int i=0; i<6; i++){
      bigrips_ICe[i]=ADC[22][i];
   }
}

void wasabi::Qbeta_mapping(){
   Qbeta_E=ADC[23][16];
   Qveto_E=ADC[22][16];
   Qbeta_T=TDC[6][QbetaTDCch[0]][0]-TDC_ref[6];
   Qveto_T=TDC[6][QbetaTDCch[1]][0]-TDC_ref[6];
   for(int i=0; i<64; i++){
      for(int j=0; j<3; j++){
         dssd_fastout[i][j]=TDC[6][64+i][j];
      }
   }
}

void wasabi::NaI_mapping(){
   NaI_E[0]=ADC[22][6];
   NaI_E[1]=ADC[22][7];
   NaI_E[2]=ADC[22][8];
   for(int i=0; i<3; i++){
      NaI_T[i]=TDC[6][NaITDCch[i]][0]-TDC_ref[6];
   }
}

Double_t wasabi::rand05()
{
  return rand()*1./RAND_MAX - 0.5;
}

void wasabi::read_bigrips_parameters(){
   ifstream in_bigrips;
   in_bigrips.open("bigrips_parameters.input", ios::in);
   in_bigrips >>fBrhoSet0;
   in_bigrips >>fBrhoSet1;
   in_bigrips >>fCh2MeVICBigRIPS10;
   in_bigrips >>fCh2MeVICBigRIPS11;
   in_bigrips >>fZetCoef10;
   in_bigrips >>fZetCoef11;
   in_bigrips >>AoQ_shift;
   in_bigrips >>Zed_shift;
}

void wasabi::set_bigrips_parameters()
{
   //temporary , these should be from file
   // These are from BigRIPS part.
   // F3PPAC1A
   fF7SciLBigRIPSRaw = 2102.;

   fCh2nsPPACBigRIPS[0][1] = 0.151096;
   fCh2nsPPACBigRIPS[0][3] = 0.147478;
   fxns_offBigRIPS[0] = -4.72;
   fXFactor[0] = 1.238;
   fXOffset[0] = 0.79;
   fXPos_Off[0] = 1.046;
   fXZPos[0] = -18.7;

   // F3PPAC2A
   fCh2nsPPACBigRIPS[1][1] = 0.146298;
   fCh2nsPPACBigRIPS[1][3] = 0.151626;
   fxns_offBigRIPS[1] = 9.79;
   fXFactor[1] = 1.226;
   fXOffset[1] = 0.88;
   fXPos_Off[1] = 1.9789;
   fXZPos[1] = 871.3;

   // F5PPAC1A
   fCh2nsPPACBigRIPS[2][1] = 0.151622;
   fCh2nsPPACBigRIPS[2][3] = 0.147927;
   fxns_offBigRIPS[2] = 13.66;
   fXFactor[2] = 1.241;
   fXOffset[2] = 1.04;
   fXPos_Off[2] = 0.0;
   fXZPos[2] = -418.7;

   // F5PPAC2A
   fCh2nsPPACBigRIPS[3][1] = 0.146886;
   fCh2nsPPACBigRIPS[3][3] = 0.147218;
   fxns_offBigRIPS[3] = -14.86;
   fXFactor[3] = 1.214;
   fXOffset[3] = 0.86;
   fXPos_Off[3] = -0.15;
   fXZPos[3] = 231.3;

   //  F3_Plastic 
   fCh2nsPlasticBigRIPS[0] = 0.0271382;
   fCh2nsPlasticBigRIPS[1] = 0.0276006;

   //  F7_Plastic 
   fCh2nsPlasticBigRIPS[2] = 0.0270701;
   fCh2nsPlasticBigRIPS[3] = 0.0277871;

   // TOF offset
   fTOFOffsetBigRIPS[0] = 242.513 -51.3; //add 8ns artificially

   fBrhoSet[0] = fBrhoSet0;  //Brho @ F3F5
   fBrhoSet[1] = fBrhoSet1;  //Brho @ F3F5


   fCh2MeVICBigRIPS[1][0] = fCh2MeVICBigRIPS10;
   fCh2MeVICBigRIPS[1][1] = fCh2MeVICBigRIPS11;

   fZetCoef[1][0] = fZetCoef10;
   fZetCoef[1][1] = fZetCoef11;

   // These are from fitting between two TDCs, where F7_Sci_L is subtracted). 
   fCh2nsPPACRatio[0][1] = 0.653953;
   fCh2nsPPACRatio[0][3] = 0.668934;
   fxch_offRelative[0][1]  = -9779.84;
   fxch_offRelative[0][3]  = -9922.98;

   fCh2nsPPACRatio[1][1] = 0.671671;
   fCh2nsPPACRatio[1][3] = 0.64846;
   fxch_offRelative[1][1]  = -9836.94;
   fxch_offRelative[1][3]  = -9648.64;

   fCh2nsPPACRatio[2][1] = 0.643935;
   fCh2nsPPACRatio[2][3] = 0.662735;
   fxch_offRelative[2][1]  = -9722.3;
   fxch_offRelative[2][3]  = -10040.9;

   fCh2nsPPACRatio[3][1] = 0.662735;
   fCh2nsPPACRatio[3][3] = 0.665662;
   fxch_offRelative[3][1]  = -10040.9;
   fxch_offRelative[3][3]  = -9876.53;

   fCh2nsPlasticRatio[0] = 3.5778;
   fCh2nsPlasticRatio[1] = 3.47689;
   fCh2nsPlasticRatio[2] = (fCh2nsPlasticRatio[0]+fCh2nsPlasticRatio[1])/2.;
   fCh2nsPlasticRatio[3] = fCh2nsPlasticRatio[2];
   fPlasticCh_offRelative[0] = -1707.5;
   fPlasticCh_offRelative[1] = -2113.98;
   fPlasticCh_offRelative[2] = 0.;
   fPlasticCh_offRelative[3] = -52.4;


   fCh2MeVICRatio[1] = 3.219;
   fICCh_offRelative[1] = 0;

   //artificial shift to A/Q and Z for online analysis
   fAoQ_shift = AoQ_shift;
   fZed_shift = Zed_shift;


   for (int j=0;j<4;j++) {
      for (int i=0;i<5;i++) {
         fCh2nsPPAC[j][i] = fCh2nsPPACRatio[j][i]*fCh2nsPPACBigRIPS[j][i];
      }
      fxns_off[j] = fxns_offBigRIPS[j] 
         - fF7SciLBigRIPSRaw *(fCh2nsPPACBigRIPS[j][1]-fCh2nsPPACBigRIPS[j][3])
         - fxch_offRelative[j][1]*fCh2nsPPACBigRIPS[j][1]
         + fxch_offRelative[j][3]*fCh2nsPPACBigRIPS[j][3];
   }

   for (int i=0;i<4;i++) {
      fCh2nsPlastic[i] = fCh2nsPlasticRatio[i]*fCh2nsPlasticBigRIPS[i];
      fTOFOffset[0] = fTOFOffsetBigRIPS[0] 
         - fF7SciLBigRIPSRaw *(fCh2nsPlasticBigRIPS[2]+fCh2nsPlasticBigRIPS[3]
               -fCh2nsPlasticBigRIPS[0]-fCh2nsPlasticBigRIPS[1])
         -fPlasticCh_offRelative[0]*fCh2nsPlasticBigRIPS[0]
         -fPlasticCh_offRelative[1]*fCh2nsPlasticBigRIPS[1]
         +fPlasticCh_offRelative[2]*fCh2nsPlasticBigRIPS[2]
         +fPlasticCh_offRelative[3]*fCh2nsPlasticBigRIPS[3];
   }

   fTOFLength[1] = 23.318;    // F3_Plastic - F5 degrader, in m
   fTOFLength[2] = 23.658;    // F5 degrader - F7_Plastic, in m


   for (int i=0;i<4;i++) {
      fCh2MeVIC[1][1] = fCh2MeVICRatio[1]*fCh2MeVICBigRIPS[1][1];
      fCh2MeVIC[1][0] = fCh2MeVICBigRIPS[1][0]
         +fICCh_offRelative[1]*fCh2MeVICBigRIPS[1][1];
   }
}

void wasabi::Process_BigRips_Analysis()
{
   set_bigrips_parameters();

   Double_t const_c = 299.792458;
   Double_t const_u = 931.49432;
   Double_t c = const_c; 
   Double_t amu = const_u ; 
   Double_t mdE = 1.;
   Double_t dERaw, dE;

   if ( bigrips_ICe[0] > 120 && bigrips_ICe[1] > 120 && bigrips_ICe[2] > 120 
         && bigrips_ICe[3] > 120 && bigrips_ICe[4] > 120 && bigrips_ICe[5] > 120 ) {
      mdE *= bigrips_ICe[0] + rand05();
      mdE *= bigrips_ICe[1] + rand05();
      mdE *= bigrips_ICe[2] + rand05();
      mdE *= bigrips_ICe[3] + rand05();
      mdE *= bigrips_ICe[4] + rand05();
      mdE *= bigrips_ICe[5] + rand05();
   }

   dERaw= pow(mdE,1./6.);
   dE = fCh2MeVIC[1][0] + fCh2MeVIC[1][1]*dERaw;

   //  if (bigrips_F3PPAC1X1<200000 && bigrips_F3PPAC1X1>100) {
   fTX1[0] = fCh2nsPPAC[0][1]*((Double_t)(bigrips_F3PPAC1X1 - bigrips_F7L)
         +rand05());
   //  }
   //  if (bigrips_F3PPAC1X2<200000 && bigrips_F3PPAC1X2>100) {
   fTX2[0] = fCh2nsPPAC[0][3]*((Double_t)(bigrips_F3PPAC1X2 - bigrips_F7L)
         +rand05());
   //  }

   //  if (bigrips_F3PPAC2X1 <200000 && bigrips_F3PPAC2X1>100) {
   fTX1[1] = fCh2nsPPAC[1][1]*(bigrips_F3PPAC2X1 - bigrips_F7L
         +rand05());
   //  }
   //  if (bigrips_F3PPAC2X2<200000 && bigrips_F3PPAC2X2>100) {
   fTX2[1] = fCh2nsPPAC[1][3]*(bigrips_F3PPAC2X2 - bigrips_F7L
         +rand05());
   //  }
   //  if (bigrips_F5PPAC1X1<200000 && bigrips_F5PPAC1X1>100) {
   fTX1[2] = fCh2nsPPAC[2][1]*(bigrips_F5PPAC1X1 - bigrips_F7L
         +rand05());
   //  }
   //  if (bigrips_F5PPAC1X2<200000 && bigrips_F5PPAC1X2>100) {
   fTX2[2] = fCh2nsPPAC[2][3]*(bigrips_F5PPAC1X2 - bigrips_F7L
         +rand05());
   //  }
   //  if (bigrips_F5PPAC2X1<200000 && bigrips_F5PPAC2X1>100) {
   fTX1[3] = fCh2nsPPAC[3][1]*(bigrips_F5PPAC2X1 - bigrips_F7L
         +rand05());
   //  }
   //  if (bigrips_F5PPAC2X2<200000 && bigrips_F5PPAC2X2>100) {
   fTX2[3] = fCh2nsPPAC[3][3]*(bigrips_F5PPAC2X2 - bigrips_F7L
         +rand05());
   //  }

   for (int i=0;i<4;i++) {
      fTDiff[i][0] = fTX1[i] - fTX2[i]    - fxns_off[i];
      fX[i] = - (fTDiff[i][0] * fXFactor[i]/2. -fXOffset[i] -fXPos_Off[i]);
   }
   for (int i=0;i<2;i++) {
      Double_t distance = fXZPos[1+2*i] - fXZPos[2*i];
      fA_FP[i] = (fX[1+2*i]-fX[2*i])/distance;
      fX_FP[i] = fX[2*i] - fA_FP[i]*fXZPos[2*i];
   }

   fDelta[0] = (fX_FP[1] - fX_FP[0]*0.926591)/31.6690;

   fTF3SCI_L = (bigrips_F3L+rand05())*fCh2nsPlastic[0];
   fTF3SCI_R = (bigrips_F3R+rand05())*fCh2nsPlastic[1];
   fTF7SCI_L = (bigrips_F7L+rand05())*fCh2nsPlastic[2];
   fTF7SCI_R = (bigrips_F7R+rand05())*fCh2nsPlastic[3];

   fTOF_F3F7 = ( (fTF7SCI_L + fTF7SCI_R) - (fTF3SCI_L + fTF3SCI_R) )/2. + fTOFOffset[0];

   Double_t L1 = fTOFLength[1];
   Double_t L2 = fTOFLength[2];
   Double_t TOF = fTOF_F3F7/1000.; // 10^-6 s

   //This should be the ratio of measured Brhos. 
   //Here we assume BrhoReal[0]/BrhoReal[1] = BrhoSet[0]/BrhoSet[1]. 
   Double_t Ratio = fBrhoSet[0]/fBrhoSet[1]; 
   Double_t Ratio2 = Ratio*Ratio;

   fBeta[0] = (c*TOF*L1 
         + L2*TMath::Sqrt(L1*L1 *(1-Ratio2)+ Ratio2*(Ratio2-1)*L2*L2 + Ratio2*c*c*TOF*TOF))
      /(c*c*TOF*TOF + L2*L2 * (Ratio2 -1));

   Ratio = fBrhoSet[1]/fBrhoSet[0]; 
   Ratio2 = Ratio*Ratio;
   fBeta[1] = (c*TOF*L2 
         + L1*TMath::Sqrt(L2*L2 *(1-Ratio2)+ Ratio2*(Ratio2-1)*L1*L1 + Ratio2*c*c*TOF*TOF))
      /(c*c*TOF*TOF + L1*L1 * (Ratio2 -1));

   fGamma[0] = 1./TMath::Sqrt(1-fBeta[0]*fBeta[0]);
   fGamma[1] = 1./TMath::Sqrt(1-fBeta[1]*fBeta[1]);

   fBrhoReal[0] = fBrhoSet[0] * (1+fDelta[0]/100.);
   fAoQ[0] = fBrhoReal[0]*c/fBeta[0]/fGamma[0]/amu + fAoQ_shift ;

   Double_t ionpair = 4866.; 
   Double_t de_v = TMath::Log(ionpair*fBeta[1]*fBeta[1]) - TMath::Log((1-fBeta[1]*fBeta[1])) - fBeta[1]*fBeta[1];

   fZet[0] = fZetCoef[1][0]*TMath::Sqrt(dE/de_v)*fBeta[1] 
      + fZetCoef[1][1] + fZed_shift;

   bigrips_F3PPAC1_X = fX[0];
   bigrips_F3PPAC2_X = fX[1];
   bigrips_F5PPAC1_X = fX[2];
   bigrips_F5PPAC2_X = fX[3];

   bigrips_F3_X = fX_FP[0];
   bigrips_F3_A = atan(fA_FP[0])*1000;
   bigrips_F5_X = fX_FP[1];
   bigrips_F5_A = atan(fA_FP[1])*1000;

   bigrips_F3PPAC1_TDiffX = fTDiff[0][0];
   bigrips_F3PPAC2_TDiffX = fTDiff[1][0];
   bigrips_F5PPAC1_TDiffX = fTDiff[2][0];
   bigrips_F5PPAC2_TDiffX = fTDiff[3][0];

   bigrips_dERaw = dERaw;
   bigrips_dE = dE;

   pid_Delta_F3F5 = fDelta[0];
   pid_TOF_F3F7 = fTOF_F3F7;
   pid_Beta_F3F5 = fBeta[0];
   pid_Beta_F5F7 = fBeta[1];
   pid_AoQ_F3F5 = fAoQ[0];
   pid_Zet_F11 = fZet[0];
}

void wasabi::pid_reset(){
   bigrips_F3PPAC1_TDiffX = -100000;
   bigrips_F3PPAC2_TDiffX = -100000;
   bigrips_F5PPAC1_TDiffX = -100000;
   bigrips_F5PPAC2_TDiffX = -100000;
   bigrips_F3PPAC1_X = -100000;
   bigrips_F3PPAC2_X = -100000;
   bigrips_F5PPAC1_X = -100000;
   bigrips_F5PPAC2_X = -100000;
   bigrips_F3_X = -100000;
   bigrips_F3_A = -100000;
   bigrips_F5_X = -100000;
   bigrips_F5_A = -100000;
   bigrips_dERaw = -100000;
   bigrips_dE = -100000;
   pid_Delta_F3F5 = -100000;
   pid_TOF_F3F7 = -100000;
   pid_Beta_F3F5 = -100000;
   pid_Beta_F5F7 = -100000;
   pid_AoQ_F3F5 = -100000;
   pid_Zet_F11 = -100000;
   for(int i=0; i<6; i++){
      fTOFLength[i]=-100000;
      fDelta[i]=-100000;
   }
   for(int i=0; i<8; i++){
      fBeta[i]=-100000;
      fDelta[i]=-100000;
   }
   for(int i=0; i<12; i++){
      fBrhoSet[i]=-100000;
      fBrhoReal[i]=-100000;
      fAoQ[i]=-100000;
   }
   for(int i=0; i<4; i++){
      fZet[i]=-100000;
      for(int j=0; j<2; j++){
         fZetCoef[i][j]=-100000;
      }
   }
   for(int i=0; i<10; i++){
      fTX1[i]=-100000;
      fTX2[i]=-100000;
      fTY1[i]=-100000;
      fTY2[i]=-100000;
      fA[i]=-100000;
      fX[i]=-100000;
      fX_FP[i]=-100000;
      fA_FP[i]=-100000;
      for(int j=0; j<2; j++){
         fTSum[i][j]=-100000;
         fTDiff[i][j]=-100000;
      }
   }
   fTF3SCI_L = -100000;
   fTF3SCI_R = -100000;
   fTF7SCI_L = -100000;
   fTF7SCI_R = -100000;
   fTOF_F3F7 = -100000;
}

void wasabi::CopyToTArt(TArtWASABI *w){

  (*w).IF_BETA=IF_BETA;
  (*w).IF_ION=IF_ION;
  (*w).numdssd=numdssd;
  (*w).numadc=numadc;
  (*w).numtdc=numtdc;
  (*w).dstrx=dstrx;
  (*w).dstry=dstry;

  for(int i=0;i<32;i++) (*w).scal[i]=scal[i];
  for(int i=0;i<numdssd;i++){
    for(int j=0;j<60;j++){
       //cout<<dssd_E_X[i][j]<<endl;
      (*w).dssd_E_X[i][j]=dssd_E_X[i][j];
      (*w).dssd_ch_X[i][j]=dssd_ch_X[i][j];
      (*w).dssd_id_X[i][j]=dssd_id_X[i][j];
      for(int k=0;k<3;k++)
	(*w).dssd_T_X[i][j][k]=dssd_T_X[i][j][k];
    }
    for(int j=0;j<40;j++){
      (*w).dssd_E_Y[i][j]=dssd_E_Y[i][j];
      (*w).dssd_ch_Y[i][j]=dssd_ch_Y[i][j];
      (*w).dssd_id_Y[i][j]=dssd_id_Y[i][j];
      for(int k=0;k<3;k++)
	(*w).dssd_T_Y[i][j][k]=dssd_T_Y[i][j][k];
    }
    (*w).dssd_X[i]=dssd_X[i];
    (*w).dssd_Y[i]=dssd_Y[i];
  }


  (*w).dssd_Z=dssd_Z;
  

  for(int i=0;i<numadc;i++) 
    for(int j=0;j<32;j++)
      (*w).ADC[i][j]=ADC[i][j];
  for(int i=0;i<numtdc;i++) 
    for(int j=0;j<128;j++) 
      for(int k=0;k<3;k++)
	(*w).TDC[i][j][k]=TDC[i][j][k];

  
  for(int i=0;i<64;i++){
    for(int j=0;j<3;j++)
      (*w).dssd_fastout[i][j]=dssd_fastout[i][j];
  }
    
  for(int i=0;i<numdssd;i++)  
    for(int j=0;j<100;j++){
      (*w).DSSD_E[i][j]=DSSD_E[i][j];
      for(int k=0;k<3;k++)  
	(*w).DSSD_T[i][j][k]=DSSD_T[i][j][k];
    }

  (*w).bigrips_F3PPAC1X1=bigrips_F3PPAC1X1;
  (*w).bigrips_F3PPAC1X2=bigrips_F3PPAC1X2;
  (*w).bigrips_F3PPAC2X1=bigrips_F3PPAC2X1;
  (*w).bigrips_F3PPAC2X2=bigrips_F3PPAC2X2;
  (*w).bigrips_F5PPAC1X1=bigrips_F5PPAC1X1;
  (*w).bigrips_F5PPAC1X2=bigrips_F5PPAC1X2;
  (*w).bigrips_F5PPAC2X1=bigrips_F5PPAC2X1;
  (*w).bigrips_F5PPAC2X2=bigrips_F5PPAC2X2;
  (*w).bigrips_F3L=bigrips_F3L;
  (*w).bigrips_F3R=bigrips_F3R;
  (*w).bigrips_F7L=bigrips_F7L;
  (*w).bigrips_F7R=bigrips_F7R;
  (*w).bigrips_F11L=bigrips_F11L;
  (*w).bigrips_F11R=bigrips_F11R;
  (*w).bigrips_IC1e=bigrips_ICe[0];
  (*w).bigrips_IC2e=bigrips_ICe[1];
  (*w).bigrips_IC3e=bigrips_ICe[2];
  (*w).bigrips_IC4e=bigrips_ICe[3];
  (*w).bigrips_IC5e=bigrips_ICe[4];
  (*w).bigrips_IC6e=bigrips_ICe[5];
  
  (*w).Qbeta1_E=Qbeta_E;
  (*w).Qbeta_T=Qbeta_T;
  (*w).Qveto_E=Qveto_E;
  (*w).Qveto_T=Qveto_T;
    
  (*w).NaI1_E=NaI_E[0];
  (*w).NaI2_E=NaI_E[1];
  (*w).NaI3_E=NaI_E[2];
  (*w).NaI1_T=NaI_T[0];
  (*w).NaI2_T=NaI_T[1];
  (*w).NaI3_T=NaI_T[2];
    
  (*w).bigrips_F3PPAC1_TDiffX=bigrips_F3PPAC1_TDiffX;
  (*w).bigrips_F3PPAC2_TDiffX=bigrips_F3PPAC2_TDiffX;
  (*w).bigrips_F5PPAC1_TDiffX=bigrips_F5PPAC1_TDiffX;
  (*w).bigrips_F5PPAC2_TDiffX=bigrips_F5PPAC2_TDiffX;
  (*w).bigrips_F3PPAC1_X=bigrips_F3PPAC1_X;
  (*w).bigrips_F3PPAC2_X=bigrips_F3PPAC2_X;
  (*w).bigrips_F5PPAC1_X=bigrips_F5PPAC1_X;
  (*w).bigrips_F5PPAC2_X=bigrips_F5PPAC2_X;
  (*w).bigrips_F3_X=bigrips_F3_X;
  (*w).bigrips_F3_A=bigrips_F3_A;
  (*w).bigrips_F5_X=bigrips_F5_X;
  (*w).bigrips_F5_A=bigrips_F5_A;
  (*w).bigrips_dERaw=bigrips_dERaw;
  (*w).bigrips_dE=bigrips_dE;
  
  (*w).pid_Delta_F3F5=pid_Delta_F3F5;
  (*w).pid_TOF_F3F7=pid_TOF_F3F7;
  (*w).pid_Beta_F3F5=pid_Beta_F3F5;
  (*w).pid_Beta_F5F7=pid_Beta_F5F7;
  (*w).pid_AoQ_F3F5=pid_AoQ_F3F5;
  (*w).pid_Zet_F11=pid_Zet_F11;

}

#endif // #ifdef dssd_cxx
