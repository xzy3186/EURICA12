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

Double_t n_exphl[1][100];//exp half-life
Double_t n_exphlL[1][100];
Double_t n_exphlR[1][100];
Double_t n_frdmhl[1][100];//frdm+qrpa
Double_t n_ktuyhl[1][100];//ktuy+gt
Double_t n_borzhl[1][100];//borzov
Double_t n_shellhl[1][100];//borzov
Double_t n_exppn[1][100];//exp half-life
Double_t n_exppnL[1][100];
Double_t n_exppnR[1][100];
Double_t n_expqbetan[1][100];//exp half-life
Double_t n_expqbetanL[1][100];
Double_t n_expqbetanR[1][100];
Double_t n_frdmpn[1][100];//frdm+qrpa
Double_t n_ktuypn[1][100];//ktuy+gt
Double_t n_borzpn[1][100];//borzov
Double_t n_shellpn[1][100];//frdm+qrpa
Double_t n_protonnumexp[1][100];
Double_t n_protonnewnumexp[1][100];
Double_t n_protonerror[1][100];
Double_t n_dimiso[1];//number of isotopes per Z

void read_data(){
   ifstream in_data;
   Int_t Z, N;

   Double_t exphl;
   Double_t exphlL;
   Double_t exphlR;
   Double_t frdmhl;
   Double_t ktuyhl;
   Double_t borzhl;
   Double_t shellhl;

   Double_t exppn;
   Double_t exppnL;
   Double_t exppnR;
   Double_t expqbetan;
   Double_t expqbetanLR;
   Double_t frdmpn;
   Double_t ktuypn;
   Double_t borzpn;
   Double_t shellpn;

   for(int i=0; i<1; i++){
      n_dimiso[i]=0;
      for(int j=0; j<100; j++){
         n_exphl[i][j]=0;
         n_exphlL[i][j]=0;
         n_exphlR[i][j]=0;
         n_frdmhl[i][j]=0;
         n_ktuyhl[i][j]=0;
         n_borzhl[i][j]=0;
         n_shellhl[i][j]=0;
         n_exppn[i][j]=0;
         n_exppnL[i][j]=0;
         n_exppnR[i][j]=0;
         n_expqbetan[i][j]=0;
         n_expqbetanL[i][j]=0;
         n_expqbetanR[i][j]=0;
         n_frdmpn[i][j]=0;
         n_ktuypn[i][j]=0;
         n_borzpn[i][j]=0;
         n_shellpn[i][j]=0;
         n_protonnumexp[i][j]=0;
         n_protonnewnumexp[i][j]=0;
         n_protonerror[i][j]=0;
      }
   }
   in_data.open("macros/n50sys.input", ios::in);
   int temp=0;
   while (in_data.good()){
      in_data >>Z>>N>>exphl>>exphlL>>exphlR>>frdmhl>>ktuyhl>>borzhl>>shellhl>>exppn>>exppnL>>exppnR>>frdmpn>>ktuypn>>borzpn>>shellpn>>expqbetan>>expqbetanLR;
      //explaw = Calhalflife(Z,N);
      int index=N-50;
      if(index<5&&index>=0){
         n_protonnumexp[index][n_dimiso[index]]=Z;
         n_protonnewnumexp[index][n_dimiso[index]]=Z+0.13;
         n_exphl[index][n_dimiso[index]]=exphl;
         n_exphlL[index][n_dimiso[index]]=exphlL;
         n_exphlR[index][n_dimiso[index]]=exphlR;
         n_frdmhl[index][n_dimiso[index]]=frdmhl;
         n_ktuyhl[index][n_dimiso[index]]=ktuyhl;
         n_borzhl[index][n_dimiso[index]]=borzhl;
         n_shellhl[index][n_dimiso[index]]=shellhl;
         n_exppn[index][n_dimiso[index]]=exppn;
         n_exppnL[index][n_dimiso[index]]=exppnL;
         n_exppnR[index][n_dimiso[index]]=exppnR;
         n_expqbetan[index][n_dimiso[index]]=expqbetan;
         n_expqbetanL[index][n_dimiso[index]]=expqbetanLR;
         n_expqbetanR[index][n_dimiso[index]]=expqbetanLR;
         n_frdmpn[index][n_dimiso[index]]=frdmpn;
         n_ktuypn[index][n_dimiso[index]]=ktuypn;
         n_borzpn[index][n_dimiso[index]]=borzpn;
         n_shellpn[index][n_dimiso[index]]=shellpn;
         n_dimiso[index]++;
      }
      temp++;
   }
   in_data.close();
}

