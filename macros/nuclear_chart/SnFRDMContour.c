void pal2() {

  int userpalette2[50];
  //for (int i=0;i<50;i++) userpalette2[i]=100-i+2;
  for (int i=0;i<50;i++) userpalette2[i]=50+i;
  //for (int i=0;i<50;i++) cout << userpalette2[i] << endl;
  //gStyle->SetPalette(50,userpalette2,0.1);
  gStyle->SetPalette(50,userpalette2);

}


void SnFRDMContour() {
  ifstream fin; 
  fin.open("Sn_FRDM95.txt");
  double proton_oddN[5000];
  double proton_evenN[5000];
  double neutron_oddN[5000];
  double neutron_evenN[5000];
  double Sn_oddN[5000];
  double Sn_evenN[5000];
  int z,n,a;
  double sn;
  int zmin=27;
  int zmax=31;
  int nmin=47;
  int nmax=55;

  string str;
  for(int i=0;i<3;i++) getline(fin,str);

  int ieven=0,iodd=0;
  while(!fin.eof()) {
    getline(fin,str);
    if(str.size()==0) continue;
    stringstream ss;
    ss << str;
    ss >> z >> n >> a >> sn;
    if(sn<0||z<zmin||z>zmax||n<nmin||n>nmax) continue;
    if(n%2==0) {
      proton_evenN[ieven]=z;
      neutron_evenN[ieven]=n;
      Sn_evenN[ieven]=sn;
      ieven++;
    } else {
      proton_oddN[iodd]=z;
      neutron_oddN[iodd]=n;
      Sn_oddN[iodd]=sn;
      iodd++;
    }
  }
  for (int i=0;i<iodd;i++) {
    cout << proton_oddN[i] << " " << neutron_oddN[i] << " " << Sn_oddN[i] << endl;
  }

//  TGraph2D* hSnOdd = new TGraph2D(iodd,neutron_oddN,proton_oddN,Sn_oddN);
//  double levels[6] = {0.5,1,1.5,2,2.5,3};
//  hSnOdd->SetNpx(300);
//  hSnOdd->SetNpy(300);
//  hSnOdd->GetHistogram()->SetContour(6,levels);
//  hSnOdd->Draw("cont1");
  

  TH2D* h2Sn = new TH2D("h2Sn","",nmax-nmin+1,nmin-0.5,nmax+0.5,zmax-zmin+1,zmin-0.5,zmax+0.5);
  for (int i=0;i<iodd;i++) {
    h2Sn->Fill(neutron_oddN[i],proton_oddN[i],Sn_oddN[i]);
  }
  for (int i=0;i<ieven;i++) {
    h2Sn->Fill(neutron_evenN[i],proton_evenN[i],Sn_evenN[i]);
  }
  h2Sn->SetStats(0);
  h2Sn->GetZaxis()->SetRangeUser(0,100);
  h2Sn->GetZaxis()->SetNdivisions(4);
  TExec *ex2 = new TExec("ex2","pal2();");
  ex2->Draw();
  h2Sn->SetContour(15);
  h2Sn->Draw("colz same");
  c1->Update();
  TPaletteAxis *palette = (TPaletteAxis*)(h2Sn->GetListOfFunctions()->FindObject("palette"));
  palette ->SetY2NDC(0.65);
  palette ->SetLabelSize(0.1);
  ///  palette ->GetAxis()->SetNdivisions(505);
  TPaveText *pt = new TPaveText(0.82,0.73,0.98,0.96,"blNDC");
  pt->AddText("P_{n}");
  pt->SetTextFont(132);
  pt->AddText("(%)");
  pt->SetBorderSize(1);
  pt->SetLineColor(1);
  pt->SetFillColor(0);
  pt->Draw();
  TLine *l1 = new TLine();
  l1->SetLineWidth(3);
  TLatex *t1 = new TLatex();
  t1->SetTextAlign(22);
  t1->SetTextSize(0.1);
  double low, high;
  //N=50
  low=26;
  high=31.5;
  l1->SetLineColor(0);
  l1->SetLineWidth(5);
  l1->DrawLine(49.5,low,49.5,high);
  l1->DrawLine(50.5,low,50.5,high);
  //Z=28
  low = 46;
  high= 54.5;
  l1->DrawLine(low,28.5,high,28.5);
  l1->DrawLine(low,27.5,high,27.5);
  //N=50
  low=26;
  high=31.5;
  l1->SetLineColor(1);
  l1->SetLineWidth(3);
  l1->DrawLine(49.5,low,49.5,high);
  l1->DrawLine(50.5,low,50.5,high);
  t1->DrawLatex(50,low-0.5,"50");
  //Z=28
  low = 46;
  high= 54.5;
  l1->SetLineStyle(1);
  l1->SetLineColor(0);
  l1->SetLineWidth(5);
  l1->SetLineColor(1);
  l1->SetLineWidth(3);
  l1->DrawLine(low,28.5,high,28.5);
  l1->DrawLine(low,27.5,high,27.5);

//  l1->DrawLine(high,28.5,high+1,28.5);
//  l1->DrawLine(high,27.5,high+1,27.5);
//
//  l1->SetLineStyle(1);
//  l1->DrawLine(high+1,28.5,high+2,28.5);
//  l1->DrawLine(high+1,27.5,high+2,27.5);

  t1->DrawLatex(low-0.5,28,"28");

  return ;
}
