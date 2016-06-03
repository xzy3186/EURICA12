void rootlogon(){
   gROOT->SetStyle("Modern");
   //  gROOT->SetStyle("Classic");

   //Force Style
   gStyle->SetHistFillColor(7);
   gStyle->SetHistFillStyle(3002);
   gStyle->SetHistLineColor(kBlue);
   gStyle->SetFuncColor(kRed);
   gStyle->SetFrameLineWidth(2);
   gStyle->SetPadGridX(1);
   gStyle->SetPadGridY(1);
   gStyle->SetCanvasColor(0);
   gStyle->SetTitleFillColor(0);
   gStyle->SetTitleStyle(0);
   gStyle->SetStatColor(0);
   gStyle->SetStatStyle(0);
   gStyle->SetStatX(0.9);  
   gStyle->SetStatY(0.9);  
   gStyle->SetPalette(1);
   gStyle->SetOptLogz(1);
   //  gStyle->SetOptTitle(0);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(1111111);
   gStyle->SetPadBorderMode(1);
   //  gStyle->SetOptDate(1);

   gStyle->SetLabelFont(132,"XYZ");
   gStyle->SetTitleFont(132,"XYZ");
   gStyle->SetTitleFont(132,"");
   gStyle->SetTextFont(132);
   gStyle->SetStatFont(132);
}
