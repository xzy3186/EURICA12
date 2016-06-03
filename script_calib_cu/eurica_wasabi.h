#ifndef eurica_wasabi_h
#define eurica_wasabi_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TObject.h>
#include <TNamed.h>
#include "eurica.h"
#include "wasabi_treeinfo.h"

class eurica_wasabi {
   public :
      TTree          *fChain;   //!pointer to the analyzed TTree or TChain
      Int_t           fCurrent; //!current Tree number in a TChain

      Long64_t        ts;
      Int_t           IF_BETA;
      Int_t           IF_ION;
      Int_t           numdssd;
      Int_t           numtdc;
      Int_t           numadc;
      Int_t           dstrx;
      Int_t           dstry;
      Int_t           scal[32];

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
      Int_t           Qveto_E;
      Int_t           Qveto_T;
      Int_t           Qbeta_T;

      Int_t           NaI_E[3];
      Int_t           NaI_T[3];

      Double_t        pid_Delta_F3F5;
      Double_t        pid_TOF_F3F7;
      Double_t        pid_Beta_F3F5;
      Double_t        pid_Beta_F5F7;
      Double_t        pid_AoQ_F3F5;
      Double_t        pid_Zet_F11;

      Int_t           ADC[NumADC][32];
      Int_t           TDC[NumTDC][128][3];
      Int_t           dssd_E_X[NumDSSD][60];
      Int_t           dssd_ch_X[NumDSSD][60];
      Int_t           dssd_id_X[NumDSSD][60];
      Int_t           dssd_T_X[NumDSSD][60][3];
      Int_t           dssd_E_Y[NumDSSD][40];
      Int_t           dssd_ch_Y[NumDSSD][40];
      Int_t           dssd_id_Y[NumDSSD][40];
      Int_t           dssd_T_Y[NumDSSD][40][3];
      Int_t           dssd_X[NumDSSD];
      Int_t           dssd_Y[NumDSSD];
      Int_t           dssd_Z;
      Int_t           dssd_fireX[NumDSSD];
      Int_t           dssd_fireY[NumDSSD];
      Int_t	          dssd_fastout[64][3];

      Int_t           gc_hit;
      Int_t           gc_ch[kMaxGeCluster];   //[GeCluster_]
      UInt_t          gc_DGFe[kMaxGeCluster];   //[GeCluster_]
      UInt_t          gc_DGFt[kMaxGeCluster];   //[GeCluster_]
      UInt_t          gc_TDCs[kMaxGeCluster];   //[GeCluster_]
      UInt_t          gc_TDCl[kMaxGeCluster];   //[GeCluster_]
      Double_t        gc_E[kMaxGeCluster];   //[GeCluster_]
      Double_t        gc_T[kMaxGeCluster];   //[GeCluster_]
      Int_t           ab_hit;
      Int_t           ab_ch[kMaxGeAddback];   //[GeAddback_]
      UInt_t          ab_DGFe[kMaxGeAddback];   //[GeAddback_]
      UInt_t          ab_DGFt[kMaxGeAddback];   //[GeAddback_]
      UInt_t          ab_TDCs[kMaxGeAddback];   //[GeAddback_]
      UInt_t          ab_TDCl[kMaxGeAddback];   //[GeAddback_]
      Double_t        ab_E[kMaxGeAddback];   //[GeAddback_]
      Double_t        ab_T[kMaxGeAddback];   //[GeAddback_]

      TBranch        *b_ts;   //!
      TBranch        *b_IF_BETA;   //!
      TBranch        *b_IF_ION;   //!
      TBranch        *b_numdssd;
      TBranch        *b_numadc;
      TBranch        *b_numtdc;
      TBranch        *b_dstrx;
      TBranch        *b_dstry;
      TBranch        *b_scal;

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

      TBranch        *b_Qbeta_E;
      TBranch        *b_Qbeta_T;
      TBranch        *b_Qveto_E;
      TBranch        *b_Qveto_T;

      TBranch        *b_NaI_E;
      TBranch        *b_NaI_T;

      TBranch        *b_pid_Delta_F3F5;
      TBranch        *b_pid_TOF_F3F7;
      TBranch        *b_pid_Beta_F3F5;
      TBranch        *b_pid_Beta_F5F7;
      TBranch        *b_pid_AoQ_F3F5;
      TBranch        *b_pid_Zet_F11;

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

