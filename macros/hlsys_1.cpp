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

Double_t p_newexphalf[100];//exp half-life
Double_t p_newexphalfL[100];
Double_t p_newexphalfR[100];
Double_t p_oldexphalf[100];//literature half-life
Double_t p_oldexphalfL[100];
Double_t p_oldexphalfR[100];
Double_t p_frdmhalf[100];//frdm+qrpa
Double_t p_ktuyhalf[100];//ktuy+gt
Double_t p_borzhalf[100];//DF+CQRPA
Double_t p_neutronnumoldexp[100];
Double_t p_neutronnumnewexp[100];
Double_t p_neutronerror[100];
Int_t p_dimiso;//number of isotopes of Z=28

Double_t n_newexphalf[100];//exp half-life
Double_t n_newexphalfL[100];
Double_t n_newexphalfR[100];
Double_t n_oldexphalf[100];//literature half-life
Double_t n_oldexphalfL[100];
Double_t n_oldexphalfR[100];
Double_t n_frdmhalf[100];//frdm+qrpa
Double_t n_ktuyhalf[100];//ktuy+gt
Double_t n_borzhalf[100];//DF+CQRPA
Double_t n_protonnumoldexp[100];
Double_t n_protonnumnewexp[100];
Double_t n_protonerror[100];
Int_t n_dimiso;//number of isotopes of Z=28

Double_t n_sm1[9];//shell model by Q. Zhi
n_sm1[8]=6900;
n_sm1[7]=1030;
n_sm1[6]= 530;
n_sm1[5]= 270;
n_sm1[4]= 150;
n_sm1[3]=  16;
n_sm1[2]= 8.3;
n_sm1[1]= 3.7;
n_sm1[0]= 2.3;

