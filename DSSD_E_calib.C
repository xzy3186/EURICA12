#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<sstream>
#include<fstream>
#include"TFile.h"
#include"TTree.h"
#include"TROOT.h"
#include"TString.h"
#include"TRandom.h"
#include"TH1.h"
#include"TH2.h"
#include"TProfile.h"
#include"TCanvas.h"
#include<TSystem.h>
#include<TStyle.h>
#include<TCutG.h>
#include<vector>
//#include<TMinuit.h>
#include<map>

TCanvas *cav1 = new TCanvas ("cav1","cav1",0,0,800,600);
TCanvas *cav2 = new TCanvas ("cav2","cav2",0,600,800,600);
TChain *tree[8][100];
TProfile *DSSDGeProfile1[8][100];
TProfile *DSSDGeProfile2[8][100];
TCutG *DSSDGeCut1[8][100];
TCutG *DSSDGeCut2[8][100];
TF1 *DSSDGeFit1[8][100];
TF1 *DSSDGeFit2[8][100];
TH1F *DSSDRawH1[8][100];
TH2F *DSSDECalib = new TH2F("DSSDECalib","DSSDECalib", 1400, 0, 1400, 1400, 0, 1400);
TH2F *h1 = new TH2F("h1","h1", 1400, 0, 1400, 1400, 0, 1400);
TH2F *h2 = new TH2F("h2","h2", 1400, 0, 1400, 1400, 0, 1400);
TF1 *DSSDRawFitH1[8][100];
Double_t a0[8][100], b0[8][100], c0[8][100], d0[8][100], e0[8][100];
Double_t sigma1[8][100], sigma2[8][100];
vector<pair<Int_t, pair<Int_t, Int_t> > > *xVecPtr = new vector<pair<Int_t, pair<Int_t, Int_t> > > ();

void ResetCalibTable(){
   for(int i=0; i<8; i++){
      for(int j=0; j<100; j++){
         a0[i][j]=0;
         b0[i][j]=0;
      }
   }
}

void SaveCalibTable(){
   FILE *fp = fopen("DSSD_E_calib.input", "w");
   for(int i=0; i<8; i++){
      for(int j=0; j<100; j++){
         if(i>=4&&j<60&&j%2==1){
            continue;
         }
         if(b0[i][j]>0.1){
            fprintf(fp, "%d %d %.8lf %.8lf %.8lf %.8lf\n", i, j, b0[i][j], a0[i][j], sigma1[i][j], sigma2[i][j]);
         }else{
            fprintf(fp, "%d %d %.8lf %.8lf %.8lf %.8lf\n", i, j, 0, 0, 0, 0);
         }
      }
   }
   fclose(fp);
}

void ReadCalibTable(){
   ifstream in_calib;
   in_calib.open("DSSD_E_calib.input", ios::in);
   int x, y;
   double p0, p1;
   double s1, s2;
   for(x=0; x<8; x++){
      for(y=0; y<100; y++){
         a0[x][y]=0;
         b0[x][y]=0;
         sigma1[x][y]=0;
         sigma2[x][y]=0;
      }
   }
   while (in_calib.good()){
      in_calib >>x>>y>>p1>>p0>>s1>>s2;
      b0[x][y]=p1;
      a0[x][y]=p0;
      sigma1[x][y]=s1;
      sigma2[x][y]=s2;
   }
}

void ChainRootFiles_All(){
   char treename[128];
   for(int i=0; i<8; i++){
      for(int j=0; j<100; j++){
         sprintf(treename,"DSSD%dCH%02d",i,j);
         tree[i][j] = new TChain (treename);
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0052.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0053.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0057.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0058.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0059.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0060.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0061.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0062.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0063.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0064.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0065.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0066.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0077.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0078.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0080.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0091.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0092.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0093.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0094.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0095.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0096.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0097.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0098.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0099.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0100.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0101.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0102.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0103.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0104.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0105.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0106.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0107.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0108.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0109.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0200.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0201.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0204.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0205.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0206.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0207.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0208.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0209.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0210.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0211.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0212.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0213.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0214.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0215.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0217.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0218.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0219.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0220.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0221.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0222.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0223.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0224.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0225.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0226.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0227.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0228.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0229.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0230.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0231.root");
      }
   }
   ReadCalibTable();
}

