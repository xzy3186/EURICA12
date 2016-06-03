#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TTree.h>
#include <stdio.h>
#include <stdlib.h>

void TDC_offset() {
   TFile *file = NULL;
   FILE *foff = NULL, *flog = NULL;
   TH1F *hvqx[8][60];
   TH1F *hvqy[8][40];
   TF1 *fvqx[8][60];
   TF1 *fvqy[8][40];
   int hmaxx[8][60], hbin1x[8][60], hbin2x[8][60];
   int hmaxy[8][40], hbin1y[8][40], hbin2y[8][40];
   double heightx[8][60], meanx[8][60], sigmax[8][60];
   double heighty[8][40], meany[8][40], sigmay[8][40];
   string hnamex[8][60], svqx = "vqx", svalqx;
   string hnamey[8][40], svqy = "vqy", svalqy;

   file = new TFile("../root/sistopper/WASABI1034.root");
   foff = fopen("TDC_off.dat", "w");
   flog = fopen("tdc_offset.log", "w");

   // INIT
   for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 60; j++) {
         // init arrays
         hmaxx[i][j] = hbin1x[i][j] = hbin2x[i][j] = 0;
         heightx[i][j] = meanx[i][j] = sigmax[i][j] = 0.0;

         // init histos name
         stringstream si1, sj;
         si1 << i;
         sj << j;
         if(j > 9) hnamex[i][j] = svqx + si1.str() + sj.str();
         else hnamex[i][j] = svqx + si1.str() + "0" + sj.str();

         //cout << hnamex[i][j] << endl;
      }
      for (int j = 0; j < 40; j++) {
         // init arrays
         hmaxy[i][j] = hbin1y[i][j] = hbin2y[i][j] = 0;
         heighty[i][j] = meany[i][j] = sigmay[i][j] = 0.0;

         // init histos name
         stringstream si1, sj;
         si1 << i;
         sj << j;
         if(j > 9) hnamey[i][j] = svqy + si1.str() + sj.str();
         else hnamey[i][j] = svqy + si1.str() + "0" + sj.str();

         //cout << hnamey[i][j] << endl;
      }
      //cout << endl;
   }

   // SCAN & FIT & SAVE PARAMS FROM TTREE
   for (int i = 0; i < 5; i++) {
      for (j = 0; j < 60; j++) {
         if(i==5 && j%2==1){
            continue;
         }
         // init histo
         hvqx[i][j] = new TH1F(hnamex[i][j].c_str(), hnamex[i][j].c_str(), 1000, -5000, 5000);

         // scan data from ttree file
         char varexp[40];
         sprintf(varexp, "DSSD_T[%d][%d][0]", i, j);
         char selection[40];
         sprintf(selection, "dssd_Z>=%d && dssd_X[0]==%d &&dssd_E_X[%d][%d]>6000", i, j, i, j);
         WASABI->Project(hnamex[i][j].c_str(), varexp, selection);
         //WASABI->Draw(hnamex[i][j].c_str() >>varexp, selection);

         // check histo (empty or not empty)
         double meancond = hvqx[i][j]->GetMean(1);

         if (fabs(meancond) > 0) {
            // fit
            hmaxx[i][j] = hvqx[i][j]->GetBinCenter(hvqx[i][j]->GetMaximumBin());
            hbin1x[i][j] = hmaxx[i][j] - 200;
            hbin2x[i][j] = hmaxx[i][j] + 200;
            if(hbin1x[i][j] < -5000) hbin1x[i][j] = -5000;
            printf("i#%3d j#%3d --- %3d [%3d:%3d] >>> ", i, j, hmaxx[i][j], hbin1x[i][j], hbin2x[i][j]);
            fprintf(flog,"i#%3d j#%3d --- %3d [%3d:%3d] >>> ", i, j, hmaxx[i][j], hbin1x[i][j], hbin2x[i][j]);

            char funcname[10];
            sprintf(funcname, "fvqx%d%d", i, j);
            fvqx[i][j] = new TF1(funcname, "gaus", hbin1x[i][j], hbin2x[i][j]);

            hvqx[i][j]->Fit(funcname, "Q", "", hbin1x[i][j], hbin2x[i][j]);
            heightx[i][j] = fvqx[i][j]->GetParameter(0);
            meanx[i][j] = fvqx[i][j]->GetParameter(1);
            sigmax[i][j] = fvqx[i][j]->GetParameter(2);
            printf("H = %.2lf, M = %.2lf, S = %.2lf\n", heightx[i][j], meanx[i][j], sigmax[i][j]);
            fprintf(flog,"H = %.2lf, M = %.2lf, S = %.2lf\n", heightx[i][j], meanx[i][j], sigmax[i][j]);
            if(sigmax[i][j]<150){
               fprintf(foff, "%d %d %d %d\n", i, j, int(meanx[i][j] + 0.5), int(sigmax[i][j] + 0.5));
            }else{
               fprintf(foff, "%d %d %d %d\n", i, j, int(hmaxx[i][j] + 0.5), int(sigmax[i][j] + 0.5));
            }
         }else {
            printf("i#%3d j#%3d --- %3d [%3d:%3d] >>> ", i, j, hmaxx[i][j], hbin1x[i][j], hbin2x[i][j]);
            printf("EMPTY\n");
            fprintf(flog,"i#%3d j#%3d --- %3d [%3d:%3d] >>> ", i, j, hmaxx[i][j], hbin1x[i][j], hbin2x[i][j]);
            fprintf(flog,"EMPTY\n");
         }
      }
      for (j = 0; j < 40; j++) {
         // init histo
         hvqy[i][j] = new TH1F(hnamey[i][j].c_str(), hnamey[i][j].c_str(), 1000, -5000, 5000);

         // scan data from ttree file
         char varexp[40];
         sprintf(varexp, "DSSD_T[%d][%d][0]", i, j+60);
         char selection[40];
         sprintf(selection, "dssd_Z>=%d && dssd_Y[0]==%d && dssd_E_Y[%d][%d]>6000", i, j, i, j);
         WASABI->Project(hnamey[i][j].c_str(), varexp, selection);

         // check histo (empty or not empty)
         double meancond = hvqy[i][j]->GetMean(1);

         if (meancond != 0.0) {
            // fit
            hmaxy[i][j] = hvqy[i][j]->GetBinCenter(hvqy[i][j]->GetMaximumBin());
            hbin1y[i][j] = hmaxy[i][j] - 200;
            hbin2y[i][j] = hmaxy[i][j] + 200;
            if(hbin1y[i][j] < -5000) hbin1y[i][j] = -5000;
            printf("i#%3d j#%3d --- %3d [%3d:%3d] >>> ", i, j+60, hmaxy[i][j], hbin1y[i][j], hbin2y[i][j]);
            fprintf(flog,"i#%3d j#%3d --- %3d [%3d:%3d] >>> ", i, j+60, hmaxy[i][j], hbin1y[i][j], hbin2y[i][j]);

            char funcname[10];
            sprintf(funcname, "fvqy%d%d", i, j);
            fvqy[i][j] = new TF1(funcname, "gaus", hbin1y[i][j], hbin2y[i][j]);

            hvqy[i][j]->Fit(funcname, "Q", "", hbin1y[i][j], hbin2y[i][j]);
            heighty[i][j] = fvqy[i][j]->GetParameter(0);
            meany[i][j] = fvqy[i][j]->GetParameter(1);
            sigmay[i][j] = fvqy[i][j]->GetParameter(2);
            printf("H = %.2lf, M = %.2lf, S = %.2lf\n", heighty[i][j], meany[i][j], sigmay[i][j]);
            fprintf(flog,"H = %.2lf, M = %.2lf, S = %.2lf\n", heighty[i][j], meany[i][j], sigmay[i][j]);
            if(sigmay[i][j]<150){
               fprintf(foff, "%d %d %d %d\n", i, j+60, int(meany[i][j] + 0.5), int(sigmay[i][j] + 0.5));
            }else{
               fprintf(foff, "%d %d %d %d\n", i, j+60, int(hmaxy[i][j] + 0.5), int(sigmay[i][j] + 0.5));
            }
         }else {
            printf("i#%3d j#%3d --- %3d [%3d:%3d] >>> ", i, j+60, hmaxy[i][j], hbin1y[i][j], hbin2y[i][j]);
            printf("EMPTY\n");
            fprintf(flog,"i#%3d j#%3d --- %3d [%3d:%3d] >>> ", i, j+60, hmaxy[i][j], hbin1y[i][j], hbin2y[i][j]);
            fprintf(flog,"EMPTY\n");
         }
      }
   }

   fclose(foff);
   fclose(flog);
   file->Close();
}

