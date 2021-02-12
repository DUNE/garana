
#include "include/garana/Accessors/StructuredGenTree.h"
#include <climits>

using namespace garana;

StructuredGenTree::StructuredGenTree() {}
StructuredGenTree::StructuredGenTree(TTree* tree){
    std::cout << "call StructuredGen constructor" << std::endl;
    SetupRead(tree); //initialize tree pointer in TreeReader instance and set branch address
}

bool StructuredGenTree::SetBranchAddresses()
{
    //if(DEBUG_GEN) 
    std::cout << " ....inside setbranchaddresses.... " << std::endl;

    // Set branch addresses and branch pointers
    fTreeIn->SetBranchAddress("GIndex",      &fGIndex,      &b_GIndex);
    fTreeIn->SetBranchAddress("GTruth",      &fGTruth,      &b_GTruth);
    fTreeIn->SetBranchAddress("FSParticles", &fFSParticles, &b_FSParticles);

    //if(DEBUG_GEN) 
    std::cout << " fTreeIn::" << fTreeIn->GetEntries() << std::endl;
    return true;
}


// get number of MCTruths in this event
UInt_t   StructuredGenTree::NGen() const {
    return fFSParticles->size();
}//

// get number of FSParticles associated with igen'th MCTruth
UInt_t   StructuredGenTree::NFSParticles( UInt_t igen ) const {

    UInt_t index = CheckFSRange(igen) ? igen : 0;
    return fFSParticles->at(index).size();

}//

//Fill a passed vector with GenFSParticles for the igen'th MCTruth
const std::vector<FSParticle>* StructuredGenTree::GetParticles(UInt_t igen) const {

    UInt_t index = CheckFSRange(igen) ? igen : 0;
    return &(fFSParticles->at(index));

}//

// returns true if MCTruth (FSParticles) came from GENIE
Bool_t  StructuredGenTree::IsGenie(UInt_t igen) const {

    std::cout << "GenTree::IsGenie(): check GIndex vs. FSParticles sizes..." << '\n';
    std::cout << "    GIndex:      " << fGIndex->size() << " vs. " << '\n';
    std::cout << "    FSParticles: " << fFSParticles->size() << std::endl;
    if(fGIndex->size()==fFSParticles->size()){
        std::cout << "call CheckFSRange" << std::endl;
        UInt_t index = CheckFSRange(igen) ? igen : 0;
        std::cout << "index: " << index << std::endl;
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
Bool_t  StructuredGenTree::IsCC(UInt_t igen) const {

    if(IsGenie(igen))
        return fGTruth->at(igen).fGint == 2;
    else
        return false;

}//

// Get the GENIE neutrino PDG code
Int_t   StructuredGenTree::NuPDG(UInt_t igen) const {

    if(IsGenie(igen))
        return fGTruth->at(igen).fProbePDG;
    else
        return INT_MAX;

}

// Get the GENIE neutrino four-momentum prior to interacting
TLorentzVector StructuredGenTree::NuP(UInt_t igen) const {

    if(IsGenie(igen))
        return fGTruth->at(igen).fProbeP4;

    else
        return TLorentzVector();
}

//Get the GENIE neutrino vertex four-position
TLorentzVector StructuredGenTree::NuVertex(UInt_t igen) const {

    if(IsGenie(igen))
        return fGTruth->at(igen).fVertex;

    else
        return TLorentzVector();
}

// Calculate the total energy of the FS system (excludes fleeting neutrinos e.g. from NC ints)
Float_t StructuredGenTree::FSEnergy(UInt_t igen) const {

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
