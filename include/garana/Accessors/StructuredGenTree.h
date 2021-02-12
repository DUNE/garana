#ifndef GARANA_STRUCTURED_GENTREE_H
#define GARANA_STRUCTURED_GENTREE_H

//garana includes
#include "include/garana/Base/GenTree.h"
#include "include/garana/DataProducts/FSParticle.h"
#include "include/garana/DataProducts/GTruth.h"

//c++ includes
#include <vector>

namespace garana {

 class StructuredGenTree : public GenTree {

  public:

    StructuredGenTree();
    StructuredGenTree(TTree* tree);
    //let compile provide destructor

    //inherited from TreeReader
    bool SetBranchAddresses() override;

    //accessors inherited from GenTree
    UInt_t         NGen() const override;
    UInt_t         NFSParticles( UInt_t igen ) const override;
    Bool_t         IsGenie( UInt_t igen ) const override;
    Bool_t         IsCC( UInt_t igen ) const override;
    Int_t          NuPDG( UInt_t igen ) const override;
    TLorentzVector NuP( UInt_t igen) const override;
    TLorentzVector NuVertex( UInt_t igen) const override;
    Float_t        FSEnergy(UInt_t igen) const override;

    const std::vector<FSParticle>* GetParticles(UInt_t igen) const;

  private:

    // Declaration of leaf types

    std::vector<std::vector<FSParticle>>* fFSParticles = nullptr;
    std::vector<GTruth>* fGTruth = nullptr;

    //branches
    TBranch* b_GTruth = nullptr;
    TBranch* b_FSParticles = nullptr;

    //StucturedGenTree specific
    Bool_t   CheckFSRange(UInt_t igen) const;


 };
}//namespace

#endif
