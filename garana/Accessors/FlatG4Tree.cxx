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

}

FlatG4Tree::FlatG4Tree(TTree* tree, char opt)
{
	CheckOpt(opt);//sets TreeReader::fOpt

    if(fOpt=='r'){
    	std::cout << "constructed FlatG4Tree object in read-only mode" << std::endl;
    	SetupRead(tree);
    }
    else {
    	std::cout << "constructed FlatG4Tree object in write mode" << std::endl;
    	fTreeIn = tree;
    	SetBranchAddresses();
    	SetVecs();
    }

}


void FlatG4Tree::GetEntry(const UInt_t& ientry) {

	FillIndexMap();
	if(ientry != fCurrentEntry) {
		fCurrentEntry = ientry;
		fTreeIn->GetEntry(ientry);
	}
}

bool FlatG4Tree::SetBranchAddresses(){

std::cout << "FlatG4Tree SetBranchAddresses()" << std::endl;

	if(fOpt=='r'){
		fTreeIn->SetBranchAddress("Event",             &fEvent,             &b_Event            );
	    fTreeIn->SetBranchAddress("TruthIndex",        &fG4TruthIndex,      &b_G4TruthIndex     );
	    //fTreeIn->SetBranchAddress("FSIndex",      &fG4FSIndex,    &b_G4FSIndex);
		fTreeIn->SetBranchAddress("NSim",              &fNSim,              &b_NSim             );
		fTreeIn->SetBranchAddress("NPts",              &fNPts,              &b_NPts             );
		fTreeIn->SetBranchAddress("NRegions",          &fNRegions,          &b_NRegions         );
		fTreeIn->SetBranchAddress("Region",            &fRegions,           &b_Regions          );
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
		fTreeIn->Branch("NRegions",          &fNRegions                   );
		fTreeIn->Branch("Region",            &fRegions                    );
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

 const UInt_t FlatG4Tree::NPoints(const UInt_t& iparticle) const {
 	return fNPts->at(iparticle);
 }//

 const bool   FlatG4Tree::IsPrimary(const UInt_t& iparticle) const {
	if(fParentPdg->at(iparticle)==INT_MAX) return true;
	else return false;
 }

 const Int_t  FlatG4Tree::PDG(const UInt_t& iparticle)       const {
	 return fPDG->at(iparticle);
 }

const UInt_t FlatG4Tree::NRegions(const UInt_t& iparticle) const {
	return fNRegions->at(iparticle);
}

const Int_t FlatG4Tree::Region(const UInt_t& iparticle, const UInt_t& iregion) const {
	return fRegions->at(LocalToGlobalIndex(iparticle)+iregion);
}

const vector<const TLorentzVector*>*  FlatG4Tree::SimMomEnter(const UInt_t& iparticle) const {

		//output vector
		auto v = new vector<const TLorentzVector*>();

		//get index range
		size_t ireg = LocalToGlobalIndex(iparticle);
		size_t ireg_max = ireg+2*fNRegions->at(iparticle);

		//fill for all regions
		//entry points are every other value and precede exit points
		for(; ireg<ireg_max; ireg+=2){
			v->push_back(new TLorentzVector(fPx->at(ireg), fPy->at(ireg),
					                          fPz->at(ireg), fE->at(ireg)));
		}
		return v;
}

const vector<const TLorentzVector*>*  FlatG4Tree::SimMomExit(const UInt_t& iparticle)  const {

	//output vector
	auto v = new vector<const TLorentzVector*>();

	//get index range
	size_t ireg = LocalToGlobalIndex(iparticle)+1;
	const size_t ireg_max = ireg-1 + 2*fNRegions->at(iparticle);

	//fill for all regions
	//exit points are every other value and follow entry points
	for(; ireg<ireg_max; ireg+=2){
		v->push_back(new TLorentzVector(fPx->at(ireg), fPy->at(ireg),
				                          fPz->at(ireg), fE->at(ireg)));
	}
	return v;
}

const vector<const TLorentzVector*>*  FlatG4Tree::SimPosEnter(const UInt_t& iparticle) const {

	//output vector
	auto v = new vector<const TLorentzVector*>();

	//get index range
	size_t ireg = LocalToGlobalIndex(iparticle);
	size_t ireg_max = ireg+2*fNRegions->at(iparticle);

	//fill for all regions
	//exit points are every other value and follow entry points
	for(; ireg<ireg_max; ireg+=2){
		v->push_back(new TLorentzVector(fX->at(ireg), fY->at(ireg),
				                          fZ->at(ireg), fT->at(ireg)));
	}
	return v;
}

const vector<const TLorentzVector*>*  FlatG4Tree::SimPosExit(const UInt_t& iparticle)  const {

	//output vector
	auto v = new vector<const TLorentzVector*>();

	//get index range
	size_t ireg = LocalToGlobalIndex(iparticle)+1;
	size_t ireg_max = ireg-1 + 2*fNRegions->at(iparticle);

	//fill for all regions
	//exit points are every other value and follow entry points
	for(; ireg<ireg_max; ireg+=2){
		v->push_back(new TLorentzVector(fX->at(ireg), fY->at(ireg),
				                          fZ->at(ireg), fT->at(ireg)));
	}
	return v;
}

const TLorentzVector* FlatG4Tree::SimMomEnter(const UInt_t& iparticle, const UInt_t& iregion) const {
	UInt_t index = LocalToGlobalIndex(iparticle) + iregion;
	return new TLorentzVector(fPx->at(index), fPy->at(index), fPz->at(index), fE->at(index));
}

const TLorentzVector* FlatG4Tree::SimMomExit(const UInt_t& iparticle, const UInt_t& iregion) const {
	UInt_t index = LocalToGlobalIndex(iparticle) + 1 + iregion;
	return new TLorentzVector(fPx->at(index), fPy->at(index), fPz->at(index), fE->at(index));
}

const TLorentzVector* FlatG4Tree::SimPosEnter(const UInt_t& iparticle, const UInt_t& iregion) const {
	UInt_t index = LocalToGlobalIndex(iparticle) + iregion;
	return new TLorentzVector(fX->at(index), fY->at(index), fZ->at(index), fT->at(index));
}
const TLorentzVector* FlatG4Tree::SimPosExit(const UInt_t& iparticle, const UInt_t& iregion) const {
	UInt_t index = LocalToGlobalIndex(iparticle) + 1 + iregion;
	return new TLorentzVector(fX->at(index), fY->at(index), fZ->at(index), fT->at(index));
}

const int FlatG4Tree::ParentPDG(const UInt_t& iparticle)         const {
	return fParentPdg->at(LocalToGlobalIndex(iparticle));
}

const int FlatG4Tree::ProgenitorPDG(const UInt_t& iparticle)     const {
	return fProgenitorPdg->at(LocalToGlobalIndex(iparticle));
}

const int FlatG4Tree::TrackID(const UInt_t& iparticle)           const {
	return fTrkID->at(LocalToGlobalIndex(iparticle));
}

const int FlatG4Tree::ParentTrackID(const UInt_t& iparticle)     const {
	return fParentTrackId->at(LocalToGlobalIndex(iparticle));
}

const int FlatG4Tree::ProgenitorTrackID(const UInt_t& iparticle) const {
	return fProgenitorTrackId->at(LocalToGlobalIndex(iparticle));
}

const Int_t FlatG4Tree::ProcessI(const UInt_t& iparticle) const {
	return fProcessI->at(LocalToGlobalIndex(iparticle));
}

const Int_t FlatG4Tree::ProcessF(const UInt_t& iparticle) const {
	return fProcessF->at(LocalToGlobalIndex(iparticle));
}

const UInt_t FlatG4Tree::NSubEntries() const {
	return fTrkID->size();
}

void FlatG4Tree::FillIndexMap() {
	fLocalToGlobalIndex.clear();
	UInt_t iparticle=0;
	int trkid = -1; fTrkID->at(0);
	for(UInt_t i=0; i<NSubEntries(); i++){
		if(trkid!=fTrkID->at(i)){
			fLocalToGlobalIndex[iparticle] = i;
			trkid = fTrkID->at(i);
			iparticle++;
		}
	}
}

const UInt_t FlatG4Tree::LocalToGlobalIndex(const UInt_t& iparticle) const {

	return fLocalToGlobalIndex.at(iparticle);
}
