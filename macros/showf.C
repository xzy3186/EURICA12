{
  cout << "27   " << f->GetParameter(1) << endl;
  cout << "28   " << f->GetParameter(4) << endl;
  cout << "29   " << f->GetParameter(7) << endl;
  cout << "30   " << f->GetParameter(10) << endl;
  cout << "31   " << f->GetParameter(13) << endl;
  cout << "32   " << f->GetParameter(16) << endl;
//  cout << "33   " << f->GetParameter(19) << endl;
//  cout << "50   " << f->GetParameter(22) << endl;

  TGraph *g = new TGraph(6);
  g->SetPoint(0,f->GetParameter( 1),27);
  g->SetPoint(1,f->GetParameter( 4),28);
  g->SetPoint(2,f->GetParameter( 7),29);
  g->SetPoint(3,f->GetParameter(10),30);
  g->SetPoint(4,f->GetParameter(13),31);
  g->SetPoint(5,f->GetParameter(16),32);
  //g->SetPoint(6,f->GetParameter(19),33);
 // g->SetPoint(7,f->GetParameter(22),50);
  new TCanvas;
  g->SetMarkerStyle(8);
  g->Draw("ap");

  TF1 *ll = new TF1("ll","pol1");
  g->Fit("ll");

  cout << ll->GetParameter(0) << "   " << ll->GetParameter(1) << endl;


}
