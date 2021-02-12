/*
 * FlatGenTree.h
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_FLATGENTREE_H_
#define GARANA_FLATGENTREE_H_

#include "include/garana/Base/GenTree.h"
#include <vector>

namespace garana {

 class FlatGenTree : public GenTree {

  public:

	FlatGenTree();
	FlatGenTree(TTree* tree);

    //accessors inherited from GenTree
    UInt_t         NGen() const override;
    UInt_t         NFSParticles( UInt_t igen ) const override;
    Bool_t         IsGenie( UInt_t igen ) const override;
    Bool_t         IsCC( UInt_t igen ) const override;
    Int_t          NuPDG( UInt_t igen ) const override;
    TLorentzVector NuP( UInt_t igen) const override;
    TLorentzVector NuVertex( UInt_t igen) const override;
    Float_t        FSEnergy(UInt_t igen) const override;

  private:

    bool SetBranchAddresses() override;


    //final state particles
    std::vector<Int_t >*  fFSPdg = nullptr;     ///< particle PDG code
    std::vector<Float_t>* fFSX = nullptr;       ///< x-coordinate [cm]
    std::vector<Float_t>* fFSY = nullptr;       ///< y-coordinate [cm]
    std::vector<Float_t>* fFSZ = nullptr;       ///< z-coordinate [cm]
    std::vector<Float_t>* fFST = nullptr;       ///< time [ns]
    std::vector<Float_t>* fFSPx = nullptr;      ///< momentum, x-component [GeV/c]
    std::vector<Float_t>* fFSPy = nullptr;      ///< momentum, y-component [GeV/c]
    std::vector<Float_t>* fFSPz = nullptr;      ///< momentum, z-component [GeV/c]
    std::vector<Float_t>* fFSE = nullptr;       ///< total energy [GeV]

    TBranch* b_FSPdg = nullptr;
    TBranch* b_FSX = nullptr;
    TBranch* b_FSY = nullptr;
    TBranch* b_FSZ = nullptr;
    TBranch* b_FST = nullptr;
    TBranch* b_FSPx = nullptr;
    TBranch* b_FSPy = nullptr;
    TBranch* b_FSPz = nullptr;
    TBranch* b_FSE = nullptr;

 };//class
}//namespace

#endif /* FLATGENTREE_H_ */
