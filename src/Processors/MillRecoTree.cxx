/*
 * MillRecoTree.cxx
 *
 *  Created on: Feb 13, 2021
 *      Author: chilgenb
 */

#include "garana/Processors/MillRecoTree.h"

#include <TTree.h>

#include <map>
#include <iostream>

using std::vector;

using namespace garana;


MillRecoTree::MillRecoTree(TTree* treeIn, TTree* treeOut)
{
    fRecoIn = new StructuredRecoTree(treeIn);
    fTreeIn = treeOut;
    fOpt='w';
	this->VerifyBranches();
	this->SetVecs();
	this->SetBranchAddresses();
	this->MillTrees();

}//constructor()

//Fill branches but do not fill
void MillRecoTree::MillTrees() {

    if(!IsVerified()){
    	std::cerr << "WARNING(MillRecoTree::MillTrees): "
    			  << "trying to mill trees that have not been verified"
    			  << std::endl;
    	return;
    }

    std::cout << "MillRecoTree: loop over " << fRecoIn->NEntries() << " gen entries" << std::endl;

    //loop over input genTree events (entries)
    for(size_t ientry=0; ientry<fRecoIn->NEntries(); ientry++){

    	ClearVecs(); //clear previous entry's data (if any)
    	fRecoIn->GetEntry(ientry);

    	if(branchToDrawOpt[kTracks]) {
    		fEvent = fRecoIn->Event();
    	}

		if(branchToDrawOpt[kTracks]) {
			FillTrack();
		}

		if(branchToDrawOpt[kVertices]) {
			FillVertex();
		}

		if(branchToDrawOpt[kVees]) {
			FillVee();
		}

		if(branchToDrawOpt[kCalClusters]) {
			FillCaloCluster();
		}

    	fTreeIn->Fill(); //actually our fTreeOut, but it's called fTreeIn in FlatRecoTree.h, fill once per event
    }//for genTree entries

    fTreeIn->Write();

}//Mill()

bool MillRecoTree::VerifyBranches() {

    // get list of branches and check it matches what we expect
    const TObjArray* branches = fRecoIn->GetBranchList();
    std::cout << "got ObjArray of branches from fTreeIn" << std::endl;
    try {
    	if(!branches || branches->GetEntries()==0 )
    		throw branches;
    }
    catch(TObjArray* branches){
    	std::cerr << "ERROR(MillRecoTree::VerifyBranches): no branches found in passed input tree"
    			  << std::endl;
    	return false;
    }

    if(branches->GetEntriesFast() != (Int_t)nameToRecoBranch.size())
    	std::cout << "WARNING(MillRecoTree::VerifyBranches): Mismatch in number of branches (expected "
    	          << nameToRecoBranch.size() << " but found " << branches->GetEntriesFast()
    	          << ")" << std::endl;
    else
    	std::cout << "found genTree with " << branches->GetEntriesFast() << " branches" << std::endl;

    // loop over branches
    TIter next(branches);
    TBranch* branch = nullptr;
    while( (branch=(TBranch*)next())) {

    	// check if branch is expected
    	if(nameToRecoBranch.find(CharStarToString(branch->GetFullName()))!=nameToRecoBranch.end()) {

    		std::cout << "   chopping branch '" << branch->GetFullName() << "'" << std::endl;

    		if(nameToRecoBranch[CharStarToString(branch->GetFullName())] == kEvent)
    			branchToDrawOpt[kEvent] = true;

    		if(nameToRecoBranch[CharStarToString(branch->GetFullName())] == kTracks)
    			branchToDrawOpt[kTracks] = true;

    		if(nameToRecoBranch[CharStarToString(branch->GetFullName())] == kVertices)
    			branchToDrawOpt[kVertices] = true;

    		if(nameToRecoBranch[CharStarToString(branch->GetFullName())] == kVees)
    			branchToDrawOpt[kVees] = true;

    		if(nameToRecoBranch[CharStarToString(branch->GetFullName())] == kCalClusters)
    			branchToDrawOpt[kCalClusters] = true;

    	}//endif known branch

    	else{
    		std::cout << "WARNING(MillRecoTree): ignoring unknown branch '"
    				  << branch->GetFullName() << "'" << std::endl;
    	}//else

    }//for branches

    fIsVerified = true;
    return true;

}//VerifyBranches()


