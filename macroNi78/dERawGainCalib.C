#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "TGraph.h"

void dERawGainCalib(int standardrunnumber) {
  int run0 = standardrunnumber;
  ifstream fin("macroNi78/parameters/zedcalib/dERaw.txt");
  ofstream fout("macroNi78/parameters/zedcalib/dEGainCalib.txt");
  //find standardrunnumber
  string str, str1;
  int run;
  int datasize=0;
  int effdatasize;
  double p0, p1; // parameters of p1 for calibration of dE gain shift
  stringstream ss;
  getline(fin,str);
  ss << str;
  ss >> str1; // first column is runnumber
  while(!ss.eof()) {
    ss >> str1;
    datasize++;
  }
  cout << datasize << endl;
  fin.seekg(0,ios::beg);

  double *dErun0 = new double[datasize]; 
  double *dErun = new double[datasize]; 
  
  while (!fin.eof()&&run!=run0) {
    str.clear();ss.str("");ss.clear(stringstream::goodbit);
    getline(fin,str);
    ss << str;
    ss >> run;
  }

  for (int i=0;i<datasize;i++) {
    ss >> dErun0[i];
    cout << dErun0[i] << "  " ;
  }
  cout << endl;
  fin.seekg(0,ios::beg);
  run = 0;
  while (!fin.eof()) {
    str.clear();ss.str("");ss.clear(stringstream::goodbit);
    getline(fin,str);
    if (str.size() <1) continue;
    ss << str;
    ss >> run;
    cout << run << "  ";
    effdatasize=0;
    for (int i=0;i<datasize;i++) {
      ss >> dErun[i];
      if (dErun[i]>10&&dErun[i]<100000) {
	effdatasize++;
	cout << dErun[i] << "  " ;
      }
    }
    cout << endl;
    if (effdatasize >1) {
      TGraph *gr = new TGraph(effdatasize);
      int j=0;
      for (int i=0; i<datasize;i++) {
	if (dErun[i]>10&&dErun[i]<100000) {
	  gr->SetPoint(j,dErun[i],dErun0[i]);
	  cout << dErun[i] << "  " << dErun0[i] << endl;
	  j++;
	}
      }
      TFitResultPtr r = gr->Fit("pol1","S");
      fout << run << "  " << r->Value(0) << "  " << r->Value(1) << endl;
      delete gr;
    } else {
      fout << run << endl;
    }    
  }
  fout.close();
  fin.close();
}
