#ifndef RIBeam_h
#define RIBeam_h

// version 1.0   2013/2/22 Toshiyuki Sumikama: for EURICA data
#include "TObject.h" 

class RIBeam : public TObject {
 public:
  RIBeam() {}
  virtual ~RIBeam() {}
  void Setbeta35(double val){beta35 = val;}
  void Setbeta57(double val){beta57 = val;}
  void Setbeta711(double val){beta711 = val;}
  void Setaoq37(double val){aoq37 = val;}
  void Setzed(double val){zed = val;}
  void SetZed(int val){Zed = val;}
  void SetMass(int val){Mass = val;}
  void Setflagall(int val){flagall = val;}
  void SetflagTSumX(int val){flagTSumX = val;}
  //  void SetflagF11PlaY(int val){flagF11PlaY = val;}
  void SetflagTOF(int val0, int val1){flagTOFt = val0;flagTOFq = val1;}
  void SetflagReaction(int val){flagReaction = val;}
  void SetflagdERelation(int val){flagdERelation = val;}
  void SetflagAngle(int val){flagAngle = val;}

  double Getbeta35() {return beta35;}
  double Getbeta57() {return beta57;}
  double Getbeta711() {return beta711;}
  double Getaoq37() {return aoq37;}
  double Getzed() {return zed;}
  int GetZed() {return Zed;}
  int GetMass() {return Mass;}
  int Getflagall() {return flagall;}
  int GetflagTSumX() {return flagTSumX;}
  //  int GetflagF11PlaY() {return flagF11PlaY;}
  int GetflagTOFt() {return flagTOFt;}
  int GetflagTOFq() {return flagTOFq;}
  int GetflagReaction(){return flagReaction;}
 private: 
  double beta35;
  double beta57;
  double beta711;
  double aoq37;
  double zed;
  int Zed;
  int Mass;
  int flagall;
//1: normal, 
//2: At least one of flag has value more than 0. 
//     This can be used for b-g. 
//0: At least one of flag has value less than 0.
//If both of 2 and 0 flag exist, this becomes 0. 

  int flagTSumX; 
//1: normal, 0: TSumX outside of gate for 3,5 and 7, 
//2: Recover of F3 position for EURICA data, but a/q resolution is bad. 

//  int flagF11PlaY;
// Y on F11 plastic for Y>39. There is a aluminum plate. 
//1: Y<39, 0: Y>=39 & zed<=32.5 and Y>=30 & zed>32.5, 
//2: TSumY outside of gate. Many of these can be used.

  int flagTOFt;
  int flagTOFq;
//[0] plastic timing gate, [1] plastic QDC gate
//1: normal, 0: outside of gate

  int flagReaction;
//1: normal, 0: reaction event

  Int_t flagdERelation;
//1: normal, 0: bad dE relation between F3-F7 plastic and zed

  Int_t flagAngle;
//1: normal, 0: bad angle relation among F3-F5-F7 angles in x direction;

  ClassDef(RIBeam,1)

};

ClassImp(RIBeam)
#endif // RIBeam_h
