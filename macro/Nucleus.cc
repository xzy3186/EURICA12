#include "Nucleus.h"

Nucleus::Nucleus() 
  : BeamEnergy(0), ProtonNum(1), MassNum(1), u(931.49406) {
  Setdir();
  Charge = ProtonNum;
  MassExcess = ReadMassExcess();
}

Nucleus::Nucleus(int pn, int mn) 
  : BeamEnergy(0), u(931.49406) {
  Setdir();
  ProtonNum = pn;
  MassNum = mn;
  Charge = ProtonNum;
  MassExcess = ReadMassExcess();
}

Nucleus::Nucleus(int pn, int mn, double en) 
  : u(931.49406) {
  Setdir();
  BeamEnergy = en;
  ProtonNum = pn;
  MassNum = mn;
  Charge = ProtonNum;
  MassExcess = ReadMassExcess();
}

Nucleus::Nucleus(int pn, int mn, double en, double me) 
  : u(931.49406) {
  Setdir();
  BeamEnergy = en;
  ProtonNum = pn;
  MassNum = mn;
  MassExcess = me;
  Charge = ProtonNum;
}
  
Nucleus::~Nucleus() {

}

double Nucleus::KineticEnergy() {
  return BeamEnergy*MassNum;
}

double Nucleus::Mass() {
  return MassExcess + MassNum * u;
}

double Nucleus::MassInU() {
  return MassExcess/u + MassNum;
}

double Nucleus::TotalEnergy() {
  return KineticEnergy()+Mass();
}

double Nucleus::Momentum() {
  return sqrt(TotalEnergy()*TotalEnergy()-Mass()*Mass());
}

double Nucleus::BeamEnergyMeVperU() {
  return BeamEnergy*MassNum/MassInU();
}


double Nucleus::beta() {
  return Momentum()/TotalEnergy();
}

double Nucleus::gamma() {
  return 1/sqrt(1-beta()*beta());
}

double Nucleus::velocity() {
  double speedoflight = 29.9792458; // cm/ns
  return beta()*speedoflight;
}

double Nucleus::Brho() {
  // B*rho[Tm] = p/Q in Si unit,
  // p in MeV/c and Q in e
  //   -> Brho= p[MeV/c]/Q[e]= p/Q [MV/c] = p/Q/c*1e6 [Vs/m]
  // [Vs/m] = [Tm]
  // c/1e6 = 299.792458 
  return Momentum()/Charge/299.792458;
}

void Nucleus::SetCharge(int q) {
  Charge = q;
}

void Nucleus::SetBeamEnergy(double en, string unit) {
  if(unit=="MeV/A") {
    BeamEnergy = en;
  } else if (unit=="MeV") {
    BeamEnergy = en/MassNum;
  } else if (unit=="MeV/u") {
    BeamEnergy = en*MassInU()/MassNum;
  } else if (unit=="MeV/c") {
    double kinEnergy = sqrt(en*en + Mass()*Mass())-Mass();
    BeamEnergy = kinEnergy/MassNum;
  } else if (unit=="Tm") {
    double mom = en*Charge*299.792458;
    double kinEnergy = sqrt(mom*mom + Mass()*Mass())-Mass();
    BeamEnergy = kinEnergy/MassNum;
  } else if (unit=="beta") {
    double be=en;
    double ga=1/sqrt(1-be*be);
    double mom = be*ga*Mass();
    double kinEnergy = sqrt(mom*mom + Mass()*Mass())-Mass();
    BeamEnergy = kinEnergy/MassNum;
  } else {
    cout << "Given unit is not found." << endl;
  }
}

void Nucleus::SetMassExcess(double me) {
  MassExcess = me;
}

void Nucleus::SetNucleus(int zed, int massnum) {
  ProtonNum = zed;
  MassNum = massnum;
  Charge = ProtonNum;
  MassExcess = ReadMassExcess();
}

void Nucleus::SetNucleus(int zed, int massnum, double me) {
  ProtonNum = zed;
  MassNum = massnum;
  Charge = ProtonNum;
  MassExcess = me;
}

