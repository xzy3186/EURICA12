 {
   // gROOT->ProcessLine(".L macros/ShowMINOSOnline.cc+");
  gROOT->ProcessLine(".L macros/ShowDALIOnline.cc+");
  //gROOT->ProcessLine(".L macros/ShowBRPPACEfficiency.cc+");
  //gROOT->ProcessLine(".L macros/ShowZDPPACEfficiency.cc+");
  gROOT->ProcessLine(".L macros/ShowPPACRaw.cc+");
  //gROOT->ProcessLine(".L macros/ShowTKE.cc+");
  //gROOT->ProcessLine(".L macros/ShowPID.cc+");
  gROOT->ProcessLine(".L macros/original/ShowMUSIC.cc+");
  gROOT->ProcessLine(".L macros/ShowMUSIC.cc+");
  gROOT->ProcessLine(".L macros/ShowPlastic.cc+");
  //gROOT->ProcessLine(".L macros/ShowPosGated.cc+");
  //gROOT->ProcessLine(".L macros/MakeOnlineBigRIPSTree.cc+");
  //gROOT->ProcessLine(".L macros/ShowDSSSDOnline.cc+"); 

  //book (new ShowMINOSOnline);
  book (new ShowDALIOnline);
  //book (new ShowBRPPACEfficiency);
  //book (new ShowZDPPACEfficiency);
  //book (new ShowPPACRaw);
  //book (new ShowMUSIC);
  //book (new ShowPID);
  //book(ShowTKE);
  //book (new ShowPlastic);
  //book (new ShowPosGated);
  //book (new MakeOnlineBigRIPSTree);
  //book (new ShowDSSSDOnline);;

 //For RawData:
  //book(new TAlRawDataExample);
  
push();
  // push("./ridf/minosdali9056.ridf");
  //push("~/../gamma14/ridf/gamma14-0070.ridf"); 
  //push("./ridf/gamma120014.ridf.gz");
  //start();
}
