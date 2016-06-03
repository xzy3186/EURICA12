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

   Double_t beta35;
   Double_t beta57;
   Double_t beta711;
   Double_t aoq37;
   Double_t zed;

   Int_t Zed;
   Int_t Mass;
   Int_t flagall;
   Int_t flagTSumX;
   Int_t flagTOFt;
   Int_t flagTOFq;
   Int_t flagReaction;
   Int_t flagdERelation;
   Int_t flagAngle;

   Long64_t t[100];
   Int_t z[100];
   Float_t x[100];
   Float_t y[100];
   Int_t ex[100];
   Int_t ey[100];
   Int_t deltaz[100];
   Double_t deltaxy[100];
   Int_t dssd_E[100];
   Int_t flag_side[100];
   Int_t dssd_fire[100][8];
   Int_t dssd_ex[100][8];
   Int_t dssd_ey[100][8];
   Int_t dssd_zmult[100][8];
   Float_t dssd_x[100][8][5];
   Float_t dssd_y[100][8][5];
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
   Int_t gc1_deltaz[40000];
   Int_t gc2_deltaz[40000];
   Int_t gc1_flag_side[40000];
   Int_t gc2_flag_side[40000];
   Double_t gc1_deltaxy[40000];
   Double_t gc2_deltaxy[40000];
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
   Int_t ab1_deltaz[40000];
   Int_t ab2_deltaz[40000];
   Int_t ab1_flag_side[40000];
   Int_t ab2_flag_side[40000];
   Double_t ab1_deltaxy[40000];
   Double_t ab2_deltaxy[40000];
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
   sprintf(outfile,"../gamma_db/cu78_%04d.root",runD);

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

   decay->Branch("beta35", &beta35,"beta35/D");
   decay->Branch("beta57", &beta57,"beta57/D");
   decay->Branch("beta711", &beta711,"beta711/D");
   decay->Branch("aoq37", &aoq37,"aoq37/D");
   decay->Branch("zed", &zed,"zed/D");

   decay->Branch("Zed", &Zed,"Zed/I");
   decay->Branch("Mass", &Mass,"Mass/I");
   decay->Branch("flagall", &flagall,"flagall/I");
   decay->Branch("flagTSumX", &flagTSumX,"flagTSumX/I");
   decay->Branch("flagTOFt", &flagTOFt,"flagTOFt/I");
   decay->Branch("flagTOFq", &flagTOFq,"flagTOFq/I");
   decay->Branch("flagReaction", &flagReaction,"flagReaction/I");
   decay->Branch("flagdERelation", &flagdERelation,"flagdERelation/I");
   decay->Branch("flagAngle", &flagAngle,"flagAngle/I");

   decay->Branch("index",&index,"index/I");
   decay->Branch("t",t,"t[index]/L");
   decay->Branch("z",z,"z[index]/I");
   decay->Branch("x",x,"x[index]/F");
   decay->Branch("y",y,"y[index]/F");
   decay->Branch("ex",ex,"ex[index]/I");
   decay->Branch("ey",ey,"ey[index]/I");
   decay->Branch("deltaz",deltaz,"deltaz[index]/I");
   decay->Branch("deltaxy",deltaxy,"deltaxy[index]/D");
   decay->Branch("dssd_E",dssd_E,"dssd_E[index]/I");
   decay->Branch("flag_side",flag_side,"flag_side[index]/I");
   decay->Branch("dssd_fire",dssd_fire,"dssd_fire[index][8]/I");
   decay->Branch("dssd_ex",dssd_ex,"dssd_ex[index][8]/I");
   decay->Branch("dssd_ey",dssd_ey,"dssd_ey[index][8]/I");
   decay->Branch("dssd_zmult",dssd_zmult,"dssd_zmult[index][8]/I");
   decay->Branch("dssd_x",dssd_x,"dssd_x[index][8][5]/F");
   decay->Branch("dssd_y",dssd_y,"dssd_y[index][8][5]/F");

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
   decay->Branch("ab1_deltaz",ab1_deltaz,"ab1_deltaz[ab_matrix]/I");
   decay->Branch("ab2_deltaz",ab2_deltaz,"ab2_deltaz[ab_matrix]/I");
   decay->Branch("ab1_flag_side",ab1_flag_side,"ab1_flag_side[ab_matrix]/I");
   decay->Branch("ab2_flag_side",ab2_flag_side,"ab2_flag_side[ab_matrix]/I");
   decay->Branch("ab1_deltaxy",ab1_deltaxy,"ab1_deltaxy[ab_matrix]/D");
   decay->Branch("ab2_deltaxy",ab2_deltaxy,"ab2_deltaxy[ab_matrix]/D");


   decay->Branch("gc_matrix",&gc_matrix,"gc_matrix/I");
   decay->Branch("gc1_E",gc1_E,"gc1_E[gc_matrix]/D");
   decay->Branch("gc2_E",gc2_E,"gc2_E[gc_matrix]/D");
   decay->Branch("gc1_T",gc1_T,"gc1_T[gc_matrix]/D");
   decay->Branch("gc2_T",gc2_T,"gc2_T[gc_matrix]/D");
   decay->Branch("gc1_dt",gc1_dt,"gc1_dt[gc_matrix]/D");
   decay->Branch("gc2_dt",gc2_dt,"gc2_dt[gc_matrix]/D");
   decay->Branch("gc1_deltaz",gc1_deltaz,"gc1_deltaz[gc_matrix]/I");
   decay->Branch("gc2_deltaz",gc2_deltaz,"gc2_deltaz[gc_matrix]/I");
   decay->Branch("gc1_flag_side",gc1_flag_side,"gc1_flag_side[gc_matrix]/I");
   decay->Branch("gc2_flag_side",gc2_flag_side,"gc2_flag_side[gc_matrix]/I");
   decay->Branch("gc1_deltaxy",gc1_deltaxy,"gc1_deltaxy[gc_matrix]/D");
   decay->Branch("gc2_deltaxy",gc2_deltaxy,"gc2_deltaxy[gc_matrix]/D");

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

      beta35 = ggdecay.beta35;
      beta57 = ggdecay.beta57;
      beta711 = ggdecay.beta711;
      aoq37 = ggdecay.aoq37;
      zed = ggdecay.zed;
      Zed = ggdecay.Zed;
      Mass = ggdecay.Mass;

      flagall = ggdecay.flagall;
      flagTSumX = ggdecay.flagTSumX;
      flagTOFt = ggdecay.flagTOFt;
      flagTOFq = ggdecay.flagTOFq;
      flagReaction = ggdecay.flagReaction;
      flagdERelation = ggdecay.flagdERelation;
      flagAngle = ggdecay.flagAngle;

      if(Zed != 29 || Mass != 78){
         continue;
      }

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
         flag_side[i] = ggdecay.beta_flag_side[i];
         memcpy(dssd_fire[i], ggdecay.beta_dssd_fire[i], sizeof(ggdecay.beta_dssd_fire[i]));
         memcpy(dssd_ex[i], ggdecay.beta_dssd_ex[i], sizeof(ggdecay.beta_dssd_ex[i]));
         memcpy(dssd_ey[i], ggdecay.beta_dssd_ey[i], sizeof(ggdecay.beta_dssd_ey[i]));
         memcpy(dssd_zmult[i], ggdecay.beta_dssd_zmult[i], sizeof(ggdecay.beta_dssd_zmult[i]));
         memcpy(dssd_x[i], ggdecay.beta_dssd_x[i], sizeof(ggdecay.beta_dssd_x[i]));
         memcpy(dssd_y[i], ggdecay.beta_dssd_y[i], sizeof(ggdecay.beta_dssd_y[i]));
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
            gc1_deltaz[i*gc_matrix+j]=ggdecay.beta_deltaz[valid_gc_decay_index_i];
            gc2_deltaz[i*gc_matrix+j]=ggdecay.beta_deltaz[valid_gc_decay_index_j];
            gc1_flag_side[i*gc_matrix+j]=ggdecay.beta_flag_side[valid_gc_decay_index_i];
            gc2_flag_side[i*gc_matrix+j]=ggdecay.beta_flag_side[valid_gc_decay_index_j];
            gc1_deltaxy[i*gc_matrix+j]=ggdecay.beta_deltaxy[valid_gc_decay_index_i];
            gc2_deltaxy[i*gc_matrix+j]=ggdecay.beta_deltaxy[valid_gc_decay_index_j];
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
            ab1_deltaz[i*ab_matrix+j]=ggdecay.beta_deltaz[valid_ab_decay_index_i];
            ab2_deltaz[i*ab_matrix+j]=ggdecay.beta_deltaz[valid_ab_decay_index_j];
            ab1_flag_side[i*ab_matrix+j]=ggdecay.beta_flag_side[valid_ab_decay_index_i];
            ab2_flag_side[i*ab_matrix+j]=ggdecay.beta_flag_side[valid_ab_decay_index_j];
            ab1_deltaxy[i*ab_matrix+j]=ggdecay.beta_deltaxy[valid_ab_decay_index_i];
            ab2_deltaxy[i*ab_matrix+j]=ggdecay.beta_deltaxy[valid_ab_decay_index_j];
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
