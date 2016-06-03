#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TTree.h>
#include <stdio.h>
#include <stdlib.h>

TFile *file = NULL;
FILE *ini[23], *fped = NULL, *flog = NULL, *fthr = NULL;
TH1F *hvq[23][32];
TF1 *fvq[23][32];
int hmax[23][32], hbin1[23][32], hbin2[23][32];
double height[23][32], mean[23][32], sigma[23][32];
string hname[23][32], svq = "vq", svalq;

void pedqanew3() {
	// Before running the macro, please check and modify the ROOT file name, ped and log file name!!!!!!!!!!
	//file = new TFile("../root/root_wasabi/WASABI0001.root");
	file = new TFile("../root/sistopper/WASABI0138.root");
	fped = fopen("ped0001.txt", "w");
	flog = fopen("log0001.txt", "w");
	fthr = fopen("ADC_thr.dat", "w");
	
	// INIT
	for (int i = 0; i < 23; i++) {
		// init .sh files
		char ininame[30];
		if (i < 20) sprintf(ininame, "v785ini%02d.sh", i);
		else sprintf(ininame, "madc32ini%02d.sh", i - 20);
		ini[i] = fopen(ininame, "w");
		cout << ininame << endl;
		cout << endl;

		for (int j = 0; j < 32; j++) {
			// init arrays
			hmax[i][j] = hbin1[i][j] = hbin2[i][j] = 0;
			height[i][j] = mean[i][j] = sigma[i][j] = 0.0;
			
			// init histos name
			stringstream si1, sj;
			si1 << i + 1;
			sj << j;
			if(j > 9) hname[i][j] = svq + si1.str() + sj.str();
			else hname[i][j] = svq + si1.str() + "0" + sj.str();

			cout << hname[i][j] << endl;
		}
		cout << endl;
	}

	// SCAN & FIT & SAVE PARAMS FROM TTREE
	for (int i = 0; i < 23; i++) {
		// init header of .sh files
		// v785ini
		if (i < 20) {
			fprintf(ini[i], "#!/bin/sh\n");
			if (i < 16) fprintf(ini[i], "BASEADDR=0x000%x\n", i);
			else fprintf(ini[i], "BASEADDR=0x00%x\n", i);
			fprintf(ini[i], "#ADC1\n");
			fprintf(ini[i], "/usr/nbbq/bin/cmdvme -am 0x9\n");
			fprintf(ini[i], "# GEO address\n");
			fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}1002 %d\n", i+3);
			fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}1016 0x01\n");
			fprintf(ini[i], "# Iterrupt level; OFF = 0\n");
			fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}100a 0x0\n");
			fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}1020 0x1\n");
			fprintf(ini[i], "# Bit 2 Clear register\n");
			fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}1034 0x011c\n");
			fprintf(ini[i], "# Bit 2 Set register\n");
			fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}1032 0x0108\n");
			fprintf(ini[i], "# Lower Threshold:Base Address + 0x1080 + Ch# * 2\n");
		}
		// madc32ini
		else {
			fprintf(ini[i], "#!/bin/sh\n");
			fprintf(ini[i], "#\n# MADC32 01\n#\n");
			fprintf(ini[i], "BASEADDR=0x00%x\n", i);
			fprintf(ini[i], "# MADC32\n");
			fprintf(ini[i], "/usr/nbbq/bin/cmdvme -am 0x9\n");
			fprintf(ini[i], "# Soft RESET\n");
			fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}6008 0x01\n");
			fprintf(ini[i], "# Module ID\n");
			fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}6004 %d\n", i + 3);
			fprintf(ini[i], "# Iterrupt level; OFF = 0\n");
			fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}6010 0x0\n");
			fprintf(ini[i], "# ADC resolution\n");
			fprintf(ini[i], "# 0 : 2k\n");
			fprintf(ini[i], "# 1 : 4k\n");
			fprintf(ini[i], "# 2 : 4k hires\n");
			fprintf(ini[i], "# 3 : 8k\n");
			fprintf(ini[i], "# 4 : 8k hires\n");
			fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}6042 0x2\n");
			fprintf(ini[i], "\n");
			fprintf(ini[i], "# Input range\n");
			fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}6060 0x0\n");
			fprintf(ini[i], "\n");
			fprintf(ini[i], "# Lower Threshold:Base Address + 0x4000 + Ch# * 2\n");
		}

		fprintf(fped, "%d 32\n", i);

		for (j = 0; j < 32; j++) {
			// init histo
			hvq[i][j] = new TH1F(hname[i][j].c_str(), hname[i][j].c_str(), 500, 0, 500);

			// scan data from ttree file
			char varexp[40];
			sprintf(varexp, "ADC[%d][%d]", i, j);
			char selection[40];
			sprintf(selection, "ADC[%d][%d]>0", i, j);
			WASABI->Project(hname[i][j].c_str(), varexp, selection);

			// check histo (empty or not empty)
			double meancond = hvq[i][j]->GetMean(1);

			if (meancond > 0.0) {
				// fit
				hmax[i][j] = hvq[i][j]->GetMaximumBin();
				hbin1[i][j] = hmax[i][j] - 100;
				hbin2[i][j] = hmax[i][j] + 100;
				if(hbin1[i][j] < 0) hbin1[i][j] = 0;
				printf("i#%3d j#%3d --- %3d [%3d:%3d] >>> ", i, j, hmax[i][j], hbin1[i][j], hbin2[i][j]);
				fprintf(flog, "i#%3d j#%3d --- %3d [%3d:%3d] >>> ", i, j, hmax[i][j], hbin1[i][j], hbin2[i][j]);

				char funcname[10];
				sprintf(funcname, "fvq%d%d", i, j);
				fvq[i][j] = new TF1(funcname, "gaus", hbin1[i][j], hbin2[i][j]);

				hvq[i][j]->Fit(funcname, "Q", "", hbin1[i][j], hbin2[i][j]);
				height[i][j] = fvq[i][j]->GetParameter(0);
				mean[i][j] = fvq[i][j]->GetParameter(1);
				sigma[i][j] = fvq[i][j]->GetParameter(2);
				printf("H = %.2lf, M = %.2lf, S = %.2lf\n", height[i][j], mean[i][j], sigma[i][j]);
				fprintf(flog, "H = %.2lf, M = %.2lf, S = %.2lf\n", height[i][j], mean[i][j], sigma[i][j]);

				fprintf(fped, "%d %d %d\n", j, int(mean[i][j] + 0.5), int(2.0 * sigma[i][j] + 0.5));
				fprintf(fthr, "%d %d %d\n", i, j, int(mean[i][j] + 0.5)+int(2.0 * sigma[i][j] + 0.5));

				if (i < 20) fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}10%x %d\n", 128 + (j * 2), int((mean[i][j]+2.0*sigma[i][j])/2.+0.5));
				else {
					if (j * 2 < 16) fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}400%x %d\n", (j * 2), int((mean[i][j]+2.0*sigma[i][j])));
					else            fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}40%x %d\n", (j * 2), int((mean[i][j]+2.0*sigma[i][j])));
				}
			}
			else {
				printf("i#%3d j#%3d --- %3d [%3d:%3d] >>> ", i, j, hmax[i][j], hbin1[i][j], hbin2[i][j]);
				fprintf(flog, "i#%3d j#%3d --- %3d [%3d:%3d] >>> ", i, j, hmax[i][j], hbin1[i][j], hbin2[i][j]);
				printf("EMPTY\n");
				fprintf(flog, "EMPTY\n");
				if (i < 20) fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}10%x %d\n", 128 + (j * 2), 0);
				else {
					if (j * 2 < 16) fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}400%x %d\n", (j * 2), 0);
					else            fprintf(ini[i], "/usr/nbbq/bin/cmdvme -ww ${BASEADDR}40%x %d\n", (j * 2), 0);
				}
			}
		}
		fclose(ini[i]);
	}

	fclose(fped);
	fclose(fthr);
	fclose(flog);
}

