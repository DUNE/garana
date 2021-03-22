/*
 * FlatG4Tree.h
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_FLATG4TREE_H_
#define GARANA_FLATG4TREE_H_

#include "garana/Base/G4Tree.h"
#include <map>

using std::vector;

namespace garana {

 class FlatG4Tree : public G4Tree {

  public:

	FlatG4Tree() {}
	FlatG4Tree(TTree* tree);
	FlatG4Tree(TTree* tree, char opt);
	// default dest'or

    // accessors inherited from G4Tree
	const UInt_t                  NSim()                                     const override;
    const bool                    IsPrimary(const UInt_t& iparticle)         const override;
    const Int_t                   PDG(const UInt_t& iparticle)               const override;
	const vector<TLorentzVector>* SimMom(const UInt_t& iparticle)                  override;
	const vector<TLorentzVector>* SimPos(const UInt_t& iparticle)                  override;
	const int                     ParentPDG(const UInt_t& iparticle)         const override;
	const int                     ProgenitorPDG(const UInt_t& iparticle)     const override;
	const int                     TrackID(const UInt_t& iparticle)           const override;
	const int                     ParentTrackID(const UInt_t& iparticle)     const override;
	const int                     ProgenitorTrackID(const UInt_t& iparticle) const override;

  protected:

    bool SetBranchAddresses() override;
    void SetVecs();
    void ClearVecs();
    void SetLimits();
    std::map<UInt_t, std::pair<UInt_t,UInt_t>> fLimits; ///< tree is completely flat so need first and last index
                                                       ///< for each array for a given particle

    // leaves and branches
    UInt_t           fNSim              = UINT_MAX; ///< number of G4 particles per event
    vector<UInt_t>*  fNPts              = nullptr;  ///< number of 4-vector "snapshots"
    vector<Int_t>*   fTrkID             = nullptr;  ///< particle's G4 trackID
    vector<Int_t>*   fPDG               = nullptr;  ///< particle's PDG code
    vector<Int_t>*   fParentPdg         = nullptr;  ///< particle parent's PDG code
    vector<Int_t>*   fProgenitorPdg     = nullptr;  ///< FS particle from gen stage that led to this one
    vector<Int_t>*   fParentTrackId     = nullptr;  ///< particle's parent's trackID
    vector<Int_t>*   fProgenitorTrackId = nullptr;  ///< FS particle from gen stage that led to this one
    vector<Int_t>*   fProcessI          = nullptr;  ///< process that produced the particle
    vector<Int_t>*   fProcessF          = nullptr;  ///< process that killed the particle
    vector<Float_t>* fX                 = nullptr;  ///< particle's x-position in lab frame [cm]
    vector<Float_t>* fY                 = nullptr;  ///< particle's y-position in lab frame [cm]
    vector<Float_t>* fZ                 = nullptr;  ///< particle's z-position in lab frame [cm]
    vector<Float_t>* fT                 = nullptr;  ///< particle's time in lab frame [ns]
    vector<Float_t>* fPx                = nullptr;  ///< particle's x-momentum in lab frame [GeV/c]
    vector<Float_t>* fPy                = nullptr;  ///< particle's y-momentum in lab frame [GeV/c]
    vector<Float_t>* fPz                = nullptr;  ///< particle's z-momentum in lab frame [GeV/c]
    vector<Float_t>* fE                 = nullptr;  ///< particle's total energy in lab frame [GeV]

    TBranch* b_NSim              = nullptr;
    TBranch* b_NPts              = nullptr;
    TBranch* b_TrkID             = nullptr;
    TBranch* b_PDG               = nullptr;
    TBranch* b_ParentPdg         = nullptr;
    TBranch* b_ProgenitorPdg     = nullptr;
    TBranch* b_ParentTrackId     = nullptr;
    TBranch* b_ProgenitorTrackId = nullptr;
    TBranch* b_ProcessI          = nullptr;
    TBranch* b_ProcessF          = nullptr;
    TBranch* b_X                 = nullptr;
    TBranch* b_Y                 = nullptr;
    TBranch* b_Z                 = nullptr;
    TBranch* b_T                 = nullptr;
    TBranch* b_Px                = nullptr;
    TBranch* b_Py                = nullptr;
    TBranch* b_Pz                = nullptr;
    TBranch* b_E                 = nullptr;

 };//class
}//namespace

#endif /* FLATG4TREE_H_ */
