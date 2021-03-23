/*
 * StructuredRecoTree.h
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_STRUCTUREDRECOTREE_H_
#define GARANA_STRUCTUREDRECOTREE_H_

#include "garana/Base/RecoTree.h"

using std::vector;

namespace garana {

 class StructuredRecoTree : public RecoTree {

   public:

	 StructuredRecoTree() {}
	 StructuredRecoTree(TTree* tree);

	 // sizes
	 const size_t NTrack()      const override;
	 const size_t NVertex()     const override;
	 const size_t NVee()        const override;
	 const size_t NCalCluster() const override;

	 // track
     const TLorentzVector* TrackVertex(const size_t& itrack)                const override;
     const TLorentzVector* TrackEnd(const size_t& itrack)                   const override;
     const size_t          NTrackHit(const size_t& itrack)                  const override;
     const TVector3*       TrackMomBeg(const size_t& itrack)                const override;
     const TVector3*       TrackMomEnd(const size_t& itrack)                const override;
     const float           TrackVtxDirectionX(const size_t& itrack)         const override;
     const float           TrackVtxDirectionY(const size_t& itrack)         const override;
     const float           TrackVtxDirectionZ(const size_t& itrack)         const override;
     const float           TrackEndDirectionX(const size_t& itrack)         const override;
     const float           TrackEndDirectionY(const size_t& itrack)         const override;
     const float           TrackEndDirectionZ(const size_t& itrack)         const override;
     const float           TrackLenFwd(const size_t& itrack)                const override;
     const float           TrackLenBkd(const size_t& itrack)                const override;
     const float           TrackIonizFwd(const size_t& itrack)              const override;
     const float           TrackIonizBkd(const size_t& itrack)              const override;
     const int             TrackChiSqrFwd(const size_t& itrack)             const override;
     const int             TrackChiSqrBkd(const size_t& itrack)             const override;
     const int             TrackChgFwd(const size_t& itrack)                const override;
     const int             TrackChgBkd(const size_t& itrack)                const override;
     void                  TrackParBeg(const size_t& itrack, float pars[5]) const override;
     void                  TrackParEnd(const size_t& itrack, float pars[5]) const override;
     void                  TrackCovarBeg(const size_t& itrack, float pars[15]) const override;
     void                  TrackCovarEnd(const size_t& itrack, float pars[15]) const override;

	 //vertex
     const TLorentzVector* GetVertex(const size_t& ivertex)                          const override;
     void                  VertexCovariance(const size_t& ivertex, float covar[][3]) const override;

     //vee
     const TLorentzVector*         VeeVertex(const size_t& ivee)                       const override;
     void                          VeeCovariance(const size_t& ivee, float covar[][3]) const override;
     const vector<TLorentzVector>* VeeMomentumPerHypothesis(const size_t& ivee)        const override;
     const float                   VeeChiSquared(const size_t& ivee)                   const override;

     //ECal cluster
     const TLorentzVector*   CalClustPosition(const size_t& ivee)       const override;
     const float             CalClustEnergy(const size_t& ivee)         const override;
     const float             CalClustEnergyError(const size_t& ivee)    const override;
     const float             CalClustTimeDifference(const size_t& ivee) const override;
     const float*            CalClustShape(const size_t& ivee)          const override;
     const float             CalClustTheta(const size_t& ivee)          const override;
     const float             CalClustPhi(const size_t& ivee)            const override;
     const vector<TVector3>* CalClustEigenVecs(const size_t& ivee)      const override;

   private:

	 //pure virtual function from TreeReader
	 bool SetBranchAddresses() override;

	 //leaves and branches
     vector<Track>*          fTracks           = nullptr;
     vector<Vee>*            fVees             = nullptr;
     vector<Vertex>*         fVertices         = nullptr;
     vector<CaloCluster>*    fCalClusters      = nullptr;

	 vector<vector<Int_t>>*  fVertTrackEnds    = nullptr;
	 vector<vector<Int_t>>*  fVeeTrackEnds     = nullptr;

	 TBranch*            b_Tracks           = nullptr;
	 TBranch*            b_Vees             = nullptr;
	 TBranch*            b_Vertices         = nullptr;
	 TBranch*            b_CalClusters      = nullptr;

     TBranch*            b_VertTrackEnds    = nullptr;
     TBranch*            b_VeeTrackEnds     = nullptr;

 };//class
}//namespace
#endif /* GARANA_STRUCTUREDRECOTREE_H_ */
