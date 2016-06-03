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


   Long64_t t;
   Int_t x;
   Int_t y;
   Int_t ex;
   Int_t ey;
   Int_t z;
   Int_t deltaz;
   Int_t dssd_E;
   Int_t numdssd;
   Int_t dssd_fire[8];
   Int_t dssd_ex[8];
   Int_t dssd_ey[8];
   //Int_t dssd_E_X[8][60];   //[numdssd]
   //Int_t dssd_ch_X[8][60];   //[numdssd]
   //Int_t dssd_id_X[8][60];   //[numdssd]
   //Int_t dssd_E_Y[8][40];   //[numdssd]
   //Int_t dssd_ch_Y[8][40];   //[numdssd]
   //Int_t dssd_id_Y[8][40];   //[numdssd]
   //Int_t dssd_T_X[8][60][3];   //[numdssd]
   //Int_t dssd_T_Y[8][40][3];   //[numdssd]
   Int_t NaI_E[3];
   Int_t NaI_T[3];
   Int_t Qbeta_E;
   Int_t Qbeta_T;
   Int_t Qveto_E;
   Int_t Qveto_T;
   Int_t index;
   Int_t run;

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

   Int_t gc_matrix;
   Double_t gc1_E[7056];
   Double_t gc2_E[7056];
   Double_t gc1_T[7056];
   Double_t gc2_T[7056];
   Int_t gc_hit;
   Int_t gc_ch[84];   //[gc_hit]
   Int_t gc_DGFe[84];   //[gc_hit]
   Int_t gc_DGFt[84];   //[gc_hit]
   Int_t gc_TDCs[84];   //[gc_hit]
   Int_t gc_TDCl[84];   //[gc_hit]
   Double_t gc_E[84];   //[gc_hit]
   Double_t gc_T[84];   //[gc_hit]

   Int_t ab_matrix;
   Double_t ab1_E[7056];
   Double_t ab2_E[7056];
   Double_t ab1_T[7056];
   Double_t ab2_T[7056];
   Int_t ab_hit;
   Int_t ab_ch[84];   //[ab_hit]
   Int_t ab_DGFe[84];   //[ab_hit]
   Int_t ab_DGFt[84];   //[ab_hit]
   Int_t ab_TDCs[84];   //[ab_hit]
   Int_t ab_TDCl[84];   //[ab_hit]
   Double_t ab_E[84];   //[ab_hit]
   Double_t ab_T[84];   //[ab_hit]

   sprintf(decayfile,"../root/sistopper/nb115test/decay_new%04d.root",runD);
   //sprintf(decayfile,"go4.root");
   sprintf(outfile,"../root/sistopper/nb115test/DECAY_GGMatrix%04d.root",runD);

   decay_ggmatrix ggdecay(decayfile);

   Long64_t dEntry, dEntryMAX;  //entry for decay
   TFile *rootfile = new TFile(outfile,"RECREATE");

   TTree *decay = new TTree("decay","decay");
   decay->Branch("t",&t,"t/L");
   decay->Branch("x",&x,"x/I");
   decay->Branch("y",&y,"y/I");
   decay->Branch("ex",&ex,"ex/I");
   decay->Branch("ey",&ey,"ey/I");
   decay->Branch("z",&z,"z/I");
   decay->Branch("deltaz",&deltaz,"deltaz/I");
   decay->Branch("dssd_E",&dssd_E,"dssd_E/I");
   decay->Branch("numdssd",&numdssd,"numdssd/I");
   decay->Branch("dssd_fire",dssd_fire,"dssd_fire[numdssd]/I");
   decay->Branch("dssd_ex",dssd_ex,"dssd_ex[numdssd]/I");
   decay->Branch("dssd_ey",dssd_ey,"dssd_ey[numdssd]/I");
   //decay->Branch("dssd_E_X",dssd_E_X,"dssd_E_X[numdssd][60]/I");
   //decay->Branch("dssd_ch_X",dssd_ch_X,"dssd_ch_X[numdssd][60]/I");
   //decay->Branch("dssd_id_X",dssd_id_X,"dssd_id_X[numdssd][60]/I");
   //decay->Branch("dssd_E_Y",dssd_E_Y,"dssd_E_Y[numdssd][40]/I");
   //decay->Branch("dssd_ch_Y",dssd_ch_Y,"dssd_ch_Y[numdssd][40]/I");
   //decay->Branch("dssd_id_Y",dssd_id_Y,"dssd_id_Y[numdssd][40]/I");
   //decay->Branch("dssd_T_X",dssd_T_X,"dssd_T_X[numdssd][60][3]/I");
   //decay->Branch("dssd_T_Y",dssd_T_Y,"dssd_T_Y[numdssd][40][3]/I");

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

   decay->Branch("NaI_E",NaI_E,"NaI_E[3]/I");
   decay->Branch("NaI_T",NaI_T,"NaI_T[3]/I");
   decay->Branch("Qbeta_E",&Qbeta_E,"Qbeta_E/I");
   decay->Branch("Qbeta_T",&Qbeta_T,"Qbeta_T/I");
   decay->Branch("Qveto_E",&Qveto_E,"Qveto_E/I");
   decay->Branch("Qveto_T",&Qveto_T,"Qveto_T/I");

   decay->Branch("index",&index,"index/I");
   decay->Branch("run",&run,"run/I");

   decay->Branch("gc_matrix",&gc_matrix,"gc_matrix/I");
   decay->Branch("gc1_E",gc1_E,"gc1_E[gc_matrix]/D");
   decay->Branch("gc2_E",gc2_E,"gc2_E[gc_matrix]/D");
   decay->Branch("gc1_T",gc1_T,"gc1_T[gc_matrix]/D");
   decay->Branch("gc2_T",gc2_T,"gc2_T[gc_matrix]/D");
   decay->Branch("ab_matrix",&ab_matrix,"ab_matrix/I");
   decay->Branch("ab1_E",ab1_E,"ab1_E[ab_matrix]/D");
   decay->Branch("ab2_E",ab2_E,"ab2_E[ab_matrix]/D");
   decay->Branch("ab1_T",ab1_T,"ab1_T[ab_matrix]/D");
   decay->Branch("ab2_T",ab2_T,"ab2_T[ab_matrix]/D");

   decay->Branch("ab_hit",&ab_hit,"ab_hit/I");
   decay->Branch("ab_ch",ab_ch,"ab_ch[ab_hit]/I");
   decay->Branch("ab_DGFe",ab_DGFe,"ab_DGFe[ab_hit]/I");
   decay->Branch("ab_DGFt",ab_DGFt,"ab_DGFt[ab_hit]/I");
   decay->Branch("ab_TDCs",ab_TDCs,"ab_TDCs[ab_hit]/I");
   decay->Branch("ab_TDCl",ab_TDCl,"ab_TDCl[ab_hit]/I");
   decay->Branch("ab_E",ab_E,"ab_E[ab_hit]/D");
   decay->Branch("ab_T",ab_T,"ab_T[ab_hit]/D");

   decay->Branch("gc_hit",&gc_hit,"gc_hit/I");
   decay->Branch("gc_ch",gc_ch,"gc_ch[gc_hit]/I");
   decay->Branch("gc_DGFe",gc_DGFe,"gc_DGFe[gc_hit]/I");
   decay->Branch("gc_DGFt",gc_DGFt,"gc_DGFt[gc_hit]/I");
   decay->Branch("gc_TDCs",gc_TDCs,"gc_TDCs[gc_hit]/I");
   decay->Branch("gc_TDCl",gc_TDCl,"gc_TDCl[gc_hit]/I");
   decay->Branch("gc_E",gc_E,"gc_E[gc_hit]/D");
   decay->Branch("gc_T",gc_T,"gc_T[gc_hit]/D");

   dEntryMAX = ggdecay.fChain->GetEntriesFast();

   for(dEntry = 0; dEntry < dEntryMAX; dEntry++){
      if(dEntry%1000 == 0){
         cout<<"RUN#"<<runD<<", "<<dEntry<<" lines finished."<<endl;
      }
      ggdecay.GetEntry(dEntry);
      t = ggdecay.t;
      x = ggdecay.x;
      y = ggdecay.y;
      ex = ggdecay.ex;
      ey = ggdecay.ey;
      z = ggdecay.z;
      deltaz = ggdecay.deltaz;
      dssd_E = ggdecay.dssd_E;
      numdssd = ggdecay.numdssd;
      memcpy(dssd_fire, ggdecay.dssd_fire, sizeof(ggdecay.dssd_fire));
      memcpy(dssd_ex, ggdecay.dssd_ex, sizeof(ggdecay.dssd_ex));
      memcpy(dssd_ey, ggdecay.dssd_ey, sizeof(ggdecay.dssd_ey));
      //memcpy(dssd_E_X, ggdecay.dssd_E_X, sizeof(ggdecay.dssd_E_X));
      //memcpy(dssd_ch_X, ggdecay.dssd_ch_X, sizeof(ggdecay.dssd_ch_X));
      //memcpy(dssd_id_X, ggdecay.dssd_id_X, sizeof(ggdecay.dssd_id_X));
      //memcpy(dssd_E_Y, ggdecay.dssd_E_Y, sizeof(ggdecay.dssd_E_Y));
      //memcpy(dssd_ch_Y, ggdecay.dssd_ch_Y, sizeof(ggdecay.dssd_ch_Y));
      //memcpy(dssd_id_Y, ggdecay.dssd_id_Y, sizeof(ggdecay.dssd_id_Y));
      //memcpy(dssd_T_X, ggdecay.dssd_T_X, sizeof(ggdecay.dssd_T_X));
      //memcpy(dssd_T_Y, ggdecay.dssd_T_Y, sizeof(ggdecay.dssd_T_Y));

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

      Qbeta_E = ggdecay.Qbeta_E;
      Qbeta_T = ggdecay.Qbeta_T;
      Qveto_E = ggdecay.Qveto_E;
      Qveto_T = ggdecay.Qveto_T;
      
      memcpy(NaI_E, ggdecay.NaI_E, sizeof(ggdecay.NaI_E));
      memcpy(NaI_T, ggdecay.NaI_T, sizeof(ggdecay.NaI_T));

      index = ggdecay.index;
      run = ggdecay.run;

      gc_hit=ggdecay.gc_hit;
      memcpy(gc_ch, ggdecay.gc_ch, sizeof(ggdecay.gc_ch));
      memcpy(gc_DGFe, ggdecay.gc_DGFe, sizeof(ggdecay.gc_DGFe));
      memcpy(gc_DGFt, ggdecay.gc_DGFt, sizeof(ggdecay.gc_DGFt));
      memcpy(gc_TDCs, ggdecay.gc_TDCs, sizeof(ggdecay.gc_TDCs));
      memcpy(gc_TDCl, ggdecay.gc_TDCl, sizeof(ggdecay.gc_TDCl));
      memcpy(gc_E, ggdecay.gc_E, sizeof(ggdecay.gc_E));
      memcpy(gc_T, ggdecay.gc_T, sizeof(ggdecay.gc_T));

      ggdecay.GammaAddback();
      ab_hit=ggdecay.ab_hit;
      memcpy(ab_ch, ggdecay.ab_ch, sizeof(ggdecay.ab_ch));
      memcpy(ab_DGFe, ggdecay.ab_DGFe, sizeof(ggdecay.ab_DGFe));
      memcpy(ab_DGFt, ggdecay.ab_DGFt, sizeof(ggdecay.ab_DGFt));
      memcpy(ab_TDCs, ggdecay.ab_TDCs, sizeof(ggdecay.ab_TDCs));
      memcpy(ab_TDCl, ggdecay.ab_TDCl, sizeof(ggdecay.ab_TDCl));
      memcpy(ab_E, ggdecay.ab_E, sizeof(ggdecay.ab_E));
      memcpy(ab_T, ggdecay.ab_T, sizeof(ggdecay.ab_T));

      gc_matrix = gc_hit*gc_hit;
      for(int i=0; i<gc_hit; i++){
         for(int j=0; j<gc_hit; j++){
            gc1_E[i*gc_hit+j]=ggdecay.gc_E[i];
            gc2_E[i*gc_hit+j]=ggdecay.gc_E[j];
            gc1_T[i*gc_hit+j]=ggdecay.gc_T[i];
            gc2_T[i*gc_hit+j]=ggdecay.gc_T[j];
         }
      }
      ab_matrix = ab_hit*ab_hit;
      for(int i=0; i<ab_hit; i++){
         for(int j=0; j<ab_hit; j++){
            ab1_E[i*ab_hit+j]=ggdecay.ab_E[i];
            ab2_E[i*ab_hit+j]=ggdecay.ab_E[j];
            ab1_T[i*ab_hit+j]=ggdecay.ab_T[i];
            ab2_T[i*ab_hit+j]=ggdecay.ab_T[j];
         }
      }
      //cout<<gc_matrix<<", "<<ab_matrix<<", come here"<<endl;
      decay->Fill();
   }
   rootfile->Write();
   rootfile->Close();
   cout<<"finished"<<endl;
}
