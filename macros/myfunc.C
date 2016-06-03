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
#include"TTreePlayer.h"
#include"TH1.h"
#include"TH2.h"
#include"TCanvas.h"
#include<TSystem.h>
#include<TStyle.h>
#include <TCutG.h>
#include "RooAddPdf.h"

using namespace std;

void name_nuclei_latex(Int_t Z, Int_t Mass, TString &name){
   name +=" ^{";
   name +=Mass;
   switch(Z){
      case 25:
         name +="}Mn";
         break;
      case 26:
         name +="}Fe";
         break;
      case 27:
         name +="}Co";
         break;
      case 28:
         name +="}Ni";
         break;
      case 29:
         name +="}Cu";
         break;
      case 30:
         name +="}Zn";
         break;
      case 31:
         name +="}Ga";
         break;
      case 32:
         name +="}Ge";
         break;
      case 45:
         name +="}Rh";
         break;
      case 46:
         name +="}Pd";
         break;
      case 47:
         name +="}Ag";
         break;
      case 48:
         name +="}Cd";
         break;
      case 49:
         name +="}In";
         break;
      case 50:
         name +="}Sn";
         break;
   }
}

void name_nuclei(Int_t Z, Int_t Mass, TString &name){
   switch(Z){
      case 25:
         name +="mn";
         break;
      case 26:
         name +="fe";
         break;
      case 27:
         name +="co";
         break;
      case 28:
         name +="ni";
         break;
      case 29:
         name +="cu";
         break;
      case 30:
         name +="zn";
         break;
      case 31:
         name +="ga";
         break;
      case 32:
         name +="ge";
         break;
      case 33:
         name +="as";
         break;
      case 38:
         name +="sr";
         break;
      case 39:
         name +="y";
         break;
      case 40:
         name +="zr";
         break;
      case 41:
         name +="nb";
         break;
      case 42:
         name +="mo";
         break;
      case 43:
         name +="tc";
         break;
      case 44:
         name +="ru";
         break;
      case 45:
         name +="rh";
         break;
      case 46:
         name +="pd";
         break;
      case 47:
         name +="ag";
         break;
      case 48:
         name +="cd";
         break;
      case 49:
         name +="in";
         break;
      case 50:
         name +="sn";
         break;
      case 51:
         name +="sb";
         break;
      case 52:
         name +="te";
         break;
   }
   name += Mass;
}

Double_t EffFunc(Double_t *e, Double_t *p){
   if(e[0]<0){
      return 0;
   }
   Double_t term0 = p[0];
   Double_t term1 = p[1]*log(e[0]/1000);
   Double_t term2 = p[2]*TMath::Power(log(e[0]/1000),2);
   Double_t term3 = p[3]*TMath::Power(log(e[0]/1000),3);
   Double_t term4 = p[4]*TMath::Power(log(e[0]/1000),4);
   Double_t term5 = p[5]*TMath::Power(log(e[0]/1000),5);
   return exp(term0+term1+term2+term3+term4+term5);
   //return Exp(TMath::Power((TMath::Power(([1]+[1]*TMath::Log(x/100.)+[2]*TMath::Power(TMath::Log(x/100.),2))^(-[6])+([3]+[4]*TMath::Log(x/1000.)+[5]*TMath::Power(TMath::Log(x/1000.),2)),(-[6]))),(-1./[6])));
}

double CalEffFunc_Ni(double e){
   TF1 *effnoadd = new TF1 ("effnoadd",EffFunc,30,5000,6);
   TF1 *effadd = new TF1 ("effadd",EffFunc,30,5000,6);
   //TF1 *effnoadd = new TF1("effnoadd","TMath::Exp((([0]+[1]*TMath::Log(x/100.)+[2]*TMath::Log(x/100.)^2)^(-[6])+([3]+[4]*TMath::Log(x/1000.)+[5]*TMath::Log(x/1000.)^2)^(-[6]))^(-1./[6]))",35.,1420.);
   //TF1 *effadd = new TF1("effadd","TMath::Exp((([0]+[1]*TMath::Log(x/100.)+[2]*TMath::Log(x/100.)^2)^(-[6])+([3]+[4]*TMath::Log(x/1000.)+[5]*TMath::Log(x/1000.)^2)^(-[6]))^(-1./[6]))",35.,1420.);
   TGraphErrors *noadd = new TGraphErrors(18);
   TGraphErrors *add = new TGraphErrors(18);

   noadd->SetPoint( 0,45.7500,3.754);
   noadd->SetPoint( 1,121.780,14.44);
   noadd->SetPoint( 2,244.690,13.76);
   noadd->SetPoint( 3,344.280,11.10);
   noadd->SetPoint( 4,411.120,10.46);
   noadd->SetPoint( 5,444.000,9.845);
   noadd->SetPoint( 6,778.900,7.104);
   noadd->SetPoint( 7,867.380,6.769);
   noadd->SetPoint( 8,964.130,6.281);
   noadd->SetPoint( 9,1112.12,5.972);
   noadd->SetPoint(10,1212.95,5.543);
   noadd->SetPoint(11,1299.14,5.285);
   noadd->SetPoint(12,1408.01,5.137);
   noadd->SetPoint(13,80.9979,12.87);
   noadd->SetPoint(14,276.399,12.39);
   noadd->SetPoint(15,302.851,11.38);
   noadd->SetPoint(16,356.013,10.25);
   noadd->SetPoint(17,383.849,10.15);
   noadd->SetPointError( 0, 0,0.063);
   noadd->SetPointError( 1, 0, 0.22);
   noadd->SetPointError( 2, 0, 0.21);
   noadd->SetPointError( 3, 0, 0.17);
   noadd->SetPointError( 4, 0, 0.16);
   noadd->SetPointError( 5, 0,0.152);
   noadd->SetPointError( 6, 0,0.109);
   noadd->SetPointError( 7, 0,0.011);
   noadd->SetPointError( 8, 0,0.097);
   noadd->SetPointError( 9, 0,0.092);
   noadd->SetPointError(10, 0,0.087);
   noadd->SetPointError(11, 0,0.084);
   noadd->SetPointError(12, 0,0.082);
   noadd->SetPointError(13, 0, 0.22);
   noadd->SetPointError(14, 0, 0.19);
   noadd->SetPointError(15, 0, 0.17);
   noadd->SetPointError(16, 0, 0.16);
   noadd->SetPointError(17, 0, 0.16);

   add->SetPoint( 0,45.7500,3.754);
   add->SetPoint( 1,121.780,14.00);
   add->SetPoint( 2,244.690,14.22);
   add->SetPoint( 3,344.280,12.59);
   add->SetPoint( 4,411.120,11.71);
   add->SetPoint( 5,444.000,11.23);
   add->SetPoint( 6,778.900,9.020);
   add->SetPoint( 7,867.380,8.559);
   add->SetPoint( 8,964.130,8.145);
   add->SetPoint( 9,1112.12,7.941);
   add->SetPoint(10,1212.95,7.269);
   add->SetPoint(11,1299.14,7.032);
   add->SetPoint(12,1408.01,6.943);
   add->SetPoint(13,80.9979,12.64);
   add->SetPoint(14,276.399,13.43);
   add->SetPoint(15,302.851,12.66);
   add->SetPoint(16,356.013,11.79);
   add->SetPoint(17,383.849,11.87);
   add->SetPointError( 0, 0,0.062);
   add->SetPointError( 1, 0, 0.22);
   add->SetPointError( 2, 0, 0.22);
   add->SetPointError( 3, 0, 0.19);
   add->SetPointError( 4, 0, 0.18);
   add->SetPointError( 5, 0, 0.17);
   add->SetPointError( 6, 0,0.139);
   add->SetPointError( 7, 0,0.017);
   add->SetPointError( 8, 0,0.125);
   add->SetPointError( 9, 0,0.123);
   add->SetPointError(10, 0,0.114);
   add->SetPointError(11, 0,0.112);
   add->SetPointError(12, 0,0.109);
   add->SetPointError(13, 0, 0.22);
   add->SetPointError(14, 0, 0.21);
   add->SetPointError(15, 0, 0.20);
   add->SetPointError(16, 0, 0.18);
   add->SetPointError(17, 0, 0.19);

   effnoadd->SetParameter(0,1);
   effnoadd->SetParameter(1,1);
   effnoadd->SetParameter(2,1);
   effnoadd->SetParameter(3,1);
   effnoadd->SetParameter(4,1);
   effnoadd->SetParameter(5,1);
   effnoadd->SetParameter(6,1);
   effadd->SetParameter(0,1);
   effadd->SetParameter(1,1);
   effadd->SetParameter(2,1);
   effadd->SetParameter(3,1);
   effadd->SetParameter(4,1);
   effadd->SetParameter(5,1);
   effadd->SetParameter(6,1);
   TCanvas *c1 = new TCanvas("c1","c1",0,0,600,400);
   //c1->Divide(1,2);
   //c1->cd(1);
   //gStyle->SetOptStat(0);
   //gStyle->SetOptFit(0);
   effadd->SetLineColor(kRed);
   effnoadd->SetLineColor(kBlue);
   noadd->SetMarkerStyle(24);
   noadd->SetTitle("Clusters total efficiency curve");
   noadd->Draw("ap");
   noadd->GetXaxis()->SetTitle("Energy (keV)");
   noadd->GetXaxis()->CenterTitle(1);
   noadd->GetXaxis()->SetTitleSize(0.05);
   noadd->GetYaxis()->SetTitle("Efficiency (%)");
   noadd->GetYaxis()->CenterTitle(1);
   noadd->GetYaxis()->SetTitleSize(0.05);
   //c1->cd(2);
   add->SetMarkerStyle(26);
   add->Draw("p");
   noadd->Fit("effnoadd","WR");
   add->Fit("effadd","WR");
   gStyle->SetLegendBorderSize(0);
   gStyle->SetLegendFillColor(0);
   TLegend *leg = new TLegend(0.55,0.55,0.8,0.8,"");
   leg->AddEntry(effnoadd,"without addback","L");
   leg->AddEntry(effadd,"with addback","L");
   leg->SetBorderSize(1);
   leg->SetFillColor(0);
   leg->Draw();
   Double_t energy[1];
   energy[0]=e;
   cout<<"eff w/o addback = "<<effnoadd->Eval(e)<<endl;
   cout<<"eff w addback = "<<effadd->Eval(e)<<endl;
   return 1;
}

double CalEffFunc_Cu(double e){
   //TF1 *effnoadd = new TF1 ("effnoadd",EffFunc,30,5000,6);
   //TF1 *effadd = new TF1 ("effadd",EffFunc,30,5000,6);
   TF1 *effnoadd = new TF1("effnoadd","TMath::Exp((([0]+[1]*TMath::Log(x/100.)+[2]*TMath::Log(x/100.)^2)^(-[6])+([3]+[4]*TMath::Log(x/1000.)+[5]*TMath::Log(x/1000.)^2)^(-[6]))^(-1./[6]))",35.,1420.);
   TF1 *effadd = new TF1("effadd","TMath::Exp((([0]+[1]*TMath::Log(x/100.)+[2]*TMath::Log(x/100.)^2)^(-[6])+([3]+[4]*TMath::Log(x/1000.)+[5]*TMath::Log(x/1000.)^2)^(-[6]))^(-1./[6]))",35.,1420.);
   TGraphErrors *noadd = new TGraphErrors(18);
   TGraphErrors *add = new TGraphErrors(18);

   noadd->SetPoint( 0,45.7500,5.129);
   noadd->SetPoint( 1,121.780,16.52);
   noadd->SetPoint( 2,244.690,15.25);
   noadd->SetPoint( 3,344.280,12.23);
   noadd->SetPoint( 4,411.120,11.37);
   noadd->SetPoint( 5,444.000,10.74);
   noadd->SetPoint( 6,778.900,7.635);
   noadd->SetPoint( 7,867.380,7.275);
   noadd->SetPoint( 8,964.130,6.701);
   noadd->SetPoint( 9,1112.12,6.373);
   noadd->SetPoint(10,1212.95,5.875);
   noadd->SetPoint(11,1299.14,5.576);
   noadd->SetPoint(12,1408.01,5.448);
   noadd->SetPoint(13,80.9979,15.53);
   noadd->SetPoint(14,276.399,13.87);
   noadd->SetPoint(15,302.851,12.76);
   noadd->SetPoint(16,356.013,11.48);
   noadd->SetPoint(17,383.849,11.27);
   noadd->SetPointError( 0, 0,0.082);
   noadd->SetPointError( 1, 0, 0.25);
   noadd->SetPointError( 2, 0, 0.23);
   noadd->SetPointError( 3, 0, 0.19);
   noadd->SetPointError( 4, 0, 0.17);
   noadd->SetPointError( 5, 0, 0.16);
   noadd->SetPointError( 6, 0,0.116);
   noadd->SetPointError( 7, 0,0.012);
   noadd->SetPointError( 8, 0,0.102);
   noadd->SetPointError( 9, 0,0.098);
   noadd->SetPointError(10, 0,0.092);
   noadd->SetPointError(11, 0,0.089);
   noadd->SetPointError(12, 0,0.087);
   noadd->SetPointError(13, 0, 0.26);
   noadd->SetPointError(14, 0, 0.21);
   noadd->SetPointError(15, 0, 0.19);
   noadd->SetPointError(16, 0, 0.17);
   noadd->SetPointError(17, 0, 0.17);

   add->SetPoint( 0,45.7500,5.095);
   add->SetPoint( 1,121.780,15.99);
   add->SetPoint( 2,244.690,15.73);
   add->SetPoint( 3,344.280,13.85);
   add->SetPoint( 4,411.120,12.73);
   add->SetPoint( 5,444.000,12.20);
   add->SetPoint( 6,778.900,9.684);
   add->SetPoint( 7,867.380,9.149);
   add->SetPoint( 8,964.130,8.657);
   add->SetPoint( 9,1112.12,8.443);
   add->SetPoint(10,1212.95,7.670);
   add->SetPoint(11,1299.14,7.407);
   add->SetPoint(12,1408.01,7.338);
   add->SetPoint(13,80.9979,15.25);
   add->SetPoint(14,276.399,15.05);
   add->SetPoint(15,302.851,14.21);
   add->SetPoint(16,356.013,13.21);
   add->SetPoint(17,383.849,13.22);
   add->SetPointError( 0, 0,0.081);
   add->SetPointError( 1, 0, 0.24);
   add->SetPointError( 2, 0, 0.23);
   add->SetPointError( 3, 0, 0.21);
   add->SetPointError( 4, 0, 0.19);
   add->SetPointError( 5, 0, 0.19);
   add->SetPointError( 6, 0,0.148);
   add->SetPointError( 7, 0,0.020);
   add->SetPointError( 8, 0,0.132);
   add->SetPointError( 9, 0,0.130);
   add->SetPointError(10, 0,0.120);
   add->SetPointError(11, 0,0.118);
   add->SetPointError(12, 0,0.116);
   add->SetPointError(13, 0, 0.25);
   add->SetPointError(14, 0, 0.23);
   add->SetPointError(15, 0, 0.22);
   add->SetPointError(16, 0, 0.20);
   add->SetPointError(17, 0, 0.20);

   effnoadd->SetParameter(0,1);
   effnoadd->SetParameter(1,1);
   effnoadd->SetParameter(2,1);
   effnoadd->SetParameter(3,1);
   effnoadd->SetParameter(4,1);
   effnoadd->SetParameter(5,1);
   effnoadd->SetParameter(6,1);
   effadd->SetParameter(0,1);
   effadd->SetParameter(1,1);
   effadd->SetParameter(2,1);
   effadd->SetParameter(3,1);
   effadd->SetParameter(4,1);
   effadd->SetParameter(5,1);
   effadd->SetParameter(6,1);
   TCanvas *c1 = new TCanvas("c1","c1",0,0,600,400);
   //c1->Divide(1,2);
   //c1->cd(1);
   //gStyle->SetOptStat(0);
   //gStyle->SetOptFit(0);
   effadd->SetLineColor(kRed);
   effnoadd->SetLineColor(kBlue);
   noadd->SetMarkerStyle(24);
   noadd->SetTitle("Clusters total efficiency curve");
   noadd->Draw("ap");
   noadd->GetXaxis()->SetTitle("Energy (keV)");
   noadd->GetXaxis()->CenterTitle(1);
   noadd->GetXaxis()->SetTitleSize(0.05);
   noadd->GetYaxis()->SetTitle("Efficiency (%)");
   noadd->GetYaxis()->CenterTitle(1);
   noadd->GetYaxis()->SetTitleSize(0.05);
   //c1->cd(2);
   add->SetMarkerStyle(26);
   add->Draw("p");
   noadd->Fit("effnoadd","R");
   add->Fit("effadd","R");
   gStyle->SetLegendBorderSize(0);
   gStyle->SetLegendFillColor(0);
   TLegend *leg = new TLegend(0.55,0.55,0.8,0.8,"");
   leg->AddEntry(effnoadd,"without addback","L");
   leg->AddEntry(effadd,"with addback","L");
   leg->SetBorderSize(1);
   leg->SetFillColor(0);
   leg->Draw();
   Double_t energy[1];
   energy[0]=e;
   cout<<"eff w/o addback = "<<effnoadd->EvalPar(energy)<<endl;
   cout<<"eff w addback = "<<effadd->EvalPar(energy)<<endl;
   return 1;
}

Double_t checkgceff(Double_t e){
   Double_t E[1];
   Double_t P[6];
   E[0] = e;
   P[0] = 1.80209;
   P[1] = -0.594968;
   P[2] = 0.372692;
   P[3] = 0.526879;
   P[4] = 0.237956;
   P[5] = 0.0426089;
   return EffFunc(E,P)/100.0;
}

