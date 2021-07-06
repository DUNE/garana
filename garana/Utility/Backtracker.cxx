/*
 * Backtracker.cxx
 *
 *  Created on: Mar 15, 2021
 *      Author: chilgenb
 */

#include "garana/Utility/Backtracker.h"

using namespace garana;
using namespace std;

const vector<UInt_t>* Backtracker::GTruthToG4Particles(const UInt_t& itruth) const {
	if(CheckRange(fGTruthToG4Particles, itruth)) {
		return &fGTruthToG4Particles.at(itruth);
	}
	else {
		return new vector<UInt_t>();
	}
}
const vector<UInt_t>* Backtracker::GTruthToTracks(const UInt_t& itruth) const {
	if(CheckRange(fGTruthToTracks, itruth)) {
		return &fGTruthToTracks.at(itruth);
	}
	else {
		return new vector<UInt_t>();
	}
}
/*void   Backtracker::FSParticleToG4Particles(const UInt_t& ifsp, vector<UInt_t>& ig4ps){
	ig4ps.push_back(ifsp); //FIXME - this is just a dummy placeholder
}*/
UInt_t const Backtracker::G4ParticleToGTruth(const UInt_t& ig4p) const {

	if(CheckRange(fG4ParticleToGTruth, ig4p)) {
		return fG4ParticleToGTruth.at(ig4p);
	}
	else {
		return UINT_MAX;
	}
}

const vector<UInt_t>* Backtracker::G4ParticleToTracks(const UInt_t& ig4p) const {

	if(CheckRange(fG4ParticleToTracks, ig4p)) {
		return &fG4ParticleToTracks.at(ig4p);
    }
	else {
		return new vector<UInt_t>();
	}
}

/*UInt_t Backtracker::G4ParticleToFSParticle(const UInt_t& ig4p){
	return ig4p; //FIXME - this is just a dummy placeholder
}*/
UInt_t const Backtracker::TrackToGTruth(const UInt_t& itrk) const {

	if(CheckRange(fTrackToGTruth, itrk)) {
		return fTrackToGTruth.at(itrk);
	}
	else {
		return UINT_MAX;
	}
}

const vector<UInt_t>* Backtracker::TrackToG4Particles(const UInt_t& itrk) const {
	if(CheckRange(fTrackToG4Particles, itrk)) {
		return &fTrackToG4Particles.at(itrk);
	}
	else {
		return new vector<UInt_t>();
	}
}

UInt_t const Backtracker::TrackToG4Particle(const UInt_t& itrk) const {
	if(CheckRange(fTrackToG4Particle, itrk)) {
		return fTrackToG4Particle.at(itrk);
	}
	else {
		return UINT_MAX;
	}
}

UInt_t const Backtracker::VertexToGTruth(const UInt_t& ivtx) const {
	if(CheckRange(fVertexToGTruth, ivtx)) {
		return fVertexToGTruth.at(ivtx);
	}
	else {
		return UINT_MAX;
	}
}

UInt_t const Backtracker::GTruthToVertex(const UInt_t& itruth) const {
	if(CheckRange(fGTruthToVertex, itruth)) {
		return fGTruthToVertex.at(itruth);
	}
	else {
		return UINT_MAX;
	}
}

const vector<UInt_t>* Backtracker::VertexToG4Particles(const UInt_t& ivtx) const {
	if(CheckRange(fVertexToG4Particles, ivtx)) {
		return &fVertexToG4Particles.at(ivtx);
	}
	else {
		return new vector<UInt_t>();
	}
}

const vector<UInt_t>*  Backtracker::G4ParticleToVertices(const UInt_t& ig4p) const {
	if(CheckRange(fG4ParticleToVertices, ig4p)) {
		return &fG4ParticleToVertices.at(ig4p);
	}
	else {
		return new vector<UInt_t>();
	}
}

UInt_t const Backtracker::VeeToGTruth(const UInt_t& ivee) const {
	return fVeeToGTruth.at(ivee);
}
UInt_t const Backtracker::GTruthToVee(const UInt_t& itruth) const {
	return fGTruthToVee.at(itruth);
}
const vector<UInt_t>* Backtracker::VeeToG4Particles(const UInt_t& ivee) const {
	if(CheckRange(fVeeToG4Particles, ivee)) {
		return &fVeeToG4Particles.at(ivee);
	}
	else {
		return new vector<UInt_t>();
	}
}
UInt_t const Backtracker::G4ParticleToVee(const UInt_t& ig4p) const {
	return fG4ParticleToVee.at(ig4p);
}

