/************************************
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

#include"ion.h"

using namespace std;

int main(int argc, char* argv[]){

   if(argc<2){
      cout<<"USAGE: MakeGGMatrix #beta_ion_RUN"<<endl;
      return 0;
   }

   int runG = atoi(argv[1]);
   char gammafile[128];
   char outfile[128];

   Long64_t ts;

   Int_t z;
   Int_t Qbeta_E;
   Int_t Qbeta_T;

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

   sprintf(gammafile,"../root/sistopper/ni78test/beta_ion_%04d.root",runG);
   //sprintf(gammafile,"go4.root");
   sprintf(outfile,"../gamma_db/isomer_ni75_%04d.root",runG);

   ion gamma;
   gamma.GetTree(gammafile);

   Long64_t gEntry, gEntryMAX;  //entry for gamma
   TFile *rootfile = new TFile(outfile,"RECREATE");

   TTree *tree = new TTree("tree","tree");
   tree->Branch("ts",&ts,"ts/L");
   tree->Branch("run",&runG,"run/I");

   tree->Branch("z", &z,"z/I");
   tree->Branch("Qbeta_E", &Qbeta_E,"Qbeta_E/I");
   tree->Branch("Qbeta_T", &Qbeta_T,"Qbeta_T/I");

   tree->Branch("beta35", &beta35,"beta35/D");
   tree->Branch("beta57", &beta57,"beta57/D");
   tree->Branch("beta711", &beta711,"beta711/D");
   tree->Branch("aoq37", &aoq37,"aoq37/D");
   tree->Branch("zed", &zed,"zed/D");

   tree->Branch("Zed", &Zed,"Zed/I");
   tree->Branch("Mass", &Mass,"Mass/I");
   tree->Branch("flagall", &flagall,"flagall/I");
   tree->Branch("flagTSumX", &flagTSumX,"flagTSumX/I");
   tree->Branch("flagTOFt", &flagTOFt,"flagTOFt/I");
   tree->Branch("flagTOFq", &flagTOFq,"flagTOFq/I");
   tree->Branch("flagReaction", &flagReaction,"flagReaction/I");
   tree->Branch("flagdERelation", &flagdERelation,"flagdERelation/I");
   tree->Branch("flagAngle", &flagAngle,"flagAngle/I");

   tree->Branch("gc_matrix",&gc_matrix,"gc_matrix/I");
   tree->Branch("gc1_E",gc1_E,"gc1_E[gc_matrix]/D");
   tree->Branch("gc2_E",gc2_E,"gc2_E[gc_matrix]/D");
   tree->Branch("gc1_T",gc1_T,"gc1_T[gc_matrix]/D");
   tree->Branch("gc2_T",gc2_T,"gc2_T[gc_matrix]/D");
   tree->Branch("ab_matrix",&ab_matrix,"ab_matrix/I");
   tree->Branch("ab1_E",ab1_E,"ab1_E[ab_matrix]/D");
   tree->Branch("ab2_E",ab2_E,"ab2_E[ab_matrix]/D");
   tree->Branch("ab1_T",ab1_T,"ab1_T[ab_matrix]/D");
   tree->Branch("ab2_T",ab2_T,"ab2_T[ab_matrix]/D");

   tree->Branch("ab_hit",&ab_hit,"ab_hit/I");
   tree->Branch("ab_ch",ab_ch,"ab_ch[ab_hit]/I");
   tree->Branch("ab_DGFe",ab_DGFe,"ab_DGFe[ab_hit]/I");
   tree->Branch("ab_DGFt",ab_DGFt,"ab_DGFt[ab_hit]/I");
   tree->Branch("ab_TDCs",ab_TDCs,"ab_TDCs[ab_hit]/I");
   tree->Branch("ab_TDCl",ab_TDCl,"ab_TDCl[ab_hit]/I");
   tree->Branch("ab_E",ab_E,"ab_E[ab_hit]/D");
   tree->Branch("ab_T",ab_T,"ab_T[ab_hit]/D");

   tree->Branch("gc_hit",&gc_hit,"gc_hit/I");
   tree->Branch("gc_ch",gc_ch,"gc_ch[gc_hit]/I");
   tree->Branch("gc_DGFe",gc_DGFe,"gc_DGFe[gc_hit]/I");
   tree->Branch("gc_DGFt",gc_DGFt,"gc_DGFt[gc_hit]/I");
   tree->Branch("gc_TDCs",gc_TDCs,"gc_TDCs[gc_hit]/I");
   tree->Branch("gc_TDCl",gc_TDCl,"gc_TDCl[gc_hit]/I");
   tree->Branch("gc_E",gc_E,"gc_E[gc_hit]/D");
   tree->Branch("gc_T",gc_T,"gc_T[gc_hit]/D");

   gEntryMAX = gamma.fChain->GetEntriesFast();

   for(gEntry = 0; gEntry < gEntryMAX; gEntry++){
      if(gEntry%1000 == 0){
         cout<<gEntry<<" lines finished."<<endl;
      }
      gamma.GetEntry(gEntry);
      ts = gamma.ts;

      z = gamma.z;
      Qbeta_E = gamma.Qbeta_E;
      Qbeta_T = gamma.Qbeta_T;

      beta35 = gamma.RIBeam_beta35;
      beta57 = gamma.RIBeam_beta57;
      beta711 = gamma.RIBeam_beta711;
      aoq37 = gamma.RIBeam_aoq37;
      zed = gamma.RIBeam_zed;
      Zed = gamma.RIBeam_Zed;
      Mass = gamma.RIBeam_Mass;
      if(Zed != 28 || Mass != 75){
         continue;
      }
      flagall = gamma.RIBeam_flagall;
      flagTSumX = gamma.RIBeam_flagTSumX;
      flagTOFt = gamma.RIBeam_flagTOFt;
      flagTOFq = gamma.RIBeam_flagTOFq;
      flagReaction = gamma.RIBeam_flagReaction;
      flagdERelation = gamma.RIBeam_flagdERelation;
      flagAngle = gamma.RIBeam_flagAngle;

      gc_hit=gamma.gc_hit;
      for(int i=0; i<gamma.gc_hit; i++){
         gc_ch[i]=gamma.gc_ch[i];
         gc_DGFe[i]=gamma.gc_DGFe[i];
         gc_DGFt[i]=gamma.gc_DGFt[i];
         gc_TDCs[i]=gamma.gc_TDCs[i];
         gc_TDCl[i]=gamma.gc_TDCl[i];
         gc_E[i]=gamma.gc_E[i];
         gc_T[i]=gamma.gc_T[i];
      }
      gamma.GammaAddback();
      ab_hit=gamma.ab_hit;
      for(int i=0; i<gamma.ab_hit; i++){
         ab_ch[i]=gamma.ab_ch[i];
         ab_DGFe[i]=gamma.ab_DGFe[i];
         ab_DGFt[i]=gamma.ab_DGFt[i];
         ab_TDCs[i]=gamma.ab_TDCs[i];
         ab_TDCl[i]=gamma.ab_TDCl[i];
         ab_E[i]=gamma.ab_E[i];
         ab_T[i]=gamma.ab_T[i];
      }
      gc_matrix = gc_hit*gc_hit;
      for(int i=0; i<gc_hit; i++){
         for(int j=0; j<gc_hit; j++){
            gc1_E[i*gc_hit+j]=gamma.gc_E[i];
            gc2_E[i*gc_hit+j]=gamma.gc_E[j];
            gc1_T[i*gc_hit+j]=gamma.gc_T[i];
            gc2_T[i*gc_hit+j]=gamma.gc_T[j];
         }
      }
      ab_matrix = ab_hit*ab_hit;
      for(int i=0; i<ab_hit; i++){
         for(int j=0; j<ab_hit; j++){
            ab1_E[i*ab_hit+j]=gamma.ab_E[i];
            ab2_E[i*ab_hit+j]=gamma.ab_E[j];
            ab1_T[i*ab_hit+j]=gamma.ab_T[i];
            ab2_T[i*ab_hit+j]=gamma.ab_T[j];
         }
      }
      tree->Fill();
   }
   rootfile->Write();
   rootfile->Close();
   cout<<"finished"<<endl;
}
