/*
 * Track.h
 *
 *  Created on: Feb 22, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_TRACK_H_
#define GARANA_TRACK_H_

#include <TLorentzVector.h>
#include <TVector3.h>

#include <climits>
#include <vector>
#include <utility>

using std::pair;
using std::vector;

namespace garana {
  class Track {

    public: 

	  Track();

	#ifndef __GCCXML__

	  Track(const float& lenFw, const float& lenBk, const float& pBeg, const float& pEnd,
			const TLorentzVector& vtx, const TLorentzVector& end, const TVector3& vtxDir, const TVector3& endDir,
			const float& chiFwd, const float& chiBac, const size_t& nHit,
			const float* trkParBeg, const float* trkParEnd, const float* covarBeg, const float* covarEnd,
			const int& chargeFwd, const int& chargeBac, const vector<pair<int,float>>& pidf, const vector<pair<int,float>>& pidb,
			const float& ionf, const float& ionb, const vector<pair<UInt_t,TLorentzVector>>& truePosVtx,
			const vector<pair<UInt_t,TLorentzVector>>& truePosEnd, const vector<pair<UInt_t,TLorentzVector>>& trueMomVtx,
			const vector<pair<UInt_t,TLorentzVector>>& trueMomEnd, const vector<std::pair<int,float>>& trueEnergy);
	#endif

	  /*int   TruthMatchID(); ///< returns the G4 track ID for the particle contributing the most energy to this track
	  float TruthMatchEDep(); ///< returns the total energy deposited by the particle contributing the most energy to this track
	  float TruthMatchEDepFrac();*/ ///< returns the fraction of the total energy contributed to this track that was deposited by the particle contributing the most energy to this track

    //private:

	  float          fLenFwd;         ///< length of the track in cm from forwards fit
	  float          fLenBac;         ///< length of the track in cm from backwards fit
	  float          fMomBeg;         ///< momentum of the track at the vertex in GeV/c
	  float          fMomEnd;         ///< momentum of the track at the end in GeV/c
	  TLorentzVector fVtx;            ///< track vertex position 4-vector [cm,ns] (vtx vs. end arbitrary)
	  TLorentzVector fEnd;            ///< track end    position 4-vector [cm,ns] (vtx vs. end arbitrary)
	  TVector3       fVtxDir;         ///< track vertex direction
	  TVector3       fEndDir;         ///< track end    direction
	  float          fChiFwd;         ///< chisquared forward fit
	  float          fChiBac;         ///< chisquared backward fit
	  size_t         fNHits;          ///< number of hits

	  float          fTrackParBeg[5]; ///< Track parameters at beginning of track y, z, curvature, phi, lambda  -- 5-param track  (cm, cm, cm-1, rad, rad)
	  float          fTrackParEnd[5]; ///< Track parameters at end of track y, z, curvature, phi, lambda  -- 5-param track  (cm, cm, cm-1, rad, rad)
	  float          fCovMatBeg[15];  ///< covariance matrix at beginning of track -- packed in a 1D array, assuming symmetry
	  float          fCovMatEnd[15];  ///< covariance matrix at end of track

      int            fChgFwd;
      int            fChgBac;
      float          fIonFwd;
      float          fIonBac;
      vector<pair<int,float>> fPidFwd;
      vector<pair<int,float>> fPidBac;

      vector<pair<UInt_t,TLorentzVector>> fTruePosVtx; ///< 4-position for each assc'd MCParticle at track vertex
      vector<pair<UInt_t,TLorentzVector>> fTruePosEnd; ///< 4-position for each assc'd MCParticle at track end
      vector<pair<UInt_t,TLorentzVector>> fTrueMomVtx; ///< 4-momentum for each assc'd MCParticle at track vertex
      vector<pair<UInt_t,TLorentzVector>> fTrueMomEnd; ///< 4-momentum for each assc'd MCParticle at track end
      vector<std::pair<int,float>>        fTrueEnergy; ///< true energy (second) [GeV] deposited by MCParticle with trackID (first)

  }; //class
}//namespace

#endif /* GARANA_TRACK_H_ */