void MillRecoTree::FillTrack() {
	for(size_t itrk=0; itrk<fRecoIn->NTrack(); itrk++){

		fTrkLenFwd      ->push_back(fRecoIn->TrackLenFwd(itrk));
		fTrkLenBac      ->push_back(fRecoIn->TrackLenBkd(itrk));
		fTrkMomBeg      ->push_back(fRecoIn->TrackMomBeg(itrk)->Mag());
		fTrkMomEnd      ->push_back(fRecoIn->TrackMomEnd(itrk)->Mag());

		fTrkVtxX        ->push_back(fRecoIn->TrackVertex(itrk)->X());
		fTrkVtxY        ->push_back(fRecoIn->TrackVertex(itrk)->Y());
		fTrkVtxZ        ->push_back(fRecoIn->TrackVertex(itrk)->Z());
		fTrkVtxT        ->push_back(fRecoIn->TrackVertex(itrk)->T());
		fTrkEndX        ->push_back(fRecoIn->TrackEnd(itrk)->X());
		fTrkEndY        ->push_back(fRecoIn->TrackEnd(itrk)->Y());
		fTrkEndZ        ->push_back(fRecoIn->TrackEnd(itrk)->Z());
		fTrkEndT        ->push_back(fRecoIn->TrackEnd(itrk)->T());

		fTrkVtxDirX     ->push_back(fRecoIn->TrackVtxDirectionX(itrk));
		fTrkVtxDirY     ->push_back(fRecoIn->TrackVtxDirectionY(itrk));
		fTrkVtxDirZ     ->push_back(fRecoIn->TrackVtxDirectionZ(itrk));
		fTrkEndDirX     ->push_back(fRecoIn->TrackEndDirectionX(itrk));
		fTrkEndDirY     ->push_back(fRecoIn->TrackEndDirectionY(itrk));
		fTrkEndDirZ     ->push_back(fRecoIn->TrackEndDirectionZ(itrk));

		fTrkChiFwd      ->push_back(fRecoIn->TrackChiSqrFwd(itrk) );
		fTrkChiBac      ->push_back(fRecoIn->TrackChiSqrBkd(itrk));
		fTrkNHits       ->push_back(fRecoIn->NTrackHit(itrk));

		float trackpars[5], trackcovar[15];
		fRecoIn->TrackParBeg(itrk,trackpars);

		fTrackXBeg   ->push_back(fRecoIn->TrackVertex(itrk)->X());
		fTrackYBeg   ->push_back(trackpars[0]);
		fTrackZBeg   ->push_back(trackpars[1]);
		fTrackCurvBeg->push_back(trackpars[2]);
		fTrackPhiBeg ->push_back(trackpars[3]);
		fTrackLambBeg->push_back(trackpars[4]);

		fRecoIn->TrackParEnd(itrk,trackpars);
		fTrackXEnd      ->push_back(fRecoIn->TrackEnd(itrk)->X());
		fTrackYEnd      ->push_back(trackpars[0]);
		fTrackZEnd      ->push_back(trackpars[1]);
		fTrackCurvEnd   ->push_back(trackpars[2]);
		fTrackPhiEnd    ->push_back(trackpars[3]);
		fTrackLambEnd   ->push_back(trackpars[4]);

		fRecoIn->TrackCovarBeg(itrk,trackcovar);
		fTrkCovMat1Beg ->push_back(trackcovar[0]);
		fTrkCovMat2Beg ->push_back(trackcovar[1]);
		fTrkCovMat3Beg ->push_back(trackcovar[2]);
		fTrkCovMat4Beg ->push_back(trackcovar[3]);
		fTrkCovMat5Beg ->push_back(trackcovar[4]);
		fTrkCovMat6Beg ->push_back(trackcovar[5]);
		fTrkCovMat7Beg ->push_back(trackcovar[6]);
		fTrkCovMat8Beg ->push_back(trackcovar[7]);
		fTrkCovMat9Beg ->push_back(trackcovar[8]);
		fTrkCovMat10Beg->push_back(trackcovar[9]);
		fTrkCovMat11Beg->push_back(trackcovar[10]);
		fTrkCovMat12Beg->push_back(trackcovar[11]);
		fTrkCovMat13Beg->push_back(trackcovar[12]);
		fTrkCovMat14Beg->push_back(trackcovar[13]);
		fTrkCovMat15Beg->push_back(trackcovar[14]);

		fRecoIn->TrackCovarEnd(itrk,trackcovar);
		fTrkCovMat1End ->push_back(trackcovar[0]);
		fTrkCovMat2End ->push_back(trackcovar[1]);
		fTrkCovMat3End ->push_back(trackcovar[2]);
		fTrkCovMat4End ->push_back(trackcovar[3]);
		fTrkCovMat5End ->push_back(trackcovar[4]);
		fTrkCovMat6End ->push_back(trackcovar[5]);
		fTrkCovMat7End ->push_back(trackcovar[6]);
		fTrkCovMat8End ->push_back(trackcovar[7]);
		fTrkCovMat9End ->push_back(trackcovar[8]);
		fTrkCovMat10End->push_back(trackcovar[9]);
		fTrkCovMat11End->push_back(trackcovar[10]);
		fTrkCovMat12End->push_back(trackcovar[11]);
		fTrkCovMat13End->push_back(trackcovar[12]);
		fTrkCovMat14End->push_back(trackcovar[13]);
		fTrkCovMat15End->push_back(trackcovar[14]);

		fTrkIonizFwd->push_back(fRecoIn->TrackIonizFwd(itrk));
		fTrkIonizBac->push_back(fRecoIn->TrackIonizBkd(itrk));
		fTrkChgFwd->push_back(fRecoIn->TrackChgFwd(itrk));
		fTrkChgBac->push_back(fRecoIn->TrackChgBkd(itrk));

		//FixMe fill associations
		//fRecoIn->GetTrackG4PIndices(itrk,fTrackG4PIndices);

	}//for track entries
}

