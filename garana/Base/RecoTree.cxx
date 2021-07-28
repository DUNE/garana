/*
 * RecoTree.cxx
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#include "garana/Base/RecoTree.h"

using namespace garana;
using std::vector;

const float RecoTree::CalClustMaxDepositFrac(const size_t& icluster) const{
	return CalClustMaxDeposit(icluster)/CalClustTrueEnergy(icluster);
}

const float RecoTree::TrackMaxDepositFrac(const size_t& itrack) const{
	//if
	return TrackMaxDeposit(itrack)/TrackTrueEnergy(itrack);
}

void RecoTree::GetTrackG4PIndices       (const size_t& itrk,    vector<UInt_t>& ig4ps  ) const {
	//std::cout << "filling given track to g4p vec with " << fTrackG4PIndices->at(itrk).size() << " entries" << std::endl;
	ig4ps = fTrackG4PIndices->at(itrk);
}

void RecoTree::GetVertexTrackIndices    (const size_t& ivtx,    vector<UInt_t>& itracks) const {
	itracks = fVertTrackIndices->at(ivtx);
}

void RecoTree::GetVeeTrackIndices       (const size_t& ivee,    vector<UInt_t>& itracks) const {
	itracks = fVeeTrackIndices->at(ivee);
}

void RecoTree::GetCalClusterTrackIndices(const size_t& iclust,  vector<UInt_t>& itracks) const {
	itracks = fCalClusterTrackIndices->at(iclust);
}

void RecoTree::GetCalClusterG4Indices(const size_t& iclust,  vector<UInt_t>& ig4ps) const {
	ig4ps = fCalClusterG4Indices->at(iclust);
}