const vector<UInt_t>* Backtracker::TrackToVertices(const UInt_t& itrk) const {
	if(CheckRange(fTrackToVertices, itrk)) {
		return &fTrackToVertices.at(itrk);
	}
	else {
		return new vector<UInt_t>();
	}
}
const vector<UInt_t>* Backtracker::VertexToTracks(const UInt_t& ivtx) const {
	if(CheckRange(fVertexToTracks, ivtx)) {
		return &fVertexToTracks.at(ivtx);
	}
	else {
		return new vector<UInt_t>();
	}
}
const vector<UInt_t>* Backtracker::TrackToVees(const UInt_t& itrk) const {
	if(CheckRange(fTrackToVees, itrk)) {
		return &fTrackToVees.at(itrk);
	}
	else {
		return new vector<UInt_t>();
	}
}
const vector<UInt_t>* Backtracker::VeeToTracks(const UInt_t& ivee) const {
	if(CheckRange(fVeeToTracks, ivee)) {
		return &fVeeToTracks.at(ivee);
	}
	else {
		return new vector<UInt_t>();
	}
}

const vector<UInt_t>*  Backtracker::TrackToCalClusters(const UInt_t& itrk) const {
	if(CheckRange(fTrackToCaloClusters, itrk)) {
		return &fTrackToCaloClusters.at(itrk);
	}
	else {
		return new vector<UInt_t>();
	}
}

const vector<UInt_t>*  Backtracker::CalClusterToTracks(const UInt_t& icluster) const {
	if(CheckRange(fCaloClusterToTracks, icluster)) {
		return &fCaloClusterToTracks.at(icluster);
	}
	else {
		return new vector<UInt_t>();
	}
}//

const vector<UInt_t>* Backtracker::G4PToCalClusters(const UInt_t& ig4p) const {
	if(CheckRange(fG4PToCaloClusters, ig4p)) {
		return &fG4PToCaloClusters.at(ig4p);
	}
	else {
		return new vector<UInt_t>();
	}
}//

const vector<UInt_t>* Backtracker::CalClusterToG4Ps(const UInt_t& icluster) const {
	if(CheckRange(fCaloClusterToG4Ps, icluster)) {
		return &fCaloClusterToG4Ps.at(icluster);
	}
	else {
		return new vector<UInt_t>();
	}
}//

