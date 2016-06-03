TCutG* ZedAoQGate(Double_t zed, Double_t dzed, 
		  Double_t aoq, Double_t daoq, char *cutname){
  TCutG *cutg = new TCutG(cutname,9);
  Double_t factor=1/3.;
  cutg->SetVarX("zet");
  cutg->SetVarY("aoq");
  cutg->SetPoint(0, zed+dzed,        aoq-daoq*factor);  
  cutg->SetPoint(1, zed+dzed,        aoq+daoq*factor);  
  cutg->SetPoint(2, zed+dzed*factor, aoq+daoq);  
  cutg->SetPoint(3, zed-dzed*factor, aoq+daoq);  
  cutg->SetPoint(4, zed-dzed,        aoq+daoq*factor);  
  cutg->SetPoint(5, zed-dzed,        aoq-daoq*factor);  
  cutg->SetPoint(6, zed-dzed*factor, aoq-daoq);  
  cutg->SetPoint(7, zed+dzed*factor, aoq-daoq);  

  Double_t x, y;  
  cutg->GetPoint(0, x, y);
  cutg->SetPoint(8, x, y);  
  return cutg;
}
