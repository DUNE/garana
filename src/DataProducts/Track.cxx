/*
 * Track.cxx
 *
 *  Created on: Feb 22, 2021
 *      Author: chilgenb
 */

#include "garana/DataProducts/Track.h"

using std::vector;
using std::pair;
using namespace garana;


Track::Track() :
		fLenFwd(FLT_MAX),
		fLenBac(FLT_MAX),
		fMomBeg(FLT_MAX),
		fMomEnd(FLT_MAX),
		fChiFwd(FLT_MAX),
		fChiBac(FLT_MAX),
		fNHits (UINT_MAX),
		fChgFwd(INT_MAX),
		fChgBac(INT_MAX),
		fIonFwd(FLT_MAX),
		fIonBac(FLT_MAX)

{
	fVtx.SetXYZT(FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX);
	fEnd.SetXYZT(FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX);
	fVtxDir.SetXYZ(FLT_MAX,FLT_MAX,FLT_MAX);
	fEndDir.SetXYZ(FLT_MAX,FLT_MAX,FLT_MAX);

	for(size_t i=0; i<5; i++) {
		fTrackParBeg =  new float[5];
		fTrackParEnd =  new float[5];
		fTrackParBeg[i] = FLT_MAX;
		fTrackParEnd[i] = FLT_MAX;
	}
	for(size_t i=0; i<15; i++) {
		fCovMatBeg =  new float[15];
		fCovMatEnd =  new float[15];
		fCovMatBeg[i] =  FLT_MAX;
		fCovMatEnd[i] =  FLT_MAX;
	}
}//

Track::Track(float& lenFw, float& lenBk, float& pBeg, float& pEnd,
		TLorentzVector& vtx, TLorentzVector& end, TVector3& vtxDir, TVector3& endDir,
		float& chiFwd, float& chiBac, size_t& nHit,
		float* trkParBeg, float* trkParEnd, float* covarBeg, float* covarEnd,
		int& chargeFwd, int& chargeBac, vector<pair<int,float>>& pidf,
		vector<pair<int,float>>& pidb, float& ionf, float& ionb ) :
			fLenFwd(lenFw),
			fLenBac(lenBk),
			fMomBeg(pBeg),
			fMomEnd(pEnd),
			fVtx   (vtx),
			fEnd   (end),
			fVtxDir(vtxDir),
			fEndDir(endDir),
			fChiFwd(chiFwd),
			fChiBac(chiBac),
			fNHits (nHit),
			fChgFwd(chargeFwd),
			fChgBac(chargeBac),
			fIonFwd(ionf),
			fIonBac(ionb),
			fPidFwd(pidf),
			fPidBac(pidb)
{

	for(size_t i=0; i<5; i++) {
		fTrackParBeg = new float[5];
		fTrackParEnd = new float[5];
		fTrackParBeg[i] = trkParBeg[i];
		fTrackParEnd[i] = trkParEnd[i];
	}
	for(size_t i=0; i<15; i++) {
		fCovMatBeg =  new float[15];
		fCovMatEnd =  new float[15];
		fCovMatBeg[i] =  covarBeg[i];
		fCovMatEnd[i] =  covarEnd[i];
	}
}//constructor

//ClassImp(Track)
