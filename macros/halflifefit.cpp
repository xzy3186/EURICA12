/****************************************************************/
/* This is a ROOT macro for fitting half-life curves.  The      */
/* input file is a .top file, which can be up to 10000 lines    */
/* long.  Longer, and hacking the code would be required.  The  */
/* program has a GUI interface, and should warn you about       */
/* most common errors.  There are a number of fitting options,  */
/* which require various degrees of input.                      */
/*    Last edited: H.Crawford 05/30/2008                        */
/****************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <TH1D.h> 
#include <TMath.h> 
#include <TGClient.h>
#include <TGCanvas.h> 
#include <TF1.h> 
#include <TRandom.h>  
#include <TGButton.h> 
#include <TGComboBox.h>
#include <TGFrame.h> 
#include <TRootEmbeddedCanvas.h> 
#include <RQ_OBJECT.h> 
#include <TGNumberEntry.h> 

// Define global fitting and control variables

double GRANDDAUGHTER = 0; 
double DAUGHTER_ONENEUTRON = 0;
double DAUGHTER_TWONEUTRON = 0; 
double ONE_NEUTRON = 0;
double TWO_NEUTRON = 0; 
double NO_NEUTRON = 1; 

double LIFE_LOW_LIMIT = 0.001; 
double LIFE_HIGH_LIMIT = 10.0; 
double LIFE_GUESS = 5; 

double DAUGHTER_LOW_LIMIT = 0;
double DAUGHTER_HIGH_LIMIT = 50000;
double DAUGHTER_GUESS = 0;

double BACKLIN_LOW_LIMIT = 0;
double BACKLIN_HIGH_LIMIT = 50000;
double BACKLIN_GUESS = 100;

double EXPINIT_GUESS = 0;
double EXPINIT_LOW_LIMIT = 0;
double EXPINIT_HIGH_LIMIT = 50000;

double EXPDECAY_GUESS = 0;
double EXPDECAY_LOW_LIMIT = 0;
double EXPDECAY_HIGH_LIMIT = 50000;

double INITIAL_LOW_LIMIT = 1;
double INITIAL_HIGH_LIMIT = 50000;
double INITIAL_GUESS = 100;

double COMPONENT2_GUESS = 1.0;
double COMPONENT2_LOW_LIMIT = 0.001;
double COMPONENT2_HIGH_LIMIT = 2.0;
double COMPONENT2_FRACTION = 0.5;
double COMPONENT2_FRACTION_LOW_LIMIT = 0;
double COMPONENT2_FRACTION_HIGH_LIMIT = 1;

bool DAUGHTER_FREE = 0; 
bool EXPDECAY_FREE = 0;
bool FRACTION_FREE = 0;
bool TWOCOMP = 0;
bool COMPONE_FREE = 0;
bool COMPTWO_FREE = 0;
bool LINEAR = 0;
bool EXP = 0;

char* FILENAME = 0;

double BIN[100000] = {0};
int DATA[100000] = {0};
int COUNT = 0;

int DRAW_CONTROL = 0;

/****************************************************************/
/* These are the Bateman equations that are used to fit the     */
/* half-life curves.                                            */
/****************************************************************/

Double_t background_linear (Double_t *x, Double_t *par) {
   return par[3];
}

Double_t background_exp (Double_t *x, Double_t *par) {
   return par[4]*(TMath::Exp(-par[5]*x[0]));
}

Double_t parent (Double_t *x, Double_t *par) {
   if (par[1] != 0) {
      return par[0]*(TMath::Exp(-((0.69314718)/par[1])*x[0]));
   } else {
      return 0;
   }
}

Double_t two_component (Double_t *x, Double_t *par) {
   if (par[1] != 0 && par[12] != 0) {
      return par[0]*(par[11]*(TMath::Exp(-((0.69314718)/par[12])*x[0])) + (1-par[11])*(TMath::Exp(-((0.69314718)/par[1])*x[0])));
   } else if (par[1] != 0 && par[12] == 0) {
      return par[0]*(1-par[11])*(TMath::Exp(-((0.69314718)/par[1])*x[0]));
   } else if (par[12] != 0 && par[1] == 0) {
      return par[0]*(par[11]*(TMath::Exp(-((0.69314718)/par[12]*x[0]))));
   } else {
      return 0;
   }
}

Double_t twocomponentfit (Double_t *x, Double_t *par) {
   return two_component(x, par);
}

Double_t component1 (Double_t *x, Double_t *par) {
   if (par[0] != 0) {
      return par[0]*(1-par[11])*(TMath::Exp(-((0.69314718)/par[1])*x[0]));
   } else {
      return 0;
   }
}

Double_t component2 (Double_t *x, Double_t *par) {
   if (par[12] != 0) {
      return par[0]*par[11]*(TMath::Exp(-((0.69314718)/par[12])*x[0]));
   } else {
      return 0;
   }
}

Double_t daughter_only (Double_t *x, Double_t *par) {
   if (((0.69314718)/par[1]) != ((0.69314718)/par[2])) {
      return par[0]*(NO_NEUTRON)*(((0.69314718)/par[2])/(((0.69314718)/par[2]) - ((0.69314718)/par[1])))*
         ((TMath::Exp(-((0.69314718)/par[1])*x[0])) - (TMath::Exp(-((0.69314718)/par[2])*x[0])));
   } else if (((0.69314718)/par[1]) == ((0.69314718)/par[2])) {
      return par[0]*(NO_NEUTRON)*(((0.69314718)/par[2])/(0.0000001))*
         ((TMath::Exp(-((0.69314718)/par[1])*x[0])) - (TMath::Exp(-((0.69314718)/par[2])*x[0])));
   }
}

Double_t component_1_daughter_only (Double_t *x, Double_t *par) {
   if (((0.69314718)/par[1]) != ((0.69314718)/par[2])) {
      return par[0]*(1-par[11])*(NO_NEUTRON)*(((0.69314718)/par[2])/(((0.69314718)/par[2]) - ((0.69314718)/par[1])))*
         ((TMath::Exp(-((0.69314718)/par[1])*x[0])) - (TMath::Exp(-((0.69314718)/par[2])*x[0])));
   } else if (((0.69314718)/par[1]) == ((0.69314718)/par[2])) {
      return par[0]*(1-par[11])*(NO_NEUTRON)*(((0.69314718)/par[2])/(0.0000001))*
         ((TMath::Exp(-((0.69314718)/par[1])*x[0])) - (TMath::Exp(-((0.69314718)/par[2])*x[0])));
   }
}

Double_t component_2_daughter_only (Double_t *x, Double_t *par) {
   if (((0.69314718)/par[12]) != ((0.69314718)/par[2])) {
      return par[11]*par[0]*(NO_NEUTRON)*(((0.69314718)/par[2])/(((0.69314718)/par[2]) - ((0.69314718)/par[12])))*
         ((TMath::Exp(-((0.69314718)/par[12])*x[0])) - (TMath::Exp(-((0.69314718)/par[2])*x[0])));
   } else if (((0.69314718)/par[12]) == ((0.69314718)/par[2])) {
      return par[11]*par[0]*(NO_NEUTRON)*(((0.69314718)/par[2])/(0.0000001))*
         ((TMath::Exp(-((0.69314718)/par[12])*x[0])) - (TMath::Exp(-((0.69314718)/par[2])*x[0])));
   }
}

Double_t daughter_two_component (Double_t *x, Double_t *par) {
   return component_1_daughter_only(x, par) + component_2_daughter_only(x, par);
}

Double_t granddaughter (Double_t *x, Double_t *par) {
   if (((0.69314718)/par[1]) != ((0.69314718)/par[2]) && ((0.69314718)/par[6]) != ((0.69314718)/par[1]) && ((0.69314718)/par[6]) != ((0.69314718)/par[2])) {
      return par[0]*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((((0.69314718)/par[1]) - ((0.69314718)/par[6]))*(((0.69314718)/par[2]) - ((0.69314718)/par[6])))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((((0.69314718)/par[1]) - ((0.69314718)/par[2]))*(((0.69314718)/par[6]) - ((0.69314718)/par[2])))) +
          ((TMath::Exp(-((0.69314718)/par[1])*x[0]))/((((0.69314718)/par[2]) - ((0.69314718)/par[1]))*
             (((0.69314718)/par[6]) - ((0.69314718)/par[1])))));
   } else if (((0.69314718)/par[1]) != ((0.69314718)/par[2]) && ((0.69314718)/par[6]) == ((0.69314718)/par[1]) && ((0.69314718)/par[6]) != ((0.69314718)/par[2])) {
      return par[0]*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((0.0000001)*(((0.69314718)/par[2]) - ((0.69314718)/par[6])))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((((0.69314718)/par[1]) - ((0.69314718)/par[2]))*(((0.69314718)/par[6]) - ((0.69314718)/par[2])))) +
          ((TMath::Exp(-((0.69314718)/par[1])*x[0]))/((((0.69314718)/par[2]) - ((0.69314718)/par[1]))*
             (0.0000001))));
   } else if (((0.69314718)/par[1]) != ((0.69314718)/par[2]) && ((0.69314718)/par[6]) != ((0.69314718)/par[1]) && ((0.69314718)/par[6]) == ((0.69314718)/par[2])) {
      return par[0]*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((((0.69314718)/par[1]) - ((0.69314718)/par[6]))*(0.0000001))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((((0.69314718)/par[1]) - ((0.69314718)/par[2]))*(0.0000001))) +
          ((TMath::Exp(-((0.69314718)/par[1])*x[0]))/((((0.69314718)/par[2]) - ((0.69314718)/par[1]))*
             (((0.69314718)/par[6]) - ((0.69314718)/par[2])))));
   } else if (((0.69314718)/par[1]) == ((0.69314718)/par[2]) && ((0.69314718)/par[6]) != ((0.69314718)/par[1]) && ((0.69314718)/par[6]) != ((0.69314718)/par[2])) {
      return par[0]*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((((0.69314718)/par[1]) - ((0.69314718)/par[6]))*(((0.69314718)/par[2]) - ((0.69314718)/par[6])))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((0.0000001)*(((0.69314718)/par[6]) - ((0.69314718)/par[1])))) +
          ((TMath::Exp(-((0.69314718)/par[1])*x[0]))/((0.0000001)*
             (((0.69314718)/par[6]) - ((0.69314718)/par[1])))));
   } else if (((0.69314718)/par[1]) == ((0.69314718)/par[2]) && ((0.69314718)/par[6]) == ((0.69314718)/par[1]) && ((0.69314718)/par[6]) == ((0.69314718)/par[2])) {
      return par[0]*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((0.0000001)*(0.0000001))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((0.0000001)*(0.0000001))) +
          ((TMath::Exp(-((0.69314718)/par[1])*x[0]))/((0.0000001)*
             (0.0000001))));
   }
}

Double_t component1_granddaughter (Double_t *x, Double_t *par) {
   if (((0.69314718)/par[1]) != ((0.69314718)/par[2]) && ((0.69314718)/par[6]) != ((0.69314718)/par[1]) && ((0.69314718)/par[6]) != ((0.69314718)/par[2])) {
      return par[0]*(1-par[11])*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((((0.69314718)/par[1]) - ((0.69314718)/par[6]))*(((0.69314718)/par[2]) - ((0.69314718)/par[6])))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((((0.69314718)/par[1]) - ((0.69314718)/par[2]))*(((0.69314718)/par[6]) - ((0.69314718)/par[2])))) +
          ((TMath::Exp(-((0.69314718)/par[1])*x[0]))/((((0.69314718)/par[2]) - ((0.69314718)/par[1]))*
             (((0.69314718)/par[6]) - ((0.69314718)/par[1])))));
   } else if (((0.69314718)/par[1]) != ((0.69314718)/par[2]) && ((0.69314718)/par[6]) == ((0.69314718)/par[1]) && ((0.69314718)/par[6]) != ((0.69314718)/par[2])) {
      return par[0]*(1-par[11])*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((0.0000001)*(((0.69314718)/par[2]) - ((0.69314718)/par[6])))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((((0.69314718)/par[1]) - ((0.69314718)/par[2]))*(((0.69314718)/par[6]) - ((0.69314718)/par[2])))) +
          ((TMath::Exp(-((0.69314718)/par[1])*x[0]))/((((0.69314718)/par[2]) - ((0.69314718)/par[1]))*
             (0.0000001))));
   } else if (((0.69314718)/par[1]) != ((0.69314718)/par[2]) && ((0.69314718)/par[6]) != ((0.69314718)/par[1]) && ((0.69314718)/par[6]) == ((0.69314718)/par[2])) {
      return par[0]*(1-par[11])*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((((0.69314718)/par[1]) - ((0.69314718)/par[6]))*(0.0000001))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((((0.69314718)/par[1]) - ((0.69314718)/par[2]))*(0.0000001))) +
          ((TMath::Exp(-((0.69314718)/par[1])*x[0]))/((((0.69314718)/par[2]) - ((0.69314718)/par[1]))*
             (((0.69314718)/par[6]) - ((0.69314718)/par[2])))));
   } else if (((0.69314718)/par[1]) == ((0.69314718)/par[2]) && ((0.69314718)/par[6]) != ((0.69314718)/par[1]) && ((0.69314718)/par[6]) != ((0.69314718)/par[2])) {
      return par[0]*(1-par[11])*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((((0.69314718)/par[1]) - ((0.69314718)/par[6]))*(((0.69314718)/par[2]) - ((0.69314718)/par[6])))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((0.0000001)*(((0.69314718)/par[6]) - ((0.69314718)/par[1])))) +
          ((TMath::Exp(-((0.69314718)/par[1])*x[0]))/((0.0000001)*
             (((0.69314718)/par[6]) - ((0.69314718)/par[1])))));
   } else if (((0.69314718)/par[1]) == ((0.69314718)/par[2]) && ((0.69314718)/par[6]) == ((0.69314718)/par[1]) && ((0.69314718)/par[6]) == ((0.69314718)/par[2])) {
      return par[0]*(1-par[11])*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((0.0000001)*(0.0000001))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((0.0000001)*(0.0000001))) +
          ((TMath::Exp(-((0.69314718)/par[1])*x[0]))/((0.0000001)*
             (0.0000001))));
   }
}

Double_t component2_granddaughter (Double_t *x, Double_t *par) {
   if (((0.69314718)/par[12]) != ((0.69314718)/par[2]) && ((0.69314718)/par[6]) != ((0.69314718)/par[12]) && ((0.69314718)/par[6]) != ((0.69314718)/par[2])) {
      return par[0]*par[11]*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((((0.69314718)/par[12]) - ((0.69314718)/par[6]))*(((0.69314718)/par[2]) - ((0.69314718)/par[6])))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((((0.69314718)/par[12]) - ((0.69314718)/par[2]))*(((0.69314718)/par[6]) - ((0.69314718)/par[2])))) +
          ((TMath::Exp(-((0.69314718)/par[12])*x[0]))/((((0.69314718)/par[2]) - ((0.69314718)/par[12]))*
             (((0.69314718)/par[6]) - ((0.69314718)/par[12])))));
   } else if (((0.69314718)/par[12]) != ((0.69314718)/par[2]) && ((0.69314718)/par[6]) == ((0.69314718)/par[12]) && ((0.69314718)/par[6]) != ((0.69314718)/par[2])) {
      return par[0]*par[11]*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((0.0000001)*(((0.69314718)/par[2]) - ((0.69314718)/par[6])))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((((0.69314718)/par[12]) - ((0.69314718)/par[2]))*(((0.69314718)/par[6]) - ((0.69314718)/par[2])))) +
          ((TMath::Exp(-((0.69314718)/par[12])*x[0]))/((((0.69314718)/par[2]) - ((0.69314718)/par[12]))*
             (0.0000001))));
   } else if (((0.69314718)/par[12]) != ((0.69314718)/par[2]) && ((0.69314718)/par[6]) != ((0.69314718)/par[12]) && ((0.69314718)/par[6]) == ((0.69314718)/par[2])) {
      return par[0]*par[11]*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((((0.69314718)/par[12]) - ((0.69314718)/par[6]))*(0.0000001))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((((0.69314718)/par[12]) - ((0.69314718)/par[2]))*(0.0000001))) +
          ((TMath::Exp(-((0.69314718)/par[12])*x[0]))/((((0.69314718)/par[2]) - ((0.69314718)/par[12]))*
             (((0.69314718)/par[6]) - ((0.69314718)/par[2])))));
   } else if (((0.69314718)/par[12]) == ((0.69314718)/par[2]) && ((0.69314718)/par[6]) != ((0.69314718)/par[12]) && ((0.69314718)/par[6]) != ((0.69314718)/par[2])) {
      return par[0]*par[11]*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((((0.69314718)/par[12]) - ((0.69314718)/par[6]))*(((0.69314718)/par[2]) - ((0.69314718)/par[6])))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((0.0000001)*(((0.69314718)/par[6]) - ((0.69314718)/par[12])))) +
          ((TMath::Exp(-((0.69314718)/par[12])*x[0]))/((0.0000001)*
             (((0.69314718)/par[6]) - ((0.69314718)/par[12])))));
   } else if (((0.69314718)/par[12]) == ((0.69314718)/par[2]) && ((0.69314718)/par[6]) == ((0.69314718)/par[12]) && ((0.69314718)/par[6]) == ((0.69314718)/par[2])) {
      return par[0]*par[11]*(((0.69314718)/par[2]))*(((0.69314718)/par[6]))*
         (((TMath::Exp(-((0.69314718)/par[6])*x[0]))/
           ((0.0000001)*(0.0000001))) +
          ((TMath::Exp(-((0.69314718)/par[2])*x[0]))/
           ((0.0000001)*(0.0000001))) +
          ((TMath::Exp(-((0.69314718)/par[12])*x[0]))/((0.0000001)*
             (0.0000001))));
   }
}

