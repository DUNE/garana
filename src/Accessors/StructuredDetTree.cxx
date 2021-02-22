/*
 * StructuredDetTree.cxx
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/StructuredDetTree.h"

using namespace garana;

StructuredDetTree::StructuredDetTree(TTree* tree=0) {
	SetupRead(tree); //initialize tree pointer in TreeReader instance and set branch address
}

bool StructuredDetTree::SetBranchAddresses() {

    fTreeIn->SetBranchAddress("Event",         &fEvent,       &b_Event);
    //fTreeIn->SetBranchAddress("TPCDigits",   "vector<gar::raw::RawDigit>",     &fTPCDigits);
    //fTreeIn->SetBranchAddress("CaloDigits.", "vector<gar::raw::CaloDigit>",    &fCaloDigits);
    /*if(fGeo->HasMuonDetector()){
        fTreeIn->Branch("MuDigits.", "vector<gar::raw::CaloDigit>",    &fMuDigits);
    }*/


    return true;
}
