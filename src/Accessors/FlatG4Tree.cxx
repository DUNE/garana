/*
 * FlatG4Tree.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/FlatG4Tree.h"

using std::vector;
using namespace garana;

// assumes read-only mode
FlatG4Tree::FlatG4Tree(TTree* tree)
{
    SetupRead(tree);
    SetLimits();
}

FlatG4Tree::FlatG4Tree(TTree* tree, char opt)
{
	CheckOpt(opt);//sets TreeReader::fOpt

    if(fOpt=='r'){
    	std::cout << "constructed FlatG4Tree object in read-only mode" << std::endl;
    	SetupRead(tree);
    	SetLimits();
    }
    else {
    	std::cout << "constructed FlatG4Tree object in write mode" << std::endl;
    	fTreeIn = tree;
    	SetBranchAddresses();
    	SetVecs();
    	SetLimits();
    }

}


/*void FlatG4Tree::GetEntry(UInt_t entry) {
	this->fG4ToFSLimits.clear();
	fTreeIn->GetEntry(entry);
    this->FindFSLimits();
}*/

bool FlatG4Tree::SetBranchAddresses(){

std::cout << "FlatG4Tree SetBranchAddresses()" << std::endl;

	if(fOpt=='r'){
		fTreeIn->SetBranchAddress("Event",             &fEvent,             &b_Event            );
	    fTreeIn->SetBranchAddress("TruthIndex",        &fG4TruthIndex,      &b_G4TruthIndex     );
	    //fTreeIn->SetBranchAddress("FSIndex",      &fG4FSIndex,    &b_G4FSIndex);
		fTreeIn->SetBranchAddress("NSim",              &fNSim,              &b_NSim             );
		fTreeIn->SetBranchAddress("NPts",              &fNPts,              &b_NPts             );
		fTreeIn->SetBranchAddress("TrkID",             &fTrkID,             &b_TrkID            );
		fTreeIn->SetBranchAddress("Pdg",               &fPDG,               &b_PDG              );
		fTreeIn->SetBranchAddress("ParentPdg",         &fParentPdg,         &b_ParentPdg        );
		fTreeIn->SetBranchAddress("ProgenitorPdg",     &fProgenitorPdg,     &b_ProgenitorPdg    );
		fTreeIn->SetBranchAddress("ParentTrackId",     &fParentTrackId,     &b_ParentTrackId    );
		fTreeIn->SetBranchAddress("ProgenitorTrackId", &fProgenitorTrackId, &b_ProgenitorTrackId);
		fTreeIn->SetBranchAddress("ProcessI",          &fProcessI,          &b_ProcessI         );
		fTreeIn->SetBranchAddress("ProcessF",          &fProcessF,          &b_ProcessF         );
		fTreeIn->SetBranchAddress("X",                 &fX,                 &b_X                );
		fTreeIn->SetBranchAddress("Y",                 &fY,                 &b_Y                );
		fTreeIn->SetBranchAddress("Z",                 &fZ,                 &b_Z                );
		fTreeIn->SetBranchAddress("T",                 &fT,                 &b_T                );
		fTreeIn->SetBranchAddress("Px",                &fPx,                &b_Px               );
		fTreeIn->SetBranchAddress("Py",                &fPy,                &b_Py               );
		fTreeIn->SetBranchAddress("Pz",                &fPz,                &b_Pz               );
		fTreeIn->SetBranchAddress("E",                 &fE,                 &b_E                );

	}


	if(fOpt=='w'){

		fTreeIn->Branch("Event",             &fEvent,            "Event/I");
		fTreeIn->Branch("NSim",              &fNSim,             "NSim/I" );
		fTreeIn->Branch("NPts",              &fNPts                       );
		fTreeIn->Branch("TrkID",             &fTrkID                      );
		fTreeIn->Branch("Pdg",               &fPDG                        );
		fTreeIn->Branch("ParentPdg",         &fParentPdg                  );
		fTreeIn->Branch("ProgenitorPdg",     &fProgenitorPdg              );
		fTreeIn->Branch("ParentTrackId",     &fParentTrackId              );
		fTreeIn->Branch("ProgenitorTrackId", &fProgenitorTrackId          );
		fTreeIn->Branch("ProcessI",          &fProcessI                   );
		fTreeIn->Branch("ProcessF",          &fProcessF                   );
		fTreeIn->Branch("X",                 &fX                          );
		fTreeIn->Branch("Y",                 &fY                          );
		fTreeIn->Branch("Z",                 &fZ                          );
		fTreeIn->Branch("T",                 &fT                          );
		fTreeIn->Branch("Px",                &fPx                         );
		fTreeIn->Branch("Py",                &fPy                         );
		fTreeIn->Branch("Pz",                &fPz                         );
		fTreeIn->Branch("E",                 &fE                          );
	}

	return true;
}