Double_t granddaughter_two_component (Double_t *x, Double_t *par) {
   return component1_granddaughter(x, par) + component2_granddaughter(x, par);
}

Double_t oneneutron_daughter (Double_t *x, Double_t *par) {
   if (par[7] != 0) {
      return par[0]*par[9]*(((0.69314718)/par[7])/
            (((0.69314718)/par[7]) - ((0.69314718)/par[1])))*
         ((TMath::Exp(-((0.69314718)/par[1])*x[0])) - (TMath::Exp(-((0.69314718)/par[7])*x[0])));
   } else {
      return 0;
   }
}

Double_t twoneutron_daughter (Double_t *x, Double_t *par) {
   if (par[8] != 0) {
      return par[0]*par[10]*(((0.69314718)/par[8])/
            (((0.69314718)/par[8]) - ((0.69314718)/par[1])))*
         ((TMath::Exp(-((0.69314718)/par[1])*x[0])) - (TMath::Exp(-((0.69314718)/par[8])*x[0])));
   } else {
      return 0;
   }
}

Double_t parent_lin (Double_t *x, Double_t *par) {
   return parent(x, par) + background_linear(x, par);
}

Double_t parent_exp (Double_t *x, Double_t *par) {
   return parent(x, par) + background_exp(x, par);
}

Double_t parent_both (Double_t *x, Double_t *par) {
   return parent(x, par) + background_linear(x, par) + 
      background_exp(x, par);
}

Double_t two_component_lin (Double_t *x, Double_t *par) {
   return two_component(x, par) + background_linear(x, par);
}

Double_t two_component_exp (Double_t *x, Double_t *par) {
   return two_component(x, par) + background_exp(x, par);
}

Double_t two_component_both (Double_t *x, Double_t *par) {
   return two_component(x, par) + background_linear(x, par) + 
      background_exp(x, par);
}

Double_t two_component_daughter (Double_t *x, Double_t *par) {
   return two_component(x, par) + daughter_two_component(x, par);
}

Double_t two_component_daughter_lin (Double_t *x, Double_t *par) {
   return two_component(x, par) + daughter_two_component(x, par) + 
      background_linear(x, par);
}

Double_t two_component_daughter_exp (Double_t *x, Double_t *par) {
   return two_component(x, par) + daughter_two_component(x, par) +
      background_exp(x, par);
}

Double_t two_component_daughter_both (Double_t *x, Double_t *par) {
   return two_component(x, par) + daughter_two_component(x, par) + 
      background_linear(x, par) + background_exp(x, par);
}

Double_t two_component_granddaughter (Double_t *x, Double_t *par) {
   return two_component(x, par) + daughter_two_component(x, par) + 
      granddaughter_two_component(x, par);
}

Double_t two_component_granddaughter_lin (Double_t *x, Double_t *par) {
   return two_component(x, par) + daughter_two_component(x, par) +
      granddaughter_two_component(x, par) + background_linear(x, par);
}

Double_t two_component_granddaughter_exp (Double_t *x, Double_t *par) {
   return two_component(x, par) + daughter_two_component(x, par) +
      granddaughter_two_component(x, par) + background_exp(x, par);
}

Double_t two_component_granddaughter_both (Double_t *x, Double_t *par) {
   return two_component(x, par) + daughter_two_component(x, par) + 
      granddaughter_two_component(x, par) + background_linear(x, par) + 
      background_exp(x, par);
}

Double_t parent_daughter (Double_t *x, Double_t *par) {
   return parent(x, par) + daughter_only(x, par);
}

Double_t parent_daughter_lin (Double_t *x, Double_t *par) {
   return parent_daughter(x, par) + background_linear(x, par);
}

Double_t parent_daughter_exp (Double_t *x, Double_t *par) {
   return parent_daughter(x, par) + background_exp(x, par);
}

Double_t parent_daughter_both (Double_t *x, Double_t *par) {
   return parent_daughter(x, par) + background_linear(x, par) + 
      background_exp(x, par);
}

Double_t parent_granddaughter (Double_t *x, Double_t *par) {
   return parent_daughter(x, par) + granddaughter(x, par);
}

Double_t parent_granddaughter_lin (Double_t *x, Double_t *par) {
   return parent_daughter(x, par) + granddaughter(x, par) + 
      background_linear(x, par);
}

Double_t parent_granddaughter_exp (Double_t *x, Double_t *par) {
   return parent_daughter(x, par) + granddaughter(x, par) + 
      background_exp(x, par);
}

Double_t parent_granddaughter_both (Double_t *x, Double_t *par) {
   return parent_daughter(x, par) + granddaughter(x, par) + 
      background_linear (x, par) + background_exp(x, par);
}

Double_t parent_neutronbranch (Double_t *x, Double_t *par) {
   return parent(x, par) + daughter_only(x, par) + oneneutron_daughter(x, par) 
      + twoneutron_daughter(x, par);
}

Double_t parent_neutronbranch_lin (Double_t *x, Double_t *par) {
   return parent_neutronbranch(x, par) + background_linear(x, par);
}

Double_t parent_neutronbranch_exp (Double_t *x, Double_t *par) {
   return parent_neutronbranch(x, par) + background_exp(x, par);
}

Double_t parent_neutronbranch_both (Double_t *x, Double_t *par) {
   return parent_neutronbranch(x, par) + background_linear(x, par) +
      background_exp(x, par);
}

/****************************************/
/*  Parameter # Key                     */
/****************************************/
/*   ###    Meaning                     */
/*    0     Initial activity            */
/*    1     Parent halflife             */
/*    2     Daughter halflife           */
/*    3     Linear bckgrnd              */
/*    4     Exp. bckgrnd initial value  */
/*    5     Exp. bckgrnd decay constant */
/*    6     Granddaughter halflife      */
/*    7     Beta-1n daughter halflife   */
/*    8     Beta-2n daughter halflife   */
/*    9     Beta-1n branching ratio     */
/*    10    Beta-2n branching ratio     */
/*    11    2nd component fraction      */
/*    12    2nd component halflife      */
/****************************************/

/****************************************************************/
/* This is the definitionsr all of the GUI classes,          */
/* including the main window, and all of the pop-up data entry  */
/* windows.                                                     */
/****************************************************************/

// This is the main class, where the plots are drawn, and all the really 
// cool stuff happens.

class Fitter {
   RQ_OBJECT("Fitter")

   private:
      TGMainFrame         *fMain;
      TRootEmbeddedCanvas *fFitCanvas;
      TGVerticalFrame     *left, *right;
      TGHorizontalFrame   *hframe, *guesslimitFrame, *lowlimitFrame, 
                          *highlimitFrame, *hframe2, *hframe3, *hframe4, 
                          *hframe5, *hframe6, *hframe7, *hframe8, *timeframe,
                          *lowrangeFrame, *yminFrame;
      TGGroupFrame        *group, *group2, *group3, *group4, *group5;
      TGTextButton        *draw, *close, *save, *setparameters;
      TGCheckButton       *back_lin, *back_exp, *daugh, *daugh_free, *grand, *neutron, 
                          *limits, *log, *print,*two_component, *logmethod,
                          *integrate, *covarmatrix, *setymin;
      TGNumberEntry       *highlimit, *lowlimit, *guesslimit, *bins, *width, 
                          *channel, *lowrange, *ymin;
      TGLabel             *highlimit_label, *lowlimit_label, *guesslimit_label, 
                          *file_label, *bin_label, *title_label, *widthlabel, *lowrange_label, 
                          *channel_label, *save_label, *time_label, *ymin_label;
      TGTextEntry         *file_name, *title, *saved;
      TGTextBuffer        *filename, *titlevalue, *savevalue;
      TGComboBox          *timechoice, *filechoice;
      TH1D                *histo;

      ifstream input;

   public:
      Fitter(const TGWindow *p, UInt_t w, UInt_t h);
      virtual ~Fitter();

      // Slots, or functions for this window

      void OpenExp();
      void OpenComponents();
      void OpenDaughter();
      void OpenGrand();
      void OpenNeutron();
      void OpenParameters();
      void CloseWindow();
      void Update();
      void Draw();
      void Save();

};

// This is an input window for entering daughter half-life values.

class InputExponential {

   RQ_OBJECT("InputExponential")

   private:
      TGTransientFrame  *fMain;
      TGHorizontalFrame *expFrame, *expFrame2, *buttonFrame;
      TGCheckButton     *exp_free;
      TGNumberEntry     *exp_decay;
      TGLabel           *exp_label;
      TGTextButton      *okay, *cancel;
      TGGroupFrame      *group;

   public:
      InputExponential(const TGWindow *p, const TGWindow *main, UInt_t w, UInt_t h,
            UInt_t options = kVerticalFrame);
      virtual ~InputExponential();

      // Slots, or functions for this window

      void CloseWindow();
      void DoOK();
      void DoCancel();
};

class InputComponents {

   RQ_OBJECT("InputComponents")

   private:
      TGTransientFrame  *fMain;
      TGHorizontalFrame *buttonFrame, *comp1Frame, *comp2Frame, *frac2Frame, *frac2Frame2, *comp1Frame2, *comp2Frame2;
      TGCheckButton     *freefraction, *freecomp1, *freecomp2;
      TGNumberEntry     *comp1, *comp2, *frac2;
      TGLabel           *comp1Label, *comp2Label, *frac2Label;
      TGTextButton      *okay, *cancel;
      TGGroupFrame      *group;

   public:
      InputComponents(const TGWindow *p, const TGWindow *main, UInt_t w, UInt_t h, 
            UInt_t options = kVerticalFrame);
      virtual ~InputComponents();

      // Slots, or functions for this window

      void CloseWindow();
      void DoOK();
      void DoCancel();
};

class InputDaughter {

   RQ_OBJECT("InputDaughter")

   private:
      TGTransientFrame  *fMain;
      TGHorizontalFrame *daughFrame, *daughFrame2, *buttonFrame;
      TGCheckButton     *daugh_free;
      TGNumberEntry     *daugh_life;
      TGLabel           *daugh_label;
      TGTextButton      *okay, *cancel;
      TGGroupFrame      *group;

   public:
      InputDaughter(const TGWindow *p, const TGWindow *main, UInt_t w, UInt_t h,
            UInt_t options = kVerticalFrame);
      virtual ~InputDaughter();

      // Slots, or functions for this window

      void CloseWindow();
      void DoOK();
      void DoCancel();
};

// This is an input window for entering grand-daughter half-life values.

class InputGrand {

   RQ_OBJECT("InputGrand")

   private:
      TGTransientFrame  *fMain;
      TGHorizontalFrame *grandFrame, *buttonFrame;
      TGNumberEntry     *grand_life;
      TGLabel           *grand_label;
      TGTextButton      *okay, *cancel;
      TGGroupFrame      *group;

   public:
      InputGrand(const TGWindow *p, const TGWindow *main, UInt_t w, UInt_t h,
            UInt_t options = kVerticalFrame);
      virtual ~InputGrand();

      // Slots, or functions for this window

      void CloseWindow();
      void DoOK();
      void DoCancel();
};

// This is an input window for entering initial values for parameters in the
// fits.

class InputParameters {

   RQ_OBJECT("InputParameters")

   private:
      TGTransientFrame  *fMain;
      TGHorizontalFrame *lifeGuessFrame, *lifeLowFrame, *lifeHighFrame, 
                        *daughterGuessFrame, *daughterLowFrame, *daughterHighFrame,
                        *backLinGuessFrame, *backLinLowFrame, *backLinHighFrame,
                        *initialGuessFrame, *initialLowFrame, *initialHighFrame,
                        *buttonFrame, *expDecayGuessFrame, *expDecayLowFrame, 
                        *expDecayHighFrame, *expInitGuessFrame, *expInitLowFrame,
                        *expInitHighFrame, *fracGuessFrame, *fracLowFrame, *fracHighFrame,
                        *component2GuessFrame, *component2LowFrame, *component2HighFrame;
      TGNumberEntry     *lifeGuessNum, *lifeLowNum, *lifeHighNum, *daughterGuessNum, 
                        *daughterLowNum, *daughterHighNum, *backLinGuessNum, 
                        *backLinLowNum, *backLinHighNum,*initialGuessNum, 
                        *initialLowNum, *initialHighNum, *expDecayGuessNum, *expDecayLowNum,
                        *expDecayHighNum, *expInitGuessNum, *expInitLowNum, *expInitHighNum,
                        *fracGuessNum, *fracLowNum, *fracHighNum, *component2GuessNum, 
                        *component2LowNum, *component2HighNum;
      TGLabel           *lifeGuessLabel, *lifeLowLabel, *lifeHighLabel, 
                        *daughterGuessLabel, *daughterLowLabel, *daughterHighLabel, 
                        *backLinGuessLabel, *backLinLowLabel, *backLinHighLabel,
                        *initialGuessLabel, *initialLowLabel, *initialHighLabel,
                        *expDecayGuessLabel, *expDecayLowLabel, *expDecayHighLabel,
                        *expInitGuessLabel, *expInitLowLabel, *expInitHighLabel,
                        *fracGuessLabel, *fracLowLabel, *fracHighLabel, *component2GuessLabel
                           *component2LowLabel, *component2HighLabel;
      TGTextButton      *okay, *cancel;
      TGGroupFrame      *group1, *group2, *group3, *group4, *group5;


   public:
      InputParameters(const TGWindow *p, const TGWindow *main, UInt_t w, UInt_t h, 
            UInt_t options = kVerticalFrame);
      virtual ~InputParameters();

      //Slots, or functions for this window

      void CloseWindow();
      void DoOK();
      void DoCancel();
};

// This is an input window for neutron branching information.

class InputNeutron {

   RQ_OBJECT("InputNeutron")

   private:
      TGTransientFrame  *fMain;
      TGHorizontalFrame *oneBranchFrame, *oneLifeFrame, *twoBranchFrame, 
                        *twoLifeFrame, *buttonFrame;
      TGNumberEntry     *oneBranch, *oneLife, *twoBranch, *twoLife;
      TGLabel           *oneBranchLabel, *oneLifeLabel, *twoBranchLabel, 
                        *twoLifeLabel;
      TGTextButton      *okay, *cancel;
      TGGroupFrame      *group;

   public:
      InputNeutron(const TGWindow *p, const TGWindow *main, UInt_t w, UInt_t h, 
            UInt_t options = kVerticalFrame);
      virtual ~InputNeutron();

      // Slots, or functions for this window

      void CloseWindow();
      void DoOK();
      void DoCancel();
};

/****************************************************************/
/* These are now the functions of the macro itself, including   */
/* constructors for all of the GUI windows, etc.                */
/****************************************************************/

// This is the function that is called when the macro is run.
// It simply opens an instance of the main GUI.

void halflifefit() { 

   // Popup the GUI 

   new Fitter(gClient->GetRoot(), 800, 300);

}

// The constructor for the main GUI window. 

