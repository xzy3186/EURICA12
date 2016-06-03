#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "TCutG.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "macro/Nucleus.cc"
#include "macro/ZedAoQGate.C"

const int nlist = 6; // array size of zlist & alist
void dEcalib(const char* filein, int runnumber) {
  //This file determines the fRawADCSqSum at Brho_center (F5-F7) and 
  // calculates the deltaE in IC @ F11. 
  // Zed parameters (two parameters) are calcluated from ATIMA. 
  //
  // zlist and alist can be selected from the nuclei in the PID spectrum:
  // tree->Draw("zet:aoq>>h(300,2.6,2.9,300,25,35)", "abs(X[6])<2&&abs(X[5])<10","colz")
  char* fileoutdECoef = "macroCu81/parameters/zedcalib/dECoef.txt";
  char* fileoutzedCoef = "macroCu81/parameters/zedcalib/zedcalibCalc.txt"; 

  int zlist[nlist] = {27,27,28,28,29,29};
  int alist[nlist] = {72,73,75,76,78,79};
  double zoffset=0.2, aoqoffset=0;
  double dzed = 0.4, daoq = 0.005;//width used in PID gate
  double Brho57 = 7.1545; // Brho value of central trajectory
  double minDeltaE = 6e3, maxDeltaE = 14e3; // used in histogram
  double dERaw[nlist];    // value at F5X=0
  double dERawErr[nlist];
  double dEcalc[nlist];
  double betacalc[nlist];
  double dEmod[nlist];
  double zmod[nlist];

  TFile *_file = TFile::Open(filein);
  TTree *tree = (TTree*)_file->Get("tree");

  Nucleus nucl;
  TString tstr("abs(X[6])<2&&runnumber==");
  tstr+=runnumber;
  tstr+="&&gNucl";

  TDirectory *tdir = gDirectory; // for tree->Project
  TH2D *h = new TH2D("h","DeltaE vs F5X",500,-120,120,500,minDeltaE,maxDeltaE);
  TProfile *profx = new TProfile("profx","profx",500,-120,120);

  for (int i = 0;i<nlist;i++) {
    //Determination of dEraw at Brho_center. 
    TCutG *gNucl = ZedAoQGate(zlist[i]+zoffset,dzed,1.0*alist[i]/zlist[i]+aoqoffset,daoq,"gNucl");
    tdir->cd();
    tree->Project("h","fRawADCSqSum[1]:X[5]",tstr);
    profx = h->ProfileX("");
    int xmin = profx->GetMean() - 2.* profx->GetRMS();
    int xmax = profx->GetMean() + 2.* profx->GetRMS();
    if (xmax < 0) {
      xmax = 1;
    } else if (xmin > 0) {
      xmin = -1;
    }
    TFitResultPtr fr = profx->Fit("pol1","S Q","",xmin,xmax);
    dERaw[i] = fr->Parameter(0); // value at F5X=0
    dERawErr[i]= fr->ParError(0);     

    //Calculation of dE MeV for Brho_center using Java ATIMA
    nucl.SetNucleus(zlist[i],alist[i]);
    nucl.SetBeamEnergy(Brho57,"Tm");
    dEcalc[i] = nucl.EnergyLoss("F7F11Simple",2);
    betacalc[i] = nucl.beta();
    //Calculation of zed calibration parameters 
    double ionpair=5911;
    double beta2 = betacalc[i]*betacalc[i];
    double de_v = log(ionpair*beta2) - log(1-beta2) - beta2;
    dEmod[i] = sqrt(dEcalc[i]/de_v)*betacalc[i];
    zmod[i] = zlist[i];
  }
  TGraph *gr1 = new TGraph(nlist,dERaw,dEcalc);
  TFitResultPtr  fr1 = gr1->Fit("pol1","QNS");
  ofstream fout(fileoutdECoef);
  fout <<fr1->Parameter(0) << "  " << fr1->Parameter(1) << endl;
  fout.close();

  TGraph *gr2 = new TGraph(nlist,dEmod,zmod);
  TFitResultPtr  fr2 = gr2->Fit("pol1","QNS");  
  fout.open(fileoutzedCoef);
  fout <<fr2->Parameter(0) << "  " << fr2->Parameter(1) << endl;
  fout.close();

}
