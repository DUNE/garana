/*
 * StructuredG4Tree.cxx
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/StructuredG4Tree.h"

using namespace garana;
using std::vector;

StructuredG4Tree::StructuredG4Tree(TTree* tree=0) {

	SetupRead(tree); //initialize tree pointer in TreeReader instance and set branch address
}//

bool StructuredG4Tree::SetBranchAddresses() {

    fTreeIn->SetBranchAddress("Event",        &fEvent,        &b_Event       );
    fTreeIn->SetBranchAddress("TruthIndex",   &fG4TruthIndex, &b_G4TruthIndex);
    //fTreeIn->SetBranchAddress("FSIndex",      &fG4FSIndex,    &b_G4FSIndex);
    fTreeIn->SetBranchAddress("G4Particles",  &fG4Particles,  &b_G4Particles );

    return true;
}//

const bool  StructuredG4Tree::IsPrimary(const UInt_t& iparticle) const {
	if(GetParticle(iparticle)->ParentPDG()==INT_MAX) return true;
	else return false;
}

const Int_t StructuredG4Tree::PDG(const UInt_t& iparticle)       const {
	return GetParticle(iparticle)->PDG();
}

const G4Particle* StructuredG4Tree::GetParticle(const UInt_t& iparticle) const {

	try {
		if(iparticle<NSim())
			return &(this->fG4Particles->at(iparticle));
		else
			throw iparticle;
	}
	catch(UInt_t iparticle){
		std::cerr << "ERROR(StructuredG4Tree::GetParticle: index out of bounds ("
				  << NSim() << " vs. " << iparticle << ")" << std::endl;
	}
	return nullptr;

}//

/*vector<G4Particle*>* StructuredG4Tree::GetG4Particles() {

	fG4ps->clear();
	for(UInt_t i=0; i<NSim(); i++){
		fG4ps->push_back(GetParticle(i));
	}
	return fG4ps;

}//*/

const UInt_t StructuredG4Tree::NSim() const {
	return fG4Particles->size();
}//

const UInt_t StructuredG4Tree::NPoints(const UInt_t& iparticle) const {
	return GetParticle(iparticle)->NPoints();
}//

const UInt_t StructuredG4Tree::NRegions(const UInt_t& iparticle) const {
	return GetParticle(iparticle)->NRegions();
}
const Int_t  StructuredG4Tree::Region(const UInt_t& iparticle, const UInt_t& iregion) const {
	return GetParticle(iparticle)->Region(iregion);
}
const vector<const TLorentzVector*>* StructuredG4Tree::SimMomEnter(const UInt_t& iparticle) const {
	auto v = new vector<const TLorentzVector*>();
	for(size_t ireg=0; ireg<NRegions(iparticle); ireg++){
		v->push_back(GetParticle(iparticle)->MomentumEnter(ireg));
	}

	return v;
}
const vector<const TLorentzVector*>* StructuredG4Tree::SimMomExit(const UInt_t& iparticle)  const {
	auto v = new vector<const TLorentzVector*>();
	for(size_t ireg=0; ireg<NRegions(iparticle); ireg++){
		v->push_back(GetParticle(iparticle)->MomentumExit(ireg));
	}

	return v;
}
const vector<const TLorentzVector*>* StructuredG4Tree::SimPosEnter(const UInt_t& iparticle) const {
	auto v = new vector<const TLorentzVector*>();
	for(size_t ireg=0; ireg<NRegions(iparticle); ireg++){
		v->push_back(GetParticle(iparticle)->PositionEnter(ireg));
	}

	return v;
}
const vector<const TLorentzVector*>* StructuredG4Tree::SimPosExit(const UInt_t& iparticle)  const {
	auto v = new vector<const TLorentzVector*>();
	for(size_t ireg=0; ireg<NRegions(iparticle); ireg++){
		v->push_back(GetParticle(iparticle)->PositionExit(ireg));
	}

	return v;
}

const int StructuredG4Tree::ParentPDG(const UInt_t& iparticle)         const {
	return GetParticle(iparticle)->ParentPDG();
}//

const int StructuredG4Tree::ProgenitorPDG(const UInt_t& iparticle)     const {
	return GetParticle(iparticle)->ProgenitorPDG();
}//

const int StructuredG4Tree::TrackID(const UInt_t& iparticle)           const {
	return GetParticle(iparticle)->TrackID();
}//

const int StructuredG4Tree::ParentTrackID(const UInt_t& iparticle)     const {
	return GetParticle(iparticle)->ParentTrackID();
}//

const int StructuredG4Tree::ProgenitorTrackID(const UInt_t& iparticle) const {
	return GetParticle(iparticle)->ProgenitorTrackID();
}//

const Int_t StructuredG4Tree::ProcessI(const UInt_t& iparticle) const {
	return GetParticle(iparticle)->ProcessI();
}//

const Int_t StructuredG4Tree::ProcessF(const UInt_t& iparticle) const {
	return GetParticle(iparticle)->ProcessF();
}//



