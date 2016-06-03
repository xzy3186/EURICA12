void DrawNucleus(int zed, int neutron,int fillColor=0,char *str="") {
  TBox *b = new TBox(neutron-0.5,zed-0.5,neutron+0.5,zed+0.5);
  if(fillColor==0) {  
    b->SetFillStyle(fillColor);
  } else {
    b->SetFillColor(fillColor);
  }
  b->Draw();
  TLatex *l1  = new TLatex();
  l1->SetTextAlign(22);
  l1->SetTextSize(0.02);
  l1 -> DrawLatex(neutron,zed,str);
  return; 
}

void DrawNucleus_dash(int zed, int neutron, int fillColor=0,char *str="") {
  TBox *b = new TBox(neutron-0.5,zed-0.5,neutron+0.5,zed+0.5);
  if(fillColor!=0) {  
//    //    b->SetFillStyle(fillColor);
//  } else {
    b->SetFillColor(fillColor);
    b->Draw();
  }
  TLine* l2 = new TLine();
  l2->SetLineStyle(2);
  l2->DrawLine(neutron-0.5,zed-0.5,neutron-0.5,zed+0.5);
  l2->DrawLine(neutron+0.5,zed-0.5,neutron+0.5,zed+0.5);
  l2->DrawLine(neutron-0.5,zed-0.5,neutron+0.5,zed-0.5);
  l2->DrawLine(neutron-0.5,zed+0.5,neutron+0.5,zed+0.5);
//  TBox *b2 = new TBox(neutron-0.5,zed-0.5,neutron+0.5,zed+0.5);
//  b2->SetFillStyle(0);
//  b2->SetLineStyle(3);
//  b2->Draw();

  TLatex *l1  = new TLatex();
  l1->SetTextAlign(22);
  l1->SetTextSize(0.02);
  l1 -> DrawLatex(neutron,zed,str);
  return; 
}

void DrawIsotope(int zed, char *isotopeName, int massmin, int massmax, int massmax_odd) {
  // massmin: min of mass for plot
  // massmax: max of mass for plot
  // massmax_odd: max of mass of odd nucleus for plot
  // if massmax_odd > massmax, massmax_odd is neglected

  vector<int> neutron;

  if (massmax < massmax_odd) {
    for (int i=massmin;i<massmax+0.1;i++) {
      neutron.push_back(i-zed);
    }
  } else {    
    for (int i=massmin;i<massmax_odd+2;i++) {
      neutron.push_back(i-zed);
    }
    for (int i=massmax_odd+3;i<massmax+0.1;i=i+2) {
      neutron.push_back(i-zed);
    }
  }

  // Draw box and name
  for (int i=0;i<neutron.size();i++){
    stringstream ss;
    // Nucleus name
    //    ss << "^{" << zed+neutron[i] << "}" << isotopeName;
    DrawNucleus_dash(zed,neutron[i],0,ss.str().c_str());
  }
  return;
}

void DrawStable(int zed, int mass) {
  DrawNucleus(zed,mass-zed,1);
  return;
}

void DrawKnown(int zed, int mass) {
  DrawNucleus(zed,mass-zed,kYellow-10);
  DrawNucleus(zed,mass-zed,0);
  return;
}

void DrawNew(int zed, int mass,int fillColor=0,char *isotopeName="") {
  TBox *b = new TBox(mass-zed-0.5,zed-0.5,mass-zed+0.5,zed+0.5);
  b->SetFillColor(fillColor);  b->Draw();
  TBox *b2 = new TBox(mass-zed-0.5,zed-0.5,mass-zed+0.5,zed+0.5);
  b2->SetFillStyle(0);  b2->Draw();
  stringstream ss;
  ss << "^{" << mass << "}" << isotopeName;
  TLatex *l1  = new TLatex();
  l1->SetTextAlign(22);
  l1->SetTextSize(0.02);
  l1->SetTextColor(2);
  l1 -> DrawLatex(mass-zed,zed,ss.str().c_str());
  return; 
}

