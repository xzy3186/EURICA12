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

Double_t rand05()
{
  return rand()*1./RAND_MAX - 0.5;
}

int main(int argc, char* argv[]){

   Int_t run;
   Int_t imp_z;
   Int_t imp_x;
   Int_t imp_y;
   Double_t beta35;
   Double_t beta57;
   Double_t beta711;
   Double_t aoq37;
   Double_t zed;
   Int_t Zed;
   Int_t Mass;
   Int_t flagall;

   Long64_t beta_t;
   Int_t beta_ex;
   Int_t beta_ey;
   Int_t beta_mulx;
   Int_t beta_muly;
   Int_t beta_flag_side; //-1: upstream fired; 0: none side fired, 1: downstream fired; 2: both sides fired.
   Int_t beta_deltaz;
   Double_t beta_deltaxy;
   Int_t beta_Qbeta_E;
   Int_t beta_Qbeta_T;
   Int_t beta_Qveto_E;
   Int_t beta_Qveto_T;
   Int_t beta_gc_hit;
   Int_t beta_gc_ch[84];
   Double_t beta_gc_E[84];
   Double_t beta_gc_T[84];
   Int_t beta_ab_hit;
   Int_t beta_ab_ch[84];
   Double_t beta_ab_E[84];
   Double_t beta_ab_T[84];

   Long64_t bg_t;
   Int_t bg_ex;
   Int_t bg_ey;
   Int_t bg_mulx;
   Int_t bg_muly;
   Int_t bg_flag_side; //-1: upstream fired; 0: none side fired, 1: downstream fired; 2: both sides fired.
   Int_t bg_deltaz;
   Double_t bg_deltaxy;
   Int_t bg_Qbeta_E;
   Int_t bg_Qbeta_T;
   Int_t bg_Qveto_E;
   Int_t bg_Qveto_T;
   Int_t bg_gc_hit;
   Int_t bg_gc_ch[84];
   Double_t bg_gc_E[84];
   Double_t bg_gc_T[84];
   Int_t bg_ab_hit;
   Int_t bg_ab_ch[84];
   Double_t bg_ab_E[84];
   Double_t bg_ab_T[84];

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
   TTree *bg = new TTree("bg","bg");

   decay->Branch("run",&run,"run/I");
   decay->Branch("z",&imp_z,"z/I");
   decay->Branch("x",&imp_x,"x/I");
   decay->Branch("y",&imp_y,"y/I");
   decay->Branch("beta35",&beta35,"beta35/D");
   decay->Branch("beta57",&beta57,"beta57/D");
   decay->Branch("beta711",&beta711,"beta711/D");
   decay->Branch("aoq37",&aoq37,"aoq37/D");
   decay->Branch("zed",&zed,"zed/D");
   decay->Branch("Zed",&Zed,"Zed/I");
   decay->Branch("Mass",&Mass,"Mass/I");
   decay->Branch("flagall",&flagall,"flagall/I");

   decay->Branch("t",&beta_t,"t/L");
   decay->Branch("ex",&beta_ex,"ex/I");
   decay->Branch("ey",&beta_ey,"ey/I");
   decay->Branch("mulx",&beta_mulx,"mulx/I");
   decay->Branch("muly",&beta_muly,"muly/I");
   decay->Branch("flag_side",&beta_flag_side,"flag_side/I");
   decay->Branch("deltaz",&beta_deltaz,"deltaz/I");
   decay->Branch("deltaxy",&beta_deltaxy,"deltaxy/D");
   decay->Branch("Qbeta_E",&beta_Qbeta_E,"Qbeta_E/I");
   decay->Branch("Qbeta_T",&beta_Qbeta_T,"Qbeta_T/I");
   decay->Branch("Qveto_E",&beta_Qveto_E,"Qveto_E/I");
   decay->Branch("Qveto_T",&beta_Qveto_T,"Qveto_T/I");
   decay->Branch("gc_hit",&beta_gc_hit,"gc_hit/I");
   decay->Branch("gc_ch",beta_gc_ch,"gc_ch[gc_hit]/I");
   decay->Branch("gc_E",beta_gc_E,"gc_E[gc_hit]/D");
   decay->Branch("gc_T",beta_gc_T,"gc_T[gc_hit]/D");
   decay->Branch("ab_hit",&beta_ab_hit,"ab_hit/I");
   decay->Branch("ab_ch",beta_ab_ch,"gc_ch[ab_hit]/I");
   decay->Branch("ab_E",beta_ab_E,"gc_E[ab_hit]/D");
   decay->Branch("ab_T",beta_ab_T,"gc_T[ab_hit]/D");

   bg->Branch("run",&run,"run/I");
   bg->Branch("z",&imp_z,"z/I");
   bg->Branch("x",&imp_x,"x/I");
   bg->Branch("y",&imp_y,"y/I");
   bg->Branch("beta35",&beta35,"beta35/D");
   bg->Branch("beta57",&beta57,"beta57/D");
   bg->Branch("beta711",&beta711,"beta711/D");
   bg->Branch("aoq37",&aoq37,"aoq37/D");
   bg->Branch("zed",&zed,"zed/D");
   bg->Branch("Zed",&Zed,"Zed/I");
   bg->Branch("Mass",&Mass,"Mass/I");
   bg->Branch("flagall",&flagall,"flagall/I");

   bg->Branch("t",&bg_t,"t/L");
   bg->Branch("ex",&bg_ex,"ex/I");
   bg->Branch("ey",&bg_ey,"ey/I");
   bg->Branch("mulx",&bg_mulx,"mulx/I");
   bg->Branch("muly",&bg_muly,"muly/I");
   bg->Branch("flag_side",&bg_flag_side,"flag_side/I");
   bg->Branch("deltaz",&bg_deltaz,"deltaz/I");
   bg->Branch("deltaxy",&bg_deltaxy,"deltaxy/D");
   bg->Branch("Qbeta_E",&beta_Qbeta_E,"Qbeta_E/I");
   bg->Branch("Qbeta_T",&beta_Qbeta_T,"Qbeta_T/I");
   bg->Branch("Qveto_E",&beta_Qveto_E,"Qveto_E/I");
   bg->Branch("Qveto_T",&beta_Qveto_T,"Qveto_T/I");
   bg->Branch("gc_hit",&bg_gc_hit,"gc_hit/I");
   bg->Branch("gc_ch",bg_gc_ch,"gc_ch[gc_hit]/I");
   bg->Branch("gc_E",bg_gc_E,"gc_E[gc_hit]/D");
   bg->Branch("gc_T",bg_gc_T,"gc_T[gc_hit]/D");
   bg->Branch("ab_hit",&bg_ab_hit,"ab_hit/I");
   bg->Branch("ab_ch",bg_ab_ch,"ab_ch[gc_hit]/I");
   bg->Branch("ab_E",bg_ab_E,"gc_E[ab_hit]/D");
   bg->Branch("ab_T",bg_ab_T,"gc_T[ab_hit]/D");

   dEntryMAX = ggdecay.fChain->GetEntriesFast();

   for(dEntry = 0; dEntry < dEntryMAX; dEntry++){
      if(dEntry%1000 == 0){
         cout<<"RUN#"<<runD<<", "<<dEntry<<" lines finished."<<endl;
      }

      ggdecay.GetEntry(dEntry);
      run = runD;
      imp_z = ggdecay.z;
      imp_x = ggdecay.x;
      imp_y = ggdecay.y;
      beta35 = ggdecay.beta35;
      beta57 = ggdecay.beta57;
      beta711 = ggdecay.beta711;
      aoq37 = ggdecay.aoq37;
      zed = ggdecay.zed;
      Zed = ggdecay.Zed;
      Mass = ggdecay.Mass;
      flagall = ggdecay.flagall;

      if(Zed != 29 || Mass != 78){
         continue;
      }

      for(int i=0; i<ggdecay.beta_; i++){
         beta_t = ggdecay.beta_t[i];
         beta_ex = ggdecay.beta_ex[i];
         beta_ey = ggdecay.beta_ey[i];
         beta_mulx = ggdecay.beta_mulx[i];
         beta_muly = ggdecay.beta_muly[i];
         beta_deltaz = ggdecay.beta_deltaz[i];
         beta_deltaxy = ggdecay.beta_deltaxy[i];
         beta_flag_side = ggdecay.beta_flag_side[i];
         if(ggdecay.beta_Qbeta_E[i]>0){
            beta_Qbeta_E = 3.458*(ggdecay.beta_Qbeta_E[i]+rand05())+738.0;
         }else{
            beta_Qbeta_E = ggdecay.beta_Qbeta_E[i];
         }
         beta_Qbeta_T = ggdecay.beta_Qbeta_T[i];
         beta_Qveto_E = ggdecay.beta_Qveto_E[i];
         beta_Qveto_T = ggdecay.beta_Qveto_T[i];

         beta_gc_hit = ggdecay.beta_gc_hit[i];
         beta_ab_hit = ggdecay.beta_ab_hit[i];

         memcpy(beta_gc_ch, ggdecay.beta_gc_ch[i], sizeof(ggdecay.beta_gc_ch[i]));
         memcpy(beta_gc_E, ggdecay.beta_gc_E[i], sizeof(ggdecay.beta_gc_E[i]));
         memcpy(beta_gc_T, ggdecay.beta_gc_T[i], sizeof(ggdecay.beta_gc_T[i]));

         memcpy(beta_ab_ch, ggdecay.beta_ab_ch[i], sizeof(ggdecay.beta_ab_ch[i]));
         memcpy(beta_ab_E, ggdecay.beta_ab_E[i], sizeof(ggdecay.beta_ab_E[i]));
         memcpy(beta_ab_T, ggdecay.beta_ab_T[i], sizeof(ggdecay.beta_ab_T[i]));
         decay->Fill();
      }

      for(int i=0; i<ggdecay.bg_; i++){
         bg_t = ggdecay.bg_t[i];
         bg_ex = ggdecay.bg_ex[i];
         bg_ey = ggdecay.bg_ey[i];
         bg_mulx = ggdecay.bg_mulx[i];
         bg_muly = ggdecay.bg_muly[i];
         bg_deltaz = ggdecay.bg_deltaz[i];
         bg_deltaxy = ggdecay.bg_deltaxy[i];
         bg_flag_side = ggdecay.bg_flag_side[i];
         if(ggdecay.beta_Qbeta_E[i]>0){
            bg_Qbeta_E = 3.458*(ggdecay.beta_Qbeta_E[i]+rand05())+738.0;
         }else{
            bg_Qbeta_E = ggdecay.beta_Qbeta_E[i];
         }
         bg_Qbeta_T = ggdecay.beta_Qbeta_T[i];
         bg_Qveto_E = ggdecay.beta_Qveto_E[i];
         bg_Qveto_T = ggdecay.beta_Qveto_T[i];

         bg_gc_hit = ggdecay.bg_gc_hit[i];
         bg_ab_hit = ggdecay.bg_ab_hit[i];

         memcpy(bg_gc_ch, ggdecay.bg_gc_ch[i], sizeof(ggdecay.bg_gc_ch[i]));
         memcpy(bg_gc_E, ggdecay.bg_gc_E[i], sizeof(ggdecay.bg_gc_E[i]));
         memcpy(bg_gc_T, ggdecay.bg_gc_T[i], sizeof(ggdecay.bg_gc_T[i]));

         memcpy(bg_ab_ch, ggdecay.bg_ab_ch[i], sizeof(ggdecay.bg_ab_ch[i]));
         memcpy(bg_ab_E, ggdecay.bg_ab_E[i], sizeof(ggdecay.bg_ab_E[i]));
         memcpy(bg_ab_T, ggdecay.bg_ab_T[i], sizeof(ggdecay.bg_ab_T[i]));
         bg->Fill();
      }
   }
   rootfile->Write();
   rootfile->Close();
   cout<<"finished"<<endl;
}
