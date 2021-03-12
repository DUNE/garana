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

CaloCluster::CaloCluster(TLorentzVector& pos, float energy, float energyErr, float timeDiff,
	      float* shape, float theta, float phi, std::vector<TVector3>& eigenVecs ) :
	    	  fEnergy(energy),
	    	  fEnergyError(energyErr),
	    	  fTimeDiffFirstLast(timeDiff),
	    	  fTheta(theta),
	    	  fPhi(phi),
	    	  fEigenVecs(eigenVecs)
{
	fPosition = pos;

	for(size_t i=0; i<6; i++)
		fShape[i] = shape[i];

}

 TLorentzVector* CaloCluster::Position(){
	 return &fPosition;
 }

 float  CaloCluster::Energy(){
	 return fEnergy;
 }

 float  CaloCluster::EnergyError() {
	 return fEnergyError;
 }

 float  CaloCluster::TimeDifference() {
	 return fTimeDiffFirstLast;
 }

 float* CaloCluster::Shape() {
	 return fShape;
 }

 float  CaloCluster::Theta() {
	 return fTheta;
 }

 float  CaloCluster::Phi() {
	 return fPhi;
 }

 std::vector<TVector3>* CaloCluster::EigenVecs(){
	 return &fEigenVecs;
 }

 ClassImp(CaloCluster)
