/*
 * StructuredRecoTree.cxx
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/StructuredRecoTree.h"

using std::vector;
using namespace garana;

StructuredRecoTree::StructuredRecoTree(TTree* tree) {
	SetupRead(tree); //initialize tree pointer in TreeReader instance and set branch addresses
}

bool StructuredRecoTree::SetBranchAddresses() {

    fTreeIn->SetBranchAddress("Event",            &fEvent,                   &b_Event                  );
    fTreeIn->SetBranchAddress("Tracks",           &fTracks          ,        &b_Tracks                 );
    fTreeIn->SetBranchAddress("Vees",             &fVees            ,        &b_Vees                   );
    fTreeIn->SetBranchAddress("Vertices",         &fVertices        ,        &b_Vertices               );
    fTreeIn->SetBranchAddress("CalClusters",      &fCalClusters     ,        &b_CalClusters            );
    fTreeIn->SetBranchAddress("TrackG4Indices",   &fTrackG4PIndices ,        &b_TrackG4PIndices        );
    fTreeIn->SetBranchAddress("VertTrackIndices", &fVertTrackIndices,        &b_VertTrackIndices       );
    fTreeIn->SetBranchAddress("VertTrackEnds",    &fVertTrackEnds   ,        &b_VertTrackEnds          );
    fTreeIn->SetBranchAddress("VeeTrackIndices",  &fVeeTrackIndices ,        &b_VeeTrackIndices        );
    fTreeIn->SetBranchAddress("VeeTrackEnds",     &fVeeTrackEnds    ,        &b_VeeTrackEnds           );
    fTreeIn->SetBranchAddress("CalTrackIndices",  &fCalClusterTrackIndices , &b_CalClusterTrackIndices );
    //fTreeIn->SetBranchAddress("CalTrackEnds",     &fCalTrackEnds    , &b_CalTrackEnds    );
    fTreeIn->SetBranchAddress("CalG4Indices",     &fCalClusterG4Indices ,    &b_CalClusterG4Indices    );
    /*if(fGeo->HasMuonDetector()){
            fTreeIn->SetBranchAddress("MuIDClusters", "vector<gar::rec::Cluster>",   &fMuClusters);
    }*/

    //TODO: add Assns for reco r&d products
    /*if(fAnaMode == "reco"){
        fRecoTree->Branch("TPCHits",       "vector<gar::rec::Hit>",        &fTPCHits);
        fRecoTree->Branch("TPCClusters",   "vector<gar::rec::TPCCluster>", &fTPCClusters);
        fRecoTree->Branch("CalHits",       "vector<gar::rec::CaloHit>",    &fCalHits);
        if(fGeo->HasMuonDetector()){
            fRecoTree->Branch("MuIDHits",       "vector<gar::rec::CaloHit>", &fMuHits);
        }
    }*/


    return true;
}// end const'or

////============ sizes ============================
const size_t StructuredRecoTree::NTrack()      const {
	return fTracks->size();
}
const size_t StructuredRecoTree::NVertex()     const {
	return fVertices->size();
}
const size_t StructuredRecoTree::NVee()        const {
	return fVees->size();
}
const size_t StructuredRecoTree::NCalCluster() const {
	return fCalClusters->size();
}

////======================== track ===================================
const TLorentzVector* StructuredRecoTree::TrackVertex(const size_t& itrack) const {
	return &(fTracks->at(itrack).fVtx);
}

const TLorentzVector* StructuredRecoTree::TrackEnd(const size_t& itrack) const {
	return &(fTracks->at(itrack).fEnd);
}
const size_t StructuredRecoTree::NTrackHit(const size_t& itrack) const {
	return fTracks->at(itrack).fNHits;
}
const TVector3* StructuredRecoTree::TrackMomBeg(const size_t& itrack) const {
	TVector3* v = new TVector3(fTracks->at(itrack).fVtxDir);
	(*v) *= fTracks->at(itrack).fMomBeg;
    return v;
}

const TVector3* StructuredRecoTree::TrackMomEnd(const size_t& itrack) const {
	TVector3* v = new TVector3(fTracks->at(itrack).fEndDir);
	(*v) *= fTracks->at(itrack).fMomEnd;
    return v;
}

const float StructuredRecoTree::TrackVtxDirectionX(const size_t& itrack) const {
	return fTracks->at(itrack).fVtxDir.X();
}

const float StructuredRecoTree::TrackVtxDirectionY(const size_t& itrack) const {
	return fTracks->at(itrack).fVtxDir.Y();
}

const float StructuredRecoTree::TrackVtxDirectionZ(const size_t& itrack) const {
	return fTracks->at(itrack).fVtxDir.Z();
}

const float StructuredRecoTree::TrackEndDirectionX(const size_t& itrack) const {
	return fTracks->at(itrack).fEndDir.X();
}

const float StructuredRecoTree::TrackEndDirectionY(const size_t& itrack) const {
	return fTracks->at(itrack).fEndDir.Y();
}

const float StructuredRecoTree::TrackEndDirectionZ(const size_t& itrack) const {
	return fTracks->at(itrack).fEndDir.Z();
}