void read_data(){
   cout<<n_sm1[0]<<", "<<n_sm1[1]<<endl;
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


   p_dimiso=0;
   for(int j=0; j<100; j++){
      p_oldexphalf[j]=-100;
      p_oldexphalfL[j]=0;
      p_oldexphalfR[j]=0;
      p_newexphalf[j]=-100;
      p_newexphalfL[j]=0;
      p_newexphalfR[j]=0;
      p_frdmhalf[j]=0;
      p_ktuyhalf[j]=0;
      p_borzhalf[j]=0;
      p_neutronnumnewexp[j]=0;
      p_neutronnumnewexp[j]=0;
      p_neutronerror[j]=0;
   }
   n_dimiso=0;
   for(int j=0; j<100; j++){
      n_oldexphalf[j]=-100;
      n_oldexphalfL[j]=0;
      n_oldexphalfR[j]=0;
      n_newexphalf[j]=-100;
      n_newexphalfL[j]=0;
      n_newexphalfR[j]=0;
      n_frdmhalf[j]=0;
      n_ktuyhalf[j]=0;
      n_borzhalf[j]=0;
      n_protonnumnewexp[j]=0;
      n_protonnumnewexp[j]=0;
      n_protonerror[j]=0;
   }
   in_data.open("macros/hlsys1.input", ios::in);
   while (in_data.good()){
      in_data >>Z>>N>>new_expghl>>new_expghlL>>new_expghlR>>new_exphl>>new_exphlL>>new_exphlR>>old_exphl>>old_exphlL>>old_exphlR>>frdmhl>>ktu1hl>>ktu2hl>>borzhl>>expQ>>expQerr;
      int index=Z-26;
      if(index==2){//Z=28 isotopes
         p_neutronnumoldexp[p_dimiso]=N-0.15;
         p_neutronnumnewexp[p_dimiso]=N;
         if(new_expghl>0){
            p_newexphalf[p_dimiso]=new_expghl;
            p_newexphalfL[p_dimiso]=new_expghlL;
            p_newexphalfR[p_dimiso]=new_expghlR;
         }else if(new_expghl<=0 && new_exphl>0){
            p_newexphalf[p_dimiso]=new_exphl;
            p_newexphalfL[p_dimiso]=new_exphlL;
            p_newexphalfR[p_dimiso]=new_exphlR;
         }
         if(old_exphl>0){
            p_oldexphalf[p_dimiso]=old_exphl;
            p_oldexphalfL[p_dimiso]=old_exphlL;
            p_oldexphalfR[p_dimiso]=old_exphlR;
         }
         p_frdmhalf[p_dimiso]=frdmhl;
         p_ktuyhalf[p_dimiso]=ktu1hl;
         p_borzhalf[p_dimiso]=borzhl;
         p_dimiso++;
      }
      index=N-44;
      if(index==6){//N=50 isotones
         n_protonnumoldexp[n_dimiso]=Z-0.15;
         n_protonnumnewexp[n_dimiso]=Z;
         if(new_expghl>0){
            n_newexphalf[n_dimiso]=new_expghl;
            n_newexphalfL[n_dimiso]=new_expghlL;
            n_newexphalfR[n_dimiso]=new_expghlR;
         }else if(new_expghl<=0 && new_exphl>0){
            n_newexphalf[n_dimiso]=new_exphl;
            n_newexphalfL[n_dimiso]=new_exphlL;
            n_newexphalfR[n_dimiso]=new_exphlR;
         }
         if(old_exphl>0){
            n_oldexphalf[n_dimiso]=old_exphl;
            n_oldexphalfL[n_dimiso]=old_exphlL;
            n_oldexphalfR[n_dimiso]=old_exphlR;
         }
         n_frdmhalf[n_dimiso]=frdmhl;
         n_ktuyhalf[n_dimiso]=ktu1hl;
         if(Z<=32){
            n_borzhalf[n_dimiso]=n_sm1[Z-24];
         }
         n_dimiso++;
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

void find_boundryZ_nhl(Double_t &nmin, Double_t &nmax, double &hlmin, double &hlmax){
   nmin = p_neutronnumoldexp[0]-0.5;
   nmax = p_neutronnumnewexp[p_dimiso-1]+0.5;
   double tempmin=1000;
   double tempmax=0;
   for(int i=0; i<p_dimiso; i++){
      if(p_newexphalf[i]>tempmax){
         tempmax=p_newexphalf[i];
      }
      if(p_oldexphalf[i]>tempmax){
         tempmax=p_oldexphalf[i];
      }
      if(p_frdmhalf[i]>tempmax){
         tempmax=p_frdmhalf[i];
      }
      if(p_ktuyhalf[i]>tempmax){
         tempmax=p_ktuyhalf[i];
      }
      if(p_borzhalf[i]>tempmax){
         tempmax=p_borzhalf[i];
      }
      if(p_newexphalf[i]<tempmin && p_newexphalf[i]>0){
         tempmin=p_newexphalf[i];
      }
      if(p_oldexphalf[i]<tempmin && p_oldexphalf[i]>0){
         tempmin=p_oldexphalf[i];
      }
      if(p_frdmhalf[i]<tempmin && p_frdmhalf[i]>0){
         tempmin=p_frdmhalf[i];
      }
      if(p_ktuyhalf[i]<tempmin && p_ktuyhalf[i]>0){
         tempmin=p_ktuyhalf[i];
      }
      if(p_borzhalf[i]<tempmin && p_borzhalf[i]>0){
         tempmin=p_borzhalf[i];
      }
      //cout<<tempmin<<", "<<tempmax<<endl;
   }
   hlmin=tempmin/2.0;
   hlmax=tempmax*2;
}

void find_boundryN_nhl(Double_t &nmin, Double_t &nmax, double &hlmin, double &hlmax){
   nmin = n_protonnumoldexp[0]-0.5;
   nmax = n_protonnumnewexp[n_dimiso-2]+0.5;
   double tempmin=1000;
   double tempmax=0;
   for(int i=0; i<n_dimiso-1; i++){
      if(n_newexphalf[i]>tempmax){
         tempmax=n_newexphalf[i];
      }
      if(n_oldexphalf[i]>tempmax){
         tempmax=n_oldexphalf[i];
      }
      if(n_frdmhalf[i]>tempmax){
         tempmax=n_frdmhalf[i];
      }
      if(n_ktuyhalf[i]>tempmax){
         tempmax=n_ktuyhalf[i];
      }
      if(n_borzhalf[i]>tempmax){
         tempmax=n_borzhalf[i];
      }
      if(n_newexphalf[i]<tempmin && n_newexphalf[i]>0){
         tempmin=n_newexphalf[i];
      }
      if(n_oldexphalf[i]<tempmin && n_oldexphalf[i]>0){
         tempmin=n_oldexphalf[i];
      }
      if(n_frdmhalf[i]<tempmin && n_frdmhalf[i]>0){
         tempmin=n_frdmhalf[i];
      }
      if(n_ktuyhalf[i]<tempmin && n_ktuyhalf[i]>0){
         tempmin=n_ktuyhalf[i];
      }
      if(n_borzhalf[i]<tempmin && n_borzhalf[i]>0){
         tempmin=n_borzhalf[i];
      }
      //cout<<tempmin<<", "<<tempmax<<endl;
   }
   hlmin=tempmin/2.0;
   hlmax=tempmax*2;
}

void plot_syshl(){

   TFile *RootFile = new TFile("root/root_histogram/hlsys_1.root","RECREATE");

   TGraphAsymmErrors *p_sys_oldexp; //array for different isotopes
   TGraphAsymmErrors *p_sys_newexp; //array for different isotopes
   TGraph *p_sys_frdm; //array for different isotopes
   TGraph *p_sys_ktuy; //array for different isotopes
   TGraph *p_sys_borz; //array for different isotopes
   TLegend *p_leg;

   TGraphAsymmErrors *n_sys_oldexp; //array for different isotopes
   TGraphAsymmErrors *n_sys_newexp; //array for different isotopes
   TGraph *n_sys_frdm; //array for different isotopes
   TGraph *n_sys_ktuy; //array for different isotopes
   TGraph *n_sys_borz; //array for different isotopes
   TLegend *n_leg;

   TCanvas *c01 = new TCanvas ("c01","c01",0,0,800,600);
   TCanvas *c02 = new TCanvas ("c02","c02",0,0,800,600);

   Double_t nmin, nmax;
   double hlmin, hlmax;
   read_data();
   /***************** half-life as a function of N by isotope *******************/
   find_boundryZ_nhl(nmin, nmax, hlmin, hlmax);
   if(p_dimiso==0){
      continue;
   }
   c01->cd();
   c01->cd()->SetGridx(0);
   c01->cd()->SetGridy(0);
   c01->cd()->SetTopMargin(0.02);
   c01->cd()->SetBottomMargin(0.15);
   c01->cd()->SetLeftMargin(0.15);
   c01->cd()->SetRightMargin(0.02);
   TString content1, content2;
   set_contentZ(28, content1, content2);
   p_sys_newexp = new TGraphAsymmErrors(p_dimiso,p_neutronnumnewexp,p_newexphalf,p_neutronerror,p_neutronerror,p_newexphalfL,p_newexphalfR);
   p_sys_oldexp = new TGraphAsymmErrors(p_dimiso,p_neutronnumoldexp,p_oldexphalf,p_neutronerror,p_neutronerror,p_oldexphalfL,p_oldexphalfR);
   p_sys_frdm = new TGraph(p_dimiso,p_neutronnumnewexp,p_frdmhalf);
   p_sys_frdm->SetLineColor(2);
   p_sys_ktuy = new TGraph(p_dimiso,p_neutronnumnewexp,p_ktuyhalf);
   p_sys_ktuy->SetLineColor(4);
   p_sys_borz = new TGraph(p_dimiso-1,&p_neutronnumnewexp[1],&p_borzhalf[1]);
   p_sys_borz->SetLineColor(6);
   TLatex text;
   text.SetTextAlign(12);
   text.SetTextSize(0.1);
   text.SetNDC(kTRUE);

   p_sys_frdm->GetXaxis()->SetLimits(nmin,nmax);
   p_sys_frdm->GetYaxis()->SetRangeUser(hlmin,hlmax);
   p_sys_frdm->SetTitle("");
   p_sys_frdm->GetXaxis()->SetTitle("Neutron number");
   p_sys_frdm->GetXaxis()->SetTitleOffset(0.85);
   p_sys_frdm->GetXaxis()->CenterTitle(1);
   p_sys_frdm->GetXaxis()->SetTitleSize(0.08);
   p_sys_frdm->GetXaxis()->SetLabelSize(0.08);
   p_sys_frdm->GetXaxis()->SetNdivisions((nmax-nmin+1)/2+1);
   p_sys_frdm->GetYaxis()->SetTitle("Half-life (ms)");
   p_sys_frdm->GetYaxis()->SetTitleOffset(0.85);
   p_sys_frdm->GetYaxis()->CenterTitle(1);
   p_sys_frdm->GetYaxis()->SetTitleSize(0.08);
   p_sys_frdm->GetYaxis()->SetLabelSize(0.08);
   p_sys_frdm->SetLineWidth(2);
   p_sys_ktuy->SetLineWidth(2);
   p_sys_borz->SetLineWidth(2);
   p_sys_frdm->Draw("AL");
   p_sys_ktuy->Draw("L");
   p_sys_borz->Draw("L");
   p_sys_oldexp->Draw("P");
   p_sys_newexp->Draw("P");

   text.DrawLatex(.3,.3,content1);
   gPad->SetLogy(1);

   p_sys_newexp->SetMarkerStyle(21);
   p_sys_newexp->SetMarkerSize(2);
   p_sys_oldexp->SetMarkerStyle(25);
   p_sys_oldexp->SetMarkerSize(2);

   p_leg = new TLegend(0.70,0.60,1.0,0.95,"");
   p_leg->AddEntry(p_sys_oldexp,"Previous work","P");
   p_leg->AddEntry(p_sys_newexp,"Present work","P");
   p_leg->AddEntry(p_sys_frdm,"FRDM+QRPA","L");
   p_leg->AddEntry(p_sys_ktuy,"KTUY+GT2","L");
   p_leg->AddEntry(p_sys_borz,"DF+CQRPA","L");
   p_leg->SetBorderSize(0);
   p_leg->SetFillColor(0);
   p_leg->SetFillStyle(0);
   p_leg->Draw();
   cout<<"c01 finished"<<endl;

   /***************** half-life as a function of Z by isotone *******************/
   find_boundryN_nhl(nmin, nmax, hlmin, hlmax);
   if(n_dimiso==0){
      continue;
   }
   c02->cd();
   c02->cd()->SetGridx(0);
   c02->cd()->SetGridy(0);
   c02->cd()->SetTopMargin(0.02);
   c02->cd()->SetBottomMargin(0.15);
   c02->cd()->SetLeftMargin(0.15);
   c02->cd()->SetRightMargin(0.02);
   TString content1, content2;
   set_contentN(50, content1, content2);
   n_sys_newexp = new TGraphAsymmErrors(n_dimiso-1,n_protonnumnewexp,n_newexphalf,n_protonerror,n_protonerror,n_newexphalfL,n_newexphalfR);
   n_sys_oldexp = new TGraphAsymmErrors(n_dimiso-1,n_protonnumoldexp,n_oldexphalf,n_protonerror,n_protonerror,n_oldexphalfL,n_oldexphalfR);
   n_sys_frdm = new TGraph(n_dimiso-1,n_protonnumnewexp,n_frdmhalf);
   n_sys_frdm->SetLineColor(2);
   n_sys_ktuy = new TGraph(n_dimiso-1,n_protonnumnewexp,n_ktuyhalf);
   n_sys_ktuy->SetLineColor(4);
   n_sys_borz = new TGraph(n_dimiso-3,n_protonnumnewexp,n_borzhalf);
   n_sys_borz->SetLineColor(6);
   TLatex text;
   text.SetTextAlign(12);
   text.SetTextSize(0.1);
   text.SetNDC(kTRUE);

   n_sys_frdm->GetXaxis()->SetLimits(nmin,nmax);
   n_sys_frdm->GetYaxis()->SetRangeUser(hlmin,hlmax);
   n_sys_frdm->SetTitle("");
   n_sys_frdm->GetXaxis()->SetTitle("Proton number");
   n_sys_frdm->GetXaxis()->SetTitleOffset(0.85);
   n_sys_frdm->GetXaxis()->CenterTitle(1);
   n_sys_frdm->GetXaxis()->SetTitleSize(0.08);
   n_sys_frdm->GetXaxis()->SetLabelSize(0.08);
   n_sys_frdm->GetXaxis()->SetNdivisions((nmax-nmin+1)/2+1);
   n_sys_frdm->GetYaxis()->SetTitle("Half-life (ms)");
   n_sys_frdm->GetYaxis()->SetTitleOffset(0.85);
   n_sys_frdm->GetYaxis()->CenterTitle(1);
   n_sys_frdm->GetYaxis()->SetTitleSize(0.08);
   n_sys_frdm->GetYaxis()->SetLabelSize(0.08);
   n_sys_frdm->SetLineWidth(2);
   n_sys_ktuy->SetLineWidth(2);
   n_sys_borz->SetLineWidth(2);
   n_sys_frdm->Draw("AL");
   n_sys_ktuy->Draw("L");
   n_sys_borz->Draw("L");
   n_sys_oldexp->Draw("P");
   n_sys_newexp->Draw("P");

   text.DrawLatex(.3,.85,content1);
   gPad->SetLogy(1);

   n_sys_newexp->SetMarkerStyle(21);
   n_sys_newexp->SetMarkerSize(2);
   n_sys_oldexp->SetMarkerStyle(25);
   n_sys_oldexp->SetMarkerSize(2);

   n_leg = new TLegend(0.7,0.15,1,0.6,"");
   n_leg->AddEntry(n_sys_newexp,"Present work","P");
   n_leg->AddEntry(n_sys_oldexp,"Previous work","P");
   n_leg->AddEntry(n_sys_frdm,"FRDM+QRPA","L");
   n_leg->AddEntry(n_sys_ktuy,"KTUY+GT2","L");
   n_leg->AddEntry(n_sys_borz,"Shell Model","L");
   n_leg->SetBorderSize(0);
   n_leg->SetFillColor(0);
   n_leg->SetFillStyle(0);
   n_leg->Draw();
   cout<<"c02 finished"<<endl;

   c01->Write();
   c02->Write();
   RootFile->Write();
   delete RootFile;
}
