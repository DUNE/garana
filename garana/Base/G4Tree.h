/*
 * G4Tree.h
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_G4TREE_H_
#define GARANA_G4TREE_H_

#include "garana/Base/TreeReader.h"

using std::vector;

namespace garana {

  class G4Tree : public TreeReader {

    public:

	  // default const'or
	  virtual ~G4Tree() {};

	  // pure virtual functions for structured or flat g4Tree
	  virtual const UInt_t                  NSim()                                     const = 0; ///< number of particles
	  virtual const UInt_t                  NPoints(const UInt_t& iparticle)           const = 0; ///< number of G4 steps (i.e. trajectory points)
	  virtual const UInt_t                  NRegions(const UInt_t& iparticle)          const = 0; ///< number of regions traversed by particle
	  virtual const Int_t                   Region(const UInt_t& iparticle, const UInt_t& iregion)              const = 0; ///< region number
	  virtual const vector<const TLorentzVector*>* SimMomEnter(const UInt_t& iparticle)const = 0; ///< particle 4-momentum at entry point, all regions
	  virtual const vector<const TLorentzVector*>* SimMomExit(const UInt_t& iparticle) const = 0; ///< particle 4-momentum at exit point, all regions
	  virtual const vector<const TLorentzVector*>* SimPosEnter(const UInt_t& iparticle)const = 0; ///< particle 4-position at entry point, all regions
	  virtual const vector<const TLorentzVector*>* SimPosExit(const UInt_t& iparticle) const = 0; ///< particle 4-position at exit point, all regions
	  virtual const TLorentzVector*         SimMomEnter(const UInt_t& iparticle, const UInt_t& iregion)const = 0; ///< particle 4-momentum at entry point in region
	  virtual const TLorentzVector*         SimMomExit(const UInt_t& iparticle, const UInt_t& iregion) const = 0; ///< particle 4-momentum at exit point in region
	  virtual const TLorentzVector*         SimPosEnter(const UInt_t& iparticle, const UInt_t& iregion)const = 0; ///< particle 4-position at entry point in region
	  virtual const TLorentzVector*         SimPosExit(const UInt_t& iparticle, const UInt_t& iregion) const = 0; ///< particle 4-position at exit point in region
      virtual const bool                    IsPrimary(const UInt_t& iparticle)         const = 0; ///< did particle come from generator?
      virtual const Int_t                   PDG(const UInt_t& iparticle)               const = 0; ///< particle PDG code
      virtual const int                     ParentPDG(const UInt_t& iparticle)         const = 0; ///< parent particle's PDG code
      virtual const int                     ProgenitorPDG(const UInt_t& iparticle)     const = 0; ///< PDG of primary that led this one
      virtual const int                     TrackID(const UInt_t& iparticle)           const = 0; ///< G4 track ID (can be <0 if it fell below trking threshold)
      virtual const int                     ParentTrackID(const UInt_t& iparticle)     const = 0; ///< G4 track ID of parent particle
      virtual const int                     ProgenitorTrackID(const UInt_t& iparticle) const = 0; ///< G4 track ID of primary that led this one
      virtual const Int_t                   ProcessI(const UInt_t& iparticle)          const = 0; ///< code for process that created this one
      virtual const Int_t                   ProcessF(const UInt_t& iparticle)          const = 0; ///< code for process that killed this one

      // truth matching
	  UInt_t const&                         GetTruthIndex(UInt_t iparticle) const; ///< index in gen tree subentry to truth match to this

    protected:

		 vector<UInt_t>*         fG4TruthIndex  = nullptr;
		 vector<UInt_t>*         fG4FSIndex     = nullptr;
		 TBranch*                b_G4TruthIndex = nullptr;
		 TBranch*                b_G4FSIndex    = nullptr;
  };//class
}//namespace

#endif /* GARANA_G4TREE_H_ */
