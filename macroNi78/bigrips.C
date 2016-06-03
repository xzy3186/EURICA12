#define bigrips_cxx
// BigRIPS offline analysis for EURICA data
// version 1.0   2013/2/22 Toshiyuki Sumikama 
// version 1.0.1 2013/3/5 Toshiyuki Sumikama 
#include "bigrips.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using namespace std;

void bigrips::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L bigrips.C
//      Root > bigrips t
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
   nan = 0./0.;
   if (fChain == 0) return;

   cout << fileout << endl;
   //   TFile file("test.root","recreate");
   TFile file(fileout,"recreate");
   TTree* tree=new TTree("tree","tree");

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   inittreeout(tree);
   initofflinepid();

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%10000==0) cout << jentry << endl;
      //      if (Cut(ientry) < 0) continue;
      fillbigripsall(); //fill anaroot values
      offlinepid();     //offline pid
      tree->Fill();
   }
   tree->Write();
   file.Close();
}

void bigrips::readtof() {
  string str;
  str=dir+"parameters/tof.txt";
  ifstream fin(str.c_str());
  fin >> tofoffset37;
  for (int i=0;i<4;i++) {
    fin >> slew37[i];
  }
  fin >> tofoffset711;
}

void bigrips::TOFGate(int &flagtoft, int &flagtofq) {
  // TOF gates to reject bad events
  if(BigRIPSPlastic_fTLRaw[1]<4094 && //overflow of TDC
     BigRIPSPlastic_fTRRaw[1]<4094 &&
     BigRIPSPlastic_fTLRaw[3]<4094 &&
     BigRIPSPlastic_fTRRaw[3]<4094 //&&

     //(BigRIPSPlastic_fTLRaw[1]+BigRIPSPlastic_fTRRaw[1])>3600 &&
     //(BigRIPSPlastic_fTLRaw[1]+BigRIPSPlastic_fTRRaw[1])<5100 &&

     //(BigRIPSPlastic_fTLRaw[3]+BigRIPSPlastic_fTRRaw[3])>4000 &&
     //(BigRIPSPlastic_fTLRaw[3]+BigRIPSPlastic_fTRRaw[3])<4300 &&

     //(BigRIPSPlastic_fTLRaw[1]-BigRIPSPlastic_fTRRaw[1])>-70 &&
     //(BigRIPSPlastic_fTLRaw[1]-BigRIPSPlastic_fTRRaw[1])< 80 &&
     //(BigRIPSPlastic_fTLRaw[3]-BigRIPSPlastic_fTRRaw[3])>  0 &&
     //(BigRIPSPlastic_fTLRaw[3]-BigRIPSPlastic_fTRRaw[3])<150 
     ) {
    flagtoft = 1;
  } else {
    flagtoft = 0;
  }

  //if(BigRIPSPlastic_fQLRaw[1]> 400 && 
  //   BigRIPSPlastic_fQRRaw[1]> 250 &&
  //   BigRIPSPlastic_fQLRaw[3]> 150 &&
  //   BigRIPSPlastic_fQRRaw[3]> 150 ) {
    flagtofq = 1;
  //} else {
  //  flagtofq = 0;
  //}
}

void bigrips::initPositionCalc(){
  //"parameters/ppac/tsum.txt"
  //"parameters/ppac/tsumspecial.txt"
  //"parameters/zshift.txt"
  string str;
  str=dir+"parameters/ppac/tsum.txt";
  ifstream fin(str.c_str());
/*
  Array of TSumX[i][j], TSumY[i][j]
  i: focal plane, 4-7: F3, 10-13: F5, 14-17: F7, 30-33: F11
  j: 0: min, 1: max
*/
  if(!fin) exit(1);
  string str1,str2;
  stringstream ss;
  int i,k=0, isXorY=0; 
  double val;
  while (!fin.eof()) {
    str1.clear(); str2.clear();
    ss.str(""); ss.clear(stringstream::goodbit);
    getline(fin,str1); 
    if(str1.substr(0,10).compare("focalplane")==0) {
      ss << str1;
      ss >> str2;
      ss >> i; 
      if(i==3) {
	k = 4;
      } else if (i==5) {
	k = 10;
      } else if (i==7) {
	k = 14;
      } else if (i==11) {
	k = 30;
      } 
      str2.clear();
      ss >> str2;
      if(str2.compare("x")==0) {
	isXorY = 0;
      } else if (str2.compare("y")==0) {
	isXorY = 1;
      }
    } else if (str1.length()>1){
      ss << str1;
      if (isXorY==0) {
	ss >> val;
	TSumX[k][0] = val;
	ss >> TSumX[k][1];
	k++;
      } else {
	ss >> TSumY[k][0];
	ss >> TSumY[k][1];
	k++;
      }
    } else {
      //nothing
    }

  }
  fin.close();


  // parameter to recover the event using wider TSumX gate.
  // k=0, for F3-PPAC1B
  str.clear();
  str=dir+"parameters/ppac/tsumspecial.txt";
  fin.open(str.c_str());

  if(!fin) exit(1);
  k=0;
  while (!fin.eof()) {
    val = -10000;
    fin >> val; 
    if (val>-10000) {
      TSumXSpecial[k]=val;
      k++;
    }
  }
  fin.close();

//  fine tuning of z position of focal plane in X & Y direction
  str.clear();
  str=dir+"parameters/zshift.txt";
  fin.open(str.c_str());
  fin >> zshiftF3X;  fin >> zshiftF3Y;
  fin >> zshiftF5X;  fin >> zshiftF5Y;
  fin >> zshiftF7X;  fin >> zshiftF7Y;
  fin >> zshiftF11PlaX;  fin >> zshiftF11PlaY;
  fin.close();
}

