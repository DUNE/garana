/*
 * RecoTree.cxx
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#include "garana/Base/RecoTree.h"

using namespace garana;
using std::vector;

void RecoTree::GetTrackG4PIndices       (const size_t& itrk,    vector<UInt_t>& ig4ps  ) const {
	ig4ps = fTrackG4PIndices->at(itrk);
}

void RecoTree::GetVertexTrackIndices    (const size_t& ivtx,    vector<UInt_t>& itracks) const {
	itracks = fVertTrackIndices->at(ivtx);
}

void RecoTree::GetVeeTrackIndices       (const size_t& ivee,    vector<UInt_t>& itracks) const {
	itracks = fVeeTrackIndices->at(ivee);
}

void RecoTree::GetCalClusterTrackIndices(const size_t& iclust,  vector<UInt_t>& itracks) const {
	itracks = fCalTrackIndices->at(iclust);
}