Double_t checkabeff(Double_t e){
   Double_t E[1];
   Double_t P[6];
   E[0] = e;
   P[0] = 2.07623;
   P[1] = -0.467005;
   P[2] = 0.126584;
   P[3] = 0.318022;
   P[4] = 0.183034;
   P[5] = 0.0379146;
   return EffFunc(E,P)/100.0;
}
Double_t check_depth_beta(Int_t Z, Int_t A, TString cut="", Float_t beta_l=0.6, Float_t beta_r=0.7){
   Int_t beta_bin = (beta_r-beta_l)*10000;
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,800,500);
   c1->SetRightMargin(0.06);
   c1->SetTopMargin(0.06);
   c1->SetLeftMargin(0.14);
   c1->SetBottomMargin(0.14);
   c1->SetGridx(0);
   c1->SetGridy(0);
   c1->SetLogz(1);
   c1->Draw();
   TString name;
   TString nuclei="gc_E>0&&";
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }
   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;

   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH2F *h1 = new TH2F("h1","",beta_bin,beta_l,beta_r,8,0,8);
   h1->SetStats(0);
   h1->GetXaxis()->SetTitle("Velocity (beta)");
   h1->GetXaxis()->SetLabelSize(0.06);
   h1->GetXaxis()->SetTitleSize(0.07);
   h1->GetYaxis()->SetTitle("Depth (mm)");
   h1->GetYaxis()->SetLabelSize(0.06);
   h1->GetYaxis()->SetTitleSize(0.07);
   decay_tree->Draw("z:beta711>>h1",nuclei+cut);
   h1->Draw("col");
   //TLatex text1;
   //TString content1, content0;
   //content0 +="Depth of";
   //name_nuclei_latex(Z,A,content1);
   //content0 +=content1;
   //text1.SetTextAlign(12);
   //text1.SetTextSize(0.08);
   //text1.SetNDC(kTRUE);
   //text1.DrawLatex(.6,.88,content0);
   TCanvas *c2 = new TCanvas("c2","c2",0,0,800,800);
   TH1F *h2 = new TH1F("h2","",8,0,8);
   TH1F *h3[8];
   c2->Divide(3,3);
   for(int i==0; i<9; i++){
      c2->cd(i+1);
      if(i==0){
         decay_tree->Draw("z>>h2",nuclei+cut);
         c2->cd(i+1)->SetBottomMargin(0.15);
         c2->cd(i+1)->SetGridx(0);
         c2->cd(i+1)->SetGridy(0);
         h2->SetStats(0);
         h2->GetYaxis()->SetLabelSize(0.06);
         h2->GetXaxis()->SetTitle("Depth (mm)");
         h2->GetXaxis()->CenterTitle(1);
         h2->GetXaxis()->SetLabelSize(0.06);
         h2->GetXaxis()->SetTitleSize(0.06);
         h2->Draw();
         TLatex text1;
         TString content1;
         name_nuclei_latex(Z,A,content1);
         text1.SetTextAlign(12);
         text1.SetTextSize(0.08);
         text1.SetNDC(kTRUE);
         text1.DrawLatex(.2,.8,content1);
      }else{
         c2->cd(i+1)->SetLogy(1);
         c2->cd(i+1)->SetGridx(0);
         c2->cd(i+1)->SetGridy(0);
         char histoname[80];
         sprintf(histoname,"dssd%d",i);
         h3[i-1]=new TH1F(histoname,"",beta_bin,beta_l,beta_r);
         h3[i-1]->SetStats(0);
         TString depth="z==";
         depth+=i-1;
         depth=And+depth;
         decay_tree->Project(histoname,"beta711",nuclei+cut+depth);
         if(i>=6){
            c2->cd(i+1)->SetBottomMargin(0.15);
            h3[i-1]->SetStats(0);
            h3[i-1]->GetXaxis()->SetTitle("Velocity (beta)");
            h3[i-1]->GetXaxis()->CenterTitle(1);
            h3[i-1]->GetXaxis()->SetTitleSize(0.06);
            h3[i-1]->GetXaxis()->SetLabelSize(0.06);
         }
         h3[i-1]->GetYaxis()->SetLabelSize(0.06);
         h3[i-1]->GetXaxis()->SetNdivisions(5);
         h3[i-1]->GetXaxis()->SetLabelSize(0.06);
         h3[i-1]->Draw();
         TLatex text1;
         TString content0;
         content0 +="dssd #";
         content0 +=i;
         text1.SetTextAlign(12);
         text1.SetTextSize(0.08);
         text1.SetNDC(kTRUE);
         text1.DrawLatex(.2,.8,content0);
      }
   }
}

Double_t check_depth(Int_t Z, Int_t A, TString cut=""){
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,500);
   c1->SetRightMargin(0.02);
   c1->SetTopMargin(0.06);
   c1->SetLeftMargin(0.14);
   c1->SetBottomMargin(0.14);
   c1->SetGridx(0);
   c1->SetGridy(0);
   c1->Draw();
   TString name;
   TString nuclei="gc_E>0&&";
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }
   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;
   //if(gROOT->FindObject(name)!=0){
   //   nuclei="("+nuclei;
   //   nuclei=nuclei+OR+name;
   //   nuclei=nuclei+")";
   //}

   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH1F *h1 = new TH1F("h1","",8,0,8);
   h1->SetStats(0);
   h1->GetXaxis()->SetTitle("Depth (mm)");
   h1->GetXaxis()->SetLabelSize(0.06);
   h1->GetXaxis()->SetTitleSize(0.07);
   h1->GetYaxis()->SetTitle("Counts / mm");
   h1->GetYaxis()->SetLabelSize(0.06);
   h1->GetYaxis()->SetTitleSize(0.07);
   decay_tree->Draw("z>>h1",nuclei+cut);
   h1->Draw();
   TLatex text1;
   TString content1, content0;
   content0 +="Depth of";
   name_nuclei_latex(Z,A,content1);
   content0 +=content1;
   text1.SetTextAlign(12);
   text1.SetTextSize(0.08);
   text1.SetNDC(kTRUE);
   text1.DrawLatex(.6,.88,content0);
}

void checkpid(Int_t zlow = 24, Int_t zhigh = 34, TString cut="", TString option="colz"){
   Int_t zbinnum = 100*(zhigh - zlow);
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,800,500);
   c1->Draw();
   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH2F *h1 = new TH2F("h1","Preliminary Particle Identification",300,2.6,2.9,zbinnum,zlow,zhigh);
   h1->GetXaxis()->SetTitle("Mass-to-charge ratio (A/Q)");
   h1->GetXaxis()->CenterTitle(1);
   h1->GetXaxis()->SetTitleSize(0.05);
   h1->GetXaxis()->SetLabelSize(0.05);
   h1->GetYaxis()->SetTitle("Atomic number (Z)");
   h1->GetYaxis()->CenterTitle(1);
   h1->GetYaxis()->SetTitleSize(0.05);
   h1->GetYaxis()->SetLabelSize(0.05);
   h1->SetStats(0);
   c1->SetGridx(0);
   c1->SetGridy(0);
   decay_tree->Draw("zed:aoq37>>h1",cut,option);
}

void checkgcE(Int_t Z, Int_t A, TString cut="", TString option="", Int_t elow=0, Int_t ehigh=2000){
   Int_t binnum = ehigh - elow;
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,1200,500);
   c1->Draw();
   TString name;
   TString nuclei="gc_E>0&&";
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }

   name_nuclei(Z,A,name);

   Zed+=Z;
   Mass+=A;
   nuclei+=Mass+Zed;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+And+name;
      nuclei=nuclei+")";
   }

   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH1F *h1 = new TH1F("h1",name,binnum,elow,ehigh);
   decay_tree->Draw("gc_E>>h1",nuclei+cut,option);
   h1->Draw(option);
}

void checkgcEbg(Int_t Z, Int_t A, TString cut="", TString option="", Int_t elow=0, Int_t ehigh=2000){
   Int_t binnum = ehigh - elow;
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,1200,500);
   c1->Draw();
   TString name;
   TString nuclei="gc_E>0&&";
   TString nonuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString noZed="Zed!=";
   TString noMass="&&Mass!=";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }

   name_nuclei(Z,A,name);

   Zed+=Z;
   Mass+=A;
   nuclei+=Mass+Zed;
   noZed+=Z;
   noMass+=A;
   nonuclei=noZed+noMass;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+OR+name;
      nuclei=nuclei+")";
   }

   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH1F *h1 = new TH1F("h1",name,binnum,elow,ehigh);
   if(gROOT->FindObject("h2")!=0){
      h2->Delete();
   }
   TH1F *h2 = new TH1F("h2",name,binnum,elow,ehigh);
   if(gROOT->FindObject("h3")!=0){
      h3->Delete();
   }
   TH1F *h3 = new TH1F("h3",name,binnum,elow,ehigh);
   Double_t num_iso, num_all;
   num_iso = (Double_t) decay_tree->Draw("gc_E>>h1",nuclei+cut,option);
   num_all = (Double_t) decay_tree->Draw("gc_E>>h2",nonuclei+cut,option);
   h2->Scale(num_iso/num_all);
   h3->Add(h1,1);
   h3->Add(h2,-1);
   h3->GetYaxis()->SetRangeUser(0,1.1*h3->GetBinContent(h3->GetMaximumBin()));
   h1->SetLineColor(kBlack);
   h3->SetLineColor(kRed);
   h1->Draw(option);
   h3->Draw("same");
}

void checkabE(Int_t Z, Int_t A, TString cut="", TString option="", Int_t elow=0, Int_t ehigh=2000){
   Int_t binnum = ehigh - elow;
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,600,600);
   c1->SetRightMargin(0.06);
   c1->SetTopMargin(0.06);
   c1->SetLeftMargin(0.14);
   c1->SetBottomMargin(0.14);
   c1->SetGridx(0);
   c1->SetGridy(0);
   c1->Draw();
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }

   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+OR+name;
      nuclei=nuclei+")";
   }

   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH1F *h1 = new TH1F("h1","",binnum,elow,ehigh);
   h1->SetStats(0);
   h1->GetXaxis()->SetTitle("E (keV)");
   h1->GetXaxis()->SetLabelSize(0.07);
   h1->GetXaxis()->SetTitleSize(0.07);
   h1->GetYaxis()->SetTitle("Counts / keV");
   h1->GetYaxis()->SetLabelSize(0.07);
   h1->GetYaxis()->SetTitleSize(0.07);
   decay_tree->Draw("ab_E>>h1",nuclei+cut,option);
   h1->Draw(option);
   TLatex text1;
   TString content1, content0;
   content0 +="#beta-delayed #gamma-ray of";
   name_nuclei_latex(Z,A,content1);
   content0 +=content1;
   text1.SetTextAlign(12);
   text1.SetTextSize(0.08);
   text1.SetNDC(kTRUE);
   text1.DrawLatex(.6,.88,content1);
}

void checkabEbg(Int_t Z, Int_t A, TString cut="", TString option="", Int_t elow=0, Int_t ehigh=2000){
   Int_t binnum = ehigh - elow;
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,1200,500);
   c1->Draw();
   TString name;
   TString nuclei;
   TString nonuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString noZed="Zed!=";
   TString noMass="&&Mass!=";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }

   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;
   noZed+=Z;
   noMass+=A;
   nonuclei=noZed+noMass;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+OR+name;
      nuclei=nuclei+")";
   }

   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH1F *h1 = new TH1F("h1",name,binnum,elow,ehigh);
   if(gROOT->FindObject("h2")!=0){
      h2->Delete();
   }
   TH1F *h2 = new TH1F("h2",name,binnum,elow,ehigh);
   if(gROOT->FindObject("h3")!=0){
      h3->Delete();
   }
   TH1F *h3 = new TH1F("h3",name,binnum,elow,ehigh);
   Double_t num_iso, num_all;
   num_iso = (Double_t) decay_tree->Draw("ab_E>>h1",nuclei+cut,option);
   num_all = (Double_t) decay_tree->Draw("ab_E>>h2",nonuclei+cut,option);
   h2->Scale(num_iso/num_all);
   h3->Add(h1,1);
   h3->Add(h2,-1);
   h3->GetYaxis()->SetRangeUser(0,1.1*h3->GetBinContent(h3->GetMaximumBin()));
   h1->SetLineColor(kBlack);
   h3->SetLineColor(kRed);
   h1->Draw(option);
   h3->Draw("same");
}

void checkgcET(Int_t Z, Int_t A, TString cut="", TString option="colz", Int_t elow=0, Int_t ehigh=2000, Int_t tlow=-4000, Int_t thigh=1000){
   Int_t ebinnum = ehigh - elow;
   Int_t tbinnum = thigh - tlow;
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,800);
   c1->Draw();
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }

   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+OR+name;
      nuclei=nuclei+")";
   }

   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH2F *h1 = new TH2F("h1",name,tbinnum,tlow,thigh,ebinnum,elow,ehigh);
   gStyle->SetOptStat(0);
   c1->cd()->SetLogz(0);
   decay_tree->Draw("gc_E:gc_T>>h1",nuclei+cut,option);
}

void checkabET(Int_t Z, Int_t A, TString cut="", TString option="colz", Int_t elow=0, Int_t ehigh=2000, Int_t tlow=-4000, Int_t thigh=1000){
   Int_t ebinnum = ehigh - elow;
   Int_t tbinnum = thigh - tlow;
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,800);
   c1->Draw();
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }

   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+OR+name;
      nuclei=nuclei+")";
   }

   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH2F *h1 = new TH2F("h1",name,tbinnum,tlow,thigh,ebinnum,elow,ehigh);
   gStyle->SetOptStat(0);
   c1->cd()->SetLogz(0);
   decay_tree->Draw("ab_E:ab_T>>h1",nuclei+cut,option);
}

void checkgcEE(Int_t Z, Int_t A, Int_t e1, Int_t e2, TString cut="", TString option="", Int_t elow=0, Int_t ehigh=2000){
   Int_t ebinnum = ehigh - elow;
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,1200,800);
   c1->Divide(1,2);
   c1->Draw();
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }

   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+OR+name;
      nuclei=nuclei+")";
   }

   Int_t ew = e2-e1;
   Int_t el1=e1-ew;
   Int_t el2=e1;
   Int_t er1=e2;
   Int_t er2=e2+ew;

   TString ggconst="&&gc1_E!=gc2_E";
   //TString ggtime="&&abs(gc1_T-gc2_T)<250";
   TString ggtime="";
   TString gateon=", gate on ";
   /**** background left ****/
   TString ggl1="&&gc1_E>";
   ggl1+=el1;
   TString ggl2="&&gc1_E<";
   ggl2+=el2;
   TString ggl=ggl1+ggl2+ggconst+ggtime;

   /**** for real peak ****/
   TString gg1="&&gc1_E>";
   gg1+=e1;
   TString gg2="&&gc1_E<";
   gg2+=e2;
   TString gg=gg1+gg2+ggconst+ggtime;

   /**** background right ****/
   TString ggr1="&&gc1_E>";
   ggr1+=er1;
   TString ggr2="&&gc1_E<";
   ggr2+=er2;
   TString ggr=ggr1+ggr2+ggconst+ggtime;
   gateon+=(e1+e2)/2;
   gateon+=" keV";

   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH1F *h1 = new TH1F("h1",name+gateon,ebinnum,elow,ehigh);
   if(gROOT->FindObject("h2")!=0){
      h2->Delete();
   }
   TH1F *h2 = new TH1F("h2",name,ebinnum,elow,ehigh);
   if(gROOT->FindObject("h3")!=0){
      h3->Delete();
   }
   TH1F *h3 = new TH1F("h3",name,ebinnum,elow,ehigh);
   if(gROOT->FindObject("h4")!=0){
      h4->Delete();
   }
   TH1F *h4 = new TH1F("h4",name,ebinnum,elow,ehigh);

   c1->cd(1);
   decay_tree->Draw("gc2_E>>h1",nuclei+cut+gg,option);
   decay_tree->Draw("gc_E>>h4",nuclei+cut,option);
   decay_tree->Draw("gc2_E>>h2",nuclei+cut+ggl,option);
   decay_tree->Draw("gc2_E>>h3",nuclei+cut+ggr,option);
   h2->Add(h3,1);
   h1->Add(h2,-0.5);
   h1->GetYaxis()->SetRangeUser(0,1.1*h1->GetBinContent(h1->GetMaximumBin()));
   h1->Draw(option);
   c1->cd(2);
   h4->Draw(option);
   c1->Update();
}

void checkgcEEl(Int_t Z, Int_t A, Int_t e1, Int_t e2, TString cut="", TString option="", Int_t elow=0, Int_t ehigh=2000){
   Int_t ebinnum = ehigh - elow;
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,1200,800);
   c1->Divide(1,2);
   c1->Draw();
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }

   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+OR+name;
      nuclei=nuclei+")";
   }

   Int_t ew = e2-e1;
   Int_t el1=e1-ew;
   Int_t el2=e1;
   Int_t er1=e2;
   Int_t er2=e2+ew;

   TString ggconst="&&gc1_E!=gc2_E";
   //TString ggtime="&&abs(gc1_T-gc2_T)<250";
   TString ggtime="";
   TString gateon=", gate on ";
   /**** background left ****/
   TString ggl1="&&gc1_E>";
   ggl1+=el1;
   TString ggl2="&&gc1_E<";
   ggl2+=el2;
   TString ggl=ggl1+ggl2+ggconst+ggtime;

   /**** for real peak ****/
   TString gg1="&&gc1_E>";
   gg1+=e1;
   TString gg2="&&gc1_E<";
   gg2+=e2;
   TString gg=gg1+gg2+ggconst+ggtime;

   /**** background right ****/
   TString ggr1="&&gc1_E>";
   ggr1+=er1;
   TString ggr2="&&gc1_E<";
   ggr2+=er2;
   TString ggr=ggr1+ggr2+ggconst+ggtime;
   gateon+=(e1+e2)/2;
   gateon+=" keV";

   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH1F *h1 = new TH1F("h1",name+gateon,ebinnum,elow,ehigh);
   if(gROOT->FindObject("h2")!=0){
      h2->Delete();
   }
   TH1F *h2 = new TH1F("h2",name,ebinnum,elow,ehigh);
   //if(gROOT->FindObject("h3")!=0){
   //   h3->Delete();
   //}
   //TH1F *h3 = new TH1F("h3",name,ebinnum,elow,ehigh);
   if(gROOT->FindObject("h4")!=0){
      h4->Delete();
   }
   TH1F *h4 = new TH1F("h4",name,ebinnum,elow,ehigh);

   c1->cd(1);
   decay_tree->Draw("gc2_E>>h1",nuclei+cut+gg,option);
   decay_tree->Draw("gc_E>>h4",nuclei+cut,option);
   decay_tree->Draw("gc2_E>>h2",nuclei+cut+ggl,option);
   //decay_tree->Draw("gc2_E>>h3",nuclei+cut+ggr,option);
   //h2->Add(h3,1);
   h1->Add(h2,-1);
   h1->GetYaxis()->SetRangeUser(0,1.1*h1->GetBinContent(h1->GetMaximumBin()));
   h1->Draw(option);
   c1->cd(2);
   h4->Draw(option);
   c1->Update();
}

