//set name for fitting parameters
void roofit_parname(int index, TString &parname){
   switch(index){
      case 0:
         parname="X0";
         break;
      case 1:
         parname="pn";
         break;
      case 2:
         parname="p2n";
         break;
      case 3:
         parname="t11";
         break;
      case 4:
         parname="t12";
         break;
      case 5:
         parname="pnd";
         break;
      case 6:
         parname="t21";
         break;
      case 7:
         parname="t22";
         break;
      case 8:
         parname="t31";
         break;
      case 9:
         parname="t32";
         break;
      case 10:
         parname="pnbnd";
         break;
      case 11:
         parname="t51";
         break;
      case 12:
         parname="t52";
         break;
      case 13:
         parname="t61";
         break;
      case 14:
         parname="t62";
         break;
      case 15:
         parname="t81";
         break;
      case 16:
         parname="t82";
         break;
      case 17:
         parname="C";
         break;
      case 18:
         parname="p12";
         break;
      case 19:
         parname="p22";
         break;
      case 20:
         parname="p32";
         break;
      case 21:
         parname="p52";
         break;
      case 22:
         parname="p62";
         break;
      case 23:
         parname="p82";
         break;
   }
}

RooRealVar *par[24];

void read_roofit_parameters(TString name){
   TString decayfilename;
   decayfilename="decay_db/";
   decayfilename+=name;
   decayfilename+=".input";
   FILE *fp = fopen(decayfilename, "r");
   int n;
   double parameter, parameterL, parameterU;
   for(int i=0; i<18; i++){
      fscanf(fp, "%d %lf %lf %lf", &n, &parameter, &parameterL, &parameterU);
      cout<<n<<", "<<parameter<<", "<<parameterL<<", "<<parameterU<<endl;
      if(i==0){
         parameter=1;
         parameterL=0;
         parameterU=0;
      }
      if(i==17){
         parameter=0.5;
         parameterL=0.5;
         parameterU=0.5;
      }
      TString parname;
      roofit_parname(i,parname);
      par[i]=new RooRealVar(parname,parname,parameter,parameter-parameterL,parameter+parameterU);
      for(int j=0; j<6; j++){
         int temp;
         if(j==0) temp=4;
         if(j==1) temp=7;
         if(j==2) temp=9;
         if(j==3) temp=12;
         if(j==4) temp=14;
         if(j==5) temp=16;
         if(n == temp){
            roofit_parname(18+j,parname);
            if(parameter!=0){
               par[18+j]=new RooRealVar(parname,parname,0.5,0,1);
            }else{
               par[18+j]=new RooRealVar(parname,parname,0,0,0);
            }
         }
      }
   }
   fclose(fp);
}

//read fitting parameters from a text file (named as something like decay_db/ni78.input)
void read_roofit_parameters(TString name){
   TString decayfilename;
   decayfilename="decay_db/";
   decayfilename+=name;
   decayfilename+=".input";
   FILE *fp = fopen(decayfilename, "r");
   int n;
   double parameter, parameterL, parameterU;
   for(int i=0; i<18; i++){
      fscanf(fp, "%d %lf %lf %lf", &n, &parameter, &parameterL, &parameterU);
      cout<<n<<", "<<parameter<<", "<<parameterL<<", "<<parameterU<<endl;
      if(i==0){
         parameter=1;
         parameterL=0;
         parameterU=0;
      }
      if(i==17){
         parameter=0.5;
         parameterL=0.5;
         parameterU=0.5;
      }
      TString parname;
      roofit_parname(i,parname);
      par[i]=new RooRealVar(parname,parname,parameter,parameter-parameterL,parameter+parameterU);
      for(int j=0; j<6; j++){
         int temp;
         if(j==0) temp=4;
         if(j==1) temp=7;
         if(j==2) temp=9;
         if(j==3) temp=12;
         if(j==4) temp=14;
         if(j==5) temp=16;
         if(n == temp){
            roofit_parname(18+j,parname);
            if(parameter!=0){
               par[18+j]=new RooRealVar(parname,parname,0.5,0,1);
            }else{
               par[18+j]=new RooRealVar(parname,parname,0,0,0);
            }
         }
      }
   }
   fclose(fp);
}

void roofit_decay(int Z, int A, int time_bin=400, double Dtime_L=5, double Dtime_U=4005){
   if(gROOT->FindObject("c1")==0){
      TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,500);
   }
   //define canvas
   c1->Divide(1,1);
   c1->cd();
   c1->SetLogy(1);
   c1->SetGridx(0);
   c1->SetGridy(0);
   c1->SetRightMargin(0.06);
   c1->SetTopMargin(0.06);
   c1->SetLeftMargin(0.14);
   c1->SetBottomMargin(0.14);
   c1->Draw();
   //define filename to be read for fitting parameters
   TString name;
   name_nuclei(Z,A,name);
   //define variable in the fitting function (t in this case)
   RooRealVar t("t","t",Dtime_L,Dtime_U,"ms");
   //define name of fitting parameters
   read_roofit_parameters(name);
   cout<<"come here"<<endl;
   //define a roofit function
   RooMyDecay* roofit_decay = new RooMyDecay("roofit_decay","roofit_decay",t,*par[0],*par[1],*par[2],*par[3],*par[4],*par[5],*par[6],*par[7],*par[8],*par[9],*par[10],*par[11],*par[12],*par[13],*par[14],*par[15],*par[16],*par[17],*par[18],*par[19],*par[20],*par[21],*par[22],*par[23]);
   //define input filename containing sample that need to be fitted
   TString decayfilename;
   decayfilename="decay_db/";
   decayfilename+=name;
   //read the file of samples
   RooDataSet* data=RooDataSet::read(decayfilename,RooArgList(t));
   RooPlot* xframe = t.frame(Title(" "));
   //perform the fit
   RooFitResult* fitres = roofit_decay->fitTo(*data, Minos(kTRUE)) ;
   //plot the fitted figure
   data->plotOn(xframe,Binning(time_bin));
   roofit_decay->plotOn(xframe);
   xframe->Draw();
   //print some fitting info to the figure
   TLatex text1, text2;
   TString content1, content2;
   TString content0, content1, content2;
   char text_half[100];
   char text_errorH[100];
   char text_errorL[100];
   char text_pn[100];
   sprintf(text_half,"%.1f",par[3]->getVal());
   sprintf(text_errorH,"%.1f",par[3]->getAsymErrorHi());
   sprintf(text_errorL,"%.1f",par[3]->getAsymErrorLo());
   sprintf(text_pn,"%.1f",par[1]->getValV()*100);
   content1="T_{1/2}";
   //content+=name;
   content1+=" = ";
   content1+=text_half;
   content1+=" ^{+";
   content1+=text_errorH;
   content1+="}_{";
   content1+=text_errorL;
   content1+="} ms";
   //content2="P_{n} = ";
   //content2+=text_pn;
   //content2+=" %";
   name_nuclei_latex(Z,A,content2);
   content0 +="#beta-decay of";
   content0 +=content2;
   text1.SetTextAlign(12);
   text1.SetTextSize(0.08);
   text1.SetNDC(kTRUE);
   //text1.DrawLatex(.5,.7,content1);
   cout<<content1<<endl;
   text2.SetTextAlign(12);
   text2.SetTextSize(0.08);
   text2.SetNDC(kTRUE);
   text2.DrawLatex(.5,.8,content0);
}