      eurica_wasabi();
      virtual void     GetTree(char* filename,TTree *tree=0);
      virtual Int_t    Cut(Long64_t entry);
      virtual Int_t    GetEntry(Long64_t entry);
      virtual Long64_t LoadTree(Long64_t entry);
      virtual void     Init(TTree *tree);
      virtual Bool_t   Notify();
      virtual void     Show(Long64_t entry = -1);
      virtual void     GetTsEntry(std::map<Long64_t,Long64_t> &mts);
      virtual void     TreeBranch(TTree *tree);
      virtual void     BetaGetPos(Int_t &mult, std::map <Int_t,vector <pair<pair<pair<Int_t,Int_t>,pair<Float_t,Int_t> >,pair<pair<Int_t,Int_t>,pair<Float_t,Int_t> > > > > &beta_event);
      /******** for sync tree **************/
      virtual void     SyncSi(wasabi &DSSD);
      virtual void     SyncTS(wasabi &DSSD);
      virtual void     SyncQbeta(wasabi &DSSD);
      virtual void     SyncBigRIPS(wasabi &DSSD);
      virtual void     SyncPID(wasabi &DSSD);
      virtual void     SyncNaI(wasabi &DSSD);
      virtual void     SyncGamma(eurica &gamma);
      virtual void     ResetGe();
};

eurica_wasabi::eurica_wasabi(){
}

void eurica_wasabi::GetTree(char *filename, TTree *tree)
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

Int_t eurica_wasabi::GetEntry(Long64_t entry)
{
   // Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t eurica_wasabi::LoadTree(Long64_t entry)
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

void eurica_wasabi::Init(TTree *tree)
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
   fChain->SetBranchAddress("IF_BETA", &IF_BETA, &b_IF_BETA);
   fChain->SetBranchAddress("IF_ION", &IF_ION, &b_IF_ION);
   fChain->SetBranchAddress("numdssd", &numdssd, &b_numdssd);
   fChain->SetBranchAddress("numtdc", &numtdc, &b_numtdc);
   fChain->SetBranchAddress("numadc", &numadc, &b_numadc);
   fChain->SetBranchAddress("dstrx", &dstrx, &b_dstrx);
   fChain->SetBranchAddress("dstry", &dstry, &b_dstry);
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
   fChain->SetBranchAddress("dssd_fireX", dssd_fireX, &b_dssd_fireX);
   fChain->SetBranchAddress("dssd_fireY", dssd_fireY, &b_dssd_fireY);
   fChain->SetBranchAddress("dssd_fastout", dssd_fastout, &b_dssd_fastout);

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

   fChain->SetBranchAddress("pid_Delta_F3F5",&pid_Delta_F3F5,&b_pid_Delta_F3F5);
   fChain->SetBranchAddress("pid_TOF_F3F7",&pid_TOF_F3F7,&b_pid_TOF_F3F7);
   fChain->SetBranchAddress("pid_Beta_F3F5",&pid_Beta_F3F5,&b_pid_Beta_F3F5);
   fChain->SetBranchAddress("pid_Beta_F5F7",&pid_Beta_F5F7,&b_pid_Beta_F5F7);
   fChain->SetBranchAddress("pid_AoQ_F3F5",&pid_AoQ_F3F5,&b_pid_AoQ_F3F5);
   fChain->SetBranchAddress("pid_Zet_F11", &pid_Zet_F11,&b_pid_Zet_F11);

   Notify();
}

Bool_t eurica_wasabi::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void eurica_wasabi::Show(Long64_t entry)
{
   // Print contents of entry.
   // If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t eurica_wasabi::Cut(Long64_t entry)
{
   // This function may be called from Loop.
   // returns  1 if entry is accepted.
   // returns -1 otherwise.
   return 1;
}

void eurica_wasabi::GetTsEntry(std::map<Long64_t,Long64_t> &mts)
{
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
   }
}

