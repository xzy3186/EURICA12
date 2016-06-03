{
  //TF1 *f = new TF1("f","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)+gaus(18)+gaus(21)");
  //TF1 *f = new TF1("f","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)+gaus(18)");
  TF1 *f = new TF1("f","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)");
  f->SetParameter( 0,1000);  f->SetParameter( 1,3.11);  f->SetParameter( 2,0.01);
  f->SetParameter( 3,1000);  f->SetParameter( 4,3.24);  f->SetParameter( 5,0.01);
  f->SetParameter( 6,1000);  f->SetParameter( 7,3.37);  f->SetParameter( 8,0.01);
  f->SetParameter( 9,1000);  f->SetParameter(10,3.49);  f->SetParameter(11,0.01);
  f->SetParameter(12,1000);  f->SetParameter(13,3.63);  f->SetParameter(14,0.01);
  f->SetParameter(15,1000);  f->SetParameter(16,3.75);  f->SetParameter(17,0.01);
  //f->SetParameter(18,100);  f->SetParameter(19,33);  f->SetParameter(20,0.1);
  //f->SetParameter(21,100);  f->SetParameter(22,50-0.5);  f->SetParameter(23,0.1);

  f->SetParLimits( 0,1,100000);  f->SetParLimits( 1,3.06,3.16);  f->SetParLimits( 2,0.005,0.36);
  f->SetParLimits( 3,1,100000);  f->SetParLimits( 4,3.19,3.29);  f->SetParLimits( 5,0.005,0.36);
  f->SetParLimits( 6,1,100000);  f->SetParLimits( 7,3.32,3.42);  f->SetParLimits( 8,0.005,0.36);
  f->SetParLimits( 9,1,100000);  f->SetParLimits(10,3.44,3.54);  f->SetParLimits(11,0.005,0.36);
  f->SetParLimits(12,1,100000);  f->SetParLimits(13,3.58,3.68);  f->SetParLimits(14,0.005,0.36);
  f->SetParLimits(15,1,100000);  f->SetParLimits(16,3.70,3.80);  f->SetParLimits(17,0.005,0.36);
  //f->SetParLimits(18,1,100000);  f->SetParLimits(19,32.5,33.5);  f->SetParLimits(20,0.05,0.36);
  //f->SetParLimits(21,1,100000);  f->SetParLimits(22,49.5-0.5,50.5-0.5);  f->SetParLimits(23,0.05,0.36);

}
