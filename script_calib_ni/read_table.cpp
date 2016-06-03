/*
 * Online monitor for DSSD DAQ
 */

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<TXMLNode.h>

#include"TApplication.h"
#include"TStyle.h"
#include"TSystem.h"
#include"TFile.h"
#include"TTree.h"
#include"TROOT.h"
#include"TString.h"
#include"TRandom.h"
#include"TH1.h"
#include"TH2.h"
#include"TCanvas.h"
#include"TMath.h"

#include<signal.h>

#include"TArtEventStore.hh"
#include"segidlist.h"

#include "TArtRawDataObject.hh"
#include "TArtRawSegmentObject.hh"
#include "TArtRawScalerObject.hh"
#include "TArtRawEventObject.hh"

#include "dssd_future.h"
#include "dssd_online.h"

#include "kbhit.h"
#include "MySignalHandler.cc"
#include "rootlogon.C"

using namespace std;

int main(int argc,char* argv[]){
   dssd outtree;
   outtree.read_mapping_table();
   for(int i=0; i<NumADC*32; i++){
      cout<<i<<", "<<outtree.ADCtoDSSD[i]<<", "<<outtree.ADCtoSTRIP[i]<<endl;
   }
   return 0;
}
