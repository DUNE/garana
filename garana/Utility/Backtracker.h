/*
 * Backtracker.h
 *
 *  Created on: Mar 15, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_BACKTRACKER_H_
#define GARANA_BACKTRACKER_H_

#include "garana/DataProducts/GTruth.h"
#include "garana/DataProducts/FSParticle.h"
#include "garana/DataProducts/G4Particle.h"
#include "garana/DataProducts/Track.h"
#include "garana/DataProducts/Vertex.h"
#include "garana/DataProducts/Vee.h"
#include "garana/DataProducts/CaloCluster.h"

#include "garana/Accessors/TreeManager.h"

#include <map>

using std::vector;
using std::map;

namespace garana {

 class Backtracker {

    public:
	  Backtracker() {}
	  Backtracker(const TreeManager* tm) : fTM(tm) {}
	  void FillMaps();

	  void       GTruthToG4Particles(const UInt_t& itruth, vector<UInt_t>& ig4ps);
	  void       GTruthToTracks(const UInt_t& itruth, vector<UInt_t>& itracks);
	  void       FSParticleToG4Particles(const UInt_t& ifsp, vector<UInt_t>& ig4ps);
	  UInt_t     G4ParticleToGTruth(const UInt_t& ig4p);
	  UInt_t     G4ParticleToFSParticle(const UInt_t& ig4p);
	  UInt_t     TrackToGTruth(const UInt_t& itrk);
   	  void       TrackToG4Particles(const UInt_t& itrk, vector<UInt_t>& ig4ps);


	  /*void       GTruthToG4Particles(const size_t& ientry, const GTruth& truth, vector<G4Particle>& g4ps);
	  void       GTruthToTracks(const size_t& ientry, const GTruth& truth, vector<Track>& tracks);
	  void       FSParticleToG4Particles(const size_t& ientry, const FSParticle& fsp, vector<G4Particle>& g4ps);
	  GTruth     G4ParticleToGTruth(const size_t& ientry, const G4Particle& g4p);
	  FSParticle G4ParticleToFSParticle(const size_t& ientry, const G4Particle& g4p);
	  GTruth     TrackToGTruth(const size_t& ientry, const Track& trk);
   	  void       TrackToG4Particles(const size_t& ientry, const Track& trk, vector<G4Particle>& g4ps);*/

    private:

   	  const TreeManager* fTM = nullptr;

      map< UInt_t, vector<UInt_t> > fGTruthToG4Particles; // gen -> g4
      map< UInt_t, UInt_t >         fG4ParticleToGTruth;  // g4 -> gen
      map< UInt_t, vector<UInt_t> > fGTruthToTracks;      // gen -> reco
      map< UInt_t, UInt_t >         fTrackToGTruth;       // reco -> gen
      map< UInt_t, vector<UInt_t> > fTrackToG4Particles;  // reco -> g4
      map< UInt_t, vector<UInt_t> > fG4ParticleToTracks;  // g4 -> reco
      map< UInt_t, vector<UInt_t> > fFSParticleToG4Particles;
      map< UInt_t, UInt_t >         fG4ParticleToFSParticle;
      map< UInt_t, UInt_t >         fVertexToGTruth;
      map< UInt_t, UInt_t >         fGTruthToVertex;


  }; //class
}//namespace

#endif /* GARANA_BACKTRACKER_H_ */
