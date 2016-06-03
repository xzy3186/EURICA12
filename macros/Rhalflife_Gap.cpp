{
   TCanvas *c1 = new TCanvas ("c1","c1",0,0,800,600);
   TGraphErrors *g1 = new TGraphErrors(16);
   g1->SetPoint( 0, 3798, 0.869);
   g1->SetPoint( 1, 2642, 2.238);
   g1->SetPoint( 2, 3146, 1.479);
   g1->SetPoint( 3, 3451, 1.475);
   g1->SetPoint( 4, 3508, 1.048);
   //g1->SetPoint( 5, 2210, 1.059);
   //g1->SetPoint( 6, 2122, 0.456);
   //g1->SetPoint( 7, 1098, 0.352);
   //g1->SetPoint( 8, 1770, 1.255);
   //g1->SetPoint( 9, 3442, 1.610);
   //g1->SetPoint(10, 4383,32.141);
   //g1->SetPoint(11, 980 , 1.485);
   //g1->SetPoint(12, 809 , 0.525);
   //g1->SetPoint(13, 2300, 1.313);
   //g1->SetPoint(14, 4350, 2.671);
   //g1->SetPoint(15, 5197, 0.429);
   g1->SetPointError( 0, 4  , 0.054);
   g1->SetPointError( 1, 7  , 0.264);
   g1->SetPointError( 2, 5  , 0.202);
   g1->SetPointError( 3, 6  , 0.018);
   g1->SetPointError( 4, 10 , 0.023);
   //g1->SetPointError( 5, 653, 0.220);
   //g1->SetPointError( 6, 600, 0.191);
   //g1->SetPointError( 7, 29 , 0.046);
   //g1->SetPointError( 8, 128, 0.157);
   //g1->SetPointError( 9, 71 , 0.315);
   //g1->SetPointError(10, 40 , 1.899);
   //g1->SetPointError(11, 796, 0.218);
   //g1->SetPointError(12, 500, 0.054);
   //g1->SetPointError(13, 433, 0.265);
   //g1->SetPointError(14, 303, 0.374);
   //g1->SetPointError(15, 3  , 0.041);
   g1->Draw("Ap");
}


