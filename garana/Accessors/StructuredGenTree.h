#ifndef GARANA_STRUCTURED_GENTREE_H
#define GARANA_STRUCTURED_GENTREE_H

//garana includes
#include "garana/Base/GenTree.h"
#include "garana/DataProducts/FSParticle.h"
#include "garana/DataProducts/GTruth.h"

using std::vector;

namespace garana {

 class StructuredGenTree : public GenTree {

  public:

    StructuredGenTree() {}
    StructuredGenTree(TTree* tree);
    //let compile provide destructor

    ///< inherited from TreeReader
    bool SetBranchAddresses() override;

    ///< accessors inherited from GenTree (see garana/Base/GenTree.h for method descriptions)
    const UInt_t          NGen()                            const override;
    const UInt_t          NFSParticles(const UInt_t& igen ) const override;
    const Bool_t          IsGenie(const UInt_t& igen )      const override;

    const Int_t           NuPDG(const UInt_t& igen )        const override;
    const TLorentzVector* NuP(const UInt_t& igen)                 override;
    const TLorentzVector* NuVertex(const UInt_t& igen)            override;
    const Bool_t          IsCC(const UInt_t& igen )         const override;
    const int             ScatterCode(const UInt_t& igen)   const override;
    const int             InteractCode(const UInt_t& igen)  const override;

    const Int_t           TgtPDG(const UInt_t& igen )       const override;
    const TLorentzVector* TgtP4(const UInt_t& igen)         const override;
    const int             TgtZ(const UInt_t& igen )         const override;
    const int             TgtA(const UInt_t& igen )         const override;
    const int             HitNucPDG(const UInt_t& igen )    const override;
    const TLorentzVector* HitNucP4(const UInt_t& igen )     const override;

    const double          Q2(const UInt_t& igen )           const override;
    const double          q2(const UInt_t& igen )           const override;
    const double          W(const UInt_t& igen )            const override;
    const double          T(const UInt_t& igen )            const override;
    const double          X(const UInt_t& igen )            const override;
    const double          Y(const UInt_t& igen )            const override;
    const TLorentzVector* FSLeptonP4(const UInt_t& igen )   const override;
    const TLorentzVector* FSHadSystP4(const UInt_t& igen )  const override;

    const int             NumNuProton(const UInt_t& igen)   const override;
    const int             NumNuNeutron(const UInt_t& igen)  const override;
    const int             NumNuPi0(const UInt_t& igen)      const override;
    const int             NumNuPiPlus(const UInt_t& igen)   const override;
    const int             NumNuPiMinus(const UInt_t& igen)  const override;

    const Float_t         FSTotEnergy(const UInt_t& igen)                   const override;
    const Float_t         FSEnergy(const UInt_t& igen, const UInt_t& ifsp)  const override;
    const Float_t         FSPDG(const UInt_t& igen, const UInt_t& ifsp)     const override;
    const Int_t           FSTrackId(const UInt_t& igen, const UInt_t& ifsp) const override;

    const GTruth*             GetGTruth(const UInt_t& igen)    const;
    const vector<FSParticle>* GetParticles(const UInt_t& igen) const;


  private:

    // Declaration of leaf types

    vector<vector<FSParticle>>* fFSParticles = nullptr;
    vector<GTruth>*             fGTruth      = nullptr;

    //branches
    TBranch* b_GTruth = nullptr;
    TBranch* b_FSParticles = nullptr;

    //StucturedGenTree specific
    const Bool_t   CheckFSRange(const UInt_t& igen) const;

 };//class
}//namespace

#endif
