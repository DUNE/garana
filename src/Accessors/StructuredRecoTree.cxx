/*
 * StructuredRecoTree.cxx
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/StructuredRecoTree.h"

using namespace garana;

StructuredRecoTree::StructuredRecoTree(TTree* tree=0) {
	SetupRead(tree); //initialize tree pointer in TreeReader instance and set branch addresses
}

bool StructuredRecoTree::SetBranchAddresses() {

    fTreeIn->SetBranchAddress("Event",            &fEvent,            &b_Event           );
    fTreeIn->SetBranchAddress("Tracks",           &fTracks          , &b_Tracks          );
    fTreeIn->SetBranchAddress("Vees",             &fVees            , &b_Vees            );
    fTreeIn->SetBranchAddress("Vertices",         &fVertices        , &b_Vertices        );
    fTreeIn->SetBranchAddress("CalClusters",      &fCalClusters     , &b_CalClusters     );
    fTreeIn->SetBranchAddress("TrackG4Indices",   &fTrackG4PIndices , &b_TrackG4PIndices );
    fTreeIn->SetBranchAddress("VertTrackIndices", &fVertTrackIndices, &b_VertTrackIndices);
    fTreeIn->SetBranchAddress("VertTrackEnds",    &fVertTrackEnds   , &b_VertTrackEnds   );
    fTreeIn->SetBranchAddress("VeeTrackIndices",  &fVeeTrackIndices , &b_VeeTrackIndices );
    fTreeIn->SetBranchAddress("VeeTrackEnds",     &fVeeTrackEnds    , &b_VeeTrackEnds    );
    fTreeIn->SetBranchAddress("CalTrackIndices",  &fCalTrackIndices , &b_CalTrackIndices );
    //fTreeIn->SetBranchAddress("CalTrackEnds",     &fCalTrackEnds    , &b_CalTrackEnds    );
    /*if(fGeo->HasMuonDetector()){
            fTreeIn->SetBranchAddress("MuIDClusters", "vector<gar::rec::Cluster>",   &fMuClusters);
    }*/

    //TODO: add Assns for reco r&d products
    /*if(fAnaMode == "reco"){
        fRecoTree->Branch("TPCHits",       "vector<gar::rec::Hit>",        &fTPCHits);
        fRecoTree->Branch("TPCClusters",   "vector<gar::rec::TPCCluster>", &fTPCClusters);
        fRecoTree->Branch("CalHits",       "vector<gar::rec::CaloHit>",    &fCalHits);
        if(fGeo->HasMuonDetector()){
            fRecoTree->Branch("MuIDHits",       "vector<gar::rec::CaloHit>", &fMuHits);
        }
    }*/


    return true;
}

size_t StructuredRecoTree::NTrack()      const {
	return fTracks->size();
}
size_t StructuredRecoTree::NVertex()     const {
	return fVertices->size();
}
size_t StructuredRecoTree::NVee()        const {
	return fVees->size();
}
size_t StructuredRecoTree::NCalCluster() const {
	return fCalClusters->size();
}

// track
TLorentzVector StructuredRecoTree::TrackVertex(size_t itrack) const {
	return fTracks->at(itrack).fVtx;
}

TLorentzVector StructuredRecoTree::TrackEnd(size_t itrack)    const {
	return fTracks->at(itrack).fEnd;
}
size_t         StructuredRecoTree::NTrackHit(size_t itrack)   const {
	return fTracks->at(itrack).fNHits;
}
TVector3 StructuredRecoTree::TrackMomBeg(size_t itrack) const {
    return fTracks->at(itrack).fMomBeg*fTracks->at(itrack).fVtxDir;
}

TVector3 StructuredRecoTree::TrackMomEnd(size_t itrack) const {
    return fTracks->at(itrack).fMomEnd*fTracks->at(itrack).fVtxDir;
}

//vertex
TLorentzVector StructuredRecoTree::GetVertex(size_t ivertex)         const {
	return *(fVertices->at(ivertex).GetVertex());
}

void        StructuredRecoTree::VertexCovariance(size_t ivertex, float covar[][3]) const {
	fVertices->at(ivertex).GetCovar(covar);
}

