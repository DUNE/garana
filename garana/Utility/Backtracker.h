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
#include <climits>

//using std::vector;
//using std::map;
using namespace std;

namespace garana {

 class Backtracker {

    public:
	  Backtracker() {}
	  Backtracker(const TreeManager* tm) : fTM(tm) {}
	  void FillMaps();

	  const vector<UInt_t>* GTruthToG4Particles(const UInt_t& itruth) const;
	  const vector<UInt_t>* GTruthToTracks(const UInt_t& itruth)      const;
	  UInt_t const          G4ParticleToGTruth(const UInt_t& ig4p)     const;
	  const vector<UInt_t>* G4ParticleToTracks(const UInt_t& ig4p)    const;
	  UInt_t const          TrackToGTruth(const UInt_t& itrk)          const;
   	  const vector<UInt_t>* TrackToG4Particles(const UInt_t& itrk)    const;
      const vector<pair<UInt_t,float>> TrackToG4ParticlesDeposits(const UInt_t& itrk)    const;
   	  UInt_t const          TrackToG4Particle(const UInt_t& itrk)     const;
      const pair<UInt_t,float> TrackToG4ParticleDeposit(const UInt_t& itrk)    const;
   	  //const vector<UInt_t>* FSParticleToG4Particles(const UInt_t& ifsp) const;
   	  //UInt_t      G4ParticleToFSParticle(const UInt_t& ig4p) const;

	  UInt_t const          VertexToGTruth(const UInt_t& ivtx)       const;
	  UInt_t const          GTruthToVertex(const UInt_t& ivtx)       const;
	  const vector<UInt_t>* VertexToG4Particles(const UInt_t& ivtx)  const;
	  const vector<UInt_t>* G4ParticleToVertices(const UInt_t& ig4p) const;

	  UInt_t const          VeeToGTruth(const UInt_t& ivee)      const;
	  UInt_t const          GTruthToVee(const UInt_t& ivee)      const;
	  const vector<UInt_t>* VeeToG4Particles(const UInt_t& ivee) const;
   	  UInt_t const          G4ParticleToVee(const UInt_t& ig4p)  const;

   	  const vector<UInt_t>*  TrackToVertices(const UInt_t& itrk) const;
   	  const vector<UInt_t>*  VertexToTracks(const UInt_t& ivtx)  const;
   	  const vector<UInt_t>*  TrackToVees(const UInt_t& itrk)     const;
   	  const vector<UInt_t>*  VeeToTracks(const UInt_t& ivee)     const;

   	  const vector<UInt_t>*  TrackToCalClusters(const UInt_t& itrk)     const;
   	  const vector<UInt_t>*  CalClusterToTracks(const UInt_t& itrk)     const;

   	  const vector<UInt_t>*  G4PToCalClusters(const UInt_t& itrk)     const;
   	  const vector<UInt_t>*  CalClusterToG4Ps(const UInt_t& itrk)     const;

   	  float ASSN_THRESHOLD = 0.5; ///< fraction of total associated energy contributed to reco object a particle must constitute to be considered associated

    private:

   	  const TreeManager* fTM = nullptr;
      //GenTree*  gen = nullptr;
      G4Tree*   g4  = nullptr;
      //DetTree*  det = nullptr;
      RecoTree* rec = nullptr;
   	  template <class T>
   	  bool CheckRange(const map<UInt_t,T>& m, const UInt_t& i) const;
   	  void Clear();

      map< UInt_t, vector<UInt_t> > fGTruthToG4Particles; // gen  -> g4
      map< UInt_t, UInt_t >         fG4ParticleToGTruth;  // g4   -> gen
      map< UInt_t, vector<UInt_t> > fGTruthToTracks;      // gen  -> reco
      map< UInt_t, UInt_t >         fTrackToGTruth;       // reco -> gen
      map< UInt_t, vector<UInt_t> > fTrackToG4Particles;  // reco -> g4
      map< UInt_t, UInt_t >         fTrackToG4Particle;   // reco -> g4
      map< UInt_t, vector<UInt_t> > fG4ParticleToTracks;  // g4   -> reco
      //map< UInt_t, vector<UInt_t> > fFSParticleToG4Particles;
      //map< UInt_t, UInt_t >         fG4ParticleToFSParticle; //TODO are these really necessary?

      map< UInt_t, vector<UInt_t> > fG4ParticleToVertices;// g4   -> reco
      map< UInt_t, vector<UInt_t> > fVertexToG4Particles; // reco -> g4
      map< UInt_t, UInt_t >         fVertexToGTruth;      // reco -> gen
      map< UInt_t, UInt_t >         fGTruthToVertex;      // gen  -> reco
      map< UInt_t, vector<UInt_t> > fVeeToG4Particles;    // reco -> g4
      map< UInt_t, UInt_t >         fG4ParticleToVee;     // g4   -> reco
      map< UInt_t, UInt_t>          fVeeToGTruth;         // reco -> gen
      map< UInt_t, UInt_t >         fGTruthToVee;         // gen  -> reco

      map< UInt_t, vector<UInt_t> > fTrackToVertices;     // reco -> reco
      map< UInt_t, vector<UInt_t> > fVertexToTracks;      // reco -> reco
      map< UInt_t, vector<UInt_t> > fVeeToTracks;         // reco -> reco
      map< UInt_t, vector<UInt_t> > fTrackToVees;         // reco -> reco
      map< UInt_t, vector<UInt_t> > fCaloClusterToTracks; // reco -> reco
      map< UInt_t, vector<UInt_t> > fTrackToCaloClusters; // reco -> reco
      map< UInt_t, vector<UInt_t> > fCaloClusterToG4Ps; // reco -> reco
      map< UInt_t, vector<UInt_t> > fG4PToCaloClusters; // reco -> reco

  }; //class
}//namespace

#endif /* GARANA_BACKTRACKER_H_ */
