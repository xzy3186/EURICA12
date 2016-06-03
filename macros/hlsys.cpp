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

////calculation for half-live from exponentian law.
//Double_t shell(Int_t Z, Int_t N){
//   Double_t c5 = 0.9039;
//   Double_t c6 = 7.7139;
//   Double_t result;
//   result = c5*(TMath::Exp(-1*(N-29)*(N-29)/15.0)+TMath::Exp(-1*(N-50)*(N-50)/37.0)+TMath::Exp(-1*(N-85)*(N-85)/9.0)+TMath::Exp(-1*(N-131)*(N-131)/3.0))+c6*TMath::Exp(-1*((Z-51.5)*(Z-51.5)+(N-80.5)*(N-80.5))/1.9);
//   return result;
//}
//
//Double_t Calhalflife(Int_t Z, Int_t N){
//   Double_t c1 = 3.37e-4;
//   Double_t c2 = -0.2558;
//   Double_t c3 = 0.4028;
//   Double_t c4 = -1.0100;
//
//   return TMath::Power(10,(c1*Z+c2)*N+c3*Z+c4+shell(Z,N))*1000;
//}
//
//gStyle->SetLegendBorderSize(0);
//gStyle->SetLegendFillColor(0);

Double_t p_exparb[10][100];//arbitrary variable
Double_t p_exparbL[10][100];
Double_t p_exparbR[10][100];
Double_t p_expQ_5[10][100];//Q^-5
Double_t p_expQ_5L[10][100];
Double_t p_expQ_5R[10][100];
Double_t p_exphalf[10][100];//exp half-life
Double_t p_exphalfL[10][100];
Double_t p_exphalfR[10][100];
Double_t p_exphalfnew[10][100];//exp half-life
Double_t p_exphalfnewL[10][100];
Double_t p_exphalfnewR[10][100];
Double_t p_exphlrt[10][100];//exp half-life ratio T(N)/T(N+1)
Double_t p_exphlrtL[10][100];
Double_t p_exphlrtR[10][100];
Double_t p_oldexphalf[10][100];//literature half-life
Double_t p_oldexphalfL[10][100];
Double_t p_oldexphalfR[10][100];
Double_t p_newexpghalf[10][100];//half-life with gamma
Double_t p_newexpghalfL[10][100];
Double_t p_newexpghalfR[10][100];
Double_t p_newexphalf[10][100];//half-life without gamma
Double_t p_newexphalfL[10][100];
Double_t p_newexphalfR[10][100];
Double_t p_frdmhalf[10][100];//frdm+qrpa
Double_t p_ktu1half[10][100];//ktuy+gt
Double_t p_ktu2half[10][100];//audi+gt
Double_t p_borzhalf[10][100];//DF+CQRPA
Double_t p_explaw[10][100];
Double_t p_neutronnumoldexp[10][100];
Double_t p_neutronnumnewexp[10][100];
Double_t p_neutronnumnewexpg[10][100];
Double_t p_neutronerror[10][100];
Double_t p_dimiso[10];//number of isotopes per Z

Double_t n_exparb[13][100];//arbitrary variable
Double_t n_exparbL[13][100];
Double_t n_exparbR[13][100];
Double_t n_expQ_5[13][100];//Q^-5
Double_t n_expQ_5L[13][100];
Double_t n_expQ_5R[13][100];
Double_t n_exphalf[13][100];//exp half-life
Double_t n_exphalfL[13][100];
Double_t n_exphalfR[13][100];
Double_t n_exphalfnew[13][100];//exp half-life
Double_t n_exphalfnewL[13][100];
Double_t n_exphalfnewR[13][100];
Double_t n_exphlrt[13][100];//exp half-life ratio T(Z)/T(Z-1)
Double_t n_exphlrtL[13][100];
Double_t n_exphlrtR[13][100];
Double_t n_oldexphalf[13][100];//literature half-life
Double_t n_oldexphalfL[13][100];
Double_t n_oldexphalfR[13][100];
Double_t n_newexpghalf[13][100];//half-life with gamma
Double_t n_newexpghalfL[13][100];
Double_t n_newexpghalfR[13][100];
Double_t n_newexphalf[13][100];//half-life without gamma
Double_t n_newexphalfL[13][100];
Double_t n_newexphalfR[13][100];
Double_t n_frdmhalf[13][100];//frdm+qrpa
Double_t n_ktu1half[13][100];//ktuy+gt
Double_t n_ktu2half[13][100];//audi+gt
Double_t n_borzhalf[13][100];//DF+CQRPA
Double_t n_explaw[13][100];
Double_t n_protonnumoldexp[13][100];
Double_t n_protonnumnewexp[13][100];
Double_t n_protonnumnewexpg[13][100];
Double_t n_protonerror[13][100];
Double_t n_dimiso[13];//number of isotones per N
Double_t n_sm1[6];//shell model 1
Double_t n_sm2[6];//shell model 2

n_sm1[5]=6900; n_sm2[5]=2057;
n_sm1[4]=1030; n_sm2[4]= 577;
n_sm1[3]= 530; n_sm2[3]= 432;
n_sm1[2]= 270; n_sm2[2]= 222;
n_sm1[1]= 150; n_sm2[1]= 127;
n_sm1[0]=  16; n_sm2[0]=  16;

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
         p_expQ_5[i][j]=0;
         p_expQ_5L[i][j]=0;
         p_expQ_5R[i][j]=0;
         p_oldexphalf[i][j]=0;
         p_oldexphalfL[i][j]=0;
         p_oldexphalfR[i][j]=0;
         p_newexpghalf[i][j]=0;
         p_newexpghalfL[i][j]=0;
         p_newexpghalfR[i][j]=0;
         p_newexphalf[i][j]=0;
         p_newexphalfL[i][j]=0;
         p_newexphalfR[i][j]=0;
         p_frdmhalf[i][j]=0;
         p_ktu1half[i][j]=0;
         p_ktu2half[i][j]=0;
         p_borzhalf[i][j]=0;
         p_explaw[i][j]=0;
         p_neutronnumnewexp[i][j]=0;
         p_neutronnumnewexp[i][j]=0;
         p_neutronnumnewexpg[i][j]=0;
         p_neutronerror[i][j]=0;
      }
   }
   for(int i=0; i<13; i++){
      n_dimiso[i]=0;
      for(int j=0; j<100; j++){
         n_expQ_5[i][j]=0;
         n_expQ_5L[i][j]=0;
         n_expQ_5R[i][j]=0;
         n_oldexphalf[i][j]=0;
         n_oldexphalfL[i][j]=0;
         n_oldexphalfR[i][j]=0;
         n_newexpghalf[i][j]=0;
         n_newexpghalfL[i][j]=0;
         n_newexpghalfR[i][j]=0;
         n_newexphalf[i][j]=0;
         n_newexphalfL[i][j]=0;
         n_newexphalfR[i][j]=0;
         n_frdmhalf[i][j]=0;
         n_ktu1half[i][j]=0;
         n_ktu2half[i][j]=0;
         n_borzhalf[i][j]=0;
         n_explaw[i][j]=0;
         n_protonnumnewexp[i][j]=0;
         n_protonnumnewexp[i][j]=0;
         n_protonnumnewexpg[i][j]=0;
         n_protonerror[i][j]=0;
      }
   }
   in_data.open("macros/hlsys.input", ios::in);
   int temp=0;
   while (in_data.good()){
      in_data >>Z>>N>>new_expghl>>new_expghlL>>new_expghlR>>new_exphl>>new_exphlL>>new_exphlR>>old_exphl>>old_exphlL>>old_exphlR>>frdmhl>>ktu1hl>>ktu2hl>>borzhl>>expQ>>expQerr;
      //explaw = Calhalflife(Z,N);
      if(Z%2==1 || N%2==1){
         continue;
      }
      int index=Z-26;
      if(index<9&&index>=0){
         p_neutronnumoldexp[index][p_dimiso[index]]=N-0.15;
         p_neutronnumnewexp[index][p_dimiso[index]]=N;
         p_neutronnumnewexpg[index][p_dimiso[index]]=N+0.15;
         p_expQ_5[index][p_dimiso[index]]=TMath::Power(expQ/1e3,1);
         p_expQ_5L[index][p_dimiso[index]]=fabs(TMath::Power(expQ/1e3,1)-TMath::Power((expQ+expQerr)/1e3,1));
         p_expQ_5R[index][p_dimiso[index]]=fabs(TMath::Power((expQ-expQerr)/1e3,1)-TMath::Power(expQ/1e3,1));
         p_newexpghalf[index][p_dimiso[index]]=new_expghl;
         p_newexpghalfL[index][p_dimiso[index]]=new_expghlL;
         p_newexpghalfR[index][p_dimiso[index]]=new_expghlR;
         p_newexphalf[index][p_dimiso[index]]=new_exphl;
         p_newexphalfL[index][p_dimiso[index]]=new_exphlL;
         p_newexphalfR[index][p_dimiso[index]]=new_exphlR;
         p_oldexphalf[index][p_dimiso[index]]=old_exphl;
         p_oldexphalfL[index][p_dimiso[index]]=old_exphlL;
         p_oldexphalfR[index][p_dimiso[index]]=old_exphlR;
         p_frdmhalf[index][p_dimiso[index]]=frdmhl;
         p_ktu1half[index][p_dimiso[index]]=ktu1hl;
         p_ktu2half[index][p_dimiso[index]]=ktu2hl;
         p_borzhalf[index][p_dimiso[index]]=borzhl;
         p_explaw[index][p_dimiso[index]]=explaw;
         p_dimiso[index]++;
      }
      index=N-44;
      if(index<13&&index>=0){
         n_protonnumoldexp[index][n_dimiso[index]]=Z-0.15;
         n_protonnumnewexp[index][n_dimiso[index]]=Z;
         n_protonnumnewexpg[index][n_dimiso[index]]=Z+0.15;
         n_expQ_5[index][n_dimiso[index]]=TMath::Power(expQ/1e3,1);
         n_expQ_5L[index][n_dimiso[index]]=fabs(TMath::Power(expQ/1e3,1)-TMath::Power((expQ+expQerr)/1e3,1));
         cout<<n_expQ_5L[index][n_dimiso[index]]<<endl;
         n_expQ_5R[index][n_dimiso[index]]=fabs(TMath::Power((expQ-expQerr)/1e3,1)-TMath::Power(expQ/1e3,1));
         n_newexpghalf[index][n_dimiso[index]]=new_expghl;
         n_newexpghalfL[index][n_dimiso[index]]=new_expghlL;
         n_newexpghalfR[index][n_dimiso[index]]=new_expghlR;
         n_newexphalf[index][n_dimiso[index]]=new_exphl;
         n_newexphalfL[index][n_dimiso[index]]=new_exphlL;
         n_newexphalfR[index][n_dimiso[index]]=new_exphlR;
         n_oldexphalf[index][n_dimiso[index]]=old_exphl;
         n_oldexphalfL[index][n_dimiso[index]]=old_exphlL;
         n_oldexphalfR[index][n_dimiso[index]]=old_exphlR;
         n_frdmhalf[index][n_dimiso[index]]=frdmhl;
         n_ktu1half[index][n_dimiso[index]]=ktu1hl;
         n_ktu2half[index][n_dimiso[index]]=ktu2hl;
         n_borzhalf[index][n_dimiso[index]]=borzhl;
         n_explaw[index][n_dimiso[index]]=explaw;
         n_dimiso[index]++;
      }
      temp++;
      //if(temp==19){
      //   break;
      //}
   }
   in_data.close();
}

