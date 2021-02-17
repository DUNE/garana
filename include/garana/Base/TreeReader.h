#ifndef GARANA_TREEREADER_H
#define GARANA_TREEREADER_H

#include <TFile.h>
#include <TTree.h>
#include <iostream>

namespace garana {
 class TreeReader {

  public:

	virtual ~TreeReader() {};

    void SetupRead(TTree* tree);
    TTree* GetInputTree();
    size_t NEntries() const;
    virtual void GetEntry(UInt_t ientry);
    Int_t Event() const;
    const TObjArray* GetBranchList() const;
    void Fill();
    void Write();
    void CheckOpt(char opt);
    bool BlockWrite() const;

    virtual bool SetBranchAddresses() = 0;

  protected:

    char     fOpt    = 'r';
    TTree*   fTreeIn = nullptr; ///< pointer to the analyzed TTree or TChain
    TBranch* b_Event = nullptr;
    Int_t    fEvent  = -1; ///< event number for tree entry

 };//class
}
#endif
