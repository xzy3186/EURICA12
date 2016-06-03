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

Double_t p_exppn[5][100];//exp half-life
Double_t p_exppnL[5][100];
Double_t p_exppnR[5][100];
Double_t p_expoldpn[5][100];//exp half-life
Double_t p_expoldpnL[5][100];
Double_t p_expoldpnR[5][100];
Double_t p_qbetan[5][100];//exp half-life
Double_t p_qbetanL[5][100];
Double_t p_qbetanR[5][100];
Double_t p_frdm1pn[5][100];//frdm+qrpa
Double_t p_frdm2pn[5][100];//frdm+qrpa
Double_t p_ktuypn[5][100];//ktuy+gt
Double_t p_borzpn[5][100];//borzov
Double_t p_neutronnumexp[5][100];
Double_t p_neutronoldnumexp[5][100];
Double_t p_neutronnewnumexp[5][100];
Double_t p_neutronerror[5][100];
Double_t p_dimiso[5];//number of isotopes per Z

void read_data(){
   ifstream in_data;
   Int_t Z, N;
   Double_t new_exppn;
   Double_t new_exppnL;
   Double_t new_exppnR;
   Double_t old_exppn;
   Double_t old_exppnL;
   Double_t old_exppnR;
   Double_t qbetan;
   Double_t qbetanLR;
   Double_t frdm1pn;
   Double_t frdm2pn;
   Double_t ktuypn;
   Double_t borzpn;

   for(int i=0; i<5; i++){
      p_dimiso[i]=0;
      for(int j=0; j<100; j++){
         p_exppn[i][j]=0;
         p_exppnL[i][j]=0;
         p_exppnR[i][j]=0;
         p_expoldpn[i][j]=0;
         p_expoldpnL[i][j]=0;
         p_expoldpnR[i][j]=0;
         p_qbetan[i][j]=0;
         p_qbetanL[i][j]=0;
         p_qbetanR[i][j]=0;
         p_frdm1pn[i][j]=0;
         p_frdm2pn[i][j]=0;
         p_ktuypn[i][j]=0;
         p_borzpn[i][j]=0;
         p_neutronnumexp[i][j]=0;
         p_neutronoldnumexp[i][j]=0;
         p_neutronnewnumexp[i][j]=0;
         p_neutronerror[i][j]=0;
      }
   }
   in_data.open("macros/pnsys.input", ios::in);
   int temp=0;
   while (in_data.good()){
      in_data >>Z>>N>>new_exppn>>new_exppnL>>new_exppnR>>old_exppn>>old_exppnL>>old_exppnR>>frdm1pn>>frdm2pn>>ktuypn>>borzpn>>qbetan>>qbetanLR;
      //explaw = Calhalflife(Z,N);
      int index=Z-27;
      if(index<5&&index>=0){
         p_neutronnumexp[index][p_dimiso[index]]=N;
         p_neutronoldnumexp[index][p_dimiso[index]]=N-0.15;
         p_neutronnewnumexp[index][p_dimiso[index]]=N+0.15;
         p_exppn[index][p_dimiso[index]]=new_exppn;
         p_exppnL[index][p_dimiso[index]]=new_exppnL;
         p_exppnR[index][p_dimiso[index]]=new_exppnR;
         p_expoldpn[index][p_dimiso[index]]=old_exppn;
         p_expoldpnL[index][p_dimiso[index]]=old_exppnL;
         p_expoldpnR[index][p_dimiso[index]]=old_exppnR;
         p_qbetan[index][p_dimiso[index]]=qbetan;
         p_qbetanL[index][p_dimiso[index]]=qbetanLR;
         p_qbetanR[index][p_dimiso[index]]=qbetanLR;
         p_frdm1pn[index][p_dimiso[index]]=frdm1pn;
         p_frdm2pn[index][p_dimiso[index]]=frdm2pn;
         p_ktuypn[index][p_dimiso[index]]=ktuypn;
         p_borzpn[index][p_dimiso[index]]=borzpn;
         p_dimiso[index]++;
         //cout<<qbetan<<endl;
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

void find_boundryZ_npn(int Z, Double_t &nmin, Double_t &nmax, double &pnmin, double &pnmax){
   int index=Z-27;
   nmin = p_neutronnumexp[index][0]-0.5;
   nmax = p_neutronnumexp[index][p_dimiso[index]-1]+0.5;
   double tempmin=1000;
   double tempmax=0;
   for(int i=0; i<p_dimiso[index]; i++){
      if(p_exppn[index][i]>tempmax){
         tempmax=p_exppn[index][i];
      }
      if(p_expoldpn[index][i]>tempmax){
         tempmax=p_exppn[index][i];
      }
      if(p_frdm1pn[index][i]>tempmax){
         tempmax=p_frdm1pn[index][i];
      }
      if(p_frdm2pn[index][i]>tempmax){
         tempmax=p_frdm2pn[index][i];
      }
      if(p_ktuypn[index][i]>tempmax){
         tempmax=p_ktuypn[index][i];
      }
      if(p_borzpn[index][i]>tempmax){
         tempmax=p_borzpn[index][i];
      }
      if(p_exppn[index][i]<tempmin && p_exppn[index][i]>0){
         tempmin=p_exppn[index][i];
      }
      if(p_expoldpn[index][i]<tempmin && p_expoldpn[index][i]>0){
         tempmin=p_exppn[index][i];
      }
      if(p_frdm1pn[index][i]<tempmin && p_frdm1pn[index][i]>0){
         tempmin=p_frdm1pn[index][i];
      }
      if(p_frdm2pn[index][i]<tempmin && p_frdm2pn[index][i]>0){
         tempmin=p_frdm2pn[index][i];
      }
      if(p_ktuypn[index][i]<tempmin && p_ktuypn[index][i]>0){
         tempmin=p_ktuypn[index][i];
      }
      if(p_borzpn[index][i]<tempmin && p_borzpn[index][i]>0){
         tempmin=p_borzpn[index][i];
      }
   }
   pnmin=tempmin/2.0;
   pnmax=tempmax*1.2;
}

void find_boundryZ_nqbetan(int Z, Double_t &nmin, Double_t &nmax, double &qbetanmin, double &qbetanmax){
   int index=Z-27;
   nmin = p_neutronnumexp[index][0]-0.5;
   nmax = p_neutronnumexp[index][p_dimiso[index]-1]+0.5;
   double tempmin=1000;
   double tempmax=0;
   for(int i=0; i<p_dimiso[index]; i++){
      if(p_qbetan[index][i]>tempmax){
         tempmax=p_qbetan[index][i];
      }
      if(p_qbetan[index][i]<tempmin && p_qbetan[index][i]>0){
         tempmin=p_qbetan[index][i];
      }
   }
   qbetanmin=tempmin/2.0;
   qbetanmax=tempmax*1.2;
}

void plot_syspn(){

   TFile *RootFile = new TFile("root/root_histogram/pnsys.root","RECREATE");
   TGraphAsymmErrors *p_sys_exp[5]; //array for different isotopes
   TGraphAsymmErrors *p_sys_old[5]; //array for different isotopes
   TGraphAsymmErrors *p_sys_qbetan[5]; //array for different isotopes
   TGraphAsymmErrors *p_sys_qbetan_real[5]; //array for different isotopes
   TGraph *p_sys_frdm1[5]; //array for different isotopes
   TGraph *p_sys_frdm2[5]; //array for different isotopes
   TGraph *p_sys_ktuy[5]; //array for different isotopes
   TGraph *p_sys_borz[5]; //array for different isotopes

   TLegend *p_leg[5];

   TCanvas *c01 = new TCanvas ("c01","c01",0,0,800,1000);
   TPad *pad = new TPad("pad","",0,0,1,1);
   pad->SetGrid();
   pad->Draw();
   TPad *overlay = new TPad("overlay","",0,0,1,1);
   overlay->Draw();
   overlay->SetFillStyle(4000);
   overlay->SetFillColor(0);

   Double_t nmin, nmax;
   double pnmin, pnmax;
   double qbetanmin, qbetanmax;
   read_data();
   /***************** half-life as a function of N by isotope *******************/
   pad->Divide(2,3);
   overlay->Divide(2,3);
   for(int i=0; i<5; i++){
      //cout<<"Pi="<<p_dimiso[i]<<endl;
      if(p_dimiso[i]==0){
         continue;
      }
      pad->cd(i+1)->Draw();
      pad->cd(i+1);
      pad->cd(i+1)->SetGridx(0);
      pad->cd(i+1)->SetGridy(0);
      pad->cd(i+1)->SetTopMargin(0.05);
      pad->cd(i+1)->SetBottomMargin(0.15);
      pad->cd(i+1)->SetLeftMargin(0.15);
      pad->cd(i+1)->SetRightMargin(0.15);
      TString content1, content2;
      set_contentZ(i+27, content1, content2);
      p_sys_exp[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronnumexp[i],p_exppn[i],p_neutronerror[i],p_neutronerror[i],p_exppnL[i],p_exppnR[i]);
      p_sys_old[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronoldnumexp[i],p_expoldpn[i],p_neutronerror[i],p_neutronerror[i],p_expoldpnL[i],p_expoldpnR[i]);
      p_sys_qbetan[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronnewnumexp[i],p_qbetan[i],p_neutronerror[i],p_neutronerror[i],p_qbetanL[i],p_qbetanR[i]);
      p_sys_qbetan_real[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronnewnumexp[i],p_qbetan[i],p_neutronerror[i],p_neutronerror[i],p_qbetanL[i],p_qbetanR[i]);
      p_sys_frdm1[i] = new TGraph(p_dimiso[i],p_neutronnumexp[i],p_frdm1pn[i]);
      p_sys_frdm1[i]->SetLineColor(2);
      p_sys_frdm2[i] = new TGraph(p_dimiso[i],p_neutronnumexp[i],p_frdm2pn[i]);
      p_sys_frdm2[i]->SetLineColor(4);
      p_sys_ktuy[i] = new TGraph(p_dimiso[i],p_neutronnumexp[i],p_ktuypn[i]);
      p_sys_ktuy[i]->SetLineColor(6);
      p_sys_borz[i] = new TGraph(p_dimiso[i],p_neutronnumexp[i],p_borzpn[i]);
      p_sys_ktuy[i]->SetLineColor(8);
      TLatex text;
      text.SetTextAlign(12);
      text.SetTextSize(0.1);
      text.SetNDC(kTRUE);
      find_boundryZ_npn(i+27,nmin,nmax,pnmin,pnmax);
      find_boundryZ_nqbetan(i+27,nmin,nmax,qbetanmin,qbetanmax);
      //cout<<i<<", "<<nmin<<endl;
      p_sys_frdm1[i]->GetXaxis()->SetLimits(nmin,nmax);
      p_sys_frdm1[i]->GetYaxis()->SetRangeUser(pnmin,pnmax);
      p_sys_frdm1[i]->SetTitle("");
      if(i>=3){
         p_sys_frdm1[i]->GetXaxis()->SetTitle("Neutron number");
         p_sys_frdm1[i]->GetXaxis()->SetTitleOffset(0.8);
         p_sys_frdm1[i]->GetXaxis()->CenterTitle(1);
      }else{
         p_sys_frdm1[i]->GetXaxis()->SetTitle("");
      }
      p_sys_frdm1[i]->GetXaxis()->SetTitleSize(0.08);
      p_sys_frdm1[i]->GetXaxis()->SetLabelSize(0.08);
      p_sys_frdm1[i]->GetXaxis()->SetNdivisions((nmax-nmin+1)/2+1);
      p_sys_frdm1[i]->GetYaxis()->SetNdivisions(5);
      if(i==0 || i==2 || i==4){
         p_sys_frdm1[i]->GetYaxis()->SetTitle("Pn value (%)");
         p_sys_frdm1[i]->GetYaxis()->CenterTitle(1);
         p_sys_frdm1[i]->GetYaxis()->SetTitleOffset(0.8);
      }else{
         p_sys_frdm1[i]->GetYaxis()->SetTitle("");
      }
      p_sys_frdm1[i]->GetYaxis()->SetTitleSize(0.08);
      p_sys_frdm1[i]->GetYaxis()->SetLabelSize(0.08);
      p_sys_frdm1[i]->SetLineWidth(2);
      p_sys_frdm2[i]->SetLineWidth(2);
      p_sys_ktuy[i]->SetLineWidth(2);
      p_sys_borz[i]->SetLineWidth(2);
      p_sys_frdm1[i]->Draw("AL");
      p_sys_frdm2[i]->Draw("L");
      p_sys_ktuy[i]->Draw("L");
      p_sys_borz[i]->Draw("L");
      p_sys_exp[i]->Draw("P");
      p_sys_old[i]->Draw("P");
      text.DrawLatex(.3,.8,content1);
      p_sys_exp[i]->SetMarkerStyle(21);
      p_sys_exp[i]->SetMarkerSize(2);
      p_sys_old[i]->SetMarkerStyle(25);
      p_sys_old[i]->SetMarkerSize(2);
      overlay->cd(i+1)->SetFillStyle(4000);
      overlay->cd(i+1)->SetFillColor(0);
      overlay->cd(i+1)->SetGridx(0);
      overlay->cd(i+1)->SetGridy(0);
      overlay->cd(i+1)->SetTopMargin(0.05);
      overlay->cd(i+1)->SetBottomMargin(0.15);
      overlay->cd(i+1)->SetLeftMargin(0.15);
      overlay->cd(i+1)->SetRightMargin(0.15);
      overlay->cd(i+1)->SetFrameFillStyle(4000);
      overlay->cd(i+1)->Draw();
      overlay->cd(i+1);
      p_sys_qbetan[i]->GetXaxis()->SetLimits(nmin,nmax);
      p_sys_qbetan[i]->GetYaxis()->SetRangeUser(0,qbetanmax);
      p_sys_qbetan[i]->SetTitle("");
      p_sys_qbetan[i]->GetXaxis()->SetLabelSize(0);
      p_sys_qbetan[i]->GetXaxis()->SetNdivisions((nmax-nmin+1)/2+1);
      p_sys_qbetan[i]->GetYaxis()->SetNdivisions(5);
      p_sys_qbetan[i]->GetYaxis()->SetLabelSize(0.08);
      p_sys_qbetan[i]->SetMarkerStyle(26);
      p_sys_qbetan[i]->SetLineStyle(2);
      p_sys_qbetan[i]->SetMarkerSize(1);
      p_sys_qbetan[i]->SetLineWidth(2);
      if(i==1 || i==3 || i==4){
         p_sys_qbetan[i]->GetYaxis()->SetTitle("Q_{#beta n}/Q_{#beta} (%)");
         p_sys_qbetan[i]->GetYaxis()->CenterTitle(1);
         p_sys_qbetan[i]->GetYaxis()->RotateTitle(1);
         p_sys_qbetan[i]->GetYaxis()->SetTitleOffset(0.8);
         p_sys_qbetan[i]->GetYaxis()->SetTitleSize(0.08);
      }else{
         p_sys_qbetan[i]->GetYaxis()->SetTitle("");
      }
      //p_sys_qbetan[i]->GetXaxis()->SetTickSize(0);
      p_sys_qbetan[i]->Draw("APLY+");
      p_sys_qbetan_real[i]->Draw("P");
      if(i==4){
         overlay->cd(6)->SetFillStyle(4000);
         overlay->cd(6)->SetFillColor(0);
         overlay->cd(6)->Draw();
         pad->cd(6);
         p_leg[i] = new TLegend(0.10,0.10,0.9,0.9,"");
         p_leg[i]->AddEntry(p_sys_exp[i],"Present work","P");
         p_leg[i]->AddEntry(p_sys_old[i],"Previous work","P");
         p_leg[i]->AddEntry(p_sys_qbetan[i],"Q_{#beta n}/Q_{#beta} (AME2012)","PL");
         p_leg[i]->AddEntry(p_sys_frdm1[i],"FRDM+QRPA-1","L");
         p_leg[i]->AddEntry(p_sys_frdm2[i],"FRDM+QRPA-2","L");
         p_leg[i]->AddEntry(p_sys_ktuy[i],"KTUY+GT2","L");
         p_leg[i]->AddEntry(p_sys_borz[i],"DF+CQRPA","L");
         p_leg[i]->SetBorderSize(0);
         p_leg[i]->SetFillColor(0);
         p_leg[i]->SetFillStyle(0);
         p_leg[i]->Draw();
      }
   }
   cout<<"c01 finished"<<endl;

   c01->Write();
   RootFile->Write();
   delete RootFile;
}
