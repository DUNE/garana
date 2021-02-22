#ifndef GARANA_STRUCTURED_GENTREE_H
#define GARANA_STRUCTURED_GENTREE_H

//garana includes
#include "garana/Base/GenTree.h"
#include "garana/DataProducts/FSParticle.h"
#include "garana/DataProducts/GTruth.h"

namespace garana {

 class StructuredGenTree : public GenTree {

  public:

    StructuredGenTree() {}
    StructuredGenTree(TTree* tree);
    //let compile provide destructor

    //inherited from TreeReader
    bool SetBranchAddresses() override;

    //accessors inherited from GenTree
    const UInt_t    NGen()                      const override;
    const UInt_t    NFSParticles( UInt_t igen ) const override;
    const Bool_t    IsGenie( UInt_t igen )      const override;
    const Bool_t    IsCC( UInt_t igen )         const override;
    const Int_t     NuPDG( UInt_t igen )        const override;
    TLorentzVector* NuP( UInt_t igen)                override;
    TLorentzVector* NuVertex( UInt_t igen)           override;
    const Float_t   FSEnergy(UInt_t igen)       const override;

    const GTruth* GetGTruth(UInt_t igen) const;
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


 };//class
}//namespace

#endif
