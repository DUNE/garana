/*
 * MillGenTree.cxx
 *
 *  Created on: Feb 13, 2021
 *      Author: chilgenb
 */

//#include "include/garana/Accessors/StructuredGenTree.h"
#include "include/garana/Processors/MillGenTree.h"

#include <TTree.h>

#include <map>
#include <iostream>

using std::vector;

using namespace garana;

namespace { //helper functions
	void FillEmpty(vector<double>* v);
	void FillEmpty(vector<int>* v);
	void FillEmpty(vector<bool>* v);
}//local namespace

MillGenTree::MillGenTree(TTree* treeIn, TTree* treeOut)
{
    fGenIn = new StructuredGenTree(treeIn);

    fTreeIn = treeOut;
    //fTreeOut = new TTree("genTree", "generator level information");
    //fGenOut= new FlatGenTree(treeOut,'w');

    fOpt='w';
	this->VerifyBranches();
	this->SetVecs();
	this->SetBranchAddresses();
	this->MillTrees();

}//constructor()

//Fill branches but do not fill
void MillGenTree::MillTrees() {

    if(!IsVerified()){
    	std::cerr << "WARNING(MillGenTree::MillTrees): "
    			  << "trying to mill trees that have not been verified"
    			  << std::endl;
    	return;
    }

    std::cout << "MillGenTree: loop over " << fGenIn->NEntries() << " gen entries" << std::endl;

    //loop over input genTree events (entries)
    for(size_t ientry=0; ientry<fGenIn->NEntries(); ientry++){

    	//fGenOut->ClearVecs(); //clear previous entry's data (if any)
    	ClearVecs();
    	fGenIn->GetEntry(ientry);

    	if(branchToDrawOpt[kGIndex])
    		fGIndex = fGenIn->GetGIndex();

    	if(branchToDrawOpt[kFSParticle]) {
    	    fNGen = fGenIn->NGen();
			std::cout << "MillGen: output NGen = " << fNGen << std::endl;
    	}

		//loop over gen entries (usually GTruths with 1 per event)
    	std::cout << "MillGenTree: loop over " << fGenIn->NGen() << " igen" <<std::endl;
		for(size_t igen=0; igen<fGenIn->NGen(); igen++){

			if(branchToDrawOpt[kFSParticle]) {

				//loop over FSparticles associated with this GTruth
				auto const& particles = fGenIn->GetParticles(igen);
				fNFS->push_back(particles->size());
				std::cout << "MillGenTree: igen->" << igen << " NFSP->"
						  << fNFS->back() << std::endl;
				FillFSParticle(particles);

			}//if filling FSParticle branches

			if(branchToDrawOpt[kGTruth]) {

				const GTruth* truth = fGenIn->GetGTruth(igen);

				if(!truth)
					FillEmptyGTruth();
				else
					FillGTruth(truth);

			}//if filling GTruth branches
		}//for gen entries

    	fTreeIn->Fill(); //actually our fTreeOut, but it's called fTreeIn in FlatGenTree.h, fill once per event
    }//for genTree entries

    fTreeIn->Write();

}//Mill()