void checkgcEEr(Int_t Z, Int_t A, Int_t e1, Int_t e2, TString cut="", TString option="", Int_t elow=0, Int_t ehigh=2000){
   Int_t ebinnum = ehigh - elow;
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,1200,800);
   c1->Divide(1,2);
   c1->Draw();
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }

   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+OR+name;
      nuclei=nuclei+")";
   }

   Int_t ew = e2-e1;
   Int_t el1=e1-ew;
   Int_t el2=e1;
   Int_t er1=e2;
   Int_t er2=e2+ew;

   TString ggconst="&&gc1_E!=gc2_E";
   TString ggtime="";
   //TString ggtime="&&abs(gc1_T-gc2_T)<250";
   TString gateon=", gate on ";
   /**** background left ****/
   TString ggl1="&&gc1_E>";
   ggl1+=el1;
   TString ggl2="&&gc1_E<";
   ggl2+=el2;
   TString ggl=ggl1+ggl2+ggconst+ggtime;

   /**** for real peak ****/
   TString gg1="&&gc1_E>";
   gg1+=e1;
   TString gg2="&&gc1_E<";
   gg2+=e2;
   TString gg=gg1+gg2+ggconst+ggtime;

   /**** background right ****/
   TString ggr1="&&gc1_E>";
   ggr1+=er1;
   TString ggr2="&&gc1_E<";
   ggr2+=er2;
   TString ggr=ggr1+ggr2+ggconst+ggtime;
   gateon+=(e1+e2)/2;
   gateon+=" keV";

   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH1F *h1 = new TH1F("h1",name+gateon,ebinnum,elow,ehigh);
   //if(gROOT->FindObject("h2")!=0){
   //   h2->Delete();
   //}
   //TH1F *h2 = new TH1F("h2",name,ebinnum,elow,ehigh);
   if(gROOT->FindObject("h3")!=0){
      h3->Delete();
   }
   TH1F *h3 = new TH1F("h3",name,ebinnum,elow,ehigh);
   if(gROOT->FindObject("h4")!=0){
      h4->Delete();
   }
   TH1F *h4 = new TH1F("h4",name,ebinnum,elow,ehigh);

   c1->cd(1);
   decay_tree->Draw("gc2_E>>h1",nuclei+cut+gg,option);
   decay_tree->Draw("gc_E>>h4",nuclei+cut,option);
   //decay_tree->Draw("gc2_E>>h2",nuclei+cut+ggl,option);
   decay_tree->Draw("gc2_E>>h3",nuclei+cut+ggr,option);
   //h2->Add(h3,1);
   h1->Add(h3,-1);
   h1->GetYaxis()->SetRangeUser(0,1.1*h1->GetBinContent(h1->GetMaximumBin()));
   h1->Draw(option);
   c1->cd(2);
   h4->Draw(option);
   c1->Update();
}

void checkabEE(Int_t Z, Int_t A, Int_t e1, Int_t e2, TString cut="", TString cut2="", TString option="", Int_t elow=0, Int_t ehigh=2000){
   Int_t ebinnum = ehigh - elow;
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,1200,800);
   c1->Divide(1,2);
   c1->Draw();
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }
   if(cut2.Sizeof()>1){
      cut2=And+cut2;
   }

   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+OR+name;
      nuclei=nuclei+")";
   }

   Int_t ew = e2-e1;
   Int_t el1=e1-ew;
   Int_t el2=e1;
   Int_t er1=e2;
   Int_t er2=e2+ew;

   TString ggconst="&&ab1_E!=ab2_E";
   TString unfold="&&ab1_E==ab2_E";
   //TString ggtime="&&abs(ab1_T-ab2_T)<250";
   TString ggtime="";
   TString gateon=", gate on ";
   /**** background left ****/
   TString ggl1="&&ab1_E>";
   ggl1+=el1;
   TString ggl2="&&ab1_E<";
   ggl2+=el2;
   TString ggl=ggl1+ggl2+ggconst+ggtime;

   /**** for real peak ****/
   TString gg1="&&ab1_E>";
   gg1+=e1;
   TString gg2="&&ab1_E<";
   gg2+=e2;
   TString gg=gg1+gg2+ggconst+ggtime;

   /**** background right ****/
   TString ggr1="&&ab1_E>";
   ggr1+=er1;
   TString ggr2="&&ab1_E<";
   ggr2+=er2;
   TString ggr=ggr1+ggr2+ggconst+ggtime;
   gateon+=(e1+e2)/2;
   gateon+=" keV";

   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH1F *h1 = new TH1F("h1",name+gateon,ebinnum,elow,ehigh);
   if(gROOT->FindObject("h2")!=0){
      h2->Delete();
   }
   TH1F *h2 = new TH1F("h2",name,ebinnum,elow,ehigh);
   if(gROOT->FindObject("h3")!=0){
      h3->Delete();
   }
   TH1F *h3 = new TH1F("h3",name,ebinnum,elow,ehigh);
   if(gROOT->FindObject("h4")!=0){
      h4->Delete();
   }
   TH1F *h4 = new TH1F("h4",name,ebinnum,elow,ehigh);

   c1->cd(1);
   decay_tree->Draw("ab2_E>>h1",nuclei+cut+cut2+gg,option);
   decay_tree->Draw("ab2_E>>h4",nuclei+cut+unfold,option);
   decay_tree->Draw("ab2_E>>h2",nuclei+cut+cut2+ggl,option);
   decay_tree->Draw("ab2_E>>h3",nuclei+cut+cut2+ggr,option);
   h2->Add(h3,1);
   h1->Add(h2,-0.5);
   h1->GetYaxis()->SetRangeUser(0,1.1*h1->GetBinContent(h1->GetMaximumBin()));
   h1->Draw(option);
   c1->cd(2);
   h4->Draw(option);
   c1->Update();
}

void checkabEEl(Int_t Z, Int_t A, Int_t e1, Int_t e2, TString cut="", TString cut2="", TString option="", Int_t elow=0, Int_t ehigh=2000){
   Int_t ebinnum = ehigh - elow;
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,1200,800);
   c1->Divide(1,2);
   c1->Draw();
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }
   if(cut2.Sizeof()>1){
      cut2=And+cut2;
   }

   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+OR+name;
      nuclei=nuclei+")";
   }

   Int_t ew = e2-e1;
   Int_t el1=e1-ew;
   Int_t el2=e1;
   Int_t er1=e2;
   Int_t er2=e2+ew;

   TString ggconst="&&ab1_E!=ab2_E";
   TString unfold="&&ab1_E==ab2_E";
   //TString ggtime="&&abs(ab1_T-ab2_T)<250";
   TString ggtime="";
   TString gateon=", gate on ";
   /**** background left ****/
   TString ggl1="&&ab1_E>";
   ggl1+=el1;
   TString ggl2="&&ab1_E<";
   ggl2+=el2;
   TString ggl=ggl1+ggl2+ggconst+ggtime;

   /**** for real peak ****/
   TString gg1="&&ab1_E>";
   gg1+=e1;
   TString gg2="&&ab1_E<";
   gg2+=e2;
   TString gg=gg1+gg2+ggconst+ggtime;

   /**** background right ****/
   TString ggr1="&&ab1_E>";
   ggr1+=er1;
   TString ggr2="&&ab1_E<";
   ggr2+=er2;
   TString ggr=ggr1+ggr2+ggconst+ggtime;
   gateon+=(e1+e2)/2;
   gateon+=" keV";

   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH1F *h1 = new TH1F("h1",name+gateon,ebinnum,elow,ehigh);
   if(gROOT->FindObject("h2")!=0){
      h2->Delete();
   }
   TH1F *h2 = new TH1F("h2",name,ebinnum,elow,ehigh);
   //if(gROOT->FindObject("h3")!=0){
   //   h3->Delete();
   //}
   //TH1F *h3 = new TH1F("h3",name,ebinnum,elow,ehigh);
   if(gROOT->FindObject("h4")!=0){
      h4->Delete();
   }
   TH1F *h4 = new TH1F("h4",name,ebinnum,elow,ehigh);

   c1->cd(1);
   decay_tree->Draw("ab2_E>>h1",nuclei+cut+cut2+gg,option);
   decay_tree->Draw("ab_E>>h4",nuclei+cut+unfold,option);
   decay_tree->Draw("ab2_E>>h2",nuclei+cut+cut2+ggl,option);
   //decay_tree->Draw("ab2_E>>h3",nuclei+cut+ggr,option);
   //h2->Add(h3,1);
   h1->Add(h2,-1);
   h1->GetYaxis()->SetRangeUser(0,1.1*h1->GetBinContent(h1->GetMaximumBin()));
   h1->Draw(option);
   c1->cd(2);
   h4->Draw(option);
   c1->Update();
}

void checkabEEr(Int_t Z, Int_t A, Int_t e1, Int_t e2, TString cut="", TString cut2="", TString option="", Int_t elow=0, Int_t ehigh=2000){
   Int_t ebinnum = ehigh - elow;
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      decay_or_tree = "tree";
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")!=0){
      c1->Close();
   }
   TCanvas *c1 = new TCanvas("c1","c1",0,0,1200,800);
   c1->Divide(1,2);
   c1->Draw();
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }
   if(cut2.Sizeof()>1){
      cut2=And+cut2;
   }

   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+OR+name;
      nuclei=nuclei+")";
   }

   Int_t ew = e2-e1;
   Int_t el1=e1-ew;
   Int_t el2=e1;
   Int_t er1=e2;
   Int_t er2=e2+ew;

   TString ggconst="&&ab1_E!=ab2_E";
   TString unfold="&&ab1_E==ab2_E";
   //TString ggtime="&&abs(ab1_T-ab2_T)<250";
   TString ggtime="";
   TString gateon=", gate on ";
   /**** background left ****/
   TString ggl1="&&ab1_E>";
   ggl1+=el1;
   TString ggl2="&&ab1_E<";
   ggl2+=el2;
   TString ggl=ggl1+ggl2+ggconst+ggtime;

   /**** for real peak ****/
   TString gg1="&&ab1_E>";
   gg1+=e1;
   TString gg2="&&ab1_E<";
   gg2+=e2;
   TString gg=gg1+gg2+ggconst+ggtime;

   /**** background right ****/
   TString ggr1="&&ab1_E>";
   ggr1+=er1;
   TString ggr2="&&ab1_E<";
   ggr2+=er2;
   TString ggr=ggr1+ggr2+ggconst+ggtime;
   gateon+=(e1+e2)/2;
   gateon+=" keV";

   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH1F *h1 = new TH1F("h1",name+gateon,ebinnum,elow,ehigh);
   //if(gROOT->FindObject("h2")!=0){
   //   h2->Delete();
   //}
   //TH1F *h2 = new TH1F("h2",name,ebinnum,elow,ehigh);
   if(gROOT->FindObject("h3")!=0){
      h3->Delete();
   }
   TH1F *h3 = new TH1F("h3",name,ebinnum,elow,ehigh);
   if(gROOT->FindObject("h4")!=0){
      h4->Delete();
   }
   TH1F *h4 = new TH1F("h4",name,ebinnum,elow,ehigh);

   c1->cd(1);
   decay_tree->Draw("ab2_E>>h1",nuclei+cut+cut2+gg,option);
   decay_tree->Draw("ab_E>>h4",nuclei+cut+unfold,option);
   //decay_tree->Draw("ab2_E>>h2",nuclei+cut+ggl,option);
   decay_tree->Draw("ab2_E>>h3",nuclei+cut+cut2+ggr,option);
   //h2->Add(h3,1);
   h1->Add(h3,-1);
   h1->GetYaxis()->SetRangeUser(0,1.1*h1->GetBinContent(h1->GetMaximumBin()));
   h1->Draw(option);
   c1->cd(2);
   h4->Draw(option);
   c1->Update();
}

TChain *cn = NULL;
char filename[200];

void loadallcut(){
   TCutG *fe70 = new TCutG("fe70",10); loadcut("cuts/fe70", fe70);
   TCutG *fe71 = new TCutG("fe71",10); loadcut("cuts/fe71", fe71);
   TCutG *fe72 = new TCutG("fe72",10); loadcut("cuts/fe72", fe72);
   TCutG *fe73 = new TCutG("fe73",10); loadcut("cuts/fe73", fe73);
   TCutG *fe74 = new TCutG("fe74",10); loadcut("cuts/fe74", fe74);
   TCutG *co72 = new TCutG("co72",10); loadcut("cuts/co72", co72);
   TCutG *co73 = new TCutG("co73",10); loadcut("cuts/co73", co73);
   TCutG *co74 = new TCutG("co74",10); loadcut("cuts/co74", co74);
   TCutG *co75 = new TCutG("co75",10); loadcut("cuts/co75", co75);
   TCutG *co76 = new TCutG("co76",10); loadcut("cuts/co76", co76);
   TCutG *co77 = new TCutG("co77",10); loadcut("cuts/co77", co77);
   TCutG *ni74 = new TCutG("ni74",10); loadcut("cuts/ni74", ni74);
   TCutG *ni75 = new TCutG("ni75",10); loadcut("cuts/ni75", ni75);
   TCutG *ni76 = new TCutG("ni76",10); loadcut("cuts/ni76", ni76);
   TCutG *ni77 = new TCutG("ni77",10); loadcut("cuts/ni77", ni77);
   TCutG *ni78 = new TCutG("ni78",10); loadcut("cuts/ni78", ni78);
   TCutG *ni79 = new TCutG("ni79",10); loadcut("cuts/ni79", ni79);
   TCutG *ni80 = new TCutG("ni80",10); loadcut("cuts/ni80", ni80);
   TCutG *cu77 = new TCutG("cu77",10); loadcut("cuts/cu77", cu77);
   TCutG *cu78 = new TCutG("cu78",10); loadcut("cuts/cu78", cu78);
   TCutG *cu79 = new TCutG("cu79",10); loadcut("cuts/cu79", cu79);
   TCutG *cu80 = new TCutG("cu80",10); loadcut("cuts/cu80", cu80);
   TCutG *cu81 = new TCutG("cu81",10); loadcut("cuts/cu81", cu81);
   TCutG *cu82 = new TCutG("cu82",10); loadcut("cuts/cu82", cu82);
   TCutG *zn80 = new TCutG("zn80",10); loadcut("cuts/zn80", zn80);
   TCutG *zn81 = new TCutG("zn81",10); loadcut("cuts/zn81", zn81);
   TCutG *zn82 = new TCutG("zn82",10); loadcut("cuts/zn82", zn82);
   TCutG *zn83 = new TCutG("zn83",10); loadcut("cuts/zn83", zn83);
   TCutG *zn84 = new TCutG("zn84",10); loadcut("cuts/zn84", zn84);
   TCutG *ga83 = new TCutG("ga83",10); loadcut("cuts/ga83", ga83);
   TCutG *ga84 = new TCutG("ga84",10); loadcut("cuts/ga84", ga84);
   TCutG *ga85 = new TCutG("ga85",10); loadcut("cuts/ga85", ga85);
   TCutG *ga86 = new TCutG("ga86",10); loadcut("cuts/ga86", ga86);
   TCutG *ga87 = new TCutG("ga87",10); loadcut("cuts/ga87", ga87);
   TCutG *ge85 = new TCutG("ge85",10); loadcut("cuts/ge85", ge85);
   TCutG *ge86 = new TCutG("ge86",10); loadcut("cuts/ge86", ge86);
   TCutG *ge87 = new TCutG("ge87",10); loadcut("cuts/ge87", ge87);
   TCutG *ge88 = new TCutG("ge88",10); loadcut("cuts/ge88", ge88);
   //TCutG *ni78 = new TCutG("ni78",10); loadcut("cuts/ni78.cut", ni78);
   //TCutG *cu78 = new TCutG("cu78",10); loadcut("cuts/cu78.cut", cu78);
   //TCutG *cu77 = new TCutG("cu77",10); loadcut("cuts/cu77.cut", cu77);
}

void savecut(TCutG *c, char *filename) {
	FILE *fp = fopen(filename, "w");
	cout << c->GetVarX() << endl;
	fprintf(fp, "%s\n", c->GetVarX());
	cout << c->GetVarY() << endl;
	fprintf(fp, "%s\n", c->GetVarY());
	int n = c->GetN();
	cout << n << endl;
	fprintf(fp, "%d\n", c->GetN());
	for (int i = 0; i < n; i++) {
		cout << c->GetX()[i] << " " << c->GetY()[i] << endl;
		fprintf(fp, "%lf %lf\n", c->GetX()[i], c->GetY()[i]);
	}
	fclose(fp);
}

void loadcut(char *filename, TCutG *c) {
	FILE *fp = fopen(filename, "r");

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
}

Int_t PlotDecay(Int_t Z, Int_t A, TString cut="", int time_bin=5000, double Dtime_L=0, double Dtime_U=5000, int option=0){
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      cout<<"No tree called decay is found"<<endl;
      return 0;
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")==0){
      TCanvas *c1 = new TCanvas("c1","c1",0,0,1200,800);
   }
   c1->Divide(1,1);
   c1->cd();
   //c1->SetLogy(1);
   c1->Draw();
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }
   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;

   long time_L = Dtime_L*1e5;
   long time_U = Dtime_U*1e5;
   if(gROOT->FindObject("h1")!=0){
      h1->Delete();
   }
   TH1F *h1 = new TH1F("h1",name,time_bin,time_L,time_U);
   decay_tree->Draw("t>>h1",nuclei+cut);
   h1->GetXaxis()->SetLimits(0,Dtime_U);
   h1->GetXaxis()->SetTitle("Time (ms)");
   Int_t width = (Dtime_U-Dtime_L)/time_bin;
   h1->GetYaxis()->SetTitle(Form("Counts / %d ms",width));
   h1->SetStats(0);
   c1->Update();
   if(option == 1){
      TString decayfilename;
      decayfilename="decay_db/";
      decayfilename+=name;
      //for(size_t i=0; i<str_filename.size(); i++){
      //   filename[i]=str_filename[i];
      //}
      FILE *fp = fopen(decayfilename, "w");
      for(int i=2; i<=time_bin; i++){
         int time = (i-1)*Dtime_U/time_bin;
         fprintf(fp,"%d %d\n",time, h1->GetBinContent(i));
      }
      cout << "Save to "<<decayfilename<<endl;
      fclose(fp);
   }else if(option == 2){
      TString decayfilename;
      decayfilename="decay_db/";
      decayfilename+=name;
      TTreePlayer *mydecay=decay->GetPlayer();
      mydecay->TTreePlayer::SetScanRedirect(true);
      mydecay->TTreePlayer::SetScanFileName(decayfilename);
      decay->Scan("t/1e5",nuclei+cut);
      cout << "Save to "<<decayfilename<<endl;
   }
   return 1;
}