void p_fillexp(int Z){
   int index = Z-26;
   for(int i=0; i<p_dimiso[index]; i++){
      p_exphalf[index][i]=0;
      p_exphalfL[index][i]=0;
      p_exphalfR[index][i]=0;
      p_exphalfnew[index][i]=0;
      p_exphalfnewL[index][i]=0;
      p_exphalfnewR[index][i]=0;
      p_exphlrt[index][i]=0;
      p_exphlrtL[index][i]=0;
      p_exphlrtR[index][i]=0;
      p_exparb[index][i]=0;
      p_exparbL[index][i]=0;
      p_exparbR[index][i]=0;
      if(p_oldexphalf[index][i]>0){
         p_exphalf[index][i]=p_oldexphalf[index][i];
         p_exphalfL[index][i]=p_oldexphalfL[index][i];
         p_exphalfR[index][i]=p_oldexphalfR[index][i];
      }
      if(p_newexphalf[index][i]>0){
         p_exphalf[index][i]=p_newexphalf[index][i];
         p_exphalfL[index][i]=p_newexphalfL[index][i];
         p_exphalfR[index][i]=p_newexphalfR[index][i];
      }
      if(p_newexpghalf[index][i]>0){
         p_exphalf[index][i]=p_newexpghalf[index][i];
         p_exphalfL[index][i]=p_newexpghalfL[index][i];
         p_exphalfR[index][i]=p_newexpghalfR[index][i];
      }
      if(p_oldexphalf[index][i]<1){
         p_exphalfnew[index][i]=p_exphalf[index][i];
         p_exphalfnewL[index][i]=p_exphalfL[index][i];
         p_exphalfnewR[index][i]=p_exphalfR[index][i];
      }else{
         p_exphalfnew[index][i]=0;
         p_exphalfnewL[index][i]=0;
         p_exphalfnewR[index][i]=0;
      }

      if(p_exphalf[index][i]>0){
         p_exparb[index][i]=p_exphalf[index][i]*p_expQ_5[index][i];
         p_exparbL[index][i]=sqrt(
               ((p_exphalf[index][i]-p_exphalfL[index][i])*p_expQ_5[index][i]-p_exphalf[index][i]*p_expQ_5[index][i])*
               ((p_exphalf[index][i]-p_exphalfL[index][i])*p_expQ_5[index][i]-p_exphalf[index][i]*p_expQ_5[index][i])+
               (p_exphalf[index][i]*(p_expQ_5[index][i]-p_expQ_5L[index][i])-p_exphalf[index][i]*p_expQ_5[index][i])*
               (p_exphalf[index][i]*(p_expQ_5[index][i]-p_expQ_5L[index][i])-p_exphalf[index][i]*p_expQ_5[index][i])
               );
         p_exparbR[index][i]=sqrt(
               ((p_exphalf[index][i]+p_exphalfR[index][i])*p_expQ_5[index][i]-p_exphalf[index][i]*p_expQ_5[index][i])*
               ((p_exphalf[index][i]+p_exphalfR[index][i])*p_expQ_5[index][i]-p_exphalf[index][i]*p_expQ_5[index][i])+
               (p_exphalf[index][i]*(p_expQ_5[index][i]+p_expQ_5R[index][i])-p_exphalf[index][i]*p_expQ_5[index][i])*
               (p_exphalf[index][i]*(p_expQ_5[index][i]+p_expQ_5R[index][i])-p_exphalf[index][i]*p_expQ_5[index][i])
               );
      }
   }
   for(int i=0; i<p_dimiso[index]-1; i++){
      p_exphlrt[index][i]=p_exphalf[index][i]/p_exphalf[index][i+1];
      p_exphlrtL[index][i]=sqrt(
            ((p_exphalf[index][i]-p_exphalfL[index][i])/p_exphalf[index][i+1]-p_exphalf[index][i]/p_exphalf[index][i+1])*
            ((p_exphalf[index][i]-p_exphalfL[index][i])/p_exphalf[index][i+1]-p_exphalf[index][i]/p_exphalf[index][i+1])+
            (p_exphalf[index][i]/(p_exphalf[index][i+1]+p_exphalfR[index][i+1])-p_exphalf[index][i]/p_exphalf[index][i+1])*
            (p_exphalf[index][i]/(p_exphalf[index][i+1]+p_exphalfR[index][i+1])-p_exphalf[index][i]/p_exphalf[index][i+1])
            );
      p_exphlrtR[index][i]=sqrt(
            ((p_exphalf[index][i]+p_exphalfR[index][i])/p_exphalf[index][i+1]-p_exphalf[index][i]/p_exphalf[index][i+1])*
            ((p_exphalf[index][i]+p_exphalfR[index][i])/p_exphalf[index][i+1]-p_exphalf[index][i]/p_exphalf[index][i+1])+
            (p_exphalf[index][i]/(p_exphalf[index][i+1]-p_exphalfL[index][i+1])-p_exphalf[index][i]/p_exphalf[index][i+1])*
            (p_exphalf[index][i]/(p_exphalf[index][i+1]-p_exphalfL[index][i+1])-p_exphalf[index][i]/p_exphalf[index][i+1])
            );
   }
}

