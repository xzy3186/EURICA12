#include "TObject.h"
#define NumDSSD 8

class CDecay : public TObject {
   public:
      CDecay(){Clear();}
      virtual void Clear();

   public:
      Long64_t t;
      Int_t z;
      Float_t x;
      Float_t y;
      Int_t ex;
      Int_t ey;
      Int_t mulx;
      Int_t muly;
      Int_t deltaz;
      Double_t deltaxy;
      Int_t E;
      Int_t dssd_fire[NumDSSD];
      Int_t flag_side; //-1: upstream fired; 0: none side fired, 1: downstream fired; 2: both sides fired.
      Int_t dssd_ex[NumDSSD];
      Int_t dssd_ey[NumDSSD];
      Int_t dssd_zmult[NumDSSD];//multiplicity in each DSSSD
      Float_t dssd_x[NumDSSD][5];//energy centroid of X in each DSSSD
      Float_t dssd_y[NumDSSD][5];//energy centroid of y in each DSSSD
      Int_t NaI_E[3];
      Int_t NaI_T[3];
      Int_t Qbeta_E;
      Int_t Qbeta_T;
      Int_t Qveto_E;
      Int_t Qveto_T;

      Int_t gc_hit;
      Int_t gc_ch[84];
      Int_t gc_DGFe[84];
      Int_t gc_TDCs[84];
      Int_t gc_DGFt[84];
      Int_t gc_TDCl[84];
      Double_t gc_E[84];
      Double_t gc_T[84];

      Int_t ab_hit;
      Int_t ab_ch[84];
      Int_t ab_DGFe[84];
      Int_t ab_TDCs[84];
      Int_t ab_DGFt[84];
      Int_t ab_TDCl[84];
      Double_t ab_E[84];
      Double_t ab_T[84];

      ClassDef(CDecay, 1);
};

class CImp : public TObject {
   public:
      CImp(){Clear();}
      virtual void Clear();

   public:
      Int_t run;
      Long64_t ts;
      Int_t z;
      Int_t x;
      Int_t y;
      Int_t tx;
      Int_t ty;
      Int_t IfInterest;

      Double_t beta35;
      Double_t beta57;
      Double_t beta711;
      Double_t aoq37;
      Double_t zed;
      Int_t Zed;
      Int_t Mass;
      Int_t flagall;
      Int_t flagTSumX;
      Int_t flagTOFt;
      Int_t flagTOFq;
      Int_t flagReaction;
      Int_t flagdERelation;
      Int_t flagAngle;

      Int_t gc_hit;
      Int_t gc_ch[84];
      Int_t gc_DGFe[84];
      Int_t gc_TDCs[84];
      Int_t gc_DGFt[84];
      Int_t gc_TDCl[84];
      Double_t gc_E[84];
      Double_t gc_T[84];

      Int_t ab_hit;
      Int_t ab_ch[84];
      Int_t ab_DGFe[84];
      Int_t ab_TDCs[84];
      Int_t ab_DGFt[84];
      Int_t ab_TDCl[84];
      Double_t ab_E[84];
      Double_t ab_T[84];

      ClassDef(CImp, 1);
};
