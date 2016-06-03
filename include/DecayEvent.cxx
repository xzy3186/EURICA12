#include "DecayEvent.h"

ClassImp(CDecay)
ClassImp(CImp)

void CDecay::Clear() {
   t = 0;
   z = -1;
   x = -1;
   y = -1;
   ex= -1;
   ey= -1;
   mulx= -1;
   muly= -1;
   deltaz = -1;
   deltaxy = -1;
   flag_side = -10;
   E=-1;
   for(int i=0; i<NumDSSD; i++){
      dssd_fire[i] = -1;
      dssd_ex[i] = -1;
      dssd_ey[i] = -1;
      dssd_zmult[i] = -1;
      for(int j=0; j<5; j++){
         dssd_x[i][j] = -1;
         dssd_y[i][j] = -1;
      }
   }
   for(int i=0; i<3; i++){
      NaI_E[i] = -1;
      NaI_T[i] = -100000;
   }
   gc_hit = 0;
   ab_hit = 0;
   for(int i=0; i<84; i++){
      gc_ch[i]=-1;
      gc_DGFe[i]=-1;
      gc_DGFt[i]=-100000;
      gc_TDCs[i]=-100000;
      gc_TDCl[i]=-100000;
      gc_E[i]=-100000;
      gc_T[i]=-100000;
      ab_ch[i]=-1;
      ab_DGFe[i]=-1;
      ab_DGFt[i]=-100000;
      ab_TDCs[i]=-100000;
      ab_TDCl[i]=-100000;
      ab_E[i]=-100000;
      ab_T[i]=-100000;
   }
   Qbeta_E = -1;
   Qbeta_T = -100000;
   Qveto_E = -1;
   Qveto_T = -100000;
}

void CImp::Clear(){
   run=0;
   ts=0;
   z=-1;
   x=-1;
   y=-1;
   tx=-100000;
   ty=-100000;
   IfInterest=0;

   beta35 = -1;
   beta57 = -1;
   beta711 = -1;
   aoq37 = -1;
   zed = -1;
   Mass = -1;
   Zed = -1;
   flagall = -1;
   flagTSumX = -1;
   flagTOFt = -1;
   flagTOFq = -1;
   flagReaction = -1;
   flagdERelation = -1;
   flagAngle = -1;
   gc_hit = 0;
   ab_hit = 0;
   for(int i=0; i<84; i++){
      gc_ch[i]=-1;
      gc_DGFe[i]=-1;
      gc_DGFt[i]=-100000;
      gc_TDCs[i]=-100000;
      gc_TDCl[i]=-100000;
      gc_E[i]=-100000;
      gc_T[i]=-100000;
      ab_ch[i]=-1;
      ab_DGFe[i]=-1;
      ab_DGFt[i]=-100000;
      ab_TDCs[i]=-100000;
      ab_TDCl[i]=-100000;
      ab_E[i]=-100000;
      ab_T[i]=-100000;
   }
}
