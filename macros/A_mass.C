{
   TCanvas *c1 = new TCanvas ("c1","c1",0,0,1200,600);
   c1->Divide(3,1);
   c1->cd(1);
   TGraph *g = new TGraph(9);
   g->SetPoint(0, 14,31997637);
   g->SetPoint(1, 15,31985684);
   g->SetPoint(2, 16,31972071);
   g->SetPoint(3, 17,31973907);
   g->SetPoint(4, 18,31974151);
   g->SetPoint(5, 19,31988085);
   g->SetPoint(6, 20,31999110);
   g->SetPoint(7, 21,32020190);
   g->SetPoint(8, 22,32039720);
   g->SetMarkerStyle(26);
   g->Draw("ALp");

   c1->cd(2);
   TGraph *g1 = new TGraph(9);
   g1->SetPoint(0, 13,31012120);
   g1->SetPoint(1, 14,30992410);
   g1->SetPoint(2, 15,30979557);
   g1->SetPoint(3, 16,30973761);
   g1->SetPoint(4, 17,30975363);
   g1->SetPoint(5, 18,30983945);
   g1->SetPoint(6, 19,30996648);
   g1->SetPoint(7, 20,31013163);
   g1->SetPoint(8, 21,31033090);
   g1->SetPoint(9, 22,31059710);
   g1->SetMarkerStyle(26);
   g1->Draw("ALp");

   c1->cd(3);
   TGraph *g2 = new TGraph(12);
   g2->SetPoint(0 ,43,65993980);
   g2->SetPoint(1 ,42,65973660);
   g2->SetPoint(2 ,41,65960547);
   g2->SetPoint(3 ,40,65946250);
   g2->SetPoint(4 ,39,65939443);
   g2->SetPoint(5 ,38,65929139);
   g2->SetPoint(6 ,37,65928869);
   g2->SetPoint(7 ,36,65926033);
   g2->SetPoint(8 ,35,65931589);
   g2->SetPoint(9 ,34,65933862);
   g2->SetPoint(10,33,65944149);
   g2->SetPoint(11,32,65955590);
   g2->SetMarkerStyle(26);
   g2->Draw("ALp");
}

