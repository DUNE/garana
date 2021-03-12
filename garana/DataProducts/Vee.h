/*
 * Vee.h
 *
 *  Created on: Feb 23, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_VEE_H_
#define GARANA_VEE_H_

#include "garana/DataProducts/Vertex.h"

namespace garana {
  class Vee : public Vertex {

    public:

	  // three hypotheses for mass and momentum
	  typedef enum { Kshort=0, Lambda1=1, Lambda2=2 } hypothesis_t;

	  Vee();
	  Vee(TLorentzVector& vertex, TLorentzVector* moms, float chisqr, float** covar);

	  float GetChiSqr();
      TLorentzVector* GetMomentaPerHypothesis();

    private:

	  TLorentzVector fMomPerHypoth[3]; ///< four-momentum of vee, one per hypothesis [GeV]
	  float fChisqr; ///< chi-squared of something ?? FIX ME!

	ClassDef(Vee,2)

  }; //class
}//namespace

#endif /* GARANA_VEE_H_ */
