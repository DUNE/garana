/*
 * Track.cxx
 *
 *  Created on: Feb 22, 2021
 *      Author: chilgenb
 */

#include "garana/DataProducts/Track.h"
#include <iostream>

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

        //fTrackParBeg =  new float[5];
        //fTrackParEnd =  new float[5];
	for(size_t i=0; i<5; i++) {
		fTrackParBeg[i] = FLT_MAX;
		fTrackParEnd[i] = FLT_MAX;
	}

       // fCovMatBeg =  new float[15];
        //fCovMatEnd =  new float[15];
	for(size_t i=0; i<15; i++) {
		fCovMatBeg[i] =  FLT_MAX;
		fCovMatEnd[i] =  FLT_MAX;
	}
}//

Track::Track(const float& lenFw, const float& lenBk, const float& pBeg, const float& pEnd,
		const TLorentzVector& vtx, const TLorentzVector& end, const TVector3& vtxDir, const TVector3& endDir,
		const float& chiFwd, const float& chiBac, const size_t& nHit,
		const float* trkParBeg, const float* trkParEnd, const float* covarBeg, const float* covarEnd,
		const int& chargeFwd, const int& chargeBac, const vector<pair<int,float>>& pidf,
		const vector<pair<int,float>>& pidb, const float& ionf, const float& ionb, const vector<pair<UInt_t,TLorentzVector>>& truePosVtx,
		const vector<pair<UInt_t,TLorentzVector>>& truePosEnd, const vector<pair<UInt_t,TLorentzVector>>& trueMomVtx,
		const vector<pair<UInt_t,TLorentzVector>>& trueMomEnd, const vector<std::pair<int,float>>& trueEnergy ) :
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
			fPidBac(pidb),
			fTruePosVtx(truePosVtx),
			fTruePosEnd(truePosEnd),
			fTrueMomVtx(trueMomVtx),
			fTrueMomEnd(trueMomEnd),
			fTrueEnergy(trueEnergy)
{

	//std::cout << "about to fill fTrackPar" << std::endl;

	//fTrackParBeg = new float[5];
	//fTrackParEnd = new float[5];
	for(size_t i=0; i<5; i++) {
		fTrackParBeg[i] = trkParBeg[i];
		fTrackParEnd[i] = trkParEnd[i];
	}

	//fCovMatBeg =  new float[15];
	//fCovMatEnd =  new float[15];
	for(size_t i=0; i<15; i++) {
		fCovMatBeg[i] =  covarBeg[i];
		fCovMatEnd[i] =  covarEnd[i];
	}
}//constructor

/*int   Track::TruthMatchID() {
	auto it = std::max_element(fTrueEnergy.begin(),fTrueEnergy.end(),
			      [](const std::pair<int,float>& lhs,const std::pair<int,float>& rhs) -> bool {return lhs.second > rhs.second; }
				  );
	return (*it).first;
}

float Track::TruthMatchEDep() { //TODO check if we actually want total EDep rather than just from the leading contributor
	auto it = std::max_element(fTrueEnergy.begin(),fTrueEnergy.end(),
			      [](const std::pair<int,float>& lhs,const std::pair<int,float>& rhs) -> bool {return lhs.second > rhs.second; }
				  );
	return (*it).second;
}

float Track::TruthMatchEDepFrac() {
	float tot = 0.;
	for(auto const& pair : fTrueEnergy) {
		tot += pair.second;

	}

	return TruthMatchEDep()/tot;
}*/

