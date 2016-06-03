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

#include"DecayEvent.cxx"
#include"decay_ggmatrix.h"

using namespace std;

int main(int argc, char* argv[]){

   if(argc<2){
      cout<<"USAGE: BuildDecay_Select #DECAYRUN"<<endl;
      return 0;
   }

   int runD = atoi(argv[1]);
   char decayfile[128];
   char outfile[128];

   sprintf(decayfile,"../root/sistopper/cu81test/decay_new%04d.root",runD);
   //sprintf(decayfile,"go4.root");
   sprintf(outfile,"../gamma_db/decay_new_cu78_%04d.root",runD);

   decay_ggmatrix ggdecay(decayfile);

   Long64_t dEntry, dEntryMAX;  //entry for decay
   TFile *rootfile = new TFile(outfile,"RECREATE");

   TTree *decay = new TTree("decay","decay");
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

   dEntryMAX = ggdecay.fChain->GetEntriesFast();

   for(dEntry = 0; dEntry < dEntryMAX; dEntry++){
      if(dEntry%1000 == 0){
         cout<<"RUN#"<<runD<<", "<<dEntry<<" lines finished."<<endl;
      }

      ggdecay.GetEntry(dEntry);
      imp->run = runD;
      imp->ts = ggdecay.ts;
      imp->z = ggdecay.z;
      imp->x = ggdecay.x;
      imp->y = ggdecay.y;
      imp->tx = ggdecay.tx;
      imp->ty = ggdecay.ty;

      imp->beta35 = ggdecay.beta35;
      imp->beta57 = ggdecay.beta57;
      imp->beta711 = ggdecay.beta711;
      imp->aoq37 = ggdecay.aoq37;
      imp->zed = ggdecay.zed;
      imp->Zed = ggdecay.Zed;
      imp->Mass = ggdecay.Mass;
      imp->flagall = ggdecay.flagall;
      imp->flagTSumX = ggdecay.flagTSumX;
      imp->flagTOFt = ggdecay.flagTOFt;
      imp->flagTOFq = ggdecay.flagTOFq;
      imp->flagReaction = ggdecay.flagReaction;
      imp->flagdERelation = ggdecay.flagdERelation;
      imp->flagAngle = ggdecay.flagAngle;
      imp->IfInterest = ggdecay.IfInterest;

      if(imp->Zed != 29 || imp->Mass != 78){
         continue;
      }

      tcbeta.Clear();
      for(int i=0; i<ggdecay.beta_; i++){
         cbeta = new(tcbeta[i]) CDecay();
         cbeta->t = ggdecay.beta_t[i];
         cbeta->z = ggdecay.beta_z[i];
         cbeta->x = ggdecay.beta_x[i];
         cbeta->y = ggdecay.beta_y[i];
         cbeta->E = ggdecay.beta_E[i];
         cbeta->ex = ggdecay.beta_ex[i];
         cbeta->ey = ggdecay.beta_ey[i];
         cbeta->mulx = ggdecay.beta_mulx[i];
         cbeta->muly = ggdecay.beta_muly[i];
         cbeta->deltaz = ggdecay.beta_deltaz[i];
         cbeta->deltaxy = ggdecay.beta_deltaxy[i];
         cbeta->flag_side = ggdecay.beta_flag_side[i];
         memcpy(cbeta->dssd_fire, ggdecay.beta_dssd_fire[i], sizeof(ggdecay.beta_dssd_fire[i]));
         memcpy(cbeta->dssd_ex, ggdecay.beta_dssd_ex[i], sizeof(ggdecay.beta_dssd_ex[i]));
         memcpy(cbeta->dssd_ey, ggdecay.beta_dssd_ey[i], sizeof(ggdecay.beta_dssd_ey[i]));
         memcpy(cbeta->dssd_zmult, ggdecay.beta_dssd_zmult[i], sizeof(ggdecay.beta_dssd_zmult[i]));
         memcpy(cbeta->dssd_x, ggdecay.beta_dssd_x[i], sizeof(ggdecay.beta_dssd_x[i]));
         memcpy(cbeta->dssd_y, ggdecay.beta_dssd_y[i], sizeof(ggdecay.beta_dssd_y[i]));
         cbeta->Qbeta_E = ggdecay.beta_Qbeta_E[i];
         cbeta->Qbeta_T = ggdecay.beta_Qbeta_T[i];
         cbeta->Qveto_E = ggdecay.beta_Qveto_E[i];
         cbeta->Qveto_T = ggdecay.beta_Qveto_T[i];
         //memcpy(cbeta->NaI_E, ggdecay.beta_NaI_E[i], sizeof(ggdecay.beta_NaI_E[i]));
         //memcpy(cbeta->NaI_T, ggdecay.beta_NaI_T[i], sizeof(ggdecay.beta_NaI_T[i]));

         cbeta->gc_hit = ggdecay.beta_gc_hit[i];
         memcpy(cbeta->gc_ch, ggdecay.beta_gc_ch[i], sizeof(ggdecay.beta_gc_ch[i]));
         //memcpy(cbeta->gc_DGFe, ggdecay.beta_gc_DGFe[i], sizeof(ggdecay.beta_gc_DGFe[i]));
         //memcpy(cbeta->gc_DGFt, ggdecay.beta_gc_DGFt[i], sizeof(ggdecay.beta_gc_DGFt[i]));
         memcpy(cbeta->gc_TDCs, ggdecay.beta_gc_TDCs[i], sizeof(ggdecay.beta_gc_TDCs[i]));
         memcpy(cbeta->gc_TDCl, ggdecay.beta_gc_TDCl[i], sizeof(ggdecay.beta_gc_TDCl[i]));
         memcpy(cbeta->gc_E, ggdecay.beta_gc_E[i], sizeof(ggdecay.beta_gc_E[i]));
         memcpy(cbeta->gc_T, ggdecay.beta_gc_T[i], sizeof(ggdecay.beta_gc_T[i]));

         cbeta->ab_hit = ggdecay.beta_ab_hit[i];
         memcpy(cbeta->ab_ch, ggdecay.beta_ab_ch[i], sizeof(ggdecay.beta_ab_ch[i]));
         //memcpy(cbeta->ab_DGFe, ggdecay.beta_ab_DGFe[i], sizeof(ggdecay.beta_ab_DGFe[i]));
         //memcpy(cbeta->ab_DGFt, ggdecay.beta_ab_DGFt[i], sizeof(ggdecay.beta_ab_DGFt[i]));
         memcpy(cbeta->ab_TDCs, ggdecay.beta_ab_TDCs[i], sizeof(ggdecay.beta_ab_TDCs[i]));
         memcpy(cbeta->ab_TDCl, ggdecay.beta_ab_TDCl[i], sizeof(ggdecay.beta_ab_TDCl[i]));
         memcpy(cbeta->ab_E, ggdecay.beta_ab_E[i], sizeof(ggdecay.beta_ab_E[i]));
         memcpy(cbeta->ab_T, ggdecay.beta_ab_T[i], sizeof(ggdecay.beta_ab_T[i]));
      }

      tcbg.Clear();
      for(int i=0; i<ggdecay.bg_; i++){
         cbg = new(tcbg[i]) CDecay();
         cbg->t = ggdecay.bg_t[i];
         cbg->z = ggdecay.bg_z[i];
         cbg->x = ggdecay.bg_x[i];
         cbg->y = ggdecay.bg_y[i];
         cbg->E = ggdecay.bg_E[i];
         cbg->ex = ggdecay.bg_ex[i];
         cbg->ey = ggdecay.bg_ey[i];
         cbg->mulx = ggdecay.bg_mulx[i];
         cbg->muly = ggdecay.bg_muly[i];
         cbg->deltaz = ggdecay.bg_deltaz[i];
         cbg->deltaxy = ggdecay.bg_deltaxy[i];
         cbg->flag_side = ggdecay.bg_flag_side[i];
         memcpy(cbg->dssd_fire, ggdecay.bg_dssd_fire[i], sizeof(ggdecay.bg_dssd_fire[i]));
         memcpy(cbg->dssd_ex, ggdecay.bg_dssd_ex[i], sizeof(ggdecay.bg_dssd_ex[i]));
         memcpy(cbg->dssd_ey, ggdecay.bg_dssd_ey[i], sizeof(ggdecay.bg_dssd_ey[i]));
         memcpy(cbg->dssd_zmult, ggdecay.bg_dssd_zmult[i], sizeof(ggdecay.bg_dssd_zmult[i]));
         memcpy(cbg->dssd_x, ggdecay.bg_dssd_x[i], sizeof(ggdecay.bg_dssd_x[i]));
         memcpy(cbg->dssd_y, ggdecay.bg_dssd_y[i], sizeof(ggdecay.bg_dssd_y[i]));
         cbg->Qbeta_E = ggdecay.bg_Qbeta_E[i];
         cbg->Qbeta_T = ggdecay.bg_Qbeta_T[i];
         cbg->Qveto_E = ggdecay.bg_Qveto_E[i];
         cbg->Qveto_T = ggdecay.bg_Qveto_T[i];
         //memcpy(cbg->NaI_E, ggdecay.bg_NaI_E[i], sizeof(ggdecay.bg_NaI_E[i]));
         //memcpy(cbg->NaI_T, ggdecay.bg_NaI_T[i], sizeof(ggdecay.bg_NaI_T[i]));

         cbg->gc_hit = ggdecay.bg_gc_hit[i];
         memcpy(cbg->gc_ch, ggdecay.bg_gc_ch[i], sizeof(ggdecay.bg_gc_ch[i]));
         //memcpy(cbg->gc_DGFe, ggdecay.bg_gc_DGFe[i], sizeof(ggdecay.bg_gc_DGFe[i]));
         //memcpy(cbg->gc_DGFt, ggdecay.bg_gc_DGFt[i], sizeof(ggdecay.bg_gc_DGFt[i]));
         memcpy(cbg->gc_TDCs, ggdecay.bg_gc_TDCs[i], sizeof(ggdecay.bg_gc_TDCs[i]));
         memcpy(cbg->gc_TDCl, ggdecay.bg_gc_TDCl[i], sizeof(ggdecay.bg_gc_TDCl[i]));
         memcpy(cbg->gc_E, ggdecay.bg_gc_E[i], sizeof(ggdecay.bg_gc_E[i]));
         memcpy(cbg->gc_T, ggdecay.bg_gc_T[i], sizeof(ggdecay.bg_gc_T[i]));

         cbg->ab_hit = ggdecay.bg_ab_hit[i];
         memcpy(cbg->ab_ch, ggdecay.bg_ab_ch[i], sizeof(ggdecay.bg_ab_ch[i]));
         //memcpy(cbg->ab_DGFe, ggdecay.bg_ab_DGFe[i], sizeof(ggdecay.bg_ab_DGFe[i]));
         //memcpy(cbg->ab_DGFt, ggdecay.bg_ab_DGFt[i], sizeof(ggdecay.bg_ab_DGFt[i]));
         memcpy(cbg->ab_TDCs, ggdecay.bg_ab_TDCs[i], sizeof(ggdecay.bg_ab_TDCs[i]));
         memcpy(cbg->ab_TDCl, ggdecay.bg_ab_TDCl[i], sizeof(ggdecay.bg_ab_TDCl[i]));
         memcpy(cbg->ab_E, ggdecay.bg_ab_E[i], sizeof(ggdecay.bg_ab_E[i]));
         memcpy(cbg->ab_T, ggdecay.bg_ab_T[i], sizeof(ggdecay.bg_ab_T[i]));
      }
      decay->Fill();
   }
   rootfile->Write();
   rootfile->Close();
   cout<<"finished"<<endl;
}