void bigrips::PositionCalc(int ifocalplane) {
  double DPPACX[2], DPPACY[2], DPPACXZ[2], DPPACYZ[2];
  int inippac, ippac;
  int i;

  //TSum gates are given in initPositionCalc()

  switch (ifocalplane) {
    //These numbers should be changed if raw data structure is changed. 
  case 3: 
    inippac = 4;
    break;
  case 5:
    inippac = 10;
    break;
  case 7:
    inippac = 14;
    break;
  case 11:
    inippac = 30;
    break;
  default:
    inippac = 100; 
  }
  
  for (i=0;i<2;i++) {
    //for each double ppac
    ippac = inippac + 2*i;
    if(BigRIPSPPAC_fTSumX[ippac]>TSumX[ippac][0]
       &&BigRIPSPPAC_fTSumX[ippac]<TSumX[ippac][1]) {
      if (BigRIPSPPAC_fTSumX[ippac+1]>TSumX[ippac+1][0]
	  &&BigRIPSPPAC_fTSumX[ippac+1]<TSumX[ippac+1][1]) {
	//two ppacs are fired. 
	DPPACX[i]  = (BigRIPSPPAC_fX[ippac]+BigRIPSPPAC_fX[ippac+1])/2;
	DPPACXZ[i] = (BigRIPSPPAC_xzpos[ippac]+BigRIPSPPAC_xzpos[ippac+1])/2;
      } 
      else {
	//one ppac is fired 
	DPPACX[i]  = BigRIPSPPAC_fX[ippac];
	DPPACXZ[i] = BigRIPSPPAC_xzpos[ippac];
      }
    } 
    else if(BigRIPSPPAC_fTSumX[ippac+1]>TSumX[ippac+1][0]
	    &&BigRIPSPPAC_fTSumX[ippac+1]<TSumX[ippac+1][1]) {
	//one ppac is fired 
      DPPACX[i]  = BigRIPSPPAC_fX[ippac+1];
      DPPACXZ[i] = BigRIPSPPAC_xzpos[ippac+1];
    } 
    else {
      //no ppac is fired
    DPPACX[i] = -1000.;
    DPPACXZ[i] = -1000.;
    }
  }


  for (i=0;i<2;i++) {
    ippac = inippac + 2*i;
    if(BigRIPSPPAC_fTSumY[ippac]>TSumY[ippac][0]
       &&BigRIPSPPAC_fTSumY[ippac]<TSumY[ippac][1]) {
      if (BigRIPSPPAC_fTSumY[ippac+1]>TSumY[ippac+1][0]
	  &&BigRIPSPPAC_fTSumY[ippac+1]<TSumY[ippac+1][1]) {
	//two ppacs are fired. 
	DPPACY[i] = (BigRIPSPPAC_fY[ippac]+BigRIPSPPAC_fY[ippac+1])/2;
	DPPACYZ[i] = (BigRIPSPPAC_yzpos[ippac]+BigRIPSPPAC_yzpos[ippac+1])/2;
      } 
      else {
	//one ppac is fired 
	DPPACY[i] = BigRIPSPPAC_fY[ippac];
	DPPACYZ[i] = BigRIPSPPAC_yzpos[ippac];
      }
    } 
    else if(BigRIPSPPAC_fTSumY[ippac+1]>TSumY[ippac+1][0]
	    &&BigRIPSPPAC_fTSumY[ippac+1]<TSumY[ippac+1][1]) {
	//one ppac is fired 
      DPPACY[i] = BigRIPSPPAC_fY[ippac+1];
      DPPACYZ[i] = BigRIPSPPAC_yzpos[ippac+1];
    } 
    else {
	//no ppac is fired 
    DPPACY[i] = -1000.;
    DPPACYZ[i] = -1000.;
    }
  }


  switch(ifocalplane) {
  case 3:

    //Here is a recovered event for spectroscopy.  
    //PPAC1B is fired only when wider gate is used. 
    //
    if(DPPACX[0]==-1000 && BigRIPSPPAC_fTSumX[5]>TSumXSpecial[0]) {
      //PPAC1B is fired with wider TSum gate
      if (flagTSumX <2) flagTSumX = 2;
      DPPACX[0] = BigRIPSPPAC_fX[5];
      DPPACXZ[0] = BigRIPSPPAC_xzpos[5];
    }


    if(DPPACX[0]!=-1000. && DPPACX[1]!=-1000.) {
      F3A = atan(
		 (DPPACX[1] - DPPACX[0]) / (DPPACXZ[1] - DPPACXZ[0])
		 )*1000; 
      F3X = DPPACX[0] - (DPPACXZ[0] - zshiftF3X) * tan(F3A/1000.);
    } else if(DPPACX[0]!=-1000.) { 
      //PPAC1 is fired and PPAC2 is not fired.
      if (flagTSumX <2) flagTSumX = 2;
      F3X = DPPACX[0];   // F3X is close to PPAC1.
      F3A = 0.0;

    }  else {
      if (flagTSumX==1) flagTSumX = 0;
      F3A = nan;
      F3X = nan;
    }	

    if(DPPACY[0]!=-1000. && DPPACY[1]!=-1000.) {
      F3B = atan(
		 (DPPACY[1] - DPPACY[0]) / (DPPACYZ[1] - DPPACYZ[0])
		 )*1000; 
      F3Y = DPPACY[0] - (DPPACYZ[0] - zshiftF3Y) * tan(F3B/1000.);
    }  else {
      F3B = nan;
      F3Y = nan;
    }	
    break;
  case 5:
    if(DPPACX[0]!=-1000. && DPPACX[1]!=-1000.) {
      F5A = atan(
		 (DPPACX[1] - DPPACX[0]) / (DPPACXZ[1] - DPPACXZ[0])
		 )*1000; 
      F5X = DPPACX[0] - (DPPACXZ[0] - zshiftF5X) * tan(F5A/1000.);
    } else {
      if(flagTSumX==1) flagTSumX = 0;
      F5A = nan;
      F5X = nan;
    }

    if(DPPACY[0]!=-1000. && DPPACY[1]!=-1000.) {
      F5B = atan(
		 (DPPACY[1] - DPPACY[0]) / (DPPACYZ[1] - DPPACYZ[0])
		 )*1000; 
      F5Y = DPPACY[0] - (DPPACYZ[0] - zshiftF5Y) * tan(F5B/1000.);
    } else {
      F5B = nan;
      F5Y = nan;
    }
    break;
  case 7:
    if(DPPACX[0]!=-1000. && DPPACX[1]!=-1000.) {
      F7A = atan(
		 (DPPACX[1] - DPPACX[0]) / (DPPACXZ[1] - DPPACXZ[0])
		 )*1000; 
      F7X = DPPACX[0] - (DPPACXZ[0] - zshiftF7X) * tan(F7A/1000.);
    } else {
      if(flagTSumX==1) flagTSumX = 0;
      F7A = nan;
      F7X = nan;
    }

    if(DPPACY[0]!=-1000. && DPPACY[1]!=-1000.) {
      F7B = atan(
		 (DPPACY[1] - DPPACY[0]) / (DPPACYZ[1] - DPPACYZ[0])
		 )*1000; 
      F7Y = DPPACY[0] - (DPPACYZ[0] - zshiftF7Y) * tan(F7B/1000.);
    } else {
      F7B = nan;
      F7Y = nan;
    }
    break;
  case 11:
    if(DPPACX[0]!=-1000. && DPPACX[1]!=-1000.) {
      F11PlaA = atan(
		 (DPPACX[1] - DPPACX[0]) / (DPPACXZ[1] - DPPACXZ[0])
		 )*1000; 
      F11PlaX = DPPACX[0] - (DPPACXZ[0] - zshiftF11PlaX) * tan(F11PlaA/1000.);
    } else {
      F11PlaA = nan;
      F11PlaX = nan;
    }

    if(DPPACY[0]!=-1000. && DPPACY[1]!=-1000.) {
      F11PlaB = atan(
		 (DPPACY[1] - DPPACY[0]) / (DPPACYZ[1] - DPPACYZ[0])
		 )*1000; 
      F11PlaY = DPPACY[0] - (DPPACYZ[0] - zshiftF11PlaY) * tan(F11PlaB/1000.);
//      flagF11PlaY = 1;
//      if(F11PlaY>=39) flagF11PlaY = 0;
    } else {
      F11PlaB = nan;
      F11PlaY = nan;
      //      flagF11PlaY = 2;
    }
    break;
  }
}

