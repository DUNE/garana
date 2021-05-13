
#include "garana/Accessors/StructuredGenTree.h"
#include <climits>

using namespace garana;

StructuredGenTree::StructuredGenTree(TTree* tree){

    SetupRead(tree); //initialize tree pointer in TreeReader instance and set branch address

}//

bool StructuredGenTree::SetBranchAddresses()
{
    // Set branch addresses and branch pointers
    fTreeIn->SetBranchAddress("Event",       &fEvent,       &b_Event);
    fTreeIn->SetBranchAddress("GIndex",      &fGIndex,      &b_GIndex);
    //fTreeIn->SetBranchAddress("FSIndex",     &fFSIndex,     &b_FSIndex);
    fTreeIn->SetBranchAddress("GTruth",      &fGTruth,      &b_GTruth);
    fTreeIn->SetBranchAddress("FSParticles", &fFSParticles, &b_FSParticles);

    return true;
}//

// get number of MCTruths in this event
const UInt_t StructuredGenTree::NGen() const {
    return fFSParticles->size();
}//

//get pointer to igen^th GTruth object
const GTruth* StructuredGenTree::GetGTruth(const UInt_t& igen) const {

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
const UInt_t StructuredGenTree::NFSParticles(const UInt_t& igen ) const {

    UInt_t index = CheckFSRange(igen) ? igen : 0;
    return fFSParticles->at(index).size();

}//

//Fill a passed vector with GenFSParticles for the igen'th MCTruth
const std::vector<FSParticle>* StructuredGenTree::GetParticles(const UInt_t& igen) const {

	UInt_t index = CheckFSRange(igen) ? igen : 0;
    return &(fFSParticles->at(index));

}//

// returns true if MCTruth (FSParticles) came from GENIE
const Bool_t StructuredGenTree::IsGenie(const UInt_t& igen) const {

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
const Bool_t StructuredGenTree::IsCC(const UInt_t& igen) const {

    if(IsGenie(igen))
        return fGTruth->at(igen).fGint == 2;
    else
        return false;

}//

// Get the region code for the neutrino vertex
const int StructuredGenTree::NuRegion(const UInt_t& igen ) const {

	if(IsGenie(igen))
		return fGTruth->at(igen).fVertexRegion;
	else
		return INT_MAX;

}//

// Get the GENIE neutrino PDG code
const Int_t StructuredGenTree::NuPDG(const UInt_t& igen) const {

    if(IsGenie(igen))
        return fGTruth->at(igen).fProbePDG;
    else
        return INT_MAX;

}

// Get the GENIE neutrino four-momentum prior to interacting
const TLorentzVector* StructuredGenTree::NuP(const UInt_t& igen) {

    if(IsGenie(igen))
        return &(fGTruth->at(igen).fProbeP4);

    else
        return nullptr;
}

//Get the GENIE neutrino vertex four-position
const TLorentzVector* StructuredGenTree::NuVertex(const UInt_t& igen) {

    if(IsGenie(igen))
        return &(fGTruth->at(igen).fVertex);

    else
        return nullptr;
}

const int StructuredGenTree::ScatterCode(const UInt_t& igen) const {
	return GetGTruth(igen)->fGscatter;
}

const int StructuredGenTree::InteractCode(const UInt_t& igen) const {
	return GetGTruth(igen)->fGint;
}

const TLorentzVector* StructuredGenTree::TgtP4(const UInt_t& igen) const {
		return &(GetGTruth(igen)->fTgtP4);
}

const int StructuredGenTree::TgtZ(const UInt_t& igen ) const {
	return GetGTruth(igen)->ftgtZ;
}

const int StructuredGenTree::TgtA(const UInt_t& igen ) const {
	return GetGTruth(igen)->ftgtA;
}

const int StructuredGenTree::TgtPDG(const UInt_t& igen ) const {
	return GetGTruth(igen)->ftgtPDG;
}

const int StructuredGenTree::HitNucPDG(const UInt_t& igen ) const {
	return GetGTruth(igen)->fHitNucPDG;
}

const TLorentzVector* StructuredGenTree::HitNucP4(const UInt_t& igen ) const {
	return &(GetGTruth(igen)->fHitNucP4);
}

const double StructuredGenTree::Q2(const UInt_t& igen ) const {
	return GetGTruth(igen)->fgQ2;
}

const double StructuredGenTree::q2(const UInt_t& igen ) const {
	return GetGTruth(igen)->fgq2;
}

const double StructuredGenTree::W(const UInt_t& igen ) const {
	return GetGTruth(igen)->fgW;
}

const double StructuredGenTree::T(const UInt_t& igen ) const {
	return GetGTruth(igen)->fgT;
}

const double StructuredGenTree::X(const UInt_t& igen ) const {
	return GetGTruth(igen)->fgX;
}

const double StructuredGenTree::Y(const UInt_t& igen ) const {
	return GetGTruth(igen)->fgY;
}

const TLorentzVector* StructuredGenTree::FSLeptonP4(const UInt_t& igen )   const {
	return &(GetGTruth(igen)->fFSleptonP4);
}

const TLorentzVector* StructuredGenTree::FSHadSystP4(const UInt_t& igen )  const {
	return &(GetGTruth(igen)->fFShadSystP4);
}

const int StructuredGenTree::NumNuProton(const UInt_t& igen)  const {
	return GetGTruth(igen)->fNumProton;
}

const int StructuredGenTree::NumNuNeutron(const UInt_t& igen) const {
	return GetGTruth(igen)->fNumNeutron;
}

const int StructuredGenTree::NumNuPi0(const UInt_t& igen)     const {
	return GetGTruth(igen)->fNumPi0;
}

const int StructuredGenTree::NumNuPiPlus(const UInt_t& igen)  const {
	return GetGTruth(igen)->fNumPiPlus;
}

const int StructuredGenTree::NumNuPiMinus(const UInt_t& igen) const {
	return GetGTruth(igen)->fNumPiMinus;
}

// Calculate the total energy of the FS system (excludes fleeting neutrinos e.g. from NC ints)
const Float_t StructuredGenTree::FSTotEnergy(const UInt_t& igen) const {

    Float_t e = 0.;
    for(auto const& fsp : fFSParticles->at(igen))
        e += fsp.E();

    return e;
}

const Float_t StructuredGenTree::FSEnergy(const UInt_t& igen, const UInt_t& ifsp) const {
	return fFSParticles->at(igen)[ifsp].E();
}

const Float_t StructuredGenTree::FSPDG(const UInt_t& igen, const UInt_t& ifsp)    const {
	return fFSParticles->at(igen)[ifsp].PDG();
}

const Int_t StructuredGenTree::FSTrackId(const UInt_t& igen, const UInt_t& ifsp)  const {
	return fFSParticles->at(igen)[ifsp].TrackId();
}

//utility method for checking validity of index for FSParticles
const Bool_t StructuredGenTree::CheckFSRange(const UInt_t& igen) const {
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