void ChainRootFiles_Ni(){
   char treename[128];
   for(int i=0; i<8; i++){
      for(int j=0; j<100; j++){
         sprintf(treename,"DSSD%dCH%02d",i,j);
         tree[i][j] = new TChain (treename);
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0052.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0053.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0057.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0058.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0059.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0060.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0061.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0062.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0063.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0064.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0065.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0066.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0077.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0078.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0080.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0091.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0092.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0093.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0094.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0095.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0096.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0097.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0098.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0099.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0100.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0101.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0102.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0103.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0104.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0105.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0106.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0107.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0108.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0109.root");
      }
   }
   ReadCalibTable();
}

void ChainRootFiles_Cu(){
   char treename[128];
   for(int i=0; i<8; i++){
      for(int j=0; j<100; j++){
         sprintf(treename,"DSSD%dCH%02d",i,j);
         tree[i][j] = new TChain (treename);
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0200.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0201.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0204.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0205.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0206.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0207.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0208.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0209.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0210.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0211.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0212.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0213.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0214.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0215.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0217.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0218.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0219.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0220.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0221.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0222.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0223.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0224.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0225.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0226.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0227.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0228.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0229.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0230.root");
         tree[i][j]->Add("root/sistopper/calib/WASABI_Calib0231.root");
      }
   }
   ReadCalibTable();
}

void SetCut(char *filename, int X1, int Y1, int X2, int Y2) {
   FILE *fp = fopen(filename, "w");
   cout<<"X1 = "<<X1<<", Y1 = "<<Y1<<", X2 = "<<X2<<", Y2 = "<<Y2<<endl;
   fprintf(fp, "dssd_E\n");
   fprintf(fp, "gc_E\n");
   int n = 6;
   int x[6], y[6];
   x[0] = X1; y[0] = Y1;
   x[1] = X1; y[1] = Y1-50;
   x[2] = X2-50; y[2] = Y2;
   x[3] = X2; y[3] = Y2;
   x[4] = X2; y[4] = Y2+50;
   x[5] = X1+50; y[5] = Y1;
   fprintf(fp, "6\n");
   for (int i = 0; i < n; i++) {
      fprintf(fp, "%d %d\n", x[i], y[i]);
   }
   fclose(fp);
}

int LoadCut(char *filename, TCutG *c) {
   FILE *fp = fopen(filename, "r");
   if(fp == 0){
      cout<<"error loading cut"<<endl;
      return 0;
   }

   char vx[30], vy[30];
   int n;
   double x, y;

   fscanf(fp, "%s", vx);
   //cout << vx << endl;
   c->SetVarX(vx);
   fscanf(fp, "%s", vy);
   //cout << vy << endl;
   c->SetVarY(vy);
   fscanf(fp, "%d", &n);
   //cout << n << endl;
   c->Set(n);
   for (int i = 0; i < n; i++) {
      fscanf(fp, "%lf %lf", &x, &y);
      //cout << x << " " << y << endl;
      c->SetPoint(i, x, y);
   }

   fclose(fp);
   cout << filename << endl;
   return 1;
}

void SortXY(int &X1, int &Y1, int &X2, int &Y2){
   int X0, Y0;
   if(X1>X2){
      X0=X1;
      Y0=Y1;
      X1=X2;
      Y1=Y2;
      X2=X0;
      Y2=Y0;
   }
}

int DrawPlot(int i, int j){
   if(i>=0 && i<8 && j>=0 && j<100){
      TH2F *h0 = new TH2F("h0","E(DSSSD) vs. E(Ge)",1400,0,1400,1400,0,1400);
      cav1->cd();
      cav1->SetLogz(0);
      double counts = tree[i][j]->Draw("gc_E:dssd_E>>h0","","col");
      h0->GetXaxis()->SetTitle("E(DSSSD) (arbitrary unit)");
      h0->GetXaxis()->SetTitleSize(0.05);
      h0->GetXaxis()->CenterTitle(1);
      h0->GetYaxis()->SetTitle("E(Ge) (keV)");
      h0->GetYaxis()->SetTitleSize(0.05);
      h0->GetYaxis()->CenterTitle(1);
      h0->SetStats(0);
      cav1->SetGridx(0);
      cav1->SetGridy(0);
      cav1->Update();
      cout<<"This is DSSD #"<<i<<", strip #"<<j<<", counts ="<<counts<<endl;
      return 1;
   }
   cout<<"No DSSD #"<<i<<" CH #"<<j<<endl;
   return 0;
}

