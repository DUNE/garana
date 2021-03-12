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

namespace garana {
  class Track { //: public TObject {

    public: 

	  Track();
	  Track(float lenFw, float lenBk, float pBeg, float pEnd,
			TLorentzVector& vtx, TLorentzVector& end, TVector3& vtxDir, TVector3& endDir,
			float chiFwd, float chiBac, size_t nHit,
			float* trkParBeg, float* trkParEnd, float* covarBeg, float* covarEnd );

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

	  float*          fTrackParBeg;//[5]; ///< Track parameters at beginning of track y, z, curvature, phi, lambda  -- 5-param track  (cm, cm, cm-1, rad, rad)
	  float*          fTrackParEnd;//[5]; ///< Track parameters at end of track y, z, curvature, phi, lambda  -- 5-param track  (cm, cm, cm-1, rad, rad)
	  float*          fCovMatBeg;//[15]; ///< covariance matrix at beginning of track -- packed in a 1D array, assuming symmetry
	  float*          fCovMatEnd;//[15]; ///< covariance matrix at end of track

	  //ClassDef(Track,2)

  }; //class
}//namespace

#endif /* GARANA_TRACK_H_ */
