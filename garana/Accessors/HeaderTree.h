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

	  Int_t Run() const;
	  Int_t SubRun() const;
	  std::string* const TreeType() const;
	  void SetRun(const Int_t run);
	  void SetSubRun(const Int_t subrun);
	  void SetTreeType(std::string type);

   private:

	  bool SetBranchAddresses() override;

	  //leaf types
	  Int_t        fRun = -1;
	  Int_t        fSubRun = -1;
      std::string  fTreeType = "";
      std::string* fTreeTypePtr = &fTreeType;

	  //branches
	  TBranch* b_Run = nullptr;
	  TBranch* b_SubRun = nullptr;
	  TBranch* b_TreeType = nullptr;


  };//class
}//namespace
#endif /* HEADERTREE_H_ */
