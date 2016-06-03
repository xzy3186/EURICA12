/****************************************
 build 2D histogram to find the energy
 correlation between DSSD and gamma
 ***************************************/

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
#include"TH1.h"
#include"TH2.h"
#include"TSystem.h"
#include"TTree.h"
#include"TROOT.h"
#include"TString.h"
#include"TRandom.h"

#include<signal.h>

//#include"TArtEventStore.h"
#include"eurica_wasabi.h"

using namespace std;

int main (int argc, char* argv []){

   if(argc<2){
      cout<<"USAGE: DSSDGeCorr #runNumber "<<endl;
      return 0;
   }

   int runN = atoi(argv[1]);
   char dssdfile[128];
   char rootfile[128];
   sprintf(dssdfile,"../root/sistopper/WASABI_EURICA%04d.root",runN);
   sprintf(rootfile,"../root/sistopper/WASABI_Calib%04d.root",runN);
   eurica_wasabi BG;
   BG.GetTree(dssdfile);

   TFile *RootFile = new TFile(rootfile,"recreate");
   TTree *tree[8][100];
   Int_t dssd_E, gc_E, dssd_T, gc_T, gc_hit, dssd_hit, dssd_hitx, dssd_hity;
   char hname[128];
   for(int i=0; i<8; i++){
      for(int j=0; j<100; j++){
         sprintf(hname,"DSSD%dCH%02d",i,j);
         tree[i][j]=new TTree(hname,hname);
         tree[i][j]->Branch("gc_E",&gc_E,"gc_E/I");
         tree[i][j]->Branch("dssd_E",&dssd_E,"dssd_E/I");
         tree[i][j]->Branch("gc_T",&gc_T,"gc_T/I");
         tree[i][j]->Branch("dssd_T",&dssd_T,"dssd_T/I");
         tree[i][j]->Branch("dssd_hit",&dssd_hit,"dssd_hit/I");
         tree[i][j]->Branch("gc_hit",&gc_hit,"gc_hit/I");
         //cout<<hname<<endl;
      }
   }
   Long64_t nMax = BG.fChain->GetEntriesFast();
   cout<<"Max events number = "<<nMax<<endl;
   for(Long64_t jentry=0; jentry<nMax; jentry++){
   //for(Long64_t jentry=0; jentry<1e4; jentry++){
      if(jentry%10000==0){
         cout<<jentry<<" lines finished"<<endl;
      }
      BG.GetEntry(jentry);
      dssd_hitx=0;
      dssd_hity=0;
      for(int i=0; i<NumDSSD; i++){
         for(int j=0; j<NumStrX; j++){
            if(BG.dssd_T_X[i][j][0]>-50000){
               dssd_hitx++;
            }
         }
         for(int j=0; j<NumStrY; j++){
            if(BG.dssd_T_Y[i][j][0]>-50000){
               dssd_hity++;
            }
         }
      }
      for(int i=0; i<NumDSSD; i++){
         for(int j=0; j<NumStrX; j++){
            if(BG.dssd_T_X[i][j][0]>-50000){
               for(int k=0; k<BG.gc_hit; k++){
                  if(BG.gc_T[k]>500&&BG.gc_T[k]<1500){
                     dssd_E=BG.dssd_E_X[i][j];
                     gc_E=BG.gc_E[k];
                     dssd_T=BG.dssd_T_X[i][j][0];
                     gc_T=BG.gc_T[k];
                     dssd_hit=dssd_hitx;
                     gc_hit=BG.gc_hit;
                     if(i>=4){
                        if(dssd_hit==2){
                           tree[i][j]->Fill();
                        }
                     }else{
                        if(dssd_hit==1){
                           tree[i][j]->Fill();
                        }
                     }
                  }
               }
            }
         }
         for(int j=0; j<NumStrY; j++){
            if(BG.dssd_T_Y[i][j][0]>-50000){
               for(int k=0; k<BG.gc_hit; k++){
                  if(BG.gc_T[k]>500&&BG.gc_T[k]<1500){
                     dssd_E=BG.dssd_E_Y[i][j];
                     gc_E=BG.gc_E[k];
                     dssd_T=BG.dssd_T_Y[i][j][0];
                     gc_T=BG.gc_T[k];
                     dssd_hit=dssd_hity;
                     gc_hit=BG.gc_hit;
                     if(dssd_hit==1){
                        tree[i][j+60]->Fill();
                     }
                  }
               }
            }
         }
      }
   }
   RootFile->Write();
   RootFile->Close();
   return 0;
}