void DrawYieldRatio() {
  TH2D *hr = new TH2D("hr","hr",6,48,53,6,26,30);
  hr->Fill(28,50,13);
}

void Drawrprocess() {
  TLine *l1 = new TLine();
  l1->SetLineWidth(2);
  l1->SetLineColor(2);
  l1->DrawLine(45.5,25.5,45.5,26.5);
  l1->DrawLine(45.5,26.5,46.5,26.5);
  l1->DrawLine(45.5,25.5,46.5,25.5);
  l1->DrawLine(46.5,25.5,50.4,26.5);
  l1->DrawLine(46.5,26.5,49.6,27.5);
  l1->DrawLine(49.6,27.5,49.6,30.5);
  l1->DrawLine(50.4,26.5,50.4,29.5);
  l1->DrawLine(49.6,30.5,50.4,30.5);
  l1->DrawLine(50.4,30.5,53.5,31.5);
  l1->DrawLine(50.4,29.5,53.5,30.5);
  l1->DrawLine(53.5,30.5,54.5,30.5);
  l1->DrawLine(54.5,30.5,54.5,31.5);
  l1->DrawLine(53.5,31.5,53.5,32.5);
  l1->DrawLine(53.5,32.5,54.5,32.5);
  l1->DrawLine(54.5,32.5,56.5,32.5+2./3);
  l1->DrawLine(54.5,31.5,56.5,31.5+2./3);

}

void pal1() {
  //  gStyle->SetPalette(55);
  //const int col_Num = 6;
  //TColor *color;
  //int userpalette[col_Num];
  ////double Red[col_Num]   = {0.0,0.00,0.0,0.00,1.00,1.00};
  ////double Green[col_Num] = {0.0,0.25,0.5,0.50,0.38,0.40};
  ////double Blue[col_Num]  = {0.5,0.50,1.0,0.25,0.00,0.40};
  //double Red[col_Num]   = {1.00,1.00,0.00,0.0,0.00.0.0};
  //double Green[col_Num] = {0.40,0.38,0.50,0.5,0.25,0.0};
  //double Blue[col_Num]  = {0.40,0.00,0.25,1.0,0.50,0.5};
  //for (int i=0;i<col_Num;i++) {
  //  if(!gROOT->GetColor(230+i)) {
  //    color = new TColor(230+i,0,0,0,"");
  //  } else {
  //    color=gROOT->GetColor(230+i);
  //  }
  //  color->SetRGB(Red[i],Green[i],Blue[i]);
  //  userpalette[i] = 230+i;
  //}
  //  gStyle->SetPalette(col_Num,userpalette);
  //  //gStyle->SetPalette(1);
  int userpalette2[50];
  for (int i=0;i<50;i++) userpalette2[i]=100-i+2;
  //for (int i=0;i<50;i++) cout << userpalette2[i] << endl;
  //gStyle->SetPalette(50,userpalette2,0.1);
  gStyle->SetPalette(50,userpalette2);

}