const float StructuredRecoTree::TrackLenFwd(const size_t& itrack) const {
	return fTracks->at(itrack).fLenFwd;
}

const float StructuredRecoTree::TrackLenBkd(const size_t& itrack) const {
	return fTracks->at(itrack).fLenBac;
}

const float StructuredRecoTree::TrackIonizFwd(const size_t& itrack) const {
	return fTracks->at(itrack).fIonFwd;
}

const float StructuredRecoTree::TrackIonizBkd(const size_t& itrack) const {
	return fTracks->at(itrack).fLenBac;
}

const int StructuredRecoTree::TrackChiSqrFwd(const size_t& itrack) const {
	return fTracks->at(itrack).fChiFwd;
}

const int StructuredRecoTree::TrackChiSqrBkd(const size_t& itrack) const {
	return fTracks->at(itrack).fChiBac;
}

const int StructuredRecoTree::TrackChgFwd(const size_t& itrack) const {
	return fTracks->at(itrack).fChgFwd;
}

const int StructuredRecoTree::TrackChgBkd(const size_t& itrack) const {
	return fTracks->at(itrack).fChgBac;
}

void StructuredRecoTree::TrackParBeg(const size_t& itrack, float pars[5]) const {
	for(size_t i=0; i<5; i++)
		pars[i] = fTracks->at(itrack).fTrackParBeg[i];
}

void StructuredRecoTree::TrackParEnd(const size_t& itrack, float pars[5]) const {
	for(size_t i=0; i<5; i++)
		pars[i] = fTracks->at(itrack).fTrackParEnd[i];
}

void StructuredRecoTree::TrackCovarBeg(const size_t& itrack, float covar[15]) const {
	for(size_t i=0; i<15; i++)
		covar[i] = fTracks->at(itrack).fCovMatBeg[i];
}

void StructuredRecoTree::TrackCovarEnd(const size_t& itrack, float covar[15]) const {
	for(size_t i=0; i<15; i++)
		covar[i] = fTracks->at(itrack).fCovMatEnd[i];
}

const TLorentzVector* StructuredRecoTree::TrackTruePosBeg(const size_t& itrack) const {
	TLorentzVector outvec(0,0,0,0);
	float ptot = 0.;
	for(size_t imctrk=0; imctrk<fTracks->at(itrack).fTruePosVtx.size(); imctrk++ ) {
		TLorentzVector tmpvec = fTracks->at(itrack).fTruePosVtx[imctrk].second;
		tmpvec *= fTracks->at(itrack).fTrueMomVtx[imctrk].second.P();
		outvec += tmpvec;
		ptot += fTracks->at(itrack).fTrueMomVtx[imctrk].second.P();
	}

	outvec *= 1.0/ptot;
	return new TLorentzVector(outvec);
}

const TLorentzVector* StructuredRecoTree::TrackTruePosEnd(const size_t& itrack) const {
	TLorentzVector outvec(0,0,0,0);
	float ptot = 0.;
	std::cout << "loop over -- " << fTracks->at(itrack).fTruePosEnd.size() << " -- true positions" << std::endl;
	for(size_t imctrk=0; imctrk<fTracks->at(itrack).fTruePosEnd.size(); imctrk++) {
		TLorentzVector tmpvec = fTracks->at(itrack).fTruePosEnd[imctrk].second;
		std::cout << "  submomentum: " << fTracks->at(itrack).fTrueMomEnd[imctrk].second.P() << std::endl;
		tmpvec *= fTracks->at(itrack).fTrueMomEnd[imctrk].second.P();
		outvec += tmpvec;
		ptot += fTracks->at(itrack).fTrueMomEnd[imctrk].second.P();
	}
    std::cout << "total true momentum: " << std::to_string(ptot) << std::endl;
	outvec *= 1.0/ptot;
	return new TLorentzVector(outvec);
}

const TLorentzVector* StructuredRecoTree::TrackTrueMomBeg(const size_t& itrack) const {
	TLorentzVector outvec(0,0,0,0);
	float ptot = 0.;
	for(size_t imctrk=0; imctrk<fTracks->at(itrack).fTrueMomVtx.size(); imctrk++) {
		TLorentzVector tmpvec = fTracks->at(itrack).fTrueMomVtx[imctrk].second;
		tmpvec *= fTracks->at(itrack).fTrueMomVtx[imctrk].second.P();
		outvec += tmpvec;
		ptot += fTracks->at(itrack).fTrueMomVtx[imctrk].second.P();
	}

	outvec *= 1.0/ptot;
	return new TLorentzVector(outvec);
}

const TLorentzVector* StructuredRecoTree::TrackTrueMomEnd(const size_t& itrack) const {
	TLorentzVector outvec(0,0,0,0);
	float ptot = 0.;
	for(size_t imctrk=0; imctrk<fTracks->at(itrack).fTrueMomEnd.size(); imctrk++) {
		TLorentzVector tmpvec = fTracks->at(itrack).fTrueMomEnd[imctrk].second;
		tmpvec *= fTracks->at(itrack).fTrueMomEnd[imctrk].second.P();
		outvec += tmpvec;
		ptot += fTracks->at(itrack).fTrueMomEnd[imctrk].second.P();
	}

	outvec *= 1.0/ptot;
	return new TLorentzVector(outvec);
}

