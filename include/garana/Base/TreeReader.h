#ifndef GARANA_TREEREADER_H
#define GARANA_TREEREADER_H

#include <TTree.h>
#include <iostream>

namespace garana {
 class TreeReader {

  public:

	virtual ~TreeReader() {};

    void SetupRead(TTree* tree);
    TTree* GetInputTree();
    size_t NEntries() const;
    void GetEntry(Long64_t ientry) const;
    Int_t Event() const;
    virtual bool SetBranchAddresses() = 0;

  protected:

    TTree*  fTreeIn; ///< pointer to the analyzed TTree or TChain

    Int_t   fEvent; ///< event number for tree entry

    TBranch* b_Event;


 };
}
#endif
