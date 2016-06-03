{
   TGraph *g = new TGraph(15);

   g->SetPoint( 0, 100 ,  0.260);
   g->SetPoint( 1, 300 ,  0.107);
   g->SetPoint( 2, 500 ,  0.068);
   g->SetPoint( 3, 700 ,  0.054);
   g->SetPoint( 4, 900 ,  0.044);
   g->SetPoint( 5, 1100,  0.042);
   g->SetPoint( 6, 1300,  0.038);
   g->SetPoint( 7, 1500,  0.036);
   g->SetPoint( 8, 1700,  0.034);
   g->SetPoint( 9, 1900,  0.033);
   g->SetPoint(10, 2100,  0.031);
   g->SetPoint(11, 2300,  0.032);
   g->SetPoint(12, 2500,  0.031);
   g->SetPoint(13, 2700,  0.037);
   g->SetPoint(14, 2900,  0.032);
   g->SetMarkerStyle(26);
   g->Draw("ALp");
}

