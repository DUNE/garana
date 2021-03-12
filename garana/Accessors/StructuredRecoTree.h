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
	 size_t NTrack()      const override;
	 size_t NVertex()     const override;
	 size_t NVee()        const override;
	 size_t NCalCluster() const override;

	 // track
     TLorentzVector TrackVertex(size_t itrack) const override;
     TLorentzVector TrackEnd(size_t itrack)    const override;
     size_t         NTrackHit(size_t itrack)   const override;
     TVector3       TrackMomBeg(size_t itrack) const override;
     TVector3       TrackMomEnd(size_t itrack) const override;

	 //vertex
     TLorentzVector GetVertex(size_t ivertex)           const override;
     float**        VertexCovariance(size_t ivertex) const override;

   private:

	 //pure virtual function from TreeReader
	 bool SetBranchAddresses() override;

	 //leaves and branches
     vector<Track>*          fTracks           = nullptr;
     vector<Vee>*            fVees             = nullptr;
     vector<Vertex>*         fVertices         = nullptr;
     vector<CaloCluster>*    fCalClusters      = nullptr;

	 vector<vector<UInt_t>>* fTrackG4PIndices  = nullptr;
	 vector<vector<UInt_t>>* fVertTrackIndices = nullptr;
	 vector<vector<UInt_t>>* fVeeTrackIndices  = nullptr;
	 vector<vector<UInt_t>>* fCalTrackIndices  = nullptr;

	 vector<vector<Int_t>>*  fVertTrackEnds    = nullptr;
	 vector<vector<Int_t>>*  fVeeTrackEnds     = nullptr;

	 TBranch*            b_Tracks           = nullptr;
	 TBranch*            b_Vees             = nullptr;
	 TBranch*            b_Vertices         = nullptr;
	 TBranch*            b_CalClusters      = nullptr;

     TBranch*            b_TrackG4PIndices  = nullptr;
     TBranch*            b_VertTrackIndices = nullptr;
     TBranch*            b_VeeTrackIndices  = nullptr;
     TBranch*            b_CalTrackIndices  = nullptr;

     TBranch*            b_VertTrackEnds    = nullptr;
     TBranch*            b_VeeTrackEnds     = nullptr;

 };//class
}//namespace
#endif /* GARANA_STRUCTUREDRECOTREE_H_ */
