/*
 * FlatGenTree.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "FlatGenTree.h"

using namespace garana;

FlatGenTree::FlatGenTree() {}

FlatGenTree::FlatGenTree(TTree* tree) {
    SetupRead(tree);
}

bool FlatGenTree::SetBranchAddresses(){

	fTreeIn->SetBranchAddress("FSParticlePDG", &fFSPdg,  &b_FSPdg);
	fTreeIn->SetBranchAddress("FSParticleX",   &fFSX  ,  &b_FSX  );
	fTreeIn->SetBranchAddress("FSParticleY",   &fFSY  ,  &b_FSY  );
	fTreeIn->SetBranchAddress("FSParticleZ",   &fFSZ  ,  &b_FSZ  );
	fTreeIn->SetBranchAddress("FSParticleT",   &fFST  ,  &b_FST  );
	fTreeIn->SetBranchAddress("FSParticlePx",  &fFSPx ,  &b_FSPx );
	fTreeIn->SetBranchAddress("FSParticlePy",  &fFSPy ,  &b_FSPy );
	fTreeIn->SetBranchAddress("FSParticlePz",  &fFSPz ,  &b_FSPz );
	fTreeIn->SetBranchAddress("FSParticleE",   &fFSE ,   &b_FSE  );

	return true;
}

//accessors inherited from GenTree
UInt_t FlatGenTree::NGen() const {
	return 0;
}
UInt_t FlatGenTree::NFSParticles( UInt_t igen ) const {
    return 0;
}
Bool_t FlatGenTree::IsGenie( UInt_t igen ) const {
    return kFALSE;
}
Bool_t FlatGenTree::IsCC( UInt_t igen ) const {
    return kFALSE;
}
Int_t FlatGenTree::NuPDG( UInt_t igen ) const {
    return 0;
}
TLorentzVector FlatGenTree::NuP( UInt_t igen) const {
	return TLorentzVector();
}
TLorentzVector FlatGenTree::NuVertex( UInt_t igen) const  {
	return TLorentzVector();
}
Float_t FlatGenTree::FSEnergy(UInt_t igen) const {
    return 0.;
}


