#ifndef Nucleus_h
#define Nucleus_h

#include <iostream> 
#include <fstream>
#include <sstream> 
#include <math.h>
#include <ctype.h>

using namespace std;

class Nucleus {
  double BeamEnergy; // MeV/A
  int ProtonNum;
  int MassNum;
  int Charge;
  double MassExcess; // MeV
  double u; // unified atomic mass unit in MeV
  string dir;
  void Setdir(){dir = "/home/ribf10/"; }

public :
  Nucleus();
  Nucleus(int pn, int mn);
  Nucleus(int pn, int mn, double en);
  Nucleus(int pn, int mn, double en, double me);
  ~Nucleus();
  void SetBeamEnergy(double en, string unit); 
  // unit is MeV/A, MeV/u, MeV(kinetic), MeV/c(momentum)
  //  Tm(magnetic ridigity)
  double KineticEnergy();
  double TotalEnergy();
  double Momentum(); // in MeV/c
  double BeamEnergyMeVperA(){return BeamEnergy;}
  double BeamEnergyMeVperU();
  double Mass(); // in MeV
  double MassInU(); // in u
  double beta(); // v/c
  double gamma(); // 1/sqrt(1-beta^2)
  double velocity();  // cm/ns
  double Brho(); // 
  void SetCharge(int q); //Q
  void SetMassExcess(double me); // in MeV
  void SetNucleus(int zed, int massnum); // Z, A
  void SetNucleus(int zed, int massnum, double me); // Z, A, MassExcess
  double ReadMassExcess(); // from ame2003
  double EnergyLoss(char* filename, int icomp); // in MeV
  // Material list is loaded from file.
  // The file should be in the directory ~/Atima/atima.data
  double EnergyLoss(char* materialname, double thickness); // energyloss in material name. thickness is in mg/cm2
  double EnergyAfterMaterial(char* filename, int icomp, string unit); // energy after icomp-th material in required unit: MeV/A, MeV, MeV/u, MeV/c, beta, Tm
  double EnergyAfterMaterial(char* materialname, double thickness, string unit);// thickness is in mg/cm2, energy after material in required unit: MeV/A, MeV, MeV/u, MeV/c, beta, Tm
  double ThicknessForExitEnergy(char* materialname, double exitEnergy, string unit);// Thickness is mg/cm2, exitEnergy is given in unit: MeV/A, MeV, MeV/u, MeV/c, beta, Tm
  string GetIsotopeName(int zed);
};

#endif

