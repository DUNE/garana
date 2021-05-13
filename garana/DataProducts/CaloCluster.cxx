/*
 * CaloCluster.cxx
 *
 *  Created on: Feb 23, 2021
 *      Author: chilgenb
 */

#include "garana/DataProducts/CaloCluster.h"

using namespace garana;

CaloCluster::CaloCluster() :
	    	  fEnergy(FLT_MAX),
	    	  fEnergyError(FLT_MAX),
	    	  fTimeDiffFirstLast(FLT_MAX),
	    	  fTheta(FLT_MAX),
	    	  fPhi(FLT_MAX)
{

	for(size_t i=0; i<6; i++) {
		if(i<3){
			fPosition.SetXYZT(FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX);
			TVector3 v;
			fEigenVecs.push_back(v);
		}
		fShape[i] = FLT_MAX;
	}
}

CaloCluster::CaloCluster(const TLorentzVector& pos, const float& energy, const float& energyErr, const float& timeDiff,
	      const float* shape, const float& theta, const float& phi, const std::vector<TVector3>& eigenVecs,
		  const std::vector<std::pair<int,float>>& edeps ) :
	    	  fEnergy(energy),
	    	  fEnergyError(energyErr),
	    	  fTimeDiffFirstLast(timeDiff),
	    	  fTheta(theta),
	    	  fPhi(phi),
	    	  fEigenVecs(eigenVecs),
			  fTrueEnergy(edeps)
{
	fPosition = pos;

	for(size_t i=0; i<6; i++)
		fShape[i] = shape[i];

}

const TLorentzVector* CaloCluster::Position() const{
	 return &fPosition;
 }

 float const&  CaloCluster::Energy() const {
	 return fEnergy;
 }

 float const& CaloCluster::EnergyError() const {
	 return fEnergyError;
 }

 float const& CaloCluster::TimeDifference() const {
	 return fTimeDiffFirstLast;
 }

 const float* CaloCluster::Shape() const {
	 return fShape;
 }

 float const& CaloCluster::Theta() const {
	 return fTheta;
 }

 float const& CaloCluster::Phi() const {
	 return fPhi;
 }

 const std::vector<TVector3>* CaloCluster::EigenVecs() const {
	 return &fEigenVecs;
 }

 const size_t CaloCluster::NIdes() const {
	 return fTrueEnergy.size();
 }

 const std::pair<int,float>* CaloCluster::GetTrackIdEdep(const size_t& iide) const {
	 return &fTrueEnergy.at(iide);
 }

 const float CaloCluster::TotalTrueEnergy() const {
	 float edep = 0.;
	 for(auto const& trkdep : fTrueEnergy)
		 edep += trkdep.second;
	 return edep;
 }

 int const& CaloCluster::TrackIdMaxDep() const {
	 float maxdep = 0.;
	 int imaxdep = 0;
	 for(size_t idep=0; idep<NIdes(); idep++ ) {
		 auto const& trkdep = GetTrackIdEdep(idep);
		 if( trkdep->second > maxdep ) {
			 imaxdep = idep;
			 maxdep = trkdep->second;
		 }
	 }

	 return (GetTrackIdEdep(imaxdep))->first;
 }

 float const& CaloCluster::MaxDeposit() const {
	 float maxdep = 0.;
	 int imaxdep = 0;
	 for(size_t idep=0; idep<NIdes(); idep++ ) {
		 auto const& trkdep = GetTrackIdEdep(idep);
		 if( trkdep->second > maxdep ) {
			 imaxdep = idep;
			 maxdep = trkdep->second;
		 }
	 }

	 return (GetTrackIdEdep(imaxdep))->second;
 }