/*********************************************
function to fit beta decay curve. assume
the nuclei taken into account are:
X1 ------> X2 ------> X3 ------> X4 (stable)
           --
           -- n emit
           --
           X5 ------> X6 ------> X7 (stable)
           -
           -  2n emit
           -
           X8 ------> X9 (stable)
Each nuclei can have up-to-two component of half life

There are 18 parameters to fit the total curve:
p[00], p[01], p[02], p[03], p[04], p[05], p[06], p[07], p[08], p[09], p[10], p[11], p[12], p[13], p[14], p[15], p[16], p[17]
 X0  ,, pn  ,, p2n ,, t11 ,, t12 ,, pnd ,, t21 ,, t22 ,, t31 ,, t32 ,,pnbnd,, t51 ,, t52 ,, t61 ,, t62 ,, t81 ,, t82 ,,  C
extra 6 parameters that not need to determined by users.
p[18], p[19], p[20], p[21], p[22], p[23]
 p11 ,, p21 ,, p31 ,, p51 ,, p61 ,, p81
**********************************************/
Double_t lX0(Double_t *t, Double_t *p){
   //for contamination of 80zn
   //return p[17]+2*(TMath::Exp(-t[0]*1.76e-4+2.508)+TMath::Exp(-t[0]*3.0e-3+3.74)+TMath::Exp(-t[0]*3.01e-2+4.43));
   //for contamination of 81zn
   //return p[17]+2*(TMath::Exp(-t[0]*2.91e-4+2.697)+TMath::Exp(-t[0]*1.26e-2+4.02));
   //for contamination of 83ga
   //return p[17]+2*(TMath::Exp(-t[0]*4.63e-4+2.652)+TMath::Exp(-t[0]*1.24e-2+4.257));
   //for contamination of 74co
   //return p[17]+0.5*(TMath::Exp(-t[0]*4.23e-4+0.88)+TMath::Exp(-t[0]*4.35e-3+2.57));
   //for contamination of 85ge
   //return p[17]+2*(TMath::Exp(-t[0]*7.59e-5+0.595)+TMath::Exp(-t[0]*1.62e-2+1.987));
   //for general case
   return p[17];
}

Double_t lX1(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1[2], p1[2];
   Double_t l1;
   Double_t X0=p[0];
   t1[0]=p[3];
   t1[1]=p[4];
   p1[0]=1-p[18];
   p1[1]=p[18];
   result = 0;
   for(int i=0; i<2; i++){
      if(t1[i]>0){
         l1=log(2)/t1[i];
         Double_t temp;
         temp = TMath::Exp(-1*l1*t[0])*p1[i];
         result = result + temp;
      }
   }
   return result*X0;
}

Double_t lX2(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1[2], p1[2], t2[2], p2[2];
   Double_t l1, l2;
   Double_t X0=p[0];
   Double_t pb=1-p[1]-p[2];
   t1[0]=p[3];
   t1[1]=p[4];
   t2[0]=p[6];
   t2[1]=p[7];
   p1[0]=1-p[18];
   p1[1]=p[18];
   p2[0]=1-p[19];
   p2[1]=p[19];
   result = 0;
   for(int i=0; i<2; i++){
      for(int j=0; j<2; j++){
         if(t1[i]>0 && t2[j]>0 && t1[i]!=t2[j]){
            l1=log(2)/t1[i];
            l2=log(2)/t2[j];
            Double_t temp;
            temp = l2*(TMath::Exp(-1*l1*t[0])/(l2-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2))*p1[i]*p2[j];
            result = result + temp;
         }
      }
   }
   return X0*pb*result;
}

Double_t lX3(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1[2], p1[2], t2[2], p2[2], t3[2], p3[2];
   Double_t l1, l2, l3;
   Double_t X0=p[0];
   Double_t pb=1-p[1]-p[2];
   Double_t pbd=1-p[5];
   t1[0]=p[3];
   t1[1]=p[4];
   t2[0]=p[6];
   t2[1]=p[7];
   t3[0]=p[8];
   t3[1]=p[9];
   p1[0]=1-p[18];
   p1[1]=p[18];
   p2[0]=1-p[19];
   p2[1]=p[19];
   p3[0]=1-p[20];
   p3[1]=p[20];
   result = 0;
   for(int i=0; i<2; i++){
      for(int j=0; j<2; j++){
         for(int k=0; k<2; k++){
            if(t1[i]>0 && t2[j]>0 && t3[k]>0 && t1[i]!=t2[j] && t1[i]!=t3[k] && t2[j]!=t3[k]){
               l1=log(2)/t1[i];
               l2=log(2)/t2[j];
               l3=log(2)/t3[k];
               Double_t temp;
               temp = l2*l3*(TMath::Exp(-1*l1*t[0])/(l2-l1)/(l3-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2)/(l3-l2)+TMath::Exp(-1*l3*t[0])/(l1-l3)/(l2-l3))*p1[i]*p2[j]*p3[k];
               result = result + temp;
            }
         }
      }
   }
   return X0*pb*pbd*result;
}

Double_t lX5(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1[2], p1[2], t5[2], p5[2];
   Double_t l1, l5;
   Double_t X0=p[0];
   Double_t pn=p[1];
   t1[0]=p[3];
   t1[1]=p[4];
   t5[0]=p[11];
   t5[1]=p[12];
   p1[0]=1-p[18];
   p1[1]=p[18];
   p5[0]=1-p[21];
   p5[1]=p[21];
   result = 0;
   for(int i=0; i<2; i++){
      for(int j=0; j<2; j++){
         if(t1[i]>0 && t5[j]>0 && t1[i]!=t5[j]){
            l1=log(2)/t1[i];
            l5=log(2)/t5[j];
            Double_t temp;
            temp = l5*(TMath::Exp(-1*l1*t[0])/(l5-l1)+TMath::Exp(-1*l5*t[0])/(l1-l5))*p1[i]*p5[j];
            result = result + temp;
         }
      }
   }
   return X0*pn*result;
}

Double_t lX6(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1[2], p1[2], t2[2], p2[2], t5[2], p5[2], t6[2], p6[2];
   Double_t l1, l2, l5, l6;
   Double_t X0=p[0];
   Double_t pb=1-p[1]-p[2];
   Double_t pn=p[1];
   Double_t pbbnd=1-p[10];
   Double_t pnd=p[5];
   t1[0]=p[3];
   t1[1]=p[4];
   t2[0]=p[6];
   t2[1]=p[7];
   t5[0]=p[11];
   t5[1]=p[12];
   t6[0]=p[13];
   t6[1]=p[14];
   p1[0]=1-p[18];
   p1[1]=p[18];
   p2[0]=1-p[19];
   p2[1]=p[19];
   p5[0]=1-p[21];
   p5[1]=p[21];
   p6[0]=1-p[22];
   p6[1]=p[22];
   result = 0;
   for(int i=0; i<2; i++){
      for(int j=0; j<2; j++){
         for(int k=0; k<2; k++){
            if(t1[i]>0 && t5[j]>0 && t6[k]>0 && t1[i]!=t5[j] && t1[i]!=t6[k] && t5[j]!=t6[k]){
               l1=log(2)/t1[i];
               l5=log(2)/t5[j];
               l6=log(2)/t6[k];
               Double_t temp;
               temp = l5*l6*(TMath::Exp(-1*l1*t[0])/(l5-l1)/(l6-l1)+TMath::Exp(-1*l5*t[0])/(l1-l5)/(l6-l5)+TMath::Exp(-1*l6*t[0])/(l1-l6)/(l5-l6))*p1[i]*p5[j]*p6[k];
               result = result + pn*pbbnd*temp;
            }
         }
      }
   }
   for(int i=0; i<2; i++){
      for(int j=0; j<2; j++){
         for(int k=0; k<2; k++){
            if(t1[i]>0 && t2[j]>0 && t6[k]>0 && t1[i]!=t2[j] && t1[i]!=t6[k] && t2[j]!=t6[k]){
               l1=log(2)/t1[i];
               l2=log(2)/t2[j];
               l6=log(2)/t6[k];
               Double_t temp;
               temp = l2*l6*(TMath::Exp(-1*l1*t[0])/(l2-l1)/(l6-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2)/(l6-l2)+TMath::Exp(-1*l6*t[0])/(l1-l6)/(l2-l6))*p1[i]*p2[j]*p6[k];
               result = result + pb*pnd*temp;
            }
         }
      }
   }
   return X0*result;
}

Double_t lX8(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1[2], p1[2], t8[2], p8[2];
   Double_t l1, l8;
   Double_t X0=p[0];
   Double_t p2n=p[2];
   t1[0]=p[3];
   t1[1]=p[4];
   t8[0]=p[15];
   t8[1]=p[16];
   p1[0]=1-p[18];
   p1[1]=p[18];
   p8[0]=1-p[23];
   p8[1]=p[23];
   result = 0;
   for(int i=0; i<2; i++){
      for(int j=0; j<2; j++){
         if(t1[i]>0 && t8[j]>0 && t1[i]!=t8[j]){
            l1=log(2)/t1[i];
            l8=log(2)/t8[j];
            Double_t temp;
            temp = l8*(TMath::Exp(-1*l1*t[0])/(l8-l1)+TMath::Exp(-1*l8*t[0])/(l1-l8))*p1[i]*p8[j];
            result = result + temp;
         }
      }
   }
   return X0*p2n*result;
}

Double_t dNdt(Double_t *t, Double_t *p){
   if(t[0]>0 && (p[1]+p[2]<=1)){
      return lX0(t,p)+lX1(t,p)+lX2(t,p)+lX3(t,p)+lX5(t,p)+lX6(t,p)+lX8(t,p);
   }
   else{
      return 0;
   }
}

Double_t dNdt_p(Double_t *t, Double_t *p){
   if(t[0]>0 && (p[1]+p[2]<=1)){
      return lX0(t,p)+lX1(t,p);
   }
   else{
      return 0;
   }
}

Double_t dNdt_d(Double_t *t, Double_t *p){
   if(t[0]>0 && (p[1]+p[2]<=1)){
      return lX0(t,p)+lX2(t,p);
   }
   else{
      return 0;
   }
}


fit_decay(Int_t Z, Int_t A, TString cut="", TString option="E", int time_bin=5000, double Dtime_L=0, double Dtime_U=5000, double fit_L=10, double fit_R=4010){
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      cout<<"No tree called decay is found"<<endl;
      return 0;
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")==0){
      TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,500);
   }
   c1->Divide(1,1);
   c1->cd();
   c1->SetLogy(1);
   c1->Draw();
   c1->SetGridx(0);
   c1->SetGridy(0);
   c1->SetRightMargin(0.06);
   c1->SetTopMargin(0.06);
   c1->SetLeftMargin(0.14);
   c1->SetBottomMargin(0.14);
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }
   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+And+name;
      nuclei=nuclei+")";
   }

   long time_L = Dtime_L*1e5;
   long time_U = Dtime_U*1e5;
   TH1F *h1 = new TH1F("h1","",time_bin,time_L,time_U);
   //TH1F *h1 = new TH1F("h1","Decay curve",time_bin,time_L,time_U);
   decay_tree->Draw("t>>h1",nuclei+cut,option);
   h1->Sumw2();
   h1->GetYaxis()->SetRangeUser(0.001*h1->GetBinContent(h1->GetMaximumBin()),2*h1->GetBinContent(h1->GetMaximumBin()));

   h1->SetTitleSize(0.1);
   h1->GetXaxis()->SetLimits(0,Dtime_U);
   h1->GetXaxis()->SetTitle("Time (ms)");
   h1->GetXaxis()->SetLabelSize(0.07);
   h1->GetXaxis()->SetTitleSize(0.07);
   Int_t width = (Dtime_U-Dtime_L)/time_bin;
   h1->GetYaxis()->SetTitle(Form("Counts / %d ms",width));
   h1->GetYaxis()->SetLabelSize(0.07);
   h1->GetYaxis()->SetTitleSize(0.07);
   h1->SetStats(0);
   TF1 *myfit = new TF1("myfit",dNdt,fit_L,fit_R,24);
   myfit->SetLineColor(kRed);
   myfit->SetNpx(5000);
   TF1 *decayp = new TF1("decayp",lX1,0,20000,24);
   decayp->SetLineColor(kBlack);
   decayp->SetNpx(5000);
   TF1 *decayd = new TF1("decayd",lX2,0,20000,24);
   decayd->SetLineColor(kBlue);
   decayd->SetNpx(5000);
   TF1 *decaygd = new TF1("decaygd",lX3,0,20000,24);
   decaygd->SetLineColor(kGreen);
   decaygd->SetNpx(5000);
   TF1 *decayn = new TF1("decayn",lX5,0,20000,24);
   decayn->SetLineColor(7);
   decayn->SetNpx(5000);
   TF1 *decayng = new TF1("decayng",lX6,0,20000,24);
   decayng->SetLineColor(8);
   decayng->SetNpx(5000);
   //TF1 *decay_dbeta2n = new TF1("decay_dbeta2n",lX8,time_L,time_U,10);
   TF1 *decaybg = new TF1("decaybg",lX0,0,20000,24);
   decaybg->SetLineColor(6);
   decaybg->SetNpx(5000);
   //myfit->SetParLimits(8,0,1e-7);
   cout<<"the nuclei taken into account are:"<<endl;
   cout<<"X1 ------> X2 ------> X3 ------> X4 (stable)"<<endl;
   cout<<"           --"<<endl;
   cout<<"           -- n emit"<<endl;
   cout<<"           --"<<endl;
   cout<<"           X5 ------> X6 ------> X7 (stable)"<<endl;
   cout<<"           -"<<endl;
   cout<<"           -  2n emit"<<endl;
   cout<<"           -"<<endl;
   cout<<"           X8 ------> X9 (stable)"<<endl<<endl;

   cout<<"Each nuclei can have up-to-two component of half life"<<endl<<endl;

   cout<<"There are 16 parameters to fit the total curve:"<<endl;
   cout<<"p[00], p[01], p[02], p[03], p[04], p[05], p[06], p[07], p[08], p[09], p[10], p[11], p[12], p[13], p[14], p[15], p[16], p[17]"<<endl;
   cout<<" X0  ,, pn  ,, p2n ,, t11 ,, t12 ,, pnd ,, t21 ,, t22 ,, t31 ,, t32 ,,pnbnd,, t51 ,, t52 ,, t61 ,, t62 ,, t81 ,, t82 ,, C"<<endl<<endl;

   read_fitting_parameters(myfit,name);

   //h1->Fit("myfit","WLR");
   h1->Fit("myfit","WLR");
   h1->Draw(option);
   c1->Update();
   Double_t *para = myfit->GetParameters();
   Double_t *sig = myfit->GetParErrors();
   decayp->SetParameters(para);
   decayd->SetParameters(para);
   decaygd->SetParameters(para);
   decayn->SetParameters(para);
   decayng->SetParameters(para);
   //decay_dbeta2n->SetParameters(para);
   decaybg->SetParameters(para);
   decayp->Draw("same");
   decayd->Draw("same");
   decaygd->Draw("same");
   decayn->Draw("same");
   decayng->Draw("same");
   //decay_dbeta2n->Draw("same");
   decaybg->Draw("same");
   Double_t t=1000;
   cout<<"total = "<<myfit->Eval(t)<<endl;
   cout<<"decay_p = "<<decayp->Eval(t)<<endl;
   cout<<"decay_d = "<<decayd->Eval(t)<<endl;
   cout<<"decay_gd = "<<decaygd->Eval(t)<<endl;
   cout<<"decay_n = "<<decayn->Eval(t)<<endl;
   cout<<"decay_ng = "<<decayng->Eval(t)<<endl;
   cout<<"decay_bg = "<<decaybg->Eval(t)<<endl;

   Double_t time1 = para[3];
   Double_t sigma1 = sig[3];
   Double_t t_half1 = time1;
   Double_t t_error1 = sigma1;
   Double_t time2 = para[4];
   Double_t sigma2 = sig[4];
   Double_t t_half2 = time2;
   Double_t t_error2 = sigma2;
   Double_t time3 = para[6];
   Double_t sigma3 = sig[6];
   Double_t t_half3 = time3;
   Double_t t_error3 = sigma3;
   cout<<"T_parent = "<<setiosflags(ios::fixed)<<setprecision(2)<<t_half1<<" ± "<<setiosflags(ios::fixed)<<setprecision(2)<<t_error1<<" ms"<<endl;
   //cout<<"T_daughter = "<<setiosflags(ios::fixed)<<setprecision(2)<<t_half2<<" ± "<<setiosflags(ios::fixed)<<setprecision(2)<<t_error2<<" ms"<<endl;
   //cout<<"T_betan = "<<setiosflags(ios::fixed)<<setprecision(2)<<t_half3<<" ± "<<setiosflags(ios::fixed)<<setprecision(2)<<t_error3<<" ms"<<endl;
   cout<<"Total parent decay = "<<decayp->Integral(0,20000)/width<<" counts"<<endl;
   cout<<"Total daughter decay = "<<decayd->Integral(0,200000)/width<<" counts"<<endl;
   cout<<"Total grand daughter decay = "<<decaygd->Integral(0,200000)/width<<" counts"<<endl;
   cout<<"Portion for parent decay in 5 - 105 ms = "<<decayp->Integral(5,105)/decayp->Integral(0,40000)*100<<"%"<<endl;
   cout<<"Portion for parent decay in 5 - 205 ms = "<<decayp->Integral(5,205)/decayp->Integral(0,40000)*100<<"%"<<endl;
   cout<<"Portion for parent decay in 5 - 405 ms = "<<decayp->Integral(5,405)/decayp->Integral(0,40000)*100<<"%"<<endl;
   if(para[1]<1){
      cout<<"Portion for daughter decay in 5 - 1005 ms = "<<decayd->Integral(5,1005)/decayd->Integral(0,20000)*100<<"%"<<endl;
      cout<<"Portion for daughter decay in 5 - 2005 ms = "<<decayd->Integral(5,2005)/decayd->Integral(0,20000)*100<<"%"<<endl;
   }
   if(para[1]>0){
      cout<<"Portion for beta-n daughter decay in 5 - 1005 ms = "<<decayn->Integral(5,1005)/decayn->Integral(0,20000)*100<<"%"<<endl;
      cout<<"Portion for beta-n daughter decay in 5 - 2005 ms = "<<decayn->Integral(5,2005)/decayn->Integral(0,20000)*100<<"%"<<endl;
   }
   double chi_mlh=0;
   for(int i=1; i<=time_bin; i++)
   {
      float time_i = h1->GetXaxis()->GetBinCenter(i);
      if(time_i>fit_L){
         int n_i = h1->GetBinContent(i);
         double y_i = myfit->Eval(time_i);
         //cout<<time_i<<", "<<y_i<<", "<<n_i<<endl;
         if(n_i>0){
            chi_mlh=chi_mlh+(y_i-n_i+n_i*log(n_i/y_i));
         }else if(n_i==0){
            chi_mlh=chi_mlh+(y_i-n_i);
         }
      }
   }
   chi_mlh=chi_mlh*2/myfit->GetNDF();
   cout<<"MLH ratio = "<<chi_mlh<<endl;

   TLatex text1, text2, text3;
   TString content0, content1, content2, content3;
   char text_half[100];
   char text_error[100];
   char text_pn[100];
   char text_chisqdf[100];
   sprintf(text_half,"%.1f",t_half1);
   sprintf(text_error,"%.1f",t_error1);
   sprintf(text_pn,"%.1f",para[1]*100);
   sprintf(text_chisqdf,"%.3f",myfit->GetChisquare()/myfit->GetNDF());
   content1="T_{1/2}";
   //content+=name;
   content1+=" = ";
   content1+=text_half;
   content1+=" #pm ";
   content1+=text_error;
   content1+=" ms";
   //content2="P_{n} = ";
   //content2+=text_pn;
   //content2+=" %";
   name_nuclei_latex(Z,A,content2);
   content0 +="#beta-decay of";
   content0 +=content2;
   content3="#chi^{2} #/NDF = ";
   content3+=text_chisqdf;
   text1.SetTextAlign(12);
   text1.SetTextSize(0.08);
   text1.SetNDC(kTRUE);
   //text1.DrawLatex(.5,.78,content1);
   text2.SetTextAlign(12);
   text2.SetTextSize(0.08);
   text2.SetNDC(kTRUE);
   cout<<content3<<endl;
   //text2.DrawLatex(.5,.68,content3);
   text3.SetTextAlign(12);
   text3.SetTextSize(0.08);
   text3.SetNDC(kTRUE);
   text3.DrawLatex(.5,.88,content0);
}

