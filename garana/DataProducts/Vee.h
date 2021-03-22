/*
 * Vee.h
 *
 *  Created on: Feb 23, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_VEE_H_
#define GARANA_VEE_H_

#include "garana/DataProducts/Vertex.h"

using std::vector;

namespace garana {
  class Vee : public Vertex {

    public:

	  // three hypotheses for mass and momentum
	  typedef enum { Kshort=0, Lambda1=1, Lambda2=2 } hypothesis_t;

	  Vee();
	  Vee(const TLorentzVector& vertex, const vector<TLorentzVector>& moms, const float& chisqr, const float* covar);

	  float const&                  GetChiSqr()                 const;
      const vector<TLorentzVector>* GetMomentaPerHypothesis()   const;
      // GetCovar inherited from Vertex

    private:

	  vector<TLorentzVector> fMomPerHypoth; ///< four-momentum of vee, one per hypothesis [GeV]
	  float fChisqr;                        // TODO chi-squared of something ?? CHECK ME!
	  float fCovar[3][3];

  }; //class
}//namespace

#endif /* GARANA_VEE_H_ */