void set_contentZ(int Z, TString &content1, TString &content2){
   switch(Z){
      case 25:
         content1="_{25}Mn";
         content2="25Mn";
         break;
      case 26:
         content1="_{26}Fe";
         content2="26Fe";
         break;
      case 27:
         content1="_{27}Co";
         content2="27Co";
         break;
      case 28:
         content1="_{28}Ni";
         content2="28Ni";
         break;
      case 29:
         content1="_{29}Cu";
         content2="29Cu";
         break;
      case 30:
         content1="_{30}Zn";
         content2="30Zn";
         break;
      case 31:
         content1="_{31}Ga";
         content2="31Ga";
         break;
      case 32:
         content1="_{32}Ge";
         content2="32Ge";
         break;
      case 33:
         content1="_{33}As";
         content2="33As";
         break;
      case 34:
         content1="_{34}Se";
         content2="34Se";
         break;
   }
}

void set_contentN(int N, TString &content1, TString &content2){
   switch(N){
      case 44:
         content1="N=44";
         content2=content1;
         break;
      case 45:
         content1="N=45";
         content2=content1;
         break;
      case 46:
         content1="N=46";
         content2=content1;
         break;
      case 47:
         content1="N=47";
         content2=content1;
         break;
      case 48:
         content1="N=48";
         content2=content1;
         break;
      case 49:
         content1="N=49";
         content2=content1;
         break;
      case 50:
         content1="N=50";
         content2=content1;
         break;
      case 51:
         content1="N=51";
         content2=content1;
         break;
      case 52:
         content1="N=52";
         content2=content1;
         break;
      case 53:
         content1="N=53";
         content2=content1;
         break;
      case 54:
         content1="N=54";
         content2=content1;
         break;
      case 55:
         content1="N=55";
         content2=content1;
         break;
      case 56:
         content1="N=56";
         content2=content1;
         break;
   }
}

void find_boundryN_nhl(int N, Double_t &nmin, Double_t &nmax, double &hlmin, double &hlmax){
   int index=N-50;
   nmin = n_protonnumexp[index][0]-0.5;
   nmax = n_protonnumexp[index][n_dimiso[index]-1]+0.5;
   double tempmin=1000;
   double tempmax=0;
   for(int i=0; i<n_dimiso[index]; i++){
      if(n_exphl[index][i]>tempmax){
         tempmax=n_exphl[index][i];
      }
      if(n_frdmhl[index][i]>tempmax){
         tempmax=n_frdmhl[index][i];
      }
      if(n_ktuyhl[index][i]>tempmax){
         tempmax=n_ktuyhl[index][i];
      }
      if(n_borzhl[index][i]>tempmax){
         tempmax=n_borzhl[index][i];
      }
      if(n_shellhl[index][i]>tempmax){
         tempmax=n_shellhl[index][i];
      }
      if(n_exphl[index][i]<tempmin && n_exphl[index][i]>0){
         tempmin=n_exphl[index][i];
      }
      if(n_frdmhl[index][i]<tempmin && n_frdmhl[index][i]>0){
         tempmin=n_frdmhl[index][i];
      }
      if(n_ktuyhl[index][i]<tempmin && n_ktuyhl[index][i]>0){
         tempmin=n_ktuyhl[index][i];
      }
      if(n_borzhl[index][i]<tempmin && n_borzhl[index][i]>0){
         tempmin=n_borzhl[index][i];
      }
      if(n_shellhl[index][i]<tempmin && n_shellhl[index][i]>0){
         tempmin=n_shellhl[index][i];
      }
   }
   hlmin=tempmin/2.0;
   hlmax=tempmax*2;
}