fit_decay_gamma_nobg(Int_t Z, Int_t A, Int_t e1, Int_t e2, TString cut="", TString option="E", int time_bin=5000, double Dtime_L=0, double Dtime_U=5000, double fit_L=5, double fit_R=5000){
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      cout<<"No tree called decay is found"<<endl;
      return 0;
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")==0){
      TCanvas *c1 = new TCanvas("c1","c1",0,0,600,600);
   }
   c1->Divide(1,1);
   c1->cd();
   c1->SetLogy(1);
   c1->SetGridx(0);
   c1->SetGridy(0);
   c1->SetRightMargin(0.06);
   c1->SetTopMargin(0.06);
   c1->SetLeftMargin(0.14);
   c1->SetBottomMargin(0.14);
   c1->Draw();
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }
   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;

   Int_t ew = e2-e1;
   Int_t el1=e1-ew;
   Int_t el2=e1;
   Int_t er1=e2;
   Int_t er2=e2+ew;

   TString gateon="Gated on ";
   gateon+=(e1+e2)/2;
   gateon+=" keV #gamma-ray";
   /**** background left ****/
   TString ggl1="&&ab_E>";
   ggl1+=el1;
   TString ggl2="&&ab_E<";
   ggl2+=el2;
   TString ggl=ggl1+ggl2;
   /**** for real peak ****/
   TString gg1="&&ab_E>";
   gg1+=e1;
   TString gg2="&&ab_E<";
   gg2+=e2;
   TString gg=gg1+gg2;
   /**** background right ****/
   TString ggr1="&&ab_E>";
   ggr1+=er1;
   TString ggr2="&&ab_E<";
   ggr2+=er2;
   TString ggr=ggr1+ggr2;

   long time_L = Dtime_L*1e5;
   long time_U = Dtime_U*1e5;
   TH1F *h1 = new TH1F("h1","",time_bin,time_L,time_U);

   decay_tree->Draw("t>>h1",nuclei+cut+gg,option);

   h1->GetYaxis()->SetRangeUser(0.001*h1->GetBinContent(h1->GetMaximumBin()),2*h1->GetBinContent(h1->GetMaximumBin()));

   h1->SetTitleSize(0.1);
   h1->GetXaxis()->SetLimits(0,Dtime_U);
   h1->GetXaxis()->SetTitle("Time (ms)");
   h1->GetXaxis()->SetLabelSize(0.07);
   h1->GetXaxis()->SetTitleSize(0.07);
   Int_t width = (Dtime_U-Dtime_L)/time_bin;
   h1->GetYaxis()->SetTitle(Form("Counts / %d ms",width));
   h1->GetYaxis()->SetLabelSize(0.07);
   h1->GetYaxis()->SetTitleSize(0.07);
   h1->SetStats(0);
   TF1 *myfit = new TF1("myfit",dNdt,fit_L,fit_R,24);
   myfit->SetLineColor(kRed);
   myfit->SetNpx(5000);
   TF1 *decayp = new TF1("decayp",lX1,0,20000,24);
   decayp->SetLineColor(kBlack);
   decayp->SetNpx(5000);
   TF1 *decaybg = new TF1("decaybg",lX0,0,20000,24);
   decaybg->SetLineColor(6);
   decaybg->SetNpx(5000);
   //myfit->SetParLimits(8,0,1e-7);
   cout<<"the nuclei taken into account are:"<<endl;
   cout<<"X1"<<endl;

   read_fitting_parameters_p(myfit,name);

   h1->Fit("myfit","LR");
   h1->Draw(option);
   c1->Update();
   Double_t *para = myfit->GetParameters();
   Double_t *sig = myfit->GetParErrors();
   decayp->SetParameters(para);
   decaybg->SetParameters(para);
   decayp->Draw("same");
   decaybg->Draw("same");

   Double_t time1 = para[3];
   Double_t sigma1 = sig[3];
   Double_t t_half1 = time1;
   Double_t t_error1 = sigma1;
   cout<<"T_parent = "<<setiosflags(ios::fixed)<<setprecision(2)<<t_half1<<" ± "<<setiosflags(ios::fixed)<<setprecision(2)<<t_error1<<" ms"<<endl;
   TLatex text1, text2, text3;
   TString content0, content1, content2, content3;
   char text_half[100];
   char text_error[100];
   char text_pn[100];
   char text_chisqdf[100];
   sprintf(text_half,"%.1f",t_half1);
   sprintf(text_error,"%.1f",t_error1);
   sprintf(text_pn,"%.1f",0);
   sprintf(text_chisqdf,"%.3f",myfit->GetChisquare()/myfit->GetNDF());
   content1="T_{1/2}";
   //content+=name;
   content1+=" = ";
   content1+=text_half;
   content1+=" #pm ";
   content1+=text_error;
   content1+=" ms";
   //content2="P_{n} = ";
   //content2+=text_pn;
   //content2+=" %";
   name_nuclei_latex(Z,A,content2);
   content0 +="#beta-decay of";
   content0 +=content2;
   content2 +=" - ";
   content2 +=(e1+e2)/2;
   content2 +=" keV";
   content3="#chi^{2} #/NDF = ";
   content3+=text_chisqdf;
   text1.SetTextAlign(12);
   text1.SetTextSize(0.08);
   text1.SetNDC(kTRUE);
   //text1.DrawLatex(.5,.68,content1);
   text2.SetTextAlign(12);
   text2.SetTextSize(0.08);
   text2.SetNDC(kTRUE);
   text2.DrawLatex(.45,.88,content2);
   text3.SetTextAlign(12);
   text3.SetTextSize(0.08);
   text3.SetNDC(kTRUE);
   //text3.DrawLatex(.5,.78,gateon);
   cout<<"MLH ratio = "<<myfit->GetChisquare()/myfit->GetNDF()<<endl;
}

fit_decay_gamma(Int_t Z, Int_t A, Int_t e1, Int_t e2, TString cut="", TString option="E", int time_bin=5000, double Dtime_L=0, double Dtime_U=5000, double fit_L=5, double fit_R=5000){
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      cout<<"No tree called decay is found"<<endl;
      return 0;
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")==0){
      TCanvas *c1 = new TCanvas("c1","c1",0,0,600,600);
   }
   c1->Divide(1,1);
   c1->cd();
   c1->SetLogy(1);
   c1->SetGridx(0);
   c1->SetGridy(0);
   c1->SetRightMargin(0.06);
   c1->SetTopMargin(0.06);
   c1->SetLeftMargin(0.14);
   c1->SetBottomMargin(0.14);
   c1->Draw();
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }
   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;

   Int_t ew = e2-e1;
   Int_t el1=e1-ew;
   Int_t el2=e1;
   Int_t er1=e2;
   Int_t er2=e2+ew;

   TString gateon="Gated on ";
   gateon+=(e1+e2)/2;
   gateon+=" keV #gamma-ray";
   /**** background left ****/
   TString ggl1="&&ab_E>";
   ggl1+=el1;
   TString ggl2="&&ab_E<";
   ggl2+=el2;
   TString ggl=ggl1+ggl2;
   /**** for real peak ****/
   TString gg1="&&ab_E>";
   gg1+=e1;
   TString gg2="&&ab_E<";
   gg2+=e2;
   TString gg=gg1+gg2;
   /**** background right ****/
   TString ggr1="&&ab_E>";
   ggr1+=er1;
   TString ggr2="&&ab_E<";
   ggr2+=er2;
   TString ggr=ggr1+ggr2;

   long time_L = Dtime_L*1e5;
   long time_U = Dtime_U*1e5;
   TH1F *h1 = new TH1F("h1","",time_bin,time_L,time_U);
   //TH1F *h1 = new TH1F("h1","Decay curve",time_bin,time_L,time_U);
   TH1F *h2 = new TH1F("h2",name,time_bin,time_L,time_U);
   TH1F *h3 = new TH1F("h3",name,time_bin,time_L,time_U);

   decay_tree->Draw("t>>h1",nuclei+cut+gg,option);
   decay_tree->Draw("t>>h2",nuclei+cut+ggl,option);
   decay_tree->Draw("t>>h3",nuclei+cut+ggr,option);
   h2->Add(h3,1);
   h1->Add(h2,-0.5);
   TH1F *hbg = new TH1F("hbg","hbg",time_bin,time_L,time_U);
   for(int i=1; i<=time_bin; i++){
      hbg->SetBinContent(i,0);
   }
   //h1->Add(hbg,1);

   h1->GetYaxis()->SetRangeUser(0.001*h1->GetBinContent(h1->GetMaximumBin()),2*h1->GetBinContent(h1->GetMaximumBin()));

   h1->SetTitleSize(0.1);
   h1->GetXaxis()->SetLimits(0,Dtime_U);
   h1->GetXaxis()->SetTitle("Time (ms)");
   h1->GetXaxis()->SetLabelSize(0.07);
   h1->GetXaxis()->SetTitleSize(0.07);
   Int_t width = (Dtime_U-Dtime_L)/time_bin;
   h1->GetYaxis()->SetTitle(Form("Counts / %d ms",width));
   h1->GetYaxis()->SetLabelSize(0.07);
   h1->GetYaxis()->SetTitleSize(0.07);
   h1->SetStats(0);
   //TF1 *myfit = new TF1("myfit",dNdt_p,fit_L,fit_R,24);
   TF1 *myfit = new TF1("myfit",dNdt,fit_L,fit_R,24);
   myfit->SetLineColor(kRed);
   TF1 *decayp = new TF1("decayp",lX1,0,20000,24);
   decayp->SetNpx(5000);
   decayp->SetLineColor(kBlack);
   TF1 *decaybg = new TF1("decaybg",lX0,0,20000,24);
   decaybg->SetLineColor(6);
   decaybg->SetNpx(5000);
   //myfit->SetParLimits(8,0,1e-7);
   cout<<"the nuclei taken into account are:"<<endl;
   cout<<"X1"<<endl;

   read_fitting_parameters_p(myfit,name);
   //read_fitting_parameters(myfit,name);

   h1->Fit("myfit","LR");
   h1->Draw(option);
   c1->Update();
   Double_t *para = myfit->GetParameters();
   Double_t *sig = myfit->GetParErrors();
   decayp->SetParameters(para);
   decaybg->SetParameters(para);
   decayp->Draw("same");
   decaybg->Draw("same");

   Double_t time1 = para[3];
   Double_t sigma1 = sig[3];
   Double_t t_half1 = time1;
   Double_t t_error1 = sigma1;
   cout<<"T_parent = "<<setiosflags(ios::fixed)<<setprecision(2)<<t_half1<<" ± "<<setiosflags(ios::fixed)<<setprecision(2)<<t_error1<<" ms"<<endl;
   TLatex text1, text2, text3;
   TString content0, content1, content2, content3;
   char text_half[100];
   char text_error[100];
   char text_pn[100];
   char text_chisqdf[100];
   sprintf(text_half,"%.1f",t_half1);
   sprintf(text_error,"%.1f",t_error1);
   sprintf(text_pn,"%.1f",0);
   sprintf(text_chisqdf,"%.3f",myfit->GetChisquare()/myfit->GetNDF());
   content1="T_{1/2}";
   //content+=name;
   content1+=" = ";
   content1+=text_half;
   content1+=" #pm ";
   content1+=text_error;
   content1+=" ms";
   //content2="P_{n} = ";
   //content2+=text_pn;
   //content2+=" %";
   name_nuclei_latex(Z,A,content2);
   content0 +="#beta-decay of";
   content0 +=content2;
   content2 +=" - ";
   content2 +=(e1+e2)/2;
   content2 +=" keV";
   content3="#chi^{2} #/NDF = ";
   content3+=text_chisqdf;
   text1.SetTextAlign(12);
   text1.SetTextSize(0.08);
   text1.SetNDC(kTRUE);
   //text1.DrawLatex(.5,.68,content1);
   text2.SetTextAlign(12);
   text2.SetTextSize(0.08);
   text2.SetNDC(kTRUE);
   text2.DrawLatex(.45,.88,content2);
   text3.SetTextAlign(12);
   text3.SetTextSize(0.08);
   text3.SetNDC(kTRUE);
   //text3.DrawLatex(.5,.78,gateon);
   cout<<"MLH ratio = "<<myfit->GetChisquare()/myfit->GetNDF()<<endl;
}

fit_decay_gamma_left(Int_t Z, Int_t A, Int_t e1, Int_t e2, TString cut="", TString option="E", int time_bin=5000, double Dtime_L=0, double Dtime_U=5000, double fit_L=5, double fit_R=5000){
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      cout<<"No tree called decay is found"<<endl;
      return 0;
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")==0){
      TCanvas *c1 = new TCanvas("c1","c1",0,0,600,600);
   }
   c1->Divide(1,1);
   c1->cd();
   c1->SetLogy(1);
   c1->SetGridx(0);
   c1->SetGridy(0);
   c1->SetRightMargin(0.06);
   c1->SetTopMargin(0.06);
   c1->SetLeftMargin(0.14);
   c1->SetBottomMargin(0.14);
   c1->Draw();
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }
   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;

   Int_t ew = e2-e1;
   Int_t el1=e1-ew;
   Int_t el2=e1;
   Int_t er1=e2;
   Int_t er2=e2+ew;

   TString gateon="Gated on ";
   gateon+=(e1+e2)/2;
   gateon+=" keV #gamma-ray";
   /**** background left ****/
   TString ggl1="&&ab_E>";
   ggl1+=el1;
   TString ggl2="&&ab_E<";
   ggl2+=el2;
   TString ggl=ggl1+ggl2;
   /**** for real peak ****/
   TString gg1="&&ab_E>";
   gg1+=e1;
   TString gg2="&&ab_E<";
   gg2+=e2;
   TString gg=gg1+gg2;

   long time_L = Dtime_L*1e5;
   long time_U = Dtime_U*1e5;
   TH1F *h1 = new TH1F("h1","",time_bin,time_L,time_U);
   //TH1F *h1 = new TH1F("h1",name+gateon,time_bin,time_L,time_U);
   TH1F *h2 = new TH1F("h2",name,time_bin,time_L,time_U);

   decay_tree->Draw("t>>h1",nuclei+cut+gg,option);
   decay_tree->Draw("t>>h2",nuclei+cut+ggl,option);
   h1->Add(h2,-1);

   h1->GetYaxis()->SetRangeUser(0.001*h1->GetBinContent(h1->GetMaximumBin()),2*h1->GetBinContent(h1->GetMaximumBin()));

   h1->SetTitleSize(0.1);
   h1->GetXaxis()->SetLimits(0,Dtime_U);
   h1->GetXaxis()->SetTitle("Time (ms)");
   h1->GetXaxis()->SetLabelSize(0.07);
   h1->GetXaxis()->SetTitleSize(0.07);
   Int_t width = (Dtime_U-Dtime_L)/time_bin;
   h1->GetYaxis()->SetTitle(Form("Counts / %d ms",width));
   h1->GetYaxis()->SetLabelSize(0.07);
   h1->GetYaxis()->SetTitleSize(0.07);
   h1->SetStats(0);
   TF1 *myfit = new TF1("myfit",dNdt,fit_L,fit_R,24);
   myfit->SetLineColor(kRed);
   TF1 *decayp = new TF1("decayp",lX1,0,20000,24);
   decayp->SetLineColor(kBlack);
   decayp->SetNpx(5000);
   TF1 *decaybg = new TF1("decaybg",lX0,0,20000,24);
   decaybg->SetLineColor(6);
   decaybg->SetNpx(5000);
   //myfit->SetParLimits(8,0,1e-7);
   cout<<"the nuclei taken into account are:"<<endl;
   cout<<"X1"<<endl;

   read_fitting_parameters_p(myfit,name);

   h1->Fit("myfit","LR");
   h1->Draw(option);
   c1->Update();
   Double_t *para = myfit->GetParameters();
   Double_t *sig = myfit->GetParErrors();
   decayp->SetParameters(para);
   decaybg->SetParameters(para);
   decayp->Draw("same");
   decaybg->Draw("same");

   Double_t time1 = para[3];
   Double_t sigma1 = sig[3];
   Double_t t_half1 = time1;
   Double_t t_error1 = sigma1;
   cout<<"T_parent = "<<setiosflags(ios::fixed)<<setprecision(2)<<t_half1<<" ± "<<setiosflags(ios::fixed)<<setprecision(2)<<t_error1<<" ms"<<endl;
   TLatex text1, text2, text3;
   TString content0, content1, content2, content3;
   char text_half[100];
   char text_error[100];
   char text_pn[100];
   char text_chisqdf[100];
   sprintf(text_half,"%.1f",t_half1);
   sprintf(text_error,"%.1f",t_error1);
   sprintf(text_pn,"%.1f",0);
   sprintf(text_chisqdf,"%.3f",myfit->GetChisquare()/myfit->GetNDF());
   content1="T_{1/2}";
   //content+=name;
   content1+=" = ";
   content1+=text_half;
   content1+=" #pm ";
   content1+=text_error;
   content1+=" ms";
   //content2="P_{n} = ";
   //content2+=text_pn;
   //content2+=" %";
   name_nuclei_latex(Z,A,content2);
   content0 +="#beta-decay of";
   content0 +=content2;
   content2 +=" - ";
   content2 +=(e1+e2)/2;
   content2 +=" keV";
   content3="#chi^{2} #/NDF = ";
   content3+=text_chisqdf;
   text1.SetTextAlign(12);
   text1.SetTextSize(0.08);
   text1.SetNDC(kTRUE);
   //text1.DrawLatex(.5,.68,content1);
   text2.SetTextAlign(12);
   text2.SetTextSize(0.08);
   text2.SetNDC(kTRUE);
   text2.DrawLatex(.45,.88,content2);
   text3.SetTextAlign(12);
   text3.SetTextSize(0.08);
   text3.SetNDC(kTRUE);
   //text3.DrawLatex(.5,.78,gateon);
}

