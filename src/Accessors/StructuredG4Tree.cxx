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

	fMom = new vector<TLorentzVector>();
	fPos = new vector<TLorentzVector>();
	//fG4ps = new vector<G4Particle*>();
	//fG4Particles = new vector<G4Particle>();
	//fG4TruthIndex = new vector<UInt_t>();
	SetupRead(tree); //initialize tree pointer in TreeReader instance and set branch address
}//

StructuredG4Tree::~StructuredG4Tree(){
	delete fMom;
	delete fPos;
	//delete fG4ps;
	//delete fG4Particles;
	//delete fG4TruthIndex;
}

bool StructuredG4Tree::SetBranchAddresses() {

    fTreeIn->SetBranchAddress("Event",        &fEvent,        &b_Event       );
    fTreeIn->SetBranchAddress("TruthIndex",   &fG4TruthIndex, &b_G4TruthIndex);
    fTreeIn->SetBranchAddress("G4Particles",  &fG4Particles,  &b_G4Particles );

    return true;
}//

G4Particle* StructuredG4Tree::GetParticle(UInt_t iparticle){

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

vector<TLorentzVector>* StructuredG4Tree::SimMom(UInt_t iparticle) {

	//probably need to add one entry/exit point per volume of interest
	// for now, just use particle start and end points

	fMom->clear();
	G4Particle* g = GetParticle(iparticle);

	TLorentzVector* pbeg = g->MomI();
	TLorentzVector* pend = g->MomF();

	fMom->push_back(*pbeg);
	fMom->push_back(*pend);

	return fMom;
}//

vector<TLorentzVector>* StructuredG4Tree::SimPos(UInt_t iparticle) {

	fPos->clear();
    G4Particle* g = GetParticle(iparticle);

	TLorentzVector* pbeg = g->PosI();
	TLorentzVector* pend = g->PosF();

	fPos->push_back(*pbeg);
	fPos->push_back(*pend);

	return fPos;
}//
