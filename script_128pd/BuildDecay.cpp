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
#include <TClonesArray.h>

#include"TFile.h"
#include"TSystem.h"
#include"TTree.h"
#include"TROOT.h"
#include"TString.h"

#include<signal.h>

//#include"TArtEventStore.hh"
#include"eurica_wasabi.h"
#include"beta.h"
#include"ion.h"
#include"DecayEvent.cxx"

using namespace std;

int main(int argc, char* argv[]){

   if(argc<2){
      cout<<"USAGE: BuildDecay RUN#"<<endl;
      return 0;
   }

   int runD = atoi(argv[1]);
   //int runD=1032;
   char dssdfile[128];
   char outfile[128];

   sprintf(dssdfile,"../root/final/pd128test/beta_ion_%04d.root",runD);
   sprintf(outfile,"../root/final/pd128test/decay_new%04d.root",runD);
   //sprintf(dssdfile,"../root/sistopper/beta_ion_%04d.root",runD);
   //sprintf(outfile,"../root/sistopper/decay_new%04d.root",runD);

   beta BETA;
   BETA.GetTree(dssdfile);
   BETA.BranchStatus();
   ion ION;
   ION.GetTree(dssdfile);

   map<Long64_t,Long64_t> mtsi; //time stamp table for beta and ion
   map<Long64_t,Long64_t>::iterator imtsi;
   multimap<Long64_t,pair<pair<Long64_t, Int_t>, pair<pair<Int_t, Int_t>, pair<Int_t, Int_t> > > > mtsb; //time stamp table for beta and ion
   multimap<Long64_t,pair<pair<Long64_t, Int_t>, pair<pair<Int_t, Int_t>, pair<Int_t, Int_t> > > > ::iterator imtsb, beta_present, bg_present;

   Long64_t bEntry, bEntry_best, iEntry, beta_ts;
   Int_t deltaz_min;
   Int_t beta_z;
   Int_t beta_x1, beta_y1;
   Int_t beta_x2, beta_y2;
   TFile *rootfile = new TFile(outfile,"RECREATE");
   TTree *decay = new TTree("decay","decay");

   Long64_t ion_lastts[40][100];
   for(int i=0; i<40; i++){
      for(int j=0; j<100; j++){
         ion_lastts[i][j]=0;
      }
   }

   Long64_t current_time, ts1, ts2;

   CImp *imp = new CImp();
   TClonesArray *tbeta = new TClonesArray("CDecay",100);
   TClonesArray *tbg = new TClonesArray("CDecay",100);
   CDecay *cbeta;
   TClonesArray &tcbeta = *tbeta;
   CDecay *cbg;
   TClonesArray &tcbg = *tbg;

   decay->Branch("imp",&imp);
   decay->Branch("beta",&tbeta);
   decay->Branch("bg",&tbg);

   cout<<"start building time table of beta"<<endl;
   BETA.GetTsEntry(mtsb);
   cout<<"start building time table of ion"<<endl;
   ION.GetTsEntry(mtsi);
   
   Long64_t time_window = 5e8;//

   cout<<"start building beta decay"<<endl;
   float pr;
   for(imtsi=mtsi.begin(); imtsi!=mtsi.end(); imtsi++){
      iEntry = imtsi->second;
      pr = float(iEntry)/mtsi.size() * 100;
      if(iEntry%1000==1){
         cout<<"RUN#"<<runD<<", "<<iEntry<<" lines finished: "<<pr<<"%,"<<endl;
      }
      //if(iEntry > 1e4){
      //   break;
      //}
      ION.GetEntry(iEntry);
      imp->run = runD;
      imp->ts = ION.ts;
      imp->z = ION.z;
      imp->x = ION.x[ION.z];
      imp->y = ION.y[ION.z];
      imp->tx = ION.tx[ION.z];
      imp->ty = ION.ty[ION.z];

      //imp->pid_Delta_F3F5 = ION.pid_Delta_F3F5;
      //imp->pid_TOF_F3F7 = ION.pid_TOF_F3F7;
      //imp->pid_Beta_F3F5 = ION.pid_Beta_F3F5;
      //imp->pid_Beta_F5F7 = ION.pid_Beta_F5F7;
      //imp->pid_AoQ_F3F5 = ION.pid_AoQ_F3F5;
      //imp->pid_Zet_F11 = ION.pid_Zet_F11;
      //imp->bigrips_zet = ION.bigrips_zet;
      //imp->bigrips_aoq = ION.bigrips_aoq;
      imp->beta711 = ION.bigrips_beta;

      imp->aoq37 = ION.aoq;
      imp->zed = ION.zet;
      imp->Zed = ION.Zed;
      imp->Mass = ION.Mass;
      imp->gc_hit = 0;
      for(int i=0; i<84; i++){
         imp->gc_ch[i] = -1;
         imp->gc_DGFe[i] = -1;
         imp->gc_DGFt[i] = -1;
         imp->gc_TDCs[i] = -1;
         imp->gc_TDCl[i] = -1;
         imp->gc_E[i] = -1;
         imp->gc_T[i] = -1;
      }
      imp->ab_hit = 0;
      for(int i=0; i<84; i++){
         imp->ab_ch[i] = -1;
         imp->ab_DGFe[i] = -1;
         imp->ab_DGFt[i] = -1;
         imp->ab_TDCs[i] = -1;
         imp->ab_TDCl[i] = -1;
         imp->ab_E[i] = -1;
         imp->ab_T[i] = -1;
      }
      imp->gc_hit = ION.gc_hit;
      for(int i=0; i<ION.gc_hit; i++){
         imp->gc_ch[i] = ION.gc_ch[i];
         //imp->gc_DGFe[i] = ION.gc_DGFe[i];
         //imp->gc_DGFt[i] = ION.gc_DGFt[i];
         imp->gc_TDCs[i] = ION.gc_TDCs[i];
         imp->gc_TDCl[i] = ION.gc_TDCl[i];
         imp->gc_E[i] = ION.gc_E[i];
         imp->gc_T[i] = ION.gc_T[i];
      }
      imp->ab_hit = ION.ab_hit;
      for(int i=0; i<ION.ab_hit; i++){
         imp->ab_ch[i] = ION.ab_ch[i];
         //imp->ab_DGFe[i] = ION.ab_DGFe[i];
         //imp->ab_DGFt[i] = ION.ab_DGFt[i];
         imp->ab_TDCs[i] = ION.ab_TDCs[i];
         imp->ab_TDCl[i] = ION.ab_TDCl[i];
         imp->ab_E[i] = ION.ab_E[i];
         imp->ab_T[i] = ION.ab_T[i];
      }

      Int_t ion_x, ion_y, ion_z;
      ion_x=ION.x[ION.z];
      ion_y=ION.y[ION.z];
      ion_z=ION.z;

      if(iEntry==0){
         ts1 = imtsi->first; //100us as dead time
         imtsb = mtsb.lower_bound(ts1);
         beta_present = imtsb;
         ts1 = imtsi->first - 3*time_window/10; //100us as dead time
         imtsb = mtsb.lower_bound(ts1);
         bg_present = imtsb;
      }
      if(ION.IfInterest()==0){
         //continue;
         if(ION.ts-ion_lastts[ION.Zed-20][ION.Mass-ION.Zed]>1e8){
            ion_lastts[ION.Zed-20][ION.Mass-ION.Zed] = ION.ts;
            imp->IfInterest = 1;
         }else{
            imp->IfInterest = 0;
            //continue;
         }
      }else{
         imp->IfInterest = 1;
      }

      if(ION.Zed<20){
         continue;
      }

      if(ion_z<0 || ion_z>7 || ion_x==0 || ion_x==59 || ion_y==0 || ion_y==39){
         continue;
      }

      tcbeta.Clear();
      ts2 = imtsi->first + time_window;
      int decay_index=0;
      current_time = 0;
      bEntry_best = 0;
      deltaz_min=2;
      //cout<<iEntry<<" lines finished 1"<<endl;
      ts1 = imtsi->first;
      imtsb = beta_present;
      while(imtsb!=mtsb.end() && imtsb->first<ts2){
         beta_ts = imtsb->first;
         if(beta_ts<ts1){
            beta_present++;
            imtsb = beta_present;
            continue;
         }
         bEntry = imtsb->second.first.first;
         beta_z = imtsb->second.first.second;
         beta_x1 = imtsb->second.second.first.first;
         beta_x2 = imtsb->second.second.first.second;
         beta_y1 = imtsb->second.second.second.first;
         beta_y2 = imtsb->second.second.second.second;
         if(beta_ts!=current_time){
            if(bEntry_best != 0){
               BETA.GetEntry(bEntry_best);
               cbeta = new(tcbeta[decay_index]) CDecay();
               cbeta->t = BETA.ts - ION.ts;
               cbeta->z = BETA.z;
               cbeta->x = BETA.x;
               cbeta->y = BETA.y;
               cbeta->ex = BETA.ex;
               cbeta->ey = BETA.ey;
               cbeta->mulx = BETA.x2-BETA.x1+1;
               cbeta->muly = BETA.y2-BETA.y1+1;
               cbeta->deltaz = abs(ION.z-BETA.z);
               cbeta->deltaxy = sqrt((BETA.x-ion_x)*(BETA.x-ion_x)+(BETA.y-ion_y)*(BETA.y-ion_y));
               cbeta->E = BETA.dssd_E;
               memcpy(cbeta->dssd_fire, BETA.dssd_fire, sizeof(BETA.dssd_fire));
               memcpy(cbeta->dssd_ex, BETA.dssd_ex, sizeof(BETA.dssd_ex));
               memcpy(cbeta->dssd_ey, BETA.dssd_ey, sizeof(BETA.dssd_ey));
               memcpy(cbeta->dssd_zmult, BETA.dssd_zmult, sizeof(BETA.dssd_zmult));
               memcpy(cbeta->dssd_x, BETA.dssd_x, sizeof(BETA.dssd_x));
               memcpy(cbeta->dssd_y, BETA.dssd_y, sizeof(BETA.dssd_y));

               Int_t flag_U=0, flag_D=0;
               if(ion_z-1>=0){
                  if(cbeta->dssd_fire[ion_z-1]>0){
                     flag_U=1;
                  }
               }
               if(ion_z+1<NumDSSD){
                  if(cbeta->dssd_fire[ion_z+1]>0){
                     flag_D=1;
                  }
               }
               if(flag_U==0 && flag_D==0){
                  cbeta->flag_side = 0;
               }
               if(flag_U==1 && flag_D==0){
                  cbeta->flag_side = -1;
               }
               if(flag_U==0 && flag_D==1){
                  cbeta->flag_side = 1;
               }
               if(flag_U==1 && flag_D==1){
                  cbeta->flag_side = 2;
               }
               //cout<<"flag_U="<<flag_U<<", flag_D="<<flag_D<<", flag_side="<<cbeta->flag_side<<endl;

               cbeta->Qbeta_E = BETA.Qbeta_E;
               cbeta->Qbeta_T = BETA.Qbeta_T;
               cbeta->Qveto_E = BETA.Qveto_E;
               cbeta->Qveto_T = BETA.Qveto_T;

               //memcpy(cbeta->NaI_E, BETA.NaI_E, sizeof(BETA.NaI_E));
               //memcpy(cbeta->NaI_T, BETA.NaI_T, sizeof(BETA.NaI_T));

               cbeta->gc_hit = BETA.gc_hit;
               for(int i=0; i<BETA.gc_hit; i++){
                  cbeta->gc_ch[i] = BETA.gc_ch[i];
                  //cbeta->gc_DGFe[i] = BETA.gc_DGFe[i];
                  //cbeta->gc_DGFt[i] = BETA.gc_DGFt[i];
                  cbeta->gc_TDCs[i] = BETA.gc_TDCs[i];
                  cbeta->gc_TDCl[i] = BETA.gc_TDCl[i];
                  cbeta->gc_E[i] = BETA.gc_E[i];
                  cbeta->gc_T[i] = BETA.gc_T[i];
               }
               cbeta->ab_hit = BETA.ab_hit;
               for(int i=0; i<BETA.ab_hit; i++){
                  cbeta->ab_ch[i] = BETA.ab_ch[i];
                  //cbeta->ab_DGFe[i] = BETA.ab_DGFe[i];
                  //cbeta->ab_DGFt[i] = BETA.ab_DGFt[i];
                  cbeta->ab_TDCs[i] = BETA.ab_TDCs[i];
                  cbeta->ab_TDCl[i] = BETA.ab_TDCl[i];
                  cbeta->ab_E[i] = BETA.ab_E[i];
                  cbeta->ab_T[i] = BETA.ab_T[i];
               }
               bEntry_best = 0;
               deltaz_min=2;
               decay_index++;
            }
            current_time = beta_ts;
            if(ion_x>=beta_x1-1 && ion_x<=beta_x2+1 && ion_y>=beta_y1-1 && ion_y<=beta_y2+1){
               if(abs(beta_z-ion_z)<deltaz_min){
                  bEntry_best = bEntry;
                  deltaz_min = abs(beta_z-ion_z);
               }
            }
            imtsb++;
         }else{
            if(ion_x>=beta_x1-1 && ion_x<=beta_x2+1 && ion_y>=beta_y1-1 && ion_y<=beta_y2+1){
               if(abs(beta_z-ion_z)<deltaz_min){
                  bEntry_best = bEntry;
                  deltaz_min = abs(beta_z-ion_z);
               }
            }
            imtsb++;
         }
         if(imtsb->first > ts2){
            if(bEntry_best != 0){
               BETA.GetEntry(bEntry_best);
               cbeta = new(tcbeta[decay_index]) CDecay();
               cbeta->t = BETA.ts - ION.ts;
               cbeta->z = BETA.z;
               cbeta->x = BETA.x;
               cbeta->y = BETA.y;
               cbeta->ex = BETA.ex;
               cbeta->ey = BETA.ey;
               cbeta->mulx = BETA.x2-BETA.x1+1;
               cbeta->muly = BETA.y2-BETA.y1+1;
               cbeta->deltaz = abs(ION.z-BETA.z);
               cbeta->deltaxy = sqrt((BETA.x-ion_x)*(BETA.x-ion_x)+(BETA.y-ion_y)*(BETA.y-ion_y));
               cbeta->E = BETA.dssd_E;
               memcpy(cbeta->dssd_fire, BETA.dssd_fire, sizeof(BETA.dssd_fire));
               memcpy(cbeta->dssd_ex, BETA.dssd_ex, sizeof(BETA.dssd_ex));
               memcpy(cbeta->dssd_ey, BETA.dssd_ey, sizeof(BETA.dssd_ey));
               memcpy(cbeta->dssd_zmult, BETA.dssd_zmult, sizeof(BETA.dssd_zmult));
               memcpy(cbeta->dssd_x, BETA.dssd_x, sizeof(BETA.dssd_x));
               memcpy(cbeta->dssd_y, BETA.dssd_y, sizeof(BETA.dssd_y));

               Int_t flag_U=0, flag_D=0;
               if(ion_z-1>=0){
                  if(cbeta->dssd_fire[ion_z-1]>0){
                     flag_U=1;
                  }
               }
               if(ion_z+1<NumDSSD){
                  if(cbeta->dssd_fire[ion_z+1]>0){
                     flag_D=1;
                  }
               }
               if(flag_U==0 && flag_D==0){
                  cbeta->flag_side = 0;
               }
               if(flag_U==1 && flag_D==0){
                  cbeta->flag_side = -1;
               }
               if(flag_U==0 && flag_D==1){
                  cbeta->flag_side = 1;
               }
               if(flag_U==1 && flag_D==1){
                  cbeta->flag_side = 2;
               }
               //cout<<"flag_U="<<flag_U<<", flag_D="<<flag_D<<", flag_side="<<cbeta->flag_side<<endl;

               cbeta->Qbeta_E = BETA.Qbeta_E;
               cbeta->Qbeta_T = BETA.Qbeta_T;
               cbeta->Qveto_E = BETA.Qveto_E;
               cbeta->Qveto_T = BETA.Qveto_T;

               //memcpy(cbeta->NaI_E, BETA.NaI_E, sizeof(BETA.NaI_E));
               //memcpy(cbeta->NaI_T, BETA.NaI_T, sizeof(BETA.NaI_T));

               cbeta->gc_hit = BETA.gc_hit;
               for(int i=0; i<BETA.gc_hit; i++){
                  cbeta->gc_ch[i] = BETA.gc_ch[i];
                  //cbeta->gc_DGFe[i] = BETA.gc_DGFe[i];
                  //cbeta->gc_DGFt[i] = BETA.gc_DGFt[i];
                  cbeta->gc_TDCs[i] = BETA.gc_TDCs[i];
                  cbeta->gc_TDCl[i] = BETA.gc_TDCl[i];
                  cbeta->gc_E[i] = BETA.gc_E[i];
                  cbeta->gc_T[i] = BETA.gc_T[i];
               }
               cbeta->ab_hit = BETA.ab_hit;
               for(int i=0; i<BETA.ab_hit; i++){
                  cbeta->ab_ch[i] = BETA.ab_ch[i];
                  //cbeta->ab_DGFe[i] = BETA.ab_DGFe[i];
                  //cbeta->ab_DGFt[i] = BETA.ab_DGFt[i];
                  cbeta->ab_TDCs[i] = BETA.ab_TDCs[i];
                  cbeta->ab_TDCl[i] = BETA.ab_TDCl[i];
                  cbeta->ab_E[i] = BETA.ab_E[i];
                  cbeta->ab_T[i] = BETA.ab_T[i];
               }
               bEntry_best = 0;
               deltaz_min=2;
               decay_index++;
            }
         }
      }

      tcbg.Clear();
      ts2 = imtsi->first - time_window/10;
      int bg_index=0;
      current_time = 0;
      bEntry_best = 0;
      deltaz_min=2;
      //cout<<iEntry<<" lines finished 1"<<endl;
      ts1 = imtsi->first - 3*time_window/10; //100us as dead time
      imtsb = bg_present;
      while(imtsb!=mtsb.end() && imtsb->first<ts2){
         beta_ts = imtsb->first;
         if(beta_ts<ts1){
            bg_present++;
            imtsb = bg_present;
            continue;
         }
         bEntry = imtsb->second.first.first;
         beta_z = imtsb->second.first.second;
         beta_x1 = imtsb->second.second.first.first;
         beta_x2 = imtsb->second.second.first.second;
         beta_y1 = imtsb->second.second.second.first;
         beta_y2 = imtsb->second.second.second.second;
         if(beta_ts!=current_time){
            if(bEntry_best != 0){
               BETA.GetEntry(bEntry_best);
               cbg = new(tcbg[bg_index]) CDecay();
               cbg->t = ION.ts - BETA.ts;
               cbg->z = BETA.z;
               cbg->x = BETA.x;
               cbg->y = BETA.y;
               cbg->ex = BETA.ex;
               cbg->ey = BETA.ey;
               cbg->mulx = BETA.x2-BETA.x1+1;
               cbg->muly = BETA.y2-BETA.y1+1;
               cbg->deltaz = abs(ION.z-BETA.z);
               cbg->deltaxy = sqrt((BETA.x-ion_x)*(BETA.x-ion_x)+(BETA.y-ion_y)*(BETA.y-ion_y));
               cbg->E = BETA.dssd_E;
               memcpy(cbg->dssd_fire, BETA.dssd_fire, sizeof(BETA.dssd_fire));
               memcpy(cbg->dssd_ex, BETA.dssd_ex, sizeof(BETA.dssd_ex));
               memcpy(cbg->dssd_ey, BETA.dssd_ey, sizeof(BETA.dssd_ey));
               memcpy(cbg->dssd_zmult, BETA.dssd_zmult, sizeof(BETA.dssd_zmult));
               memcpy(cbg->dssd_x, BETA.dssd_x, sizeof(BETA.dssd_x));
               memcpy(cbg->dssd_y, BETA.dssd_y, sizeof(BETA.dssd_y));

               Int_t flag_U=0, flag_D=0;
               if(ion_z-1>=0){
                  if(cbg->dssd_fire[ion_z-1]>0){
                     flag_U=1;
                  }
               }
               if(ion_z+1<NumDSSD){
                  if(cbg->dssd_fire[ion_z+1]>0){
                     flag_D=1;
                  }
               }
               if(flag_U==0 && flag_D==0){
                  cbg->flag_side = 0;
               }
               if(flag_U==1 && flag_D==0){
                  cbg->flag_side = -1;
               }
               if(flag_U==0 && flag_D==1){
                  cbg->flag_side = 1;
               }
               if(flag_U==1 && flag_D==1){
                  cbg->flag_side = 2;
               }
               cbg->Qbeta_E = BETA.Qbeta_E;
               cbg->Qbeta_T = BETA.Qbeta_T;
               cbg->Qveto_E = BETA.Qveto_E;
               cbg->Qveto_T = BETA.Qveto_T;

               //memcpy(cbg->NaI_E, BETA.NaI_E, sizeof(BETA.NaI_E));
               //memcpy(cbg->NaI_T, BETA.NaI_T, sizeof(BETA.NaI_T));

               cbg->gc_hit = BETA.gc_hit;
               for(int i=0; i<BETA.gc_hit; i++){
                  cbg->gc_ch[i] = BETA.gc_ch[i];
                  //cbg->gc_DGFe[i] = BETA.gc_DGFe[i];
                  //cbg->gc_DGFt[i] = BETA.gc_DGFt[i];
                  cbg->gc_TDCs[i] = BETA.gc_TDCs[i];
                  cbg->gc_TDCl[i] = BETA.gc_TDCl[i];
                  cbg->gc_E[i] = BETA.gc_E[i];
                  cbg->gc_T[i] = BETA.gc_T[i];
               }
               cbg->ab_hit = BETA.ab_hit;
               for(int i=0; i<BETA.ab_hit; i++){
                  cbg->ab_ch[i] = BETA.ab_ch[i];
                  //cbg->ab_DGFe[i] = BETA.ab_DGFe[i];
                  //cbg->ab_DGFt[i] = BETA.ab_DGFt[i];
                  cbg->ab_TDCs[i] = BETA.ab_TDCs[i];
                  cbg->ab_TDCl[i] = BETA.ab_TDCl[i];
                  cbg->ab_E[i] = BETA.ab_E[i];
                  cbg->ab_T[i] = BETA.ab_T[i];
               }
               bEntry_best = 0;
               deltaz_min=2;
               bg_index++;
            }
            current_time = beta_ts;
            if(ion_x>=beta_x1-1 && ion_x<=beta_x2+1 && ion_y>=beta_y1-1 && ion_y<=beta_y2+1){
               if(abs(beta_z-ion_z)<deltaz_min){
                  bEntry_best = bEntry;
                  deltaz_min = abs(beta_z-ion_z);
               }
            }
            imtsb++;
         }else{
            if(ion_x>=beta_x1-1 && ion_x<=beta_x2+1 && ion_y>=beta_y1-1 && ion_y<=beta_y2+1){
               if(abs(beta_z-ion_z)<deltaz_min){
                  bEntry_best = bEntry;
                  deltaz_min = abs(beta_z-ion_z);
               }
            }
            imtsb++;
         }
         if(imtsb->first > ts2){
            if(bEntry_best != 0){
               BETA.GetEntry(bEntry_best);
               cbg = new(tcbg[bg_index]) CDecay();
               cbg->t = ION.ts - BETA.ts;
               cbg->z = BETA.z;
               cbg->x = BETA.x;
               cbg->y = BETA.y;
               cbg->ex = BETA.ex;
               cbg->ey = BETA.ey;
               cbg->mulx = BETA.x2-BETA.x1+1;
               cbg->muly = BETA.y2-BETA.y1+1;
               cbg->deltaz = abs(ION.z-BETA.z);
               cbg->deltaxy = sqrt((BETA.x-ion_x)*(BETA.x-ion_x)+(BETA.y-ion_y)*(BETA.y-ion_y));
               cbg->E = BETA.dssd_E;
               memcpy(cbg->dssd_fire, BETA.dssd_fire, sizeof(BETA.dssd_fire));
               memcpy(cbg->dssd_ex, BETA.dssd_ex, sizeof(BETA.dssd_ex));
               memcpy(cbg->dssd_ey, BETA.dssd_ey, sizeof(BETA.dssd_ey));
               memcpy(cbg->dssd_zmult, BETA.dssd_zmult, sizeof(BETA.dssd_zmult));
               memcpy(cbg->dssd_x, BETA.dssd_x, sizeof(BETA.dssd_x));
               memcpy(cbg->dssd_y, BETA.dssd_y, sizeof(BETA.dssd_y));

               Int_t flag_U=0, flag_D=0;
               if(ion_z-1>=0){
                  if(cbg->dssd_fire[ion_z-1]>0){
                     flag_U=1;
                  }
               }
               if(ion_z+1<NumDSSD){
                  if(cbg->dssd_fire[ion_z+1]>0){
                     flag_D=1;
                  }
               }
               if(flag_U==0 && flag_D==0){
                  cbg->flag_side = 0;
               }
               if(flag_U==1 && flag_D==0){
                  cbg->flag_side = -1;
               }
               if(flag_U==0 && flag_D==1){
                  cbg->flag_side = 1;
               }
               if(flag_U==1 && flag_D==1){
                  cbg->flag_side = 2;
               }
               cbg->Qbeta_E = BETA.Qbeta_E;
               cbg->Qbeta_T = BETA.Qbeta_T;
               cbg->Qveto_E = BETA.Qveto_E;
               cbg->Qveto_T = BETA.Qveto_T;

               //memcpy(cbg->NaI_E, BETA.NaI_E, sizeof(BETA.NaI_E));
               //memcpy(cbg->NaI_T, BETA.NaI_T, sizeof(BETA.NaI_T));

               cbg->gc_hit = BETA.gc_hit;
               for(int i=0; i<BETA.gc_hit; i++){
                  cbg->gc_ch[i] = BETA.gc_ch[i];
                  //cbg->gc_DGFe[i] = BETA.gc_DGFe[i];
                  //cbg->gc_DGFt[i] = BETA.gc_DGFt[i];
                  cbg->gc_TDCs[i] = BETA.gc_TDCs[i];
                  cbg->gc_TDCl[i] = BETA.gc_TDCl[i];
                  cbg->gc_E[i] = BETA.gc_E[i];
                  cbg->gc_T[i] = BETA.gc_T[i];
               }
               cbg->ab_hit = BETA.ab_hit;
               for(int i=0; i<BETA.ab_hit; i++){
                  cbg->ab_ch[i] = BETA.ab_ch[i];
                  //cbg->ab_DGFe[i] = BETA.ab_DGFe[i];
                  //cbg->ab_DGFt[i] = BETA.ab_DGFt[i];
                  cbg->ab_TDCs[i] = BETA.ab_TDCs[i];
                  cbg->ab_TDCl[i] = BETA.ab_TDCl[i];
                  cbg->ab_E[i] = BETA.ab_E[i];
                  cbg->ab_T[i] = BETA.ab_T[i];
               }
               bEntry_best = 0;
               deltaz_min=2;
               bg_index++;
            }
         }
      }
      decay->Fill();
   }
   rootfile->Write();
   rootfile->Close();
}