int DrawFit(int i, int j){
   if(i>=0 && i<8 && j>=0 && j<100){
      char linename1[80];
      char linename2[80];
      sprintf(linename1,"DSSD%dCH%02dLine1",i,j);
      sprintf(linename2,"DSSD%dCH%02dLine2",i,j);
      if(gROOT->FindObject(linename1)==0){
         DSSDGeFit1[i][j] = new TF1(linename1,"pol1",0,1000);
      }
      if(gROOT->FindObject(linename2)==0){
         DSSDGeFit2[i][j] = new TF1(linename2,"pol1",0,1000);
      }
      DSSDGeFit1[i][j]->SetParameter(0,1333-a0[i][j]);
      DSSDGeFit1[i][j]->SetParameter(1,-1*b0[i][j]);
      //DSSDGeFit1[i][j]->SetParameter(2,-1*c0[i][j]);
      //DSSDGeFit1[i][j]->SetParameter(3,-1*d0[i][j]);
      //DSSDGeFit1[i][j]->SetParameter(4,-1*e0[i][j]);
      DSSDGeFit2[i][j]->SetParameter(0,1173-a0[i][j]);
      DSSDGeFit2[i][j]->SetParameter(1,-1*b0[i][j]);
      //DSSDGeFit2[i][j]->SetParameter(2,-1*c0[i][j]);
      //DSSDGeFit2[i][j]->SetParameter(3,-1*d0[i][j]);
      //DSSDGeFit2[i][j]->SetParameter(4,-1*e0[i][j]);

      char cutfile1[80];
      char cutfile2[80];
      sprintf(cutfile1,"cuts/DSSD%dCH%02d1.CUT",i,j);
      sprintf(cutfile2,"cuts/DSSD%dCH%02d2.CUT",i,j);
      char cutname1[80];
      char cutname2[80];
      sprintf(cutname1,"DSSD%dCH%02dCut1",i,j);
      sprintf(cutname2,"DSSD%dCH%02dCut2",i,j);
      if(gROOT->FindObject(cutname1)==0){
         DSSDGeCut1[i][j] = new TCutG(cutname1,10);
      }
      if(gROOT->FindObject(cutname2)==0){
         DSSDGeCut2[i][j] = new TCutG(cutname2,10);
      }
      if(LoadCut(cutfile1,DSSDGeCut1[i][j])==0 || LoadCut(cutfile2,DSSDGeCut2[i][j])==0){
         cout<<"No cut is available, quit."<<endl;
         return 0;
      }

      cav1->cd();
      cav1->Clear();
      cav1->SetLogz(0);
      double counts = tree[i][j]->Draw("gc_E:dssd_E>>h1","","colz");
      cout<<"come here"<<endl;
      DSSDGeFit1[i][j]->Draw("same");
      DSSDGeFit2[i][j]->Draw("same");
      cav1->Update();
      cav2->cd();
      cav2->Clear();
      cav2->SetLogz(0);
      char vartoplot[1000];
      char vartocut[500];
      //sprintf(vartoplot,"dssd_E*%.8lf+%.8lf+gc_E>>h1(1400,0,1400)",a0[i][j],b0[i][j]);
      sprintf(vartoplot,"(%.16lf+dssd_E*%.16lf+dssd_E*dssd_E*%.16lf+dssd_E*dssd_E*dssd_E*%.16lf+dssd_E*dssd_E*dssd_E*dssd_E*%.16lf+gc_E):(dssd_E)>>h2",a0[i][j],b0[i][j],c0[i][j],d0[i][j],e0[i][j]);
      sprintf(vartocut,"DSSD%dCH%02dCut1 || DSSD%dCH%02dCut2",i,j,i,j);
      tree[i][j]->Draw(vartoplot,"gc_E<1170","colz");
      cout<<"This is DSSD #"<<i<<", strip #"<<j<<", counts ="<<counts<<endl;
      return 1;
   }
   cout<<"No DSSD #"<<i<<" CH #"<<j<<endl;
   return 0;
}

