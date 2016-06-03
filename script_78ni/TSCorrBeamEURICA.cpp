/************************************
Find the time stamp correlation
between DSSD events and gamma events
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
#include"TH1.h"
#include"TCanvas.h"
#include"TSystem.h"
#include"TTree.h"
#include"TROOT.h"
#include"TString.h"
#include"TRandom.h"

#include<signal.h>

#include"TArtEventStore.hh"
#include"eurica_wasabi.h"
#include"BIGRIPS.h"

using namespace std;

int main(int argc, char* argv[]){

   if(argc<5){
      cout<<"USAGE: TSCorrBeamEURICA euricaRUN# beamRUN# TS_offset TS_WindowWidth"<<endl;
      return 0;
   }
   TCanvas *c1 = new TCanvas("c1","c1",700,500);
   c1->Draw();
   c1->cd();

   int runE = atoi(argv[1]);
   int runB = atoi(argv[2]);
   Long64_t offs = atol(argv[3]);
   Long64_t widt = atol(argv[4]);
   char euricafile[128];
   char beamfile[128];

   sprintf(euricafile,"../root/sistopper/ni78test/WASABI_EURICA%d.root",runE);
   sprintf(beamfile,"../root/bigrips/v0/bigrips_run%04d.root",runB);

   TFile *rootfile = new TFile("root_dir/TSCorrBeamEURICA.root","RECREATE");
   Long64_t width=0;
   if(widt<200){
      width=widt;
   }else if(widt>=200){
      width=200;
   }
   TH1F *TSCorr = new TH1F("TSCorr","Time Correlation",width,offs,offs+widt);

   eurica_wasabi DSSD;
   DSSD.GetTree(euricafile);
   BIGRIPS beam(beamfile);
   map<Long64_t,Long64_t> mtse, mtsb; //time stamp table for dssd and beam
   map<Long64_t,Long64_t>::iterator imtse, imtsb;

   cout<<"start building time table for eurica and beam"<<endl;
   DSSD.GetTsEntry(mtse);
   cout<<"come here"<<endl;
   beam.GetTsEntry(mtsb);
   cout<<mtse.size()<<" events for eurica"<<endl;
   cout<<mtsb.size()<<" events for beam"<<endl;
   cout<<"offsite = "<<offs<<", width = "<<widt<<endl;

   cout<<"Scan coincidence time stamps"<<endl;
   for(imtse=mtse.begin();imtse!=mtse.end();imtse++){
      Long64_t ts1 = imtse->first + offs;
      Long64_t ts2 = ts1 + widt;
      imtsb = mtsb.lower_bound(ts1);
      while(imtsb!=mtsb.end() && imtsb->first < ts2){
         //cout<<"come here"<<endl;
         TSCorr->Fill(imtsb->first - imtse->first);
         imtsb++;
      }
   }
   cout<<"finished filling"<<endl;
   TSCorr->Draw();
   c1->SaveAs("pics/TSCorrBeamEURICA.eps");
   c1->SaveAs("pics/TSCorrBeamEURICA.root");
   rootfile->Write();
   rootfile->Close();
   cout<<"come here!!"<<endl;
   return 0;
}
