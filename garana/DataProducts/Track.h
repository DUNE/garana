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
//#include <TROOT.h>

#include <climits>
#include <vector>
#include <utility>

using std::pair;
using std::vector;

namespace garana {
  class Track { //: public TObject {

    public: 

	  Track();
	  Track(const float& lenFw, const float& lenBk, const float& pBeg, const float& pEnd,
			const TLorentzVector& vtx, const TLorentzVector& end, const TVector3& vtxDir, const TVector3& endDir,
			const float& chiFwd, const float& chiBac, const size_t& nHit,
			const float* trkParBeg, const float* trkParEnd, const float* covarBeg, const float* covarEnd,
			const int& chargeFwd, const int& chargeBac, const vector<pair<int,float>>& pidf, const vector<pair<int,float>>& pidb,
			const float& ionf, const float& ionb );

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

	  float*          fTrackParBeg; ///< Track parameters at beginning of track y, z, curvature, phi, lambda  -- 5-param track  (cm, cm, cm-1, rad, rad)
	  float*          fTrackParEnd; ///< Track parameters at end of track y, z, curvature, phi, lambda  -- 5-param track  (cm, cm, cm-1, rad, rad)
	  float*          fCovMatBeg;   ///< covariance matrix at beginning of track -- packed in a 1D array, assuming symmetry
	  float*          fCovMatEnd;   ///< covariance matrix at end of track

      int             fChgFwd;
      int             fChgBac;
      float           fIonFwd;
      float           fIonBac;
      vector<pair<int,float>> fPidFwd;
      vector<pair<int,float>> fPidBac;

	  //ClassDef(Track,2)

  }; //class
}//namespace

#endif /* GARANA_TRACK_H_ */
