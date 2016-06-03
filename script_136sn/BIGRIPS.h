//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jun 25 22:48:01 2012 by ROOT version 5.32/00
// from TTree tree/tree
// found on file: bripsdata/brips_1111.root
//////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TClonesArray.h>
#include <TObject.h>
#include "TVectorD.h"
#include "TMatrixD.h"
#include <TArtPPAC.hh>
#include <TArtPlastic.hh>
#include <TArtIC.hh>
#include <TArtFocalPlane.hh>
#include <TArtTOF.hh>
#include <TArtRIPS.hh>
#include <TArtBeam.hh>
#include <TNamed.h>

using namespace std;

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxBigRIPSPPAC = 34;
const Int_t kMaxBigRIPSPlastic = 14;
const Int_t kMaxBigRIPSIC = 2;
const Int_t kMaxBigRIPSFocalPlane = 11;
const Int_t kMaxBigRIPSTOF = 1;
const Int_t kMaxBigRIPSRIPS = 2;
const Int_t kMaxBigRIPSBeam = 1;

class BIGRIPS {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           EventInfo_;
   UInt_t          EventInfo_fUniqueID[1];   //[EventInfo_]
   UInt_t          EventInfo_fBits[1];   //[EventInfo_]
   TString         EventInfo_fName[1];
   TString         EventInfo_fTitle[1];
   ULong64_t       EventInfo_timestamp[1];   //[EventInfo_]
   Int_t           EventInfo_runnumber[1];   //[EventInfo_]
   Int_t           EventInfo_eventnumber[1];   //[EventInfo_]
   TString         EventInfo_subsysname[1];
   Int_t           EventInfo_comp_val[1];   //[EventInfo_]
   UInt_t          EventInfo_fBit[1];   //[EventInfo_]
   //Int_t           BigRIPSPPAC_;
   //UInt_t          BigRIPSPPAC_fUniqueID[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //UInt_t          BigRIPSPPAC_fBits[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Int_t           BigRIPSPPAC_id[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Int_t           BigRIPSPPAC_fpl[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //TString         BigRIPSPPAC_name[kMaxBigRIPSPPAC];
   //Int_t           BigRIPSPPAC_fDataState[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Double_t        BigRIPSPPAC_xzpos[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Double_t        BigRIPSPPAC_yzpos[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Int_t           BigRIPSPPAC_fTX1Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Int_t           BigRIPSPPAC_fTX2Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Int_t           BigRIPSPPAC_fTY1Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Int_t           BigRIPSPPAC_fTY2Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Int_t           BigRIPSPPAC_fTARaw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Int_t           BigRIPSPPAC_fQX1Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Int_t           BigRIPSPPAC_fQX2Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Int_t           BigRIPSPPAC_fQY1Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Int_t           BigRIPSPPAC_fQY2Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Int_t           BigRIPSPPAC_fQARaw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Double_t        BigRIPSPPAC_fTSumX[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Double_t        BigRIPSPPAC_fTSumY[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Double_t        BigRIPSPPAC_fTDiffX[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Double_t        BigRIPSPPAC_fTDiffY[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Double_t        BigRIPSPPAC_fX[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Double_t        BigRIPSPPAC_fY[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Bool_t          BigRIPSPPAC_fFiredX[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Bool_t          BigRIPSPPAC_fFiredY[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
   //Int_t           BigRIPSPlastic_;
   //UInt_t          BigRIPSPlastic_fUniqueID[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //UInt_t          BigRIPSPlastic_fBits[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Int_t           BigRIPSPlastic_id[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Int_t           BigRIPSPlastic_fpl[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //TString         BigRIPSPlastic_name[kMaxBigRIPSPlastic];
   //Int_t           BigRIPSPlastic_fDataState[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Double_t        BigRIPSPlastic_zposition[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Double_t        BigRIPSPlastic_zoffset[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Int_t           BigRIPSPlastic_fTLRaw[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Int_t           BigRIPSPlastic_fTRRaw[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Int_t           BigRIPSPlastic_fQLRaw[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Int_t           BigRIPSPlastic_fQRRaw[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Double_t        BigRIPSPlastic_fTime[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Double_t        BigRIPSPlastic_fTimeL[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Double_t        BigRIPSPlastic_fTimeR[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Double_t        BigRIPSPlastic_fTimeLSlew[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Double_t        BigRIPSPlastic_fTimeRSlew[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Double_t        BigRIPSPlastic_fTimeSlew[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
   //Int_t           BigRIPSIC_;
   //UInt_t          BigRIPSIC_fUniqueID[kMaxBigRIPSIC];   //[BigRIPSIC_]
   //UInt_t          BigRIPSIC_fBits[kMaxBigRIPSIC];   //[BigRIPSIC_]
   //Int_t           BigRIPSIC_id[kMaxBigRIPSIC];   //[BigRIPSIC_]
   //Int_t           BigRIPSIC_fpl[kMaxBigRIPSIC];   //[BigRIPSIC_]
   //TString         BigRIPSIC_name[kMaxBigRIPSIC];
   //Int_t           BigRIPSIC_fDataState[kMaxBigRIPSIC];   //[BigRIPSIC_]
   //Double_t        BigRIPSIC_zcoef[kMaxBigRIPSIC][2];   //[BigRIPSIC_]
   //Double_t        BigRIPSIC_ionpair[kMaxBigRIPSIC];   //[BigRIPSIC_]
   //Int_t           BigRIPSIC_nhitchannel[kMaxBigRIPSIC];   //[BigRIPSIC_]
   //Int_t           BigRIPSIC_fADC[kMaxBigRIPSIC][10];   //[BigRIPSIC_]
   //Double_t        BigRIPSIC_fEnergy[kMaxBigRIPSIC][10];   //[BigRIPSIC_]
   //Double_t        BigRIPSIC_fRawADCSqSum[kMaxBigRIPSIC];   //[BigRIPSIC_]
   //Double_t        BigRIPSIC_fRawADCAvSum[kMaxBigRIPSIC];   //[BigRIPSIC_]
   //Double_t        BigRIPSIC_fCalMeVSqSum[kMaxBigRIPSIC];   //[BigRIPSIC_]
   //Double_t        BigRIPSIC_fCalMeVAvSum[kMaxBigRIPSIC];   //[BigRIPSIC_]
   //Int_t           BigRIPSFocalPlane_;
   //UInt_t          BigRIPSFocalPlane_fUniqueID[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
   //UInt_t          BigRIPSFocalPlane_fBits[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
   //Int_t           BigRIPSFocalPlane_id[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
   //Int_t           BigRIPSFocalPlane_fpl[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
   //TString         BigRIPSFocalPlane_name[kMaxBigRIPSFocalPlane];
   //Int_t           BigRIPSFocalPlane_fDataState[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
   ////TVectorT<double> BigRIPSFocalPlane_opt_vector[kMaxBigRIPSFocalPlane];
   //Int_t           BigRIPSFocalPlane_nfired_ppacx[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
   //Int_t           BigRIPSFocalPlane_nfired_ppacy[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
   //Double_t        BigRIPSFocalPlane_zpos[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
   //Int_t           BigRIPSTOF_;
   //UInt_t          BigRIPSTOF_fUniqueID[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
   //UInt_t          BigRIPSTOF_fBits[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
   //Int_t           BigRIPSTOF_id[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
   //Int_t           BigRIPSTOF_fpl[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
   //TString         BigRIPSTOF_name[kMaxBigRIPSTOF];
   //Int_t           BigRIPSTOF_fDataState[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
   //Double_t        BigRIPSTOF_tof[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
   //Double_t        BigRIPSTOF_clight[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
   //Double_t        BigRIPSTOF_length[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
   //TString         BigRIPSTOF_upstream_plname[kMaxBigRIPSTOF];
   //TString         BigRIPSTOF_downstream_plname[kMaxBigRIPSTOF];
   //Int_t           BigRIPSTOF_upstream_plfpl[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
   //Int_t           BigRIPSTOF_downstream_plfpl[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
   //Double_t        BigRIPSTOF_time_offset[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
   //Int_t           BigRIPSRIPS_;
   //UInt_t          BigRIPSRIPS_fUniqueID[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
   //UInt_t          BigRIPSRIPS_fBits[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
   //Int_t           BigRIPSRIPS_id[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
   //Int_t           BigRIPSRIPS_fpl[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
   //TString         BigRIPSRIPS_name[kMaxBigRIPSRIPS];
   //Int_t           BigRIPSRIPS_fDataState[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
   //Int_t           BigRIPSRIPS_upstream_fpl[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
   //Int_t           BigRIPSRIPS_downstream_fpl[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
   //Double_t        BigRIPSRIPS_center_brho[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
   //Double_t        BigRIPSRIPS_brho[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
   //Double_t        BigRIPSRIPS_length[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
   ////TMatrixT<double> BigRIPSRIPS_matrix[kMaxBigRIPSRIPS];
   //Double_t        BigRIPSRIPS_delta[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
   //Double_t        BigRIPSRIPS_angle[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
   //Int_t           BigRIPSBeam_;
   //UInt_t          BigRIPSBeam_fUniqueID[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
   //UInt_t          BigRIPSBeam_fBits[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
   //Int_t           BigRIPSBeam_id[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
   //Int_t           BigRIPSBeam_fpl[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
   //TString         BigRIPSBeam_name[kMaxBigRIPSBeam];
   //Int_t           BigRIPSBeam_fDataState[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
   //Double_t        BigRIPSBeam_brho[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
   //Double_t        BigRIPSBeam_aoq[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
   //Double_t        BigRIPSBeam_zet[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
   //Double_t        BigRIPSBeam_beta[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
   //Double_t        BigRIPSBeam_clight[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
   //Double_t        BigRIPSBeam_mnucleon[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
   //Int_t           BigRIPSBeam_nrips[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
   //TString         BigRIPSBeam_ripsname[2][kMaxBigRIPSBeam];
   //TString         BigRIPSBeam_tofname[kMaxBigRIPSBeam];
   //TString         BigRIPSBeam_icname[kMaxBigRIPSBeam];
   Double_t        AOQ;   //from new PID
   Double_t        ZET;   //from new PID