void NuclearChart() {
  //  gROOT->ProcessLine(".L function.c");
  TCanvas *c1 = new TCanvas("c1","",0,0,750,400);

  //Set aspect ratio of square in Pad
//  double w = gPad->GetWw()*gPad->GetAbsWNDC();
//  double h = gPad->GetWh()*gPad->GetAbsHNDC();
  double xmin = 30;
  double xmax = 56;
  double ymin = 24;
  double ymax = 36 ; // should be within frame


  double frame_xmin = xmin-2;
  double frame_xmax = xmax+1;
  double frame_ymin = ymin-2;
  double frame_ymin = ymin-2;
  double frame_ymax = ymin+(xmax-xmin); //temporary

  gPad->DrawFrame(frame_xmin,frame_ymin,frame_xmax,frame_ymax);
  double pixel_xaxis = gPad->XtoPixel(frame_xmax)-gPad->XtoPixel(frame_xmin);
  double pixel_yaxis = gPad->YtoPixel(frame_ymin)-gPad->YtoPixel(frame_ymax);
  frame_ymax = frame_ymin+(frame_xmax-frame_xmin)*pixel_yaxis/pixel_xaxis;
  gPad->DrawFrame(frame_xmin,frame_ymin,frame_xmax,frame_ymax);


  TH2D *frame = new TH2D("frame","",10,frame_xmin,frame_xmax,10,frame_ymin,frame_ymax);
  frame->SetStats(0);
  frame->Draw("AH");
  //  delete frame;    // to delete a frame
  c1->SetFrameLineColor(0);

  c1->SetFixedAspectRatio();
  c1->SetLeftMargin(0.03);



  int zed;

  //  Known  isotopes      //
  //  for(int i=23+xmin+4;i<67+1;i++) DrawKnown(23,i);    //V
  zed=24;for(int i=zed+xmin;i<70+1;i++) DrawKnown(zed,i);    //Cr
  zed=25;for(int i=zed+xmin;i<72+1;i++) DrawKnown(zed,i);    //Mn
  zed=26;for(int i=zed+xmin;i<74+1;i++) DrawKnown(zed,i);    //Fe
  zed=27;for(int i=zed+xmin;i<76+1;i++) DrawKnown(zed,i);    //Co
  zed=28;for(int i=zed+xmin;i<79+1;i++) DrawKnown(zed,i);    //Ni
  zed=29;for(int i=zed+xmin;i<82+1;i++) DrawKnown(zed,i);    //Cu
  zed=30;for(int i=zed+xmin;i<85+1;i++) DrawKnown(zed,i);    //Zn
  zed=31;for(int i=zed+xmin;i<87+1;i++) DrawKnown(zed,i);    //Ga
  zed=32;for(int i=zed+xmin;i<xmax+zed+1;i++) DrawKnown(zed,i);    //Ge
  zed=33;for(int i=64;i<xmax+zed+1;i++) DrawKnown(zed,i);    //As
  zed=34;for(int i=64;i<xmax+zed+1;i++) DrawKnown(zed,i);    //Se
  zed=35;for(int i=70;i<xmax+zed+1;i++) DrawKnown(zed,i);    //Br
  zed=36;for(int i=69;i<xmax+zed+1;i++) DrawKnown(zed,i);    //Kr

  //Nuclues by FRDM95
  //  DrawIsotope(zed=23,"V", zed+xmin,77,72);
  DrawIsotope(zed=24,"Cr",zed+xmin,78,73);
  DrawIsotope(zed=25,"Mn",zed+xmin,zed+xmax,76);
  DrawIsotope(zed=26,"Fe",zed+xmin,zed+xmax,77);
  DrawIsotope(zed=27,"Co",zed+xmin,zed+xmax,80);
  DrawIsotope(zed=28,"Ni",zed+xmin,zed+xmax,81);
  DrawIsotope(zed=29,"Cu",zed+xmin,zed+xmax,90);
  DrawIsotope(zed=30,"Zn",zed+xmin,zed+xmax,93);
  DrawIsotope(zed=31,"Ga",zed+xmin,zed+xmax,94);
  DrawIsotope(zed=32,"Ge",zed+xmin,zed+xmax,101);
  DrawIsotope(zed=33,"As",64,zed+xmax,102);
  DrawIsotope(zed=34,"Se",64,zed+xmax,105);
  DrawIsotope(zed=35,"Br",69,zed+xmax,108);
  DrawIsotope(zed=36,"Kr",67,zed+xmax,117);

  if(xmax>82-24-1) DrawIsotope(zed=24,"Cr",82,82,1000);


  //  Stable           //
  int CrStable[4] = {50,52,53,54};
  for(int i=3;i<4;i++) DrawStable(24,CrStable[i]);   //Cr
  DrawStable(25,55);   //Mn
  int FeStable[4] = {54,56,57,58};
  for(int i=1;i<4;i++) DrawStable(26,FeStable[i]);   //Fe
  DrawStable(27,59);   //Co
  int NiStable[5] = {58,60,61,62,64};
  for(int i=0;i<5;i++) DrawStable(28,NiStable[i]);   //Ni
  DrawStable(29,63);  DrawStable(29,65);   //Cu
  int ZnStable[5] = {64,66,67,68,70};
  for(int i=0;i<5;i++) DrawStable(30,ZnStable[i]);   //Zn
  DrawStable(31,69);  DrawStable(31,71);   //Ga
  int GeStable[5] = {70,72,73,74,76};
  for(int i=0;i<5;i++) DrawStable(32,GeStable[i]);   //Ge
  DrawStable(33,75);     //As
  int SeStable[6] = {74,76,77,78,80,82};
  for(int i=0;i<6;i++) DrawStable(34,SeStable[i]);   //Se
  DrawStable(35,79);    DrawStable(35,81);    //Br
  int KrStable[6] = {78,80,82,83,84,86};
  for(int i=0;i<6;i++) DrawStable(36,KrStable[i]);   //Kr

  //New isotope
//  DrawNew(25,73,kYellow-10,"Mn");  
//  DrawNew(26,76,kYellow-10,"Fe");  
//  DrawNew(27,77,kYellow-10,"Co");  DrawNew(27,78,kYellow-10,"Co");
//  DrawNew(28,80,kYellow-10,"Ni");  DrawNew(28,81,kYellow-10,"Ni");
//  DrawNew(29,83,kYellow-10,"Cu");  

// List of yield ratio
  //TH2D *h2 = new TH2D("h2","h2",10,45.5,55.5,10,22.5,32.5);
  TH2D *h2 = new TH2D("h2","h2",13,43.5,56.5,10,22.5,32.5);

  h2->Fill(44,26,65.9     );
  h2->Fill(45,26,37.2     );
  h2->Fill(46,26,16.5     );
  h2->Fill(47,26,11.1     );
  h2->Fill(48,26,8.2      );
  h2->Fill(45,27,52.8     );
  h2->Fill(46,27,40.4     );
  h2->Fill(47,27,31.6     );
  h2->Fill(48,27,25.9     );
  h2->Fill(49,27,17.6     );
  h2->Fill(50,27,13.0     );
  h2->Fill(46,28,507.7    );
  h2->Fill(47,28,331.6    );
  h2->Fill(48,28,234.6    );
  h2->Fill(49,28,158.9    );
  h2->Fill(50,28,121.8    );
  h2->Fill(51,28,42.7     );
  h2->Fill(52,28,22.3     );
  h2->Fill(48,29,474.4    );
  h2->Fill(49,29,330.7    );
  h2->Fill(50,29,241.3    );
  h2->Fill(51,29,113.3    );
  h2->Fill(52,29,66.4     );
  h2->Fill(53,29,31.6     );
  h2->Fill(50,30,562.2    );
  h2->Fill(51,30,303.2    );
  h2->Fill(52,30,177.9    );
  h2->Fill(53,30,99.4     );
  h2->Fill(54,30,63.4     );
  h2->Fill(52,31,310.1    );
  h2->Fill(53,31,92.7     );
  h2->Fill(54,31,91.9     );
  h2->Fill(55,31,51.2     );
  h2->Fill(56,31,26.2     );
  h2->Fill(53,32,510.7    );
  h2->Fill(54,32,225.5    );
  h2->Fill(55,32,103.1    );
  h2->Fill(56,32,59.1     );
  //h2->Fill(48,26,11.8965);
  //h2->Fill(49,26,17.0455);
  //h2->Fill(48,27,9.50491);
  //h2->Fill(49,27,19.0517);
  //h2->Fill(50,27,13.1187);
  //h2->Fill(51,27,28.4218);
  //h2->Fill(48,28,7.61612);
  //h2->Fill(49,28,13.5509);
  //h2->Fill(50,28,15.0314);
  //h2->Fill(51,28,47.3913);
  //h2->Fill(52,28,13.1902);
  //h2->Fill(49,29,8.36959);
  //h2->Fill(50,29,7.56459);
  //h2->Fill(51,29,25.0395);
  //h2->Fill(52,29,10.3199);
  //h2->Fill(53,29,30.8411);
  //h2->Fill(51,30,11.3299);
  //h2->Fill(52,30,9.22326);
  //h2->Fill(53,30,29.984 );
  TExec *ex1 = new TExec("ex1","pal1();");
  ex1->Draw();

  h2->SetContour(20);
  h2->GetZaxis()->SetRangeUser(6,655);
  h2->Draw("colz same");
  c1->SetLogz(1);
  c1->Update();
  TPaletteAxis *palette = (TPaletteAxis*)(h2->GetListOfFunctions()->FindObject("palette"));
  palette->SetX1NDC( palette->GetX2NDC()-(palette->GetX2NDC()-palette->GetX1NDC())*0.5);
  palette->SetY2NDC(0.6);
  palette->SetY1NDC(0.1);
  
  TPaveText *pt = new TPaveText(0.90,0.58,0.99,0.72,"blNDC");
  pt->SetTextFont(12);
  //pt->SetLabelSize(12);
  pt->AddText("T_{1/2} (ms)");
  pt->SetBorderSize(1);
  pt->SetLineColor(0);
  pt->SetFillColor(0);
  pt->Draw();



  c1->Update();
  c1->cd(0);
  double newzed[13]={26,26,26,27,27,28,28,29,29,30,31,32,32};
  double newneu[13]={72,73,74,76,77,79,80,81,82,84,87,87,88}; // here mass number
  for (int i=0;i<13;i++) newneu[i] = newneu[i] - newzed[i];
  TGraph *gr = new TGraph(13,newneu,newzed);
  gr->SetMarkerColor(1);
  gr->SetMarkerStyle(33);
  TMultiGraph *g = new TMultiGraph();
  g->Add(gr);
  g->Draw("P");
  //  gr->Draw("P");

  TLine *l1 = new TLine();
  l1->SetLineWidth(3);
  TLatex *t1 = new TLatex();
  t1->SetTextAlign(22);
  double low, high;
  //N=50
  low=ymin-1;
  high=ymax+1;
  l1->DrawLine(49.5,low,49.5,high);
  l1->DrawLine(50.5,low,50.5,high);
  t1->DrawLatex(50,low-0.5,"50");
  //Z=28
  low = xmin-1;
  high= 82.5-28;
  l1->DrawLine(low,28.5,high,28.5);
  l1->DrawLine(low,27.5,high,27.5);

  l1->SetLineStyle(2);
  l1->DrawLine(high,28.5,high+1,28.5);
  l1->DrawLine(high,27.5,high+1,27.5);

  l1->SetLineStyle(1);
  l1->DrawLine(high+1,28.5,high+2,28.5);
  l1->DrawLine(high+1,27.5,high+2,27.5);

  t1->DrawLatex(low-0.5,28,"28");

  t1->SetTextFont(131);
  t1->SetTextSize(0.04);
  t1->DrawLatex(xmax-1.5,ymin-2.2,"Neutron Number");
  t1->SetTextAngle(90);
  t1->DrawLatex(xmin-2.2,ymax-2.,"Proton Number");
  //  Draw r-process
  //Drawrprocess();

  TLegend* lg = new TLegend(0.75,0.7,0.9,0.9);
  lg->SetTextFont(131);
  lg->SetFillColor(0);
  lg->AddEntry((TObject*)0,"Stable isotope","");
  lg->AddEntry((TObject*)0,"Known isotope","");
  lg->AddEntry(gr,"New half-life","p");
  //lg->AddEntry((TObject*)0,"r-process path","");
  lg->Draw();
  c1->Update(); // to get x1ndc etc.
  double lg_ndctox1,lg_ndctox2,lg_ndctoy1,lg_ndctoy2;
  lg_ndctox1=gPad->AbsPixeltoX(gPad->UtoPixel(lg->GetX1NDC()));
  lg_ndctox2=gPad->AbsPixeltoX(gPad->UtoPixel(lg->GetX2NDC()));
  lg_ndctoy1=gPad->AbsPixeltoY(gPad->VtoPixel(lg->GetY1NDC()));
  lg_ndctoy2=gPad->AbsPixeltoY(gPad->VtoPixel(lg->GetY2NDC()));
  TBox *blg = new TBox();
  double boxsize = 0.5;
  double xspace = 0.45;
  double yspace;

  TBox *b1 = new TBox();

  //stable
  b1->SetFillStyle(100);
  b1->SetFillColor(1);
  b1->SetLineColor(1);
  b1->SetLineWidth(1);
  yspace  = 0.4;
  b1->DrawBox(lg_ndctox1+xspace,lg_ndctoy2-yspace,
	      lg_ndctox1+xspace+boxsize,lg_ndctoy2-yspace-boxsize);
  //known
  b1->SetFillStyle(100);
  b1->SetFillColor(kYellow-10);
  b1->SetLineColor(1);
  b1->SetLineWidth(1);
  yspace  = 1.5;
  b1->DrawBox(lg_ndctox1+xspace,lg_ndctoy2-yspace,
	      lg_ndctox1+xspace+boxsize,lg_ndctoy2-yspace-boxsize);
  b1->SetFillStyle(0);
  b1->DrawBox(lg_ndctox1+xspace,lg_ndctoy2-yspace,
	      lg_ndctox1+xspace+boxsize,lg_ndctoy2-yspace-boxsize);

//  //r-process
//  b1->SetFillStyle(0);
//  b1->SetLineColor(2);
//  b1->SetLineWidth(2);
//  yspace  = 2.9;
//  b1->DrawBox(lg_ndctox1+xspace,lg_ndctoy2-yspace,
//	      lg_ndctox1+xspace+boxsize,lg_ndctoy2-yspace-boxsize);

  TPad *npad = new TPad("npad","",0.1,0.5,0.4,0.9,-1);
  npad->Draw();
  npad->cd();
  frame_xmin = 46;
  frame_ymin = 25;
  frame_xmax = 56;
  frame_ymax = 33;
  gPad->DrawFrame(frame_xmin,frame_ymin,frame_xmax,frame_ymax);
  pixel_xaxis = gPad->XtoPixel(frame_xmax)-gPad->XtoPixel(frame_xmin);
  pixel_yaxis = gPad->YtoPixel(frame_ymin)-gPad->YtoPixel(frame_ymax);
  frame_ymax = frame_ymin+(frame_xmax-frame_xmin)*pixel_yaxis/pixel_xaxis;
  gPad->DrawFrame(frame_xmin,frame_ymin,frame_xmax,frame_ymax);
  TH2D *frame = new TH2D("frame","",10,frame_xmin,frame_xmax,8,frame_ymin,frame_ymax);
  npad->SetBottomMargin(0.15);
  npad->SetRightMargin(0.18);
  frame->SetStats(0);
  frame->Draw("AH");
  npad->SetFrameLineColor(0);
  //  delete frame;    // to delete a frame

  c1->Update();
  cout << npad->GetX1() << endl;
  TBox *b2 = new TBox();
  b2->SetFillStyle(0);
  b2->SetLineColor(kGreen+3);
  b2->SetLineWidth(2);
  b2->DrawBox(npad->GetX1()+0.1,npad->GetY1()+0.1,npad->GetX2()-0.1,npad->GetY2()-0.2);

  gROOT->ProcessLine(".x SnFRDMContour.c");
  
//  b1->SetFillStyle(100);
//  b1->SetFillColor(kYellow-10);
//  b1->SetLineColor(1);
//  b1->SetLineWidth(1);
//  yspace  = 1.1;
//  b1->DrawBox(lg_ndctox1+xspace,lg_ndctoy2-yspace,
//	      lg_ndctox1+xspace+boxsize,lg_ndctoy2-yspace-boxsize);
  return;
}
