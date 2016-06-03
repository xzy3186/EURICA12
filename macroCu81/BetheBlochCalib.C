// This file is used to determine the parameters in the Bethe-Bloch function.
// Data set is deltaE vs beta @ F5-F7 of several zed. 
// Fitting is done for data set of all zed using Minuit2
#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TString.h"
#include "Minuit2/FCNBase.h"
#include "TFitterMinuit.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
class BetheBlochFCN : public ROOT::Minuit2::FCNBase {
  vector<int> zed;
  vector<double> beta;
  vector<double> dE;
  vector<double> dEerr;
public: 
  BetheBlochFCN() {};
  double operator() (const vector<double> & par) const {
    //number of parameter is 5.
    double chi2=0;
    for (int i=0; i<(int)zed.size(); i++) {
      chi2+=pow(dE[i]-dEcalc(i,par),2)/dEerr[i]/dEerr[i];
    }
    return chi2;
  }

  double Up() const {return 1.;}

  void SetZed(vector<int> zedin) {zed = zedin;}
  void Setbeta(vector<double> betain) {beta = betain;}
  void SetdE(vector<double> dEin) {dE = dEin;}
  void SetdEerr(vector<double> dEerrin) {dEerr = dEerrin;}
  double dEcalc(int i, const vector<double> & par) const {
    //const member function to call this from operator()
    double beta_mod = beta[i] - par[2];//conversion from beta57 to betaIC
    double beta2_mod = beta_mod*beta_mod;
    return par[0]+par[1]*zed[i]*zed[i]/beta2_mod
      *(log(5911*beta2_mod/(1-beta2_mod)) -beta2_mod
	+par[3]+par[4]*beta_mod);//empirical correction
  }
};

void BetheBlochCalib(char* filename) {
  int zedmin = 26, zedmax = 32;
  double betamin = 0.6, betamax = 0.68;
  double deltaEmin = 180, deltaEmax = 320;
  //  double d_zed = 0.4; //for zed gate
  TString flag = "&&flagall==1";
  char filenameout[] = "macroCu81/parameters/zedcalib/zedcalib5prm.txt";
  double betashift = 0.0034; // typical value of betaIC - beta57, here this is assumed to be constant. 

  TFile *_betheblochFile = TFile::Open(filename);
  TTree *tree = (TTree*)_betheblochFile->Get("tree");

  TDirectory *tdir = gDirectory; // for tree->Project
  TH2D *h_betheblochcalib = new TH2D("h_betheblochcalib","hist for bethe-bloch calibration", 300, betamin, betamax, 500, deltaEmin, deltaEmax);
  TProfile *hpx_betheblochcalib = new TProfile("hpx_betheblochcalib","", 300, betamin, betamax);

  vector<int> zedlist;
  for(int i=zedmin;i<zedmax+1;i++) {
    zedlist.push_back(i);
  }

  //data for calibration
  vector<int> zedtrue; //zed (true)
  vector<double> beta; // beta57
  vector<double> dE; //dE
  vector<double> dEerr; //dEerror

  stringstream ss;
  string str;
  double beta_temp,dE_temp, dEerr_temp;
  //Extraction of dE, beta57 for zed from zedmin to zedmax
  for(int j=0;j<(int)zedlist.size();j++) {
    ss.str("");ss.clear(stringstream::goodbit); str.clear(); 
    ss << zedlist[j];  ss >>  str;
    TString zedstr("Zed==");  zedstr+=str;
    tdir->cd();
    tree->Project("h_betheblochcalib","deltaE:beta57",zedstr+flag);
    
    h_betheblochcalib->ProfileX("hpx_betheblochcalib");
    
    for (int i=0;i<hpx_betheblochcalib->GetNbinsX();i++) {
      beta_temp=hpx_betheblochcalib->GetXaxis()->GetBinCenter(i);
      dE_temp=hpx_betheblochcalib->GetBinContent(i);
      dEerr_temp=hpx_betheblochcalib->GetBinError(i);
      if (dEerr_temp>0) {
	zedtrue.push_back(zedlist[j]);
	beta.push_back(beta_temp);
	dE.push_back(dE_temp);
	dEerr.push_back(dEerr_temp);
      }
    }
  }

  TFitterMinuit * minuit = new TFitterMinuit();
  BetheBlochFCN fcn;
  fcn.SetZed(zedtrue);
  fcn.Setbeta(beta);
  fcn.SetdE(dE);
  fcn.SetdEerr(dEerr);
  minuit->SetMinuitFCN(&fcn);
  //starting values
  double startdEconst = 0;
  double startfactor = 1.027*(0.1535*0.103*172/375.54*2);//0.103 = rho*dx
  double startbetashift = betashift; //corresponding to betaIC - beta57
  double startp0=0,startp1=0; //empirical parameter: 0th and 1st of pol1
  minuit->SetParameter(0,"dEconst",  startdEconst,  0.01,0,0);
  minuit->SetParameter(1,"factor",   startfactor,   0.1,0,0);
  minuit->SetParameter(2,"betashift",startbetashift,0.,0,0); // constant
  minuit->SetParameter(3,"p0",       startp0,      0.1,0,0);
  minuit->SetParameter(4,"p1",       startp1,      0.1,0,0);
  //  minuit->SetPrintLevel(0);
  //create Minimizer (default is Migrad)
  minuit->CreateMinimizer();
  //  cout << "n.d.f = " << zedtrue.size() - 4 <<endl;
  int iret=minuit->Minimize();

  if(iret != 0) {
    cout << "error: Minimization failed." << endl;
  }
  ofstream fout;
  fout.open(filenameout);
  
  for(int i=0;i<5;i++) {
    fout << minuit->GetParameter(i) << "  ";
  }
  fout << endl; 
  fout.close();
  return;
}
