#ifndef GARANA_TREEREADER_H_
#define GARANA_TREEREADER_H_

// ROOT includes
#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TVector3.h>

// C++ includes
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <climits>

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::map;

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

    //static const std::string treename; problem when using shared libs?
    const std::string treename;

    char     fOpt    = 'r';
    TTree*   fTreeIn = nullptr; ///< pointer to the analyzed TTree or TChain
    TBranch* b_Event = nullptr;
    Int_t    fEvent  = -1; ///< event number for tree entry



 };//class
}//namespace

#endif /* GARANA_TREEREADER_H_ */
