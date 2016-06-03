/************************************
combine root files for decay and Go4,
for the calibration, beta delayed
decay, and isomeric decay.
************************************/

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
#include<utility>
#include<sstream>
#include<cmath>
#include<TProfile.h>
#include<TXMLNode.h>

#include"TFile.h"
#include"TSystem.h"
#include"TTree.h"
#include"TROOT.h"
#include"TString.h"
#include"TRandom.h"

#include<signal.h>

//#include"TArtEventStore.hh"
#include"decay_ggmatrix.h"

using namespace std;

int main(int argc, char* argv[]){

   if(argc<2){
      cout<<"USAGE: MakeGGMatrixDecay #DECAYRUN"<<endl;
      return 0;
   }

   int runD = atoi(argv[1]);
   char decayfile[128];
   char outfile[128];


   Int_t index;
   Int_t run;

   Int_t ion_z;
   Int_t ion_x;
   Int_t ion_y;
   Int_t ion_tx;
   Int_t ion_ty;
   Double_t pid_Delta_F3F5;
   Double_t pid_TOF_F3F7;
   Double_t pid_Beta_F3F5;
   Double_t pid_Beta_F5F7;
   Double_t pid_AoQ_F3F5;
   Double_t pid_Zet_F11;
   Double_t bigrips_zet;
   Double_t bigrips_aoq;
   Double_t bigrips_beta;

   Double_t zet;
   Double_t aoq;
   Double_t mass;
   Int_t Zed;
   Int_t Mass;

   Long64_t t[100];
   Int_t z[100];
   Int_t x[100];
   Int_t y[100];
   Int_t ex[100];
   Int_t ey[100];
   Int_t deltaz[100];
   Double_t deltaxy[100];
   Int_t dssd_E[100];
   Int_t dssd_fire[100][8];
   Int_t dssd_ex[100][8];
   Int_t dssd_ey[100][8];
   Int_t NaI_E[100][3];
   Int_t NaI_T[100][3];
   Int_t Qbeta_E[100];
   Int_t Qbeta_T[100];
   Int_t Qveto_E[100];
   Int_t Qveto_T[100];

   Int_t gc_matrix;
   Double_t gc1_E[40000];//(beta_index_max(10) X gc_hit_max(20))^2
   Double_t gc2_E[40000];
   Double_t gc1_T[40000];
   Double_t gc2_T[40000];
   Double_t gc1_dt[40000];
   Double_t gc2_dt[40000];
   Int_t gc_hit[100];
   Int_t gc_ch[100][84];   //[gc_hit]
   Int_t gc_DGFe[100][84];   //[gc_hit]
   Int_t gc_DGFt[100][84];   //[gc_hit]
   Int_t gc_TDCs[100][84];   //[gc_hit]
   Int_t gc_TDCl[100][84];   //[gc_hit]
   Double_t gc_E[100][84];   //[gc_hit]
   Double_t gc_T[100][84];   //[gc_hit]

   Int_t ab_matrix;
   Double_t ab1_E[40000];
   Double_t ab2_E[40000];
   Double_t ab1_T[40000];
   Double_t ab2_T[40000];
   Double_t ab1_dt[40000];
   Double_t ab2_dt[40000];
   Int_t ab_hit[100];
   Int_t ab_ch[100][84];   //[ab_hit]
   Int_t ab_DGFe[100][84];   //[ab_hit]
   Int_t ab_DGFt[100][84];   //[ab_hit]
   Int_t ab_TDCs[100][84];   //[ab_hit]
   Int_t ab_TDCl[100][84];   //[ab_hit]
   Double_t ab_E[100][84];   //[ab_hit]
   Double_t ab_T[100][84];   //[ab_hit]

   sprintf(decayfile,"../root/sistopper/ni78test/decay_new%04d.root",runD);
   //sprintf(decayfile,"go4.root");
   sprintf(outfile,"../root/sistopper/ni78test/DECAY_GGMatrix%04d.root",runD);

   decay_ggmatrix ggdecay(decayfile);

   Long64_t dEntry, dEntryMAX;  //entry for decay
   TFile *rootfile = new TFile(outfile,"RECREATE");

   TTree *decay = new TTree("decay","decay");

   decay->Branch("run",&run,"run/I");
   decay->Branch("ion_z",&ion_z,"ion_z/I");
   decay->Branch("ion_x",&ion_x,"ion_x/I");
   decay->Branch("ion_y",&ion_y,"ion_y/I");
   decay->Branch("ion_tx",&ion_tx,"ion_tx/I");
   decay->Branch("ion_ty",&ion_ty,"ion_ty/I");

   decay->Branch("pid_Delta_F3F5",&pid_Delta_F3F5,"pid_Delta_F3F5/D");
   decay->Branch("pid_TOF_F3F7",&pid_TOF_F3F7,"pid_TOF_F3F7/D");
   decay->Branch("pid_Beta_F3F5",&pid_Beta_F3F5,"pid_Beta_F3F5/D");
   decay->Branch("pid_Beta_F5F7",&pid_Beta_F5F7,"pid_Beta_F5F7/D");
   decay->Branch("pid_AoQ_F3F5",&pid_AoQ_F3F5,"pid_AoQ_F3F5/D");
   decay->Branch("pid_Zet_F11", &pid_Zet_F11,"pid_Zet_F11/D");
   decay->Branch("bigrips_zet", &bigrips_zet,"bigrips_zet/D");
   decay->Branch("bigrips_aoq", &bigrips_aoq,"bigrips_aoq/D");
   decay->Branch("bigrips_beta", &bigrips_beta,"bigrips_beta/D");

   decay->Branch("zet", &zet,"zet/D");
   decay->Branch("aoq", &aoq,"aoq/D");
   decay->Branch("mass", &mass,"mass/D");
   decay->Branch("Zed", &Zed,"Zed/I");
   decay->Branch("Mass", &Mass,"Mass/I");

   decay->Branch("index",&index,"index/I");
   decay->Branch("t",t,"t[index]/L");
   decay->Branch("z",z,"z[index]/I");
   decay->Branch("x",x,"x[index]/I");
   decay->Branch("y",y,"y[index]/I");
   decay->Branch("ex",ex,"ex[index]/I");
   decay->Branch("ey",ey,"ey[index]/I");
   decay->Branch("deltaz",deltaz,"deltaz[index]/I");
   decay->Branch("deltaxy",deltaxy,"deltaxy[index]/D");
   decay->Branch("dssd_E",dssd_E,"dssd_E[index]/I");
   decay->Branch("dssd_fire",dssd_fire,"dssd_fire[index][8]/I");
   decay->Branch("dssd_ex",dssd_ex,"dssd_ex[index][8]/I");
   decay->Branch("dssd_ey",dssd_ey,"dssd_ey[index][8]/I");

   decay->Branch("NaI_E",NaI_E,"NaI_E[index][3]/I");
   decay->Branch("NaI_T",NaI_T,"NaI_T[index][3]/I");
   decay->Branch("Qbeta_E",Qbeta_E,"Qbeta_E[index]/I");
   decay->Branch("Qbeta_T",Qbeta_T,"Qbeta_T[index]/I");
   decay->Branch("Qveto_E",Qveto_E,"Qveto_E[index]/I");
   decay->Branch("Qveto_T",Qveto_T,"Qveto_T[index]/I");

   decay->Branch("ab_hit",ab_hit,"ab_hit[index]/I");
   decay->Branch("ab_ch",ab_ch,"ab_ch[index][84]/I");
   decay->Branch("ab_DGFe",ab_DGFe,"ab_DGFe[index][84]/I");
   decay->Branch("ab_DGFt",ab_DGFt,"ab_DGFt[index][84]/I");
   decay->Branch("ab_TDCs",ab_TDCs,"ab_TDCs[index][84]/I");
   decay->Branch("ab_TDCl",ab_TDCl,"ab_TDCl[index][84]/I");
   decay->Branch("ab_E",ab_E,"ab_E[index][84]/D");
   decay->Branch("ab_T",ab_T,"ab_T[index][84]/D");

   decay->Branch("gc_hit",gc_hit,"gc_hit[index]/I");
   decay->Branch("gc_ch",gc_ch,"gc_ch[index][84]/I");
   decay->Branch("gc_DGFe",gc_DGFe,"gc_DGFe[index][84]/I");
   decay->Branch("gc_DGFt",gc_DGFt,"gc_DGFt[index][84]/I");
   decay->Branch("gc_TDCs",gc_TDCs,"gc_TDCs[index][84]/I");
   decay->Branch("gc_TDCl",gc_TDCl,"gc_TDCl[index][84]/I");
   decay->Branch("gc_E",gc_E,"gc_E[index][84]/D");
   decay->Branch("gc_T",gc_T,"gc_T[index][84]/D");

   decay->Branch("ab_matrix",&ab_matrix,"ab_matrix/I");
   decay->Branch("ab1_E",ab1_E,"ab1_E[ab_matrix]/D");
   decay->Branch("ab2_E",ab2_E,"ab2_E[ab_matrix]/D");
   decay->Branch("ab1_T",ab1_T,"ab1_T[ab_matrix]/D");
   decay->Branch("ab2_T",ab2_T,"ab2_T[ab_matrix]/D");
   decay->Branch("ab1_dt",ab1_dt,"ab1_dt[ab_matrix]/D");
   decay->Branch("ab2_dt",ab2_dt,"ab2_dt[ab_matrix]/D");


   decay->Branch("gc_matrix",&gc_matrix,"gc_matrix/I");
   decay->Branch("gc1_E",gc1_E,"gc1_E[gc_matrix]/D");
   decay->Branch("gc2_E",gc2_E,"gc2_E[gc_matrix]/D");
   decay->Branch("gc1_T",gc1_T,"gc1_T[gc_matrix]/D");
   decay->Branch("gc2_T",gc2_T,"gc2_T[gc_matrix]/D");
   decay->Branch("gc1_dt",gc1_dt,"gc1_dt[ab_matrix]/D");
   decay->Branch("gc2_dt",gc2_dt,"gc2_dt[ab_matrix]/D");

   int valid_gc_decay_index[200];
   int valid_gc_hit[200];
   int valid_ab_decay_index[200];
   int valid_ab_hit[200];

   dEntryMAX = ggdecay.fChain->GetEntriesFast();

   for(dEntry = 0; dEntry < dEntryMAX; dEntry++){
      if(dEntry%1000 == 0){
         cout<<"RUN#"<<runD<<", "<<dEntry<<" lines finished."<<endl;
      }
      for(int i=0; i<200; i++){
         valid_gc_decay_index[i]=-1;
         valid_gc_hit[i]=-1;
         valid_ab_decay_index[i]=-1;
         valid_ab_hit[i]=-1;
      }
      ab_matrix=0;
      gc_matrix=0;

      ggdecay.GetEntry(dEntry);
      ion_z = ggdecay.z;
      ion_x = ggdecay.x;
      ion_y = ggdecay.y;
      ion_tx = ggdecay.tx;
      ion_ty = ggdecay.ty;

      pid_Delta_F3F5 = ggdecay.pid_Delta_F3F5;
      pid_TOF_F3F7 = ggdecay.pid_TOF_F3F7;
      pid_Beta_F3F5 = ggdecay.pid_Beta_F3F5;
      pid_Beta_F5F7 = ggdecay.pid_Beta_F5F7;
      pid_AoQ_F3F5 = ggdecay.pid_AoQ_F3F5;
      pid_Zet_F11 = ggdecay.pid_Zet_F11;
      bigrips_zet = ggdecay.bigrips_zet;
      bigrips_aoq = ggdecay.bigrips_aoq;
      bigrips_beta = ggdecay.bigrips_beta;

      aoq = ggdecay.aoq;
      zet = ggdecay.zet;
      mass = ggdecay.mass;
      Zed = ggdecay.Zed;
      Mass = ggdecay.Mass;

      run = ggdecay.run;
      index = ggdecay.beta_;
      for(int i=0; i<index; i++){
         t[i] = ggdecay.beta_t[i];
         z[i] = ggdecay.beta_z[i];
         x[i] = ggdecay.beta_x[i];
         y[i] = ggdecay.beta_y[i];
         ex[i] = ggdecay.beta_ex[i];
         ey[i] = ggdecay.beta_ey[i];
         deltaz[i] = ggdecay.beta_deltaz[i];
         deltaxy[i] = ggdecay.beta_deltaxy[i];
         dssd_E[i] = ggdecay.beta_E[i];
         memcpy(dssd_fire[i], ggdecay.beta_dssd_fire[i], sizeof(ggdecay.beta_dssd_fire[i]));
         memcpy(dssd_ex[i], ggdecay.beta_dssd_ex[i], sizeof(ggdecay.beta_dssd_ex[i]));
         memcpy(dssd_ey[i], ggdecay.beta_dssd_ey[i], sizeof(ggdecay.beta_dssd_ey[i]));
         Qbeta_E[i] = ggdecay.beta_Qbeta_E[i];
         Qbeta_T[i] = ggdecay.beta_Qbeta_T[i];
         Qveto_E[i] = ggdecay.beta_Qveto_E[i];
         Qveto_T[i] = ggdecay.beta_Qveto_T[i];
         memcpy(NaI_E[i], ggdecay.beta_NaI_E[i], sizeof(ggdecay.beta_NaI_E[i]));
         memcpy(NaI_T[i], ggdecay.beta_NaI_T[i], sizeof(ggdecay.beta_NaI_T[i]));

         gc_hit[i]=ggdecay.beta_gc_hit[i];
         memcpy(gc_ch[i], ggdecay.beta_gc_ch[i], sizeof(ggdecay.beta_gc_ch[i]));
         memcpy(gc_DGFe[i], ggdecay.beta_gc_DGFe[i], sizeof(ggdecay.beta_gc_DGFe[i]));
         memcpy(gc_DGFt[i], ggdecay.beta_gc_DGFt[i], sizeof(ggdecay.beta_gc_DGFt[i]));
         memcpy(gc_TDCs[i], ggdecay.beta_gc_TDCs[i], sizeof(ggdecay.beta_gc_TDCs[i]));
         memcpy(gc_TDCl[i], ggdecay.beta_gc_TDCl[i], sizeof(ggdecay.beta_gc_TDCl[i]));
         memcpy(gc_E[i], ggdecay.beta_gc_E[i], sizeof(ggdecay.beta_gc_E[i]));
         memcpy(gc_T[i], ggdecay.beta_gc_T[i], sizeof(ggdecay.beta_gc_T[i]));

         ggdecay.GammaAddback(i);
         ab_hit[i]=ggdecay.beta_ab_hit[i];
         memcpy(ab_ch[i], ggdecay.beta_ab_ch[i], sizeof(ggdecay.beta_ab_ch[i]));
         memcpy(ab_DGFe[i], ggdecay.beta_ab_DGFe[i], sizeof(ggdecay.beta_ab_DGFe[i]));
         memcpy(ab_DGFt[i], ggdecay.beta_ab_DGFt[i], sizeof(ggdecay.beta_ab_DGFt[i]));
         memcpy(ab_TDCs[i], ggdecay.beta_ab_TDCs[i], sizeof(ggdecay.beta_ab_TDCs[i]));
         memcpy(ab_TDCl[i], ggdecay.beta_ab_TDCl[i], sizeof(ggdecay.beta_ab_TDCl[i]));
         memcpy(ab_E[i], ggdecay.beta_ab_E[i], sizeof(ggdecay.beta_ab_E[i]));
         memcpy(ab_T[i], ggdecay.beta_ab_T[i], sizeof(ggdecay.beta_ab_T[i]));
         if(i<10 && gc_hit[i]<20){
            for(int j=0; j<gc_hit[i]; j++){
               valid_gc_decay_index[gc_matrix]=i;
               valid_gc_hit[gc_matrix]=j;
               gc_matrix++;
            }
         }
         if(i<10 && ab_hit[i]<20){
            for(int j=0; j<ab_hit[i]; j++){
               valid_ab_decay_index[ab_matrix]=i;
               valid_ab_hit[ab_matrix]=j;
               ab_matrix++;
            }
         }
      }

      for(int i=0; i<gc_matrix; i++){
         for(int j=0; j<gc_matrix; j++){
            int valid_gc_decay_index_i = valid_gc_decay_index[i];
            int valid_gc_decay_index_j = valid_gc_decay_index[j];
            int valid_gc_hit_i = valid_gc_hit[i];
            int valid_gc_hit_j = valid_gc_hit[j];
            gc1_E[i*gc_matrix+j]=ggdecay.beta_gc_E[valid_gc_decay_index_i][valid_gc_hit_i];
            gc2_E[i*gc_matrix+j]=ggdecay.beta_gc_E[valid_gc_decay_index_j][valid_gc_hit_j];
            gc1_T[i*gc_matrix+j]=ggdecay.beta_gc_T[valid_gc_decay_index_i][valid_gc_hit_i];
            gc2_T[i*gc_matrix+j]=ggdecay.beta_gc_T[valid_gc_decay_index_j][valid_gc_hit_j];
            gc1_dt[i*gc_matrix+j]=ggdecay.beta_t[valid_gc_decay_index_i];
            gc2_dt[i*gc_matrix+j]=ggdecay.beta_t[valid_gc_decay_index_j];
         }
      }
      gc_matrix = gc_matrix*gc_matrix;
      for(int i=0; i<ab_matrix; i++){
         for(int j=0; j<ab_matrix; j++){
            int valid_ab_decay_index_i = valid_ab_decay_index[i];
            int valid_ab_decay_index_j = valid_ab_decay_index[j];
            int valid_ab_hit_i = valid_ab_hit[i];
            int valid_ab_hit_j = valid_ab_hit[j];
            ab1_E[i*ab_matrix+j]=ggdecay.beta_ab_E[valid_ab_decay_index_i][valid_ab_hit_i];
            ab2_E[i*ab_matrix+j]=ggdecay.beta_ab_E[valid_ab_decay_index_j][valid_ab_hit_j];
            ab1_T[i*ab_matrix+j]=ggdecay.beta_ab_T[valid_ab_decay_index_i][valid_ab_hit_i];
            ab2_T[i*ab_matrix+j]=ggdecay.beta_ab_T[valid_ab_decay_index_j][valid_ab_hit_j];
            ab1_dt[i*ab_matrix+j]=ggdecay.beta_t[valid_ab_decay_index_i];
            ab2_dt[i*ab_matrix+j]=ggdecay.beta_t[valid_ab_decay_index_j];
         }
      }
      ab_matrix = ab_matrix*ab_matrix;
      //cout<<gc_matrix<<", "<<ab_matrix<<", come here"<<endl;
      decay->Fill();
   }
   rootfile->Write();
   rootfile->Close();
   cout<<"finished"<<endl;
}