fit_decay_gamma_right(Int_t Z, Int_t A, Int_t e1, Int_t e2, TString cut="", TString option="E", int time_bin=5000, double Dtime_L=0, double Dtime_U=5000, double fit_L=5, double fit_R=5000){
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      cout<<"No tree called decay is found"<<endl;
      return 0;
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")==0){
      TCanvas *c1 = new TCanvas("c1","c1",0,0,600,600);
   }
   c1->Divide(1,1);
   c1->cd();
   c1->SetLogy(1);
   c1->SetGridx(0);
   c1->SetGridy(0);
   c1->SetRightMargin(0.06);
   c1->SetTopMargin(0.06);
   c1->SetLeftMargin(0.14);
   c1->SetBottomMargin(0.14);
   c1->Draw();
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }
   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;

   Int_t ew = e2-e1;
   Int_t el1=e1-ew;
   Int_t el2=e1;
   Int_t er1=e2;
   Int_t er2=e2+ew;

   TString gateon="Gated on ";
   gateon+=(e1+e2)/2;
   gateon+=" keV #gamma-ray";
   /**** for real peak ****/
   TString gg1="&&ab_E>";
   gg1+=e1;
   TString gg2="&&ab_E<";
   gg2+=e2;
   TString gg=gg1+gg2;
   /**** background right ****/
   TString ggr1="&&ab_E>";
   ggr1+=er1;
   TString ggr2="&&ab_E<";
   ggr2+=er2;
   TString ggr=ggr1+ggr2;

   long time_L = Dtime_L*1e5;
   long time_U = Dtime_U*1e5;
   TH1F *h1 = new TH1F("h1","",time_bin,time_L,time_U);
   //TH1F *h1 = new TH1F("h1",name+gateon,time_bin,time_L,time_U);
   TH1F *h3 = new TH1F("h3",name,time_bin,time_L,time_U);

   decay_tree->Draw("t>>h1",nuclei+cut+gg,option);
   decay_tree->Draw("t>>h3",nuclei+cut+ggr,option);
   h1->Add(h3,-1);

   h1->GetYaxis()->SetRangeUser(0.001*h1->GetBinContent(h1->GetMaximumBin()),2*h1->GetBinContent(h1->GetMaximumBin()));

   h1->SetTitleSize(0.1);
   h1->GetXaxis()->SetLimits(0,Dtime_U);
   h1->GetXaxis()->SetTitle("Time (ms)");
   h1->GetXaxis()->SetLabelSize(0.07);
   h1->GetXaxis()->SetTitleSize(0.07);
   Int_t width = (Dtime_U-Dtime_L)/time_bin;
   h1->GetYaxis()->SetTitle(Form("Counts / %d ms",width));
   h1->GetYaxis()->SetLabelSize(0.07);
   h1->GetYaxis()->SetTitleSize(0.07);
   h1->SetStats(0);
   TF1 *myfit = new TF1("myfit",dNdt,fit_L,fit_R,24);
   myfit->SetLineColor(kRed);
   TF1 *decayp = new TF1("decayp",lX1,0,20000,24);
   decayp->SetLineColor(kBlack);
   decayp->SetNpx(5000);
   TF1 *decaybg = new TF1("decaybg",lX0,0,20000,24);
   decaybg->SetLineColor(6);
   decaybg->SetNpx(5000);
   //myfit->SetParLimits(8,0,1e-7);
   cout<<"the nuclei taken into account are:"<<endl;
   cout<<"X1"<<endl;

   read_fitting_parameters_p(myfit,name);

   h1->Fit("myfit","LR");
   h1->Draw(option);
   c1->Update();
   Double_t *para = myfit->GetParameters();
   Double_t *sig = myfit->GetParErrors();
   decayp->SetParameters(para);
   decaybg->SetParameters(para);
   decayp->Draw("same");
   decaybg->Draw("same");

   Double_t time1 = para[3];
   Double_t sigma1 = sig[3];
   Double_t t_half1 = time1;
   Double_t t_error1 = sigma1;
   cout<<"T_parent = "<<setiosflags(ios::fixed)<<setprecision(2)<<t_half1<<" ± "<<setiosflags(ios::fixed)<<setprecision(2)<<t_error1<<" ms"<<endl;
   TLatex text1, text2, text3;
   TString content0, content1, content2, content3;
   char text_half[100];
   char text_error[100];
   char text_pn[100];
   char text_chisqdf[100];
   sprintf(text_half,"%.1f",t_half1);
   sprintf(text_error,"%.1f",t_error1);
   sprintf(text_pn,"%.1f",0);
   sprintf(text_chisqdf,"%.3f",myfit->GetChisquare()/myfit->GetNDF());
   content1="T_{1/2}";
   //content+=name;
   content1+=" = ";
   content1+=text_half;
   content1+=" #pm ";
   content1+=text_error;
   content1+=" ms";
   //content2="P_{n} = ";
   //content2+=text_pn;
   //content2+=" %";
   name_nuclei_latex(Z,A,content2);
   content0 +="#beta-decay of";
   content0 +=content2;
   content2 +=" - ";
   content2 +=(e1+e2)/2;
   content2 +=" keV";
   content3="#chi^{2} #/NDF = ";
   content3+=text_chisqdf;
   text1.SetTextAlign(12);
   text1.SetTextSize(0.08);
   text1.SetNDC(kTRUE);
   //text1.DrawLatex(.5,.68,content1);
   text2.SetTextAlign(12);
   text2.SetTextSize(0.08);
   text2.SetNDC(kTRUE);
   text2.DrawLatex(.45,.88,content2);
   text3.SetTextAlign(12);
   text3.SetTextSize(0.08);
   text3.SetNDC(kTRUE);
   //text3.DrawLatex(.5,.78,gateon);
}

void read_fitting_parameters(TF1 *myfit, TString name){
   //myfit->SetParNames("X0","Pn","P2n","t11","t12","Pnbd","t21","t22","t31","t32","Pnbnd","t51","t52","t61","t62","t81","t82","C","p12","p22","p32","p52","p62","p82");
   TString decayfilename;
   decayfilename="decay_db/";
   decayfilename+=name;
   decayfilename+=".input";
   FILE *fp = fopen(decayfilename, "r");
   int n;
   double parameter, parameterL, parameterU;
   for(int i=0; i<18; i++){
      fscanf(fp, "%d %lf %lf %lf", &n, &parameter, &parameterL, &parameterU);
      //if(i==17){
      //   parameterL=sqrt(parameter);
      //   parameterU=sqrt(parameter);
      //}
      cout<<n<<", "<<parameter<<", "<<parameterL<<", "<<parameterU<<endl;
      myfit->SetParameter(n,parameter);
      if(parameterL==parameterU && parameterL==0){
         myfit->FixParameter(n,parameter);
      }else{
         myfit->SetParLimits(n,parameter-parameterL,parameter+parameterU);
      }
      for(int j=0; j<6; j++){ //set px2 depending on tx2
         int temp;
         if(j==0) temp=4;
         if(j==1) temp=7;
         if(j==2) temp=9;
         if(j==3) temp=12;
         if(j==4) temp=14;
         if(j==5) temp=16;
         if(n == temp){
            if(parameter!=0){
               if(temp==9){
                  myfit->SetParameter(18+j,0.25);
                  myfit->SetParLimits(18+j,0.25,0.25);
               }else{
                  myfit->SetParameter(18+j,0.25);
                  myfit->SetParLimits(18+j,0.25,0.25);
               }
            }else{
               myfit->SetParameter(18+j,0);
               myfit->FixParameter(18+j,0);
            }
         }
      }
   }
}

void read_fitting_parameters_p(TF1 *myfit, TString name){
   //myfit->SetParNames("X0","Pn","P2n","t11","t12","t21","t22","t31","t32","t51","t52","t61","t62","t81","t82","C","p11","p21","p31","p51","p61","p81");
   TString decayfilename;
   decayfilename="decay_db/";
   decayfilename+=name;
   decayfilename+=".input";
   FILE *fp = fopen(decayfilename, "r");
   int n;
   double parameter, parameterL, parameterU;
   for(int i=0; i<18; i++){
      fscanf(fp, "%d %lf %lf %lf", &n, &parameter, &parameterL, &parameterU);
      cout<<n<<", "<<parameter<<", "<<parameterL<<", "<<parameterU<<endl;
      if(i==0 || i==3 || i==17){
         if(i==0){
            parameter=parameter/10;
            parameterL=parameterL/10;
            parameterU=parameterU/2;
         }
         if(i==17){
            parameter=parameter/10;
            if(parameterL>0){
               parameterL=parameter;
            }
         }
         myfit->SetParameter(n,parameter);
         if(parameterL==parameterU && parameterL==0){
            myfit->FixParameter(n,parameter);
         }else{
            myfit->SetParLimits(n,parameter-parameterL,parameter+parameterU);
         }
      }else{
         myfit->SetParameter(n,0);
         myfit->FixParameter(n,0);
      }
   }
   for(int j=0; j<6; j++){
      myfit->SetParameter(18+j,0);
      myfit->FixParameter(18+j,0);
   }
}

void roofit_parname(int index, TString &parname){
   switch(index){
      case 0:
         parname="X0";
         break;
      case 1:
         parname="pn";
         break;
      case 2:
         parname="p2n";
         break;
      case 3:
         parname="t11";
         break;
      case 4:
         parname="t12";
         break;
      case 5:
         parname="pnd";
         break;
      case 6:
         parname="t21";
         break;
      case 7:
         parname="t22";
         break;
      case 8:
         parname="t31";
         break;
      case 9:
         parname="t32";
         break;
      case 10:
         parname="pnbnd";
         break;
      case 11:
         parname="t51";
         break;
      case 12:
         parname="t52";
         break;
      case 13:
         parname="t61";
         break;
      case 14:
         parname="t62";
         break;
      case 15:
         parname="t81";
         break;
      case 16:
         parname="t82";
         break;
      case 17:
         parname="C";
         break;
      case 18:
         parname="p12";
         break;
      case 19:
         parname="p22";
         break;
      case 20:
         parname="p32";
         break;
      case 21:
         parname="p52";
         break;
      case 22:
         parname="p62";
         break;
      case 23:
         parname="p82";
         break;
   }
}

RooRealVar *par[24];

void read_roofit_parameters(TString name){
   TString decayfilename;
   decayfilename="decay_db/";
   decayfilename+=name;
   decayfilename+=".input";
   FILE *fp = fopen(decayfilename, "r");
   int n;
   double parameter, parameterL, parameterU;
   for(int i=0; i<18; i++){
      fscanf(fp, "%d %lf %lf %lf", &n, &parameter, &parameterL, &parameterU);
      cout<<n<<", "<<parameter<<", "<<parameterL<<", "<<parameterU<<endl;
      if(i==0){
         parameter=1;
         parameterL=0;
         parameterU=0;
      }
      if(i==17){
         parameter=0.5;
         parameterL=0.5;
         parameterU=0.5;
      }
      TString parname;
      roofit_parname(i,parname);
      par[i]=new RooRealVar(parname,parname,parameter,parameter-parameterL,parameter+parameterU);
      for(int j=0; j<6; j++){
         int temp;
         if(j==0) temp=4;
         if(j==1) temp=7;
         if(j==2) temp=9;
         if(j==3) temp=12;
         if(j==4) temp=14;
         if(j==5) temp=16;
         if(n == temp){
            roofit_parname(18+j,parname);
            if(parameter!=0){
               par[18+j]=new RooRealVar(parname,parname,0.5,0.5,0.5);
            }else{
               par[18+j]=new RooRealVar(parname,parname,0,0,0);
            }
         }
      }
   }
   fclose(fp);
}

void read_roofit_parameters_p(TString name){
   TString decayfilename;
   decayfilename="decay_db/";
   decayfilename+=name;
   decayfilename+=".input";
   TString parname;
   FILE *fp = fopen(decayfilename, "r");
   int n;
   double parameter, parameterL, parameterU;
   for(int i=0; i<18; i++){
      fscanf(fp, "%d %lf %lf %lf", &n, &parameter, &parameterL, &parameterU);
      cout<<n<<", "<<parameter<<", "<<parameterL<<", "<<parameterU<<endl;
      roofit_parname(i,parname);
      if(i==0){
         par[i]=new RooRealVar(parname,parname,1,1,1);
      }else if(i==3){
         par[i]=new RooRealVar(parname,parname,parameter,parameter-parameterL,parameter+parameterU);
      }else if(i==17){
         par[i]=new RooRealVar(parname,parname,0.5,0,1);
      }else{
         par[i]=new RooRealVar(parname,parname,0,0,0);
      }
   }
   for(int j=0; j<6; j++){
      roofit_parname(18+j,parname);
      par[18+j]=new RooRealVar(parname,parname,0,0,0);
   }
   fclose(fp);
}

void roofit_decay(int Z, int A, int IF_GOG=0, int time_bin=400, double Dtime_L=5, double Dtime_U=4005){
   if(gROOT->FindObject("c1")==0){
      TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,500);
   }
   c1->Divide(1,1);
   c1->cd();
   c1->SetLogy(1);
   c1->SetGridx(0);
   c1->SetGridy(0);
   c1->SetRightMargin(0.06);
   c1->SetTopMargin(0.06);
   c1->SetLeftMargin(0.14);
   c1->SetBottomMargin(0.14);
   c1->Draw();
   TString name;
   name_nuclei(Z,A,name);
   RooRealVar t("t","t",Dtime_L,Dtime_U,"ms");
   if(IF_GOG==0){
      read_roofit_parameters(name);
   }else{
      read_roofit_parameters_p(name);
   }
   cout<<"come here"<<endl;
   RooMyDecay* roofit_decay = new RooMyDecay("roofit_decay","roofit_decay",t,*par[0],*par[1],*par[2],*par[3],*par[4],*par[5],*par[6],*par[7],*par[8],*par[9],*par[10],*par[11],*par[12],*par[13],*par[14],*par[15],*par[16],*par[17],*par[18],*par[19],*par[20],*par[21],*par[22],*par[23]);
   TString decayfilename;
   decayfilename="decay_db/";
   decayfilename+=name;
   RooDataSet* data=RooDataSet::read(decayfilename,RooArgList(t));
   RooPlot* xframe = t.frame(Title(" "));
   //roofit_decay->fitTo(*data,option);
   //RooFitResult* fitres = roofit_decay->fitTo(*data, Minos(kTRUE), PrintLevel(-1)) ;
   RooFitResult* fitres = roofit_decay->fitTo(*data, Minos(kTRUE)) ;
   data->plotOn(xframe,Binning(time_bin));
   roofit_decay->plotOn(xframe);
   xframe->Draw();
   TLatex text1, text2;
   TString content1, content2;
   TString content0, content1, content2;
   char text_half[100];
   char text_errorH[100];
   char text_errorL[100];
   char text_pn[100];
   sprintf(text_half,"%.1f",par[3]->getVal());
   sprintf(text_errorH,"%.1f",par[3]->getAsymErrorHi());
   sprintf(text_errorL,"%.1f",par[3]->getAsymErrorLo());
   sprintf(text_pn,"%.1f",par[1]->getValV()*100);
   content1="T_{1/2}";
   //content+=name;
   content1+=" = ";
   content1+=text_half;
   content1+=" ^{+";
   content1+=text_errorH;
   content1+="}_{";
   content1+=text_errorL;
   content1+="} ms";
   //content2="P_{n} = ";
   //content2+=text_pn;
   //content2+=" %";
   name_nuclei_latex(Z,A,content2);
   content0 +="#beta-decay of";
   content0 +=content2;
   text1.SetTextAlign(12);
   text1.SetTextSize(0.08);
   text1.SetNDC(kTRUE);
   //text1.DrawLatex(.5,.7,content1);
   cout<<content1<<endl;
   text2.SetTextAlign(12);
   text2.SetTextSize(0.08);
   text2.SetNDC(kTRUE);
   text2.DrawLatex(.5,.8,content0);
}

