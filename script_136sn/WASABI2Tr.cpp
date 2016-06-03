/*
 * Offline decoder for DSSD DAQ
 */

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<TXMLNode.h>

#include"TSystem.h"
#include"TFile.h"
#include"TTree.h"
#include"TROOT.h"
#include"TString.h"
#include"TRandom.h"
#include"TMath.h"
#include"TClonesArray.h"

#include<signal.h>

#include"TArtEventStore.hh"
#include"segidlist.h"

#include "TArtRawDataObject.hh"
#include "TArtRawSegmentObject.hh"
#include "TArtRawScalerObject.hh"
#include "TArtRawEventObject.hh"

#include "wasabi_treeinfo.h"

using namespace std;

bool stoploop = false;
void stop_interrupt()
{
  printf("keyboard interrupt\n");
  stoploop = true;
}

int main(int argc,char* argv[]){
   if(argc<2){
      cout << "USAGE: ./WASABI2Tr #runnumber" << endl;
      return 1;
   }
   int runN = atoi(argv[1]);

   char filename[128];
   char rootname[128];

   sprintf(filename,"../rawdata/sistopper/uranium2012/exp/data%04d.ridf",runN);
   sprintf(rootname,"../root/sistopper/sn136test/WASABI%04d.root",runN);
   //sprintf(rootname,"../root/sistopper/WASABI_checkoffset81Cu.root");

   TArtStoreManager * sman = TArtStoreManager::Instance();
   TArtEventStore *estore = new TArtEventStore();
   estore->SetInterrupt(&stoploop);
   TArtRawEventObject *rawevent = estore->GetRawEventObject();
   //TArtRawEventObject *rawevent = new TArtRawEventObject();

   //estore->Initialize(rawevent);
   estore->Open(filename);
   //estore->Open(0);

   TFile *RootFile = new TFile(rootname,"RECREATE");
   TTree *tree = new TTree("WASABI","data");
   TClonesArray * info_array = (TClonesArray *)sman->FindDataContainer("EventInfo");
   tree->Branch(info_array->GetName(),&info_array);

   wasabi outtree;
   outtree.TreeBranch(tree);

   Long64_t event=0;

   //map <Int_t,vector<pair<Int_t,Int_t> > > map_beta;
   //map <Int_t,vector<pair<Int_t,Int_t> > >::iterator imap_beta;
   //Int_t beta_multi;

   outtree.read_mapping_table();
   outtree.read_bigrips_parameters();
   outtree.read_calib_table();
   outtree.read_threshold_table();
   outtree.TDC_getoff();

   while(estore->GetNextEvent()){
      event++;
      /******************************* initialize *************************************/
      outtree.ResetLeaf();
      int multi_hit[NumTDC][128];
      for(int k = 0; k<NumTDC;k++){
         for(int l=0;l<128;l++){
            multi_hit[k][l] =0;
         }
      }
      int multi_hitfast[128];
      for(int l=0;l<128;l++){
         multi_hitfast[l] =0;
      }

      /********************* filling data from raw data file *************************/
      for(int i=0;i<rawevent->GetNumSeg();i++){
         for(int ii=0;ii<rawevent->GetNumScaler();ii++){
            TArtRawScalerObject *seg = rawevent->GetScaler(ii);
            //cout << seg->GetNumChannel() << endl;
            for(int j=0;j<seg->GetNumChannel();j++){
               //cout << seg->GetScaler(j) << endl;
               outtree.scal[j] = seg->GetScaler(j);
            }
         }

         TArtRawSegmentObject *seg = rawevent->GetSegment(i);
         if(seg->GetDetector()==BETAA){
            for(int j=0;j<seg->GetNumData();j++){
               TArtRawDataObject *d = seg->GetData(j);
               int geo = d->GetGeo();
               int ch = d->GetCh();
               int val = d->GetVal();
               //if(geo==12 && val>3800){
               //   cout<<"geo="<<geo<<", ch="<<ch<<", val="<<val<<endl;
               //}
               if(geo >=3 && geo <26){
                  int adc_num = geo - 3;
                  //outtree.ADC[adc_num][ch] = val-outtree.ADC_thr[adc_num][ch];
                  outtree.ADC[adc_num][ch] = val;
               }
               if(geo==30){
                  outtree.ADC[23][ch]=val;
               }
            }
         }else if(seg->GetDetector() == BETAT){
            for(int j=0;j<seg->GetNumData();j++){
               TArtRawDataObject *d = seg->GetData(j);
               int geo = d->GetGeo();
               int ch = d->GetCh();
               int val = d->GetVal();
               if (geo > 25 && geo < 32){
                  int tdc_num = geo - 26;
                  if(multi_hit[tdc_num][ch] < NumTDCmulti){
                     int multi_temp = multi_hit[tdc_num][ch];
                     outtree.TDC[tdc_num][ch][multi_temp] = val;
                     multi_hit[tdc_num][ch]++;
                  }
               }
               if (geo == 0){
                  int tdc_num = 6;
                  if(multi_hit[tdc_num][ch] < NumTDCmulti){
                     int multi_temp = multi_hit[tdc_num][ch];
                     outtree.TDC[tdc_num][ch][multi_temp] = val;
                     multi_hit[tdc_num][ch]++;
                  }
               }
            }
         }
      }

      outtree.TDC_getref();
      outtree.dssd_E_mapping();
      outtree.dssd_T_mapping();
      outtree.bigrips_mapping();
      outtree.Qbeta_mapping();
      outtree.NaI_mapping();

      /**** simple analysis ****/
      outtree.IfBeta(outtree.IF_BETA, outtree.IF_ION);
      outtree.pid_reset();
      if(outtree.IF_ION==1){
         outtree.IonGetPos_TDC(outtree.dssd_Z,outtree.dssd_X,outtree.dssd_Y);
         outtree.Process_BigRips_Analysis();
      }

      rawevent->Clear();
      tree->Fill();
      if(event%1000==0){
         cout <<"RUN#"<<runN<<", number of event " << event << endl;
      }
         //cout<<outtree.fCh2nsPPAC[0][1]<<endl;

      //if(event==3000){
      //   break;
      //}
   }
   tree->Write();

   RootFile->Write();
   RootFile->Close();

   return 0;
}