void eurica_wasabi::BetaGetPos(Int_t &mult, std::map<Int_t,vector<pair<pair<pair<Int_t,Int_t>,pair<Float_t,Int_t> >,pair<pair<Int_t,Int_t>,pair<Float_t,Int_t> > > > > &beta_event)
{//mult is the multiplicity of beta event. map(z,vector(pair(x,y))) restore position
   //information of beta decay.
   Int_t beta_x1[60], beta_x2[60], beta_ex[60], beta_nhitx;
   Int_t beta_y1[40], beta_y2[40], beta_ey[60], beta_nhity;
   Int_t ch_last, x, y;
   Int_t x1, x2, ex, y1, y2, ey;
   Float_t x0, y0, beta_x[60], beta_y[40];
   mult=0;
   for(Int_t z=0; z<NumDSSD; z++){
      beta_nhitx = -1;
      ch_last = -2;
      for(int i=0; i<60; i++){
         beta_x[i] = 0;
         beta_ex[i] = 0;
      }
      for(x=1; x<NumStrX-1; x++){
         if(dssd_T_X[z][x][0]<3000 && dssd_T_X[z][x][0]>-4000 && dssd_E_X[z][x]>50){
            if(x!=ch_last+1){
               if(beta_nhitx>=0){
                  beta_x[beta_nhitx] = beta_x[beta_nhitx]/beta_ex[beta_nhitx];
               }
               beta_nhitx ++;
               beta_ex[beta_nhitx] = dssd_E_X[z][x];
               beta_x[beta_nhitx] = x*dssd_E_X[z][x];
               beta_x1[beta_nhitx] = x;
               beta_x2[beta_nhitx] = x;
               ch_last = x;
            }else{
               beta_ex[beta_nhitx] = beta_ex[beta_nhitx] + dssd_E_X[z][x];
               beta_x[beta_nhitx] = beta_x[beta_nhitx] + x*dssd_E_X[z][x];
               beta_x2[beta_nhitx] = x;
               ch_last ++;
            }
         }
      }
      if(beta_nhitx>=0){
         beta_x[beta_nhitx] = beta_x[beta_nhitx]/beta_ex[beta_nhitx];
      }
      beta_nhity = -1;
      ch_last = -2;
      for(int i=0; i<40; i++){
         beta_y[i] = 0;
         beta_ey[i] = 0;
      }
      for(y=1; y<NumStrY-1; y++){
         if(dssd_T_Y[z][y][0]<3000 && dssd_T_Y[z][y][0]>-4000 && dssd_E_Y[z][y]>50){
            if(y!=ch_last+1){
               if(beta_nhity>=0){
                  beta_y[beta_nhity] = beta_y[beta_nhity]/beta_ey[beta_nhity];
               }
               beta_nhity ++;
               beta_ey[beta_nhity] = dssd_E_Y[z][y];
               beta_y[beta_nhity] = y*dssd_E_Y[z][y];
               beta_y1[beta_nhity] = y;
               beta_y2[beta_nhity] = y;
               ch_last = y;
            }else{
               beta_ey[beta_nhity] = beta_ey[beta_nhity] + dssd_E_Y[z][y];
               beta_y[beta_nhity] = beta_y[beta_nhity] + y*dssd_E_Y[z][y];
               beta_y2[beta_nhity] = y;
               ch_last ++;
            }
         }
      }
      if(beta_nhity>=0){
         beta_y[beta_nhity] = beta_y[beta_nhity]/beta_ey[beta_nhity];
      }

      vector<pair<pair<pair<Int_t,Int_t>,pair<Float_t,Int_t> >,pair<pair<Int_t,Int_t>,pair<Float_t,Int_t> > > > beta_dssd;
      for(int i=0; i<beta_nhitx+1; i++){
         for(int j=0; j<beta_nhity+1; j++){
            x0 = beta_x[i];
            x1 = beta_x1[i];
            x2 = beta_x2[i];
            ex = beta_ex[i];
            if(z>=4){
               ex = ex/2;
            }
            y0 = beta_y[j];
            y1 = beta_y1[j];
            y2 = beta_y2[j];
            ey = beta_ey[j];
            Int_t fill = 1;
            if(beta_nhitx==beta_nhity && (ey>1.1*ex+200 || ey<0.9*ex-200)){
               fill = 0;
            }
            if(fill==1)
            {
               mult++;
               //cout<<"x1 = "<<beta_x1[i]<<", x0 = "<<beta_x[i]<<", x2 = "<<beta_x2[i]<<endl;
               //beta_dssd.push_back(pair<pair<Int_t,Int_t>,pair<Int_t,Int_t> > ((x,ex),(y,ey) ) );
               beta_dssd.push_back(make_pair(make_pair(make_pair(x1,x2),make_pair(x0,ex) ),make_pair(make_pair(y1,y2),make_pair(y0,ey) ) ) );
            }
         }
      }
      if(beta_dssd.size()>0){
         beta_event[z]=beta_dssd;
      }
   }
}

