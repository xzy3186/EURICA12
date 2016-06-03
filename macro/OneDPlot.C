#include "TGraph.h"

#include <iostream>
#include <fstream>
#include <sstream>
TGraph* OneDPlot(const char* filename) {
  ifstream fin(filename);
  if (!fin) {
    cout << "file not found" << endl;
    exit(1);
  }
  vector<double> x, y;
  string strbuf;
  stringstream ss;
  double buf1,buf2;

  while (!fin.eof()) {
    strbuf.clear();
    getline(fin,strbuf); 
    ss.str(strbuf);
    if (strbuf.size()!=0) {
      ss >> buf1;
      ss >> buf2;
      x.push_back(buf1); y.push_back(buf2); 
    } 
  }

  Int_t vec_len = x.size();
  Double_t *xval = new Double_t[vec_len]; 
  Double_t *yval = new Double_t[vec_len]; 
  for (int i=0;i<vec_len;i++) {
    xval[i] = x[i]; yval[i] = y[i]; 
  }

  TGraph *graph1 = new TGraph(vec_len, xval, yval);
  return graph1;
}


TGraph* OneDPlot(const char* filename, int dataNum) {
  ifstream fin(filename);
  if (!fin) {
    cout << "file not found" << endl;
    exit(1);
  }
  vector<double> x, y;
  string strbuf;
  stringstream ss;
  double buf1,buf2;

  while (!fin.eof()) {
    strbuf.clear();ss.str("");ss.clear(stringstream::goodbit);
    getline(fin,strbuf); 
    ss.str(strbuf);
    if (strbuf.size()!=0) {
      ss >> buf1;
      for (int i=0;i<dataNum;i++) {
	if (ss.eof()) exit(1);
	ss >> buf2;
      }
      x.push_back(buf1); y.push_back(buf2); 
    } 
  }

  Int_t vec_len = x.size();
  Double_t *xval = new Double_t[vec_len]; 
  Double_t *yval = new Double_t[vec_len]; 
  for (int i=0;i<vec_len;i++) {
    xval[i] = x[i]; yval[i] = y[i]; 
  }

  TGraph *graph1 = new TGraph(vec_len, xval, yval);
  return graph1;
}
