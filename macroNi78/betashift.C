#include "macro/Nucleus.cc"

void betashift(int zed, int mass) {
  double Brho57 = 7.1545;
  Nucleus nucl(zed,mass);
  nucl.SetBeamEnergy(Brho57,"Tm");
  double beta1 = nucl.beta();
  cout << beta1 - nucl.EnergyAfterMaterial("F7F11Simple",1,"beta")<<endl;
}
