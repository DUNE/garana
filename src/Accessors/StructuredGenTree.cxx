
#include "include/garana/Accessors/StructuredGenTree.h"
#include <climits>

using namespace garana;

StructuredGenTree::StructuredGenTree() {}
StructuredGenTree::StructuredGenTree(TTree* tree){

    SetupRead(tree); //initialize tree pointer in TreeReader instance and set branch address

}//

bool StructuredGenTree::SetBranchAddresses()
{
    // Set branch addresses and branch pointers
    fTreeIn->SetBranchAddress("Event",       &fEvent,       &b_Event);
    fTreeIn->SetBranchAddress("GIndex",      &fGIndex,      &b_GIndex);
    fTreeIn->SetBranchAddress("GTruth",      &fGTruth,      &b_GTruth);
    fTreeIn->SetBranchAddress("FSParticles", &fFSParticles, &b_FSParticles);

    return true;
}//

// get number of MCTruths in this event
const UInt_t   StructuredGenTree::NGen() const {
    return fFSParticles->size();
}//

//get pointer to igen^th GTruth object
const GTruth* StructuredGenTree::GetGTruth(const UInt_t igen) const {

	if(!IsGenie(igen)) {
		const GTruth* ptr = nullptr;
		return ptr;
	}
	else {
		const GTruth* ptr = &(fGTruth->at(igen));
		return ptr;
	}
}

// get number of FSParticles associated with igen'th MCTruth
const UInt_t   StructuredGenTree::NFSParticles(const UInt_t igen ) const {

    UInt_t index = CheckFSRange(igen) ? igen : 0;
    return fFSParticles->at(index).size();

}//

//Fill a passed vector with GenFSParticles for the igen'th MCTruth
const std::vector<FSParticle>* StructuredGenTree::GetParticles(const UInt_t igen) const {

	UInt_t index = CheckFSRange(igen) ? igen : 0;
    return &(fFSParticles->at(index));

}//

// returns true if MCTruth (FSParticles) came from GENIE
const Bool_t  StructuredGenTree::IsGenie(const UInt_t igen) const {

    if(fGIndex->size()==fFSParticles->size()){
        UInt_t index = CheckFSRange(igen) ? igen : 0;
        return fGIndex->at(index) != -1;
    }
    else{
        std::cout << "ERROR: StructuredGenTree::IsGenie -> "
                  << " sizeof(GIndex) != sizeof(FSParticles)"
                  << std::endl;
        return false;
    }
}//

// check if nu interaction is CC (supports only GENIE ints for now)
const Bool_t  StructuredGenTree::IsCC(const UInt_t igen) const {

    if(IsGenie(igen))
        return fGTruth->at(igen).fGint == 2;
    else
        return false;

}//

// Get the GENIE neutrino PDG code
const Int_t   StructuredGenTree::NuPDG(const UInt_t igen) const {

    if(IsGenie(igen))
        return fGTruth->at(igen).fProbePDG;
    else
        return INT_MAX;

}

// Get the GENIE neutrino four-momentum prior to interacting
TLorentzVector* StructuredGenTree::NuP(const UInt_t igen) {

    if(IsGenie(igen))
        return &(fGTruth->at(igen).fProbeP4);

    else
        return nullptr;
}

//Get the GENIE neutrino vertex four-position
TLorentzVector* StructuredGenTree::NuVertex(const UInt_t igen) {

    if(IsGenie(igen))
        return &(fGTruth->at(igen).fVertex);

    else
        return nullptr;
}

// Calculate the total energy of the FS system (excludes fleeting neutrinos e.g. from NC ints)
const Float_t StructuredGenTree::FSEnergy(UInt_t igen) const {

    Float_t e = 0.;
    for(auto const& fsp : fFSParticles->at(igen))
        e += fsp.E();

    return e;
}

//utility method for checking validity of index for FSParticles
Bool_t StructuredGenTree::CheckFSRange( UInt_t igen) const {
    if(igen < fFSParticles->size())
        return kTRUE;
    else{
        std::cout << "ERROR: StructuredGenTree -> "
                  << "passed index to FSParticle is out of range ("
                  << igen << " vs. " << fFSParticles->size() << ")."
                  << " Returning first element."
                  << std::endl;
        return kFALSE;
    }
}//
