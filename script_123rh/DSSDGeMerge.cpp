/************************************
combine root files for DSSD and Go4,
for the calibration, beta delayed
gamma, and isomeric gamma.
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

using namespace std;

int main(int argc, char* argv[]){

   if(argc<3){
      cout<<"USAGE: DSSDGeMerge #DSSDRUN #GAMMARUN"<<endl;
      return 0;
   }

   int runD = atoi(argv[1]);
   int runG = atoi(argv[2]);
   char dssdfile[128];
   char gammafile[128];
   char outfile[128];

   sprintf(dssdfile,"../root/sistopper/rh123test/WASABI%04d.root",runD);
   sprintf(gammafile,"../root/euroball/go4_%04d.root",runG);
   //sprintf(gammafile,"go4.root");
   sprintf(outfile,"../root/sistopper/rh123test/WASABI_EURICA%04d.root",runD);

   wasabi DSSD;
   DSSD.GetTree(dssdfile);
   eurica gamma(gammafile);
   map<Long64_t,Long64_t> mtsd, mtsg; //time stamp table for dssd and gamma
   map<Long64_t,Long64_t>::iterator imtsd, imtsg;

   map<Long64_t,Long64_t> mvdg; //time stamp correlation between dssd and gamma
   map<Long64_t,Long64_t>::iterator imvdg;


   Long64_t dEntry, gEntry;  //entry for dssd and gamma
   TFile *rootfile = new TFile(outfile,"RECREATE");

   TTree *tree = new TTree("tree","tree");

   map <Int_t,vector<pair<Int_t,Int_t> > > map_beta;
   map <Int_t,vector<pair<Int_t,Int_t> > >::iterator imap_beta;

   eurica_wasabi outtree;
   outtree.TreeBranch(tree);

   cout<<"start building time table for dssd and gamma"<<endl;
   DSSD.GetTsEntry(mtsd);
   //cout<<"come here"<<endl;
   gamma.GetTsEntry(mtsg);
   cout<<mtsd.size()<<" events for dssd"<<endl;
   cout<<mtsg.size()<<" events for gamma"<<endl;

   Long64_t tswindL = -50;
   //Long64_t tswindL = 3950;
   Long64_t tswindU = 100;
   cout<<"Scan coincidence time stamps"<<endl;
   for(imtsd=mtsd.begin();imtsd!=mtsd.end();imtsd++){
      Long64_t ts1 = imtsd->first + tswindL;
      Long64_t ts2 = ts1 + tswindU;
      imtsg = mtsg.lower_bound(ts1);
      if(imtsg!=mtsg.end() && imtsg->first < ts2){
         mvdg[imtsd->second]=imtsg->second;
      }
   }
   cout<<"nentries = "<<mvdg.size()<<" for dssd x gamma"<<endl;

   for(imtsd=mtsd.begin();imtsd!=mtsd.end();imtsd++){
      dEntry=imtsd->second;
      if(dEntry%1000==0){
         cout<<"RUN #"<<runD<<", "<<dEntry<<" lines finished"<<endl;
      }
      Long64_t temp = DSSD.LoadTree(dEntry);
      if(temp < 0){
         break;
      }
      DSSD.GetEntry(dEntry);
      outtree.SyncTS(DSSD);
      outtree.SyncSi(DSSD);
      outtree.SyncQbeta(DSSD);
      outtree.SyncBigRIPS(DSSD);
      outtree.SyncPID(DSSD);
      outtree.SyncNaI(DSSD);

      outtree.ResetGe();
      imvdg=mvdg.find(imtsd->second);
      if(imvdg !=mvdg.end()){
         gEntry=imvdg->second;
         gamma.GetEntry(gEntry);
         outtree.SyncGamma(gamma);
      }
      tree->Fill();
   }
   rootfile->Write();
   rootfile->Close();
}
