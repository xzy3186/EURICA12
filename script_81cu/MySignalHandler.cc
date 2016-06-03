// MySignalHandler.cc
#include "MySignalHandler.h"
#include <TSystem.h>
#include <iostream>
using namespace std;
Bool_t MySignalHandler::Notify()
{
   cout << "catch signal " << (UInt_t)GetSignal() << endl;
   gSystem->ExitLoop();
   return kTRUE;
}
