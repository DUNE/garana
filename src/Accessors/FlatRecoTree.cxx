/*
 * FlatRecoTree.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/FlatRecoTree.h"

using std::vector;
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

//TODO check if this is actually needed
/*void FlatRecoTree::GetEntry(UInt_t entry) {
	this->fRecoToFSLimits.clear();
	fTreeIn->GetEntry(entry);
    this->FindFSLimits();
}*/

//TODO impliment me
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

//TODO impliment me
 void FlatRecoTree::SetVecs() {


 }

 //TODO impliment me
 void FlatRecoTree::ClearVecs() {



 }

 // sizes
 const size_t FlatRecoTree::NTrack()      const {
	 return fTrkNHits->size();
 }

 const size_t FlatRecoTree::NVertex()     const {
	 return fVtxX->size();
 }

 const size_t FlatRecoTree::NVee()        const {
	 return fVeeVtxX->size();
 }

 const size_t FlatRecoTree::NCalCluster() const {
	 return fCalClustX->size();
 }

 const TLorentzVector* FlatRecoTree::TrackVertex(const size_t& itrack) const {
	 TLorentzVector* v = new TLorentzVector(fTrkVtxX->at(itrack),
			                                fTrkVtxY->at(itrack),
			                                fTrkVtxZ->at(itrack),
			                                fTrkVtxT->at(itrack) );
	 return v;
 }

 const TLorentzVector* FlatRecoTree::TrackEnd(const size_t& itrack)    const {
	 TLorentzVector* v = new TLorentzVector(fTrkEndX->at(itrack),
			                                fTrkEndY->at(itrack),
			                                fTrkEndZ->at(itrack),
			                                fTrkEndT->at(itrack) );
	 return v;
 }

 const size_t  FlatRecoTree::NTrackHit(const size_t& itrack)   const {
	 return fTrkNHits->at(itrack);
 }

 const TVector3* FlatRecoTree::TrackMomBeg(const size_t& itrack) const {
	 TVector3* v = new TVector3(fTrkVtxDirX->at(itrack),
			                    fTrkVtxDirX->at(itrack),
			                    fTrkVtxDirX->at(itrack) );
	 (*v) *= fTrkMomBeg->at(itrack);
	 return v; //*fTrkMomBeg->at(itrack);

 }

 const TVector3* FlatRecoTree::TrackMomEnd(const size_t& itrack) const {
	 TVector3* v = new TVector3(fTrkEndDirX->at(itrack),
			                    fTrkEndDirX->at(itrack),
			                    fTrkEndDirX->at(itrack) );
	 (*v) *= fTrkMomEnd->at(itrack);
	 return v;//*fTrkMomEnd->at(itrack);
 }

 const float FlatRecoTree::TrackLenFwd(const size_t& itrack) const {
 	return fTrkLenFwd->at(itrack);
 }

 const float FlatRecoTree::TrackLenBkd(const size_t& itrack) const {
 	return fTrkLenBac->at(itrack);
 }

 const float FlatRecoTree::TrackIonizFwd(const size_t& itrack) const {
 	return fTrkIonizFwd->at(itrack);
 }

 const float FlatRecoTree::TrackIonizBkd(const size_t& itrack) const {
 	return fTrkIonizBac->at(itrack);
 }

 const int FlatRecoTree::TrackChgFwd(const size_t& itrack) const {
 	return fTrkChgFwd->at(itrack);
 }

 const int FlatRecoTree::TrackChgBkd(const size_t& itrack) const {
	 return fTrkChgBac->at(itrack);
 }

 void FlatRecoTree::TrackParBeg(const size_t& itrack, float pars[5]) const {

 	pars[0] = fTrackXBeg   ->at(itrack);
 	pars[1] = fTrackYBeg   ->at(itrack);
 	pars[2] = fTrackZBeg   ->at(itrack);
 	pars[3] = fTrackCurvBeg->at(itrack);
 	pars[4] = fTrackPhiBeg ->at(itrack);
 	pars[5] = fTrackLambBeg->at(itrack);
 }

 void FlatRecoTree::TrackParEnd(const size_t& itrack, float pars[5]) const {
	pars[0] = fTrackXEnd   ->at(itrack);
	pars[1] = fTrackYEnd   ->at(itrack);
	pars[2] = fTrackZEnd   ->at(itrack);
	pars[3] = fTrackCurvEnd->at(itrack);
	pars[4] = fTrackPhiEnd ->at(itrack);
	pars[5] = fTrackLambEnd->at(itrack);
 }

 /// ================ vertex ==========================
 const TLorentzVector* FlatRecoTree::GetVertex(const size_t& ivertex) const {


     const TLorentzVector* v = new TLorentzVector(  fVtxX->at(ivertex),
	                                                fVtxY->at(ivertex),
	                                                fVtxZ->at(ivertex),
	                                                fVtxT->at(ivertex) );
	 return v;

 }

 void FlatRecoTree::VertexCovariance(const size_t& ivertex, float covar[][3]) const {

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

 /// =============== Vee =======================
 const TLorentzVector* FlatRecoTree::VeeVertex(const size_t& ivee) const {
 	return new TLorentzVector(fVeeVtxX->at(ivee), fVeeVtxY->at(ivee), fVeeVtxZ->at(ivee), fVeeVtxT->at(ivee)); } void FlatRecoTree::VeeCovariance(const size_t& ivee, float covar[][3]) const {
	 covar[0][0] = fVeeVtxCovar11->at(ivee);
	 covar[0][1] = fVeeVtxCovar12->at(ivee);
	 covar[0][2] = fVeeVtxCovar13->at(ivee);
	 covar[1][0] = fVeeVtxCovar21->at(ivee);
	 covar[1][1] = fVeeVtxCovar22->at(ivee);
	 covar[1][2] = fVeeVtxCovar23->at(ivee);
	 covar[2][0] = fVeeVtxCovar31->at(ivee);
	 covar[2][1] = fVeeVtxCovar32->at(ivee);
	 covar[2][2] = fVeeVtxCovar33->at(ivee); } const vector<TLorentzVector>* FlatRecoTree::VeeMomentumPerHypothesis(const size_t& ivee) const {

	vector<TLorentzVector>* v = new vector<TLorentzVector>();
	v->push_back(TLorentzVector(fVeePxKshort->at(ivee),fVeePyKshort->at(ivee),
			fVeePzKshort->at(ivee),fVeeEKshort->at(ivee)));
	v->push_back(TLorentzVector(fVeePxLamb1->at(ivee),fVeePyLamb1->at(ivee),
			fVeePzLamb1->at(ivee),fVeeELamb1->at(ivee)));
	v->push_back(TLorentzVector(fVeePxLamb2->at(ivee),fVeePyLamb2->at(ivee),
			fVeePzLamb2->at(ivee),fVeeELamb2->at(ivee)));
 	return v; } const float FlatRecoTree::VeeChiSquared(const size_t& ivee) const { 	return fVeeChisqr->at(ivee); } /// ================ ECal cluster ====================== const TLorentzVector*   FlatRecoTree::CalClustPosition(const size_t& icluster) const { 	return new TLorentzVector(fCalClustX->at(icluster),fCalClustY->at(icluster),
 			            fCalClustZ->at(icluster),fCalClustT->at(icluster)); } const float  FlatRecoTree::CalClustEnergy(const size_t& icluster) const { 	return fCalClustEnergy->at(icluster); } const float  FlatRecoTree::CalClustEnergyError(const size_t& icluster) const { 	return fCalClustEnergyError->at(icluster); } const float  FlatRecoTree::CalClustTimeDifference(const size_t& icluster) const { 	return fCalClustTdiff->at(icluster); } const float* FlatRecoTree::CalClustShape(const size_t& icluster) const {

	float* shape = new float[6];
	shape[0] = fCalClustEllip->at(icluster);
	shape[1] = fCalClustR1->at(icluster);
	shape[2] = fCalClustR2->at(icluster);
	shape[3] = fCalClustR3->at(icluster);
	shape[4] = fCalClustVol->at(icluster);
	shape[5] = fCalClustWidth->at(icluster);
 	return shape; } const float  FlatRecoTree::CalClustTheta(const size_t& icluster) const { 	return fCalClustTheta->at(icluster); } const float  FlatRecoTree::CalClustPhi(const size_t& icluster) const { 	return fCalClustPhi->at(icluster); } const vector<TVector3>* FlatRecoTree::CalClustEigenVecs(const size_t& icluster) const{

	vector<TVector3>* v = new vector<TVector3>();
	v->push_back(TVector3(fCalClustEigen1X->at(icluster),fCalClustEigen1Y->at(icluster),fCalClustEigen1Z->at(icluster)));
	v->push_back(TVector3(fCalClustEigen2X->at(icluster),fCalClustEigen2Y->at(icluster),fCalClustEigen2Z->at(icluster)));
	v->push_back(TVector3(fCalClustEigen3X->at(icluster),fCalClustEigen3Y->at(icluster),fCalClustEigen3Z->at(icluster)));
 	return v; }