void bigrips::readoptics() {
  string str1,str2;
  stringstream ss;
  string str;
  str=dir+"parameters/optics.txt";
  ifstream fin(str.c_str());
  if(!fin) exit(1);
  while (!fin.eof()) {
    str1.clear(); str2.clear();
    ss.str(""); ss.clear(stringstream::goodbit);
    getline(fin, str1);
    ss << str1;
    ss >> str2; 
    if (str2.compare("xx35")==0) {
      ss >> xx35;
    } else if (str2.compare("xa35")==0) {
      ss >> xa35;
    } else if (str2.compare("xd35")==0) {
    ss >> xd35;
    } else if (str2.compare("xxx35")==0) {
      ss >> xxx35;
    } else if (str2.compare("xxa35")==0) {
      ss >> xxa35;
    } else if (str2.compare("xxd35")==0) {
      ss >> xxd35;
    } else if (str2.compare("xaa35")==0) {
      ss >> xaa35;
    } else if (str2.compare("xad35")==0) {
      ss >> xad35;
    } else if (str2.compare("xdd35")==0) {
      ss >> xdd35;
    } else if (str2.compare("xxxx35")==0) {
      ss >> xxxx35;
    } else if (str2.compare("xxxa35")==0) {
      ss >> xxxa35;
    } else if (str2.compare("xxaa35")==0) {
      ss >> xxaa35;
    } else if (str2.compare("xaaa35")==0) {
      ss >> xaaa35;
    } else if (str2.compare("xaaaa35")==0) {
      ss >> xaaaa35;
    } else if (str2.compare("xx57")==0) {
      ss >> xx57;
    } else if (str2.compare("xa57")==0) {
      ss >> xa57;
    } else if (str2.compare("xd57")==0) {
      ss >> xd57;
    } else if (str2.compare("xxx57")==0) {
      ss >> xxx57;
    } else if (str2.compare("xxa57")==0) {
      ss >> xxa57;
    } else if (str2.compare("xxd57")==0) {
      ss >> xxd57;
    } else if (str2.compare("xaa57")==0) {
      ss >> xaa57;
    } else if (str2.compare("xad57")==0) {
      ss >> xad57;
    } else if (str2.compare("xdd57")==0) {
      ss >> xdd57;
    } else if (str2.compare("xxxx57")==0) {
      ss >> xxxx57;
    } else if (str2.compare("xxxa57")==0) {
      ss >> xxxa57;
    } else if (str2.compare("xxaa57")==0) {
      ss >> xxaa57;
    } else if (str2.compare("xaaa57")==0) {
      ss >> xaaa57;
    } else if (str2.compare("xaaaa57")==0) {
      ss >> xaaaa57;
    }
  }
}

void bigrips::readdEcoef(){
  string str;
  str=dir+"parameters/zedcalib/dEGainCalib.txt";
  ifstream fin(str.c_str());
  //parameters for gain shift 
  if(!fin) exit(1);
  string strbuf;
  stringstream ss;
  Double_t dbuf;
  while (!fin.eof()) {
    strbuf.clear();
    fin >> strbuf;
    if (strbuf.size()>0) {
      dEGainRun.push_back(atoi(strbuf.c_str()));
      fin >> dbuf;
      dEGain0.push_back(dbuf);
      fin >> dbuf; 
      dEGain1.push_back(dbuf);
    }
  }
  fin.close();
  str.clear();
  str=dir+"parameters/zedcalib/dECoef.txt";
  fin.open(str.c_str());
  fin >> dEcoef0;
  fin >> dEcoef1;
  fin.close();
}

void bigrips::getdEGain(double &dE0, double &dE1) {
  if(dEGainRun.size()>0) {
    for (unsigned int i=0; i<dEGainRun.size(); i++) {
      if (dEGainRun[i]==EventInfo_runnumber[0]) {
	dE0 = dEGain0[i];
	dE1 = dEGain1[i];
	break;
      }
    } 
  } else {
    dE0 =0.;
    dE1 =1.;
  }
}

void bigrips::DeltaECalc(){
  double dEg0, dEg1; // dEg0 = 0, dEg1 = 1 for selected run
  getdEGain(dEg0,dEg1);   

  deltaE = dEcoef0 + dEcoef1 * (dEg0+dEg1*BigRIPSIC_fRawADCSqSum[1]);
}


void bigrips::readzedcoef(const char* filename, int numOfPar){
  ifstream fin(filename);
  if(!fin) exit(1);
  string strbuf;
  stringstream ss;
  Double_t dbuf;
  int flag; // flag ==0: common for all run, 1: run number dependent

  getline(fin,strbuf); 
  strbuf.clear();
  getline(fin,strbuf); 
  if (strbuf.size()<1) {
    flag =0; // common parameters
  } else {
    flag =1; // runnumber dependent parameters
  } 
  fin.clear();
  fin.seekg(0,ios::beg);
  if (flag==0) {// common parameters
    strbuf.clear();
    zcoefRun.push_back(0); // to make size same as others
    fin >> dbuf; 
    zcoef0.push_back(dbuf);
    fin >> dbuf; 
    zcoef1.push_back(dbuf);
    if (numOfPar==5) { 
      fin >> dbuf; 
      zcoef2.push_back(dbuf);
      fin >> dbuf; 
      zcoef3.push_back(dbuf);
      fin >> dbuf;
      zcoef4.push_back(dbuf);
    }
  } else { // runnumber dependent parameters
    while (!fin.eof()) {
      strbuf.clear();
      fin >> strbuf;
      if (strbuf.size()>0) {
	zcoefRun.push_back(atoi(strbuf.c_str()));
	fin >> dbuf;
	zcoef0.push_back(dbuf);
	fin >> dbuf; 
	zcoef1.push_back(dbuf);
	if (numOfPar==5) {
	  fin >> dbuf; 
	  zcoef2.push_back(dbuf);
	  fin >> dbuf; 
	  zcoef3.push_back(dbuf);
	  fin >> dbuf;
	  zcoef4.push_back(dbuf);
	}
      }
    }
  }
  fin.close();
}