bool MillGenTree::VerifyBranches() {

    // get list of branches and check it matches what we expect
    const TObjArray* branches = fGenIn->GetBranchList();
    std::cout << "got ObjArray of branches from fTreeIn" << std::endl;
    try {
    	if(!branches || branches->GetEntries()==0 )
    		throw branches;
    }
    catch(TObjArray* branches){
    	std::cerr << "ERROR(MillGenTree::VerifyBranches): no branches found in passed input tree"
    			  << std::endl;
    	return false;
    }

    if(branches->GetEntriesFast() != nameToGenBranch.size())
    	std::cout << "WARNING(MillGenTree::VerifyBranches): Mismatch in number of branches (expected "
    	          << nameToGenBranch.size() << " but found " << branches->GetEntriesFast()
    	          << ")" << std::endl;
    else
    	std::cout << "found genTree with " << branches->GetEntriesFast() << " branches" << std::endl;

    // loop over branches
    TIter next(branches);
    TBranch* branch = nullptr;
    while( (branch=(TBranch*)next())) {

    	// check if branch is expected
    	if(nameToGenBranch.find(CharStarToString(branch->GetFullName()))!=nameToGenBranch.end()) {

    		std::cout << "   chopping branch '" << branch->GetFullName() << "'" << std::endl;

    		if(nameToGenBranch[CharStarToString(branch->GetFullName())] == kEvent)
    			branchToDrawOpt[kEvent] = true;

    		if(nameToGenBranch[CharStarToString(branch->GetFullName())] == kGIndex)
        		branchToDrawOpt[kGIndex] = true;

    		if(nameToGenBranch[CharStarToString(branch->GetFullName())] == kGTruth)
        		branchToDrawOpt[kGTruth] = true;

    		if(nameToGenBranch[CharStarToString(branch->GetFullName())] == kFSParticle)
        		branchToDrawOpt[kFSParticle] = true;

    	}//endif known branch

    	else{
    		std::cout << "WARNING(MillGenTree): ignoring unknown branch '"
    				  << branch->GetFullName() << "'" << std::endl;
    	}//else

    }//for branches

    fIsVerified = true;
    return true;

}//VerifyBranches()

void MillGenTree::FillGTruth(const GTruth* truth){

	fNuX->push_back(truth->fVertex.X());
	fNuY->push_back(truth->fVertex.Y());
	fNuZ->push_back(truth->fVertex.Z());
	fNuT->push_back(truth->fVertex.T());

	fWeight->push_back(truth->fweight);
	fProbability->push_back(truth->fprobability);
	fXsec->push_back(truth->fXsec);
	fDiffXsec->push_back(truth->fDiffXsec);
	fGPhaseSpace->push_back(truth->fGPhaseSpace);

	fProbePDG->push_back(truth->fProbePDG);
	fProbePx->push_back(truth->fProbeP4.Px());
	fProbePy->push_back(truth->fProbeP4.Py());
	fProbePz->push_back(truth->fProbeP4.Pz());
	fProbeE->push_back(truth->fProbeP4.E());

	fTgtPx->push_back(truth->fProbeP4.Px());
	fTgtPy->push_back(truth->fProbeP4.Py());
	fTgtPz->push_back(truth->fProbeP4.Pz());
	fTgtE->push_back(truth->fProbeP4.E());
	fTgtZ->push_back(truth->ftgtZ);
	fTgtA->push_back(truth->ftgtA);
	fTgtPDG->push_back(truth->ftgtPDG);
	fHitNucPDG->push_back(truth->fHitNucPDG);
	fHitQrkPDG->push_back(truth->fHitQrkPDG);
	fIsSeaQuark->push_back(truth->fIsSeaQuark);

	fHitNucPx->push_back(truth->fHitNucP4.Px());
	fHitNucPy->push_back(truth->fHitNucP4.Py());
	fHitNucPz->push_back(truth->fHitNucP4.Pz());
	fHitNucE->push_back(truth->fHitNucP4.E());
	fHitNucPos->push_back(truth->fHitNucPos);
	fGscatter->push_back(truth->fGscatter);
	fGint->push_back(truth->fGint);
	fGQ2->push_back(truth->fgQ2);
	fGq2->push_back(truth->fgq2);
	fGW->push_back(truth->fgW);
	fGT->push_back(truth->fgT);
	fGX->push_back(truth->fgX);
	fGY->push_back(truth->fgY);

	fFSleptonPx->push_back(truth->fFSleptonP4.Px());
	fFSleptonPy->push_back(truth->fFSleptonP4.Py());
	fFSleptonPz->push_back(truth->fFSleptonP4.Pz());
	fFSleptonE->push_back(truth->fFSleptonP4.E());

	fFShadSystPx->push_back(truth->fFShadSystP4.Px());
	fFShadSystPy->push_back(truth->fFShadSystP4.Py());
	fFShadSystPz->push_back(truth->fFShadSystP4.Pz());
	fFShadSystE->push_back(truth->fFShadSystP4.E());

	fIsCharm->push_back(truth->fIsCharm);
	fCharmHadronPDG->push_back(truth->fCharmHadronPdg);
	fIsStrange->push_back(truth->fIsStrange);
	fStrangeHadronPDG->push_back(truth->fStrangeHadronPdg);
	fNumProton->push_back(truth->fNumProton);
	fNumNeutron->push_back(truth->fNumNeutron);
	fNumPi0->push_back(truth->fNumPi0);
	fNumPiPlus->push_back(truth->fNumPiPlus);
	fNumPiMinus->push_back(truth->fNumPiMinus);
	fResNum->push_back(truth->fResNum);
	fDecayMode->push_back(truth->fDecayMode);
}//FillGTruth()

