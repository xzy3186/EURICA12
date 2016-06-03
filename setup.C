//This macro is used for offline analysis to load files to the 
//Chain and add TCUTGs defined in the cut folder

#include "TCutG.h"
#include "TChain.h"
#include "TFile.h"

TChain *c130cd = new TChain();

void setup(){

  char name[100]; 

  //--------------------------------------------------------------------
  //PID cut files:
  TFile *BRcut[3];
  TFile *ZDcut[3];
  
  for(int i=0;i<3;i++) {
    sprintf(name,"./cut/brcut%i.root",i);
    BRcut[i] = new TFile(name,"READ");
  }
  
  for(int i=0;i<3;i++) {
    sprintf(name,"./cut/zdcut%i.root",i);
    ZDcut[i] = new TFile(name,"READ");
  }

  //--------------------------------------------------------------------
  //Cuts
  TCutG *brcut[3];
  TCutG *zdcut[3];

  for(int i=0;i<3;i++) {
    sprintf(name,"brcut%i",i);
    BRcut[i]->GetObject(name,brcut[i]);
    brcut[i]->SetVarX("BigRIPSBeam.aoq[0]");
    brcut[i]->SetVarY("BigRIPSBeam.zet[0]");
  }
  
  for(int i=0;i<3;i++) {
    sprintf(name,"zdcut%i",i);
    ZDcut[i]->GetObject(name,zdcut[i]);
    zdcut[i]->SetVarX("BigRIPSBeam.aoq[3]");
    zdcut[i]->SetVarY("BigRIPSBeam.zet[3]");
  }

  //130Cd coulex
  //c130cd->AddFile("./rootfiles/run0001.root",0,"tree");
    
  return;
}