int MakeCutOnPlot(int i, int j){
   if(i>=0 && i<8 && j>=0 && j<100){
      int X1, X2, Y1, Y2;

      char cutfile1[80];
      char cutfile2[80];
      sprintf(cutfile1,"cuts/DSSD%dCH%02d1.CUT",i,j);
      sprintf(cutfile2,"cuts/DSSD%dCH%02d2.CUT",i,j);

      cav1->cd();
      cav1->Clear();
      cav1->SetLogz(0);
      h1->Reset();
      getData(xVecPtr, i, j, 0);
      h1->Draw("colz");
      int counts = tree[i][j]->GetEntries();
      cav1->Update();
      cout<<"This is DSSD #"<<i<<", strip #"<<j<<", counts ="<<counts<<endl;
      if(counts<100){
         cout<<"histograim is empty"<<endl;
         return 0;
      }
      cout<<"draw a line on the upper correlated curve"<<endl;
      TLine *line = NULL;
      line = (TLine*) cav1->WaitPrimitive("TLine");
      X1 = line->GetX1();
      Y1 = line->GetY1();
      X2 = line->GetX2();
      Y2 = line->GetY2();
      SortXY(X1,Y1,X2,Y2);
      SetCut(cutfile1,X1,Y1,X2,Y2);
      line->Delete();
      TLine *line = NULL;
      cout<<"draw a line on the lower correlated curve"<<endl;
      line = (TLine*) cav1->WaitPrimitive("TLine");
      X1 = line->GetX1();
      Y1 = line->GetY1();
      X2 = line->GetX2();
      Y2 = line->GetY2();
      SortXY(X1,Y1,X2,Y2);
      //cout<<"come here"<<endl;
      SetCut(cutfile2,X1,Y1,X2,Y2);
      line->Delete();
      return 1;
   }
   cout<<"No DSSD #"<<i<<" CH #"<<j<<endl;
   return 0;
}

void MakeCutOnPlotDSSD(int i){
   for(int j=0; j<100; j++){
      if(i>=4 && j<60 && j%2==1){
         continue;
      }
      MakeCutOnPlot(i,j);
   }
}

void MakeCutOnPlotALL(){
   for(int i=0; i<8; i++){
      MakeCutOnPlotDSSD(i);
   }
}

Double_t DSSDE(Double_t *dssd_ch, Double_t *p){
   if(dssd_ch>0){
      return p[0]+p[2]/dssd_ch[0]+p[1]*dssd_ch[0];
   }else{
      return 0;
   }
}


int FitOnPlot(int i, int j){
   Double_t a1, a2, b1, b2, c1, c2, d1, d2, e1, e2;
   if(i>=0 && i<8 && j>=0 && j<100){
      cout<<"This is DSSD #"<<i<<", strip #"<<j<<endl;
      getData(xVecPtr, i, j, 1);
      Int_t dssd_ch, dssd_E;
      vector<pair<Int_t, pair<Int_t, Int_t> > > xVec = *xVecPtr;           // xVecPtr is global
      int n = xVec.size();
      DSSDECalib->Reset();
      for(int index=0; index<n; index++){
         dssd_ch = xVec[index].first;
         dssd_E = xVec[index].second.first;
         DSSDECalib->Fill(dssd_ch,dssd_E);
      }
      //DSSDECalib->Draw("col");

      char profilename1[80];
      sprintf(profilename1,"DSSD%dCH%02d1",i,j);
      if(gROOT->FindObject(profilename1)==0){
         DSSDGeProfile1[i][j] = new TProfile (profilename1,profilename1,1400,0,1400,0,1400,"g");
      }
      DSSDECalib->ProfileX(profilename1);

      char linename1[80];
      sprintf(linename1,"DSSD%dCH%02dLine1",i,j);
      char linename2[80];
      sprintf(linename2,"DSSD%dCH%02dLine2",i,j);
      if(gROOT->FindObject(linename1)==0){
         DSSDGeFit1[i][j] = new TF1(linename1,"pol1",0,1000);
      }
      DSSDGeProfile1[i][j]->Fit(linename1);
      //if(gROOT->FindObject(linename2)==0){
      //   DSSDGeFit2[i][j] = new TF1(linename2,DSSDE,0,1000,3);
      //}
      //DSSDGeFit2[i][j]->SetParameter(0,DSSDGeFit1[i][j]->GetParameter(0));
      //DSSDGeFit2[i][j]->SetParameter(1,DSSDGeFit1[i][j]->GetParameter(1));
      //DSSDGeFit2[i][j]->SetParameter(2,0);
      //DSSDGeFit2[i][j]->SetParLimits(2,-500000,500000);
      //DSSDGeProfile1[i][j]->Fit(linename2);
      a1=DSSDGeFit1[i][j]->GetParameter(0);
      b1=DSSDGeFit1[i][j]->GetParameter(1);
      //c1=DSSDGeFit2[i][j]->GetParameter(2);
      //d1=DSSDGeFit1[i][j]->GetParameter(3);
      //e1=DSSDGeFit1[i][j]->GetParameter(4);
      a0[i][j] = a1;
      b0[i][j] = b1;
      //c0[i][j] = c1;
      //d0[i][j] = d1;
      //e0[i][j] = e1;
      FitOnLoop(i,j,a0[i][j],b0[i][j]);
      //cout<<"a1 = "<<a1<<", a2 = "<<a2<<", a = "<<a0[i][j]<<endl;
      //cout<<"b1 = "<<b1<<", b2 = "<<b2<<", b = "<<b0[i][j]<<endl;
      //cout<<"c1 = "<<c1<<", c2 = "<<c2<<", c = "<<c0[i][j]<<endl;
      DrawFit(i,j);
   }
   return 1;
}

