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

Double_t p_oldexphalf[10][100];//literature half-life
Double_t p_oldexphalfL[10][100];
Double_t p_oldexphalfR[10][100];
Double_t p_newexphalf[10][100];//half-life with gamma
Double_t p_newexphalfL[10][100];
Double_t p_newexphalfR[10][100];
Double_t p_updexphalf[10][100];//half-life without gamma
Double_t p_updexphalfL[10][100];
Double_t p_updexphalfR[10][100];
Double_t p_allexphalf[10][100];//half-life without gamma
Double_t p_allexphalfL[10][100];
Double_t p_allexphalfR[10][100];
Double_t p_oldneutronnum[10][100];
Double_t p_neutronnum[10][100];
Double_t p_neutronerror[10][100];
Double_t p_dimiso[10];//number of isotopes per Z

void read_data(){
   ifstream in_data;
   Int_t Z, N;
   Double_t expQ;
   Double_t expQerr;
   Double_t old_exphl;
   Double_t old_exphlL;
   Double_t old_exphlR;
   Double_t new_exphl;
   Double_t new_exphlL;
   Double_t new_exphlR;
   Double_t new_expghl;
   Double_t new_expghlL;
   Double_t new_expghlR;
   Double_t frdmhl;
   Double_t ktu1hl;
   Double_t ktu2hl;
   Double_t borzhl;
   Double_t explaw;

   for(int i=0; i<10; i++){
      p_dimiso[i]=0;
      for(int j=0; j<100; j++){
         p_oldexphalf[i][j]=-1000;
         p_oldexphalfL[i][j]=0;
         p_oldexphalfR[i][j]=0;
         p_newexphalf[i][j]=-1000;
         p_newexphalfL[i][j]=0;
         p_newexphalfR[i][j]=0;
         p_updexphalf[i][j]=-1000;
         p_updexphalfL[i][j]=0;
         p_updexphalfR[i][j]=0;
         p_allexphalf[i][j]=-1000;
         p_allexphalfL[i][j]=0;
         p_allexphalfR[i][j]=0;
         p_oldneutronnum[i][j]=0;
         p_neutronnum[i][j]=0;
         p_neutronerror[i][j]=0;
      }
   }
   in_data.open("macros/hlsys.input", ios::in);
   while (in_data.good()){
      in_data >>Z>>N>>new_expghl>>new_expghlL>>new_expghlR>>new_exphl>>new_exphlL>>new_exphlR>>old_exphl>>old_exphlL>>old_exphlR>>frdmhl>>ktu1hl>>ktu2hl>>borzhl>>expQ>>expQerr;

      int index=Z-26;
      if(index<6&&index>=0 && N>=43 && N<=52){
         p_oldneutronnum[index][p_dimiso[index]]=N;
         p_neutronnum[index][p_dimiso[index]]=N;
         if(old_exphl>0){
            if(new_expghl>0){
               p_updexphalf[index][p_dimiso[index]]=new_expghl;
               p_updexphalfL[index][p_dimiso[index]]=new_expghlL;
               p_updexphalfR[index][p_dimiso[index]]=new_expghlR;
               p_allexphalf[index][p_dimiso[index]]=new_expghl;
               p_allexphalfL[index][p_dimiso[index]]=new_expghlL;
               p_allexphalfR[index][p_dimiso[index]]=new_expghlR;
               p_oldexphalf[index][p_dimiso[index]]=old_exphl;
               p_oldexphalfL[index][p_dimiso[index]]=old_exphlL;
               p_oldexphalfR[index][p_dimiso[index]]=old_exphlR;
               p_oldneutronnum[index][p_dimiso[index]]=N-0.15;
            }else{
               p_oldexphalf[index][p_dimiso[index]]=old_exphl;
               p_oldexphalfL[index][p_dimiso[index]]=old_exphlL;
               p_oldexphalfR[index][p_dimiso[index]]=old_exphlR;
               p_allexphalf[index][p_dimiso[index]]=old_exphl;
               p_allexphalfL[index][p_dimiso[index]]=old_exphlL;
               p_allexphalfR[index][p_dimiso[index]]=old_exphlR;
            }
         }else{
            if(new_expghl>0){
               p_newexphalf[index][p_dimiso[index]]=new_expghl;
               p_newexphalfL[index][p_dimiso[index]]=new_expghlL;
               p_newexphalfR[index][p_dimiso[index]]=new_expghlR;
               p_allexphalf[index][p_dimiso[index]]=new_expghl;
               p_allexphalfL[index][p_dimiso[index]]=new_expghlL;
               p_allexphalfR[index][p_dimiso[index]]=new_expghlR;
            }else{
               p_newexphalf[index][p_dimiso[index]]=new_exphl;
               p_newexphalfL[index][p_dimiso[index]]=new_exphlL;
               p_newexphalfR[index][p_dimiso[index]]=new_exphlR;
               p_allexphalf[index][p_dimiso[index]]=new_exphl;
               p_allexphalfL[index][p_dimiso[index]]=new_exphlL;
               p_allexphalfR[index][p_dimiso[index]]=new_exphlR;
            }
         }
         cout<<"Z="<<Z<<", N="<<N<<", T1/2="<<p_allexphalf[index][p_dimiso[index]]<<endl;
         p_dimiso[index]++;
      }
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

void find_boundryZ_total_nhl(Double_t &nmin, Double_t &nmax, double &hlmin, double &hlmax){
   nmin = 1000;
   nmax = 0;
   hlmax=0;
   hlmin=1000;
   for(int i=1; i<7; i++){
      for(int j=0; j<p_dimiso[i]; j++){
         if(p_neutronnum[i][j]<nmin){
            nmin=p_neutronnum[i][j];
         }
         if(p_neutronnum[i][j]>nmax){
            nmax=p_neutronnum[i][j];
         }
         if(p_allexphalf[i][j]>0 && p_allexphalf[i][j]>hlmax){
            hlmax=p_allexphalf[i][j];
         }
         if(p_allexphalf[i][j]>0 && p_allexphalf[i][j]<hlmin){
            hlmin=p_allexphalf[i][j];
         }
      }
   }
   hlmin=hlmin/2;
   hlmax=hlmax*1.5;
   nmin = nmin-0.5;
   nmax = nmax+0.5;
   //cout<<hlmin<<", "<<hlmax<<endl;
}

int SetColor(int Z){
   int color;
   switch(Z){
      case 26:
         color=0;
         break;
      case 27:
         color=2;
         break;
      case 28:
         color=1;
         break;
      case 29:
         color=4;
         break;
      case 30:
         color=46;
         break;
      case 31:
         color=6;
         break;
   }
   return color;
}

int SetMarker_new(int Z){
   int marker;
   switch(Z){
      case 26:
         marker=5;
         break;
      case 27:
         marker=20;
         break;
      case 28:
         marker=21;
         break;
      case 29:
         marker=22;
         break;
      case 30:
         marker=29;
         break;
      case 31:
         marker=28;
         break;
   }
   return marker;
}

int SetMarker_old(int Z){
   int marker;
   switch(Z){
      case 26:
         marker=5;
         break;
      case 27:
         marker=24;
         break;
      case 28:
         marker=25;
         break;
      case 29:
         marker=26;
         break;
      case 30:
         marker=30;
         break;
      case 31:
         marker=28;
         break;
   }
   return marker;
}

void plot_syshl(){

   TFile *RootFile = new TFile("root/root_histogram/hlsys_all.root","RECREATE");
   TGraphAsymmErrors *p_sys_oldexp[10]; //array for different isotopes
   TGraphAsymmErrors *p_sys_updexp[10]; //array for different isotopes
   TGraphAsymmErrors *p_sys_newexp[10]; //array for different isotopes
   TGraph *p_sys_allexp[10]; //array for different isotopes

   TLegend *p_legiso;
   TLegend *p_leghl;

   TCanvas *c01 = new TCanvas ("c01","c01",0,0,800,600);

   Double_t nmin, nmax;
   double hlmin, hlmax;

   read_data();

   /***************** half-life as a function of N for all isotopes *************/
   c01->cd();
   c01->cd()->SetGridx(0);
   c01->cd()->SetGridy(0);
   find_boundryZ_total_nhl(nmin, nmax, hlmin, hlmax);
   gPad->SetLogy(1);
   int if_filled=0;
   for(int i=1; i<7; i++){
      if(p_dimiso[i]==0){
         continue;
      }
      cout<<p_dimiso[i]<<endl;
      p_sys_allexp[i] = new TGraph(p_dimiso[i],p_neutronnum[i],p_allexphalf[i]);
      p_sys_newexp[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronnum[i],p_newexphalf[i],p_neutronerror[i],p_neutronerror[i],p_newexphalfL[i],p_newexphalfR[i]);
      p_sys_updexp[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronnum[i],p_updexphalf[i],p_neutronerror[i],p_neutronerror[i],p_updexphalfL[i],p_updexphalfR[i]);
      p_sys_oldexp[i] = new TGraphAsymmErrors(p_dimiso[i],p_oldneutronnum[i],p_oldexphalf[i],p_neutronerror[i],p_neutronerror[i],p_oldexphalfL[i],p_oldexphalfR[i]);
      int color, marker_new, marker_old;
      color=SetColor(i+26);
      marker_new=SetMarker_new(i+26);
      marker_old=SetMarker_old(i+26);
      p_sys_newexp[i]->SetMarkerStyle(marker_new);
      p_sys_updexp[i]->SetMarkerStyle(marker_new);
      p_sys_oldexp[i]->SetMarkerStyle(marker_old);
      p_sys_allexp[i]->SetMarkerStyle(marker_old);
      if(i+26<=28){
         p_sys_newexp[i]->SetMarkerSize(3);
         p_sys_updexp[i]->SetMarkerSize(2);
         p_sys_oldexp[i]->SetMarkerSize(2);
         p_sys_allexp[i]->SetMarkerSize(2);
      }else if(i+26==29){
         p_sys_newexp[i]->SetMarkerSize(3.5);
         p_sys_updexp[i]->SetMarkerSize(2.5);
         p_sys_oldexp[i]->SetMarkerSize(2.5);
         p_sys_allexp[i]->SetMarkerSize(2.5);
      }else{
         p_sys_newexp[i]->SetMarkerSize(4);
         p_sys_updexp[i]->SetMarkerSize(3);
         p_sys_oldexp[i]->SetMarkerSize(3);
         p_sys_allexp[i]->SetMarkerSize(3);
      }
      p_sys_allexp[i]->SetLineWidth(2);
      p_sys_allexp[i]->SetLineColor(color);
      if(if_filled==0){
         p_sys_allexp[i]->GetXaxis()->SetLimits(nmin,nmax);
         p_sys_allexp[i]->GetYaxis()->SetRangeUser(hlmin,hlmax);
         //p_sys_allexp[i]->SetTitle("Half-lives (isotope)");
         p_sys_allexp[i]->SetTitle("");
         p_sys_allexp[i]->GetXaxis()->SetTitle("neutron number");
         p_sys_allexp[i]->GetYaxis()->SetTitle("half-life (ms)");
         p_sys_allexp[i]->GetXaxis()->CenterTitle(1);
         p_sys_allexp[i]->GetYaxis()->CenterTitle(1);
         p_sys_allexp[i]->Draw("AL");
         p_sys_newexp[i]->Draw("P");
         p_sys_updexp[i]->Draw("P");
         p_sys_oldexp[i]->Draw("P");
         if_filled=1;
      }else{
         p_sys_allexp[i]->Draw("L");
         p_sys_newexp[i]->Draw("P");
         p_sys_updexp[i]->Draw("P");
         p_sys_oldexp[i]->Draw("P");
      }
   }
   p_legiso = new TLegend(0.7,0.5,1.1,0.9,"");
   for(int i=6; i>=1; i--){
      if(p_dimiso[i]==0){
         continue;
      }
      TString content1, content2;
      set_contentZ(26+i, content1, content2);
      p_legiso->AddEntry(p_sys_allexp[i],content1,"PL");
   }
   //p_leghl = new TLegend(0.1,0.1,0.4,0.2,"");
   ////p_leghl->AddEntry(p_sys_newexp[1],"new half-life","P");
   //p_leghl->AddEntry(p_sys_updexp[2],"Present work","P");
   //p_leghl->AddEntry(p_sys_oldexp[2],"Previous work","P");
   p_legiso->SetBorderSize(0);
   p_legiso->SetFillColor(0);
   p_legiso->SetFillStyle(0);
   p_legiso->Draw();
   //p_leghl->SetBorderSize(0);
   //p_leghl->SetFillColor(0);
   //p_leghl->SetFillStyle(0);
   //p_leghl->Draw();
   cout<<"c01 finished"<<endl;

   c01->Write();
   RootFile->Write();
   delete RootFile;
}
