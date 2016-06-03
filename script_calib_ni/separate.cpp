/************************************
Separate beta and implantation events
into different trees.
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

#include"eurica_wasabi.h"
#include"BIGRIPS.h"
#include"beta.h"
#include"ion.h"

using namespace std;

int main(int argc, char* argv[]){

   if(argc<3){
      cout<<"USAGE: separate eurica_wasabi_file bigripsfile"<<endl;
      return 0;
   }

   int runN = atoi(argv[1]);
   int runB = atoi(argv[2]);
   char dssdfile[128];
   char bigripsfile[128];
   char outfile[128];
   int j;

   sprintf(dssdfile,"../root/sistopper/ni78test/WASABI_EURICA%04d.root",runN);
   //sprintf(dssdfile,"../root/sistopper/WASABI_EURICA%04d.root",runN);
   sprintf(bigripsfile,"../root/bigrips/v1/bigrips_run%04d.root",runB);
   //sprintf(outfile,"../root/sistopper/beta_ion_%04d.root",runN);
   sprintf(outfile,"../root/sistopper/ni78test/beta_ion_%04d.root",runN);

   /************** build TS table and match two root files **********/

   map<Long64_t,Long64_t> mtbrips,mteuro;
   map<Long64_t,Long64_t>::iterator imtbrips,imteuro;

   map<Long64_t,Long64_t>  mvbe;
   map<Long64_t,Long64_t>::iterator  imvbe;

   eurica_wasabi DSSD;
   DSSD.GetTree(dssdfile);
   BIGRIPS brips(bigripsfile);

   /*
    * Crate timestamp vs eventnumber map
    */

   brips.GetTsEntry(mtbrips);
   DSSD.GetTsEntry(mteuro);

   Long64_t tswindL = 100;
   Long64_t tswindU = 100;

   cout << " Check time stamp correlation " << endl;
   cout << mteuro.size() << " WASABI " << endl;
   cout << mtbrips.size() << " BIGRIPS " << endl;

   for(imteuro = mteuro.begin();imteuro != mteuro.end();imteuro++)
   {
      Long64_t ts1 = imteuro->first - tswindL;
      Long64_t ts2 = imteuro->first + tswindU;
      imtbrips = mtbrips.lower_bound(ts1);
      //cout<<imteuro->first<<" - "<<imtbrips->first<<" = "<<imteuro->first-imtbrips->first<<endl;
      if(imtbrips!=mtbrips.end() && imtbrips->first < ts2)
      {
         //cout<<"come here"<<endl;
         mvbe[imteuro->second]=imtbrips->second;
      }
   }
   cout << "Number of entry = " << mvbe.size() << " for BIGRIPS x WASABI" << endl;


   map <Int_t,vector<pair<pair<pair<Int_t,Int_t>,pair<Float_t,Int_t> >,pair<pair<Int_t,Int_t>,pair<Float_t,Int_t> > > > > map_beta;
   map <Int_t,vector<pair<pair<pair<Int_t,Int_t>,pair<Float_t,Int_t> >,pair<pair<Int_t,Int_t>,pair<Float_t,Int_t> > > > >::iterator imap_beta;
   Long64_t nEntry;

   TFile *rootfile = new TFile(outfile,"RECREATE");
   TTree *tbeta = new TTree("beta","beta");
   TTree *tion = new TTree("ion","ion");
   beta BETA;
   ion ION;
   BETA.TreeBranch(tbeta);
   ION.TreeBranch(tion);

   int beta_multi;

   int neve = 0;
   float pr;
   //for(nEntry=0; nEntry<nEntries; nEntry++){
   for(imteuro = mteuro.begin();imteuro!=mteuro.end();imteuro++){
      pr = float(neve)/mteuro.size() * 100;
      if(neve % 1000 == 0) cout <<"RUN#" <<runN<< ". Event " << neve << " Checked : " << pr << "% ..." << endl;
      neve++;

      nEntry = imteuro->second;
      DSSD.GetEntry(nEntry);
      imvbe = mvbe.find(nEntry);
      //cout<<"ion = "<<IF_ION<<", beta = "<<IF_BETA<<endl;
      //if(DSSD.IF_ION==1){
      if(imvbe != mvbe.end()){
         ION.SyncTS(DSSD);
         //ION.IonGetPos_TDC(ION.z,ION.x,ION.y);
         //ION.SyncBigRIPS(DSSD);
         ION.SyncQbeta(DSSD);
         ION.SyncPID(DSSD);
         ION.SyncNaI(DSSD);
         ION.SyncSi(DSSD);
         ION.ResetGe();
         ION.SyncGamma(DSSD);

         brips.GetEntry(imvbe->second);
         ION.RIBeam_beta35 = brips.RIBeam_beta35[0];
         ION.RIBeam_beta57 = brips.RIBeam_beta57[0];
         ION.RIBeam_beta711 = brips.RIBeam_beta711[0];
         ION.RIBeam_aoq37 = brips.RIBeam_aoq37[0];
         ION.RIBeam_zed = brips.RIBeam_zed[0];
         ION.RIBeam_Zed = brips.RIBeam_Zed[0];
         ION.RIBeam_Mass = brips.RIBeam_Mass[0];
         ION.RIBeam_flagall = brips.RIBeam_flagall[0];
         ION.RIBeam_flagTSumX = brips.RIBeam_flagTSumX[0];
         ION.RIBeam_flagTOFt = brips.RIBeam_flagTOFt[0];
         ION.RIBeam_flagTOFq = brips.RIBeam_flagTOFq[0];
         ION.RIBeam_flagReaction = brips.RIBeam_flagReaction[0];
         ION.RIBeam_flagdERelation = brips.RIBeam_flagdERelation[0];
         ION.RIBeam_flagAngle = brips.RIBeam_flagAngle[0];

         tion->Fill();
      }else if(DSSD.IF_BETA==1&&imvbe == mvbe.end()){
         BETA.SyncTS(DSSD);
         map_beta.clear();

         DSSD.BetaGetPos(beta_multi,map_beta);

         BETA.dssd_mulhit=0;
         BETA.dssd_E=0;
         for(int z=0; z<NumDSSD; z++){
            BETA.dssd_fire[z]=0;
            BETA.dssd_ex[z]=-1;
            BETA.dssd_ey[z]=-1;
            BETA.dssd_zmult[z]=0;
            for(int i=0; i<5; i++){
               BETA.dssd_x[z][i]=-1;
               BETA.dssd_y[z][i]=-1;
            }
            imap_beta = map_beta.find(z);
            if(imap_beta != map_beta.end()){
               BETA.dssd_fire[z]=1;
               BETA.dssd_ex[z]=0;
               BETA.dssd_ey[z]=0;
               BETA.dssd_mulhit++;
               for(int x=1; x<NumStrX-1; x++){
                  if(DSSD.dssd_T_X[z][x][0]<3000 && DSSD.dssd_T_X[z][x][0]>-4000 && DSSD.dssd_E_X[z][x]>50){
                        BETA.dssd_ex[z] = BETA.dssd_ex[z]+DSSD.dssd_E_X[z][x];
                  }
               }
               for(int y=1; y<NumStrY-1; y++){
                  if(DSSD.dssd_T_Y[z][y][0]<3000 && DSSD.dssd_T_Y[z][y][0]>-4000 && DSSD.dssd_E_Y[z][y]>50){
                        BETA.dssd_ey[z] = BETA.dssd_ey[z]+DSSD.dssd_E_Y[z][y];
                  }
               }
               for(j=0; j<imap_beta->second.size(); j++){
                  if(BETA.dssd_zmult[z]<5){
                     BETA.dssd_x[z][BETA.dssd_zmult[z]]=imap_beta->second[j].first.second.first;
                     BETA.dssd_y[z][BETA.dssd_zmult[z]]=imap_beta->second[j].second.second.first;
                     //cout<<BETA.dssd_x[z][BETA.dssd_zmult[z]]<<endl;
                     //cout<<BETA.dssd_y[z][BETA.dssd_zmult[z]]<<endl;
                     BETA.dssd_zmult[z]++;
                  }
               }
            }
            if(z>=4 && BETA.dssd_fire[z]==1){
               BETA.dssd_ex[z]=BETA.dssd_ex[z]/2;
            }
            if(BETA.dssd_fire[z]==1){
               BETA.dssd_E=BETA.dssd_E+BETA.dssd_ex[z];
            }
         }
         if(BETA.dssd_fire[0]==1&&BETA.dssd_fire[7]==1){
            continue;
         }
         for(int z=0; z<NumDSSD; z++){
            imap_beta = map_beta.find(z);
            if(imap_beta != map_beta.end()){
               BETA.z=z;
               for(j=0; j<imap_beta->second.size(); j++){
                  BETA.x1=imap_beta->second[j].first.first.first;
                  BETA.x2=imap_beta->second[j].first.first.second;
                  BETA.x=imap_beta->second[j].first.second.first;
                  BETA.ex=imap_beta->second[j].first.second.second;
                  BETA.y1=imap_beta->second[j].second.first.first;
                  BETA.y2=imap_beta->second[j].second.first.second;
                  BETA.y=imap_beta->second[j].second.second.first;
                  BETA.ey=imap_beta->second[j].second.second.second;
                  BETA.tx=(DSSD.dssd_T_X[BETA.z][BETA.x1][0]+DSSD.dssd_T_X[BETA.z][BETA.x2][0])/2;
                  BETA.ty=(DSSD.dssd_T_Y[BETA.z][BETA.y1][0]+DSSD.dssd_T_Y[BETA.z][BETA.y2][0])/2;
                  BETA.SyncSi(DSSD);
                  BETA.SyncQbeta(DSSD);
                  BETA.ResetGe();
                  BETA.SyncGamma(DSSD);
                  BETA.SyncNaI(DSSD);
                  tbeta->Fill();
               }
            }
         }
      }
   }
   rootfile->Write();
   rootfile->Close();
}
