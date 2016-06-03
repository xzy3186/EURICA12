/*
 * Conver ridf data to ROOT file
 */

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<TXMLNode.h>

#include <TApplication.h>
#include"TFile.h"
#include"TTree.h"
#include"TROOT.h"
#include"TString.h"
#include"TRandom.h"
#include"TH1.h"
#include"TH2.h"
#include"TCanvas.h"
#include<TSystem.h>
#include<TStyle.h>

#include<signal.h>
#include"TArtEventStore.hh"
#include"segidlist.h"

#include "TArtRawDataObject.hh"
#include "TArtRawSegmentObject.hh"
#include "TArtRawScalerObject.hh"
#include "TArtRawEventObject.hh"

#include "kbhit.h"
#include "MySignalHandler.cc"
#include "rootlogon.C"

using namespace std;

//void stop_interrupt(int signum){
//   cout << "interrupt" << endl;
//   keeploop = false;
//}

/*
 * Program start here
 */
int main(int argn,char* argv[]){
   TApplication theApp("app",&argn,argv);
   gSystem->AddSignalHandler( new MySignalHandler( kSigInterrupt ) );
   gSystem->AddSignalHandler( new MySignalHandler( kSigTermination ) );
   bool keeploop = true;
   int if_stop = 0;
   rootlogon();

   //   signal(SIGINT,stop_interrupt);

   //gStyle->SetOptStat(111111);
   //gSystem->Load("libXMLParser.so");
   //gSystem->Load("libanacore.so");
   //gSystem->Load("libanabrips.so");

   TArtEventStore *estore = new TArtEventStore();
   TArtRawEventObject *rawevent = estore->GetRawEventObject();
   //TArtRawEventObject *rawevent = new TArtRawEventObject();
   //estore->Initialize(rawevent);
   estore->Open(0);

   TCanvas *c1 = new TCanvas("c1","PLS_E",0,10,900,500);
   //TCanvas *c2 = new TCanvas("c2","PLS_T",500,10,500,1000);
   TH2F *h1 = new TH2F("h1","h1",32,0,32,410,0,4100);
   TH1F *h5 = new TH1F("h5","h5",410,0,4100);
   //TH2F *h2 = new TH2F("h2","h2",1300,200,1500,200,200,400);
   TH2F *h2 = new TH2F("h2","h2",32,0,32,410,0,4100);
   TH2F *h3 = new TH2F("h3","h3",32,0,32,410,0,4100);
   TH2F *h4 = new TH2F("h4","h4",32,0,32,410,0,4100);
   //TH2F *h3 = new TH2F("h3","h3",200,0,4000,100,0,2000);
   //TH2F *h4 = new TH2F("h4","h4",100,150,250,200,150,300);
   //TH1F *h5 = new TH1F("h5","h5",410,0,4100);
   //TH1F *h6 = new TH1F("h6","h6",2500,0,25000);

   c1->Divide(2,2);
   c1->Draw();
   c1->cd(1);
   h1->Draw();
   c1->cd(2);
   h2->Draw();
   c1->cd(3);
   h3->Draw();
   c1->cd(4);
   h4->Draw();
   c1->Update();

   //c2->Divide(1,2);
   //c2->Draw();
   //c2->cd(1);
   //h5->Draw();
   //c2->cd(2);
   //h6->Draw();

   TTree *tree = new TTree("plastic","data");

   char rootname[128];
   int runN = atoi(argv[1]);
   sprintf(rootname,"run%03d.root",runN);

   TFile *RootFile = new TFile(rootname,"recreate");

   /* QDC readout for plastic scintillator */
   Int_t ADC[4][32];
   Int_t ADC_VAL[128];
   Int_t ADC_CH[128];
   Int_t ADC_GEO[128];
   Int_t NHITS;
   Int_t plsE[32];
   Int_t plsV[32];
   /* TDC readout for DSSDs */
   Int_t plsT[32][5];
   Int_t plsTi[32];
   Long64_t event=0;

   tree->Branch("NHITS",&NHITS,"NHITS/I");
   tree->Branch("ADC_VAL",ADC_VAL,"ADC_VAL[NHITS]/I");
   tree->Branch("ADC_GEO",ADC_GEO,"ADC_GEO[NHITS]/I");
   tree->Branch("ADC_CH",ADC_CH,"ADC_CH[NHITS]/I");
   tree->Branch("ADC",ADC,"ADC[4][32]/I");
   tree->Branch("plsE",plsE,"plsE[32]/I");
   tree->Branch("plsV",plsV,"plsV[32]/I");
   tree->Branch("plsT",plsT,"plsT[32][5]/I");

   tree->Branch("event",&event,"event/L");

   cout<<"Online monitor started, press <Space> to pause."<<endl;

   while(keeploop){
      if(kbhit()==1){
         int if_continue;
         cout<<"online monitor is paused"<<endl;
         cout<<"Press 0 <Enter> to stop, 1 <Enter> to restart"<<endl;
         cout<<"Press 2 <Enter> to restart after clear"<<endl;
         cin >> if_continue;
         string choose;
         if(if_continue==0){
            choose="stop";
         }else if(if_continue==1){
            choose="restart";
         }else if(if_continue==2){
            choose="restart after reset";
         }
         cout<<"You choose "<<choose<<", please press ctrl+c to continue;"<<endl;
         theApp.Run();
         if(if_continue == 0){
            //keeploop = false;
            break;
         }else if(if_continue==1){
            cout<<"monitor restarted, press <Space> to pause;"<<endl;
         }else if(if_continue==2){
            cout<<"monitor restarted, press <Space> to pause;"<<endl;
            tree->Reset();
            h1->Reset();
            h2->Reset();
            h3->Reset();
            h4->Reset();
            //h5->Reset();
            //h6->Reset();
            event=0;
         }
      }
      int temp = estore->GetNextEvent();
      //cout<<"Is data = "<<temp<<endl;
      if(temp == 0){
         if_stop ++;
         if(if_stop>1000){
            break;
         }
         gSystem->Sleep(1000);
         //cout<<"come here"<<endl;
         continue;
      }

      //while(estore->GetNextEvent() && keeploop && event < 1000000){
      event++;
      //cout<<event<<endl;
      /* initialize */
      for(int i=0; i<32; i++){
      //   plsE[i]=-1;
      //   plsV[i]=-1;
      //   plsTi[i]=0;
         for(int j=0; j<4; j++){
            //plsT[i][j]=-1;
            ADC[j][i]=-1;
         }
      }
      for(int i=0; i<128; i++){
         ADC_VAL[i]=-1;
         ADC_CH[i]=-1;
         ADC_GEO[i]=-1;
      }

      NHITS=0;
      for(int i=0;i<rawevent->GetNumSeg();i++){
         TArtRawSegmentObject *seg = rawevent->GetSegment(i);
         if(seg->GetDetector()==BETAA){
            for(int j=0;j<seg->GetNumData();j++){
               TArtRawDataObject *d = seg->GetData(j);
               int geo = d->GetGeo();
               int ch = d->GetCh();
               int val = d->GetVal();
               if(geo>=3 && geo<7){
                  ADC_VAL[NHITS]=val;
                  ADC_CH[NHITS]=ch;
                  ADC_GEO[NHITS]=geo;
                  NHITS++;
                  ADC[geo-3][ch]=val;
               }
               //switch(geo){
               //   case 25:
               //      plsV[ch]=val;
               //      break;
               //   case 30:
               //      plsE[ch]=val;
               //      break;
               //}
            }
         }else if(seg->GetDetector() == BETAT){
            for(int j=0;j<seg->GetNumData();j++){
               TArtRawDataObject *d = seg->GetData(j);
               int geo = d->GetGeo(); 
               int ch = d->GetCh();
               int val = d->GetVal(); 
               switch(geo){
                  case 10:
                     if(plsTi[ch]<5){
                        plsT[ch][plsTi[ch]]=val;
                        plsTi[ch]++;
                     }
                     //if(ch==0){
                     //   if(pls_t<0){
                     //      pls_t=val;
                     //   }else{
                     //      pls_t=(val<pls_t)?val:pls_t;
                     //   }
                     //}else if(ch==1){
                     //   if(pls_subt<0){
                     //      pls_subt=val;
                     //   }else{
                     //      pls_subt=(val<pls_subt)?val:pls_subt;
                     //   }
                     //}
                     break;
               }
            }
         }
      }

      tree->Fill();
      if_stop=0;
      rawevent->Clear();

      //if(ADC[0][0]>100){
      //   h5->Fill(ADC[0][0]);
      //}
      //if(plsV[0]>100){
      //   //h2->Fill(plsE[16],plsE[17]);
      //   h2->Fill(plsV[0]);
      //}

      //if(plsE[16]>100 && plsV[17]>100){
      //   //h2->Fill(plsE[16],plsE[17]);
      //   h3->Fill(plsE[16],plsV[17]);
      //}
      //}
      //      if(plsE[16]>100 && plsT[0][0]>0 && plsT[1][0]>0 &&((plsT[0][0]-plsT[1][0])>600)){
      // h4->Fill(plsE[16],plsE[17]);
      // }

      //if(pls_t>0){
      //   h5->Fill(pls_t);
      //   h6->Fill(pls_t-pls_subt);
      //}
      //if(plsV[17]>0){
      //   h5->Fill(plsV[17]);
      //}
      //if(plsT[17][0]>0){
      //   h6->Fill(plsT[17][0]);
      //}

      if(event%100==0){
         cout << "number of event " << event << ", press <Space> to pause;" << endl;
         c1->cd(1);
         //	 tree->Draw("plsE[17]>>h1(200,0,10000)");
         tree->Draw("ADC_VAL:ADC_CH>>h1","ADC_GEO==3","col");
         //h5->Draw();

         // h1->Draw();
         //tree->Draw("plsT[0][0]-plsT[1][0]","plsT[1][0]>0");
         c1->cd(2);
         //tree->Draw("plsT[0][0]>>h5","plsT[0][0]>0");
         //tree->Draw("-plsT[1][0]+plsT[1][1]>>h5","plsT[1][1]>0");
         //tree->Draw("plsE[17]>>h2(200,500,4000)");
         //tree->Draw("plsE[1]>>h2+");
         tree->Draw("ADC_VAL:ADC_CH>>h2","ADC_GEO==4","col");
         //h2->Draw();

         //h3->Draw();
         c1->cd(3);
         //h6->Draw();
         //tree->Draw("plsT[1]>>h6","plsT[1]>0");
         //tree->Draw("plsE[16]>>h3(200,500,10000)","plsE[17]>500");
         //tree->Draw("plsE[2]>>h3+");
         //h3->Draw("col");
         tree->Draw("ADC_VAL:ADC_CH>>h3","ADC_GEO==5","col");
         c1->cd(4);
         tree->Draw("ADC_VAL:ADC_CH>>h4","ADC_GEO==6","col");
         c1->cd();
         c1->Update();
         //c2->cd(1);
         //h5->Draw();
         ////tree->Draw("plsT[16][0]");
         //c2->cd(2);
         ////tree->Draw("plsT[17][0]");
         //h6->Draw();
         //c2->cd();
         //c2->Update();
      }
   }
   cout<<"online monitor stopped, press ctrl+c to save file and quit;"<<endl;
   theApp.Run();
   tree->Write();
   RootFile->Write();
   RootFile->Close();
   cout<<"file saved, quit!"<<endl;
   return 0;
   }