double Nucleus::ReadMassExcess() {
  string file= dir+"AME2003/mass.mas03";
  ifstream fin(file.c_str());
  if(!fin) {
    cout << "file is not found" << endl;
    return 0.;
  }
  string str,str1,str2;
  istringstream ss;

  while (!fin.eof()) {
    getline(fin,str);
    //    if (str.compare(0,4,"1N-Z")==0) {
    if ((str.substr(0,4)).compare("1N-Z")==0) {
      break;
    }
  }

  int mass=0; // mass number
  while (!fin.eof()) {
    getline(fin,str);
    //    if (str.compare(0,1,"0")==0) {
    if ((str.substr(0,1)).compare("0")==0) {
      mass++; // mass number
    }
    if (mass==MassNum) break;
  } // reach line of mass number
  
  int zed, isSameMass=0;
  do {
    ss.str(str);
    //    if (str.compare(0,1,"0")==0) { 
    if ((str.substr(0,1)).compare("0")==0) { // next mass number
      isSameMass++;
      if(isSameMass==1) {
	ss >> str1 >> str1 >> str1 >> str1;
      }
    } else {
      ss >> str1 >> str1 >> str1 ;
    }
    zed = atoi(str1.c_str()); // "ss >> readzed" doesn't work in ROOT CINT.
    if (zed<ProtonNum||zed==ProtonNum||isSameMass>1)  break; 
    //If neutron-rich nucleus is not given in the AME2003 table
    //most neutron-rich nucleus with same mass number is selected.
    //For proton-rich side, most proton-rich nucleus is selected. 
    getline(fin,str);
  } while(!fin.eof()); // reach line of mass and z

  long pos = ss.tellg();
  ss.seekg(pos+13);
  ss >> str1;
 
  int len = str1.length();
  //  if (str1.compare(len-1,1,"#")==0) str1.erase(len-1,len);
  if ((str.substr(len-1,1)).compare("#")==0) str1.erase(len-1,len);
  
  return atof(str1.c_str())/1000;
}

double Nucleus::EnergyLoss(char* filename, int icomp) {
  // material list is loaded from filename
  // return energy loss in icomp-th material
  string file=dir+"Atima/atima.data/temp.conf";
  ofstream fout(file.c_str());
  fout << "jconfiguration" << endl;
  fout << "standard" << endl;
  fout << filename << endl;
  fout << GetIsotopeName(ProtonNum) << "  " << ProtonNum 
       << "  " << MassNum << "  " << MassInU() << endl;
  fout << 1 << endl << 1 << endl << 17 << "  " << 1 << endl;
  fout << BeamEnergyMeVperU() << endl;
  fout << "0.0  0.0 "<< endl;
  fout << "0 0 0 0" << endl; 
  fout << "25 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24" << endl;
  fout.close();

  string file2=dir+"Atima/atima.data/temp.batch";
  ofstream fout2(file2.c_str());
  fout2 << "ReadConf temp.conf" << endl << "Format pvt" << endl 
	<< "CalcOrder successive" << endl 
	<< "Splines s" << endl << "CalcParams" << endl 
	<< "Value 0 outputtemp.txt" << endl << "EndInput" << endl;
  fout2.close();

  char str[255];
  strcpy(str,"(cd ~/Atima; ./JavaAtima2 atima.data/temp.batch >> /dev/null)");
  int ret=system(str);
  if (ret!=0) return ret;

  string filein=dir+"Atima/atima.output/outputtemp.txt";
  ifstream fin(filein.c_str());
  string s;
  stringstream ss;
  double ein, eout, eloss;
  if (!fin) {
    cout << "no file" << endl;
    return 0;
  } else {
    int i;
    while (!fin.eof()&&s!="Ein") {
    fin >> s; 
    }
    fin >> s >> s;
    for (i=0;i<icomp;i++) {
      fin >> s;
    }
    s.erase(s.size()-1);
    ss << s;
    ss >> ein;
    ss.clear();
    while (!fin.eof()&&s!="Eout") {
    fin >> s; 
    }
    fin >> s >> s;
    for (i=0;i<icomp;i++) {
      fin >> s;
    }
    s.erase(s.size()-1);
    ss << s;
    ss >> eout;
    ss.clear();
    eloss = (ein-eout)*MassInU();
  return eloss;
  }
}

double Nucleus::EnergyLoss(char* materialname, double thickness) {
  string file=dir+"Atima/atima.data/temp.mat";
  ofstream fout(file.c_str());
  fout << "jtargetlist" << endl;
  fout << "0" << endl;
  fout << "stack 1 " << materialname << endl;
  fout << thickness << " 1 " << materialname << endl;
  fout << "end stack" << endl;
  fout << "end jtargetlist" << endl;
  fout.close();
  char ch[]="temp.mat";
  return EnergyLoss(ch,1);
}


