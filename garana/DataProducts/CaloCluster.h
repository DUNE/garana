/*
 * CaloCluster.h
 *
 *  Created on: Feb 23, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_CALOCLUSTER_H_
#define GARANA_CALOCLUSTER_H_

#include <TLorentzVector.h>
#include <TVector3.h>

#include <vector>
#include <climits>

using std::vector;

namespace garana {

  class CaloCluster {

    public: 

	  CaloCluster();

	#ifndef __GCCXML__

	  CaloCluster(const TLorentzVector& pos, const float& energy, const float& energyErr, const float& timeDiff,
			      const float* shape, const float& theta, const float& phi, const std::vector<TVector3>& eigenVecs );

	  TLorentzVector*   Position();
	  float             Energy();
	  float             EnergyError();
	  float             TimeDifference();
	  float*            Shape();
	  float             Theta();
	  float             Phi();
	  vector<TVector3>* EigenVecs();

	#endif

    private:

	  TLorentzVector fPosition;    ///< 4-position of the cluster [cm,ns]
      float fEnergy;               ///< energy of the ECal cluster [GeV]
      float fEnergyError;          ///< uncertainty of the cluster energy [GeV]
      float fTimeDiffFirstLast;    ///< time difference between the first and last layer of the cluster [ns]
      float fShape[6];             ///< cluster shape parameters (Ellipsoid r1, r2, r3, vol, width)
      float fTheta;                ///< intrasic direction of the cluster theta
      float fPhi;                  ///< intrasic direction of the cluster phi
      vector<TVector3> fEigenVecs; ///< Eigenvectors of the cluster in ascending order (principal axis with smallest inertial mass) normalised to 1

  }; //class
}//namespace

#endif /* GARANA_CALOCLUSTER_H_ */