void check_depth_all(){
   TLatex text1, text2, text3, text4, text5, text6;
   text1.SetTextAlign(12);
   text1.SetTextSize(0.15);
   text1.SetNDC(kTRUE);
   text2.SetTextAlign(12);
   text2.SetTextSize(0.15);
   text2.SetNDC(kTRUE);
   text3.SetTextAlign(12);
   text3.SetTextSize(0.15);
   text3.SetNDC(kTRUE);
   text4.SetTextAlign(12);
   text4.SetTextSize(0.15);
   text4.SetNDC(kTRUE);
   text5.SetTextAlign(12);
   text5.SetTextSize(0.15);
   text5.SetNDC(kTRUE);
   text6.SetTextAlign(12);
   text6.SetTextSize(0.15);
   text6.SetNDC(kTRUE);
   gStyle->SetOptStat(0);
   TCanvas *c1 = new TCanvas("c1","range",0,0,1300,600);
   //TH1F *h1 = new TH1F("h1","84Ga",8,0,8);
   //TH1F *h2 = new TH1F("h2","83Ga",8,0,8);
   //TH1F *h3 = new TH1F("h3","80Zn",8,0,8);
   //TH1F *h4 = new TH1F("h4","78Cu",8,0,8);
   //TH1F *h5 = new TH1F("h5","77Cu",8,0,8);
   //TH1F *h6 = new TH1F("h6","75Ni",8,0,8);
   TH1F *h1 = new TH1F("h1","",8,0,8);
   TH1F *h2 = new TH1F("h2","",8,0,8);
   TH1F *h3 = new TH1F("h3","",8,0,8);
   TH1F *h4 = new TH1F("h4","",8,0,8);
   TH1F *h5 = new TH1F("h5","",8,0,8);
   TH1F *h6 = new TH1F("h6","",8,0,8);
   c1->Divide(3,2,0,0);
   c1->cd(1);
   c1->cd(1)->SetRightMargin(0.02);
   c1->cd(1)->SetLeftMargin(0.1);
   c1->cd(1)->SetGridy(0);
   h1->GetYaxis()->SetLabelSize(0.0);
   h1->GetYaxis()->SetNdivisions(4);
   ion->Draw("z>>h1","RIBeam_Zed==31&&RIBeam_Mass==84");
   h1->SetTitleSize(0.08);
   h1->GetXaxis()->SetTitle("Depth (mm)");
   h1->GetXaxis()->SetTitleSize(0.05);
   h1->GetXaxis()->SetLabelSize(0.05);
   text1.DrawLatex(.6,.8,"^{84}Ga");
   c1->cd(2);
   c1->cd(2)->SetRightMargin(0.02);
   c1->cd(2)->SetLeftMargin(0.02);
   c1->cd(2)->SetGridy(0);
   h2->GetYaxis()->SetLabelSize(0.0);
   h2->GetYaxis()->SetNdivisions(4);
   ion->Draw("z>>h2","RIBeam_Zed==31&&RIBeam_Mass==83");
   h2->SetTitleSize(0.08);
   text2.DrawLatex(.6,.8,"^{83}Ga");
   c1->cd(3);
   c1->cd(3)->SetRightMargin(0.02);
   c1->cd(3)->SetLeftMargin(0.02);
   c1->cd(3)->SetGridy(0);
   h3->GetYaxis()->SetLabelSize(0.0);
   h3->GetYaxis()->SetNdivisions(4);
   ion->Draw("z>>h3","RIBeam_Zed==30&&RIBeam_Mass==80");
   h3->SetTitleSize(0.08);
   h3->GetXaxis()->SetTitle("Depth (mm)");
   h3->GetXaxis()->SetTitleSize(0.05);
   h3->GetXaxis()->SetLabelSize(0.05);
   text3.DrawLatex(.6,.8,"^{80}Zn");
   c1->cd(4);
   c1->cd(4)->SetRightMargin(0.02);
   c1->cd(4)->SetLeftMargin(0.1);
   c1->cd(4)->SetBottomMargin(0.2);
   c1->cd(4)->SetGridy(0);
   h4->GetYaxis()->SetLabelSize(0.0);
   h4->GetYaxis()->SetNdivisions(4);
   ion->Draw("z>>h4","RIBeam_Zed==29&&RIBeam_Mass==78");
   h4->SetTitleSize(0.08);
   //h4->GetXaxis()->SetTitle("Depth (mm)");
   h4->GetXaxis()->SetTitleSize(0.08);
   h4->GetXaxis()->SetLabelSize(0.08);
   text4.DrawLatex(.2,.8,"^{78}Cu");
   c1->cd(5);
   c1->cd(5)->SetRightMargin(0.02);
   c1->cd(5)->SetLeftMargin(0.02);
   c1->cd(5)->SetBottomMargin(0.2);
   c1->cd(5)->SetGridy(0);
   h5->GetYaxis()->SetLabelSize(0.0);
   h5->GetYaxis()->SetNdivisions(4);
   ion->Draw("z>>h5","RIBeam_Zed==29&&RIBeam_Mass==77");
   h5->SetTitleSize(0.08);
   h5->GetXaxis()->SetTitle("Depth (mm)");
   h5->GetXaxis()->CenterTitle(1);
   h5->GetXaxis()->SetTitleSize(0.08);
   h5->GetXaxis()->SetLabelSize(0.08);
   text5.DrawLatex(.2,.8,"^{77}Cu");
   c1->cd(6);
   c1->cd(6)->SetRightMargin(0.02);
   c1->cd(6)->SetLeftMargin(0.02);
   c1->cd(6)->SetBottomMargin(0.2);
   c1->cd(6)->SetGridy(0);
   h6->GetYaxis()->SetLabelSize(0.0);
   h6->GetYaxis()->SetNdivisions(4);
   ion->Draw("z>>h6","RIBeam_Zed==28&&RIBeam_Mass==75");
   h6->SetTitleSize(0.08);
   //h6->GetXaxis()->SetTitle("Depth (mm)");
   h6->GetXaxis()->SetTitleSize(0.08);
   h6->GetXaxis()->SetLabelSize(0.08);
   text6.DrawLatex(.2,.8,"^{75}Ni");
}

/*********************************************
function to fit beta decay curve with
millisecond isomer.
The nuclei taken into account are:
 X1 --------> X2 ------> X3 ------> X4 (stable)
P_n --------> X5 ------> X6 ------> X7 (stable)
X1(isomer)-> X1 ------> X2 ------> X3 ------> X4 (stable)
            P-n ------> X5 ------> X6 ------> X7 (stable)
**********************************************/
Double_t lX0_isomer(Double_t *t, Double_t *p){
   return p[17];
}

Double_t lX1_isomer(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1;
   Double_t l1;
   Double_t X0=p[0];
   t1=p[3];
   p1=1-p[2];
   if(t1>0){
      l1=log(2)/t1;
      Double_t temp;
      result = TMath::Exp(-1*l1*t[0])*p1;
   }
   return result*X0;
}

Double_t lXm_isomer(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1;
   Double_t l1;
   Double_t X0=p[0];
   t1=p[4];
   pm=p[2];
   if(t1>0){
      l1=log(2)/t1;
      Double_t temp;
      result = TMath::Exp(-1*l1*t[0])*pm;
   }
   return result*X0;
}

Double_t lX2_isomer(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2;
   Double_t l1, l2;
   Double_t X0=p[0];
   Double_t pb=1-p[1];
   t1=p[3];
   t2=p[6];
   p1=1-p[2];
   if(t1>0 && t2>0 && t1!=t2){
      l1=log(2)/t1;
      l2=log(2)/t2;
      result = l2*(TMath::Exp(-1*l1*t[0])/(l2-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2))*p1;
   }
   return X0*pb*result;
}

Double_t lX1m_isomer(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2;
   Double_t l1, l2;
   Double_t X0=p[0];
   t1=p[4];
   t2=p[3];
   pm=p[2];
   if(t1>0 && t2>0 && t1!=t2){
      l1=log(2)/t1;
      l2=log(2)/t2;
      result = l2*(TMath::Exp(-1*l1*t[0])/(l2-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2))*pm;
   }
   return X0*result;
}

Double_t lX3_isomer(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2, t3, p3;
   Double_t l1, l2, l3;
   Double_t X0=p[0];
   Double_t pb=1-p[1];
   t1=p[3];
   t2=p[6];
   t3=p[8];
   p1=1-p[2];
   result = 0;
   if(t1>0 && t2>0 && t3>0 && t1!=t2 && t1!=t3 && t2!=t3){
      l1=log(2)/t1;
      l2=log(2)/t2;
      l3=log(2)/t3;
      Double_t temp;
      result = l2*l3*(TMath::Exp(-1*l1*t[0])/(l2-l1)/(l3-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2)/(l3-l2)+TMath::Exp(-1*l3*t[0])/(l1-l3)/(l2-l3))*p1;
   }
   return X0*pb*result;
}

Double_t lX2m_isomer(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2, t3, p3;
   Double_t l1, l2, l3;
   Double_t X0=p[0];
   Double_t pb=1-p[1];
   t1=p[4];
   t2=p[3];
   t3=p[6];
   pm=p[2];
   result = 0;
   if(t1>0 && t2>0 && t3>0 && t1!=t2 && t1!=t3 && t2!=t3){
      l1=log(2)/t1;
      l2=log(2)/t2;
      l3=log(2)/t3;
      result = l2*l3*(TMath::Exp(-1*l1*t[0])/(l2-l1)/(l3-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2)/(l3-l2)+TMath::Exp(-1*l3*t[0])/(l1-l3)/(l2-l3))*pm;
   }
   return X0*pb*result;
}

Double_t lX3m_isomer(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2, t3, p3, t4, p4;
   Double_t l1, l2, l3, l4;
   Double_t X0=p[0];
   Double_t pb=1-p[1];
   t1=p[4];
   t2=p[3];
   t3=p[6];
   t4=p[8];
   pm=p[2];
   result = 0;
   if(t1>0 && t2>0 && t3>0 && t4>0 && t1!=t2 && t1!=t3 && t1!=t4 && t2!=t3 && t2!=t4 && t3!=t4){
      l1=log(2)/t1;
      l2=log(2)/t2;
      l3=log(2)/t3;
      l4=log(2)/t4;
      result = l2*l3*l4*(TMath::Exp(-1*l1*t[0])/(l2-l1)/(l3-l1)/(l4-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2)/(l3-l2)/(l4-l2)+TMath::Exp(-1*l3*t[0])/(l1-l3)/(l2-l3)/(l4-l3)+TMath::Exp(-1*l4*t[0])/(l1-l4)/(l2-l4)/(l3-l4))*pm;
   }
   return X0*pb*result;
}

Double_t lX5_isomer(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t5, p5;
   Double_t l1, l5;
   Double_t X0=p[0];
   Double_t pn=p[1];
   t1=p[3];
   t5=p[11];
   p1=1-p[2];
   if(t1>0 && t5>0 && t1!=t5){
      l1=log(2)/t1;
      l5=log(2)/t5;
      result = l5*(TMath::Exp(-1*l1*t[0])/(l5-l1)+TMath::Exp(-1*l5*t[0])/(l1-l5))*p1;
   }
   return X0*pn*result;
}

Double_t lX5m_isomer(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2, t3, p3;
   Double_t l1, l2, l3;
   Double_t X0=p[0];
   Double_t pn=p[1];
   t1=p[4];
   t2=p[3];
   t3=p[11];
   pm=p[2];
   result = 0;
   if(t1>0 && t2>0 && t3>0 && t1!=t2 && t1!=t3 && t2!=t3){
      l1=log(2)/t1;
      l2=log(2)/t2;
      l3=log(2)/t3;
      result = l2*l3*(TMath::Exp(-1*l1*t[0])/(l2-l1)/(l3-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2)/(l3-l2)+TMath::Exp(-1*l3*t[0])/(l1-l3)/(l2-l3))*pm;
   }
   return X0*pn*result;
}

Double_t lX6_isomer(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2, t3, p3;
   Double_t l1, l2, l3;
   Double_t X0=p[0];
   Double_t pn=p[1];
   t1=p[3];
   t2=p[11];
   t3=p[13];
   p1=1-p[2];
   result = 0;
   if(t1>0 && t2>0 && t3>0 && t1!=t2 && t1!=t3 && t2!=t3){
      l1=log(2)/t1;
      l2=log(2)/t2;
      l3=log(2)/t3;
      result = l2*l3*(TMath::Exp(-1*l1*t[0])/(l2-l1)/(l3-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2)/(l3-l2)+TMath::Exp(-1*l3*t[0])/(l1-l3)/(l2-l3))*p1;
   }
   return X0*pn*result;
}

Double_t lX6m_isomer(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2, t3, p3, t4, p4;
   Double_t l1, l2, l3, l4;
   Double_t X0=p[0];
   Double_t pn=p[1];
   t1=p[4];
   t2=p[3];
   t3=p[11];
   t4=p[13];
   pm=p[2];
   result = 0;
   if(t1>0 && t2>0 && t3>0 && t4>0 && t1!=t2 && t1!=t3 && t1!=t4 && t2!=t3 && t2!=t4 && t3!=t4){
      l1=log(2)/t1;
      l2=log(2)/t2;
      l3=log(2)/t3;
      l4=log(2)/t4;
      result = l2*l3*l4*(TMath::Exp(-1*l1*t[0])/(l2-l1)/(l3-l1)/(l4-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2)/(l3-l2)/(l4-l2)+TMath::Exp(-1*l3*t[0])/(l1-l3)/(l2-l3)/(l4-l3)+TMath::Exp(-1*l4*t[0])/(l1-l4)/(l2-l4)/(l3-l4))*pm;
   }
   return X0*pn*result;
}

Double_t dNdt_isomer(Double_t *t, Double_t *p){
   if(t[0]>0 && (p[1]<=1)){
      return lX0_isomer(t,p)+lXm_isomer(t,p)+lX1_isomer(t,p)+lX1m_isomer(t,p)+lX2_isomer(t,p)+lX2m_isomer(t,p)+lX3_isomer(t,p)+lX3m_isomer(t,p)+lX5_isomer(t,p)+lX5m_isomer(t,p)+lX6_isomer(t,p)+lX6m_isomer(t,p);
   }
   else{
      return 0;
   }
}

fit_decay_isomer(Int_t Z, Int_t A, TString cut="", TString option="E", int time_bin=5000, double Dtime_L=0, double Dtime_U=5000, double fit_L=5, double fit_R=5000){
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      cout<<"No tree called decay is found"<<endl;
      return 0;
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")==0){
      TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,500);
   }
   c1->Divide(1,1);
   c1->cd();
   c1->SetLogy(1);
   c1->Draw();
   c1->SetGridx(0);
   c1->SetGridy(0);
   c1->SetRightMargin(0.06);
   c1->SetTopMargin(0.06);
   c1->SetLeftMargin(0.14);
   c1->SetBottomMargin(0.14);
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }
   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+And+name;
      nuclei=nuclei+")";
   }

   long time_L = Dtime_L*1e5;
   long time_U = Dtime_U*1e5;
   TH1F *h1 = new TH1F("h1","",time_bin,time_L,time_U);
   //TH1F *h1 = new TH1F("h1","Decay curve",time_bin,time_L,time_U);
   decay_tree->Draw("t>>h1",nuclei+cut,option);
   h1->Sumw2();
   h1->GetYaxis()->SetRangeUser(0.001*h1->GetBinContent(h1->GetMaximumBin()),2*h1->GetBinContent(h1->GetMaximumBin()));

   h1->SetTitleSize(0.1);
   h1->GetXaxis()->SetLimits(0,Dtime_U);
   h1->GetXaxis()->SetTitle("Time (ms)");
   h1->GetXaxis()->SetLabelSize(0.07);
   h1->GetXaxis()->SetTitleSize(0.07);
   Int_t width = (Dtime_U-Dtime_L)/time_bin;
   h1->GetYaxis()->SetTitle(Form("Counts / %d ms",width));
   h1->GetYaxis()->SetLabelSize(0.07);
   h1->GetYaxis()->SetTitleSize(0.07);
   h1->SetStats(0);
   TF1 *myfit = new TF1("myfit",dNdt_isomer,fit_L,fit_R,22);
   myfit->SetLineColor(kRed);
   TF1 *decayp = new TF1("decayp",lX1_isomer,0,20000,22);
   decayp->SetLineColor(kBlack);
   TF1 *decaypm = new TF1("decaypm",lXm_isomer,0,20000,22);
   decaypm->SetLineColor(kBlue);
   TF1 *decayd = new TF1("decayd",lX2_isomer,0,20000,22);
   decayd->SetLineColor(kGreen);
   TF1 *decaybg = new TF1("decaybg",lX0_isomer,0,20000,22);
   decaybg->SetLineColor(6);

   cout<<"the nuclei taken into account are:"<<endl;
   cout<<"X1 -----   -> X2 ------> X3 ------> X4 (stable)"<<endl;
   cout<<"X1 (isomer)-> X1 ------> X2 ------> X3 "<<endl;

   read_fitting_parameters(myfit,name);

   //h1->Fit("myfit","WLR");
   h1->Fit("myfit","LR");
   h1->Draw(option);
   c1->Update();
   Double_t *para = myfit->GetParameters();
   Double_t *sig = myfit->GetParErrors();
   decayp->SetParameters(para);
   decaypm->SetParameters(para);
   decayd->SetParameters(para);
   decaybg->SetParameters(para);
   decayp->Draw("same");
   decaypm->Draw("same");
   decayd->Draw("same");
   decaybg->Draw("same");

   Double_t time1 = para[3];
   Double_t sigma1 = sig[3];
   Double_t t_half1 = time1;
   Double_t t_error1 = sigma1;
   Double_t time2 = para[4];
   Double_t sigma2 = sig[4];
   Double_t t_half2 = time2;
   Double_t t_error2 = sigma2;
   Double_t time3 = para[6];
   Double_t sigma3 = sig[6];
   Double_t t_half3 = time3;
   Double_t t_error3 = sigma3;
   cout<<"T_parent = "<<setiosflags(ios::fixed)<<setprecision(2)<<t_half1<<" ± "<<setiosflags(ios::fixed)<<setprecision(2)<<t_error1<<" ms"<<endl;
   cout<<"T_parent_isomer = "<<setiosflags(ios::fixed)<<setprecision(2)<<t_half2<<" ± "<<setiosflags(ios::fixed)<<setprecision(2)<<t_error2<<" ms"<<endl;
   //cout<<"T_daughter = "<<setiosflags(ios::fixed)<<setprecision(2)<<t_half2<<" ± "<<setiosflags(ios::fixed)<<setprecision(2)<<t_error2<<" ms"<<endl;
   //cout<<"T_betan = "<<setiosflags(ios::fixed)<<setprecision(2)<<t_half3<<" ± "<<setiosflags(ios::fixed)<<setprecision(2)<<t_error3<<" ms"<<endl;
   cout<<"Total parent decay = "<<decayp->Integral(0,20000)/width<<" counts"<<endl;
   cout<<"Total daughter decay = "<<decaypm->Integral(0,200000)/width<<" counts"<<endl;
   //cout<<"Total grand daughter decay = "<<decaygd->Integral(0,200000)/width<<" counts"<<endl;
   //cout<<"Portion for parent decay in 5 - 105 ms = "<<decayp->Integral(5,105)/decayp->Integral(0,20000)*100<<"%"<<endl;
   //cout<<"Portion for parent decay in 5 - 205 ms = "<<decayp->Integral(5,205)/decayp->Integral(0,20000)*100<<"%"<<endl;
   //if(para[1]<1){
   //   cout<<"Portion for daughter decay in 5 - 1005 ms = "<<decayd->Integral(5,1005)/decayd->Integral(0,20000)*100<<"%"<<endl;
   //   cout<<"Portion for daughter decay in 5 - 2005 ms = "<<decayd->Integral(5,2005)/decayd->Integral(0,20000)*100<<"%"<<endl;
   //}
   //if(para[1]>0){
   //   cout<<"Portion for beta-n daughter decay in 5 - 1005 ms = "<<decayn->Integral(5,1005)/decayn->Integral(0,20000)*100<<"%"<<endl;
   //   cout<<"Portion for beta-n daughter decay in 5 - 2005 ms = "<<decayn->Integral(5,2005)/decayn->Integral(0,20000)*100<<"%"<<endl;
   //}
   TLatex text1, text2, text3;
   TString content0, content1, content2, content3;
   char text_half[100];
   char text_error[100];
   char text_pn[100];
   char text_chisqdf[100];
   sprintf(text_half,"%.1f",t_half1);
   sprintf(text_error,"%.1f",t_error1);
   sprintf(text_pn,"%.1f",para[1]*100);
   sprintf(text_chisqdf,"%.3f",myfit->GetChisquare()/myfit->GetNDF());
   content1="T_{1/2}";
   //content+=name;
   content1+=" = ";
   content1+=text_half;
   content1+=" #pm ";
   content1+=text_error;
   content1+=" ms";
   //content2="P_{n} = ";
   //content2+=text_pn;
   //content2+=" %";
   name_nuclei_latex(Z,A,content2);
   content0 +="#beta-decay of";
   content0 +=content2;
   content3="#chi^{2} #/NDF = ";
   content3+=text_chisqdf;
   text1.SetTextAlign(12);
   text1.SetTextSize(0.08);
   text1.SetNDC(kTRUE);
   //text1.DrawLatex(.5,.78,content1);
   text2.SetTextAlign(12);
   text2.SetTextSize(0.08);
   text2.SetNDC(kTRUE);
   cout<<content3<<endl;
   //text2.DrawLatex(.5,.68,content3);
   text3.SetTextAlign(12);
   text3.SetTextSize(0.08);
   text3.SetNDC(kTRUE);
   text3.DrawLatex(.5,.88,content0);
}

