{
   TGraph *g = new TGraph(8);
   g->SetPoint(0, 0.634, 0);
   g->SetPoint(1, 0.634, 1);
   g->SetPoint(2, 0.635, 2);
   g->SetPoint(3, 0.639, 3);
   g->SetPoint(4, 0.643, 4);
   g->SetPoint(5, 0.638, 5);
   g->SetPoint(6, 0.638, 6);
   g->SetPoint(7, 0.638, 7);

   g->SetMarkerStyle(26);
   g->Draw("ALp");
}

