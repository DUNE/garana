/*
 * Vee.cxx
 *
 *  Created on: Feb 23, 2021
 *      Author: chilgenb
 */

#include "garana/DataProducts/Vee.h"

using namespace garana;
using std::vector;

Vee::Vee() {
  fChisqr = FLT_MAX;
  fPosition.SetXYZT(FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX);
  for(size_t i=0; i<3; i++){

	  //fMomPerHypoth[i].SetPxPyPzE(FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX);
	  //fCovar = new float*[3];

	  for(size_t j=0; j<3; j++){
		  //fCovar[i] = new float[3];
		  fCovar[i][j] = FLT_MAX;
	  }
  }
} //

Vee::Vee(const TLorentzVector& vertex, const vector<TLorentzVector>& moms, const float& chisqr, const float* covar) {

  fChisqr = chisqr;
  fPosition = vertex;

  for(size_t i=0; i<3; i++){

	  //fMomPerHypoth[i] = moms[i];
	  fMomPerHypoth.push_back(moms[i]);
	  //fCovar = new float*[3];

	  for(size_t j=0; j<3; j++){
		//  fCovar[i] = new float[3];
		  fCovar[i][j] = covar[0]; //TODO check input array dimensions

	  }
  }
} //

float const& Vee::GetChiSqr() const {
	return fChisqr;
}

const vector<TLorentzVector>* Vee::GetMomentaPerHypothesis() const {
	return &fMomPerHypoth;
}
