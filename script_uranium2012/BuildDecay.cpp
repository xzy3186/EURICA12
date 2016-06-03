/************************************
build decay curve based on ion and
beta time stamp. Also add energy and
position information to each decay
event.
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
#include"eurica_wasabi.h"
#include"beta.h"
#include"ion.h"

using namespace std;

int main(int argc, char* argv[]){

   if(argc<2){
      cout<<"USAGE: BuildDecay RUN#"<<endl;
      return 0;
   }

   int runD = atoi(argv[1]);
   char dssdfile[128];
   char outfile[128];

   sprintf(dssdfile,"../root/sistopper/beta_ion_%04d.root",runD);
   sprintf(outfile,"../root/sistopper/decay_new%04d.root",runD);

   beta BETA;
   BETA.GetTree(dssdfile);
   ion ION;
   ION.GetTree(dssdfile);

   map<Long64_t,Long64_t> mtsi; //time stamp table for beta and ion
   multimap<Long64_t,pair<pair<Long64_t, Int_t>, pair<Int_t, Int_t> > > mtsb; //time stamp table for beta and ion
   map<Long64_t,Long64_t>::iterator imtsi;
   multimap<Long64_t,pair<pair<Long64_t, Int_t>, pair<Int_t, Int_t> > > ::iterator imtsb;

   Long64_t bEntry, bEntry_best, iEntry, beta_ts;
   Int_t deltaz_min;
   Int_t beta_z, beta_x, beta_y;
   TFile *rootfile = new TFile(outfile,"RECREATE");
   TTree *decay = new TTree("decay","decay");

   Long64_t decay_time;
   Long64_t current_time;
   Int_t _numdssd = NumDSSD;
   Int_t decay_z;
   Int_t decay_x;
   Int_t decay_y;
   Int_t decay_deltaz;
   Int_t decay_E;
   Int_t decay_ex[NumDSSD];
   Int_t decay_ey[NumDSSD];
   //Int_t dssd_E_X[NumDSSD][NumStrX];
   //Int_t dssd_E_Y[NumDSSD][NumStrY];
   //Int_t dssd_T_X[NumDSSD][NumStrX][3];
   //Int_t dssd_T_Y[NumDSSD][NumStrY][3];
   //Int_t dssd_ch_X[NumDSSD][NumStrX];
   //Int_t dssd_id_X[NumDSSD][NumStrY];
   //Int_t dssd_ch_Y[NumDSSD][NumStrX];
   //Int_t dssd_id_Y[NumDSSD][NumStrY];
   Int_t NaI_E[3];
   Int_t NaI_T[3];
   Int_t Qbeta_E;
   Int_t Qbeta_T;
   Int_t Qveto_E;
   Int_t Qveto_T;
   Int_t decay_index;
   Int_t decay_run;
   Int_t gc_hit;
   Int_t gc_ch[84];
   Int_t gc_DGFe[84];
   Int_t gc_TDCs[84];
   Int_t gc_DGFt[84];
   Int_t gc_TDCl[84];
   Double_t gc_E[84];
   Double_t gc_T[84];
   Int_t ab_hit;
   Int_t ab_ch[84];
   Int_t ab_DGFe[84];
   Int_t ab_TDCs[84];
   Int_t ab_DGFt[84];
   Int_t ab_TDCl[84];
   Double_t ab_E[84];
   Double_t ab_T[84];
   Double_t pid_Delta_F3F5;
   Double_t pid_TOF_F3F7;
   Double_t pid_Beta_F3F5;
   Double_t pid_Beta_F5F7;
   Double_t pid_AoQ_F3F5;
   Double_t pid_Zet_F11;
   Double_t bigrips_aoq;
   Double_t bigrips_zet;
   Double_t bigrips_beta;

   Double_t aoq;
   Double_t zet;
   Double_t mass;
   Int_t Mass;
   Int_t Zed;

   decay->Branch("t",&decay_time,"t/L");
   decay->Branch("x",&decay_x,"x/I");
   decay->Branch("y",&decay_y,"y/I");
   decay->Branch("z",&decay_z,"z/I");
   decay->Branch("deltaz",&decay_deltaz,"deltaz/I");
   decay->Branch("numdssd",&_numdssd,"numdssd/I");
   decay->Branch("dssd_E",&decay_E,"dssd_E/I");
   decay->Branch("dssd_ex",decay_ex,"dssd_ex[numdssd]/I");
   decay->Branch("dssd_ey",decay_ey,"dssd_ey[numdssd]/I");
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
   decay->Branch("bigrips_aoq", &bigrips_aoq,"bigrips_aoq/D");
   decay->Branch("bigrips_zet", &bigrips_zet,"bigrips_zet/D");
   decay->Branch("bigrips_beta", &bigrips_beta,"bigrips_beta/D");

   decay->Branch("zet", &zet,"zet/D");
   decay->Branch("aoq", &aoq,"aoq/D");
   decay->Branch("mass", &mass,"mass/D");
   decay->Branch("Zed", &Zed,"Zed/I");
   decay->Branch("Mass",&Mass,"Mass/I");

   decay->Branch("Qbeta_E",&Qbeta_E,"Qbeta_E/I");
   decay->Branch("Qbeta_T",&Qbeta_T,"Qbeta_T/I");
   decay->Branch("Qveto_E",&Qveto_E,"Qveto_E/I");
   decay->Branch("Qveto_T",&Qveto_T,"Qveto_T/I");

   decay->Branch("index",&decay_index,"index/I");
   decay->Branch("run",&decay_run,"run/I");
   decay->Branch("gc_hit",&gc_hit,"gc_hit/I");
   decay->Branch("gc_ch",gc_ch,"gc_ch[gc_hit]/I");
   decay->Branch("gc_DGFe",gc_DGFe,"gc_DGFe[gc_hit]/I");
   decay->Branch("gc_DGFt",gc_DGFt,"gc_DGFt[gc_hit]/I");
   decay->Branch("gc_TDCs",gc_TDCs,"gc_TDCs[gc_hit]/I");
   decay->Branch("gc_TDCl",gc_TDCl,"gc_TDCl[gc_hit]/I");
   decay->Branch("gc_E",gc_E,"gc_E[gc_hit]/D");
   decay->Branch("gc_T",gc_T,"gc_T[gc_hit]/D");
   decay->Branch("ab_hit",&ab_hit,"ab_hit/I");
   decay->Branch("ab_ch",ab_ch,"ab_ch[ab_hit]/I");
   decay->Branch("ab_DGFe",ab_DGFe,"ab_DGFe[ab_hit]/I");
   decay->Branch("ab_DGFt",ab_DGFt,"ab_DGFt[ab_hit]/I");
   decay->Branch("ab_TDCs",ab_TDCs,"ab_TDCs[ab_hit]/I");
   decay->Branch("ab_TDCl",ab_TDCl,"ab_TDCl[ab_hit]/I");
   decay->Branch("ab_E",ab_E,"ab_E[ab_hit]/D");
   decay->Branch("ab_T",ab_T,"ab_T[ab_hit]/D");

   decay->Branch("NaI_E",NaI_E,"NaI_E[3]/I");
   decay->Branch("NaI_T",NaI_T,"NaI_T[3]/I");

   cout<<"start building time table of beta"<<endl;
   BETA.GetTsEntry(mtsb);
   cout<<"start building time table of ion"<<endl;
   ION.GetTsEntry(mtsi);
   
   Long64_t time_window = 5e8;//

   Int_t num_decay=0;

   cout<<"start building beta decay"<<endl;
   for(imtsi=mtsi.begin(); imtsi!=mtsi.end(); imtsi++){
      iEntry = imtsi->second;
      if(iEntry%10==1){
         cout<<"RUN#"<<runD<<", "<<iEntry<<" lines finished 0"<<endl;
      }
      ION.GetEntry(iEntry);
      pid_Delta_F3F5 = ION.pid_Delta_F3F5;
      pid_TOF_F3F7 = ION.pid_TOF_F3F7;
      pid_Beta_F3F5 = ION.pid_Beta_F3F5;
      pid_Beta_F5F7 = ION.pid_Beta_F5F7;
      pid_AoQ_F3F5 = ION.pid_AoQ_F3F5;
      pid_Zet_F11 = ION.pid_Zet_F11;
      bigrips_zet = ION.bigrips_zet;
      bigrips_aoq = ION.bigrips_aoq;
      bigrips_beta = ION.bigrips_beta;

      aoq = ION.aoq;
      zet = ION.zet;
      mass = ION.mass;
      Zed = ION.Zed;
      Mass = ION.Mass;

      if(zet>28.5 || zet<26.5){
         continue;
      }

      Long64_t ts1 = imtsi->first; //100us as dead time
      Long64_t ts2 = ts1 + time_window;
      Int_t ion_x, ion_y, ion_z;
      ion_x=ION.x[ION.z];
      ion_y=ION.y[ION.z];
      ion_z=ION.z;
      if(ion_z<0 || ion_z>7 || ion_x==0 || ion_x==59 || ion_y==0 || ion_y==39){
         continue;
      }

      Int_t index_temp=1;
      current_time = 0;
      imtsb = mtsb.lower_bound(ts1);
      bEntry_best = 0;
      deltaz_min=2;
      //cout<<iEntry<<" lines finished 1"<<endl;
      while(imtsb!=mtsb.end() && imtsb->first<ts2){
         beta_ts = imtsb->first;
         bEntry = imtsb->second.first.first;
         beta_z = imtsb->second.first.second;
         beta_x = imtsb->second.second.first;
         beta_y = imtsb->second.second.second;
         if(beta_ts!=current_time){
            if(bEntry_best != 0){
               BETA.GetEntry(bEntry_best);
               decay_time = BETA.ts - ION.ts;
               decay_z = ION.z;
               decay_deltaz = abs(ION.z-BETA.z);
               decay_x = ION.x[ION.z];
               decay_y = ION.y[ION.z];
               decay_E = BETA.dssd_E;
               memcpy(decay_ex, BETA.dssd_ex, sizeof(BETA.dssd_ex));
               memcpy(decay_ey, BETA.dssd_ey, sizeof(BETA.dssd_ey));

               Qbeta_E = BETA.Qbeta_E;
               Qbeta_T = BETA.Qbeta_T;
               Qveto_E = BETA.Qveto_E;
               Qveto_T = BETA.Qveto_T;

               memcpy(NaI_E, BETA.NaI_E, sizeof(BETA.NaI_E));
               memcpy(NaI_T, BETA.NaI_T, sizeof(BETA.NaI_T));

               if(decay_E>50){
                  decay_index=index_temp;
                  index_temp++;
               }else{
                  decay_index=0;
               }
               gc_hit = BETA.gc_hit;
               ab_hit = BETA.ab_hit;
               memcpy(gc_ch, BETA.gc_ch, sizeof(BETA.gc_ch));
               memcpy(gc_DGFe, BETA.gc_DGFe, sizeof(BETA.gc_DGFe));
               memcpy(gc_DGFt, BETA.gc_DGFt, sizeof(BETA.gc_DGFt));
               memcpy(gc_TDCs, BETA.gc_TDCs, sizeof(BETA.gc_TDCs));
               memcpy(gc_TDCl, BETA.gc_TDCl, sizeof(BETA.gc_TDCl));
               memcpy(gc_E, BETA.gc_E, sizeof(BETA.gc_E));
               memcpy(gc_T, BETA.gc_T, sizeof(BETA.gc_T));
               memcpy(ab_ch, BETA.ab_ch, sizeof(BETA.ab_ch));
               memcpy(ab_DGFe, BETA.ab_DGFe, sizeof(BETA.ab_DGFe));
               memcpy(ab_DGFt, BETA.ab_DGFt, sizeof(BETA.ab_DGFt));
               memcpy(ab_TDCs, BETA.ab_TDCs, sizeof(BETA.ab_TDCs));
               memcpy(ab_TDCl, BETA.ab_TDCl, sizeof(BETA.ab_TDCl));
               memcpy(ab_E, BETA.ab_E, sizeof(BETA.ab_E));
               memcpy(ab_T, BETA.ab_T, sizeof(BETA.ab_T));
               decay_run=runD;
               decay->Fill();
               bEntry_best = 0;
               deltaz_min=2;
            }
            current_time = beta_ts;
            if(abs(beta_x-ion_x)<=1 && abs(beta_y-ion_y)<=1){
               if(abs(beta_z-ion_z)<deltaz_min){
                  bEntry_best = bEntry;
                  deltaz_min = abs(beta_z-ion_z);
               }
            }
            imtsb++;
         }else{
            if(abs(beta_x-ion_x)<=1 && abs(beta_y-ion_y)<=1){
               if(abs(beta_z-ion_z)<=deltaz_min){
                  bEntry_best = bEntry;
                  deltaz_min = abs(beta_z-ion_z);
               }
            }
            imtsb++;
         }
      }
   }
   rootfile->Write();
   rootfile->Close();
}
