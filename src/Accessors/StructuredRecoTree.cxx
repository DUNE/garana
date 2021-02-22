/*
 * StructuredRecoTree.cxx
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/StructuredRecoTree.h"

using namespace garana;

StructuredRecoTree::StructuredRecoTree(TTree* tree=0) {
	SetupRead(tree); //initialize tree pointer in TreeReader instance and set branch address
}

bool StructuredRecoTree::SetBranchAddresses() {

    fTreeIn->SetBranchAddress("Event",           &fEvent,                      &b_Event);
    /*fTreeIn->SetBranchAddress("Tracks",          "vector<gar::adp::AnaTrack>", &fTracks);
    fTreeIn->SetBranchAddress("Vees",            "vector<gar::rec::Vee>",      &fVees);
    fTreeIn->SetBranchAddress("Vertices",        "vector<gar::rec::Vertex>",   &fVertices);
    fTreeIn->SetBranchAddress("CalClusters",     "vector<gar::rec::Cluster>",  &fCalClusters);
    fTreeIn->SetBranchAddress("TrackG4Indices",  "vector<vector<UInt_t>>",     &fTrackG4PIndices);
    fTreeIn->SetBranchAddress("VertTrackIndices","vector<vector<UInt_t>>",     &fVertTrackIndices);
    fTreeIn->SetBranchAddress("VertTrackEnds",   "vector<vector<Int_t>>",      &fVertTrackEnds);
    fTreeIn->SetBranchAddress("VeeTrackIndices", "vector<vector<UInt_t>>",     &fVeeTrackIndices);
    fTreeIn->SetBranchAddress("VeeTrackEnds",    "vector<vector<Int_t>>",      &fVeeTrackEnds);
    fTreeIn->SetBranchAddress("CalTrackIndices", "vector<vector<UInt_t>>",     &fCalTrackIndices);*/
    //fRecoTree->Branch("CalTrackEnds", "vector<vector<Int_t>>", &fCalTrackEnds);
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