Fitter::Fitter(const TGWindow *p, UInt_t w, UInt_t h) {

   gStyle->SetFillColor(10);

   // Create a main frame

   fMain = new TGMainFrame(p, w, h);
   fMain->Connect ("CloseWindow()", "Fitter", this, "CloseWindow()");

   // Create sub-frames to allow correct arrangement of widgets

   hframe = new TGHorizontalFrame(fMain, 900, 400);

   left = new TGVerticalFrame(hframe, 100, 400);
   right = new TGVerticalFrame(hframe, 100, 400);

   // Create the histogram canvas on the RHS of the GUI

   fFitCanvas = new TRootEmbeddedCanvas("FitCanvas", right, 600, 400);
   right->AddFrame(fFitCanvas, new TGLayoutHints(kLHintsExpandY|kLHintsCenterX|
            kLHintsExpandX, 10, 10, 10, 10));

   // Create the fit options subframe on the LHS of the GUI

   group5 = new TGGroupFrame(left, "Fit Method Options", kVerticalFrame);
   left->AddFrame(group5, new TGLayoutHints(kLHintsTop|kLHintsCenterX|
            kLHintsExpandX, 2,2,2,2));

   group = new TGGroupFrame(left, "Fit Options", kVerticalFrame);
   left->AddFrame(group, new TGLayoutHints(kLHintsTop|kLHintsCenterX|
            kLHintsExpandX, 2,2,2,2));

   logmethod = new TGCheckButton(group5, "Use Log Likelihood method?");
   group5->AddFrame(logmethod, new TGLayoutHints(kLHintsTop|kLHintsLeft, 2,2,2,2));

   integrate = new TGCheckButton(group5, "Fit to integral over time bins?");
   group5->AddFrame(integrate, new TGLayoutHints(kLHintsTop|kLHintsLeft, 2,2,2,2));

   covarmatrix = new TGCheckButton(group5, "Print out covariance matrix?");
   group5->AddFrame(covarmatrix, new TGLayoutHints(kLHintsTop|kLHintsLeft, 2,2,2,2));

   back_lin = new TGCheckButton(group, "Linear background?");
   group->AddFrame(back_lin, new TGLayoutHints(kLHintsTop|kLHintsLeft, 2,2,2,2));

   back_exp = new TGCheckButton(group, "Exponential background?");
   group->AddFrame(back_exp, new TGLayoutHints(kLHintsTop|kLHintsLeft, 2,2,2,2));

   two_component = new TGCheckButton(group, "Two-component fit?");
   group->AddFrame(two_component, new TGLayoutHints(kLHintsTop|kLHintsLeft, 2,2,2,2));

   daugh = new TGCheckButton(group, "Include daughter activity?");
   group->AddFrame(daugh, new TGLayoutHints(kLHintsTop|kLHintsLeft, 2,2,2,2));

   grand = new TGCheckButton(group, "Include grand-daughter activity?");
   group->AddFrame(grand, new TGLayoutHints(kLHintsTop|kLHintsLeft, 2,2,2,2));

   neutron = new TGCheckButton(group, "Include parent neutron branching?");
   group->AddFrame(neutron, new TGLayoutHints(kLHintsTop|kLHintsLeft, 2,2,2,2));

   setparameters = new TGTextButton(group, "&Set Parameter Values...");
   setparameters->Connect("Clicked()", "Fitter", this, "OpenParameters()");
   group->AddFrame(setparameters, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 2,2,2,2));

   // Connect the check boxes to data entry pop-up windows, where all needed 
   // information will be entered.

   back_lin->Connect("Clicked()", "Fitter", this, "Update()");
   back_exp->Connect("Clicked()", "Fitter", this, "OpenExp()");
   two_component->Connect("Clicked()", "Fitter", this, "OpenComponents()");
   daugh->Connect("Clicked()", "Fitter", this, "OpenDaughter()");
   grand->Connect("Clicked()", "Fitter", this, "OpenGrand()");
   neutron->Connect("Clicked()", "Fitter", this, "OpenNeutron()");

   // Create the data file info sub-frame on the LHS of GUI

   group4 = new TGGroupFrame(left, "File Info", kVerticalFrame);
   left->AddFrame(group4, new TGLayoutHints(kLHintsTop|kLHintsCenterX|
            kLHintsExpandX, 2,2,2,2));

   hframe3 = new TGHorizontalFrame(group4, 100, 30);
   group4->AddFrame(hframe3, new TGLayoutHints(kLHintsCenterX|kLHintsTop, 
            2,2,2,2));

   // File name information...

   file_label = new TGLabel(hframe3, new TGString("File: "));
   file_name = new TGTextEntry(hframe3, filename = new TGTextBuffer(300));
   filename->AddText(0, "decay_db/");
   file_name->Resize(300, 25);
   hframe3->AddFrame(file_label, new TGLayoutHints(kLHintsCenterY|kLHintsLeft, 
            2,2,2,2));
   hframe3->AddFrame(file_name, new TGLayoutHints(kLHintsCenterY|kLHintsRight, 
            2,2,2,2));

   // Data format -- how many ms/channel in data

   hframe7 = new TGHorizontalFrame(group4, 100, 30);
   group4->AddFrame(hframe7, new TGLayoutHints(kLHintsCenterX|kLHintsTop, 
            2,2,2,2));
   channel_label = new TGLabel(hframe7, new TGString("time units/channel in file: "));
   channel = new TGNumberEntry(hframe7, 1, 12);
   hframe7->AddFrame(channel_label, new TGLayoutHints(kLHintsCenterY|kLHintsLeft, 
            2,2,2,2));
   hframe7->AddFrame(channel, new TGLayoutHints(kLHintsCenterY|kLHintsRight, 
            2,2,2,2));

   // Create thlotting options sub-frame on LHS of GUI

   group3 = new TGGroupFrame(left, "Plot Options", kVerticalFrame);
   left->AddFrame(group3, new TGLayoutHints(kLHintsTop|kLHintsCenterX|
            kLHintsExpandX, 2,2,2,2));

   // Histogram title entry

   hframe4 = new TGHorizontalFrame(group3, 100, 30);
   group3->AddFrame(hframe4, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 
            2,2,2,2));
   title_label = new TGLabel(hframe4, new TGString("      Plot Name: "));
   hframe4->AddFrame(title_label, new TGLayoutHints(kLHintsCenterY|
            kLHintsCenterX, 2,2,2,2));
   title = new TGTextEntry(hframe4, titlevalue = new TGTextBuffer(100));
   hframe4->AddFrame(title, new TGLayoutHints(kLHintsCenterY|kLHintsCenterX, 
            2,2,2,2));
   titlevalue->AddText(0, "^{}");
   title->Resize(200, 25);

   // Histogram bin width options

   hframe5 = new TGHorizontalFrame(group3, 100, 20);
   group3->AddFrame(hframe5, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 
            2,2,2,2));
   bin_label = new TGLabel(hframe5, new TGString("# of time units per bin: "));
   hframe5->AddFrame(bin_label, new TGLayoutHints(kLHintsCenterY|kLHintsCenterX, 
            2,2,2,2));
   bins = new TGNumberEntry(hframe5, 1, 12);
   hframe5->AddFrame(bins, new TGLayoutHints(kLHintsCenterY|kLHintsCenterX, 
            2,2,2,2));

   // Range option

   hframe6 = new TGHorizontalFrame(group3, 100, 30);
   group3->AddFrame(hframe6, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 
            2,2,2,2));
   widthlabel = new TGLabel(hframe6, new TGString("Range to plot (in time units): "));
   hframe6->AddFrame(widthlabel, new TGLayoutHints(kLHintsCenterY|kLHintsCenterX, 
            2,2,2,2));
   width = new TGNumberEntry(hframe6, 1000, 12);
   hframe6->AddFrame(width, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 2,2,2,2));
   lowrangeFrame = new TGHorizontalFrame(group3, 100, 30);
   group3->AddFrame(lowrangeFrame, new TGLayoutHints(kLHintsTop|kLHintsCenterX,
            2,2,2,2));
   lowrange_label = new TGLabel(lowrangeFrame, new TGString("Minimum to plot (in time units): "));
   lowrangeFrame->AddFrame(lowrange_label, new TGLayoutHints(kLHintsCenterY|kLHintsCenterX,
            2,2,2,2));
   lowrange = new TGNumberEntry(lowrangeFrame, 0, 12);
   lowrangeFrame->AddFrame(lowrange, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 2,2,2,2));

   // Plot appearance options, like the time scale to be used, log settings
   // for the y-axis, etc.

   timeFrame = new TGHorizontalFrame(group3, 100, 30);
   group3->AddFrame(timeFrame, new TGLayoutHints(kLHintsTop|kLHintsCenterX,
            2,2,2,2));
   time_label = new TGLabel(timeFrame, new TGString("Time unit for plot:"));
   timeFrame->AddFrame(time_label, new TGLayoutHints(kLHintsCenterY|
            kLHintsCenterX, 2,2,2,2));
   timechoice = new TGComboBox(timeFrame);
   timeFrame->AddFrame(timechoice, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 
            2,2,2,2));
   timechoice->AddEntry("ms", 1);
   timechoice->AddEntry("s", 2);
   timechoice->AddEntry("us", 3);
   timechoice->AddEntry("ns", 4);
   timechoice->AddEntry("min", 5);
   timechoice->AddEntry("days", 6);
   timechoice->Select(1);
   timechoice->Resize(50, 20);

   log = new TGCheckButton(group3, "Log scale for y-axis?");
   group3->AddFrame(log, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 2,2,2,2));

   setymin = new TGCheckButton(group3, "Fix minimum on y-axis?");
   group3->AddFrame(setymin, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 2,2,2,2));

   setymin->Connect("Clicked()", "Fitter", this, "Update()");

   yminFrame = new TGHorizontalFrame(group3, 100, 30);
   group3->AddFrame(yminFrame, new TGLayoutHints(kLHintsTop|kLHintsCenterX,
            2,2,2,2));
   ymin_label = new TGLabel(yminFrame, new TGString("Minimum on y-axis: "));
   yminFrame->AddFrame(ymin_label, new TGLayoutHints(kLHintsCenterY|kLHintsCenterX,
            2,2,2,2));
   ymin = new TGNumberEntry(yminFrame, 1, 12);
   yminFrame->AddFrame(ymin, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 2,2,2,2));  

   print = new TGCheckButton(group3, "Print-out fit results on plot?");
   group3->AddFrame(print, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 2,2,2,2));

   hframe2 = new TGHorizontalFrame(left, 100, 50);
   left->AddFrame(hframe2, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX|
            kLHintsBottom, 2,2,2,2));

   // Saved file file name entry

   hframe8 = new TGHorizontalFrame(group3, 100, 30);
   group3->AddFrame(hframe8, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 
            2,2,2,2));
   save_label = new TGLabel(hframe8, new TGString("Save plot as: "));
   hframe8->AddFrame(save_label, new TGLayoutHints(kLHintsCenterY|kLHintsCenterX, 
            2,2,2,2));
   saved = new TGTextEntry(hframe8, savevalue = new TGTextBuffer(100));
   hframe8->AddFrame(saved, new TGLayoutHints(kLHintsCenterY|kLHintsCenterX, 
            2,2,2,2));
   savevalue->AddText(0, "Enter file name (with '.eps')...");
   saved->Resize(200, 25);

   filechoice = new TGComboBox(hframe8);
   hframe8->AddFrame(filechoice, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 
            2,2,2,2));
   filechoice->AddEntry(".eps", 1);
   filechoice->AddEntry(".ps", 2);
   filechoice->AddEntry(".pdf", 3);
   filechoice->AddEntry(".gif", 4);
   filechoice->AddEntry(".jpg", 5);
   filechoice->AddEntry(".png", 6);
   filechoice->Select(6);
   filechoice->Resize(50, 25);

   // Draw and Exit buttons for the GUI
   draw = new TGTextButton(hframe2, "&Draw");
   draw->Connect("Clicked()", "Fitter", this, "Draw()");
   hframe2->AddFrame(draw, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 
            2,2,2,2));

   save = new TGTextButton(hframe2, "&Save");
   save->Connect("Clicked()", "Fitter", this, "Save()");
   hframe2->AddFrame(save, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 
            2,2,2,2));

   close = new TGTextButton(hframe2, "&Exit");
   close->Connect("Clicked()", "Fitter", this, "CloseWindow()");
   hframe2->AddFrame(close, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 
            2,2,2,2));

   // Arrange all of the window properly and we're finished building the GUI

   hframe->AddFrame(left, new TGLayoutHints(kLHintsLeft|kLHintsTop, 2,2,2,2));
   hframe->AddFrame(right, new TGLayoutHints(kLHintsRight|kLHintsTop|
            kLHintsExpandX|kLHintsExpandY, 
            2,2,2,2));

   fMain->AddFrame(hframe, new TGLayoutHints(kLHintsExpandX|kLHintsExpandY, 
            2,2,2,2));

   fMain->SetWindowName("Half-Life Fitter");
   fMain->MapSubwindows();
   fMain->Resize(fMain->GetDefaultSize());
   fMain->MapWindow();

   ymin->SetState(0);

}

// GUI destructor

Fitter::~Fitter() {

   // Delete all created widgets
   delete saved, save_label, savevalue;
   delete title, title_label, titlevalue;
   delete time_label, ymin_label;
   delete bins, bin_label, widthlabel, width;
   delete lowrange_label, lowrange, lowrangeFrame, yminFrame;
   delete setymin, filechoice;
   delete hframe4, hframe5, group3, hframe6, hframe7, hframe8;
   delete hframe2, timeFrame, *ymin;
   delete close, draw;
   delete filename, file_label, file_name, channel_label, channel;
   delete hframe3;
   delete neutron, daugh, back_lin, grand, limits, print, 
          back_exp, two_component, logmethod, integrate, covarmatrix;
   delete timechoice;
   delete group, group5, group4;
   delete left;
   delete fFitCanvas;
   delete right;
   delete hframe;
   delete fMain;
}

void Fitter::OpenExp() {

   bool exponential = (back_exp->GetState() == kButtonDown);
   EXP = exponential;

   if (exponential) {
      new InputExponential(gClient->GetRoot(), fMain, 400, 200);
   };

}

void Fitter::OpenComponents() {

   bool twocomp = (two_component->GetState() == kButtonDown);
   TWOCOMP = twocomp;

   if (twocomp) {
      new InputComponents(gClient->GetRoot(), fMain, 400, 200);
   };
}

void Fitter::OpenDaughter() {

   bool daughter = (daugh->GetState() == kButtonDown);

   if (daughter) {
      new InputDaughter(gClient->GetRoot(), fMain, 400, 200);
   };

}

void Fitter::OpenGrand() {

   bool granddaughter = (grand->GetState() == kButtonDown);

   if (granddaughter) {
      new InputGrand(gClient->GetRoot(), fMain, 400, 200);
   };

}

void Fitter::OpenParameters() {

   new InputParameters(gClient->GetRoot(), fMain, 400, 200);

}

void Fitter::OpenNeutron() {

   bool neutronbranch = (neutron->GetState() == kButtonDown);

   if (neutron) {
      new InputNeutron(gClient->GetRoot(), fMain, 400, 200);
   };

}

// GUI Exit funtion (terminates ROOT too)

void Fitter::CloseWindow() {

   // When called, closes the whole thing, and exit ROOT.

   gApplication->Terminate(0);
}

// The Update() function to respond to check boxes by enabling other data 
// entry fields

void Fitter::Update() {

   // Check which check-buttons are selected

   bool linear = (back_lin->GetState() == kButtonDown);
   LINEAR = linear;
   bool daughter = (daugh->GetState() == kButtonDown);
   bool neutronbranch = (neutron->GetState() == kButtonDown);
   bool granddaugh = (grand->GetState() == kButtonDown);
   bool setyminimum = (setymin->GetState() == kButtonDown);
   if (setyminimum) {
      ymin->SetState(1);
   } else {
      ymin->SetState(0);
   }

}

// The main function, which actually fits the histograms.

