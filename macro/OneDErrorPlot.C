TGraphErrors* OneDErrorPlot(const char* filename) {
  ifstream fin(filename);
  if (!fin) {
    cout << "file not found" << endl;
    return;
  }
  vector<double> x, y, yerr;
  string strbuf;
  stringstream ss;
  double buf1,buf2,buf3;

  while (!fin.eof()) {
    strbuf.clear();
    getline(fin,strbuf); 
    ss.str(strbuf);
    if (strbuf.size()!=0) {
      ss >> buf1;
      ss >> buf2 >> buf3;
      x.push_back(buf1); y.push_back(buf2); yerr.push_back(buf3); 
    } 
  }

  Int_t vec_len = x.size();
  Double_t *xval = new Double_t[vec_len]; 
  Double_t *yval = new Double_t[vec_len]; 
  Double_t *yerrval = new Double_t[vec_len];
  for (int i=0;i<vec_len;i++) {
    xval[i] = x[i]; yval[i] = y[i]; yerrval[i] = yerr[i];
  }

  TGraphErrors *graph1 = new TGraphErrors(vec_len, xval, yval,0,yerrval);
  //, yerrval, yerrval);
  return graph1;
}


TGraphErrors* OneDErrorPlot(const char* filename, int dataNum) {
  ifstream fin(filename);
  if (!fin) {
    cout << "file not found" << endl;
    return;
  }
  vector<double> x, y, yerr;
  string strbuf;
  stringstream ss;
  double buf1,buf2,buf3;

  while (!fin.eof()) {
    strbuf.clear();
    getline(fin,strbuf); 
    ss.str(strbuf);
    if (strbuf.size()!=0) {
      ss >> buf1;
      for (int i=0;i<dataNum;i++) {
	if (ss.eof()) return;
	ss >> buf2 >> buf3;
      }
      x.push_back(buf1); y.push_back(buf2); yerr.push_back(buf3); 
    } 
  }

  Int_t vec_len = x.size();
  Double_t *xval = new Double_t[vec_len]; 
  Double_t *yval = new Double_t[vec_len]; 
  Double_t *yerrval = new Double_t[vec_len];
  for (int i=0;i<vec_len;i++) {
    xval[i] = x[i]; yval[i] = y[i]; yerrval[i] = yerr[i];
  }

  TGraphErrors *graph1 = new TGraphErrors(vec_len, xval, yval,0,yerrval);
  return graph1;
}