void bigrips::getzedcoef(double &zc0, double &zc1) {
  if (zcoefRun.size()==1) {
    zc0 = zcoef0[0];
    zc1 = zcoef1[0];
  } else {
    for (int i=0; i<(int)zcoefRun.size(); i++) {
      if (zcoefRun[i]==EventInfo_runnumber[0]) {
	zc0 = zcoef0[i];
	zc1 = zcoef1[i];
	break;
      }
    }
  }
}

void bigrips::getzedcoef(double &zc0, double &zc1, double &zc2, double &zc3, double &zc4) {
  if (zcoefRun.size()==1) {
    zc0 = zcoef0[0];
    zc1 = zcoef1[0];
    zc2 = zcoef2[0];
    zc3 = zcoef3[0];
    zc4 = zcoef4[0];
  } else {
    for (int i=0; i<(int)zcoefRun.size(); i++) {
      if (zcoefRun[i]==EventInfo_runnumber[0]) {
	zc0 = zcoef0[i];
	zc1 = zcoef1[i];
	zc2 = zcoef2[i];
	zc3 = zcoef3[i];
	zc4 = zcoef4[i];
	break;
      }
    }
  }
}

void bigrips::zedCalc(int numOfPar){
  double zc0,zc1,zc2,zc3,zc4;  

  if (numOfPar == 2) {
    getzedcoef(zc0,zc1);
    double ionpair=5911;
    double beta2=beta57*beta57;
    double de_v = log(ionpair*beta2) - log(1-beta2) - beta2;
    zed = zc0 + zc1 * sqrt(deltaE/de_v)*beta57;
  } else if (numOfPar == 5) {
    getzedcoef(zc0,zc1,zc2,zc3,zc4);
    double betaIC = (beta57-zc2); // beta @ IC
    double betaIC2 = betaIC*betaIC;
    //deltaE = zc0 + zc1*zed*zed/betaIC2
    //  *(log(5911*betaIC2/(1-betaIC2))-betaIC2 + zc3 + zc4*betaIC)
    double zed2 = (deltaE - zc0)/zc1*betaIC2
      /(log(5911*betaIC2/(1-betaIC2)) - betaIC2 + zc3 + zc4*betaIC);
    zed = sqrt(zed2);
  }
}

void bigrips::ZedMass(){
  double zed1, zed2;
  double mass11, mass12, mass21, mass22;
  double dev11, dev12, dev21, dev22;
  double dzed = 0.149;      // final resolution
  double daoq = 0.001345;   // final resolution
  if (aoq37<2.85) {
    dzed = 4*dzed;
    daoq = 6*daoq;
  } else {
    dzed = 3*dzed;
    daoq = 3*daoq;
  }
  zed1 =  floor(zed);
  zed2 =  ceil(zed);
  mass11 =  floor(aoq37*zed1);
  mass12 =  ceil(aoq37*zed1);
  mass21 =  floor(aoq37*zed2);
  mass22 =  ceil(aoq37*zed2);
  dev11 =pow((zed-zed1)/dzed,2) + pow((aoq37-mass11/zed1)/daoq,2);
  dev12 =pow((zed-zed1)/dzed,2) + pow((aoq37-mass12/zed1)/daoq,2);
  dev21 =pow((zed-zed2)/dzed,2) + pow((aoq37-mass21/zed2)/daoq,2);
  dev22 =pow((zed-zed2)/dzed,2) + pow((aoq37-mass22/zed2)/daoq,2);
  if (dev11 < 1) {
    Zed =  (int)zed1; 
    Mass = (int)mass11;
  } else if (dev12 < 1) {
    Zed = (int)zed1; 
    Mass =(int)mass12;
  } else if (dev21 < 1) {
    Zed = (int)zed2; 
    Mass = (int)mass21;
  } else if (dev22 < 1) {
    Zed =  (int)zed2; 
    Mass = (int)mass22;
  } else {
    Zed = 0;
    Mass = 0;
  }
}

void bigrips::ZedMass2(){
  // for flagTSumX ==2
  double zed1, zed2;
  double mass11, mass12, mass21, mass22;
  double dev11, dev12, dev21, dev22;
  double dzed = 0.4;      // final resolution
  double daoq = 0.15;   // final resolution
  zed1 =  floor(zed);
  zed2 =  ceil(zed);
  mass11 =  floor(aoq37*zed1);
  mass12 =  ceil(aoq37*zed1);
  mass21 =  floor(aoq37*zed2);
  mass22 =  ceil(aoq37*zed2);
  dev11 =pow((zed-zed1)/dzed,2) + pow((aoq37-mass11/zed1)/daoq,2);
  dev12 =pow((zed-zed1)/dzed,2) + pow((aoq37-mass12/zed1)/daoq,2);
  dev21 =pow((zed-zed2)/dzed,2) + pow((aoq37-mass21/zed2)/daoq,2);
  dev22 =pow((zed-zed2)/dzed,2) + pow((aoq37-mass22/zed2)/daoq,2);
  if (dev11 < 1) {
    Zed =  (int)zed1; 
    Mass = (int)mass11;
  } else if (dev12 < 1) {
    Zed =  (int)zed1; 
    Mass = (int)mass12;
  } else if (dev21 < 1) {
    Zed =  (int)zed2; 
    Mass = (int)mass21;
  } else if (dev22 < 1) {
    Zed =  (int)zed2; 
    Mass = (int)mass22;
  } else {
    Zed = 0;
    Mass = 0;
  }
}

void bigrips::initF3XAoQ(){
//List of F3position for gate of reaction event between AoQ and Z measurements. 
  string str1,str2;
  stringstream ss;
  int i=0;
  double val;
  string str;
  str=dir+"parameters/flag/F3XAoQ.txt";
  ifstream fin(str.c_str());
  if(!fin) exit(1);
  while (!fin.eof()) {
    str1.clear(); str2.clear();
    ss.str(""); ss.clear(stringstream::goodbit);
    getline(fin, str1);
    if (str1.length()>1) {
      ss << str1;
      ss >> dbF3XAoQ[i][0]; //zed
      ss >> val;
      dbF3XAoQ[i][1] = val/dbF3XAoQ[i][0];// aoq
      ss >> dbF3XAoQ[i][2]; //f3x from data
      i++;
    }
  }  
  MaxF3XAoQ = i;

}