int FitOnLoop(int i, int j, double &a, double &b){
   double a1, b1;
   double a2=a, b2=b;
   char dssdrawname[100];
   sprintf(dssdrawname,"DSSD%dCH%02dRawH1",i,j);

   char cutfile1[80];
   char cutfile2[80];
   sprintf(cutfile1,"cuts/DSSD%dCH%02d1.CUT",i,j);
   sprintf(cutfile2,"cuts/DSSD%dCH%02d2.CUT",i,j);
   char cutname1[80];
   char cutname2[80];
   sprintf(cutname1,"DSSD%dCH%02dCut1",i,j);
   sprintf(cutname2,"DSSD%dCH%02dCut2",i,j);
   if(gROOT->FindObject(cutname1)==0){
      DSSDGeCut1[i][j] = new TCutG(cutname1,10);
   }
   if(gROOT->FindObject(cutname2)==0){
      DSSDGeCut2[i][j] = new TCutG(cutname2,10);
   }

   if(LoadCut(cutfile1,DSSDGeCut1[i][j])==0 || LoadCut(cutfile2,DSSDGeCut2[i][j])==0){
      cout<<"No cut is available, quit."<<endl;
      return 0;
   }
   if(gROOT->FindObject(dssdrawname)==0){
      DSSDRawH1[i][j] = new TH1F (dssdrawname,dssdrawname,2000,0,2000);
   }

   TF1 *f = new TF1("f","gaus(0)+gaus(3)");
   TF1 *ll = new TF1("ll","pol1");
   TGraph *g = new TGraph(2);
   double sigma1_avr, sigma2_avr;
   int index = 0;
   a1=a2;
   b1=b2;

   Int_t dssd_ch, gc_E;
   vector<pair<Int_t, pair<Int_t, Int_t> > > xVec = *xVecPtr;           // xVecPtr is global
   int n = xVec.size();
   DSSDRawH1[i][j]->Reset();
   for(int index=0; index<n; index++){
      dssd_ch = xVec[index].first;
      gc_E = xVec[index].second.second;
      DSSDRawH1[i][j]->Fill(a1+b1*dssd_ch+gc_E);
   }

   DSSDRawH1[i][j]->Draw();
   f->SetParameter(0,100);
   f->SetParLimits(0,0,1e4);
   f->SetParameter(1,1173);
   f->SetParameter(2,20);
   f->SetParLimits(2,5,100);
   f->SetParameter(3,100);
   f->SetParLimits(3,0,1e4);
   f->SetParameter(4,1333);
   f->SetParameter(5,20);
   f->SetParLimits(5,5,100);
   DSSDRawH1[i][j]->Fit("f","Q");
   sigma1[i][j] = fabs(f->GetParameter(2))+fabs(f->GetParameter(5));
   sigma2[i][j] = fabs(f->GetParameter(1)-1173)+fabs(f->GetParameter(4)-1333);

   f->Delete();
   g->Delete();
   ll->Delete();
   cout<<"sigma1 = "<<sigma1[i][j]<<", sigma2 = "<<sigma2[i][j]<<endl;
   return 1;
}


//Int_t dssd_E_calibed(Int_t * xPtr, double par[]){
//   Int_t x = * xPtr;
//   double slope2 = par[0];
//   double slope = par[1];
//   double offset = par[2];
//   double f = 0;
//   if (x >= 0) {
//      f = (Int_t)(slope2*x*x+slope*x+offset);
//   }
//   return f;
//}
//
//void fcn(int &npar, double *deriv, double &f, double par[], int flag){
//   vector<pair<Int_t, Int_t> > xVec = *xVecPtr;           // xVecPtr is global
//   int n = xVec.size();
//   double Kai2=0;
//   for(int i=0; i<n; i++){
//      Int_t dssd_ch = xVec[i].first;
//      Int_t dssd_E_real = xVec[i].second;
//      Int_t dssd_E = dssd_E_calibed(&dssd_ch, par);
//      Kai2 = Kai2 + sqrt((dssd_E-dssd_E_real)*(dssd_E-dssd_E_real));
//   }
//   f = Kai2;
//   cout<<f<<endl;
//}

