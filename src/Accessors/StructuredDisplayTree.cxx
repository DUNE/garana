/*
 * StructuredDisplayTree.cxx
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/StructuredDisplayTree.h"

using namespace garana;

StructuredDisplayTree::StructuredDisplayTree(TTree* tree=0) {
	SetupRead(tree); //initialize tree pointer in TreeReader instance and set branch address
}

bool StructuredDisplayTree::SetBranchAddresses() {
    fTreeIn->SetBranchAddress("Event",     &fEvent,                  &b_Event);
    //fTreeIn->SetBranchAddress("MCTracks", "vector<MCDisplayTrack>",  &fMCDisplay);
    /*if(fAnaMode!="readout"){
        fDisplayTree->Branch("RecoTracks", "vector<adp::AnaTrack>",   &fRecoDisplay);
    }*/



    return true;
}