TGraph* bigrips::F3XAoQGate(Double_t f3x, Double_t df3x, 
		  Double_t aoq, Double_t daoq){
  TGraph *gr = new TGraph(9);
  Double_t factor=1/3.;
  gr->SetPoint(0, f3x+df3x,        aoq-daoq*factor);  
  gr->SetPoint(1, f3x+df3x,        aoq+daoq*factor);  
  gr->SetPoint(2, f3x+df3x*factor, aoq+daoq);  
  gr->SetPoint(3, f3x-df3x*factor, aoq+daoq);  
  gr->SetPoint(4, f3x-df3x,        aoq+daoq*factor);  
  gr->SetPoint(5, f3x-df3x,        aoq-daoq*factor);  
  gr->SetPoint(6, f3x-df3x*factor, aoq-daoq);  
  gr->SetPoint(7, f3x+df3x*factor, aoq-daoq);  

  Double_t x, y;  
  gr->GetPoint(0, x, y);
  gr->SetPoint(8, x, y);  
  return gr;
}

void bigrips::makeF3XAoQGate() {
  Double_t df3x = 6.;
  Double_t daoq=0.004;
  for (int i=0;i<MaxF3XAoQ;i++) {
    gtF3XAoQ[i] = F3XAoQGate(dbF3XAoQ[i][2], df3x, dbF3XAoQ[i][1], daoq);
  }
}

void bigrips::IsReaction() {
  Int_t flagInside;
  for (int i=0;i<MaxF3XAoQ;i++) {
    flagInside=gtF3XAoQ[i]->IsInside(F3X,aoq37);
    if (flagInside==1 && abs(zed-dbF3XAoQ[i][0]) > 0.65) {
      flagReaction = 0;
    }
  }
}

void bigrips::deltaERelationGate() {
  //consistency check of deltaE at plastic sci. and deltaE at IC
  // gate is written by fQLRaw*fQRRaw (y) vs zed (x)
  double x[20], y[20];
  int imax;
  TGraph *grF3 = new TGraph();
  TGraph *grF7 = new TGraph();
  //for plastic at F3
  x[0]=23.4677; y[0]=471504     ;
  x[1]=26.1185; y[1]=699523	;
  x[2]=27.9612; y[2]=988718	;
  x[3]=29.9655; y[3]=1.38914e+06;
  x[4]=31.0323; y[4]=1.61716e+06;
  x[5]=31.9698; y[5]=1.71171e+06;
  x[6]=32.5841; y[6]=1.70614e+06;
  x[7]=33.5;    y[7]=1.70614e+06;
  x[8]=33.5;    y[8]=1.02209e+06;
  x[9]=32.5841; y[9]=1.02209e+06;
  x[10]=31.1293;y[10]=799629	;
  x[11]=28.9634;y[11]=499311	;
  x[12]=23.4677;y[12]=293538	;
  x[13]=23.4677;y[13]=471504   ;
  imax = 14;
  for (int i=0;i<imax;i++) {
    grF3->SetPoint(i,x[i],y[i]);
  }

  x[0]=23.5323; y[0]=76016.9;
  x[1]=25.9569; y[1]=117436 ;
  x[2]=27.9289; y[2]=158247 ;
  x[3]=29.9655; y[3]=199057 ;
  x[4]=31     ; y[4]=214285 ;
  x[5]=32.5841; y[5]=213676 ;
  x[6]=33.5;    y[6]=213676 ;
  x[7]=33.5;    y[7]=104036 ;
  x[8]=32.681 ; y[8]=104036 ;
  x[9]=26.7328; y[9]=54089  ;
  x[10]=23.5323;y[10]=51652.5;
  x[11]=23.5323;y[11]=76016.9;
  imax = 12;

  for (int i=0;i<imax;i++) {
    grF7->SetPoint(i,x[i],y[i]);
  }

  if (grF3->IsInside(zed,BigRIPSPlastic_fQLRaw[1]*BigRIPSPlastic_fQRRaw[1])!=1||grF7->IsInside(zed,BigRIPSPlastic_fQLRaw[3]*BigRIPSPlastic_fQRRaw[3])!=1) {
    flagdERelation = 0;
  }
}

void bigrips::AngleRelationGate() {
  double p0[2], p1[2], dA[2];

  //F5A vs F3A
  p0[0] = -3.3;
  p1[0] = 0.98;
  dA[0] = 15;

  //F7A vs F5A
  p0[1] = 0.14;
  p1[1] = 0.85;
  dA[1] = 15;
  
  if(fabs(F5A-p1[0]*F3A-p0[0])> dA[0] || fabs(F7A-p1[1]*F5A-p0[1])> dA[1]) {
    flagAngle = 0;
  }
}



