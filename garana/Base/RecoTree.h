/*
 * G4Tree.h
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_RECOTREE_H_
#define GARANA_RECOTREE_H_

#include "garana/Base/TreeReader.h"
#include "garana/DataProducts/Track.h"
#include "garana/DataProducts/Vertex.h"
#include "garana/DataProducts/Vee.h"
#include "garana/DataProducts/CaloCluster.h"


namespace garana {

  class RecoTree : public TreeReader {

    public:

	  virtual ~RecoTree() {};


	  // pure virtual methods
	  // sizes
	  virtual const size_t NTrack()      const = 0; ///< number of tracks in this event
	  virtual const size_t NVertex()     const = 0; ///< number of vertices in this event
	  virtual const size_t NVee()        const = 0; ///< number of vees in this event
	  virtual const size_t NCalCluster() const = 0; ///< number of ECal clusters in this event

	  // track
      virtual const TLorentzVector* TrackVertex(const size_t& itrack)        const = 0; ///< 4-position of track's assumed start point
      virtual const TLorentzVector* TrackEnd(const size_t& itrack)           const = 0; ///< 4-position of track's assumed end point
      virtual const size_t          NTrackHit(const size_t& itrack)          const = 0; ///< number of reconstructed hits used in track fit
      virtual const TVector3*       TrackMomBeg(const size_t& itrack)        const = 0; ///< momentum 3-vector as track's assumed start point
      virtual const TVector3*       TrackMomEnd(const size_t& itrack)        const = 0; ///< momentum 3-vector as track's assumed end point
      virtual const float           TrackVtxDirectionX(const size_t& itrack) const = 0; ///< x-direction cosine at track vertex
      virtual const float           TrackVtxDirectionY(const size_t& itrack) const = 0; ///< y-direction cosine at track vertex
      virtual const float           TrackVtxDirectionZ(const size_t& itrack) const = 0; ///< z-direction cosine at track vertex
      virtual const float           TrackEndDirectionX(const size_t& itrack) const = 0; ///< x-direction cosine at track end
      virtual const float           TrackEndDirectionY(const size_t& itrack) const = 0; ///< y-direction cosine at track end
      virtual const float           TrackEndDirectionZ(const size_t& itrack) const = 0; ///< z-direction cosine at track end
      virtual const float           TrackLenFwd(const size_t& itrack)        const = 0; ///< track length from forward fit
      virtual const float           TrackLenBkd(const size_t& itrack)        const = 0; ///< track length from backward fit
      virtual const float           TrackIonizFwd(const size_t& itrack)      const = 0; ///< track average ionization rate from forward fit
      virtual const float           TrackIonizBkd(const size_t& itrack)      const = 0; ///< track average ionization rate from backward fit
      virtual const int             TrackChiSqrFwd(const size_t& itrack)     const = 0; ///< chi-squared of track fit in forward direction
      virtual const int             TrackChiSqrBkd(const size_t& itrack)     const = 0; ///< chi-squared of track fit in backward direction
      virtual const int             TrackChgFwd(const size_t& itrack)        const = 0; ///< charge sign of track if current hypothesis correct
      virtual const int             TrackChgBkd(const size_t& itrack)        const = 0; ///< charge sign of track if current hypothesis wrong
      virtual void                  TrackParBeg(const size_t& itrack, float pars[5])    const = 0; ///< track fit parameters at the track's assumed start
      virtual void                  TrackParEnd(const size_t& itrack, float pars[5])    const = 0; ///< track fit parameters at the track's assumed end
      virtual void                  TrackCovarBeg(const size_t& itrack, float pars[15]) const = 0; ///< track fit covariance matrix (assume symmetry) at track's assumed start
      virtual void                  TrackCovarEnd(const size_t& itrack, float pars[15]) const = 0; ///< track fit covariance matrix (assume symmetry) at track's assumed end

      virtual const TLorentzVector*       TrackTruePosBeg(const size_t& itrack)       const = 0; ///< true 4-position at track vertex [cm,ns]
      virtual const TLorentzVector*       TrackTruePosEnd(const size_t& itrack)       const = 0; ///< true 4-position at track end [cm,ns]
      virtual const TLorentzVector*       TrackTrueMomBeg(const size_t& itrack)       const = 0; ///< true 4-momentum at track vertex [GeV/c,GeV]
      virtual const TLorentzVector*       TrackTrueMomEnd(const size_t& itrack)       const = 0; ///< true 4-momentum at track end [GeV/c,GeV]
	  virtual const float                 TrackTrueEnergy(const size_t& icluster)     const = 0; ///< total associated true energy deposited with ith cluster
	  virtual const size_t                TrackNTrueTrack(const size_t& icluster)     const = 0; ///< number of MCParticles associated with ith cluster
	  virtual const int                   TrackTrkIdMaxDeposit(const size_t& icluster)const = 0; ///< trackID of the MCParticle depositing the most energy in ith cluster
	  virtual const float                 TrackMaxDeposit(const size_t& icluster)     const = 0; ///< maximum true deposited energy from a single MCParticle
	          const float                 TrackMaxDepositFrac(const size_t& icluster) const;     ///< largest fraction of total energy contributed by single MCParticle
	  virtual const std::pair<int,float>* TrackTrueDeposit(const size_t& icluster, const size_t& itrack) const = 0; ///<


	  //vertex
      virtual const TLorentzVector* GetVertex(const size_t& ivertex)                          const = 0; ///< vertex 4-position for vertex with index ivertex
      virtual void                  VertexCovariance(const size_t& ivertex, float covar[][3]) const = 0; ///< given a vertex index, fill given position covariance matrix

      //vee
      virtual const TLorentzVector*         VeeVertex(const size_t& ivee)                       const = 0; ///< vertex 4-position for vee with index ivee
      virtual void                          VeeCovariance(const size_t& ivee, float covar[][3]) const = 0; ///< given a vee index, fill given position covariance matrix
      virtual const vector<TLorentzVector>* VeeMomentumPerHypothesis(const size_t& ivee)        const = 0; ///< 4-momentum for vee if it matches {Kshort, Lambda1, Lambda2}
      virtual const float                   VeeChiSquared(const size_t& ivee)                   const = 0;

      //calo cluster
	  virtual const TLorentzVector*   CalClustPosition(const size_t& icluster)       const = 0;
	  virtual const float             CalClustEnergy(const size_t& icluster)         const = 0; ///< reconstructed ECal cluster energy
	  virtual const float             CalClustEnergyError(const size_t& icluster)    const = 0;
	  virtual const float             CalClustTrueEnergy(const size_t& icluster)     const = 0; ///< total associated true energy deposited with ith cluster
	  virtual const size_t            CalClustNTrueTrack(const size_t& icluster)     const = 0; ///< number of MCParticles associated with ith cluster
	  virtual const int               CalClustTrkIdMaxDeposit(const size_t& icluster)const = 0; ///< trackID of the MCParticle depositing the most energy in ith cluster
	  virtual const float             CalClustMaxDeposit(const size_t& icluster)     const = 0; ///< maximum true deposited energy from a single MCParticle
	          const float             CalClustMaxDepositFrac(const size_t& icluster) const;     ///< largest fraction of total energy contributed by single MCParticle
	  virtual const std::pair<int,float>* CalClustTrueDeposit(const size_t& icluster, const size_t& itrack) const = 0; ///<
	  virtual const float             CalClustTimeDifference(const size_t& icluster) const = 0;
	  virtual const float*            CalClustShape(const size_t& icluster)          const = 0;
	  virtual const float             CalClustTheta(const size_t& icluster)          const = 0;
	  virtual const float             CalClustPhi(const size_t& icluster)            const = 0;
	  virtual const vector<TVector3>* CalClustEigenVecs(const size_t& icluster)      const = 0;

      // truth matching
      void GetTrackG4PIndices       (const size_t& itrk,    vector<UInt_t>& ig4ps  ) const; ///< given a track index, fill a given vector with matched G4 particle indices
      void GetVertexTrackIndices    (const size_t& ivtx,    vector<UInt_t>& itracks) const; ///< given a vertex index, fill a given vector with matched track indices
      void GetVeeTrackIndices       (const size_t& ivee,    vector<UInt_t>& itracks) const; ///< given a vee index, fill a given vector with matched G4 particle indices
      void GetCalClusterTrackIndices(const size_t& iclust,  vector<UInt_t>& itracks) const; ///< given a calocluster index, fill a given vector with matched track indices
      void GetCalClusterG4Indices   (const size_t& iclust,  vector<UInt_t>& ig4ps)   const; ///< given a calocluster index, fill a given vector with matched G4Particle indices

    protected:

      //associations
 	  vector<vector<UInt_t>>* fTrackG4PIndices        = nullptr;
 	  vector<vector<UInt_t>>* fVertTrackIndices       = nullptr;
 	  vector<vector<UInt_t>>* fVeeTrackIndices        = nullptr;
 	  vector<vector<UInt_t>>* fCalClusterTrackIndices = nullptr;
 	  vector<vector<UInt_t>>* fCalClusterG4Indices    = nullptr;

      TBranch*  b_TrackG4PIndices        = nullptr;
      TBranch*  b_VertTrackIndices       = nullptr;
      TBranch*  b_VeeTrackIndices        = nullptr;
      TBranch*  b_CalClusterTrackIndices = nullptr;
      TBranch*  b_CalClusterG4Indices    = nullptr;

  };//class
}//namespace

#endif /* GARANA_RECOTREE_H_ */