   // List of branches
   TBranch        *b_EventInfo_;   //!
   TBranch        *b_EventInfo_fUniqueID;   //!
   TBranch        *b_EventInfo_fBits;   //!
   TBranch        *b_EventInfo_fName;   //!
   TBranch        *b_EventInfo_fTitle;   //!
   TBranch        *b_EventInfo_timestamp;   //!
   TBranch        *b_EventInfo_runnumber;   //!
   TBranch        *b_EventInfo_eventnumber;   //!
   TBranch        *b_EventInfo_subsysname;   //!
   TBranch        *b_EventInfo_comp_val;   //!
   TBranch        *b_EventInfo_fBit;   //!
   //TBranch        *b_BigRIPSPPAC_;   //!
   //TBranch        *b_BigRIPSPPAC_fUniqueID;   //!
   //TBranch        *b_BigRIPSPPAC_fBits;   //!
   //TBranch        *b_BigRIPSPPAC_id;   //!
   //TBranch        *b_BigRIPSPPAC_fpl;   //!
   //TBranch        *b_BigRIPSPPAC_name;   //!
   //TBranch        *b_BigRIPSPPAC_fDataState;   //!
   //TBranch        *b_BigRIPSPPAC_xzpos;   //!
   //TBranch        *b_BigRIPSPPAC_yzpos;   //!
   //TBranch        *b_BigRIPSPPAC_fTX1Raw;   //!
   //TBranch        *b_BigRIPSPPAC_fTX2Raw;   //!
   //TBranch        *b_BigRIPSPPAC_fTY1Raw;   //!
   //TBranch        *b_BigRIPSPPAC_fTY2Raw;   //!
   //TBranch        *b_BigRIPSPPAC_fTARaw;   //!
   //TBranch        *b_BigRIPSPPAC_fQX1Raw;   //!
   //TBranch        *b_BigRIPSPPAC_fQX2Raw;   //!
   //TBranch        *b_BigRIPSPPAC_fQY1Raw;   //!
   //TBranch        *b_BigRIPSPPAC_fQY2Raw;   //!
   //TBranch        *b_BigRIPSPPAC_fQARaw;   //!
   //TBranch        *b_BigRIPSPPAC_fTSumX;   //!
   //TBranch        *b_BigRIPSPPAC_fTSumY;   //!
   //TBranch        *b_BigRIPSPPAC_fTDiffX;   //!
   //TBranch        *b_BigRIPSPPAC_fTDiffY;   //!
   //TBranch        *b_BigRIPSPPAC_fX;   //!
   //TBranch        *b_BigRIPSPPAC_fY;   //!
   //TBranch        *b_BigRIPSPPAC_fFiredX;   //!
   //TBranch        *b_BigRIPSPPAC_fFiredY;   //!
   //TBranch        *b_BigRIPSPlastic_;   //!
   //TBranch        *b_BigRIPSPlastic_fUniqueID;   //!
   //TBranch        *b_BigRIPSPlastic_fBits;   //!
   //TBranch        *b_BigRIPSPlastic_id;   //!
   //TBranch        *b_BigRIPSPlastic_fpl;   //!
   //TBranch        *b_BigRIPSPlastic_name;   //!
   //TBranch        *b_BigRIPSPlastic_fDataState;   //!
   //TBranch        *b_BigRIPSPlastic_zposition;   //!
   //TBranch        *b_BigRIPSPlastic_zoffset;   //!
   //TBranch        *b_BigRIPSPlastic_fTLRaw;   //!
   //TBranch        *b_BigRIPSPlastic_fTRRaw;   //!
   //TBranch        *b_BigRIPSPlastic_fQLRaw;   //!
   //TBranch        *b_BigRIPSPlastic_fQRRaw;   //!
   //TBranch        *b_BigRIPSPlastic_fTime;   //!
   //TBranch        *b_BigRIPSPlastic_fTimeL;   //!
   //TBranch        *b_BigRIPSPlastic_fTimeR;   //!
   //TBranch        *b_BigRIPSPlastic_fTimeLSlew;   //!
   //TBranch        *b_BigRIPSPlastic_fTimeRSlew;   //!
   //TBranch        *b_BigRIPSPlastic_fTimeSlew;   //!
   //TBranch        *b_BigRIPSIC_;   //!
   //TBranch        *b_BigRIPSIC_fUniqueID;   //!
   //TBranch        *b_BigRIPSIC_fBits;   //!
   //TBranch        *b_BigRIPSIC_id;   //!
   //TBranch        *b_BigRIPSIC_fpl;   //!
   //TBranch        *b_BigRIPSIC_name;   //!
   //TBranch        *b_BigRIPSIC_fDataState;   //!
   //TBranch        *b_BigRIPSIC_zcoef;   //!
   //TBranch        *b_BigRIPSIC_ionpair;   //!
   //TBranch        *b_BigRIPSIC_nhitchannel;   //!
   //TBranch        *b_BigRIPSIC_fADC;   //!
   //TBranch        *b_BigRIPSIC_fEnergy;   //!
   //TBranch        *b_BigRIPSIC_fRawADCSqSum;   //!
   //TBranch        *b_BigRIPSIC_fRawADCAvSum;   //!
   //TBranch        *b_BigRIPSIC_fCalMeVSqSum;   //!
   //TBranch        *b_BigRIPSIC_fCalMeVAvSum;   //!
   //TBranch        *b_BigRIPSFocalPlane_;   //!
   //TBranch        *b_BigRIPSFocalPlane_fUniqueID;   //!
   //TBranch        *b_BigRIPSFocalPlane_fBits;   //!
   //TBranch        *b_BigRIPSFocalPlane_id;   //!
   //TBranch        *b_BigRIPSFocalPlane_fpl;   //!
   //TBranch        *b_BigRIPSFocalPlane_name;   //!
   //TBranch        *b_BigRIPSFocalPlane_fDataState;   //!
// //  TBranch        *b_BigRIPSFocalPlane_opt_vector;   //!
   //TBranch        *b_BigRIPSFocalPlane_nfired_ppacx;   //!
   //TBranch        *b_BigRIPSFocalPlane_nfired_ppacy;   //!
   //TBranch        *b_BigRIPSFocalPlane_zpos;   //!
   //TBranch        *b_BigRIPSTOF_;   //!
   //TBranch        *b_BigRIPSTOF_fUniqueID;   //!
   //TBranch        *b_BigRIPSTOF_fBits;   //!
   //TBranch        *b_BigRIPSTOF_id;   //!
   //TBranch        *b_BigRIPSTOF_fpl;   //!
   //TBranch        *b_BigRIPSTOF_name;   //!
   //TBranch        *b_BigRIPSTOF_fDataState;   //!
   //TBranch        *b_BigRIPSTOF_tof;   //!
   //TBranch        *b_BigRIPSTOF_clight;   //!
   //TBranch        *b_BigRIPSTOF_length;   //!
   //TBranch        *b_BigRIPSTOF_upstream_plname;   //!
   //TBranch        *b_BigRIPSTOF_downstream_plname;   //!
   //TBranch        *b_BigRIPSTOF_upstream_plfpl;   //!
   //TBranch        *b_BigRIPSTOF_downstream_plfpl;   //!
   //TBranch        *b_BigRIPSTOF_time_offset;   //!
   //TBranch        *b_BigRIPSRIPS_;   //!
   //TBranch        *b_BigRIPSRIPS_fUniqueID;   //!
   //TBranch        *b_BigRIPSRIPS_fBits;   //!
   //TBranch        *b_BigRIPSRIPS_id;   //!
   //TBranch        *b_BigRIPSRIPS_fpl;   //!
   //TBranch        *b_BigRIPSRIPS_name;   //!
   //TBranch        *b_BigRIPSRIPS_fDataState;   //!
   //TBranch        *b_BigRIPSRIPS_upstream_fpl;   //!
   //TBranch        *b_BigRIPSRIPS_downstream_fpl;   //!
   //TBranch        *b_BigRIPSRIPS_center_brho;   //!
   //TBranch        *b_BigRIPSRIPS_brho;   //!
   //TBranch        *b_BigRIPSRIPS_length;   //!
// //  TBranch        *b_BigRIPSRIPS_matrix;   //!
   //TBranch        *b_BigRIPSRIPS_delta;   //!
   //TBranch        *b_BigRIPSRIPS_angle;   //!
   //TBranch        *b_BigRIPSBeam_;   //!
   //TBranch        *b_BigRIPSBeam_fUniqueID;   //!
   //TBranch        *b_BigRIPSBeam_fBits;   //!
   //TBranch        *b_BigRIPSBeam_id;   //!
   //TBranch        *b_BigRIPSBeam_fpl;   //!
   //TBranch        *b_BigRIPSBeam_name;   //!
   //TBranch        *b_BigRIPSBeam_fDataState;   //!
   //TBranch        *b_BigRIPSBeam_brho;   //!
   //TBranch        *b_BigRIPSBeam_aoq;   //!
   //TBranch        *b_BigRIPSBeam_zet;   //!
   //TBranch        *b_BigRIPSBeam_beta;   //!
   //TBranch        *b_BigRIPSBeam_clight;   //!
   //TBranch        *b_BigRIPSBeam_mnucleon;   //!
   //TBranch        *b_BigRIPSBeam_nrips;   //!
   //TBranch        *b_BigRIPSBeam_ripsname;   //!
   //TBranch        *b_BigRIPSBeam_tofname;   //!
   //TBranch        *b_BigRIPSBeam_icname;   //!
   TBranch        *b_AOQ;   //!
   TBranch        *b_ZET;   //!