void bigrips::offlinepid() {
  clearofflinepid();
  int flagtoft, flagtofq;
  TOFGate(flagtoft, flagtofq);
  flagTOFt = flagtoft;
  flagTOFq = flagtofq;

  //Here should be changed. To function!
  tof37 = BigRIPSPlastic_fTime[3] - BigRIPSPlastic_fTime[1];
  tof37 += tofoffset37  //
    +slew37[0]/sqrt(BigRIPSPlastic_fQLRaw[1])
    +slew37[1]/sqrt(BigRIPSPlastic_fQRRaw[1]) 
    -slew37[2]/sqrt(BigRIPSPlastic_fQLRaw[3]) 
    -slew37[3]/sqrt(BigRIPSPlastic_fQRRaw[3]);

  PositionCalc(3);
  PositionCalc(5);
  PositionCalc(7);
  PositionCalc(11);

  double a35, b35, c35, a57, b57, c57;
  //x(F5 or F7) = a*delta*delta + b*delta + c
  a35=xdd35;
  b35=xd35 + xxd35*F3X + xad35*F3A ;
  c35=xx35*F3X + xa35*F3A + xxx35*F3X*F3X + xxa35*F3X*F3A + xaa35*F3A*F3A
    + xxxx35*F3X*F3X*F3X + xxxa35*F3X*F3X*F3A + xxaa35*F3X*F3A*F3A
    + xaaa35*F3A*F3A*F3A + xaaaa35*F3A*F3A*F3A*F3A;

  a57=xdd57;
  b57=xd57 + xxd57*F5X + xad57*F5A ;
  c57=xx57*F5X + xa57*F5A + xxx57*F5X*F5X + xxa57*F5X*F5A + xaa57*F5A*F5A
    + xxxx57*F5X*F5X*F5X + xxxa57*F5X*F5X*F5A + xxaa57*F5X*F5A*F5A
    + xaaa57*F5A*F5A*F5A + xaaaa57*F5A*F5A*F5A*F5A;

  if(a35 == 0) {
    delta35 = (F5X-c35)/b35;
  } else {
    delta35 = (-b35 + sqrt(b35*b35 - 4*a35*(c35-F5X)))/2/a35;
  }
  if(a57 == 0) {
    delta57 = (F7X-c57)/b57;
  } else {
    delta57 = (-b57 - sqrt(b57*b57 - 4*a57*(c57-F7X)))/2/a57;
  }

  brho35 = BigRIPSRIPS_center_brho[0]*(1+delta35/100.);
  brho57 = BigRIPSRIPS_center_brho[1]*(1+delta57/100.);

  rbrho35 = brho35/brho57;
  rbrho57 = brho57/brho35;

  beta35 = 
    (clight*tof37*L1
     +L2*sqrt(L1*L1*(1-rbrho35*rbrho35)+rbrho35*rbrho35*(rbrho35*rbrho35-1)*L2*L2 
	      + rbrho35*rbrho35*clight*clight*tof37*tof37))
    /(clight*clight*tof37*tof37 +L2*L2*(rbrho35*rbrho35-1));

  beta57 = 
    (clight*tof37*L2
     +L1*sqrt(L2*L2*(1-rbrho57*rbrho57)+rbrho57*rbrho57*(rbrho57*rbrho57-1)*L2*L2 
	      + rbrho57*rbrho57*clight*clight*tof37*tof37))
    /(clight*clight*tof37*tof37 +L1*L1*(rbrho57*rbrho57-1));

  gamma35 = 1/sqrt(1-beta35*beta35);
  gamma57 = 1/sqrt(1-beta57*beta57);

  aoq37 = brho35*clight/beta35/gamma35/amu;

// These are identical. 
//  aoq35 = brho35*clight/beta35/gamma35/amu; 
//  aoq57 = brho57*clight/beta57/gamma57/amu; 

  tof711 = BigRIPSPlastic_fTime[6] - BigRIPSPlastic_fTime[3] + tofoffset711;

  //Length between F7-F11 plastic 
  // 47783-205-432 =47146
  beta711 =47146/tof711/clight;

  DeltaECalc();
  zedCalc(numOfZedPar);


  // for Y on F11_plastic
  //  if (zed>32.5 && F11PlaY>=30 && flagF11PlaY==1) flagF11PlaY = 0;

  // flag analysis
//  IsReaction();
//  deltaERelationGate();
//  AngleRelationGate();

  if(flagTSumX == 0 || // flagF11PlaY == 0 ||  // flagReaction is enough
     flagTOFt == 0 || flagTOFq== 0 ||flagReaction==0 ||flagdERelation==0 ||
     flagAngle==0) {
    flagall = 0;
  } 
  else if (flagTSumX == 2 && //flagF11PlaY == 1 && 
	   flagTOFt == 1 && flagTOFq == 1 && flagReaction == 1
	   &&flagdERelation==1 && flagAngle==1) {
    flagall = 2;
  }
  
  if (flagall == 1) {
    ZedMass();
  } else if (flagTSumX==2&&flagTOFt==1&&flagTOFq==1&&flagReaction==1
	     &&flagdERelation==1 && flagAngle==1) {
    ZedMass2();
  } else {
    Zed=0;
    Mass=0;
  }

  ribeam = new((*caribeam)[0]) RIBeam();
  ribeam->Setbeta35(beta35); 
  ribeam->Setbeta57(beta57); 
  ribeam->Setbeta711(beta711);
  ribeam->Setaoq37(aoq37); 
  ribeam->Setzed(zed); 
  ribeam->SetZed(Zed);
  ribeam->SetMass(Mass);
  ribeam->Setflagall(flagall); 
  ribeam->SetflagTSumX(flagTSumX); 
  //  ribeam->SetflagF11PlaY(flagF11PlaY); 
  ribeam->SetflagTOF(flagTOFt,flagTOFq); 
  ribeam->SetflagReaction(flagReaction);
  ribeam->SetflagdERelation(flagdERelation);
  ribeam->SetflagAngle(flagAngle);

  ribeamothers = new((*caribeamothers)[0]) RIBeamOthers(); 
  ribeamothers->SetTOF37(tof37);
  ribeamothers->SetTOF711(tof711);
  ribeamothers->SetF3PosAng(F3X,F3A,F3Y,F3B);
  ribeamothers->SetF5PosAng(F5X,F5A,F5Y,F5B);
  ribeamothers->SetF7PosAng(F7X,F7A,F7Y,F7B);
  ribeamothers->Setdelta35(delta35);
  ribeamothers->Setdelta57(delta57);
  ribeamothers->Setbrho35(brho35);
  ribeamothers->Setbrho57(brho57);
  ribeamothers->SetdeltaE(deltaE);

}

void bigrips::initofflinepid() {
  L1=23488.;    //length from F3 plastic to F5 degrader
  L2=23488.;    //length from F5 degrader to F7 plastic
  amu=931.49432;
  clight=299.792;
  
  initPositionCalc();
  initF3XAoQ();
  makeF3XAoQGate();
  readdEcoef();
  numOfZedPar=5;
  //numOfZedPar=2;
  string str;
  if(numOfZedPar==5) {
    str=dir+"parameters/zedcalib/zedcalib5prm.txt";
  } else if (numOfZedPar==2) {
    str=dir+"parameters/zedcalib/zedcalibCalc.txt";
    //zedcalibCalc.txt is caliculated parameter using energy loss by ATIMA
  }
    readzedcoef(str.c_str(),numOfZedPar); 
  
  readtof();

  // initialization by calculated values up to 1st order
  xx35= 0.926591;
  xa35= -0.004712;
  xd35= 31.669;

  xx57=1.080;
  xa57=0.0226346;
  xd57= -34.1741;

  xxx35  =0;
  xxa35  =0;
  xxd35  =0;
  xaa35  =0;
  xad35  =0;
  xdd35  =0;
  xxx57  =0;
  xxa57  =0;
  xxd57  =0;
  xaa57  =0;
  xad57  =0;
  xdd57  =0;
  xxxx35 =0;
  xxxx57 =0;
  xxxa35 =0;
  xxxa57 =0;
  xxaa35 =0;
  xxaa57 =0;
  xaaa35 =0;
  xaaa57 =0;
  xaaaa35=0;
  xaaaa57=0;
  
  xad57 = 0;
  xdd57 = 0;
  xaa57 = 0;
  xxa57 = 0;
  xxxx57 = 0;
  xxaa57 = 0;

  readoptics(); //replaced by values written in file

}

