#include <iostream>
#include <sstream>
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TGraph.h"
#include "include/TArtRIPS.hh"
#include "macro/Nucleus.cc"

string itostr(int val) {
  stringstream ss;
  ss << val;
  return ss.str();
}
double Dispersion(char* filename, int z, int mass){ 
  //There is large particle dependence. Due to slewing?
  double thickness_center_mm =4.44;
  double angle_mrad = 5.35;
  TFile *_f = new TFile(filename);
  TTree *tree = (TTree*)_f->Get("tree");
  TClonesArray* rips_array = new TClonesArray("TArtRIPS");
  tree->SetBranchAddress("BigRIPSRIPS",&rips_array);
  tree->GetEvent(0);

  double center_brho[2];
  for(int i=0;i<2;i++) {
    TArtRIPS *rips=(TArtRIPS*)rips_array->At(i);
    center_brho[i]= rips->GetCenterBrho();
    cout << center_brho[i]<<endl;
  }

  string condition("flagall==1&&");
  condition+=string("Zed==")+itostr(z)+string("&&Mass==")+itostr(mass)+string("&&abs(F3X)<1&&abs(F7X)<10");
  TDirectory *tdir = gDirectory;

  TH2D *hdisp = new TH2D("hdisp","hdisp",500,-120,120,200,230,280);
  TProfile *profx = new TProfile("profx","profx",500,-120,120);
  tdir->cd();
  tree->Project("hdisp","tof37:F5X",condition.c_str());
  profx = hdisp->ProfileX();

  TFitResultPtr fr = profx->Fit("pol1","SQ");
  double p0 = fr->Parameter(0); // tof37 value at F5X=0
  double p1 = fr->Parameter(1);     
  cout << p0 << "  " << p1 << endl;
  Nucleus nucl1(z,mass), nucl2(z,mass);

  // tof37 calculation 
  double L35=23488., L57=23488.;
  nucl1.SetBeamEnergy(center_brho[0],"Tm");
  nucl2.SetBeamEnergy(nucl1.EnergyAfterMaterial("Al",2700*thickness_center_mm/10,"Tm"),"Tm");
  double tof37_center = L35/nucl1.velocity()/10 + L57/nucl2.velocity()/10;

  double offset = -50; // F5X=-50
  double tof37_offset, p1_calc;
 
  double xd35[50],p1_diff[50];
  // xd35 vs tof_calc(ns)
  for (int i=0;i<50;i++) {
    xd35[i] = 27 + i*0.2;
    nucl1.SetBeamEnergy(center_brho[0]*(1+offset/xd35[i]/100),"Tm");
    nucl2.SetBeamEnergy(nucl1.EnergyAfterMaterial("Al",2700*(thickness_center_mm+offset*tan(angle_mrad/1000))/10,"Tm"),"Tm");
    tof37_offset= L35/nucl1.velocity()/10 + L57/nucl2.velocity()/10; 
    p1_calc = (tof37_offset - tof37_center)/offset; 
    p1_diff[i] = p1-p1_calc;
  }

  TGraph *gr = new TGraph(50,p1_diff,xd35);
  gr->Draw("AC*");
  fr = gr->Fit("pol1","SQ","",-0.001,0.001);

  nucl1.SetBeamEnergy(center_brho[0]*(1+offset/(fr->Parameter(0))/100),"Tm");
  nucl2.SetBeamEnergy(nucl1.EnergyAfterMaterial("Al",2700*(thickness_center_mm+offset*tan(angle_mrad/1000))/10,"Tm"),"Tm");
  cout << (nucl1.Brho()/center_brho[0]-1)*100 << endl;
  cout << (nucl2.Brho()/center_brho[1]-1)*100 << endl;

  return fr->Parameter(0);
}
