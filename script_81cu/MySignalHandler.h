// MySignalHandler.h
#ifndef __MY_SIGNAL_HANDLER_H__
#define __MY_SIGNAL_HANDLER_H__
#include <TSysEvtHandler.h>
class MySignalHandler : public TSignalHandler {
   public:
      MySignalHandler( ESignals sig ) : TSignalHandler( sig ) {}
      Bool_t Notify();
};
#endif
