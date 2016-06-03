// This file is used to determine the parameters in the Bethe-Bloch function.
// Data set is deltaE vs beta57 of several zed. 
// Fitting is done for data set fo all zed using Minuit2
#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TString.h"
#include "Minuit2/FCNBase.h"
#include "TFitterMinuit.h"
#include "TStopwatch.h"
#include "macroCu81/AoQAnalysis.C"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
class AoQAnalysisFCN : public ROOT::Minuit2::FCNBase, public AoQAnalysis {
  mutable int icall;
public: 
  AoQAnalysisFCN() {icall =0;}
  //SetTree(tree) is necessary after constructor. 
  //  double operator() (const vector<double> & par) const {
  double operator() (const vector<double> & par) const {
    //number of parameter is 15.
    // FCN is not chi^2;
    icall++;
    double fcn = Loop(par);
    if(icall%10==0||icall==1) cout << icall << "  " << fcn<<endl;
    return fcn;
    //    return 1;
  }

  double Up() const {return 1.;}

};


void AoQFit(char* filename) {
  string filenameout = "macroCu81/parameters/aoqcalib.txt";

  TFile *_File = TFile::Open(filename);
  TTree *tree = (TTree*)_File->Get("tree");

  TFitterMinuit * minuit = new TFitterMinuit();
  AoQAnalysisFCN fcn;
  fcn.SetTree(tree);
  minuit->SetMinuitFCN(&fcn);
  //starting values
  double startTOFOffset = 244.952;
  double startslew[4] = {21.3088,18.4476,20.0625,12.8254};

  double startxx[2],startxa[2],startxd[2];
  double startxxx[2],startxxa[2],startxxd[2],startxaa[2],startxad[2],startxdd[2];
  double startxxxx[2],startxxxa[2],startxxaa[2],startxaaa[2];
  double startxaaaa[2];

  int flag;
  flag = 1; 
  if (flag == 0) { // default values
    startxx[0]    = 0.926591;
    startxa[0]    = -0.00471245;
    startxd[0]    = 31.6690;
    startxxx[0]   = 0.0;
    startxxa[0]   = 0.0;
    startxxd[0]   = 0.0;
    startxaa[0]   = 0.0;
    startxad[0]   = 0.0;
    startxdd[0]   = 0.0;
    startxxxx[0]  = 0.0;
    startxxxa[0]  = 0.0;
    startxxaa[0]  = 0.0;
    startxaaa[0]  = 0.0;
    startxaaaa[0] = 0.0;
    startxx[1]    = 1.08043;
    startxa[1]    = 0.0226346;
    startxd[1]    = -34.4174; 
    startxxx[1]   = 0.0;
    startxxa[1]   = 0.0;
    startxxd[1]   = 0.0;
    startxaa[1]   = 0.0;
    startxad[1]   = 0.0;
    startxdd[1]   = 0.0;
    startxxxx[1]  = 0.0;
    startxxxa[1]  = 0.0;
    startxxaa[1]  = 0.0;
    startxaaa[1]  = 0.0;
    startxaaaa[1] = 0.0;
  } else { // for user's parameters
    startxx[0]    = 1.00365;
    startxa[0]    = -0.143 ;
    startxd[0]    = 29.751 ;
    startxxx[0]   = 0.0;
    startxxa[0]   = 0.0;
    startxxd[0]   = 0.0;
    startxaa[0]   = 0.0;
    startxad[0]   = -0.020;
    startxdd[0]   = -0.125;
    startxxxx[0]  = -2.3e-4;
    startxxxa[0]  = 0.0;
    startxxaa[0]  = 3.2e-4;
    startxaaa[0]  = 1.6e-4;
    startxaaaa[0] = 0.0;
    startxx[1]    =0.7565  ;
    startxa[1]    =0.02	   ;
    startxd[1]    =-24.;
    startxxx[1]   = 0;
    startxxa[1]   = 0.0;
    startxxd[1]   = -0.098;
    startxaa[1]   = 0.00176;
    startxad[1]   = 0.00;
    startxdd[1]   = 3.1;
    startxxxx[1]  = 2.3e-6;
    startxxxa[1]  = 0.0;
    startxxaa[1]  = -6.5e-5;
    startxaaa[1]  = 1.19e-4;
    startxaaaa[1] = 0.0;
  }

  minuit->SetParameter(0, "TOF_Offset",startTOFOffset,0.01,240,250);
  minuit->SetParameter(1, "slewF3L",  startslew[0],    1,0,50);
  minuit->SetParameter(2, "slewF3R",  startslew[1],    1,0,50);
  minuit->SetParameter(3, "slewF7L",  startslew[2],    1,0,50);
  minuit->SetParameter(4, "slewF7R",  startslew[3],    1,0,50);
  minuit->SetParameter(5, "xx35",     startxx[0],      0.,0.7,1.2);
  minuit->SetParameter(6, "xa35",     startxa[0],      0.,0,0);
  minuit->SetParameter(7, "xd35",     startxd[0],      0.0,0,0);
  minuit->SetParameter(8, "xxx35",    startxxx[0],     0e-4,0,0);
  minuit->SetParameter(9, "xxa35",    startxxa[0],     0e-4,0,0);
  minuit->SetParameter(10,"xxd35",    startxxd[0],     0.,0,0);
  minuit->SetParameter(11,"xaa35",    startxaa[0],     0e-4,0,0);
  minuit->SetParameter(12,"xad35",    startxad[0],     0.1,0,0);
  minuit->SetParameter(13,"xdd35",    startxdd[0],     0.1,0,0);
  minuit->SetParameter(14,"xxxx35",   startxxxx[0],    0e-4,0,0);
  minuit->SetParameter(15,"xxxa35",   startxxxa[0],    0e-4,0,0);
  minuit->SetParameter(16,"xxaa35",   startxxaa[0],    0e-4,0,0);
  minuit->SetParameter(17,"xaaa35",   startxaaa[0],    0e-4,0,0);
  minuit->SetParameter(18,"xaaaa35",  startxaaaa[0],   0.,0,0);
  minuit->SetParameter(19,"xx57",     startxx[1],      0.,0.7,1.2);
  minuit->SetParameter(20,"xa57",     startxa[1],      0,0,0);
  minuit->SetParameter(21,"xd57",     startxd[1],      0.,0,0);
  minuit->SetParameter(22,"xxx57",    startxxx[1],     0,0,0);
  minuit->SetParameter(23,"xxa57",    startxxa[1],     0,0,0);
  minuit->SetParameter(24,"xxd57",    startxxd[1],     0,0,0);
  minuit->SetParameter(25,"xaa57",    startxaa[1],     0.,0,0);
  minuit->SetParameter(26,"xad57",    startxad[1],     0.,0,0);
  minuit->SetParameter(27,"xdd57",    startxdd[1],     0.,0,0);
  minuit->SetParameter(28,"xxxx57",   startxxxx[1],    0.e-5,0,0);
  minuit->SetParameter(29,"xxxa57",   startxxxa[1],    0.,0,0);
  minuit->SetParameter(30,"xxaa57",   startxxaa[1],    0.e-5,0,0);
  minuit->SetParameter(31,"xaaa57",   startxaaa[1],    0.e-5,0,0);
  minuit->SetParameter(32,"xaaaa57",  startxaaaa[1],   0e-6,0,0);

  //  minuit->SetPrintLevel(0);
  //create Minimizer (default is Migrad)
  minuit->CreateMinimizer();
  //  cout << "n.d.f = " << zedtrue.size() - 4 <<endl;
  TStopwatch w;
  w.Start();
  int iret=minuit->Minimize();
  w.Stop();
  cout << "Time: " << w.RealTime() << " , " << w.CpuTime() << endl; 
  if(iret != 0) {
    cout << "error: Minimization failed." << endl;
  }
  ofstream fout;
  fout.open(filenameout.c_str());
  
  for(int i=0;i<5;i++) {
    fout << minuit->GetParameter(i) << endl;
  }
  fout << endl; 
  fout.close();
  return;
}