void MillRecoTree::FillVertex() {

	for(size_t ivtx=0; ivtx<fRecoIn->NVertex(); ivtx++) {
		fVtxX->push_back(fRecoIn->GetVertex(ivtx)->X());
		fVtxY->push_back(fRecoIn->GetVertex(ivtx)->Y());
		fVtxZ->push_back(fRecoIn->GetVertex(ivtx)->Z());
		fVtxT->push_back(fRecoIn->GetVertex(ivtx)->T());

		float covar[3][3];
		fRecoIn->VertexCovariance(ivtx,covar);
		fVtxCovar11->push_back(covar[0][0]);
		fVtxCovar12->push_back(covar[0][1]);
		fVtxCovar13->push_back(covar[0][2]);
		fVtxCovar21->push_back(covar[1][0]);
		fVtxCovar22->push_back(covar[1][1]);
		fVtxCovar23->push_back(covar[1][2]);
		fVtxCovar31->push_back(covar[2][0]);
		fVtxCovar32->push_back(covar[2][1]);
		fVtxCovar33->push_back(covar[2][2]);
	}
}

void MillRecoTree::FillVee() {

	for(size_t ivee=0; ivee<fRecoIn->NVee(); ivee++){

		fVeeVtxX->push_back(fRecoIn->VeeVertex(ivee)->X());
		fVeeVtxY->push_back(fRecoIn->VeeVertex(ivee)->Y());
		fVeeVtxZ->push_back(fRecoIn->VeeVertex(ivee)->Z());
		fVeeVtxT->push_back(fRecoIn->VeeVertex(ivee)->T());
		fVeeChisqr->push_back(fRecoIn->VeeChiSquared(ivee));

		float covar[3][3];
		fRecoIn->VeeCovariance(ivee,covar);
		fVeeVtxCovar11->push_back(covar[0][0]);
		fVeeVtxCovar12->push_back(covar[0][1]);
		fVeeVtxCovar13->push_back(covar[0][2]);
		fVeeVtxCovar21->push_back(covar[1][0]);
		fVeeVtxCovar22->push_back(covar[1][1]);
		fVeeVtxCovar23->push_back(covar[1][2]);
		fVeeVtxCovar31->push_back(covar[2][0]);
		fVeeVtxCovar32->push_back(covar[2][1]);
		fVeeVtxCovar33->push_back(covar[2][2]);

		fVeePxKshort->push_back(fRecoIn->VeeMomentumPerHypothesis(ivee)->at(0).Px());
		fVeePyKshort->push_back(fRecoIn->VeeMomentumPerHypothesis(ivee)->at(0).Py());
		fVeePzKshort->push_back(fRecoIn->VeeMomentumPerHypothesis(ivee)->at(0).Pz());
		fVeeEKshort ->push_back(fRecoIn->VeeMomentumPerHypothesis(ivee)->at(0).E());

		fVeePxLamb1 ->push_back(fRecoIn->VeeMomentumPerHypothesis(ivee)->at(1).Px());
		fVeePyLamb1 ->push_back(fRecoIn->VeeMomentumPerHypothesis(ivee)->at(1).Py());
		fVeePzLamb1 ->push_back(fRecoIn->VeeMomentumPerHypothesis(ivee)->at(1).Pz());
		fVeeELamb1  ->push_back(fRecoIn->VeeMomentumPerHypothesis(ivee)->at(1).E());

		fVeePxLamb2 ->push_back(fRecoIn->VeeMomentumPerHypothesis(ivee)->at(2).Px());
		fVeePyLamb2 ->push_back(fRecoIn->VeeMomentumPerHypothesis(ivee)->at(2).Py());
		fVeePzLamb2 ->push_back(fRecoIn->VeeMomentumPerHypothesis(ivee)->at(2).Pz());
		fVeeELamb2  ->push_back(fRecoIn->VeeMomentumPerHypothesis(ivee)->at(2).E());

	}
}