void eurica_wasabi::TreeBranch(TTree *tree)
{
   numdssd = NumDSSD;
   numadc = NumADC;
   numtdc = NumTDC;
   dstrx = NumDSSD*NumStrX;
   dstry = NumDSSD*NumStrY;
   tree->Branch("ts",&ts,"ts/L");
   tree->Branch("numdssd",&numdssd,"numdssd/I");
   tree->Branch("numadc",&numadc,"numadc/I");
   tree->Branch("numtdc",&numtdc,"numtdc/I");
   tree->Branch("dstrx",&dstrx,"dstrx/I");
   tree->Branch("dstry",&dstry,"dstry/I");
   tree->Branch("IF_BETA",&IF_BETA,"IF_BETA/I");
   tree->Branch("IF_ION",&IF_ION,"IF_ION/I");

   tree->Branch("scal",scal,"scal[32]/I");
   tree->Branch("ADC",ADC,"ADC[numadc][32]/I");
   tree->Branch("TDC",TDC,"TDC[numtdc][128][3]/I");
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
   tree->Branch("dssd_fastout",dssd_fastout,"dssd_fastout[64][3]/I");

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

   tree->Branch("pid_Delta_F3F5",&pid_Delta_F3F5,"pid_Delta_F3F5/D");
   tree->Branch("pid_TOF_F3F7",&pid_TOF_F3F7,"pid_TOF_F3F7/D");
   tree->Branch("pid_Beta_F3F5",&pid_Beta_F3F5,"pid_Beta_F3F5/D");
   tree->Branch("pid_Beta_F5F7",&pid_Beta_F5F7,"pid_Beta_F5F7/D");
   tree->Branch("pid_AoQ_F3F5",&pid_AoQ_F3F5,"pid_AoQ_F3F5/D");
   tree->Branch("pid_Zet_F11", &pid_Zet_F11,"pid_Zet_F11/D");

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
}

void eurica_wasabi::SyncSi(wasabi &DSSD){
   memcpy(ADC, DSSD.ADC, sizeof(DSSD.ADC));
   memcpy(TDC, DSSD.TDC, sizeof(DSSD.TDC));
   memcpy(dssd_E_X, DSSD.dssd_E_X, sizeof(DSSD.dssd_E_X));
   memcpy(dssd_ch_X, DSSD.dssd_ch_X, sizeof(DSSD.dssd_ch_X));
   memcpy(dssd_id_X, DSSD.dssd_id_X, sizeof(DSSD.dssd_id_X));
   memcpy(dssd_E_Y, DSSD.dssd_E_Y, sizeof(DSSD.dssd_E_Y));
   memcpy(dssd_ch_Y, DSSD.dssd_ch_Y, sizeof(DSSD.dssd_ch_Y));
   memcpy(dssd_id_Y, DSSD.dssd_id_Y, sizeof(DSSD.dssd_id_Y));
   memcpy(dssd_T_X, DSSD.dssd_T_X, sizeof(DSSD.dssd_T_X));
   memcpy(dssd_T_Y, DSSD.dssd_T_Y, sizeof(DSSD.dssd_T_Y));
   memcpy(dssd_X, DSSD.dssd_X, sizeof(DSSD.dssd_X));
   memcpy(dssd_Y, DSSD.dssd_Y, sizeof(DSSD.dssd_Y));
   memcpy(dssd_fireX, DSSD.dssd_fireX, sizeof(DSSD.dssd_fireX));
   memcpy(dssd_fireY, DSSD.dssd_fireY, sizeof(DSSD.dssd_fireY));
   dssd_Z = DSSD.dssd_Z;
   IF_BETA = DSSD.IF_BETA;
   IF_ION = DSSD.IF_ION;
}

void eurica_wasabi::SyncTS(wasabi &DSSD){
   ts = DSSD.EventInfo_timestamp[0];
}

void eurica_wasabi::SyncQbeta(wasabi &DSSD){
   Qbeta_E = DSSD.Qbeta_E;
   Qbeta_T = DSSD.Qbeta_T;
   Qveto_E = DSSD.Qveto_E;
   Qveto_T = DSSD.Qveto_T;
   memcpy(dssd_fastout, DSSD.dssd_fastout, sizeof(DSSD.dssd_fastout));
}