void bigrips::clearofflinepid(){
  tof37=-1000.;
  tof711=-1000.;
  beta35 =-1000.;
  beta57 =-1000.;
  beta711 =-1000.;
  delta35=-1000.;
  delta57=-1000.;
  brho35 =-1000.; 
  brho57 =-1000.; 
  aoq37  =-1000.; 
  zed    =-1000.; 
  Zed = 0;
  Mass = 0;
  flagall      = 1;
  flagTSumX    = 1;
  //  flagF11PlaY  = 1;
  flagTOFt   = 1;
  flagTOFq   = 1;
  flagReaction = 1;
  flagdERelation = 1;
  flagAngle = 1;
}

void bigrips::inittreeout(TTree* tree) {
  eventinfo = new TClonesArray("TArtEventInfo",kMaxEventInfo);
  ppac = new TClonesArray("TArtPPAC",kMaxBigRIPSPPAC);
  plastic = new TClonesArray("TArtPlastic",kMaxBigRIPSPlastic);
  ic = new TClonesArray("TArtIC",kMaxBigRIPSIC);
  focalplane = new TClonesArray("TArtFocalPlane",kMaxBigRIPSFocalPlane);
  tof = new TClonesArray("TArtTOF",kMaxBigRIPSTOF);
  rips = new TClonesArray("TArtRIPS",kMaxBigRIPSRIPS);
  beam = new TClonesArray("TArtBeam",kMaxBigRIPSBeam);
  caribeam = new TClonesArray("RIBeam",1);
  caribeamothers = new TClonesArray("RIBeamOthers",1);

  tree->Branch("EventInfo",&eventinfo);
  tree->Branch("BigRIPSPPAC",&ppac);
  tree->Branch("BigRIPSPlastic",&plastic);
  tree->Branch("BigRIPSIC",&ic);
  tree->Branch("BigRIPSFocalPlane",&focalplane);
  tree->Branch("BigRIPSTOF",&tof);
  tree->Branch("BigRIPSRIPS",&rips);
  tree->Branch("BigRIPSBeam",&beam);
  tree->Branch("RIBeam",&caribeam);
  tree->Branch("RIBeamOthers",&caribeamothers);
}