int getData(vector<pair<Int_t, pair<Int_t, Int_t> > > *xVecPtr, int i, int j, int flag){
   Long64_t entry, Nentry;
   Int_t dssd_E, gc_E, dssd_E_real, dssd_hit, mulhit;
   TBranch *b_dssd_E, *b_gc_E, *b_dssd_hit;
   Int_t num_event=0;

   char cutfile1[80];
   char cutfile2[80];
   sprintf(cutfile1,"cuts/DSSD%dCH%02d1.CUT",i,j);
   sprintf(cutfile2,"cuts/DSSD%dCH%02d2.CUT",i,j);
   char cutname1[80];
   char cutname2[80];
   sprintf(cutname1,"DSSD%dCH%02dCut1",i,j);
   sprintf(cutname2,"DSSD%dCH%02dCut2",i,j);
   if(gROOT->FindObject(cutname1)==0){
      DSSDGeCut1[i][j] = new TCutG(cutname1,10);
   }
   if(gROOT->FindObject(cutname2)==0){
      DSSDGeCut2[i][j] = new TCutG(cutname2,10);
   }
   if(LoadCut(cutfile1,DSSDGeCut1[i][j])==0 || LoadCut(cutfile2,DSSDGeCut2[i][j])==0){
      cout<<"No cut is available, quit."<<endl;
      return 0;
   }

   tree[i][j]->SetBranchAddress("dssd_E", &dssd_E, &b_dssd_E);
   tree[i][j]->SetBranchAddress("dssd_hit", &dssd_hit, &b_dssd_hit);
   tree[i][j]->SetBranchAddress("gc_E", &gc_E, &b_gc_E);
   tree[i][j]->SetBranchStatus("*",0);
   tree[i][j]->SetBranchStatus("dssd_E");
   tree[i][j]->SetBranchStatus("gc_E");
   tree[i][j]->SetBranchStatus("dssd_hit");

   Nentry = tree[i][j]->GetEntries();
   cout<<Nentry<<endl;
   xVecPtr->clear();
   for(entry = 0; entry < Nentry; entry++){
      tree[i][j]->GetEntry(entry);
      dssd_E_real = 0;
      if(flag==1){
         if(DSSDGeCut1[i][j]->IsInside(dssd_E, gc_E)){
            dssd_E_real = 1333 - gc_E;
         }else if(DSSDGeCut2[i][j]->IsInside(dssd_E, gc_E)){
            dssd_E_real = 1173 - gc_E;
         }
         if(dssd_E>0 && dssd_E_real>0){
            xVecPtr->push_back(make_pair(dssd_E, make_pair(dssd_E_real, gc_E) ) );
            num_event++;
         }
      }else if(flag==0){
         h1->Fill(dssd_E, gc_E);
      }
      //if(entry%1000==0){
      //   cout<<entry<<endl;
      //}
   }
   return num_event;
}