void Fitter::Draw() {

   if (DRAW_CONTROL == 1) {
      delete histo;
   }

   // Get the information regarding the number of ms/channel in the data and 
   // the desired range of the histogram

   double range = width->GetNumber();
   double per_channel = channel->GetNumber();
   double lowrangelimit = lowrange->GetNumber();
   double minimumy = ymin->GetNumber();
   int i = 1;

   // This is just here to avoid a weird error message...I'll take it out when
   // I figure out the problem.
   int data[100000] = {0};

   if (((int)range/per_channel) > 100000) {
      cout<<"careful man!!"<<endl;
      //    cout << "Sorry, the range you have chosen is too long." << endl;
      //goto end;
   }

   gStyle->SetFillColor(10);

   // Only read in from the data file the first time, or if the data file
   // changes, otherwise just use the original data stored in the arrays.

   if (FILENAME != filename->GetString()) {

      FILENAME = filename->GetString();
      cout << "Reading in file: " << FILENAME << endl;
      input.open(FILENAME);

      if (input.fail()) {
         cerr << "Couldn't open " << FILENAME << ". Sorry." << endl;
         goto end;
      }

      // Read in data from .top file format

      while (!input.eof()) {
         input >> BIN[COUNT];
         input >> DATA[COUNT];
         COUNT ++;
      }

      input.close();
   }

   // Find out what check boxes are selected

   int timescale = timechoice->GetSelected();
   bool linear = (back_lin->GetState() == kButtonDown);
   bool exp = (back_exp->GetState() == kButtonDown);
   bool twocomponent = (two_component->GetState() == kButtonDown);
   bool daughter = (daugh->GetState() == kButtonDown);
   bool neutronbranch = (neutron->GetState() == kButtonDown);
   bool granddaugh = (grand->GetState() == kButtonDown);
   bool logony = (log->GetState() == kButtonDown);
   bool printout = (print->GetState() == kButtonDown);
   bool uselogmethod = (logmethod->GetState() == kButtonDown);
   bool useintegrate = (integrate->GetState() == kButtonDown);
   bool printoutmatrix = (covarmatrix->GetState() == kButtonDown);
   bool setyminimum = (setymin->GetState() == kButtonDown);

   // Some error messages to avoid unpleasant ROOT errors.  

   int FLAG = 0;
   int retval;

   if (daughter) {
      if (!DAUGHTER_FREE) {
         if (DAUGHTER_GUESS <= 0) {
            FLAG = 1;
            new TGMsgBox(gClient->GetRoot(), fMain,
                  "Something is weird...", "You need to enter a valid beta daughter half-life.  \nOr just don't include the daughter in the fit!", kMBIconStop, kMBDismiss, &retval);
         }
      }
   }
   if (neutronbranch) {
      if ((ONE_NEUTRON + TWO_NEUTRON) < 1) {
         if (DAUGHTER_GUESS <= 0) {
            FLAG = 1;
            new TGMsgBox(gClient->GetRoot(), fMain,
                  "Something is weird...", "You need to enter a valid beta daughter half-life.  \n With the neutron branches as they are now, the beta daughter will be included in the fit.", kMBIconStop, kMBDismiss, &retval);
         }
      }
   }
   if (granddaugh) {
      if (GRANDDAUGHTER <= 0) {
         FLAG = 1;
         new TGMsgBox(gClient->GetRoot(), fMain,
               "Something is weird...", "You need to enter a valid grand-daughter half-life.  \nOr just don't include the grand-daughter in the fit.", kMBIconStop, kMBDismiss, &retval);
      } else if (!daughter) {
         FLAG = 1;
         new TGMsgBox(gClient->GetRoot(), fMain,"Something is weird...", 
               "Sorry, right now to include a grand-daughter in the fit \nyou also need to include the daughter with a set half-life.  \nPlease do this.", kMBIconStop, kMBDismiss, &retval);
      }
   }

   if (FLAG == 1) {
      goto end;
   }

   // Get info on desired bin width for histogram

   if (bins->GetNumber() != 0) {
      double number_time = bins->GetNumber();
   } else {
      cout << "Bin width value is invalid." << endl;
      goto end;
   }

   // Create the correct y-axis label based on bin width

   char ytitle[40];

   // Build the histogram

   int nbins = (int)range/number_time;

   // Fill the histogram

   char timeunit[5];
   char xtitle[40];

   histo = new TH1D("", titlevalue->GetString(), nbins, lowrangelimit, range+lowrangelimit);
   for (int j=0; j<=COUNT; j++) {
      histo->Fill((per_channel*BIN[j]+(0.5*per_channel)), DATA[j]);
   }
   if (timescale == 2) {
      sprintf(timeunit, " s");
      sprintf(xtitle, "Time (s)");
      sprintf(ytitle, "Counts / %g s", number_time);
      DRAW_CONTROL = 1;
   } else if (timescale == 1) {
      sprintf(timeunit, " ms");
      sprintf(xtitle, "Time (ms)");
      sprintf(ytitle, "Counts / %g ms", number_time);
      DRAW_CONTROL = 1;
   } else if (timescale == 4) {
      sprintf(timeunit, " ns");
      sprintf(xtitle, "Time (ns)");
      sprintf(ytitle, "Counts / %g ns", number_time);
      DRAW_CONTROL = 1;
   } else if (timescale == 3) {
      sprintf(timeunit, " us");
      sprintf(xtitle, "Time (us)");
      sprintf(ytitle, "Counts / %g us", number_time);
      DRAW_CONTROL = 1;
   } else if (timescale == 5) {
      sprintf(timeunit, " min");
      sprintf(xtitle, "Time (min)");
      sprintf(ytitle, "Counts / %g min", number_time);
      DRAW_CONTROL = 1;
   } else if (timescale == 6) {
      sprintf(timeunit, " days");
      sprintf(xtitle, "Time (days)");
      sprintf(ytitle, "Counts / %g days", number_time);
      DRAW_CONTROL = 1;
   }

   // Get the canvas for the histogram to be plotted

   TCanvas *fCanvas = fFitCanvas->GetCanvas();
   fCanvas->cd();
   fCanvas->Update();
   fCanvas->SetBorderMode(0);
   fCanvas->SetFillColor(0);

   // Set the log y scale if desired

   if (logony) {
      fCanvas->SetLogy(1);
   } else {
      fCanvas->SetLogy(0);
   }

   // fCanvas->SetLogy(1);


   gStyle->SetTitleFillColor(0);
   gStyle->SetTitleBorderSize(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetCanvasColor(2);
   gStyle->SetFrameBorderMode(0);
   gStyle->SetFrameFillColor(2);

   histo->GetXaxis()->CenterTitle();
   histo->GetYaxis()->CenterTitle();

   histo->GetYaxis()->SetTitleSize(0.02);
   histo->GetYaxis()->SetLabelSize(0.02);
   histo->GetXaxis()->SetTitleSize(0.02);
   histo->GetXaxis()->SetLabelSize(0.02);


   /*
      if(noxerror) {
      gStyle->SetErrorX(0);
      histo->SetMarkerStyle(20);
      histo->SetMarkerSize(1);
      }
      */
   int freeparameters = 0; // We need to count the free parameters, for a reduced chi-square

   // Perform fit based on selected check-boxes

   if (!linear && !exp && !daughter && !neutronbranch && !granddaugh && !twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", parent, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 2;
   } else if (linear && !exp && !daughter && !neutronbranch && !granddaugh && !twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", parent_lin, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 3;
   } else if (!linear && exp && !daughter && !neutronbranch && !granddaugh && !twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", parent_exp, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 4;
   } else if (linear && exp && !daughter && !neutronbranch && !granddaugh && !twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", parent_both, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 5;
   } else if (!linear && !exp && daughter && !neutronbranch && !granddaugh && !twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", parent_daughter, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 3;
   } else if (linear && !exp && daughter && !neutronbranch && !granddaugh && !twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", parent_daughter_lin, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 4;
   } else if (!linear && exp && daughter && !neutronbranch && !granddaugh && !twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", parent_daughter_exp, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 5;
   } else if (linear && exp && daughter && !neutronbranch && !granddaugh && !twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", parent_daughter_both, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 6;
   } else if (!linear && !exp && daughter && neutronbranch && !granddaugh && !twocomponent) {
      NO_NEUTRON = 1 - ONE_NEUTRON - TWO_NEUTRON;
      TF1 *fitFcn = new TF1("fitFcn", parent_neutronbranch, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 7;
   } else if (linear && !exp && daughter && neutronbranch && !granddaugh && !twocomponent) {
      NO_NEUTRON = 1 - ONE_NEUTRON - TWO_NEUTRON;
      TF1 *fitFcn = new TF1("fitFcn", parent_neutronbranch_lin, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 8;
   } else if (!linear && exp && daughter && neutronbranch && !granddaugh && !twocomponent) {
      NO_NEUTRON = 1 - ONE_NEUTRON - TWO_NEUTRON;
      TF1 *fitFcn = new TF1("fitFcn", parent_neutronbranch_exp, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 9;
   } else if (linear && exp && daughter && neutronbranch && !granddaugh && !twocomponent) {
      NO_NEUTRON = 1 - ONE_NEUTRON - TWO_NEUTRON;
      TF1 *fitFcn = new TF1("fitFcn", parent_neutronbranch_both, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 10;
   } else if (!linear && !exp && daughter && !neutronbranch && granddaugh && !twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", parent_granddaughter, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 4;
   } else if (linear && !exp && daughter && !neutronbranch && granddaugh && !twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", parent_granddaughter_lin, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 5;
   } else if (!linear && exp && daughter && !neutronbranch && granddaugh && !twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", parent_granddaughter_exp, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 6;
   } else if (linear && exp && daughter && !neutronbranch && granddaugh && !twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", parent_granddaughter_both, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 7;
   } else if (!linear && !exp && !daughter && !neutronbranch && !granddaugh && twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", twocomponentfit, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 4;
   } else if (linear && !exp && !daughter && !neutronbranch && !granddaugh && twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", two_component_lin, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 5;
   } else if (!linear && exp && !daughter && !neutronbranch && !granddaugh && twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", two_component_exp, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 6;
   } else if (linear && exp && !daughter && !neutronbranch && !granddaugh && twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", two_component_both, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 7;
   } else if (!linear && !exp && daughter && !neutronbranch && !granddaugh && twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", two_component_daughter, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 5;
   } else if (linear && !exp && daughter && !neutronbranch && !granddaugh && twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", two_component_daughter_lin, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 6;
   } else if (!linear && exp && daughter && !neutronbranch && !granddaugh && twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", two_component_daughter_exp, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 7;
   } else if (linear && exp && daughter && !neutronbranch && !granddaugh && twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", two_component_daughter_both, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 8;
   } else if (!linear && !exp && daughter && !neutronbranch && granddaugh && twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", two_component_granddaughter, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 6;
   } else if (linear && !exp && daughter && !neutronbranch && granddaugh && twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", two_component_granddaughter_lin, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 7;
   } else if (!linear && exp && daughter && !neutronbranch && granddaugh && twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", two_component_granddaughter_exp, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 8;
   } else if (linear && exp && daughter && !neutronbranch && granddaugh && twocomponent) {
      TF1 *fitFcn = new TF1("fitFcn", two_component_granddaughter_both, lowrangelimit, range+lowrangelimit, 13);
      freeparameters = 9;
   } else if (!daughter && granddaugh) {
      FLAG = 1;
      new TGMsgBox(gClient->GetRoot(), fMain,
            "To include a granddaughter, you must also include the daughter.",
            kMBIconStop, kMBDismiss, &retval);
   } else if (granddaugh && neutronbranch) {
      FLAG = 1;
      new TGMsgBox(gClient->GetRoot(), fMain,
            "At this time, you cannot include both a granddaughter and neutron branching.\n I'm sorry.", 
            kMBIconStop, KMBDismiss, &retval);
   }

   // Set the initial values of all the parameters for the fit.

   fitFcn->SetParameter(0, INITIAL_GUESS);
   fitFcn->SetParLimits(0, INITIAL_LOW_LIMIT, INITIAL_HIGH_LIMIT);
   if (!twocomponent) {  
      fitFcn->SetParameter(1, LIFE_GUESS);
      fitFcn->SetParLimits(1, LIFE_LOW_LIMIT, LIFE_HIGH_LIMIT);
   }
   if (daughter) {
      if (DAUGHTER_FREE) {
         fitFcn->SetParameter(2, DAUGHTER_GUESS);
         fitFcn->SetParLimits(2, DAUGHTER_LOW_LIMIT, DAUGHTER_HIGH_LIMIT);
      } else if (!DAUGHTER_FREE) {
         fitFcn->FixParameter(2, DAUGHTER_GUESS);
         freeparameters = freeparameters - 1;
      }
   } else if (!daughter) {
      fitFcn->FixParameter(2, 0);
   }
   if (linear) {
      fitFcn->SetParameter(3, BACKLIN_GUESS);
      fitFcn->SetParLimits(3, BACKLIN_LOW_LIMIT, BACKLIN_HIGH_LIMIT);
   } else if (!linear) {
      fitFcn->FixParameter(3, 0);
   }
   if (exp) {
      fitFcn->SetParameter(4, EXPINIT_GUESS);
      fitFcn->SetParLimits(4, EXPINIT_LOW_LIMIT, EXPINIT_HIGH_LIMIT);
      if (EXPDECAY_FREE) {
         fitFcn->SetParameter(5, EXPDECAY_GUESS);
         fitFcn->SetParLimits(5, EXPDECAY_LOW_LIMIT, EXPDECAY_HIGH_LIMIT);
      } else if (!EXPDECAY_FREE) {
         fitFcn->FixParameter(5, EXPDECAY_GUESS);
         freeparameters = freeparameters - 1;
      }
   } else if (!exp) {
      fitFcn->FixParameter(4, 0);
      fitFcn->FixParameter(5, 0);
   }
   if (granddaugh) {
      fitFcn->FixParameter(6, GRANDDAUGHTER);
      freeparameters = freeparameters - 1;
   } else if (!granddaugh) {
      fitFcn->FixParameter(6, 0);
   }
   if (neutronbranch) {
      fitFcn->FixParameter(7, DAUGHTER_ONENEUTRON);
      fitFcn->FixParameter(8, DAUGHTER_TWONEUTRON);
      fitFcn->FixParameter(9, ONE_NEUTRON);
      fitFcn->FixParameter(10, TWO_NEUTRON);
      freeparameters = freeparameters - 4;
   } else if (!neutronbranch) {
      fitFcn->FixParameter(7, 0);
      fitFcn->FixParameter(8, 0);
      fitFcn->FixParameter(9, 0);
      fitFcn->FixParameter(10, 0);
   }
   if (twocomponent) {
      if (!FRACTION_FREE) {
         fitFcn->FixParameter(11, COMPONENT2_FRACTION);
         freeparameters = freeparameters - 1;
      } else if (FRACTION_FREE) {
         fitFcn->SetParameter(11, COMPONENT2_FRACTION);
         fitFcn->SetParLimits(11, COMPONENT2_FRACTION_LOW_LIMIT, COMPONENT2_FRACTION_HIGH_LIMIT);
      }
      if (!COMPONE_FREE) {
         fitFcn->FixParameter(1, LIFE_GUESS);
         freeparameters = freeparameters - 1;
      } else if (COMPONE_FREE) {
         fitFcn->SetParameter(1, LIFE_GUESS);
         fitFcn->SetParLimits(1, LIFE_LOW_LIMIT, LIFE_HIGH_LIMIT);
      }
      if (!COMPTWO_FREE) {
         fitFcn->FixParameter(12, COMPONENT2_GUESS);
         freeparameters = freeparameters - 1;
      } else {
         fitFcn->SetParameter(12, COMPONENT2_GUESS);
         fitFcn->SetParLimits(12, COMPONENT2_LOW_LIMIT, COMPONENT2_HIGH_LIMIT);
      }
   } else if (!twocomponent) {
      fitFcn->FixParameter(11, 0);
      fitFcn->FixParameter(12, 0);
   }

   cout << "The number of free parameters in the fit is " << freeparameters << endl;
   cout << " " << endl;

   // Actually fit the histogram, and set the appearance (i.e. titles, etc.)

   if (uselogmethod && !useintegrate) {
      histo->Fit("fitFcn", "LQMR");
   } else if (uselogmethod && useintegrate) {
      histo->Fit("fitFcn", "ILQMR");
   } else if (!uselogmethod && useintegrate) {
      histo->Fit("fitFcn", "IQMR");
   } else if (!uselogmethod && !useintegrate) {
      histo->Fit("fitFcn", "QMR");
   }
   histo->GetXaxis()->SetTitle(xtitle);
   histo->GetYaxis()->SetTitle(ytitle);
   histo->GetYaxis()->SetTitleOffset(1.3);

   if (setyminimum) { 
      histo->SetMinimum(minimumy);
   }
   gStyle->SetOptStat(0);

   if (printoutmatrix) {

      TVirtualFitter *actualfitter = TVirtualFitter::GetFitter();
      TMatrixD errormatrix(13,13, actualfitter->GetCovarianceMatrix());

      // Print out the covariance matrix

      for (int i=0; i<=12; i++) {
         for (int j=0; j<=12; j++) {
            if (errormatrix(i,j) < 1e-15) {
               errormatrix(i,j) = 0;
            }
         }
         cout << setprecision(5) << setw(12) << errormatrix(i,0) << setprecision(5) << setw(12) 
            << errormatrix(i,1) << setprecision(5) << setw(12) << errormatrix(i,2) 
            << setprecision(5) << setw(12) << errormatrix(i,3) << setprecision(5) << setw(8) 
            << errormatrix(i,4) << setprecision(5) << setw(8) << errormatrix(i,5) 
            << setprecision(5) << setw(12) << errormatrix(i,6) << setprecision(5) << setw(8) 
            << errormatrix(i,7) << setprecision(5) << setw(8) << errormatrix(i,8) 
            << setprecision(5) << setw(8) << errormatrix(i,9) << setprecision(5) << setw(8) 
            << errormatrix(i,10) << setprecision(5) << setw(8) << errormatrix(i,11) 
            << setprecision(5) << setw(8) << errormatrix(i,12) << endl;
      }
   }

   // Define the constituent functions of the fit.

   if (!twocomponent) {
      TF1 *parentFcn = new TF1 ("parentFcn", parent, lowrangelimit, range+lowrangelimit, 13);
      parentFcn->SetLineColor(3);
      if (granddaugh) {
         TF1 *grandFcn = new TF1("grandFcn", granddaughter, lowrangelimit, range+lowrangelimit, 13);
         grandFcn->SetLineColor(7);
      }
      if (daughter) {
         TF1 *daughterFcn = new TF1("daughterFcn", daughter_only, lowrangelimit, range+lowrangelimit, 13);
         daughterFcn->SetLineColor(4);
      }
   }
   if (linear) {
      TF1 *backFcn = new TF1("backFcn", background_linear, lowrangelimit, range+lowrangelimit, 13);
      backFcn->SetLineColor(2);
   }
   if (exp) {
      TF1 *backFcn = new TF1("backFcn", background_exp, lowrangelimit, range+lowrangelimit, 13);
      backFcn->SetLineColor(2);
   }
   if (neutronbranch) {
      TF1 *ndaughFcn = new TF1("ndaughFcn", oneneutron_daughter, lowrangelimit, range+lowrangelimit, 13);
      ndaughFcn->SetLineColor(5);
      TF1 *n2daughFcn = new TF1("n2daughFcn", twoneutron_daughter, lowrangelimit, range+lowrangelimit, 13);
      n2daughFcn->SetLineColor(6);
   }
   if (twocomponent) {
      TF1 *comp1Fcn = new TF1("comp1Fcn", component1, lowrangelimit, range+lowrangelimit, 13);
      comp1Fcn->SetLineColor(8);
      TF1 *comp2Fcn = new TF1("comp2Fcn", component2, lowrangelimit, range+lowrangelimit, 13);
      comp2Fcn->SetLineColor(9);
      if (granddaugh) {
         TF1 *grandFcn = new TF1("grandFcn", granddaughter_two_component, lowrangelimit, range+lowrangelimit, 13);
         grandFcn->SetLineColor(7);
      }
      if (daughter) {
         TF1 *daughterFcn = new TF1("daughterFcn", daughter_two_component, lowrangelimit, range+lowrangelimit, 13);
         daughterFcn->SetLineColor(4);
      }
   }

   Double_t par[13];
   fitFcn->GetParameters(par);
   double chisquare = fitFcn->GetChisquare();

   Double_t chimean[100000] = {0};
   Double_t function_value = 0;
   Double_t logfunction = 0;
   Double_t bincenter = 0;
   Double_t bincontents = 0;
   Double_t chi[100000] = {0};

   for (int i=0; i <= (nbins-1); i++) {
      bincenter = histo->GetXaxis()->GetBinCenter(i+1);
      bincontents = histo->GetBinContent(i+1);
      function_value = fitFcn->Eval(bincenter, 0, 0);
      chi[i] = function_value - bincontents*TMath::Log(function_value)
         + TMath::LnGamma(bincontents+1);
      logfunction = TMath::Log(function_value);
      chimean[i] = 1.009303*logfunction + 2.766579;
      function_value = 0;
      logfunction = 0;
      bincenter = 0;
      bincontents = 0;
   }

   Double_t degreesoffreedom = 0;
   Double_t chisquared_loglike = 0;

   for (int i = 0; i <= (nbins-1); i++) {
      degreesoffreedom = degreesoffreedom + chimean[i];
      chisquared_loglike = chisquared_loglike + chi[i];
   }

   degreesoffreedom = degreesoffreedom - freeparameters;
   chisquared_loglike = chisquared_loglike*2;

   // Extract all of the results of the fit.

   double initial_activity = par[0];
   double initial_activity_error = fitFcn->GetParError(0);
   if (!twocomponent) {
      double halflife = par[1];
      double halflife_error = fitFcn->GetParError(1);
   }
   if (daughter) {
      double daughter_halflife = par[2];
      double daughter_halflife_error = fitFcn->GetParError(2);
   }
   if (linear) {
      double background_linear = par[3];
      double background_linear_error = fitFcn->GetParError(3);
   }
   if (exp) {
      double background_exp_initial = par[4];
      double background_exp_initial_error = fitFcn->GetParError(4);
      if (EXPDECAY_FREE) {
         double background_exp_decay = par[5];
         double background_exp_decay_error = fitFcn->GetParError(5);
      } else {
         double background_exp_decay = par[5];
      }
   }
   double granddaughter = GRANDDAUGHTER;
   double one_neutron_halflife = DAUGHTER_ONENEUTRON;
   double two_neutron_halflife = DAUGHTER_TWONEUTRON;
   if (twocomponent) {
      double halflife = par[1];
      double component2_halflife = par[12];
      double component2_fraction = par[11];
      if (FRACTION_FREE) {
         double component2_fraction_error = fitFcn->GetParError(11);
      }
      if (COMPONE_FREE) {
         double halflife_error = fitFcn->GetParError(1);
      } 
      if (COMPTWO_FREE) {
         double component2_halflife_error = fitFcn->GetParError(12);
      }

   }

   // Print out the results of the fit to the screen.

   cout << titlevalue->GetString() << endl;

   if (twocomponent) {
      if (COMPONE_FREE) {
         cout << "Component 1 half-life = " << halflife << timeunit << " +/- "
            << halflife_error << endl;
      } else if (!COMPONE_FREE) {
         cout << "Component 1 half-life = " << halflife << timeunit << " (fixed)" << endl;
      }
      if (COMPTWO_FREE) {
         cout << "Component 2 half-life = " << component2_halflife << timeunit << " +/- " 
            << component2_halflife_error << endl;
      } else if (!COMPTWO_FREE) {
         cout << "Component 2 half-life = " << component2_halflife << timeunit << " (fixed)" << endl;
      }
      if (FRACTION_FREE) {
         cout << "Fraction of component 2 = " << component2_fraction << " +/- " 
            << component2_fraction_error << endl;
      } else if (!FRACTION_FREE) {
         cout << "Fraction of component 2 = " << component2_fraction << " (fixed)" << endl;
      }
   } else if (!twocomponent) {
      cout << "Half-life = " << halflife << " +/- " << halflife_error << timeunit << endl;
   }
   cout << "Initial activity = " << initial_activity << " +/- " << initial_activity_error 
      << " counts/" << number_time << timeunit << endl;
   if (linear) {
      cout << "Background (constant) = " << background_linear << " +/- " << background_linear_error
         << " counts/" << number_time << timeunit << endl;
   }
   if (exp) {
      cout << "Background (exponential) intial value = " << background_exp_initial << " +/- " 
         << background_exp_initial_error << " counts/" << number_time << timeunit << endl;
      if (EXPDECAY_FREE) {
         cout << "Background (exponential) decay constant = " << background_exp_decay << " +/- " 
            << background_exp_decay_error << timeunit << "-1" << endl;
      } else {
         cout << "Background (exponential) decay constant = " << background_exp_decay 
            << timeunit << "-1 (fixed)" << endl;
      }
   } 
   if (daughter) {
      if (DAUGHTER_FREE) {
         cout << "Daughter half-life = " << daughter_halflife << " +/- " 
            << daughter_halflife_error << timeunit << endl;
      } else if (!DAUGHTER_FREE) {
         cout << "Daughter half-life = " << daughter_halflife << timeunit << " (fixed)" << endl;
      }
   }
   if (granddaugh) {
      cout << "Granddaughter half-life = " << granddaughter << timeunit << " (fixed)" << endl;
   }
   if (neutronbranch) {
      cout << "One-neutron daughter branching ratio = " << ONE_NEUTRON 
         << " (fixed)" << endl;
      cout << "One-neutron daughter half-life = " << one_neutron_halflife << timeunit 
         << " (fixed)" << endl;
      cout << "Two-neutron daughter branching ratio = " << TWO_NEUTRON 
         << " (fixed)" << endl;
      cout << "Two-neutron daughter half-life = " << two_neutron_halflife << timeunit
         << " (fixed)" << endl;
   }

   if (uselogmethod) {
      cout << "Chi-square (ROOT) = " << chisquare << endl;
      cout << "Reduced chi-square (ROOT) = " << chisquare/degreesoffreedom << endl;
      if (chisquared_loglike >= 0 && degreesoffreedom > 0) {
         cout << "Chi-square (calculated) = " << chisquared_loglike << endl;
         cout << "Reduced chi-square (calculated) = " << chisquared_loglike/degreesoffreedom << endl;
      } else {
         cout << "Error calculating the chi-squared directly.  Sorry." << endl;
      }
   } else if (!uselogmethod) {
      cout << "Chi-square = " << chisquare << endl;
      cout << "Reduced chi-square = " << chisquare/(nbins - freeparameters) << endl;
   }
   cout << "" << endl;

   // Draw the histogram, with the options for displaying fit results on the plot.

   histo->Draw("E1P");
   //   histo->Draw("histo");
   fCanvas->Update();
   if (twocomponent) {
      comp1Fcn->SetParameters(par);
      comp1Fcn->Draw("same");
      comp2Fcn->SetParameters(par);
      comp2Fcn->Draw("same");
      fitFcn->Draw("same");
   } else if (!twocomponent) {
      parentFcn->SetParameters(par);
      parentFcn->Draw("same");
      fitFcn->Draw("same");
   }
   if (linear || exp) {
      backFcn->SetParameters(par);
      backFcn->Draw("same");
   }
   if (daughter) {
      daughterFcn->SetParameters(par);
      daughterFcn->Draw("same");
   } 
   if (neutronbranch) {
      ndaughFcn->SetParameters(par);
      ndaughFcn->Draw("same");
      n2daughFcn->SetParameters(par);
      n2daughFcn->Draw("same");
   }
   if (granddaugh) {
      grandFcn->SetParameters(par);
      grandFcn->Draw("same");
   }
   fCanvas->Update();


   TLatex la;
   // la.SetTextAlign(15);
   la.SetTextSize(0.1);
   la.SetTextAngle(0);
   // la.SetTextFont(11);
   // la.DrawLatex(2.015,47.2,"");


   // la.DrawLatex(25,40,"790 keV");
   // la.DrawLatex(25,20,"12^{+}#rightarrow10^{+}");





   if (printout) {
      TPaveText *text = new TPaveText(0.45, 0.65, 0.65, 0.88,"NDC");
      text->ConvertNDCtoPad();
      text->SetTextSize(0.025);
      text->SetBorderSize(0);
      text->SetFillStyle(0);

      if (!twocomponent) {
         char str1[80];
         sprintf (str1, "Half-life: %.3f +/- %.3f%s", halflife, halflife_error, timeunit);
         text->AddText(str1);
      } else if (twocomponent) {
         char str1[80];
         if (COMPONE_FREE) {
            sprintf(str1, "Component 1 Half-life: %.3f +/- %.3f%s", halflife, halflife_error, timeunit);
         } else if (!COMPONE_FREE) {
            sprintf(str1, "Component 1 Half-life: %.3f%s (fixed)", halflife, timeunit);
         }
         char str11[80];
         if (COMPTWO_FREE) {
            sprintf(str11, "Component 2 Half-life: %.3f +/- %.3f%s", component2_halflife, 
                  component2_halflife_error, timeunit);
         } else if (!COMPTWO_FREE) {
            sprintf(str11, "Component 2 Half-life: %.3f%s (fixed)", component2_halflife, timeunit);
         }
         if (FRACTION_FREE) {
            char str12[80];
            sprintf(str12, "Component 2 Fraction: %.3f +/- %.3f", component2_fraction, component2_fraction_error);
         } else if (!FRACTION_FREE) {
            char str12[80];
            sprintf(str12, "Component 2 Fraction: %.3f (fixed)", component2_fraction);
         }
         text->AddText(str1);
         text->AddText(str11);
         text->AddText(str12);
      }
      char str2[80];
      sprintf (str2, "Initial Activity: %.3f +/- %.3f counts/%g%s", initial_activity, initial_activity_error, number_time, timeunit);
      text->AddText(str2);
      if (linear) {
         char str3[80];
         sprintf (str3, "Background (constant): %.3f +/- %.3f counts/%g%s", background_linear, background_linear_error, number_time, timeunit);
         text->AddText(str3);
      }
      if (exp) {
         char str3[80];
         sprintf(str3, "Background (exponential) initial value: %.3f +/- %.3f counts/%g%s", background_exp_initial, background_exp_initial_error, number_time, timeunit);
         if (EXPDECAY_FREE) {
            char str4[80];
            sprintf(str4, "Background (exponential) decay constant: %.5f +/- %.5f%s-1", background_exp_decay, background_exp_decay_error, timeunit);
         } else if (!EXPDECAY_FREE) {
            char str4[80];
            sprintf(str4, "Background (exponential) decay constant: %.5f%s-1 (fixed)", background_exp_decay, timeunit);
         }
         text->AddText(str3);
         text->AddText(str4);
      }
      if (daughter) {
         if (DAUGHTER_FREE) {
            char str5[80];
            sprintf(str5, "Daughter half-life: %.3f +/- %.3f%s", daughter_halflife, daughter_halflife_error, timeunit);
         } else if (!DAUGHTER_FREE) {
            char str5[80];
            sprintf(str5, "Daughter half-life: %.3f%s (fixed)", daughter_halflife, timeunit);
         }
         text->AddText(str5);
      }
      if (granddaugh) {
         char str6[80];
         sprintf(str6, "Grand-daughter halflife: %.3f%s (fixed)", granddaughter, timeunit);
         text->AddText(str6);
      }
      if (neutronbranch) {
         char str7[80];
         sprintf (str7, "One-neutron branching ratio: %.3f (fixed)", ONE_NEUTRON);
         char str8[80];
         sprintf (str8, "One-neutron daughter half-life: %.3f%s (fixed)", one_neutron_halflife, timeunit);
         if (TWO_NEUTRON != 0) {
            char str9[80];
            sprintf(str9, "Two-neutron branching ratio: %.3f (fixed)", TWO_NEUTRON);
            char str10[80];
            sprintf(str10, "Two-neutron daughter half-life: %.3f%s (fixed)", two_neutron_halflife, timeunit);
         }
         text->AddText(str7);
         text->AddText(str8);
         if (TWO_NEUTRON != 0) {
            text->AddText(str9);
            text->AddText(str10);
         }
      }

      text->Draw("");
   }

   fCanvas->Update();

end:

}

void Fitter::Save() {

   int filetype = filechoice->GetSelected();
   TCanvas *fCanvas = fFitCanvas->GetCanvas();
   if (filetype == 1) {
      fCanvas->Print(savevalue->GetString(), "eps");
   } else if (filetype == 2) {
      fCanvas->Print(savevalue->GetString(), "ps");
   } else if (filetype == 3) {
      fCanvas->Print(savevalue->GetString(), "pdf");
   } else if (filetype == 4) {
      fCanvas->Print(savevalue->GetString(), "gif");
   } else if (filetype == 5) {
      fCanvas->Print(savevalue->GetString(), "jpg");
   } else if (filetype == 6) {
      fCanvas->Print(savevalue->GetString(), "png");
   }
}

InputExponential::InputExponential(const TGWindow *p, const TGWindow *main,
      UInt_t w, UInt_t h, UInt_t options) 
{
   // Create message box test dialog. Use this dialog to select the different
   // message dialog box styles and show the message dialog by clicking the
   // "Test" button.

   fMain = new TGTransientFrame(p, main, w, h, options);
   fMain->Connect("CloseWindow()", "InputExponential", this, "CloseWindow()");

   group = new TGGroupFrame(fMain, "Exponential Background Options", kVerticalFrame);
   fMain->AddFrame(group, new TGLayoutHints(kLHintsTop|kLHintsCenterX|kLHintsExpandX, 2,2,2,2));

   expFrame = new TGHorizontalFrame(group, 0, 0, 0);
   expFrame2 = new TGHorizontalFrame(group, 0, 0, 0);
   buttonFrame = new TGHorizontalFrame(fMain, 0, 0, 0);

   exp_decay = new TGNumberEntry(expFrame, EXPDECAY_GUESS, 12);
   expFrame->AddFrame(exp_decay, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
   exp_label = new TGLabel(expFrame, "Background Decay Constant (1/(time unit))");
   expFrame->AddFrame(exp_label, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
   group->AddFrame(expFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   exp_free = new TGCheckButton(expFrame2, "Keep background decay constant as free parameter?");
   expFrame2->AddFrame(exp_free, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 2,2,2,2));
   group->AddFrame(expFrame2, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   if (EXPDECAY_FREE) {
      exp_free->SetState(1);
   }

   okay = new TGTextButton(buttonFrame, "&OK");
   okay->Connect("Clicked()", "InputExponential", this, "DoOK()");
   buttonFrame->AddFrame(okay, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   cancel = new TGTextButton(buttonFrame, "&Cancel");
   cancel->Connect("Clicked()", "InputExponential", this, "DoCancel()");
   buttonFrame->AddFrame(cancel, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   fMain->AddFrame(buttonFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   fMain->MapSubwindows();
   fMain->Resize(fMain->GetDefaultSize());

   // position relative to the parent's window
   Window_t wdum;
   int ax, ay;
   gVirtualX->TranslateCoordinates(main->GetId(), fMain->GetParent()->GetId(),
         (Int_t)(((TGFrame *) main)->GetWidth() - fMain->GetWidth()) >> 1,
         (Int_t)(((TGFrame *) main)->GetHeight() - fMain->GetHeight()) >> 1,
         ax, ay, wdum);
   fMain->Move(ax, ay);

   fMain->SetWindowName("Exponential Background Entry");

   fMain->MapWindow();
   gClient->WaitFor(fMain);
}

// Order is important when deleting frames. Delete children first,
// parents last.

InputExponential::~InputExponential()
{
   // Delete widgets created by dialog.

   delete okay; delete cancel;
   delete exp_free; delete exp_decay;
   delete exp_label;
   delete buttonFrame; delete expFrame2; delete expFrame;
   delete group;
   delete fMain;
}

void InputExponential::CloseWindow()
{
   // Close dialog in response to window manager close.

   delete this;
}

void InputExponential::DoCancel()
{
   // Handle Close button.

   fMain->SendCloseMessage();
}

void InputExponential::DoOK()
{
   EXPDECAY_GUESS = (exp_decay->GetNumber());

   EXPDECAY_FREE = (exp_free->GetState() == kButtonDown);

   if (EXPDECAY_FREE) {
      cout << "Exponential background decay constant is a free parameter." << endl;
   } else {
      cout << "Exponential background decay constant is set to " << EXPDECAY_GUESS << " 1/time units." << endl;
   } 
   cout << "" << endl;

   fMain->SendCloseMessage();

}

InputComponents::InputComponents(const TGWindow *p, const TGWindow *main, 
      UInt_t w, UInt_t h, UInt_t options)
{
   fMain = new TGTransientFrame(p, main, w, h, options);
   fMain->Connect("CloseWindow()", "InputComponents", this, "CloseWindow()");

   group = new TGGroupFrame(fMain, "Two-Component Fit Options", kVerticalFrame);
   fMain->AddFrame(group, new TGLayoutHints(kLHintsTop|kLHintsCenterX|kLHintsExpandX, 2,2,2,2));

   comp1Frame = new TGHorizontalFrame(group, 0, 0, 0);
   comp1Frame2 = new TGHorizontalFrame(group, 0, 0, 0);
   comp2Frame = new TGHorizontalFrame(group, 0, 0, 0);
   comp2Frame2 = new TGHorizontalFrame(group, 0, 0, 0);
   frac2Frame = new TGHorizontalFrame(group, 0, 0, 0);
   frac2Frame2 = new TGHorizontalFrame(group, 0, 0, 0);
   buttonFrame = new TGHorizontalFrame(fMain, 0, 0, 0);

   comp1 = new TGNumberEntry(comp1Frame, LIFE_GUESS, 12);

   comp1Frame->AddFrame(comp1, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
   comp1Label = new TGLabel(comp1Frame, "Component 1 (i.e. ground state) Half-Life");
   comp1Frame->AddFrame(comp1Label, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
   group->AddFrame(comp1Frame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   freecomp1 = new TGCheckButton(comp1Frame2, "Keep component 1 half-life as free parameter?");
   comp1Frame2->AddFrame(freecomp1, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 2,2,2,2));
   group->AddFrame(comp1Frame2, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   comp2 = new TGNumberEntry(comp2Frame, COMPONENT2_GUESS, 12);

   comp2Frame->AddFrame(comp2, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
   comp2Label = new TGLabel(comp2Frame, "Component 2 (i.e. excited state) Half-Life");
   comp2Frame->AddFrame(comp2Label, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
   group->AddFrame(comp2Frame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   freecomp2 = new TGCheckButton(comp2Frame2, "Keep component 2 half-life as free parameter?");
   comp2Frame2->AddFrame(freecomp2, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 2,2,2,2));
   group->AddFrame(comp2Frame2, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   frac2 = new TGNumberEntry(frac2Frame, COMPONENT2_FRACTION, 12);
   frac2Frame->AddFrame(frac2, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
   frac2Label = new TGLabel(frac2Frame, "Fraction in State 2?");
   frac2Frame->AddFrame(frac2Label, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
   group->AddFrame(frac2Frame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   freefraction = new TGCheckButton(frac2Frame2, "Keep component 2 fraction as free parameter?");
   frac2Frame2->AddFrame(freefraction, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 2,2,2,2));
   group->AddFrame(frac2Frame2, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   if (FRACTION_FREE) {
      freefraction->SetState(1);
   }

   if (COMPONE_FREE) {
      freecomp1->SetState(1);
   }

   if (COMPTWO_FREE) {
      freecomp2->SetState(1);
   }

   okay = new TGTextButton(buttonFrame, "&OK");
   okay->Connect("Clicked()", "InputComponents", this, "DoOK()");
   buttonFrame->AddFrame(okay, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   cancel = new TGTextButton(buttonFrame, "&Cancel");
   cancel->Connect("Clicked()", "InputComponents", this, "DoCancel()");
   buttonFrame->AddFrame(cancel, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   fMain->AddFrame(buttonFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   fMain->MapSubwindows();
   fMain->Resize(fMain->GetDefaultSize());

   // position relative to the parent's window
   Window_t wdum;
   int ax, ay;
   gVirtualX->TranslateCoordinates(main->GetId(), fMain->GetParent()->GetId(),
         (Int_t)(((TGFrame *) main)->GetWidth() - fMain->GetWidth()) >> 1,
         (Int_t)(((TGFrame *) main)->GetHeight() - fMain->GetHeight()) >> 1,
         ax, ay, wdum);
   fMain->Move(ax, ay);

   fMain->SetWindowName("Two Component Information Entry");

   fMain->MapWindow();
   gClient->WaitFor(fMain);
}

// Order is important when deleting frames. Delete children first,
// parents last.

InputComponents::~InputComponents()
{
   // Delete widgets created by dialog.

   delete okay; delete cancel;
   delete comp1; delete comp2; delete frac2; delete freefraction;
   delete freecomp1; delete freecomp2;
   delete comp1Label; delete comp2Label; delete frac2Label;
   delete buttonFrame; delete comp1Frame; delete comp2Frame;
   delete frac2Frame; delete frac2Frame2; delete comp2Frame2; 
   delete comp1Frame2;
   delete group;
   delete fMain;
}

void InputComponents::CloseWindow()
{
   // Close dialog in response to window manager close.

   delete this;
}

void InputComponents::DoCancel()
{
   // Handle Close button.

   fMain->SendCloseMessage();
}

void InputComponents::DoOK()
{
   FRACTION_FREE = (freefraction->GetState() == kButtonDown);

   COMPONE_FREE = (freecomp1->GetState() == kButtonDown);
   COMPTWO_FREE = (freecomp2->GetState() == kButtonDown);

   LIFE_GUESS = comp1->GetNumber();

   COMPONENT2_GUESS = comp2->GetNumber();

   COMPONENT2_FRACTION = (frac2->GetNumber());

   if (COMPONE_FREE) {
      cout << "Component 1 half-life is a free parameter." << endl;
   } else {
      cout << "Component 1 Half-life is " << comp1->GetNumber() << " time units." << endl;
   }
   if (COMPTWO_FREE) {
      cout << "Component 2 half-life is a free parameter." << endl;
   } else {
      cout << "Component 2 Half-life is " << comp2->GetNumber() << " time units." << endl;
   }
   if (FRACTION_FREE) {
      cout << "Fraction of component 2 is a free parameter." << endl;
   } else {
      cout << "Fraction of component 2 is " << frac2->GetNumber() << " time units." << endl;
   }
   cout << "" << endl;

   fMain->SendCloseMessage();

}

InputDaughter::InputDaughter(const TGWindow *p, const TGWindow *main,
      UInt_t w, UInt_t h, UInt_t options) 
{
   // Create message box test dialog. Use this dialog to select the different
   // message dialog box styles and show the message dialog by clicking the
   // "Test" button.

   fMain = new TGTransientFrame(p, main, w, h, options);
   fMain->Connect("CloseWindow()", "InputDaughter", this, "CloseWindow()");

   group = new TGGroupFrame(fMain, "Half-life Options", kVerticalFrame);
   fMain->AddFrame(group, new TGLayoutHints(kLHintsTop|kLHintsCenterX|kLHintsExpandX, 2,2,2,2));

   daughFrame = new TGHorizontalFrame(group, 0, 0, 0);
   daughFrame2 = new TGHorizontalFrame(group, 0, 0, 0);
   buttonFrame = new TGHorizontalFrame(fMain, 0, 0, 0);

   daugh_life = new TGNumberEntry(daughFrame, DAUGHTER_GUESS, 12);

   daughFrame->AddFrame(daugh_life, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
   daugh_label = new TGLabel(daughFrame, "Beta Daughter Half-life");
   daughFrame->AddFrame(daugh_label, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
   group->AddFrame(daughFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   daugh_free = new TGCheckButton(daughFrame2, "Keep daughter half-life as free parameter?");
   daughFrame2->AddFrame(daugh_free, new TGLayoutHints(kLHintsTop|kLHintsCenterX, 2,2,2,2));
   group->AddFrame(daughFrame2, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   if (DAUGHTER_FREE) {
      daugh_free->SetState(1);
   }

   okay = new TGTextButton(buttonFrame, "&OK");
   okay->Connect("Clicked()", "InputDaughter", this, "DoOK()");
   buttonFrame->AddFrame(okay, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   cancel = new TGTextButton(buttonFrame, "&Cancel");
   cancel->Connect("Clicked()", "InputDaughter", this, "DoCancel()");
   buttonFrame->AddFrame(cancel, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   fMain->AddFrame(buttonFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   fMain->MapSubwindows();
   fMain->Resize(fMain->GetDefaultSize());

   // position relative to the parent's window
   Window_t wdum;
   int ax, ay;
   gVirtualX->TranslateCoordinates(main->GetId(), fMain->GetParent()->GetId(),
         (Int_t)(((TGFrame *) main)->GetWidth() - fMain->GetWidth()) >> 1,
         (Int_t)(((TGFrame *) main)->GetHeight() - fMain->GetHeight()) >> 1,
         ax, ay, wdum);
   fMain->Move(ax, ay);

   fMain->SetWindowName("Daughter Half-life Entry");

   fMain->MapWindow();
   gClient->WaitFor(fMain);
}

// Order is important when deleting frames. Delete children first,
// parents last.

InputDaughter::~InputDaughter()
{
   // Delete widgets created by dialog.

   delete okay; delete cancel;
   delete daugh_free; delete daugh_life;
   delete daugh_label;
   delete buttonFrame; delete daughFrame2; delete daughFrame;
   delete group;
   delete fMain;
}

void InputDaughter::CloseWindow()
{
   // Close dialog in response to window manager close.

   delete this;
}

void InputDaughter::DoCancel()
{
   // Handle Close button.

   fMain->SendCloseMessage();
}

void InputDaughter::DoOK()
{
   DAUGHTER_GUESS = daugh_life->GetNumber();

   DAUGHTER_FREE = (daugh_free->GetState() == kButtonDown);

   if (DAUGHTER_FREE) {
      cout << "Beta-daughter half-life is a free parameter." << endl;
   } else if (DAUGHTER_GUESS!=0) {
      cout << "Beta-daughter half-life set to " << DAUGHTER_GUESS << " time units." << endl;
   } else {
      cout << "Beta-daughter half-life is set to 0 time units." << endl;
   }
   cout << "" << endl;

   fMain->SendCloseMessage();

}

InputGrand::InputGrand(const TGWindow *p, const TGWindow *main,
      UInt_t w, UInt_t h, UInt_t options) 
{
   // Create message box test dialog. Use this dialog to select the different
   // message dialog box styles and show the message dialog by clicking the
   // "Test" button.

   fMain = new TGTransientFrame(p, main, w, h, options);
   fMain->Connect("CloseWindow()", "InputGrand", this, "CloseWindow()");

   group = new TGGroupFrame(fMain, "Half-life Options", kVerticalFrame);
   fMain->AddFrame(group, new TGLayoutHints(kLHintsTop|kLHintsCenterX|kLHintsExpandX, 2,2,2,2));

   grandFrame = new TGHorizontalFrame(group, 0, 0, 0);
   buttonFrame = new TGHorizontalFrame(fMain, 0, 0, 0);

   grand_life = new TGNumberEntry(grandFrame, GRANDDAUGHTER, 12);

   grandFrame->AddFrame(grand_life, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
   grand_label = new TGLabel(grandFrame, "Beta Grand-Daughter Half-life");
   grandFrame->AddFrame(grand_label, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
   group->AddFrame(grandFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   okay = new TGTextButton(buttonFrame, "&OK");
   okay->Connect("Clicked()", "InputGrand", this, "DoOK()");
   buttonFrame->AddFrame(okay, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   cancel = new TGTextButton(buttonFrame, "&Cancel");
   cancel->Connect("Clicked()", "InputGrand", this, "DoCancel()");
   buttonFrame->AddFrame(cancel, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   fMain->AddFrame(buttonFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   fMain->MapSubwindows();
   fMain->Resize(fMain->GetDefaultSize());

   // position relative to the parent's window
   Window_t wdum;
   int ax, ay;
   gVirtualX->TranslateCoordinates(main->GetId(), fMain->GetParent()->GetId(),
         (Int_t)(((TGFrame *) main)->GetWidth() - fMain->GetWidth()) >> 1,
         (Int_t)(((TGFrame *) main)->GetHeight() - fMain->GetHeight()) >> 1,
         ax, ay, wdum);
   fMain->Move(ax, ay);

   fMain->SetWindowName("Grand-Daughter Half-life Entry");

   fMain->MapWindow();
   gClient->WaitFor(fMain);
}

// Order is important when deleting frames. Delete children first,
// parents last.

InputGrand::~InputGrand()
{
   // Delete widgets created by dialog.

   delete okay; delete cancel;
   delete grand_life;
   delete grand_label;
   delete buttonFrame; delete grandFrame;
   delete group;
   delete fMain;
}

void InputGrand::CloseWindow()
{
   // Close dialog in response to window manager close.

   delete this;
}

void InputGrand::DoCancel()
{
   // Handle Close button.

   fMain->SendCloseMessage();
}

void InputGrand::DoOK()
{
   GRANDDAUGHTER = (grand_life->GetNumber());

   if (GRANDDAUGHTER != 0) { 
      cout << "Beta grand-daughter half-life set to " << GRANDDAUGHTER << " time units." << endl;
   } else {
      cout << "Beta grand-daughter half-life is set to 0 time units." << endl;
   }

   cout << "" << endl;

   fMain->SendCloseMessage();

}

InputNeutron::InputNeutron(const TGWindow *p, const TGWindow *main,
      UInt_t w, UInt_t h, UInt_t options) 
{
   // Create message box test dialog. Use this dialog to select the different
   // message dialog box styles and show the message dialog by clicking the
   // "Test" button.

   fMain = new TGTransientFrame(p, main, w, h, options);
   fMain->Connect("CloseWindow()", "InputNeutron", this, "CloseWindow()");

   group = new TGGroupFrame(fMain, "Neutron Branching Options", kVerticalFrame);
   fMain->AddFrame(group, new TGLayoutHints(kLHintsTop|kLHintsCenterX|kLHintsExpandX, 2,2,2,2));

   oneBranchFrame = new TGHorizontalFrame(group, 0, 0, 0);
   oneLifeFrame = new TGHorizontalFrame(group, 0, 0, 0);
   twoBranchFrame = new TGHorizontalFrame(group, 0, 0, 0);
   twoLifeFrame = new TGHorizontalFrame(group, 0, 0, 0);
   buttonFrame = new TGHorizontalFrame(fMain, 0, 0, 0);

   oneBranch = new TGNumberEntry(oneBranchFrame, ONE_NEUTRON, 12);

   oneBranchFrame->AddFrame(oneBranch, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
   oneBranchLabel = new TGLabel(oneBranchFrame, "Parent Beta-1n Branching Ratio");
   oneBranchFrame->AddFrame(oneBranchLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
   group->AddFrame(oneBranchFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   oneLife = new TGNumberEntry(oneLifeFrame, DAUGHTER_ONENEUTRON, 12);

   oneLifeFrame->AddFrame(oneLife, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
   oneLifeLabel = new TGLabel(oneLifeFrame, "Beta-1n Daughter Half-life");
   oneLifeFrame->AddFrame(oneLifeLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
   group->AddFrame(oneLifeFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   twoBranch = new TGNumberEntry(twoBranchFrame, TWO_NEUTRON, 12);

   twoBranchFrame->AddFrame(twoBranch, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
   twoBranchLabel = new TGLabel(twoBranchFrame, "Parent Beta-2n Branching Ratio");
   twoBranchFrame->AddFrame(twoBranchLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
   group->AddFrame(twoBranchFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   twoLife = new TGNumberEntry(twoLifeFrame, DAUGHTER_TWONEUTRON, 12);

   twoLifeFrame->AddFrame(twoLife, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
   twoLifeLabel = new TGLabel(twoLifeFrame, "Beta-2n Daughter Half-life");
   twoLifeFrame->AddFrame(twoLifeLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
   group->AddFrame(twoLifeFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   okay = new TGTextButton(buttonFrame, "&OK");
   okay->Connect("Clicked()", "InputNeutron", this, "DoOK()");
   buttonFrame->AddFrame(okay, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   cancel = new TGTextButton(buttonFrame, "&Cancel");
   cancel->Connect("Clicked()", "InputNeutron", this, "DoCancel()");
   buttonFrame->AddFrame(cancel, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   fMain->AddFrame(buttonFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   fMain->MapSubwindows();
   fMain->Resize(fMain->GetDefaultSize());

   // position relative to the parent's window
   Window_t wdum;
   int ax, ay;
   gVirtualX->TranslateCoordinates(main->GetId(), fMain->GetParent()->GetId(),
         (Int_t)(((TGFrame *) main)->GetWidth() - fMain->GetWidth()) >> 1,
         (Int_t)(((TGFrame *) main)->GetHeight() - fMain->GetHeight()) >> 1,
         ax, ay, wdum);
   fMain->Move(ax, ay);

   fMain->SetWindowName("Neutron Branching Entry");

   fMain->MapWindow();
   gClient->WaitFor(fMain);
}

// Order is important when deleting frames. Delete children first,
// parents last.

InputNeutron::~InputNeutron()
{
   // Delete widgets created by dialog.

   delete okay; delete cancel;
   delete oneBranch; delete twoBranch; delete oneLife; delete twoLife;
   delete oneBranchLabel; delete twoBranchLabel; delete oneLifeLabel; delete twoLifeLabel;
   delete buttonFrame; delete oneBranchFrame; delete twoBranchFrame;
   delete oneLifeFrame; delete twoLifeFrame;
   delete group;
   delete fMain;
}

void InputNeutron::CloseWindow()
{
   // Close dialog in response to window manager close.

   delete this;
}

void InputNeutron::DoCancel()
{
   // Handle Close button.

   fMain->SendCloseMessage();
}

void InputNeutron::DoOK()
{

   if (oneBranch->GetNumber() != 0) {
      ONE_NEUTRON = oneBranch->GetNumber();
   } else {
      ONE_NEUTRON = 0;
   }

   if (twoBranch->GetNumber() != 0) {
      TWO_NEUTRON = twoBranch->GetNumber();
   } else {
      TWO_NEUTRON = 0;
   }

   if (oneLife->GetNumber() != 0) {
      DAUGHTER_ONENEUTRON = oneLife->GetNumber();
   } else {
      DAUGHTER_ONENEUTRON = 0;
   }

   if (twoLife->GetNumber() != 0) {
      DAUGHTER_TWONEUTRON = twoLife->GetNumber();
   } else {
      DAUGHTER_TWONEUTRON = 0;
   }

   int retval; 

   if (ONE_NEUTRON + TWO_NEUTRON > 1) {
      new TGMsgBox(gClient->GetRoot(), fMain,
            "Something is weird...", "The branching ratios you have entered sum to more than 1.\n This is non-physical.\n Please enter new values.", kMBIconStop, kMBDismiss, &retval);
   } else {
      cout << "Beta-1n branching ratio is " << ONE_NEUTRON << endl;
      if (DAUGHTER_ONENEUTRON != 0) {
         cout << "Beta-1n daughter half-life is " << DAUGHTER_ONENEUTRON << " time units." << endl;
      } else {
         cout << "Beta-1n daughter half-life is 0 time units." << endl;
      }
      cout << "Beta-2n branching ratio is " << TWO_NEUTRON << endl;
      if (DAUGHTER_TWONEUTRON != 0) {
         cout << "Beta-2n daughter half-life is " << DAUGHTER_TWONEUTRON << " time units." << endl;
      } else {
         cout << "Beta-2n daughter half-life is 0 time units." << endl;
      }

      cout << "" << endl;

      fMain->SendCloseMessage();
   }

}

InputParameters::InputParameters(const TGWindow *p, const TGWindow *main,
      UInt_t w, UInt_t h, UInt_t options) 
{
   // Create message box test dialog. Use this dialog to select the different
   // message dialog box styles and show the message dialog by clicking the
   // "Test" button.

   fMain = new TGTransientFrame(p, main, w, h, options);
   fMain->Connect("CloseWindow()", "InputParameters", this, "CloseWindow()");

   if (!TWOCOMP) {
      group1 = new TGGroupFrame(fMain, "Parent Half-life Parameter Control", kVerticalFrame);
      fMain->AddFrame(group1, new TGLayoutHints(kLHintsTop|kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   }

   if (DAUGHTER_FREE) {
      group2 = new TGGroupFrame(fMain, "Daughter Half-life Parameter Control", kVerticalFrame);
      fMain->AddFrame(group2, new TGLayoutHints(kLHintsTop|kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   }

   if (LINEAR || EXP) {
      group3 = new TGGroupFrame(fMain, "Background Parameter Control", kVerticalFrame);
      fMain->AddFrame(group3, new TGLayoutHints(kLHintsTop|kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   }

   group4 = new TGGroupFrame(fMain, "Initial Activity Parameter Control", kVerticalFrame);
   fMain->AddFrame(group4, new TGLayoutHints(kLHintsTop|kLHintsCenterX|kLHintsExpandX, 2,2,2,2));

   if (TWOCOMP) {
      if (FRACTION_FREE || COMPONE_FREE || COMPTWO_FREE) {
         group5 = new TGGroupFrame(fMain, "Two-Component Fit Parameter Control", kVerticalFrame);
         fMain->AddFrame(group5, new TGLayoutHints(kLHintsTop|kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
      }      
   }

   if (!TWOCOMP) {
      lifeGuessFrame = new TGHorizontalFrame(group1, 0, 0, 0);
      lifeLowFrame = new TGHorizontalFrame(group1, 0, 0, 0);
      lifeHighFrame = new TGHorizontalFrame(group1, 0, 0, 0);
   }

   if (DAUGHTER_FREE) {
      daughterGuessFrame = new TGHorizontalFrame(group2, 0, 0, 0);
      daughterLowFrame = new TGHorizontalFrame(group2, 0, 0, 0);
      daughterHighFrame = new TGHorizontalFrame(group2, 0, 0, 0);
   }

   if (LINEAR) {
      backLinGuessFrame = new TGHorizontalFrame(group3, 0, 0, 0);
      backLinLowFrame = new TGHorizontalFrame(group3, 0, 0, 0);
      backLinHighFrame = new TGHorizontalFrame(group3, 0, 0, 0);
   }

   if (EXP) {
      if (EXPDECAY_FREE) {
         expDecayGuessFrame = new TGHorizontalFrame(group3, 0, 0, 0);
         expDecayLowFrame = new TGHorizontalFrame(group3, 0, 0, 0);
         expDecayHighFrame = new TGHorizontalFrame(group3, 0, 0, 0);
      }
      expInitGuessFrame = new TGHorizontalFrame(group3, 0, 0, 0);
      expInitLowFrame = new TGHorizontalFrame(group3, 0, 0, 0);
      expInitHighFrame = new TGHorizontalFrame(group3, 0, 0, 0);
   }

   if (TWOCOMP) {
      if (FRACTION_FREE) {
         fracGuessFrame = new TGHorizontalFrame(group5, 0, 0, 0);
         fracLowFrame = new TGHorizontalFrame(group5, 0, 0, 0);
         fracHighFrame = new TGHorizontalFrame(group5, 0, 0, 0);
      } 
      if (COMPONE_FREE) {
         lifeGuessFrame = new TGHorizontalFrame(group5, 0, 0, 0);
         lifeLowFrame = new TGHorizontalFrame(group5, 0, 0, 0);
         lifeHighFrame = new TGHorizontalFrame(group5, 0, 0, 0);
      }
      if (COMPTWO_FREE) {
         component2GuessFrame = new TGHorizontalFrame(group5, 0, 0, 0);
         component2LowFrame = new TGHorizontalFrame(group5, 0, 0, 0);
         component2HighFrame = new TGHorizontalFrame(group5, 0, 0, 0);
      }
   }

   initialGuessFrame = new TGHorizontalFrame(group4, 0, 0, 0);
   initialLowFrame = new TGHorizontalFrame(group4, 0, 0, 0);
   initialHighFrame = new TGHorizontalFrame(group4, 0, 0, 0);

   buttonFrame = new TGHorizontalFrame(fMain, 0, 0, 0);

   if (!TWOCOMP){
      if (LIFE_GUESS != 0) {
         lifeGuessNum = new TGNumberEntry(lifeGuessFrame, LIFE_GUESS, 12);
      } else {
         lifeGuessNum = new TGNumberEntry(lifeGuessFrame, 0, 12);
      }
      lifeGuessFrame->AddFrame(lifeGuessNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
      lifeGuessLabel = new TGLabel(lifeGuessFrame, "Guess for Half-life?");
      lifeGuessFrame->AddFrame(lifeGuessLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
      group1->AddFrame(lifeGuessFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

      lifeLowNum = new TGNumberEntry(lifeLowFrame, LIFE_LOW_LIMIT, 12);

      lifeLowFrame->AddFrame(lifeLowNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
      lifeLowLabel = new TGLabel(lifeLowFrame, "Lower Bound for Half-life?");
      lifeLowFrame->AddFrame(lifeLowLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
      group1->AddFrame(lifeLowFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

      lifeHighNum = new TGNumberEntry(lifeHighFrame, LIFE_HIGH_LIMIT, 12);

      lifeHighFrame->AddFrame(lifeHighNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
      lifeHighLabel = new TGLabel(lifeHighFrame, "Upper Bound for Half-life?");
      lifeHighFrame->AddFrame(lifeHighLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
      group1->AddFrame(lifeHighFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));
   }

   if (DAUGHTER_FREE) {

      daughterGuessNum = new TGNumberEntry(daughterGuessFrame, DAUGHTER_GUESS, 12);

      daughterGuessFrame->AddFrame(daughterGuessNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
      daughterGuessLabel = new TGLabel(daughterGuessFrame, "Guess for Daughter Half-life?");
      daughterGuessFrame->AddFrame(daughterGuessLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
      group2->AddFrame(daughterGuessFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

      daughterLowNum = new TGNumberEntry(daughterLowFrame, DAUGHTER_LOW_LIMIT, 12);

      daughterLowFrame->AddFrame(daughterLowNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
      daughterLowLabel = new TGLabel(daughterLowFrame, "Lower Bound for Daughter Half-life?");
      daughterLowFrame->AddFrame(daughterLowLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
      group2->AddFrame(daughterLowFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

      daughterHighNum = new TGNumberEntry(daughterHighFrame, DAUGHTER_HIGH_LIMIT, 12);

      daughterHighFrame->AddFrame(daughterHighNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
      daughterHighLabel = new TGLabel(daughterHighFrame, "Upper Bound for Daughter Half-life?");
      daughterHighFrame->AddFrame(daughterHighLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
      group2->AddFrame(daughterHighFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));
   }

   if (LINEAR) {
      backLinGuessNum = new TGNumberEntry(backLinGuessFrame, BACKLIN_GUESS, 12);
      backLinGuessFrame->AddFrame(backLinGuessNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
      backLinGuessLabel = new TGLabel(backLinGuessFrame, "Guess for Background (linear)?");
      backLinGuessFrame->AddFrame(backLinGuessLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
      group3->AddFrame(backLinGuessFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

      backLinLowNum = new TGNumberEntry(backLinLowFrame, BACKLIN_LOW_LIMIT, 12);
      backLinLowFrame->AddFrame(backLinLowNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
      backLinLowLabel = new TGLabel(backLinLowFrame, "Lower Bound for Background (linear)?");
      backLinLowFrame->AddFrame(backLinLowLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
      group3->AddFrame(backLinLowFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

      backLinHighNum = new TGNumberEntry(backLinHighFrame, BACKLIN_HIGH_LIMIT, 12);
      backLinHighFrame->AddFrame(backLinHighNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
      backLinHighLabel = new TGLabel(backLinHighFrame, "Upper Bound for Background (linear)?");
      backLinHighFrame->AddFrame(backLinHighLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
      group3->AddFrame(backLinHighFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));
   }

   if (EXP) {
      if (EXPDECAY_FREE) {
         expDecayGuessNum = new TGNumberEntry(expDecayGuessFrame, EXPDECAY_GUESS, 12);
         expDecayGuessFrame->AddFrame(expDecayGuessNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
         expDecayGuessLabel = new TGLabel(expDecayGuessFrame, "Guess for Background Decay Constant (exp)?");
         expDecayGuessFrame->AddFrame(expDecayGuessLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
         group3->AddFrame(expDecayGuessFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

         expDecayLowNum = new TGNumberEntry(expDecayLowFrame, EXPDECAY_LOW_LIMIT, 12);
         expDecayLowFrame->AddFrame(expDecayLowNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
         expDecayLowLabel = new TGLabel(expDecayLowFrame, "Lower Bound for Background Decay Constant (exp)?");
         expDecayLowFrame->AddFrame(expDecayLowLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
         group3->AddFrame(expDecayLowFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

         expDecayHighNum = new TGNumberEntry(expDecayHighFrame, EXPDECAY_HIGH_LIMIT, 12);
         expDecayHighFrame->AddFrame(expDecayHighNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
         expDecayHighLabel = new TGLabel(expDecayHighFrame, "Upper Bound for Background Decay Constant (exp)?");
         expDecayHighFrame->AddFrame(expDecayHighLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
         group3->AddFrame(expDecayHighFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));
      }
      expInitGuessNum = new TGNumberEntry(expInitGuessFrame, EXPINIT_GUESS, 12);
      expInitGuessFrame->AddFrame(expInitGuessNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
      expInitGuessLabel = new TGLabel(expInitGuessFrame, "Guess for Background Initial Value (exp)?");
      expInitGuessFrame->AddFrame(expInitGuessLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
      group3->AddFrame(expInitGuessFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

      expInitLowNum = new TGNumberEntry(expInitLowFrame, EXPINIT_LOW_LIMIT, 12);
      expInitLowFrame->AddFrame(expInitLowNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
      expInitLowLabel = new TGLabel(expInitLowFrame, "Lower Bound for Background Initial Value (exp)?");
      expInitLowFrame->AddFrame(expInitLowLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
      group3->AddFrame(expInitLowFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

      expInitHighNum = new TGNumberEntry(expInitHighFrame, EXPINIT_HIGH_LIMIT, 12);
      expInitHighFrame->AddFrame(expInitHighNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
      expInitHighLabel = new TGLabel(expInitHighFrame, "Upper Bound for Background Initial Value (exp)?");
      expInitHighFrame->AddFrame(expInitHighLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
      group3->AddFrame(expInitHighFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));
   }

   if (TWOCOMP && FRACTION_FREE) {
      if (FRACTION_FREE){
         fracGuessNum = new TGNumberEntry(fracGuessFrame, COMPONENT2_FRACTION, 12);
         fracGuessFrame->AddFrame(fracGuessNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
         fracGuessLabel = new TGLabel(fracGuessFrame, "Guess for Fraction of Component 2?");
         fracGuessFrame->AddFrame(fracGuessLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
         group5->AddFrame(fracGuessFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

         fracLowNum = new TGNumberEntry(fracLowFrame, COMPONENT2_FRACTION_LOW_LIMIT, 12);
         fracLowFrame->AddFrame(fracLowNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
         fracLowLabel = new TGLabel(fracLowFrame, "Lower Bound for Fraction of Component 2?");
         fracLowFrame->AddFrame(fracLowLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
         group5->AddFrame(fracLowFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

         fracHighNum = new TGNumberEntry(fracHighFrame, COMPONENT2_FRACTION_HIGH_LIMIT, 12);
         fracHighFrame->AddFrame(fracHighNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
         fracHighLabel = new TGLabel(fracHighFrame, "Upper Bound for Fraction of Component 2?");
         fracHighFrame->AddFrame(fracHighLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
         group5->AddFrame(fracHighFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));
      }
      if (COMPONE_FREE) {
         if (LIFE_GUESS != 0) {
            lifeGuessNum = new TGNumberEntry(lifeGuessFrame, LIFE_GUESS, 12);
         } else {
            lifeGuessNum = new TGNumberEntry(lifeGuessFrame, 0, 12);
         }
         lifeGuessFrame->AddFrame(lifeGuessNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
         lifeGuessLabel = new TGLabel(lifeGuessFrame, "Guess for component 1 Half-life?");
         lifeGuessFrame->AddFrame(lifeGuessLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
         group5->AddFrame(lifeGuessFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

         lifeLowNum = new TGNumberEntry(lifeLowFrame, LIFE_LOW_LIMIT, 12);

         lifeLowFrame->AddFrame(lifeLowNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
         lifeLowLabel = new TGLabel(lifeLowFrame, "Lower Bound for component 1 half-life?");
         lifeLowFrame->AddFrame(lifeLowLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
         group5->AddFrame(lifeLowFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

         lifeHighNum = new TGNumberEntry(lifeHighFrame, LIFE_HIGH_LIMIT, 12);

         lifeHighFrame->AddFrame(lifeHighNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
         lifeHighLabel = new TGLabel(lifeHighFrame, "Upper Bound for component 1 half-life?");
         lifeHighFrame->AddFrame(lifeHighLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
         group5->AddFrame(lifeHighFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));
      }
      if (COMPTWO_FREE) {
         if (COMPONENT2_GUESS != 0) {
            component2GuessNum = new TGNumberEntry(component2GuessFrame, COMPONENT2_GUESS, 12);
         } else {
            component2GuessNum = new TGNumberEntry(component2GuessFrame, 0, 12);
         }
         component2GuessFrame->AddFrame(component2GuessNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
         component2GuessLabel = new TGLabel(component2GuessFrame, "Guess for component 2 half-life?");
         component2GuessFrame->AddFrame(component2GuessLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
         group5->AddFrame(component2GuessFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

         component2LowNum = new TGNumberEntry(component2LowFrame, LIFE_LOW_LIMIT, 12);

         component2LowFrame->AddFrame(component2LowNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
         component2LowLabel = new TGLabel(component2LowFrame, "Lower Bound for component 2 half-life?");
         component2LowFrame->AddFrame(component2LowLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
         group5->AddFrame(component2LowFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

         component2HighNum = new TGNumberEntry(component2HighFrame, LIFE_HIGH_LIMIT, 12);

         component2HighFrame->AddFrame(component2HighNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
         component2HighLabel = new TGLabel(component2HighFrame, "Upper Bound for component 2 half-life?");
         component2HighFrame->AddFrame(component2HighLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
         group5->AddFrame(component2HighFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));
      }
   }

   initialGuessNum = new TGNumberEntry(initialGuessFrame, INITIAL_GUESS, 12);
   initialGuessFrame->AddFrame(initialGuessNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
   initialGuessLabel = new TGLabel(initialGuessFrame, "Guess for Initial Activity?");
   initialGuessFrame->AddFrame(initialGuessLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2)); 
   group4->AddFrame(initialGuessFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   initialLowNum = new TGNumberEntry(initialLowFrame, INITIAL_LOW_LIMIT, 12);
   initialLowFrame->AddFrame(initialLowNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
   initialLowLabel = new TGLabel(initialLowFrame, "Lower Bound for Initial Activity?");
   initialLowFrame->AddFrame(initialLowLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
   group4->AddFrame(initialLowFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   initialHighNum = new TGNumberEntry(initialHighFrame, INITIAL_HIGH_LIMIT, 12);
   initialHighFrame->AddFrame(initialHighNum, new TGLayoutHints(kLHintsRight|kLHintsCenterY, 2,2,2,2));
   initialHighLabel = new TGLabel(initialHighFrame, "Upper Bound for Initial Activity?");
   initialHighFrame->AddFrame(initialHighLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 2,2,2,2));
   group4->AddFrame(initialHighFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   okay = new TGTextButton(buttonFrame, "&OK");
   okay->Connect("Clicked()", "InputParameters", this, "DoOK()");
   buttonFrame->AddFrame(okay, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   cancel = new TGTextButton(buttonFrame, "&Cancel");
   cancel->Connect("Clicked()", "InputParameters", this, "DoCancel()");
   buttonFrame->AddFrame(cancel, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
   fMain->AddFrame(buttonFrame, new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandX, 2,2,2,2));

   fMain->MapSubwindows();
   fMain->Resize(fMain->GetDefaultSize());

   // position relative to the parent's window
   Window_t wdum;
   int ax, ay;
   gVirtualX->TranslateCoordinates(main->GetId(), fMain->GetParent()->GetId(),
         (Int_t)(((TGFrame *) main)->GetWidth() - fMain->GetWidth()) >> 1,
         (Int_t)(((TGFrame *) main)->GetHeight() - fMain->GetHeight()) >> 1,
         ax, ay, wdum);
   fMain->Move(ax, ay);
   fMain->SetWindowName("Parameter Entry");
   fMain->MapWindow();
   gClient->WaitFor(fMain);
}

// Order is important when deleting frames. Delete children first,
// parents last.

InputParameters::~InputParameters()
{
   // Delete widgets created by dialog.

   delete okay; delete cancel;
   if (!TWOCOMP) {
      delete lifeGuessNum; delete lifeLowNum; delete lifeHighNum;
      delete lifeGuessLabel; delete lifeLowLabel; delete lifeHighLabel;
      delete lifeGuessFrame; delete lifeLowFrame; delete lifeHighFrame;
   }
   delete initialGuessNum; delete initialLowNum; delete initialHighNum;
   delete initialGuessLabel; delete initialLowLabel; delete initialHighLabel;
   delete initialGuessFrame; delete initialLowFrame; delete initialHighFrame;
   if (DAUGHTER_FREE) {
      delete daughterGuessNum; delete daughterLowNum; delete daughterHighNum;
      delete daughterGuessLabel; delete daughterLowLabel; delete daughterHighLabel;
      delete daughterGuessFrame; delete daughterLowFrame; delete daughterHighFrame;
   }
   if (LINEAR) {
      delete backLinGuessNum; delete backLinLowNum; delete backLinHighNum;
      delete backLinGuessLabel; delete backLinLowLabel; delete backLinHighLabel;
      delete backLinGuessFrame; delete backLinLowFrame; delete backLinHighFrame;
   }
   if (TWOCOMP && FRACTION_FREE) {
      delete fracGuessNum; delete fracLowNum; delete fracHighNum;
      delete fracGuessLabel; delete fracLowLabel; delete fracHighLabel;
      delete fracGuessFrame; delete fracLowFrame; delete fracHighFrame;
   }
   if (TWOCOMP && COMPONE_FREE) {
      delete lifeGuessNum; delete lifeLowNum; delete lifeHighNum;
      delete lifeGuessLabel; delete lifeLowLabel; delete lifeHighLabel;
      delete lifeGuessFrame; delete lifeLowFrame; delete lifeHighFrame;
   }
   if (TWOCOMP && COMPTWO_FREE) {
      delete component2GuessNum; delete component2LowNum; delete component2HighNum;
      //  delete component2GuessLabel; 
      //  delete component2LowLabel; delete component2HighLabel;
      delete component2GuessFrame; delete component2LowFrame; delete component2HighFrame;
   }
   if (EXP) { 
      if (EXPDECAY_FREE) {
         delete expDecayGuessNum; delete expDecayLowNum; delete expDecayHighNum;
         delete expDecayGuessLabel; delete expDecayLowLabel; delete expDecayHighLabel;
         delete expDecayGuessFrame; delete expDecayLowFrame; delete expDecayHighFrame;
      }
      delete expInitGuessNum; delete expInitLowNum; delete expInitHighNum;
      delete expInitGuessLabel; delete expInitLowLabel; delete expInitHighLabel;
      delete expInitGuessFrame; delete expInitLowFrame; delete expInitHighFrame;
   }
   delete buttonFrame;
   if (!TWOCOMP) {
      delete group1;
   } 
   if (DAUGHTER_FREE) {
      delete group2; 
   }
   if (LINEAR || EXP) {
      delete group3; 
   }
   delete group4;
   if (TWOCOMP && (FRACTION_FREE || COMPONE_FREE || COMPTWO_FREE)) {
      delete group5;
   }
   delete fMain;
}

void InputParameters::CloseWindow()
{
   // Close dialog in response to window manager close.

   delete this;
}

void InputParameters::DoCancel()
{
   // Handle Close button.

   fMain->SendCloseMessage();
}

void InputParameters::DoOK()
{

   if (!TWOCOMP) {
      if (lifeGuessNum->GetNumber() != 0) {
         LIFE_GUESS = lifeGuessNum->GetNumber();
         cout << "Guess for half-life is set to " << LIFE_GUESS << "." << endl;
      } else {
         LIFE_GUESS = 0;
         cout << "Guess for half-life is set to 0." << endl;
      }

      if (lifeLowNum->GetNumber() != 0) {
         LIFE_LOW_LIMIT = lifeLowNum->GetNumber();
         cout << "The half-life lower bound is " << LIFE_LOW_LIMIT << "." << endl;
      } else {
         LIFE_LOW_LIMIT = 0;
         cout << "The half-life lower bound is 0." << endl;
      }

      if (lifeHighNum->GetNumber() != 0) {
         LIFE_HIGH_LIMIT = (lifeHighNum->GetNumber());
         cout << "The half-life upper bound is " << LIFE_HIGH_LIMIT << "." << endl;
      } else {
         LIFE_HIGH_LIMIT = 0;
         cout << "The half-life upper bound is 0." << endl;
      }

      int retval;

      if (lifeLowNum->GetNumber() >= lifeHighNum->GetNumber()) {
         new TGMsgBox(gClient->GetRoot(), fMain,
               "Something is weird...", "Your upper half-life  bound is below your lower bound.\n This doesn't make any sense.\n Please fix this.", kMBIconStop, kMBDismiss, &retval);
         goto end;
      } else if ((lifeGuessNum->GetNumber() < lifeLowNum->GetNumber()) || (lifeGuessNum->GetNumber() > lifeHighNum->GetNumber())) {
         new TGMsgBox(gClient->GetRoot(), fMain, 
               "Something is weird...", "Your half-life guess is out of the limits you set.\n That's silly. Please fix this.", kMBIconStop, kMBDismiss, &retval);
         goto end;
      }

   }
   if (DAUGHTER_FREE){
      if (daughterGuessNum->GetNumber() != 0) {
         DAUGHTER_GUESS = (daughterGuessNum->GetNumber());
         cout << "Guess for daughter half-life is set to " << DAUGHTER_GUESS << "." << endl;
      } else {
         DAUGHTER_GUESS = 0;
         cout << "Guess for daughter half-life is set to 0." << endl;
      }

      if (daughterLowNum->GetNumber() != 0) {
         DAUGHTER_LOW_LIMIT = (daughterLowNum->GetNumber());
         cout << "The daughter half-life lower bound is " << DAUGHTER_LOW_LIMIT << "." << endl;
      } else {
         DAUGHTER_LOW_LIMIT = 0;
         cout << "The daughter half-life lower bound is 0." << endl;
      }

      if (daughterHighNum->GetNumber() != 0) {
         DAUGHTER_HIGH_LIMIT = (daughterHighNum->GetNumber());
         cout << "The daughter half-life upper bound is " << DAUGHTER_HIGH_LIMIT << "." << endl;
      } else {
         DAUGHTER_HIGH_LIMIT = 0;
         cout << "The daughter half-life upper bound is 0." << endl;
      }

      if (daughterLowNum->GetNumber() >= daughterHighNum->GetNumber()) {
         new TGMsgBox(gClient->GetRoot(), fMain,
               "Something is weird...", "Your upper daughter half-life  bound is below your lower bound.\n This doesn't make any sense.\n Please fix this.", kMBIconStop, kMBDismiss, &retval);
         goto end;
      } else if ((daughterGuessNum->GetNumber() < daughterLowNum->GetNumber()) || (daughterGuessNum->GetNumber() > daughterHighNum->GetNumber())) {
         new TGMsgBox(gClient->GetRoot(), fMain, 
               "Something is weird...", "Your daughter half-life guess is out of the limits you set.\n That's silly. Please fix this.", kMBIconStop, kMBDismiss, &retval);
         goto end;
      }
   }

   INITIAL_GUESS = initialGuessNum->GetNumber();
   cout << "Guess for initial activity is set to " << INITIAL_GUESS << "." << endl;

   INITIAL_LOW_LIMIT = initialLowNum->GetNumber();
   cout << "The initial activity lower bound is " << INITIAL_LOW_LIMIT << "." << endl;

   INITIAL_HIGH_LIMIT = initialHighNum->GetNumber();
   cout << "The initial activity upper bound is " << INITIAL_HIGH_LIMIT << "." << endl;

   if (initialLowNum->GetNumber() >= initialHighNum->GetNumber()) {
      new TGMsgBox(gClient->GetRoot(), fMain,
            "Something is weird...", "Your upper initial activity  bound is below your lower bound.\n This doesn't make any sense.\n Please fix this.", kMBIconStop, kMBDismiss, &retval);
      goto end;
   } else if ((initialGuessNum->GetNumber() < initialLowNum->GetNumber()) || (initialGuessNum->GetNumber() > initialHighNum->GetNumber())) {
      new TGMsgBox(gClient->GetRoot(), fMain, 
            "Something is weird...", "Your initial activity guess is out of the limits you set.\n That's silly. Please fix this.", kMBIconStop, kMBDismiss, &retval);
      goto end;
   } 

   if (LINEAR) {
      BACKLIN_GUESS = backLinGuessNum->GetNumber();
      cout << "Guess for linear background is set to " << BACKLIN_GUESS << "." << endl;

      BACKLIN_LOW_LIMIT = backLinLowNum->GetNumber();
      cout << "The linear background lower bound is " << BACKLIN_LOW_LIMIT << "." << endl;

      BACKLIN_HIGH_LIMIT = backLinHighNum->GetNumber();
      cout << "The linear background upper bound is " << BACKLIN_HIGH_LIMIT << "." << endl;

      if (backLinLowNum->GetNumber() >= backLinHighNum->GetNumber()) {
         new TGMsgBox(gClient->GetRoot(), fMain,
               "Something is weird...", "Your upper background (linear) bound is below your lower bound.\n This doesn't make any sense.\n Please fix this.", kMBIconStop, kMBDismiss, &retval);
         goto end;
      } else if ((backLinGuessNum->GetNumber() < backLinLowNum->GetNumber()) || (backLinGuessNum->GetNumber() > backLinHighNum->GetNumber())) {
         new TGMsgBox(gClient->GetRoot(), fMain, 
               "Something is weird...", "Your background (linear) guess is out of the limits you set.\n That's silly. Please fix this.", kMBIconStop, kMBDismiss, &retval);
         goto end;
      }

      cout << "" << endl;
   }

   if (TWOCOMP) {
      if (FRACTION_FREE) {
         COMPONENT2_FRACTION = fracGuessNum->GetNumber();
         cout << "Guess for fraction of component 2 is set to " << COMPONENT2_FRACTION << "." << endl;

         COMPONENT2_FRACTION_LOW_LIMIT = fracLowNum->GetNumber();
         cout << "The fraction of component 2 lower bound is " << COMPONENT2_FRACTION_LOW_LIMIT << "." << endl;

         COMPONENT2_FRACTION_HIGH_LIMIT = fracHighNum->GetNumber();
         cout << "The fraction of component 2 upper bound is " << COMPONENT2_FRACTION_HIGH_LIMIT << "." << endl;

         if (fracLowNum->GetNumber() >= fracHighNum->GetNumber()) {
            new TGMsgBox(gClient->GetRoot(), fMain,
                  "Something is weird...", "Your upper fraction of component 2 bound is below your lower bound.\n This doesn't make any sense.\n Please fix this.", kMBIconStop, kMBDismiss, &retval);
            goto end;
         } else if ((fracGuessNum->GetNumber() < fracLowNum->GetNumber()) || (fracGuessNum->GetNumber() > fracHighNum->GetNumber())) {
            new TGMsgBox(gClient->GetRoot(), fMain, 
                  "Something is weird...", "Your fraction of component 2 guess is out of the limits you set.\n That's silly. Please fix this.", kMBIconStop, kMBDismiss, &retval);
            goto end;
         } else if (fracHighNum->GetNumber() > 1) {
            new TGMsgBox(gClient->GetRoot(), fMain,
                  "Something is weird...", "The upper limit on the fraction of component 2 cannot be higher than one. \n Please lower it.", kMBIconStop, kMBDismiss, &retval);
            goto end;
         } 

         cout << "" << endl;
      }
      if (COMPONE_FREE) {
         if (lifeGuessNum->GetNumber() != 0) {
            LIFE_GUESS = lifeGuessNum->GetNumber();
            cout << "Guess for component 1 half-life is set to " << LIFE_GUESS << "." << endl;
         } else {
            LIFE_GUESS = 0;
            cout << "Guess for component 1 half-life is set to 0." << endl;
         }

         if (lifeLowNum->GetNumber() != 0) {
            LIFE_LOW_LIMIT = lifeLowNum->GetNumber();
            cout << "The component 1 half-life lower bound is " << LIFE_LOW_LIMIT << "." << endl;
         } else {
            LIFE_LOW_LIMIT = 0;
            cout << "The component 1 half-life lower bound is 0." << endl;
         }

         if (lifeHighNum->GetNumber() != 0) {
            LIFE_HIGH_LIMIT = (lifeHighNum->GetNumber());
            cout << "The component 1 half-life upper bound is " << LIFE_HIGH_LIMIT << "." << endl;
         } else {
            LIFE_HIGH_LIMIT = 0;
            cout << "The component 1 half-life upper bound is 0." << endl;
         }

         int retval;

         if (lifeLowNum->GetNumber() >= lifeHighNum->GetNumber()) {
            new TGMsgBox(gClient->GetRoot(), fMain,
                  "Something is weird...", "Your component 1 upper half-life  bound is below your lower bound.\n This doesn't make any sense.\n Please fix this.", kMBIconStop, kMBDismiss, &retval);
            goto end;
         } else if ((lifeGuessNum->GetNumber() < lifeLowNum->GetNumber()) || (lifeGuessNum->GetNumber() > lifeHighNum->GetNumber())) {
            new TGMsgBox(gClient->GetRoot(), fMain, 
                  "Something is weird...", "Your component 1 half-life guess is out of the limits you set.\n That's silly. Please fix this.", kMBIconStop, kMBDismiss, &retval);
            goto end;
         }

      }
      if (COMPTWO_FREE) {
         if (component2GuessNum->GetNumber() != 0) {
            COMPONENT2_GUESS = component2GuessNum->GetNumber();
            cout << "Guess for component 2 half-life is set to " << COMPONENT2_GUESS << "." << endl;
         } else {
            COMPONENT2_GUESS = 0;
            cout << "Guess for component 2 half-life is set to 0." << endl;
         }

         if (component2LowNum->GetNumber() != 0) {
            COMPONENT2_LOW_LIMIT = component2LowNum->GetNumber();
            cout << "The component 2 half-life lower bound is " << COMPONENT2_LOW_LIMIT << "." << endl;
         } else {
            COMPONENT2_LOW_LIMIT = 0;
            cout << "The component 2 half-life lower bound is 0." << endl;
         }

         if (component2HighNum->GetNumber() != 0) {
            COMPONENT2_HIGH_LIMIT = (component2HighNum->GetNumber());
            cout << "The component 2 half-life upper bound is " << COMPONENT2_HIGH_LIMIT << "." << endl;
         } else {
            COMPONENT2_HIGH_LIMIT = 0;
            cout << "The component 2 half-life upper bound is 0." << endl;
         }

         int retval;

         if (component2LowNum->GetNumber() >= component2HighNum->GetNumber()) {
            new TGMsgBox(gClient->GetRoot(), fMain,
                  "Something is weird...", "Your component 2 upper half-life  bound is below your lower bound.\n This doesn't make any sense.\n Please fix this.", kMBIconStop, kMBDismiss, &retval);
            goto end;
         } else if ((component2GuessNum->GetNumber() < component2LowNum->GetNumber()) || (component2GuessNum->GetNumber() > component2HighNum->GetNumber())) {
            new TGMsgBox(gClient->GetRoot(), fMain, 
                  "Something is weird...", "Your component 2 half-life guess is out of the limits you set.\n That's silly. Please fix this.", kMBIconStop, kMBDismiss, &retval);
            goto end;
         }

      }
   }


   if (EXP) {
      if (EXPDECAY_FREE) {
         EXPDECAY_GUESS = expDecayGuessNum->GetNumber();
         cout << "Guess for exponential background decay constant is set to " << EXPDECAY_GUESS << "." << endl;

         EXPDECAY_LOW_LIMIT = expDecayLowNum->GetNumber();
         cout << "The exponential background decay constant lower bound is " << EXPDECAY_LOW_LIMIT << "." << endl;

         EXPDECAY_HIGH_LIMIT = expDecayHighNum->GetNumber();
         cout << "The exponential background decay constant upper bound is " << EXPDECAY_HIGH_LIMIT << "." << endl;

         if (expDecayLowNum->GetNumber() >= expDecayHighNum->GetNumber()) {
            new TGMsgBox(gClient->GetRoot(), fMain,
                  "Something is weird...", "Your upper background decay constant (exp) bound is below your lower bound.\n This doesn't make any sense.\n Please fix this.", kMBIconStop, kMBDismiss, &retval);
            goto end;
         } else if ((expDecayGuessNum->GetNumber() < expDecayLowNum->GetNumber()) || (expDecayGuessNum->GetNumber() > expDecayHighNum->GetNumber())) {
            new TGMsgBox(gClient->GetRoot(), fMain, 
                  "Something is weird...", "Your background decay constant (exp) guess is out of the limits you set.\n That's silly. Please fix this.", kMBIconStop, kMBDismiss, &retval);
            goto end;
         }

         cout << "" << endl;
      }
      EXPINIT_GUESS = expInitGuessNum->GetNumber();
      cout << "Guess for exponential background initial value is set to " << EXPINIT_GUESS << "." << endl;

      EXPINIT_LOW_LIMIT = expInitLowNum->GetNumber();
      cout << "Guess for exponential background initial value lower bound is " << EXPINIT_LOW_LIMIT << "." << endl;

      EXPINIT_HIGH_LIMIT = expInitHighNum->GetNumber();
      cout << "Guess for exponential background initial value upper bound is " << EXPINIT_HIGH_LIMIT << "." << endl;

      if (expInitLowNum->GetNumber() >= expInitHighNum->GetNumber()) {
         new TGMsgBox(gClient->GetRoot(), fMain,
               "Something is weird...", "Your upper background (exp) initial value bound is below your lower bound.\n This doesn't make any sense.\n Please fix this.", kMBIconStop, kMBDismiss, &retval);
         goto end;
      } else if ((expInitGuessNum->GetNumber() < expInitLowNum->GetNumber()) || (expInitGuessNum->GetNumber() > expInitHighNum->GetNumber())) {
         new TGMsgBox(gClient->GetRoot(), fMain, 
               "Something is weird...", "Your background (exp) initial value guess is out of the limits you set.\n That's silly. Please fix this.", kMBIconStop, kMBDismiss, &retval);
         goto end;
      }

      cout << "" << endl;
   }

   fMain->SendCloseMessage();
end:

}
