{
   tree->Draw("BigRIPSBeam.zet>>h1(1000,25,35)");
   gROOT->ProcessLine(".x fit.C");
   //.x macro/fit.C;
   h1->Fit("f");
   gROOT->ProcessLine(".x showf.C");
}