//implement accessors inherited from G4Tree
 void FlatG4Tree::SetVecs() {

	 fNPts                 = new vector<UInt_t>();
	 fTrkID                = new vector<Int_t>();
	 fPDG                  = new vector<Int_t>();
	 fParentPdg            = new vector<Int_t>();
	 fProgenitorPdg        = new vector<Int_t>();
	 fParentTrackId        = new vector<Int_t>();
	 fProgenitorTrackId    = new vector<Int_t>();
	 fProcessI             = new vector<Int_t>();
	 fProcessF             = new vector<Int_t>();
	 fX                    = new vector<Float_t>();
	 fY                    = new vector<Float_t>();
	 fZ                    = new vector<Float_t>();
	 fT                    = new vector<Float_t>();
	 fPx                   = new vector<Float_t>();
	 fPy                   = new vector<Float_t>();
	 fPz                   = new vector<Float_t>();
	 fE                    = new vector<Float_t>();

 }

 void FlatG4Tree::ClearVecs() {

	 fNPts->clear();
	 fTrkID->clear();
	 fPDG->clear();
	 fParentPdg->clear();
	 fProgenitorPdg->clear();
	 fParentTrackId->clear();
	 fProgenitorTrackId->clear();
	 fProcessI->clear();
	 fProcessF->clear();
	 fX->clear();
	 fY->clear();
	 fZ->clear();
	 fT->clear();
	 fPx->clear();
	 fPy->clear();
	 fPz->clear();
	 fE->clear();

 }

 const UInt_t FlatG4Tree::NSim() const {
	 return fNSim;
 }//

 const bool   FlatG4Tree::IsPrimary(const UInt_t& iparticle) const {
	if(fParentPdg->at(iparticle)==INT_MAX) return true;
	else return false;
 }

 const Int_t  FlatG4Tree::PDG(const UInt_t& iparticle)       const {
	 return fPDG->at(iparticle);
 }


const vector<TLorentzVector>* FlatG4Tree::SimMom(const UInt_t& iparticle) {
	UInt_t first = fLimits[iparticle].first;
	UInt_t last = fLimits[iparticle].second;
	vector<TLorentzVector>* v = new vector<TLorentzVector>();
	v->push_back(TLorentzVector(fPx->at(first),fPy->at(first),fPz->at(first),fE->at(first)));
	v->push_back(TLorentzVector(fPx->at(last),fPy->at(last),fPz->at(last),fE->at(last)));
	return v;

}
// FIX ME (dummy implementation)
const vector<TLorentzVector>* FlatG4Tree::SimPos(const UInt_t& iparticle) {
	UInt_t first = fLimits[iparticle].first;
	UInt_t last = fLimits[iparticle].second;
	vector<TLorentzVector>* v = new vector<TLorentzVector>();
	v->push_back(TLorentzVector(fX->at(first),fY->at(first),fZ->at(first),fT->at(first)));
	v->push_back(TLorentzVector(fX->at(last), fY->at(last), fZ->at(last), fT->at(last)));
	return v;
}

const int FlatG4Tree::ParentPDG(const UInt_t& iparticle)         const {
	return fParentPdg->at(iparticle);
}

const int FlatG4Tree::ProgenitorPDG(const UInt_t& iparticle)     const {
	return fProgenitorPdg->at(iparticle);
}

const int FlatG4Tree::TrackID(const UInt_t& iparticle)           const {
	return fTrkID->at(iparticle);
}

const int FlatG4Tree::ParentTrackID(const UInt_t& iparticle)     const {
	return fParentTrackId->at(iparticle);
}

const int FlatG4Tree::ProgenitorTrackID(const UInt_t& iparticle) const {
	return fProgenitorTrackId->at(iparticle);
}

void FlatG4Tree::SetLimits(){
	UInt_t last=0;
	for(UInt_t i=0; i<fNSim; i++) {
		fLimits[i] = std::make_pair(last,last+fNPts->at(i));
		last += fNPts->at(i);
	}
}
