/*
 * FlatRecoTree.h
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_FLATRECOTREE_H_
#define GARANA_FLATRECOTREE_H_

#include "garana/Base/RecoTree.h"

using std::vector;

namespace garana {

 class FlatRecoTree : public RecoTree {

  public:

	FlatRecoTree() {}
	FlatRecoTree(TTree* tree);
	FlatRecoTree(TTree* tree, char opt);

    //accessors inherited from RecoTree
    //virtual void GetEntry(UInt_t entry) override;

	// sizes
	const size_t NTrack()      const override;
	const size_t NVertex()     const override;
	const size_t NVee()        const override;
	const size_t NCalCluster() const override;

	 // track
    const TLorentzVector* TrackVertex(const size_t& itrack)                const override;
    const TLorentzVector* TrackEnd(const size_t& itrack)                   const override;
    const size_t          NTrackHit(const size_t& itrack)                  const override;
    const TVector3*       TrackMomBeg(const size_t& itrack)                const override;
    const TVector3*       TrackMomEnd(const size_t& itrack)                const override;
    const float           TrackVtxDirectionX(const size_t& itrack)         const override;
    const float           TrackVtxDirectionY(const size_t& itrack)         const override;
    const float           TrackVtxDirectionZ(const size_t& itrack)         const override;
    const float           TrackEndDirectionX(const size_t& itrack)         const override;
    const float           TrackEndDirectionY(const size_t& itrack)         const override;
    const float           TrackEndDirectionZ(const size_t& itrack)         const override;
    const float           TrackLenFwd(const size_t& itrack)                const override;
    const float           TrackLenBkd(const size_t& itrack)                const override;
    const float           TrackIonizFwd(const size_t& itrack)              const override;
    const float           TrackIonizBkd(const size_t& itrack)              const override;
    const int             TrackChiSqrFwd(const size_t& itrack)             const override;
    const int             TrackChiSqrBkd(const size_t& itrack)             const override;
    const int             TrackChgFwd(const size_t& itrack)                const override;
    const int             TrackChgBkd(const size_t& itrack)                const override;
    void                  TrackParBeg(const size_t& itrack, float pars[5]) const override;
    void                  TrackParEnd(const size_t& itrack, float pars[5]) const override;
    void                  TrackCovarBeg(const size_t& itrack, float pars[15]) const override;
    void                  TrackCovarEnd(const size_t& itrack, float pars[15]) const override;

	 //vertex
    const TLorentzVector* GetVertex(const size_t& ivertex)                          const override;
    void                  VertexCovariance(const size_t& ivertex, float covar[][3]) const override;

    //vee
    const TLorentzVector*         VeeVertex(const size_t& ivee)                       const override;
    void                          VeeCovariance(const size_t& ivee, float covar[][3]) const override;
    const vector<TLorentzVector>* VeeMomentumPerHypothesis(const size_t& ivee)        const override;
    const float                   VeeChiSquared(const size_t& ivee)                   const override;

    //ECal cluster
    const TLorentzVector*   CalClustPosition(const size_t& icluster)       const override;
    const float             CalClustEnergy(const size_t& icluster)         const override;
    const float             CalClustEnergyError(const size_t& icluster)    const override;
	const float             CalClustTrueEnergy(const size_t& icluster)     const override;
	const size_t            CalClustNTrueTrack(const size_t& icluster)     const override;
	const int               CalClustTrkIdMaxDeposit(const size_t& icluster)const override;
	const float             CalClustMaxDeposit(const size_t& icluster)     const override;
	const std::pair<int,float>* CalClustTrueDeposit(const size_t& icluster, const size_t& itrack) const override;
    const float             CalClustTimeDifference(const size_t& icluster) const override;
    const float*            CalClustShape(const size_t& icluster)          const override;
    const float             CalClustTheta(const size_t& icluster)          const override;
    const float             CalClustPhi(const size_t& icluster)            const override;
    const vector<TVector3>* CalClustEigenVecs(const size_t& icluster)      const override;

    //private:
  protected:

    bool SetBranchAddresses() override;
    void SetVecs();
    void ClearVecs();

	//leaves and branches //FIXME: redundant info for track positions?
    //track info
	vector<float>*  fTrkLenFwd             = nullptr;        ///< length of the track in cm from forwards fit
	vector<float>*  fTrkLenBac             = nullptr;        ///< length of the track in cm from backwards fit
	vector<float>*  fTrkMomBeg             = nullptr;        ///< momentum of the track at the vertex in GeV/c
	vector<float>*  fTrkMomEnd             = nullptr;        ///< momentum of the track at the end in GeV/c
	vector<float>*  fTrkVtxX               = nullptr;        ///< track vertex position 4-vector [cm,ns] (vtx vs. end arbitrary)
	vector<float>*  fTrkVtxY               = nullptr;
	vector<float>*  fTrkVtxZ               = nullptr;
	vector<float>*  fTrkVtxT               = nullptr;
	vector<float>*  fTrkEndX               = nullptr;        ///< track end    position 4-vector [cm,ns] (vtx vs. end arbitrary)
	vector<float>*  fTrkEndY               = nullptr;
	vector<float>*  fTrkEndZ               = nullptr;
	vector<float>*  fTrkEndT               = nullptr;

	vector<float>*  fTrkVtxDirX            = nullptr;        ///< track vertex direction
	vector<float>*  fTrkVtxDirY            = nullptr;
	vector<float>*  fTrkVtxDirZ            = nullptr;
	vector<float>*  fTrkEndDirX            = nullptr;        ///< track end    direction
	vector<float>*  fTrkEndDirY            = nullptr;
	vector<float>*  fTrkEndDirZ            = nullptr;
	vector<float>*  fTrkChiFwd             = nullptr;        ///< chisquared forward fit
	vector<float>*  fTrkChiBac             = nullptr;        ///< chisquared backward fit
	vector<size_t>* fTrkNHits              = nullptr;        ///< number of hits

	vector<float>*  fTrackXBeg             = nullptr; ///< Track x-coord at beginning of track [cm]
	vector<float>*  fTrackYBeg             = nullptr; ///< Track y-coord (par[0]) at beginning of track [cm]
	vector<float>*  fTrackZBeg             = nullptr; ///< Track z-coord (par[1]) at beginning of track [cm]
	vector<float>*  fTrackCurvBeg          = nullptr; ///< Track curvature (par[2]) at beginning of track [cm^-1]
	vector<float>*  fTrackPhiBeg           = nullptr; ///< Track phi (par[3]) at beginning of track [rad]
	vector<float>*  fTrackLambBeg          = nullptr; ///< Track lambda (par[4]) at beginning of track [rad]
	vector<float>*  fTrackXEnd             = nullptr; ///< Track x-coord at end of track [cm]
	vector<float>*  fTrackYEnd             = nullptr; ///< Track y-coord (par[0]) at end of track [cm]
	vector<float>*  fTrackZEnd             = nullptr; ///< Track z-coord (par[1]) at end of track [cm]
	vector<float>*  fTrackCurvEnd          = nullptr; ///< Track curvature (par[2]) at end of track [cm^-1]
	vector<float>*  fTrackPhiEnd           = nullptr; ///< Track phi (par[3]) at end of track [rad]
	vector<float>*  fTrackLambEnd          = nullptr; ///< Track lambda (par[4]) at end of track [rad]
	vector<float>*  fTrkCovMat1Beg         = nullptr; ///< covariance matrix at beginning of track -- assuming symmetry
	vector<float>*  fTrkCovMat2Beg         = nullptr;
	vector<float>*  fTrkCovMat3Beg         = nullptr;
	vector<float>*  fTrkCovMat4Beg         = nullptr;
	vector<float>*  fTrkCovMat5Beg         = nullptr;
	vector<float>*  fTrkCovMat6Beg         = nullptr;
	vector<float>*  fTrkCovMat7Beg         = nullptr;
	vector<float>*  fTrkCovMat8Beg         = nullptr;
	vector<float>*  fTrkCovMat9Beg         = nullptr;
	vector<float>*  fTrkCovMat10Beg        = nullptr;
	vector<float>*  fTrkCovMat11Beg        = nullptr;
	vector<float>*  fTrkCovMat12Beg        = nullptr;
	vector<float>*  fTrkCovMat13Beg        = nullptr;
	vector<float>*  fTrkCovMat14Beg        = nullptr;
	vector<float>*  fTrkCovMat15Beg        = nullptr;
	vector<float>*  fTrkCovMat1End         = nullptr; ///< covariance matrix at end of track -- assuming symmetry
	vector<float>*  fTrkCovMat2End         = nullptr;
	vector<float>*  fTrkCovMat3End         = nullptr;
	vector<float>*  fTrkCovMat4End         = nullptr;
	vector<float>*  fTrkCovMat5End         = nullptr;
	vector<float>*  fTrkCovMat6End         = nullptr;
	vector<float>*  fTrkCovMat7End         = nullptr;
	vector<float>*  fTrkCovMat8End         = nullptr;
	vector<float>*  fTrkCovMat9End         = nullptr;
	vector<float>*  fTrkCovMat10End        = nullptr;
	vector<float>*  fTrkCovMat11End        = nullptr;
	vector<float>*  fTrkCovMat12End        = nullptr;
	vector<float>*  fTrkCovMat13End        = nullptr;
	vector<float>*  fTrkCovMat14End        = nullptr;
	vector<float>*  fTrkCovMat15End        = nullptr;

	vector<float>*  fTrkIonizFwd           = nullptr;
	vector<float>*  fTrkIonizBac           = nullptr;
	vector<int>*    fTrkChgFwd             = nullptr;
	vector<int>*    fTrkChgBac             = nullptr;


	// Vee info
	vector<float>* fVeeVtxX             = nullptr;    ///< x-position of vertex [cm]
	vector<float>* fVeeVtxY             = nullptr;    ///< y-position of vertex [cm]
	vector<float>* fVeeVtxZ             = nullptr;    ///< z-position of vertex [cm]
	vector<float>* fVeeVtxT             = nullptr;    ///< time of vertex [ns]
	vector<float>* fVeeVtxCovar11       = nullptr;    ///< uncertainties in vertex position [cm]
	vector<float>* fVeeVtxCovar12       = nullptr;
	vector<float>* fVeeVtxCovar13       = nullptr;
	vector<float>* fVeeVtxCovar21       = nullptr;
	vector<float>* fVeeVtxCovar22       = nullptr;
	vector<float>* fVeeVtxCovar23       = nullptr;
	vector<float>* fVeeVtxCovar31       = nullptr;
	vector<float>* fVeeVtxCovar32       = nullptr;
	vector<float>* fVeeVtxCovar33       = nullptr;

	vector<float>* fVeePxKshort         = nullptr; ///< four-momentum of vee, for Kshort hypothesis [GeV]
	vector<float>* fVeePyKshort         = nullptr;
	vector<float>* fVeePzKshort         = nullptr;
	vector<float>* fVeeEKshort          = nullptr;
	vector<float>* fVeePxLamb1          = nullptr; ///< four-momentum of vee, for Kshort hypothesis [GeV]
	vector<float>* fVeePyLamb1          = nullptr;
	vector<float>* fVeePzLamb1          = nullptr;
	vector<float>* fVeeELamb1           = nullptr;
	vector<float>* fVeePxLamb2          = nullptr; ///< four-momentum of vee, for Kshort hypothesis [GeV]
	vector<float>* fVeePyLamb2          = nullptr;
	vector<float>* fVeePzLamb2          = nullptr;
	vector<float>* fVeeELamb2           = nullptr;
	vector<float>* fVeeChisqr           = nullptr; ///< chi-squared

    // Vertex info
	vector<float>* fVtxX                = nullptr;    ///< x-position of vertex [cm]
	vector<float>* fVtxY                = nullptr;    ///< y-position of vertex [cm]
	vector<float>* fVtxZ                = nullptr;    ///< z-position of vertex [cm]
	vector<float>* fVtxT                = nullptr;    ///< time of vertex [ns]
	vector<float>* fVtxCovar11          = nullptr;    ///< uncertainties in vertex position [cm]
	vector<float>* fVtxCovar12          = nullptr;
	vector<float>* fVtxCovar13          = nullptr;
	vector<float>* fVtxCovar21          = nullptr;
	vector<float>* fVtxCovar22          = nullptr;
	vector<float>* fVtxCovar23          = nullptr;
	vector<float>* fVtxCovar31          = nullptr;
	vector<float>* fVtxCovar32          = nullptr;
	vector<float>* fVtxCovar33          = nullptr;

    // CalCluster info
    vector<float>* fCalClustX           = nullptr; ///< x-position of the cluster [cm]
    vector<float>* fCalClustY           = nullptr; ///< y-position of the cluster [cm]
    vector<float>* fCalClustZ           = nullptr; ///< z-position of the cluster [cm]
    vector<float>* fCalClustT           = nullptr; ///< time of the cluster [ns]
    vector<float>* fCalClustEnergy      = nullptr; ///< energy of the ECal cluster [GeV]
    vector<float>* fCalClustEnergyError = nullptr; ///< uncertainty of the cluster energy [GeV]
    vector<float>* fCalClustTdiff       = nullptr; ///< time difference between the first and last layer of the cluster [ns]
    vector<float>* fCalClustEllip       = nullptr; ///< cluster shape parameter ellipsoid
    vector<float>* fCalClustR1          = nullptr; ///< cluster shape parameter r1
    vector<float>* fCalClustR2          = nullptr; ///< cluster shape parameter r2
    vector<float>* fCalClustR3          = nullptr; ///< cluster shape parameter r3
    vector<float>* fCalClustVol         = nullptr; ///< cluster shape parameter volume
    vector<float>* fCalClustWidth       = nullptr; ///< cluster shape parameter width
    vector<float>* fCalClustTheta       = nullptr; ///< intrasic direction of the cluster theta
    vector<float>* fCalClustPhi         = nullptr; ///< intrasic direction of the cluster phi
    vector<float>* fCalClustEigen1X     = nullptr; ///< Eigenvectors of the cluster in ascending order (principal axis with smallest inertial mass) normalised to 1
    vector<float>* fCalClustEigen1Y     = nullptr;
    vector<float>* fCalClustEigen1Z     = nullptr;
    vector<float>* fCalClustEigen2X     = nullptr; ///< Eigenvectors of the cluster in ascending order (principal axis with smallest inertial mass) normalised to 1
    vector<float>* fCalClustEigen2Y     = nullptr;
    vector<float>* fCalClustEigen2Z     = nullptr;
    vector<float>* fCalClustEigen3X     = nullptr; ///< Eigenvectors of the cluster in ascending order (principal axis with smallest inertial mass) normalised to 1
    vector<float>* fCalClustEigen3Y     = nullptr;
    vector<float>* fCalClustEigen3Z     = nullptr;

    // associations
	vector<vector<UInt_t>>* fTrackG4PIndices   = nullptr;
	vector<vector<UInt_t>>* fVertTrackIndices  = nullptr;
	vector<vector<UInt_t>>* fVeeTrackIndices   = nullptr;
	vector<vector<UInt_t>>* fCalTrackIndices   = nullptr;

	vector<vector<Int_t>>*  fVertTrackEnds     = nullptr;
	vector<vector<Int_t>>*  fVeeTrackEnds      = nullptr;

	// branches
	TBranch* b_TrkLenFwd           = nullptr;
	TBranch* b_TrkLenBac           = nullptr;
	TBranch* b_TrkMomBeg           = nullptr;
	TBranch* b_TrkMomEnd           = nullptr;
	TBranch* b_TrkVtxX             = nullptr;
	TBranch* b_TrkVtxY             = nullptr;
	TBranch* b_TrkVtxZ             = nullptr;
	TBranch* b_TrkVtxT             = nullptr;
	TBranch* b_TrkEndX             = nullptr;
	TBranch* b_TrkEndY             = nullptr;
	TBranch* b_TrkEndZ             = nullptr;
	TBranch* b_TrkEndT             = nullptr;

	TBranch* b_TrkVtxDirX          = nullptr;
	TBranch* b_TrkVtxDirY          = nullptr;
	TBranch* b_TrkVtxDirZ          = nullptr;
	TBranch* b_TrkEndDirX          = nullptr;
	TBranch* b_TrkEndDirY          = nullptr;
	TBranch* b_TrkEndDirZ          = nullptr;
	TBranch* b_TrkChiFwd           = nullptr;
	TBranch* b_TrkChiBac           = nullptr;
	TBranch* b_TrkNHits            = nullptr;

	TBranch* b_TrackXBeg           = nullptr;
	TBranch* b_TrackYBeg           = nullptr;
	TBranch* b_TrackZBeg           = nullptr;
	TBranch* b_TrackCurvBeg        = nullptr;
	TBranch* b_TrackPhiBeg         = nullptr;
	TBranch* b_TrackLambBeg        = nullptr;
	TBranch* b_TrackParEnd         = nullptr;
	TBranch* b_TrackXEnd           = nullptr;
	TBranch* b_TrackYEnd           = nullptr;
	TBranch* b_TrackZEnd           = nullptr;
	TBranch* b_TrackCurvEnd        = nullptr;
	TBranch* b_TrackPhiEnd         = nullptr;
	TBranch* b_TrackLambEnd        = nullptr;
	TBranch* b_TrkCovMat1Beg       = nullptr;
	TBranch* b_TrkCovMat2Beg       = nullptr;
	TBranch* b_TrkCovMat3Beg       = nullptr;
	TBranch* b_TrkCovMat4Beg       = nullptr;
	TBranch* b_TrkCovMat5Beg       = nullptr;
	TBranch* b_TrkCovMat6Beg       = nullptr;
	TBranch* b_TrkCovMat7Beg       = nullptr;
	TBranch* b_TrkCovMat8Beg       = nullptr;
	TBranch* b_TrkCovMat9Beg       = nullptr;
	TBranch* b_TrkCovMat10Beg      = nullptr;
	TBranch* b_TrkCovMat11Beg      = nullptr;
	TBranch* b_TrkCovMat12Beg      = nullptr;
	TBranch* b_TrkCovMat13Beg      = nullptr;
	TBranch* b_TrkCovMat14Beg      = nullptr;
	TBranch* b_TrkCovMat15Beg      = nullptr;
	TBranch* b_TrkCovMat1End       = nullptr;
	TBranch* b_TrkCovMat2End       = nullptr;
	TBranch* b_TrkCovMat3End       = nullptr;
	TBranch* b_TrkCovMat4End       = nullptr;
	TBranch* b_TrkCovMat5End       = nullptr;
	TBranch* b_TrkCovMat6End       = nullptr;
	TBranch* b_TrkCovMat7End       = nullptr;
	TBranch* b_TrkCovMat8End       = nullptr;
	TBranch* b_TrkCovMat9End       = nullptr;
	TBranch* b_TrkCovMat10End      = nullptr;
	TBranch* b_TrkCovMat11End      = nullptr;
	TBranch* b_TrkCovMat12End      = nullptr;
	TBranch* b_TrkCovMat13End      = nullptr;
	TBranch* b_TrkCovMat14End      = nullptr;
	TBranch* b_TrkCovMat15End      = nullptr;

	TBranch* b_VeeVtxX             = nullptr;
	TBranch* b_VeeVtxY             = nullptr;
	TBranch* b_VeeVtxZ             = nullptr;
	TBranch* b_VeeVtxT             = nullptr;
	TBranch* b_VeeVtxCovar11       = nullptr;
	TBranch* b_VeeVtxCovar12       = nullptr;
	TBranch* b_VeeVtxCovar13       = nullptr;
	TBranch* b_VeeVtxCovar21       = nullptr;
	TBranch* b_VeeVtxCovar22       = nullptr;
	TBranch* b_VeeVtxCovar23       = nullptr;
	TBranch* b_VeeVtxCovar31       = nullptr;
	TBranch* b_VeeVtxCovar32       = nullptr;
	TBranch* b_VeeVtxCovar33       = nullptr;

	TBranch* b_VeePxKshort         = nullptr;
	TBranch* b_VeePyKshort         = nullptr;
	TBranch* b_VeePzKshort         = nullptr;
	TBranch* b_VeeEKshort          = nullptr;
	TBranch* b_VeePxLamb1          = nullptr;
	TBranch* b_VeePyLamb1          = nullptr;
	TBranch* b_VeePzLamb1          = nullptr;
	TBranch* b_VeeELamb1           = nullptr;
	TBranch* b_VeePxLamb2          = nullptr;
	TBranch* b_VeePyLamb2          = nullptr;
	TBranch* b_VeePzLamb2          = nullptr;
	TBranch* b_VeeELamb2           = nullptr;
	TBranch* b_VeeChisqr           = nullptr;

	TBranch* b_VtxX                = nullptr;
	TBranch* b_VtxY                = nullptr;
	TBranch* b_VtxZ                = nullptr;
	TBranch* b_VtxT                = nullptr;
	TBranch* b_VtxCovar11          = nullptr;
	TBranch* b_VtxCovar12          = nullptr;
	TBranch* b_VtxCovar13          = nullptr;
	TBranch* b_VtxCovar21          = nullptr;
	TBranch* b_VtxCovar22          = nullptr;
	TBranch* b_VtxCovar23          = nullptr;
	TBranch* b_VtxCovar31          = nullptr;
	TBranch* b_VtxCovar32          = nullptr;
	TBranch* b_VtxCovar33          = nullptr;

    TBranch* b_CalClustX           = nullptr;
	TBranch* b_CalClustY           = nullptr;
	TBranch* b_CalClustZ           = nullptr;
	TBranch* b_CalClustT           = nullptr;
	TBranch* b_CalClustEnergy      = nullptr;
	TBranch* b_CalClustEnergyError = nullptr;
	TBranch* b_CalClustTdiff       = nullptr;
	TBranch* b_CalClustEllip       = nullptr;
	TBranch* b_CalClustR1          = nullptr;
	TBranch* b_CalClustR2          = nullptr;
	TBranch* b_CalClustR3          = nullptr;
	TBranch* b_CalClustVol         = nullptr;
	TBranch* b_CalClustWidth       = nullptr;
	TBranch* b_CalClustTheta       = nullptr;
	TBranch* b_CalClustPhi         = nullptr;
	TBranch* b_CalClustEigen1X     = nullptr;
	TBranch* b_CalClustEigen1Y     = nullptr;
	TBranch* b_CalClustEigen1Z     = nullptr;
	TBranch* b_CalClustEigen2X     = nullptr;
	TBranch* b_CalClustEigen2Y     = nullptr;
	TBranch* b_CalClustEigen2Z     = nullptr;
	TBranch* b_CalClustEigen3X     = nullptr;
	TBranch* b_CalClustEigen3Y     = nullptr;
	TBranch* b_CalClustEigen3Z     = nullptr;

    TBranch* b_TrackG4PIndices     = nullptr;
    TBranch* b_VertTrackIndices    = nullptr;
    TBranch* b_VeeTrackIndices     = nullptr;
    TBranch* b_CalTrackIndices     = nullptr;

    TBranch* b_VertTrackEnds       = nullptr;
    TBranch* b_VeeTrackEnds        = nullptr;

    TBranch* b_TrkIonizFwd         = nullptr;
    TBranch* b_TrkIonizBac         = nullptr;
    TBranch* b_TrkChgFwd           = nullptr;
    TBranch* b_TrkChgBac           = nullptr;

 };//class
}//namespace

#endif /* GARANA_FLATRECOTREE_H_ */