void n_fillexp(int N){
   int index = N-44;
   for(int i=0; i<n_dimiso[index]; i++){
      n_exphalf[index][i]=0;
      n_exphalfL[index][i]=0;
      n_exphalfR[index][i]=0;
      n_exphlrt[index][i]=0;
      n_exphlrtL[index][i]=0;
      n_exphlrtR[index][i]=0;
      n_exparb[index][i]=0;
      n_exparbL[index][i]=0;
      n_exparbR[index][i]=0;
      if(n_oldexphalf[index][i]>0){
         n_exphalf[index][i]=n_oldexphalf[index][i];
         n_exphalfL[index][i]=n_oldexphalfL[index][i];
         n_exphalfR[index][i]=n_oldexphalfR[index][i];
      }
      if(n_newexphalf[index][i]>0){
         n_exphalf[index][i]=n_newexphalf[index][i];
         n_exphalfL[index][i]=n_newexphalfL[index][i];
         n_exphalfR[index][i]=n_newexphalfR[index][i];
      }
      if(n_newexpghalf[index][i]>0){
         n_exphalf[index][i]=n_newexpghalf[index][i];
         n_exphalfL[index][i]=n_newexpghalfL[index][i];
         n_exphalfR[index][i]=n_newexpghalfR[index][i];
      }
      if(n_oldexphalf[index][i]<1){
         n_exphalfnew[index][i]=n_exphalf[index][i];
         n_exphalfnewL[index][i]=n_exphalfL[index][i];
         n_exphalfnewR[index][i]=n_exphalfR[index][i];
      }else{
         n_exphalfnew[index][i]=0;
         n_exphalfnewL[index][i]=0;
         n_exphalfnewR[index][i]=0;
      }
      if(n_exphalf[index][i]>0){
         n_exparb[index][i]=n_exphalf[index][i]*n_expQ_5[index][i];
         n_exparbL[index][i]=sqrt(
               ((n_exphalf[index][i]-n_exphalfL[index][i])*n_expQ_5[index][i]-n_exphalf[index][i]*n_expQ_5[index][i])*
               ((n_exphalf[index][i]-n_exphalfL[index][i])*n_expQ_5[index][i]-n_exphalf[index][i]*n_expQ_5[index][i])+
               (n_exphalf[index][i]*(n_expQ_5[index][i]-n_expQ_5L[index][i])-n_exphalf[index][i]*n_expQ_5[index][i])*
               (n_exphalf[index][i]*(n_expQ_5[index][i]-n_expQ_5L[index][i])-n_exphalf[index][i]*n_expQ_5[index][i])
               );
         n_exparbR[index][i]=sqrt(
               ((n_exphalf[index][i]+n_exphalfR[index][i])*n_expQ_5[index][i]-n_exphalf[index][i]*n_expQ_5[index][i])*
               ((n_exphalf[index][i]+n_exphalfR[index][i])*n_expQ_5[index][i]-n_exphalf[index][i]*n_expQ_5[index][i])+
               (n_exphalf[index][i]*(n_expQ_5[index][i]+n_expQ_5R[index][i])-n_exphalf[index][i]*n_expQ_5[index][i])*
               (n_exphalf[index][i]*(n_expQ_5[index][i]+n_expQ_5R[index][i])-n_exphalf[index][i]*n_expQ_5[index][i])
               );
      }
   }
   for(int i=1; i<n_dimiso[index]; i++){
      n_exphlrt[index][i]=n_exphalf[index][i]/n_exphalf[index][i-1];
      n_exphlrtL[index][i]=sqrt(
            ((n_exphalf[index][i]-n_exphalfL[index][i])/n_exphalf[index][i-1]-n_exphalf[index][i]/n_exphalf[index][i-1])*
            ((n_exphalf[index][i]-n_exphalfL[index][i])/n_exphalf[index][i-1]-n_exphalf[index][i]/n_exphalf[index][i-1])+
            (n_exphalf[index][i]/(n_exphalf[index][i-1]+n_exphalfR[index][i-1])-n_exphalf[index][i]/n_exphalf[index][i-1])*
            (n_exphalf[index][i]/(n_exphalf[index][i-1]+n_exphalfR[index][i-1])-n_exphalf[index][i]/n_exphalf[index][i-1])
            );
      n_exphlrtR[index][i]=sqrt(
            ((n_exphalf[index][i]+n_exphalfR[index][i])/n_exphalf[index][i-1]-n_exphalf[index][i]/n_exphalf[index][i-1])*
            ((n_exphalf[index][i]+n_exphalfR[index][i])/n_exphalf[index][i-1]-n_exphalf[index][i]/n_exphalf[index][i-1])+
            (n_exphalf[index][i]/(n_exphalf[index][i-1]-n_exphalfL[index][i-1])-n_exphalf[index][i]/n_exphalf[index][i-1])*
            (n_exphalf[index][i]/(n_exphalf[index][i-1]-n_exphalfL[index][i-1])-n_exphalf[index][i]/n_exphalf[index][i-1])
            );
   }
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

void find_boundryZ_nhl(int Z, Double_t &nmin, Double_t &nmax, double &hlmin, double &hlmax){
   int index=Z-26;
   nmin = p_neutronnumoldexp[index][0]-0.5;
   //cout<<index<<", "<<p_dimiso[index]<<endl;
   nmax = p_neutronnumnewexpg[index][p_dimiso[index]-1]+0.5;
   double tempmin=1000;
   double tempmax=0;
   for(int i=0; i<p_dimiso[index]; i++){
      //cout<<p_newexphalf[index][i]<<", "<<p_frdmhalf[index][i]<<", "<<p_oldexphalf[index][i]<<endl;
      if(p_newexpghalf[index][i]>tempmax){
         tempmax=p_newexpghalf[index][i];
      }
      if(p_newexphalf[index][i]>tempmax){
         tempmax=p_newexphalf[index][i];
      }
      if(p_oldexphalf[index][i]>tempmax){
         tempmax=p_oldexphalf[index][i];
      }
      if(p_frdmhalf[index][i]>tempmax){
         tempmax=p_frdmhalf[index][i];
      }
      if(p_ktu1half[index][i]>tempmax){
         tempmax=p_ktu1half[index][i];
      }
      if(p_ktu2half[index][i]>tempmax){
         tempmax=p_ktu2half[index][i];
      }
      if(p_borzhalf[index][i]>tempmax){
         tempmax=p_borzhalf[index][i];
      }
      if(p_explaw[index][i]>tempmax){
         tempmax=p_explaw[index][i];
      }
      if(p_newexpghalf[index][i]<tempmin && p_newexpghalf[index][i]>0){
         tempmin=p_newexpghalf[index][i];
      }
      if(p_newexphalf[index][i]<tempmin && p_newexphalf[index][i]>0){
         tempmin=p_newexphalf[index][i];
      }
      if(p_oldexphalf[index][i]<tempmin && p_oldexphalf[index][i]>0){
         tempmin=p_oldexphalf[index][i];
      }
      if(p_frdmhalf[index][i]<tempmin && p_frdmhalf[index][i]>0){
         tempmin=p_frdmhalf[index][i];
      }
      if(p_ktu1half[index][i]<tempmin && p_ktu1half[index][i]>0){
         tempmin=p_ktu1half[index][i];
      }
      if(p_ktu2half[index][i]<tempmin && p_ktu2half[index][i]>0){
         tempmin=p_ktu2half[index][i];
      }
      if(p_borzhalf[index][i]<tempmin && p_borzhalf[index][i]>0){
         tempmin=p_borzhalf[index][i];
      }
      if(p_explaw[index][i]<tempmin && p_explaw[index][i]>0){
         tempmin=p_explaw[index][i];
      }
      //cout<<tempmin<<", "<<tempmax<<endl;
   }
   hlmin=tempmin/2.0;
   hlmax=tempmax*2;
}

void find_boundryN_nhl(int N, Double_t &nmin, Double_t &nmax, double &hlmin, double &hlmax){
   int index=N-44;
   nmin = n_protonnumoldexp[index][0]-0.5;
   //cout<<index<<", "<<n_dimiso[index]<<endl;
   nmax = n_protonnumnewexpg[index][n_dimiso[index]-1]+0.5;
   double tempmin=1000;
   double tempmax=0;
   for(int i=0; i<n_dimiso[index]; i++){
      if(n_newexpghalf[index][i]>tempmax){
         tempmax=n_newexpghalf[index][i];
      }
      if(n_newexphalf[index][i]>tempmax){
         tempmax=n_newexphalf[index][i];
      }
      if(n_oldexphalf[index][i]>tempmax){
         tempmax=n_oldexphalf[index][i];
      }
      if(n_frdmhalf[index][i]>tempmax){
         tempmax=n_frdmhalf[index][i];
      }
      if(n_ktu1half[index][i]>tempmax){
         tempmax=n_ktu1half[index][i];
      }
      if(n_ktu2half[index][i]>tempmax){
         tempmax=n_ktu2half[index][i];
      }
      if(n_borzhalf[index][i]>tempmax){
         tempmax=n_borzhalf[index][i];
      }
      if(n_explaw[index][i]>tempmax){
         tempmax=n_explaw[index][i];
      }
      if(n_newexpghalf[index][i]<tempmin && n_newexpghalf[index][i]>0){
         tempmin=n_newexpghalf[index][i];
      }
      if(n_newexphalf[index][i]<tempmin && n_newexphalf[index][i]>0){
         tempmin=n_newexphalf[index][i];
      }
      if(n_oldexphalf[index][i]<tempmin && n_oldexphalf[index][i]>0){
         tempmin=n_oldexphalf[index][i];
      }
      if(n_frdmhalf[index][i]<tempmin && n_frdmhalf[index][i]>0){
         tempmin=n_frdmhalf[index][i];
      }
      if(n_ktu1half[index][i]<tempmin && n_ktu1half[index][i]>0){
         tempmin=n_ktu1half[index][i];
      }
      if(n_ktu2half[index][i]<tempmin && n_ktu2half[index][i]>0){
         tempmin=n_ktu2half[index][i];
      }
      if(n_borzhalf[index][i]<tempmin && n_borzhalf[index][i]>0){
         tempmin=n_borzhalf[index][i];
      }
      if(n_explaw[index][i]<tempmin && n_explaw[index][i]>0){
         tempmin=n_explaw[index][i];
      }
      //cout<<tempmin<<", "<<tempmax<<endl;
      if(N==50 && i<6){
         if(n_sm1[i]>tempmax){
            tempmax=n_sm1[i];
         }
         if(n_sm2[i]>tempmax){
            tempmax=n_sm2[i];
         }
         if(n_sm1[i]<tempmin && n_sm1[i]>0){
            tempmin=n_sm1[i];
         }
         if(n_sm2[i]<tempmin && n_sm2[i]>0){
            tempmin=n_sm2[i];
         }
      }
   }
   hlmin=tempmin/2.0;
   hlmax=tempmax*2;
}

void find_boundryZ_total_nhl(Double_t &nmin, Double_t &nmax, double &hlmin, double &hlmax){
   nmin = 1000;
   nmax = 0;
   hlmax=0;
   hlmin=1000;
   for(int i=0; i<8; i++){
      p_fillexp(i+26);
      for(int j=0; j<p_dimiso[i]; j++){
         if(p_neutronnumnewexp[i][j]<nmin){
            nmin=p_neutronnumnewexp[i][j];
         }
         if(p_neutronnumnewexp[i][j]>nmax){
            nmax=p_neutronnumnewexp[i][j];
         }
         if(p_exphalf[i][j]>0 && p_exphalf[i][j]>hlmax){
            hlmax=p_exphalf[i][j];
         }
         if(p_exphalf[i][j]>0 && p_exphalf[i][j]<hlmin){
            hlmin=p_exphalf[i][j];
         }
      }
   }
   hlmin=hlmin/2.0;
   hlmax=hlmax*2;
   nmin = nmin-0.5;
   nmax = nmax+0.5;
   //cout<<hlmin<<", "<<hlmax<<endl;
}

void find_boundryN_total_nhl(Double_t &nmin, Double_t &nmax, double &hlmin, double &hlmax){
   nmin = 1000;
   nmax = 0;
   hlmax=0;
   hlmin=1000;
   for(int i=0; i<13; i++){
      n_fillexp(i+44);
      for(int j=0; j<n_dimiso[i]; j++){
         if(n_protonnumnewexp[i][j]<nmin){
            nmin=n_protonnumnewexp[i][j];
         }
         if(n_protonnumnewexp[i][j]>nmax){
            nmax=n_protonnumnewexp[i][j];
         }
         if(n_exphalf[i][j]>0 && n_exphalf[i][j]>hlmax){
            hlmax=n_exphalf[i][j];
         }
         if(n_exphalf[i][j]>0 && n_exphalf[i][j]<hlmin){
            hlmin=n_exphalf[i][j];
         }
      }
   }
   hlmin=hlmin/2.0;
   hlmax=hlmax*2;
   nmin = nmin-0.5;
   nmax = nmax+0.5;
}

void find_boundryZ_total_Q_5hl(Double_t &Q_5min, Double_t &Q_5max, double &hlmin, double &hlmax){
   //cout<<index<<", "<<p_dimiso[index]<<endl;
   hlmax=0;
   hlmin=1000;
   Q_5max=0;
   Q_5min=1;
   for(int index=0; index<9; index++){
      p_fillexp(index+26);
      for(int i=0; i<p_dimiso[index]; i++){
         //cout<<p_newexphalf[index][i]<<", "<<p_frdmhalf[index][i]<<", "<<p_oldexphalf[index][i]<<endl;
         if(p_expQ_5[index][i]>0 && p_expQ_5[index][i]>Q_5max){
            Q_5max=p_expQ_5[index][i];
         }
         if(p_expQ_5[index][i]>0 && p_expQ_5[index][i]<Q_5min){
            Q_5min=p_expQ_5[index][i];
         }
         if(p_exphalf[index][i]>0 && p_exphalf[index][i]>hlmax){
            hlmax=p_exphalf[index][i];
         }
         if(p_exphalf[index][i]>0 && p_exphalf[index][i]<hlmin){
            hlmin=p_exphalf[index][i];
         }
      }
   }
   Q_5max=2*Q_5max;
   Q_5min=0.5*Q_5min;
   hlmin=hlmin/2.0;
   hlmax=hlmax*2;
}


void find_boundryN_total_Q_5hl(Double_t &Q_5min, Double_t &Q_5max, double &hlmin, double &hlmax){
   //cout<<index<<", "<<n_dimiso[index]<<endl;
   hlmax=0;
   hlmin=1000;
   Q_5max=0;
   Q_5min=1;
   for(int index=0; index<13; index++){
      n_fillexp(index+44);
      for(int i=0; i<n_dimiso[index]; i++){
         //cout<<n_newexphalf[index][i]<<", "<<n_frdmhalf[index][i]<<", "<<n_oldexphalf[index][i]<<endl;
         if(n_expQ_5[index][i]>0 && n_expQ_5[index][i]>Q_5max){
            Q_5max=n_expQ_5[index][i];
         }
         if(n_expQ_5[index][i]>0 && n_expQ_5[index][i]<Q_5min){
            Q_5min=n_expQ_5[index][i];
         }
         if(n_exphalf[index][i]>0 && n_exphalf[index][i]>hlmax){
            hlmax=n_exphalf[index][i];
         }
         if(n_exphalf[index][i]>0 && n_exphalf[index][i]<hlmin){
            hlmin=n_exphalf[index][i];
         }
         if(n_expQ_5[index][i]>0 && n_expQ_5[index][i]>Q_5max){
            Q_5max=n_expQ_5[index][i];
         }
         if(n_expQ_5[index][i]>0 && n_expQ_5[index][i]<Q_5min){
            Q_5min=n_expQ_5[index][i];
         }
      }
   }
   Q_5max=2*Q_5max;
   Q_5min=0.5*Q_5min;
   hlmin=hlmin/2.0;
   hlmax=hlmax*2;
}

void find_boundryZ_total_Q_5(double &Q_5min, double &Q_5max){
   Q_5max=0;
   Q_5min=1;
   for(int i=0; i<9; i++){
      for(int j=0; j<p_dimiso[i]; j++){
         if(p_expQ_5[i][j]>0 && p_expQ_5[i][j]>Q_5max){
            Q_5max=p_expQ_5[i][j];
         }
         if(p_expQ_5[i][j]>0 && p_expQ_5[i][j]<Q_5min){
            Q_5min=p_expQ_5[i][j];
         }
      }
   }
   Q_5max=2*Q_5max;
   Q_5min=0.5*Q_5min;
}


void find_boundryN_total_Q_5(double &Q_5min, double &Q_5max){
   Q_5max=0;
   Q_5min=1;
   for(int i=0; i<13; i++){
      n_fillexp(i+44);
      for(int j=0; j<n_dimiso[i]; j++){
         if(n_expQ_5[i][j]>0 && n_expQ_5[i][j]>Q_5max){
            Q_5max=n_expQ_5[i][j];
         }
         if(n_expQ_5[i][j]>0 && n_expQ_5[i][j]<Q_5min){
            Q_5min=n_expQ_5[i][j];
         }
      }
   }
   Q_5max=2*Q_5max;
   Q_5min=0.5*Q_5min;
}

void find_boundryZ_total_narb(Double_t &nmin, Double_t &nmax, double &arbmin, double &arbmax){
   arbmax=0;
   arbmin=1000;
   nmin = 1000;
   nmax = 0;
   for(int i=0; i<8; i++){
      p_fillexp(i+26);
      for(int j=0; j<p_dimiso[i]; j++){
         if(p_neutronnumnewexp[i][j]<nmin){
            nmin=p_neutronnumnewexp[i][j];
         }
         if(p_neutronnumnewexp[i][j]>nmax){
            nmax=p_neutronnumnewexp[i][j];
         }
         if(p_exparb[i][j]>0 && p_exparb[i][j]>arbmax){
            arbmax=p_exparb[i][j];
         }
         if(p_exparb[i][j]>0 && p_exparb[i][j]<arbmin){
            arbmin=p_exparb[i][j];
         }
      }
   }
   arbmin=arbmin/2.0;
   arbmax=arbmax*2;
   nmin = nmin-0.5;
   nmax = nmax+0.5;
   //cout<<arbmin<<", "<<arbmax<<endl;
}

void find_boundryN_total_narb(Double_t &nmin, Double_t &nmax, double &arbmin, double &arbmax){
   arbmax=0;
   arbmin=1000;
   nmax=0;
   nmin=1000;
   for(int i=0; i<13; i++){
      n_fillexp(i+44);
      for(int j=0; j<n_dimiso[i]; j++){
         if(n_protonnumnewexp[i][j]<nmin){
            nmin=n_protonnumnewexp[i][j];
         }
         if(n_protonnumnewexp[i][j]>nmax){
            nmax=n_protonnumnewexp[i][j];
         }
         if(n_exparb[i][j]>0 && n_exparb[i][j]>arbmax){
            arbmax=n_exparb[i][j];
         }
         if(n_exparb[i][j]>0 && n_exparb[i][j]<arbmin){
            arbmin=n_exparb[i][j];
         }
      }
   }
   arbmin=arbmin/2.0;
   arbmax=arbmax*2;
   nmin = nmin-0.5;
   nmax = nmax+0.5;
   //cout<<arbmin<<", "<<arbmax<<endl;
}

void find_boundryZ_total_nhlrt(Double_t &nmin, Double_t &nmax, double &hlrtmin, double &hlrtmax){
   nmin = 1000;
   nmax = 0;
   hlrtmax=0;
   hlrtmin=1000;
   for(int i=0; i<8; i++){
      p_fillexp(i+26);
      for(int j=0; j<p_dimiso[i]; j++){
         if(p_neutronnumnewexp[i][j]<nmin){
            nmin=p_neutronnumnewexp[i][j];
         }
         if(p_neutronnumnewexp[i][j]>nmax){
            nmax=p_neutronnumnewexp[i][j];
         }
         if(p_exphlrt[i][j]>0 && p_exphlrt[i][j]>hlrtmax){
            hlrtmax=p_exphlrt[i][j];
         }
         if(p_exphlrt[i][j]>0 && p_exphlrt[i][j]<hlrtmin){
            hlrtmin=p_exphlrt[i][j];
         }
      }
   }
   hlrtmax=hlrtmax*1.2;
   nmin = nmin-0.5;
   nmax = nmax+0.5;
}

void find_boundryN_total_nhlrt(Double_t &nmin, Double_t &nmax, double &hlrtmin, double &hlrtmax){
   nmin = 1000;
   nmax = 0;
   hlrtmax=0;
   hlrtmin=1000;
   for(int i=0; i<13; i++){
      n_fillexp(i+44);
      for(int j=0; j<n_dimiso[i]; j++){
         if(n_protonnumnewexp[i][j]<nmin){
            nmin=n_protonnumnewexp[i][j];
         }
         if(n_protonnumnewexp[i][j]>nmax){
            nmax=n_protonnumnewexp[i][j];
         }
         if(n_exphlrt[i][j]>0 && n_exphlrt[i][j]>hlrtmax){
            hlrtmax=n_exphlrt[i][j];
         }
         if(n_exphlrt[i][j]>0 && n_exphlrt[i][j]<hlrtmin){
            hlrtmin=n_exphlrt[i][j];
         }
      }
   }
   nmin = nmin-0.5;
   nmax = nmax+0.5;
   hlrtmax=hlrtmax*1.2;
}

void plot_syshl(){

   TFile *RootFile = new TFile("root/root_histogram/hlsys_all.root","RECREATE");
   TGraphAsymmErrors *p_sys_exp[10]; //array for different isotopes
   TGraphAsymmErrors *p_sys_exp1[10]; //array for different isotopes
   TGraphAsymmErrors *p_sys_expold[10]; //array for different isotopes
   TGraphAsymmErrors *p_sys_expnew[10]; //array for different isotopes
   TGraphAsymmErrors *p_sys_expgnew[10]; //array for different isotopes
   TGraphAsymmErrors *p_sys_Qexp[10]; //array for different isotopes
   TGraphAsymmErrors *p_sys_Qhlexp[10]; //array for different isotopes
   TGraphAsymmErrors *p_sys_arbexp[10]; //array for different isotopes
   TGraphAsymmErrors *p_sys_hlrtexp[10]; //array for different isotopes
   TGraphAsymmErrors *n_sys_exp[13]; //array for different isotopes
   TGraphAsymmErrors *n_sys_expold[13]; //array for different isotopes
   TGraphAsymmErrors *n_sys_expnew[13]; //array for different isotopes
   TGraphAsymmErrors *n_sys_expgnew[13]; //array for different isotopes
   TGraphAsymmErrors *n_sys_Qexp[13]; //array for different isotopes
   TGraphAsymmErrors *n_sys_Qhlexp[13]; //array for different isotopes
   TGraphAsymmErrors *n_sys_arbexp[13]; //array for different isotopes
   TGraphAsymmErrors *n_sys_hlrtexp[13]; //array for different isotopes

   TGraph *p_sys_frdm[10]; //array for different isotopes
   TGraph *p_sys_ktu1[10]; //array for different isotopes
   TGraph *p_sys_ktu2[10]; //array for different isotopes
   TGraph *p_sys_borz[10]; //array for different isotopes
   TGraph *p_sys_explaw[10]; //array for different isotopes
   TGraph *n_sys_frdm[13]; //array for different isotopes
   TGraph *n_sys_ktu1[13]; //array for different isotopes
   TGraph *n_sys_ktu2[13]; //array for different isotopes
   TGraph *n_sys_borz[13]; //array for different isotopes
   TGraph *n_sys_explaw[13]; //array for different isotopes
   TGraph *n_sys_sm1; //array for different isotopes
   TGraph *n_sys_sm2; //array for different isotopes

   TLegend *p_legend;
   TLegend *n_legend;
   TLegend *p_leg[10];
   TLegend *n_leg[13];
   TLegend *p_Qhllegend;
   TLegend *n_Qhllegend;
   TLegend *p_Qlegend;
   TLegend *n_Qlegend;
   TLegend *p_arblegend;
   TLegend *n_arblegend;
   TLegend *p_hlrtlegend;
   TLegend *n_hlrtlegend;

   TCanvas *c01 = new TCanvas ("c01","c01",0,0,800,1200);
   TCanvas *c02 = new TCanvas ("c02","c02",0,0,1000,800);
   TCanvas *c03 = new TCanvas ("c03","c03",0,0,800,600);
   TCanvas *c04 = new TCanvas ("c04","c04",0,0,800,600);
   //TCanvas *c05 = new TCanvas ("c05","c05",0,0,800,600);
   //TCanvas *c06 = new TCanvas ("c06","c06",0,0,800,600);
   //TCanvas *c07 = new TCanvas ("c07","c07",0,0,800,600);
   //TCanvas *c08 = new TCanvas ("c08","c08",0,0,800,600);
   //TCanvas *c09 = new TCanvas ("c09","c09",0,0,800,600);
   //TCanvas *c10 = new TCanvas ("c10","c10",0,0,800,600);
   //TCanvas *c11 = new TCanvas ("c11","c11",0,0,800,600);
   //TCanvas *c12 = new TCanvas ("c12","c12",0,0,800,600);

   Double_t nmin, nmax;
   double hlmin, hlmax;
   double hlrtmin, hlrtmax;
   double arbmin, arbmax;
   double Q_5min, Q_5max;
   read_data();
   /***************** half-life as a function of N by isotope *******************/
   c01->Divide(2,4);
   find_boundryZ_total_nhl(nmin, nmax, hlmin, hlmax);
   for(int i=0; i<7; i++){
      if(p_dimiso[i]==0){
         continue;
      }
      c01->cd(i+1);
      c01->cd(i+1)->SetGridx(0);
      c01->cd(i+1)->SetGridy(0);
      c01->cd(i+1)->SetTopMargin(0);
      c01->cd(i+1)->SetBottomMargin(0.15);
      c01->cd(i+1)->SetLeftMargin(0.2);
      c01->cd(i+1)->SetRightMargin(0);
      TString content1, content2;
      set_contentZ(i+26, content1, content2);
      //p_sys_expnew[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronnumnewexp[i],p_newexphalf[i],p_neutronerror[i],p_neutronerror[i],p_newexphalfL[i],p_newexphalfR[i]);
      //p_sys_expgnew[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronnumnewexpg[i],p_newexpghalf[i],p_neutronerror[i],p_neutronerror[i],p_newexpghalfL[i],p_newexpghalfR[i]);
      //p_sys_expold[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronnumoldexp[i],p_oldexphalf[i],p_neutronerror[i],p_neutronerror[i],p_oldexphalfL[i],p_oldexphalfR[i]);
      p_sys_exp[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronnumnewexp[i],p_exphalf[i],p_neutronerror[i],p_neutronerror[i],p_exphalfL[i],p_exphalfR[i]);
      p_sys_exp1[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronnumnewexp[i],p_exphalfnew[i],p_neutronerror[i],p_neutronerror[i],p_exphalfnewL[i],p_exphalfnewR[i]);
      p_sys_frdm[i] = new TGraph(p_dimiso[i],p_neutronnumnewexp[i],p_frdmhalf[i]);
      p_sys_frdm[i]->SetLineColor(2);
      p_sys_ktu1[i] = new TGraph(p_dimiso[i],p_neutronnumnewexp[i],p_ktu1half[i]);
      p_sys_ktu1[i]->SetLineColor(4);
      p_sys_ktu2[i] = new TGraph(p_dimiso[i],p_neutronnumnewexp[i],p_ktu2half[i]);
      //if(i==1 || i==2){
      if(i==4){
         //p_sys_ktu2[i] = new TGraph(p_dimiso[i]-1,p_neutronnumnewexp[i],p_ktu2half[i]);
         p_sys_borz[i] = new TGraph(p_dimiso[i]-1,&p_neutronnumnewexp[i][1],&p_borzhalf[i][1]);
      }else{
         //p_sys_ktu2[i] = new TGraph(p_dimiso[i],p_neutronnumnewexp[i],p_ktu2half[i]);
         p_sys_borz[i] = new TGraph(p_dimiso[i],p_neutronnumnewexp[i],p_borzhalf[i]);
      }
      p_sys_ktu2[i]->SetLineColor(6);
      //if(i==2){
      //   p_sys_borz[i] = new TGraph(p_dimiso[i]-1,&p_neutronnumnewexp[i][1],&p_borzhalf[i][1]);
      //}else if(i==4){
      //   p_sys_borz[i] = new TGraph(p_dimiso[i]-2,&p_neutronnumnewexp[i][2],&p_borzhalf[i][2]);
      //}else if(i==5){
      //   p_sys_borz[i] = new TGraph(p_dimiso[i]-5,&p_neutronnumnewexp[i][5],&p_borzhalf[i][5]);
      //}else if(i==6){
      //   p_sys_borz[i] = new TGraph(p_dimiso[i]-5,&p_neutronnumnewexp[i][4],&p_borzhalf[i][4]);
      //}else{
      //   p_sys_borz[i] = new TGraph(p_dimiso[i],p_neutronnumnewexp[i],p_borzhalf[i]);
      //}
      p_sys_borz[i]->SetLineColor(8);
      p_sys_explaw[i] = new TGraph(p_dimiso[i],p_neutronnumnewexp[i],p_explaw[i]);
      p_sys_explaw[i]->SetLineColor(3);
      TLatex text;
      text.SetTextAlign(12);
      text.SetTextSize(0.1);
      text.SetNDC(kTRUE);
      find_boundryZ_nhl(i+26,nmin,nmax,hlmin,hlmax);
      //cout<<i<<", "<<nmin<<endl;
      p_sys_frdm[i]->GetXaxis()->SetLimits(nmin,nmax);
      p_sys_frdm[i]->GetYaxis()->SetRangeUser(hlmin,hlmax);
      p_sys_frdm[i]->SetTitle("");
      if(i>=5){
         p_sys_frdm[i]->GetXaxis()->SetTitle("Neutron number");
         p_sys_frdm[i]->GetXaxis()->CenterTitle(1);
      }else{
         p_sys_frdm[i]->GetXaxis()->SetTitle("");
      }
      p_sys_frdm[i]->GetXaxis()->SetTitleSize(0.08);
      p_sys_frdm[i]->GetXaxis()->SetLabelSize(0.08);
      if(i>0){
         p_sys_frdm[i]->GetXaxis()->SetNdivisions((nmax-nmin+1)/2+1);
      }else{
         p_sys_frdm[i]->GetXaxis()->SetNdivisions((nmax-nmin+1)/2+1);
      }
      if(i==0 || i==2 || i==4 || i==6){
         p_sys_frdm[i]->GetYaxis()->SetTitle("Half-life (ms)");
         p_sys_frdm[i]->GetYaxis()->CenterTitle(1);
      }else{
         p_sys_frdm[i]->GetYaxis()->SetTitle("");
      }
      p_sys_frdm[i]->GetYaxis()->SetTitleSize(0.08);
      p_sys_frdm[i]->GetYaxis()->SetLabelSize(0.08);
      p_sys_frdm[i]->SetLineWidth(2);
      p_sys_ktu1[i]->SetLineWidth(2);
      p_sys_ktu2[i]->SetLineWidth(2);
      p_sys_borz[i]->SetLineWidth(2);
      //p_sys_explaw[i]->SetLineWidth(2);
      p_sys_frdm[i]->Draw("AL");
      p_sys_ktu1[i]->Draw("L");
      p_sys_ktu2[i]->Draw("L");
      p_sys_borz[i]->Draw("L");
      //p_sys_explaw[i]->Draw("L");
      //p_sys_expold[i]->Draw("P");
      //p_sys_expnew[i]->Draw("P");
      //p_sys_expgnew[i]->Draw("P");
      p_sys_exp[i]->Draw("P");
      p_sys_exp1[i]->Draw("P");
      text.DrawLatex(.6,.8,content1);
      gPad->SetLogy(1);
      //p_sys_expnew[i]->SetMarkerStyle(24);
      //p_sys_expnew[i]->SetMarkerSize(1);
      //p_sys_expgnew[i]->SetMarkerStyle(20);
      //p_sys_expgnew[i]->SetMarkerSize(1);
      //p_sys_expold[i]->SetMarkerStyle(26);
      //p_sys_expold[i]->SetMarkerSize(1);
      p_sys_exp[i]->SetMarkerStyle(25);
      p_sys_exp[i]->SetMarkerSize(1);
      p_sys_exp1[i]->SetMarkerStyle(21);
      p_sys_exp1[i]->SetMarkerSize(1);
      if(i==6){
         c01->cd(8);
         p_leg[i] = new TLegend(0.10,0.10,0.9,0.9,"");
         //p_leg[i]->AddEntry(p_sys_expgnew[i],"w gamma","P");
         //p_leg[i]->AddEntry(p_sys_expnew[i],"w/o gamma","P");
         //p_leg[i]->AddEntry(p_sys_expold[i],"Prev. Exp.","P");
         p_leg[i]->AddEntry(p_sys_exp[i],"Exp","P");
         p_leg[i]->AddEntry(p_sys_exp1[i],"new half-life","P");
         p_leg[i]->AddEntry(p_sys_frdm[i],"FRDM+QRPA","L");
         p_leg[i]->AddEntry(p_sys_ktu1[i],"KTUY+GT2","L");
         p_leg[i]->AddEntry(p_sys_ktu2[i],"HFB+pnQRPA","L");
         p_leg[i]->AddEntry(p_sys_borz[i],"DF+CQRPA","L");
         //p_leg[i]->AddEntry(p_sys_explaw[i],"Exp Law","L");
         p_leg[i]->SetBorderSize(0);
         p_leg[i]->SetFillColor(0);
         p_leg[i]->SetFillStyle(0);
         p_leg[i]->Draw();
      }
   }
   cout<<"c01 finished"<<endl;
   /***************** half-life as a function of Z by isotone *******************/
   c02->Divide(3,2);
   for(int i=1; i<7; i++){
      if(n_dimiso[i]==0){
         continue;
      }
      c02->cd(i);
      c02->cd(i)->SetGridx(0);
      c02->cd(i)->SetGridy(0);
      c02->cd(i)->SetTopMargin(0);
      c02->cd(i)->SetBottomMargin(0.15);
      c02->cd(i)->SetLeftMargin(0.15);
      c02->cd(i)->SetRightMargin(0);
      TString content1, content2;
      set_contentN(i+44, content1, content2);
      n_sys_expnew[i] = new TGraphAsymmErrors(n_dimiso[i],n_protonnumnewexp[i],n_newexphalf[i],n_protonerror[i],n_protonerror[i],n_newexphalfL[i],n_newexphalfR[i]);
      n_sys_expgnew[i] = new TGraphAsymmErrors(n_dimiso[i],n_protonnumnewexpg[i],n_newexpghalf[i],n_protonerror[i],n_protonerror[i],n_newexpghalfL[i],n_newexpghalfR[i]);
      n_sys_expold[i] = new TGraphAsymmErrors(n_dimiso[i],n_protonnumoldexp[i],n_oldexphalf[i],n_protonerror[i],n_protonerror[i],n_oldexphalfL[i],n_oldexphalfR[i]);
      n_sys_frdm[i] = new TGraph(n_dimiso[i],n_protonnumnewexp[i],n_frdmhalf[i]);
      n_sys_frdm[i]->SetLineColor(2);
      n_sys_ktu1[i] = new TGraph(n_dimiso[i],n_protonnumnewexp[i],n_ktu1half[i]);
      n_sys_ktu1[i]->SetLineColor(4);
      //n_sys_borz[i] = new TGraph(n_dimiso[i],n_protonnumnewexp[i],n_borzhalf[i]);
      //n_sys_borz[i]->SetLineColor(6);
      //n_sys_explaw[i] = new TGraph(n_dimiso[i],n_protonnumnewexp[i],n_explaw[i]);
      //n_sys_explaw[i]->SetLineColor(3);
      TLatex text;
      text.SetTextAlign(12);
      text.SetTextSize(0.1);
      text.SetNDC(kTRUE);
      find_boundryN_nhl(i+44,nmin,nmax,hlmin,hlmax);
      //cout<<i<<", "<<nmin<<endl;
      n_sys_frdm[i]->GetXaxis()->SetLimits(nmin,nmax);
      n_sys_frdm[i]->GetYaxis()->SetRangeUser(hlmin,hlmax);
      n_sys_frdm[i]->SetTitle("");
      if(i>=4){
         n_sys_frdm[i]->GetXaxis()->SetTitle("Proton number");
         n_sys_frdm[i]->GetXaxis()->CenterTitle(1);
      }else{
         n_sys_frdm[i]->GetXaxis()->SetTitle("");
      }
      n_sys_frdm[i]->GetXaxis()->SetTitleSize(0.08);
      n_sys_frdm[i]->GetXaxis()->SetLabelSize(0.08);
      n_sys_frdm[i]->GetXaxis()->SetNdivisions(nmax-nmin+1);
      if(i==1 || i==4 || i==8){
         n_sys_frdm[i]->GetYaxis()->SetTitle("Half-life (ms)");
         n_sys_frdm[i]->GetYaxis()->CenterTitle(1);
      }else{
         n_sys_frdm[i]->GetYaxis()->SetTitle("");
      }
      n_sys_frdm[i]->GetYaxis()->SetTitleSize(0.08);
      n_sys_frdm[i]->GetYaxis()->SetLabelSize(0.08);
      n_sys_frdm[i]->SetLineWidth(2);
      n_sys_ktu1[i]->SetLineWidth(2);
      //n_sys_borz[i]->SetLineWidth(2);
      //n_sys_explaw[i]->SetLineWidth(2);
      n_sys_frdm[i]->Draw("AL");
      n_sys_ktu1[i]->Draw("L");
      //n_sys_borz[i]->Draw("L");
      //n_sys_explaw[i]->Draw("L");
      if(i==6){
         n_sys_sm1 = new TGraph(n_dimiso[i]-2,n_protonnumnewexp[i],n_sm1);
         n_sys_sm1->SetLineColor(1);
         n_sys_sm2 = new TGraph(n_dimiso[i]-2,n_protonnumnewexp[i],n_sm2);
         n_sys_sm2->SetLineColor(6);
         n_sys_sm1->SetLineWidth(2);
         n_sys_sm2->SetLineWidth(2);
         n_sys_sm1->Draw("L");
         n_sys_sm2->Draw("L");
      }
      n_sys_expold[i]->Draw("P");
      n_sys_expnew[i]->Draw("P");
      n_sys_expgnew[i]->Draw("P");
      text.DrawLatex(.2,.8,content1);
      gPad->SetLogy(1);
      n_sys_expnew[i]->SetMarkerStyle(24);
      n_sys_expnew[i]->SetMarkerSize(1);
      n_sys_expgnew[i]->SetMarkerStyle(20);
      n_sys_expgnew[i]->SetMarkerSize(1);
      n_sys_expold[i]->SetMarkerStyle(26);
      n_sys_expold[i]->SetMarkerSize(1);
      if(i==1){
         n_leg[i] = new TLegend(0.63,0.15,1.08,0.6,"");
         n_leg[i]->AddEntry(n_sys_expgnew[i],"w gamma","P");
         n_leg[i]->AddEntry(n_sys_expnew[i],"w/o gamma","P");
         n_leg[i]->AddEntry(n_sys_expold[i],"Prev. Exp.","P");
         n_leg[i]->AddEntry(n_sys_frdm[i],"FRDM+QRPA","L");
         n_leg[i]->AddEntry(n_sys_ktu1[i],"KTUY+GT2","L");
         //n_leg[i]->AddEntry(n_sys_borz[i],"DF+CQRPA","L");
         //n_leg[i]->AddEntry(n_sys_explaw[i],"Exp Law","L");
         n_leg[i]->SetBorderSize(0);
         n_leg[i]->SetFillColor(0);
         n_leg[i]->SetFillStyle(0);
         n_leg[i]->Draw();
      }
      if(i==6){
         n_leg[i] = new TLegend(0.6,0.20,1.,0.5,"");
         n_leg[i]->AddEntry(n_sys_sm1,"SM (GT+FF)","L");
         n_leg[i]->AddEntry(n_sys_sm2,"SM (GT)","L");
         n_leg[i]->SetBorderSize(0);
         n_leg[i]->SetFillColor(0);
         n_leg[i]->SetFillStyle(0);
         n_leg[i]->Draw();
      }
   }
   cout<<"c02 finished"<<endl;
   /***************** half-life as a function of N for all isotopes *************/
   c03->cd();
   c03->cd()->SetGridx(0);
   c03->cd()->SetGridy(0);
   find_boundryZ_total_nhl(nmin, nmax, hlmin, hlmax);
   gPad->SetLogy(1);
   int if_filled=0;
   for(int i=0; i<8; i++){
      if(p_dimiso[i]==0){
         continue;
      }
      p_sys_exp[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronnumnewexp[i],p_exphalf[i],p_neutronerror[i],p_neutronerror[i],p_exphalfL[i],p_exphalfR[i]);
      p_sys_exp1[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronnumnewexp[i],p_exphalfnew[i],p_neutronerror[i],p_neutronerror[i],p_exphalfnewL[i],p_exphalfnewR[i]);
      if(if_filled==0){
         p_sys_exp[i]->GetXaxis()->SetLimits(nmin,nmax);
         p_sys_exp[i]->GetYaxis()->SetRangeUser(hlmin,hlmax);
         p_sys_exp[i]->SetTitle("Half-lives (isotope)");
         p_sys_exp[i]->GetXaxis()->SetTitle("neutron number");
         p_sys_exp[i]->GetYaxis()->SetTitle("half-life (ms)");
         p_sys_exp[i]->GetXaxis()->CenterTitle(1);
         p_sys_exp[i]->GetYaxis()->CenterTitle(1);
         p_sys_exp[i]->SetMarkerStyle(25);
         p_sys_exp1[i]->SetMarkerStyle(21);
         p_sys_exp[i]->SetMarkerSize(1);
         p_sys_exp1[i]->SetMarkerSize(2);
         p_sys_exp[i]->SetLineWidth(2);
         p_sys_exp[i]->SetLineColor(i+1);
         p_sys_exp[i]->Draw("APL");
         p_sys_exp1[i]->Draw("P");
         if_filled=1;
      }else{
         p_sys_exp[i]->SetMarkerStyle(25);
         p_sys_exp1[i]->SetMarkerStyle(21);
         p_sys_exp[i]->SetMarkerSize(1);
         p_sys_exp1[i]->SetMarkerSize(2);
         p_sys_exp[i]->SetLineWidth(2);
         p_sys_exp[i]->SetLineColor(i+1);
         p_sys_exp[i]->Draw("PL");
         p_sys_exp1[i]->Draw("P");
      }
   }
   p_legend = new TLegend(0.7,0.5,1.1,0.9,"");
   for(int i=7; i>=0; i--){
      if(p_dimiso[i]==0){
         continue;
      }
      TString content1, content2;
      set_contentZ(26+i, content1, content2);
      p_legend->AddEntry(p_sys_exp[i],content1,"PL");
   }
   p_legend->AddEntry(p_sys_exp1[1],"new half-life","P");
   p_legend->SetBorderSize(0);
   p_legend->SetFillColor(0);
   p_legend->SetFillStyle(0);
   p_legend->Draw();
   cout<<"c03 finished"<<endl;
   /***************** half-life as a function of Z for all isotones *************/
   c04->cd();
   c04->cd()->SetGridx(0);
   c04->cd()->SetGridy(0);
   find_boundryN_total_nhl(nmin, nmax, hlmin, hlmax);
   gPad->SetLogy(1);
   if_filled=0;
   for(int i=0; i<11; i++){
      if(n_dimiso[i]==0){
         continue;
      }
      if(i>=5){
         n_sys_exp[i] = new TGraphAsymmErrors(n_dimiso[i]-1,n_protonnumnewexp[i],n_exphalf[i],n_protonerror[i],n_protonerror[i],n_exphalfL[i],n_exphalfR[i]);
      }else{
         n_sys_exp[i] = new TGraphAsymmErrors(n_dimiso[i],n_protonnumnewexp[i],n_exphalf[i],n_protonerror[i],n_protonerror[i],n_exphalfL[i],n_exphalfR[i]);
      }
      if(if_filled==0){
         n_sys_exp[i]->GetXaxis()->SetLimits(nmin,nmax);
         n_sys_exp[i]->GetYaxis()->SetRangeUser(hlmin,hlmax);
         n_sys_exp[i]->SetTitle("Half-lives (isotone)");
         n_sys_exp[i]->GetXaxis()->SetTitle("Proton number");
         n_sys_exp[i]->GetYaxis()->SetTitle("half-life (ms)");
         n_sys_exp[i]->GetXaxis()->CenterTitle(1);
         n_sys_exp[i]->GetYaxis()->CenterTitle(1);
         n_sys_exp[i]->SetMarkerStyle(24);
         n_sys_exp[i]->SetMarkerSize(1);
         n_sys_exp[i]->SetLineWidth(2);
         if(i<10 && i>0){
            n_sys_exp[i]->SetLineColor(i);
         }else if(i==0){
            n_sys_exp[i]->SetLineColor(i+20);
         }else{
            n_sys_exp[i]->SetLineColor(i+1);
         }
         n_sys_exp[i]->Draw("APL");
         if_filled=1;
      }else{
         n_sys_exp[i]->SetMarkerStyle(24);
         n_sys_exp[i]->SetMarkerSize(1);
         n_sys_exp[i]->SetLineWidth(2);
         if(i<10){
            n_sys_exp[i]->SetLineColor(i);
         }else{
            n_sys_exp[i]->SetLineColor(i+1);
         }
         n_sys_exp[i]->Draw("PL");
      }
   }
   n_legend = new TLegend(0.10,0.5,0.6,0.9,"");
   for(int i=10; i>=0; i--){
      if(n_dimiso[i]==0){
         continue;
      }
      TString content1, content2;
      set_contentN(44+i, content1, content2);
      n_legend->AddEntry(n_sys_exp[i],content2,"PL");
   }
   n_legend->SetBorderSize(0);
   n_legend->SetFillColor(0);
   n_legend->SetFillStyle(0);
   n_legend->Draw();
   cout<<"c04 finished"<<endl;
   ///***************** half-life as a function of Q for by isotope ***************/
   //c05->cd();
   //c05->cd()->SetGridx(0);
   //c05->cd()->SetGridy(0);
   //find_boundryZ_total_Q_5hl(Q_5min,Q_5max,hlmin,hlmax);
   ////gPad->SetLogy(1);
   //gPad->SetLogx(1);
   //if_filled=0;
   //for(int i=0; i<9; i++){
   //   if(p_dimiso[i]==0){
   //      continue;
   //   }
   //   if(i==1||i==2){
   //      p_sys_Qhlexp[i] = new TGraphAsymmErrors(p_dimiso[i]-1,p_exphalf[i],p_expQ_5[i],p_exphalfL[i],p_exphalfR[i],p_expQ_5L[i],p_expQ_5R[i]);
   //   }else{
   //      p_sys_Qhlexp[i] = new TGraphAsymmErrors(p_dimiso[i],p_exphalf[i],p_expQ_5[i],p_exphalfL[i],p_exphalfR[i],p_expQ_5L[i],p_expQ_5R[i]);
   //   }
   //   if(if_filled==0){
   //      p_sys_Qhlexp[i]->GetXaxis()->SetLimits(hlmin,hlmax);
   //      p_sys_Qhlexp[i]->GetYaxis()->SetRangeUser(Q_5min,Q_5max);
   //      p_sys_Qhlexp[i]->SetTitle("half-life vs. Q^-5 (isotope)");
   //      p_sys_Qhlexp[i]->GetXaxis()->SetTitle("half-life (ms)");
   //      p_sys_Qhlexp[i]->GetYaxis()->SetTitle("Q-beta (MeV ^-5)");
   //      p_sys_Qhlexp[i]->GetXaxis()->CenterTitle(1);
   //      p_sys_Qhlexp[i]->GetYaxis()->CenterTitle(1);
   //      p_sys_Qhlexp[i]->SetMarkerStyle(25);
   //      p_sys_Qhlexp[i]->SetMarkerSize(1);
   //      p_sys_Qhlexp[i]->SetLineWidth(2);
   //      p_sys_Qhlexp[i]->SetLineColor(i+1);
   //      p_sys_Qhlexp[i]->Draw("APL");
   //      if_filled=1;
   //   }else{
   //      p_sys_Qhlexp[i]->SetMarkerStyle(25);
   //      p_sys_Qhlexp[i]->SetMarkerSize(1);
   //      p_sys_Qhlexp[i]->SetLineWidth(2);
   //      p_sys_Qhlexp[i]->SetLineColor(i+1);
   //      p_sys_Qhlexp[i]->Draw("PL");
   //   }
   //}
   //p_Qhllegend = new TLegend(0.7,0.5,1.1,0.9,"");
   //for(int i=8; i>=0; i--){
   //   if(p_dimiso[i]==0){
   //      continue;
   //   }
   //   TString content1, content2;
   //   set_contentZ(26+i, content1, content2);
   //   p_Qhllegend->AddEntry(p_sys_Qhlexp[i],content2,"PL");
   //}
   //p_Qhllegend->SetBorderSize(0);
   //p_Qhllegend->SetFillColor(0);
   //p_Qhllegend->SetFillStyle(0);
   //p_Qhllegend->Draw();
   //cout<<"c05 finished"<<endl;
   ///***************** half-life as a function of Q for by isotone ***************/
   //c06->cd();
   //c06->cd()->SetGridx(0);
   //c06->cd()->SetGridy(0);
   //find_boundryN_total_Q_5hl(Q_5min,Q_5max,hlmin,hlmax);
   ////gPad->SetLogy(1);
   //gPad->SetLogx(1);
   //if_filled=0;
   //for(int i=1; i<11; i++){
   //   if(n_dimiso[i]==0){
   //      continue;
   //   }
   //   if(i==6||i==8){
   //      n_sys_Qhlexp[i] = new TGraphAsymmErrors(n_dimiso[i]-1,&n_exphalf[i][1],&n_expQ_5[i][1],&n_exphalfL[i][1],&n_exphalfR[i][1],&n_expQ_5L[i][1],&n_expQ_5R[i][1]);
   //   }else{
   //      n_sys_Qhlexp[i] = new TGraphAsymmErrors(n_dimiso[i],n_exphalf[i],n_expQ_5[i],n_exphalfL[i],n_exphalfR[i],n_expQ_5L[i],n_expQ_5R[i]);
   //   }
   //   if(if_filled==0){
   //      n_sys_Qhlexp[i]->GetXaxis()->SetLimits(hlmin,hlmax);
   //      n_sys_Qhlexp[i]->GetYaxis()->SetRangeUser(Q_5min,Q_5max);
   //      n_sys_Qhlexp[i]->SetTitle("half-life vs. Q^-5 (isotone)");
   //      n_sys_Qhlexp[i]->GetXaxis()->SetTitle("half-life (ms)");
   //      n_sys_Qhlexp[i]->GetYaxis()->SetTitle("Q-beta (MeV ^-5)");
   //      n_sys_Qhlexp[i]->GetXaxis()->CenterTitle(1);
   //      n_sys_Qhlexp[i]->GetYaxis()->CenterTitle(1);
   //      n_sys_Qhlexp[i]->SetMarkerStyle(24);
   //      n_sys_Qhlexp[i]->SetMarkerSize(1);
   //      n_sys_Qhlexp[i]->SetLineWidth(2);
   //      if(i<10){
   //         n_sys_Qhlexp[i]->SetLineColor(i);
   //      }else{
   //         n_sys_Qhlexp[i]->SetLineColor(i+1);
   //      }
   //      n_sys_Qhlexp[i]->Draw("APL");
   //      if_filled=1;
   //   }else{
   //      n_sys_Qhlexp[i]->SetMarkerStyle(24);
   //      n_sys_Qhlexp[i]->SetMarkerSize(1);
   //      n_sys_Qhlexp[i]->SetLineWidth(2);
   //      if(i<10){
   //         n_sys_Qhlexp[i]->SetLineColor(i);
   //      }else{
   //         n_sys_Qhlexp[i]->SetLineColor(i+1);
   //      }
   //      n_sys_Qhlexp[i]->Draw("PL");
   //   }
   //}
   //n_Qhllegend = new TLegend(0.10,0.5,0.6,0.9,"");
   //for(int i=10; i>=1; i--){
   //   if(n_dimiso[i]==0){
   //      continue;
   //   }
   //   TString content1, content2;
   //   set_contentN(44+i, content1, content2);
   //   n_Qhllegend->AddEntry(n_sys_Qhlexp[i],content2,"PL");
   //}
   //n_Qhllegend->SetBorderSize(0);
   //n_Qhllegend->SetFillColor(0);
   //n_Qhllegend->SetFillStyle(0);
   //n_Qhllegend->Draw();
   //cout<<"c06 finished"<<endl;

   ///***************** Q^-5 as a function of N for all isotopes *************/
   //c07->cd();
   //c07->cd()->SetGridx(0);
   //c07->cd()->SetGridy(0);
   //find_boundryZ_total_nhl(nmin, nmax, hlmin, hlmax);
   //find_boundryZ_total_Q_5(Q_5min, Q_5max);
   //gPad->SetLogy(1);
   //if_filled=0;
   //for(int i=0; i<9; i++){
   //   if(p_dimiso[i]==0){
   //      continue;
   //   }
   //   p_sys_Qexp[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronnumnewexp[i],p_expQ_5[i],p_neutronerror[i],p_neutronerror[i],p_expQ_5L[i],p_expQ_5R[i]);
   //   if(if_filled==0){
   //      p_sys_Qexp[i]->GetXaxis()->SetLimits(nmin,nmax);
   //      p_sys_Qexp[i]->GetYaxis()->SetRangeUser(Q_5min,Q_5max);
   //      p_sys_Qexp[i]->SetTitle("Q^-5 (isotope)");
   //      p_sys_Qexp[i]->GetXaxis()->SetTitle("neutron number");
   //      p_sys_Qexp[i]->GetYaxis()->SetTitle("Q-beta (MeV ^-5)");
   //      p_sys_Qexp[i]->GetXaxis()->CenterTitle(1);
   //      p_sys_Qexp[i]->GetYaxis()->CenterTitle(1);
   //      p_sys_Qexp[i]->SetMarkerStyle(24);
   //      p_sys_Qexp[i]->SetMarkerSize(1);
   //      p_sys_Qexp[i]->SetLineWidth(2);
   //      p_sys_Qexp[i]->SetLineColor(i+1);
   //      p_sys_Qexp[i]->Draw("APL");
   //      if_filled=1;
   //   }else{
   //      p_sys_Qexp[i]->SetMarkerStyle(24);
   //      p_sys_Qexp[i]->SetMarkerSize(1);
   //      p_sys_Qexp[i]->SetLineWidth(2);
   //      p_sys_Qexp[i]->SetLineColor(i+1);
   //      p_sys_Qexp[i]->Draw("PL");
   //   }
   //}
   //p_Qlegend = new TLegend(0.7,0.5,1.1,0.9,"");
   //for(int i=8; i>=0; i--){
   //   if(p_dimiso[i]==0){
   //      continue;
   //   }
   //   TString content1, content2;
   //   set_contentZ(26+i, content1, content2);
   //   p_Qlegend->AddEntry(p_sys_Qexp[i],content2,"PL");
   //}
   //p_Qlegend->SetBorderSize(0);
   //p_Qlegend->SetFillColor(0);
   //p_Qlegend->SetFillStyle(0);
   //p_Qlegend->Draw();
   //cout<<"c07 finished"<<endl;
   ///***************** Q^-5 as a function of Z for all isotones *************/
   //c08->cd();
   //c08->cd()->SetGridx(0);
   //c08->cd()->SetGridy(0);
   //find_boundryN_total_nhl(nmin, nmax, hlmin, hlmax);
   //find_boundryN_total_Q_5(Q_5min, Q_5max);
   //gPad->SetLogy(1);
   //if_filled=0;
   //for(int i=1; i<11; i++){
   //   if(n_dimiso[i]==0){
   //      continue;
   //   }
   //   n_sys_Qexp[i] = new TGraphAsymmErrors(n_dimiso[i],n_protonnumnewexp[i],n_expQ_5[i],n_protonerror[i],n_protonerror[i],n_expQ_5L[i],n_expQ_5R[i]);
   //   if(if_filled==0){
   //      n_sys_Qexp[i]->GetXaxis()->SetLimits(nmin,nmax);
   //      n_sys_Qexp[i]->GetYaxis()->SetRangeUser(Q_5min,Q_5max);
   //      n_sys_Qexp[i]->SetTitle("Q^-5 (isotone)");
   //      n_sys_Qexp[i]->GetXaxis()->SetTitle("neutron number");
   //      n_sys_Qexp[i]->GetYaxis()->SetTitle("Q-beta (MeV ^-5)");
   //      n_sys_Qexp[i]->GetXaxis()->CenterTitle(1);
   //      n_sys_Qexp[i]->GetYaxis()->CenterTitle(1);
   //      n_sys_Qexp[i]->SetMarkerStyle(24);
   //      n_sys_Qexp[i]->SetMarkerSize(1);
   //      n_sys_Qexp[i]->SetLineWidth(2);
   //      if(i<10){
   //         n_sys_Qexp[i]->SetLineColor(i);
   //      }else{
   //         n_sys_Qexp[i]->SetLineColor(i+1);
   //      }
   //      n_sys_Qexp[i]->Draw("APL");
   //      if_filled=1;
   //   }else{
   //      n_sys_Qexp[i]->SetMarkerStyle(24);
   //      n_sys_Qexp[i]->SetMarkerSize(1);
   //      n_sys_Qexp[i]->SetLineWidth(2);
   //      if(i<10){
   //         n_sys_Qexp[i]->SetLineColor(i);
   //      }else{
   //         n_sys_Qexp[i]->SetLineColor(i+1);
   //      }
   //      n_sys_Qexp[i]->Draw("PL");
   //   }
   //}
   //n_Qlegend = new TLegend(0.10,0.5,0.6,0.9,"");
   //for(int i=10; i>=1; i--){
   //   if(n_dimiso[i]==0){
   //      continue;
   //   }
   //   TString content1, content2;
   //   set_contentN(44+i, content1, content2);
   //   n_Qlegend->AddEntry(n_sys_Qexp[i],content2,"PL");
   //}
   //n_Qlegend->SetBorderSize(0);
   //n_Qlegend->SetFillColor(0);
   //n_Qlegend->SetFillStyle(0);
   //n_Qlegend->Draw();
   //cout<<"c08 finished"<<endl;
   ///***************** half-life * Q^-5 as a function of N for all isotopes *************/
   //c09->cd();
   //c09->cd()->SetGridx(0);
   //c09->cd()->SetGridy(0);
   //find_boundryZ_total_narb(nmin, nmax, arbmin, arbmax);
   //gPad->SetLogy(1);
   //if_filled=0;
   //for(int i=0; i<9; i++){
   //   if(p_dimiso[i]==0){
   //      continue;
   //   }
   //   p_sys_arbexp[i] = new TGraphAsymmErrors(p_dimiso[i],p_neutronnumnewexp[i],p_exparb[i],p_neutronerror[i],p_neutronerror[i],p_exparbL[i],p_exparbR[i]);
   //   if(if_filled==0){
   //      p_sys_arbexp[i]->GetXaxis()->SetLimits(nmin,nmax);
   //      p_sys_arbexp[i]->GetYaxis()->SetRangeUser(arbmin,arbmax);
   //      p_sys_arbexp[i]->SetTitle("Half-lives * Q^-5 (isotope)");
   //      p_sys_arbexp[i]->GetXaxis()->SetTitle("Neutron number");
   //      p_sys_arbexp[i]->GetYaxis()->SetTitle("half-life * Q^-5");
   //      p_sys_arbexp[i]->GetXaxis()->CenterTitle(1);
   //      p_sys_arbexp[i]->GetYaxis()->CenterTitle(1);
   //      p_sys_arbexp[i]->SetMarkerStyle(24);
   //      p_sys_arbexp[i]->SetMarkerSize(1);
   //      p_sys_arbexp[i]->SetLineWidth(2);
   //      p_sys_arbexp[i]->SetLineColor(i+1);
   //      p_sys_arbexp[i]->Draw("APL");
   //      if_filled=1;
   //   }else{
   //      p_sys_arbexp[i]->SetMarkerStyle(24);
   //      p_sys_arbexp[i]->SetMarkerSize(1);
   //      p_sys_arbexp[i]->SetLineWidth(2);
   //      p_sys_arbexp[i]->SetLineColor(i+1);
   //      p_sys_arbexp[i]->Draw("PL");
   //   }
   //}
   //p_arblegend = new TLegend(0.7,0.5,1.1,0.9,"");
   //for(int i=8; i>=0; i--){
   //   if(p_dimiso[i]==0){
   //      continue;
   //   }
   //   TString content1, content2;
   //   set_contentZ(26+i, content1, content2);
   //   p_arblegend->AddEntry(p_sys_arbexp[i],content2,"PL");
   //}
   //p_arblegend->SetBorderSize(0);
   //p_arblegend->SetFillColor(0);
   //p_arblegend->SetFillStyle(0);
   //p_arblegend->Draw();
   //cout<<"c09 finished"<<endl;
   ///***************** half-life * Q^-5 as a function of Z for all isotones *************/
   //c10->cd();
   //c10->cd()->SetGridx(0);
   //c10->cd()->SetGridy(0);
   //find_boundryN_total_narb(nmin, nmax, arbmin, arbmax);
   //gPad->SetLogy(1);
   //if_filled=0;
   //for(int i=1; i<11; i++){
   //   if(n_dimiso[i]==0){
   //      continue;
   //   }
   //   n_sys_arbexp[i] = new TGraphAsymmErrors(n_dimiso[i],n_protonnumnewexp[i],n_exparb[i],n_protonerror[i],n_protonerror[i],n_exparbL[i],n_exparbR[i]);
   //   if(if_filled==0){
   //      n_sys_arbexp[i]->GetXaxis()->SetLimits(nmin,nmax);
   //      n_sys_arbexp[i]->GetYaxis()->SetRangeUser(arbmin,arbmax);
   //      n_sys_arbexp[i]->SetTitle("Half-lives * Q^-5 (isotone)");
   //      n_sys_arbexp[i]->GetXaxis()->SetTitle("Proton number");
   //      n_sys_arbexp[i]->GetYaxis()->SetTitle("half-life * Q^-5");
   //      n_sys_arbexp[i]->GetXaxis()->CenterTitle(1);
   //      n_sys_arbexp[i]->GetYaxis()->CenterTitle(1);
   //      n_sys_arbexp[i]->SetMarkerStyle(24);
   //      n_sys_arbexp[i]->SetMarkerSize(1);
   //      n_sys_arbexp[i]->SetLineWidth(2);
   //      if(i<10){
   //         n_sys_arbexp[i]->SetLineColor(i);
   //      }else{
   //         n_sys_arbexp[i]->SetLineColor(i+1);
   //      }
   //      n_sys_arbexp[i]->Draw("APL");
   //      if_filled=1;
   //   }else{
   //      n_sys_arbexp[i]->SetMarkerStyle(24);
   //      n_sys_arbexp[i]->SetMarkerSize(1);
   //      n_sys_arbexp[i]->SetLineWidth(2);
   //      if(i<10){
   //         n_sys_arbexp[i]->SetLineColor(i);
   //      }else{
   //         n_sys_arbexp[i]->SetLineColor(i+1);
   //      }
   //      n_sys_arbexp[i]->Draw("PL");
   //   }
   //}
   //n_arblegend = new TLegend(0.10,0.5,0.6,0.9,"");
   //for(int i=10; i>=1; i--){
   //   if(n_dimiso[i]==0){
   //      continue;
   //   }
   //   TString content1, content2;
   //   set_contentN(44+i, content1, content2);
   //   n_arblegend->AddEntry(n_sys_arbexp[i],content2,"PL");
   //}
   //n_arblegend->SetBorderSize(0);
   //n_arblegend->SetFillColor(0);
   //n_arblegend->SetFillStyle(0);
   //n_arblegend->Draw();
   //cout<<"c10 finished"<<endl;
   ///***************** half-life ratio as a function of N for all isotopes *************/
   //c11->cd();
   //c11->cd()->SetGridx(0);
   //c11->cd()->SetGridy(0);
   //find_boundryZ_total_nhlrt(nmin, nmax, hlrtmin, hlrtmax);
   //if_filled=0;
   //for(int i=2; i<8; i++){
   //   if(p_dimiso[i]==0){
   //      continue;
   //   }
   //   p_sys_hlrtexp[i] = new TGraphAsymmErrors(p_dimiso[i]-1,p_neutronnumnewexp[i],p_exphlrt[i],p_neutronerror[i],p_neutronerror[i],p_exphlrtL[i],p_exphlrtR[i]);
   //   if(if_filled==0){
   //      p_sys_hlrtexp[i]->GetXaxis()->SetLimits(nmin,nmax);
   //      p_sys_hlrtexp[i]->GetYaxis()->SetRangeUser(0,hlrtmax);
   //      p_sys_hlrtexp[i]->SetTitle("Half-lives ratio { T1/2(N) / T1/2(N+1) }");
   //      p_sys_hlrtexp[i]->GetXaxis()->SetTitle("Neutron number");
   //      p_sys_hlrtexp[i]->GetYaxis()->SetTitle("half-life ratio");
   //      p_sys_hlrtexp[i]->GetXaxis()->CenterTitle(1);
   //      p_sys_hlrtexp[i]->GetYaxis()->CenterTitle(1);
   //      p_sys_hlrtexp[i]->SetMarkerStyle(24);
   //      p_sys_hlrtexp[i]->SetMarkerSize(1);
   //      p_sys_hlrtexp[i]->SetLineWidth(2);
   //      p_sys_hlrtexp[i]->SetLineColor(i+1);
   //      p_sys_hlrtexp[i]->Draw("APL");
   //      if_filled=1;
   //   }else{
   //      p_sys_hlrtexp[i]->SetMarkerStyle(24);
   //      p_sys_hlrtexp[i]->SetMarkerSize(1);
   //      p_sys_hlrtexp[i]->SetLineWidth(2);
   //      p_sys_hlrtexp[i]->SetLineColor(i+1);
   //      p_sys_hlrtexp[i]->Draw("PL");
   //   }
   //}
   //p_hlrtlegend = new TLegend(0.7,0.5,1.1,0.9,"");
   //for(int i=7; i>=2; i--){
   //   if(p_dimiso[i]==0){
   //      continue;
   //   }
   //   TString content1, content2;
   //   set_contentZ(26+i, content1, content2);
   //   p_hlrtlegend->AddEntry(p_sys_hlrtexp[i],content2,"PL");
   //}
   //p_hlrtlegend->SetBorderSize(0);
   //p_hlrtlegend->SetFillColor(0);
   //p_hlrtlegend->SetFillStyle(0);
   //p_hlrtlegend->Draw();
   //cout<<"c11 finished"<<endl;
   ///***************** half-life ratio as a function of Z for all isotones *************/
   //c12->cd();
   //c12->cd()->SetGridx(0);
   //c12->cd()->SetGridy(0);
   //find_boundryN_total_nhlrt(nmin, nmax, hlrtmin, hlrtmax);
   //if_filled=0;
   //for(int i=1; i<7; i++){
   //   if(n_dimiso[i]==0){
   //      continue;
   //   }
   //   n_sys_hlrtexp[i] = new TGraphAsymmErrors(n_dimiso[i]-1,&n_protonnumnewexp[i][1],&n_exphlrt[i][1],&n_protonerror[i][1],&n_protonerror[i][1],&n_exphlrtL[i][1],&n_exphlrtR[i][1]);
   //   if(if_filled==0){
   //      n_sys_hlrtexp[i]->GetXaxis()->SetLimits(nmin,nmax);
   //      n_sys_hlrtexp[i]->GetYaxis()->SetRangeUser(0,hlrtmax);
   //      n_sys_hlrtexp[i]->SetTitle("Half-lives ratio { T1/2(Z) / T1/2(Z-1) }");
   //      n_sys_hlrtexp[i]->GetXaxis()->SetTitle("Proton number");
   //      n_sys_hlrtexp[i]->GetYaxis()->SetTitle("half-life ratio");
   //      n_sys_hlrtexp[i]->GetXaxis()->CenterTitle(1);
   //      n_sys_hlrtexp[i]->GetYaxis()->CenterTitle(1);
   //      n_sys_hlrtexp[i]->SetMarkerStyle(24);
   //      n_sys_hlrtexp[i]->SetMarkerSize(1);
   //      n_sys_hlrtexp[i]->SetLineWidth(2);
   //      if(i<10){
   //         n_sys_hlrtexp[i]->SetLineColor(i);
   //      }else{
   //         n_sys_hlrtexp[i]->SetLineColor(i+1);
   //      }
   //      n_sys_hlrtexp[i]->Draw("APL");
   //      if_filled=1;
   //   }else{
   //      n_sys_hlrtexp[i]->SetMarkerStyle(24);
   //      n_sys_hlrtexp[i]->SetMarkerSize(1);
   //      n_sys_hlrtexp[i]->SetLineWidth(2);
   //      if(i<10){
   //         n_sys_hlrtexp[i]->SetLineColor(i);
   //      }else{
   //         n_sys_hlrtexp[i]->SetLineColor(i+1);
   //      }
   //      n_sys_hlrtexp[i]->Draw("PL");
   //   }
   //}
   //n_hlrtlegend = new TLegend(0.5,0.5,0.9,0.9,"");
   //for(int i=6; i>=1; i--){
   //   if(n_dimiso[i]==0){
   //      continue;
   //   }
   //   TString content1, content2;
   //   set_contentN(44+i, content1, content2);
   //   n_hlrtlegend->AddEntry(n_sys_hlrtexp[i],content2,"PL");
   //}
   //n_hlrtlegend->SetBorderSize(0);
   //n_hlrtlegend->SetFillColor(0);
   //n_hlrtlegend->SetFillStyle(0);
   //n_hlrtlegend->Draw();
   //cout<<"c12 finished"<<endl;

   c01->Write();
   c02->Write();
   c03->Write();
   c04->Write();
   //c05->Write();
   //c06->Write();
   //c07->Write();
   //c08->Write();
   //c09->Write();
   //c10->Write();
   //c11->Write();
   //c12->Write();
   RootFile->Write();
   delete RootFile;
}
