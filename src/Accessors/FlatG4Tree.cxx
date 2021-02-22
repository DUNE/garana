/*
 * FlatG4Tree.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/FlatG4Tree.h"

using std::vector;
using namespace garana;

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

/*void FlatG4Tree::GetEntry(UInt_t entry) {
	this->fG4ToFSLimits.clear();
	fTreeIn->GetEntry(entry);
    this->FindFSLimits();
}*/

bool FlatG4Tree::SetBranchAddresses(){

std::cout << "FlatG4Tree SetBranchAddresses()" << std::endl;

	if(fOpt=='r'){
		fTreeIn->SetBranchAddress("Event",             &fEvent,             &b_Event            );
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
	 return this->fNSim;
 }//

 //FIX ME (dummy implementation)
vector<TLorentzVector>* FlatG4Tree::SimMom(UInt_t iparticle) {
	if(iparticle>0)
		return nullptr;
	return nullptr;
}
// FIX ME (dummy implementation)
vector<TLorentzVector>* FlatG4Tree::SimPos(UInt_t iparticle) {
	if(iparticle>0)
		return nullptr;
	return nullptr;
}