   BIGRIPS(char* filename,TTree *tree=0);
   virtual ~BIGRIPS();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
//   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   virtual void     GetTsEntry(map <Long64_t,Long64_t> &mts);
};

BIGRIPS::BIGRIPS(char* filename,TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
      if (!f || !f->IsOpen()) {
         f = new TFile(filename);
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

BIGRIPS::~BIGRIPS()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t BIGRIPS::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t BIGRIPS::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void BIGRIPS::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventInfo", &EventInfo_, &b_EventInfo_);
   fChain->SetBranchAddress("EventInfo.fUniqueID", EventInfo_fUniqueID, &b_EventInfo_fUniqueID);
   fChain->SetBranchAddress("EventInfo.fBits", EventInfo_fBits, &b_EventInfo_fBits);
   fChain->SetBranchAddress("EventInfo.fName", EventInfo_fName, &b_EventInfo_fName);
   fChain->SetBranchAddress("EventInfo.fTitle", EventInfo_fTitle, &b_EventInfo_fTitle);
   fChain->SetBranchAddress("EventInfo.timestamp", EventInfo_timestamp, &b_EventInfo_timestamp);
   fChain->SetBranchAddress("EventInfo.runnumber", EventInfo_runnumber, &b_EventInfo_runnumber);
   fChain->SetBranchAddress("EventInfo.eventnumber", EventInfo_eventnumber, &b_EventInfo_eventnumber);
   fChain->SetBranchAddress("EventInfo.subsysname", EventInfo_subsysname, &b_EventInfo_subsysname);
   fChain->SetBranchAddress("EventInfo.comp_val", EventInfo_comp_val, &b_EventInfo_comp_val);
   fChain->SetBranchAddress("EventInfo.fBit", EventInfo_fBit, &b_EventInfo_fBit);
   //fChain->SetBranchAddress("BigRIPSPPAC", &BigRIPSPPAC_, &b_BigRIPSPPAC_);
   //fChain->SetBranchAddress("BigRIPSPPAC.fUniqueID", BigRIPSPPAC_fUniqueID, &b_BigRIPSPPAC_fUniqueID);
   //fChain->SetBranchAddress("BigRIPSPPAC.fBits", BigRIPSPPAC_fBits, &b_BigRIPSPPAC_fBits);
   //fChain->SetBranchAddress("BigRIPSPPAC.id", BigRIPSPPAC_id, &b_BigRIPSPPAC_id);
   //fChain->SetBranchAddress("BigRIPSPPAC.fpl", BigRIPSPPAC_fpl, &b_BigRIPSPPAC_fpl);
   //fChain->SetBranchAddress("BigRIPSPPAC.name", BigRIPSPPAC_name, &b_BigRIPSPPAC_name);
   //fChain->SetBranchAddress("BigRIPSPPAC.fDataState", BigRIPSPPAC_fDataState, &b_BigRIPSPPAC_fDataState);
   //fChain->SetBranchAddress("BigRIPSPPAC.xzpos", BigRIPSPPAC_xzpos, &b_BigRIPSPPAC_xzpos);
   //fChain->SetBranchAddress("BigRIPSPPAC.yzpos", BigRIPSPPAC_yzpos, &b_BigRIPSPPAC_yzpos);
   //fChain->SetBranchAddress("BigRIPSPPAC.fTX1Raw", BigRIPSPPAC_fTX1Raw, &b_BigRIPSPPAC_fTX1Raw);
   //fChain->SetBranchAddress("BigRIPSPPAC.fTX2Raw", BigRIPSPPAC_fTX2Raw, &b_BigRIPSPPAC_fTX2Raw);
   //fChain->SetBranchAddress("BigRIPSPPAC.fTY1Raw", BigRIPSPPAC_fTY1Raw, &b_BigRIPSPPAC_fTY1Raw);
   //fChain->SetBranchAddress("BigRIPSPPAC.fTY2Raw", BigRIPSPPAC_fTY2Raw, &b_BigRIPSPPAC_fTY2Raw);
   //fChain->SetBranchAddress("BigRIPSPPAC.fTARaw", BigRIPSPPAC_fTARaw, &b_BigRIPSPPAC_fTARaw);
   //fChain->SetBranchAddress("BigRIPSPPAC.fQX1Raw", BigRIPSPPAC_fQX1Raw, &b_BigRIPSPPAC_fQX1Raw);
   //fChain->SetBranchAddress("BigRIPSPPAC.fQX2Raw", BigRIPSPPAC_fQX2Raw, &b_BigRIPSPPAC_fQX2Raw);
   //fChain->SetBranchAddress("BigRIPSPPAC.fQY1Raw", BigRIPSPPAC_fQY1Raw, &b_BigRIPSPPAC_fQY1Raw);
   //fChain->SetBranchAddress("BigRIPSPPAC.fQY2Raw", BigRIPSPPAC_fQY2Raw, &b_BigRIPSPPAC_fQY2Raw);
   //fChain->SetBranchAddress("BigRIPSPPAC.fQARaw", BigRIPSPPAC_fQARaw, &b_BigRIPSPPAC_fQARaw);
   //fChain->SetBranchAddress("BigRIPSPPAC.fTSumX", BigRIPSPPAC_fTSumX, &b_BigRIPSPPAC_fTSumX);
   //fChain->SetBranchAddress("BigRIPSPPAC.fTSumY", BigRIPSPPAC_fTSumY, &b_BigRIPSPPAC_fTSumY);
   //fChain->SetBranchAddress("BigRIPSPPAC.fTDiffX", BigRIPSPPAC_fTDiffX, &b_BigRIPSPPAC_fTDiffX);
   //fChain->SetBranchAddress("BigRIPSPPAC.fTDiffY", BigRIPSPPAC_fTDiffY, &b_BigRIPSPPAC_fTDiffY);
   //fChain->SetBranchAddress("BigRIPSPPAC.fX", BigRIPSPPAC_fX, &b_BigRIPSPPAC_fX);
   //fChain->SetBranchAddress("BigRIPSPPAC.fY", BigRIPSPPAC_fY, &b_BigRIPSPPAC_fY);
   //fChain->SetBranchAddress("BigRIPSPPAC.fFiredX", BigRIPSPPAC_fFiredX, &b_BigRIPSPPAC_fFiredX);
   //fChain->SetBranchAddress("BigRIPSPPAC.fFiredY", BigRIPSPPAC_fFiredY, &b_BigRIPSPPAC_fFiredY);
   //fChain->SetBranchAddress("BigRIPSPlastic", &BigRIPSPlastic_, &b_BigRIPSPlastic_);
   //fChain->SetBranchAddress("BigRIPSPlastic.fUniqueID", BigRIPSPlastic_fUniqueID, &b_BigRIPSPlastic_fUniqueID);
   //fChain->SetBranchAddress("BigRIPSPlastic.fBits", BigRIPSPlastic_fBits, &b_BigRIPSPlastic_fBits);
   //fChain->SetBranchAddress("BigRIPSPlastic.id", BigRIPSPlastic_id, &b_BigRIPSPlastic_id);
   //fChain->SetBranchAddress("BigRIPSPlastic.fpl", BigRIPSPlastic_fpl, &b_BigRIPSPlastic_fpl);
   //fChain->SetBranchAddress("BigRIPSPlastic.name", BigRIPSPlastic_name, &b_BigRIPSPlastic_name);
   //fChain->SetBranchAddress("BigRIPSPlastic.fDataState", BigRIPSPlastic_fDataState, &b_BigRIPSPlastic_fDataState);
   //fChain->SetBranchAddress("BigRIPSPlastic.zposition", BigRIPSPlastic_zposition, &b_BigRIPSPlastic_zposition);
   //fChain->SetBranchAddress("BigRIPSPlastic.zoffset", BigRIPSPlastic_zoffset, &b_BigRIPSPlastic_zoffset);
   //fChain->SetBranchAddress("BigRIPSPlastic.fTLRaw", BigRIPSPlastic_fTLRaw, &b_BigRIPSPlastic_fTLRaw);
   //fChain->SetBranchAddress("BigRIPSPlastic.fTRRaw", BigRIPSPlastic_fTRRaw, &b_BigRIPSPlastic_fTRRaw);
   //fChain->SetBranchAddress("BigRIPSPlastic.fQLRaw", BigRIPSPlastic_fQLRaw, &b_BigRIPSPlastic_fQLRaw);
   //fChain->SetBranchAddress("BigRIPSPlastic.fQRRaw", BigRIPSPlastic_fQRRaw, &b_BigRIPSPlastic_fQRRaw);
   //fChain->SetBranchAddress("BigRIPSPlastic.fTime", BigRIPSPlastic_fTime, &b_BigRIPSPlastic_fTime);
   //fChain->SetBranchAddress("BigRIPSPlastic.fTimeL", BigRIPSPlastic_fTimeL, &b_BigRIPSPlastic_fTimeL);
   //fChain->SetBranchAddress("BigRIPSPlastic.fTimeR", BigRIPSPlastic_fTimeR, &b_BigRIPSPlastic_fTimeR);
   //fChain->SetBranchAddress("BigRIPSPlastic.fTimeLSlew", BigRIPSPlastic_fTimeLSlew, &b_BigRIPSPlastic_fTimeLSlew);
   //fChain->SetBranchAddress("BigRIPSPlastic.fTimeRSlew", BigRIPSPlastic_fTimeRSlew, &b_BigRIPSPlastic_fTimeRSlew);
   //fChain->SetBranchAddress("BigRIPSPlastic.fTimeSlew", BigRIPSPlastic_fTimeSlew, &b_BigRIPSPlastic_fTimeSlew);
   //fChain->SetBranchAddress("BigRIPSIC", &BigRIPSIC_, &b_BigRIPSIC_);
   //fChain->SetBranchAddress("BigRIPSIC.fUniqueID", BigRIPSIC_fUniqueID, &b_BigRIPSIC_fUniqueID);
   //fChain->SetBranchAddress("BigRIPSIC.fBits", BigRIPSIC_fBits, &b_BigRIPSIC_fBits);
   //fChain->SetBranchAddress("BigRIPSIC.id", BigRIPSIC_id, &b_BigRIPSIC_id);
   //fChain->SetBranchAddress("BigRIPSIC.fpl", BigRIPSIC_fpl, &b_BigRIPSIC_fpl);
   //fChain->SetBranchAddress("BigRIPSIC.name", BigRIPSIC_name, &b_BigRIPSIC_name);
   //fChain->SetBranchAddress("BigRIPSIC.fDataState", BigRIPSIC_fDataState, &b_BigRIPSIC_fDataState);
   //fChain->SetBranchAddress("BigRIPSIC.zcoef[2]", BigRIPSIC_zcoef, &b_BigRIPSIC_zcoef);
   //fChain->SetBranchAddress("BigRIPSIC.ionpair", BigRIPSIC_ionpair, &b_BigRIPSIC_ionpair);
   //fChain->SetBranchAddress("BigRIPSIC.nhitchannel", BigRIPSIC_nhitchannel, &b_BigRIPSIC_nhitchannel);
   //fChain->SetBranchAddress("BigRIPSIC.fADC[10]", BigRIPSIC_fADC, &b_BigRIPSIC_fADC);
   //fChain->SetBranchAddress("BigRIPSIC.fEnergy[10]", BigRIPSIC_fEnergy, &b_BigRIPSIC_fEnergy);
   //fChain->SetBranchAddress("BigRIPSIC.fRawADCSqSum", BigRIPSIC_fRawADCSqSum, &b_BigRIPSIC_fRawADCSqSum);
   //fChain->SetBranchAddress("BigRIPSIC.fRawADCAvSum", BigRIPSIC_fRawADCAvSum, &b_BigRIPSIC_fRawADCAvSum);
   //fChain->SetBranchAddress("BigRIPSIC.fCalMeVSqSum", BigRIPSIC_fCalMeVSqSum, &b_BigRIPSIC_fCalMeVSqSum);
   //fChain->SetBranchAddress("BigRIPSIC.fCalMeVAvSum", BigRIPSIC_fCalMeVAvSum, &b_BigRIPSIC_fCalMeVAvSum);
   //fChain->SetBranchAddress("BigRIPSFocalPlane", &BigRIPSFocalPlane_, &b_BigRIPSFocalPlane_);
   //fChain->SetBranchAddress("BigRIPSFocalPlane.fUniqueID", BigRIPSFocalPlane_fUniqueID, &b_BigRIPSFocalPlane_fUniqueID);
   //fChain->SetBranchAddress("BigRIPSFocalPlane.fBits", BigRIPSFocalPlane_fBits, &b_BigRIPSFocalPlane_fBits);
   //fChain->SetBranchAddress("BigRIPSFocalPlane.id", BigRIPSFocalPlane_id, &b_BigRIPSFocalPlane_id);
   //fChain->SetBranchAddress("BigRIPSFocalPlane.fpl", BigRIPSFocalPlane_fpl, &b_BigRIPSFocalPlane_fpl);
   //fChain->SetBranchAddress("BigRIPSFocalPlane.name", BigRIPSFocalPlane_name, &b_BigRIPSFocalPlane_name);
   //fChain->SetBranchAddress("BigRIPSFocalPlane.fDataState", BigRIPSFocalPlane_fDataState, &b_BigRIPSFocalPlane_fDataState);
// //  fChain->SetBranchAddress("BigRIPSFocalPlane.opt_vector", BigRIPSFocalPlane_opt_vector, &b_BigRIPSFocalPlane_opt_vector);
   //fChain->SetBranchAddress("BigRIPSFocalPlane.nfired_ppacx", BigRIPSFocalPlane_nfired_ppacx, &b_BigRIPSFocalPlane_nfired_ppacx);
   //fChain->SetBranchAddress("BigRIPSFocalPlane.nfired_ppacy", BigRIPSFocalPlane_nfired_ppacy, &b_BigRIPSFocalPlane_nfired_ppacy);
   //fChain->SetBranchAddress("BigRIPSFocalPlane.zpos", BigRIPSFocalPlane_zpos, &b_BigRIPSFocalPlane_zpos);
   //fChain->SetBranchAddress("BigRIPSTOF", &BigRIPSTOF_, &b_BigRIPSTOF_);
   //fChain->SetBranchAddress("BigRIPSTOF.fUniqueID", BigRIPSTOF_fUniqueID, &b_BigRIPSTOF_fUniqueID);
   //fChain->SetBranchAddress("BigRIPSTOF.fBits", BigRIPSTOF_fBits, &b_BigRIPSTOF_fBits);
   //fChain->SetBranchAddress("BigRIPSTOF.id", BigRIPSTOF_id, &b_BigRIPSTOF_id);
   //fChain->SetBranchAddress("BigRIPSTOF.fpl", BigRIPSTOF_fpl, &b_BigRIPSTOF_fpl);
   //fChain->SetBranchAddress("BigRIPSTOF.name", BigRIPSTOF_name, &b_BigRIPSTOF_name);
   //fChain->SetBranchAddress("BigRIPSTOF.fDataState", BigRIPSTOF_fDataState, &b_BigRIPSTOF_fDataState);
   //fChain->SetBranchAddress("BigRIPSTOF.tof", BigRIPSTOF_tof, &b_BigRIPSTOF_tof);
   //fChain->SetBranchAddress("BigRIPSTOF.clight", BigRIPSTOF_clight, &b_BigRIPSTOF_clight);
   //fChain->SetBranchAddress("BigRIPSTOF.length", BigRIPSTOF_length, &b_BigRIPSTOF_length);
   //fChain->SetBranchAddress("BigRIPSTOF.upstream_plname", BigRIPSTOF_upstream_plname, &b_BigRIPSTOF_upstream_plname);
   //fChain->SetBranchAddress("BigRIPSTOF.downstream_plname", BigRIPSTOF_downstream_plname, &b_BigRIPSTOF_downstream_plname);
   //fChain->SetBranchAddress("BigRIPSTOF.upstream_plfpl", BigRIPSTOF_upstream_plfpl, &b_BigRIPSTOF_upstream_plfpl);
   //fChain->SetBranchAddress("BigRIPSTOF.downstream_plfpl", BigRIPSTOF_downstream_plfpl, &b_BigRIPSTOF_downstream_plfpl);
   //fChain->SetBranchAddress("BigRIPSTOF.time_offset", BigRIPSTOF_time_offset, &b_BigRIPSTOF_time_offset);
   //fChain->SetBranchAddress("BigRIPSRIPS", &BigRIPSRIPS_, &b_BigRIPSRIPS_);
   //fChain->SetBranchAddress("BigRIPSRIPS.fUniqueID", BigRIPSRIPS_fUniqueID, &b_BigRIPSRIPS_fUniqueID);
   //fChain->SetBranchAddress("BigRIPSRIPS.fBits", BigRIPSRIPS_fBits, &b_BigRIPSRIPS_fBits);
   //fChain->SetBranchAddress("BigRIPSRIPS.id", BigRIPSRIPS_id, &b_BigRIPSRIPS_id);
   //fChain->SetBranchAddress("BigRIPSRIPS.fpl", BigRIPSRIPS_fpl, &b_BigRIPSRIPS_fpl);
   //fChain->SetBranchAddress("BigRIPSRIPS.name", BigRIPSRIPS_name, &b_BigRIPSRIPS_name);
   //fChain->SetBranchAddress("BigRIPSRIPS.fDataState", BigRIPSRIPS_fDataState, &b_BigRIPSRIPS_fDataState);
   //fChain->SetBranchAddress("BigRIPSRIPS.upstream_fpl", BigRIPSRIPS_upstream_fpl, &b_BigRIPSRIPS_upstream_fpl);
   //fChain->SetBranchAddress("BigRIPSRIPS.downstream_fpl", BigRIPSRIPS_downstream_fpl, &b_BigRIPSRIPS_downstream_fpl);
   //fChain->SetBranchAddress("BigRIPSRIPS.center_brho", BigRIPSRIPS_center_brho, &b_BigRIPSRIPS_center_brho);
   //fChain->SetBranchAddress("BigRIPSRIPS.brho", BigRIPSRIPS_brho, &b_BigRIPSRIPS_brho);
   //fChain->SetBranchAddress("BigRIPSRIPS.length", BigRIPSRIPS_length, &b_BigRIPSRIPS_length);
// //  fChain->SetBranchAddress("BigRIPSRIPS.matrix", BigRIPSRIPS_matrix, &b_BigRIPSRIPS_matrix);
   //fChain->SetBranchAddress("BigRIPSRIPS.delta", BigRIPSRIPS_delta, &b_BigRIPSRIPS_delta);
   //fChain->SetBranchAddress("BigRIPSRIPS.angle", BigRIPSRIPS_angle, &b_BigRIPSRIPS_angle);
   //fChain->SetBranchAddress("BigRIPSBeam", &BigRIPSBeam_, &b_BigRIPSBeam_);
   //fChain->SetBranchAddress("BigRIPSBeam.fUniqueID", BigRIPSBeam_fUniqueID, &b_BigRIPSBeam_fUniqueID);
   //fChain->SetBranchAddress("BigRIPSBeam.fBits", BigRIPSBeam_fBits, &b_BigRIPSBeam_fBits);
   //fChain->SetBranchAddress("BigRIPSBeam.id", BigRIPSBeam_id, &b_BigRIPSBeam_id);
   //fChain->SetBranchAddress("BigRIPSBeam.fpl", BigRIPSBeam_fpl, &b_BigRIPSBeam_fpl);
   //fChain->SetBranchAddress("BigRIPSBeam.name", BigRIPSBeam_name, &b_BigRIPSBeam_name);
   //fChain->SetBranchAddress("BigRIPSBeam.fDataState", BigRIPSBeam_fDataState, &b_BigRIPSBeam_fDataState);
   //fChain->SetBranchAddress("BigRIPSBeam.brho", BigRIPSBeam_brho, &b_BigRIPSBeam_brho);
   //fChain->SetBranchAddress("BigRIPSBeam.aoq", BigRIPSBeam_aoq, &b_BigRIPSBeam_aoq);
   //fChain->SetBranchAddress("BigRIPSBeam.zet", BigRIPSBeam_zet, &b_BigRIPSBeam_zet);
   //fChain->SetBranchAddress("BigRIPSBeam.beta", BigRIPSBeam_beta, &b_BigRIPSBeam_beta);
   //fChain->SetBranchAddress("BigRIPSBeam.clight", BigRIPSBeam_clight, &b_BigRIPSBeam_clight);
   //fChain->SetBranchAddress("BigRIPSBeam.mnucleon", BigRIPSBeam_mnucleon, &b_BigRIPSBeam_mnucleon);
   //fChain->SetBranchAddress("BigRIPSBeam.nrips", BigRIPSBeam_nrips, &b_BigRIPSBeam_nrips);
   //fChain->SetBranchAddress("BigRIPSBeam.ripsname[2]", BigRIPSBeam_ripsname, &b_BigRIPSBeam_ripsname);
   //fChain->SetBranchAddress("BigRIPSBeam.tofname", BigRIPSBeam_tofname, &b_BigRIPSBeam_tofname);
   //fChain->SetBranchAddress("BigRIPSBeam.icname", BigRIPSBeam_icname, &b_BigRIPSBeam_icname);
   fChain->SetBranchAddress("AOQ", &AOQ, &b_AOQ);
   fChain->SetBranchAddress("ZET", &ZET, &b_ZET);
   Notify();
}

Bool_t BIGRIPS::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void BIGRIPS::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t BIGRIPS::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
void BIGRIPS::GetTsEntry(map<Long64_t,Long64_t> &mts)
{
   Long64_t nenties = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb =0;
   for(Long64_t jentry = 0;jentry < nenties ;jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if(ientry<0) break;
      nb = fChain->GetEntry(jentry); nbytes += nb;
      Long64_t ts = (Long64_t)EventInfo_timestamp[0];
      //cout<<"brips ts = "<<ts<<endl;
      mts.insert(pair<Long64_t,Long64_t> (ts,jentry));
   }
}
