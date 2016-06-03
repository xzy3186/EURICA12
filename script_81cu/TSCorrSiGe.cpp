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
#include"wasabi_treeinfo.h"
#include"eurica.h"

using namespace std;

int main(int argc, char* argv[]){

   if(argc<5){
      cout<<"USAGE: TSCorr_Si_Ge dssdRUN# gammaRUN# TS_offset TS_WindowWidth"<<endl;
      return 0;
   }
   TCanvas *c1 = new TCanvas("c1","c1",700,500);
   c1->Draw();
   c1->cd();

   int runD = atoi(argv[1]);
   int runG = atoi(argv[2]);
   Long64_t offs = atol(argv[3]);
   Long64_t widt = atol(argv[4]);
   char dssdfile[128];
   char gammafile[128];

   sprintf(gammafile,"../root/root_wasabi/test/go4_%d.root",runG);
   sprintf(dssdfile,"../root/root_wasabi/test/WASABI%04d.root",runD);

   TFile *rootfile = new TFile("../root/root_wasabi/TSCorr_Si_Ge.root","RECREATE");
   Long64_t width=0;
   if(widt<200){
      width=widt;
   }else if(widt>=200){
      width=200;
   }
   TH1F *TSCorr = new TH1F("TSCorr","Time Correlation",width,offs,offs+widt);

   wasabi DSSD;
   DSSD.GetTree(dssdfile);
   eurica GE(gammafile);
   map<Long64_t,Long64_t> mtsd, mtsg; //time stamp table for dssd and beam
   map<Long64_t,Long64_t>::iterator imtsd, imtsg;

   cout<<"start building time table for dssd and gamma"<<endl;
   DSSD.GetTsEntry(mtsd);
   cout<<"come here"<<endl;
   GE.GetTsEntry(mtsg);
   cout<<mtsd.size()<<" events for dssd"<<endl;
   cout<<mtsg.size()<<" events for gamma"<<endl;
   cout<<"offsite = "<<offs<<", width = "<<widt<<endl;

   cout<<"Scan coincidence time stamps"<<endl;
   for(imtsd=mtsd.begin();imtsd!=mtsd.end();imtsd++){
      Long64_t ts1 = imtsd->first + offs;
      Long64_t ts2 = ts1 + widt;
      imtsg = mtsg.lower_bound(ts1);
      while(imtsg!=mtsg.end() && imtsg->first < ts2){
         //cout<<"come here"<<endl;
         TSCorr->Fill(imtsg->first - imtsd->first);
         imtsg++;
      }
   }
   cout<<"finished filling"<<endl;
   TSCorr->Draw();
   c1->SaveAs("pics/TSCorr.jpg");
   rootfile->Write();
   rootfile->Close();
   cout<<"come here!!"<<endl;
   return 0;
}
