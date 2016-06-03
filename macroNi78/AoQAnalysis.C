#define AoQAnalysis_cxx
#include "AoQAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void AoQAnalysis::SetTree(TTree *tree) {
   Init(tree);
}

double AoQAnalysis::Loop() { 
//   In a ROOT session, you can do:
//      Root > .L AoQAnalysis.C
//      Root > AoQAnalysis t(tree);
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return -1.;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   TFile* file;
   TTree* tree;
   if(strlen(fileout) > 0) {
     file=new TFile(fileout,"recreate");
     tree=new TTree("tree","tree");
     initTreeOutput(tree);
   }
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      //      if(jentry%10000==0) cout << jentry << endl;

      if (Cut() < 0) continue;
      CorrectedTOF();
      deltaCalc();
      betaCalc();
      tof37Calc();
      FCN+=pow(tof37-tof37_calculated,2);
      if(strlen(fileout)>0) tree->Fill();
   }
   if(strlen(fileout)>0) {
     tree->Write();
     file->Close();
   }
   return FCN;
}


double AoQAnalysis::Loop(const vector<double> & par) const { 
   FCN = 0;
   if (fChain == 0) return -1.;

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   int ip=0;
   SetTOFOffset(par[ip]);ip++;
   SetSlew(par[ip],par[ip+1],par[ip+2],par[ip+3]);ip+=4;
   SetFirstME(0,par[ip],par[ip+1],par[ip+2]);ip+=3;
   SetSecondME(0,par[ip],par[ip+1],par[ip+2],par[ip+3],par[ip+4],par[ip+5]);ip+=6;
   SetThirdME(0,par[ip],par[ip+1],par[ip+2],par[ip+3]);ip+=4;
   SetFourthME(0,par[ip]);ip+=1;
   SetFirstME(1,par[ip],par[ip+1],par[ip+2]);ip+=3;
   SetSecondME(1,par[ip],par[ip+1],par[ip+2],par[ip+3],par[ip+4],par[ip+5]);ip+=6;
   SetThirdME(1,par[ip],par[ip+1],par[ip+2],par[ip+3]);ip+=4;
   SetFourthME(1,par[ip]);ip+=1;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (Cut() < 0) continue;
      CorrectedTOF();
      deltaCalc();
      betaCalc();
      tof37Calc();
      FCN+=(tof37-tof37_calculated)*(tof37-tof37_calculated);
 //     if(Zed[0]==30&&Mass[0]==80&&jentry<100) {
 //	cout << fTime[1] << "  " << fTime[3] << "  " << tof37 << "  " << tof37_calculated <<"  " << delta[0] << "  "<< delta[1]<< "  "<< beta[0] << "  " << beta[1] << "  "<< BrhoCenter[0] << "  " << BrhoCenter[1] << endl;
 //     }
   }
   return FCN;
}

void AoQAnalysis::initialize() {
//  BrhoCenter[0]=7.5715; // read from root file
//  BrhoCenter[1]=7.0675;
  length[0] = 23488.; // mm
  length[1] = 23488.;
  u = 931.49432;
  clight = 299.792; //mm/ns
  FCN = 0;
}

void AoQAnalysis::initTreeOutput(TTree* tree) {
  tree->Branch("Zed",&Zed[0],"Zed/I");
  tree->Branch("Mass",&Mass[0],"Mass/I");
  tree->Branch("delta35",&delta[0],"delta35/D");
  tree->Branch("delta37",&delta[1],"delta37/D");
  tree->Branch("beta35",&beta[0],"beta35/D");
  tree->Branch("beta37",&beta[1],"beta37/D");
  tree->Branch("tof37",&tof37,"tof37/D");
  tree->Branch("tof37_calculated",&tof37_calculated,"tof37_calculated/D");
}


void AoQAnalysis::loadParameters() {
  tofoffset = 244.55;
  slew[0] = 0.;
  slew[1] = 0.;
  slew[2] = 0.;
  slew[3] = 0.;

  xx[0] = 0.917467;
  xa[0] = -0.0052;
  xd[0] = 31.605;
  xad[0] = 0.0;
  xdd[0] = 0.0;
  xaa[0] = 0.0;
  xxa[0] = 0.0;
  xxxx[0] = 0.0;
  xxaa[0] = 0.0;
  xx[1] = 1.0910;
  xa[1] = 0.020415;
  xd[1] = -34.4457; 
  xad[1] = 0.0;
  xdd[1] = 0.0;
  xaa[1] = 0.0;
  xxa[1] = 0.0;
  xxxx[1] = 0.0;
  xxaa[1] = 0.0;
}

inline void AoQAnalysis::CorrectedTOF() const {
  tof37 = fTime[3]-fTime[1] + tofoffset 
    +slew[0]/sqrt(fQLRaw[1])+slew[1]/sqrt(fQRRaw[1])
    -slew[2]/sqrt(fQLRaw[3])-slew[3]/sqrt(fQRRaw[3]); 
}

inline void AoQAnalysis::deltaCalc() const {
  double xi[2],xf[2],ai[2],af[2];
  xi[0]=F3X[0];
  xi[1]=F5X[0];
  xf[0]=F5X[0];
  xf[1]=F7X[0];
  ai[0]=F3A[0];
  ai[1]=F5A[0];
  af[0]=F5A[0];
  af[1]=F7A[0];

  // xf = a*delta^2 + b*delta + c
  // delta = (-b+/-sqrt(b^2-4a(c-xf)))/2a
  // if c=0,xf=0, delta =0;
  // for b>0, F3-F5
  // delta = (-b+sqrt(b^2-4a(c-xf)))/2a
  // for b<0, F5-F7
  // delta = (-b-sqrt(b^2-4a(c-xf)))/2a

  double coefa[2], coefb[2], coefc[2];

  for (int i=0;i<2;i++) {
    coefa[i] = xdd[i];
    coefb[i] = xd[i] + xxd[i]*xi[i] + xad[i]*ai[i];
    coefc[i] = xx[i]*xi[i] + xa[i]*ai[i] 
      + xxx[i]*xi[i]*xi[i] + xxa[i]*xi[i]*ai[i] + xaa[i]*ai[i]*ai[i]  
      + xxxx[i]*xi[i]*xi[i]*xi[i] + xxxa[i]*xi[i]*xi[i]*ai[i] 
      + xxaa[i]*xi[i]*ai[i]*ai[i] + xaaa[i]*ai[i]*ai[i]*ai[i]
      + xaaaa[i]*ai[i]*ai[i]*ai[i]*ai[i];

    if(coefa[i]==0) {
      delta[i] = (xf[i]-coefc[i])/coefb[i];
    } else {
      delta[i] = (-coefb[i] +pow(-1,i)*sqrt(coefb[i]*coefb[i] 
		 - 4*coefa[i]*(coefc[i]-xf[i])))/2/coefa[i];
    }
  }
}

inline void AoQAnalysis::betaCalc() const {
  for (int i=0;i<2;i++) {
    double mom = BrhoCenter[i]*(1+delta[i]/100) * Zed[0] * 299.792458;
    double mass = Mass[0] * 931.49406 ; //mass in MeV
    beta[i]=mom/mass/sqrt(1+(mom/mass)*(mom/mass));
  }
}

inline void AoQAnalysis::tof37Calc() const {
  double tof[2];
  for (int i=0;i<2;i++) {
    tof[i]=length[i]/(beta[i]*clight);
  }
  tof37_calculated = tof[0]+tof[1];
}
