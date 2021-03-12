/*
 * Vee.cxx
 *
 *  Created on: Feb 23, 2021
 *      Author: chilgenb
 */

#include "garana/DataProducts/Vee.h"

using namespace garana;

Vee::Vee() {
  fChisqr = FLT_MAX;
  fPosition.SetXYZT(FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX);
  for(size_t i=0; i<3; i++){

	  fMomPerHypoth[i].SetPxPyPzE(FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX);
	  fCovar = new float*[3];

	  for(size_t j=0; j<3; j++){
		  fCovar[i] = new float[3];
		  fCovar[i][j] = FLT_MAX;
	  }
  }
} //

Vee::Vee(TLorentzVector& vertex, TLorentzVector* moms, float chisqr, float** covar) {

  fChisqr = chisqr;
  fPosition = vertex;

  for(size_t i=0; i<3; i++){

	  fMomPerHypoth[i] = moms[i];
	  fCovar = new float*[3];

	  for(size_t j=0; j<3; j++){
		  fCovar[i] = new float[3];
		  fCovar[i][j] = covar[i][j]; //TODO check input array dimensions

	  }
  }
} //

float Vee::GetChiSqr() {
	return fChisqr;
}

TLorentzVector* Vee::GetMomentaPerHypothesis() {
	return fMomPerHypoth;
}

ClassImp(Vee)
