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
			      const float* shape, const float& theta, const float& phi, const std::vector<TVector3>& eigenVecs,
				  const std::vector<std::pair<int,float>>& edeps);

	  const TLorentzVector*   Position() const;
	  float const&      Energy() const;
	  float const&      EnergyError() const;
	  float const&      TimeDifference() const;
	  const float*      Shape() const;
	  float const&      Theta() const;
	  float const&      Phi() const;
	  const vector<TVector3>* EigenVecs() const;
      const size_t      NIdes() const;
      const std::pair<int,float>* GetTrackIdEdep(const size_t& iide) const;
      const float       TotalTrueEnergy() const;
      float const&      MaxDeposit() const;
      int const&        TrackIdMaxDep() const;

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
      vector<std::pair<int,float>> fTrueEnergy; ///< true energy (second) [GeV] deposited by MCParticle with trackID (first)

  }; //class
}//namespace

#endif /* GARANA_CALOCLUSTER_H_ */