//int FitOnLoop(int i, int j, double &c, double &a, double &b){
//   getData(xVecPtr, i, j);
//   const int npar = 3;
//   TMinuit minuit(npar);
//   minuit.SetFCN(fcn);
//   double par[npar];               // the start values
//   double stepSize[npar];          // step sizes 
//   double minVal[npar];            // minimum bound on parameter 
//   double maxVal[npar];            // maximum bound on parameter
//   string parName[npar];
//   par[0] = c;            // a guess
//   par[1] = a;            // a guess
//   par[2] = b;            // a guess
//   stepSize[0] = fabs(0.001*c);       // take e.g. 0.1 of start value
//   stepSize[1] = fabs(0.001*a);       // take e.g. 0.1 of start value
//   stepSize[2] = fabs(0.01*b);       // take e.g. 0.1 of start value
//   minVal[0] = c-10*fabs(c);   // if min and max values = 0, parameter is unbounded.
//   minVal[1] = a-0.5*fabs(a);   // if min and max values = 0, parameter is unbounded.
//   minVal[2] = b-0.5*fabs(b);   // if min and max values = 0, parameter is unbounded.
//   maxVal[0] = c+10*fabs(c);
//   maxVal[1] = a+0.5*fabs(a);
//   maxVal[2] = b+0.5*fabs(b);
//   parName[0] = "slope2";
//   parName[1] = "slope";
//   parName[2] = "offset";
//   for (int i=0; i<npar; i++){
//      minuit.DefineParameter(i, parName[i].c_str(), 
//            par[i], stepSize[i], minVal[i], maxVal[i]);
//   }
//   //minuit.ExecuteCommand("SIMPLEX",0,0);
//   minuit.Migrad();       // Minuit's best minimization algorithm
//   double outpar[npar], err[npar];
//   for (int i=0; i<npar; i++){
//      minuit.GetParameter(i,outpar[i],err[i]);
//   }
//   par[0] = outpar[0];            // a guess
//   par[1] = a;            // a guess
//   par[2] = b;            // a guess
//   stepSize[0] = 0;       // take e.g. 0.1 of start value
//   stepSize[1] = fabs(0.0001*a);       // take e.g. 0.1 of start value
//   stepSize[2] = fabs(0.01*b);       // take e.g. 0.1 of start value
//   minVal[0] = outpar[0];   // if min and max values = 0, parameter is unbounded.
//   minVal[1] = a-fabs(a);   // if min and max values = 0, parameter is unbounded.
//   minVal[2] = b-fabs(b);   // if min and max values = 0, parameter is unbounded.
//   maxVal[0] = outpar[0];
//   maxVal[1] = a+fabs(a);
//   maxVal[2] = b+fabs(b);
//   minuit.Migrad();       // Minuit's best minimization algorithm
//   for (int i=0; i<npar; i++){
//      minuit.GetParameter(i,outpar[i],err[i]);
//   }
//   c = outpar[0];
//   a = outpar[1];
//   b = outpar[2];
//   sigma1[i][j] = err[1];
//   sigma2[i][j] = err[2];
//}

