#ifndef RIBeamOthers_h
#define RIBeaOthersm_h

// version 1.0 2013/2/22 Toshiyuki Sumikama: for EURICA data
#include "TObject.h" 

class RIBeamOthers : public TObject {
 public:
  RIBeamOthers() {}
  virtual ~RIBeamOthers() {}
  void SetTOF37(double val){tof37=val;}
  void SetTOF711(double val){tof711 =val;}
  void SetF3PosAng(double val0, double val1, double val2, double val3){F3X=val0;F3A=val1;F3Y=val2;F3B=val3;}
  void SetF5PosAng(double val0, double val1, double val2, double val3){F5X=val0;F5A=val1;F5Y=val2;F5B=val3;}
  void SetF7PosAng(double val0, double val1, double val2, double val3){F7X=val0;F7A=val1;F7Y=val2;F7B=val3;}
  void Setdelta35(double val){delta35 = val;}
  void Setdelta57(double val){delta57 = val;}
  void Setbrho35(double val){brho35 = val;}
  void Setbrho57(double val){brho57 = val;}
  void SetdeltaE(double val){deltaE = val;}

  double GetTOF37(){return tof37;}
  double GetTOF711(){return tof711;}
  double GetF3X(){return F3X;}
  double GetF3A(){return F3A;}
  double GetF3Y(){return F3Y;}
  double GetF3B(){return F3B;}
  double GetF5X(){return F5X;}
  double GetF5A(){return F5A;}
  double GetF5Y(){return F5Y;}
  double GetF5B(){return F5B;}
  double GetF7X(){return F7X;}
  double GetF7A(){return F7A;}
  double GetF7Y(){return F7Y;}
  double GetF7B(){return F7B;}
  double Getdelta35(){return delta35;}
  double Getdelta57(){return delta57;}
  double Getbrho35(){return brho35;}
  double Getbrho57(){return brho57;}
  double GetdeltaE(){return deltaE;}

 private: 
  double tof37; // with slew correction
  double tof711;
  double F3X;
  double F3A;
  double F3Y;
  double F3B;
  double F5X;
  double F5A;
  double F5Y;
  double F5B;
  double F7X;
  double F7A;
  double F7Y;
  double F7B;
  double delta35;
  double delta57;
  double brho35;
  double brho57;
  double deltaE;
  ClassDef(RIBeamOthers,1)

};

ClassImp(RIBeamOthers)
#endif // RIBeamOthers_h