/*********************************************
function to fit beta decay curve with
millisecond isomer.
The nuclei taken into account are:
 X1 --------> X2 ------> X3 ------> X4 (stable)
            X2(isomer)-> X3 ------> X4 (stable)
            X2(isomer)-> X2 ------> X3 ------> X4 (stable)
P_n --------> X5 ------> X6 ------> X7 (stable)
**********************************************/
Double_t lX0_cu77(Double_t *t, Double_t *p){
   return p[17];
}

Double_t lX1_cu77(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1;
   Double_t l1;
   Double_t X0=p[0];
   t1=p[3];
   p1=1;
   if(t1>0){
      l1=log(2)/t1;
      Double_t temp;
      result = TMath::Exp(-1*l1*t[0])*p1;
   }
   return result*X0;
}

Double_t lX2_cu77(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2;
   Double_t l1, l2;
   Double_t X0=p[0];
   Double_t pb=1-p[1];
   t1=p[3];
   t2=p[6];
   p1=1-p[2];
   if(t1>0 && t2>0 && t1!=t2){
      l1=log(2)/t1;
      l2=log(2)/t2;
      result = l2*(TMath::Exp(-1*l1*t[0])/(l2-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2))*p1;
   }
   return X0*pb*result;
}

Double_t lX2m1_cu77(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2;
   Double_t l1, l2;
   Double_t X0=p[0];
   Double_t pb=1-p[1];
   t1=p[3];
   t2=p[7];
   p1=(p[2])*0.66;
   if(t1>0 && t2>0 && t1!=t2){
      l1=log(2)/t1;
      l2=log(2)/t2;
      result = l2*(TMath::Exp(-1*l1*t[0])/(l2-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2))*p1;
   }
   return X0*pb*result;
}

Double_t lX2m2_cu77(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2, t3, p3;
   Double_t l1, l2, l3;
   Double_t X0=p[0];
   Double_t pb=1-p[1];
   t1=p[3];
   t2=p[7];
   t3=p[6];
   p1=(p[2])*0.33;
   result = 0;
   if(t1>0 && t2>0 && t3>0 && t1!=t2 && t1!=t3 && t2!=t3){
      l1=log(2)/t1;
      l2=log(2)/t2;
      l3=log(2)/t3;
      result = l2*l3*(TMath::Exp(-1*l1*t[0])/(l2-l1)/(l3-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2)/(l3-l2)+TMath::Exp(-1*l3*t[0])/(l1-l3)/(l2-l3))*p1;
   }
   return X0*pb*result;
}

Double_t lX3_cu77(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2, t3, p3;
   Double_t l1, l2, l3;
   Double_t X0=p[0];
   Double_t pb=1-p[1];
   t1=p[3];
   t2=p[6];
   t3=p[8];
   p1=1-p[2];
   result = 0;
   if(t1>0 && t2>0 && t3>0 && t1!=t2 && t1!=t3 && t2!=t3){
      l1=log(2)/t1;
      l2=log(2)/t2;
      l3=log(2)/t3;
      Double_t temp;
      result = l2*l3*(TMath::Exp(-1*l1*t[0])/(l2-l1)/(l3-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2)/(l3-l2)+TMath::Exp(-1*l3*t[0])/(l1-l3)/(l2-l3))*p1;
   }
   return X0*pb*result;
}

Double_t lX3m1_cu77(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2, t3, p3;
   Double_t l1, l2, l3;
   Double_t X0=p[0];
   Double_t pb=1-p[1];
   t1=p[3];
   t2=p[7];
   t3=p[8];
   p1=(p[2])*0.66;
   result = 0;
   if(t1>0 && t2>0 && t3>0 && t1!=t2 && t1!=t3 && t2!=t3){
      l1=log(2)/t1;
      l2=log(2)/t2;
      l3=log(2)/t3;
      Double_t temp;
      result = l2*l3*(TMath::Exp(-1*l1*t[0])/(l2-l1)/(l3-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2)/(l3-l2)+TMath::Exp(-1*l3*t[0])/(l1-l3)/(l2-l3))*p1;
   }
   return X0*pb*result;
}

Double_t lX3m2_cu77(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2, t3, p3, t4, p4;
   Double_t l1, l2, l3, l4;
   Double_t X0=p[0];
   Double_t pb=1-p[1];
   t1=p[3];
   t2=p[7];
   t3=p[6];
   t4=p[8];
   p1=(p[2])*0.33;
   result = 0;
   if(t1>0 && t2>0 && t3>0 && t4>0 && t1!=t2 && t1!=t3 && t1!=t4 && t2!=t3 && t2!=t4 && t3!=t4){
      l1=log(2)/t1;
      l2=log(2)/t2;
      l3=log(2)/t3;
      l4=log(2)/t4;
      result = l2*l3*l4*(TMath::Exp(-1*l1*t[0])/(l2-l1)/(l3-l1)/(l4-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2)/(l3-l2)/(l4-l2)+TMath::Exp(-1*l3*t[0])/(l1-l3)/(l2-l3)/(l4-l3)+TMath::Exp(-1*l4*t[0])/(l1-l4)/(l2-l4)/(l3-l4))*p1;
   }
   return X0*pb*result;
}

Double_t lX5_cu77(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t5, p5;
   Double_t l1, l5;
   Double_t X0=p[0];
   Double_t pn=p[1];
   t1=p[3];
   t5=p[11];
   p1=1;
   if(t1>0 && t5>0 && t1!=t5){
      l1=log(2)/t1;
      l5=log(2)/t5;
      result = l5*(TMath::Exp(-1*l1*t[0])/(l5-l1)+TMath::Exp(-1*l5*t[0])/(l1-l5))*p1;
   }
   return X0*pn*result;
}

Double_t lX6_cu77(Double_t *t, Double_t *p){
   Double_t result;
   Double_t t1, p1, t2, p2, t3, p3;
   Double_t l1, l2, l3;
   Double_t X0=p[0];
   Double_t pn=p[1];
   t1=p[3];
   t2=p[11];
   t3=p[13];
   p1=1;
   result = 0;
   if(t1>0 && t2>0 && t3>0 && t1!=t2 && t1!=t3 && t2!=t3){
      l1=log(2)/t1;
      l2=log(2)/t2;
      l3=log(2)/t3;
      result = l2*l3*(TMath::Exp(-1*l1*t[0])/(l2-l1)/(l3-l1)+TMath::Exp(-1*l2*t[0])/(l1-l2)/(l3-l2)+TMath::Exp(-1*l3*t[0])/(l1-l3)/(l2-l3))*p1;
   }
   return X0*pn*result;
}

Double_t dNdt_cu77(Double_t *t, Double_t *p){
   if(t[0]>0 && (p[1]<=1)){
      return lX0_cu77(t,p)+lX1_cu77(t,p)+lX2_cu77(t,p)+lX2m1_cu77(t,p)+lX2m2_cu77(t,p)+lX3_cu77(t,p)+lX3m1_cu77(t,p)+lX3m2_cu77(t,p)+lX5_cu77(t,p)+lX6_cu77(t,p);
   }
   else{
      return 0;
   }
}

fit_decay_cu77(Int_t Z, Int_t A, TString cut="", TString option="E", int time_bin=5000, double Dtime_L=0, double Dtime_U=5000, double fit_L=5, double fit_R=5000){
   TString decay_or_tree;
   if(gROOT->FindObject("decay")!=0){
      decay_or_tree = "decay";
   }else{
      cout<<"No tree called decay is found"<<endl;
      return 0;
   }
   TChain *decay_tree = (TChain *)gROOT->FindObject(decay_or_tree);
   if(gROOT->FindObject("c1")==0){
      TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,500);
   }
   c1->Divide(1,1);
   c1->cd();
   c1->SetLogy(1);
   c1->Draw();
   c1->SetGridx(0);
   c1->SetGridy(0);
   c1->SetRightMargin(0.06);
   c1->SetTopMargin(0.06);
   c1->SetLeftMargin(0.14);
   c1->SetBottomMargin(0.14);
   TString name;
   TString nuclei;
   TString Zed="&&Zed==";
   TString Mass="Mass==";
   TString And="&&";
   TString OR="||";
   if(cut.Sizeof()>1){
      cut=And+cut;
   }
   name_nuclei(Z,A,name);
   Zed+=Z;
   Mass+=A;
   nuclei=Mass+Zed;
   if(gROOT->FindObject(name)!=0){
      nuclei="("+nuclei;
      nuclei=nuclei+And+name;
      nuclei=nuclei+")";
   }

   long time_L = Dtime_L*1e5;
   long time_U = Dtime_U*1e5;
   TH1F *h1 = new TH1F("h1","",time_bin,time_L,time_U);
   //TH1F *h1 = new TH1F("h1","Decay curve",time_bin,time_L,time_U);
   decay_tree->Draw("t>>h1",nuclei+cut,option);
   h1->Sumw2();
   h1->GetYaxis()->SetRangeUser(0.001*h1->GetBinContent(h1->GetMaximumBin()),2*h1->GetBinContent(h1->GetMaximumBin()));

   h1->SetTitleSize(0.1);
   h1->GetXaxis()->SetLimits(0,Dtime_U);
   h1->GetXaxis()->SetTitle("Time (ms)");
   h1->GetXaxis()->SetLabelSize(0.07);
   h1->GetXaxis()->SetTitleSize(0.07);
   Int_t width = (Dtime_U-Dtime_L)/time_bin;
   h1->GetYaxis()->SetTitle(Form("Counts / %d ms",width));
   h1->GetYaxis()->SetLabelSize(0.07);
   h1->GetYaxis()->SetTitleSize(0.07);
   h1->SetStats(0);
   TF1 *myfit = new TF1("myfit",dNdt_cu77,fit_L,fit_R,22);
   myfit->SetLineColor(kRed);
   TF1 *decayp = new TF1("decayp",lX1_cu77,0,20000,22);
   decayp->SetLineColor(kBlack);
   TF1 *decayd = new TF1("decayd",lX2_cu77,0,20000,22);
   decayd->SetLineColor(kGreen);
   TF1 *decaybg = new TF1("decaybg",lX0_cu77,0,20000,22);
   decaybg->SetLineColor(6);

   cout<<"the nuclei taken into account are:"<<endl;
   cout<<"X1 -----   -> X2 ------> X3 ------> X4 (stable)"<<endl;
   cout<<"        -> X2 (isomer)-> X3 ------> X4 (stable)"<<endl;
   cout<<"        -> X2 (isomer)-> X2 ------> X3 ------> X4 (stable)"<<endl;
   cout<<"           -> X5 ------> X6 ------> X7 (stable)"<<endl;

   read_fitting_parameters(myfit,name);

   //h1->Fit("myfit","WLR");
   h1->Fit("myfit","LR");
   h1->Draw(option);
   c1->Update();
   Double_t *para = myfit->GetParameters();
   Double_t *sig = myfit->GetParErrors();
   decayp->SetParameters(para);
   decayd->SetParameters(para);
   decaybg->SetParameters(para);
   decayp->Draw("same");
   decayd->Draw("same");
   decaybg->Draw("same");

   Double_t time1 = para[3];
   Double_t sigma1 = sig[3];
   Double_t t_half1 = time1;
   Double_t t_error1 = sigma1;
   Double_t time2 = para[4];
   Double_t sigma2 = sig[4];
   Double_t t_half2 = time2;
   Double_t t_error2 = sigma2;
   Double_t time3 = para[6];
   Double_t sigma3 = sig[6];
   Double_t t_half3 = time3;
   Double_t t_error3 = sigma3;
   cout<<"T_parent = "<<setiosflags(ios::fixed)<<setprecision(2)<<t_half1<<" ± "<<setiosflags(ios::fixed)<<setprecision(2)<<t_error1<<" ms"<<endl;
   TLatex text1, text2, text3;
   TString content0, content1, content2, content3;
   char text_half[100];
   char text_error[100];
   char text_pn[100];
   char text_chisqdf[100];
   sprintf(text_half,"%.1f",t_half1);
   sprintf(text_error,"%.1f",t_error1);
   sprintf(text_pn,"%.1f",para[1]*100);
   sprintf(text_chisqdf,"%.3f",myfit->GetChisquare()/myfit->GetNDF());
   content1="T_{1/2}";
   //content+=name;
   content1+=" = ";
   content1+=text_half;
   content1+=" #pm ";
   content1+=text_error;
   content1+=" ms";
   //content2="P_{n} = ";
   //content2+=text_pn;
   //content2+=" %";
   name_nuclei_latex(Z,A,content2);
   content0 +="#beta-decay of";
   content0 +=content2;
   content3="#chi^{2} #/NDF = ";
   content3+=text_chisqdf;
   text1.SetTextAlign(12);
   text1.SetTextSize(0.08);
   text1.SetNDC(kTRUE);
   //text1.DrawLatex(.5,.78,content1);
   text2.SetTextAlign(12);
   text2.SetTextSize(0.08);
   text2.SetNDC(kTRUE);
   cout<<content3<<endl;
   //text2.DrawLatex(.5,.68,content3);
   text3.SetTextAlign(12);
   text3.SetTextSize(0.08);
   text3.SetNDC(kTRUE);
   text3.DrawLatex(.5,.88,content0);
}

void roofit_parname_full(int index, TString &parname){
   switch(index){
      case 0:
         parname="X0";
         break;
      case 1:
         parname="pn";
         break;
      case 2:
         parname="p2n";
         break;
      case 3:
         parname="t1";
         break;
      case 4:
         parname="pn2";
         break;
      case 5:
         parname="t2";
         break;
      case 6:
         parname="pn3";
         break;
      case 7:
         parname="t3";
         break;
      case 8:
         parname="t4";
         break;
      case 9:
         parname="pn5";
         break;
      case 10:
         parname="t5";
         break;
      case 11:
         parname="pn6";
         break;
      case 12:
         parname="t6";
         break;
      case 13:
         parname="t7";
         break;
      case 14:
         parname="pn8";
         break;
      case 15:
         parname="t8";
         break;
      case 16:
         parname="t9";
         break;
      case 17:
         parname="t10";
         break;
      case 18:
         parname="C";
         break;
   }
}

void read_roofit_parameters_full(TString name){
   TString decayfilename;
   decayfilename="decay_db/";
   decayfilename+=name;
   decayfilename+="_full.input";
   FILE *fp = fopen(decayfilename, "r");
   int n;
   double parameter, parameterL, parameterU;
   for(int i=0; i<19; i++){
      fscanf(fp, "%d %lf %lf %lf", &n, &parameter, &parameterL, &parameterU);
      cout<<n<<", "<<parameter<<", "<<parameterL<<", "<<parameterU<<endl;
      if(i==0){
         parameter=1;
         parameterL=0;
         parameterU=0;
      }
      if(i==18){
         parameter=0.5;
         parameterL=0.5;
         parameterU=0.5;
      }
      TString parname;
      roofit_parname_full(i,parname);
      par[i]=new RooRealVar(parname,parname,parameter,parameter-parameterL,parameter+parameterU);
   }
   fclose(fp);
}

void roofit_decay_full(int Z, int A, int IF_GOG=0, int time_bin=400, double Dtime_L=5, double Dtime_U=4005){
   if(gROOT->FindObject("c1")==0){
      TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,500);
   }
   c1->Divide(1,1);
   c1->cd();
   c1->SetLogy(1);
   c1->SetGridx(0);
   c1->SetGridy(0);
   c1->SetRightMargin(0.06);
   c1->SetTopMargin(0.06);
   c1->SetLeftMargin(0.14);
   c1->SetBottomMargin(0.14);
   c1->Draw();
   TString name;
   name_nuclei(Z,A,name);
   RooRealVar t("t","t",Dtime_L,Dtime_U,"ms");

   read_roofit_parameters_full(name);
   cout<<"come here"<<endl;

   RooMyDecay_full* roofit_decay = new RooMyDecay_full("roofit_decay","roofit_decay",t,*par[0],*par[1],*par[2],*par[3],*par[4],*par[5],*par[6],*par[7],*par[8],*par[9],*par[10],*par[11],*par[12],*par[13],*par[14],*par[15],*par[16],*par[17],*par[18]);
   TString decayfilename;
   decayfilename="decay_db/";
   decayfilename+=name;
   RooDataSet* data=RooDataSet::read(decayfilename,RooArgList(t));
   RooPlot* xframe = t.frame(Title(" "));
   //roofit_decay->fitTo(*data,option);
   //RooFitResult* fitres = roofit_decay->fitTo(*data, Minos(kTRUE), PrintLevel(-1)) ;
   RooFitResult* fitres = roofit_decay->fitTo(*data, Minos(kTRUE)) ;
   data->plotOn(xframe,Binning(time_bin));
   roofit_decay->plotOn(xframe);
   xframe->Draw();
   TLatex text1, text2;
   TString content1, content2;
   TString content0, content1, content2;
   char text_half[100];
   char text_errorH[100];
   char text_errorL[100];
   char text_pn[100];
   sprintf(text_half,"%.1f",par[3]->getVal());
   sprintf(text_errorH,"%.1f",par[3]->getAsymErrorHi());
   sprintf(text_errorL,"%.1f",par[3]->getAsymErrorLo());
   sprintf(text_pn,"%.1f",par[1]->getValV()*100);
   content1="T_{1/2}";
   //content+=name;
   content1+=" = ";
   content1+=text_half;
   content1+=" ^{+";
   content1+=text_errorH;
   content1+="}_{";
   content1+=text_errorL;
   content1+="} ms";
   //content2="P_{n} = ";
   //content2+=text_pn;
   //content2+=" %";
   name_nuclei_latex(Z,A,content2);
   content0 +="#beta-decay of";
   content0 +=content2;
   text1.SetTextAlign(12);
   text1.SetTextSize(0.08);
   text1.SetNDC(kTRUE);
   //text1.DrawLatex(.5,.7,content1);
   cout<<content1<<endl;
   text2.SetTextAlign(12);
   text2.SetTextSize(0.08);
   text2.SetNDC(kTRUE);
   text2.DrawLatex(.5,.8,content0);
}