const float  StructuredRecoTree::TrackTrueEnergy(const size_t& itrack) const {
	return FLT_MAX-itrack*0;
}

const size_t StructuredRecoTree::TrackNTrueTrack(const size_t& itrack)     const {
	return fTracks->at(itrack).fTrueEnergy.size();
}

const int    StructuredRecoTree::TrackTrkIdMaxDeposit(const size_t& itrack) const {
	int imax=-1;
	float emax = -1.;
	for(size_t i=0; i<fTracks->at(itrack).fTrueEnergy.size(); i++) {

		if(fTracks->at(itrack).fTrueEnergy.at(i).second > emax){
			emax = fTracks->at(itrack).fTrueEnergy.at(i).second;
			imax = i;
		}
	}

	return fTracks->at(itrack).fTrueEnergy.at(imax).first;
}

const float  StructuredRecoTree::TrackMaxDeposit(const size_t& itrack)     const {
	return fTracks->at(itrack).fTrueEnergy.at(TrackTrkIdMaxDeposit(itrack)).second;
}

const std::pair<int,float>* StructuredRecoTree::TrackTrueDeposit(const size_t& itrack) const {
	int id = TrackTrkIdMaxDeposit(itrack);
	for(auto const& pair : fTracks->at(itrack).fTrueEnergy) {
		if(id==pair.first)
			return &pair;
	}

	return nullptr;

}

//============== vertex ======================
const TLorentzVector* StructuredRecoTree::GetVertex(const size_t& ivertex) const {
	return fVertices->at(ivertex).GetVertex();
}

void StructuredRecoTree::VertexCovariance(const size_t& ivertex, float covar[][3]) const {
	fVertices->at(ivertex).GetCovar(covar);
}

/// =============== Vee =======================

const TLorentzVector* StructuredRecoTree::VeeVertex(const size_t& ivee) const {
	return fVees->at(ivee).GetVertex();
}

void StructuredRecoTree::VeeCovariance(const size_t& ivee, float covar[][3]) const {
	return fVees->at(ivee).GetCovar(covar);
}

const vector<TLorentzVector>* StructuredRecoTree::VeeMomentumPerHypothesis(const size_t& ivee) const {
	return fVees->at(ivee).GetMomentaPerHypothesis();
}

const float StructuredRecoTree::VeeChiSquared(const size_t& ivee) const {
	return fVees->at(ivee).GetChiSqr();
}

/// ================ ECal cluster ======================
const CaloCluster* StructuredRecoTree::GetCalCluster(const size_t& icluster) const {
	if(fCalClusters->size()==0)
		return nullptr;

	return &(fCalClusters->at(icluster));
}
const TLorentzVector*   StructuredRecoTree::CalClustPosition(const size_t& icluster) const {
	return GetCalCluster(icluster)->Position();
}

const float  StructuredRecoTree::CalClustEnergy(const size_t& icluster) const {
	return GetCalCluster(icluster)->Energy();
}

const float  StructuredRecoTree::CalClustEnergyError(const size_t& icluster) const {
	return GetCalCluster(icluster)->EnergyError();
}

const float  StructuredRecoTree::CalClustTrueEnergy(const size_t& icluster)     const{
	return GetCalCluster(icluster)->TotalTrueEnergy();
}
const size_t StructuredRecoTree::CalClustNTrueTrack(const size_t& icluster)     const{
	return GetCalCluster(icluster)->NIdes();
}
const int    StructuredRecoTree::CalClustTrkIdMaxDeposit(const size_t& icluster)const{
	return GetCalCluster(icluster)->TrackIdMaxDep();
}
const float  StructuredRecoTree::CalClustMaxDeposit(const size_t& icluster)const{
	if(GetCalCluster(icluster))
		return GetCalCluster(icluster)->MaxDeposit();
	else
		return 0.;
}
const std::pair<int,float>* StructuredRecoTree::CalClustTrueDeposit(const size_t& icluster, const size_t& itrack) const {
	return GetCalCluster(icluster)->GetTrackIdEdep(itrack);
}
const float  StructuredRecoTree::CalClustTimeDifference(const size_t& icluster) const {
	return fCalClusters->at(icluster).TimeDifference();
}

const float* StructuredRecoTree::CalClustShape(const size_t& icluster) const {
	return fCalClusters->at(icluster).Shape();
}

const float  StructuredRecoTree::CalClustTheta(const size_t& icluster) const {
	return fCalClusters->at(icluster).Theta();
}

const float  StructuredRecoTree::CalClustPhi(const size_t& icluster) const {
	return fCalClusters->at(icluster).Phi();
}

const vector<TVector3>* StructuredRecoTree::CalClustEigenVecs(const size_t& icluster) const{
	return fCalClusters->at(icluster).EigenVecs();
}

