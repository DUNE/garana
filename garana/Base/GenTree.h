#ifndef GARANA_GENTREE_H
#define GARANA_GENTREE_H

#include "garana/Base/TreeReader.h"

namespace garana{

 class GenTree : public TreeReader {

  public: // TODO: make everything protected?

   virtual ~GenTree() {};

   virtual const UInt_t          NGen()                      const = 0;
   virtual const UInt_t          NFSParticles( UInt_t igen ) const = 0;
   virtual const Bool_t          IsGenie( UInt_t igen )      const = 0;
   virtual const Bool_t          IsCC( UInt_t igen )         const = 0;
   virtual const Int_t           NuPDG( UInt_t igen )        const = 0;
   virtual       TLorentzVector* NuP( UInt_t igen)                 = 0;
   virtual       TLorentzVector* NuVertex( UInt_t igen)            = 0;
   virtual const Float_t         FSEnergy(UInt_t igen)       const = 0;

   const std::vector<Int_t>* GetGIndex() const;

   //inline static const std::string treename = "genTree";

  protected:

   const std::vector<Int_t>* fGIndex = nullptr;
   TBranch* b_GIndex = nullptr;

 }; //class
} //namespace

#endif //GenTree
