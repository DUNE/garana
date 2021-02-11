#ifndef GARANA_GENTREE_H
#define GARANA_GENTREE_H

#include "TreeReader.h"
#include "TLorentzVector.h"

namespace garana{

 class GenTree : public TreeReader {

  public:

   virtual ~GenTree() {};

   virtual UInt_t         NGen() const = 0;
   virtual UInt_t         NFSParticles( UInt_t igen ) const = 0;
   virtual Bool_t         IsGenie( UInt_t igen ) const = 0;
   virtual Bool_t         IsCC( UInt_t igen ) const = 0;
   virtual Int_t          NuPDG( UInt_t igen ) const = 0;
   virtual TLorentzVector NuP( UInt_t igen) const = 0;
   virtual TLorentzVector NuVertex( UInt_t igen) const = 0;
   virtual Float_t        FSEnergy(UInt_t igen) const = 0;

  protected:

   std::vector<Int_t>* fGIndex = nullptr;
   TBranch* b_GIndex = nullptr;

 }; //class
} //namespace
#endif //GenTree
