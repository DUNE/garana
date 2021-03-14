/*
 * FlatRecoTree.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/FlatRecoTree.h"

using namespace garana;

FlatRecoTree::FlatRecoTree(TTree* tree)
{
    SetupRead(tree);
}

FlatRecoTree::FlatRecoTree(TTree* tree, char opt)
{
	CheckOpt(opt);//sets TreeReader::fOpt

    if(fOpt=='r'){
    	std::cout << "constructed FlatRecoTree object in read-only mode" << std::endl;
    	SetupRead(tree);
    }
    else {
    	std::cout << "constructed FlatRecoTree object in write mode" << std::endl;
    	fTreeIn = tree;
    	SetBranchAddresses();
    }

}

/*void FlatRecoTree::GetEntry(UInt_t entry) {
	this->fRecoToFSLimits.clear();
	fTreeIn->GetEntry(entry);
    this->FindFSLimits();
}*/

bool FlatRecoTree::SetBranchAddresses(){

std::cout << "FlatRecoTree SetBranchAddresses()" << std::endl;

	if(fOpt=='r'){
		fTreeIn->SetBranchAddress("Event",             &fEvent,            &b_Event           );

	}


	if(fOpt=='w'){

		fTreeIn->Branch("Event",             &fEvent, "Event/I");

	}

	return true;
}

//implement accessors inherited from RecoTree

 void FlatRecoTree::SetVecs() {


 }

 void FlatRecoTree::ClearVecs() {



 }

 // sizes
 size_t FlatRecoTree::NTrack()      const {
	 return fTrkNHits->size();
 }

 size_t FlatRecoTree::NVertex()     const {
	 return fVtxX->size();
 }

 size_t FlatRecoTree::NVee()        const {
	 return fVeeVtxX->size();
 }

 size_t FlatRecoTree::NCalCluster() const {
	 return fCalClustX->size();
 }

 TLorentzVector FlatRecoTree::TrackVertex(size_t itrack) const {
	 TLorentzVector v(fTrkVtxX->at(itrack),
			          fTrkVtxY->at(itrack),
			          fTrkVtxZ->at(itrack),
			          fTrkVtxT->at(itrack)
			 );
	 return v;
 }

 TLorentzVector FlatRecoTree::TrackEnd(size_t itrack)    const {
	 TLorentzVector v(fTrkEndX->at(itrack),
			          fTrkEndY->at(itrack),
			          fTrkEndZ->at(itrack),
			          fTrkEndT->at(itrack)
			 );
	 return v;
 }

 size_t         FlatRecoTree::NTrackHit(size_t itrack)   const {
	 return fTrkNHits->at(itrack);
 }

 TVector3       FlatRecoTree::TrackMomBeg(size_t itrack) const {
	 TVector3 v(fTrkVtxDirX->at(itrack),
			    fTrkVtxDirX->at(itrack),
			    fTrkVtxDirX->at(itrack)
			  );
	 return v*fTrkMomBeg->at(itrack);

 }

 TVector3       FlatRecoTree::TrackMomEnd(size_t itrack) const {
	 TVector3 v(fTrkEndDirX->at(itrack),
			    fTrkEndDirX->at(itrack),
			    fTrkEndDirX->at(itrack)
			  );
	 return v*fTrkMomEnd->at(itrack);
 }


  //vertex
 TLorentzVector FlatRecoTree::GetVertex(size_t ivertex) const {

	 TLorentzVector v(fVtxX->at(ivertex),
	                  fVtxX->at(ivertex),
	                  fVtxX->at(ivertex),
	                  fVtxT->at(ivertex) );
	 return v;

 }

 void        FlatRecoTree::VertexCovariance(size_t ivertex, float covar[][3]) const {

	 covar[0][0] = fVtxCovar11->at(ivertex);
	 covar[0][1] = fVtxCovar12->at(ivertex);
	 covar[0][2] = fVtxCovar13->at(ivertex);
	 covar[1][0] = fVtxCovar21->at(ivertex);
	 covar[1][1] = fVtxCovar22->at(ivertex);
	 covar[1][2] = fVtxCovar23->at(ivertex);
	 covar[2][0] = fVtxCovar31->at(ivertex);
	 covar[2][1] = fVtxCovar32->at(ivertex);
	 covar[2][2] = fVtxCovar33->at(ivertex);

 }
