{
   TCanvas *c1 = new TCanvas ("c1","c1",0,0,800,600);
   c1->cd();
   c1->Divide(1,2);
   c1->cd(1);
   TGraph *g1 = new TGraph(13);
   g1->SetPoint(0 ,965 , 248.79);
   g1->SetPoint(1 ,970 , 248.86);
   g1->SetPoint(2 ,975 , 248.92);
   g1->SetPoint(3 ,980 , 248.99);
   g1->SetPoint(4 ,985 , 249.06);
   g1->SetPoint(5 ,990 , 249.13);
   g1->SetPoint(6 ,995 , 249.2 );
   g1->SetPoint(7 ,1000, 249.27);
   g1->SetPoint(8 ,1005, 249.34);
   g1->SetPoint(9 ,1010, 249.41);
   g1->SetPoint(10,1015, 249.49);
   g1->SetPoint(11,1020, 249.56);
   g1->SetPoint(12,1025, 249.63);
   g1->SetMarkerStyle(26);
   g1->Draw("ALp");
   c1->cd(2);
   TGraph *g2 = new TGraph(11);
   g2->SetPoint(0 ,45,237.85);
   g2->SetPoint(1 ,50,240.04);
   g2->SetPoint(2 ,55,242.09);
   g2->SetPoint(3 ,60,244.14);
   g2->SetPoint(4 ,65,246.22);
   g2->SetPoint(5 ,70,248.34);
   g2->SetPoint(6 ,75,250.5 );
   g2->SetPoint(7 ,80,252.7 );
   g2->SetPoint(8 ,85,254.94);
   g2->SetPoint(9 ,90,257.21);
   g2->SetPoint(10,95,259.53);
   g2->SetMarkerStyle(26);
   g2->Draw("ALp");
}
