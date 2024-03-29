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

const vector<pair<UInt_t,float>> Backtracker::TrackToG4ParticlesDeposits(const UInt_t& itrk)    const {

	vector<pair<UInt_t,float>> outvec;
	auto ig4ps =  TrackToG4Particles(itrk);
	auto iddeps = rec->TrackTrueDeposits(itrk);

	map<int,UInt_t> trackIdToig4; // Geant4 trackID to G4Particle index
	for(auto const& ig4p : *ig4ps){
		trackIdToig4[g4->TrackID(ig4p)] = ig4p;
	}


	for( auto const& iddep : *iddeps) {
		outvec.push_back(make_pair(trackIdToig4[iddep.first],iddep.second));
	}

	return outvec;

}

UInt_t const Backtracker::TrackToG4Particle(const UInt_t& itrk) const {
	if(CheckRange(fTrackToG4Particle, itrk)) {
		return fTrackToG4Particle.at(itrk);
	}
	else {
		return UINT_MAX;
	}
}

const pair<UInt_t,float> Backtracker::TrackToG4ParticleDeposit(const UInt_t& itrk )    const {

	int trkidMax = rec->TrackTrkIdMaxDeposit(itrk);
	auto ig4ps =  TrackToG4Particles(itrk);
	map<int,UInt_t> trackIdToig4; // Geant4 trackID to G4Particle index

	for(auto const& ig4p : *ig4ps){
		trackIdToig4[g4->TrackID(ig4p)] = ig4p;
	}

	const pair<UInt_t,float> outpair(trackIdToig4[trkidMax],rec->TrackMaxDeposit(itrk));
	return outpair;

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

    //cout << "In FillMaps..." << endl;
    Clear();
    //GenTree*  gen = nullptr;
    //g4  = nullptr;
    //DetTree*  det = nullptr;
    //rec = nullptr;

    //cout << "get trees" << endl;
    //if(fTM->IsActiveGenTree())  gen = fTM->GetGenTree();
    if(fTM->IsActiveG4Tree())   g4  = fTM->GetG4Tree();
    //if(fTM->IsActiveDetTree())  det = fTM->GetDetTree();
    if(fTM->IsActiveRecTree())  rec = fTM->GetRecoTree();

    //cout << "checking which are active..." << endl;
    if(fTM->IsActiveG4Tree()){
        //cout << "g4Tree is active" << endl;

        for(UInt_t ig4p=0; ig4p<g4->NSim(); ig4p++) {
        	fG4ParticleToTracks[ig4p] = {};
        }

        if(fTM->IsActiveRecTree()){
            //cout << "recoTree is active" << endl;
            for(UInt_t itrk = 0; itrk<rec->NTrack(); itrk++ ) {

            	//if(rec->TrackMaxDepositFrac(itrk)<ASSN_THRESHOLD) continue;

            	//vector<UInt_t> tmpindices;
            	//cout << "call GetTrackG4PIndices" << endl;
            	rec->GetTrackG4PIndices(itrk, fTrackToG4Particles[itrk]);
            	//cout << "get match ID" << endl;
            	int matchid = rec->TrackTrkIdMaxDeposit(itrk);
            	//cout << "track matched to " << fTrackToG4Particles[itrk].size() << " G4 particle(s)" << endl;

            	//cout << "point i" << endl;
            	if(rec->TrackMaxDepositFrac(itrk)<ASSN_THRESHOLD) {
                    //cout << "track deposit fraction too low (" << rec->TrackMaxDepositFrac(itrk)
                    //     << ")...skipping to next track" << endl;
            		continue;
            	}//should this be considered an association?

            	//cout << "point ii" << endl;
            	for(UInt_t ig4p=0; ig4p<fTrackToG4Particles[itrk].size(); ig4p++){
            		//for(UInt_t ig4p=0; ig4p<tmpindices.size(); ig4p++){

            		if(fG4ParticleToTracks.find(fTrackToG4Particles[itrk][ig4p]) != fG4ParticleToTracks.end()) {

            			//fTrackToG4Particles[itrk][ig4p] = tmpindices[ig4p];
            			//if(fG4ParticleToTracks.find(tmpindices[ig4p]) != fG4ParticleToTracks.end() &&  //){
            			//if(g4->TrackID(tmpindices[ig4p]) == matchid ) {
                        if(g4->TrackID(fTrackToG4Particles[itrk][ig4p]) == matchid ) {
                        	//cout << "found match id" << endl;
                        	fTrackToG4Particle[itrk] = ig4p;
	                    	fG4ParticleToTracks[ig4p].push_back(itrk);
	                    	break;
                        } //if match id matches g4particle ID
	            	}//if G4Particle index is in map
            	}//for all matched particles to this track

            	//cout << "point iii" << endl;
	       // for(UInt_t ig4p=0; ig4p<g4->NSim(); ig4p++) {
	       //     if(fG4ParticleToTracks[ig4p].size() == 0) continue;
	       //     cout << "G4particle " << ig4p << " matched to " << fG4ParticleToTracks[ig4p].size()
	       //          << " reco track(s)" << endl;
	       // }//for all g4Particles
            }//for tracks
        }//if recoTree active
    }//if g4Tree active

    //cout << "point 1" << endl;

    if(fTM->IsActiveGenTree()){

     //   cout << "genTree is active" << endl;

        if(fTM->IsActiveG4Tree()){

            //G4 particles
            for(UInt_t ig4 = 0; ig4<g4->NSim(); ig4++ ) {
            	fG4ParticleToGTruth[ig4] = g4->GetTruthIndex(ig4);
            	fGTruthToG4Particles[ fG4ParticleToGTruth[ig4] ].push_back(ig4);
            
            	//fG4ParticleToFSParticle[ig4]  //map< UInt_t, UInt_t >
            	//fFSParticleToG4Particles //map< UInt_t, vector<UInt_t> >
            
            }//endfor g4 particles
        }//endif g4tree

       // cout << "point 2" << endl;

        if(fTM->IsActiveRecTree()){

            //tracks
            for(UInt_t itrk=0; itrk<rec->NTrack(); itrk++ ) {
         //       cout << "point 2i" << endl;
                //cout << "fTrackToG4Particles[itrk][0] = " << fTrackToG4Particles[itrk][0] << endl;
                //cout << "fG4ParticleToGTruth[ fTrackToG4Particles[itrk][0] ] = " << fG4ParticleToGTruth[ fTrackToG4Particles[itrk][0] ] << endl;
                if(fTrackToG4Particles[itrk].size()==0) continue;
                fTrackToGTruth[itrk] = fG4ParticleToGTruth[ fTrackToG4Particles[itrk][0] ]; //TODO select truth with most associated energy
           //     cout << "point 2ii" << endl;
                fGTruthToTracks[ fTrackToGTruth[itrk] ].push_back(itrk);
             //   cout << "point 2iii" << endl;
            }//endfor tracks

           // cout << "point 2a" << endl;

            //vertices
            for(UInt_t ivtx=0; ivtx<rec->NVertex(); ivtx++ ) {
                rec->GetVertexTrackIndices(ivtx,fVertexToTracks[ivtx]);
                for(UInt_t itrk=0; itrk<fVertexToTracks[ivtx].size(); itrk++) {
                    fTrackToVertices[ fVertexToTracks[ivtx][itrk] ].push_back(ivtx);

                    for(UInt_t ig4p=0; ig4p<fTrackToG4Particles[fVertexToTracks[ivtx][itrk]].size(); ig4p++) {
                        fVertexToG4Particles[ivtx].push_back( fTrackToG4Particles[ fVertexToTracks[ivtx][itrk] ][ig4p] );
                        fG4ParticleToVertices[ fVertexToG4Particles[ivtx].back() ].push_back(ivtx);
                    }// for g4Particles
                }// for tracks
             //       cout << "point 2b" << endl;
            	fVertexToGTruth[ivtx] = fTrackToGTruth[ fVertexToTracks[ivtx][0] ];//TODO you sure all tracks associated with vertex associated with same GTruth?
            	fGTruthToVertex[ fVertexToGTruth[ivtx] ] = ivtx;
            }//endfor vertices

           // cout << "point 3" << endl;

            //vees
            for(UInt_t ivee=0; ivee<rec->NVee(); ivee++){
            
                rec->GetVeeTrackIndices(ivee, fVeeToTracks[ivee]);
            
                for(UInt_t itrk=0; itrk<fVeeToTracks[ivee].size(); itrk++){
            
                    fTrackToVees[ fVeeToTracks[ivee][itrk] ].push_back(ivee);
            
            	for(UInt_t ig4p=0; ig4p<fTrackToG4Particles[ fVeeToTracks[ivee][itrk] ].size(); ig4p++) {
            	    fVeeToG4Particles[ivee].push_back(fTrackToG4Particles[ fVeeToTracks[ivee][itrk] ][ig4p]);
            	    fG4ParticleToVee[fVeeToG4Particles[ivee].back()] = ivee;
            	}
                }// for tracks
            
                fVeeToGTruth[ivee] = fTrackToGTruth[ fVeeToTracks[ivee][0] ];//TODO you sure all tracks associated with vee associated with same GTruth?
                fGTruthToVee[ fVeeToGTruth[ivee] ] = ivee;
            }//endfor vees

          // cout << "point 4" << endl;

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
            }//for clusters

         //   cout << "point 5" << endl;

        }//endif recotree
    }//if gentree

    //cout << "at end of FillMaps()" << endl;

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

    //gen = nullptr;
    g4  = nullptr;
    //det = nullptr;
    rec = nullptr;

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