double Nucleus::EnergyAfterMaterial(char* filename, int icomp, string unit) {
  double EnergynAfterMaterial = BeamEnergy - EnergyLoss(filename,icomp)/MassNum;
  
  if(unit=="MeV/A") {
    return EnergynAfterMaterial;
  } else if (unit=="MeV") {
    return EnergynAfterMaterial*MassNum;
  } else if (unit=="MeV/u") {
    return EnergynAfterMaterial*MassNum/MassInU();
  } else if (unit=="MeV/c") {
    double totalEnergy =  EnergynAfterMaterial*MassNum + Mass();
    return sqrt(totalEnergy*totalEnergy -Mass()*Mass());
  } else if (unit=="Tm") {
    double totalEnergy =  EnergynAfterMaterial*MassNum + Mass();
    double momentum = sqrt(totalEnergy*totalEnergy -Mass()*Mass());
    return momentum/Charge/299.792458;
  } else if (unit=="beta") {
    double totalEnergy =  EnergynAfterMaterial*MassNum + Mass();
    double momentum = sqrt(totalEnergy*totalEnergy -Mass()*Mass());
    return momentum/totalEnergy;
  } else {
    cout << "Given unit is not found." << endl;
    return 0;
  }
}

double Nucleus::EnergyAfterMaterial(char* materialname, double thickness, string unit) {
  double EnergynAfterMaterial = BeamEnergy - EnergyLoss(materialname,thickness)/MassNum;
  
  if(unit=="MeV/A") {
    return EnergynAfterMaterial;
  } else if (unit=="MeV") {
    return EnergynAfterMaterial*MassNum;
  } else if (unit=="MeV/u") {
    return EnergynAfterMaterial*MassNum/MassInU();
  } else if (unit=="MeV/c") {
    double totalEnergy =  EnergynAfterMaterial*MassNum + Mass();
    return sqrt(totalEnergy*totalEnergy -Mass()*Mass());
  } else if (unit=="Tm") {
    double totalEnergy =  EnergynAfterMaterial*MassNum + Mass();
    double momentum = sqrt(totalEnergy*totalEnergy -Mass()*Mass());
    return momentum/Charge/299.792458;
  } else if (unit=="beta") {
    double totalEnergy =  EnergynAfterMaterial*MassNum + Mass();
    double momentum = sqrt(totalEnergy*totalEnergy -Mass()*Mass());
    return momentum/totalEnergy;
  } else {
    cout << "Given unit is not found." << endl;
    return 0;
  }
}

double Nucleus::ThicknessForExitEnergy(char* materialname, double exitEnergy, string unit) {
  string file=dir+"Atima/atima.data/temp.mat";
  double thickness_temp = 100.; //temporary
  ofstream fout(file.c_str());
  fout << "jtargetlist" << endl;
  fout << "0" << endl;
  fout << "stack 1 " << materialname << endl;
  fout << thickness_temp << " 1 " << materialname << endl;
  fout << "end stack" << endl;
  fout << "end jtargetlist" << endl;
  fout.close();
  char ch[]="temp.mat";

  string file1=dir+"Atima/atima.data/temp.conf";
  fout.open(file1.c_str());
  fout << "jconfiguration" << endl;
  fout << "standard" << endl;
  fout << ch << endl;
  fout << GetIsotopeName(ProtonNum) << "  " << ProtonNum 
       << "  " << MassNum << "  " << MassInU() << endl;
  fout << 1 << endl << 1 << endl << 17 << "  " << 1 << endl;
  fout << BeamEnergyMeVperU() << endl;
  fout << "0.0  0.0 "<< endl;
  fout << "0 0 0 0" << endl; 
  fout << "25 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24" << endl;
  fout.close();

  //calculation exitenergy in MeV/u 
  double exitEn;
  if(unit=="MeV/A") {
    exitEn=exitEnergy/MassInU()*MassNum;
  } else if (unit=="MeV") {
    exitEn=exitEnergy/MassInU();
  } else if (unit=="MeV/u") {
    exitEn=exitEnergy;
  } else if (unit=="MeV/c") {
    double kinEnergy = sqrt(exitEnergy*exitEnergy + Mass()*Mass())-Mass();
    exitEn = kinEnergy/MassInU();
  } else if (unit=="Tm") {
    double mom = exitEnergy*Charge*299.792458;
    double kinEnergy = sqrt(mom*mom + Mass()*Mass())-Mass();
    exitEn = kinEnergy/MassInU();
  } else if (unit=="beta") {
    double be=exitEnergy;
    double ga=1/sqrt(1-be*be);
    double mom = be*ga*Mass();
    double kinEnergy = sqrt(mom*mom + Mass()*Mass())-Mass();
    exitEn = kinEnergy/MassInU();
  } 

  string file2=dir+"Atima/atima.data/temp.batch";
  fout.open(file2.c_str());
  fout << "ReadConf temp.conf" << endl << "Format pvt" << endl 
       << "CalcOrder successive" << endl << "Mode fen " << exitEn << endl
       << "Splines s" << endl << "CalcParams" << endl 
       << "Value 0 outputtemp.txt" << endl << "EndInput" << endl;
  fout.close();

  char str[255];
  strcpy(str,"(cd ~/Atima; ./JavaAtima2 atima.data/temp.batch >> /dev/null)");
  int ret=system(str);
  if (ret!=0) return ret;

  string filein=dir+"Atima/atima.output/outputtemp.txt";
  ifstream fin(filein.c_str());
  string s;
  stringstream ss;
  double thickness;
  if (!fin) {
    cout << "no file" << endl;
    return 0;
  } else {
    while (!fin.eof()&&s!="thickness") {
    fin >> s; 
    }
    fin >> s >> s >> s;
    s.erase(s.size()-1);
    ss << s;
    ss >> thickness;
  }

  return thickness;
}