//=======================================
void Backtracker::FillMaps() {

	Clear();
    //GenTree*  gen = nullptr;
    G4Tree*   g4  = nullptr;
    //DetTree*  det = nullptr;
    RecoTree* rec = nullptr;

    //if(fTM->IsActiveGenTree())  gen = fTM->GetGenTree();
    if(fTM->IsActiveG4Tree())   g4  = fTM->GetG4Tree();
    //if(fTM->IsActiveDetTree())  det = fTM->GetDetTree();
    if(fTM->IsActiveRecTree())  rec = fTM->GetRecoTree();

	if(fTM->IsActiveG4Tree()){

		for(UInt_t ig4p=0; ig4p<g4->NSim(); ig4p++) {
			fG4ParticleToTracks[ig4p] = {};
		}

		if(fTM->IsActiveRecTree()){

			for(UInt_t itrk = 0; itrk<rec->NTrack(); itrk++ ) {

				if(rec->TrackMaxDepositFrac(itrk)>ASSN_THRESHOLD) continue;

				vector<UInt_t> tmpindices;
				rec->GetTrackG4PIndices(itrk, tmpindices); //fTrackToG4Particles[itrk]);
				int matchid = rec->TrackTrkIdMaxDeposit(itrk);
				//cout << "track matched to " << fTrackToG4Particles[itrk].size() << " G4 particle(s)" << endl;

				//for(UInt_t ig4p=0; ig4p<fTrackToG4Particles[itrk].size(); ig4p++){
				for(UInt_t ig4p=0; ig4p<tmpindices.size(); ig4p++){


					if(fG4ParticleToTracks.find(fTrackToG4Particles[itrk][ig4p]) != fG4ParticleToTracks.end()) {
						fTrackToG4Particles[itrk][ig4p] = tmpindices[ig4p];
					//if(fG4ParticleToTracks.find(tmpindices[ig4p]) != fG4ParticleToTracks.end() &&  //){
						if(	g4->TrackID(tmpindices[ig4p]) == matchid ) {

							fTrackToG4Particle[itrk] = ig4p;
							fG4ParticleToTracks[ig4p].push_back(itrk);
							break;
						}
					}
				}
				//for(UInt_t ig4p=0; ig4p<g4->NSim(); ig4p++) {
				//	if(fG4ParticleToTracks[ig4p].size() == 0) continue;
					//cout << "G4particle " << ig4p << " matched to " << fG4ParticleToTracks[ig4p].size()
					//     << " reco track(s)" << endl;
				//}
			}
		}
	}


	if(fTM->IsActiveGenTree()){
		if(fTM->IsActiveG4Tree()){

			//G4 particles
			for(UInt_t ig4 = 0; ig4<g4->NSim(); ig4++ ) {
				fG4ParticleToGTruth[ig4] = g4->GetTruthIndex(ig4);
				fGTruthToG4Particles[ fG4ParticleToGTruth[ig4] ].push_back(ig4);

				//fG4ParticleToFSParticle[ig4]  //map< UInt_t, UInt_t >
				//fFSParticleToG4Particles //map< UInt_t, vector<UInt_t> >

			}//endfor g4 particles


		}//endif g4tree

		if(fTM->IsActiveRecTree()){

			//tracks
			for(UInt_t itrk=0; itrk<rec->NTrack(); itrk++ ) {
            	fTrackToGTruth[itrk] = fG4ParticleToGTruth[ fTrackToG4Particles[itrk][0] ]; //TODO select truth with most associated energy
            	fGTruthToTracks[ fTrackToGTruth[itrk] ].push_back(itrk);
            }//endfor tracks

			//vertices
            for(UInt_t ivtx=0; ivtx<rec->NVertex(); ivtx++ ) {
            	rec->GetVertexTrackIndices(ivtx,fVertexToTracks[ivtx]);
            	for(UInt_t itrk=0; itrk<fVertexToTracks[ivtx].size(); itrk++) {
            	    fTrackToVertices[ fVertexToTracks[ivtx][itrk] ].push_back(ivtx);

            	    for(UInt_t ig4p=0; ig4p<fTrackToG4Particles[fVertexToTracks[ivtx][itrk]].size(); ig4p++) {
            	        fVertexToG4Particles[ivtx].push_back( fTrackToG4Particles[ fVertexToTracks[ivtx][itrk] ][ig4p] );
            	        fG4ParticleToVertices[ fVertexToG4Particles[ivtx].back() ].push_back(ivtx);
            	    }
            	}
        	    fVertexToGTruth[ivtx] = fTrackToGTruth[ fVertexToTracks[ivtx][0] ];//TODO you sure all tracks associated with vertex associated with same GTruth?
        	    fGTruthToVertex[ fVertexToGTruth[ivtx] ] = ivtx;
            }//endfor vertices

            //vees
            for(UInt_t ivee=0; ivee<rec->NVee(); ivee++){

            	rec->GetVeeTrackIndices(ivee, fVeeToTracks[ivee]);

            	for(UInt_t itrk=0; itrk<fVeeToTracks[ivee].size(); itrk++){

            	    fTrackToVees[ fVeeToTracks[ivee][itrk] ].push_back(ivee);

            	    for(UInt_t ig4p=0; ig4p<fTrackToG4Particles[ fVeeToTracks[ivee][itrk] ].size(); ig4p++) {
            	        fVeeToG4Particles[ivee].push_back(fTrackToG4Particles[ fVeeToTracks[ivee][itrk] ][ig4p]);
            	        fG4ParticleToVee[fVeeToG4Particles[ivee].back()] = ivee;
            	    }
            	}

        	    fVeeToGTruth[ivee] = fTrackToGTruth[ fVeeToTracks[ivee][0] ];//TODO you sure all tracks associated with vee associated with same GTruth?
        	    fGTruthToVee[ fVeeToGTruth[ivee] ] = ivee;
            }//endfor vees

            //ECal clusters
            for(UInt_t iclust=0; iclust<rec->NCalCluster(); iclust++){

            	rec->GetCalClusterTrackIndices(iclust,fCaloClusterToTracks[iclust]);

            	for(UInt_t itrk=0; itrk<fCaloClusterToTracks[iclust].size(); itrk++){
            		fTrackToCaloClusters[ fCaloClusterToTracks[iclust][itrk] ].push_back(iclust);
            	}

            	rec->GetCalClusterG4Indices(iclust,fCaloClusterToG4Ps[iclust]);

            	for(UInt_t ig4p=0; ig4p<fCaloClusterToG4Ps[iclust].size(); ig4p++){
            		fG4PToCaloClusters[ fCaloClusterToG4Ps[iclust][ig4p] ].push_back(iclust);
            	}
            }

		}//endif recotree

	}//if gentree

}//end FillMaps()

template <class T>
bool Backtracker::CheckRange(const map<UInt_t,T>& m, const UInt_t& i) const {

	try {
		if(m.find(i)==m.end())
			throw(i);
		return true;
	}
	catch(UInt_t i){
		//cerr << "ERROR Backtracker: map index not found" << endl;
		return false;
	}
}

void Backtracker::Clear() {

    fGTruthToG4Particles.clear();
    fG4ParticleToGTruth.clear();
    fGTruthToTracks.clear();
    fTrackToGTruth.clear();
    fTrackToG4Particles.clear();
    fTrackToG4Particle.clear();
    fG4ParticleToTracks.clear();
    //fFSParticleToG4Particles.clear();
    //fG4ParticleToFSParticle.clear();
    fVertexToGTruth.clear();
    fGTruthToVertex.clear();
    fG4ParticleToVertices.clear();
    fVertexToG4Particles.clear();
    fVertexToGTruth.clear();
    fGTruthToVertex.clear();
    fVeeToG4Particles.clear();
    fG4ParticleToVee.clear();
    fVeeToGTruth.clear();
    fGTruthToVee.clear();
    fTrackToVertices.clear();
    fVertexToTracks.clear();
    fVeeToTracks.clear();
    fTrackToVees.clear();
    fCaloClusterToTracks.clear();
    fTrackToCaloClusters.clear();
    fCaloClusterToG4Ps.clear();
    fG4PToCaloClusters.clear();
}