void eurica_wasabi::SyncBigRIPS(wasabi &DSSD){
   bigrips_F3PPAC1X1 = DSSD.bigrips_F3PPAC1X1;
   bigrips_F3PPAC1X2 = DSSD.bigrips_F3PPAC1X2;
   bigrips_F3PPAC2X1 = DSSD.bigrips_F3PPAC2X1;
   bigrips_F3PPAC2X2 = DSSD.bigrips_F3PPAC2X2;
   bigrips_F5PPAC1X1 = DSSD.bigrips_F5PPAC1X1;
   bigrips_F5PPAC1X2 = DSSD.bigrips_F5PPAC1X2;
   bigrips_F5PPAC2X1 = DSSD.bigrips_F5PPAC2X1;
   bigrips_F5PPAC2X2 = DSSD.bigrips_F5PPAC2X2;
   bigrips_F3L = DSSD.bigrips_F3L;
   bigrips_F3R = DSSD.bigrips_F3R;
   bigrips_F7L = DSSD.bigrips_F7L;
   bigrips_F7R = DSSD.bigrips_F7R;
   bigrips_F11L = DSSD.bigrips_F11L;
   bigrips_F11R = DSSD.bigrips_F11R;
   memcpy(bigrips_ICe, DSSD.bigrips_ICe, sizeof(DSSD.bigrips_ICe));
}

void eurica_wasabi::SyncPID(wasabi &DSSD){
   pid_Delta_F3F5 = DSSD.pid_Delta_F3F5;
   pid_TOF_F3F7 = DSSD.pid_TOF_F3F7;
   pid_Beta_F3F5 = DSSD.pid_Beta_F3F5;
   pid_Beta_F5F7 = DSSD.pid_Beta_F5F7;
   pid_AoQ_F3F5 = DSSD.pid_AoQ_F3F5;
   pid_Zet_F11 = DSSD.pid_Zet_F11;
}

void eurica_wasabi::SyncNaI(wasabi &DSSD){
   memcpy(NaI_E, DSSD.NaI_E, sizeof(DSSD.NaI_E));
   memcpy(NaI_T, DSSD.NaI_T, sizeof(DSSD.NaI_T));
}

void eurica_wasabi::SyncGamma(eurica &gamma){
   gc_hit = gamma.GeCluster_;
   memcpy(gc_ch, gamma.GeCluster_channel, sizeof(gamma.GeCluster_channel));
   memcpy(gc_DGFe, gamma.GeCluster_fADCe, sizeof(gamma.GeCluster_fADCe));
   memcpy(gc_DGFt, gamma.GeCluster_fADCt, sizeof(gamma.GeCluster_fADCt));
   memcpy(gc_TDCs, gamma.GeCluster_fTDCs, sizeof(gamma.GeCluster_fTDCs));
   memcpy(gc_TDCl, gamma.GeCluster_fTDCl, sizeof(gamma.GeCluster_fTDCl));
   memcpy(gc_E, gamma.GeCluster_fEnergy, sizeof(gamma.GeCluster_fEnergy));
   memcpy(gc_T, gamma.GeCluster_fTime, sizeof(gamma.GeCluster_fTime));
   ab_hit = gamma.GeAddback_;
   memcpy(ab_ch, gamma.GeAddback_channel, sizeof(gamma.GeAddback_channel));
   memcpy(ab_DGFe, gamma.GeAddback_fADCe, sizeof(gamma.GeAddback_fADCe));
   memcpy(ab_DGFt, gamma.GeAddback_fADCt, sizeof(gamma.GeAddback_fADCt));
   memcpy(ab_TDCs, gamma.GeAddback_fTDCs, sizeof(gamma.GeAddback_fTDCs));
   memcpy(ab_TDCl, gamma.GeAddback_fTDCl, sizeof(gamma.GeAddback_fTDCl));
   memcpy(ab_E, gamma.GeAddback_fEnergy, sizeof(gamma.GeAddback_fEnergy));
   memcpy(ab_T, gamma.GeAddback_fTime, sizeof(gamma.GeAddback_fTime));
}

void eurica_wasabi::ResetGe(){
   gc_hit=0;
   ab_hit=0;
}

#endif // #ifdef dssdgamma_cxx