string Nucleus::GetIsotopeName(int zed) {
  switch (zed) {
  case 1:
    return "H";
  case 2:
    return "He";
  case 3:
    return "Li";
  case 4:
    return "Be";
  case 5:
    return "B";
  case 6:
    return "C";
  case 7:
    return "N";
  case 8:
    return "O";
  case 9:
    return "F";
  case 10:
    return "Ne";
  case 11:
    return "Na";
  case 12:
    return "Mg";
  case 13:
    return "Al";
  case 14:
    return "Si";
  case 15:
    return "P";
  case 16:
    return "S";
  case 17:
    return "Cl";
  case 18:
    return "Ar";
  case 19:
    return "K";
  case 20:
    return "Ca";
  case 21:
    return "Sc";
  case 22:
    return "Ti";
  case 23:
    return "V";
  case 24:
    return "Cr";
  case 25:
    return "Mn";
  case 26:
    return "Fe";
  case 27:
    return "Co";
  case 28:
    return "Ni";
  case 29:
    return "Cu";
  case 30:
    return "Zn";
  case 31:
    return "Ga";
  case 32:
    return "Ge";
  case 33:
    return "As";
  case 34:
    return "Se";
  case 35:
    return "Br";
  case 36:
    return "Kr";
  case 37:
    return "Rb";
  case 38:
    return "Sr";
  case 39:
    return "Y";
  case 40:
    return "Zr";
  case 41:
    return "Nb";
  case 42:
    return "Mo";
  case 43:
    return "Tc";
  case 44:
    return "Ru";
  case 45:
    return "Rh";
  case 46:
    return "Pd";
  case 47:
    return "Ag";
  case 48:
    return "Cd";
  case 49:
    return "In";
  case 50:
    return "Sn";
  case 51:
    return "Sb";
  case 52:
    return "Te";
  case 53:
    return "I";
  case 54:
    return "Xe";
  case 55:
    return "Cs";
  case 56:
    return "Ba";
  case 57:
    return "La";
  case 58:
    return "Ce";
  case 59:
    return "Pr";
  case 60:
    return "Nd";
  case 61:
    return "Pm";
  case 62:
    return "Sm";
  case 63:
    return "Eu";
  case 64:
    return "Gd";
  case 65:
    return "Tb";
  case 66:
    return "Dy";
  case 67:
    return "Ho";
  case 68:
    return "Er";
  case 69:
    return "Tm";
  case 70:
    return "Yb";
  case 71:
    return "Lu";
  case 72:
    return "Hf";
  case 73:
    return "Ta";
  case 74:
    return "W";
  case 75:
    return "Re";
  case 76:
    return "os";
  case 77:
    return "Ir";
  case 78:
    return "Pt";
  case 79:
    return "Au";
  case 80:
    return "Hg";
  case 81:
    return "Tl";
  case 82:
    return "Pb";
  case 83:
    return "Bi";
  case 84:
    return "Po";
  case 85:
    return "At";
  case 86:
    return "Rn";
  case 87:
    return "Fr";
  case 88:
    return "Ra";
  case 89:
    return "Ac";
  case 90:
    return "Th";
  case 91:
    return "Pa";
  case 92:
    return "U";
  case 93:
    return "Np";
  case 94:
    return "Pu";
  case 95:
    return "Am";
  case 96:
    return "Cm";
  case 97:
    return "Bk";
  case 98:
    return "Cf";
  case 99:
    return "Es";
  case 100:
    return "Fm";
  case 101:
    return "Md";
  case 102:
    return "No";
  case 103:
    return "Lr";
  case 104:
    return "Rf";
  case 105:
    return "Db";
  case 106:
    return "Sg";
  case 107:
    return "Bh";
  case 108:
    return "Hs";
  case 109:
    return "Mt";
  case 110:
    return "Ds";
  case 111:
    return "Rg";
  case 112:
    return "Cn";
  case 113:
    return "Uut";
  case 114:
    return "Fl";
  case 115:
    return "Uup";
  case 116:
    return "Lv";
  default:
    cout << "zed is out of database" << endl;
    return "error";
  }
}