//int FitOnLoop(int i, int j, double &a, double &b){
//   double a1, b1;
//   double a_array[200], sigma_array[200], b_array[200];
//   double a2=a, b2=b;
//   char dssdrawname[100];
//   char dssdrawfitname[100];
//   sprintf(dssdrawname,"DSSD%dCH%02dRawH1",i,j);
//   sprintf(dssdrawfitname,"DSSD%dCH%02dRawFitH1",i,j);
//
//   char cutfile1[80];
//   char cutfile2[80];
//   sprintf(cutfile1,"cuts/DSSD%dCH%02d1.CUT",i,j);
//   sprintf(cutfile2,"cuts/DSSD%dCH%02d2.CUT",i,j);
//   char cutname1[80];
//   char cutname2[80];
//   sprintf(cutname1,"DSSD%dCH%02dCut1",i,j);
//   sprintf(cutname2,"DSSD%dCH%02dCut2",i,j);
//   if(gROOT->FindObject(cutname1)==0){
//      DSSDGeCut1[i][j] = new TCutG(cutname1,10);
//   }
//   if(gROOT->FindObject(cutname2)==0){
//      DSSDGeCut2[i][j] = new TCutG(cutname2,10);
//   }
//
//   char cond[100];
//   sprintf(cond,"DSSD%dCH%02dCut1 || DSSD%dCH%02dCut2",i,j,i,j);
//   if(LoadCut(cutfile1,DSSDGeCut1[i][j])==0 || LoadCut(cutfile2,DSSDGeCut2[i][j])==0){
//      cout<<"No cut is available, quit."<<endl;
//      return 0;
//   }
//   if(gROOT->FindObject(dssdrawname)==0){
//      DSSDRawH1[i][j] = new TH1F (dssdrawname,dssdrawname,2000,0,2000);
//   }
//
//   TF1 *f = new TF1("f","gaus(0)+gaus(3)");
//   TF1 *ll = new TF1("ll","pol1");
//   TGraph *g = new TGraph(2);
//   double sigma1_avr, sigma2_avr;
//   int index = 0;
//   for(double fact1=0.90; fact1<=1.10; fact1=fact1+0.002){
//      //cout<<"fact1="<<fact1<<", fact2="<<fact2<<endl;
//      a1=a2*fact1;
//      //b1=b2*fact2;
//      b1=b2;
//      char vartoplot[100];
//      sprintf(vartoplot,"dssd_E*%.8lf+%.8lf+gc_E",a1,b1);
//      tree[i][j]->Project(dssdrawname,vartoplot,cond);
//      DSSDRawH1[i][j]->Draw();
//      f->SetParameter(0,100);
//      f->SetParLimits(0,0,1e4);
//      f->SetParameter(1,1173);
//      f->SetParameter(2,20);
//      f->SetParLimits(2,5,100);
//      f->SetParameter(3,100);
//      f->SetParLimits(3,0,1e4);
//      f->SetParameter(4,1333);
//      f->SetParameter(5,20);
//      f->SetParLimits(5,5,100);
//      DSSDRawH1[i][j]->Fit("f","Q");
//      //sigma = fabs(f->GetParameter(1)-1173)+fabs(f->GetParameter(4)-1333);
//      sigma1[i][j] = fabs(f->GetParameter(2))+fabs(f->GetParameter(5));
//      //cout<<"a="<<a1<<", b="<<b1<<",sigma = "<<sigma<<endl;
//      a_array[index]=a1;
//      sigma_array[index]=sigma1[i][j];
//      index++;
//   }
//   double sigma_min=100;
//   double sigma_avr_min=200;
//   for(int ii=1; ii<index-1; ii++){
//      sigma1[i][j] = sigma_array[ii];
//      sigma1_avr = sigma_array[ii-1]+sigma_array[ii]+sigma_array[ii+1];
//      //cout<<"sigma_avr = "<<sigma1_avr<<", sigma_avr_min = "<<sigma_avr_min<<endl;
//      cout<<"a = "<<a_array[ii]<<", sigma = "<<sigma1[i][j]<<", sigma_avr = "<<sigma1_avr<<endl;
//      if(sigma1_avr + sigma1[i][j] < sigma_avr_min + sigma_min){
//         sigma_min = sigma1[i][j];
//         sigma_avr_min = sigma1_avr;
//         a = a_array[ii];
//      }
//   }
//   sigma1[i][j] = sigma_min;
//
//   int index = 0;
//   for(double fact2=0.60; fact2<=1.40; fact2=fact2+0.01){
//      a1=a;
//      b1=b2*fact2;
//      char vartoplot[100];
//      sprintf(vartoplot,"dssd_E*%.8lf+%.8lf+gc_E",a1,b1);
//      tree[i][j]->Project(dssdrawname,vartoplot,cond);
//      DSSDRawH1[i][j]->Draw();
//      f->SetParameter(0,100);
//      f->SetParLimits(0,0,1e4);
//      f->SetParameter(1,1173);
//      f->SetParameter(2,20);
//      f->SetParLimits(2,5,100);
//      f->SetParameter(3,100);
//      f->SetParLimits(3,0,1e4);
//      f->SetParameter(4,1333);
//      f->SetParameter(5,20);
//      f->SetParLimits(5,5,100);
//      DSSDRawH1[i][j]->Fit("f","Q");
//      sigma2[i][j] = fabs(f->GetParameter(1)-1173)+fabs(f->GetParameter(4)-1333);
//      cout<<"a = "<<a1<<", b = "<<b1<<", sigma = "<<sigma2[i][j]<<endl;
//      sigma_array[index]=sigma2[i][j];
//      b_array[index]=b1;
//      index++;
//      if(sigma2[i][j]<sigma_min){
//         sigma_min=sigma2[i][j];
//         b=b1;
//      }
//   }
//   double sigma_min=100;
//   double sigma_avr_min=200;
//   for(int ii=1; ii<index-1; ii++){
//      sigma2[i][j] = sigma_array[ii];
//      sigma2_avr = sigma_array[ii-1]+sigma_array[ii]+sigma_array[ii+1];
//      if(sigma2_avr + sigma2[i][j] < sigma_avr_min + sigma_min){
//         sigma_min = sigma2[i][j];
//         sigma_avr_min = sigma2_avr;
//         b = b_array[ii];
//      }
//   }
//   sigma2[i][j] = sigma_min;
//
//   f->Delete();
//   g->Delete();
//   ll->Delete();
//   cout<<"sigma1 = "<<sigma1[i][j]<<", sigma2 = "<<sigma2[i][j]<<endl;
//   return 1;
//}

void FitOnPlotDSSD(int i){
   //ChainRootFiles_All();
   for(int j=0; j<100; j++){
      if(i>=4 && j<60 && j%2==1){
         a0[i][j]=a0[i][j-1];
         b0[i][j]=b0[i][j-1];
         continue;
      }
      FitOnPlot(i, j);
   }
   SaveCalibTable();
}

void FitOnPlotAll(){
   ChainRootFiles_All();
   ResetCalibTable();
   for(int i=0; i<8; i++){
      FitOnPlotDSSD(i);
   }
   SaveCalibTable();
}