void MillRecoTree::FillCaloCluster() {

	for(size_t iclust=0; iclust<fRecoIn->NCalCluster(); iclust++){
		fCalClustX->push_back(fRecoIn->CalClustPosition(iclust)->X());
		fCalClustY->push_back(fRecoIn->CalClustPosition(iclust)->Y());
		fCalClustZ->push_back(fRecoIn->CalClustPosition(iclust)->Z());
		fCalClustT->push_back(fRecoIn->CalClustPosition(iclust)->T());
		fCalClustEnergy->push_back(fRecoIn->CalClustEnergy(iclust));
		fCalClustEnergyError->push_back(fRecoIn->CalClustEnergyError(iclust));
		fCalClustTdiff->push_back(fRecoIn->CalClustTimeDifference(iclust));
		fCalClustEllip->push_back(fRecoIn->CalClustShape(iclust)[0]);
		fCalClustR1->push_back(fRecoIn->CalClustShape(iclust)[1]);
		fCalClustR2->push_back(fRecoIn->CalClustShape(iclust)[2]);
		fCalClustR3->push_back(fRecoIn->CalClustShape(iclust)[3]);
		fCalClustVol->push_back(fRecoIn->CalClustShape(iclust)[4]);
		fCalClustWidth->push_back(fRecoIn->CalClustShape(iclust)[5]);
		fCalClustTheta->push_back(fRecoIn->CalClustTheta(iclust));
		fCalClustPhi->push_back(fRecoIn->CalClustPhi(iclust));
		fCalClustEigen1X->push_back(fRecoIn->CalClustEigenVecs(iclust)->at(0).X());
		fCalClustEigen1Y->push_back(fRecoIn->CalClustEigenVecs(iclust)->at(0).Y());
		fCalClustEigen1Z->push_back(fRecoIn->CalClustEigenVecs(iclust)->at(0).Z());
		fCalClustEigen2X->push_back(fRecoIn->CalClustEigenVecs(iclust)->at(1).X());
		fCalClustEigen2Y->push_back(fRecoIn->CalClustEigenVecs(iclust)->at(1).Y());
		fCalClustEigen2Z->push_back(fRecoIn->CalClustEigenVecs(iclust)->at(1).Z());
		fCalClustEigen3X->push_back(fRecoIn->CalClustEigenVecs(iclust)->at(2).X());
		fCalClustEigen3Y->push_back(fRecoIn->CalClustEigenVecs(iclust)->at(2).Y());
		fCalClustEigen3Z->push_back(fRecoIn->CalClustEigenVecs(iclust)->at(2).Z());
	}
}



/* MillRecoTree.cxx */