void find_boundryN_npn(int N, Double_t &nmin, Double_t &nmax, double &pnmin, double &pnmax){
   int index=N-50;
   nmin = n_protonnumexp[index][0]-0.5;
   nmax = n_protonnumexp[index][n_dimiso[index]-1]+0.5;
   double tempmin=1000;
   double tempmax=0;
   for(int i=0; i<n_dimiso[index]; i++){
      if(n_exppn[index][i]>tempmax){
         tempmax=n_exppn[index][i];
      }
      if(n_frdmpn[index][i]>tempmax){
         tempmax=n_frdmpn[index][i];
      }
      if(n_ktuypn[index][i]>tempmax){
         tempmax=n_ktuypn[index][i];
      }
      if(n_borzpn[index][i]>tempmax){
         tempmax=n_borzpn[index][i];
      }
      if(n_shellpn[index][i]>tempmax){
         tempmax=n_shellpn[index][i];
      }
      if(n_exppn[index][i]<tempmin && n_exppn[index][i]>0){
         tempmin=n_exppn[index][i];
      }
      if(n_frdmpn[index][i]<tempmin && n_frdmpn[index][i]>0){
         tempmin=n_frdmpn[index][i];
      }
      if(n_ktuypn[index][i]<tempmin && n_ktuypn[index][i]>0){
         tempmin=n_ktuypn[index][i];
      }
      if(n_borzpn[index][i]<tempmin && n_borzpn[index][i]>0){
         tempmin=n_borzpn[index][i];
      }
      if(n_shellpn[index][i]<tempmin && n_shellpn[index][i]>0){
         tempmin=n_shellpn[index][i];
      }
   }
   pnmin=tempmin/2.0;
   pnmax=tempmax*1.2;
}

void find_boundryN_nqbetan(int N, Double_t &nmin, Double_t &nmax, double &qbetanmin, double &qbetanmax){
   int index=N-50;
   nmin = n_protonnumexp[index][0]-0.5;
   nmax = n_protonnumexp[index][n_dimiso[index]-1]+0.5;
   double tempmin=1000;
   double tempmax=0;
   for(int i=0; i<n_dimiso[index]; i++){
      if(n_expqbetan[index][i]>tempmax){
         tempmax=n_expqbetan[index][i];
      }
      if(n_expqbetan[index][i]<tempmin && n_expqbetan[index][i]>0){
         tempmin=n_expqbetan[index][i];
      }
   }
   qbetanmin=tempmin/2.0;
   qbetanmax=tempmax*1.2;
}

