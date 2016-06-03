{

  //  gROOT->Reset();

#include "Riostream.h"

 
  double t12[150][150];
  double t12nishimu[150][150];
  double ertl[150][150];
  double erth[150][150];

  ifstream infile;
  ofstream outfile;

  int  Znumber,Nnumber;
  Double_t Anishimu[8]={0};

  double data,halflife,errl,errh;

 int Z; int num[100]; 

 
TCanvas *c1 = new TCanvas("c1","Graph Draw Options",0,0,2000,800);


TLatex l;
 l.SetTextAlign(12);
 l.SetTextSize(0.1);

 c1->Divide(4,2);

 

 int N[100]; N[40]=63; N[41]=64; N[42]=66; N[43]=67; N[44]=67; N[45]=69; N[46]=71; N[47]=75;

 int M[100];
  int n=20; 
   Double_t plot[n]={0}, X[n]={0}, etl[n]={0}, eth[n]={0}, eA[n]={0};

 
for (int canv=1; canv<=7; canv++){
 
  c1->cd(canv); Z=47-canv;

//========================THEORY=================================
 
 infile.open("frdm.dat");

   while (!infile.eof()){
     infile>>Znumber>>Nnumber>>halflife>>data>>data>>data>>data;
     t12[Znumber][Nnumber]=halflife*1000;
   }
 
   for (int i=0; i<n; i++){
     plot[i]=t12[Z][N[Z]+i-1];
     X[i]=Z+N[Z]+i-1;
   }
   
        TGraph *frdm = new TGraph(n,X,plot);
	frdm->Draw("AL");
	frdm->SetLineColor(2);
	
   infile.close();

//=========================NISHIMU===============================

    infile.open("nishimu.dat");
  
    while (!infile.eof()){
     infile>>Znumber>>Nnumber>>halflife>>errl>>errh;
     t12nishimu[Znumber][Nnumber]=halflife*1000;
     ertl[Znumber][Nnumber]=errl*1000;
     erth[Znumber][Nnumber]=errh*1000;

    }

     for (int i=0; i<9; i++){
       plot[i]=t12nishimu[Z][N[Z]+i];
       etl[i]=ertl[Z][N[Z]+i];
       eth[i]=erth[Z][N[Z]+i];
       Anishimu[i]=Z+N[Z]+i;
     }

     //TGraphErrors *expnishimu = new TGraph(8,Anishimu,plot,eA,eth); 
     expnishimu = new TGraphAsymmErrors(8,Anishimu,plot,eA,eA,etl,eth); 
     expnishimu->Draw("P");

 infile.close();
//=======================GIUSEPPE==============================    
     
 num[40]=2; num[41]=2; num[42]=3; num[43]=8; num[44]=5; num[45]=7; num[46]=6;
 M[40]=70; M[41]=72; M[42]=73; M[43]=72; M[44]=75; M[45]=77; M[46]=77;

   infile.open("giuseppe.dat");
  
    while (!infile.eof()){
     infile>>Znumber>>Nnumber>>halflife>>errl>>errh;
     t12nishimu[Znumber][Nnumber]=halflife*1000;
     ertl[Znumber][Nnumber]=errl*1000;
     erth[Znumber][Nnumber]=errh*1000;
    }

     for (int i=0; i<num[Z]; i++){
       plot[i]=t12nishimu[Z][M[Z]+i];
       etl[i]=ertl[Z][M[Z]+i];
       eth[i]=erth[Z][M[Z]+i];
       Anishimu[i]=Z+M[Z]+i;
       cout<<Anishimu[i]<<" "<<plot[i]<<endl;
     }

     //TGraphErrors *expnishimu = new TGraph(8,Anishimu,plot,eA,eth); 
     expgiuseppe = new TGraphAsymmErrors(num[Z],Anishimu,plot,eA,eA,etl,eth); 
     expgiuseppe->Draw("P");


 infile.close();

//===================== DRAWING OPTIONS ========================//
 

 gPad->SetLogy(1);
 expnishimu->SetMarkerStyle(20);
 expgiuseppe->SetMarkerStyle(26);

 if(canv==7){
   l.DrawLatex(110,200,"_{40}Zr");
   frdm->GetXaxis()->SetRangeUser(105,112);
   frdm->GetYaxis()->SetRangeUser(25,3e2);
   frdm->SetTitle("");
  }
 if(canv==6) {
   l.DrawLatex(112,400,"_{41}Nb");
   frdm->GetXaxis()->SetRangeUser(106,115);
   frdm->GetYaxis()->SetRangeUser(10,6e2);
   frdm->SetTitle("");
 }
 if(canv==5) {
   l.DrawLatex(115,900,"_{42}Mo");
   frdm->GetXaxis()->SetRangeUser(109,118);
   frdm->GetYaxis()->SetRangeUser(20,2e3);
   frdm->SetTitle("");
  }
 if(canv==4) {
   l.DrawLatex(120,250,"_{43}Tc");
 }
 if(canv==3) {
   l.DrawLatex(121,200,"_{44}Ru");
   frdm->GetXaxis()->SetRangeUser(113,125);
   frdm->GetYaxis()->SetRangeUser(20,700);  
 frdm->SetTitle("");
  }
 if(canv==2) {
   l.DrawLatex(123,800,"_{45}Rh");
   frdm->GetXaxis()->SetRangeUser(113,128);
   frdm->GetYaxis()->SetRangeUser(5,4000);
   frdm->SetTitle("");
  }
   if(canv==1) {
     l.DrawLatex(125,2000,"_{46}Pd");
   frdm->GetXaxis()->SetRangeUser(116,129);
   frdm->GetYaxis()->SetRangeUser(20,9000);
   frdm->SetTitle("");
    }
   
 }


 leg = new TLegend(0.7, 0.85, 0.89, 0.89);
 leg->AddEntry(frdm,"FRDM","l");
 //leg->Draw();
     



     return(0);
}



