/*
 * HeaderTree.h
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_HEADERTREE_H_
#define GARANA_HEADERTREE_H_

#include "garana/Base/TreeReader.h"
#include <string>

namespace garana{

  class HeaderTree : public TreeReader  {

   public:

	  HeaderTree();
	  HeaderTree(TTree* tree);
	  HeaderTree(TTree* tree, char opt);

	  Int_t const& Run()                  const;
	  Int_t const& SubRun()               const;
	  Int_t const& POT()                  const;
	  Int_t const& NSpills()              const;
	  const std::string* const TreeType() const;
	  TLorentzVector const& TpcCenter()   const;
	  std::string const& Geometry()       const;
	  void SetRun(const Int_t run);
	  void SetSubRun(const Int_t subrun);
	  void SetTreeType(std::string type);

   private:

	  bool SetBranchAddresses() override;

	  //leaf types
	  Int_t          fRun = -1;
	  Int_t          fSubRun = -1;
      Int_t          fPOT = -1;
      Int_t          fNSpills = -1;
	  TLorentzVector fTpcCenter;
      std::string    fGeometry;
      std::string    fTreeType;
      std::string*   fTreeTypePtr = &fTreeType;
      std::string*   fGeometryPtr = &fGeometry;

	  //branches
	  TBranch* b_Run       = nullptr;
	  TBranch* b_SubRun    = nullptr;
	  TBranch* b_TreeType  = nullptr;
	  TBranch* b_TpcCenter = nullptr;
	  TBranch* b_POT       = nullptr;
	  TBranch* b_NSpills   = nullptr;
	  TBranch* b_Geometry  = nullptr;

  };//class
}//namespace
#endif /* HEADERTREE_H_ */
