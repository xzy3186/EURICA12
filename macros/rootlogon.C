void rootlogon()
{
  gROOT->ProcessLine(".L macros/RooMyDecay.cxx+");
  gSystem->Load("libRooFitCore.so") ;
  using namespace RooFit ;
}
