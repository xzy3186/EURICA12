
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TH1.h"
#include "TF1.h"
#include "TVirtualFitter.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TGraphErrors.h"
#include <fstream>
#include <sstream>
#include <algorithm>
   
void dEShift(const char* filein, const char* fileout, Int_t runnumber) {
  // This is the first step to obtain the gain shift parameter
  // for fRawADCSqSum at ionization chamber. 
  // fRawADCSqSum[0] is the F7. 
  // fRawADCSqSum[1] is the F11. 
  // This file is for F11.
  // This function obtain deltaE in ch for typical conditions 
  // given by beta(=v/c).  
  // Here the beta windows, expected central values and its width 
  // are necessary. These values can be obtained by
  // tree->Draw("fRawADCSqSum[1]:beta[0]>>h(300,0.63,0.66,300,6e3,15e3)","","colz")" on the root prompt. 
  // For all runs, this file is expected to be used by "dEShiftParallel.sh".

   int imax = 4;
   TString betastr[50]; 
   //based on run 1050
   betastr[0]=TString("beta[0]>0.645&&beta[0]<0.646"); // for zed = 30
   betastr[1]=TString("beta[0]>0.641&&beta[0]<0.642"); // for zed = 31
   betastr[2]=TString("beta[0]>0.638&&beta[0]<0.639"); // for zed = 31
   betastr[3]=TString("beta[0]>0.649&&beta[0]<0.650"); // for zed = 31
   ////based on run 5102
   //betastr[0]=TString("beta[0]>0.650&&beta[0]<0.652"); // for zed = 27
   //betastr[1]=TString("beta[0]>0.647&&beta[0]<0.648"); // for zed = 28
   //betastr[2]=TString("beta[0]>0.645&&beta[0]<0.646"); // for zed = 29
   //betastr[3]=TString("beta[0]>0.645&&beta[0]<0.646"); // for zed = 30
   //betastr[4]=TString("beta[0]>0.642&&beta[0]<0.643"); // for zed = 31
   //betastr[5]=TString("beta[0]>0.639&&beta[0]<0.640"); // for zed = 32

   double dErawcenter[50];
   dErawcenter[0] =  9932;
   dErawcenter[1] =  10770;
   dErawcenter[2] =  11620;
   dErawcenter[3] =  9144;

   //dErawcenter[0] =  7799;
   //dErawcenter[1] =  8513;
   //dErawcenter[2] =  9231;
   //dErawcenter[3] =  9916;
   //dErawcenter[4] = 10720;
   //dErawcenter[5] = 11570;
   double width = 300.; //Width of dE spectrum in channel to make 1D-spectrum

   TDirectory *tdir = gDirectory; // for tree->Project
   TH1F *h = new TH1F("h", "h", 700,6e3, 15e3);
   // The min and max values of histgram should be adjusted.

   //   char* fileout = "/home/sumikama/Analysis/Cu81/macroCu81/parameters/zedcalib/dERaw.txt";


   TFile *_file = TFile::Open(filein);
   TTree *tree = (TTree*)_file->Get("tree");
   TString runnumberstr("EventInfo.runnumber[0]==");
   int runnumber_temp = runnumber;
   string str;
   stringstream ss;
   ss.str("");ss.clear(stringstream::goodbit); str.clear(); 
   ss << runnumber_temp;  ss >> str;
   runnumberstr+=str;runnumberstr += "&&";
   double dErawresult[50];
   for(int j=0;j<imax;j++) {
     tdir->cd(); // in order to work Project well 
     tree->Project("h","fRawADCSqSum[1]",runnumberstr+betastr[j]);
     TFitResultPtr fitptr = h->Fit("gaus","QNS","",dErawcenter[j]-width,dErawcenter[j]+width);
     dErawresult[j] = fitptr->Value(1);
   }
   
   ofstream fout(fileout,ios::out|ios::app);
   fout << runnumber;
   for (int j=0;j<imax;j++) {
     fout <<"  "<< dErawresult[j];
   }
   fout << endl;
   fout.close();

   return;
}