void MillGenTree::FillEmptyGTruth(){

	FillEmpty(fNuX);
	FillEmpty(fNuY);
	FillEmpty(fNuZ);
	FillEmpty(fNuT);
	FillEmpty(fWeight);
	FillEmpty(fProbability);
	FillEmpty(fXsec);
	FillEmpty(fDiffXsec);
	FillEmpty(fGPhaseSpace);
	FillEmpty(fProbePDG);
	FillEmpty(fProbePx);
	FillEmpty(fProbePy);
	FillEmpty(fProbePz);
	FillEmpty(fProbeE);
	FillEmpty(fTgtPx);
	FillEmpty(fTgtPy);
	FillEmpty(fTgtPz);
	FillEmpty(fTgtE);

	FillEmpty(fTgtZ);
	FillEmpty(fTgtA);
	FillEmpty(fTgtPDG);
	FillEmpty(fHitNucPDG);
	FillEmpty(fHitQrkPDG);
	FillEmpty(fIsSeaQuark);
	FillEmpty(fHitNucPx);
	FillEmpty(fHitNucPy);
	FillEmpty(fHitNucPz);
	FillEmpty(fHitNucE);
	FillEmpty(fHitNucPos);

	FillEmpty(fGscatter);
	FillEmpty(fGint);
	FillEmpty(fGQ2);
	FillEmpty(fGq2);
	FillEmpty(fGW);
	FillEmpty(fGT);
	FillEmpty(fGX);
	FillEmpty(fGY);
	FillEmpty(fFSleptonPx);
	FillEmpty(fFSleptonPy);
	FillEmpty(fFSleptonPz);
	FillEmpty(fFSleptonE);
	FillEmpty(fFShadSystPx);
	FillEmpty(fFShadSystPy);
	FillEmpty(fFShadSystPz);
	FillEmpty(fFShadSystE);

	FillEmpty(fIsCharm);
	FillEmpty(fCharmHadronPDG);
	FillEmpty(fIsStrange);
	FillEmpty(fStrangeHadronPDG);
	FillEmpty(fNumProton);
	FillEmpty(fNumNeutron);
	FillEmpty(fNumPi0);
	FillEmpty(fNumPiPlus);
	FillEmpty(fNumPiMinus);
	FillEmpty(fResNum);
	FillEmpty(fDecayMode);
}//FillEmptyGTruth

void MillGenTree::FillFSParticle(const vector<FSParticle>* fsps){

	for( auto const& fsp : *fsps ) {

		fFSPdg->push_back(fsp.PDG());
		fFSPosX->push_back(fsp.X());
		fFSPosY->push_back(fsp.Y());
		fFSPosZ->push_back(fsp.Z());
		fFST->push_back(fsp.T());
		fFSMomX->push_back(fsp.Px());
		fFSMomY->push_back(fsp.Py());
		fFSMomZ->push_back(fsp.Pz());
		fFSE->push_back(fsp.E());

	}//for FSParticles
}//FillFSParticle

namespace {

	void FillEmpty(vector<double>* v){
    	v->push_back(DBL_MAX);
    }

	void FillEmpty(vector<int>* v){
	    	v->push_back(INT_MAX);
	}

	void FillEmpty(vector<bool>* v){
	    	v->push_back(false);
	}

}

/* MillGenTree.cxx */
