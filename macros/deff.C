{
   TCanvas *c1 = new TCanvas ("c1","c1",0,0,800,600);
   TGraph *g1 = new TGraph(18);
   g1->SetPoint( 0, 45.8  ,  -0.137);
   g1->SetPoint( 1, 81.0  ,  -0.131);
   g1->SetPoint( 2, 121.8 ,  -0.144);
   g1->SetPoint( 3, 244.7 ,  -0.133);
   g1->SetPoint( 4, 276.4 ,  -0.136);
   g1->SetPoint( 5, 302.9 ,  -0.151);
   g1->SetPoint( 6, 344.3 ,  -0.150);
   g1->SetPoint( 7, 356.0 ,  -0.154);
   g1->SetPoint( 8, 383.8 ,  -0.155);
   g1->SetPoint( 9, 411.1 ,  -0.106);
   g1->SetPoint(10, 444.0 ,  -0.138);
   g1->SetPoint(11, 778.9 ,  -0.107);
   g1->SetPoint(12, 867.4 ,  -0.092);
   g1->SetPoint(13, 964.1 ,  -0.098);
   g1->SetPoint(14, 1112.1,  -0.088);
   g1->SetPoint(15, 1213.0,  -0.079);
   g1->SetPoint(16, 1299.1,  -0.090);
   g1->SetPoint(17, 1408.0,  -0.084);
   TGraph *g2 = new TGraph(18);
   g2->SetPoint( 0, 45.8  ,  0.139);
   g2->SetPoint( 1, 81.0  ,  0.129);
   g2->SetPoint( 2, 121.8 ,  0.149);
   g2->SetPoint( 3, 244.7 ,  0.155);
   g2->SetPoint( 4, 276.4 ,  0.098);
   g2->SetPoint( 5, 302.9 ,  0.096);
   g2->SetPoint( 6, 344.3 ,  0.144);
   g2->SetPoint( 7, 356.0 ,  0.091);
   g2->SetPoint( 8, 383.8 ,  0.085);
   g2->SetPoint( 9, 411.1 ,  0.123);
   g2->SetPoint(10, 444.0 ,  0.121);
   g2->SetPoint(11, 778.9 ,  0.099);
   g2->SetPoint(12, 867.4 ,  0.097);
   g2->SetPoint(13, 964.1 ,  0.090);
   g2->SetPoint(14, 1112.1,  0.085);
   g2->SetPoint(15, 1213.0,  0.080);
   g2->SetPoint(16, 1299.1,  0.085);
   g2->SetPoint(17, 1408.0,  0.073);
   g1->Draw("ALp");
   g2->Draw("Lp");
}