void bigrips::fillbigripsall() { // fill anaroot values
  eventinfo->Clear();
  ppac->Clear();
  plastic->Clear();
  ic->Clear();
  focalplane->Clear();
  tof->Clear();
  rips->Clear();
  beam->Clear();

  /*************** sync eventinfo **********************/
  
  for(int id=0; id<EventInfo_; id++){
    taeventinfo = new((*eventinfo)[id]) TArtEventInfo();
    taeventinfo->SetUniqueID(EventInfo_fUniqueID[id]);
    taeventinfo->SetBit(EventInfo_fBits[id]);
    taeventinfo->SetNameTitle(EventInfo_fName[id],EventInfo_fTitle[id]);
    taeventinfo->SetRunNumber(EventInfo_runnumber[id]);
    taeventinfo->SetEventNumber(EventInfo_eventnumber[id]);
    taeventinfo->SetSubsysName((char*)EventInfo_subsysname[id].Data());
    taeventinfo->SetTimeStamp(EventInfo_timestamp[id]);
    taeventinfo->SetTSCheck(EventInfo_comp_val[id]);
    taeventinfo->SetTriggerBit(EventInfo_fBit[id]);
  }

  /*************** sync ppac **********************/
  
  for(int id=0; id<BigRIPSPPAC_; id++){
    tappac = new((*ppac)[id]) TArtPPAC();
    tappac->SetUniqueID(BigRIPSPPAC_fUniqueID[id]);
    tappac->SetBit(BigRIPSPPAC_fBits[id]);
    tappac->SetID(BigRIPSPPAC_id[id]);
    tappac->SetFpl(BigRIPSPPAC_fpl[id]);
    tappac->SetDetectorName(BigRIPSPPAC_name[id]);    
    tappac->SetDataState(BigRIPSPPAC_fDataState[id]);
    tappac->SetXZPos(BigRIPSPPAC_xzpos[id]);
    tappac->SetYZPos(BigRIPSPPAC_yzpos[id]);
    tappac->SetTX1Raw(BigRIPSPPAC_fTX1Raw[id]);
    tappac->SetTX2Raw(BigRIPSPPAC_fTX2Raw[id]);
    tappac->SetTY1Raw(BigRIPSPPAC_fTY1Raw[id]);
    tappac->SetTY2Raw(BigRIPSPPAC_fTY2Raw[id]);
    tappac->SetTARaw(BigRIPSPPAC_fTARaw[id]);
    tappac->SetQX1Raw(BigRIPSPPAC_fQX1Raw[id]);
    tappac->SetQX2Raw(BigRIPSPPAC_fQX2Raw[id]);
    tappac->SetQY1Raw(BigRIPSPPAC_fQY1Raw[id]);
    tappac->SetQY2Raw(BigRIPSPPAC_fQY2Raw[id]);
    tappac->SetQARaw(BigRIPSPPAC_fQARaw[id]);
    tappac->SetTSumX(BigRIPSPPAC_fTSumX[id]);
    tappac->SetTSumY(BigRIPSPPAC_fTSumY[id]);
    tappac->SetTDiffX(BigRIPSPPAC_fTDiffX[id]);
    tappac->SetTDiffY(BigRIPSPPAC_fTDiffY[id]);
    tappac->SetX(BigRIPSPPAC_fX[id]);
    tappac->SetY(BigRIPSPPAC_fY[id]);
    tappac->SetFiredX(BigRIPSPPAC_fFiredX[id]);
    tappac->SetFiredY(BigRIPSPPAC_fFiredY[id]);
  }

  /*************** sync plastic **********************/
  
  for(int id=0; id<BigRIPSPlastic_; id++){
    taplastic = new((*plastic)[id]) TArtPlastic();
    taplastic->SetUniqueID(BigRIPSPlastic_fUniqueID[id]);
    taplastic->SetBit(BigRIPSPlastic_fBits[id]);
    taplastic->SetID(BigRIPSPlastic_id[id]);
    taplastic->SetFpl(BigRIPSPlastic_fpl[id]);
    taplastic->SetDetectorName(BigRIPSPlastic_name[id]);    
    taplastic->SetDataState(BigRIPSPlastic_fDataState[id]);
    taplastic->SetZposition(BigRIPSPlastic_zposition[id]);
    taplastic->SetZoffset(BigRIPSPlastic_zoffset[id]);
    taplastic->SetTLRaw(BigRIPSPlastic_fTLRaw[id]);
    taplastic->SetTRRaw(BigRIPSPlastic_fTRRaw[id]);
    taplastic->SetQLRaw(BigRIPSPlastic_fQLRaw[id]);
    taplastic->SetQRRaw(BigRIPSPlastic_fQRRaw[id]);
    taplastic->SetTime(BigRIPSPlastic_fTime[id]);
    taplastic->SetTimeL(BigRIPSPlastic_fTimeL[id]);
    taplastic->SetTimeR(BigRIPSPlastic_fTimeR[id]);
    taplastic->SetTimeLSlew(BigRIPSPlastic_fTimeLSlew[id]);
    taplastic->SetTimeRSlew(BigRIPSPlastic_fTimeRSlew[id]);
    taplastic->SetTimeSlew(BigRIPSPlastic_fTimeSlew[id]);
  }

  /*************** sync ic **********************/
  
  for(int id=0; id<BigRIPSIC_; id++){
    taic = new((*ic)[id]) TArtIC();
    taic->SetUniqueID(BigRIPSIC_fUniqueID[id]);
    taic->SetBit(BigRIPSIC_fBits[id]);
    taic->SetID(BigRIPSIC_id[id]);
    taic->SetFpl(BigRIPSIC_fpl[id]);
    taic->SetDetectorName(BigRIPSIC_name[id]);    
    taic->SetDataState(BigRIPSIC_fDataState[id]);
    for(int i=0; i<2; i++){
      taic->SetZCoef(i, BigRIPSIC_zcoef[id][i]);
    }
    taic->SetIonPair(BigRIPSIC_ionpair[id]);
    taic->SetNumHit(BigRIPSIC_nhitchannel[id]);
    for(int i=0; i<10; i++){
      taic->SetRawADC(i, BigRIPSIC_fADC[id][i]);
      taic->SetEnergy(i, BigRIPSIC_fEnergy[id][i]);
    }
    taic->SetRawADCSqSum(BigRIPSIC_fRawADCSqSum[id]);
    taic->SetRawADCAvSum(BigRIPSIC_fRawADCAvSum[id]);
    taic->SetEnergySqSum(BigRIPSIC_fCalMeVSqSum[id]);
    taic->SetEnergyAvSum(BigRIPSIC_fCalMeVAvSum[id]);
  }
  
  /*************** sync focalplane **********************/
  
  for(int id=0; id<BigRIPSFocalPlane_; id++){
    tafocalplane = new((*focalplane)[id]) TArtFocalPlane();
    tafocalplane->SetUniqueID(BigRIPSFocalPlane_fUniqueID[id]);
    tafocalplane->SetBit(BigRIPSFocalPlane_fBits[id]);
    tafocalplane->SetID(BigRIPSFocalPlane_id[id]);
    tafocalplane->SetFpl(BigRIPSFocalPlane_fpl[id]);
    tafocalplane->SetDetectorName(BigRIPSFocalPlane_name[id]);    
    tafocalplane->SetDataState(BigRIPSFocalPlane_fDataState[id]);
    tafocalplane->SetUniqueID(BigRIPSFocalPlane_fUniqueID[id]);
    tafocalplane->SetBit(BigRIPSFocalPlane_fBits[id]);
    tafocalplane->SetID(BigRIPSFocalPlane_id[id]);
    tafocalplane->SetFpl(BigRIPSFocalPlane_fpl[id]);
    tafocalplane->SetDetectorName(BigRIPSFocalPlane_name[id]);
    tafocalplane->SetDataState(BigRIPSFocalPlane_fDataState[id]);
    tafocalplane->SetOptVector(0, BigRIPSFocalPlane_X[id]);
    tafocalplane->SetOptVector(1, BigRIPSFocalPlane_A[id]);
    tafocalplane->SetOptVector(2, BigRIPSFocalPlane_Y[id]);
    tafocalplane->SetOptVector(3, BigRIPSFocalPlane_B[id]);
    tafocalplane->CopyPos();
    tafocalplane->SetNumFiredPPACX(BigRIPSFocalPlane_nfired_ppacx[id]);
    tafocalplane->SetNumFiredPPACY(BigRIPSFocalPlane_nfired_ppacy[id]);
    tafocalplane->SetZpos(BigRIPSFocalPlane_zpos[id]);
  }
  
  /*************** sync tof **********************/
  
  for(int id=0; id<BigRIPSTOF_; id++){
    tatof = new((*tof)[id]) TArtTOF();
    tatof->SetTOF(BigRIPSTOF_tof[id]);
    tatof->SetLength(BigRIPSTOF_length[id]);
    tatof->SetUpStreamLength(BigRIPSTOF_ulength[id]);
    tatof->SetDownStreamLength(BigRIPSTOF_dlength[id]);
//    tatof->SetUpstreamPlaName(BigRIPSTOF_upstream_plname[id]);
//    tatof->SetDownstreamPlaName(BigRIPSTOF_downstream_plname[id]);
    tatof->SetUpstreamPlaFpl(BigRIPSTOF_upstream_plfpl[id]);
    tatof->SetDownstreamPlaFpl(BigRIPSTOF_downstream_plfpl[id]);
    tatof->SetTimeOffset(BigRIPSTOF_time_offset[id]);
  }
  
  /*************** sync rips **********************/
  
  for(int id=0; id<BigRIPSRIPS_; id++){
    tarips = new((*rips)[id]) TArtRIPS();
    tarips->SetUpstreamFpl(BigRIPSRIPS_upstream_fpl[id]);
    tarips->SetDownstreamFpl(BigRIPSRIPS_downstream_fpl[id]);
    tarips->SetCenterBrho(BigRIPSRIPS_center_brho[id]);
    tarips->SetBrho(BigRIPSRIPS_brho[id]);
    tarips->SetLength(BigRIPSRIPS_length[id]);
    tarips->SetDelta(BigRIPSRIPS_delta[id]);
    tarips->SetAngle(BigRIPSRIPS_angle[id]);
    tarips->SetMatrix(BigRIPSRIPS_matrix[id]);
  }
  /*************** sync beam **********************/
  for(int id=0; id<BigRIPSBeam_; id++){
    //    tabeam = new(cabeam[id]) TArtBeam();
    tabeam = new((*beam)[id]) TArtBeam();
    //    tabeam = (TArtBeam *) ((*beam)[id]);
    tabeam->SetBrho(BigRIPSBeam_brho[id]);
    tabeam->SetAoQ(BigRIPSBeam_aoq[id]);
    tabeam->SetZet(BigRIPSBeam_zet[id]);
    tabeam->SetBeta(BigRIPSBeam_beta[id]);
    tabeam->SetNumRIPS(BigRIPSBeam_nrips[id]);
  }
}

