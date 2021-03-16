/*
 * Backtracker.cxx
 *
 *  Created on: Mar 15, 2021
 *      Author: chilgenb
 */

#include "garana/Utility/Backtracker.h"

using namespace garana;
using std::vector;

void   Backtracker::GTruthToG4Particles(const UInt_t& itruth, vector<UInt_t>& ig4ps){
	ig4ps = fGTruthToG4Particles[itruth];
}
void   Backtracker::GTruthToTracks(const UInt_t& itruth, vector<UInt_t>& itracks){
	itracks = fGTruthToTracks[itruth];
}
void   Backtracker::FSParticleToG4Particles(const UInt_t& ifsp, vector<UInt_t>& ig4ps){
	ig4ps.push_back(ifsp); //FIXME - this is just a dummy placeholder
}
UInt_t Backtracker::G4ParticleToGTruth(const UInt_t& ig4p){
	return fG4ParticleToGTruth[ig4p];
}
UInt_t Backtracker::G4ParticleToFSParticle(const UInt_t& ig4p){
	return ig4p; //FIXME - this is just a dummy placeholder
}
UInt_t Backtracker::TrackToGTruth(const UInt_t& itrk){
	return fTrackToGTruth[itrk];
}
void   Backtracker::TrackToG4Particles(const UInt_t& itrk, vector<UInt_t>& ig4ps){
	ig4ps = fTrackToG4Particles[itrk];
}

void Backtracker::FillMaps() {

    fGTruthToG4Particles.clear();
    fG4ParticleToGTruth.clear();
    fGTruthToTracks.clear();
    fTrackToGTruth.clear();
    fTrackToG4Particles.clear();
    fG4ParticleToTracks.clear();
    fFSParticleToG4Particles.clear();
    fG4ParticleToFSParticle.clear();
    fVertexToGTruth.clear();
    fGTruthToVertex.clear();

    //GenTree*  gen = nullptr;
    G4Tree*   g4  = nullptr;
    //DetTree*  det = nullptr;
    RecoTree* rec = nullptr;

    //if(fTM->IsActiveGenTree())  gen = fTM->GetGenTree();
    if(fTM->IsActiveG4Tree())   g4  = fTM->GetG4Tree();
    //if(fTM->IsActiveDetTree())  det = fTM->GetDetTree();
    if(fTM->IsActiveRecTree())  rec = fTM->GetRecoTree();

	if(fTM->IsActiveG4Tree()){
		if(fTM->IsActiveRecTree()){

			for(UInt_t itrk = 0; itrk<rec->NTrack(); itrk++ ) {
				rec->GetTrackG4PIndices(itrk, fTrackToG4Particles[itrk]); //map< UInt_t, vector<UInt_t> >
				for(UInt_t ig4p=0; ig4p<fTrackToG4Particles[itrk].size(); ig4p++)
				    fG4ParticleToTracks[ig4p].push_back(fTrackToG4Particles[itrk][ig4p]); //map< UInt_t, vector<UInt_t> >
			}
		}
	}

	if(fTM->IsActiveGenTree()){
		if(fTM->IsActiveG4Tree()){

			for(UInt_t ig4 = 0; ig4<g4->NSim(); ig4++ ) {
				fG4ParticleToGTruth[ig4] = g4->GetTruthIndex(ig4);              //map< UInt_t, UInt_t >
				fGTruthToG4Particles[ fG4ParticleToGTruth[ig4] ].push_back(ig4);  //map< UInt_t, vector<UInt_t> >

				//fG4ParticleToFSParticle[ig4]  //map< UInt_t, UInt_t >
				//fFSParticleToG4Particles //map< UInt_t, vector<UInt_t> >

			}//end for g4 particles


		}//endif g4tree
		if(fTM->IsActiveRecTree()){
            for(UInt_t itrk=0; itrk<rec->NTrack(); itrk++ ) {
            	fTrackToGTruth[itrk] = fG4ParticleToGTruth[ fTrackToG4Particles[itrk][0] ];  //map< UInt_t, UInt_t >  //TODO select truth with most associated energy
            	fGTruthToTracks[ fTrackToGTruth[itrk] ].push_back(itrk); //map< UInt_t, vector<UInt_t> >

            }
			 //fVertexToGTruth //map< UInt_t, UInt_t >
			 //fGTruthToVertex //map< UInt_t, UInt_t >
		}//endif recotree

	}//if gentree

}
