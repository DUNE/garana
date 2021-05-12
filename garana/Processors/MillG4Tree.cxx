/*
 * MillG4Tree.cxx
 *
 *  Created on: Feb 13, 2021
 *      Author: chilgenb
 */

//#include "include/garana/Accessors/StructuredG4Tree.h"
#include "garana/Processors/MillG4Tree.h"

#include <TTree.h>

#include <map>
#include <iostream>

using std::vector;

using namespace garana;

MillG4Tree::MillG4Tree(TTree* treeIn, TTree* treeOut)
{
    fG4In = new StructuredG4Tree(treeIn);

    fTreeIn = treeOut;
    fOpt='w';
	this->VerifyBranches();
	this->SetVecs();
	this->SetBranchAddresses();
	this->MillTrees();

}//constructor()

//Fill branches but do not fill
void MillG4Tree::MillTrees() {

    if(!IsVerified()){
    	std::cerr << "WARNING(MillG4Tree::MillTrees): "
    			  << "trying to mill trees that have not been verified"
    			  << std::endl;
    	return;
    }

    std::cout << "MillG4Tree: loop over " << fG4In->NEntries() << " gen entries" << std::endl;

    //loop over input g4Tree events (entries)
    for(size_t ientry=0; ientry<fG4In->NEntries(); ientry++){

    	ClearVecs(); //clear previous entry's data (if any)
    	fG4In->GetEntry(ientry);

    	if(branchToDrawOpt[kEvent]) {
    		fEvent = fG4In->Event();
    	}

    	if(branchToDrawOpt[kG4Particles]) {
    	    fNSim = fG4In->NSim();
			std::cout << "MillG4: output NG4 = " << fNSim << std::endl;

			//loop over g4 entries
	    	std::cout << "MillG4Tree: loop over " << fG4In->NSim() << " isim" <<std::endl;
			for(size_t isim=0; isim<fG4In->NSim(); isim++){

				auto posenter = fG4In->SimPosEnter(isim); // 4-position for particle at entry, all regions
				auto momenter = fG4In->SimMomEnter(isim); // 4-momentum for particle at entry, all regions
				auto posexit  = fG4In->SimPosExit(isim); // 4-position for particle at exit/end, all regions
				auto momexit = fG4In->SimMomExit(isim); // 4-momentum for particle at exit, all regions

				for(size_t ireg=0; ireg<fG4In->NRegions(isim); ireg++){
					for(size_t i=0; i<2; i++){
						fNPts              ->push_back(fG4In->NPoints(isim));
						fTrkID             ->push_back(fG4In->TrackID(isim));
						fPDG               ->push_back(fG4In->PDG(isim));
						fParentPdg         ->push_back(fG4In->ParentPDG(isim));
						fProgenitorPdg     ->push_back(fG4In->ProgenitorPDG(isim));
						fParentTrackId     ->push_back(fG4In->ParentTrackID(isim));
						fProgenitorTrackId ->push_back(fG4In->ProgenitorTrackID(isim));
						fProcessI          ->push_back(fG4In->ProcessI(isim));
						fProcessF          ->push_back(fG4In->ProcessF(isim));
						if(i==0) {
							fX                 ->push_back(posenter->at(ireg)->X());
							fY                 ->push_back(posenter->at(ireg)->Y());
							fZ                 ->push_back(posenter->at(ireg)->Z());
							fT                 ->push_back(posenter->at(ireg)->T());
							fPx                ->push_back(momenter->at(ireg)->Px());
							fPy                ->push_back(momenter->at(ireg)->Py());
							fPz                ->push_back(momenter->at(ireg)->Pz());
							fE                 ->push_back(momenter->at(ireg)->E());
						}
						else {
							fX                 ->push_back(posexit->at(ireg)->X());
							fY                 ->push_back(posexit->at(ireg)->Y());
							fZ                 ->push_back(posexit->at(ireg)->Z());
							fT                 ->push_back(posexit->at(ireg)->T());
							fPx                ->push_back(momexit->at(ireg)->Px());
							fPy                ->push_back(momexit->at(ireg)->Py());
							fPz                ->push_back(momexit->at(ireg)->Pz());
							fE                 ->push_back(momexit->at(ireg)->E());
						}
					}
				}// for regions

			    if(branchToDrawOpt[kG4TruthIndex]) {
			    	fG4TruthIndex->push_back(fG4In->GetTruthIndex(isim));
			    }

    	    }//for g4 entries
		}//if branch present

    	fTreeIn->Fill(); //actually our fTreeOut, but it's called fTreeIn in FlatG4Tree.h, fill once per event

    }//for genTree entries

    fTreeIn->Write();

}//Mill()

bool MillG4Tree::VerifyBranches() {

    // get list of branches and check it matches what we expect
    const TObjArray* branches = fG4In->GetBranchList();
    std::cout << "got ObjArray of branches from fTreeIn" << std::endl;
    try {
    	if(!branches || branches->GetEntries()==0 )
    		throw branches;
    }
    catch(TObjArray* branches){
    	std::cerr << "ERROR(MillG4Tree::VerifyBranches): no branches found in passed input tree"
    			  << std::endl;
    	return false;
    }

    if(branches->GetEntriesFast() != (Int_t)nameToG4Branch.size())
    	std::cout << "WARNING(MillG4Tree::VerifyBranches): Mismatch in number of branches (expected "
    	          << nameToG4Branch.size() << " but found " << branches->GetEntriesFast()
    	          << ")" << std::endl;
    else
    	std::cout << "found genTree with " << branches->GetEntriesFast() << " branches" << std::endl;

    // loop over branches
    TIter next(branches);
    TBranch* branch = nullptr;
    while( (branch=(TBranch*)next())) {

    	// check if branch is expected
    	if(nameToG4Branch.find(CharStarToString(branch->GetFullName()))!=nameToG4Branch.end()) {

    		std::cout << "   chopping branch '" << branch->GetFullName() << "'" << std::endl;

    		if(nameToG4Branch[CharStarToString(branch->GetFullName())] == kEvent)
    			branchToDrawOpt[kEvent] = true;

    		if(nameToG4Branch[CharStarToString(branch->GetFullName())] == kG4Particles)
        		branchToDrawOpt[kG4Particles] = true;

    		if(nameToG4Branch[CharStarToString(branch->GetFullName())] == kG4TruthIndex)
        		branchToDrawOpt[kG4TruthIndex] = true;

    	}//endif known branch

    	else{
    		std::cout << "WARNING(MillG4Tree): ignoring unknown branch '"
    				  << branch->GetFullName() << "'" << std::endl;
    	}//else

    }//for branches

    fIsVerified = true;
    return true;

}//VerifyBranches()


/* MillG4Tree.cxx */
