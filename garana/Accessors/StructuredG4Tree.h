/*
 * StructuredG4Tree.h
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_STRUCTUREDG4TREE_H_
#define GARANA_STRUCTUREDG4TREE_H_

#include "garana/Base/G4Tree.h"
#include "garana/DataProducts/G4Particle.h"

using std::vector;

namespace garana {

 class StructuredG4Tree : public G4Tree {

   public:

	 StructuredG4Tree() {};
	 StructuredG4Tree(TTree* tree);
	// ~StructuredG4Tree(){}



	 const UInt_t                  NSim()                                     const override;
	 const UInt_t                  NPoints(const UInt_t& iparticle)           const override;
	 const vector<TLorentzVector>* SimMom(const UInt_t& iparticle)                  override;
	 const vector<TLorentzVector>* SimPos(const UInt_t& iparticle)                  override;
	 const bool                    IsPrimary(const UInt_t& iparticle)         const override;
	 const Int_t                   PDG(const UInt_t& iparticle)               const override;
	 const int                     ParentPDG(const UInt_t& iparticle)         const override;
	 const int                     ProgenitorPDG(const UInt_t& iparticle)     const override;
	 const int                     TrackID(const UInt_t& iparticle)           const override;
	 const int                     ParentTrackID(const UInt_t& iparticle)     const override;
	 const int                     ProgenitorTrackID(const UInt_t& iparticle) const override;
     const Int_t                   ProcessI(const UInt_t& iparticle)          const override;
     const Int_t                   ProcessF(const UInt_t& iparticle)          const override;

	 const G4Particle*             GetParticle(const UInt_t& iparticle) const;
	 //vector<G4Particle*>*      GetParticles();

   private:

	 //pure virtual function from TreeReader
	 bool SetBranchAddresses() override;


	 //leaves and branches
	 vector<G4Particle>*     fG4Particles   = nullptr;  ///< 'condensed' nusimdata::MCParticles from G4
     TBranch*                b_G4Particles  = nullptr;

     //G4Particle*   fG4p           = nullptr;
    // vector<G4Particle*>* fG4ps    = nullptr;

 };//class
}//namespace
#endif /* GARANA_STRUCTUREDG4TREE_H_ */