void plot_sysn50(){

   TFile *RootFile = new TFile("root/root_histogram/n50sys.root","RECREATE");
   TGraphAsymmErrors *n_sys_exphl[1]; //array for different isotopes
   TGraph *n_sys_frdmhl[1]; //array for different isotopes
   TGraph *n_sys_ktuyhl[1]; //array for different isotopes
   TGraph *n_sys_borzhl[1]; //array for different isotopes
   TGraph *n_sys_shellhl[1]; //array for different isotopes
   TGraphAsymmErrors *n_sys_exppn[1]; //array for different isotopes
   TGraphAsymmErrors *n_sys_expqbetan[1]; //array for different isotopes
   TGraphAsymmErrors *n_sys_expqbetan_real[1]; //array for different isotopes
   TGraph *n_sys_frdmpn[1]; //array for different isotopes
   TGraph *n_sys_ktuypn[1]; //array for different isotopes
   TGraph *n_sys_borzpn[1]; //array for different isotopes
   TGraph *n_sys_shellpn[1]; //array for different isotopes

   TLegend *n_leghl[1];
   TLegend *n_legpn[1];

   TCanvas *c01 = new TCanvas ("c01","c01",0,0,800,600);

   double nmin, nmax;
   double pnmin, pnmax;
   double hlmin, hlmax;
   double qbetanmin, qbetanmax;
   read_data();
   int i=0;
   /***************** half-lives as a function of Z *******************/
   c01->cd();
   c01->cd()->SetLogy(1);
   c01->cd()->SetGridx(0);
   c01->cd()->SetGridy(0);
   c01->cd()->SetTopMargin(0.05);
   c01->cd()->SetBottomMargin(0.15);
   c01->cd()->SetLeftMargin(0.15);
   c01->cd()->SetRightMargin(0.1);
   TString content1, content2;
   set_contentZ(i+27, content1, content2);
   n_sys_exphl[i] = new TGraphAsymmErrors(n_dimiso[i],n_protonnumexp[i],n_exphl[i],n_protonerror[i],n_protonerror[i],n_exphlL[i],n_exphlR[i]);
   n_sys_frdmhl[i] = new TGraph(n_dimiso[i],n_protonnumexp[i],n_frdmhl[i]);
   n_sys_frdmhl[i]->SetLineColor(2);
   n_sys_ktuyhl[i] = new TGraph(n_dimiso[i],n_protonnumexp[i],n_ktuyhl[i]);
   n_sys_ktuyhl[i]->SetLineColor(4);
   n_sys_borzhl[i] = new TGraph(n_dimiso[i]-3,&n_protonnumexp[i][1],&n_borzhl[i][1]);
   n_sys_borzhl[i]->SetLineColor(6);
   n_sys_shellhl[i] = new TGraph(n_dimiso[i],n_protonnumexp[i],n_shellhl[i]);
   n_sys_shellhl[i]->SetLineColor(8);
   TLatex text;
   text.SetTextAlign(12);
   text.SetTextSize(0.1);
   text.SetNDC(kTRUE);
   find_boundryN_nhl(i+50,nmin,nmax,hlmin,hlmax);
   //cout<<i<<", "<<nmin<<endl;
   n_sys_frdmhl[i]->GetXaxis()->SetLimits(nmin,nmax);
   n_sys_frdmhl[i]->GetYaxis()->SetRangeUser(hlmin,hlmax);
   n_sys_frdmhl[i]->SetTitle("");
   n_sys_frdmhl[i]->GetXaxis()->SetTitle("Proton number");
   n_sys_frdmhl[i]->GetXaxis()->SetTitleOffset(0.8);
   n_sys_frdmhl[i]->GetXaxis()->CenterTitle(1);
   n_sys_frdmhl[i]->GetXaxis()->SetTitleSize(0.08);
   n_sys_frdmhl[i]->GetXaxis()->SetLabelSize(0.08);
   n_sys_frdmhl[i]->GetXaxis()->SetNdivisions((nmax-nmin+1)/2+1);
   n_sys_frdmhl[i]->GetYaxis()->SetNdivisions(5);
   n_sys_frdmhl[i]->GetYaxis()->SetTitle("Half-life (ms)");
   n_sys_frdmhl[i]->GetYaxis()->CenterTitle(1);
   n_sys_frdmhl[i]->GetYaxis()->SetTitleOffset(0.8);
   n_sys_frdmhl[i]->GetYaxis()->SetTitleSize(0.08);
   n_sys_frdmhl[i]->GetYaxis()->SetLabelSize(0.08);
   n_sys_frdmhl[i]->SetLineWidth(2);
   n_sys_ktuyhl[i]->SetLineWidth(2);
   n_sys_borzhl[i]->SetLineWidth(2);
   n_sys_shellhl[i]->SetLineWidth(2);
   n_sys_frdmhl[i]->Draw("AL");
   n_sys_ktuyhl[i]->Draw("L");
   n_sys_borzhl[i]->Draw("L");
   n_sys_shellhl[i]->Draw("L");
   n_sys_exphl[i]->Draw("P");
   //text.DrawLatex(.3,.8,content1);
   n_sys_exphl[i]->SetMarkerStyle(21);
   n_sys_exphl[i]->SetMarkerSize(2);

   c01->cd();
   n_leghl[i] = new TLegend(0.2,0.55,0.55,0.95,"");
   n_leghl[i]->AddEntry(n_sys_exphl[i],"Experiment","P");
   n_leghl[i]->AddEntry(n_sys_frdmhl[i],"FRDM+QRPA","L");
   n_leghl[i]->AddEntry(n_sys_ktuyhl[i],"KTUY+GT2","L");
   n_leghl[i]->AddEntry(n_sys_borzhl[i],"DF+CQRPA","L");
   n_leghl[i]->AddEntry(n_sys_shellhl[i],"Shell Model","L");
   n_leghl[i]->SetBorderSize(0);
   n_leghl[i]->SetFillColor(0);
   n_leghl[i]->SetFillStyle(0);
   n_leghl[i]->Draw();
   cout<<"c01 finished"<<endl;

   /***************** Pn as a function of Z *******************/
   TCanvas *c02 = new TCanvas ("c02","c02",0,0,800,600);
   TPad *pad = new TPad("pad","",0,0,1,1);
   pad->SetGrid();
   pad->Draw();
   TPad *overlay = new TPad("overlay","",0,0,1,1);
   overlay->Draw();
   overlay->SetFillStyle(4000);
   overlay->SetFillColor(0);

   pad->cd();
   pad->cd()->SetGridx(0);
   pad->cd()->SetGridy(0);
   pad->cd()->SetTopMargin(0.05);
   pad->cd()->SetBottomMargin(0.15);
   pad->cd()->SetLeftMargin(0.15);
   pad->cd()->SetRightMargin(0.15);
   TString content1, content2;
   set_contentZ(i+27, content1, content2);
   n_sys_exppn[i] = new TGraphAsymmErrors(n_dimiso[i],n_protonnumexp[i],n_exppn[i],n_protonerror[i],n_protonerror[i],n_exppnL[i],n_exppnR[i]);
   n_sys_expqbetan_real[i] = new TGraphAsymmErrors(n_dimiso[i],n_protonnewnumexp[i],n_expqbetan[i],n_protonerror[i],n_protonerror[i],n_expqbetanL[i],n_expqbetanR[i]);
   n_sys_expqbetan[i] = new TGraphAsymmErrors(n_dimiso[i]-1,&n_protonnewnumexp[i][1],&n_expqbetan[i][1],&n_protonerror[i][1],&n_protonerror[i][1],&n_expqbetanL[i][1],&n_expqbetanR[i][1]);
   n_sys_frdmpn[i] = new TGraph(n_dimiso[i],n_protonnumexp[i],n_frdmpn[i]);
   n_sys_frdmpn[i]->SetLineColor(2);
   n_sys_ktuypn[i] = new TGraph(n_dimiso[i],n_protonnumexp[i],n_ktuypn[i]);
   n_sys_ktuypn[i]->SetLineColor(4);
   n_sys_borzpn[i] = new TGraph(n_dimiso[i]-1,&n_protonnumexp[i][1],&n_borzpn[i][1]);
   n_sys_borzpn[i]->SetLineColor(6);
   n_sys_shellpn[i] = new TGraph(n_dimiso[i],n_protonnumexp[i],n_shellpn[i]);
   n_sys_shellpn[i]->SetLineColor(8);
   TLatex text;
   text.SetTextAlign(12);
   text.SetTextSize(0.1);
   text.SetNDC(kTRUE);
   find_boundryN_npn(i+50,nmin,nmax,pnmin,pnmax);
   find_boundryN_nqbetan(i+50,nmin,nmax,qbetanmin,qbetanmax);
   //cout<<i<<", "<<nmin<<endl;
   n_sys_frdmpn[i]->GetXaxis()->SetLimits(nmin,nmax);
   n_sys_frdmpn[i]->GetYaxis()->SetRangeUser(0.0,pnmax);
   n_sys_frdmpn[i]->SetTitle("");
   n_sys_frdmpn[i]->GetXaxis()->SetTitle("Proton number");
   n_sys_frdmpn[i]->GetXaxis()->SetTitleOffset(0.8);
   n_sys_frdmpn[i]->GetXaxis()->CenterTitle(1);
   n_sys_frdmpn[i]->GetXaxis()->SetTitleSize(0.08);
   n_sys_frdmpn[i]->GetXaxis()->SetLabelSize(0.08);
   n_sys_frdmpn[i]->GetXaxis()->SetNdivisions((nmax-nmin+1)/2+1);
   n_sys_frdmpn[i]->GetYaxis()->SetNdivisions(5);
   n_sys_frdmpn[i]->GetYaxis()->SetTitle("Pn value (%)");
   n_sys_frdmpn[i]->GetYaxis()->CenterTitle(1);
   n_sys_frdmpn[i]->GetYaxis()->SetTitleOffset(0.8);
   n_sys_frdmpn[i]->GetYaxis()->SetTitleSize(0.08);
   n_sys_frdmpn[i]->GetYaxis()->SetLabelSize(0.08);
   n_sys_frdmpn[i]->SetLineWidth(2);
   n_sys_ktuypn[i]->SetLineWidth(2);
   n_sys_borzpn[i]->SetLineWidth(2);
   n_sys_shellpn[i]->SetLineWidth(2);
   n_sys_frdmpn[i]->Draw("AL");
   n_sys_ktuypn[i]->Draw("L");
   n_sys_borzpn[i]->Draw("L");
   n_sys_shellpn[i]->Draw("L");
   n_sys_exppn[i]->Draw("P");
   //text.DrawLatex(.3,.8,content1);
   n_sys_exppn[i]->SetMarkerStyle(21);
   n_sys_exppn[i]->SetMarkerSize(2);
   overlay->cd()->SetFillStyle(4000);
   overlay->cd()->SetFillColor(0);
   overlay->cd()->SetGridx(0);
   overlay->cd()->SetGridy(0);
   overlay->cd()->SetTopMargin(0.05);
   overlay->cd()->SetBottomMargin(0.15);
   overlay->cd()->SetLeftMargin(0.15);
   overlay->cd()->SetRightMargin(0.15);
   overlay->cd()->SetFrameFillStyle(4000);
   overlay->cd()->Draw();
   overlay->cd();
   n_sys_expqbetan[i]->GetXaxis()->SetLimits(nmin,nmax);
   n_sys_expqbetan[i]->GetYaxis()->SetRangeUser(0.0,qbetanmax);
   n_sys_expqbetan[i]->SetTitle("");
   n_sys_expqbetan[i]->GetXaxis()->SetLabelSize(0);
   n_sys_expqbetan[i]->GetXaxis()->SetNdivisions((nmax-nmin+1)/2+1);
   n_sys_expqbetan[i]->GetYaxis()->SetNdivisions(5);
   n_sys_expqbetan[i]->GetYaxis()->SetLabelSize(0.08);
   n_sys_expqbetan[i]->SetMarkerStyle(26);
   n_sys_expqbetan[i]->SetLineStyle(2);
   n_sys_expqbetan[i]->SetMarkerSize(2);
   n_sys_expqbetan[i]->GetYaxis()->SetTitle("Q_{#beta n}/Q_{#beta} (%)");
   n_sys_expqbetan[i]->GetYaxis()->CenterTitle(1);
   n_sys_expqbetan[i]->GetYaxis()->RotateTitle(1);
   n_sys_expqbetan[i]->GetYaxis()->SetTitleOffset(0.8);
   n_sys_expqbetan[i]->GetYaxis()->SetTitleSize(0.08);
   n_sys_expqbetan[i]->Draw("APLY+");
   n_sys_expqbetan_real[i]->Draw("P");

   pad->cd();
   n_legpn[i] = new TLegend(0.55,0.6,0.80,0.95,"");
   n_legpn[i]->AddEntry(n_sys_exppn[i],"Experiment","P");
   n_legpn[i]->AddEntry(n_sys_expqbetan[i],"Q_{#beta n}/Q_{#beta} (AME2012)","PL");
   n_legpn[i]->AddEntry(n_sys_frdmpn[i],"FRDM+QRPA","L");
   n_legpn[i]->AddEntry(n_sys_ktuypn[i],"KTUY+GT2","L");
   n_legpn[i]->AddEntry(n_sys_borzpn[i],"DF+CQRPA","L");
   n_legpn[i]->AddEntry(n_sys_shellpn[i],"Shell Model","L");
   n_legpn[i]->SetBorderSize(0);
   n_legpn[i]->SetFillColor(0);
   n_legpn[i]->SetFillStyle(0);
   n_legpn[i]->Draw();
   cout<<"c02 finished"<<endl;

   c01->Write();
   c02->Write();
   RootFile->Write();
   delete RootFile;
}
