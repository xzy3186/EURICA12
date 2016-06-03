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

   Double_t beta35;
   Double_t beta57;
   Double_t beta711;
   Double_t aoq37;
   Double_t zed;

   Int_t Zed;
   Int_t Mass;
   Int_t flagall;

   Long64_t t;
   Int_t z;
   Float_t x;
   Float_t y;
   Int_t ex;
   Int_t ey;
   Int_t mulx;
   Int_t muly;
   Int_t flag_side;
   Int_t deltaz;
   Double_t deltaxy;

   Int_t gc_matrix;
   Double_t gc1_E[7056];//(beta_index_max(10) X gc_hit_max(20))^2
   Double_t gc2_E[7056];
   Double_t gc1_T[7056];
   Double_t gc2_T[7056];
   Int_t gc_hit;
   Int_t gc_ch[84];   //[gc_hit]
   Double_t gc_E[84];   //[gc_hit]
   Double_t gc_T[84];   //[gc_hit]

   Int_t ab_matrix;
   Double_t ab1_E[7056];
   Double_t ab2_E[7056];
   Double_t ab1_T[7056];
   Double_t ab2_T[7056];
   Int_t ab_hit;
   Int_t ab_ch[84];   //[ab_hit]
   Double_t ab_E[84];   //[ab_hit]
   Double_t ab_T[84];   //[ab_hit]

   sprintf(decayfile,"../root/sistopper/ni78test/decay_new%04d.root",runD);
   //sprintf(decayfile,"go4.root");
   sprintf(outfile,"../gamma_db/ni78_%04d.root",runD);

   decay_ggmatrix ggdecay(decayfile);

   Long64_t dEntry, dEntryMAX;  //entry for decay
   TFile *rootfile = new TFile(outfile,"RECREATE");

   TTree *decay = new TTree("decay","decay");

   decay->Branch("run",&run,"run/I");
   decay->Branch("ion_z",&ion_z,"ion_z/I");
   decay->Branch("ion_x",&ion_x,"ion_x/I");
   decay->Branch("ion_y",&ion_y,"ion_y/I");

   decay->Branch("beta35", &beta35,"beta35/D");
   decay->Branch("beta57", &beta57,"beta57/D");
   decay->Branch("beta711", &beta711,"beta711/D");
   decay->Branch("aoq37", &aoq37,"aoq37/D");
   decay->Branch("zed", &zed,"zed/D");

   decay->Branch("Zed", &Zed,"Zed/I");
   decay->Branch("Mass", &Mass,"Mass/I");
   decay->Branch("flagall", &flagall,"flagall/I");

   decay->Branch("index",&index,"index/I");
   decay->Branch("t",&t,"t/L");
   decay->Branch("z",&z,"z/I");
   decay->Branch("x",&x,"x/F");
   decay->Branch("y",&y,"y/F");
   decay->Branch("ex",&ex,"ex/I");
   decay->Branch("ey",&ey,"ey/I");
   decay->Branch("mulx",&mulx,"mulx/I");
   decay->Branch("muly",&muly,"muly/I");
   decay->Branch("flag_side",&flag_side,"flag_side/I");
   decay->Branch("deltaz",&deltaz,"deltaz/I");
   decay->Branch("deltaxy",&deltaxy,"deltaxy/D");

   decay->Branch("ab_hit",&ab_hit,"ab_hit/I");
   decay->Branch("ab_ch",ab_ch,"ab_ch[ab_hit]/I");
   decay->Branch("ab_E",ab_E,"ab_E[ab_hit]/D");
   decay->Branch("ab_T",ab_T,"ab_T[ab_hit]/D");

   decay->Branch("gc_hit",&gc_hit,"gc_hit/I");
   decay->Branch("gc_ch",gc_ch,"gc_ch[gc_hit]/I");
   decay->Branch("gc_E",gc_E,"gc_E[gc_hit]/D");
   decay->Branch("gc_T",gc_T,"gc_T[gc_hit]/D");

   decay->Branch("ab_matrix",&ab_matrix,"ab_matrix/I");
   decay->Branch("ab1_E",ab1_E,"ab1_E[ab_matrix]/D");
   decay->Branch("ab2_E",ab2_E,"ab2_E[ab_matrix]/D");
   decay->Branch("ab1_T",ab1_T,"ab1_T[ab_matrix]/D");
   decay->Branch("ab2_T",ab2_T,"ab2_T[ab_matrix]/D");

   decay->Branch("gc_matrix",&gc_matrix,"gc_matrix/I");
   decay->Branch("gc1_E",gc1_E,"gc1_E[gc_matrix]/D");
   decay->Branch("gc2_E",gc2_E,"gc2_E[gc_matrix]/D");
   decay->Branch("gc1_T",gc1_T,"gc1_T[gc_matrix]/D");
   decay->Branch("gc2_T",gc2_T,"gc2_T[gc_matrix]/D");

   dEntryMAX = ggdecay.fChain->GetEntriesFast();

   for(dEntry = 0; dEntry < dEntryMAX; dEntry++){
      if(dEntry%1000 == 0){
         cout<<"RUN#"<<runD<<", "<<dEntry<<" lines finished."<<endl;
      }

      ab_matrix=0;
      gc_matrix=0;

      ggdecay.GetEntry(dEntry);
      ion_z = ggdecay.z;
      ion_x = ggdecay.x;
      ion_y = ggdecay.y;

      beta35 = ggdecay.beta35;
      beta57 = ggdecay.beta57;
      beta711 = ggdecay.beta711;
      aoq37 = ggdecay.aoq37;
      zed = ggdecay.zed;
      Zed = ggdecay.Zed;
      Mass = ggdecay.Mass;

      flagall = ggdecay.flagall;

      if(Zed != 28 || Mass != 78){
         continue;
      }

      run = ggdecay.run;
      int index_all = ggdecay.beta_;
      for(int i=0; i<index_all; i++){
         index = i;
         t = ggdecay.beta_t[i];
         z = ggdecay.beta_z[i];
         x = ggdecay.beta_x[i];
         y = ggdecay.beta_y[i];
         ex = ggdecay.beta_ex[i];
         ey = ggdecay.beta_ey[i];
         if(z>=4){
            mulx = ggdecay.beta_mulx[i]/2;
         }else{
            mulx = ggdecay.beta_mulx[i];
         }
         muly = ggdecay.beta_muly[i];
         flag_side = ggdecay.beta_flag_side[i];
         deltaz = ggdecay.beta_deltaz[i];
         deltaxy = ggdecay.beta_deltaxy[i];

         gc_hit=ggdecay.beta_gc_hit[i];
         memcpy(gc_ch, ggdecay.beta_gc_ch[i], sizeof(ggdecay.beta_gc_ch[i]));
         memcpy(gc_E, ggdecay.beta_gc_E[i], sizeof(ggdecay.beta_gc_E[i]));
         memcpy(gc_T, ggdecay.beta_gc_T[i], sizeof(ggdecay.beta_gc_T[i]));

         ggdecay.GammaAddback(i);
         ab_hit=ggdecay.beta_ab_hit[i];
         memcpy(ab_ch, ggdecay.beta_ab_ch[i], sizeof(ggdecay.beta_ab_ch[i]));
         memcpy(ab_E, ggdecay.beta_ab_E[i], sizeof(ggdecay.beta_ab_E[i]));
         memcpy(ab_T, ggdecay.beta_ab_T[i], sizeof(ggdecay.beta_ab_T[i]));

         gc_matrix = gc_hit*gc_hit;
         for(int a=0; a<gc_hit; a++){
            for(int b=0; b<gc_hit; b++){
               gc1_E[a*gc_hit+b]=gc_E[a];
               gc2_E[a*gc_hit+b]=gc_E[b];
               gc1_T[a*gc_hit+b]=gc_T[a];
               gc2_T[a*gc_hit+b]=gc_T[b];
            }
         }
         ab_matrix = ab_hit*ab_hit;
         for(int a=0; a<ab_hit; a++){
            for(int b=0; b<ab_hit; b++){
               ab1_E[a*ab_hit+b]=ab_E[a];
               ab2_E[a*ab_hit+b]=ab_E[b];
               ab1_T[a*ab_hit+b]=ab_T[a];
               ab2_T[a*ab_hit+b]=ab_T[b];
            }
         }
         decay->Fill();
      }
   }
   rootfile->Write();
   rootfile->Close();
   cout<<"finished"<<endl;
}
